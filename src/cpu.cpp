#include "cpu.h"

#include <cstdint>

void Cpu::reset() {
    registers.fill(0);

    pc = 0xbfc00000;
}

Cpu::Cpu() {
    reset();
}

void Cpu::tick() {
    // TODO: Fetch instruction from memory
    uint32_t opcode = 0;

    pc += 4;
}
