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
    auto op = inst.op();
    auto rt = inst.rt();
    auto rs = inst.rs();

    switch (op) {
        case InstructionOp::ori:
            regs.r[rt] = regs.r[rs] | inst.imm_zext32();
            break;
        case InstructionOp::lui:
            regs.r[rt] = inst.imm() << 16;
            break;
        case InstructionOp::sw: {
            u32 addr = regs.r[rs] + inst.imm_sext32();
            bus->store32(addr, regs.r[rt]);
            break;
        }
        default:
            std::fprintf(stderr, "Unhandled instruction 0x%08x\n", inst.bits);
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
