#include "system.h"

static const char* bios_error_string(BIOS::Error err) {
    switch (err) {
        case BIOS::Error::InvalidSize:
            return "invalid size (expected 512 KB)";
        case BIOS::Error::OpenFailed:
            return "failed to open file";
        case BIOS::Error::ReadFailed:
            return "failed to read file";
    }
    return "unknown error";
}

int main() {
    auto psx = std::make_unique<System>();

    if (auto result = psx->load_bios("roms/SCPH1001.BIN"); !result) {
        std::fprintf(stderr, "BIOS load error: %s\n", bios_error_string(result.error()));
        return EXIT_FAILURE;
    }

    psx->reset();

    for (;;) {
        psx->cpu.tick(psx->bus);
    }

    return EXIT_SUCCESS;
}
