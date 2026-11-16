#!/bin/bash
# Program FPGA and setup PCIe on dut19
# Usage: ./program_fpga.sh <sof_file>

set -e

SOF_FILE="${1:-$(ls -t *.sof 2>/dev/null | head -1)}"

if [[ -z "$SOF_FILE" || ! -f "$SOF_FILE" ]]; then
    echo "Usage: $0 <sof_file>"
    echo "Or run in directory with .sof files"
    exit 1
fi

PCIE_EP=0000:b4:00.0
PCIE_RP=0000:b3:00.0

echo "=== Programming FPGA: $SOF_FILE ==="

# 1. Remove endpoint from PCIe bus
echo "[1/8] Removing PCIe endpoint..."
echo 1 | sudo tee /sys/bus/pci/devices/${PCIE_EP}/remove > /dev/null 2>&1 || true

# 2. Link disable
echo "[2/8] Disabling PCIe link..."
sudo setpci -s ${PCIE_RP} CAP_EXP+0x10.B=0x50

# 3. Program FPGA
echo "[3/8] Programming FPGA..."
quartus_pgm -c 1 -m JTAG -o "p;${SOF_FILE}"

# 4. Link enable
echo "[4/8] Enabling PCIe link..."
sudo setpci -s ${PCIE_RP} CAP_EXP+0x10.B=0x40

# 5. Wait for link training
echo "[5/8] Waiting for link training..."
sleep 2

# 6. Rescan PCIe bus
echo "[6/8] Rescanning PCIe bus..."
echo 1 | sudo tee /sys/bus/pci/rescan > /dev/null

# 7. Verify device
echo "[7/8] Verifying device..."
if lspci -s ${PCIE_EP} | grep -q .; then
    echo "  Device found:"
    lspci -s ${PCIE_EP}
else
    echo "  ERROR: Device not found!"
    exit 1
fi

# 8. Disable ACS
echo "[8/8] Disabling ACS..."
sudo setpci -s ${PCIE_RP} ECAP_ACS+0x6.w=0x0

echo ""
echo "=== FPGA programmed successfully ==="
echo ""
echo "To bind to VFIO for testing:"
echo "  echo ${PCIE_EP} | sudo tee /sys/bus/pci/devices/${PCIE_EP}/driver/unbind 2>/dev/null"
echo "  sudo modprobe vfio-pci"
echo "  echo vfio-pci | sudo tee /sys/bus/pci/devices/${PCIE_EP}/driver_override"
echo "  echo ${PCIE_EP} | sudo tee /sys/bus/pci/drivers/vfio-pci/bind"
