#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vpcie_axi_top.h"
#include <cstdio>
#include <map>
#include <vector>

Vpcie_axi_top* dut;
VerilatedVcdC* trace;
int cycle = 0;
std::map<uint64_t, uint64_t> host_mem;

struct PendingCpl { uint8_t tag; uint64_t data; };
std::vector<PendingCpl> pending_cpls;

void tick() {
    dut->clk = 0; dut->eval(); trace->dump(cycle * 10);
    dut->clk = 1; dut->eval(); trace->dump(cycle * 10 + 5);
    cycle++;
    
    // Handle DMA TLP requests
    if (dut->tx_st_hvalid && dut->tx_st_sop) {
        uint32_t dw0 = dut->tx_st_hdr[3];
        uint8_t fmt = (dw0 >> 29) & 0x7;
        uint8_t type = (dw0 >> 24) & 0x1F;
        
        if (fmt == 0b001 && type == 0b00000) {  // MRd64
            uint8_t tag = (dut->tx_st_hdr[2] >> 8) & 0xFF;
            uint64_t addr = ((uint64_t)dut->tx_st_hdr[1] << 32) | (dut->tx_st_hdr[0] & ~3ULL);
            pending_cpls.push_back({tag, host_mem[addr]});
        }
        else if (fmt == 0b011 && type == 0b00000) {  // MWr64
            uint64_t addr = ((uint64_t)dut->tx_st_hdr[1] << 32) | (dut->tx_st_hdr[0] & ~3ULL);
            uint64_t data = ((uint64_t)dut->tx_st_data[1] << 32) | dut->tx_st_data[0];
            host_mem[addr] = data;
        }
    }
    
    // Send completions
    if (!pending_cpls.empty()) {
        auto& cpl = pending_cpls[0];
        dut->rx_st_hdr[3] = (0b010 << 29) | (0b01010 << 24) | 2;
        dut->rx_st_hdr[2] = (0x0100 << 16) | 8;
        dut->rx_st_hdr[1] = (0x0100 << 16) | (cpl.tag << 8);
        dut->rx_st_hdr[0] = 0;
        dut->rx_st_data[0] = cpl.data & 0xFFFFFFFF;
        dut->rx_st_data[1] = (cpl.data >> 32) & 0xFFFFFFFF;
        dut->rx_st_sop = 1; dut->rx_st_eop = 1;
        dut->rx_st_hvalid = 1; dut->rx_st_dvalid = 1;
        pending_cpls.erase(pending_cpls.begin());
    } else {
        for (int i = 0; i < 4; i++) dut->rx_st_hdr[i] = 0;
        for (int i = 0; i < 8; i++) dut->rx_st_data[i] = 0;
        dut->rx_st_sop = 0; dut->rx_st_eop = 0;
        dut->rx_st_hvalid = 0; dut->rx_st_dvalid = 0;
    }
}

void send_mwr(uint32_t addr, uint64_t data) {
    dut->rx_st_hdr[3] = (0b011 << 29) | (0b00000 << 24) | 2;
    dut->rx_st_hdr[2] = (0x0200 << 16) | 0xFF;
    dut->rx_st_hdr[1] = 0;
    dut->rx_st_hdr[0] = addr & ~3;
    dut->rx_st_data[0] = data & 0xFFFFFFFF;
    dut->rx_st_data[1] = (data >> 32) & 0xFFFFFFFF;
    dut->rx_st_sop = 1; dut->rx_st_eop = 1;
    dut->rx_st_hvalid = 1; dut->rx_st_dvalid = 1; dut->rx_st_bar = 0;
    tick();
}

void send_mrd(uint32_t addr, uint8_t tag) {
    dut->rx_st_hdr[3] = (0b001 << 29) | (0b00000 << 24) | 2;
    dut->rx_st_hdr[2] = (0x0200 << 16) | (tag << 8) | 0xFF;
    dut->rx_st_hdr[1] = 0;
    dut->rx_st_hdr[0] = addr & ~3;
    dut->rx_st_sop = 1; dut->rx_st_eop = 1;
    dut->rx_st_hvalid = 1; dut->rx_st_dvalid = 0; dut->rx_st_bar = 0;
    tick();
}

