# pcieBasic

Minimal PCIe DMA example using Intel MCDMA (BAS/BAM).

## Structure

```
├── rtl/
│   ├── axi_core_hw.sv    # AXI master (BAS) + AXI-Lite slave (BAM)
│   ├── axi_core_hw.tcl   # Platform Designer component
│   └── dma_core.sv       # Simple DMA engine
├── sw/
│   ├── build_sim.sh      # Verilator build script
│   └── sim_dma.cpp       # Simulation testbench
├── host/
│   ├── build.sh          # Host app build script
│   ├── main.cpp          # Example host application
│   ├── pcie-util.cpp     # VFIO PCIe utilities
│   └── pcie-util.h
└── build_fpga.sh         # FPGA build script
```

## DMA Registers (BAR0)

| Offset | Register | Description |
|--------|----------|-------------|
| 0x00 | RESET | Write 1 to soft reset (self-clearing) |
| 0x08 | SRC_ADDR | Source address in host memory (64-bit) |
| 0x10 | DST_ADDR | Destination address in host memory (64-bit) |
| 0x18 | LEN | Transfer length in 64-bit words |
| 0x20 | CTRL | [0] GO (write 1 to start), [1] BUSY (read) |

## Usage

### Host Software
```c
bar->write64(0x00, 1);         // Reset
bar->write64(0x08, src_addr);  // Source
bar->write64(0x10, dst_addr);  // Destination  
bar->write64(0x18, length);    // Length (qwords)
bar->write64(0x20, 1);         // Start DMA
while (bar->read64(0x20) & 2); // Wait for completion
```

### Simulation
```bash
cd sw
./build_sim.sh
```

### FPGA Build
```bash
./build_fpga.sh
```

## Architecture

```
Host Memory <---> BAS <---> axi_core_hw <---> dma_core
                  BAM <--->      |
                              BAR access
```

- **BAM**: Translates host BAR reads/writes to AXI-Lite
- **BAS**: Translates AXI master transactions to PCIe TLPs for host memory access
