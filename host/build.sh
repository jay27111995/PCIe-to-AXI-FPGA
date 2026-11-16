#!/bin/bash
set -e
g++ -O2 -Wall -std=c++17 main.cpp pcie-util.cpp -o test_bridge
g++ -O2 -Wall -std=c++17 dump_debug.cpp pcie-util.cpp -o dump_debug
echo "Built: test_bridge, dump_debug"
echo ""
echo "Usage:"
echo "  sudo ./test_bridge <pcie_device>   # Run tests"
echo "  sudo ./dump_debug <pcie_device>    # Dump debug registers"
echo ""
echo "Example:"
echo "  sudo ./test_bridge 0000:b4:00.0"
echo "  sudo ./dump_debug 0000:b4:00.0"
