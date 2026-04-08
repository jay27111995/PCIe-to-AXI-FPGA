#include "pcie-util.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <x86intrin.h>

#define REG_RESET    0x00
#define REG_SRC_ADDR 0x08
#define REG_DST_ADDR 0x10
#define REG_LEN      0x18
#define REG_CTRL     0x20
#define SRAM_BASE    0x1000

int main(int argc, char* argv[])
{
  if (argc < 2) { printf("Usage: %s <pcie_device>\n", argv[0]); return 1; }

  PCIe::Function pf(argv[1]);
  auto& bar = *pf.BARs[0];
  bar.map();

  bar.write64(REG_RESET, 1);
  usleep(1000);

  // Test SRAM
  printf("=== Test SRAM ===\n");
  for (int i = 0; i < 8; i++) bar.write64(SRAM_BASE + i*8, 0xDEADBEEF00000000ULL | i);
  for (int i = 0; i < 8; i++) printf("SRAM[%d] = %016lx\n", i, bar.read64(SRAM_BASE + i*8));

  // Test DMA
  printf("\n=== Test DMA ===\n");
  uint64_t* src = (uint64_t*)pf.createDmaArea(4096, 0x100000);
  uint64_t* dst = (uint64_t*)pf.createDmaArea(4096, 0x200000);
  
  src[0] = 0xCAFEF00D12345678ULL;
  dst[0] = 0;
  _mm_clflush(src); _mm_clflush(dst); _mm_mfence();

  bar.write64(REG_SRC_ADDR, 0x100000);
  bar.write64(REG_DST_ADDR, 0x200000);
  bar.write64(REG_LEN, 1);
  bar.write64(REG_CTRL, 1);
  usleep(10000);

  _mm_clflush(dst); _mm_mfence();
  
  bool pass = (dst[0] == src[0]);
  printf("src=%016lx dst=%016lx\n", src[0], dst[0]);
  printf("\n=== TEST %s ===\n", pass ? "PASSED" : "FAILED");
  return pass ? 0 : 1;
}
