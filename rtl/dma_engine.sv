//-----------------------------------------------------------------------------
// dma_engine.sv - DMA controller with separate H2C and C2H engines
//
// Register Map (AXI slave):
//   0x00: ctrl       - [0]=start, [1]=dir (0=H2C, 1=C2H), [2]=irq_en
//   0x08: status     - [0]=busy, [1]=done, [2]=error
//   0x10: host_addr  - 64-bit host memory address
//   0x18: local_addr - 32-bit local RAM address
//   0x20: length     - bytes to transfer
//-----------------------------------------------------------------------------
module dma_engine
    import rtile_pkg::*;
(
    input  logic clk,
    input  logic rst_n,

    // AXI Slave - config registers
    input  logic [31:0]  s_axi_awaddr,
    input  logic         s_axi_awvalid,
    output logic         s_axi_awready,
    input  logic [63:0]  s_axi_wdata,
    input  logic [7:0]   s_axi_wstrb,
    input  logic         s_axi_wvalid,
    output logic         s_axi_wready,
    output logic [1:0]   s_axi_bresp,
    output logic         s_axi_bvalid,
    input  logic         s_axi_bready,
    input  logic [31:0]  s_axi_araddr,
    input  logic         s_axi_arvalid,
    output logic         s_axi_arready,
    output logic [63:0]  s_axi_rdata,
    output logic [1:0]   s_axi_rresp,
    output logic         s_axi_rvalid,
    input  logic         s_axi_rready,

    // AXI Master - local RAM
    output logic [31:0]  m_local_awaddr,
    output logic         m_local_awvalid,
    input  logic         m_local_awready,
    output logic [63:0]  m_local_wdata,
    output logic [7:0]   m_local_wstrb,
    output logic         m_local_wvalid,
    input  logic         m_local_wready,
    input  logic [1:0]   m_local_bresp,
    input  logic         m_local_bvalid,
    output logic         m_local_bready,
    output logic [31:0]  m_local_araddr,
    output logic         m_local_arvalid,
    input  logic         m_local_arready,
    input  logic [63:0]  m_local_rdata,
    input  logic [1:0]   m_local_rresp,
    input  logic         m_local_rvalid,
    output logic         m_local_rready,

    // AXI Master - host memory (via PCIe)
    output logic [63:0]  m_host_awaddr,
    output logic         m_host_awvalid,
    input  logic         m_host_awready,
    output logic [63:0]  m_host_wdata,
    output logic [7:0]   m_host_wstrb,
    output logic         m_host_wvalid,
    input  logic         m_host_wready,
    input  logic [1:0]   m_host_bresp,
    input  logic         m_host_bvalid,
    output logic         m_host_bready,
    output logic [63:0]  m_host_araddr,
    output logic         m_host_arvalid,
    input  logic         m_host_arready,
    input  logic [63:0]  m_host_rdata,
    input  logic [1:0]   m_host_rresp,
    input  logic         m_host_rvalid,
    output logic         m_host_rready,

    // Interrupt request (directly generates PCIe MWr TLP)
    output logic         irq_req
);

    //=========================================================================
    // Config Registers
    //=========================================================================
    logic [31:0] ctrl_reg, status_reg;
    logic [63:0] host_addr;
    logic [31:0] local_addr, length_reg;

    wire start  = ctrl_reg[0];
    wire dir    = ctrl_reg[1];  // 0=H2C, 1=C2H
    wire irq_en = ctrl_reg[2];

    // Engine status
    logic h2c_busy, h2c_done;
    logic c2h_busy, c2h_done;
    wire busy = h2c_busy | c2h_busy;
    wire done = h2c_done | c2h_done;

    always_comb begin
        status_reg = {30'b0, done, busy};
    end

    // Register write
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ctrl_reg <= 0;
            host_addr <= 0;
            local_addr <= 0;
            length_reg <= 0;
            s_axi_awready <= 1;
            s_axi_wready <= 1;
            s_axi_bvalid <= 0;
            s_axi_bresp <= AXI_OKAY;
        end else begin
            // Auto-clear start when engine accepts
            if (start && !busy) ctrl_reg[0] <= 0;

            if (s_axi_awvalid && s_axi_wvalid && s_axi_awready) begin
                case (s_axi_awaddr[7:0])
                    8'h00: ctrl_reg   <= s_axi_wdata[31:0];
                    8'h10: host_addr  <= s_axi_wdata;
                    8'h18: local_addr <= s_axi_wdata[31:0];
                    8'h20: length_reg <= s_axi_wdata[31:0];
                endcase
                s_axi_awready <= 0;
                s_axi_wready <= 0;
                s_axi_bvalid <= 1;
            end
            
            if (s_axi_bvalid && s_axi_bready) begin
                s_axi_bvalid <= 0;
                s_axi_awready <= 1;
                s_axi_wready <= 1;
            end
        end
    end

    // Register read
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_axi_arready <= 1;
            s_axi_rvalid <= 0;
            s_axi_rresp <= AXI_OKAY;
            s_axi_rdata <= 0;
        end else begin
            if (s_axi_arvalid && s_axi_arready) begin
                case (s_axi_araddr[7:0])
                    8'h00: s_axi_rdata <= {32'b0, ctrl_reg};
                    8'h08: s_axi_rdata <= {32'b0, status_reg};
                    8'h10: s_axi_rdata <= host_addr;
                    8'h18: s_axi_rdata <= {32'b0, local_addr};
                    8'h20: s_axi_rdata <= {32'b0, length_reg};
                    default: s_axi_rdata <= 64'hDEAD_DEAD;
                endcase
                s_axi_arready <= 0;
                s_axi_rvalid <= 1;
            end
            
            if (s_axi_rvalid && s_axi_rready) begin
                s_axi_rvalid <= 0;
                s_axi_arready <= 1;
            end
        end
    end

    //=========================================================================
    // Interrupt Request - pulse when DMA completes and irq_en is set
    // PCIe layer converts this to MSI-X TLP
    //=========================================================================
    logic done_r;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            irq_req <= 0;
            done_r <= 0;
        end else begin
            done_r <= done;
            // Rising edge of done + irq enabled
            irq_req <= done && !done_r && irq_en;
        end
    end

    //=========================================================================
    // H2C and C2H internal signals
    //=========================================================================
    // H2C: reads host, writes local
    logic [63:0] h2c_host_araddr;
    logic        h2c_host_arvalid, h2c_host_rready;
    logic [31:0] h2c_local_awaddr;
    logic        h2c_local_awvalid, h2c_local_wvalid, h2c_local_bready;
    logic [63:0] h2c_local_wdata;
    logic [7:0]  h2c_local_wstrb;

    // C2H: reads local, writes host
    logic [31:0] c2h_local_araddr;
    logic        c2h_local_arvalid, c2h_local_rready;
    logic [63:0] c2h_host_awaddr;
    logic        c2h_host_awvalid, c2h_host_wvalid, c2h_host_bready;
    logic [63:0] c2h_host_wdata;
    logic [7:0]  c2h_host_wstrb;

    //=========================================================================
    // Port muxing - only one engine active at a time
    //=========================================================================
    // Host read (H2C only)
    assign m_host_araddr  = h2c_host_araddr;
    assign m_host_arvalid = h2c_host_arvalid;
    assign m_host_rready  = h2c_host_rready;

    // Host write (C2H only)
    assign m_host_awaddr  = c2h_host_awaddr;
    assign m_host_awvalid = c2h_host_awvalid;
    assign m_host_wdata   = c2h_host_wdata;
    assign m_host_wstrb   = c2h_host_wstrb;
    assign m_host_wvalid  = c2h_host_wvalid;
    assign m_host_bready  = c2h_host_bready;

    // Local read (C2H only)
    assign m_local_araddr  = c2h_local_araddr;
    assign m_local_arvalid = c2h_local_arvalid;
    assign m_local_rready  = c2h_local_rready;

    // Local write (H2C only)
    assign m_local_awaddr  = h2c_local_awaddr;
    assign m_local_awvalid = h2c_local_awvalid;
    assign m_local_wdata   = h2c_local_wdata;
    assign m_local_wstrb   = h2c_local_wstrb;
    assign m_local_wvalid  = h2c_local_wvalid;
    assign m_local_bready  = h2c_local_bready;

    //=========================================================================
    // H2C Engine: Host → FPGA (read from m_host, write to m_local)
    //=========================================================================
    dma_h2c u_h2c (
        .clk, .rst_n,
        .start(start && !dir && !busy),
        .host_addr, .local_addr, .length(length_reg),
        .busy(h2c_busy), .done(h2c_done),
        // Host read
        .m_host_araddr(h2c_host_araddr),
        .m_host_arvalid(h2c_host_arvalid),
        .m_host_arready,
        .m_host_rdata, .m_host_rresp, .m_host_rvalid,
        .m_host_rready(h2c_host_rready),
        // Local write
        .m_local_awaddr(h2c_local_awaddr),
        .m_local_awvalid(h2c_local_awvalid),
        .m_local_awready,
        .m_local_wdata(h2c_local_wdata),
        .m_local_wstrb(h2c_local_wstrb),
        .m_local_wvalid(h2c_local_wvalid),
        .m_local_wready,
        .m_local_bresp, .m_local_bvalid,
        .m_local_bready(h2c_local_bready)
    );

    //=========================================================================
    // C2H Engine: FPGA → Host (read from m_local, write to m_host)
    //=========================================================================
    dma_c2h u_c2h (
        .clk, .rst_n,
        .start(start && dir && !busy),
        .host_addr, .local_addr, .length(length_reg),
        .busy(c2h_busy), .done(c2h_done),
        // Local read
        .m_local_araddr(c2h_local_araddr),
        .m_local_arvalid(c2h_local_arvalid),
        .m_local_arready,
        .m_local_rdata, .m_local_rresp, .m_local_rvalid,
        .m_local_rready(c2h_local_rready),
        // Host write
        .m_host_awaddr(c2h_host_awaddr),
        .m_host_awvalid(c2h_host_awvalid),
        .m_host_awready,
        .m_host_wdata(c2h_host_wdata),
        .m_host_wstrb(c2h_host_wstrb),
        .m_host_wvalid(c2h_host_wvalid),
        .m_host_wready,
        .m_host_bresp, .m_host_bvalid,
        .m_host_bready(c2h_host_bready)
    );

