#include "game/auto_00_0011D3AC_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"
#include "game/auto_00_000E911C_text.h"
#include "game/rep_1838.h"

extern MinigameAssets lbl_3_common_bss_32724;
extern MinigameCharMgrAssets lbl_8036E548;
extern PasswordSlot lbl_80371C30[];
extern void* lbl_803CC1B8; // current queue task
extern u8 lbl_803C6CF8[];  // ARAMLoader; [0x715]: transfer done
extern u8 lbl_3_common_bss_34C90[];
extern u8 lbl_800EFBA4[];
extern u8 lbl_3_data_225F0[];        // ARAM load instructions at +0x10
extern u8 lbl_3_data_25464[];        // sprite descriptors (fn_80034E20)
extern u8 lbl_3_data_25A24[];
extern u8 lbl_3_data_25EE4[];
extern u8 lbl_3_data_26254[];
extern u8 lbl_3_data_261C4[9][16];   // password digit substitution tables
extern u16 lbl_3_data_81FC[];        // sound ids

extern void LoadActorLayout(void* layout);
extern void convertGeometryAndSknHeader(void* geometry, void* skin);
extern void fn_80034E20(void* group, void* descs);
extern void fn_3_109DE0(PasswordRecord* out);
extern s32 fn_3_107988(u32 pick);
extern s32 fn_3_107C88(void);
extern u8 fn_3_107CD0(void);
extern u32 fn_3_90064(s32 id);
extern s32 sndFXKeyOff(u32 voice);
extern s32 sndFXCtrl(u32 voice, u8 ctrl, u8 value);
extern s32 sndFXStartEx(u16 fid, u8 vol, u8 pan, u8 studio);

#define MG11D3 ((MG11D3View*)&g_Minigame)
#define SPRITE(task, n) (lbl_80371C30[(task)->baseIdx + (n)].obj)
// Sprite k + i of a task; this operand order is what the original compiles to.
#define SPRITE_I(task, k, i) (lbl_80371C30[(k) + (task)->baseIdx + (i)].obj)

// .text:0x0011D3AC size:0x2F4 mapped:0x8075C440
void fn_3_11D3AC(void) {
    return;
}

// .text:0x0011D6A0 size:0xE0 mapped:0x8075C734
// Loads the result-screen assets; returns 1 once done.
s32 fn_3_11D6A0(void) {
    switch (lbl_3_common_bss_32724.loadState) {
    case 0:
        lbl_8036E548.file = (u32*)ARAMTransfer(lbl_3_data_225F0 + 0x10, 0, 0, 0); // TODO type
        lbl_3_common_bss_32724.loadState++;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            lbl_3_common_bss_32724.loadState++;
        }
        break;
    case 2:
        if (g_d_GameSettings.GameModeSelected != 6) {
            fn_3_11D3AC();
        }
        lbl_3_common_bss_32724.loadState++;
        break;
    default:
        return 1;
    }
    return 0;
}

