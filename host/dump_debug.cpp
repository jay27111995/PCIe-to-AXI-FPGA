#include "pcie-util.h"
#include <cstdio>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pcie_device>\n", argv[0]);
        printf("Dumps debug registers from PCIe-AXI bridge\n");
        return 1;
    }

    PCIe::Function pf(argv[1]);
    auto& bar = *pf.BARs[0];
    bar.map();

    printf("=== PCIe-AXI Bridge Debug Dump ===\n");
    printf("Device: %s\n\n", argv[1]);

    // Status register
    uint32_t status = bar.read32(0x2000);
    printf("Status (0x2000):     0x%08x\n", status);
    printf("  rx_seen:           %d\n", status & 1);
    printf("  tx_seen:           %d\n", (status >> 1) & 1);
    printf("  tx_state:          %d", (status >> 4) & 0xF);
    switch ((status >> 4) & 0xF) {
        case 0: printf(" (IDLE)\n"); break;
        case 1: printf(" (BAR_WR_ADDR)\n"); break;
        case 2: printf(" (BAR_WR_RESP)\n"); break;
        case 3: printf(" (BAR_RD_ADDR)\n"); break;
        case 4: printf(" (BAR_RD_DATA)\n"); break;
        case 5: printf(" (BAR_CPL)\n"); break;
        case 6: printf(" (DMA_MRD)\n"); break;
        case 7: printf(" (DMA_MWR)\n"); break;
        case 8: printf(" (MSIX)\n"); break;
        case 9: printf(" (SEND)\n"); break;
        default: printf(" (UNKNOWN)\n"); break;
    }
    uint8_t rx_type = (status >> 8) & 0xFF;
    printf("  last_rx_type:      0x%02x (fmt=%d, type=%d)\n", 
           rx_type, (rx_type >> 5) & 0x7, rx_type & 0x1F);

    printf("\nCounters:\n");
    printf("  RX TLP count:      %u\n", bar.read32(0x2004));
    printf("  TX TLP count:      %u\n", bar.read32(0x2008));
    printf("  RX ready cycles:   %u\n", bar.read32(0x2048));
    printf("  TX ready cycles:   %u\n", bar.read32(0x204C));
    printf("  Total cycles:      %u (lo)\n", bar.read32(0x2040));

    printf("\nLast RX TLP (from host):\n");
    uint32_t rx_dw3 = bar.read32(0x201C);
    uint32_t rx_dw2 = bar.read32(0x2018);
    uint32_t rx_dw1 = bar.read32(0x2014);
    uint32_t rx_dw0 = bar.read32(0x2010);
    printf("  Header: %08x %08x %08x %08x\n", rx_dw3, rx_dw2, rx_dw1, rx_dw0);
    printf("    Fmt:     %d\n", (rx_dw3 >> 29) & 0x7);
    printf("    Type:    0x%02x\n", (rx_dw3 >> 24) & 0x1F);
    printf("    Length:  %d DW\n", rx_dw3 & 0x3FF);
    printf("    ReqID:   0x%04x\n", (rx_dw2 >> 16) & 0xFFFF);
    printf("    Tag:     0x%02x\n", (rx_dw2 >> 8) & 0xFF);
    printf("    FBE:     0x%x\n", rx_dw2 & 0xF);
    printf("    LBE:     0x%x\n", (rx_dw2 >> 4) & 0xF);
    printf("    Addr:    0x%08x\n", rx_dw0);
    printf("  Data:   0x%08x_%08x\n", bar.read32(0x2024), bar.read32(0x2020));

    printf("\nLast TX TLP (to host):\n");
    uint32_t tx_dw3 = bar.read32(0x2034);
    uint32_t tx_dw2 = bar.read32(0x2030);
    uint32_t tx_dw1 = bar.read32(0x202C);
    uint32_t tx_dw0 = bar.read32(0x2028);
    printf("  Header: %08x %08x %08x %08x\n", tx_dw3, tx_dw2, tx_dw1, tx_dw0);
    printf("    Fmt:     %d\n", (tx_dw3 >> 29) & 0x7);
    printf("    Type:    0x%02x\n", (tx_dw3 >> 24) & 0x1F);
    printf("    Length:  %d DW\n", tx_dw3 & 0x3FF);
    if (((tx_dw3 >> 24) & 0x1F) == 0x0A) {  // CplD
        printf("    CplID:   0x%04x\n", (tx_dw2 >> 16) & 0xFFFF);
        printf("    Status:  %d\n", (tx_dw2 >> 13) & 0x7);
        printf("    ByteCnt: %d\n", tx_dw2 & 0xFFF);
        printf("    ReqID:   0x%04x\n", (tx_dw1 >> 16) & 0xFFFF);
        printf("    Tag:     0x%02x\n", (tx_dw1 >> 8) & 0xFF);
        printf("    LowAddr: 0x%02x\n", tx_dw1 & 0x7F);
    }
    printf("  Data:   0x%08x_%08x\n", bar.read32(0x203C), bar.read32(0x2038));

    // Quick sanity check
    printf("\n=== Quick Check ===\n");
    if (bar.read32(0x2004) == 0) {
        printf("WARNING: No RX TLPs seen! Bridge may not be receiving from R-Tile.\n");
    }
    if ((status & 1) == 0) {
        printf("WARNING: rx_seen=0 - Bridge hasn't processed any RX TLPs.\n");
    }
    if (((status >> 4) & 0xF) != 0) {
        printf("WARNING: tx_state=%d - Bridge stuck in non-IDLE state!\n", (status >> 4) & 0xF);
    }

    return 0;
}
