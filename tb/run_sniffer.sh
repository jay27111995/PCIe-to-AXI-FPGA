#!/bin/bash
set -e
cd "$(dirname "$0")"
rm -rf obj_dir

verilator --cc --exe --build --trace --top-module pcie_sniffer \
    -Wno-fatal -Wno-UNUSEDSIGNAL -Wno-UNUSEDPARAM -Wno-CASEINCOMPLETE -Wno-WIDTHEXPAND -Wno-UNOPTFLAT \
    -I../rtl \
    ../rtl/pcie_sniffer.sv \
    tb_pcie_sniffer.cpp \
    -o tb_pcie_sniffer

./obj_dir/tb_pcie_sniffer
