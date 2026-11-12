#!/bin/bash
# Run axi_ram unit testbench

set -e

cd "$(dirname "$0")"

echo "Building axi_ram testbench..."
verilator --cc --exe --build --trace \
    -I../rtl \
    ../rtl/rtile_pkg.sv \
    ../rtl/axi_ram.sv \
    tb_axi_ram.cpp \
    -o tb_axi_ram \
    --top-module axi_ram \
    -Wno-fatal

echo "Running testbench..."
./obj_dir/tb_axi_ram

echo ""
echo "Waveform saved to axi_ram_tb.vcd"
echo "View with: gtkwave axi_ram_tb.vcd"
