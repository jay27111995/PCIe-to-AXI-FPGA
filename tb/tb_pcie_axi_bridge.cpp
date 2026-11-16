//-----------------------------------------------------------------------------
// tb_pcie_axi_bridge.cpp - Standalone testbench for pcie_axi_bridge
//
// Tests the PCIe-AXI bridge in isolation:
//   1. BAR read (PCIe MRd -> AXI read -> CplD)
//   2. BAR write (PCIe MWr -> AXI write)
//   3. Host memory read (AXI master read -> PCIe MRd -> CplD -> AXI read data)
//   4. Host memory write (AXI master write -> PCIe MWr)
//   5. MSI-X interrupt generation
//-----------------------------------------------------------------------------
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vpcie_axi_bridge.h"
#include <cstdio>
#include <cstdint>
#include <queue>

Vpcie_axi_bridge* dut;
VerilatedVcdC* trace;
int cycle = 0;

// Simulated AXI slave memory (what host sees via BAR)
uint64_t axi_slave_mem[256];

// Simulated host memory (what FPGA accesses via AXI master)
uint64_t host_mem[256];

// Pending completions to send back
struct PendingCpl {
    uint8_t tag;
    uint64_t data;
    uint16_t rid;
};
std::queue<PendingCpl> pending_cpls;

void tick() {
    dut->clk = 0;
    dut->eval();
    if (trace) trace->dump(cycle * 10);
    
    dut->clk = 1;
    dut->eval();
    if (trace) trace->dump(cycle * 10 + 5);
    
    cycle++;
}

void reset() {
    dut->rst_n = 0;
    dut->rx_st_hvalid = 0;
    dut->rx_st_dvalid = 0;
    dut->rx_st_sop = 0;
    dut->rx_st_eop = 0;
    dut->tx_st_ready = 1;
    dut->link_up = 1;
    dut->ltssm_state = 0x11;  // L0
    
    // AXI slave responses (directly connected)
    dut->s_axi_awready = 1;
    dut->s_axi_wready = 1;
    dut->s_axi_bvalid = 0;
    dut->s_axi_bresp = 0;
    dut->s_axi_arready = 1;
    dut->s_axi_rvalid = 0;
    dut->s_axi_rresp = 0;
    dut->s_axi_rdata = 0;
    
    // AXI master requests (directly connected)
    dut->m_axi_awaddr = 0;
    dut->m_axi_awvalid = 0;
    dut->m_axi_wdata = 0;
    dut->m_axi_wstrb = 0xFF;
    dut->m_axi_wvalid = 0;
    dut->m_axi_bready = 1;
    dut->m_axi_araddr = 0;
    dut->m_axi_arvalid = 0;
    dut->m_axi_rready = 1;
    
    // MSI-X
    dut->msix_valid = 0;
    dut->msix_addr = 0;
    dut->msix_data = 0;
    
    // Credits (initialize)
    dut->tx_hcrdt_init = 0;
    dut->tx_hcrdt_update = 0;
    dut->tx_hcrdt_update_cnt = 0;
    dut->tx_dcrdt_init = 0;
    dut->tx_dcrdt_update = 0;
    dut->tx_dcrdt_update_cnt = 0;
    
    for (int i = 0; i < 10; i++) tick();
    dut->rst_n = 1;
    for (int i = 0; i < 5; i++) tick();
}

// Build a PCIe MRd TLP header (3DW for addresses < 4GB)
void send_mrd32(uint32_t addr, uint8_t tag, uint16_t rid = 0x0100) {
    // Wait for rx_st_ready
    while (!dut->rx_st_ready) tick();
    
    // DW0: Fmt=000 (3DW no data), Type=00000 (MRd), Length=2
    uint32_t dw0 = (0b000 << 29) | (0b00000 << 24) | 2;
    // DW1: Requester ID, Tag, First/Last BE
    uint32_t dw1 = (rid << 16) | (tag << 8) | 0xFF;
    // DW2: Address (32-bit)
    uint32_t dw2 = addr & ~3u;
    
    dut->rx_st_hdr[0] = dw2;
    dut->rx_st_hdr[1] = dw1;
    dut->rx_st_hdr[2] = dw0;
    dut->rx_st_hdr[3] = 0;
    dut->rx_st_data[0] = 0;
    dut->rx_st_sop = 1;
    dut->rx_st_eop = 1;
    dut->rx_st_hvalid = 1;
    dut->rx_st_dvalid = 0;
    dut->rx_st_bar = 0;
    
    tick();
    
    dut->rx_st_hvalid = 0;
    dut->rx_st_sop = 0;
    dut->rx_st_eop = 0;
}

