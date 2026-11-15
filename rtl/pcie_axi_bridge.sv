//-----------------------------------------------------------------------------
// pcie_axi_bridge.sv - Bidirectional PCIe to AXI Bridge
//
// Handles both directions:
//   1. PCIe → AXI Slave: Host BAR access to FPGA registers/memory
//   2. AXI Master → PCIe: DMA engine access to host memory
//
// Also handles:
//   - TX arbitration between BAR completions, DMA MRd, DMA MWr, MSI-X
//   - Credit management
//   - CplD routing back to DMA
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
    // PCIe R-Tile Interface
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

    // Credits
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
    // AXI Slave - BAR access (host reads/writes FPGA)
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
    // AXI Master - DMA to host memory
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
    // MSI-X Interface
    //=========================================================================
    input  logic        msix_valid,
    output logic        msix_ready,
    input  logic [63:0] msix_addr,
    input  logic [31:0] msix_data
);

    assign rx_st_ready = 1'b1;

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
    // DMA MRd: Host memory read (AXI AR → PCIe MRd → CplD → AXI R)
    //=========================================================================
    logic [63:0] dma_mrd_addr_r;
    logic [7:0]  dma_mrd_tag;
    logic        dma_mrd_valid;  // Request pending
    logic        dma_mrd_sent;   // MRd TLP sent, waiting for CplD

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            m_axi_arready <= 1;
            m_axi_rvalid <= 0;
            m_axi_rresp <= AXI_OKAY;
            dma_mrd_valid <= 0;
            dma_mrd_sent <= 0;
            dma_mrd_tag <= 0;
        end else begin
            // Accept new read request
            if (m_axi_arvalid && m_axi_arready && !dma_mrd_valid) begin
                dma_mrd_addr_r <= m_axi_araddr;
                dma_mrd_valid <= 1;
                dma_mrd_tag <= dma_mrd_tag + 1;
                m_axi_arready <= 0;
            end

            // TX sent the MRd
            if (dma_mrd_valid && dma_mrd_ready_pulse) begin
                dma_mrd_valid <= 0;
                dma_mrd_sent <= 1;
            end

            // Receive CplD
            if (dma_mrd_sent && rx_is_cpld && cpl_rx_tag == dma_mrd_tag) begin
                m_axi_rdata <= rx_st_data[63:0];
                m_axi_rvalid <= 1;
                dma_mrd_sent <= 0;
                m_axi_arready <= 1;
            end

            // R handshake
            if (m_axi_rvalid && m_axi_rready) begin
                m_axi_rvalid <= 0;
            end
        end
    end

    //=========================================================================
    // DMA MWr: Host memory write (AXI AW+W → PCIe MWr → AXI B)
    //=========================================================================
    logic [63:0] dma_mwr_addr_r;
    logic [63:0] dma_mwr_data_r;
    logic        dma_mwr_valid;  // Request pending

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            m_axi_awready <= 1;
            m_axi_wready <= 1;
            m_axi_bvalid <= 0;
            m_axi_bresp <= AXI_OKAY;
            dma_mwr_valid <= 0;
        end else begin
            // Accept new write request
            if (m_axi_awvalid && m_axi_wvalid && m_axi_awready && !dma_mwr_valid) begin
                dma_mwr_addr_r <= m_axi_awaddr;
                dma_mwr_data_r <= m_axi_wdata;
                dma_mwr_valid <= 1;
                m_axi_awready <= 0;
                m_axi_wready <= 0;
            end

            // TX sent the MWr - return B response
            if (dma_mwr_valid && dma_mwr_ready_pulse) begin
                dma_mwr_valid <= 0;
                m_axi_bvalid <= 1;
            end

            // B handshake
            if (m_axi_bvalid && m_axi_bready) begin
                m_axi_bvalid <= 0;
                m_axi_awready <= 1;
                m_axi_wready <= 1;
            end
        end
    end

    //=========================================================================
    // TX Arbiter
    //=========================================================================
    typedef enum logic [3:0] {
        TX_IDLE,
        TX_BAR_WR_ADDR,
        TX_BAR_WR_RESP,
        TX_BAR_RD_ADDR,
        TX_BAR_RD_DATA,
        TX_BAR_CPL,
        TX_DMA_MRD,
        TX_DMA_MWR,
        TX_MSIX
    } tx_state_e;

    tx_state_e tx_state;

    // Pulses to signal DMA request consumed
    logic dma_mrd_ready_pulse;
    logic dma_mwr_ready_pulse;

    // BAR completion info
    logic [15:0] bar_req_rid;
    logic [7:0]  bar_req_tag;
    logic [6:0]  bar_req_lower_addr;
    logic [63:0] bar_cpl_data;
    logic [1:0]  bar_cpl_status;

    // TX registers
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
            dma_mrd_ready_pulse <= 0;
            dma_mwr_ready_pulse <= 0;
        end else begin
            tx_cpl_hdr_dec <= 0;
            tx_cpl_data_dec <= 0;
            msix_ready <= 0;
            dma_mrd_ready_pulse <= 0;
            dma_mwr_ready_pulse <= 0;

            case (tx_state)
                TX_IDLE: begin
                    tx_st_hvalid <= 0;
                    tx_st_dvalid <= 0;
                    tx_st_sop <= 0;
                    tx_st_eop <= 0;

                    // Priority: BAR > DMA MRd > DMA MWr > MSI-X
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
                    else if (dma_mrd_valid) begin
                        tx_state <= TX_DMA_MRD;
                    end
                    else if (dma_mwr_valid) begin
                        tx_state <= TX_DMA_MWR;
                    end
                    else if (msix_valid) begin
                        tx_state <= TX_MSIX;
                    end
                end

                // BAR Write
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

                // BAR Read
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
                    if (tx_st_ready && !tx_st_hvalid) begin
                        tx_st_sop <= 1;
                        tx_st_eop <= 1;
                        tx_st_hvalid <= 1;
                        tx_st_dvalid <= 1;
                        tx_cpl_hdr_dec <= 1;
                        tx_cpl_data_dec <= 1;
                        tx_hdr_r <= {
                            {3'b010, 5'b01010, 8'b0, 6'b0, 10'd2},
                            {16'h0100, (bar_cpl_status == AXI_OKAY) ? 3'b000 : 3'b001, 1'b0, 12'd8},
                            {bar_req_rid, bar_req_tag, 1'b0, bar_req_lower_addr},
                            32'b0
                        };
                        tx_data_r <= bar_cpl_data;
                        tx_state <= TX_IDLE;
                    end
                end

                // DMA MRd
                TX_DMA_MRD: begin
                    if (tx_st_ready && !tx_st_hvalid) begin
                        tx_st_sop <= 1;
                        tx_st_eop <= 1;
                        tx_st_hvalid <= 1;
                        tx_st_dvalid <= 0;
                        dma_mrd_ready_pulse <= 1;
                        tx_hdr_r <= {
                            {3'b001, 5'b00000, 8'b0, 6'b0, 10'd2},
                            {16'h0100, dma_mrd_tag, 4'hF, 4'hF},
                            dma_mrd_addr_r[63:32],
                            {dma_mrd_addr_r[31:2], 2'b00}
                        };
                        tx_data_r <= 64'b0;
                        tx_state <= TX_IDLE;
                    end
                end

                // DMA MWr
                TX_DMA_MWR: begin
                    if (tx_st_ready && !tx_st_hvalid) begin
                        tx_st_sop <= 1;
                        tx_st_eop <= 1;
                        tx_st_hvalid <= 1;
                        tx_st_dvalid <= 1;
                        dma_mwr_ready_pulse <= 1;
                        tx_hdr_r <= {
                            {3'b011, 5'b00000, 8'b0, 6'b0, 10'd2},
                            {16'h0100, 8'h00, 4'hF, 4'hF},
                            dma_mwr_addr_r[63:32],
                            {dma_mwr_addr_r[31:2], 2'b00}
                        };
                        tx_data_r <= dma_mwr_data_r;
                        tx_state <= TX_IDLE;
                    end
                end

                // MSI-X
                TX_MSIX: begin
                    if (tx_st_ready && !tx_st_hvalid) begin
                        tx_st_sop <= 1;
                        tx_st_eop <= 1;
                        tx_st_hvalid <= 1;
                        tx_st_dvalid <= 1;
                        msix_ready <= 1;
                        tx_hdr_r <= {
                            {3'b011, 5'b00000, 8'b0, 6'b0, 10'd1},
                            {16'h0100, 8'h00, 4'hF, 4'hF},
                            msix_addr[63:32],
                            {msix_addr[31:2], 2'b00}
                        };
                        tx_data_r <= {32'b0, msix_data};
                        tx_state <= TX_IDLE;
                    end
                end
            endcase
        end
    end

    //=========================================================================
    // TX Output
    //=========================================================================
    assign tx_st_hdr = tx_hdr_r;
    assign tx_st_data = {192'b0, tx_data_r};

endmodule
