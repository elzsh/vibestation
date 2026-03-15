#include "cpu.h"

#include "bus.h"

#include <cstdio>
#include <cstdlib>

namespace CPU {

State state{};

void Initialize() {
    state = {};
    state.pc = 0xBFC00000;
}

static void DecodeAndExecute(u32 instruction) {
    std::fprintf(stderr, "Unhandled instruction %08x\n", instruction);
    std::abort();
}

void RunNextInstruction() {
    const u32 instruction = BUS::Load32(state.pc);
    state.pc += 4;

    DecodeAndExecute(instruction);
}

}    // namespace CPU