endmodule


//=============================================================================
// H2C: Host to Card - Read from host, write to local RAM
//=============================================================================
module dma_h2c (
    input  logic clk,
    input  logic rst_n,

    input  logic        start,
    input  logic [63:0] host_addr,
    input  logic [31:0] local_addr,
    input  logic [31:0] length,
    output logic        busy,
    output logic        done,

    // AXI Master - read from host
    output logic [63:0] m_host_araddr,
    output logic        m_host_arvalid,
    input  logic        m_host_arready,
    input  logic [63:0] m_host_rdata,
    input  logic [1:0]  m_host_rresp,
    input  logic        m_host_rvalid,
    output logic        m_host_rready,

    // AXI Master - write to local
    output logic [31:0] m_local_awaddr,
    output logic        m_local_awvalid,
    input  logic        m_local_awready,
    output logic [63:0] m_local_wdata,
    output logic [7:0]  m_local_wstrb,
    output logic        m_local_wvalid,
    input  logic        m_local_wready,
    input  logic [1:0]  m_local_bresp,
    input  logic        m_local_bvalid,
    output logic        m_local_bready
);

    typedef enum logic [2:0] {
        IDLE,
        RD_ADDR,    // Issue read address to host
        RD_DATA,    // Wait for read data
        WR_ADDR,    // Issue write address+data to local
        WR_RESP,    // Wait for write response
        DONE
    } state_e;

    state_e state;
    logic [63:0] cur_host;
    logic [31:0] cur_local;
    logic [31:0] bytes_left;
    logic [63:0] data_buf;

    assign busy = (state != IDLE) && (state != DONE);
    assign done = (state == DONE);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state <= IDLE;
            cur_host <= 0;
            cur_local <= 0;
            bytes_left <= 0;
            data_buf <= 0;
            m_host_araddr <= 0;
            m_host_arvalid <= 0;
            m_host_rready <= 0;
            m_local_awaddr <= 0;
            m_local_awvalid <= 0;
            m_local_wdata <= 0;
            m_local_wstrb <= 0;
            m_local_wvalid <= 0;
            m_local_bready <= 0;
        end else begin
            case (state)
                IDLE: begin
                    if (start && length > 0) begin
                        cur_host <= host_addr;
                        cur_local <= local_addr;
                        bytes_left <= length;
                        state <= RD_ADDR;
                    end
                end

                RD_ADDR: begin
                    m_host_araddr <= cur_host;
                    m_host_arvalid <= 1;
                    if (m_host_arvalid && m_host_arready) begin
                        m_host_arvalid <= 0;
                        m_host_rready <= 1;
                        state <= RD_DATA;
                    end
                end

                RD_DATA: begin
                    if (m_host_rvalid) begin
                        data_buf <= m_host_rdata;
                        m_host_rready <= 0;
                        // Setup write address/data for next state
                        m_local_awaddr <= cur_local;
                        m_local_wdata <= m_host_rdata;  // Use rdata directly
                        m_local_wstrb <= 8'hFF;
                        state <= WR_ADDR;
                    end
                end

                WR_ADDR: begin
                    // Assert both AW and W together
                    m_local_awvalid <= 1;
                    m_local_wvalid <= 1;
                    // Wait for BOTH channels to be accepted
                    if (m_local_awvalid && m_local_awready && m_local_wvalid && m_local_wready) begin
                        m_local_awvalid <= 0;
                        m_local_wvalid <= 0;
                        m_local_bready <= 1;
                        state <= WR_RESP;
                    end
                end

                // WR_DATA removed - merged into WR_ADDR

                WR_RESP: begin
                    if (m_local_bvalid) begin
                        m_local_bready <= 0;
                        cur_host <= cur_host + 8;
                        cur_local <= cur_local + 8;
                        if (bytes_left <= 8)
                            state <= DONE;
                        else begin
                            bytes_left <= bytes_left - 8;
                            state <= RD_ADDR;
                        end
                    end
                end

                DONE: begin
                    state <= IDLE;
                end
            endcase
        end
    end

