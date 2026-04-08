`timescale 1 ps / 1 ps
`default_nettype none

// DMA core with AXI debug logging
// Page 0 (0x000-0xFFF): Registers
//   0x00: RESET       0x08: SRC_ADDR    0x10: DST_ADDR    0x18: LEN    0x20: CTRL[0]=GO,[1]=BUSY
//   0x28: DBG_STATE   0x30: DBG_RADDR   0x38: DBG_RDATA   0x40: DBG_WADDR  0x48: DBG_WDATA
//   0x50: DBG_CNT (read/write counts)
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

  typedef enum logic [2:0] {IDLE, READ, WAIT_RDATA, WRITE, WAIT_WDONE} state_t;
  state_t state;

  // Debug registers
  logic [63:0] dbg_raddr, dbg_rdata, dbg_waddr, dbg_wdata;
  logic [15:0] dbg_rcnt, dbg_wcnt;
  logic [7:0]  dbg_state_hist;

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

  // Debug: capture AXI transactions
  always_ff @(posedge clk) begin
    if (rst) begin
      dbg_raddr <= '0; dbg_rdata <= '0;
      dbg_waddr <= '0; dbg_wdata <= '0;
      dbg_rcnt <= '0; dbg_wcnt <= '0;
      dbg_state_hist <= '0;
    end else begin
      // Capture read request
      if (rburst_req_valid && rburst_req_ready) begin
        dbg_raddr <= rburst_req_addr;
        dbg_rcnt <= dbg_rcnt + 1;
      end
      // Capture read response
      if (rburst_rsp_valid) begin
        dbg_rdata <= rburst_rsp_data;
      end
      // Capture write request
      if (wburst_req_valid && wburst_req_ready) begin
        dbg_waddr <= wburst_req_addr;
        dbg_wdata <= wburst_req_data;
        dbg_wcnt <= dbg_wcnt + 1;
      end
      // State history
      dbg_state_hist <= {dbg_state_hist[4:0], state};
    end
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
        WRITE: if (wburst_req_ready) state <= WAIT_WDONE;
        WAIT_WDONE: if (wburst_rsp_valid) begin
          if (xfer_cnt + 1 >= reg_len) begin state <= IDLE; busy <= 0; end
          else begin xfer_cnt <= xfer_cnt + 1; state <= READ; end
        end
      endcase
    end
  end

  // Register reads
  logic [63:0] reg_rdata;
  always_comb begin
    case (bar_raddr[6:3])
      4'd0: reg_rdata = '0;
      4'd1: reg_rdata = reg_src;
      4'd2: reg_rdata = reg_dst;
      4'd3: reg_rdata = {56'd0, reg_len};
      4'd4: reg_rdata = {62'd0, busy, 1'b0};
      4'd5: reg_rdata = {53'd0, dbg_state_hist, state};  // 0x28: DBG_STATE
      4'd6: reg_rdata = dbg_raddr;                       // 0x30: DBG_RADDR
      4'd7: reg_rdata = dbg_rdata;                       // 0x38: DBG_RDATA
      4'd8: reg_rdata = dbg_waddr;                       // 0x40: DBG_WADDR
      4'd9: reg_rdata = dbg_wdata;                       // 0x48: DBG_WDATA
      4'd10: reg_rdata = {32'd0, dbg_wcnt, dbg_rcnt};    // 0x50: DBG_CNT
      default: reg_rdata = '0;
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
