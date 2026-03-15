#pragma once

#include "types.h"

#include <vector>

namespace BUS {

enum : u32 {
    MEMORY_LUT_SIZE = 0x100000,       // Size of the 2**20 pages LUT
    MEMORY_LUT_PAGE_SIZE = 0x1000,    // Size of the 12-bit pages (4096)
    MEMORY_LUT_PAGE_SHIFT = 12,
};

using MemoryReadHandler = u32 (*)(u32 address);

extern u8* bios;
extern MemoryReadHandler* memory_handlers;

void Initialize(std::vector<u8> bios_data);
void Shutdown();

u32 Load32(u32 address);

}    // namespace BUS
