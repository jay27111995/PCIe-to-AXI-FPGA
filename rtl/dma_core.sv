`timescale 1 ps / 1 ps
`default_nettype none

// DMA core - memcpy via BAR registers
// Page 0 (0x000-0xFFF): Registers
//   0x00: RESET       0x08: SRC_ADDR    0x10: DST_ADDR    0x18: LEN    0x20: CTRL[0]=GO,[1]=BUSY
// Pages 1-4 (0x1000-0x4FFF): 16KB SRAM

module dma_core (
    input  wire          clk,
    input  wire          rst_n,
    input  wire  [19:0]  bar_raddr,
    input  wire  [19:0]  bar_waddr,
    output logic [63:0]  bar_rdata,
    input  wire  [63:0]  bar_wdata,
    input  wire          bar_wen,
    input  wire          rburst_req_ready,
    output logic         rburst_req_valid,
    output logic [3:0]   rburst_req_id,
    output logic [63:0]  rburst_req_addr,
    output logic [7:0]   rburst_req_len,
    input  wire          rburst_rsp_valid,
    input  wire  [3:0]   rburst_rsp_id,
    input  wire  [63:0]  rburst_rsp_data,
    input  wire          wburst_req_ready,
    output logic         wburst_req_valid,
    output logic [3:0]   wburst_req_id,
    output logic [63:0]  wburst_req_addr,
    output logic [63:0]  wburst_req_data,
    output logic [7:0]   wburst_req_len,
    input  wire          wburst_rsp_valid,
    input  wire  [3:0]   wburst_rsp_id
);

  // Registers
  logic [63:0] reg_src, reg_dst;
  logic [7:0]  reg_len, xfer_cnt;
  logic        busy, soft_rst;

  wire rst = ~rst_n | soft_rst;

  typedef enum logic [1:0] {IDLE, READ, WAIT_RDATA, WRITE} state_t;
  state_t state;

  // Latch for read data
  logic [63:0] rdata_latched;
  logic rdata_valid;

  // 16KB SRAM (2048 x 64-bit)
  logic [63:0] mem [0:2047];
  logic [63:0] mem_rdata;

  // Memory write
  always_ff @(posedge clk) begin
    if (bar_wen && bar_waddr[14:12] != 0)
      mem[bar_waddr[13:3]] <= bar_wdata;
  end

  // Memory read
  always_ff @(posedge clk) begin
    mem_rdata <= mem[bar_raddr[13:3]];
  end

  // Latch read response data
  always_ff @(posedge clk) begin
    if (rst) begin
      rdata_valid <= 0;
      rdata_latched <= '0;
    end else if (rburst_rsp_valid) begin
      rdata_latched <= rburst_rsp_data;
      rdata_valid <= 1;
    end else if (state == WRITE && wburst_req_ready) begin
      rdata_valid <= 0;
    end
  end

  // State machine
  always_ff @(posedge clk) begin
    if (rst) begin
      reg_src <= '0; reg_dst <= '0; reg_len <= '0;
      state <= IDLE; xfer_cnt <= '0; busy <= '0; soft_rst <= '0;
    end else begin
      soft_rst <= '0;
      case (state)
        IDLE: begin
          if (bar_wen && bar_waddr[14:12] == 0) begin
            case (bar_waddr[5:3])
              3'd0: soft_rst <= bar_wdata[0];
              3'd1: reg_src <= bar_wdata;
              3'd2: reg_dst <= bar_wdata;
              3'd3: reg_len <= bar_wdata[7:0];
              3'd4: if (bar_wdata[0]) begin state <= READ; xfer_cnt <= '0; busy <= 1; end
            endcase
          end
        end
        READ: if (rburst_req_ready) state <= WAIT_RDATA;
        WAIT_RDATA: if (rdata_valid) state <= WRITE;
        WRITE: if (wburst_req_ready) begin
          if (xfer_cnt + 1 >= reg_len) begin state <= IDLE; busy <= 0; end
          else begin xfer_cnt <= xfer_cnt + 1; state <= READ; end
        end
      endcase
    end
  end

  // Register reads
  logic [63:0] reg_rdata;
  always_comb begin
    case (bar_raddr[5:3])
      3'd0: reg_rdata = '0;
      3'd1: reg_rdata = reg_src;
      3'd2: reg_rdata = reg_dst;
      3'd3: reg_rdata = {56'd0, reg_len};
      default: reg_rdata = {62'd0, busy, 1'b0};
    endcase
  end

  // BAR read mux: page 0 = regs, pages 1-4 = mem
  assign bar_rdata = (bar_raddr[14:12] == 0) ? reg_rdata : mem_rdata;

  // AXI burst - read request
  assign rburst_req_valid = (state == READ);
  assign rburst_req_id    = '0;
  assign rburst_req_addr  = reg_src + {53'd0, xfer_cnt, 3'd0};
  assign rburst_req_len   = '0;

  // AXI burst - write request (use latched data)
  assign wburst_req_valid = (state == WRITE);
  assign wburst_req_id    = '0;
  assign wburst_req_addr  = reg_dst + {53'd0, xfer_cnt, 3'd0};
  assign wburst_req_data  = rdata_latched;
  assign wburst_req_len   = '0;

endmodule
