// DMA Engine Unit Test

#include <verilated.h>
#include "Vdma_engine.h"
#include <cstdio>
#include <map>

Vdma_engine* dut;
int cycle = 0;

std::map<uint64_t, uint64_t> host_mem;
std::map<uint32_t, uint64_t> local_mem;

// AXI response state
bool host_rd_pending = false;
uint64_t host_rd_data = 0;
bool host_wr_pending = false;
bool local_rd_pending = false;
uint64_t local_rd_data = 0;
bool local_wr_pending = false;

void tick() {
    // Drive responses BEFORE clock (hold until handshake)
    dut->m_host_rvalid = host_rd_pending ? 1 : 0;
    dut->m_host_rdata = host_rd_data;
    dut->m_host_bvalid = host_wr_pending ? 1 : 0;
    dut->m_local_rvalid = local_rd_pending ? 1 : 0;
    dut->m_local_rdata = local_rd_data;
    dut->m_local_bvalid = local_wr_pending ? 1 : 0;
    
    // Check for completed handshakes BEFORE clock
    bool hr_done = host_rd_pending && dut->m_host_rvalid && dut->m_host_rready;
    bool hb_done = host_wr_pending && dut->m_host_bvalid && dut->m_host_bready;
    bool lr_done = local_rd_pending && dut->m_local_rvalid && dut->m_local_rready;
    bool lb_done = local_wr_pending && dut->m_local_bvalid && dut->m_local_bready;
    
    dut->clk = 0; dut->eval();
    dut->clk = 1; dut->eval();
    cycle++;
    
    // Process new requests AFTER clock
    if (dut->m_host_arvalid && dut->m_host_arready && !host_rd_pending) {
        host_rd_data = host_mem[dut->m_host_araddr];
        host_rd_pending = true;
    }
    if (dut->m_host_awvalid && dut->m_host_wvalid &&
        dut->m_host_awready && dut->m_host_wready && !host_wr_pending) {
        host_mem[dut->m_host_awaddr] = dut->m_host_wdata;
        host_wr_pending = true;
    }
    if (dut->m_local_arvalid && dut->m_local_arready && !local_rd_pending) {
        local_rd_data = local_mem[dut->m_local_araddr];
        local_rd_pending = true;
    }
    if (dut->m_local_awvalid && dut->m_local_wvalid &&
        dut->m_local_awready && dut->m_local_wready && !local_wr_pending) {
        local_mem[dut->m_local_awaddr] = dut->m_local_wdata;
        local_wr_pending = true;
    }
    
    // Clear pending after handshake
    if (hr_done) host_rd_pending = false;
    if (hb_done) host_wr_pending = false;
    if (lr_done) local_rd_pending = false;
    if (lb_done) local_wr_pending = false;
}

void reg_write(uint32_t addr, uint64_t data) {
    dut->s_axi_awaddr = addr;
    dut->s_axi_awvalid = 1;
    dut->s_axi_wdata = data;
    dut->s_axi_wstrb = 0xFF;
    dut->s_axi_wvalid = 1;
    dut->s_axi_bready = 1;
    for (int i = 0; i < 20 && !dut->s_axi_bvalid; i++) tick();
    tick();
    dut->s_axi_awvalid = 0;
    dut->s_axi_wvalid = 0;
    dut->s_axi_bready = 0;
}

uint64_t reg_read(uint32_t addr) {
    dut->s_axi_araddr = addr;
    dut->s_axi_arvalid = 1;
    dut->s_axi_rready = 1;
    for (int i = 0; i < 20 && !dut->s_axi_rvalid; i++) tick();
    uint64_t data = dut->s_axi_rdata;
    tick();
    dut->s_axi_arvalid = 0;
    dut->s_axi_rready = 0;
    return data;
}

bool wait_done(int timeout = 200) {
    for (int i = 0; i < timeout; i++) tick();
    uint64_t status = reg_read(0x08);
    return !(status & 1);
}

