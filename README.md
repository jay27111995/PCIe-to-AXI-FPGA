# PCIe-to-AXI FPGA Bridge

Intel R-Tile PCIe Gen5 x16 to AXI-Lite bridge with DMA engine for Agilex 7 FPGA.

## Architecture

```
Host CPU --PCIe Gen5 x16--> R-Tile IP --> pcie_axi_bridge --> Address Decoder
                                               |                    |
                                               |              +-----+-----+-----+
                                               |              |     |     |     |
                                               |              v     v     v     v
                                               |           DMA   RAM   PCIe   AXI
                                               |          Regs  (4KB) Sniff  Sniff
                                               |
                                               +--> PCIe TLP (Host MRd/MWr/MSI-X)
```

## Memory Map (BAR0)

| Address       | Region        | Description                      |
|---------------|---------------|----------------------------------|
| 0x0000-0x0FFF | DMA Engine    | Control, status, DMA config      |
| 0x1000-0x1FFF | Local RAM     | 4KB buffer (host + DMA access)   |
| 0x2000-0x2FFF | PCIe Sniffer  | 256-entry TLP trace buffer       |
| 0x3000-0x3FFF | AXI Sniffer   | 64-entry AXI transaction trace   |

### DMA Registers (0x0000)

| Offset | Name       | Access | Description                                |
|--------|------------|--------|--------------------------------------------|
| 0x00   | ctrl       | R/W    | [0] start, [1] dir (0=H2C, 1=C2H), [2] irq_en |
| 0x08   | status     | RO     | [0] busy, [1] done                         |
| 0x10   | host_addr  | R/W    | 64-bit host memory address                 |
| 0x18   | local_addr | R/W    | 32-bit local RAM address                   |
| 0x20   | length     | R/W    | Transfer length in bytes                   |

### PCIe Sniffer Registers (0x2000)

256-entry trace buffer capturing PCIe TLPs with trigger support.

| Offset | Name           | Access | Description                              |
|--------|----------------|--------|------------------------------------------|
| 0x00   | status         | RO     | [0] rx_seen, [1] tx_seen, [7:4] tx_state, [16] running, [17] triggered, [18] full |
| 0x04   | control        | WO     | [0] start, [1] stop, [2] clear           |
| 0x08   | mode           | R/W    | [1:0] capture mode, [5:4] filter         |
| 0x0C   | trigger_cfg    | R/W    | [7:0] trigger type, [8] type_en          |
| 0x10   | write_ptr      | RO     | Current write pointer (0-255)            |
| 0x14   | entry_count    | RO     | Number of entries captured               |
| 0x18   | rx_count       | RO     | Total RX TLPs seen                       |
| 0x1C   | tx_count       | RO     | Total TX TLPs seen                       |
| 0x30   | read_ptr       | R/W    | Select trace entry to read               |
| 0x34-4C| trace_entry    | RO     | Selected entry (hdr, data, meta)         |
| 0x50-7C| last_rx/tx     | RO     | Last-seen RX/TX TLP headers and data     |

Capture modes: 0=continuous, 1=stop-on-full, 2=stop-on-trigger, 3=start-on-trigger

### AXI Sniffer Registers (0x3000)

64-entry trace buffer capturing internal AXI transactions.

| Offset | Name           | Access | Description                              |
|--------|----------------|--------|------------------------------------------|
| 0x00   | status         | RO     | [0] running, [1] full, [8-12] seen flags |
| 0x04   | control        | WO     | [0] start, [1] stop, [2] clear           |
| 0x08   | write_ptr      | RO     | Current write pointer                    |
| 0x0C   | entry_count    | RO     | Number of entries captured               |
| 0x10   | aw_count       | RO     | AW transactions seen                     |
| 0x14   | ar_count       | RO     | AR transactions seen                     |
| 0x20   | read_ptr       | R/W    | Select trace entry to read               |
| 0x24   | trace_addr     | RO     | Selected entry address                   |
| 0x28-2C| trace_data     | RO     | Selected entry data (64-bit)             |
| 0x30   | trace_meta     | RO     | Channel, phase, strobe/resp, timestamp   |

## Quick Start

### Simulation

Run all tests (requires Verilator):
```bash
cd tb && ./run.sh           # Integration test (top.sv) - 6 tests
cd tb && ./run_bridge.sh    # Bridge unit test
cd tb && ./run_sniffer.sh   # Sniffer unit test - 6 tests
```

### FPGA Build
```bash
./build_fpga.sh 0x08  # Revision ID
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
sudo ./test_bridge $PCI      # Basic RAM/DMA test
sudo ./dump_debug $PCI test  # Self-test with trace capture
```

### Debug Commands

```bash
# Show status of both sniffers
sudo ./dump_debug $PCI status

# Dump PCIe TLP trace
sudo ./dump_debug $PCI pcie 20

# Dump AXI transaction trace
sudo ./dump_debug $PCI axi 20

# Dump both traces
sudo ./dump_debug $PCI trace 20

# Start/stop/clear sniffers
sudo ./dump_debug $PCI start
sudo ./dump_debug $PCI stop
sudo ./dump_debug $PCI clear

# Self-test: capture BAR activity and dump traces
sudo ./dump_debug $PCI test
```

## Project Structure

```
rtl/
  top.sv              # System top with address decoder
  pcie_axi_bridge.sv  # Bidirectional PCIe<->AXI bridge (auto Completer ID)
  pcie_sniffer.sv     # 256-entry PCIe TLP trace with trigger
  axi_sniffer.sv      # 64-entry AXI transaction trace
  dma_engine.sv       # DMA controller (H2C + C2H)
  axi_ram.sv          # 4KB SRAM (M20K)
  rtile_crdt.sv       # Credit manager
  rtile_pkg.sv        # Types and constants

tb/
  tb_rtile.cpp        # Integration test (6 tests)
  tb_pcie_axi_bridge.cpp  # Bridge unit test
  tb_pcie_sniffer.cpp     # Sniffer unit test (6 tests)
  run.sh, run_bridge.sh, run_sniffer.sh

fpga/
  axi_bridge_hw.sv    # Qsys wrapper (R-Tile 4-seg to 1-seg)
  bridge_hw.tcl       # Platform Designer component script
  pcie_bridge.tcl     # R-Tile IP configuration
  pcie_bridge.qsf     # Quartus project settings

host/
  main.cpp            # Linux VFIO test application
  dump_debug.cpp      # Debug sniffer dump utility (PCIe + AXI)
  pcie-util.cpp/h     # VFIO helper functions
  build.sh            # Build script
```

## Features

- **PCIe Gen5 x16** via Intel R-Tile hard IP
- **Bidirectional bridge**: Host BAR access + DMA to host memory
- **Auto Completer ID**: Captures BDF from first TLP after enumeration
- **256-entry PCIe trace**: Capture TLPs with trigger/filter
- **64-entry AXI trace**: Capture internal AXI transactions
- **4KB local RAM**: Accessible from host and DMA
- **MSI-X interrupt** support

## License

MIT

## Disclaimer

This project was developed with assistance from AI (Claude/Kiro). The code, architecture, and documentation were created through human-AI collaboration.

