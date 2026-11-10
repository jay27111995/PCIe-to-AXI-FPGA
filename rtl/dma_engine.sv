//-----------------------------------------------------------------------------
// dma_engine.sv - BAR-triggered DMA controller
//
// Register Map (BAR access):
//   0x00: ctrl     - [0]=start, [1]=dir (0=read/H2C, 1=write/C2H), [2]=irq_en
//   0x08: status   - [0]=busy, [1]=done, [2]=error
//   0x10: host_addr_lo
//   0x18: host_addr_hi
//   0x20: local_addr
//   0x28: length   - bytes to transfer
//
// DMA Read (H2C):  Host memory → local RAM (issues PCIe MRd, receives CplD)
// DMA Write (C2H): Local RAM → host memory (issues PCIe MWr)
//-----------------------------------------------------------------------------
module dma_engine
    import rtile_pkg::*;
#(
    parameter int ADDR_W = 32,
    parameter int DATA_W = 64
)(
    input  logic clk,
    input  logic rst_n,

    //-------------------------------------------------------------------------
    // AXI-Lite Slave (BAR control interface)
    //-------------------------------------------------------------------------
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

    //-------------------------------------------------------------------------
    // AXI-Lite Master (local RAM access)
    //-------------------------------------------------------------------------
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

    //-------------------------------------------------------------------------
    // PCIe DMA Request Interface (to rtile_top)
    //-------------------------------------------------------------------------
    // MRd request (H2C: read from host)
    output logic                pcie_mrd_valid,
    input  logic                pcie_mrd_ready,
    output logic [63:0]         pcie_mrd_addr,
    output logic [9:0]          pcie_mrd_len,     // DW count
    output logic [7:0]          pcie_mrd_tag,

    // MWr request (C2H: write to host)
    output logic                pcie_mwr_valid,
    input  logic                pcie_mwr_ready,
    output logic [63:0]         pcie_mwr_addr,
    output logic [63:0]         pcie_mwr_data,
    output logic [9:0]          pcie_mwr_len,

    // Completion data (response to MRd)
    input  logic                pcie_cpl_valid,
    input  logic [7:0]          pcie_cpl_tag,
    input  logic [63:0]         pcie_cpl_data,

    //-------------------------------------------------------------------------
    // Status
    //-------------------------------------------------------------------------
    output logic                dma_irq
);

    //-------------------------------------------------------------------------
    // Registers
    //-------------------------------------------------------------------------
    logic [31:0] ctrl_reg;
    logic [31:0] status_reg;
    logic [31:0] host_addr_lo;
    logic [31:0] host_addr_hi;
    logic [31:0] local_addr;
    logic [31:0] length_reg;

    wire start  = ctrl_reg[0];
    wire dir    = ctrl_reg[1];  // 0=H2C (read from host), 1=C2H (write to host)
    wire irq_en = ctrl_reg[2];

    wire busy  = status_reg[0];
    wire done  = status_reg[1];

    //-------------------------------------------------------------------------
    // BAR Register Access (AXI Slave)
    //-------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ctrl_reg <= 0;
            host_addr_lo <= 0;
            host_addr_hi <= 0;
            local_addr <= 0;
            length_reg <= 0;
            s_axi_awready <= 1;
            s_axi_wready <= 1;
            s_axi_bvalid <= 0;
            s_axi_bresp <= AXI_OKAY;
        end else begin
            // Auto-clear start bit
            if (start && !busy) ctrl_reg[0] <= 0;

            if (s_axi_awvalid && s_axi_wvalid && s_axi_awready) begin
                case (s_axi_awaddr[7:0])
                    8'h00: ctrl_reg     <= s_axi_wdata[31:0];
                    8'h10: host_addr_lo <= s_axi_wdata[31:0];
                    8'h18: host_addr_hi <= s_axi_wdata[31:0];
                    8'h20: local_addr   <= s_axi_wdata[31:0];
                    8'h28: length_reg   <= s_axi_wdata[31:0];
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

    // Read registers
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
                    8'h10: s_axi_rdata <= {32'b0, host_addr_lo};
                    8'h18: s_axi_rdata <= {32'b0, host_addr_hi};
                    8'h20: s_axi_rdata <= {32'b0, local_addr};
                    8'h28: s_axi_rdata <= {32'b0, length_reg};
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

    //-------------------------------------------------------------------------
    // DMA FSM
    //-------------------------------------------------------------------------
    typedef enum logic [3:0] {
        DMA_IDLE,
        // H2C (host to card) - read from host
        DMA_H2C_ISSUE_MRD,
        DMA_H2C_WAIT_CPL,
        DMA_H2C_WRITE_RAM,
        DMA_H2C_WAIT_RAM,
        // C2H (card to host) - write to host
        DMA_C2H_READ_RAM,
        DMA_C2H_WAIT_RAM,
        DMA_C2H_ISSUE_MWR,
        DMA_C2H_WAIT_MWR,
        // Done
        DMA_DONE
    } dma_state_e;

    dma_state_e dma_state;
    logic [31:0] bytes_remaining;
    logic [63:0] cur_host_addr;
    logic [31:0] cur_local_addr;
    logic [63:0] dma_data_buf;
    logic [7:0]  cur_tag;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dma_state <= DMA_IDLE;
            status_reg <= 0;
            bytes_remaining <= 0;
            cur_host_addr <= 0;
            cur_local_addr <= 0;
            cur_tag <= 0;
            dma_data_buf <= 0;
            
            pcie_mrd_valid <= 0;
            pcie_mwr_valid <= 0;
            m_axi_arvalid <= 0;
            m_axi_awvalid <= 0;
            m_axi_wvalid <= 0;
            m_axi_rready <= 0;
            m_axi_bready <= 0;
            dma_irq <= 0;
        end else begin
            dma_irq <= 0;  // Pulse

            case (dma_state)
                DMA_IDLE: begin
                    status_reg[0] <= 0;  // Not busy
                    if (start && length_reg > 0) begin
                        status_reg <= 32'h1;  // Busy
                        bytes_remaining <= length_reg;
                        cur_host_addr <= {host_addr_hi, host_addr_lo};
                        cur_local_addr <= local_addr;
                        cur_tag <= 8'hA0;
                        
                        if (!dir)
                            dma_state <= DMA_H2C_ISSUE_MRD;
                        else
                            dma_state <= DMA_C2H_READ_RAM;
                    end
                end

                //-------------------------------------------------------------
                // H2C: Read from host memory, write to local RAM
                //-------------------------------------------------------------
                DMA_H2C_ISSUE_MRD: begin
                    pcie_mrd_valid <= 1;
                    pcie_mrd_addr <= cur_host_addr;
                    pcie_mrd_len <= 10'd2;  // 2 DW = 8 bytes
                    pcie_mrd_tag <= cur_tag;
                    
                    if (pcie_mrd_ready) begin
                        pcie_mrd_valid <= 0;
                        dma_state <= DMA_H2C_WAIT_CPL;
                    end
                end

                DMA_H2C_WAIT_CPL: begin
                    if (pcie_cpl_valid && pcie_cpl_tag == cur_tag) begin
                        dma_data_buf <= pcie_cpl_data;
                        dma_state <= DMA_H2C_WRITE_RAM;
                    end
                end

                DMA_H2C_WRITE_RAM: begin
                    m_axi_awaddr <= cur_local_addr;
                    m_axi_awvalid <= 1;
                    m_axi_wdata <= dma_data_buf;
                    m_axi_wstrb <= 8'hFF;
                    m_axi_wvalid <= 1;
                    m_axi_bready <= 1;
                    dma_state <= DMA_H2C_WAIT_RAM;
                end

                DMA_H2C_WAIT_RAM: begin
                    if (m_axi_awready) m_axi_awvalid <= 0;
                    if (m_axi_wready) m_axi_wvalid <= 0;
                    
                    if (m_axi_bvalid) begin
                        m_axi_bready <= 0;
                        cur_host_addr <= cur_host_addr + 8;
                        cur_local_addr <= cur_local_addr + 8;
                        cur_tag <= cur_tag + 1;
                        
                        if (bytes_remaining <= 8) begin
                            bytes_remaining <= 0;
                            dma_state <= DMA_DONE;
                        end else begin
                            bytes_remaining <= bytes_remaining - 8;
                            dma_state <= DMA_H2C_ISSUE_MRD;
                        end
                    end
                end

                //-------------------------------------------------------------
                // C2H: Read from local RAM, write to host memory
                //-------------------------------------------------------------
                DMA_C2H_READ_RAM: begin
                    m_axi_araddr <= cur_local_addr;
                    m_axi_arvalid <= 1;
                    m_axi_rready <= 1;
                    dma_state <= DMA_C2H_WAIT_RAM;
                end

                DMA_C2H_WAIT_RAM: begin
                    if (m_axi_arready) m_axi_arvalid <= 0;
                    
                    if (m_axi_rvalid) begin
                        m_axi_rready <= 0;
                        dma_data_buf <= m_axi_rdata;
                        dma_state <= DMA_C2H_ISSUE_MWR;
                    end
                end

                DMA_C2H_ISSUE_MWR: begin
                    pcie_mwr_valid <= 1;
                    pcie_mwr_addr <= cur_host_addr;
                    pcie_mwr_data <= dma_data_buf;
                    pcie_mwr_len <= 10'd2;
                    dma_state <= DMA_C2H_WAIT_MWR;
                end

                DMA_C2H_WAIT_MWR: begin
                    if (pcie_mwr_ready) begin
                        pcie_mwr_valid <= 0;
                        cur_host_addr <= cur_host_addr + 8;
                        cur_local_addr <= cur_local_addr + 8;
                        
                        if (bytes_remaining <= 8) begin
                            bytes_remaining <= 0;
                            dma_state <= DMA_DONE;
                        end else begin
                            bytes_remaining <= bytes_remaining - 8;
                            dma_state <= DMA_C2H_READ_RAM;
                        end
                    end
                end

                //-------------------------------------------------------------
                // Done
                //-------------------------------------------------------------
                DMA_DONE: begin
                    status_reg <= 32'h2;  // Done, not busy
                    if (irq_en) dma_irq <= 1;
                    dma_state <= DMA_IDLE;
                end
            endcase
        end
    end

endmodule
