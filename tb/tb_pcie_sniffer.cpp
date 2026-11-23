//-----------------------------------------------------------------------------
// tb_pcie_sniffer.cpp - Testbench for pcie_sniffer module
//
// Tests the PCIe TLP trace capture functionality:
//   1. Basic RX/TX capture (last-seen)
//   2. Trace buffer capture
//   3. Trigger modes
//   4. Filter modes
//   5. Control (start/stop/clear)
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
    for (int i = 0; i < 8; i++) dut->rx_st_data[i] = 0;
    dut->rx_st_sop = 0;
    dut->rx_st_hvalid = 0;
    dut->rx_st_ready = 1;
    dut->tx_st_hdr[0] = 0;
    dut->tx_st_hdr[1] = 0;
    dut->tx_st_hdr[2] = 0;
    dut->tx_st_hdr[3] = 0;
    for (int i = 0; i < 8; i++) dut->tx_st_data[i] = 0;
    dut->tx_st_sop = 0;
    dut->tx_st_hvalid = 0;
    dut->tx_st_ready = 1;
    dut->tx_state = 0;
    dut->dbg_addr = 0;
    dut->dbg_wdata = 0;
    dut->dbg_wen = 0;
    
    for (int i = 0; i < 5; i++) tick();
    dut->rst_n = 1;
    for (int i = 0; i < 3; i++) tick();
}

// Read a debug register (word address * 4)
// Note: dbg_rdata is registered, need tick to get result
uint32_t read_dbg(uint16_t byte_addr) {
    dut->dbg_addr = byte_addr;
    tick();  // Clock in the address, output appears on dbg_rdata
    return dut->dbg_rdata;
}

