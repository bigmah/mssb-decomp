#include "main/file_800639BC.h"
#include "static/GameSettings.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_80008E00.h"
#include "main/file_8000F150.h"
#include "main/file_80069BDC.h"
#include "main/file_800B0724.h"
#include "main/file_800A7C08.h"
#include "main/file_80021308.h"
#include "main/file_80034F50.h"
#include "main/file_8004B284.h"
#include "Unknown/File_0x800a64e0.h"
#include "Dolphin/mtx.h"
#include "string.h"

extern SoundManager lbl_800EF808;
extern AssetLoadInstructions lbl_801092E8; // logo sound data
extern AssetLoadInstructions lbl_80109044; // message table
extern u8 lbl_80109378[]; // TODO type (spani creation desc)
extern void* lbl_803CBD30; // queue node of the logo screen task
extern u16 lbl_803CBD24;

extern u8 lbl_80361B20[0xF8]; // TODO type
extern u8 lbl_800E8754[0x28]; // TODO type
extern u8 lbl_803CB8D0[8];
extern u8 lbl_80108EC4[12];       // character ids to pick from
extern StreamTrack lbl_802E4CE8[16];
extern StreamTrack lbl_8034E478[16];
extern u8 lbl_800E87B4[15][16];   // TODO type: stream file descriptors
extern u8 lbl_800E88A4[16][2];    // stream volumes
extern s16 lbl_80108EDC[9][5];

extern s32 randRange_FUN_80042bf0(s32 lo, s32 hi);
extern void* ARAMTransfer(AssetLoadInstructions* instr, void* dest, u8 mode, u32 aramAddr);
extern void fn_80034E20(void* task, void* desc);
extern void* fn_80034CEC(void* task);

// .text:0x800639BC size:0x988
void fn_800639BC(void) {
    return;
}

// .text:0x80064344 size:0xEC
void fn_80064344(void) {
    return;
}

// .text:0x80064430 size:0x104
void fn_80064430(void) {
    return;
}

// .text:0x80064534 size:0x220
void fn_80064534(void) {
    return;
}

// .text:0x80064754 size:0x8C
s32 translateStarPitchHitIndex(u8 pitch) {
    switch (pitch) {
    case 0: return 6;
    case 1: return 7;
    case 2: return 10;
    case 3: return 11;
    case 4: return 14;
    case 5: return 15;
    case 6: return 16;
    case 7: return 17;
    case 8: return 12;
    case 9: return 13;
    case 10: return 8;
    case 11: return 9;
    }
    return -1;
}

// .text:0x800647E0 size:0x9C
u8 translateStarPitch(u8 star) {
    switch (star) {
    case 0: return 0x85;
    case 1: return 0x87;
    case 2: return 0x91;
    case 3: return 0x93;
    case 4: return 0x99;
    case 5: return 0x9B;
    case 6: return 0x8D;
    case 7: return 0x8F;
    case 8: return 0x89;
    case 9: return 0x8B;
    case 10: return 0x95;
    case 11: return 0x97;
    case 12: return 0xA1;
    case 13: return 0xA0;
    case 14: return 0xA2;
    }
    return star;
}

// .text:0x8006487C size:0x9C
u8 translateStarSwing(u8 star) {
    switch (star) {
    case 0: return 0x84;
    case 1: return 0x86;
    case 2: return 0x90;
    case 3: return 0x92;
    case 4: return 0x98;
    case 5: return 0x9A;
    case 6: return 0x8C;
    case 7: return 0x8E;
    case 8: return 0x88;
    case 9: return 0x8A;
    case 10: return 0x94;
    case 11: return 0x96;
    case 12: return 0x9D;
    case 13: return 0x9E;
    case 14: return 0x9F;
    }
    return star;
}

// .text:0x80064918 size:0x54
u8 fn_80064918(s16 charId) {
    switch (charId) {
    case 0: case 1:
        return 4;
    case 4: case 5: case 11: case 14:
        return 1;
    case 3: case 28: case 33: case 34: case 35: case 36: case 39: case 47:
        return 2;
    case 12: case 16: case 32: case 40: case 44: case 45: case 46: case 48: case 51:
        return 5;
    case 6: case 7: case 8: case 13: case 15: case 18: case 20: case 24: case 25: case 26:
    case 29: case 30: case 31: case 41: case 43:
        return 3;
    }
    return 0;
}

// .text:0x8006496C size:0x50
void fn_8006496C(void) {
    CharSelectState* cs = &lbl_8034E9A0;

    g_d_GameSettings.PlayerPorts[0] = cs->ports[0];
    if (g_d_GameSettings._10 == 0) {
        if (cs->ports[0] == 0) {
            g_d_GameSettings.PlayerPorts[1] = 5;
        } else {
            g_d_GameSettings.PlayerPorts[1] = 4;
        }
    } else {
        g_d_GameSettings.PlayerPorts[1] = cs->ports[1];
    }
}

// .text:0x800649BC size:0x48
void fn_800649BC(void) {
    g_d_GameSettings.home_AwaySetting = randRange_FUN_80042bf0(0, 1);
    lbl_800E8754[0] = 3;
    lbl_800E8754[3] = lbl_803CB8D0[0];
}

