#pragma once

#include "bus.h"
#include "types.h"

struct CPU {
    Bus* bus;

    u32 pc{};
    u32 next_pc{};

    void reset();
    void tick();

private:
    void decode_and_execute(Instruction instruction);
};
