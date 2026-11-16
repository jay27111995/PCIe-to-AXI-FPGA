# PCIe-to-AXI FPGA Bridge

Intel R-Tile PCIe Gen5 x16 to AXI-Lite bridge with DMA engine for Agilex 7 FPGA.

## Architecture

```
Host CPU --PCIe Gen5 x16--> R-Tile IP --> pcie_axi_bridge --> Address Decoder
                                               |                    |
                                               |              +-----+-----+
                                               |              |     |     |
                                               |              v     v     v
                                               |           DMA   RAM   Debug
                                               |          Regs  (4KB) Sniffer
                                               |
                                               +--> PCIe TLP (Host MRd/MWr/MSI-X)
```

## Memory Map (BAR0)

| Address       | Region       | Description                     |
|---------------|--------------|----------------------------------|
| 0x0000-0x0FFF | DMA Engine   | Control, status, DMA config      |
| 0x1000-0x1FFF | Local RAM    | 4KB buffer (host + DMA access)   |
| 0x2000-0x2FFF | Debug Sniffer| PCIe TLP capture registers       |

### DMA Registers (0x0000)

| Offset | Name       | Access | Description                                |
|--------|------------|--------|--------------------------------------------|
| 0x00   | ctrl       | R/W    | [0] start, [1] dir (0=H2C, 1=C2H), [2] irq_en |
| 0x08   | status     | RO     | [0] busy, [1] done                         |
| 0x10   | host_addr  | R/W    | 64-bit host memory address                 |
| 0x18   | local_addr | R/W    | 32-bit local RAM address                   |
| 0x20   | length     | R/W    | Transfer length in bytes                   |

### Debug Sniffer Registers (0x2000)

| Offset | Name           | Access | Description                              |
|--------|----------------|--------|------------------------------------------|
| 0x00   | status         | RO     | [0] rx_seen, [1] tx_seen, [7:4] tx_state |
| 0x04   | rx_count       | RO     | Number of RX TLPs captured               |
| 0x08   | tx_count       | RO     | Number of TX TLPs captured               |
| 0x0C   | control        | WO     | [0] clear counts                         |
| 0x10-1C| last_rx_hdr    | RO     | Last RX TLP header (4 DWs)               |
| 0x20-24| last_rx_data   | RO     | Last RX TLP data (2 DWs)                 |
| 0x28-34| last_tx_hdr    | RO     | Last TX TLP header (4 DWs)               |
| 0x38-3C| last_tx_data   | RO     | Last TX TLP data (2 DWs)                 |
| 0x40-44| cycle_count    | RO     | Free-running cycle counter (64-bit)      |
| 0x48   | rx_ready_cnt   | RO     | Cycles rx_st_ready was high              |
| 0x4C   | tx_ready_cnt   | RO     | Cycles tx_st_ready was high              |

## Quick Start

### Simulation

Run all tests (requires Verilator):
```bash
cd tb && ./run.sh           # Integration test (top.sv)
cd tb && ./run_bridge.sh    # Bridge unit test
cd tb && ./run_sniffer.sh   # Sniffer unit test
cd tb && ./run_axi_ram.sh   # RAM unit test
```

### FPGA Build
```bash
./build_fpga.sh 0x05  # Revision ID
```

### Hardware Test
```bash
# Program FPGA
quartus_pgm -c 1 -m JTAG -o "p;*.sof"

# Bind to VFIO
PCI=0000:b1:00.0
echo vfio-pci > /sys/bus/pci/devices/$PCI/driver_override
echo $PCI > /sys/bus/pci/drivers/vfio-pci/bind

# Run tests
cd host && ./build.sh
sudo ./test_bridge $PCI
sudo ./dump_debug $PCI   # Read debug sniffer
```

## Project Structure

```
rtl/
  top.sv              # System top with address decoder
  pcie_axi_bridge.sv  # Bidirectional PCIe<->AXI bridge
  pcie_sniffer.sv     # Debug TLP capture module
  dma_engine.sv       # DMA controller (H2C + C2H)
  axi_ram.sv          # 4KB SRAM (M20K)
  rtile_crdt.sv       # Credit manager
  rtile_pkg.sv        # Types and constants

tb/
  tb_rtile.cpp        # Integration test (6 tests)
  tb_pcie_axi_bridge.cpp  # Bridge unit test (5 tests)
  tb_pcie_sniffer.cpp     # Sniffer unit test (6 tests)
  tb_dma.cpp          # DMA unit test
  tb_axi_ram.cpp      # RAM unit test
  run.sh              # Run integration test
  run_bridge.sh       # Run bridge test
  run_sniffer.sh      # Run sniffer test
  run_axi_ram.sh      # Run RAM test

fpga/
  axi_bridge_hw.sv    # Qsys wrapper (R-Tile 4-seg to 1-seg)
  bridge_hw.tcl       # Platform Designer component script
  pcie_bridge.tcl     # R-Tile IP configuration
  pcie_bridge.qsf     # Quartus project settings
  pcie_bridge.sdc     # Timing constraints

host/
  main.cpp            # Linux VFIO test application
  dump_debug.cpp      # Debug sniffer dump utility
  pcie-util.cpp       # VFIO helper functions
  pcie-util.h         # VFIO helper header
  build.sh            # Build script
```

## DMA Example

### C2H (FPGA to Host)
```c
write64(0x1000, 0xCAFEBABE);  // Data in RAM
write64(0x0010, host_phys);   // host_addr (64-bit)
write64(0x0018, 0x1000);      // local_addr
write64(0x0020, 8);           // length
write64(0x0000, 0x3);         // start + C2H
while (read64(0x0008) & 1);   // wait
```

### H2C (Host to FPGA)
```c
write64(0x0010, host_phys);   // host_addr (64-bit)
write64(0x0018, 0x1000);      // local_addr
write64(0x0020, 8);           // length
write64(0x0000, 0x1);         // start + H2C
while (read64(0x0008) & 1);   // wait
```

## License

MIT
