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
enum class InstructionOp : u8 {
    ori = 0x0D,
    lui = 0x0F,
};

// clang-format off
enum class Reg : u8 {
    zero, at, v0, v1, a0, a1, a2, a3,
    t0, t1, t2, t3, t4, t5, t6, t7,
    s0, s1, s2, s3, s4, s5, s6, s7,
    t8, t9, k0, k1, gp, sp, fp, ra,
    count
};
// clang-format on

struct Registers {
    union {
        u32 r[static_cast<u8>(Reg::count)];

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

        struct {
            u32 zero;    // r0
            u32 at;      // r1
            u32 v0;      // r2
            u32 v1;      // r3
            u32 a0;      // r4
            u32 a1;      // r5
            u32 a2;      // r6
            u32 a3;      // r7
            u32 t0;      // r8
            u32 t1;      // r9
            u32 t2;      // r10
            u32 t3;      // r11
            u32 t4;      // r12
            u32 t5;      // r13
            u32 t6;      // r14
            u32 t7;      // r15
            u32 s0;      // r16
            u32 s1;      // r17
            u32 s2;      // r18
            u32 s3;      // r19
            u32 s4;      // r20
            u32 s5;      // r21
            u32 s6;      // r22
            u32 s7;      // r23
            u32 t8;      // r24
            u32 t9;      // r25
            u32 k0;      // r26
            u32 k1;      // r27
            u32 gp;      // r28
            u32 sp;      // r29
            u32 fp;      // r30
            u32 ra;      // r31
            u32 hi;
            u32 lo;
        };

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
    };
};

struct Instruction {

    u32 bits;

    constexpr explicit Instruction(u32 raw) : bits(raw) {}

    // pimary opcode [31..26] 6-bits
    constexpr InstructionOp op() const { return static_cast<InstructionOp>(bits >> 26); }

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