// Build a PCIe MWr TLP header (3DW for addresses < 4GB)
void send_mwr32(uint32_t addr, uint64_t data) {
    while (!dut->rx_st_ready) tick();
    
    // DW0: Fmt=010 (3DW with data), Type=00000 (MWr), Length=2
    uint32_t dw0 = (0b010 << 29) | (0b00000 << 24) | 2;
    // DW1: Requester ID, Tag, First/Last BE
    uint32_t dw1 = (0x0100 << 16) | (0 << 8) | 0xFF;
    // DW2: Address (32-bit)
    uint32_t dw2 = addr & ~3u;
    
    dut->rx_st_hdr[0] = dw2;
    dut->rx_st_hdr[1] = dw1;
    dut->rx_st_hdr[2] = dw0;
    dut->rx_st_hdr[3] = 0;
    dut->rx_st_data[0] = data;
    dut->rx_st_sop = 1;
    dut->rx_st_eop = 1;
    dut->rx_st_hvalid = 1;
    dut->rx_st_dvalid = 1;
    dut->rx_st_bar = 0;
    
    tick();
    
    dut->rx_st_hvalid = 0;
    dut->rx_st_dvalid = 0;
    dut->rx_st_sop = 0;
    dut->rx_st_eop = 0;
}

// Send a CplD back (simulating host responding to FPGA's MRd)
void send_cpld(uint8_t tag, uint64_t data, uint16_t cpl_rid = 0xb400) {
    while (!dut->rx_st_ready) tick();
    
    // DW0: Fmt=010 (3DW with data), Type=01010 (CplD), Length=2
    uint32_t dw0 = (0b010 << 29) | (0b01010 << 24) | 2;
    // DW1: Completer ID, Status=0, Byte Count=8
    uint32_t dw1 = (0x0000 << 16) | (0 << 13) | 8;
    // DW2: Requester ID, Tag, Lower Address
    uint32_t dw2 = (cpl_rid << 16) | (tag << 8) | 0;
    
    dut->rx_st_hdr[0] = dw2;
    dut->rx_st_hdr[1] = dw1;
    dut->rx_st_hdr[2] = dw0;
    dut->rx_st_hdr[3] = 0;
    dut->rx_st_data[0] = data;
    dut->rx_st_sop = 1;
    dut->rx_st_eop = 1;
    dut->rx_st_hvalid = 1;
    dut->rx_st_dvalid = 1;
    dut->rx_st_bar = 0;
    
    tick();
    
    dut->rx_st_hvalid = 0;
    dut->rx_st_dvalid = 0;
    dut->rx_st_sop = 0;
    dut->rx_st_eop = 0;
}

// AXI slave behavior (responds to bridge's AXI slave interface)
void axi_slave_tick() {
    static int read_delay = 0;
    static uint32_t read_addr = 0;
    
    // Handle write
    if (dut->s_axi_awvalid && dut->s_axi_wvalid) {
        uint32_t addr = dut->s_axi_awaddr;
        uint64_t data = dut->s_axi_wdata;
        axi_slave_mem[addr / 8] = data;
        // printf("  AXI Slave Write: addr=0x%x data=0x%lx\n", addr, data);
    }
    
    // Handle write response
    static bool bvalid_pending = false;
    if (dut->s_axi_bready && bvalid_pending) {
        dut->s_axi_bvalid = 0;
        bvalid_pending = false;
    }
    if (dut->s_axi_awvalid && dut->s_axi_wvalid && dut->s_axi_awready) {
        bvalid_pending = true;
        dut->s_axi_bvalid = 1;
        dut->s_axi_bresp = 0;  // OKAY
    }
    
    // Handle read
    if (dut->s_axi_arvalid && dut->s_axi_arready) {
        read_addr = dut->s_axi_araddr;
        read_delay = 2;  // Simulate some latency
    }
    
    if (read_delay > 0) {
        read_delay--;
        if (read_delay == 0) {
            dut->s_axi_rdata = axi_slave_mem[read_addr / 8];
            dut->s_axi_rvalid = 1;
            dut->s_axi_rresp = 0;  // OKAY
            // printf("  AXI Slave Read: addr=0x%x data=0x%lx\n", read_addr, dut->s_axi_rdata);
        }
    }
    
    if (dut->s_axi_rvalid && dut->s_axi_rready) {
        dut->s_axi_rvalid = 0;
    }
}

