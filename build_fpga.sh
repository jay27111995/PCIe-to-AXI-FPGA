#!/usr/bin/env bash
# PCIe-to-AXI Bridge FPGA Build Script for Intel Agilex 7 R-Tile
# This uses the intel_pcie_axi_mcdma IP for PCIe, then our custom bridge.

set -o pipefail

if [ $# -ne 1 ]; then
  echo "Error: Missing required argument."
  echo "Usage: $0 <rev_id>"
  echo "Example: $0 0x01"
  exit 1
fi
if [[ ! $1 =~ ^0x[0-9a-fA-F][0-9a-fA-F]$ ]]; then
  echo "Error: Revision id must be 8-bit hex integer (e.g. 0x01)."
  exit 1
fi
revid=$1

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"

echo "=========================================="
echo "PCIe-to-AXI Bridge FPGA Build"
echo "Revision ID: ${revid}"
echo "Build dir: ${BUILD_DIR}"
echo "=========================================="

# Check for Quartus
if ! command -v quartus_sh &> /dev/null; then
    echo "Error: quartus_sh not found. Load Quartus environment first."
    echo "  source /path/to/quartus/settings64.sh"
    exit 1
fi

# Step 1: Setup build directory and copy RTL files
echo ""
echo "[Step 1/4] Setting up build directory..."
rm -rf "${BUILD_DIR}"
mkdir -p "${BUILD_DIR}"
cp "${SCRIPT_DIR}"/rtl/*.sv "${BUILD_DIR}/"
cp "${SCRIPT_DIR}"/fpga/pcie_bridge.tcl "${BUILD_DIR}/"
cp "${SCRIPT_DIR}"/fpga/pcie_bridge.qsf "${BUILD_DIR}/"
cp "${SCRIPT_DIR}"/fpga/pcie_bridge.sdc "${BUILD_DIR}/"
cp "${SCRIPT_DIR}"/fpga/bridge_hw.tcl "${BUILD_DIR}/"

cd "${BUILD_DIR}"

# Step 2: Configure and generate Qsys
echo "[Step 2/4] Generating Qsys..."
rm -f pcie_bridge.qsf
sed -i "s/__REVID__/${revid}/" pcie_bridge.tcl
qsys-script --script=pcie_bridge.tcl --export pcie_bridge.qsys

if [ ! -f pcie_bridge.qsys ]; then
  echo "Error: pcie_bridge.qsys was not generated"
  exit 1
fi

echo "[Step 3/4] Generating Verilog from Qsys..."
# Force regeneration by removing cached IP directory
rm -rf pcie_bridge
qsys-generate pcie_bridge.qsys --synthesis=VERILOG --clear-output-directory

if [ ! -d "ip/pcie_bridge" ]; then
  echo "Error: qsys-generate failed"
  exit 1
fi

# Step 4: Quartus compile
echo "[Step 4/4] Running Quartus compilation..."
rm -f pcie_bridge.qsf
cp "${SCRIPT_DIR}/fpga/pcie_bridge.qsf" pcie_bridge.qsf

if ! quartus_sh --flow compile pcie_bridge; then
  echo "Error: Quartus compilation failed"
  exit 1
fi

# Package output
gitdesc=$(git -C "${SCRIPT_DIR}" describe --dirty --always --abbrev=7 2>/dev/null || echo "unknown")
output=output_files/pcie_bridge.sof
md5=$(md5sum "${output}" | cut -d ' ' -f1)
final="pcie-bridge-revid-${revid}-git-${gitdesc}-md5-${md5}.sof"
cp "${output}" "${final}"
cp "${final}" "${SCRIPT_DIR}/"

echo ""
echo "=========================================="
echo "Build complete: ${final}"
echo "=========================================="
echo ""
echo "To program FPGA:"
echo "  quartus_pgm -c 1 -m JTAG -o \"p;${final}\""
