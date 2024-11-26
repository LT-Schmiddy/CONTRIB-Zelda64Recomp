#ifndef __PLAY_PATCHES_H__
#define __PLAY_PATCHES_H__

#include "patches.h"
#include "patch_helpers.h"

void debug_play_update(PlayState* play);
void camera_pre_play_update(PlayState* play);
void camera_post_play_update(PlayState* play);
void analog_cam_pre_play_update(PlayState* play);
void analog_cam_post_play_update(PlayState* play);
void matrix_play_update(PlayState* play);
void autosave_post_play_update(PlayState* play);

DECLARE_FUNC(void, recomp_set_reset_button_visibility, u8 visibility);
DECLARE_FUNC(bool, recomp_should_reset_game);

#endif
