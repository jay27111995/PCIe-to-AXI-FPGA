#!/bin/bash
set -e
cd "$(dirname "$0")"
rm -rf obj_dir

verilator --cc --exe --build --trace --top-module pcie_axi_top \
    -Wno-fatal -Wno-UNUSEDSIGNAL -Wno-UNUSEDPARAM -Wno-CASEINCOMPLETE -Wno-WIDTHEXPAND -Wno-UNOPTFLAT \
    -I../rtl \
    ../rtl/rtile_pkg.sv \
    ../rtl/rtile_crdt.sv \
    ../rtl/axi_ram.sv \
    ../rtl/dma_engine.sv \
    ../rtl/rtile_top.sv \
    ../rtl/pcie_axi_top.sv \
    tb_rtile.cpp \
    -o tb_rtile

./obj_dir/tb_rtile
