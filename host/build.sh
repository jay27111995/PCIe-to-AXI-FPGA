#!/bin/bash
# Build host programs for PCIe-to-AXI bridge testing

set -e

CFLAGS="-O2 -Wall -I include"
SRC=src
OUT=bin

mkdir -p $OUT

echo "Building host programs..."

# Build VFIO library
gcc $CFLAGS -c $SRC/pcie_vfio.c -o $OUT/pcie_vfio.o

# Build test program
gcc $CFLAGS -c $SRC/test_bridge.c -o $OUT/test_bridge.o
gcc $CFLAGS $OUT/pcie_vfio.o $OUT/test_bridge.o -o $OUT/test_bridge

# Clean up object files
rm -f $OUT/*.o

echo ""
echo "Built in $OUT/:"
echo "  test_bridge   - BAR and DMA tests"
echo ""

cat << 'EOF'
=== VFIO Setup ===

1. Find your FPGA device:
   lspci | grep -i '1172\|altera\|fpga'

2. Bind to VFIO:
   PCI=0000:b1:00.0
   echo $PCI > /sys/bus/pci/devices/$PCI/driver/unbind 2>/dev/null || true
   echo vfio-pci > /sys/bus/pci/devices/$PCI/driver_override
   echo $PCI > /sys/bus/pci/drivers/vfio-pci/bind
   GRP=$(basename $(readlink /sys/bus/pci/devices/$PCI/iommu_group))

3. Run tests:
   sudo ./bin/test_bridge $PCI $GRP

EOF
