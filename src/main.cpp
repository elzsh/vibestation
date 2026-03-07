#include "bios.h"

#include <iostream>

int main() {
    std::expected<BIOS::Image, BIOS::Error> image = BIOS::load_image("roms/SCPH1001.BIN");

    for (const auto& element : image->data) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << +element << '\n';
    }
}
