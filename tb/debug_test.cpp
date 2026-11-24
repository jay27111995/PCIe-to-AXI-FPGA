#include "Vtop.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>

Vtop* dut;
uint64_t cycle = 0;

void tick() {
    dut->clk = 0; dut->eval();
    dut->clk = 1; dut->eval();
    cycle++;
}

int main() {
    Verilated::commandArgs(0, nullptr);
    dut = new Vtop;
    
    // Reset
    dut->rst_n = 0;
    dut->rx_st_hvalid = 0;
    dut->rx_st_dvalid = 0;
    dut->rx_st_sop = 0;
    dut->tx_st_ready = 1;
    for (int i = 0; i < 10; i++) tick();
    dut->rst_n = 1;
    for (int i = 0; i < 5; i++) tick();
    
    printf("Sending MRd to 0x1000, tag=0x10, len=2\n");
    
    // Wait for ready
    while (!dut->rx_st_ready) tick();
    
    // Send MRd
    dut->rx_st_hdr[3] = (0b001 << 29) | (0b00000 << 24) | 2;  // 4DW MRd, len=2
    dut->rx_st_hdr[2] = (0x0200 << 16) | (0x10 << 8) | 0xFF;  // RID, tag, BE
    dut->rx_st_hdr[1] = 0;
    dut->rx_st_hdr[0] = 0x1000;  // address
    dut->rx_st_sop = 1;
    dut->rx_st_hvalid = 1;
    dut->rx_st_bar = 0;
    tick();
    dut->rx_st_sop = 0;
    dut->rx_st_hvalid = 0;
    
    printf("MRd sent at cycle %lu\n", cycle);
    
    // Wait for CplD with debug
    for (int i = 0; i < 100; i++) {
        tick();
        if (dut->tx_st_hvalid) {
            uint32_t dw0 = dut->tx_st_hdr[3];
            printf("Cycle %lu: TX hvalid, DW0=0x%08x, fmt=%d, type=%d\n",
                   cycle, dw0, (dw0 >> 29) & 0x7, (dw0 >> 24) & 0x1F);
            if (dut->tx_st_dvalid) {
                printf("  Data: 0x%08x_%08x\n", dut->tx_st_data[1], dut->tx_st_data[0]);
            }
        }
    }
    
    delete dut;
    return 0;
}
