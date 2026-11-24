//-----------------------------------------------------------------------------
// tb_pcie_sniffer.cpp - Testbench for pcie_sniffer module (new AXI interface)
//
// Tests:
//   1. Basic status/control
//   2. RX/TX capture
//   3. Trace buffer read
//   4. Clear functionality
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
    dut->global_timestamp = cycle;
}

void reset() {
    dut->rst_n = 0;
    dut->global_timestamp = 0;
    dut->rx_st_hdr[0] = 0;
    dut->rx_st_hdr[1] = 0;
    dut->rx_st_hdr[2] = 0;
    dut->rx_st_hdr[3] = 0;
    for (int i = 0; i < 8; i++) dut->rx_st_data[i] = 0;
    dut->rx_st_sop = 0;
    dut->rx_st_eop = 0;
    dut->rx_st_hvalid = 0;
    dut->rx_st_dvalid = 0;
    dut->rx_st_bar = 0;
    dut->rx_st_ready = 1;
    dut->tx_st_hdr[0] = 0;
    dut->tx_st_hdr[1] = 0;
    dut->tx_st_hdr[2] = 0;
    dut->tx_st_hdr[3] = 0;
    for (int i = 0; i < 8; i++) dut->tx_st_data[i] = 0;
    dut->tx_st_sop = 0;
    dut->tx_st_eop = 0;
    dut->tx_st_hvalid = 0;
    dut->tx_st_dvalid = 0;
    dut->tx_st_ready = 1;
    dut->axi_araddr = 0;
    dut->axi_arvalid = 0;
    dut->axi_rready = 1;
    dut->axi_awaddr = 0;
    dut->axi_wdata = 0;
    dut->axi_awvalid = 0;
    dut->axi_wvalid = 0;
    dut->axi_bready = 1;
    
    for (int i = 0; i < 5; i++) tick();
    dut->rst_n = 1;
    for (int i = 0; i < 3; i++) tick();
}

// Read a 64-bit register via AXI
uint64_t axi_read(uint16_t addr) {
    dut->axi_araddr = addr;
    dut->axi_arvalid = 1;
    
    // Wait for arready
    while (!dut->axi_arready) tick();
    tick();
    dut->axi_arvalid = 0;
    
    // Wait for rvalid
    while (!dut->axi_rvalid) tick();
    uint64_t data = dut->axi_rdata;
    tick();
    
    return data;
}

// Write a 64-bit register via AXI
void axi_write(uint16_t addr, uint64_t value) {
    dut->axi_awaddr = addr;
    dut->axi_wdata = value;
    dut->axi_awvalid = 1;
    dut->axi_wvalid = 1;
    
    // Wait for ready
    while (!dut->axi_awready || !dut->axi_wready) tick();
    tick();
    dut->axi_awvalid = 0;
    dut->axi_wvalid = 0;
    
    // Wait for bvalid
    while (!dut->axi_bvalid) tick();
    tick();
}

// Simulate an RX TLP
void send_rx_tlp(uint32_t hdr0, uint32_t hdr1, uint32_t hdr2, uint32_t hdr3, 
                 uint64_t data0 = 0, uint64_t data1 = 0) {
    dut->rx_st_hdr[0] = hdr0;
    dut->rx_st_hdr[1] = hdr1;
    dut->rx_st_hdr[2] = hdr2;
    dut->rx_st_hdr[3] = hdr3;
    dut->rx_st_data[0] = data0 & 0xFFFFFFFF;
    dut->rx_st_data[1] = data0 >> 32;
    dut->rx_st_data[2] = data1 & 0xFFFFFFFF;
    dut->rx_st_data[3] = data1 >> 32;
    dut->rx_st_sop = 1;
    dut->rx_st_hvalid = 1;
    tick();
    dut->rx_st_hvalid = 0;
    dut->rx_st_sop = 0;
}

// Simulate a TX TLP
void send_tx_tlp(uint32_t hdr0, uint32_t hdr1, uint32_t hdr2, uint32_t hdr3,
                 uint64_t data0 = 0, uint64_t data1 = 0) {
    dut->tx_st_hdr[0] = hdr0;
    dut->tx_st_hdr[1] = hdr1;
    dut->tx_st_hdr[2] = hdr2;
    dut->tx_st_hdr[3] = hdr3;
    dut->tx_st_data[0] = data0 & 0xFFFFFFFF;
    dut->tx_st_data[1] = data0 >> 32;
    dut->tx_st_data[2] = data1 & 0xFFFFFFFF;
    dut->tx_st_data[3] = data1 >> 32;
    dut->tx_st_sop = 1;
    dut->tx_st_hvalid = 1;
    tick();
    dut->tx_st_hvalid = 0;
    dut->tx_st_sop = 0;
}

//=============================================================================
// Test Cases
//=============================================================================

bool test_status_read() {
    printf("Test 1: Status register read\n");
    
    // Read status at 0x000 - should be 0 (not running, not full)
    uint64_t status = axi_read(0x000);
    printf("    Status: 0x%016lx\n", status);
    
    if (status == 0) {
        printf("  [OK] PASS\n");
        return true;
    }
    printf("  [X] FAIL (expected 0)\n");
    return false;
}

bool test_start_stop() {
    printf("Test 2: Start/Stop control\n");
    
    // Write start (bit 0)
    axi_write(0x000, 1);
    
    // Read status - should show running
    uint64_t status = axi_read(0x000);
    bool running = status & 1;
    printf("    After start: status=0x%lx, running=%d\n", status, running);
    
    if (!running) {
        printf("  [X] FAIL (not running after start)\n");
        return false;
    }
    
    // Write stop (bit 1)
    axi_write(0x000, 2);
    
    status = axi_read(0x000);
    running = status & 1;
    printf("    After stop: status=0x%lx, running=%d\n", status, running);
    
    if (running) {
        printf("  [X] FAIL (still running after stop)\n");
        return false;
    }
    
    printf("  [OK] PASS\n");
    return true;
}

