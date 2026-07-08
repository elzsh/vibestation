#include "bus.h"

#include "bios.h"

#include <cstdio>
#include <cstring>

Bus::Bus() {
    read_handlers.fill(&unmapped_read);
    write_handlers.fill(&unmapped_write);
}

void Bus::set_handler(u32 base, u32 size, ReadHandler rd, WriteHandler wr) {
    u32 start_page = base >> PAGE_SHIFT;
    u32 num_pages = (size + (1 << PAGE_SHIFT) - 1) >> PAGE_SHIFT;

    for (u32 i = 0; i < num_pages; i++) {
        read_handlers[start_page + i] = rd;
        write_handlers[start_page + i] = wr;
    }
}

void Bus::map_bios(std::span<u8> bios_data) {
    bios = bios_data;
    set_handler(BIOS::BASE, BIOS::SIZE, &bios_read, &ignore_write);
}

/* Unmapped & Sink */
u32 Bus::unmapped_read(Bus* /*bus*/, u32 address) {
    std::fprintf(stderr, "Unhandled load32 at address 0x%08x\n", address);
    return 0xFFFFFFFF;
}

void Bus::unmapped_write(Bus* /*bus*/, u32 address, u32 value) {
    std::fprintf(stderr, "Unhandled store32: val 0x%08x to addr 0x%08x\n", value, address);
}

void Bus::ignore_write(Bus* /*bus*/, u32 /*address*/, u32 /*value*/) { /* KEEP EMPTY */ }

/* BIOS */
u32 Bus::bios_read(Bus* bus, u32 address) {
    u32 offset = address & BIOS::MASK;
    u32 value;

    std::memcpy(&value, &bus->bios[offset], sizeof(u32));

    if constexpr (std::endian::native != std::endian::little) {
        value = std::byteswap(value);
    }

    return value;
}

/* MEMCTRL */
void Bus::memctrl_write(Bus* /*bus*/, u32 address, u32 value) {
    std::fprintf(stderr, "MEMCTRL write: val 0x%08x to addr 0x%08x\n", value, address);
}
