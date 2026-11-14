#pragma once

#include <array>
#include <cstdint>
#include <linux/vfio.h>
#include <optional>
#include <string>

namespace PCIe {
class Function;

class BaseAddressRegister {
public:
  BaseAddressRegister(Function &func, unsigned index, uint64_t size);
  void map();
  void write32(uint64_t offset, uint32_t value);
  void write64(uint64_t offset, uint64_t value);
  uint32_t read32(uint64_t offset);
  uint64_t read64(uint64_t offset);

private:
  Function &mFunc;
  unsigned mIndex;
  uint64_t mSize;
  uint8_t *mBase = nullptr;
};

class Function {
public:
  Function(const std::string &deviceStr);
  ~Function();
  void* createDmaArea(uint64_t size, uint64_t iova);

  std::array<std::optional<BaseAddressRegister>, 6> BARs;
  int mDeviceFd = 0;
  int mContainerFd = 0;
  int mGroupFd = 0;

private:
  void findIommuGroup();
  std::string mDeviceStr;
  int mMmuGroup = 0;
};

} // namespace PCIe
