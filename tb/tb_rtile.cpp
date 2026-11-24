#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtop.h"
#include <cstdio>
#include <map>
#include <vector>

Vtop* dut;
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
    
    // Send completions only when bridge is ready to accept
    if (!pending_cpls.empty() && dut->rx_st_ready) {
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
    } else if (dut->rx_st_ready) {
        // Only clear signals when ready (so we don't clear them while presenting a TLP)
        for (int i = 0; i < 4; i++) dut->rx_st_hdr[i] = 0;
        for (int i = 0; i < 8; i++) dut->rx_st_data[i] = 0;
        dut->rx_st_sop = 0; dut->rx_st_eop = 0;
        dut->rx_st_hvalid = 0; dut->rx_st_dvalid = 0;
    }
}

void send_mwr(uint32_t addr, uint64_t data) {
    // Wait for rx_st_ready before sending TLP
    while (!dut->rx_st_ready) tick();
    
    dut->rx_st_hdr[3] = (0b011 << 29) | (0b00000 << 24) | 2;
    dut->rx_st_hdr[2] = (0x0200 << 16) | 0xFF;
    dut->rx_st_hdr[1] = 0;
    dut->rx_st_hdr[0] = addr & ~3;  // 4-byte align (PCIe requirement)
    // For 64-bit AXI: data position depends on address bit 2
    // Bridge will use brg_awaddr[2] to select which 32-bit half
    if (addr & 4) {
        // Writing to upper half of 64-bit word
        dut->rx_st_data[0] = 0;
        dut->rx_st_data[1] = data & 0xFFFFFFFF;
    } else {
        // Writing to lower half (or full 64-bit)
        dut->rx_st_data[0] = data & 0xFFFFFFFF;
        dut->rx_st_data[1] = (data >> 32) & 0xFFFFFFFF;
    }
    dut->rx_st_sop = 1; dut->rx_st_eop = 1;
    dut->rx_st_hvalid = 1; dut->rx_st_dvalid = 1; dut->rx_st_bar = 0;
    tick();
    // Clear valid signals after presenting TLP
    dut->rx_st_sop = 0; dut->rx_st_eop = 0;
    dut->rx_st_hvalid = 0; dut->rx_st_dvalid = 0;
}

void send_mrd(uint32_t addr, uint8_t tag, uint16_t len_dw = 2) {
    // Wait for rx_st_ready before sending TLP
    while (!dut->rx_st_ready) tick();
    
    dut->rx_st_hdr[3] = (0b001 << 29) | (0b00000 << 24) | (len_dw & 0x3FF);
    dut->rx_st_hdr[2] = (0x0200 << 16) | (tag << 8) | 0xFF;
    dut->rx_st_hdr[1] = 0;
    dut->rx_st_hdr[0] = addr & ~3;
    dut->rx_st_sop = 1; dut->rx_st_eop = 1;
    dut->rx_st_hvalid = 1; dut->rx_st_dvalid = 0; dut->rx_st_bar = 0;
    tick();
    // Clear valid signals after presenting TLP
    dut->rx_st_sop = 0; dut->rx_st_eop = 0;
    dut->rx_st_hvalid = 0; dut->rx_st_dvalid = 0;
}

bool wait_cpld(uint8_t exp_tag, uint64_t exp_data, int timeout = 30, bool debug = false) {
    for (int i = 0; i < timeout; i++) {
        tick();
        if (dut->tx_st_hvalid && dut->tx_st_sop) {
            uint32_t dw0 = dut->tx_st_hdr[3];
            uint8_t fmt = (dw0 >> 29) & 0x7;
            uint8_t type = (dw0 >> 24) & 0x1F;
            if (fmt == 0b010 && type == 0b01010) {
                uint8_t tag = (dut->tx_st_hdr[1] >> 8) & 0xFF;
                uint64_t data = ((uint64_t)dut->tx_st_data[1] << 32) | dut->tx_st_data[0];
                if (debug) {
                    printf("    CplD: tag=0x%02x (exp 0x%02x), data=0x%016lx (exp 0x%016lx)\n",
                           tag, exp_tag, data, exp_data);
                }
                return (tag == exp_tag && data == exp_data);
            }
        }
    }
    if (debug) printf("    Timeout waiting for CplD\n");
    return false;
}

