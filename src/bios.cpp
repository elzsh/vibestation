#include "bios.h"

#include <fstream>

namespace BIOS {
std::expected<std::vector<u8>, Error> load(const std::filesystem::path& filepath) {
    std::error_code ec;
    auto size = std::filesystem::file_size(filepath, ec);
    if (ec) {
        return std::unexpected(Error::OpenFailed);
    }

    if (size != SIZE) {
        return std::unexpected(Error::InvalidSize);
    }

    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        return std::unexpected(Error::OpenFailed);
    }

    std::vector<u8> data(SIZE);
    if (!file.read(reinterpret_cast<char*>(data.data()), SIZE)) {
        return std::unexpected(Error::ReadFailed);
    }

    return data;
}
}    // namespace BIOS
