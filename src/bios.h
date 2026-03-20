#pragma once

#include "types.h"

#include <expected>
#include <filesystem>
#include <vector>

namespace BIOS {
constexpr u32 SIZE = 0x80000;       // 512 KB
constexpr u32 MASK = 0x7FFFF;       // BIOS SIZE - 1
constexpr u32 BASE = 0x1FC00000;    // KUSEG physical address

enum class Error {
    InvalidSize,
    OpenFailed,
    ReadFailed,
};

std::expected<std::vector<u8>, Error> load_image(const std::filesystem::path& filepath);
}    // namespace BIOS
