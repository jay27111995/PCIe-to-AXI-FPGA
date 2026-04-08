#include "pcie-util.h"
#include <assert.h>
#include <cstdio>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

void PCIe::Function::findIommuGroup() {
  std::string iommuGroupPath =
      "/sys/bus/pci/devices/" + mDeviceStr + "/iommu_group";
  char buf[256];
  size_t size = readlink(iommuGroupPath.c_str(), buf, sizeof(buf) - 1);
  assert(size < sizeof(buf));
  buf[size] = '\0';
  std::string str(buf);
  mMmuGroup = std::stoi(str.substr(str.rfind("/") + 1));
}

PCIe::Function::Function(const std::string &deviceStr) : mDeviceStr(deviceStr) {
  findIommuGroup();

  struct vfio_group_status group_status = {.argsz = sizeof(group_status)};

  mContainerFd = open("/dev/vfio/vfio", O_RDWR);
  assert(ioctl(mContainerFd, VFIO_GET_API_VERSION) == VFIO_API_VERSION);
  assert(ioctl(mContainerFd, VFIO_CHECK_EXTENSION, VFIO_TYPE1_IOMMU));

  char tmpstr[32];
  snprintf(tmpstr, sizeof(tmpstr), "/dev/vfio/%d", mMmuGroup);
  mGroupFd = open(tmpstr, O_RDWR);

  ioctl(mGroupFd, VFIO_GROUP_GET_STATUS, &group_status);
  assert(group_status.flags & VFIO_GROUP_FLAGS_VIABLE);

  ioctl(mGroupFd, VFIO_GROUP_SET_CONTAINER, &mContainerFd);
  ioctl(mContainerFd, VFIO_SET_IOMMU, VFIO_TYPE1_IOMMU);

  mDeviceFd = ioctl(mGroupFd, VFIO_GROUP_GET_DEVICE_FD, mDeviceStr.c_str());
  assert(mDeviceFd != -1);

  struct vfio_device_info device_info = {.argsz = sizeof(device_info)};
  assert(ioctl(mDeviceFd, VFIO_DEVICE_GET_INFO, &device_info) != -1);

  for (unsigned idx = 0; idx < BARs.size(); idx++) {
    struct vfio_region_info reg = {.argsz = sizeof(reg)};
    reg.index = idx;
    ioctl(mDeviceFd, VFIO_DEVICE_GET_REGION_INFO, &reg);
    if (reg.size > 0) {
      BARs[idx].emplace(*this, idx, reg.size);
    }
  }
}

PCIe::Function::~Function() {}

void* PCIe::Function::createDmaArea(uint64_t size, uint64_t iova) {
  uint64_t page_size = sysconf(_SC_PAGESIZE);
  size = (size + page_size - 1) & ~(page_size - 1);

  void* p = mmap(NULL, size, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  struct vfio_iommu_type1_dma_map dma_map = {.argsz = sizeof(dma_map)};
  dma_map.size = size;
  dma_map.vaddr = (uint64_t)p;
  dma_map.iova = iova ? iova : dma_map.vaddr;
  dma_map.flags = VFIO_DMA_MAP_FLAG_READ | VFIO_DMA_MAP_FLAG_WRITE;

  int rcode = ioctl(mContainerFd, VFIO_IOMMU_MAP_DMA, &dma_map);
  assert(rcode != -1);

  return p;
}

PCIe::BaseAddressRegister::BaseAddressRegister(Function &func, unsigned index,
                                               uint64_t size)
    : mFunc(func), mIndex(index), mSize(size) {}

void PCIe::BaseAddressRegister::map() {
  struct vfio_region_info reg = {.argsz = sizeof(reg)};
  reg.index = mIndex;
  ioctl(mFunc.mDeviceFd, VFIO_DEVICE_GET_REGION_INFO, &reg);
  mBase = reinterpret_cast<uint8_t *>(mmap(NULL, reg.size,
                                           PROT_READ | PROT_WRITE, MAP_SHARED,
                                           mFunc.mDeviceFd, reg.offset));
  assert(mBase != nullptr);
}

void PCIe::BaseAddressRegister::write32(uint64_t offset, uint32_t value) {
  assert(offset < (mSize - 3));
  *reinterpret_cast<volatile uint32_t *>(mBase + offset) = value;
}

void PCIe::BaseAddressRegister::write64(uint64_t offset, uint64_t value) {
  assert(offset < (mSize - 7));
  *reinterpret_cast<volatile uint64_t *>(mBase + offset) = value;
}

uint32_t PCIe::BaseAddressRegister::read32(uint64_t offset) {
  assert(offset < (mSize - 3));
  return *reinterpret_cast<volatile uint32_t *>(mBase + offset);
}

uint64_t PCIe::BaseAddressRegister::read64(uint64_t offset) {
  assert(offset < (mSize - 7));
  return *reinterpret_cast<volatile uint64_t *>(mBase + offset);
}
