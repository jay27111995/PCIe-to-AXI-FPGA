#include "pcie-util.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#define REG_RESET    0x00
#define REG_SRC_ADDR 0x08
#define REG_DST_ADDR 0x10
#define REG_LEN      0x18
#define REG_CTRL     0x20
#define SRAM_BASE    0x1000

int main(int argc, char* argv[])
{
  if (argc < 2) {
    printf("Usage: %s <pcie_device>\n", argv[0]);
    return 1;
  }

  PCIe::Function pf(argv[1]);
  if (!pf.BARs[0]) {
    printf("BAR0 not available\n");
    return 1;
  }

  auto& bar = *pf.BARs[0];
  bar.map();

  printf("=== Reset DMA ===\n");
  bar.write64(REG_RESET, 1);

  printf("\n=== Test SRAM ===\n");
  for (int i = 0; i < 8; i++) {
    uint64_t val = 0xDEADBEEF00000000ULL | i;
    bar.write64(SRAM_BASE + i * 8, val);
  }
  for (int i = 0; i < 8; i++) {
    uint64_t val = bar.read64(SRAM_BASE + i * 8);
    printf("SRAM[%d] = 0x%016lx\n", i, val);
  }

  printf("\n=== Test DMA ===\n");
  
  uint64_t* src = (uint64_t*)pf.createDmaArea(4096, 0);
  uint64_t* dst = (uint64_t*)pf.createDmaArea(4096, 0);
  
  for (int i = 0; i < 8; i++) {
    src[i] = 0xCAFEF00D00000000ULL | i;
  }
  memset(dst, 0, 64);

  printf("Source:\n");
  for (int i = 0; i < 8; i++)
    printf("  src[%d] = 0x%016lx\n", i, src[i]);

  printf("src_addr=0x%lx dst_addr=0x%lx\n", (uint64_t)src, (uint64_t)dst);

  bar.write64(REG_SRC_ADDR, (uint64_t)src);
  bar.write64(REG_DST_ADDR, (uint64_t)dst);
  bar.write64(REG_LEN, 8);
  
  printf("Readback: SRC=0x%lx DST=0x%lx LEN=0x%lx\n", 
         bar.read64(REG_SRC_ADDR), bar.read64(REG_DST_ADDR), bar.read64(REG_LEN));

  printf("Starting DMA (CTRL=1)...\n");
  bar.write64(REG_CTRL, 1);
  
  usleep(1000);  // Small delay
  
  uint64_t ctrl;
  int timeout = 1000;
  while ((ctrl = bar.read64(REG_CTRL)) & 2) {
    printf("CTRL=0x%lx (busy)\n", ctrl);
    usleep(100);
    if (--timeout == 0) { printf("Timeout!\n"); break; }
  }
  printf("CTRL=0x%lx (done)\n", ctrl);

  printf("Destination:\n");
  for (int i = 0; i < 8; i++)
    printf("  dst[%d] = 0x%016lx\n", i, dst[i]);

  bool pass = memcmp(src, dst, 64) == 0;
  printf("\n=== TEST %s ===\n", pass ? "PASSED" : "FAILED");

  return pass ? 0 : 1;
}
