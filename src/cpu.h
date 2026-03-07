#pragma once

#include "types.h"

#include <array>
#include <cstdint>

class Cpu {
public:
    Cpu();

    void reset();

    void tick();

private:
    uint32_t pc{};
    std::array<u32, 32> registers{};
};
