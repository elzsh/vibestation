#pragma once

#include <cstdint>

using u8 = uint8_t;
using s8 = int8_t;
using u16 = uint16_t;
using s16 = int16_t;
using u32 = uint32_t;
using s32 = int32_t;
using u64 = uint64_t;
using s64 = int64_t;

/*
 * CPU Types
 */
struct Instruction {
    u32 bits;

    constexpr explicit Instruction(u32 raw) : bits(raw) {}

    // pimary opcode [31..26] 6-bits
    constexpr u8 op() const { return static_cast<u8>(bits >> 26); }

    // register source [25..21] 5-bits
    constexpr u8 rs() const { return static_cast<u8>((bits >> 21) & 0x1F); }

    // register target [20..16] 5-bits
    constexpr u8 rt() const { return static_cast<u8>((bits >> 16) & 0x1F); }

    // register destination [15..11] 5-bit
    constexpr u8 rd() const { return static_cast<u8>((bits >> 11) & 0x1F); }

    // shift ammount [10..6] 5-bits
    constexpr u8 shamt() const { return static_cast<u8>((bits >> 6) & 0x1F); }

    // function code [5..0] 6-bits
    constexpr u8 funct() const { return static_cast<u8>(bits & 0x3F); }

    // immediate [15..0] 16-bits
    constexpr u16 imm() const { return static_cast<u16>(bits & 0xFFFF); }

    // jump target [25..0] 26-bits
    constexpr u32 target() const { return static_cast<u32>(bits & 0x3FFFFFF); }
};
