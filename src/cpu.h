#pragma once

#include "types.h"

struct Bus;

struct CPU {
    u32 pc;
    u32 next_pc;

    void reset();
    void tick(Bus& bus);

private:
    void decode_and_execute(u32 instruction);
};
