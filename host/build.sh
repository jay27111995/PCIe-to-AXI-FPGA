#!/bin/bash
set -e
g++ -O2 -Wall -std=c++17 main.cpp pcie-util.cpp -o test_bridge
echo "Built: test_bridge"
echo "Usage: sudo ./test_bridge <pcie_device>"
echo "Example: sudo ./test_bridge 0000:b4:00.0"
