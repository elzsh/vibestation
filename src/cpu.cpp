#include "cpu.h"

#include <cstdio>
#include <cstdlib>

void CPU::reset() {
    pc = 0xBFC00000;
    next_pc = pc + 4;
}

void CPU::decode_and_execute(u32 instruction) {
    std::fprintf(stderr, "Unhandled instruction %08x\n", instruction);
    std::abort();
}

void CPU::tick(Bus& bus) {
    u32 instruction = bus.load32(pc);

    pc = next_pc;
    next_pc += 4;

    decode_and_execute(instruction);
}
