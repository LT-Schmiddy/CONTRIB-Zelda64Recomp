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


RECOMP_PATCH void GameState_Update(GameState* gameState) {
    GraphicsContext* gfxCtx = gameState->gfxCtx;

    GameState_SetFrameBuffer(gameState->gfxCtx);

    gameState->main(gameState);

    if (R_PAUSE_BG_PRERENDER_STATE != PAUSE_BG_PRERENDER_PROCESS) {
        GameState_Draw(gameState, gfxCtx);
        GameState_DrawEnd(gfxCtx);
    }
}
 