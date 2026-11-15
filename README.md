# PCIe-to-AXI FPGA Bridge

Intel R-Tile PCIe Gen5 x16 to AXI-Lite bridge with DMA engine for Agilex 7 FPGA.

## Architecture

```
Host CPU ──PCIe Gen5 x16──► R-Tile IP ──► pcie_axi_bridge ──► Address Decoder
                                               │                    │
                                               │              ┌─────┴─────┐
                                               │              ▼           ▼
                                               │         dma_engine    axi_ram
                                               │              │        (4KB)
                                               │              └─────────►│
                                               │                   (DMA path)
                                               │
                                               └──► PCIe TLP (DMA MRd/MWr/MSI-X)
```

## Memory Map (BAR0)

| Address       | Region     | Description                   |
|---------------|------------|-------------------------------|
| 0x0000-0x0FFF | DMA Engine | Control, status, DMA config   |
| 0x1000-0x1FFF | Local RAM  | 4KB buffer (host + DMA access)|

### DMA Registers (0x0000)

| Offset | Name       | Access | Description                                |
|--------|------------|--------|--------------------------------------------|
| 0x00   | ctrl       | R/W    | [0] start, [1] dir (0=H2C, 1=C2H), [2] irq_en |
| 0x08   | status     | RO     | [0] busy, [1] done                         |
| 0x10   | host_addr  | R/W    | 64-bit host memory address                 |
| 0x18   | local_addr | R/W    | 32-bit local RAM address                   |
| 0x20   | length     | R/W    | Transfer length in bytes                   |

### MSI-X Interrupts

When irq_en (ctrl[2]) is set and DMA completes, an MSI-X interrupt is generated.
The MSI-X address defaults to 0xFEE00000 (x86 APIC). On real hardware, the OS
configures this during PCIe enumeration.

## Quick Start

### Simulation
```bash
cd tb && ./run.sh
```

### FPGA Build
```bash
./build_fpga.sh 0x01
```

### Hardware Test
```bash
# Program FPGA
quartus_pgm -c 1 -m JTAG -o "p;*.sof"

# Bind to VFIO
PCI=0000:b1:00.0
echo vfio-pci > /sys/bus/pci/devices/$PCI/driver_override
echo $PCI > /sys/bus/pci/drivers/vfio-pci/bind

# Run test
sudo ./host/bin/test_bridge $PCI $(basename $(readlink /sys/bus/pci/devices/$PCI/iommu_group))
```

## DMA Example

### C2H (FPGA → Host)
```c
write64(0x1000, 0xCAFEBABE);  // Data in RAM
write64(0x0010, host_phys);    // host_addr (64-bit)
write64(0x0018, 0x1000);       // local_addr
write64(0x0020, 8);            // length
write64(0x0000, 0x3);          // start + C2H
while (read64(0x0008) & 1);    // wait
```

### H2C (Host → FPGA)
```c
write64(0x0010, host_phys);    // host_addr (64-bit)
write64(0x0018, 0x1000);       // local_addr
write64(0x0020, 8);            // length
write64(0x0000, 0x1);          // start + H2C
while (read64(0x0008) & 1);    // wait
```

## Project Structure

```
rtl/
├── top.sv             # System top
├── pcie_axi_bridge.sv # Bidirectional PCIe↔AXI bridge + MSI-X
├── dma_engine.sv      # DMA controller (H2C + C2H)
├── axi_ram.sv         # 4KB SRAM (M20K)
├── rtile_crdt.sv      # Credit manager
└── rtile_pkg.sv       # Types, constants

tb/
├── tb_rtile.cpp       # Integration test (5 tests)
├── tb_dma.cpp         # DMA unit test
├── tb_axi_ram.cpp     # RAM unit test
└── run.sh

fpga/
├── axi_bridge_hw.sv   # Qsys wrapper (R-Tile 4-seg to 1-seg)
├── bridge_hw.tcl      # Platform Designer script
├── pcie_bridge.tcl    # R-Tile IP config
├── pcie_bridge.qsf    # Quartus settings
└── pcie_bridge.sdc    # Timing constraints

host/
├── main.cpp           # Linux VFIO test app
├── pcie-util.cpp      # VFIO helpers
├── pcie-util.h        # VFIO helpers header
└── build.sh           # Build script
```

## License

MIT
