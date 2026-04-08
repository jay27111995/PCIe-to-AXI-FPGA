#include "Vdma_core.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include <cstdint>
#include <cstdio>
#include <memory>
#include <queue>
#include <map>

std::unique_ptr<Vdma_core> top;
std::unique_ptr<VerilatedFstC> tfp;
uint64_t tick = 0;

// Simple sparse memory
std::map<uint64_t, uint64_t> mem;

void clk_tick() {
  top->clk = 0;
  top->eval();
  if (tfp) tfp->dump(tick++);
  top->clk = 1;
  top->eval();
  if (tfp) tfp->dump(tick++);
}

void reset() {
  top->rst = 1;
  for (int i = 0; i < 8; i++) clk_tick();
  top->rst = 0;
  clk_tick();
}

void bar_write(uint32_t addr, uint64_t data) {
  top->bar_waddr = addr >> 3;
  top->bar_wdata = data;
  top->bar_wen = 1;
  clk_tick();
  top->bar_wen = 0;
  printf("BAR Write [0x%04x] = 0x%016lx\n", addr, data);
}

uint64_t bar_read(uint32_t addr) {
  top->bar_raddr = addr >> 3;
  clk_tick();
  uint64_t data = top->bar_rdata;
  printf("BAR Read  [0x%04x] = 0x%016lx\n", addr, data);
  return data;
}

void handle_axi() {
  static std::queue<std::pair<uint64_t, uint8_t>> rd_pending;  // addr, id
  static std::queue<std::pair<uint64_t, uint8_t>> wr_pending;  // addr, id

  // Read request
  top->rburst_req_ready = 1;
  if (top->rburst_req_valid) {
    printf("  AXI RD REQ: addr=0x%016lx id=%d\n",
           (uint64_t)top->rburst_req_addr, top->rburst_req_id);
    rd_pending.push({top->rburst_req_addr, top->rburst_req_id});
  }

  // Read response (1 cycle delay)
  top->rburst_rsp_valid = 0;
  if (!rd_pending.empty()) {
    auto [addr, id] = rd_pending.front();
    rd_pending.pop();
    top->rburst_rsp_valid = 1;
    top->rburst_rsp_id = id;
    top->rburst_rsp_data = mem[addr];
    printf("  AXI RD RSP: addr=0x%016lx data=0x%016lx\n", addr, mem[addr]);
  }

  // Write request
  top->wburst_req_ready = 1;
  if (top->wburst_req_valid) {
    printf("  AXI WR REQ: addr=0x%016lx data=0x%016lx id=%d\n",
           (uint64_t)top->wburst_req_addr, (uint64_t)top->wburst_req_data,
           top->wburst_req_id);
    mem[top->wburst_req_addr] = top->wburst_req_data;
    wr_pending.push({top->wburst_req_addr, top->wburst_req_id});
  }

  // Write response (1 cycle delay)
  top->wburst_rsp_valid = 0;
  if (!wr_pending.empty()) {
    auto [addr, id] = wr_pending.front();
    wr_pending.pop();
    top->wburst_rsp_valid = 1;
    top->wburst_rsp_id = id;
    printf("  AXI WR RSP: id=%d\n", id);
  }
}

void run_cycles(int n) {
  for (int i = 0; i < n; i++) {
    handle_axi();
    clk_tick();
  }
}

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);

  top = std::make_unique<Vdma_core>();
  tfp = std::make_unique<VerilatedFstC>();
  top->trace(tfp.get(), 99);
  tfp->open("dma_core.fst");

  // Initialize
  top->bar_wen = 0;
  top->rburst_req_ready = 1;
  top->rburst_rsp_valid = 0;
  top->wburst_req_ready = 1;
  top->wburst_rsp_valid = 0;

  reset();

  // Setup test data in "host memory"
  uint64_t src_addr = 0x1000;
  uint64_t dst_addr = 0x2000;
  uint64_t len = 4;

  printf("\n=== Initialize source memory ===\n");
  for (uint64_t i = 0; i < len; i++) {
    mem[src_addr + i * 8] = 0xDEADBEEF00000000 | i;
    printf("mem[0x%lx] = 0x%016lx\n", src_addr + i * 8, mem[src_addr + i * 8]);
  }

  printf("\n=== Configure DMA ===\n");
  bar_write(0x00, 1);             // RESET
  bar_write(0x08, src_addr);      // SRC_ADDR
  bar_write(0x10, dst_addr);      // DST_ADDR
  bar_write(0x18, len);           // LEN
  bar_write(0x20, 1);             // GO

  printf("\n=== Run DMA ===\n");
  // Run until done
  for (int i = 0; i < 100; i++) {
    handle_axi();
    clk_tick();
    top->bar_raddr = 0x20 >> 3;
    if ((top->bar_rdata & 2) == 0 && i > 5) {
      printf("DMA complete after %d cycles\n", i);
      break;
    }
  }

  printf("\n=== Verify destination memory ===\n");
  bool pass = true;
  for (uint64_t i = 0; i < len; i++) {
    uint64_t expected = 0xDEADBEEF00000000 | i;
    uint64_t actual = mem[dst_addr + i * 8];
    printf("mem[0x%lx] = 0x%016lx %s\n", dst_addr + i * 8, actual,
           actual == expected ? "OK" : "FAIL");
    if (actual != expected) pass = false;
  }

  printf("\n=== TEST %s ===\n", pass ? "PASSED" : "FAILED");

  tfp->close();
  return pass ? 0 : 1;
}
