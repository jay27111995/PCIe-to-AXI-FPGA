#!/bin/bash
# Run pcie_axi_bridge standalone testbench
set -e

cd "$(dirname "$0")"

# Clean previous build
rm -rf obj_dir

# Verilate without tracing to simplify build
verilator --cc ../rtl/rtile_pkg.sv ../rtl/rtile_crdt.sv ../rtl/pcie_axi_bridge.sv \
    --exe tb_pcie_axi_bridge.cpp -o tb_pcie_axi_bridge \
    --top-module pcie_axi_bridge \
    -Wno-WIDTH -Wno-CASEINCOMPLETE -Wno-UNOPTFLAT -Wno-TIMESCALEMOD \
    --Mdir obj_dir --build --assert

# Run test
./obj_dir/tb_pcie_axi_bridge
