#pragma once

#include "bus.h"
#include "types.h"

struct CPU {
    Bus* bus;

    Registers regs{};
    u32 pc{};
    u32 npc{};

    void reset();
    void tick();

private:
    void decode_and_execute(Instruction instruction);
};
