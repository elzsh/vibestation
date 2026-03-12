#include "bus.h"

#include "types.h"

u8* g_bios = nullptr;

namespace Bus {
template<MemoryAccessType size> static u32 BIOSReadHandler(u32 address);
};    // namespace Bus

template<MemoryAccessType size> u32 Bus::BIOSReadHandler(u32 address) {}