bool wait_cpld(uint8_t exp_tag, uint64_t exp_data, int timeout = 30) {
    for (int i = 0; i < timeout; i++) {
        tick();
        if (dut->tx_st_hvalid && dut->tx_st_sop) {
            uint32_t dw0 = dut->tx_st_hdr[3];
            if (((dw0 >> 29) & 0x7) == 0b010 && ((dw0 >> 24) & 0x1F) == 0b01010) {
                uint8_t tag = (dut->tx_st_hdr[1] >> 8) & 0xFF;
                uint64_t data = ((uint64_t)dut->tx_st_data[1] << 32) | dut->tx_st_data[0];
                return (tag == exp_tag && data == exp_data);
            }
        }
    }
    return false;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    dut = new Vpcie_axi_top;
    trace = new VerilatedVcdC;
    Verilated::traceEverOn(true);
    dut->trace(trace, 99);
    trace->open("pcie_axi_tb.vcd");

    // Init
    dut->clk = 0; dut->rst_n = 0;
    for (int i = 0; i < 4; i++) dut->rx_st_hdr[i] = 0;
    for (int i = 0; i < 8; i++) dut->rx_st_data[i] = 0;
    dut->rx_st_sop = 0; dut->rx_st_eop = 0;
    dut->rx_st_hvalid = 0; dut->rx_st_dvalid = 0; dut->rx_st_bar = 0;
    dut->tx_st_ready = 1;
    dut->tx_hcrdt_init = 0; dut->tx_hcrdt_update = 0;
    dut->tx_dcrdt_init = 0; dut->tx_dcrdt_update = 0;
    dut->link_up = 1; dut->ltssm_state = 0x11;
    
    for (int i = 0; i < 10; i++) tick();
    dut->rst_n = 1;
    for (int i = 0; i < 50; i++) tick();
    
    // Credits
    dut->tx_hcrdt_init = 0b111; dut->tx_dcrdt_init = 0b111; tick();
    for (int i = 0; i < 10; i++) {
        dut->tx_hcrdt_update = 0b111; dut->tx_hcrdt_update_cnt = 50;
        dut->tx_dcrdt_update = 0b111; dut->tx_dcrdt_update_cnt = 500;
        tick();
    }
    dut->tx_hcrdt_update = 0; dut->tx_dcrdt_update = 0;
    dut->tx_hcrdt_init = 0; dut->tx_dcrdt_init = 0;

    int pass = 0, fail = 0;
    printf("=== PCIe-to-AXI Bridge + DMA Testbench ===\n\n");

    // Test 1: Scratch register
    printf("Test 1: Scratch register write/read\n");
    send_mwr(0x0000, 0xCAFEBABE12345678);
    for (int i = 0; i < 10; i++) tick();
    send_mrd(0x0000, 0x10);
    if (wait_cpld(0x10, 0xCAFEBABE12345678)) { printf("  ✓ PASS\n"); pass++; }
    else { printf("  ✗ FAIL\n"); fail++; }

    // Test 2: RAM write/read
    printf("Test 2: RAM write/read\n");
    send_mwr(0x2000, 0x1111222233334444);
    for (int i = 0; i < 10; i++) tick();
    send_mrd(0x2000, 0x20);
    if (wait_cpld(0x20, 0x1111222233334444)) { printf("  ✓ PASS\n"); pass++; }
    else { printf("  ✗ FAIL\n"); fail++; }

    // Test 3: DMA C2H (RAM → Host)
    printf("Test 3: DMA C2H (RAM → Host)\n");
    send_mwr(0x2008, 0xAAAABBBBCCCCDDDD);  // Put data in RAM
    for (int i = 0; i < 10; i++) tick();
    send_mwr(0x1020, 0x2008);      // local_addr
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1010, 0x80000000);  // host_lo
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1018, 0);           // host_hi
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1028, 8);           // length
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1000, 0x3);         // start C2H
    for (int i = 0; i < 100; i++) tick();
    if (host_mem[0x80000000] == 0xAAAABBBBCCCCDDDD) { printf("  ✓ PASS\n"); pass++; }
    else { printf("  ✗ FAIL (got 0x%lx)\n", host_mem[0x80000000]); fail++; }

    // Test 4: DMA H2C (Host → RAM)  
    printf("Test 4: DMA H2C (Host → RAM)\n");
    host_mem[0x90000000] = 0xDEADBEEF12345678;
    send_mwr(0x1020, 0x2100);      // local_addr
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1010, 0x90000000);  // host_lo
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1018, 0);           // host_hi
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1028, 8);           // length
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1000, 0x1);         // start H2C
    for (int i = 0; i < 100; i++) tick();
    send_mrd(0x2100, 0x30);
    if (wait_cpld(0x30, 0xDEADBEEF12345678)) { printf("  ✓ PASS\n"); pass++; }
    else { printf("  ✗ FAIL\n"); fail++; }

    printf("\n=== Results: %d passed, %d failed ===\n", pass, fail);
    
    trace->close();
    delete trace;
    delete dut;
    return fail > 0 ? 1 : 0;
}
