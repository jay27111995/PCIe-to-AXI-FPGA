#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vaxi_ram.h"
#include <cstdio>
#include <cstdint>

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
bool axi_write(uint32_t addr, uint64_t data, uint8_t strb = 0xFF) {
    int timeout;
    
    // Present write
    dut->s_axi_awaddr = addr;
    dut->s_axi_awvalid = 1;
    dut->s_axi_wdata = data;
    dut->s_axi_wstrb = strb;
    dut->s_axi_wvalid = 1;
    dut->eval();  // Evaluate so DUT sees the inputs
    
    // Wait for address and data handshake (valid & ready both high)
    timeout = 20;
    while (timeout-- > 0) {
        if (dut->s_axi_awready && dut->s_axi_wready) break;
        tick();
    }
    if (timeout <= 0) { printf("  ERROR: Write handshake timeout\n"); return false; }
    
    tick();  // Complete the handshake cycle
    
    // Deassert valid
    dut->s_axi_awvalid = 0;
    dut->s_axi_wvalid = 0;
    
    // Wait for bvalid
    timeout = 20;
    while (timeout-- > 0) {
        if (dut->s_axi_bvalid) break;
        tick();
    }
    if (timeout <= 0) { printf("  ERROR: Write response timeout\n"); return false; }
    
    // Check response
    if (dut->s_axi_bresp != 0) {
        printf("  ERROR: Bad write response: %d\n", dut->s_axi_bresp);
        return false;
    }
    
    tick();  // Let bvalid clear
    return true;
}

// Read and return data
bool axi_read(uint32_t addr, uint64_t* data) {
    int timeout;
    
    // Present read address
    dut->s_axi_araddr = addr;
    dut->s_axi_arvalid = 1;
    dut->eval();  // Evaluate so DUT sees the inputs
    
    // Wait for address handshake
    timeout = 20;
    while (timeout-- > 0) {
        if (dut->s_axi_arready) break;
        tick();
    }
    if (timeout <= 0) { printf("  ERROR: Read handshake timeout\n"); return false; }
    
    tick();  // Complete the handshake cycle
    
    // Deassert valid
    dut->s_axi_arvalid = 0;
    
    // Wait for rvalid
    timeout = 20;
    while (timeout-- > 0) {
        if (dut->s_axi_rvalid) break;
        tick();
    }
    if (timeout <= 0) { printf("  ERROR: Read data timeout\n"); return false; }
    
    // Capture data
    *data = dut->s_axi_rdata;
    
    // Check response
    if (dut->s_axi_rresp != 0) {
        printf("  ERROR: Bad read response: %d\n", dut->s_axi_rresp);
        return false;
    }
    
    tick();  // Let rvalid clear
    return true;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    dut = new Vaxi_ram;
    trace = new VerilatedVcdC;
    Verilated::traceEverOn(true);
    dut->trace(trace, 99);
    trace->open("axi_ram_tb.vcd");

    int pass = 0, fail = 0;
    uint64_t rdata;
    bool ok;
    int i;

    printf("=== axi_ram Unit Testbench ===\n\n");

    //=========================================================================
    // Test 1: Single write/read
    //=========================================================================
    printf("Test 1: Single write/read\n");
    reset();
    
    if (!axi_write(0x2000, 0xCAFEBABE12345678)) { fail++; goto test2; }
    if (!axi_read(0x2000, &rdata)) { fail++; goto test2; }
    
    if (rdata == 0xCAFEBABE12345678) {
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
    
    // Write to different addresses
    if (!axi_write(0x2000, 0x1111111111111111)) { fail++; goto test3; }
    if (!axi_write(0x2008, 0x2222222222222222)) { fail++; goto test3; }
    if (!axi_write(0x2010, 0x3333333333333333)) { fail++; goto test3; }
    if (!axi_write(0x2018, 0x4444444444444444)) { fail++; goto test3; }
    
    // Read back in different order
    if (!axi_read(0x2018, &rdata) || rdata != 0x4444444444444444) {
        printf("  ✗ FAIL at 0x2018: got 0x%016lx\n", rdata); fail++; goto test3;
    }
    if (!axi_read(0x2000, &rdata) || rdata != 0x1111111111111111) {
        printf("  ✗ FAIL at 0x2000: got 0x%016lx\n", rdata); fail++; goto test3;
    }
    if (!axi_read(0x2010, &rdata) || rdata != 0x3333333333333333) {
        printf("  ✗ FAIL at 0x2010: got 0x%016lx\n", rdata); fail++; goto test3;
    }
    if (!axi_read(0x2008, &rdata) || rdata != 0x2222222222222222) {
        printf("  ✗ FAIL at 0x2008: got 0x%016lx\n", rdata); fail++; goto test3;
    }
    
    printf("  ✓ PASS\n"); pass++;

test3:
    //=========================================================================
    // Test 3: Byte strobes (partial write)
    //=========================================================================
    printf("Test 3: Byte strobes (partial write)\n");
    reset();
    
    // Write full word first
    if (!axi_write(0x2000, 0xFFFFFFFFFFFFFFFF)) { fail++; goto test4; }
    
    // Overwrite only lower 4 bytes (strb = 0x0F)
    if (!axi_write(0x2000, 0x00000000DEADBEEF, 0x0F)) { fail++; goto test4; }
    
    // Read back - upper 4 bytes should be FF, lower should be DEADBEEF
    if (!axi_read(0x2000, &rdata)) { fail++; goto test4; }
    
    if (rdata == 0xFFFFFFFFDEADBEEF) {
        printf("  ✓ PASS\n"); pass++;
    } else {
        printf("  ✗ FAIL: expected 0xFFFFFFFFDEADBEEF, got 0x%016lx\n", rdata);
        fail++;
    }

test4:
    //=========================================================================
    // Test 4: Back-to-back writes
    //=========================================================================
    printf("Test 4: Back-to-back writes\n");
    reset();
    
    for (i = 0; i < 16; i++) {
        if (!axi_write(0x2000 + i*8, 0x1000 + i)) { fail++; goto test5; }
    }
    
    // Verify all
    ok = true;
    for (i = 0; i < 16; i++) {
        if (!axi_read(0x2000 + i*8, &rdata) || rdata != (uint64_t)(0x1000 + i)) {
            printf("  ✗ FAIL at offset %d: expected 0x%x, got 0x%016lx\n", i, 0x1000+i, rdata);
            ok = false; break;
        }
    }
    
    if (ok) { printf("  ✓ PASS\n"); pass++; }
    else { fail++; }

test5:
    //=========================================================================
    // Test 5: Back-to-back reads
    //=========================================================================
    printf("Test 5: Back-to-back reads\n");
    reset();
    
    // Setup data
    for (i = 0; i < 8; i++) {
        if (!axi_write(0x2000 + i*8, 0xA000 + i)) { fail++; goto done; }
    }
    
    // Rapid reads
    ok = true;
    for (i = 0; i < 8; i++) {
        if (!axi_read(0x2000 + i*8, &rdata) || rdata != (uint64_t)(0xA000 + i)) {
            printf("  ✗ FAIL at offset %d: expected 0x%x, got 0x%016lx\n", i, 0xA000+i, rdata);
            ok = false; break;
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