// Wait for and capture TX TLP
bool wait_tx_tlp(int timeout = 100) {
    for (int i = 0; i < timeout; i++) {
        axi_slave_tick();
        tick();
        if (dut->tx_st_hvalid && dut->tx_st_sop) {
            return true;
        }
    }
    return false;
}

//=============================================================================
// Test Cases
//=============================================================================

bool test_bar_write() {
    printf("Test 1: BAR Write (Host -> FPGA)\n");
    
    axi_slave_mem[0x100/8] = 0;
    send_mwr32(0x100, 0xDEADBEEF12345678ULL);
    
    // Wait for AXI write to complete
    for (int i = 0; i < 20; i++) {
        axi_slave_tick();
        tick();
    }
    
    if (axi_slave_mem[0x100/8] == 0xDEADBEEF12345678ULL) {
        printf("  [OK] BAR write successful\n");
        return true;
    } else {
        printf("  [X] BAR write failed: got 0x%lx\n", axi_slave_mem[0x100/8]);
        return false;
    }
}

bool test_bar_read() {
    printf("Test 2: BAR Read (Host <- FPGA)\n");
    
    axi_slave_mem[0x200/8] = 0xCAFEBABE87654321ULL;
    send_mrd32(0x200, 0x42, 0x0100);
    
    // Wait for CplD
    if (!wait_tx_tlp(50)) {
        printf("  [X] Timeout waiting for CplD\n");
        return false;
    }
    
    // Check TLP type
    uint32_t dw0 = dut->tx_st_hdr[2];
    uint8_t fmt = (dw0 >> 29) & 0x7;
    uint8_t type = (dw0 >> 24) & 0x1F;
    uint64_t data = dut->tx_st_data[0];
    
    if (fmt == 0b010 && type == 0b01010) {  // CplD
        if (data == 0xCAFEBABE87654321ULL) {
            printf("  [OK] BAR read returned correct data\n");
            return true;
        } else {
            printf("  [X] BAR read wrong data: 0x%lx\n", data);
            return false;
        }
    } else {
        printf("  [X] Wrong TLP type: fmt=%d type=%d\n", fmt, type);
        return false;
    }
}

bool test_host_mem_write() {
    printf("Test 3: Host Memory Write (FPGA -> Host)\n");
    
    // Issue AXI master write request
    dut->m_axi_awaddr = 0x1000;
    dut->m_axi_awvalid = 1;
    dut->m_axi_wdata = 0xABCD1234FEDC5678ULL;
    dut->m_axi_wvalid = 1;
    
    tick();
    
    // Wait for bridge to accept
    while (dut->m_axi_awvalid && !dut->m_axi_awready) tick();
    dut->m_axi_awvalid = 0;
    dut->m_axi_wvalid = 0;
    
    // Wait for MWr TLP
    if (!wait_tx_tlp(50)) {
        printf("  [X] Timeout waiting for MWr TLP\n");
        return false;
    }
    
    // Check TLP type
    uint32_t dw0 = dut->tx_st_hdr[2];
    uint8_t fmt = (dw0 >> 29) & 0x7;
    uint8_t type = (dw0 >> 24) & 0x1F;
    uint64_t data = dut->tx_st_data[0];
    
    // Check address from header
    uint64_t addr = ((uint64_t)dut->tx_st_hdr[1] << 32) | (dut->tx_st_hdr[0] & ~3ULL);
    
    if ((fmt == 0b011 || fmt == 0b010) && type == 0b00000) {  // MWr
        if (data == 0xABCD1234FEDC5678ULL && (addr & 0xFFFF) == 0x1000) {
            printf("  [OK] Host memory write TLP generated\n");
            
            // Wait for B response
            for (int i = 0; i < 20; i++) {
                tick();
                if (dut->m_axi_bvalid) break;
            }
            if (dut->m_axi_bvalid) {
                printf("  [OK] AXI B response received\n");
                return true;
            }
        }
    }
    printf("  [X] Wrong TLP: fmt=%d type=%d addr=0x%lx data=0x%lx\n", fmt, type, addr, data);
    return false;
}

