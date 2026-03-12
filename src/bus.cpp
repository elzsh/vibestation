#include "bus.h"

#include "types.h"

#include <cstdint>

u8* g_bios = nullptr;

namespace Bus {
static u32 BIOSReadHandler(u32 address);
};    // namespace Bus

u32 Bus::BIOSReadHandler(u32 address) {
    const u32 offset = address & UINT32_C(0x7FFFF);

    return g_bios[offset];
}
