#pragma pool_data off

#include "menus/rep_04B0.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"
#include "musyx/musyx.h"
#include "main/file_80011640.h"
#include "menus/auto_00_00001254_text.h"
#include "menus/auto_00_00013BA4_text.h"
#include "menus/auto_00_00016870_text.h"
#include "menus/rep_0438.h"

// Buttons latched by the menus, one per port (PortInput in main/file_8004207C.h).
typedef struct PortInput {
    /*0x0*/ u16 held;
    /*0x2*/ u16 pressed;
    /*0x4*/ u16 repeat;
} PortInput;

// Controller state, one per port (lbl_803C77B8; PadState in main/file_800A7C08.h).
// static/UnknownHomes_Static.h declares it with a partial view, so index it through this one.
typedef struct PadState04B0 {
    /*0x00*/ u16 held;
    /*0x02*/ u16 down;
    /*0x04*/ u16 repeat;
    /*0x06*/ u8 _06[0x20 - 0x6];
} PadState04B0;
#define PADS ((PadState04B0*)&lbl_803C77B8)

// Character select work area (lbl_8034E9A0; see CharSelWork in main/file_8004207C.h).
typedef struct CharSel04B0 {
    /*0x0000*/ u8 _0000[0x46E0];
    /*0x46E0*/ s32 captain[2]; // captain character id per team, -1: none
    /*0x46E8*/ u8 _46E8[0x46F8 - 0x46E8];
    /*0x46F8*/ s8 teamPort[4]; // controller port per player
    /*0x46FC*/ s8 joined[4];   // port pressed A to join
    /*0x4700*/ u8 _4700[0x4704 - 0x4700];
    /*0x4704*/ u8 _4704;
    /*0x4705*/ u8 _4705[0x4729 - 0x4705];
    /*0x4729*/ u8 _4729;
    /*0x472A*/ u8 _472A[0x472C - 0x472A];
    /*0x472C*/ PortInput input[4];
    /*0x4744*/ u8 _4744[0x4757 - 0x4744];
    /*0x4757*/ u8 charFlag[0x36]; // per character id: already picked
} CharSel04B0;
extern CharSel04B0 lbl_8034E9A0;

// Team select screen state (lbl_2_bss_100B8; raw bytes in auto_00_00016870_text.c).
typedef struct CaptainSelMenu {
    /*0x00*/ s8 qHead;
    /*0x01*/ s8 qTail;
    /*0x02*/ u8 queue[10];
    /*0x0C*/ u8 _0C[4];
    /*0x10*/ u8 picked[2];   // per player: captain chosen
    /*0x12*/ u8 _12[2];
    /*0x14*/ u8 loadReq[2];  // per player: model load requested
    /*0x16*/ u8 _16[3];
    /*0x19*/ u8 active;
    /*0x1A*/ u8 busy;
    /*0x1B*/ u8 _1B;
    /*0x1C*/ u8 timer[2];    // per player: frames since the cursor settled
    /*0x1E*/ u8 _1E[0x2D - 0x1E];
    /*0x2D*/ u8 count;
    /*0x2E*/ u8 _2E[0x40 - 0x2E];
    /*0x40*/ u8 animState[2];
    /*0x42*/ u8 loading[4];
    /*0x46*/ u8 _46[4];
    /*0x4A*/ u8 debugCam;    // disabled debug camera
    /*0x4B*/ u8 debugMenu;   // disabled debug menu
    /*0x4C*/ u8 _4C[0x54 - 0x4C];
} CaptainSelMenu; // size: 0x54
extern CaptainSelMenu lbl_2_bss_100B8;
extern u8 lbl_2_bss_100B4;

// Captain cursor per team (lbl_2_bss_F410).
typedef struct CaptainCursor {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s32 sel[4]; // index into lbl_800FE5D4
    /*0x20*/ u8 _20[0x58 - 0x20];
} CaptainCursor;
extern CaptainCursor lbl_2_bss_F410;

// Per-player menu flags (lbl_2_bss_F468).
typedef struct MenuFlagsF468 {
    /*0x00*/ u8 _00[0x45];
    /*0x45*/ u8 _45[2];
    /*0x47*/ u8 _47[2];
    /*0x49*/ u8 _49[2];
    /*0x4B*/ u8 _4B[2];
} MenuFlagsF468;
extern MenuFlagsF468 lbl_2_bss_F468;

