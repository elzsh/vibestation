#pragma once

#include "types.h"

#include <expected>
#include <filesystem>
#include <vector>

namespace BIOS {

enum : u32 {
    SIZE = 0x80000,    // 512 KB
    MASK = 0x7FFFF,    // SIZE - 1
    BASE = 0x1FC00000,
};

enum class Error {
    OpenFailed,
    InvalidSize,
    ReadFailed,
};

struct Image {
    std::vector<u8> data;
};

std::expected<Image, Error> load_image(const std::filesystem::path& filepath);

}    // namespace BIOS
