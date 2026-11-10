//-----------------------------------------------------------------------------
// rtile_top.sv - PCIe to AXI-Lite Bridge with DMA support
//
// Handles:
// - BAR0 MRd/MWr → AXI-Lite master (for register/DMA control)
// - DMA MRd → PCIe MRd to host → CplD routed to DMA engine
// - DMA MWr → PCIe MWr to host
//-----------------------------------------------------------------------------
module rtile_top
    import rtile_pkg::*;
#(
    parameter int AXI_ADDR_W = 32,
    parameter int AXI_DATA_W = 64
)(
    input  logic        clk,
    input  logic        rst_n,

    //-------------------------------------------------------------------------
    // R-Tile Avalon-ST RX (HIP → us)
    //-------------------------------------------------------------------------
    input  logic [127:0] rx_st_hdr,
    input  logic [255:0] rx_st_data,
    input  logic         rx_st_sop,
    input  logic         rx_st_eop,
    input  logic         rx_st_hvalid,
    input  logic         rx_st_dvalid,
    input  logic [2:0]   rx_st_bar,
    output logic         rx_st_ready,

    //-------------------------------------------------------------------------
    // R-Tile Avalon-ST TX (us → HIP)
    //-------------------------------------------------------------------------
    output logic [127:0] tx_st_hdr,
    output logic [255:0] tx_st_data,
    output logic         tx_st_sop,
    output logic         tx_st_eop,
    output logic         tx_st_hvalid,
    output logic         tx_st_dvalid,
    input  logic         tx_st_ready,

    //-------------------------------------------------------------------------
    // Credit Interface
    //-------------------------------------------------------------------------
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

    //-------------------------------------------------------------------------
    // Status
    //-------------------------------------------------------------------------
    input  logic         link_up,
    input  logic [5:0]   ltssm_state,

    //-------------------------------------------------------------------------
    // AXI-Lite Master (BAR access)
    //-------------------------------------------------------------------------
    output logic [AXI_ADDR_W-1:0] m_axi_awaddr,
    output logic                  m_axi_awvalid,
    input  logic                  m_axi_awready,
    output logic [AXI_DATA_W-1:0] m_axi_wdata,
    output logic [AXI_DATA_W/8-1:0] m_axi_wstrb,
    output logic                  m_axi_wvalid,
    input  logic                  m_axi_wready,
    input  logic [1:0]            m_axi_bresp,
    input  logic                  m_axi_bvalid,
    output logic                  m_axi_bready,
    output logic [AXI_ADDR_W-1:0] m_axi_araddr,
    output logic                  m_axi_arvalid,
    input  logic                  m_axi_arready,
    input  logic [AXI_DATA_W-1:0] m_axi_rdata,
    input  logic [1:0]            m_axi_rresp,
    input  logic                  m_axi_rvalid,
    output logic                  m_axi_rready,

    //-------------------------------------------------------------------------
    // DMA Interface (from dma_engine)
    //-------------------------------------------------------------------------
    // MRd request (DMA reads from host)
    input  logic                  dma_mrd_valid,
    output logic                  dma_mrd_ready,
    input  logic [63:0]           dma_mrd_addr,
    input  logic [9:0]            dma_mrd_len,
    input  logic [7:0]            dma_mrd_tag,

    // MWr request (DMA writes to host)
    input  logic                  dma_mwr_valid,
    output logic                  dma_mwr_ready,
    input  logic [63:0]           dma_mwr_addr,
    input  logic [63:0]           dma_mwr_data,
    input  logic [9:0]            dma_mwr_len,

    // Completion to DMA (response to MRd)
    output logic                  dma_cpl_valid,
    output logic [7:0]            dma_cpl_tag,
    output logic [63:0]           dma_cpl_data
);

    assign rx_st_ready = 1'b1;

    //-------------------------------------------------------------------------
    // Credit Manager
    //-------------------------------------------------------------------------
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

    //-------------------------------------------------------------------------
    // RX: Decode incoming TLPs
    //-------------------------------------------------------------------------
    logic [2:0]  rx_fmt;
    logic [4:0]  rx_type;
    logic [9:0]  rx_len;
    logic [15:0] rx_rid;
    logic [7:0]  rx_tag;
    logic [3:0]  rx_fbe, rx_lbe;
    logic [63:0] rx_addr;
    logic        rx_is_mrd, rx_is_mwr, rx_is_cpld;

    always_comb begin
        rx_fmt  = hdr_fmt(rx_st_hdr);
        rx_type = hdr_type(rx_st_hdr);
        rx_len  = hdr_len(rx_st_hdr);
        rx_rid  = hdr_rid(rx_st_hdr);
        rx_tag  = hdr_tag(rx_st_hdr);
        rx_fbe  = hdr_fbe(rx_st_hdr);
        rx_lbe  = hdr_lbe(rx_st_hdr);
        rx_addr = is_4dw(rx_fmt) ? hdr_addr64(rx_st_hdr) : {32'b0, hdr_addr32(rx_st_hdr)};

        rx_is_mrd  = rx_st_hvalid && rx_st_sop && (rx_type == 5'b00000) && !has_data(rx_fmt);
        rx_is_mwr  = rx_st_hvalid && rx_st_sop && (rx_type == 5'b00000) && has_data(rx_fmt);
        rx_is_cpld = rx_st_hvalid && rx_st_sop && (rx_type == 5'b01010) && has_data(rx_fmt);
    end

    // CplD fields (different header format)
    // DW2 of CplD: [31:16]=RequesterID, [15:8]=Tag, [6:0]=LowerAddr
    wire [7:0] cpl_rx_tag = rx_st_hdr[47:40];

    //-------------------------------------------------------------------------
    // Route incoming CplD to DMA engine
    //-------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dma_cpl_valid <= 0;
            dma_cpl_tag <= 0;
            dma_cpl_data <= 0;
        end else begin
            dma_cpl_valid <= 0;
            if (rx_is_cpld) begin
                dma_cpl_valid <= 1;
                dma_cpl_tag <= cpl_rx_tag;
                dma_cpl_data <= rx_st_data[63:0];
            end
        end
    end

    //-------------------------------------------------------------------------
    // TX Arbiter: BAR completion vs DMA MRd vs DMA MWr
    //-------------------------------------------------------------------------
    typedef enum logic [3:0] {
        ST_IDLE,
        // BAR write path
        ST_BAR_WR_ADDR,
        ST_BAR_WR_RESP,
        // BAR read path
        ST_BAR_RD_ADDR,
        ST_BAR_RD_DATA,
        ST_BAR_CPL,
        // DMA MRd (read from host)
        ST_DMA_MRD,
        // DMA MWr (write to host)
        ST_DMA_MWR
    } state_e;

    state_e state;

    // BAR completion info
    logic [15:0] bar_req_rid;
    logic [7:0]  bar_req_tag;
    logic [6:0]  bar_req_lower_addr;
    logic [63:0] bar_cpl_data;
    logic [1:0]  bar_cpl_status;

    // Byte enables
    logic [7:0] wstrb_from_be;
    assign wstrb_from_be = {rx_lbe, rx_fbe};

    // Registered TX header/data
    logic [127:0] tx_hdr_r;
    logic [63:0]  tx_data_r;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state <= ST_IDLE;
            m_axi_awvalid <= 0;
            m_axi_wvalid <= 0;
            m_axi_bready <= 0;
            m_axi_arvalid <= 0;
            m_axi_rready <= 0;
            tx_st_hvalid <= 0;
            tx_st_dvalid <= 0;
            tx_st_sop <= 0;
            tx_st_eop <= 0;
            tx_cpl_hdr_dec <= 0;
            tx_cpl_data_dec <= 0;
            dma_mrd_ready <= 0;
            dma_mwr_ready <= 0;
        end else begin
            tx_cpl_hdr_dec <= 0;
            tx_cpl_data_dec <= 0;
            dma_mrd_ready <= 0;
            dma_mwr_ready <= 0;

            case (state)
                ST_IDLE: begin
                    tx_st_hvalid <= 0;
                    tx_st_dvalid <= 0;
                    tx_st_sop <= 0;
                    tx_st_eop <= 0;

                    // Priority: BAR access > DMA MRd > DMA MWr
                    if (rx_is_mwr && rx_st_bar == 3'd0) begin
                        m_axi_awaddr <= rx_addr[AXI_ADDR_W-1:0];
                        m_axi_awvalid <= 1;
                        m_axi_wdata <= rx_st_data[AXI_DATA_W-1:0];
                        m_axi_wstrb <= wstrb_from_be;
                        m_axi_wvalid <= 1;
                        state <= ST_BAR_WR_ADDR;
                    end
                    else if (rx_is_mrd && rx_st_bar == 3'd0) begin  // Removed credit check for debug
                        bar_req_rid <= rx_rid;
                        bar_req_tag <= rx_tag;
                        bar_req_lower_addr <= rx_addr[6:0];
                        m_axi_araddr <= rx_addr[AXI_ADDR_W-1:0];
                        m_axi_arvalid <= 1;
                        state <= ST_BAR_RD_ADDR;
                    end
                    else if (dma_mrd_valid) begin
                        state <= ST_DMA_MRD;
                    end
                    else if (dma_mwr_valid) begin
                        state <= ST_DMA_MWR;
                    end
                end

                //-------------------------------------------------------------
                // BAR Write Path
                //-------------------------------------------------------------
                ST_BAR_WR_ADDR: begin
                    if (m_axi_awready) m_axi_awvalid <= 0;
                    if (m_axi_wready)  m_axi_wvalid <= 0;
                    
                    if ((m_axi_awready || !m_axi_awvalid) && 
                        (m_axi_wready || !m_axi_wvalid)) begin
                        m_axi_bready <= 1;
                        state <= ST_BAR_WR_RESP;
                    end
                end

                ST_BAR_WR_RESP: begin
                    if (m_axi_bvalid) begin
                        m_axi_bready <= 0;
                        state <= ST_IDLE;
                    end
                end

                //-------------------------------------------------------------
                // BAR Read Path
                //-------------------------------------------------------------
                ST_BAR_RD_ADDR: begin
                    if (m_axi_arready) begin
                        m_axi_arvalid <= 0;
                        m_axi_rready <= 1;
                        state <= ST_BAR_RD_DATA;
                    end
                end

                ST_BAR_RD_DATA: begin
                    if (m_axi_rvalid) begin
                        m_axi_rready <= 0;
                        bar_cpl_data <= m_axi_rdata;
                        bar_cpl_status <= m_axi_rresp;
                        state <= ST_BAR_CPL;
                    end
                end

                ST_BAR_CPL: begin
                    if (tx_st_ready && !tx_st_hvalid) begin
                        tx_st_sop <= 1;
                        tx_st_eop <= 1;
                        tx_st_hvalid <= 1;
                        tx_st_dvalid <= 1;
                        tx_cpl_hdr_dec <= 1;
                        tx_cpl_data_dec <= 1;
                        // Register header/data for output
                        tx_hdr_r <= {
                            {3'b010, 5'b01010, 8'b0, 6'b0, 10'd2},                    // DW0
                            {16'h0100, (bar_cpl_status == AXI_OKAY) ? 3'b000 : 3'b001, 1'b0, 12'd8}, // DW1
                            {bar_req_rid, bar_req_tag, 1'b0, bar_req_lower_addr},     // DW2
                            32'b0                                                     // DW3
                        };
                        tx_data_r <= bar_cpl_data;
                        state <= ST_IDLE;
                    end
                end

                //-------------------------------------------------------------
                // DMA MRd (read from host memory)
                //-------------------------------------------------------------
                ST_DMA_MRD: begin
                    if (tx_st_ready && !tx_st_hvalid) begin
                        tx_st_sop <= 1;
                        tx_st_eop <= 1;
                        tx_st_hvalid <= 1;
                        tx_st_dvalid <= 0;
                        dma_mrd_ready <= 1;
                        tx_hdr_r <= {
                            {3'b001, 5'b00000, 8'b0, 6'b0, dma_mrd_len},
                            {16'h0100, dma_mrd_tag, 4'hF, 4'hF},
                            dma_mrd_addr[63:32],
                            {dma_mrd_addr[31:2], 2'b00}
                        };
                        tx_data_r <= 64'b0;
                        state <= ST_IDLE;
                    end
                end

                //-------------------------------------------------------------
                // DMA MWr (write to host memory)
                //-------------------------------------------------------------
                ST_DMA_MWR: begin
                    if (tx_st_ready && !tx_st_hvalid) begin
                        tx_st_sop <= 1;
                        tx_st_eop <= 1;
                        tx_st_hvalid <= 1;
                        tx_st_dvalid <= 1;
                        dma_mwr_ready <= 1;
                        tx_hdr_r <= {
                            {3'b011, 5'b00000, 8'b0, 6'b0, dma_mwr_len},
                            {16'h0100, 8'h00, 4'hF, 4'hF},
                            dma_mwr_addr[63:32],
                            {dma_mwr_addr[31:2], 2'b00}
                        };
                        tx_data_r <= dma_mwr_data;
                        state <= ST_IDLE;
                    end
                end
            endcase
        end
    end

    //-------------------------------------------------------------------------
    // TX Header/Data - use registered values
    //-------------------------------------------------------------------------
    assign tx_st_hdr = tx_hdr_r;
    assign tx_st_data = {192'b0, tx_data_r};

endmodule