bool test_rx_capture() {
    printf("Test 3: RX TLP capture\n");
    
    // Clear and start
    axi_write(0x000, 4);  // clear
    axi_write(0x000, 1);  // start
    
    // Send an RX TLP
    uint32_t hdr0 = 0x40000002;  // MRd, 2 DW
    uint32_t hdr1 = 0x01004200;  // req_id, tag
    uint32_t hdr2 = 0x12340000;  // addr
    send_rx_tlp(hdr0, hdr1, hdr2, 0, 0xCAFEBABEDEADBEEF);
    
    tick(); tick();
    
    // Check entry_count
    uint64_t entry_count = axi_read(0x010);
    printf("    Entry count: %lu\n", entry_count);
    
    if (entry_count < 1) {
        printf("  [X] FAIL (no entries captured)\n");
        return false;
    }
    
    // Read last RX header at 0x040
    uint64_t last_rx_hdr0 = axi_read(0x040);
    uint64_t last_rx_hdr1 = axi_read(0x048);
    printf("    Last RX hdr: 0x%016lx 0x%016lx\n", last_rx_hdr0, last_rx_hdr1);
    
    // Check header matches
    uint32_t got_hdr0 = last_rx_hdr0 & 0xFFFFFFFF;
    if (got_hdr0 == hdr0) {
        printf("  [OK] PASS\n");
        return true;
    }
    
    printf("  [X] FAIL (header mismatch: expected 0x%08x, got 0x%08x)\n", hdr0, got_hdr0);
    return false;
}

bool test_trace_read() {
    printf("Test 4: Trace RAM read\n");
    
    // Clear and start
    axi_write(0x000, 4);  // clear
    axi_write(0x000, 1);  // start
    
    // Send multiple TLPs
    for (int i = 0; i < 3; i++) {
        send_rx_tlp(0x40000002 | (i << 8), 0x01004200, 0x12340000 + i * 0x100, 0);
        tick();
    }
    
    axi_write(0x000, 2);  // stop
    
    // Check entry count
    uint64_t entry_count = axi_read(0x010);
    printf("    Entry count: %lu\n", entry_count);
    
    if (entry_count < 3) {
        printf("  [X] FAIL (expected 3+ entries, got %lu)\n", entry_count);
        return false;
    }
    
    // Read trace entry 0 at 0x100
    uint64_t trace_qw0 = axi_read(0x100);  // hdr[63:0]
    uint64_t trace_qw1 = axi_read(0x108);  // hdr[127:64]
    printf("    Trace[0] hdr: 0x%016lx 0x%016lx\n", trace_qw0, trace_qw1);
    
    // Check it looks like our first TLP
    uint32_t got_hdr0 = trace_qw0 & 0xFFFFFFFF;
    if (got_hdr0 == 0x40000002) {
        printf("  [OK] PASS\n");
        return true;
    }
    
    printf("  [X] FAIL (trace mismatch)\n");
    return false;
}

bool test_clear() {
    printf("Test 5: Clear functionality\n");
    
    // Start and capture something
    axi_write(0x000, 1);  // start
    send_rx_tlp(0x40000001, 0, 0, 0);
    tick();
    
    // Verify we have entries
    uint64_t count_before = axi_read(0x010);
    printf("    Before clear: entry_count=%lu\n", count_before);
    
    // Clear
    axi_write(0x000, 4);
    
    // Check counters reset
    uint64_t count_after = axi_read(0x010);
    uint64_t write_ptr = axi_read(0x008);
    printf("    After clear: entry_count=%lu, write_ptr=%lu\n", count_after, write_ptr);
    
    if (count_after == 0 && write_ptr == 0) {
        printf("  [OK] PASS\n");
        return true;
    }
    
    printf("  [X] FAIL (counters not reset)\n");
    return false;
}

bool test_tx_capture() {
    printf("Test 6: TX TLP capture\n");
    
    // Clear and start
    axi_write(0x000, 4);  // clear
    axi_write(0x000, 1);  // start
    
    // Send a TX TLP
    uint32_t hdr0 = 0x4A000008;  // CplD, 8 DW
    send_tx_tlp(hdr0, 0, 0, 0, 0xFEEDFACE);
    
    tick(); tick();
    
    // Check tx_count
    uint64_t tx_count = axi_read(0x020);
    printf("    TX count: %lu\n", tx_count);
    
    // Read last TX at 0x080
    uint64_t last_tx_hdr = axi_read(0x080);
    printf("    Last TX hdr: 0x%016lx\n", last_tx_hdr);
    
    uint32_t got = last_tx_hdr & 0xFFFFFFFF;
    if (tx_count >= 1 && got == hdr0) {
        printf("  [OK] PASS\n");
        return true;
    }
    
    printf("  [X] FAIL\n");
    return false;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    dut = new Vpcie_sniffer;
    
    int pass = 0, fail = 0;
    
    reset();
    if (test_status_read()) pass++; else fail++;
    
    reset();
    if (test_start_stop()) pass++; else fail++;
    
    reset();
    if (test_rx_capture()) pass++; else fail++;
    
    reset();
    if (test_trace_read()) pass++; else fail++;
    
    reset();
    if (test_clear()) pass++; else fail++;
    
    reset();
    if (test_tx_capture()) pass++; else fail++;
    
    printf("\n=== Results: %d passed, %d failed ===\n", pass, fail);
    
    delete dut;
    return fail > 0 ? 1 : 0;
}