endmodule


//=============================================================================
// C2H: Card to Host - Read from local RAM, write to host
//=============================================================================
module dma_c2h (
    input  logic clk,
    input  logic rst_n,

    input  logic        start,
    input  logic [63:0] host_addr,
    input  logic [31:0] local_addr,
    input  logic [31:0] length,
    output logic        busy,
    output logic        done,

    // AXI Master - read from local
    output logic [31:0] m_local_araddr,
    output logic        m_local_arvalid,
    input  logic        m_local_arready,
    input  logic [63:0] m_local_rdata,
    input  logic [1:0]  m_local_rresp,
    input  logic        m_local_rvalid,
    output logic        m_local_rready,

    // AXI Master - write to host
    output logic [63:0] m_host_awaddr,
    output logic        m_host_awvalid,
    input  logic        m_host_awready,
    output logic [63:0] m_host_wdata,
    output logic [7:0]  m_host_wstrb,
    output logic        m_host_wvalid,
    input  logic        m_host_wready,
    input  logic [1:0]  m_host_bresp,
    input  logic        m_host_bvalid,
    output logic        m_host_bready
);

    typedef enum logic [2:0] {
        IDLE,
        RD_ADDR,    // Issue read address to local
        RD_DATA,    // Wait for read data
        WR_ADDR,    // Issue write address+data to host
        WR_RESP,    // Wait for write response
        DONE
    } state_e;

    state_e state;
    logic [63:0] cur_host;
    logic [31:0] cur_local;
    logic [31:0] bytes_left;
    logic [63:0] data_buf;

    assign busy = (state != IDLE) && (state != DONE);
    assign done = (state == DONE);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state <= IDLE;
            cur_host <= 0;
            cur_local <= 0;
            bytes_left <= 0;
            data_buf <= 0;
            m_local_araddr <= 0;
            m_local_arvalid <= 0;
            m_local_rready <= 0;
            m_host_awaddr <= 0;
            m_host_awvalid <= 0;
            m_host_wdata <= 0;
            m_host_wstrb <= 0;
            m_host_wvalid <= 0;
            m_host_bready <= 0;
        end else begin
            case (state)
                IDLE: begin
                    if (start && length > 0) begin
                        cur_host <= host_addr;
                        cur_local <= local_addr;
                        bytes_left <= length;
                        state <= RD_ADDR;
                    end
                end

                RD_ADDR: begin
                    m_local_araddr <= cur_local;
                    m_local_arvalid <= 1;
                    if (m_local_arvalid && m_local_arready) begin
                        m_local_arvalid <= 0;
                        m_local_rready <= 1;
                        state <= RD_DATA;
                    end
                end

                RD_DATA: begin
                    if (m_local_rvalid) begin
                        data_buf <= m_local_rdata;
                        m_local_rready <= 0;
                        // Setup write address/data for next state
                        m_host_awaddr <= cur_host;
                        m_host_wdata <= m_local_rdata;  // Use rdata directly
                        m_host_wstrb <= 8'hFF;
                        state <= WR_ADDR;
                    end
                end

                WR_ADDR: begin
                    // Assert both AW and W together (axi_pcie_master needs both)
                    m_host_awvalid <= 1;
                    m_host_wvalid <= 1;
                    // Wait for BOTH channels to be accepted
                    if (m_host_awvalid && m_host_awready && m_host_wvalid && m_host_wready) begin
                        m_host_awvalid <= 0;
                        m_host_wvalid <= 0;
                        m_host_bready <= 1;
                        state <= WR_RESP;
                    end
                end

                // WR_DATA removed - merged into WR_ADDR

                WR_RESP: begin
                    if (m_host_bvalid) begin
                        m_host_bready <= 0;
                        cur_host <= cur_host + 8;
                        cur_local <= cur_local + 8;
                        if (bytes_left <= 8)
                            state <= DONE;
                        else begin
                            bytes_left <= bytes_left - 8;
                            state <= RD_ADDR;
                        end
                    end
                end

                DONE: begin
                    state <= IDLE;
                end
            endcase
        end
    end

endmodule