bool test_host_mem_read() {
    printf("Test 4: Host Memory Read (FPGA <- Host)\n");
    
    // Issue AXI master read request
    dut->m_axi_araddr = 0x2000;
    dut->m_axi_arvalid = 1;
    
    tick();
    
    // Wait for bridge to accept
    while (dut->m_axi_arvalid && !dut->m_axi_arready) tick();
    dut->m_axi_arvalid = 0;
    
    // Wait for MRd TLP
    if (!wait_tx_tlp(50)) {
        printf("  [X] Timeout waiting for MRd TLP\n");
        return false;
    }
    
    // Check TLP type and capture tag
    uint32_t dw0 = dut->tx_st_hdr[2];
    uint32_t dw1 = dut->tx_st_hdr[1];
    uint8_t fmt = (dw0 >> 29) & 0x7;
    uint8_t type = (dw0 >> 24) & 0x1F;
    uint8_t tag = (dw1 >> 8) & 0xFF;
    
    if ((fmt == 0b001 || fmt == 0b000) && type == 0b00000) {  // MRd
        printf("  [OK] MRd TLP generated, tag=%d\n", tag);
        
        // Simulate host responding with CplD
        tick(); tick();
        send_cpld(tag, 0x9999888877776666ULL, 0xb400);
        
        // Wait for AXI R response
        for (int i = 0; i < 30; i++) {
            tick();
            if (dut->m_axi_rvalid) break;
        }
        
        if (dut->m_axi_rvalid && dut->m_axi_rdata == 0x9999888877776666ULL) {
            printf("  [OK] AXI R data received correctly\n");
            return true;
        } else {
            printf("  [X] Wrong R data: 0x%lx\n", (uint64_t)dut->m_axi_rdata);
        }
    } else {
        printf("  [X] Wrong TLP type: fmt=%d type=%d\n", fmt, type);
    }
    return false;
}

bool test_msix() {
    printf("Test 5: MSI-X Interrupt\n");
    
    dut->msix_valid = 1;
    dut->msix_addr = 0xFEE00000ULL;
    dut->msix_data = 0x12345678;
    
    // Wait for bridge to generate MWr
    if (!wait_tx_tlp(50)) {
        printf("  [X] Timeout waiting for MSI-X MWr\n");
        return false;
    }
    
    dut->msix_valid = 0;
    
    // Check TLP
    uint32_t dw0 = dut->tx_st_hdr[2];
    uint8_t fmt = (dw0 >> 29) & 0x7;
    uint8_t type = (dw0 >> 24) & 0x1F;
    uint32_t data = dut->tx_st_data[0] & 0xFFFFFFFF;
    
    if ((fmt == 0b011 || fmt == 0b010) && type == 0b00000) {  // MWr
        if (data == 0x12345678) {
            printf("  [OK] MSI-X TLP generated correctly\n");
            return true;
        }
    }
    printf("  [X] Wrong MSI-X TLP: fmt=%d type=%d data=0x%x\n", fmt, type, data);
    return false;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    
    dut = new Vpcie_axi_bridge;
    trace = new VerilatedVcdC;
    dut->trace(trace, 99);
    trace->open("tb_pcie_axi_bridge.vcd");
    
    printf("=== PCIe-AXI Bridge Testbench ===\n\n");
    
    reset();
    
    int passed = 0;
    int total = 5;
    
    if (test_bar_write()) passed++;
    reset();
    
    if (test_bar_read()) passed++;
    reset();
    
    if (test_host_mem_write()) passed++;
    reset();
    
    if (test_host_mem_read()) passed++;
    reset();
    
    if (test_msix()) passed++;
    
    printf("\n=== Results: %d/%d tests passed ===\n", passed, total);
    
    trace->close();
    delete dut;
    
    return (passed == total) ? 0 : 1;
}