// Menu camera (lbl_2_bss_1010C).
typedef struct MenuCamera {
    /*0x00*/ Mtx view;
    /*0x30*/ u16 rotX;
    /*0x32*/ u16 rotY;
    /*0x34*/ f32 strafe;
    /*0x38*/ f32 dolly;
    /*0x3C*/ Vec target;
    /*0x48*/ Vec eye;
    /*0x54*/ s32 _54;
} MenuCamera; // size: 0x58
extern MenuCamera lbl_2_bss_1010C;

typedef struct MenuLightMtx {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ Mtx view;
    /*0x44*/ u8 _44[4];
} MenuLightMtx;
extern MenuLightMtx lbl_2_bss_10164;

typedef struct MenuCamData {
    /*0x000*/ u8 _000[0x418];
    /*0x418*/ Vec eye;
    /*0x424*/ Vec target;
    /*0x430*/ Vec up;
} MenuCamData;
extern MenuCamData lbl_2_data_19E8;
extern LightSrc lbl_2_data_1DD4[4];
extern Vec lbl_2_data_20EC;
extern f32 lbl_2_data_20F8[2];

// Tutorial / port mapping (lbl_803C66B0; TutorialSteps in main/file_8004207C.h).
typedef struct TutorialPorts {
    /*0x00*/ u8 _00[5];
    /*0x05*/ u8 _05;
    /*0x06*/ u8 _06[0xE - 0x6];
    /*0x0E*/ u8 _0E;
    /*0x0F*/ u8 _0F[0x55 - 0xF];
    /*0x55*/ u8 active[4];
    /*0x59*/ u8 portOf[4]; // player of port i
} TutorialPorts;
extern TutorialPorts lbl_803C66B0;

typedef struct MenuWork04B0 {
    /*0x0000*/ u8 _0000[0xCF5D];
    /*0xCF5D*/ u8 random[2]; // per player: random captain requested
} MenuWork04B0;
extern MenuWork04B0 lbl_803297E0;

typedef struct Unk803C5EA4_04B0 {
    /*0x00*/ u8 _00[5];
    /*0x05*/ u8 _05;
} Unk803C5EA4_04B0;
extern Unk803C5EA4_04B0 lbl_803C5EA4;

typedef struct SceneFlow04B0 {
    /*0x00*/ u16 _00;
    /*0x02*/ u16 scene;
    /*0x04*/ u16 step;
    /*0x06*/ u16 prevScene;
} SceneFlow04B0;
extern SceneFlow04B0* lbl_803CBBCC;

typedef struct SaveFlags04B0 {
    /*0x00*/ u8 _00[0xF4];
    /*0xF4*/ u8 _F4;
} SaveFlags04B0;
extern SaveFlags04B0 lbl_80361B20;

typedef struct TeamPick04B0 {
    /*0x00*/ s8 sel[2];
} TeamPick04B0;
extern TeamPick04B0 lbl_803C6724;

extern u8 lbl_803CBBC4[4];
extern u8 lbl_803CBCD8[4];
extern u8 lbl_800EFBA4[]; // sound effect volumes
extern u8 lbl_800FE5D4[12]; // captain character ids
extern u8 lbl_800FE930[][6]; // challenge captain ids
extern u8 lbl_80108EC4[12];

// Character select state for up to 4 cursors (lbl_803C6028; RosterSelect in main/file_8004C5F8.h).
typedef struct RosterSel04B0 {
    /*0x00*/ u8 _00[0x74];
    /*0x74*/ u8 _74[4];
    /*0x78*/ u8 _78[0x7F - 0x78];
    /*0x7F*/ s8 _7F[4];
} RosterSel04B0;
extern RosterSel04B0 lbl_803C6028;

// main/file_8004C5F8.h (not included: its headers conflict with main/file_80011640.h)
void fn_8004D4F0(s32 owner, s32 entry, s32 set); // s8 owner in main/file_8004C5F8.h; callers sign-extend
s32 fn_8004D57C(s32 unused, s32 pressed, u16 dirs); // s16 in main/file_8004C5F8.h; callers here use the full int
void fn_8004E504(s32 byId, s32 entry0, s32 entry1, s32 entry2, s32 entry3);
void fn_8004E5B4(s32 owner, s32 entry, s32 set); // s8 owner in main/file_8004C5F8.h; callers sign-extend
s32 fn_8004E62C(s32 p, s32 unused, s32 pressed, u16 dirs); // see fn_8004D57C

// main/file_800527C4.h (not included: its lbl_8034E9A0 view conflicts)
void fn_800625A4(s32 index, s32 step);
void fn_80052968(void);
void fn_80052D70(void);

// main/file_800B0724.h (not included: conflicts with static/UnknownHomes_Static.h)
void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);

