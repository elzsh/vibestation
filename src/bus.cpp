#include "bus.h"

#include "bios.h"

#include <cstring>

static constexpr u32 KUSEG = 0;
static constexpr u32 KSEG0 = 0x80000000;
static constexpr u32 KSEG1 = 0xA0000000;
static constexpr u32 KSEG2 = 0xC0000000;

namespace BUS {

static std::vector<u8> s_bios_data;

u8* bios = nullptr;
MemoryReadHandler* memory_handlers = nullptr;

static u32 UnmappedReadHandler(u32 address) {
    fprintf(stderr, "Unhandled load32 at address %08x\n", address);
    return 0xFFFFFFFF;
}

static u32 BIOSReadHandler(u32 address) {
    const u32 offset = address & BIOS::MASK;

    u32 value;
    std::memcpy(&value, &bios[offset], sizeof(u32));
    return value;
}

static void SetHandlerForRegion(u32 base, u32 size, MemoryReadHandler handler) {
    const u32 start_page = (base / MEMORY_LUT_PAGE_SIZE);
    const u32 num_pages = ((size + (MEMORY_LUT_PAGE_SIZE - 1)) / MEMORY_LUT_PAGE_SIZE);

    for (u32 i = 0; i < num_pages; i++) {
        memory_handlers[start_page + i] = handler;
    }
}

void Initialize(std::vector<u8> bios_data) {
    s_bios_data = std::move(bios_data);
    bios = s_bios_data.data();

    memory_handlers = new MemoryReadHandler[MEMORY_LUT_SIZE];
    std::fill_n(memory_handlers, MEMORY_LUT_SIZE, &UnmappedReadHandler);

    SetHandlerForRegion(KUSEG | BIOS::BASE, BIOS::SIZE, BIOSReadHandler);
    SetHandlerForRegion(KSEG0 | BIOS::BASE, BIOS::SIZE, BIOSReadHandler);
    SetHandlerForRegion(KSEG1 | BIOS::BASE, BIOS::SIZE, BIOSReadHandler);
}

void Shutdown() {
    delete[] memory_handlers;
    memory_handlers = nullptr;
    bios = nullptr;
    s_bios_data.clear();
}

u32 Load32(u32 address) {
    return memory_handlers[address >> MEMORY_LUT_PAGE_SHIFT](address);
}

}    // namespace BUS
