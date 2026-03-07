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
    SIZE = 0x80000,
};

struct Image {
    std::vector<u8> data;    // BIOS ROM
};

std::expected<Image, Error> load_image(const std::filesystem::path& filepath);

}    // namespace BIOS
