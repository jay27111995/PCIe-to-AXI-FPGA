//-----------------------------------------------------------------------------
// top.sv - PCIe-to-AXI System Top with DMA and Debug Sniffers
//
// Memory map (BAR0):
//   0x0000-0x0FFF: DMA engine registers
//   0x1000-0x1FFF: Local RAM (4KB)
//   0x2000-0x2FFF: PCIe Sniffer (32-entry TLP trace, 64-bit direct access)
//   0x3000-0x37FF: AXI Slave Sniffer (64-entry, BAR access)
//   0x3800-0x3FFF: AXI Master Sniffer (64-entry, DMA to host)
//
// All sniffers share a global timestamp for event correlation.
// All sniffers use direct 64-bit AXI reads - no register decode complexity.
//-----------------------------------------------------------------------------
module top
    import rtile_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,

    // R-Tile interface
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
    input  logic [5:0]   ltssm_state
);

    //=========================================================================
    // Internal signals - Bridge AXI bus
    //=========================================================================
    logic [31:0] brg_awaddr, brg_araddr;
    logic [63:0] brg_wdata;
    logic [7:0]  brg_wstrb;
    logic [1:0]  brg_bresp;
    logic brg_awvalid, brg_awready, brg_wvalid, brg_wready;
    logic brg_bvalid, brg_bready, brg_arvalid, brg_arready;
    logic [63:0] brg_rdata_mux;
    logic [1:0]  brg_rresp_mux;
    logic        brg_rvalid_mux;
    logic        brg_rready;

    // DMA → Bridge AXI master (host memory access)
    logic [63:0] dma_host_awaddr, dma_host_araddr;
    logic [63:0] dma_host_wdata, dma_host_rdata;
    logic [7:0]  dma_host_wstrb;
    logic [1:0]  dma_host_bresp, dma_host_rresp;
    logic dma_host_awvalid, dma_host_awready, dma_host_wvalid, dma_host_wready;
    logic dma_host_bvalid, dma_host_bready, dma_host_arvalid, dma_host_arready;
    logic dma_host_rvalid, dma_host_rready;

    // DMA control (BAR 0x0xxx)
    logic [31:0] dma_s_awaddr, dma_s_araddr;
    logic [63:0] dma_s_wdata, dma_s_rdata;
    logic [7:0]  dma_s_wstrb;
    logic [1:0]  dma_s_bresp, dma_s_rresp;
    logic dma_s_awvalid, dma_s_awready, dma_s_wvalid, dma_s_wready;
    logic dma_s_bvalid, dma_s_bready, dma_s_arvalid, dma_s_arready;
    logic dma_s_rvalid, dma_s_rready;

    // RAM BAR access (BAR 0x1xxx)
    logic [31:0] ram_bar_awaddr, ram_bar_araddr;
    logic [63:0] ram_bar_wdata, ram_bar_rdata;
    logic [7:0]  ram_bar_wstrb;
    logic [1:0]  ram_bar_bresp, ram_bar_rresp;
    logic ram_bar_awvalid, ram_bar_awready, ram_bar_wvalid, ram_bar_wready;
    logic ram_bar_bvalid, ram_bar_bready, ram_bar_arvalid, ram_bar_arready;
    logic ram_bar_rvalid, ram_bar_rready;

    // DMA local RAM access
    logic [31:0] dma_local_awaddr, dma_local_araddr;
    logic [63:0] dma_local_wdata, dma_local_rdata;
    logic [7:0]  dma_local_wstrb;
    logic [1:0]  dma_local_bresp, dma_local_rresp;
    logic dma_local_awvalid, dma_local_awready, dma_local_wvalid, dma_local_wready;
    logic dma_local_bvalid, dma_local_bready, dma_local_arvalid, dma_local_arready;
    logic dma_local_rvalid, dma_local_rready;

    // RAM arbiter signals
    logic [31:0] ram_awaddr, ram_araddr;
    logic [63:0] ram_wdata, ram_rdata;
    logic [7:0]  ram_wstrb;
    logic [1:0]  ram_bresp, ram_rresp;
    logic ram_awvalid, ram_awready, ram_wvalid, ram_wready;
    logic ram_bvalid, ram_bready, ram_arvalid, ram_arready;
    logic ram_rvalid, ram_rready;

    // MSI-X
    logic        msix_valid_i, msix_ready_i;
    logic [63:0] msix_addr_i;
    logic [31:0] msix_data_i;
    logic        dma_irq_req;

    //=========================================================================
    // PCIe-AXI Bridge
    //=========================================================================
    pcie_axi_bridge #(.AXI_ADDR_W(32), .AXI_DATA_W(64)) u_bridge (
        .clk, .rst_n,
        // PCIe interface
        .rx_st_hdr, .rx_st_data, .rx_st_sop, .rx_st_eop,
        .rx_st_hvalid, .rx_st_dvalid, .rx_st_bar, .rx_st_ready,
        .tx_st_hdr, .tx_st_data, .tx_st_sop, .tx_st_eop,
        .tx_st_hvalid, .tx_st_dvalid, .tx_st_ready,
        // Credits
        .rx_hcrdt_init, .rx_hcrdt_update, .rx_hcrdt_update_cnt,
        .rx_dcrdt_init, .rx_dcrdt_update, .rx_dcrdt_update_cnt,
        .tx_hcrdt_init, .tx_hcrdt_init_ack, .tx_hcrdt_update, .tx_hcrdt_update_cnt,
        .tx_dcrdt_init, .tx_dcrdt_init_ack, .tx_dcrdt_update, .tx_dcrdt_update_cnt,
        .link_up, .ltssm_state,
        // AXI Slave output (BAR access)
        .s_axi_awaddr(brg_awaddr), .s_axi_awvalid(brg_awvalid), .s_axi_awready(brg_awready),
        .s_axi_wdata(brg_wdata), .s_axi_wstrb(brg_wstrb), .s_axi_wvalid(brg_wvalid), .s_axi_wready(brg_wready),
        .s_axi_bresp(brg_bresp), .s_axi_bvalid(brg_bvalid), .s_axi_bready(brg_bready),
        .s_axi_araddr(brg_araddr), .s_axi_arvalid(brg_arvalid), .s_axi_arready(brg_arready),
        .s_axi_rdata(brg_rdata_mux), .s_axi_rresp(brg_rresp_mux), .s_axi_rvalid(brg_rvalid_mux), .s_axi_rready(brg_rready),
        // AXI Master input (DMA → host)
        .m_axi_awaddr(dma_host_awaddr), .m_axi_awvalid(dma_host_awvalid), .m_axi_awready(dma_host_awready),
        .m_axi_wdata(dma_host_wdata), .m_axi_wstrb(dma_host_wstrb), .m_axi_wvalid(dma_host_wvalid), .m_axi_wready(dma_host_wready),
        .m_axi_bresp(dma_host_bresp), .m_axi_bvalid(dma_host_bvalid), .m_axi_bready(dma_host_bready),
        .m_axi_araddr(dma_host_araddr), .m_axi_arvalid(dma_host_arvalid), .m_axi_arready(dma_host_arready),
        .m_axi_rdata(dma_host_rdata), .m_axi_rresp(dma_host_rresp), .m_axi_rvalid(dma_host_rvalid), .m_axi_rready(dma_host_rready),
        // MSI-X
        .msix_valid(msix_valid_i), .msix_ready(msix_ready_i),
        .msix_addr(msix_addr_i), .msix_data(msix_data_i)
    );

    //=========================================================================
    // Global Timestamp - shared across all sniffers
    //=========================================================================
    logic [31:0] global_timestamp;
    logic        clear_timestamp;
    
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            global_timestamp <= 0;
        else if (clear_timestamp)
            global_timestamp <= 0;
        else
            global_timestamp <= global_timestamp + 1;
    end

    //=========================================================================
    // Address Decode
    //=========================================================================
    wire wr_to_dma      = !brg_awaddr[13] && !brg_awaddr[12];         // 0x0xxx
    wire wr_to_ram      = !brg_awaddr[13] &&  brg_awaddr[12];         // 0x1xxx
    wire wr_to_pcie_snf =  brg_awaddr[13] && !brg_awaddr[12];         // 0x2xxx
    wire wr_to_axi_slv  =  brg_awaddr[13] &&  brg_awaddr[12] && !brg_awaddr[11]; // 0x3000-0x37FF
    wire wr_to_axi_mst  =  brg_awaddr[13] &&  brg_awaddr[12] &&  brg_awaddr[11]; // 0x3800-0x3FFF

    wire rd_to_dma      = !brg_araddr[13] && !brg_araddr[12];         // 0x0xxx
    wire rd_to_ram      = !brg_araddr[13] &&  brg_araddr[12];         // 0x1xxx
    wire rd_to_pcie_snf =  brg_araddr[13] && !brg_araddr[12];         // 0x2xxx
    wire rd_to_axi_slv  =  brg_araddr[13] &&  brg_araddr[12] && !brg_araddr[11]; // 0x3000-0x37FF
    wire rd_to_axi_mst  =  brg_araddr[13] &&  brg_araddr[12] &&  brg_araddr[11]; // 0x3800-0x3FFF

    //=========================================================================
    // PCIe Sniffer - 0x2000-0x2FFF
    //=========================================================================
    logic        pcie_snf_arready, pcie_snf_rvalid;
    logic [63:0] pcie_snf_rdata;
    logic        pcie_snf_awready, pcie_snf_wready, pcie_snf_bvalid;
    
    // Clear timestamp when any sniffer is cleared
    wire pcie_clear = wr_to_pcie_snf && brg_awvalid && brg_wvalid && brg_wdata[2];
    wire axi_slv_clear = wr_to_axi_slv && brg_awvalid && brg_wvalid && brg_wdata[2];
    wire axi_mst_clear = wr_to_axi_mst && brg_awvalid && brg_wvalid && brg_wdata[2];
    assign clear_timestamp = pcie_clear || axi_slv_clear || axi_mst_clear;

    pcie_sniffer #(.DEPTH(32)) u_pcie_sniffer (
        .clk, .rst_n,
        .global_timestamp,
        // RX/TX paths
        .rx_st_hdr, .rx_st_data, .rx_st_sop, .rx_st_eop,
        .rx_st_hvalid, .rx_st_dvalid, .rx_st_bar, .rx_st_ready,
        .tx_st_hdr, .tx_st_data, .tx_st_sop, .tx_st_eop,
        .tx_st_hvalid, .tx_st_dvalid, .tx_st_ready,
        // AXI interface
        .axi_araddr(brg_araddr[11:0]),
        .axi_arvalid(brg_arvalid && rd_to_pcie_snf),
        .axi_arready(pcie_snf_arready),
        .axi_rdata(pcie_snf_rdata),
        .axi_rvalid(pcie_snf_rvalid),
        .axi_rready(brg_rready),
        .axi_awaddr(brg_awaddr[11:0]),
        .axi_wdata(brg_wdata),
        .axi_awvalid(brg_awvalid && wr_to_pcie_snf),
        .axi_wvalid(brg_wvalid && wr_to_pcie_snf),
        .axi_awready(pcie_snf_awready),
        .axi_wready(pcie_snf_wready),
        .axi_bvalid(pcie_snf_bvalid),
        .axi_bready(brg_bready)
    );

    //=========================================================================
    // AXI Slave Sniffer - 0x3000-0x37FF (BAR access trace)
    //=========================================================================
    logic        axi_slv_arready, axi_slv_rvalid;
    logic [63:0] axi_slv_rdata;
    logic        axi_slv_awready, axi_slv_wready, axi_slv_bvalid;

    axi_sniffer #(.DEPTH(64)) u_axi_slave_sniffer (
        .clk, .rst_n,
        .global_timestamp,
        // Snoop bridge AXI bus
        .axi_awaddr(brg_awaddr),
        .axi_awvalid(brg_awvalid),
        .axi_awready(brg_awready),
        .axi_wdata(brg_wdata),
        .axi_wstrb(brg_wstrb),
        .axi_wvalid(brg_wvalid),
        .axi_wready(brg_wready),
        .axi_bresp(brg_bresp),
        .axi_bvalid(brg_bvalid),
        .axi_bready(brg_bready),
        .axi_araddr(brg_araddr),
        .axi_arvalid(brg_arvalid),
        .axi_arready(brg_arready),
        .axi_rdata(brg_rdata_mux),
        .axi_rresp(brg_rresp_mux),
        .axi_rvalid(brg_rvalid_mux),
        .axi_rready(brg_rready),
        // Control interface
        .s_araddr(brg_araddr[10:0]),
        .s_arvalid(brg_arvalid && rd_to_axi_slv),
        .s_arready(axi_slv_arready),
        .s_rdata(axi_slv_rdata),
        .s_rvalid(axi_slv_rvalid),
        .s_rready(brg_rready),
        .s_awaddr(brg_awaddr[10:0]),
        .s_wdata(brg_wdata),
        .s_awvalid(brg_awvalid && wr_to_axi_slv),
        .s_wvalid(brg_wvalid && wr_to_axi_slv),
        .s_awready(axi_slv_awready),
        .s_wready(axi_slv_wready),
        .s_bvalid(axi_slv_bvalid),
        .s_bready(brg_bready)
    );

    //=========================================================================
    // AXI Master Sniffer - 0x3800-0x3FFF (DMA to host trace)
    //=========================================================================
    logic        axi_mst_arready, axi_mst_rvalid;
    logic [63:0] axi_mst_rdata;
    logic        axi_mst_awready, axi_mst_wready, axi_mst_bvalid;

    axi_sniffer #(.DEPTH(64)) u_axi_master_sniffer (
        .clk, .rst_n,
        .global_timestamp,
        // Snoop DMA -> host AXI bus
        .axi_awaddr(dma_host_awaddr[31:0]),
        .axi_awvalid(dma_host_awvalid),
        .axi_awready(dma_host_awready),
        .axi_wdata(dma_host_wdata),
        .axi_wstrb(dma_host_wstrb),
        .axi_wvalid(dma_host_wvalid),
        .axi_wready(dma_host_wready),
        .axi_bresp(dma_host_bresp),
        .axi_bvalid(dma_host_bvalid),
        .axi_bready(dma_host_bready),
        .axi_araddr(dma_host_araddr[31:0]),
        .axi_arvalid(dma_host_arvalid),
        .axi_arready(dma_host_arready),
        .axi_rdata(dma_host_rdata),
        .axi_rresp(dma_host_rresp),
        .axi_rvalid(dma_host_rvalid),
        .axi_rready(dma_host_rready),
        // Control interface
        .s_araddr(brg_araddr[10:0]),
        .s_arvalid(brg_arvalid && rd_to_axi_mst),
        .s_arready(axi_mst_arready),
        .s_rdata(axi_mst_rdata),
        .s_rvalid(axi_mst_rvalid),
        .s_rready(brg_rready),
        .s_awaddr(brg_awaddr[10:0]),
        .s_wdata(brg_wdata),
        .s_awvalid(brg_awvalid && wr_to_axi_mst),
        .s_wvalid(brg_wvalid && wr_to_axi_mst),
        .s_awready(axi_mst_awready),
        .s_wready(axi_mst_wready),
        .s_bvalid(axi_mst_bvalid),
        .s_bready(brg_bready)
    );

    //=========================================================================
    // DMA Engine routes
    //=========================================================================
    assign dma_s_awaddr  = brg_awaddr;
    assign dma_s_wdata   = brg_wdata;
    assign dma_s_wstrb   = brg_wstrb;
    assign dma_s_awvalid = brg_awvalid && wr_to_dma;
    assign dma_s_wvalid  = brg_wvalid  && wr_to_dma;
    assign dma_s_bready  = brg_bready;
    assign dma_s_araddr  = brg_araddr;
    assign dma_s_arvalid = brg_arvalid && rd_to_dma;
    assign dma_s_rready  = brg_rready;

    //=========================================================================
    // RAM routes
    //=========================================================================
    assign ram_bar_awaddr  = brg_awaddr;
    assign ram_bar_wdata   = brg_wdata;
    assign ram_bar_wstrb   = brg_wstrb;
    assign ram_bar_awvalid = brg_awvalid && wr_to_ram;
    assign ram_bar_wvalid  = brg_wvalid  && wr_to_ram;
    assign ram_bar_bready  = brg_bready;
    assign ram_bar_araddr  = brg_araddr;
    assign ram_bar_arvalid = brg_arvalid && rd_to_ram;
    assign ram_bar_rready  = brg_rready;

    //=========================================================================
    // Response mux - simple priority: DMA > RAM > PCIe snf > AXI slv > AXI mst
    //=========================================================================
    assign brg_awready = wr_to_dma      ? dma_s_awready :
                         wr_to_ram      ? ram_bar_awready :
                         wr_to_pcie_snf ? pcie_snf_awready :
                         wr_to_axi_slv  ? axi_slv_awready :
                         wr_to_axi_mst  ? axi_mst_awready : 1'b1;

    assign brg_wready  = wr_to_dma      ? dma_s_wready :
                         wr_to_ram      ? ram_bar_wready :
                         wr_to_pcie_snf ? pcie_snf_wready :
                         wr_to_axi_slv  ? axi_slv_wready :
                         wr_to_axi_mst  ? axi_mst_wready : 1'b1;

    assign brg_bvalid  = dma_s_bvalid | ram_bar_bvalid | pcie_snf_bvalid | axi_slv_bvalid | axi_mst_bvalid;
    assign brg_bresp   = dma_s_bvalid ? dma_s_bresp : (ram_bar_bvalid ? ram_bar_bresp : 2'b00);

    assign brg_arready = rd_to_dma      ? dma_s_arready :
                         rd_to_ram      ? ram_bar_arready :
                         rd_to_pcie_snf ? pcie_snf_arready :
                         rd_to_axi_slv  ? axi_slv_arready :
                         rd_to_axi_mst  ? axi_mst_arready : 1'b1;

    assign brg_rvalid_mux = dma_s_rvalid | ram_bar_rvalid | pcie_snf_rvalid | axi_slv_rvalid | axi_mst_rvalid;
    
    assign brg_rdata_mux  = dma_s_rvalid     ? dma_s_rdata :
                            ram_bar_rvalid   ? ram_bar_rdata :
                            pcie_snf_rvalid  ? pcie_snf_rdata :
                            axi_slv_rvalid   ? axi_slv_rdata :
                            axi_mst_rvalid   ? axi_mst_rdata : 64'hDEAD_BEEF;
    
    assign brg_rresp_mux  = dma_s_rvalid ? dma_s_rresp : (ram_bar_rvalid ? ram_bar_rresp : 2'b00);

    //=========================================================================
    // DMA Engine
    //=========================================================================
    dma_engine u_dma (
        .clk, .rst_n,
        // Control registers
        .s_axi_awaddr(dma_s_awaddr), .s_axi_awvalid(dma_s_awvalid), .s_axi_awready(dma_s_awready),
        .s_axi_wdata(dma_s_wdata), .s_axi_wstrb(dma_s_wstrb), .s_axi_wvalid(dma_s_wvalid), .s_axi_wready(dma_s_wready),
        .s_axi_bresp(dma_s_bresp), .s_axi_bvalid(dma_s_bvalid), .s_axi_bready(dma_s_bready),
        .s_axi_araddr(dma_s_araddr), .s_axi_arvalid(dma_s_arvalid), .s_axi_arready(dma_s_arready),
        .s_axi_rdata(dma_s_rdata), .s_axi_rresp(dma_s_rresp), .s_axi_rvalid(dma_s_rvalid), .s_axi_rready(dma_s_rready),
        // Local RAM
        .m_local_awaddr(dma_local_awaddr), .m_local_awvalid(dma_local_awvalid), .m_local_awready(dma_local_awready),
        .m_local_wdata(dma_local_wdata), .m_local_wstrb(dma_local_wstrb), .m_local_wvalid(dma_local_wvalid), .m_local_wready(dma_local_wready),
        .m_local_bresp(dma_local_bresp), .m_local_bvalid(dma_local_bvalid), .m_local_bready(dma_local_bready),
        .m_local_araddr(dma_local_araddr), .m_local_arvalid(dma_local_arvalid), .m_local_arready(dma_local_arready),
        .m_local_rdata(dma_local_rdata), .m_local_rresp(dma_local_rresp), .m_local_rvalid(dma_local_rvalid), .m_local_rready(dma_local_rready),
        // Host memory
        .m_host_awaddr(dma_host_awaddr), .m_host_awvalid(dma_host_awvalid), .m_host_awready(dma_host_awready),
        .m_host_wdata(dma_host_wdata), .m_host_wstrb(dma_host_wstrb), .m_host_wvalid(dma_host_wvalid), .m_host_wready(dma_host_wready),
        .m_host_bresp(dma_host_bresp), .m_host_bvalid(dma_host_bvalid), .m_host_bready(dma_host_bready),
        .m_host_araddr(dma_host_araddr), .m_host_arvalid(dma_host_arvalid), .m_host_arready(dma_host_arready),
        .m_host_rdata(dma_host_rdata), .m_host_rresp(dma_host_rresp), .m_host_rvalid(dma_host_rvalid), .m_host_rready(dma_host_rready),
        // IRQ
        .irq_req(dma_irq_req)
    );

    //=========================================================================
    // RAM Arbiter - BAR and DMA both access local RAM (inline)
    //=========================================================================
    logic arb_busy, arb_owner;  // 0=BAR, 1=DMA

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            arb_busy <= 0;
            arb_owner <= 0;
        end else if (!arb_busy) begin
            if (ram_bar_awvalid || ram_bar_arvalid) begin
                arb_busy <= 1;
                arb_owner <= 0;
            end else if (dma_local_awvalid || dma_local_arvalid) begin
                arb_busy <= 1;
                arb_owner <= 1;
            end
        end else begin
            if (arb_owner == 0 && ((ram_bar_bvalid && ram_bar_bready) || (ram_bar_rvalid && ram_bar_rready)))
                arb_busy <= 0;
            if (arb_owner == 1 && ((dma_local_bvalid && dma_local_bready) || (dma_local_rvalid && dma_local_rready)))
                arb_busy <= 0;
        end
    end

    // Mux to RAM
    assign ram_awaddr  = arb_owner ? dma_local_awaddr  : ram_bar_awaddr;
    assign ram_awvalid = arb_owner ? dma_local_awvalid : ram_bar_awvalid;
    assign ram_wdata   = arb_owner ? dma_local_wdata   : ram_bar_wdata;
    assign ram_wstrb   = arb_owner ? dma_local_wstrb   : ram_bar_wstrb;
    assign ram_wvalid  = arb_owner ? dma_local_wvalid  : ram_bar_wvalid;
    assign ram_bready  = arb_owner ? dma_local_bready  : ram_bar_bready;
    assign ram_araddr  = arb_owner ? dma_local_araddr  : ram_bar_araddr;
    assign ram_arvalid = arb_owner ? dma_local_arvalid : ram_bar_arvalid;
    assign ram_rready  = arb_owner ? dma_local_rready  : ram_bar_rready;

    // Response back to requesters
    assign ram_bar_awready   = !arb_owner && ram_awready;
    assign ram_bar_wready    = !arb_owner && ram_wready;
    assign ram_bar_bresp     = ram_bresp;
    assign ram_bar_bvalid    = !arb_owner && ram_bvalid;
    assign ram_bar_arready   = !arb_owner && ram_arready;
    assign ram_bar_rdata     = ram_rdata;
    assign ram_bar_rresp     = ram_rresp;
    assign ram_bar_rvalid    = !arb_owner && ram_rvalid;

    assign dma_local_awready = arb_owner && ram_awready;
    assign dma_local_wready  = arb_owner && ram_wready;
    assign dma_local_bresp   = ram_bresp;
    assign dma_local_bvalid  = arb_owner && ram_bvalid;
    assign dma_local_arready = arb_owner && ram_arready;
    assign dma_local_rdata   = ram_rdata;
    assign dma_local_rresp   = ram_rresp;
    assign dma_local_rvalid  = arb_owner && ram_rvalid;

    //=========================================================================
    // Local RAM (4KB)
    //=========================================================================
    axi_ram #(.DEPTH(512), .ADDR_W(12), .DATA_W(64)) u_ram (
        .clk, .rst_n,
        .s_axi_awaddr(ram_awaddr[11:0]), .s_axi_awvalid(ram_awvalid), .s_axi_awready(ram_awready),
        .s_axi_wdata(ram_wdata), .s_axi_wstrb(ram_wstrb), .s_axi_wvalid(ram_wvalid), .s_axi_wready(ram_wready),
        .s_axi_bresp(ram_bresp), .s_axi_bvalid(ram_bvalid), .s_axi_bready(ram_bready),
        .s_axi_araddr(ram_araddr[11:0]), .s_axi_arvalid(ram_arvalid), .s_axi_arready(ram_arready),
        .s_axi_rdata(ram_rdata), .s_axi_rresp(ram_rresp), .s_axi_rvalid(ram_rvalid), .s_axi_rready(ram_rready)
    );

    //=========================================================================
    // MSI-X Generation
    //=========================================================================
    logic [63:0] msix_addr_reg;
    logic [31:0] msix_data_reg;
    logic        msix_pending;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            msix_valid_i <= 0;
            msix_pending <= 0;
            msix_addr_reg <= 64'hFEE00000;
            msix_data_reg <= 32'h0;
        end else begin
            if (dma_irq_req && !msix_pending) begin
                msix_valid_i <= 1;
                msix_pending <= 1;
            end
            if (msix_valid_i && msix_ready_i) begin
                msix_valid_i <= 0;
                msix_pending <= 0;
            end
        end
    end

    assign msix_addr_i = msix_addr_reg;
    assign msix_data_i = msix_data_reg;

endmodule
