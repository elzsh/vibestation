#pragma once

#include "types.h"

#include <span>

struct Bus {
    constexpr static u32 PAGE_SHIFT = 12;
    constexpr static u32 PAGE_SIZE = 0x1000;      // 4KB (Bottom 12 bits of the 29 bit address)
    constexpr static u32 PAGE_COUNT = 0x20000;    // Top 17 bits of the 29 bit address

    using ReadHandler = u32 (*)(Bus* bus, u32 address);

    Bus();

    u32 load32(u32 address) {
        u32 physical = address & 0x1FFFFFFF;    // Drop top 3 bits
        return read_handlers[physical >> PAGE_SHIFT](this, address);
    }

    void map_bios(std::span<u8> bios_data);

private:
    std::span<u8> bios;
    std::array<ReadHandler, PAGE_COUNT> read_handlers;

    void set_handler(u32 base, u32 size, ReadHandler read_handler);
    static u32 unmapped_read(Bus* bus, u32 address);
    static u32 bios_read(Bus* bus, u32 address);
};
