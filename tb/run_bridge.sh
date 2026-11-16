#!/bin/bash
set -e
cd "$(dirname "$0")"
rm -rf obj_dir

verilator --cc --exe --build --trace --top-module pcie_axi_bridge \
    -Wno-fatal -Wno-UNUSEDSIGNAL -Wno-UNUSEDPARAM -Wno-CASEINCOMPLETE -Wno-WIDTHEXPAND -Wno-UNOPTFLAT \
    -I../rtl \
    ../rtl/rtile_pkg.sv \
    ../rtl/rtile_crdt.sv \
    ../rtl/pcie_axi_bridge.sv \
    tb_pcie_axi_bridge.cpp \
    -o tb_pcie_axi_bridge

./obj_dir/tb_pcie_axi_bridge
