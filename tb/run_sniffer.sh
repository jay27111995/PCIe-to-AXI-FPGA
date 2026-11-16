#!/bin/bash
# Run pcie_sniffer standalone testbench
set -e

cd "$(dirname "$0")"

# Clean previous build
rm -rf obj_dir

# Verilate without tracing to simplify build
verilator --cc ../rtl/pcie_sniffer.sv \
    --exe tb_pcie_sniffer.cpp -o tb_pcie_sniffer \
    --top-module pcie_sniffer \
    -Wno-WIDTH -Wno-CASEINCOMPLETE -Wno-UNOPTFLAT -Wno-TIMESCALEMOD \
    -Wno-UNUSEDSIGNAL -Wno-UNUSEDPARAM \
    --Mdir obj_dir --build --assert

# Run test
./obj_dir/tb_pcie_sniffer
