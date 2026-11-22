//-----------------------------------------------------------------------------
// top.sv - PCIe-to-AXI System Top with DMA
//
// Memory map (BAR0):
//   0x0000-0x0FFF: DMA engine registers
//   0x1000-0x1FFF: Local RAM (4KB)
//   0x2000-0x2FFF: Debug/Sniffer registers (read-only)
//
// Architecture:
//   Host ─PCIe─► pcie_axi_bridge ─AXI─► [DMA regs | RAM | Debug]
//                      ▲
//                      │ AXI Master
//                      │
//                 dma_engine ─AXI─► RAM
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
    // Internal signals
    //=========================================================================
    
    // Bridge -> internal AXI bus (BAR access)
    // Note: s_axi_r* are INPUTS to bridge (read response from slaves)
    //       s_axi_ar* outputs come from bridge (read request to slaves)
    logic [31:0] brg_awaddr, brg_araddr;
    logic [63:0] brg_wdata;
    logic [7:0]  brg_wstrb;
    logic [1:0]  brg_bresp;
    logic brg_awvalid, brg_awready, brg_wvalid, brg_wready;
    logic brg_bvalid, brg_bready, brg_arvalid, brg_arready;
    
    // Read response signals - muxed from DMA/RAM/Debug, fed INTO bridge
    logic [63:0] brg_rdata_mux;
    logic [1:0]  brg_rresp_mux;
    logic        brg_rvalid_mux;
    logic        brg_rready;  // Output from bridge

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

    // Debug signals
    logic [3:0]  dbg_tx_state;

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
        // AXI Slave output (BAR access → DMA/RAM)
        .s_axi_awaddr(brg_awaddr), .s_axi_awvalid(brg_awvalid), .s_axi_awready(brg_awready),
        .s_axi_wdata(brg_wdata), .s_axi_wstrb(brg_wstrb), .s_axi_wvalid(brg_wvalid), .s_axi_wready(brg_wready),
        .s_axi_bresp(brg_bresp), .s_axi_bvalid(brg_bvalid), .s_axi_bready(brg_bready),
        .s_axi_araddr(brg_araddr), .s_axi_arvalid(brg_arvalid), .s_axi_arready(brg_arready),
        .s_axi_rdata(brg_rdata_mux), .s_axi_rresp(brg_rresp_mux), .s_axi_rvalid(brg_rvalid_mux), .s_axi_rready(brg_rready),
        // AXI Master input (DMA → host memory)
        .m_axi_awaddr(dma_host_awaddr), .m_axi_awvalid(dma_host_awvalid), .m_axi_awready(dma_host_awready),
        .m_axi_wdata(dma_host_wdata), .m_axi_wstrb(dma_host_wstrb), .m_axi_wvalid(dma_host_wvalid), .m_axi_wready(dma_host_wready),
        .m_axi_bresp(dma_host_bresp), .m_axi_bvalid(dma_host_bvalid), .m_axi_bready(dma_host_bready),
        .m_axi_araddr(dma_host_araddr), .m_axi_arvalid(dma_host_arvalid), .m_axi_arready(dma_host_arready),
        .m_axi_rdata(dma_host_rdata), .m_axi_rresp(dma_host_rresp), .m_axi_rvalid(dma_host_rvalid), .m_axi_rready(dma_host_rready),
        // MSI-X
        .msix_valid(msix_valid_i), .msix_ready(msix_ready_i),
        .msix_addr(msix_addr_i), .msix_data(msix_data_i),
        // Debug
        .dbg_tx_state(dbg_tx_state)
    );

    //=========================================================================
    // PCIe Sniffer (Debug) - 0x2xxx
    //=========================================================================
    wire wr_to_pcie_dbg = brg_awaddr[13] && !brg_awaddr[12];  // 0x2xxx write
    wire pcie_dbg_wen = brg_awvalid && brg_wvalid && wr_to_pcie_dbg;
    logic [31:0] pcie_dbg_rdata;
    
    pcie_sniffer u_sniffer (
        .clk, .rst_n,
        .rx_st_hdr, .rx_st_data, .rx_st_sop, .rx_st_hvalid, .rx_st_ready,
        .tx_st_hdr, .tx_st_data, .tx_st_sop, .tx_st_hvalid, .tx_st_ready,
        .tx_state(dbg_tx_state),
        .dbg_addr(dbg_addr_to_sniffer),
        .dbg_wdata(brg_wdata[31:0]),
        .dbg_wen(pcie_dbg_wen),
        .dbg_rdata(pcie_dbg_rdata)
    );

    //=========================================================================
    // AXI Sniffer (Debug) - 0x3xxx
    //=========================================================================
    wire wr_to_axi_dbg = brg_awaddr[13] && brg_awaddr[12];  // 0x3xxx write
    wire axi_dbg_wen = brg_awvalid && brg_wvalid && wr_to_axi_dbg;
    logic [31:0] axi_dbg_rdata;
    
    axi_sniffer #(.DEPTH(64)) u_axi_sniffer (
        .clk, .rst_n,
        // Snoop bridge -> DMA/RAM AXI bus
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
        // Debug interface
        .dbg_addr(dbg_addr_to_sniffer[7:0]),
        .dbg_wdata(brg_wdata[31:0]),
        .dbg_wen(axi_dbg_wen),
        .dbg_rdata(axi_dbg_rdata)
    );

    //=========================================================================
    // Address Decode: 0x0xxx=DMA, 0x1xxx=RAM, 0x2xxx=PCIe Debug, 0x3xxx=AXI Debug
    //=========================================================================
    wire wr_to_ram = brg_awaddr[12] && !brg_awaddr[13];  // 0x1xxx
    wire rd_to_ram = brg_araddr[12] && !brg_araddr[13];  // 0x1xxx
    wire rd_to_pcie_dbg = brg_araddr[13] && !brg_araddr[12];  // 0x2xxx
    wire rd_to_axi_dbg  = brg_araddr[13] && brg_araddr[12];   // 0x3xxx

    // Write path
    assign dma_s_awaddr  = brg_awaddr;
    assign dma_s_wdata   = brg_wdata;
    assign dma_s_wstrb   = brg_wstrb;
    assign dma_s_awvalid = brg_awvalid && !wr_to_ram;
    assign dma_s_wvalid  = brg_wvalid  && !wr_to_ram;
    assign dma_s_bready  = brg_bready;

    assign ram_bar_awaddr  = brg_awaddr;
    assign ram_bar_wdata   = brg_wdata;
    assign ram_bar_wstrb   = brg_wstrb;
    assign ram_bar_awvalid = brg_awvalid && wr_to_ram;
    assign ram_bar_wvalid  = brg_wvalid  && wr_to_ram;
    assign ram_bar_bready  = brg_bready;

    assign brg_awready = wr_to_ram ? ram_bar_awready : dma_s_awready;
    assign brg_wready  = wr_to_ram ? ram_bar_wready  : dma_s_wready;
    assign brg_bvalid  = dma_s_bvalid | ram_bar_bvalid;
    assign brg_bresp   = dma_s_bvalid ? dma_s_bresp : ram_bar_bresp;

    // Read path - with debug register support
    assign dma_s_araddr  = brg_araddr;
    assign dma_s_arvalid = brg_arvalid && !rd_to_ram && !rd_to_dbg;
    assign dma_s_rready  = brg_rready;

    assign ram_bar_araddr  = brg_araddr;
    assign ram_bar_arvalid = brg_arvalid && rd_to_ram;
    assign ram_bar_rready  = brg_rready;

    // Debug reads - 2-cycle pipeline for proper timing
    // Supports both PCIe sniffer (0x2xxx) and AXI sniffer (0x3xxx)
    // 2026-11-22: Fixed - latched address drives combinational sniffer mux,
    //             rvalid asserts one cycle after to allow combinational settle
    wire rd_to_dbg = rd_to_pcie_dbg || rd_to_axi_dbg;
    logic        dbg_rvalid;
    logic [63:0] dbg_rdata_ext;
    logic [31:0] dbg_rdata_latched;
    logic [11:0] dbg_addr_latched;
    logic        dbg_sel_axi_latched;  // 1=AXI sniffer, 0=PCIe sniffer
    logic        dbg_rd_pending;       // AR handshake done, waiting for data
    wire         dbg_ar_handshake = brg_arvalid && brg_arready && rd_to_dbg;
    
    // Latched address drives sniffers
    wire [11:0] dbg_addr_to_sniffer = (dbg_rd_pending || dbg_rvalid) ? dbg_addr_latched : brg_araddr[11:0];
    
    // Mux between PCIe sniffer and AXI sniffer data
    wire [31:0] dbg_rdata = dbg_sel_axi_latched ? axi_dbg_rdata : pcie_dbg_rdata;
    
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dbg_rvalid <= 0;
            dbg_rd_pending <= 0;
            dbg_rdata_latched <= 0;
            dbg_addr_latched <= 0;
            dbg_sel_axi_latched <= 0;
        end else begin
            if (dbg_ar_handshake && !dbg_rd_pending && !dbg_rvalid) begin
                // Cycle 0: AR handshake - latch address and select
                dbg_addr_latched <= brg_araddr[11:0];
                dbg_sel_axi_latched <= rd_to_axi_dbg;
                dbg_rd_pending <= 1;
            end else if (dbg_rd_pending && !dbg_rvalid) begin
                // Cycle 1: Address stable -> sample data, assert rvalid
                dbg_rdata_latched <= dbg_rdata;
                dbg_rvalid <= 1;
                dbg_rd_pending <= 0;
            end else if (dbg_rvalid && brg_rready) begin
                // Cycle 2+: R handshake complete
                dbg_rvalid <= 0;
            end
        end
    end
    assign dbg_rdata_ext = {32'b0, dbg_rdata_latched};  // Zero-extend to 64 bits

    assign brg_arready    = rd_to_dbg ? 1'b1 : (rd_to_ram ? ram_bar_arready : dma_s_arready);
    assign brg_rvalid_mux = dma_s_rvalid | ram_bar_rvalid | dbg_rvalid;
    assign brg_rdata_mux  = dma_s_rvalid ? dma_s_rdata : (ram_bar_rvalid ? ram_bar_rdata : dbg_rdata_ext);
    assign brg_rresp_mux  = dma_s_rvalid ? dma_s_rresp : (ram_bar_rvalid ? ram_bar_rresp : 2'b00);

    //=========================================================================
    // DMA Engine
    //=========================================================================
    dma_engine u_dma (
        .clk, .rst_n,
        // Control registers (BAR 0x0xxx)
        .s_axi_awaddr(dma_s_awaddr), .s_axi_awvalid(dma_s_awvalid), .s_axi_awready(dma_s_awready),
        .s_axi_wdata(dma_s_wdata), .s_axi_wstrb(dma_s_wstrb), .s_axi_wvalid(dma_s_wvalid), .s_axi_wready(dma_s_wready),
        .s_axi_bresp(dma_s_bresp), .s_axi_bvalid(dma_s_bvalid), .s_axi_bready(dma_s_bready),
        .s_axi_araddr(dma_s_araddr), .s_axi_arvalid(dma_s_arvalid), .s_axi_arready(dma_s_arready),
        .s_axi_rdata(dma_s_rdata), .s_axi_rresp(dma_s_rresp), .s_axi_rvalid(dma_s_rvalid), .s_axi_rready(dma_s_rready),
        // Local RAM access
        .m_local_awaddr(dma_local_awaddr), .m_local_awvalid(dma_local_awvalid), .m_local_awready(dma_local_awready),
        .m_local_wdata(dma_local_wdata), .m_local_wstrb(dma_local_wstrb), .m_local_wvalid(dma_local_wvalid), .m_local_wready(dma_local_wready),
        .m_local_bresp(dma_local_bresp), .m_local_bvalid(dma_local_bvalid), .m_local_bready(dma_local_bready),
        .m_local_araddr(dma_local_araddr), .m_local_arvalid(dma_local_arvalid), .m_local_arready(dma_local_arready),
        .m_local_rdata(dma_local_rdata), .m_local_rresp(dma_local_rresp), .m_local_rvalid(dma_local_rvalid), .m_local_rready(dma_local_rready),
        // Host memory access (via bridge)
        .m_host_awaddr(dma_host_awaddr), .m_host_awvalid(dma_host_awvalid), .m_host_awready(dma_host_awready),
        .m_host_wdata(dma_host_wdata), .m_host_wstrb(dma_host_wstrb), .m_host_wvalid(dma_host_wvalid), .m_host_wready(dma_host_wready),
        .m_host_bresp(dma_host_bresp), .m_host_bvalid(dma_host_bvalid), .m_host_bready(dma_host_bready),
        .m_host_araddr(dma_host_araddr), .m_host_arvalid(dma_host_arvalid), .m_host_arready(dma_host_arready),
        .m_host_rdata(dma_host_rdata), .m_host_rresp(dma_host_rresp), .m_host_rvalid(dma_host_rvalid), .m_host_rready(dma_host_rready),
        // IRQ
        .irq_req(dma_irq_req)
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
            msix_addr_reg <= 64'hFEE00000;  // Default x86 APIC
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

    //=========================================================================
    // RAM Arbiter (BAR vs DMA)
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
            // Release on response
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

    // Demux from RAM
    assign ram_bar_awready   = !arb_owner ? ram_awready : 0;
    assign ram_bar_wready    = !arb_owner ? ram_wready  : 0;
    assign ram_bar_bresp     = ram_bresp;
    assign ram_bar_bvalid    = !arb_owner ? ram_bvalid  : 0;
    assign ram_bar_arready   = !arb_owner ? ram_arready : 0;
    assign ram_bar_rdata     = ram_rdata;
    assign ram_bar_rresp     = ram_rresp;
    assign ram_bar_rvalid    = !arb_owner ? ram_rvalid  : 0;

    assign dma_local_awready = arb_owner ? ram_awready : 0;
    assign dma_local_wready  = arb_owner ? ram_wready  : 0;
    assign dma_local_bresp   = ram_bresp;
    assign dma_local_bvalid  = arb_owner ? ram_bvalid  : 0;
    assign dma_local_arready = arb_owner ? ram_arready : 0;
    assign dma_local_rdata   = ram_rdata;
    assign dma_local_rresp   = ram_rresp;
    assign dma_local_rvalid  = arb_owner ? ram_rvalid  : 0;

    //=========================================================================
    // AXI RAM (4KB)
    //=========================================================================
    axi_ram #(.DEPTH(512)) u_ram (
        .clk, .rst_n,
        .s_axi_awaddr(ram_awaddr[11:0]), .s_axi_awvalid(ram_awvalid), .s_axi_awready(ram_awready),
        .s_axi_wdata(ram_wdata), .s_axi_wstrb(ram_wstrb), .s_axi_wvalid(ram_wvalid), .s_axi_wready(ram_wready),
        .s_axi_bresp(ram_bresp), .s_axi_bvalid(ram_bvalid), .s_axi_bready(ram_bready),
        .s_axi_araddr(ram_araddr[11:0]), .s_axi_arvalid(ram_arvalid), .s_axi_arready(ram_arready),
        .s_axi_rdata(ram_rdata), .s_axi_rresp(ram_rresp), .s_axi_rvalid(ram_rvalid), .s_axi_rready(ram_rready)
    );

endmodule