void reset_state() {
    host_mem.clear();
    local_mem.clear();
    host_rd_pending = false;
    host_wr_pending = false;
    local_rd_pending = false;
    local_wr_pending = false;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    dut = new Vdma_engine;
    
    dut->clk = 0; dut->rst_n = 0;
    dut->s_axi_awaddr = 0; dut->s_axi_awvalid = 0;
    dut->s_axi_wdata = 0; dut->s_axi_wstrb = 0; dut->s_axi_wvalid = 0;
    dut->s_axi_bready = 0;
    dut->s_axi_araddr = 0; dut->s_axi_arvalid = 0;
    dut->s_axi_rready = 0;
    
    dut->m_host_arready = 1; dut->m_host_awready = 1; dut->m_host_wready = 1;
    dut->m_host_rvalid = 0; dut->m_host_rdata = 0; dut->m_host_rresp = 0;
    dut->m_host_bvalid = 0; dut->m_host_bresp = 0;
    dut->m_local_arready = 1; dut->m_local_awready = 1; dut->m_local_wready = 1;
    dut->m_local_rvalid = 0; dut->m_local_rdata = 0; dut->m_local_rresp = 0;
    dut->m_local_bvalid = 0; dut->m_local_bresp = 0;
    
    for (int i = 0; i < 5; i++) tick();
    dut->rst_n = 1;
    for (int i = 0; i < 5; i++) tick();
    
    int pass = 0, fail = 0;
    printf("=== DMA Engine Unit Test ===\n\n");
    
    // Test 1: Registers
    printf("Test 1: Register access\n");
    reg_write(0x10, 0x123456789ABCDEF0);
    reg_write(0x18, 0x1000);
    reg_write(0x20, 64);
    if (reg_read(0x10) == 0x123456789ABCDEF0) { printf("  [OK] host_addr\n"); pass++; }
    else { printf("  [X] host_addr\n"); fail++; }
    if (reg_read(0x18) == 0x1000) { printf("  [OK] local_addr\n"); pass++; }
    else { printf("  [X] local_addr\n"); fail++; }
    if (reg_read(0x20) == 64) { printf("  [OK] length\n"); pass++; }
    else { printf("  [X] length\n"); fail++; }
    
    // Test 2: H2C
    printf("\nTest 2: H2C 8 bytes\n");
    reset_state();
    host_mem[0x2000] = 0xCAFEBABEDEADBEEF;
    reg_write(0x10, 0x2000);
    reg_write(0x18, 0x100);
    reg_write(0x20, 8);
    reg_write(0x00, 0x1);
    if (wait_done() && local_mem[0x100] == 0xCAFEBABEDEADBEEF) {
        printf("  [OK] PASS\n"); pass++;
    } else {
        printf("  [X] FAIL (0x%lx)\n", local_mem[0x100]); fail++;
    }
    
    // Test 3: C2H
    printf("\nTest 3: C2H 8 bytes\n");
    reset_state();
    local_mem[0x200] = 0x1111222233334444;
    reg_write(0x10, 0x3000);
    reg_write(0x18, 0x200);
    reg_write(0x20, 8);
    reg_write(0x00, 0x3);
    if (wait_done() && host_mem[0x3000] == 0x1111222233334444) {
        printf("  [OK] PASS\n"); pass++;
    } else {
        printf("  [X] FAIL (0x%lx)\n", host_mem[0x3000]); fail++;
    }
    
    // Test 4: H2C multi-beat
    printf("\nTest 4: H2C 24 bytes\n");
    reset_state();
    host_mem[0x4000] = 0xAAAAAAAAAAAAAAAA;
    host_mem[0x4008] = 0xBBBBBBBBBBBBBBBB;
    host_mem[0x4010] = 0xCCCCCCCCCCCCCCCC;
    reg_write(0x10, 0x4000);
    reg_write(0x18, 0x300);
    reg_write(0x20, 24);
    reg_write(0x00, 0x1);
    bool ok = wait_done() &&
              local_mem[0x300] == 0xAAAAAAAAAAAAAAAA &&
              local_mem[0x308] == 0xBBBBBBBBBBBBBBBB &&
              local_mem[0x310] == 0xCCCCCCCCCCCCCCCC;
    if (ok) { printf("  [OK] PASS\n"); pass++; }
    else { printf("  [X] FAIL\n"); fail++; }
    
    // Test 5: C2H multi-beat
    printf("\nTest 5: C2H 24 bytes\n");
    reset_state();
    local_mem[0x400] = 0x1111111111111111;
    local_mem[0x408] = 0x2222222222222222;
    local_mem[0x410] = 0x3333333333333333;
    reg_write(0x10, 0x5000);
    reg_write(0x18, 0x400);
    reg_write(0x20, 24);
    reg_write(0x00, 0x3);
    ok = wait_done() &&
         host_mem[0x5000] == 0x1111111111111111 &&
         host_mem[0x5008] == 0x2222222222222222 &&
         host_mem[0x5010] == 0x3333333333333333;
    if (ok) { printf("  [OK] PASS\n"); pass++; }
    else { printf("  [X] FAIL\n"); fail++; }
    
    printf("\n=== Results: %d passed, %d failed ===\n", pass, fail);
    delete dut;
    return fail > 0 ? 1 : 0;
}
