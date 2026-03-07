#pragma once

#include "types.h"

#include <array>

class CPU {
public:
    CPU();

    void reset();
    void tick();

private:
    u32 pc{};
    std::array<u32, 32> registers{};
};
