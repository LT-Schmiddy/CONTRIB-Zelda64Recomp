#include "patches.h"
#include "patch_helpers.h"

#include "play_patches.h"

#include "global.h"
#include "z64save.h"
#include "z64shrink_window.h"
#include "z64view.h"
#include "regs.h"

typedef struct {
    /* 0x000 */ GameState state;
    /* 0x0A8 */ View view;
} TitleSetupState; // size = 0x210

void TitleSetup_Init(GameState* thisx);
void TitleSetup_Main(GameState* thisx);
void TitleSetup_Destroy(GameState* thisx);

RECOMP_PATCH void TitleSetup_Init(GameState* thisx) {
    TitleSetupState* this = (TitleSetupState*)thisx;

    GameState_SetFramerateDivisor(&this->state, 1);
    Matrix_Init(&this->state);
    ShrinkWindow_Init();
    View_Init(&this->view, this->state.gfxCtx);
    this->state.main = TitleSetup_Main;
    this->state.destroy = TitleSetup_Destroy;

    gSaveContext.respawnFlag = 0;
    gSaveContext.respawn[RESPAWN_MODE_GORON].entrance = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_ZORA].entrance = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_DEKU].entrance = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_HUMAN].entrance = 0xFF;

    // @recomp the game reset button shouldn't be shown during the title sequence, 
    // despite the fact that a PlayState is initialized.
    recomp_set_in_title_sequence(true);
}