// Version that just checks we got a completion (any data)
bool wait_cpld_any(uint8_t exp_tag, uint64_t *out_data = nullptr, int timeout = 30) {
    for (int i = 0; i < timeout; i++) {
        tick();
        if (dut->tx_st_hvalid && dut->tx_st_sop) {
            uint32_t dw0 = dut->tx_st_hdr[3];
            uint8_t fmt = (dw0 >> 29) & 0x7;
            uint8_t type = (dw0 >> 24) & 0x1F;
            if (fmt == 0b010 && type == 0b01010) {
                uint8_t tag = (dut->tx_st_hdr[1] >> 8) & 0xFF;
                uint64_t data = ((uint64_t)dut->tx_st_data[1] << 32) | dut->tx_st_data[0];
                printf("    CplD: tag=0x%02x (exp 0x%02x), data=0x%016lx\n", tag, exp_tag, data);
                if (out_data) *out_data = data;
                return (tag == exp_tag);
            }
        }
    }
    printf("    Timeout waiting for CplD (tag=0x%02x)\n", exp_tag);
    return false;
}

// Wait for multi-DW CplD and return all data
bool wait_cpld_multi(uint8_t exp_tag, uint64_t *out_data, int num_qw, int timeout = 50) {
    for (int i = 0; i < timeout; i++) {
        tick();
        if (dut->tx_st_hvalid && dut->tx_st_sop) {
            uint32_t dw0 = dut->tx_st_hdr[3];
            uint8_t fmt = (dw0 >> 29) & 0x7;
            uint8_t type = (dw0 >> 24) & 0x1F;
            uint16_t len = dw0 & 0x3FF;
            if (fmt == 0b010 && type == 0b01010) {
                uint8_t tag = (dut->tx_st_hdr[1] >> 8) & 0xFF;
                printf("    CplD: tag=0x%02x (exp 0x%02x), len=%d DW\n", tag, exp_tag, len);
                // Extract data from tx_st_data (256 bits = 8 DW = 4 QW)
                for (int q = 0; q < num_qw && q < 4; q++) {
                    out_data[q] = ((uint64_t)dut->tx_st_data[q*2+1] << 32) | dut->tx_st_data[q*2];
                    printf("      QW%d: 0x%016lx\n", q, out_data[q]);
                }
                return (tag == exp_tag && len >= num_qw * 2);
            }
        }
    }
    printf("    Timeout waiting for multi-DW CplD (tag=0x%02x)\n", exp_tag);
    return false;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    dut = new Vtop;
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
    printf("=== PCIe-to-AXI Bridge + DMA Testbench ===\n");
    printf("Address map: 0x0xxx=DMA, 0x1xxx=RAM\n\n");

    //=========================================================================
    // New address map:
    //   0x0000-0x0FFF: DMA registers
    //   0x1000-0x1FFF: RAM (4KB)
    //=========================================================================

    // Test 1: RAM write/read (basic PCIe connectivity test)
    printf("Test 1: RAM write/read\n");
    send_mwr(0x1000, 0xCAFEBABE12345678);
    for (int i = 0; i < 10; i++) tick();
    send_mrd(0x1000, 0x10);
    if (wait_cpld(0x10, 0xCAFEBABE12345678)) { printf("  PASS\n"); pass++; }
    else { printf("  FAIL\n"); fail++; }

    // Test 2: RAM multiple addresses
    printf("Test 2: RAM multiple addresses\n");
    send_mwr(0x1008, 0x1111222233334444);
    for (int i = 0; i < 10; i++) tick();
    send_mrd(0x1008, 0x20);
    if (wait_cpld(0x20, 0x1111222233334444, 30, true)) { printf("  PASS\n"); pass++; }
    else { printf("  FAIL\n"); fail++; }

    // Test 3: Debug registers (sniffer at 0x2xxx)
    printf("Test 3: Debug register read (sniffer)\n");
    // Test multiple addresses to verify address decode
    struct { uint32_t addr; const char* name; } dbg_tests[] = {
        {0x2000, "status"},
        {0x2010, "write_ptr"},
        {0x2018, "rx_count"},
    };
    bool dbg_ok = true;
    for (auto& t : dbg_tests) {
        send_mrd(t.addr, 0x25);
        uint64_t dbg_data;
        bool got_cpl = wait_cpld_any(0x25, &dbg_data, 50);
        if (got_cpl) {
            printf("    %s (0x%04x): 0x%016lx\n", t.name, t.addr, dbg_data);
        } else {
            printf("    %s (0x%04x): TIMEOUT\n", t.name, t.addr);
            dbg_ok = false;
        }
    }
    if (dbg_ok) { printf("  PASS (debug reads completed)\n"); pass++; }
    else { printf("  FAIL (debug read timeout)\n"); fail++; }

    // Test 4: DMA C2H (RAM -> Host)
    // New register map: 0x10=host_addr(64-bit), 0x18=local_addr, 0x20=length
    printf("Test 4: DMA C2H (RAM -> Host)\n");
    send_mwr(0x1100, 0xAAAABBBBCCCCDDDD);  // Put data in RAM at 0x1100
    for (int i = 0; i < 10; i++) tick();
    send_mwr(0x0010, 0x80000000);  // host_addr (full 64-bit, single write)
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x0018, 0x1100);      // local_addr
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x0020, 8);           // length
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x0000, 0x3);         // start C2H
    for (int i = 0; i < 100; i++) tick();
    if (host_mem[0x80000000] == 0xAAAABBBBCCCCDDDD) { printf("  [OK] PASS\n"); pass++; }
    else { printf("  [X] FAIL (got 0x%lx)\n", host_mem[0x80000000]); fail++; }

    // Test 5: DMA H2C (Host -> RAM)  
    printf("Test 5: DMA H2C (Host -> RAM)\n");
    host_mem[0x90000000] = 0xDEADBEEF12345678;
    send_mwr(0x0010, 0x90000000);  // host_addr (full 64-bit, single write)
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x0018, 0x1200);      // local_addr
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x0020, 8);           // length
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x0000, 0x1);         // start H2C
    for (int i = 0; i < 100; i++) tick();
    send_mrd(0x1200, 0x30);        // Read from RAM at 0x1200
    if (wait_cpld(0x30, 0xDEADBEEF12345678)) { printf("  [OK] PASS\n"); pass++; }
    else { printf("  [X] FAIL\n"); fail++; }

    // Test 6: Multi-DW BAR read (4 DW = 16 bytes = 2 AXI beats)
    printf("Test 6: Multi-DW BAR read (4 DW)\n");
    // Write pattern to RAM at consecutive addresses
    send_mwr(0x1400, 0xAAAABBBBCCCCDDDD);
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1408, 0x1111222233334444);
    for (int i = 0; i < 10; i++) tick();
    // Request 4 DW read (16 bytes)
    send_mrd(0x1400, 0x40, 4);  // addr, tag, len=4 DW
    uint64_t multi_data[2];
    if (wait_cpld_multi(0x40, multi_data, 2)) {
        bool ok = (multi_data[0] == 0xAAAABBBBCCCCDDDD) && 
                  (multi_data[1] == 0x1111222233334444);
        if (ok) { printf("  [OK] PASS\n"); pass++; }
        else { printf("  [X] FAIL (data mismatch)\n"); fail++; }
    } else { 
        printf("  [X] FAIL (no CplD)\n"); fail++; 
    }

    // Test 7: Multi-CplD test (64 bytes = 16 DW = 2 CplDs)
    printf("Test 7: Multi-CplD BAR read (64 bytes)\n");
    // Write 64 bytes of test pattern to RAM at 0x1500
    send_mwr(0x1500, 0x0001000200030004);  // QW0
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1508, 0x0005000600070008);  // QW1
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1510, 0x0009000A000B000C);  // QW2
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1518, 0x000D000E000F0010);  // QW3
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1520, 0x0011001200130014);  // QW4
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1528, 0x0015001600170018);  // QW5
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1530, 0x0019001A001B001C);  // QW6
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x1538, 0x001D001E001F0020);  // QW7
    for (int i = 0; i < 10; i++) tick();
    
    // Request 16 DW (64 bytes) - should get 2 CplDs of 8 DW each
    send_mrd(0x1500, 0x50, 16);
    uint64_t cpl1[4], cpl2[4];
    bool got_cpl1 = wait_cpld_multi(0x50, cpl1, 4);
    bool got_cpl2 = wait_cpld_multi(0x50, cpl2, 4);
    if (got_cpl1 && got_cpl2) {
        bool ok = (cpl1[0] == 0x0001000200030004) && (cpl1[3] == 0x000D000E000F0010) &&
                  (cpl2[0] == 0x0011001200130014) && (cpl2[3] == 0x001D001E001F0020);
        if (ok) { printf("  [OK] PASS (2 CplDs received)\n"); pass++; }
        else { 
            printf("  [X] FAIL (data mismatch)\n"); 
            printf("    Expected cpl1[0]=0x0001000200030004, got 0x%016lx\n", cpl1[0]);
            printf("    Expected cpl2[0]=0x0011001200130014, got 0x%016lx\n", cpl2[0]);
            fail++; 
        }
    } else {
        printf("  [X] FAIL (didn't receive 2 CplDs)\n"); fail++;
    }

    // Test 8: 256-byte read (64 DW = 8 CplDs)
    printf("Test 8: Large multi-CplD BAR read (256 bytes)\n");
    // Write pattern: address offset as data at each 8-byte location
    for (int i = 0; i < 32; i++) {
        send_mwr(0x1600 + i*8, 0x1600 + i*8);  // Store address as data
        for (int j = 0; j < 3; j++) tick();
    }
    for (int i = 0; i < 10; i++) tick();
    
    // Request 64 DW (256 bytes) - should get 8 CplDs of 8 DW (32 bytes) each
    send_mrd(0x1600, 0x60, 64);
    int cpld_count = 0;
    bool data_ok = true;
    for (int cpl = 0; cpl < 8 && data_ok; cpl++) {
        uint64_t data[4];
        if (wait_cpld_multi(0x60, data, 4, 100)) {
            cpld_count++;
            // Check first QW of each CplD
            uint64_t expected = 0x1600 + cpl * 32;  // Each CplD covers 32 bytes
            if (data[0] != expected) {
                printf("    CplD %d: expected first QW=0x%lx, got 0x%016lx\n", cpl, expected, data[0]);
                data_ok = false;
            }
        } else {
            printf("    Timeout waiting for CplD %d\n", cpl);
            data_ok = false;
        }
    }
    if (cpld_count == 8 && data_ok) {
        printf("  [OK] PASS (%d CplDs received)\n", cpld_count);
        pass++;
    } else {
        printf("  [X] FAIL (got %d CplDs, data_ok=%d)\n", cpld_count, data_ok);
        fail++;
    }

    // Test 9: Odd-length read (10 DW = 40 bytes = 1 full CplD + 1 partial)
    printf("Test 9: Odd-length BAR read (10 DW = 40 bytes)\n");
    // Reuse data from 0x1600 area
    send_mrd(0x1600, 0x70, 10);  // 10 DW = 40 bytes
    uint64_t odd1[4], odd2[4];
    bool got_odd1 = wait_cpld_multi(0x70, odd1, 4);  // First CplD: 8 DW
    bool got_odd2 = wait_cpld_multi(0x70, odd2, 1);  // Second CplD: 2 DW
    if (got_odd1 && got_odd2) {
        // First CplD should have 8 DW, second should have 2 DW
        bool ok = (odd1[0] == 0x1600) && (odd2[0] == 0x1620);
        if (ok) { printf("  [OK] PASS (8 DW + 2 DW CplDs)\n"); pass++; }
        else { 
            printf("  [X] FAIL (data mismatch: odd1[0]=0x%lx, odd2[0]=0x%lx)\n", odd1[0], odd2[0]);
            fail++;
        }
    } else {
        printf("  [X] FAIL (didn't get 2 CplDs: got1=%d got2=%d)\n", got_odd1, got_odd2);
        fail++;
    }

    // Test 10: MSI-X interrupt
    // When DMA completes with irq_en=1, should see MWr to MSI-X address (0xFEE00000)
    printf("Test 10: DMA with MSI-X interrupt\n");
    host_mem.erase(0xFEE00000);  // Clear any previous MSI-X
    host_mem[0xA0000000] = 0x1234567890ABCDEF;
    send_mwr(0x0010, 0xA0000000);  // host_addr
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x0018, 0x1300);      // local_addr
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x0020, 8);           // length
    for (int i = 0; i < 5; i++) tick();
    send_mwr(0x0000, 0x5);         // start H2C + irq_en (bit 0 + bit 2)
    for (int i = 0; i < 150; i++) tick();
    // Check if MSI-X was received (MWr to 0xFEE00000)
    if (host_mem.count(0xFEE00000)) { 
        printf("  [OK] PASS (MSI-X data=0x%lx)\n", host_mem[0xFEE00000]); 
        pass++; 
    } else { 
        printf("  [X] FAIL (no MSI-X received)\n"); 
        fail++; 
    }

    // Test 11: Sniffer control write (clear/start/stop)
    printf("Test 11: Sniffer control write\n");
    // Write to PCIe sniffer control register at 0x2004
    // bit 0 = start, bit 1 = stop, bit 2 = clear
    send_mwr(0x2004, 0x4);  // Clear
    for (int i = 0; i < 10; i++) tick();
    send_mwr(0x2004, 0x1);  // Start
    for (int i = 0; i < 10; i++) tick();
    // Now read status at 0x2000 - should show running=1
    send_mrd(0x2000, 0x80);
    uint64_t status_data;
    if (wait_cpld_any(0x80, &status_data)) {
        uint32_t status = (uint32_t)status_data;
        bool running = (status >> 16) & 1;
        printf("    Status: 0x%08x, running=%d\n", status, running);
        if (running) {
            printf("  [OK] PASS\n");
            pass++;
        } else {
            printf("  [X] FAIL (sniffer not running after start)\n");
            fail++;
        }
    } else {
        printf("  [X] FAIL (no status response)\n");
        fail++;
    }
    // Stop the sniffer
    send_mwr(0x2004, 0x2);  // Stop
    for (int i = 0; i < 10; i++) tick();

    printf("\n=== Results: %d passed, %d failed ===\n", pass, fail);
    
    trace->close();
    delete trace;
    delete dut;
    return fail > 0 ? 1 : 0;
}
