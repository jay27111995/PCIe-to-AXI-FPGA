//-----------------------------------------------------------------------------
// dma_engine.sv - BAR-triggered DMA controller
//
// Register Map:
//   0x00: ctrl       - [0]=start, [1]=dir (0=H2C, 1=C2H), [2]=irq_en
//   0x08: status     - [0]=busy, [1]=done, [2]=error
//   0x10: host_addr  - 64-bit host memory address
//   0x18: local_addr - 32-bit local RAM address
//   0x20: length     - bytes to transfer
//
// H2C (dir=0): Host → FPGA (PCIe MRd, then AXI write)
// C2H (dir=1): FPGA → Host (AXI read, then PCIe MWr)
//-----------------------------------------------------------------------------
module dma_engine
    import rtile_pkg::*;
#(
    parameter int ADDR_W = 32,
    parameter int DATA_W = 64
)(
    input  logic clk,
    input  logic rst_n,

    // AXI Slave - config registers
    input  logic [ADDR_W-1:0]   s_axi_awaddr,
    input  logic                s_axi_awvalid,
    output logic                s_axi_awready,
    input  logic [DATA_W-1:0]   s_axi_wdata,
    input  logic [DATA_W/8-1:0] s_axi_wstrb,
    input  logic                s_axi_wvalid,
    output logic                s_axi_wready,
    output logic [1:0]          s_axi_bresp,
    output logic                s_axi_bvalid,
    input  logic                s_axi_bready,
    input  logic [ADDR_W-1:0]   s_axi_araddr,
    input  logic                s_axi_arvalid,
    output logic                s_axi_arready,
    output logic [DATA_W-1:0]   s_axi_rdata,
    output logic [1:0]          s_axi_rresp,
    output logic                s_axi_rvalid,
    input  logic                s_axi_rready,

    // AXI Master - local RAM access
    output logic [ADDR_W-1:0]   m_axi_awaddr,
    output logic                m_axi_awvalid,
    input  logic                m_axi_awready,
    output logic [DATA_W-1:0]   m_axi_wdata,
    output logic [DATA_W/8-1:0] m_axi_wstrb,
    output logic                m_axi_wvalid,
    input  logic                m_axi_wready,
    input  logic [1:0]          m_axi_bresp,
    input  logic                m_axi_bvalid,
    output logic                m_axi_bready,
    output logic [ADDR_W-1:0]   m_axi_araddr,
    output logic                m_axi_arvalid,
    input  logic                m_axi_arready,
    input  logic [DATA_W-1:0]   m_axi_rdata,
    input  logic [1:0]          m_axi_rresp,
    input  logic                m_axi_rvalid,
    output logic                m_axi_rready,

    // PCIe interface
    output logic                pcie_mrd_valid,
    input  logic                pcie_mrd_ready,
    output logic [63:0]         pcie_mrd_addr,
    output logic [9:0]          pcie_mrd_len,
    output logic [7:0]          pcie_mrd_tag,
    output logic                pcie_mwr_valid,
    input  logic                pcie_mwr_ready,
    output logic [63:0]         pcie_mwr_addr,
    output logic [63:0]         pcie_mwr_data,
    output logic [9:0]          pcie_mwr_len,
    input  logic                pcie_cpl_valid,
    input  logic [7:0]          pcie_cpl_tag,
    input  logic [63:0]         pcie_cpl_data,

    output logic                dma_irq
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
    wire busy   = status_reg[0];

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
            if (start && !busy) ctrl_reg[0] <= 0;  // Auto-clear start

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
    // DMA Transfer FSM - Simple 4-state machine
    //=========================================================================
    typedef enum logic [1:0] {
        IDLE,
        FETCH,      // Get data from source (PCIe MRd or AXI read)
        STORE,      // Put data to destination (AXI write or PCIe MWr)
        DONE
    } state_e;

    state_e state;
    logic [31:0] bytes_left;
    logic [63:0] cur_host;
    logic [31:0] cur_local;
    logic [63:0] data_buf;
    logic [7:0]  tag;

    // Sub-state tracking
    logic fetch_issued, fetch_done;
    logic store_issued, store_done;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state <= IDLE;
            status_reg <= 0;
            bytes_left <= 0;
            cur_host <= 0;
            cur_local <= 0;
            data_buf <= 0;
            tag <= 0;
            fetch_issued <= 0;
            fetch_done <= 0;
            store_issued <= 0;
            store_done <= 0;
            
            pcie_mrd_valid <= 0;
            pcie_mwr_valid <= 0;
            m_axi_arvalid <= 0;
            m_axi_awvalid <= 0;
            m_axi_wvalid <= 0;
            m_axi_rready <= 0;
            m_axi_bready <= 0;
            dma_irq <= 0;
        end else begin
            dma_irq <= 0;

            case (state)
                //-------------------------------------------------------------
                IDLE: begin
                    status_reg[0] <= 0;  // Not busy
                    fetch_issued <= 0;
                    fetch_done <= 0;
                    store_issued <= 0;
                    store_done <= 0;
                    
                    if (start && length_reg > 0) begin
                        status_reg <= 32'h1;  // Busy
                        bytes_left <= length_reg;
                        cur_host <= host_addr;
                        cur_local <= local_addr;
                        tag <= 8'hA0;
                        state <= FETCH;
                    end
                end

                //-------------------------------------------------------------
                // FETCH: Get 8 bytes from source
                //   H2C: PCIe MRd from host, wait for CplD
                //   C2H: AXI read from local RAM
                //-------------------------------------------------------------
                FETCH: begin
                    if (!dir) begin
                        // H2C: Read from host via PCIe
                        if (!fetch_issued) begin
                            pcie_mrd_valid <= 1;
                            pcie_mrd_addr <= cur_host;
                            pcie_mrd_len <= 10'd2;
                            pcie_mrd_tag <= tag;
                            if (pcie_mrd_ready) begin
                                pcie_mrd_valid <= 0;
                                fetch_issued <= 1;
                            end
                        end else if (pcie_cpl_valid && pcie_cpl_tag == tag) begin
                            data_buf <= pcie_cpl_data;
                            fetch_issued <= 0;
                            state <= STORE;
                        end
                    end else begin
                        // C2H: Read from local RAM via AXI
                        if (!fetch_issued) begin
                            m_axi_araddr <= cur_local;
                            m_axi_arvalid <= 1;
                            m_axi_rready <= 1;
                            if (m_axi_arready) begin
                                m_axi_arvalid <= 0;
                                fetch_issued <= 1;
                            end
                        end else if (m_axi_rvalid) begin
                            data_buf <= m_axi_rdata;
                            m_axi_rready <= 0;
                            fetch_issued <= 0;
                            state <= STORE;
                        end
                    end
                end

                //-------------------------------------------------------------
                // STORE: Put 8 bytes to destination
                //   H2C: AXI write to local RAM
                //   C2H: PCIe MWr to host
                //-------------------------------------------------------------
                STORE: begin
                    if (!dir) begin
                        // H2C: Write to local RAM via AXI
                        if (!store_issued) begin
                            m_axi_awaddr <= cur_local;
                            m_axi_awvalid <= 1;
                            m_axi_wdata <= data_buf;
                            m_axi_wstrb <= 8'hFF;
                            m_axi_wvalid <= 1;
                            m_axi_bready <= 1;
                            store_issued <= 1;
                        end
                        if (m_axi_awvalid && m_axi_awready) m_axi_awvalid <= 0;
                        if (m_axi_wvalid && m_axi_wready) m_axi_wvalid <= 0;
                        if (m_axi_bvalid) begin
                            m_axi_bready <= 0;
                            store_issued <= 0;
                            cur_host <= cur_host + 8;
                            cur_local <= cur_local + 8;
                            tag <= tag + 1;
                            if (bytes_left <= 8)
                                state <= DONE;
                            else begin
                                bytes_left <= bytes_left - 8;
                                state <= FETCH;
                            end
                        end
                    end else begin
                        // C2H: Write to host via PCIe
                        if (!store_issued) begin
                            pcie_mwr_valid <= 1;
                            pcie_mwr_addr <= cur_host;
                            pcie_mwr_data <= data_buf;
                            pcie_mwr_len <= 10'd2;
                            store_issued <= 1;
                        end
                        if (pcie_mwr_valid && pcie_mwr_ready) begin
                            pcie_mwr_valid <= 0;
                            store_issued <= 0;
                            cur_host <= cur_host + 8;
                            cur_local <= cur_local + 8;
                            tag <= tag + 1;
                            if (bytes_left <= 8)
                                state <= DONE;
                            else begin
                                bytes_left <= bytes_left - 8;
                                state <= FETCH;
                            end
                        end
                    end
                end

                //-------------------------------------------------------------
                DONE: begin
                    status_reg <= 32'h2;  // Done, not busy
                    if (irq_en) dma_irq <= 1;
                    state <= IDLE;
                end
            endcase
        end
    end

endmodule