// Write a debug register
void write_dbg(uint16_t byte_addr, uint32_t value) {
    dut->dbg_addr = byte_addr;
    dut->dbg_wdata = value;
    dut->dbg_wen = 1;
    tick();
    dut->dbg_wen = 0;
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

bool test_last_seen_capture() {
    printf("Test 1: Last-Seen RX/TX Capture\n");
    
    // Send an MRd TLP: Fmt=000, Type=00000, Length=2
    uint32_t dw0 = (0b000 << 29) | (0b00000 << 24) | 2;
    uint32_t dw1 = (0x0100 << 16) | (0x42 << 8) | 0xFF;
    uint32_t dw2 = 0x12340000;
    uint32_t dw3 = 0;
    uint32_t data_lo = 0xCAFEBABE;
    uint32_t data_hi = 0xDEADBEEF;
    
    send_rx_tlp(dw2, dw1, dw0, dw3, data_lo, data_hi);
    tick(); tick();
    
    // Check status register for rx_seen
    uint32_t status = read_dbg(0x00);
    if (!(status & 1)) {
        printf("  [X] rx_seen not set (status=0x%08x)\n", status);
        return false;
    }
    
    // Check rx_count (offset 0x018)
    uint32_t rx_count = read_dbg(0x18);
    if (rx_count != 1) {
        printf("  [X] rx_count wrong: %d\n", rx_count);
        return false;
    }
    
    // Check last_rx_hdr (now at offset 0x070-0x07C)
    uint32_t hdr0 = read_dbg(0x70);
    uint32_t hdr1 = read_dbg(0x74);
    
    if (hdr0 != dw2 || hdr1 != dw1) {
        printf("  [X] last_rx_hdr mismatch\n");
        printf("      Expected: 0x%08x 0x%08x\n", dw2, dw1);
        printf("      Got:      0x%08x 0x%08x\n", hdr0, hdr1);
        return false;
    }
    
    // Check last_rx_data (now at offset 0x080-0x09C for 256 bits)
    uint32_t captured_lo = read_dbg(0x80);
    uint32_t captured_hi = read_dbg(0x84);
    
    if (captured_lo != data_lo || captured_hi != data_hi) {
        printf("  [X] last_rx_data mismatch\n");
        printf("      Expected: 0x%08x 0x%08x\n", data_lo, data_hi);
        printf("      Got:      0x%08x 0x%08x\n", captured_lo, captured_hi);
        return false;
    }
    
    printf("  [OK] Last-seen capture working\n");
    return true;
}

bool test_trace_buffer_basic() {
    printf("Test 2: Trace Buffer Basic Capture\n");
    
    // Clear and start capture
    write_dbg(0x04, 0x04);  // Clear
    tick();
    write_dbg(0x04, 0x01);  // Start
    tick();
    
    // Verify running (bit 16)
    uint32_t status = read_dbg(0x00);
    if (!(status & (1 << 16))) {
        printf("  [X] Not running after start (status=0x%08x)\n", status);
        return false;
    }
    
    // Send 5 RX TLPs
    for (int i = 0; i < 5; i++) {
        uint32_t dw0 = (0b000 << 29) | (0b00000 << 24) | (i + 1);
        uint32_t dw1 = (0x0100 << 16) | ((0x10 + i) << 8);
        send_rx_tlp(0x1000 + i * 0x100, dw1, dw0, 0, 0xAAAA0000 + i, 0xBBBB0000 + i);
        tick();
    }
    
    // Send 3 TX TLPs
    for (int i = 0; i < 3; i++) {
        uint32_t dw0 = (0b010 << 29) | (0b01010 << 24) | 2;  // CplD
        uint32_t dw1 = (0xb400 << 16) | 8;
        send_tx_tlp(0, dw1, dw0, 0, 0xCCCC0000 + i, 0xDDDD0000 + i);
        tick();
    }
    
    // Check entry count (offset 0x014)
    uint32_t entry_count = read_dbg(0x14);
    if (entry_count != 8) {
        printf("  [X] Entry count wrong: %d (expected 8)\n", entry_count);
        return false;
    }
    
    // Read back entry 0 (first RX)
    write_dbg(0x30, 0);  // Set read_ptr to 0
    tick();
    
    uint32_t trace_hdr0 = read_dbg(0x34);
    uint32_t trace_meta = read_dbg(0x64);  // trace_meta now at 0x64
    uint8_t direction = trace_meta & 1;
    
    if (direction != 0) {
        printf("  [X] Entry 0 should be RX (dir=0), got dir=%d\n", direction);
        return false;
    }
    
    // Read back entry 5 (first TX)
    write_dbg(0x30, 5);  // Set read_ptr to 5
    tick();
    
    trace_meta = read_dbg(0x64);  // trace_meta now at 0x64
    direction = trace_meta & 1;
    
    if (direction != 1) {
        printf("  [X] Entry 5 should be TX (dir=1), got dir=%d\n", direction);
        return false;
    }
    
    printf("  [OK] Trace buffer captures RX and TX TLPs\n");
    return true;
}

bool test_stop_on_full() {
    printf("Test 3: Stop-on-Full Mode\n");
    
    // Clear, set mode=1 (stop-on-full), start
    write_dbg(0x04, 0x04);  // Clear
    write_dbg(0x08, 0x01);  // Mode = stop-on-full
    write_dbg(0x04, 0x01);  // Start
    tick();
    
    // Send 260 TLPs (should stop at 256)
    for (int i = 0; i < 260; i++) {
        uint32_t dw0 = (0b000 << 29) | (i & 0xFF);
        send_rx_tlp(i, 0, dw0, 0, i, 0);
    }
    
    // Check status - should be stopped and full
    uint32_t status = read_dbg(0x00);
    bool running = (status >> 16) & 1;
    bool full = (status >> 18) & 1;
    
    if (running) {
        printf("  [X] Still running after overflow\n");
        return false;
    }
    
    if (!full) {
        printf("  [X] Full flag not set\n");
        return false;
    }
    
    // Entry count should be 256
    uint32_t entry_count = read_dbg(0x14);
    if (entry_count != 256) {
        printf("  [X] Entry count wrong: %d (expected 256)\n", entry_count);
        return false;
    }
    
    printf("  [OK] Stop-on-full mode works\n");
    return true;
}

bool test_continuous_mode() {
    printf("Test 4: Continuous (Ring Buffer) Mode\n");
    
    // Clear, set mode=0 (continuous), start
    write_dbg(0x04, 0x04);  // Clear
    write_dbg(0x08, 0x00);  // Mode = continuous
    write_dbg(0x04, 0x01);  // Start
    tick();
    
    // Send 300 TLPs (should wrap around)
    for (int i = 0; i < 300; i++) {
        uint32_t dw0 = (0b000 << 29) | (i & 0xFF);
        send_rx_tlp(i * 0x100, 0, dw0, 0, 0x1000 + i, 0);
    }
    
    // Should still be running (bit 16)
    uint32_t status = read_dbg(0x00);
    bool running = (status >> 16) & 1;
    
    if (!running) {
        printf("  [X] Stopped in continuous mode\n");
        return false;
    }
    
    // Write pointer should have wrapped (300 mod 256 = 44)
    uint32_t write_ptr = read_dbg(0x10);
    if (write_ptr != 44) {
        printf("  [X] Write pointer wrong: %d (expected 44)\n", write_ptr);
        return false;
    }
    
    // Entry 0 should have the 257th TLP (i=256), address = 256*0x100 = 0x10000
    write_dbg(0x30, 0);
    tick();
    uint32_t trace_hdr0 = read_dbg(0x34);
    if (trace_hdr0 != 0x10000) {
        printf("  [X] Entry 0 should be TLP 256, got hdr0=0x%08x\n", trace_hdr0);
        return false;
    }
    
    printf("  [OK] Continuous mode wraps correctly\n");
    return true;
}

bool test_clear_control() {
    printf("Test 5: Clear Control\n");
    
    // First capture some TLPs
    write_dbg(0x04, 0x01);  // Start
    for (int i = 0; i < 10; i++) {
        send_rx_tlp(i, 0, 0, 0, i, 0);
    }
    
    uint32_t count_before = read_dbg(0x14);
    if (count_before == 0) {
        printf("  [X] No entries captured before clear\n");
        return false;
    }
    
    // Clear
    write_dbg(0x04, 0x04);
    tick();
    
    // Check entry count is 0
    uint32_t count_after = read_dbg(0x14);
    if (count_after != 0) {
        printf("  [X] Entry count not cleared: %d\n", count_after);
        return false;
    }
    
    // Check write_ptr is 0
    uint32_t write_ptr = read_dbg(0x10);
    if (write_ptr != 0) {
        printf("  [X] Write pointer not cleared: %d\n", write_ptr);
        return false;
    }
    
    printf("  [OK] Clear control works\n");
    return true;
}

bool test_tx_state_capture() {
    printf("Test 6: TX State in Trace Entry\n");
    
    write_dbg(0x04, 0x04);  // Clear
    write_dbg(0x04, 0x01);  // Start
    
    // Set tx_state and capture a TLP
    dut->tx_state = 7;
    send_rx_tlp(0x1234, 0, 0, 0, 0, 0);
    tick();
    
    // Read trace entry metadata (now at 0x64 instead of 0x4C)
    write_dbg(0x30, 0);
    tick();
    uint32_t trace_meta = read_dbg(0x64);
    uint8_t captured_state = (trace_meta >> 1) & 0xF;
    
    if (captured_state != 7) {
        printf("  [X] TX state wrong: %d (expected 7)\n", captured_state);
        return false;
    }
    
    printf("  [OK] TX state captured in trace entry\n");
    return true;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    
    dut = new Vpcie_sniffer;
    
    printf("=== PCIe Sniffer Trace Buffer Testbench ===\n\n");
    
    int passed = 0;
    int total = 6;
    
    reset();
    if (test_last_seen_capture()) passed++;
    
    reset();
    if (test_trace_buffer_basic()) passed++;
    
    reset();
    if (test_stop_on_full()) passed++;
    
    reset();
    if (test_continuous_mode()) passed++;
    
    reset();
    if (test_clear_control()) passed++;
    
    reset();
    if (test_tx_state_capture()) passed++;
    
    printf("\n=== Results: %d/%d tests passed ===\n", passed, total);
    
    delete dut;
    
    return (passed == total) ? 0 : 1;
}
