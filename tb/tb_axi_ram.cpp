#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vaxi_ram.h"
#include <cstdio>
#include <cstdint>
#include <cstdlib>

Vaxi_ram* dut;
VerilatedVcdC* trace;
uint64_t cycle = 0;

void tick() {
    dut->clk = 0; dut->eval(); trace->dump(cycle * 10);
    dut->clk = 1; dut->eval(); trace->dump(cycle * 10 + 5);
    cycle++;
}

void reset() {
    dut->rst_n = 0;
    dut->s_axi_awaddr = 0;
    dut->s_axi_awvalid = 0;
    dut->s_axi_wdata = 0;
    dut->s_axi_wstrb = 0xFF;
    dut->s_axi_wvalid = 0;
    dut->s_axi_bready = 1;
    dut->s_axi_araddr = 0;
    dut->s_axi_arvalid = 0;
    dut->s_axi_rready = 1;
    
    for (int i = 0; i < 5; i++) tick();
    dut->rst_n = 1;
    for (int i = 0; i < 5; i++) tick();
}

// Write and wait for response
bool axi_write(uint32_t addr, uint64_t data, uint8_t strb = 0xFF, int timeout = 20) {
    // Present write
    dut->s_axi_awaddr = addr;
    dut->s_axi_awvalid = 1;
    dut->s_axi_wdata = data;
    dut->s_axi_wstrb = strb;
    dut->s_axi_wvalid = 1;
    dut->eval();

    // Wait for handshake
    int t = timeout;
    while (t-- > 0) {
        if (dut->s_axi_awready && dut->s_axi_wready) break;
        tick();
    }
    if (t <= 0) { printf("  ERROR: Write handshake timeout\n"); return false; }
    
    tick();
    dut->s_axi_awvalid = 0;
    dut->s_axi_wvalid = 0;
    
    // Wait for bvalid
    t = timeout;
    while (t-- > 0) {
        if (dut->s_axi_bvalid) break;
        tick();
    }
    if (t <= 0) { printf("  ERROR: Write response timeout\n"); return false; }
    
    if (dut->s_axi_bresp != 0) {
        printf("  ERROR: Bad write response: %d\n", dut->s_axi_bresp);
        return false;
    }
    
    tick();
    return true;
}

// Read and return data
bool axi_read(uint32_t addr, uint64_t* data, int timeout = 20) {
    // Present read
    dut->s_axi_araddr = addr;
    dut->s_axi_arvalid = 1;
    dut->eval();
    
    // Wait for handshake
    int t = timeout;
    while (t-- > 0) {
        if (dut->s_axi_arready) break;
        tick();
    }
    if (t <= 0) { printf("  ERROR: Read handshake timeout\n"); return false; }
    
    tick();
    dut->s_axi_arvalid = 0;
    
    // Wait for rvalid
    t = timeout;
    while (t-- > 0) {
        if (dut->s_axi_rvalid) break;
        tick();
    }
    if (t <= 0) { printf("  ERROR: Read data timeout\n"); return false; }
    
    *data = dut->s_axi_rdata;
    
    if (dut->s_axi_rresp != 0) {
        printf("  ERROR: Bad read response: %d\n", dut->s_axi_rresp);
        return false;
    }
    
    tick();
    return true;
}

