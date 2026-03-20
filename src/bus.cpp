#include "bus.h"

#include "bios.h"

#include <bit>
#include <cassert>
#include <cstdio>
#include <cstring>

Bus::Bus() {
    read_handlers.fill(&unmapped_read);
}

void Bus::set_handler(u32 base, u32 size, ReadHandler read_handler) {
    u32 start_page = base >> PAGE_SHIFT;
    u32 num_pages = (size + (1 << PAGE_SHIFT) - 1) >> PAGE_SHIFT;

    assert(start_page + num_pages <= PAGE_COUNT);

    for (u32 i = 0; i < num_pages; i++) {
        read_handlers[start_page + i] = read_handler;
    }
}

void Bus::map_bios(std::vector<u8>&& bios_data) {
    bios = std::move(bios_data);
    set_handler(BIOS::BASE, BIOS::SIZE, &bios_read);
}

u32 Bus::unmapped_read(Bus* /*bus*/, u32 address) {
    std::fprintf(stderr, "Unhandled load32 at address %08x\n", address);
    return 0xFFFFFFFF;
}

u32 Bus::bios_read(Bus* bus, u32 address) {
    u32 offset = address & BIOS::MASK;
    u32 value;

    std::memcpy(&value, &bus->bios[offset], sizeof(u32));

    if constexpr (std::endian::native != std::endian::little) {
        value = std::byteswap(value);
    }

    return value;
}
