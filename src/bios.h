#pragma once

#include "types.h"

#include <expected>
#include <filesystem>
#include <vector>

namespace BIOS {
constexpr u32 SIZE = 0x80000;       // 512 KB
constexpr u32 BASE = 0x1FC00000;    // KUSEG region
constexpr u32 MASK = 0x7FFFF;

enum class Error {
    OpenFailed,
    ReadFailed,
    InvalidSize,
};

std::expected<std::vector<u8>, Error> load(const std::filesystem::path& filepath);
}    // namespace BIOS
