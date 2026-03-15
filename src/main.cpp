#include "bios.h"
#include "bus.h"
#include "cpu.h"

int main() {
    auto result = BIOS::load_image("roms/SCPH1001.BIN");
    if (!result) {
        std::fprintf(stderr, "Failed to open BIOS\n");
        return EXIT_FAILURE;
    }

    BUS::Initialize(std::move(result->data));
    CPU::Initialize();

    for (;;) {
        CPU::RunNextInstruction();
    }

    return 0;
}