// .text:0x80064A04 size:0x13E8
void unsure_FillRosterPositions(void) {
    return;
}

// .text:0x80065DEC size:0x10C0
void characterSelectScreen(void) {
    return;
}

// .text:0x80066EAC size:0x1F4
void fn_80066EAC(void) {
    return;
}

// .text:0x800670A0 size:0x15C
void fn_800670A0(void) {
    return;
}

// .text:0x800671FC size:0x68
void fn_800671FC(void) {
    u8 stadium;

    if (lbl_80361B20[0xF5] != 0) {
        stadium = randRange_FUN_80042bf0(0, 5);
    } else {
        do {
            stadium = randRange_FUN_80042bf0(0, 5);
        } while (stadium == 1);
    }
    g_d_GameSettings.StadiumID = stadium;
}

// .text:0x80067264 size:0x360
void fn_80067264(void) {
    return;
}

// .text:0x800675C4 size:0x308
void fn_800675C4(void) {
    return;
}

// .text:0x800678CC size:0x1FC
void fn_800678CC(void) {
    return;
}

// .text:0x80067AC8 size:0x78
s16 fn_80067AC8(s16 id, s8 col) {
    s32 row;
    s32 i;

    for (row = 0; row < 9; row++) {
        for (i = 0; i < 5; i++) {
            if (id == lbl_80108EDC[row][i]) {
                if (col == -1) {
                    return id;
                }
                return lbl_80108EDC[row][col];
            }
            if (lbl_80108EDC[row][i] == -1) {
                break;
            }
        }
    }
    return -1;
}

// .text:0x80067B40 size:0x108
void fn_80067B40(void) {
    return;
}

// .text:0x80067C48 size:0x328
void fn_80067C48(void) {
    return;
}

// .text:0x80067F70 size:0x534
void fn_80067F70(void) {
    return;
}

// .text:0x800684A4 size:0x70
void fn_800684A4(void) {
    s32* cap = lbl_8034E9A0.captain;

    cap[0] = lbl_80108EC4[randRange_FUN_80042bf0(0, 12)];
    do {
        cap[1] = lbl_80108EC4[randRange_FUN_80042bf0(0, 12)];
    } while (cap[0] == cap[1]);
}

// .text:0x80068514 size:0x118
void fn_80068514(void) {
    return;
}

// .text:0x8006862C size:0xF4
void fn_8006862C(void) {
    return;
}

// .text:0x80068720 size:0x5C
void fn_80068720(u8 track) {
    if (lbl_800EF808.unk398 != 0) {
        fn_800A86B4(3);
        fn_800A8B78(&lbl_802E4CE8[track]);
    }
}

// .text:0x8006877C size:0xBC
void fn_8006877C(u8 track) {
    if (lbl_800EF808.unk398 != 0) {
        fn_800A8878(lbl_800E88A4[track][0], lbl_800E88A4[track][0]);
        if (track == 12) {
            fn_800A8AB0(0);
        } else {
            fn_800A8AB0(2);
        }
        fn_800A8E30(lbl_800E87B4[track], &lbl_8034E478[track], 0, NULL);
        fn_800A86B4(4);
        fn_800A86B4(1);
    }
}

// .text:0x80068838 size:0xF78
void fn_80068838(void) {
    return;
}

// .text:0x800697B0 size:0xA4
void fn_800697B0(void) {
    return;
}

// .text:0x80069854 size:0xA4
void fn_80069854(void) {
    return;
}

// .text:0x800698F8 size:0x170
void fn_800698F8(void) {
    return;
}

// .text:0x80069A68 size:0x30
void fn_80069A68(void) {
    fn_80021518(0x35, lbl_800EF808.groups[47]);
}

// .text:0x80069A98 size:0x3C
void fn_80069A98(void) {
    fn_80034CEC(lbl_803CBD30);
    lbl_803CBD30 = NULL;
    lbl_80366158._2A = 2;
}

// .text:0x80069AD4 size:0x34
void fn_80069AD4(void) {
    if (lbl_80366158._2A == 2) {
        fn_800B0A14_removeQueue(&lbl_80366158);
    }
}

// .text:0x80069B08 size:0x60
void fn_80069B08(void) {
    SceneTask* task = lbl_803CC1B8;

    if (lbl_80366158._2A != 0) {
        lbl_80371C30[task->u14.objIdx].obj->_5C = 0;
        lbl_80371C30[task->u14.objIdx].obj->flags |= 2;
        lbl_803CC1B8->func = fn_80069AD4;
    }
}

// .text:0x80069B68 size:0x74
// NONMATCHING 97%: the original called fn_80035838 without its u8 return prototype (cmpwi, no clrlwi.)
#if NONMATCHING
BOOL fn_80069B68(void) {
    if (fn_80035838(&lbl_801092E8, 0x16) != 0) {
        lbl_803CBD30 = fn_800B0A5C_insertQueue(fn_80069B08, lbl_803CC1B8->priority);
        fn_80034E20(lbl_803CBD30, lbl_80109378);
        lbl_80366158._2A = 0;
        return TRUE;
    }
    return FALSE;
}
#endif
