#pragma once

#include "bios.h"
#include "bus.h"
#include "cpu.h"

struct System {
    std::vector<u8> bios;
    Bus bus;
    CPU cpu;

    // Make System non-copyable
    System() = default;
    System(const System&) = delete;
    System& operator=(const System&) = delete;

    std::expected<void, BIOS::Error> load_bios(const std::filesystem::path& path) {
        auto result = BIOS::load(path);
        if (!result) {
            return std::unexpected(result.error());
        }

        bios = std::move(*result);
        bus.map_bios(bios);

        return {};
    }

    void reset() { cpu.reset(); }
};