static inline s32 captainIndex(s32 id) {
    s32 i;
    u8* p = lbl_800FE5D4;
    for (i = 0; i < 12; p++, i++) {
        if (*p == id) {
            id = i;
            break;
        }
    }
    return id;
}

static inline s32 challengeCaptainIndex(s32 id) {
    s32 i;
    for (i = 0; i < 6; i++) {
        if (id == lbl_800FE930[lbl_80361B20._F4][i]) {
            return i;
        }
    }
    return id;
}

// Show a captain cursor on one controller's slot (fn_8004E504 takes one entry per port).
#define SHOW_CAPTAIN_CURSOR(port, sel)                 \
    switch (port) {                                    \
    case 0:                                            \
        fn_8004E504(0, (sel), -1, -1, -1);             \
        break;                                         \
    case 1:                                            \
        fn_8004E504(0, -1, (sel), -1, -1);             \
        break;                                         \
    case 2:                                            \
        fn_8004E504(0, -1, -1, (sel), -1);             \
        break;                                         \
    case 3:                                            \
        fn_8004E504(0, -1, -1, -1, (sel));             \
        break;                                         \
    }

// .text:0x00014574 size:0x21C
// Debug camera: move the eye or the 2D offset with the d-pad.
void fn_2_14574(PortInput* in) {
    f32 t;
    if (in->repeat & 8) {
        if (in->held & 0x200) {
            lbl_2_bss_1010C.eye.x += 0.1f;
        } else if (in->held & 0x100) {
            lbl_2_bss_1010C.eye.y += 1.0f;
        } else if (in->held & 0x400) {
            lbl_2_bss_1010C.eye.z += 0.1f;
        }
    } else if (in->repeat & 4) {
        if (in->held & 0x200) {
            lbl_2_bss_1010C.eye.x -= 0.1f;
        } else if (in->held & 0x100) {
            lbl_2_bss_1010C.eye.y -= 0.1f;
        } else if (in->held & 0x400) {
            lbl_2_bss_1010C.eye.z -= 0.1f;
        }
    } else if (in->repeat & 1) {
        if (in->held & 0x200) {
            t = 320.0f + lbl_2_data_20F8[0];
            t -= 0.1;
            lbl_2_data_20F8[0] = t - 320.0f;
        } else if (in->held & 0x100) {
            t = 320.0f + lbl_2_data_20F8[1];
            t -= 0.1;
            lbl_2_data_20F8[1] = t - 320.0f;
        }
    } else if (in->repeat & 2) {
        if (in->held & 0x200) {
            t = 320.0f + lbl_2_data_20F8[0];
            t += 0.1;
            lbl_2_data_20F8[0] = t - 320.0f;
        } else if (in->held & 0x100) {
            t = 320.0f + lbl_2_data_20F8[1];
            t += 0.1;
            lbl_2_data_20F8[1] = t - 320.0f;
        }
    }
}

// .text:0x00014790 size:0x428
// A second controller pressed A: it joins as player 2.
void fn_2_14790(void) {
    s8 port = -1;
    s32 i;
    s32 prev;

    if (lbl_2_bss_100B8.active == 0 || lbl_2_bss_100B8.busy != 0 || g_d_GameSettings.GameModeSelected == 5) {
        return;
    }
    if (lbl_803C66B0._0E == 1) {
        return;
    }
    for (i = 1; i < 4; i++) {
        if (lbl_8034E9A0.joined[i] && (PADS[i].down & 0x100)) {
            port = i;
            break;
        }
    }
    if (port == -1) {
        return;
    }
    if (lbl_803C5EA4._05 != 0) {
        return;
    }

    if (lbl_2_bss_100B8.picked[1] != 0) {
        lbl_2_bss_100B8.picked[1] = 0;
        lbl_2_bss_100B8._12[1] = 0;
        fn_8004E5B4(1, lbl_8034E9A0.captain[1], 0);
        lbl_8034E9A0.charFlag[lbl_8034E9A0.captain[1]] = 0;
        lbl_8034E9A0.captain[1] = -1;
    }

    lbl_8034E9A0.joined[port] = 0;
    lbl_803C5EA4._05 = 1;
    lbl_8034E9A0.teamPort[port] = lbl_8034E9A0.teamPort[1];
    lbl_8034E9A0.teamPort[1] = port;
    lbl_803C66B0.portOf[0] = 0;
    lbl_803C66B0.portOf[1] = 1;
    if (lbl_8034E9A0.charFlag[0] != 0 || lbl_2_bss_F410.sel[0] == 0) {
        lbl_803C6724.sel[1] = 1;
    } else {
        lbl_803C6724.sel[1] = 0;
    }
    lbl_803C6028._74[lbl_8034E9A0.teamPort[1]] = 0;
    fn_800625A4(1, 1);
    g_d_GameSettings._10 = 1;
    lbl_803297E0.random[1] = 0;
    lbl_803C6028._7F[1] = -1;
    if (lbl_2_bss_F410.sel[0] == 0) {
        lbl_2_bss_F410.sel[1] = 1;
    } else {
        lbl_2_bss_F410.sel[1] = 0;
    }
    lbl_803C6028._74[lbl_8034E9A0.teamPort[1]] = 0;
    SHOW_CAPTAIN_CURSOR(lbl_8034E9A0.teamPort[1], lbl_2_bss_F410.sel[1])

    for (prev = -1; !fn_2_15104(lbl_2_bss_F410.sel[1], prev, 1, 1); prev = lbl_2_bss_F410.sel[1]) {
    }

    lbl_8034E9A0._4704 = 0;
    if (lbl_2_bss_F468._45[1] != 0) {
        lbl_2_bss_F468._45[1] = 0;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    }
    lbl_8034E9A0.input[1].repeat = 0;
    lbl_8034E9A0.input[1].pressed = 0;
    lbl_8034E9A0.input[1].held = 0;
    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
}

