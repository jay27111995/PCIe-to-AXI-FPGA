#!/bin/bash
set -e
g++ -O2 -Wall -std=c++17 main.cpp pcie-util.cpp -o test_bridge
g++ -O2 -Wall -std=c++17 dump_debug.cpp pcie-util.cpp -o dump_debug
g++ -O2 -Wall -std=c++17 bw_test.cpp pcie-util.cpp -o bw_test
echo "Built: test_bridge, dump_debug, bw_test"
echo ""
echo "Usage:"
echo "  sudo ./test_bridge <pcie_device>      # Run basic tests"
echo "  sudo ./dump_debug <pcie_device> test  # Debug with trace capture"
echo "  sudo ./bw_test <pcie_device>          # Bandwidth measurement"
echo ""
echo "Example:"
echo "  sudo ./test_bridge 0000:b1:00.0"
echo "  sudo ./dump_debug 0000:b1:00.0 test"
echo "  sudo ./bw_test 0000:b1:00.0 all"
