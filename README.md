# PCIe-to-AXI FPGA Bridge

Intel R-Tile PCIe Gen5 x16 to AXI-Lite bridge with DMA engine for Agilex 7 FPGA.

## Features

- PCIe Gen5 x16 endpoint (32 GT/s per lane)
- 64KB BAR0 address space
- AXI-Lite register interface
- 4KB local RAM
- DMA engine (H2C and C2H)

## Architecture

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                         Intel R-Tile PCIe IP                                │
│                    (intel_pcie_axi_mcdma, Gen5 x16)                        │
│                         Handles TLP ↔ AXI                                   │
└────────────────────────────────┬────────────────────────────────────────────┘
                                 │ AXI-Lite
                                 ▼
┌─────────────────────────────────────────────────────────────────────────────┐
│                           axi_bridge_hw                                     │
│  ┌─────────────────────────────────────────────────────────────────────┐   │
│  │                      Address Decoder                                  │   │
│  │        [13:12] = 00 → regs, 01 → dma, 10 → ram                       │   │
│  └──────────────────┬─────────────────┬─────────────────┬───────────────┘   │
│                     │                 │                 │                    │
│  ┌─────────────────┐│ ┌──────────────┐│ ┌──────────────┐│                   │
│  │   axi_regs      ││ │  dma_engine  ││ │   axi_ram    ││                   │
│  │ 0x0000-0x0FFF   ││ │ 0x1000-0x1FFF││ │ 0x2000-0x2FFF││                   │
│  │ scratch, status ││ │ H2C/C2H DMA  ││ │ 4KB local    ││                   │
│  └─────────────────┘│ └──────┬───────┘│ └──────────────┘│                   │
│                     │        │        │                  │                   │
└─────────────────────┼────────┼────────┼──────────────────┼───────────────────┘
                              │ AXI Master (DMA to host)
                              ▼
                         Host Memory
```

## Memory Map (BAR0, 64KB)

| Address Range     | Region       | Description                    |
|-------------------|--------------|--------------------------------|
| 0x0000 - 0x0FFF   | Control Regs | Scratch register, write count  |
| 0x1000 - 0x1FFF   | DMA Engine   | Control, status, addresses     |
| 0x2000 - 0x2FFF   | Local RAM    | 4KB SRAM                       |

### Control Registers (0x0000 base)

| Offset | Name        | Access | Description                |
|--------|-------------|--------|----------------------------|
| 0x00   | scratch     | R/W    | 64-bit scratch register    |
| 0x08   | write_count | RO     | Number of BAR writes       |

### DMA Registers (0x1000 base)

| Offset | Name         | Access | Description                                |
|--------|--------------|--------|--------------------------------------------|
| 0x00   | ctrl         | R/W    | [0] start, [1] dir (0=H2C, 1=C2H), [2] irq |
| 0x08   | status       | RO     | [0] busy, [1] done, [2] error              |
| 0x10   | host_addr_lo | R/W    | Host address bits [31:0]                   |
| 0x18   | host_addr_hi | R/W    | Host address bits [63:32]                  |
| 0x20   | local_addr   | R/W    | Local RAM address                          |
| 0x28   | length       | R/W    | Transfer length in bytes                   |

## Project Structure

```
PCIe-to-AXI-FPGA/
├── rtl/                    # RTL source files
│   ├── rtile_pkg.sv        # Types, constants
│   ├── rtile_crdt.sv       # Credit manager (simulation only)
│   ├── rtile_top.sv        # TLP bridge (simulation only)
│   ├── axi_regs.sv         # Control registers
│   ├── axi_ram.sv          # 4KB SRAM
│   ├── dma_engine.sv       # DMA controller
│   ├── pcie_axi_top.sv     # Simulation top-level
│   └── axi_bridge_hw.sv    # FPGA top-level (Qsys component)
│
├── tb/                     # Verilator testbench
│   ├── tb_rtile.cpp        # Main testbench
│   └── run.sh              # Build & run
│
├── fpga/                   # FPGA build files
│   ├── pcie_bridge.tcl     # Qsys system definition
│   ├── bridge_hw.tcl       # Custom component wrapper
│   ├── pcie_bridge.qsf     # Quartus settings & pins
│   └── pcie_bridge.sdc     # Timing constraints
│
├── host/                   # Linux host software
│   ├── include/
│   │   └── pcie_vfio.h     # VFIO interface header
│   ├── src/
│   │   ├── pcie_vfio.c     # VFIO BAR mapping
│   │   └── test_bridge.c   # Test program
│   └── build.sh            # Build script
│
├── build_fpga.sh           # FPGA build script
└── README.md               # This file
```

## Building

### Prerequisites

- **Simulation**: Verilator 5.024+
- **FPGA**: Intel Quartus Prime Pro 25.3+
- **Host**: Linux with VFIO/IOMMU support

### Simulation

```bash
cd tb
module load verilator/5.024  # if needed
./run.sh
```

Expected output:
```
=== PCIe-to-AXI Bridge + DMA Testbench ===

