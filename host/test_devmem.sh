#!/bin/bash
# Safer test using /dev/mem instead of VFIO
# This reads BAR0 directly without IOMMU translation

set -e

PCIE_EP="${1:-0000:b4:00.0}"

# Get BAR0 address
BAR0=$(lspci -s ${PCIE_EP#0000:} -v 2>/dev/null | grep "Region 0" | awk '{print $4}')
if [ -z "$BAR0" ]; then
    echo "Could not find BAR0 address"
    exit 1
fi
echo "BAR0 physical address: $BAR0"

# Enable memory access
echo "Enabling memory access..."
PCIE_RP="0000:b3:00.0"
sudo setpci -s ${PCIE_EP} COMMAND=0x06  # Memory + Master enable

# Wait for settle
sleep 0.1

# Set completion timeout disable
echo "Disabling completion timeout..."
sudo setpci -s ${PCIE_EP} CAP_EXP+0x28.W=0x0010

# Read using devmem2 (if available) or busybox devmem
echo ""
echo "Attempting to read debug register at offset 0x2000..."
DEBUG_ADDR=$(printf "0x%x" $((0x$BAR0 + 0x2000)))
echo "Physical address: $DEBUG_ADDR"

# Try the read - this may crash the system if FPGA responds badly
echo "Reading... (if this hangs, FPGA is not responding)"
if command -v devmem2 &>/dev/null; then
    sudo devmem2 $DEBUG_ADDR w
elif [ -c /dev/mem ]; then
    # Use dd with xxd as fallback
    sudo dd if=/dev/mem bs=4 count=1 skip=$((DEBUG_ADDR/4)) 2>/dev/null | xxd -e
else
    echo "No devmem2 or /dev/mem available"
    exit 1
fi

echo "Read completed successfully!"
