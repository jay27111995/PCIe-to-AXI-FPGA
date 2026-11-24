# PCIe-to-AXI FPGA Bridge

Intel R-Tile PCIe Gen5 x16 to internal bus bridge with DMA engine for Agilex 7 FPGA.

## Architecture

```
Host CPU ──PCIe Gen5 x16──► R-Tile IP ──► pcie_axi_bridge ──► Address Decoder
                                │                                   │
                                │                   ┌───────┬───────┼───────┬───────┐
                                │                   │       │       │       │       │
                                │                   ▼       ▼       ▼       ▼       ▼
                                │                 DMA     RAM    PCIe    AXI     AXI
                                │                Regs   (4KB)  Sniffer Slave   Master
                                │                  │                  Sniff   Sniff
                                │                  │
                                │                  ▼
                                │            dma_engine ──► RAM
                                │                  │
                                │   (DMA to host)  │
                                ◄──────────────────┘
```

**Three Sniffers with Shared Timestamp:**
- PCIe Sniffer: Captures TLPs on PCIe interface (host ↔ R-Tile)
- AXI Slave Sniffer: Captures BAR access transactions (host → FPGA)
- AXI Master Sniffer: Captures DMA transactions (FPGA → host memory)

All sniffers share a global timestamp for event correlation.

## Memory Map (BAR0)

| Address       | Region            | Description                      |
|---------------|-------------------|----------------------------------|
| 0x0000-0x0FFF | DMA Engine        | Control, status, DMA config      |
| 0x1000-0x1FFF | Local RAM         | 4KB buffer (host + DMA access)   |
| 0x2000-0x2FFF | PCIe Sniffer      | 256-entry TLP trace buffer       |
| 0x3000-0x37FF | AXI Slave Sniffer | 64-entry BAR access trace        |
| 0x3800-0x3FFF | AXI Master Sniffer| 64-entry DMA to host trace       |

### DMA Registers (0x0000)

| Offset | Name       | Access | Description                                |
|--------|------------|--------|--------------------------------------------|
| 0x00   | ctrl       | R/W    | [0] start, [1] dir (0=H2C, 1=C2H), [2] irq_en |
| 0x08   | status     | RO     | [0] busy, [1] done                         |
| 0x10   | host_addr  | R/W    | 64-bit host memory address                 |
| 0x18   | local_addr | R/W    | 32-bit local RAM address                   |
| 0x20   | length     | R/W    | Transfer length in bytes                   |

### PCIe Sniffer Registers (0x2000)

256-entry trace buffer capturing full PCIe TLPs (header + 256-bit data).

| Offset | Name           | Access | Description                              |
|--------|----------------|--------|------------------------------------------|
| 0x00   | status         | RO     | [0] rx_seen, [1] tx_seen, [16] running, [17] triggered, [18] full |
| 0x04   | control        | WO     | [0] start, [1] stop, [2] clear           |
| 0x08   | mode           | R/W    | [1:0] capture mode, [5:4] filter         |
| 0x0C   | trigger_cfg    | R/W    | [7:0] trigger type, [8] type_en          |
| 0x10   | write_ptr      | RO     | Current write pointer (0-255)            |
| 0x14   | entry_count    | RO     | Number of entries captured               |
| 0x18   | rx_count       | RO     | Total RX TLPs seen                       |
| 0x1C   | tx_count       | RO     | Total TX TLPs seen                       |
| 0x30   | read_ptr       | R/W    | Select trace entry to read               |
| 0x34-40| trace_hdr[0-3] | RO     | Selected entry header (128 bits)         |
| 0x44-60| trace_data[0-7]| RO     | Selected entry data (256 bits)           |
| 0x64   | trace_meta0    | RO     | timestamp[31:0] (cycle counter)          |
| 0x68   | trace_meta1    | RO     | [0] dir, [1] rx_sop, [2] rx_eop, [3] rx_hvalid, [4] rx_dvalid, [7:5] rx_bar, [8] rx_ready, [9] tx_sop, [10] tx_eop, [11] tx_hvalid, [12] tx_dvalid, [13] tx_ready |
| 0x70-7C| last_rx_hdr    | RO     | Last RX TLP header                       |
| 0x80-9C| last_rx_data   | RO     | Last RX TLP data (256 bits)              |
| 0xA0-AC| last_tx_hdr    | RO     | Last TX TLP header                       |
| 0xB0-CC| last_tx_data   | RO     | Last TX TLP data (256 bits)              |

Capture modes: 0=continuous, 1=stop-on-full, 2=stop-on-trigger, 3=start-on-trigger

### AXI Slave Sniffer Registers (0x3000)

64-entry trace buffer capturing BAR access (host → FPGA).

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

### AXI Master Sniffer Registers (0x3800)

64-entry trace buffer capturing DMA to host memory (FPGA → host).
Same register layout as AXI Slave Sniffer, offset by 0x800.

## Variable-Length TLP Support

The bridge supports BAR reads up to 4KB with automatic splitting into multiple completion TLPs:

```
Host Request                    FPGA Response
─────────────                   ─────────────
MRd: 64 bytes at 0x1500   →    CplD #1: 32 bytes (0x1500-0x151F)
                          →    CplD #2: 32 bytes (0x1520-0x153F)
```

**How it works:**

1. Host sends MRd TLP with length (1-1024 DW)
2. Bridge issues sequential AXI reads (8 bytes each)
3. After collecting 32 bytes (or remaining data), sends CplD
4. Repeats until all bytes sent
5. Each CplD has correct ByteCount (remaining) and LowerAddress

