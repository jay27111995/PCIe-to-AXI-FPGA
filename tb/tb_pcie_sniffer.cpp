//-----------------------------------------------------------------------------
// tb_pcie_sniffer.cpp - Testbench for pcie_sniffer module
//
// Tests the PCIe TLP sniffer debug functionality:
//   1. RX TLP capture
//   2. TX TLP capture
//   3. Cycle counting
//   4. Ready signal counting
//   5. Clear control
//-----------------------------------------------------------------------------
#include <verilated.h>
#include "Vpcie_sniffer.h"
#include <cstdio>
#include <cstdint>

Vpcie_sniffer* dut;
int cycle = 0;

void tick() {
    dut->clk = 0;
    dut->eval();
    
    dut->clk = 1;
    dut->eval();
    
    cycle++;
}

void reset() {
    dut->rst_n = 0;
    dut->rx_st_hdr[0] = 0;
    dut->rx_st_hdr[1] = 0;
    dut->rx_st_hdr[2] = 0;
    dut->rx_st_hdr[3] = 0;
    dut->rx_st_data[0] = 0;
    dut->rx_st_sop = 0;
    dut->rx_st_hvalid = 0;
    dut->rx_st_ready = 1;
    dut->tx_st_hdr[0] = 0;
    dut->tx_st_hdr[1] = 0;
    dut->tx_st_hdr[2] = 0;
    dut->tx_st_hdr[3] = 0;
    dut->tx_st_data[0] = 0;
    dut->tx_st_sop = 0;
    dut->tx_st_hvalid = 0;
    dut->tx_st_ready = 1;
    dut->tx_state = 0;
    dut->dbg_addr = 0;
    
    for (int i = 0; i < 5; i++) tick();
    dut->rst_n = 1;
    for (int i = 0; i < 3; i++) tick();
}

// Read a debug register
uint32_t read_dbg(uint8_t addr) {
    dut->dbg_addr = addr;
    dut->eval();
    return dut->dbg_rdata;
}

// Simulate an RX TLP
void send_rx_tlp(uint32_t hdr0, uint32_t hdr1, uint32_t hdr2, uint32_t hdr3, 
                 uint32_t data_lo, uint32_t data_hi) {
    dut->rx_st_hdr[0] = hdr0;
    dut->rx_st_hdr[1] = hdr1;
    dut->rx_st_hdr[2] = hdr2;
    dut->rx_st_hdr[3] = hdr3;
    dut->rx_st_data[0] = data_lo;
    dut->rx_st_data[1] = data_hi;
    for (int i = 2; i < 8; i++) dut->rx_st_data[i] = 0;
    dut->rx_st_sop = 1;
    dut->rx_st_hvalid = 1;
    tick();
    dut->rx_st_hvalid = 0;
    dut->rx_st_sop = 0;
}

// Simulate a TX TLP
void send_tx_tlp(uint32_t hdr0, uint32_t hdr1, uint32_t hdr2, uint32_t hdr3,
                 uint32_t data_lo, uint32_t data_hi) {
    dut->tx_st_hdr[0] = hdr0;
    dut->tx_st_hdr[1] = hdr1;
    dut->tx_st_hdr[2] = hdr2;
    dut->tx_st_hdr[3] = hdr3;
    dut->tx_st_data[0] = data_lo;
    dut->tx_st_data[1] = data_hi;
    for (int i = 2; i < 8; i++) dut->tx_st_data[i] = 0;
    dut->tx_st_sop = 1;
    dut->tx_st_hvalid = 1;
    tick();
    dut->tx_st_hvalid = 0;
    dut->tx_st_sop = 0;
}

//=============================================================================
// Test Cases
//=============================================================================

bool test_rx_capture() {
    printf("Test 1: RX TLP Capture\n");
    
    // Send an MRd TLP: Fmt=000, Type=00000, Length=2
    uint32_t dw0 = (0b000 << 29) | (0b00000 << 24) | 2;
    uint32_t dw1 = (0x0100 << 16) | (0x42 << 8) | 0xFF;  // RID=0x100, Tag=0x42
    uint32_t dw2 = 0x12340000;  // Address
    uint32_t dw3 = 0;
    uint32_t data_lo = 0xCAFEBABE;
    uint32_t data_hi = 0xDEADBEEF;
    
    send_rx_tlp(dw2, dw1, dw0, dw3, data_lo, data_hi);
    tick(); tick();
    
    // Check status register
    uint32_t status = read_dbg(0x00);
    if (!(status & 1)) {
        printf("  [X] rx_seen not set\n");
        return false;
    }
    
    // Check rx_count
    uint32_t rx_count = read_dbg(0x04);
    if (rx_count != 1) {
        printf("  [X] rx_count wrong: %d\n", rx_count);
        return false;
    }
    
    // Check last_rx_hdr
    uint32_t hdr0 = read_dbg(0x10);
    uint32_t hdr1 = read_dbg(0x14);
    uint32_t hdr2 = read_dbg(0x18);
    
    if (hdr0 != dw2 || hdr1 != dw1 || hdr2 != dw0) {
        printf("  [X] last_rx_hdr mismatch\n");
        printf("      Expected: 0x%08x 0x%08x 0x%08x\n", dw2, dw1, dw0);
        printf("      Got:      0x%08x 0x%08x 0x%08x\n", hdr0, hdr1, hdr2);
        return false;
    }
    
    // Check last_rx_data
    uint32_t captured_lo = read_dbg(0x20);
    uint32_t captured_hi = read_dbg(0x24);
    
    if (captured_lo != data_lo || captured_hi != data_hi) {
        printf("  [X] last_rx_data mismatch\n");
        printf("      Expected: 0x%08x 0x%08x\n", data_lo, data_hi);
        printf("      Got:      0x%08x 0x%08x\n", captured_lo, captured_hi);
        return false;
    }
    
    printf("  [OK] RX TLP captured correctly\n");
    return true;
}

