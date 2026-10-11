#include "game/auto_00_000E911C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"

// Layout object (LayoutObj in main/file_8000F150.h), only the fields used here.
typedef struct ResultsSprite {
    /*0x00*/ u8 _00[0x54];
    /*0x54*/ u32 flags;
    /*0x58*/ u8 _58[0x4];
    /*0x5C*/ u32 frame; // 16.16
    /*0x60*/ u8 _60[0x4];
    /*0x64*/ u16 anim;
    /*0x66*/ u8 _66[2];
    /*0x68*/ u8 visible;
    /*0x69*/ u8 animState;
} ResultsSprite;

typedef struct ResultsSlot {
    /*0x0*/ ResultsSprite* obj;
    /*0x4*/ u32 _04;
} ResultsSlot;

extern ResultsSlot lbl_80371C30[];
extern ResultsTask* lbl_803CC1B8;
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_800EFBA4[];
extern u16 lbl_3_data_81DC[];
extern u16 lbl_3_data_81FC[];
extern u8 lbl_3_data_8404[]; // [stadium][0x1E]
extern u8 lbl_3_data_84B8[];
// The original reaches these through the lbl_3_data_19770 pool base
// (+0x1838, +0x1840, +0x2060); they live inside lbl_3_data_1A730.
extern u8 lbl_3_data_1A730[];
#define RESULTS_ANIM_B ((u16*)(lbl_3_data_1A730 + 0x878))
#define RESULTS_DESC   (lbl_3_data_1A730 + 0x880)
#define RESULTS_ANIM_A ((u16*)(lbl_3_data_1A730 + 0x10A0))

extern void fn_80034E20(void*, void*);
extern void fn_3_1079C8(u8* out, s32 mode);
extern void fn_3_90064(s32 id);
extern s32 fn_3_125424(u8* a, s32 i, u32 v);
extern void sndFXCtrl(int, int, u8);
extern s32 sndFXStartEx(u16, u8, u8, u8);

#define SPRITE(task, n) (lbl_80371C30[(task)->baseIdx + (n)].obj)

