//-----------------------------------------------------------------------------
// axi_ram.sv - Simple AXI-Lite RAM
//
// 4KB RAM accessible via AXI-Lite
//-----------------------------------------------------------------------------
module axi_ram
    import rtile_pkg::*;
#(
    parameter int ADDR_W = 32,
    parameter int DATA_W = 64,
    parameter int DEPTH  = 512   // 512 x 64b = 4KB
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
    input  logic                s_axi_rready
);

    localparam ADDR_BITS = $clog2(DEPTH);

    // RAM storage
    logic [DATA_W-1:0] mem [DEPTH];

    // Address extraction (word-aligned)
    wire [ADDR_BITS-1:0] wr_idx = s_axi_awaddr[ADDR_BITS+2:3];
    wire [ADDR_BITS-1:0] rd_idx = s_axi_araddr[ADDR_BITS+2:3];

    // Write channel
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_axi_awready <= 1;
            s_axi_wready <= 1;
            s_axi_bvalid <= 0;
            s_axi_bresp <= AXI_OKAY;
        end else begin
            if (s_axi_awvalid && s_axi_wvalid && s_axi_awready) begin
                // Byte-lane write
                for (int i = 0; i < DATA_W/8; i++) begin
                    if (s_axi_wstrb[i])
                        mem[wr_idx][i*8 +: 8] <= s_axi_wdata[i*8 +: 8];
                end
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

    // Read channel
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_axi_arready <= 1;
            s_axi_rvalid <= 0;
            s_axi_rresp <= AXI_OKAY;
            s_axi_rdata <= 0;
        end else begin
            if (s_axi_arvalid && s_axi_arready) begin
                s_axi_rdata <= mem[rd_idx];
                s_axi_arready <= 0;
                s_axi_rvalid <= 1;
            end
            
            if (s_axi_rvalid && s_axi_rready) begin
                s_axi_rvalid <= 0;
                s_axi_arready <= 1;
            end
        end
    end

endmodule
