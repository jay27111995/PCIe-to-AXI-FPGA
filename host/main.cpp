#include "pcie-util.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <x86intrin.h>

#define REG_RESET    0x00
#define REG_SRC_ADDR 0x08
#define REG_DST_ADDR 0x10
#define REG_LEN      0x18
#define REG_CTRL     0x20
#define REG_DBG_STATE 0x28
#define REG_DBG_RADDR 0x30
#define REG_DBG_RDATA 0x38
#define REG_DBG_WADDR 0x40
#define REG_DBG_WDATA 0x48
#define REG_DBG_CNT   0x50

static inline void clflush_range(void* addr, size_t len) {
  char* p = (char*)((uint64_t)addr & ~63ULL);
  char* end = (char*)addr + len;
  while (p < end) { _mm_clflush(p); p += 64; }
}

int main(int argc, char* argv[])
{
  if (argc < 2) { printf("Usage: %s <pcie_device>\n", argv[0]); return 1; }

  PCIe::Function pf(argv[1]);
  auto& bar = *pf.BARs[0];
  bar.map();

  bar.write64(REG_RESET, 1);
  usleep(1000);

  printf("=== DMA with cache flush ===\n");
  
  void* src_raw = mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT, -1, 0);
  void* dst_raw = mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT, -1, 0);
  uint64_t* src = (uint64_t*)(((uint64_t)src_raw + 127) & ~127ULL);
  uint64_t* dst = (uint64_t*)(((uint64_t)dst_raw + 127) & ~127ULL);
  
  pf.createDmaArea(4096, (uint64_t)src);
  pf.createDmaArea(4096, (uint64_t)dst);
  
  for (int i = 0; i < 16; i++) src[i] = 0xCAFEF00D00000000ULL | i;
  memset(dst, 0xAA, 128);
  
  // Flush source to memory so DMA can read it
  clflush_range(src, 128);
  _mm_mfence();
  
  printf("src=%p dst=%p\n", src, dst);
  
  bar.write64(REG_SRC_ADDR, (uint64_t)src);
  bar.write64(REG_DST_ADDR, (uint64_t)dst);
  bar.write64(REG_LEN, 1);
  
  _mm_mfence();  // Ensure BAR writes complete
  bar.write64(REG_CTRL, 1);
  _mm_mfence();
  
  usleep(100000);
  
  // Invalidate destination cache before reading
  clflush_range(dst, 128);
  _mm_mfence();
  
  printf("After DMA:\n");
  printf("  CTRL=%016lx\n", bar.read64(REG_CTRL));
  printf("  DBG_STATE=%016lx\n", bar.read64(REG_DBG_STATE));
  printf("  DBG_RADDR=%016lx\n", bar.read64(REG_DBG_RADDR));
  printf("  DBG_RDATA=%016lx\n", bar.read64(REG_DBG_RDATA));
  printf("  DBG_WADDR=%016lx\n", bar.read64(REG_DBG_WADDR));
  printf("  DBG_WDATA=%016lx\n", bar.read64(REG_DBG_WDATA));
  printf("  DBG_CNT=%016lx (wcnt:rcnt)\n", bar.read64(REG_DBG_CNT));
  printf("  dst[0]=%016lx src[0]=%016lx\n", dst[0], src[0]);

  return 0;
}
