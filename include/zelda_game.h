#ifndef __ZELDA_GAME_H__
#define __ZELDA_GAME_H__
#include <stdint.h>
#include <atomic>

#include <cstdint>
#include <span>
#include <vector>

namespace zelda64 {
    // Quicksaving is disabled for now:
    //void quicksave_save();
    //void quicksave_load();

    void trigger_game_reset();
    void quicksave_save();
    void quicksave_load();
    std::vector<uint8_t> decompress_mm(std::span<const uint8_t> compressed_rom);
};

#endif
