#include "cpu.h"

void CPU::reset() {
    registers.fill(0);

    pc = 0xbfc00000;
}

CPU::CPU() {
    reset();
}

void CPU::tick() {
    // TODO: Read instruction from memory

    pc += 4;
}