bool test_tx_capture() {
    printf("Test 2: TX TLP Capture\n");
    
    // Send a CplD TLP: Fmt=010, Type=01010, Length=2
    uint32_t dw0 = (0b010 << 29) | (0b01010 << 24) | 2;
    uint32_t dw1 = (0xb400 << 16) | 8;  // Completer ID, byte count
    uint32_t dw2 = (0x0100 << 16) | (0x42 << 8);  // RID, Tag
    uint32_t dw3 = 0;
    uint32_t data_lo = 0x90ABCDEF;
    uint32_t data_hi = 0x12345678;
    
    send_tx_tlp(dw2, dw1, dw0, dw3, data_lo, data_hi);
    tick(); tick();
    
    // Check status register
    uint32_t status = read_dbg(0x00);
    if (!(status & 2)) {
        printf("  [X] tx_seen not set\n");
        return false;
    }
    
    // Check tx_count
    uint32_t tx_count = read_dbg(0x08);
    if (tx_count != 1) {
        printf("  [X] tx_count wrong: %d\n", tx_count);
        return false;
    }
    
    // Check last_tx_hdr
    uint32_t hdr0 = read_dbg(0x28);
    uint32_t hdr1 = read_dbg(0x2C);
    uint32_t hdr2 = read_dbg(0x30);
    
    if (hdr0 != dw2 || hdr1 != dw1 || hdr2 != dw0) {
        printf("  [X] last_tx_hdr mismatch\n");
        return false;
    }
    
    // Check last_tx_data
    uint32_t captured_lo = read_dbg(0x38);
    uint32_t captured_hi = read_dbg(0x3C);
    
    if (captured_lo != data_lo || captured_hi != data_hi) {
        printf("  [X] last_tx_data mismatch\n");
        printf("      Expected: 0x%08x 0x%08x\n", data_lo, data_hi);
        printf("      Got:      0x%08x 0x%08x\n", captured_lo, captured_hi);
        return false;
    }
    
    printf("  [OK] TX TLP captured correctly\n");
    return true;
}

bool test_cycle_counter() {
    printf("Test 3: Cycle Counter\n");
    
    uint32_t before_lo = read_dbg(0x40);
    
    // Run some cycles
    for (int i = 0; i < 100; i++) tick();
    
    uint32_t after_lo = read_dbg(0x40);
    uint32_t diff = after_lo - before_lo;
    
    if (diff >= 95 && diff <= 105) {  // Allow some tolerance
        printf("  [OK] Cycle counter working (diff=%d)\n", diff);
        return true;
    } else {
        printf("  [X] Cycle counter wrong: diff=%d (expected ~100)\n", diff);
        return false;
    }
}

bool test_ready_counters() {
    printf("Test 4: Ready Signal Counters\n");
    
    // Reset and check initial
    reset();
    
    // Run with rx_st_ready=1 for some cycles
    dut->rx_st_ready = 1;
    dut->tx_st_ready = 0;
    for (int i = 0; i < 50; i++) tick();
    
    // Now rx_st_ready=0, tx_st_ready=1
    dut->rx_st_ready = 0;
    dut->tx_st_ready = 1;
    for (int i = 0; i < 30; i++) tick();
    
    uint32_t rx_ready_cnt = read_dbg(0x48);
    uint32_t tx_ready_cnt = read_dbg(0x4C);
    
    // rx_ready should be ~50+3 (reset cycles), tx_ready ~30
    if (rx_ready_cnt >= 45 && rx_ready_cnt <= 60 &&
        tx_ready_cnt >= 25 && tx_ready_cnt <= 35) {
        printf("  [OK] Ready counters: rx=%d tx=%d\n", rx_ready_cnt, tx_ready_cnt);
        return true;
    } else {
        printf("  [X] Ready counters wrong: rx=%d tx=%d\n", rx_ready_cnt, tx_ready_cnt);
        return false;
    }
}

bool test_tx_state() {
    printf("Test 5: TX State Capture\n");
    
    // Set tx_state to different values and check status register
    dut->tx_state = 5;
    tick();
    
    uint32_t status = read_dbg(0x00);
    uint8_t captured_state = (status >> 4) & 0xF;
    
    if (captured_state == 5) {
        printf("  [OK] TX state captured: %d\n", captured_state);
        return true;
    } else {
        printf("  [X] TX state wrong: got %d, expected 5\n", captured_state);
        return false;
    }
}

bool test_default_value() {
    printf("Test 6: Default Value for Unknown Address\n");
    
    // Read from an address outside the defined range
    uint32_t value = read_dbg(0x80);  // Address 0x80 should hit default
    
    if (value == 0xDEADBEEF) {
        printf("  [OK] Default value returned: 0x%08x\n", value);
        return true;
    } else {
        printf("  [X] Wrong default value: 0x%08x (expected 0xDEADBEEF)\n", value);
        return false;
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    
    dut = new Vpcie_sniffer;
    
    printf("=== PCIe Sniffer Testbench ===\n\n");
    
    int passed = 0;
    int total = 6;
    
    reset();
    if (test_rx_capture()) passed++;
    
    reset();
    if (test_tx_capture()) passed++;
    
    reset();
    if (test_cycle_counter()) passed++;
    
    reset();
    if (test_ready_counters()) passed++;
    
    reset();
    if (test_tx_state()) passed++;
    
    reset();
    if (test_default_value()) passed++;
    
    printf("\n=== Results: %d/%d tests passed ===\n", passed, total);
    
    delete dut;
    
    return (passed == total) ? 0 : 1;
}