// .text:0x00014BB8 size:0xE8
void fn_2_14BB8(u8 index, s32 mode) {
    switch (mode) {
    case 0:
        AnimateCharacter(index, 0x6A, 0, 1, 1, 0, 0, -1);
        QueueCharacterAnimation(index, 0x6B, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8.animState[index] = 0;
        break;
    case 1:
        AnimateCharacter(index, 0x69, 1, 1, 1, 0, 0, -1);
        lbl_2_bss_100B8.animState[index] = 1;
        break;
    }
}

// .text:0x00014CA0 size:0x318
// Move a player's captain cursor.
void fn_2_14CA0(u8 player, PortInput* in) {
    s32 port;
    s32 id;
    s32 i;
    u8* p;

    if (g_d_GameSettings.GameModeSelected != 5) {
        if (g_d_GameSettings._10 == 0 && player != 0) {
            port = lbl_8034E9A0.teamPort[0] == 0;
            lbl_803C6028._74[port] = 1;
        } else {
            port = lbl_8034E9A0.teamPort[player];
            lbl_803C6028._74[port] = 0;
        }
        SHOW_CAPTAIN_CURSOR(port, lbl_2_bss_F410.sel[player])
        id = fn_8004E62C(port, in->held, in->pressed, in->repeat);
        for (i = 0, p = lbl_800FE5D4; i < 12; p++, i++) {
            if (*p == id) {
                id = i;
                break;
            }
        }
        lbl_2_bss_F410.sel[player] = id;
    } else {
        id = fn_8004D57C(in->held, in->pressed, in->repeat);
        for (i = 0; i < 6; i++) {
            if (id == lbl_800FE930[lbl_80361B20._F4][i]) {
                id = i;
                break;
            }
        }
        lbl_2_bss_F410.sel[0] = id;
    }
}

// .text:0x00014FB8 size:0x118
// Pick a random captain for a player (different from the other team's).
void fn_2_14FB8(s32 player) {
    s32 ids[2];
    s32 i;

    ids[0] = lbl_80108EC4[lbl_2_bss_F410.sel[0]];
    ids[1] = lbl_80108EC4[lbl_2_bss_F410.sel[1]];
    do {
        ids[player] = fn_2_14F8(0, 19);
        for (i = 0; i < 12; i++) {
            if (lbl_80108EC4[i] == ids[player]) {
                break;
            }
        }
    } while (i == 12 || ids[0] == ids[1]);
    lbl_2_bss_F410.sel[player] = i;
}

// .text:0x000150D0 size:0x34
void fn_2_150D0(u8 index) {
    if (lbl_2_bss_100B8.loadReq[index] == 0) {
        lbl_2_bss_100B8.loadReq[index] = 1;
        lbl_2_bss_100B8.timer[index] = 0;
    }
}

// .text:0x00015104 size:0xB8
// Request the model load once the cursor has rested for 15 frames.
s32 fn_2_15104(s32 cur, s32 prev, u8 index, u8 value) {
    if (prev != cur) {
        lbl_2_bss_100B8.timer[index] = 1;
    } else if (lbl_2_bss_100B8.timer[index] != 0) {
        if (++lbl_2_bss_100B8.timer[index] >= 15) {
            lbl_2_bss_100B8.loadReq[index] = 1;
            lbl_2_bss_100B8.timer[index] = 0;
            fn_2_16A48(index, value);
        }
    }
    return lbl_2_bss_100B8.timer[index] == 0;
}

// .text:0x000151BC size:0x450
// B pressed: undo the captain pick, or leave the screen.
void fn_2_151BC(u8 player) {
    s32 i;

    if (lbl_2_bss_100B8.picked[player] != 0) {
        lbl_2_bss_100B8.picked[player] = 0;
        lbl_2_bss_100B8._12[player] = 0;
        lbl_8034E9A0.charFlag[lbl_8034E9A0.captain[player]] = 0;
        fn_8004E5B4(player, lbl_8034E9A0.captain[player], 0);
    } else if (player != 0) {
        if (lbl_803297E0.random[player] != 0) {
            lbl_803297E0.random[player] = 0;
        }
        if (g_d_GameSettings._10 == 0) {
            fn_2_16A74(player, 0);
            lbl_803C6028._7F[lbl_8034E9A0.teamPort[lbl_803C66B0.portOf[0]]] = -1;
            lbl_2_bss_100B8.picked[0] = 0;
            lbl_2_bss_100B8._12[0] = 0;
            lbl_8034E9A0.charFlag[lbl_8034E9A0.captain[0]] = 0;
            lbl_803C66B0.portOf[0] = 0;
            fn_8004E5B4(0, lbl_8034E9A0.captain[0], 0);
            lbl_8034E9A0.captain[0] = -1;
            lbl_8034E9A0.captain[1] = -1;
            fn_800625A4(0, 4);
            fn_2_14BB8(player ^ 1, 1);
        } else {
            lbl_8034E9A0.joined[lbl_8034E9A0.teamPort[1]] = 1;
            if (lbl_2_bss_100B8.picked[0] != 0) {
                lbl_803C66B0.portOf[0] = lbl_803C66B0.portOf[1] = 1;
            } else {
                lbl_803C66B0.portOf[0] = lbl_803C66B0.portOf[1] = 0;
            }
            lbl_803C5EA4._05 = 0;
            lbl_803C6028._7F[lbl_8034E9A0.teamPort[lbl_803C66B0.portOf[player]]] = -1;
            if (lbl_803CBBCC->prevScene == 10 && lbl_2_bss_100B8.picked[0] == 0) {
                lbl_8034E9A0.charFlag[lbl_8034E9A0.captain[0]] = 0;
                fn_8004E5B4(0, lbl_8034E9A0.captain[0], 0);
                lbl_8034E9A0.captain[0] = -1;
                lbl_8034E9A0.captain[1] = -1;
            }
            lbl_2_bss_100B8.picked[player] = 0;
            lbl_2_bss_100B8._12[player] = 0;
            lbl_803C66B0.portOf[player] = 0;
            if (lbl_2_bss_100B8.picked[0] != 0) {
                fn_800625A4(player, 5);
            } else {
                fn_800625A4(player, 4);
            }
        }
    } else {
        lbl_803C6028._7F[lbl_8034E9A0.teamPort[0]] = -1;
        if (lbl_8034E9A0.teamPort[1] != -1) {
            lbl_803C6028._7F[lbl_8034E9A0.teamPort[1]] = -1;
        }
        lbl_803297E0.random[1] = 0;
        lbl_803297E0.random[0] = 0;
        lbl_2_bss_100B4 = 1;
        for (i = 0; i < lbl_2_bss_100B8.count; i++) {
            fn_2_16A74(i, 0);
        }
        if (g_d_GameSettings.GameModeSelected == 5) {
            lbl_803CBBC4[0] = 2;
        } else {
            if (g_d_GameSettings._10 == 0) {
                fn_800625A4(0, 2);
                fn_800625A4(1, 2);
            } else if (g_d_GameSettings._10 == 1) {
                fn_800625A4(0, 2);
                fn_800625A4(1, 2);
            }
            lbl_803CBCD8[2] = 0x14;
        }
        lbl_2_bss_F468._45[1] = 0;
        lbl_2_bss_F468._45[0] = 0;
        lbl_803CBBCC->step = 8;
    }

    if (g_d_GameSettings._10 == 1) {
        fn_2_14BB8(player, 1);
    }
    fn_2_1C34(0x200);
}

// .text:0x0001560C size:0x484
// NONMATCHING 96%: register allocation; the original indexes sel[] from the raw param
// (clrlslwi) and keeps &g_d_GameSettings in r30
#if NONMATCHING
// A pressed: pick the captain under the cursor.
void fn_2_1560C(u8 player) {
    s32 port;

    if (g_d_GameSettings.GameModeSelected == 5) {
        if (lbl_2_bss_100B8.timer[0] != 0 || lbl_2_bss_100B8.loading[0] != 0) {
            return;
        }
        lbl_8034E9A0.captain[0] = lbl_800FE930[lbl_80361B20._F4][lbl_2_bss_F410.sel[0]];
        lbl_2_bss_100B8.picked[0] = 1;
        lbl_2_bss_100B8._12[0] = 1;
        fn_8004D4F0(lbl_8034E9A0.teamPort[0], lbl_8034E9A0.captain[0], 1);
        fn_2_14BB8(0, 0);
        lbl_803CBBCC->step = 4;
        return;
    }

    if (lbl_2_bss_100B8.timer[player] != 0 || lbl_2_bss_100B8.loading[player] != 0) {
        return;
    }
    if (g_d_GameSettings._10 == 0 && lbl_8036E548.active[player]->mode[0] == 0 && player != 0) {
        return;
    }
    fn_2_14BB8(player, 0);
    if (lbl_2_bss_100B8.picked[player] != 0) {
        return;
    }

    lbl_8034E9A0.captain[player] = lbl_800FE5D4[lbl_2_bss_F410.sel[player]];
    if (g_d_GameSettings._10 == 0 && player != 0) {
        if (lbl_8034E9A0.teamPort[0] == 0) {
            fn_8004E5B4(1, lbl_8034E9A0.captain[player], 1);
        } else {
            fn_8004E5B4(0, lbl_8034E9A0.captain[player], 1);
        }
    } else {
        fn_8004E5B4(lbl_8034E9A0.teamPort[player], lbl_8034E9A0.captain[player], 1);
    }
    lbl_2_bss_100B8.picked[player] = 1;
    lbl_2_bss_100B8._12[player] = 1;
    lbl_8034E9A0.charFlag[lbl_800FE5D4[lbl_2_bss_F410.sel[player]]] = 1;

    if (player == 0 && g_d_GameSettings._10 == 0 && g_d_GameSettings.GameModeSelected != 5) {
        fn_800625A4(1, 6);
        port = lbl_8034E9A0.teamPort[0] == 0;
        lbl_803C66B0.portOf[player] = 1;
        lbl_803C6028._74[port] = 1;
        if (lbl_2_bss_F410.sel[0] == 0) {
            lbl_2_bss_F410.sel[1] = 1;
        } else {
            lbl_2_bss_F410.sel[1] = 0;
        }
        SHOW_CAPTAIN_CURSOR(port, lbl_2_bss_F410.sel[1])
        lbl_803C6724.sel[1] = lbl_2_bss_F410.sel[1];
        fn_2_15104(lbl_2_bss_F410.sel[1], -1, 1, 1);
    }
}
#endif

// .text:0x00015A90 size:0x6C
// Step *value with left/right, wrapping in [0, max].
void fn_2_15A90(s32* value, u8 port, s32 max) {
    u16 repeat = lbl_8034E9A0.input[port].repeat;
    if (repeat & 1) {
        (*value)--;
        if (*value < 0) {
            *value = max;
        }
    } else if (repeat & 2) {
        (*value)++;
        if (*value > max) {
            *value = 0;
        }
    }
}

// .text:0x00015AFC size:0x384
// Buttons for one port on the captain select screen.
void fn_2_15AFC(s32 port, s32 held, s32 pressed, u16 repeat) {
    s8 cursor[4];
    u8 player;
    s32 id;

    if (lbl_8034E9A0.teamPort[port] == -1) {
        return;
    }
    if (lbl_803297E0.random[lbl_803C66B0.portOf[port]] != 0) {
        if (g_d_GameSettings._10 == 0 && lbl_803C66B0.portOf[0] == 1) {
            cursor[lbl_803C66B0.portOf[port]] = lbl_803C66B0.portOf[0];
        } else {
            cursor[lbl_803C66B0.portOf[port]] = lbl_8034E9A0.teamPort[lbl_803C66B0.portOf[port]];
        }
        if ((u32)lbl_803C6028._7F[cursor[lbl_803C66B0.portOf[port]]] >> 31) { // cursor free (< 0)
            if (g_d_GameSettings.GameModeSelected != 5) {
                lbl_2_bss_F410.sel[lbl_803C66B0.portOf[port]] = captainIndex(fn_8004E62C(cursor[lbl_803C66B0.portOf[port]], held, pressed, repeat));
                fn_800625A4(lbl_803C66B0.portOf[port], 3);
            } else {
                id = fn_8004D57C(held, pressed, repeat);
                lbl_2_bss_F410.sel[0] = challengeCaptainIndex(id);
                fn_2_12238();
                lbl_803CBBC4[0] = 3;
            }
            lbl_803297E0.random[lbl_803C66B0.portOf[port]] = 0;
        }
    } else if (lbl_803297E0.random[lbl_803C66B0.portOf[port]] == 0) {
        u16 trig = pressed;
        if (trig & 0x100) {
            if ((u8)fn_2_35D0(lbl_803C66B0.portOf[port]) == 0) {
                fn_2_1560C(lbl_803C66B0.portOf[port]);
            }
        } else if (trig & 0x200) {
            if ((u8)fn_2_35D0(lbl_803C66B0.portOf[port]) == 0) {
                fn_2_151BC(lbl_803C66B0.portOf[port]);
            }
        } else if (trig & 0x20) {
            if ((u8)fn_2_35D0(lbl_803C66B0.portOf[port]) == 0 && g_d_GameSettings.GameModeSelected != 5) {
                lbl_803297E0.random[lbl_803C66B0.portOf[port]] = 1;
            }
        } else if (trig & 0x10) {
            if ((u8)fn_2_35D0(lbl_803C66B0.portOf[port]) == 0) {
                player = lbl_803C66B0.portOf[port];
                if (lbl_2_bss_100B8.picked[player] == 0) {
                    lbl_2_bss_F468._45[player] = 1;
                    lbl_2_bss_F468._4B[player] = 1;
                    lbl_2_bss_F468._47[player] = 0;
                    sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                }
            }
        }
    }
}

// .text:0x00015E80 size:0x59C
// NONMATCHING 97%: two extra saved registers (r22/r23) and sel[port] indexed from the
// extended copy of port; ~97% when sel[team] is written ((s32*)&lbl_2_bss_F410)[team + 4]
#if NONMATCHING
// Captain select screen update for one port.
void fn_2_15E80(u8 port) {
    PortInput in;
    s32 i;
    s32 start;
    s32 before;
    s32 cur;
    u8 player = lbl_803C66B0.portOf[port];
    s32 team = lbl_8034E9A0.teamPort[port];

    if (lbl_2_bss_100B8.active == 0 || lbl_2_bss_100B8.busy != 0 || lbl_803C66B0.active[port] != 0 ||
        lbl_803297E0.random[player] != 0) {
        in.held = in.pressed = in.repeat = 0;
    } else if (g_d_GameSettings.GameModeSelected == 5 && lbl_803CBBC4[3] == 1) {
        in.held = in.pressed = in.repeat = 0;
    } else if (lbl_2_bss_100B8.picked[player] != 0) {
        in.held = lbl_8034E9A0.input[port].held & 0x200;
        in.pressed = lbl_8034E9A0.input[port].pressed & 0x200;
        in.repeat = lbl_8034E9A0.input[port].repeat & 0x200;
        goto buttons;
    } else if (lbl_2_bss_F468._45[player] != 0) {
        u16 pressed = lbl_8034E9A0.input[port].pressed;
        if (pressed & 2) {
            if (lbl_2_bss_F468._47[player] == 0) {
                lbl_2_bss_F468._47[player] = 1;
                lbl_2_bss_F468._49[player] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            in.repeat = in.pressed = in.held = 0;
        } else if (pressed & 1) {
            if (lbl_2_bss_F468._47[player] == 1) {
                lbl_2_bss_F468._47[player] = 0;
                lbl_2_bss_F468._49[player] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            in.repeat = in.pressed = in.held = 0;
        } else {
            if (pressed != 0 && !(pressed & 8) && !(pressed & 4)) {
                lbl_2_bss_F468._45[player] = 0;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
            in.repeat = in.pressed = in.held = 0;
        }
    } else {
        in.held = lbl_8034E9A0.input[port].held;
        in.pressed = lbl_8034E9A0.input[port].pressed;
        in.repeat = lbl_8034E9A0.input[port].repeat;
    }

    lbl_2_bss_100B8.debugCam = 0;
    lbl_2_bss_100B8.debugMenu = 0;
    if (lbl_2_bss_100B8.debugCam != 0) {
        if (lbl_2_bss_100B8.debugMenu != 0) {
            lbl_2_bss_100B8.debugCam = 0;
        } else {
            fn_2_14574(&in);
        }
        return;
    }
    if (lbl_2_bss_100B8.debugMenu != 0) {
        fn_2_14220(&in);
        return;
    }

    if (lbl_803CBBCC->prevScene == 10 && lbl_8034E9A0.captain[port] != -1 && g_d_GameSettings._10 == 0) {
        fn_8004E5B4(0, lbl_800FE5D4[lbl_2_bss_F410.sel[0]], 1);
        for (i = 0; i < 2; i++) {
            SHOW_CAPTAIN_CURSOR(lbl_8034E9A0.teamPort[i], lbl_2_bss_F410.sel[i])
        }
    }

    // (the second pressed test is redundant in the original too)
    if (lbl_2_bss_100B8.picked[player] == 0 || in.held != 0 || in.pressed != 0 || in.pressed != 0) {
        lbl_803C6724.sel[port] = lbl_2_bss_F410.sel[player];
        start = lbl_2_bss_F410.sel[team];
        do {
            before = lbl_2_bss_F410.sel[team];
            fn_2_14CA0(player, &in);
            cur = lbl_2_bss_F410.sel[team];
        } while (lbl_8034E9A0.charFlag[lbl_800FE5D4[cur]] != 0 && start != cur && before != cur);

        if (lbl_2_bss_F410.sel[port] == lbl_2_bss_F410.sel[port ^ 1] && lbl_803C5EA4._05 != 0) {
            lbl_2_bss_F410.sel[team]++;
            if (lbl_2_bss_F410.sel[team] >= 12) {
                lbl_2_bss_F410.sel[team] = 0;
            }
        } else if ((in.repeat & 0xF) == 0 || (in.repeat & 0x20)) {
        buttons:
            fn_2_15AFC(port, in.held, in.pressed, in.repeat);
        } else if (g_d_GameSettings.GameModeSelected == 5) {
            if (in.repeat & 3) {
                fn_2_12238();
                fn_800625A4(0, 3);
                lbl_803CBBC4[0] = 3;
            }
        } else if (!(in.pressed & 0x1000) && (in.repeat & 0xF) != 0) {
            fn_800625A4(player, 3);
        }
    } else {
        goto buttons;
    }
}
#endif

// .text:0x0001641C size:0x44
void fn_2_1641C(void) {
    fn_2_1A88();
    lbl_8034E9A0.joined[0] = 0;
    lbl_8034E9A0.joined[1] = -1;
    lbl_8034E9A0.joined[2] = -1;
    lbl_8034E9A0.joined[3] = -1;
    lbl_8034E9A0._4729 = 0;
}

// .text:0x00016460 size:0x204
// NONMATCHING 90%: the original keeps &lbl_2_data_19E8 in r31 from the prologue on;
// ours rematerialises it after the calls (also shifts r29-r31)
#if NONMATCHING
static inline void copyVec(Vec* dst, Vec* src) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

static inline void setMenuCamera(Vec* eye, Vec* target) {
    camera_803c639c_s* cam;
    fn_80052D70();
    cam = fn_80052768_getCamera(0);
    copyVec(&cam->eye, eye);
    copyVec(&cam->target, target);
    fn_80052968();
}

// Orbit the menu camera and rebuild its view matrix.
void fn_2_16460(void) {
    Vec angle;
    Vec offset = {0.0f, 0.0f, 100.0f};
    Mtx rotX;
    Mtx rotY;
    Mtx m;
    f32 c;
    f32 s;

    angle.x = lbl_2_bss_1010C.rotX;
    angle.y = lbl_2_bss_1010C.rotY;
    angle.z = 0.0f;
    PSVECScale(&angle, 0.0000958738f, &angle);
    PSMTXRotRad(rotX, 'X', angle.x);
    PSMTXRotRad(rotY, 'Y', angle.y);
    s = rotY[0][2];
    c = rotY[0][0];
    PSMTXConcat(rotY, rotX, m);
    PSMTXMultVec(m, &offset, &lbl_2_bss_1010C.target);
    lbl_2_bss_1010C.eye.x += lbl_2_bss_1010C.dolly * s - lbl_2_bss_1010C.strafe * c;
    lbl_2_bss_1010C.eye.z += lbl_2_bss_1010C.dolly * c + lbl_2_bss_1010C.strafe * s;
    lbl_2_bss_1010C.target.x += lbl_2_bss_1010C.eye.x;
    lbl_2_bss_1010C.target.y += lbl_2_bss_1010C.eye.y;
    lbl_2_bss_1010C.target.z += lbl_2_bss_1010C.eye.z;

    setMenuCamera(&lbl_2_data_19E8.eye, &lbl_2_data_19E8.target);
    makeLookAtMatrix(lbl_2_bss_1010C.view, &lbl_2_bss_1010C.eye, &lbl_2_data_19E8.up, &lbl_2_bss_1010C.target);
}
#endif

// .text:0x00016664 size:0x68
void fn_2_16664(void) {
    return;
}

// .text:0x000166CC size:0x58
void fn_2_166CC(void) {
    return;
}

// .text:0x00016724 size:0x14C
void fn_2_16724(void) {
    return;
}
