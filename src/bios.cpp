#include "bios.h"

#include <fstream>

namespace BIOS {

std::expected<Image, Error> load_image(const std::filesystem::path& filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);

    if (!file) {
        return std::unexpected(Error::OpenFailed);
    }

    if (file.tellg() != BIOS::SIZE) {
        return std::unexpected(Error::InvalidSize);
    }

    file.seekg(0);

    Image image;
    image.data.resize(BIOS::SIZE);

    if (!file.read(reinterpret_cast<char*>(image.data.data()), BIOS::SIZE)) {
        return std::unexpected(Error::ReadFailed);
    }

    return image;
}

}    // namespace BIOS
