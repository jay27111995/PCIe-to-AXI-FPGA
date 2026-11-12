# PCIe-to-AXI FPGA Bridge

Intel R-Tile PCIe Gen5 x16 to AXI-Lite bridge with DMA engine for Agilex 7 FPGA.

## Architecture

```
Host CPU ──PCIe Gen5 x16──► R-Tile IP ──► rtile_top ──► Address Decoder
                                              │              │
                                              │         ┌────┴────┐
                                              │         ▼         ▼
                                              │    dma_engine   axi_ram
                                              │         │       (4KB)
                                              │         └────────►│
                                              │              (DMA path)
                                              │
                                              └──► PCIe TLP (DMA MRd/MWr)
```

## Memory Map (BAR0)

| Address       | Region     | Description                   |
|---------------|------------|-------------------------------|
| 0x0000-0x0FFF | DMA Engine | Control, status, DMA config   |
| 0x1000-0x1FFF | Local RAM  | 4KB buffer (host + DMA access)|

### DMA Registers (0x0000)

| Offset | Name       | Access | Description                                |
|--------|------------|--------|--------------------------------------------|
| 0x00   | ctrl       | R/W    | [0] start, [1] dir (0=H2C, 1=C2H), [2] irq |
| 0x08   | status     | RO     | [0] busy, [1] done, [2] error              |
| 0x10   | host_addr  | R/W    | 64-bit host memory address                 |
| 0x18   | local_addr | R/W    | 32-bit local RAM address                   |
| 0x20   | length     | R/W    | Transfer length in bytes                   |

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
├── rtile_pkg.sv      # Types, constants
├── rtile_top.sv      # TLP ↔ AXI bridge
├── rtile_crdt.sv     # Credit manager
├── dma_engine.sv     # DMA controller
├── axi_ram.sv        # 4KB SRAM (M20K)
└── pcie_axi_top.sv   # System top

tb/
├── tb_rtile.cpp      # Integration test
├── tb_axi_ram.cpp    # RAM unit test
└── run.sh

fpga/                 # Quartus build files
host/                 # Linux VFIO test app
```

## License

MIT
