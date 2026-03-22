#include "cpu.h"

#include "types.h"

#include <cstdio>
#include <cstdlib>

void CPU::reset() {
    pc = 0xBFC00000;
    next_pc = pc + 4;
}

void CPU::decode_and_execute(Instruction inst) {
    switch (inst.op()) {
        case 0x0F:    // lui
            std::fprintf(stderr, "What now?\n");
            std::abort();
            break;
        default:
            std::fprintf(stderr, "Unhandled instruction %08x\n", inst.bits);
            std::abort();
            break;
    }
}

void CPU::tick() {
    Instruction inst(bus->load32(pc));

    pc = next_pc;
    next_pc += 4;

    decode_and_execute(inst);
}
