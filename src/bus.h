#pragma once

#include "types.h"

#include <cstdio>
#include <cstdlib>
#include <span>

struct Bus {
    constexpr static u32 PAGE_SHIFT = 12;
    constexpr static u32 PAGE_SIZE = 0x1000;      // 4KB (Bottom 12 bits of the 29 bit address)
    constexpr static u32 PAGE_COUNT = 0x20000;    // Top 17 bits of the 29 bit address

    using ReadHandler = u32 (*)(Bus* bus, u32 address);
    using WriteHandler = void (*)(Bus* bus, u32 address, u32 value);

    Bus();

    u32 load32(u32 address) {
        // if the two LSB are not 00
        if ((address & 0x3) != 0) [[unlikely]] {
            std::fprintf(stderr, "Unaligned load32 address: 0x%08x\n", address);
            std::abort();
        }

        u32 physical = address & 0x1FFFFFFF;    // Drop KSEG/KUSEG bits
        return read_handlers[physical >> PAGE_SHIFT](this, address);
    }

    void store32(u32 address, u32 val) {
        // if the two LSB are not 00
        if ((address & 0x3) != 0) [[unlikely]] {
            std::fprintf(stderr, "Unaligned store32 address: 0x%08x\n", address);
            std::abort();
        }

        // TODO: Implement write queue for single clock cycle write
        std::fprintf(
            stderr,
            "Unhandled store32 of value 0x%08x into address 0x%08x\n",
            val,
            address
        );
        std::abort();
    }

    void map_bios(std::span<u8> bios_data);

private:
    std::span<u8> bios;
    std::array<ReadHandler, PAGE_COUNT> read_handlers;
    std::array<WriteHandler, PAGE_COUNT> write_handlers;

    void set_handler(u32 base, u32 size, ReadHandler rd, WriteHandler wr);

    /* Unmapped & Sink */
    static u32 unmapped_read(Bus* bus, u32 address);
    static void unmapped_write(Bus* bus, u32 address, u32 value);
    static void ignore_write(Bus* bus, u32 address, u32 value);

    /* BIOS */
    static u32 bios_read(Bus* bus, u32 address);

    /* memctrl */
    static void memctrl_write(Bus* bus, u32 address, u32 value);
};
