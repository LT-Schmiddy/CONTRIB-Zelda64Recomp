#ifndef __ZELDA_GAME_H__
#define __ZELDA_GAME_H__
#include <stdint.h>
#include <atomic>

namespace zelda64 {
    // Quicksaving is disabled for now:
    //void quicksave_save();
    //void quicksave_load();

    void trigger_game_reset();
};

#endif
