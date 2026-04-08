#!/bin/bash
set -e

verilator --cc --exe --build --trace-fst \
  -Wno-fatal \
  ../rtl/dma_core.sv \
  sim_dma.cpp \
  -o sim_dma

./obj_dir/sim_dma
