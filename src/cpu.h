#pragma once

#include "types.h"

namespace CPU {

struct State {
    u32 pc;
};

extern State state;

void Initialize();
void RunNextInstruction();

}    // namespace CPU
