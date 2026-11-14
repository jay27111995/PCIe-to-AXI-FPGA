`timescale 1 ps / 1 ps

`default_nettype none

typedef enum logic [7:0]{
  OP_ADD,
  OP_AND,
  OP_BEQ,
  OP_BNE,
  OP_JUMP,
  OP_MRD,
  OP_MWR,
  OP_NOP,
  OP_OR,
  OP_STOP,
  OP_SUB,
  OP_WAIT,
  OP_XOR,
  OP_SLOT
} opcode_t;

typedef struct packed {
  opcode_t op;
  logic [1:0] op0; // 2'b00 = reg0, 2'b01 = reg1, 2'b10 = reg2, 2'b11 = imm64
  logic [1:0] op1;
  logic [1:0] res; // 2'b00 = reg0, 2'b01 = reg1, 2'b10 = reg2, 2'b11 = no result
  union packed {
    struct packed {
      logic [3:0] mrd_sem;
      logic [7:0] len;
      logic [2:0] attr;
      logic       th;
      logic [1:0] ph;
      logic [9:0] mrd_mem_slot;
      logic [21:0] _padding_;
    } mem;
    struct packed {
      logic [33:0] _padding_;
      logic [15:0] target;
    } jump;
    logic [49:0] _padding_;
  }u;
  logic [63:0] imm64;
} instr_t;

typedef struct packed {
  logic [15:0] pc;
  logic [3:0] idx; // Thread idx
  logic [191:0] regs;
} thread_ctx_t;

typedef struct packed {
  logic valid;
  thread_ctx_t tctx;
} pipe_if0_if1_t;

typedef struct packed {
  logic valid;
  thread_ctx_t tctx;
  instr_t instr;
} pipe_if1_exe_t;

typedef struct packed {
  logic valid;
  thread_ctx_t tctx;
} pipe_exe_wb_t;

typedef struct packed {
  logic [3:0] sem_idx;
  logic [9:0] mem_idx;
} taginfo_t;

typedef struct packed {
  logic [31:0] timestamp;
  logic [63:0] addr;
  logic mwr_valid;
  logic mrd_valid;
  logic [9:0] mrd_tag;
  logic cpld_valid;
  logic [9:0] cpld_tag;
  logic [8:0] _reserved;
} event_t;

module bram_sp #(
  parameter int ADDR_WIDTH = 10, // depth = 2**ADDR_WIDTH
  parameter int DATA_WIDTH = 32
) (
  input wire clk,
  input wire en, // enable
  input wire we, // write enable
  input wire [ADDR_WIDTH-1:0] addr,
  input wire [DATA_WIDTH-1:0] din,
  output logic [DATA_WIDTH-1:0] dout
);

  logic [DATA_WIDTH-1:0] mem [0:(1<<ADDR_WIDTH)-1];

  always_ff @(posedge clk) begin
      if (en) begin
          if (we) begin
              mem[addr] <= din;
          end
          // Synchronous read
          dout <= mem[addr];
      end
  end
endmodule

module bram_sdp #(
  parameter int ADDR_WIDTH = 10,
  parameter int DATA_WIDTH = 32
) (

  // Write port
  input wire wclk,
  input wire we,
  input wire [ADDR_WIDTH-1:0] waddr,
  input wire [DATA_WIDTH-1:0] din,

  // Read port
  input wire rclk,
  input wire re,
  input wire [ADDR_WIDTH-1:0] raddr,
  output logic [DATA_WIDTH-1:0] dout
);

  // Optional vendor hints
  // (* ram_style = "block" *)
  logic [DATA_WIDTH-1:0] mem [0:(1<<ADDR_WIDTH)-1];

  // Write port
  always_ff @(posedge wclk) begin
      if (we) begin
          mem[waddr] <= din;
      end
  end

  // Read port (synchronous)
  always_ff @(posedge rclk) begin
      if (re) begin
          dout <= mem[raddr];
      end
  end
endmodule

