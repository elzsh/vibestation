#pragma once

#include "types.h"

#include <expected>
#include <filesystem>
#include <vector>

namespace BIOS {

enum class Error {
    OpenFailed,
    InvalidSize,
    ReadFailed,
};

enum : u32 {
    BASE = 0x1FC00000,
    SIZE = 0x80000,    // 512 KB
};

struct Image {
    std::vector<u8> data;    // BIOS ROM
};

std::expected<Image, Error> load_image(const std::filesystem::path& filepath);

}    // namespace BIOS
