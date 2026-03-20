#pragma once

#include "bios.h"
#include "bus.h"
#include "cpu.h"

struct System {
    Bus bus;
    CPU cpu;

    System() = default;
    System(const System&) = delete;
    System& operator=(const System&) = delete;

    std::expected<void, BIOS::Error> load_bios(const std::filesystem::path& path) {
        auto result = BIOS::load_image(path);
        if (!result) {
            return std::unexpected(result.error());
        }
        bus.map_bios(std::move(*result));
        return {};
    }

    void reset() { cpu.reset(); }
};