// .text:0x000E911C size:0xC14 mapped:0x807281B0
// NONMATCHING 87%: the original keeps a second copy of the task pointer (r30) and a
// pooled lbl_3_data_19770 base (r27) for the RESULTS_* tables (nmverify flags
// lbl_3_data_1A730 for that reason); loops over sprites get unrolled differently.
#if NONMATCHING
void fn_3_E911C(void) {
    ResultsTask* task = lbl_803CC1B8;
    u16 mode = task->mode;
    ResultsOrder order[4];
    u32 tick = 0;
    u32 i;
    u32 stadium;
    u8 vol;
    s32 voice;
    u32 n;
    s32 idx;
    s8 chara;
    u8 player;

    if (mode != 0) {
        if (lbl_3_common_bss_32724[0x96] != 0 || g_GameLogic.gameStatus != 0x26) {
            fn_800B0A14_removeQueue(fn_80034CEC(task));
            return;
        }
    } else if (lbl_3_common_bss_32724[0x96] != 0 || g_GameLogic.gameStatus != 3) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }

    switch (task->state) {
    case 0:
        fn_80034E20(task, RESULTS_DESC);
        if (task->mode != 0) {
            if (g_Minigame._1E2A >= 6) {
                SPRITE(task, 0)->anim = 0x170;
                fn_3_90064(lbl_3_data_81FC[0x36]);
            } else {
                SPRITE(task, 0)->anim = 0x16F;
                fn_3_90064(lbl_3_data_81FC[0x25]);
            }
        } else {
            if (g_Minigame.toyField_turnNumber == 0) {
                SPRITE(task, 0)->anim = 0x171;
            } else {
                SPRITE(task, 0)->anim = 0x16F;
            }
            stadium = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                vol = lbl_3_data_84B8[0x1C];
            } else {
                vol = lbl_3_data_8404[stadium * 0x1E + 0x1C];
            }
            voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 0xE, vol, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                vol = lbl_3_data_84B8[0x1D];
            } else {
                vol = lbl_3_data_8404[stadium * 0x1E + 0x1D];
            }
            sndFXCtrl(voice, 0x5B, vol);
        }
        if (task->mode != 0) {
            task->kind = 0;
        } else {
            task->kind = 2;
        }
        i = 0;
        do {
            idx = task->baseIdx + i;
            i++;
            lbl_80371C30[idx + 0x38].obj->flags &= ~2;
        } while (i < 4);
        if (task->kind == 2 && g_Minigame.toyField_turnNumber == 0) {
            SPRITE(task, 0x1B)->flags &= ~2;
            i = 0;
            do {
                idx = task->baseIdx + i;
                i++;
                lbl_80371C30[idx + 0x1C].obj->flags &= ~2;
            } while (i < 4);
        }
        task->state = 1;
        break;

    case 1:
        if (mode != 0) {
            if (task->round != 0) {
                fn_3_1079C8((u8*)order, 1);
            } else {
                fn_3_1079C8((u8*)order, 2);
            }
        } else {
            fn_3_1079C8((u8*)order, 0);
        }
        if (task->mode == 0 && g_Minigame.toyField_turnNumber == 0) {
            SPRITE(task, 2)->anim = 0x183;
        } else {
            SPRITE(task, 2)->anim = 0x184;
        }
        SPRITE(task, 2)->frame = 0;
        SPRITE(task, 2)->visible = 1;
        for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
            player = order[i].player;
            chara = g_Minigame.minigameControlStruct[0].characterIndex[player];
            SPRITE(task, i + 3)->frame = task->kind << 16;
            SPRITE(task, i + 7)->frame = chara << 16;
            // TODO type: inMemRoster indexed flat by character
            SPRITE(task, i * 2 + 0xF)->frame = (&inMemRoster[0][0])[chara].stats.CharID << 16;
            SPRITE(task, i * 2 + 0x10)->frame = (&inMemRoster[0][0])[chara].stats.CharID << 16;
            SPRITE(task, i + 0x17)->anim = RESULTS_ANIM_A[order[i].rank];
            SPRITE(task, i + 0x1C)->anim = RESULTS_ANIM_B[order[i].rank];
            if (task->mode != 0) {
                if (task->round != 0) {
                    task->score[i] = g_Minigame._1E22[player];
                } else {
                    task->score[i] = g_Minigame._1E26[player];
                }
            } else {
                task->score[i] = g_Minigame.miniGameCurrentPoints[player];
            }
            SPRITE(task, i * 3 + 0x24)->frame = 0;
            SPRITE(task, i * 3 + 0x25)->frame = 0;
            SPRITE(task, i * 3 + 0x26)->frame = 0;
            SPRITE(task, i * 3 + 0x24)->visible = 1;
            SPRITE(task, i * 3 + 0x25)->visible = 1;
            SPRITE(task, i * 3 + 0x26)->visible = 1;
            if (task->mode != 0 && task->round == 0) {
                task->bonus[i] = g_Minigame._1E22[player] - g_Minigame._1E26[player];
                n = task->bonus[i];
                if (n > 99) {
                    n = 99;
                }
                if (n >= 10) {
                    fn_800363D8(task, i + 0x3C, 1, 0x174, 11);
                } else {
                    fn_800363D8(task, i + 0x3C, 1, 0x174, 10);
                }
                if (n >= 10) {
                    fn_800363D8(task, i + 0x3C, 2, 0x174, (n % 100) / 10);
                } else {
                    fn_800363D8(task, i + 0x3C, 2, 0x174, 11);
                }
                fn_800363D8(task, i + 0x3C, 3, 0x174, n % 10);
            }
            SPRITE(task, i + 0x3C)->frame = 0;
            SPRITE(task, i + 0x3C)->visible = 0;
        }
        task->state = 2;
        // fallthrough
    case 2:
        switch (task->kind) {
        case 0:
        case 1:
            if (task->round != 0) {
                if (g_GameLogic._125 >= 5) {
                    task->state = 7;
                }
            } else if (SPRITE(task, 2)->animState == 2) {
                task->state = 5;
            }
            break;
        case 2:
            if (g_Minigame.toyField_turnNumber == 0 && SPRITE(task, 2)->animState == 2) {
                task->timer = 0;
                task->state = 3;
            }
            break;
        }
        break;

    case 3:
        task->timer++;
        if (task->timer >= 4) {
            task->timer = 0;
            task->cursor++;
            if (task->cursor >= 4) {
                task->cursor = 0;
            }
            for (i = 0; i < 4; i++) {
                if (i == task->cursor) {
                    SPRITE(task, i + 0x38)->flags |= 2;
                } else {
                    SPRITE(task, i + 0x38)->flags &= ~2;
                }
            }
            if (task->cursor == g_Minigame.rosterID) {
                task->spins++;
                if (task->spins >= 5) {
                    SPRITE(task, g_Minigame.rosterID + 0x38)->visible = 1;
                    task->state = 4;
                }
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        break;

    case 5:
        for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
            if (task->bonus[i] != 0) {
                ResultsSprite* spr = SPRITE(task, i + 0x3C);
                if ((spr->frame >> 16) >= 9) {
                    spr->visible = 0;
                    task->timer = 0;
                    task->state = 6;
                } else {
                    spr->visible = 1;
                }
            }
        }
        break;

    case 6:
        task->timer++;
        if (task->timer >= 4) {
            for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
                if (task->bonus[i] != 0) {
                    tick = 1;
                    task->score[i]++;
                    task->bonus[i]--;
                }
            }
            task->timer = 0;
        }
        for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
            if (task->bonus[i] != 0) {
                break;
            }
        }
        if (i >= g_Minigame.miniGameNumberOfParticipants && g_GameLogic._125 >= 3) {
            task->state = 7;
        }
        break;

    case 7:
        if (fn_3_125424((u8*)task, 2, 0) != 0) {
            switch (task->kind) {
            case 0:
                if (task->round == 0) {
                    if (g_Minigame._1E2A >= 6) {
                        task->kind = 1;
                    }
                    task->round = 1;
                    task->state = 1;
                }
                break;
            }
        }
        break;
    }

    if (task->state >= 1) {
        for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
            n = task->score[i];
            if (task->mode != 0) {
                if (n > 99) {
                    n = 99;
                }
            } else if (n > 999) {
                n = 999;
            }
            fn_800363D8(task, i * 3 + 0x24, 1, 0x66, (n % 1000) / 100);
            fn_800363D8(task, i * 3 + 0x25, 1, 0x66, (n % 100) / 10);
            fn_800363D8(task, i * 3 + 0x26, 1, 0x66, n % 10);
        }
    }
    if (tick != 0) {
        sndFXStartEx(0x1C1, lbl_800EFBA4[0xA], 0x3F, 0);
    }
}
#endif
