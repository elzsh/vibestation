#pragma once

#include "types.h"

#include <array>
#include <vector>

struct Bus {
    constexpr static u32 PHYS_MASK = 0x1FFFFFFF;    // 512MB physical address space
    constexpr static u32 PAGE_SIZE = 0x1000;        // 4KB per page
    constexpr static u32 PAGE_COUNT = 0x20000;      // 2^17 pages (512MB / 4KB)
    constexpr static u32 PAGE_SHIFT = 12;

    using ReadHandler = u32 (*)(Bus* bus, u32 address);

    Bus();

    [[nodiscard]] u32 load32(u32 address) {
        u32 physical = address & PHYS_MASK;
        return read_handlers[physical >> PAGE_SHIFT](this, physical);
    }

    void map_bios(std::vector<u8>&& bios_data);

private:
    std::array<ReadHandler, PAGE_COUNT> read_handlers;
    std::vector<u8> bios;

    void set_handler(u32 base, u32 size, ReadHandler read_handler);
    static u32 unmapped_read(Bus* bus, u32 address);
    static u32 bios_read(Bus* bus, u32 address);
};
