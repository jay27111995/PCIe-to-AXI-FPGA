//-----------------------------------------------------------------------------
// axi_regs.sv - Simple AXI-Lite register bank for testing
//
// 0x00: scratch (RW)
// 0x08: write_count (RO)
//-----------------------------------------------------------------------------
module axi_regs
    import rtile_pkg::*;
#(
    parameter int ADDR_W = 32,
    parameter int DATA_W = 64
)(
    input  logic clk,
    input  logic rst_n,

    // AXI-Lite Slave
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

    // Direct access (for testbench visibility)
    output logic [63:0]         scratch,
    output logic [31:0]         write_count
);

    // Registers
    logic [63:0] scratch_reg;
    logic [31:0] write_cnt;

    assign scratch = scratch_reg;
    assign write_count = write_cnt;

    // Write FSM
    typedef enum logic [1:0] { W_IDLE, W_DATA, W_RESP } wr_state_e;
    wr_state_e wr_state;
    logic [ADDR_W-1:0] wr_addr;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wr_state <= W_IDLE;
            s_axi_awready <= 0;
            s_axi_wready <= 0;
            s_axi_bvalid <= 0;
            s_axi_bresp <= AXI_OKAY;
            scratch_reg <= 64'hDEAD_BEEF_CAFE_BABE;
            write_cnt <= 0;
        end else begin
            case (wr_state)
                W_IDLE: begin
                    s_axi_awready <= 1;
                    s_axi_wready <= 1;
                    if (s_axi_awvalid && s_axi_wvalid) begin
                        // Got both address and data
                        wr_addr <= s_axi_awaddr;
                        s_axi_awready <= 0;
                        s_axi_wready <= 0;
                        
                        // Write to register
                        case (s_axi_awaddr[11:0])
                            12'h000: scratch_reg <= s_axi_wdata;
                            // 0x08 is read-only
                        endcase
                        write_cnt <= write_cnt + 1;
                        
                        s_axi_bvalid <= 1;
                        s_axi_bresp <= AXI_OKAY;
                        wr_state <= W_RESP;
                    end
                    else if (s_axi_awvalid) begin
                        wr_addr <= s_axi_awaddr;
                        s_axi_awready <= 0;
                        wr_state <= W_DATA;
                    end
                end

                W_DATA: begin
                    if (s_axi_wvalid) begin
                        s_axi_wready <= 0;
                        
                        case (wr_addr[11:0])
                            12'h000: scratch_reg <= s_axi_wdata;
                        endcase
                        write_cnt <= write_cnt + 1;
                        
                        s_axi_bvalid <= 1;
                        s_axi_bresp <= AXI_OKAY;
                        wr_state <= W_RESP;
                    end
                end

                W_RESP: begin
                    if (s_axi_bready) begin
                        s_axi_bvalid <= 0;
                        wr_state <= W_IDLE;
                    end
                end
            endcase
        end
    end

    // Read FSM
    typedef enum logic [1:0] { R_IDLE, R_DATA } rd_state_e;
    rd_state_e rd_state;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rd_state <= R_IDLE;
            s_axi_arready <= 0;
            s_axi_rvalid <= 0;
            s_axi_rresp <= AXI_OKAY;
            s_axi_rdata <= 0;
        end else begin
            case (rd_state)
                R_IDLE: begin
                    s_axi_arready <= 1;
                    if (s_axi_arvalid) begin
                        s_axi_arready <= 0;
                        
                        case (s_axi_araddr[11:0])
                            12'h000: s_axi_rdata <= scratch_reg;
                            12'h008: s_axi_rdata <= {32'b0, write_cnt};
                            default: s_axi_rdata <= 64'hFFFF_FFFF_FFFF_FFFF;
                        endcase
                        
                        s_axi_rvalid <= 1;
                        s_axi_rresp <= AXI_OKAY;
                        rd_state <= R_DATA;
                    end
                end

                R_DATA: begin
                    if (s_axi_rready) begin
                        s_axi_rvalid <= 0;
                        rd_state <= R_IDLE;
                    end
                end
            endcase
        end
    end

endmodule
