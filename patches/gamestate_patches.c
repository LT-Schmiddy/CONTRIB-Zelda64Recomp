#include "gamestate_patches.h"
#include "global.h"
#include "audiomgr.h"
#include "idle.h"
#include "sys_cfb.h"
#include "libc64/malloc.h"
#include "z64debug_text.h"
#include "z64rumble.h"
#include "z64speed_meter.h"
#include "z64vimode.h"
#include "z64viscvg.h"
#include "z64vismono.h"
#include "z64viszbuf.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"
#include "debug.h"

void do_reset_game(GameState* this) {
    PlayState* play = (PlayState*)this;
    gSaveContext.gameMode = GAMEMODE_OWL_SAVE;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_FADE_BLACK;
    play->nextEntrance = ENTRANCE(CUTSCENE, 0);
    gSaveContext.save.cutsceneIndex = 0;
    gSaveContext.sceneLayer = 0;
}

RECOMP_PATCH void GameState_Update(GameState* gameState) {
    GraphicsContext* gfxCtx = gameState->gfxCtx;

    GameState_SetFrameBuffer(gameState->gfxCtx);

    if (recomp_should_reset_game()) {
        do_reset_game(gameState);
    }

    gameState->main(gameState);

    if (R_PAUSE_BG_PRERENDER_STATE != PAUSE_BG_PRERENDER_PROCESS) {
        GameState_Draw(gameState, gfxCtx);
        GameState_DrawEnd(gfxCtx);
    }
}
 