// .text:0x0011D780 size:0x34C mapped:0x8075C814
// Password display task.
void fn_3_11D780(void) {
    PasswordTask* task = lbl_803CC1B8;
    u8 raw[8];
    u8 code[16];
    u32 i;

    if (lbl_3_common_bss_32724.quit != 0) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    if (g_Minigame._1A3C != 0) {
        if (g_GameLogic._125 == 4) {
            fn_800B0A14_removeQueue(fn_80034CEC(task));
            return;
        }
        if (g_GameLogic.gameStatus != 0x24) {
            fn_800B0A14_removeQueue(fn_80034CEC(task));
            return;
        }
    } else {
        if (g_GameLogic._125 == 3) {
            fn_800B0A14_removeQueue(fn_80034CEC(task));
            return;
        }
        if (g_GameLogic.gameStatus != 0xE) {
            fn_800B0A14_removeQueue(fn_80034CEC(task));
            return;
        }
    }
    if (g_Minigame._1907 != 1) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }

    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_26254);
        if (g_Minigame._1A3C != 0) {
            SPRITE(task, 0)->anim = 0xBF;
            task->_1E = 3;
        } else {
            SPRITE(task, 0)->anim = 0xBE;
            task->_1E = 7;
        }
        task->bits = random_fn_3_9EE24(0x100);
        task->key = random_fn_3_9EE24(0x1A);
        task->state = 1;
        // fallthrough
    case 1:
        fn_3_11DACC(code, raw, task->bits, task->key);
        i = 0;
        do {
            fn_800363D8(task, i + 2, 1, 0xBD, code[i]);
            fn_800363D8(task, i + 2, 2, 0xBD, code[i]);
            i++;
        } while (i < 16);
        task->state = 2;
        break;
    case 2:
        if (g_GameLogic._125 == task->_1E) {
            SPRITE(task, 0)->visible = 1;
            SPRITE(task, 0)->frame = 0;
            SPRITE(task, 1)->visible = 1;
            SPRITE(task, 1)->frame = 0;
            i = 0;
            do {
                SPRITE_I(task, 2, i)->frame = 0;
                i++;
            } while (i < 16);
            task->state = 3;
        }
        break;
    case 3:
        if (g_GameLogic._125 != task->_1E) {
            SPRITE(task, 0)->visible = 4;
            SPRITE(task, 0)->frame = 0x140000;
            SPRITE(task, 1)->visible = 4;
            task->state = 2;
        }
        break;
    }
}

// .text:0x0011DACC size:0x2F8 mapped:0x8075CB60
void fn_3_11DACC(void) {
    return;
}

// .text:0x0011DDC4 size:0xBC mapped:0x8075CE58
// CRC-16 (reflected CCITT polynomial 0x8408, initial value 0).
u16 fn_3_11DDC4(u8* data, u32 len) {
    u32 crc = 0;
    u32 b;
    u32 i;
    u32 j;

    for (i = 0; i < len; i++, data++) {
        b = *data;
        for (j = 0; j < 8; j++) {
            if ((crc ^ b) & 1) {
                crc >>= 1;
                crc ^= 0x8408;
            } else {
                crc >>= 1;
            }
            b >>= 1;
        }
    }
    return crc;
}

// .text:0x0011DE80 size:0x4C mapped:0x8075CF14
void fn_3_11DE80(void) {
    if (g_GameLogic._125 == 0) {
        MG11D3->rouletteTask = fn_800B0A5C_insertQueue(fn_3_11DECC, 2);
    }
}

// .text:0x0011DECC size:0x43C mapped:0x8075CF60
void fn_3_11DECC(void) {
    return;
}

// .text:0x0011E308 size:0x5C mapped:0x8075D39C
void fn_3_11E308(void) {
    if (g_GameLogic._125 == 1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
        ((ResultsTask*)fn_800B0A5C_insertQueue(fn_3_E911C, 2))->mode = 1;
    }
}

// The score boards close when the minigame quits, ends or a pause menu leaves it.
static inline s32 ScoreBoard_ShouldClose(void) {
    if (lbl_3_common_bss_32724.quit != 0 || lbl_3_common_bss_32724._B7 != 0) {
        return 1;
    }
    if (g_GameLogic.gameStatus == 0xF) {
        return 1;
    }
    if (g_Minigame.pauseInd != 0) {
        switch (lbl_3_common_bss_34C90[0x1D2]) { // TODO type: MinigameBss34C90View._1D2
        case 7:
        case 9:
            return 1;
        case 13:
            return 1;
        }
    }
    if (g_GameLogic.gameStatus == 0xE && g_GameLogic.FrameCountOfCurrentPitch == 0) {
        return 1;
    }
    return 0;
}

// .text:0x0011E364 size:0x460 mapped:0x8075D3F8
void fn_3_11E364(void) {
    return;
}

// .text:0x0011E7C4 size:0x464 mapped:0x8075D858
void fn_3_11E7C4(void) {
    return;
}
