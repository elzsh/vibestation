#include "cpu.h"

#include "types.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>

void CPU::reset() {
    std::ranges::fill(std::span{regs.r}.subspan(1), 0xdeadc0de);
    regs.hi = 0xdeadc0de;
    regs.lo = 0xdeadc0de;
    regs.zero = 0;

    pc = 0xBFC00000;
    npc = pc + 4;
}

void CPU::decode_and_execute(Instruction inst) {
    switch (inst.op()) {
        case InstructionOp::lui:
            regs.r[inst.rt()] = inst.imm() << 16;
            break;
        default:
            std::fprintf(stderr, "Unhandled instruction %08x\n", inst.bits);
            std::abort();
            break;
    }
}

void CPU::tick() {
    Instruction inst(bus->load32(pc));

    pc = npc;
    npc += 4;

    decode_and_execute(inst);
}
