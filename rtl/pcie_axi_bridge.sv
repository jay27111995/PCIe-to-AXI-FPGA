//-----------------------------------------------------------------------------
// pcie_axi_bridge.sv - Bidirectional PCIe to AXI Bridge
//
// Handles both directions:
//   1. PCIe -> AXI Slave: Host BAR access to FPGA registers/memory
//   2. AXI Master -> PCIe: FPGA-initiated access to host memory
//
// Features:
//   - TX arbitration between BAR completions, host MRd, host MWr, MSI-X
//   - Credit management via rtile_crdt
//   - CplD routing back to AXI master initiator
//
// The AXI master port can be used by any module needing host memory access
// (DMA engines, scatter-gather controllers, etc.)
//-----------------------------------------------------------------------------
module pcie_axi_bridge
    import rtile_pkg::*;
#(
    parameter int AXI_ADDR_W = 32,
    parameter int AXI_DATA_W = 64
)(
    input  logic clk,
    input  logic rst_n,

    //=========================================================================
    // PCIe R-Tile Interface (directly connects to R-Tile IP)
    //=========================================================================
    input  logic [127:0] rx_st_hdr,
    input  logic [255:0] rx_st_data,
    input  logic         rx_st_sop,
    input  logic         rx_st_eop,
    input  logic         rx_st_hvalid,
    input  logic         rx_st_dvalid,
    input  logic [2:0]   rx_st_bar,
    output logic         rx_st_ready,

    output logic [127:0] tx_st_hdr,
    output logic [255:0] tx_st_data,
    output logic         tx_st_sop,
    output logic         tx_st_eop,
    output logic         tx_st_hvalid,
    output logic         tx_st_dvalid,
    input  logic         tx_st_ready,

    // Credits (directly connects to R-Tile IP)
    output logic [2:0]   rx_hcrdt_init,
    output logic [2:0]   rx_hcrdt_update,
    output logic [5:0]   rx_hcrdt_update_cnt,
    output logic [2:0]   rx_dcrdt_init,
    output logic [2:0]   rx_dcrdt_update,
    output logic [11:0]  rx_dcrdt_update_cnt,
    input  logic [2:0]   tx_hcrdt_init,
    output logic [2:0]   tx_hcrdt_init_ack,
    input  logic [2:0]   tx_hcrdt_update,
    input  logic [5:0]   tx_hcrdt_update_cnt,
    input  logic [2:0]   tx_dcrdt_init,
    output logic [2:0]   tx_dcrdt_init_ack,
    input  logic [2:0]   tx_dcrdt_update,
    input  logic [11:0]  tx_dcrdt_update_cnt,

    input  logic         link_up,
    input  logic [5:0]   ltssm_state,

    //=========================================================================
    // AXI Slave Interface - BAR access (host reads/writes FPGA)
    // Connect to: register files, SRAM, FIFOs, etc.
    //=========================================================================
    output logic [AXI_ADDR_W-1:0]   s_axi_awaddr,
    output logic                    s_axi_awvalid,
    input  logic                    s_axi_awready,
    output logic [AXI_DATA_W-1:0]   s_axi_wdata,
    output logic [AXI_DATA_W/8-1:0] s_axi_wstrb,
    output logic                    s_axi_wvalid,
    input  logic                    s_axi_wready,
    input  logic [1:0]              s_axi_bresp,
    input  logic                    s_axi_bvalid,
    output logic                    s_axi_bready,
    output logic [AXI_ADDR_W-1:0]   s_axi_araddr,
    output logic                    s_axi_arvalid,
    input  logic                    s_axi_arready,
    input  logic [AXI_DATA_W-1:0]   s_axi_rdata,
    input  logic [1:0]              s_axi_rresp,
    input  logic                    s_axi_rvalid,
    output logic                    s_axi_rready,

    //=========================================================================
    // AXI Master Interface - Host memory access (FPGA reads/writes host)
    // Connect to: DMA engines, scatter-gather controllers, etc.
    //=========================================================================
    input  logic [63:0]             m_axi_awaddr,
    input  logic                    m_axi_awvalid,
    output logic                    m_axi_awready,
    input  logic [AXI_DATA_W-1:0]   m_axi_wdata,
    input  logic [AXI_DATA_W/8-1:0] m_axi_wstrb,
    input  logic                    m_axi_wvalid,
    output logic                    m_axi_wready,
    output logic [1:0]              m_axi_bresp,
    output logic                    m_axi_bvalid,
    input  logic                    m_axi_bready,
    input  logic [63:0]             m_axi_araddr,
    input  logic                    m_axi_arvalid,
    output logic                    m_axi_arready,
    output logic [AXI_DATA_W-1:0]   m_axi_rdata,
    output logic [1:0]              m_axi_rresp,
    output logic                    m_axi_rvalid,
    input  logic                    m_axi_rready,

    //=========================================================================
    // MSI-X Interface (directly connects to interrupt controller)
    //=========================================================================
    input  logic        msix_valid,
    output logic        msix_ready,
    input  logic [63:0] msix_addr,
    input  logic [31:0] msix_data,

    //=========================================================================
    // Debug Interface
    //=========================================================================
    output logic [3:0]  dbg_tx_state
);

    //=========================================================================
    // Credit Manager
    //=========================================================================
    logic tx_cpl_hdr_ok, tx_cpl_data_ok;
    logic tx_cpl_hdr_dec, tx_cpl_data_dec;

    rtile_crdt u_crdt (
        .clk, .rst_n,
        .rx_hcrdt_init, .rx_hcrdt_update, .rx_hcrdt_update_cnt,
        .rx_dcrdt_init, .rx_dcrdt_update, .rx_dcrdt_update_cnt,
        .tx_hcrdt_init, .tx_hcrdt_init_ack, .tx_hcrdt_update, .tx_hcrdt_update_cnt,
        .tx_dcrdt_init, .tx_dcrdt_init_ack, .tx_dcrdt_update, .tx_dcrdt_update_cnt,
        .rx_cpl_hdr_ret(1'b0), .rx_cpl_data_ret(1'b0), .rx_cpl_data_cnt(12'b0),
        .tx_cpl_hdr_ok, .tx_cpl_data_ok,
        .tx_cpl_hdr_dec, .tx_cpl_data_dec, .tx_cpl_data_amt(12'd1),
        .init_done()
    );

    //=========================================================================
    // RX: Decode incoming TLPs
    //=========================================================================
    wire [2:0]  rx_fmt  = hdr_fmt(rx_st_hdr);
    wire [4:0]  rx_type = hdr_type(rx_st_hdr);
    wire [9:0]  rx_len  = hdr_len(rx_st_hdr);
    wire [15:0] rx_rid  = hdr_rid(rx_st_hdr);
    wire [7:0]  rx_tag  = hdr_tag(rx_st_hdr);
    wire [3:0]  rx_fbe  = hdr_fbe(rx_st_hdr);
    wire [3:0]  rx_lbe  = hdr_lbe(rx_st_hdr);
    wire [63:0] rx_addr = is_4dw(rx_fmt) ? hdr_addr64(rx_st_hdr) : {32'b0, hdr_addr32(rx_st_hdr)};

    wire rx_is_mrd  = rx_st_hvalid && rx_st_sop && (rx_type == 5'b00000) && !has_data(rx_fmt);
    wire rx_is_mwr  = rx_st_hvalid && rx_st_sop && (rx_type == 5'b00000) && has_data(rx_fmt);
    wire rx_is_cpld = rx_st_hvalid && rx_st_sop && (rx_type == 5'b01010) && has_data(rx_fmt);

    wire [7:0] cpl_rx_tag = rx_st_hdr[47:40];
    wire [7:0] wstrb_from_be = {rx_lbe, rx_fbe};

    //=========================================================================
    // Completer ID Auto-Capture
    // Capture our BDF from the first incoming TLP after link_up.
    // Host's Requester ID tells us our bus number (we're bus = host_bus + 1).
    //=========================================================================
    logic [15:0] completer_id;
    logic        completer_id_valid;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            completer_id <= 16'h0000;
            completer_id_valid <= 0;
        end else if (!link_up) begin
            // Reset on link down so we re-capture after re-enumeration
            completer_id_valid <= 0;
        end else if (!completer_id_valid && rx_st_hvalid && rx_st_sop) begin
            // First TLP after link_up - capture our BDF
            // Host's bus is rx_rid[15:8], we're typically on the next bus
            // Device and function are 0 for single-function endpoint
            completer_id <= {rx_rid[15:8] + 8'd1, 8'h00};
            completer_id_valid <= 1;
        end
    end

    //=========================================================================
    // Host Memory Read (AXI Master AR -> PCIe MRd -> CplD -> AXI Master R)
    // Translates AXI read requests into PCIe MRd TLPs
    //=========================================================================
    logic [63:0] host_mrd_addr;
    logic [7:0]  host_mrd_tag;
    logic        host_mrd_pending;   // Request waiting to be sent
    logic        host_mrd_inflight;  // MRd TLP sent, waiting for CplD

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            m_axi_arready <= 1;
            m_axi_rvalid <= 0;
            m_axi_rresp <= AXI_OKAY;
            host_mrd_pending <= 0;
            host_mrd_inflight <= 0;
            host_mrd_tag <= 0;
        end else begin
            // Accept new read request from AXI master
            if (m_axi_arvalid && m_axi_arready && !host_mrd_pending) begin
                host_mrd_addr <= m_axi_araddr;
                host_mrd_pending <= 1;
                host_mrd_tag <= host_mrd_tag + 1;
                m_axi_arready <= 0;
            end

            // TX sent the MRd TLP
            if (host_mrd_pending && host_mrd_ready_pulse) begin
                host_mrd_pending <= 0;
                host_mrd_inflight <= 1;
            end

            // Receive CplD from host
            if (host_mrd_inflight && rx_is_cpld && cpl_rx_tag == host_mrd_tag) begin
                m_axi_rdata <= rx_st_data[63:0];
                m_axi_rvalid <= 1;
                host_mrd_inflight <= 0;
                m_axi_arready <= 1;
            end

            // AXI R handshake complete
            if (m_axi_rvalid && m_axi_rready) begin
                m_axi_rvalid <= 0;
            end
        end
    end

    //=========================================================================
    // Host Memory Write (AXI Master AW+W -> PCIe MWr -> AXI Master B)
    // Translates AXI write requests into PCIe MWr TLPs
    //=========================================================================
    logic [63:0] host_mwr_addr;
    logic [63:0] host_mwr_data;
    logic        host_mwr_pending;  // Request waiting to be sent

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            m_axi_awready <= 1;
            m_axi_wready <= 1;
            m_axi_bvalid <= 0;
            m_axi_bresp <= AXI_OKAY;
            host_mwr_pending <= 0;
        end else begin
            // Accept new write request from AXI master
            if (m_axi_awvalid && m_axi_wvalid && m_axi_awready && !host_mwr_pending) begin
                host_mwr_addr <= m_axi_awaddr;
                host_mwr_data <= m_axi_wdata;
                host_mwr_pending <= 1;
                m_axi_awready <= 0;
                m_axi_wready <= 0;
            end

            // TX sent the MWr TLP - return B response
            if (host_mwr_pending && host_mwr_ready_pulse) begin
                host_mwr_pending <= 0;
                m_axi_bvalid <= 1;
            end

            // AXI B handshake complete
            if (m_axi_bvalid && m_axi_bready) begin
                m_axi_bvalid <= 0;
                m_axi_awready <= 1;
                m_axi_wready <= 1;
            end
        end
    end

    //=========================================================================
    // TX State Machine - Arbitrates between different TX sources
    //=========================================================================
    typedef enum logic [3:0] {
        TX_IDLE,
        TX_BAR_WR_ADDR,
        TX_BAR_WR_RESP,
        TX_BAR_RD_ADDR,
        TX_BAR_RD_DATA,
        TX_BAR_CPL,
        TX_HOST_MRD,
        TX_HOST_MWR,
        TX_MSIX,
        TX_SEND       // Wait for tx_st_ready handshake
    } tx_state_e;

    tx_state_e tx_state;

    // Pulses to signal host memory request consumed by TX
    logic host_mrd_ready_pulse;
    logic host_mwr_ready_pulse;

    // BAR completion info (saved from RX)
    logic [15:0] bar_req_rid;
    logic [7:0]  bar_req_tag;
    logic [6:0]  bar_req_lower_addr;
    logic [63:0] bar_cpl_data;
    logic [1:0]  bar_cpl_status;

    // TX header/data registers
    logic [127:0] tx_hdr_r;
    logic [63:0]  tx_data_r;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tx_state <= TX_IDLE;
            s_axi_awvalid <= 0;
            s_axi_wvalid <= 0;
            s_axi_bready <= 0;
            s_axi_arvalid <= 0;
            s_axi_rready <= 0;
            tx_st_hvalid <= 0;
            tx_st_dvalid <= 0;
            tx_st_sop <= 0;
            tx_st_eop <= 0;
            tx_cpl_hdr_dec <= 0;
            tx_cpl_data_dec <= 0;
            msix_ready <= 0;
            host_mrd_ready_pulse <= 0;
            host_mwr_ready_pulse <= 0;
        end else begin
            tx_cpl_hdr_dec <= 0;
            tx_cpl_data_dec <= 0;
            msix_ready <= 0;
            host_mrd_ready_pulse <= 0;
            host_mwr_ready_pulse <= 0;

            case (tx_state)
                TX_IDLE: begin
                    tx_st_hvalid <= 0;
                    tx_st_dvalid <= 0;
                    tx_st_sop <= 0;
                    tx_st_eop <= 0;

                    // Priority: BAR requests > Host MRd > Host MWr > MSI-X
                    if (rx_is_mwr && rx_st_bar == 3'd0) begin
                        s_axi_awaddr <= rx_addr[AXI_ADDR_W-1:0];
                        s_axi_awvalid <= 1;
                        s_axi_wdata <= rx_st_data[AXI_DATA_W-1:0];
                        s_axi_wstrb <= wstrb_from_be;
                        s_axi_wvalid <= 1;
                        tx_state <= TX_BAR_WR_ADDR;
                    end
                    else if (rx_is_mrd && rx_st_bar == 3'd0) begin
                        bar_req_rid <= rx_rid;
                        bar_req_tag <= rx_tag;
                        bar_req_lower_addr <= rx_addr[6:0];
                        s_axi_araddr <= rx_addr[AXI_ADDR_W-1:0];
                        s_axi_arvalid <= 1;
                        tx_state <= TX_BAR_RD_ADDR;
                    end
                    else if (host_mrd_pending) begin
                        tx_state <= TX_HOST_MRD;
                    end
                    else if (host_mwr_pending) begin
                        tx_state <= TX_HOST_MWR;
                    end
                    else if (msix_valid) begin
                        tx_state <= TX_MSIX;
                    end
                end

                //-------------------------------------------------------------
                // BAR Write: Host writes to FPGA via PCIe MWr
                //-------------------------------------------------------------
                TX_BAR_WR_ADDR: begin
                    if (s_axi_awready) s_axi_awvalid <= 0;
                    if (s_axi_wready)  s_axi_wvalid <= 0;
                    if ((s_axi_awready || !s_axi_awvalid) && 
                        (s_axi_wready || !s_axi_wvalid)) begin
                        s_axi_bready <= 1;
                        tx_state <= TX_BAR_WR_RESP;
                    end
                end

                TX_BAR_WR_RESP: begin
                    if (s_axi_bvalid) begin
                        s_axi_bready <= 0;
                        tx_state <= TX_IDLE;
                    end
                end

                //-------------------------------------------------------------
                // BAR Read: Host reads from FPGA via PCIe MRd -> CplD
                //-------------------------------------------------------------
                TX_BAR_RD_ADDR: begin
                    if (s_axi_arready) begin
                        s_axi_arvalid <= 0;
                        s_axi_rready <= 1;
                        tx_state <= TX_BAR_RD_DATA;
                    end
                end

                TX_BAR_RD_DATA: begin
                    if (s_axi_rvalid) begin
                        s_axi_rready <= 0;
                        bar_cpl_data <= s_axi_rdata;
                        bar_cpl_status <= s_axi_rresp;
                        tx_state <= TX_BAR_CPL;
                    end
                end

                TX_BAR_CPL: begin
                    // Build CplD TLP header
                    tx_st_sop <= 1;
                    tx_st_eop <= 1;
                    tx_st_hvalid <= 1;
                    tx_st_dvalid <= 1;
                    tx_cpl_hdr_dec <= 1;
                    tx_cpl_data_dec <= 1;
                    tx_hdr_r <= {
                        // DW0: Fmt=010 (3DW+data), Type=01010 (CplD), Length=2DW
                        {3'b010, 5'b01010, 8'b0, 6'b0, 10'd2},
                        // DW1: Completer ID, Status, Byte Count (8 bytes)
                        {completer_id, (bar_cpl_status == AXI_OKAY) ? 3'b000 : 3'b001, 1'b0, 12'd8},
                        // DW2: Requester ID, Tag, Lower Address
                        {bar_req_rid, bar_req_tag, 1'b0, bar_req_lower_addr},
                        // DW3: unused for 3DW header
                        32'b0
                    };
                    tx_data_r <= bar_cpl_data;
                    tx_state <= TX_SEND;
                end

                //-------------------------------------------------------------
                // Host Memory Read: FPGA reads from host via PCIe MRd
                //-------------------------------------------------------------
                TX_HOST_MRD: begin
                    // Build MRd TLP header (4DW, no data)
                    tx_st_sop <= 1;
                    tx_st_eop <= 1;
                    tx_st_hvalid <= 1;
                    tx_st_dvalid <= 0;
                    host_mrd_ready_pulse <= 1;
                    tx_hdr_r <= {
                        // DW0: Fmt=001 (4DW no data), Type=00000 (MRd), Length=2DW
                        {3'b001, 5'b00000, 8'b0, 6'b0, 10'd2},
                        // DW1: Requester ID (us), Tag, First/Last BE
                        {completer_id, host_mrd_tag, 4'hF, 4'hF},
                        // DW2: Address[63:32]
                        host_mrd_addr[63:32],
                        // DW3: Address[31:2], reserved
                        {host_mrd_addr[31:2], 2'b00}
                    };
                    tx_data_r <= 64'b0;
                    tx_state <= TX_SEND;
                end

                //-------------------------------------------------------------
                // Host Memory Write: FPGA writes to host via PCIe MWr
                //-------------------------------------------------------------
                TX_HOST_MWR: begin
                    // Build MWr TLP header (4DW with data)
                    tx_st_sop <= 1;
                    tx_st_eop <= 1;
                    tx_st_hvalid <= 1;
                    tx_st_dvalid <= 1;
                    host_mwr_ready_pulse <= 1;
                    tx_hdr_r <= {
                        // DW0: Fmt=011 (4DW+data), Type=00000 (MWr), Length=2DW
                        {3'b011, 5'b00000, 8'b0, 6'b0, 10'd2},
                        // DW1: Requester ID (us), Tag=0, First/Last BE
                        {completer_id, 8'h00, 4'hF, 4'hF},
                        // DW2: Address[63:32]
                        host_mwr_addr[63:32],
                        // DW3: Address[31:2], reserved
                        {host_mwr_addr[31:2], 2'b00}
                    };
                    tx_data_r <= host_mwr_data;
                    tx_state <= TX_SEND;
                end

                //-------------------------------------------------------------
                // MSI-X: Send interrupt to host
                //-------------------------------------------------------------
                TX_MSIX: begin
                    // Build MSI-X MWr TLP header (4DW with 1DW data)
                    tx_st_sop <= 1;
                    tx_st_eop <= 1;
                    tx_st_hvalid <= 1;
                    tx_st_dvalid <= 1;
                    msix_ready <= 1;
                    tx_hdr_r <= {
                        // DW0: Fmt=011 (4DW+data), Type=00000 (MWr), Length=1DW
                        {3'b011, 5'b00000, 8'b0, 6'b0, 10'd1},
                        // DW1: Requester ID (us), Tag=0, First/Last BE
                        {completer_id, 8'h00, 4'hF, 4'hF},
                        // DW2: MSI-X address[63:32]
                        msix_addr[63:32],
                        // DW3: MSI-X address[31:2], reserved
                        {msix_addr[31:2], 2'b00}
                    };
                    tx_data_r <= {32'b0, msix_data};
                    tx_state <= TX_SEND;
                end

                //-------------------------------------------------------------
                // TX_SEND: Wait for R-Tile to accept the TLP
                //-------------------------------------------------------------
                TX_SEND: begin
                    if (tx_st_ready) begin
                        // R-Tile accepted the TLP
                        tx_st_hvalid <= 0;
                        tx_st_dvalid <= 0;
                        tx_st_sop <= 0;
                        tx_st_eop <= 0;
                        tx_state <= TX_IDLE;
                    end
                    // Keep valid signals asserted while waiting
                end
            endcase
        end
    end

    //=========================================================================
    // TX Output
    //=========================================================================
    assign tx_st_hdr = tx_hdr_r;
    assign tx_st_data = {192'b0, tx_data_r};
    
    // Only accept new RX TLPs when in IDLE state
    assign rx_st_ready = (tx_state == TX_IDLE);
    
    // Debug output
    assign dbg_tx_state = tx_state;

endmodule
