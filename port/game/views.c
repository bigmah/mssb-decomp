// Accessors for fields of global structs that some units can't reach through
// the real struct (their headers clash) and whose GameCube-offset views are
// wrong on PC.
#include "main/file_80021308.h" // SoundManager

extern SoundManager lbl_800EF808;

// SoundManager.unk39A[0]: roster slot whose sound bank is being loaded
// (game/auto_00_0005985C_text.c).
u8* port_sound_load_index(void) {
    return &lbl_800EF808.unk39A[0];
}

// MSSB_TRACE_GAME=1: print the game-flow state when it changes.
#include "game/UnknownHomes_Game.h"
#include <stdlib.h>
#include "static/GameSettings.h"
extern GameScores g_Scores;
void port_trace_game(void) {
    static int enabled = -1;
    static int last[7] = {-1, -1, -1, -1, -1, -1, -1};
    int now[7];
    if (enabled < 0) {
        enabled = getenv("MSSB_TRACE_GAME") != NULL;
    }
    if (!enabled) {
        return;
    }
    now[0] = g_GameLogic.gameStatus;
    now[1] = g_GameLogic._125;
    now[2] = g_Pitcher.pitcherActionState;
    now[3] = g_d_GameSettings._06;
    now[4] = g_Scores.inning;
    now[5] = g_GameLogic.teamBatting;
    now[6] = g_Strikes.outs;
    if (memcmp(now, last, sizeof(now)) != 0) {
        memcpy(last, now, sizeof(now));
        fprintf(stderr, "[game] status %d load %d pitcher %d mode %d pitchframe %d | inning %d batting %d outs %d balls %d strikes %d runs %d-%d\n",
                now[0], now[1], now[2], now[3], g_GameLogic.FrameCountOfCurrentPitch, now[4], now[5], now[6], g_Strikes.balls,
                g_Strikes.strikes, g_Scores.team[0].runs[0], g_Scores.team[1].runs[0]);
    }
}

// Browser on WebKit (the page sets AURORA_PIPELINE_PREWARM=app): every GPU pipeline compile holds
// up presenting a frame, so the ~200 a game uses compile ahead only while a hitch doesn't show: the
// Now Loading screen, the stadium intro and the scene between batters or half-innings. During play
// a new effect still compiles on first use, if the windows weren't long enough to reach it.
#include <aurora/aurora.h>
#include <string.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
void port_pipeline_prewarm_policy(void) {
    static int enabled = -1;
    static int last = -1;
    int perFrame = 0;
    if (enabled < 0) {
        const char* env = getenv("AURORA_PIPELINE_PREWARM");
        enabled = env != NULL && strcmp(env, "app") == 0;
    }
    if (!enabled) {
        return;
    }
    if (g_d_GameSettings._06 == 2) { // in the game module
        switch (g_GameLogic.gameStatus) {
        case 0:
            if (g_Scores.inning == 0) { // Now Loading
                perFrame = 2;
            }
            break;
        case 4: // set-up after loading
            perFrame = 2;
            break;
        case 5:  // stadium intro (VS)
        case 22: // between batters, side change
            perFrame = 1;
            break;
        }
    }
    if (perFrame != last) {
#ifdef __EMSCRIPTEN__
        if (perFrame > 0 && last == 0) {
            // A quiet moment: also store the pipelines this device used (aurora appends them to
            // /mssb/pipeline_cache.bin) so the next game compiles them ahead too.
            EM_ASM({ if (window.mssbSaveData) window.mssbSaveData(); });
        }
#endif
        size_t left = aurora_set_pipeline_prewarm(perFrame);
        if (getenv("MSSB_DEBUG_PREWARM") != NULL) {
            fprintf(stderr, "[prewarm] %d per frame (status %d), %u waiting\n", perFrame, g_GameLogic.gameStatus,
                    (unsigned)left);
        }
        last = perFrame;
    }
}

// MSSB_TRACE_TASKS=1 also prints the scene flow (lbl_803CBBCC) when it changes.
#include "main/menu_globals.h"
void port_trace_scene(void) {
    static int enabled = -1;
    static int last = -1;
    int now;
    if (enabled < 0) {
        enabled = getenv("MSSB_TRACE_TASKS") != NULL;
    }
    if (!enabled || lbl_803CBBCC == NULL) {
        return;
    }
    now = lbl_803CBBCC->scene * 0x10000 + lbl_803CBBCC->step;
    if (now != last) {
        last = now;
        fprintf(stderr, "[scene] scene %d step %d (prev %d/%d)\n", lbl_803CBBCC->scene, lbl_803CBBCC->step,
                lbl_803CBBCC->prevScene, lbl_803CBBCC->prevStep);
    }
}

// Bytes of lbl_8036E548 (CharMgr) that game/auto_00_000AC9F8_text.c reads by
// their GameCube offsets (it declares the object as u8[]).
#include "main/file_80011640.h" // CharMgr
#include <stdio.h>
extern CharMgr lbl_8036E548;
u8* port_charmgr_byte(u32 gcOffset) {
    if (gcOffset >= 0x2D3C && gcOffset < 0x2D60 && (gcOffset - 0x2D3C) % 0xC == 0xA) {
        return &lbl_8036E548.preload[(gcOffset - 0x2D3C) / 0xC].state;
    }
    switch (gcOffset) {
    case 0x307D:
        return &lbl_8036E548._307D;
    case 0x307E:
        return &lbl_8036E548._307E;
    }
    fprintf(stderr, "port_charmgr_byte: unmapped offset 0x%X\n", gcOffset);
    abort();
}

// lbl_80366158._28 (the pause flag) for units that declare the object as
// u8[] and index it by its GameCube offset (LBL_80366158_U8).
#include "main/file_80008E00.h" // lbl_80366158_s
u8* port_80366158_byte(u32 gcOffset) {
    if (gcOffset == 0x28) {
        return &lbl_80366158._28;
    }
    fprintf(stderr, "port_80366158_byte: unmapped offset 0x%X\n", gcOffset);
    abort();
}

// Web: the intro is cut short unless MSSB_SKIP_INTRO=0 (?intro). Boot goes
// straight to the title screen, as after a soft reset (the health screen and
// logos are skipped: src/main/file_80008E00.c), the title takes a press at once
// (src/main/file_80069BDC.c), and Start/A are pressed through to the main menu.
s32 port_skip_intro(void) {
    static int enabled = -1;
    if (enabled < 0) {
        const char* env = getenv("MSSB_SKIP_INTRO");
        enabled = env != NULL && env[0] != '\0' && env[0] != '0';
    }
    return enabled;
}

// Returns the buttons to add to port 1 this frame.
u16 port_intro_buttons(void) {
    static u32 frame;
    if (!port_skip_intro() || lbl_803CBBCC == NULL || lbl_803CBBCC->scene != 1) {
        return 0;
    }
    // Two frames down, fourteen up: each press is a fresh edge.
    return (frame++ % 16) < 2 ? 0x1000 | 0x100 : 0; // PAD_BUTTON_START | PAD_BUTTON_A
}
