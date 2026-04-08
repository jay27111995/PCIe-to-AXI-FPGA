`timescale 1ns/1ps

module tb_dma_core;
  logic clk = 0, rst_n = 0;
  logic [19:0] bar_raddr, bar_waddr;
  logic [63:0] bar_rdata, bar_wdata;
  logic bar_wen;

  // AXI burst interface
  logic rburst_req_ready, rburst_req_valid;
  logic [3:0] rburst_req_id;
  logic [63:0] rburst_req_addr;
  logic [7:0] rburst_req_len;
  logic rburst_rsp_valid;
  logic [3:0] rburst_rsp_id;
  logic [63:0] rburst_rsp_data;

  logic wburst_req_ready, wburst_req_valid;
  logic [3:0] wburst_req_id;
  logic [63:0] wburst_req_addr, wburst_req_data;
  logic [7:0] wburst_req_len;
  logic wburst_rsp_valid;
  logic [3:0] wburst_rsp_id;

  // Simulated host memory
  logic [63:0] host_mem [0:15];

  dma_core dut (.*);

  always #5 clk = ~clk;

  // Simulate AXI read: when rburst_req_valid, return data after 2 cycles
  int read_delay;
  logic [63:0] pending_raddr;
  always_ff @(posedge clk) begin
    rburst_rsp_valid <= 0;
    if (rburst_req_valid && rburst_req_ready) begin
      pending_raddr <= rburst_req_addr;
      read_delay <= 2;
    end else if (read_delay > 0) begin
      read_delay <= read_delay - 1;
      if (read_delay == 1) begin
        rburst_rsp_valid <= 1;
        rburst_rsp_data <= host_mem[pending_raddr[6:3]];
        rburst_rsp_id <= 0;
      end
    end
  end

  // Simulate AXI write: when wburst_req_valid, accept and store
  always_ff @(posedge clk) begin
    wburst_rsp_valid <= 0;
    if (wburst_req_valid && wburst_req_ready) begin
      host_mem[wburst_req_addr[6:3]] <= wburst_req_data;
      wburst_rsp_valid <= 1;
      wburst_rsp_id <= 0;
      $display("  WRITE: addr=%h data=%h", wburst_req_addr, wburst_req_data);
    end
  end

  task write_reg(input [19:0] addr, input [63:0] data);
    @(posedge clk);
    bar_waddr <= addr; bar_wdata <= data; bar_wen <= 1;
    @(posedge clk);
    bar_wen <= 0;
  endtask

  task read_reg(input [19:0] addr, output [63:0] data);
    @(posedge clk);
    bar_raddr <= addr;
    @(posedge clk);
    @(posedge clk);
    data = bar_rdata;
  endtask

  logic [63:0] ctrl;
  int pass;

  initial begin
    // Init
    bar_wen = 0; bar_waddr = 0; bar_wdata = 0; bar_raddr = 0;
    rburst_req_ready = 1; wburst_req_ready = 1;
    rburst_rsp_valid = 0; wburst_rsp_valid = 0;
    read_delay = 0;

    // Init host memory: src at 0x00, dst at 0x40
    for (int i = 0; i < 8; i++) host_mem[i] = 64'hCAFEF00D00000000 + i;
    for (int i = 8; i < 16; i++) host_mem[i] = 0;

    // Reset
    #20 rst_n = 1;
    #20;

    $display("=== DMA Core Testbench ===");
    $display("Source data (host_mem[0:7]):");
    for (int i = 0; i < 8; i++) $display("  [%0d] = %h", i, host_mem[i]);

    // Configure DMA: src=0x00, dst=0x40, len=4
    write_reg(20'h08, 64'h0000_0000_0000_0000);  // SRC_ADDR
    write_reg(20'h10, 64'h0000_0000_0000_0040);  // DST_ADDR
    write_reg(20'h18, 64'h4);                     // LEN = 4 words

    $display("\nStarting DMA: src=0x00 dst=0x40 len=4");
    write_reg(20'h20, 64'h1);  // GO

    // Wait for completion
    repeat (100) @(posedge clk);

    // Check CTRL
    read_reg(20'h20, ctrl);
    $display("\nCTRL after wait: %h (busy=%b)", ctrl, ctrl[1]);

    // Verify destination
    $display("\nDestination data (host_mem[8:11]):");
    pass = 1;
    for (int i = 0; i < 4; i++) begin
      $display("  [%0d] = %h (expected %h)", i+8, host_mem[i+8], host_mem[i]);
      if (host_mem[i+8] != host_mem[i]) pass = 0;
    end

    $display("\n=== TEST %s ===", pass ? "PASSED" : "FAILED");
    $finish;
  end
endmodule
