#include "game/auto_00_0016C410_text.h"
#include "static/GameSettings.h"
#include "musyx/musyx.h"

extern u16 lbl_3_data_81DC[];                  // first stadium sound id, per stadium
extern StadiumSfxMix lbl_3_data_8404[][15];    // per stadium
extern StadiumSfxMix lbl_3_data_84B8[15];      // minigames (GameModeSelected 6) at stadium 4

// .text:0x0016C410 size:0x138 mapped:0x807AB4A4
// NONMATCHING 98%: the original keeps the sound-id load after the GameModeSelected test; ours
// hoists it (re-testing stadium == 4 inside gives the right order plus one extra bne).
#if NONMATCHING
// Plays sound 4 (5 when alt is set) at stadium 4; other stadiums would use 13/14 but play nothing.
void fn_3_16C410(u8 alt) {
    u32 stadium;
    s32 sound;
    GameInitVariables* gs;
    SND_VOICEID voice;
    u8 vol;
    u8 ctrl;

    if (alt) {
        if (g_d_GameSettings.StadiumID == 4) {
            sound = 5;
        } else {
            sound = 14;
        }
    } else {
        if (g_d_GameSettings.StadiumID == 4) {
            sound = 4;
        } else {
            sound = 13;
        }
    }
    gs = &g_d_GameSettings;
    stadium = gs->StadiumID;
    if (stadium == 4) {
        if (gs->GameModeSelected == 6) {
            vol = lbl_3_data_84B8[sound].vol;
        } else {
            vol = lbl_3_data_8404[stadium][sound].vol;
        }
        voice = sndFXStartEx(lbl_3_data_81DC[stadium] + sound, vol, 0x3F, 0);
        if (gs->GameModeSelected == 6) {
            ctrl = lbl_3_data_84B8[sound].ctrl5B;
        } else {
            ctrl = lbl_3_data_8404[stadium][sound].ctrl5B;
        }
        sndFXCtrl(voice, 0x5B, ctrl);
    }
}
#endif