module tagpool(
    input wire clk,
    input wire rst,
    input wire [TAG_BITS_P-1:0] release_tag_i,
    input wire release_tag_valid_i,
    output logic [TAG_BITS_P-1:0] alloc_tag_o,
    input wire alloc_tag_valid_i,
    output logic alloc_tag_ready_o
  );

  parameter NUM_TAGS_LOG2_P = 9;
  parameter TAG_BITS_P = 10;
  parameter TAG_OFFSET_P = 256;

  typedef enum {S_PRIME, S_EMPTY_IN, S_EMPTY_OUT, S_READY} state_t;
  state_t state, next_state;
  logic [NUM_TAGS_LOG2_P-1:0] prod_idx, cons_idx;
  logic empty;

  assign empty = (prod_idx == cons_idx);

  logic ren, wen;
  assign ren = (state == S_EMPTY_OUT && next_state == S_READY) || (state == S_READY && alloc_tag_valid_i && ~empty);
  assign wen = (state == S_PRIME) || release_tag_valid_i;

  bram_sdp #(
    .ADDR_WIDTH(NUM_TAGS_LOG2_P),
    .DATA_WIDTH(TAG_BITS_P)
  ) u_dpram(
    .rclk(clk),
    .wclk(clk),
    .re(ren),
    .we(wen),
    .waddr(prod_idx),
    .raddr(cons_idx),
    .din(state == S_PRIME ? (TAG_OFFSET_P + TAG_BITS_P'(prod_idx)) : release_tag_i),
    .dout(alloc_tag_o)
  );

  always_ff @(posedge clk) begin
    if (rst) state <= S_PRIME;
    else state <= next_state;
  end

  always_comb begin
    next_state = state;
    alloc_tag_ready_o = 0;
    case (state)
      S_PRIME: begin
        if (prod_idx == (1 << NUM_TAGS_LOG2_P) - 2 ) next_state = S_EMPTY_OUT;
      end
      S_EMPTY_OUT: begin
        if (~empty) begin
          next_state = S_READY;
        end
      end
      S_EMPTY_IN: begin
        alloc_tag_ready_o = 1;
        if (alloc_tag_valid_i) next_state = S_EMPTY_OUT;
      end
      S_READY: begin
        if (empty) begin
          next_state = S_EMPTY_IN;
        end else begin
          alloc_tag_ready_o = 1;
        end
      end
    endcase
  end

  always_ff @(posedge clk) begin
    if (rst) cons_idx <= 0;
    else if (ren) cons_idx <= cons_idx + 1;
  end

  always_ff @(posedge clk) begin
    if (rst) prod_idx <= 0;
    else if (wen) prod_idx <= prod_idx + 1;
  end

endmodule

module semaphores(
    input wire clk,
    input wire rst,

    input wire [$clog2(NUM_SEMS_P)-1:0] sem_inc_idx_i,
    input wire sem_inc_en_i,
    input wire [$clog2(NUM_SEMS_P)-1:0] sem_dec_idx_i,
    input wire sem_dec_en_i,
    output logic [NUM_SEMS_P-1:0] sem_zero_o
  );
  parameter NUM_SEMS_P = 16;
  parameter SEM_BITS_P = 8;

  logic [SEM_BITS_P-1:0] sems[0:NUM_SEMS_P-1];

  // Dedicated adder circuitry for each of semaphores
  always_ff @(posedge clk) begin
    for (int unsigned i = 0; i < NUM_SEMS_P; i++) begin
      if (rst) begin
        sems[i] <= 0;
      end else begin
        if (sem_inc_en_i && sem_inc_idx_i == NUM_SEMS_P'(i) &&
            sem_dec_en_i && sem_dec_idx_i == NUM_SEMS_P'(i)) begin
          // do nothing
        end else if (sem_inc_en_i && sem_inc_idx_i == NUM_SEMS_P'(i)) begin
          sems[i] <= sems[i] + 1;
        end else if (sem_dec_en_i && sem_dec_idx_i == NUM_SEMS_P'(i)) begin
          sems[i] <= sems[i] - 1;
        end
      end
    end
  end

  always_comb begin
    for (int unsigned i = 0; i < NUM_SEMS_P; i++) begin
      sem_zero_o[i] = sems[i] == 0 ? 1'b1 : 1'b0;
    end
  end

endmodule

module core (
    input  wire          clk,
    input  wire          rst,
    // BAR access
    input wire   [19:0]  bar_raddr,
    input wire   [19:0]  bar_waddr,
    output logic [63:0]  bar_rdata,
    input wire   [63:0]  bar_wdata,
    input wire           bar_wen,
    // MRd/MWr
    input wire           mem_req_mrd_ready,
    output logic         mem_req_mrd_valid,
    input wire           mem_req_mwr_ready,
    output logic         mem_req_mwr_valid,
    output logic [9:0]   mem_req_tag,
    output logic [63:0]  mem_req_data,
    output logic [63:0]  mem_req_addr,
    output logic [7:0]   mem_req_len,
    output logic [2:0]   mem_req_attr,
    output logic         mem_req_th,
    output logic [1:0]   mem_req_ph,
    // CplD
    input wire           mem_cpl_valid,
    input wire   [9:0]   mem_cpl_tag,
    input wire   [63:0]  mem_cpl_data
  );

  logic reg_ctrl_run;
  logic stall;

  logic [9:0] next_pc, pc_plus_one;
  logic [7:0] thread_idx, thread_idx_max;
  always_ff @(posedge clk) begin
    if (rst) thread_idx <= 8'h0;
    else if (tctx_state == S_TCTX0) begin
      thread_idx <= thread_idx + 8'h1;
    end else if (reg_ctrl_run & ~stall) begin
      thread_idx <= (thread_idx == thread_idx_max) ? 8'h0 : thread_idx + 8'h1;
    end
  end

  thread_ctx_t tctx_out, init_tctx;

  assign init_tctx.idx = thread_idx;
  assign init_tctx.pc = thread_idx;

  typedef enum {S_TCTX0, S_TCTX1} tctx_state_t;
  tctx_state_t tctx_state, next_tctx_state;

  always_ff @(posedge clk) begin
    if (rst) tctx_state <= S_TCTX0;
    else tctx_state <= next_tctx_state;
  end

  always_comb begin
    next_tctx_state = tctx_state;
    case (tctx_state)
      S_TCTX0: begin
        if (thread_idx == 8'hff) next_tctx_state = S_TCTX1;
      end
      S_TCTX1: begin
      end
    endcase
  end

  bram_sdp #(
    .ADDR_WIDTH(8),
    .DATA_WIDTH($bits(thread_ctx_t))
  ) u_tmem(
    .rclk(clk),
    .wclk(clk),
    .re(reg_ctrl_run & ~stall),
    .we(tctx_state == S_TCTX0 || pipe_exe_wb.valid),
    .waddr(tctx_state == S_TCTX0 ? thread_idx : pipe_exe_wb.tctx.idx),
    .raddr(thread_idx),
    .din(tctx_state == S_TCTX0 ? init_tctx : pipe_exe_wb.tctx),
    .dout(tctx_out)
  );

  logic if0_valid;
  always_ff @(posedge clk) begin
    if (reg_ctrl_run & ~stall) if0_valid <= tctx_state == S_TCTX1;
  end

  pipe_if0_if1_t pipe_if0_if1;
  pipe_if1_exe_t pipe_if1_exe;
  pipe_exe_wb_t pipe_exe_wb;

  logic [63:0] next_res;

  always_ff @(posedge clk) begin
    if (rst) begin
      pipe_if0_if1.valid <= 0;
      pipe_if1_exe.valid <= 0;
      pipe_exe_wb.valid <= 0;
    end else if (reg_ctrl_run & ~stall) begin
      pipe_if0_if1.valid <= if0_valid;
      pipe_if0_if1.tctx <= tctx_out;
      //
      pipe_if1_exe.valid <= pipe_if0_if1.valid;
      pipe_if1_exe.tctx <= pipe_if0_if1.tctx;
      pipe_if1_exe.instr <= {inst_hi, inst_lo};
      //
      pipe_exe_wb.valid <= pipe_if1_exe.valid;
      pipe_exe_wb.tctx <= pipe_if1_exe.tctx;
      pipe_exe_wb.tctx.pc <= next_pc;
      // Update result register
      for (int unsigned i = 0; i < 3; i++) begin
        pipe_exe_wb.tctx.regs[i*64+:64] <= (2'(i) == pipe_if1_exe.instr.res) ? next_res : pipe_if1_exe.tctx.regs[i*64+:64];
      end
    end
  end

  wire [63:0] inst_lo, inst_hi;

  logic imem_we;
  assign imem_we = ~reg_ctrl_run & bar_wen & (bar_waddr[19:16] == 0);

  bram_sp #(
    .ADDR_WIDTH(10),
    .DATA_WIDTH(64)
  ) imem_lo (
    .clk(clk),
    .en(~stall | imem_we),
    .we(imem_we & ~bar_waddr[3]),
    .addr(reg_ctrl_run ? tctx_out.pc : bar_waddr[13:4]),
    .din(bar_wdata),
    .dout(inst_lo)
  );

  bram_sp #(
    .ADDR_WIDTH(10),
    .DATA_WIDTH(64)
  ) imem_hi (
    .clk(clk),
    .en(~stall),
    .we(imem_we & bar_waddr[3]),
    .addr(reg_ctrl_run ? tctx_out.pc : bar_waddr[13:4]),
    .din(bar_wdata),
    .dout(inst_hi)
  );

  always_ff @(posedge clk) begin
    if (rst) reg_ctrl_run <= 0;
    else if (bar_waddr == 17'h1_0000 && bar_wen) {thread_idx_max, reg_ctrl_run} <= bar_wdata;
  end

/*
  // Handle rmem response
  logic [63:0] rdata [0:15];
  always_ff @(posedge clk) begin
    if (rmem_rsp_valid) rdata[rmem_rsp_id] <= rmem_rsp_data;
  end
*/

  logic [9:0] mem_slot_idx;
  logic [63:0] cpld_ram_rdata;
  logic [3:0] sem_inc_idx, sem_dec_idx;
  logic sem_inc_en, sem_dec_en;
  logic [15:0] sem_zero;

  semaphores u_sem(
    .clk(clk),
    .rst(rst),
    .sem_inc_idx_i(sem_inc_idx),
    .sem_inc_en_i(sem_inc_en),
    .sem_dec_idx_i(sem_dec_idx),
    .sem_dec_en_i(sem_dec_en),
    .sem_zero_o(sem_zero)
  );

  logic tag_ready;
  logic tag_alloc_en;

  tagpool #(
    .TAG_BITS_P(9)
  ) u_tags(
    .clk(clk),
    .rst(rst),
    .release_tag_i(mem_cpl_tag),
    .release_tag_valid_i(mem_cpl_valid),
    .alloc_tag_o(mem_req_tag),
    .alloc_tag_valid_i(tag_alloc_en),
    .alloc_tag_ready_o(tag_ready)
  );

  taginfo_t taginfo_in, taginfo_out;
  assign taginfo_in.sem_idx = sem_inc_idx;
  assign taginfo_in.mem_idx = mem_slot_idx;
  assign sem_dec_idx = taginfo_out.sem_idx;

  bram_sdp #(
    .ADDR_WIDTH(10),
    .DATA_WIDTH($bits(taginfo_t))
  ) u_taginfo_ram(
    .rclk(clk),
    .wclk(clk),
    .re(1'b1),
    .we(sem_inc_en),
    .waddr(mem_req_tag),
    .din(taginfo_in),
    .raddr(mem_cpl_tag),
    .dout(taginfo_out)
  );


  logic mem_cpl_valid_d;
  logic [63:0] mem_cpl_data_d;
  always_ff @(posedge clk) begin
    mem_cpl_valid_d <= mem_cpl_valid;
    mem_cpl_data_d <= mem_cpl_data;
  end

  bram_sdp #(
    .ADDR_WIDTH(10),
    .DATA_WIDTH(64)
  ) u_cpld_ram(
    .rclk(clk),
    .wclk(clk),
    .re(1'b1),
    .we(mem_cpl_valid_d),
    .waddr(taginfo_out.mem_idx),
    .din(mem_cpl_data_d),
    .raddr(inst_lo[9:0]), // Assume all instructions are OP_SLOT
    .dout(cpld_ram_rdata)
  );

  always_ff @(posedge clk) begin
    if (rst) sem_dec_en <= 0;
    else sem_dec_en <= mem_cpl_valid;
  end

  assign sem_inc_idx = pipe_if1_exe.instr.u.mem.mrd_sem;
  assign mem_slot_idx = pipe_if1_exe.instr.u.mem.mrd_mem_slot;

  logic [255:0] ops;
  assign ops = {pipe_if1_exe.instr[63:0], pipe_if1_exe.tctx.regs};
  logic [63:0] op0, op1;
  assign op0 = ops[64*pipe_if1_exe.instr.op0+:64];
  assign op1 = ops[64*pipe_if1_exe.instr.op1+:64];
  logic op0_eq_op1;
  assign op0_eq_op1 = (op0 == op1);

  assign pc_plus_one = pipe_if1_exe.tctx.pc + 1;

  assign mem_req_addr = op0;
  assign mem_req_len  = pipe_if1_exe.instr.u.mem.len;
  assign mem_req_data = op1;
  assign mem_req_attr = pipe_if1_exe.instr.u.mem.attr;
  assign mem_req_th   = pipe_if1_exe.instr.u.mem.th;
  assign mem_req_ph   = pipe_if1_exe.instr.u.mem.ph;

  always_comb begin
    tag_alloc_en = 0;
    mem_req_mrd_valid = 0;
    mem_req_mwr_valid = 0;
    sem_inc_en = 0;
    next_pc = pc_plus_one;
    next_res = 0;
    stall = 0;
    if (reg_ctrl_run & pipe_if1_exe.valid) begin
      case(pipe_if1_exe.instr.op)
        OP_NOP: begin
        end
        OP_STOP: begin
          stall = 1;
        end
        OP_MRD: begin
          if (mem_req_mrd_ready && tag_ready) begin
            mem_req_mrd_valid = 1;
            tag_alloc_en = 1;
            sem_inc_en = 1;
          end else begin
            // Stall waiting for TLP credits
            stall = 1;
          end
        end
        OP_MWR: begin
          if (mem_req_mwr_ready) begin
            mem_req_mwr_valid = 1;
          end else begin
            // Stall waiting for TLP credits
            stall = 1;
          end
        end
        OP_WAIT: begin
          if (op0 & ~sem_zero) begin
            // Skip to next thread, do not advance PC
            next_pc = pipe_if1_exe.tctx.pc;
          end
        end
        OP_JUMP: next_pc = pipe_if1_exe.instr.u.jump.target;
        OP_BEQ:  if (op0_eq_op1) next_pc = pipe_if1_exe.instr.u.jump.target;
        OP_BNE:  if (!op0_eq_op1) next_pc = pipe_if1_exe.instr.u.jump.target;
        OP_ADD:  next_res = op0 + op1;
        OP_SUB:  next_res = op0 - op1;
        OP_AND:  next_res = op0 & op1;
        OP_OR:   next_res = op0 | op1;
        OP_XOR:  next_res = op0 ^ op1;
        OP_SLOT: next_res = cpld_ram_rdata;
      endcase
    end
  end

  //
  // Event log
  //
  logic [31:0] evnt_time;
  always_ff @(posedge clk) begin
    if (rst) evnt_time <= 0;
    else evnt_time <= evnt_time + 1;
  end

  event_t evnt;
  assign evnt.timestamp = evnt_time;
  assign evnt.addr = mem_req_addr;
  assign evnt.mwr_valid = mem_req_mwr_valid & mem_req_mwr_ready;
  assign evnt.mrd_valid = mem_req_mrd_valid & mem_req_mrd_ready;
  assign evnt.mrd_tag = mem_req_tag;
  assign evnt.cpld_valid = mem_cpl_valid;
  assign evnt.cpld_tag = mem_cpl_tag;

  logic evnt_we;
  assign evnt_we = (mem_req_mrd_valid & mem_req_mrd_ready) |
                   (mem_req_mwr_valid & mem_req_mwr_ready) |
                    mem_cpl_valid;

  logic [9:0] evnt_idx;
  always_ff @(posedge clk) begin
    if (rst) evnt_idx <= 0;
    else if (evnt_we && ~evnt_idx) evnt_idx <= evnt_idx + 1;
  end

  logic [63:0] evnt_lo, evnt_hi;

  bram_sp #(
    .ADDR_WIDTH(10),
    .DATA_WIDTH(64)
  ) emem_lo (
    .clk(clk),
    .en(1'b1),
    .we(evnt_we),
    .addr(evnt_we ? evnt_idx : bar_raddr[13:4]),
    .din(evnt[63:0]),
    .dout(evnt_lo)
  );

  bram_sp #(
    .ADDR_WIDTH(10),
    .DATA_WIDTH(64)
  ) emem_hi (
    .clk(clk),
    .en(1'b1),
    .we(evnt_we),
    .addr(evnt_we ? evnt_idx : bar_raddr[13:4]),
    .din(evnt[127:64]),
    .dout(evnt_hi)
  );

  always_comb begin
    if (bar_raddr == 20'h2_0000) bar_rdata = evnt_idx;
    else bar_rdata = bar_raddr[3] ? evnt_hi : evnt_lo;
  end

  initial begin
    if ($bits(instr_t) != 128) $error("Packed struct instr_t has wrong size %d", $bits(instr_t));
  end
endmodule
