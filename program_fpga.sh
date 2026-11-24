#!/bin/bash
set -e

SOF=$1
CABLE=1
PCIE_EP=0000:b1:00.0
PCIE_RP=0000:b0:02.0

if [ ! -f "$SOF" ]; then
    echo "$SOF not found, exiting"
    exit 1
fi

echo "[1/6] Removing PCIe device..."
echo 1 | sudo tee /sys/bus/pci/devices/${PCIE_EP}/remove 2>/dev/null || true
sleep 2

echo "[2/6] Disabling PCIe link..."
sudo setpci -s ${PCIE_RP} CAP_EXP+0x10.B=0x50
sleep 2

# Verify link is disabled
LINK_CTRL=$(sudo setpci -s ${PCIE_RP} CAP_EXP+0x10.B)
echo "    Link control: 0x${LINK_CTRL}"
if [ "$LINK_CTRL" != "50" ]; then
    echo "    Warning: Link may not be disabled"
fi

echo "[3/6] Programming FPGA..."
quartus_pgm -c $CABLE -m jtag -o "p;$SOF"
sleep 3

echo "[4/6] Enabling PCIe link..."
sudo setpci -s ${PCIE_RP} CAP_EXP+0x10.B=0x40
sleep 3

echo "[5/6] Rescanning PCIe bus..."
echo 1 | sudo tee /sys/bus/pci/rescan
sleep 1

echo "[6/6] Binding to VFIO..."
echo ${PCIE_EP} | sudo tee /sys/bus/pci/devices/${PCIE_EP}/driver/unbind 2>/dev/null || true
echo vfio-pci | sudo tee /sys/bus/pci/devices/${PCIE_EP}/driver_override
echo ${PCIE_EP} | sudo tee /sys/bus/pci/drivers/vfio-pci/bind

echo ""
lspci -s ${PCIE_EP}
echo ""
echo "Done. Run: sudo ./host/dump_debug ${PCIE_EP} test"
