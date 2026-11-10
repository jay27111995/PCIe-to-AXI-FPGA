//-----------------------------------------------------------------------------
// pcie_axi_top.sv - PCIe-to-AXI System Top with DMA
//
// Memory map (BAR0):
//   0x0000-0x0FFF: Control registers  
//   0x1000-0x1FFF: DMA engine registers
//   0x2000-0x2FFF: Local RAM (directly from BAR, DMA uses separate path)
//-----------------------------------------------------------------------------
module pcie_axi_top
    import rtile_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,

    // R-Tile
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

    output logic [63:0]  scratch_reg,
    output logic [31:0]  write_count,
    output logic         dma_irq
);

    // Bridge AXI master
    logic [31:0] brg_awaddr, brg_araddr;
    logic [63:0] brg_wdata, brg_rdata;
    logic [7:0]  brg_wstrb;
    logic [1:0]  brg_bresp, brg_rresp;
    logic brg_awvalid, brg_awready, brg_wvalid, brg_wready;
    logic brg_bvalid, brg_bready, brg_arvalid, brg_arready;
    logic brg_rvalid, brg_rready;

    // DMA PCIe interface
    logic dma_mrd_valid, dma_mrd_ready;
    logic [63:0] dma_mrd_addr;
    logic [9:0] dma_mrd_len;
    logic [7:0] dma_mrd_tag;
    logic dma_mwr_valid, dma_mwr_ready;
    logic [63:0] dma_mwr_addr, dma_mwr_data;
    logic [9:0] dma_mwr_len;
    logic dma_cpl_valid;
    logic [7:0] dma_cpl_tag;
    logic [63:0] dma_cpl_data;

    // Slave buses
    logic [31:0] reg_awaddr, reg_araddr;
    logic [63:0] reg_wdata, reg_rdata;
    logic [7:0] reg_wstrb;
    logic [1:0] reg_bresp, reg_rresp;
    logic reg_awvalid, reg_awready, reg_wvalid, reg_wready;
    logic reg_bvalid, reg_bready, reg_arvalid, reg_arready, reg_rvalid, reg_rready;

    logic [31:0] dma_awaddr, dma_araddr;
    logic [63:0] dma_wdata, dma_rdata;
    logic [7:0] dma_wstrb;
    logic [1:0] dma_bresp, dma_rresp;
    logic dma_awvalid, dma_awready, dma_wvalid, dma_wready;
    logic dma_bvalid, dma_bready, dma_arvalid, dma_arready, dma_rvalid, dma_rready;

    logic [31:0] ram_awaddr, ram_araddr;
    logic [63:0] ram_wdata, ram_rdata;
    logic [7:0] ram_wstrb;
    logic [1:0] ram_bresp, ram_rresp;
    logic ram_awvalid, ram_awready, ram_wvalid, ram_wready;
    logic ram_bvalid, ram_bready, ram_arvalid, ram_arready, ram_rvalid, ram_rready;

    // DMA → RAM path
    logic [31:0] dma_ram_awaddr, dma_ram_araddr;
    logic [63:0] dma_ram_wdata, dma_ram_rdata;
    logic [7:0] dma_ram_wstrb;
    logic [1:0] dma_ram_bresp, dma_ram_rresp;
    logic dma_ram_awvalid, dma_ram_awready, dma_ram_wvalid, dma_ram_wready;
    logic dma_ram_bvalid, dma_ram_bready, dma_ram_arvalid, dma_ram_arready;
    logic dma_ram_rvalid, dma_ram_rready;

    //=========================================================================
    // Bridge
    //=========================================================================
    rtile_top #(.AXI_ADDR_W(32), .AXI_DATA_W(64)) u_bridge (
        .clk, .rst_n,
        .rx_st_hdr, .rx_st_data, .rx_st_sop, .rx_st_eop,
        .rx_st_hvalid, .rx_st_dvalid, .rx_st_bar, .rx_st_ready,
        .tx_st_hdr, .tx_st_data, .tx_st_sop, .tx_st_eop,
        .tx_st_hvalid, .tx_st_dvalid, .tx_st_ready,
        .rx_hcrdt_init, .rx_hcrdt_update, .rx_hcrdt_update_cnt,
        .rx_dcrdt_init, .rx_dcrdt_update, .rx_dcrdt_update_cnt,
        .tx_hcrdt_init, .tx_hcrdt_init_ack, .tx_hcrdt_update, .tx_hcrdt_update_cnt,
        .tx_dcrdt_init, .tx_dcrdt_init_ack, .tx_dcrdt_update, .tx_dcrdt_update_cnt,
        .link_up, .ltssm_state,
        .m_axi_awaddr(brg_awaddr), .m_axi_awvalid(brg_awvalid), .m_axi_awready(brg_awready),
        .m_axi_wdata(brg_wdata), .m_axi_wstrb(brg_wstrb), .m_axi_wvalid(brg_wvalid), .m_axi_wready(brg_wready),
        .m_axi_bresp(brg_bresp), .m_axi_bvalid(brg_bvalid), .m_axi_bready(brg_bready),
        .m_axi_araddr(brg_araddr), .m_axi_arvalid(brg_arvalid), .m_axi_arready(brg_arready),
        .m_axi_rdata(brg_rdata), .m_axi_rresp(brg_rresp), .m_axi_rvalid(brg_rvalid), .m_axi_rready(brg_rready),
        .dma_mrd_valid, .dma_mrd_ready, .dma_mrd_addr, .dma_mrd_len, .dma_mrd_tag,
        .dma_mwr_valid, .dma_mwr_ready, .dma_mwr_addr, .dma_mwr_data, .dma_mwr_len,
        .dma_cpl_valid, .dma_cpl_tag, .dma_cpl_data
    );

    //=========================================================================
    // Address Decode (simple, stateless for each slave)
    // 0x0xxx=reg, 0x1xxx=dma, 0x2xxx=ram
    //=========================================================================
    wire [1:0] wr_sel = brg_awaddr[13:12];
    wire [1:0] rd_sel = brg_araddr[13:12];

    // Fan out address/data to all slaves
    assign reg_awaddr = brg_awaddr; assign reg_wdata = brg_wdata; assign reg_wstrb = brg_wstrb;
    assign dma_awaddr = brg_awaddr; assign dma_wdata = brg_wdata; assign dma_wstrb = brg_wstrb;
    assign ram_awaddr = brg_awaddr; assign ram_wdata = brg_wdata; assign ram_wstrb = brg_wstrb;
    assign reg_araddr = brg_araddr;
    assign dma_araddr = brg_araddr;
    assign ram_araddr = brg_araddr;

    // Route valid based on address
    assign reg_awvalid = brg_awvalid && (wr_sel == 2'b00);
    assign reg_wvalid  = brg_wvalid  && (wr_sel == 2'b00);
    assign dma_awvalid = brg_awvalid && (wr_sel == 2'b01);
    assign dma_wvalid  = brg_wvalid  && (wr_sel == 2'b01);
    assign ram_awvalid = brg_awvalid && (wr_sel == 2'b10);
    assign ram_wvalid  = brg_wvalid  && (wr_sel == 2'b10);

    assign reg_arvalid = brg_arvalid && (rd_sel == 2'b00);
    assign dma_arvalid = brg_arvalid && (rd_sel == 2'b01);
    assign ram_arvalid = brg_arvalid && (rd_sel == 2'b10);

    // Mux ready back
    assign brg_awready = (wr_sel == 2'b00) ? reg_awready : (wr_sel == 2'b01) ? dma_awready : ram_awready;
    assign brg_wready  = (wr_sel == 2'b00) ? reg_wready  : (wr_sel == 2'b01) ? dma_wready  : ram_wready;
    assign brg_arready = (rd_sel == 2'b00) ? reg_arready : (rd_sel == 2'b01) ? dma_arready : ram_arready;

    // Fan out bready/rready
    assign reg_bready = brg_bready; assign dma_bready = brg_bready; assign ram_bready = brg_bready;
    assign reg_rready = brg_rready; assign dma_rready = brg_rready; assign ram_rready = brg_rready;

    // Mux responses (only one should be valid at a time)
    assign brg_bvalid = reg_bvalid | dma_bvalid | ram_bvalid;
    assign brg_bresp  = reg_bvalid ? reg_bresp : dma_bvalid ? dma_bresp : ram_bresp;
    assign brg_rvalid = reg_rvalid | dma_rvalid | ram_rvalid;
    assign brg_rdata  = reg_rvalid ? reg_rdata : dma_rvalid ? dma_rdata : ram_rdata;
    assign brg_rresp  = reg_rvalid ? reg_rresp : dma_rvalid ? dma_rresp : ram_rresp;

    //=========================================================================
    // Registers
    //=========================================================================
    axi_regs #(.ADDR_W(32), .DATA_W(64)) u_regs (
        .clk, .rst_n,
        .s_axi_awaddr(reg_awaddr), .s_axi_awvalid(reg_awvalid), .s_axi_awready(reg_awready),
        .s_axi_wdata(reg_wdata), .s_axi_wstrb(reg_wstrb), .s_axi_wvalid(reg_wvalid), .s_axi_wready(reg_wready),
        .s_axi_bresp(reg_bresp), .s_axi_bvalid(reg_bvalid), .s_axi_bready(reg_bready),
        .s_axi_araddr(reg_araddr), .s_axi_arvalid(reg_arvalid), .s_axi_arready(reg_arready),
        .s_axi_rdata(reg_rdata), .s_axi_rresp(reg_rresp), .s_axi_rvalid(reg_rvalid), .s_axi_rready(reg_rready),
        .scratch(scratch_reg), .write_count(write_count)
    );

    //=========================================================================
    // DMA Engine (control via BAR, data via separate RAM port)
    //=========================================================================
    dma_engine #(.ADDR_W(32), .DATA_W(64)) u_dma (
        .clk, .rst_n,
        // Control (BAR 0x1xxx)
        .s_axi_awaddr(dma_awaddr), .s_axi_awvalid(dma_awvalid), .s_axi_awready(dma_awready),
        .s_axi_wdata(dma_wdata), .s_axi_wstrb(dma_wstrb), .s_axi_wvalid(dma_wvalid), .s_axi_wready(dma_wready),
        .s_axi_bresp(dma_bresp), .s_axi_bvalid(dma_bvalid), .s_axi_bready(dma_bready),
        .s_axi_araddr(dma_araddr), .s_axi_arvalid(dma_arvalid), .s_axi_arready(dma_arready),
        .s_axi_rdata(dma_rdata), .s_axi_rresp(dma_rresp), .s_axi_rvalid(dma_rvalid), .s_axi_rready(dma_rready),
        // RAM access (direct, not through BAR decoder)
        .m_axi_awaddr(dma_ram_awaddr), .m_axi_awvalid(dma_ram_awvalid), .m_axi_awready(dma_ram_awready),
        .m_axi_wdata(dma_ram_wdata), .m_axi_wstrb(dma_ram_wstrb), .m_axi_wvalid(dma_ram_wvalid), .m_axi_wready(dma_ram_wready),
        .m_axi_bresp(dma_ram_bresp), .m_axi_bvalid(dma_ram_bvalid), .m_axi_bready(dma_ram_bready),
        .m_axi_araddr(dma_ram_araddr), .m_axi_arvalid(dma_ram_arvalid), .m_axi_arready(dma_ram_arready),
        .m_axi_rdata(dma_ram_rdata), .m_axi_rresp(dma_ram_rresp), .m_axi_rvalid(dma_ram_rvalid), .m_axi_rready(dma_ram_rready),
        // PCIe
        .pcie_mrd_valid(dma_mrd_valid), .pcie_mrd_ready(dma_mrd_ready),
        .pcie_mrd_addr(dma_mrd_addr), .pcie_mrd_len(dma_mrd_len), .pcie_mrd_tag(dma_mrd_tag),
        .pcie_mwr_valid(dma_mwr_valid), .pcie_mwr_ready(dma_mwr_ready),
        .pcie_mwr_addr(dma_mwr_addr), .pcie_mwr_data(dma_mwr_data), .pcie_mwr_len(dma_mwr_len),
        .pcie_cpl_valid(dma_cpl_valid), .pcie_cpl_tag(dma_cpl_tag), .pcie_cpl_data(dma_cpl_data),
        .dma_irq(dma_irq)
    );

    //=========================================================================
    // RAM with simple 2-port arbiter (BAR vs DMA)
    //=========================================================================
    // Track who owns the RAM
    logic ram_busy, ram_owner;  // owner: 0=BAR, 1=DMA
    
    // Actual RAM interface
    logic [31:0] ram_real_awaddr, ram_real_araddr;
    logic [63:0] ram_real_wdata, ram_real_rdata;
    logic [7:0] ram_real_wstrb;
    logic [1:0] ram_real_bresp, ram_real_rresp;
    logic ram_real_awvalid, ram_real_awready, ram_real_wvalid, ram_real_wready;
    logic ram_real_bvalid, ram_real_bready, ram_real_arvalid, ram_real_arready;
    logic ram_real_rvalid, ram_real_rready;

    // Arbiter FSM
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ram_busy <= 0;
            ram_owner <= 0;
        end else begin
            if (!ram_busy) begin
                // BAR has priority
                if (ram_awvalid || ram_arvalid) begin
                    ram_busy <= 1;
                    ram_owner <= 0;
                end else if (dma_ram_awvalid || dma_ram_arvalid) begin
                    ram_busy <= 1;
                    ram_owner <= 1;
                end
            end else begin
                // Release when transaction completes
                if ((ram_real_bvalid && ram_real_bready) || (ram_real_rvalid && ram_real_rready))
                    ram_busy <= 0;
            end
        end
    end

    // Mux to RAM
    wire bar_owns = !ram_owner;
    assign ram_real_awaddr  = bar_owns ? ram_awaddr  : dma_ram_awaddr;
    assign ram_real_wdata   = bar_owns ? ram_wdata   : dma_ram_wdata;
    assign ram_real_wstrb   = bar_owns ? ram_wstrb   : dma_ram_wstrb;
    assign ram_real_awvalid = bar_owns ? ram_awvalid : dma_ram_awvalid;
    assign ram_real_wvalid  = bar_owns ? ram_wvalid  : dma_ram_wvalid;
    assign ram_real_bready  = bar_owns ? ram_bready  : dma_ram_bready;
    assign ram_real_araddr  = bar_owns ? ram_araddr  : dma_ram_araddr;
    assign ram_real_arvalid = bar_owns ? ram_arvalid : dma_ram_arvalid;
    assign ram_real_rready  = bar_owns ? ram_rready  : dma_ram_rready;

    // Responses back
    assign ram_awready     = bar_owns ? ram_real_awready : 1'b0;
    assign ram_wready      = bar_owns ? ram_real_wready  : 1'b0;
    assign ram_bresp       = ram_real_bresp;
    assign ram_bvalid      = bar_owns ? ram_real_bvalid  : 1'b0;
    assign ram_arready     = bar_owns ? ram_real_arready : 1'b0;
    assign ram_rdata       = ram_real_rdata;
    assign ram_rresp       = ram_real_rresp;
    assign ram_rvalid      = bar_owns ? ram_real_rvalid  : 1'b0;

    assign dma_ram_awready = bar_owns ? 1'b0 : ram_real_awready;
    assign dma_ram_wready  = bar_owns ? 1'b0 : ram_real_wready;
    assign dma_ram_bresp   = ram_real_bresp;
    assign dma_ram_bvalid  = bar_owns ? 1'b0 : ram_real_bvalid;
    assign dma_ram_arready = bar_owns ? 1'b0 : ram_real_arready;
    assign dma_ram_rdata   = ram_real_rdata;
    assign dma_ram_rresp   = ram_real_rresp;
    assign dma_ram_rvalid  = bar_owns ? 1'b0 : ram_real_rvalid;

    axi_ram #(.ADDR_W(32), .DATA_W(64), .DEPTH(512)) u_ram (
        .clk, .rst_n,
        .s_axi_awaddr(ram_real_awaddr), .s_axi_awvalid(ram_real_awvalid), .s_axi_awready(ram_real_awready),
        .s_axi_wdata(ram_real_wdata), .s_axi_wstrb(ram_real_wstrb), .s_axi_wvalid(ram_real_wvalid), .s_axi_wready(ram_real_wready),
        .s_axi_bresp(ram_real_bresp), .s_axi_bvalid(ram_real_bvalid), .s_axi_bready(ram_real_bready),
        .s_axi_araddr(ram_real_araddr), .s_axi_arvalid(ram_real_arvalid), .s_axi_arready(ram_real_arready),
        .s_axi_rdata(ram_real_rdata), .s_axi_rresp(ram_real_rresp), .s_axi_rvalid(ram_real_rvalid), .s_axi_rready(ram_real_rready)
    );

endmodule
