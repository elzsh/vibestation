#pragma once

#include "types.h"

namespace CPU {

struct State {
    u32 pc{};    // address of the next instruction to execute
};
}    // namespace CPU