// Simple random for testing
uint64_t rand64() {
    return ((uint64_t)rand() << 32) | rand();
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    dut = new Vaxi_ram;
    trace = new VerilatedVcdC;
    Verilated::traceEverOn(true);
    dut->trace(trace, 99);
    trace->open("axi_ram_tb.vcd");

    srand(12345);  // Fixed seed for reproducibility

    int pass = 0, fail = 0;
    uint64_t rdata;
    bool ok;
    int i;

    printf("=== axi_ram Comprehensive Testbench ===\n\n");

    //=========================================================================
    // Test 1: Single write/read
    //=========================================================================
    printf("Test 1: Single write/read\n");
    reset();
    
    if (!axi_write(0x1000, 0xCAFEBABE12345678ULL)) { fail++; goto test2; }
    if (!axi_read(0x1000, &rdata)) { fail++; goto test2; }
    
    if (rdata == 0xCAFEBABE12345678ULL) {
        printf("  ✓ PASS\n"); pass++;
    } else {
        printf("  ✗ FAIL: expected 0xCAFEBABE12345678, got 0x%016lx\n", rdata);
        fail++;
    }

test2:
    //=========================================================================
    // Test 2: Multiple addresses
    //=========================================================================
    printf("Test 2: Multiple addresses\n");
    reset();
    
    if (!axi_write(0x1000, 0x1111111111111111ULL)) { fail++; goto test3; }
    if (!axi_write(0x1008, 0x2222222222222222ULL)) { fail++; goto test3; }
    if (!axi_write(0x1010, 0x3333333333333333ULL)) { fail++; goto test3; }
    if (!axi_write(0x1018, 0x4444444444444444ULL)) { fail++; goto test3; }
    
    if (!axi_read(0x1018, &rdata) || rdata != 0x4444444444444444ULL) {
        printf("  ✗ FAIL at 0x1018: got 0x%016lx\n", rdata); fail++; goto test3;
    }
    if (!axi_read(0x1000, &rdata) || rdata != 0x1111111111111111ULL) {
        printf("  ✗ FAIL at 0x1000: got 0x%016lx\n", rdata); fail++; goto test3;
    }
    if (!axi_read(0x1010, &rdata) || rdata != 0x3333333333333333ULL) {
        printf("  ✗ FAIL at 0x1010: got 0x%016lx\n", rdata); fail++; goto test3;
    }
    if (!axi_read(0x1008, &rdata) || rdata != 0x2222222222222222ULL) {
        printf("  ✗ FAIL at 0x1008: got 0x%016lx\n", rdata); fail++; goto test3;
    }
    
    printf("  ✓ PASS\n"); pass++;

test3:
    //=========================================================================
    // Test 3: Byte strobes (partial write)
    //=========================================================================
    printf("Test 3: Byte strobes (partial write)\n");
    reset();
    
    if (!axi_write(0x1000, 0xFFFFFFFFFFFFFFFFULL)) { fail++; goto test4; }
    if (!axi_write(0x1000, 0x00000000DEADBEEFULL, 0x0F)) { fail++; goto test4; }
    if (!axi_read(0x1000, &rdata)) { fail++; goto test4; }
    
    if (rdata == 0xFFFFFFFFDEADBEEFULL) {
        printf("  ✓ PASS\n"); pass++;
    } else {
        printf("  ✗ FAIL: expected 0xFFFFFFFFDEADBEEF, got 0x%016lx\n", rdata);
        fail++;
    }

test4:
    //=========================================================================
    // Test 4: Boundary addresses (first and last)
    //=========================================================================
    printf("Test 4: Boundary addresses\n");
    reset();
    
    // First address (index 0)
    if (!axi_write(0x1000, 0x1111000000000001ULL)) { fail++; goto test5; }
    // Last address (index 511 = 0x1FF, addr = 0x1000 + 511*8 = 0x1FF8)
    if (!axi_write(0x1FF8, 0x2222000000000002ULL)) { fail++; goto test5; }
    
    if (!axi_read(0x1000, &rdata) || rdata != 0x1111000000000001ULL) {
        printf("  ✗ FAIL at first addr: got 0x%016lx\n", rdata); fail++; goto test5;
    }
    if (!axi_read(0x1FF8, &rdata) || rdata != 0x2222000000000002ULL) {
        printf("  ✗ FAIL at last addr: got 0x%016lx\n", rdata); fail++; goto test5;
    }
    
    printf("  ✓ PASS\n"); pass++;

test5:
    //=========================================================================
    // Test 5: All byte strobe patterns
    //=========================================================================
    printf("Test 5: All byte strobe patterns (256 patterns)\n");
    reset();
    
    ok = true;
    for (int strb = 0; strb < 256 && ok; strb++) {
        uint64_t base_val = 0xAAAAAAAAAAAAAAAAULL;
        uint64_t write_val = 0x0000000000000000ULL;
        
        // Write base value
        if (!axi_write(0x1100, base_val)) { ok = false; break; }
        
        // Partial write with strobe
        if (!axi_write(0x1100, write_val, strb)) { ok = false; break; }
        
        // Read back
        if (!axi_read(0x1100, &rdata)) { ok = false; break; }
        
        // Calculate expected: bytes with strb=1 become 0, others stay 0xAA
        uint64_t expected = 0;
        for (int b = 0; b < 8; b++) {
            if (strb & (1 << b)) {
                expected |= ((uint64_t)0x00 << (b * 8));
            } else {
                expected |= ((uint64_t)0xAA << (b * 8));
            }
        }
        
        if (rdata != expected) {
            printf("  ✗ FAIL strb=0x%02x: expected 0x%016lx, got 0x%016lx\n", 
                   strb, expected, rdata);
            ok = false;
        }
    }
    
    if (ok) { printf("  ✓ PASS\n"); pass++; }
    else { fail++; }

test6:
    //=========================================================================
    // Test 6: Back-to-back writes
    //=========================================================================
    printf("Test 6: Back-to-back writes (64 writes)\n");
    reset();
    
    for (i = 0; i < 64; i++) {
        if (!axi_write(0x1000 + i*8, 0x1000 + i)) { fail++; goto test7; }
    }
    
    ok = true;
    for (i = 0; i < 64; i++) {
        if (!axi_read(0x1000 + i*8, &rdata) || rdata != (uint64_t)(0x1000 + i)) {
            printf("  ✗ FAIL at offset %d: expected 0x%lx, got 0x%016lx\n", 
                   i, (uint64_t)(0x1000+i), rdata);
            ok = false; break;
        }
    }
    
    if (ok) { printf("  ✓ PASS\n"); pass++; }
    else { fail++; }

test7:
    //=========================================================================
    // Test 7: Back-to-back reads
    //=========================================================================
    printf("Test 7: Back-to-back reads (64 reads)\n");
    reset();
    
    for (i = 0; i < 64; i++) {
        if (!axi_write(0x1000 + i*8, 0xA000 + i)) { fail++; goto test8; }
    }
    
    ok = true;
    for (i = 0; i < 64; i++) {
        if (!axi_read(0x1000 + i*8, &rdata) || rdata != (uint64_t)(0xA000 + i)) {
            printf("  ✗ FAIL at offset %d\n", i);
            ok = false; break;
        }
    }
    
    if (ok) { printf("  ✓ PASS\n"); pass++; }
    else { fail++; }

test8:
    //=========================================================================
    // Test 8: Read back-pressure (rready low)
    //=========================================================================
    printf("Test 8: Read back-pressure (rready delayed)\n");
    reset();
    
    if (!axi_write(0x1200, 0xBACCBACCBACCBACCULL)) { fail++; goto test9; }
    
    // Start read but hold rready low
    dut->s_axi_rready = 0;
    dut->s_axi_araddr = 0x1200;
    dut->s_axi_arvalid = 1;
    dut->eval();
    
    // Wait for arready
    for (i = 0; i < 20 && !dut->s_axi_arready; i++) tick();
    tick();
    dut->s_axi_arvalid = 0;
    
    // Wait for rvalid with rready=0
    for (i = 0; i < 20 && !dut->s_axi_rvalid; i++) tick();
    
    // rvalid should be high, data waiting
    if (!dut->s_axi_rvalid) {
        printf("  ✗ FAIL: rvalid not asserted\n"); fail++; goto test9;
    }
    
    // Hold for a few cycles (data should persist)
    tick(); tick(); tick();
    
    if (!dut->s_axi_rvalid) {
        printf("  ✗ FAIL: rvalid dropped before rready\n"); fail++; goto test9;
    }
    
    // Now assert rready
    dut->s_axi_rready = 1;
    rdata = dut->s_axi_rdata;
    tick();
    
    if (rdata == 0xBACCBACCBACCBACCULL) {
        printf("  ✓ PASS\n"); pass++;
    } else {
        printf("  ✗ FAIL: expected 0xBACCBACCBACCBACC, got 0x%016lx\n", rdata);
        fail++;
    }

test9:
    //=========================================================================
    // Test 9: Write back-pressure (bready low)
    //=========================================================================
    printf("Test 9: Write back-pressure (bready delayed)\n");
    reset();
    
    dut->s_axi_bready = 0;
    dut->s_axi_awaddr = 0x1300;
    dut->s_axi_awvalid = 1;
    dut->s_axi_wdata = 0xABCDABCDABCDABCDULL;
    dut->s_axi_wstrb = 0xFF;
    dut->s_axi_wvalid = 1;
    dut->eval();
    
    // Wait for handshake
    for (i = 0; i < 20 && !(dut->s_axi_awready && dut->s_axi_wready); i++) tick();
    tick();
    dut->s_axi_awvalid = 0;
    dut->s_axi_wvalid = 0;
    
    // Wait for bvalid
    for (i = 0; i < 20 && !dut->s_axi_bvalid; i++) tick();
    
    if (!dut->s_axi_bvalid) {
        printf("  ✗ FAIL: bvalid not asserted\n"); fail++; goto test10;
    }
    
    // Hold bready low
    tick(); tick(); tick();
    
    if (!dut->s_axi_bvalid) {
        printf("  ✗ FAIL: bvalid dropped before bready\n"); fail++; goto test10;
    }
    
    // Now assert bready
    dut->s_axi_bready = 1;
    tick();
    
    // Verify write happened
    if (!axi_read(0x1300, &rdata)) { fail++; goto test10; }
    
    if (rdata == 0xABCDABCDABCDABCDULL) {
        printf("  ✓ PASS\n"); pass++;
    } else {
        printf("  ✗ FAIL: data not written correctly, got 0x%016lx\n", rdata);
        fail++;
    }

test10:
    //=========================================================================
    // Test 10: Reset recovery
    //=========================================================================
    printf("Test 10: Reset recovery\n");
    reset();
    
    // Write some data
    if (!axi_write(0x1400, 0x1234567890ABCDEFULL)) { fail++; goto test11; }
    
    // Reset
    dut->rst_n = 0;
    tick(); tick();
    dut->rst_n = 1;
    tick(); tick(); tick();
    
    // Should be able to do transactions after reset
    if (!axi_write(0x1400, 0xAFAFAFAFAFAFAFAFULL)) { 
        printf("  ✗ FAIL: write after reset failed\n"); fail++; goto test11; 
    }
    if (!axi_read(0x1400, &rdata)) { 
        printf("  ✗ FAIL: read after reset failed\n"); fail++; goto test11; 
    }
    
    if (rdata == 0xAFAFAFAFAFAFAFAFULL) {
        printf("  ✓ PASS\n"); pass++;
    } else {
        printf("  ✗ FAIL: expected 0xAFAFAFAFAFAFAFAF, got 0x%016lx\n", rdata);
        fail++;
    }

test11:
    //=========================================================================
    // Test 11: Random stress test
    //=========================================================================
    printf("Test 11: Random stress test (500 operations)\n");
    reset();
    
    // Shadow memory for verification - track which addresses are written
    uint64_t shadow[512];
    bool written[512];
    for (i = 0; i < 512; i++) {
        shadow[i] = 0;
        written[i] = false;
    }
    
    ok = true;
    for (i = 0; i < 500 && ok; i++) {
        int idx = rand() % 512;
        uint32_t addr = 0x1000 + idx * 8;
        
        if (rand() % 2 || !written[idx]) {
            // Write (always write if never written before)
            uint64_t val = rand64();
            if (!axi_write(addr, val)) { ok = false; break; }
            shadow[idx] = val;
            written[idx] = true;
        } else {
            // Read (only read addresses we've written)
            if (!axi_read(addr, &rdata)) { ok = false; break; }
            if (rdata != shadow[idx]) {
                printf("  ✗ FAIL at op %d, addr 0x%x: expected 0x%016lx, got 0x%016lx\n",
                       i, addr, shadow[idx], rdata);
                ok = false;
            }
        }
    }
    
    if (ok) { printf("  ✓ PASS\n"); pass++; }
    else { fail++; }

done:
    //=========================================================================
    // Summary
    //=========================================================================
    printf("\n=== Results: %d passed, %d failed ===\n", pass, fail);
    
    trace->close();
    delete trace;
    delete dut;
    return fail > 0 ? 1 : 0;
}