Test 1: Scratch register write/read
  ✓ PASS
Test 2: RAM write/read
  ✓ PASS
Test 3: DMA C2H (RAM → Host)
  ✓ PASS
Test 4: DMA H2C (Host → RAM)
  ✓ PASS

=== Results: 4 passed, 0 failed ===
```

### FPGA Build

```bash
# Load Quartus
source /path/to/quartus/settings64.sh

# Build with revision ID 0x01
./build_fpga.sh 0x01
```

This generates `pcie-bridge-revid-0x01-git-XXXXXX-md5-XXXX.sof`.

### Host Software

```bash
cd host
./build.sh
```

## Running on Hardware

### 1. Program FPGA

```bash
quartus_pgm -c 1 -m JTAG -o "p;pcie-bridge-revid-0x01-git-*.sof"
```

### 2. Rescan PCIe Bus

```bash
# Warm reboot may be needed, or:
echo 1 > /sys/bus/pci/rescan
```

### 3. Find Device

```bash
lspci | grep -i '1172\|altera\|fpga'
# Example: b1:00.0 Memory controller: Intel Corporation Device beef
```

### 4. Bind to VFIO

```bash
PCI=0000:b1:00.0

# Unbind from current driver
echo $PCI > /sys/bus/pci/devices/$PCI/driver/unbind 2>/dev/null || true

# Bind to vfio-pci
echo vfio-pci > /sys/bus/pci/devices/$PCI/driver_override
echo $PCI > /sys/bus/pci/drivers/vfio-pci/bind

# Find IOMMU group
GRP=$(basename $(readlink /sys/bus/pci/devices/$PCI/iommu_group))
echo "IOMMU group: $GRP"
```

### 5. Run Tests

```bash
sudo ./host/bin/test_bridge $PCI $GRP
```

Expected output:
```
=== PCIe-to-AXI Bridge Test ===
PCI: 0000:b1:00.0, IOMMU Group: 12
BAR0 mapped at 0x7f1234560000, size 65536 bytes

=== Test 1: Scratch Register ===
  Write: 0xcafebabe12345678
  Read:  0xcafebabe12345678
  ✓ PASS

=== Test 2: RAM Write/Read ===
  Write: 0x1111222233334444 @ 0x2000
  Read:  0x1111222233334444
  ✓ PASS

=== Test 3: RAM Pattern Test ===
  64/64 words verified
  ✓ PASS

=== Test 4: DMA Register Access ===
  DMA status: 0x0000000000000000
  host_lo: 0x0000000080000000 (expect 0x80000000)
  local:   0x0000000000002000 (expect 0x2000)
  length:  0x0000000000000040 (expect 0x40)
  ✓ PASS

=== Results: 0 tests failed ===
```

## DMA Usage

### C2H (Card to Host) - Read from FPGA RAM to host memory

```c
// Write data to local RAM first
write64(0x2000, 0x1234567890ABCDEF);

// Configure DMA
write64(0x1020, 0x2000);      // local_addr
write64(0x1010, host_phys);   // host_addr_lo  
write64(0x1018, 0);           // host_addr_hi
write64(0x1028, 8);           // length (bytes)
write64(0x1000, 0x3);         // ctrl: start=1, dir=C2H
```

### H2C (Host to Card) - Write from host memory to FPGA RAM

```c
// Configure DMA
write64(0x1020, 0x2000);      // local_addr
write64(0x1010, host_phys);   // host_addr_lo
write64(0x1018, 0);           // host_addr_hi
write64(0x1028, 8);           // length (bytes)
write64(0x1000, 0x1);         // ctrl: start=1, dir=H2C

// Wait for completion
while (read64(0x1008) & 0x1);  // Wait while busy
```

## Troubleshooting

### PCIe not detected
- Check FPGA is programmed and PERST# is released
- Try warm reboot or PCIe rescan
- Verify refclk (100MHz) is present

### VFIO bind fails
- Ensure IOMMU is enabled in BIOS and kernel (intel_iommu=on)
- Check all devices in IOMMU group are unbound

### BAR access hangs
- Check link is trained: `lspci -vv | grep LnkSta`
- Verify BAR is enabled: `lspci -vv | grep "Memory at"`

### DMA doesn't complete
- Ensure IOMMU mapping is set up for DMA buffer
- Check DMA status register for errors

## TODO

- [ ] Add interrupt support (MSI-X)
- [ ] Add scatter-gather DMA
- [ ] Expand to all 4 R-Tile segments
- [ ] Add performance counters

## License

MIT