**Limits:**
- Max 32 bytes (8 DW) per CplD (R-Tile 256-bit bus width)
- Max 4KB per request (PCIe spec limit for completions)
- Sequential AXI reads (not burst)

## Quick Start

### Simulation

Run all tests (requires Verilator):
```bash
cd tb && ./run.sh           # Integration test (top.sv) - 10 tests
cd tb && ./run_bridge.sh    # Bridge unit test
cd tb && ./run_sniffer.sh   # Sniffer unit test - 6 tests
```

### FPGA Build
```bash
./build_fpga.sh 0x0C  # Revision ID
```

### Hardware Test

PCIe addresses (fpga machine):
```
PCIE_EP=0000:b1:00.0   # Endpoint (FPGA)
PCIE_RP=0000:b0:02.0   # Root port
```

**1. Remove endpoint and disable link:**
```bash
echo 1 | sudo tee /sys/bus/pci/devices/${PCIE_EP}/remove 2>/dev/null || true
sudo setpci -s ${PCIE_RP} CAP_EXP+0x10.B=0x50
```

**2. Program FPGA:**
```bash
quartus_pgm -c 1 -m JTAG -o "p;pcie-bridge-revid-0x0C-*.sof"
```

**3. Enable link and rescan:**
```bash
sudo setpci -s ${PCIE_RP} CAP_EXP+0x10.B=0x40
sleep 2
echo 1 | sudo tee /sys/bus/pci/rescan
```

**4. Verify and disable ACS:**
```bash
lspci -s ${PCIE_EP}
sudo setpci -s ${PCIE_RP} ECAP_ACS+0x6.w=0x0
```

**5. Bind to VFIO:**
```bash
echo ${PCIE_EP} | sudo tee /sys/bus/pci/devices/${PCIE_EP}/driver/unbind 2>/dev/null || true
sudo modprobe vfio-pci
echo vfio-pci | sudo tee /sys/bus/pci/devices/${PCIE_EP}/driver_override
echo ${PCIE_EP} | sudo tee /sys/bus/pci/drivers/vfio-pci/bind
```

**6. Run tests:**
```bash
cd host && ./build.sh
sudo ./test_bridge $PCIE_EP      # Basic RAM/DMA test
sudo ./dump_debug $PCIE_EP test  # Self-test with trace capture
```

### Debug Commands

```bash
# Show status of all 3 sniffers
sudo ./dump_debug $PCI status

# Dump merged trace (all sniffers, sorted by timestamp)
sudo ./dump_debug $PCI trace 20

# Dump individual sniffer traces
sudo ./dump_debug $PCI pcie 20     # PCIe TLPs only
sudo ./dump_debug $PCI axi 20      # AXI slave (BAR access) only
sudo ./dump_debug $PCI dma 20      # AXI master (DMA) only

# Start/stop/clear all sniffers (also resets timestamp)
sudo ./dump_debug $PCI start
sudo ./dump_debug $PCI stop
sudo ./dump_debug $PCI clear

# Step-by-step debug tests
sudo ./dump_debug $PCI test_wr     # Trace a single BAR write
sudo ./dump_debug $PCI test_rd     # Trace a single BAR read
sudo ./dump_debug $PCI test_rw     # Trace BAR write + read
sudo ./dump_debug $PCI test_h2c    # Trace DMA host-to-card
sudo ./dump_debug $PCI test_c2h    # Trace DMA card-to-host

# Full self-test
sudo ./dump_debug $PCI test
```

## Project Structure

```
rtl/
  top.sv              # System top with address decoder and 3 sniffers
  pcie_axi_bridge.sv  # PCIe<->AXI bridge with multi-CplD support
  pcie_sniffer.sv     # 256-entry PCIe trace (512-bit entries, full TLP data)
  axi_sniffer.sv      # 64-entry AXI transaction trace (used for both slave/master)
  dma_engine.sv       # DMA controller (H2C + C2H)
  axi_ram.sv          # 4KB SRAM (M20K)
  rtile_crdt.sv       # Credit manager
  rtile_pkg.sv        # Types and constants

tb/
  tb_rtile.cpp        # Integration test (11 tests including multi-CplD)
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
  dump_debug.cpp      # Debug tool with merged trace view
  pcie-util.cpp/h     # VFIO helper functions
  build.sh            # Build script
```

## Features

- **PCIe Gen5 x16** via Intel R-Tile hard IP
- **Variable-length BAR reads**: Up to 4KB with automatic multi-CplD splitting
- **Bidirectional bridge**: Host BAR access + DMA to host memory
- **Auto Completer ID**: Captures BDF from first TLP after enumeration
- **256-entry PCIe trace**: Full 256-bit TLP data capture with trigger/filter
- **64-entry AXI trace**: Capture internal AXI transactions
- **4KB local RAM**: Accessible from host and DMA
- **MSI-X interrupt** support

## Tests

| Test | Description |
|------|-------------|
| 1 | RAM write/read (single 64-bit) |
| 2 | RAM multiple addresses |
| 3 | Debug register read (sniffer) |
| 4 | DMA C2H (RAM → Host) |
| 5 | DMA H2C (Host → RAM) |
| 6 | Multi-DW BAR read (4 DW = 16 bytes) |
| 7 | Multi-CplD read (64 bytes = 2 CplDs) |
| 8 | Large multi-CplD read (256 bytes = 8 CplDs) |
| 9 | Odd-length read (10 DW = 8+2 DW CplDs) |
| 10 | DMA with MSI-X interrupt |

## License

MIT

## Disclaimer

This project was developed with assistance from AI (Claude/Kiro). The code, architecture, and documentation were created through human-AI collaboration.
