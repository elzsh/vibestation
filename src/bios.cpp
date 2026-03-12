#include "bios.h"

#include <fstream>

std::expected<BIOS::Image, BIOS::Error> BIOS::load_image(const std::filesystem::path& filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);

    if (!file) {
        return std::unexpected(BIOS::Error::OpenFailed);
    }

    if (file.tellg() != BIOS::SIZE) {
        return std::unexpected(BIOS::Error::InvalidSize);
    }

    file.seekg(0);

    BIOS::Image image;
    image.data.resize(BIOS::SIZE);

    if (!file.read(reinterpret_cast<char*>(image.data.data()), BIOS::SIZE)) {
        return std::unexpected(BIOS::Error::ReadFailed);
    }

    return image;
}
