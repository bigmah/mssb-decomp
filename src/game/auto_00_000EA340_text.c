#include "game/auto_00_000EA340_text.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    u8* p;
    s32 pad;
} QEnt;

extern u8 lbl_3_common_bss_32724[];
extern u8 g_GameLogic[];
extern u8 lbl_80371C30[];
typedef struct {
    void* fn;
    u8 pad[0x10];
    u16 u14;
    u16 u16_;
    u16 u18;
    u16 u1A;
    u16 u1C;
    u16 u1E;
} QObj;
extern u8* lbl_803CC1B8;
extern u8 lbl_3_data_8EC4[];
extern u8 lbl_3_data_900C[];
extern u8 inMemRoster[];
extern void fn_3_E9D30(void);
extern u8 g_UnkSound_32718[];
extern u8 lbl_800EF808[];
extern u8 lbl_3_data_19830[];
extern u8 g_Ball[];
extern u8 g_Pitcher[];
extern u8 lbl_3_common_bss_34C90[];
extern void fn_3_9C28C(void);
extern void fn_3_9894C(void);
extern void fn_3_98DE0(void);
extern void fn_3_EA8FC(void);
extern void fn_3_EB6E0(void);
extern void fn_3_129458(void);
extern void fn_3_9143C(void);
extern void fn_3_96914(void);
extern void fn_3_97144(void*);
extern void fn_3_EAEF4(void);
extern void fn_3_EDA3C(void);
extern void fn_3_1254F8(void);
extern void fn_3_126604(void);
extern void fn_3_1274B4(void);
extern void fn_3_128B90(void);
extern void fn_3_E911C(void);
extern void fn_3_12C3F0(void);
extern void fn_3_12B7A0(void);
extern void fn_3_12A6C4(void);
extern void fn_80053FE8(void);
extern void fn_80051D00(void);
extern void fn_8004D0F0(void);
extern void fn_80050F78(s32);
extern void fn_8004CC4C(u8, u8, u8, s32, s16);
extern u8 lbl_8034E978[];
extern u8 lbl_800FEF70[];
extern u8 lbl_3_data_19770[];
extern u8 lbl_3_data_8FCC[];
extern u8 lbl_3_data_8F64[];
extern u16 lbl_3_data_8FC4[];
extern u16 lbl_3_data_81DC[];
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
extern void sndFXCtrl(int, int, u8);
extern s32 sndFXStartEx(u16, u8, u8, u8);
extern u8 lbl_3_data_8F24[];
extern u8 lbl_3_data_8E68[];
extern u8 lbl_3_data_8EA8[];
extern u8 g_Minigame[];
extern void fn_80034E20(void*, void*);
extern void fn_3_ED2F4(void);
extern void fn_3_ED0F4(void);
extern void fn_3_EC014(void);
extern void fn_3_ED6E0(void);

// Typed views for the functions below. g_Minigame, lbl_80371C30 and
// lbl_803CC1B8 are declared as raw bytes in this file (the older functions
// index them by offset), so the newer code reaches them through these.
typedef struct EaSprite {
    /*0x00*/ u8 _00[0x48];
    /*0x48*/ f32 x;
    /*0x4C*/ f32 y;
    /*0x50*/ u8 _50[0x4];
    /*0x54*/ u32 flags;
    /*0x58*/ u32 color;
    /*0x5C*/ u32 frame; // 16.16
    /*0x60*/ u8 _60[0x4];
    /*0x64*/ u16 anim;
    /*0x66*/ u8 _66[2];
    /*0x68*/ u8 visible;
    /*0x69*/ u8 animState;
} EaSprite;

typedef struct EaSlot {
    /*0x0*/ EaSprite* obj;
    /*0x4*/ u32 _04;
} EaSlot;

// Minigame HUD task (queue item).
typedef struct EaTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x10];
    /*0x14*/ u16 baseIdx;
    /*0x16*/ u16 _16;
    /*0x18*/ u16 param; // set by the creator
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 _1E;
    /*0x20*/ u16 _20;
    /*0x22*/ u16 _22;
} EaTask;

// g_Minigame (MiniGameStruct in game/UnknownHomes_Game.h), only the fields used here.
typedef struct EaMinigame {
    /*0x0000*/ u8 _0000[0x1890];
    /*0x1890*/ s16 points[4]; // miniGameCurrentPoints
    /*0x1898*/ u8 _1898[0x18BC - 0x1898];
    /*0x18BC*/ struct {
        s16 _0;
        s16 delta;
    } _18BC[4];
    /*0x18CC*/ s8 characterIndex[4]; // minigameControlStruct[0]
    /*0x18D0*/ u8 _18D0[0x18E0 - 0x18D0];
    /*0x18E0*/ s8 order[4];
    /*0x18E4*/ u8 _18E4[0x18F4 - 0x18E4];
    /*0x18F4*/ s8 player[3];
    /*0x18F7*/ u8 _18F7[0x1906 - 0x18F7];
    /*0x1906*/ u8 numPlayers;
    /*0x1907*/ u8 _1907[2];
    /*0x1909*/ u8 _1909;
    /*0x190A*/ u8 _190A;
    /*0x190B*/ u8 _190B;
    /*0x190C*/ u8 turn;
    /*0x190D*/ u8 _190D[0x1921 - 0x190D];
    /*0x1921*/ u8 _1921;
    /*0x1922*/ u8 _1922[0x19A0 - 0x1922];
    /*0x19A0*/ u8 _19A0;
    /*0x19A1*/ u8 _19A1[0x19CD - 0x19A1];
    /*0x19CD*/ u8 _19CD;
    /*0x19CE*/ u8 _19CE[0x1A2A - 0x19CE];
    /*0x1A2A*/ u8 game;  // indexes the per-game tables
    /*0x1A2B*/ u8 _1A2B;
    /*0x1A2C*/ u8 _1A2C[0x1A3C - 0x1A2C];
    /*0x1A3C*/ u8 _1A3C;
} EaMinigame;

#define EA_MG (*(EaMinigame*)g_Minigame)
#define EA_TASK ((EaTask*)lbl_803CC1B8)
#define EA_SPRITE(task, n) (((EaSlot*)lbl_80371C30)[(task)->baseIdx + (n)].obj)
// TODO type: inMemRoster is CharacterStats[2][9] (stride 0xA0), declared as bytes here
#define EA_CHAR_ID(i) (*(s16*)(inMemRoster + (i) * 0xA0 + 0x24))

extern void fn_3_ED058(void);

// .text:0x000EA340 size:0x114 mapped:0x807293D4
// NONMATCHING 95%: `add r7, r0, r4` operand order of baseIdx + i (3 sites)
#if NONMATCHING
void fn_3_EA340(void) {
    EaTask* task = EA_TASK;
    s32 i;
    s32 frame;

    fn_80034E20(task, lbl_3_data_900C);
    for (i = 0; i < 3; i++) {
        if (EA_MG.player[i] >= 0) {
            frame = EA_MG.characterIndex[EA_MG.player[i]] << 16;
            EA_SPRITE(task, i + 3)->frame = frame;
            EA_SPRITE(task, i + 6)->frame = frame;
            EA_SPRITE(task, i + 9)->frame = EA_CHAR_ID(EA_MG.player[i]) << 16;
        }
    }
    task->param = 0;
    EA_TASK->func = fn_3_E9D30;
}
#endif

// .text:0x000ED0F4 size:0x150 mapped:0x8072C188
// NONMATCHING 97%: scheduling of the sprite/table address computations
#if NONMATCHING
void fn_3_ED0F4(void) {
    EaTask* task = EA_TASK;
    u32 stadium;
    u8 vol;
    s32 voice;

    fn_80034E20(task, lbl_3_data_8F64);
    EA_SPRITE(task, 1)->anim = lbl_3_data_8FC4[EA_MG._1921 - 1];
    stadium = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[0x38];
    } else {
        vol = lbl_3_data_8404[stadium * 0x1E + 0x38];
    }
    voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x1C, vol, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[0x39];
    } else {
        vol = lbl_3_data_8404[stadium * 0x1E + 0x39];
    }
    sndFXCtrl(voice, 0x5B, vol);
    task->param = 0;
    EA_MG._19CD = 1;
    EA_TASK->func = fn_3_ED058;
}
#endif

// The game data around lbl_3_data_19770 is addressed from that symbol as a pool
// base; these are the tables at lbl_3_data_19830 + 0xE0/0x140/0x148/0x150.
typedef struct EaPool {
    /*0x0000*/ u8 _0000[0x1A0];
    /*0x01A0*/ u8 desc1A0[0x60];  // sprite layout for fn_3_EC804
    /*0x0200*/ u16 anim200[4];
    /*0x0208*/ u16 stop208[4];
    /*0x0210*/ u16 end210[4];
    /*0x0218*/ u8 _0218[0x1280 - 0x218];
    /*0x1280*/ u8 desc1280[0x580]; // sprite layout for fn_3_EA454
    /*0x1800*/ u16 title1800[8];   // [game]
    /*0x1810*/ u16 sub1810[4];
    /*0x1818*/ u16 sub1818[4];
    /*0x1820*/ u16 count1820[4];   // [numPlayers - 1]
    /*0x1828*/ u16 frame1828[8];   // [game]
    /*0x1838*/ u16 rank1838[4];
} EaPool;
#define EA_POOL ((EaPool*)lbl_3_data_19770)
typedef struct EaMgFlags {
    /*0x1934*/ u8 _1934;
    /*0x1935*/ s8 _1935;
    /*0x1936*/ s8 _1936;
} EaMgFlags;
#define EA_MG_FLAGS (*(EaMgFlags*)(g_Minigame + 0x1934)) // TODO type

// .text:0x000EC804 size:0x3AC mapped:0x8072B898
// NONMATCHING 93%: original indexes the pooled tables as `addi rT, pool, 0x200; lhzx` (data lives in another
// unit, so the pool can't be reproduced); prologue scheduling
#if NONMATCHING
void fn_3_EC804(void) {
    EaTask* task = EA_TASK;
    u8* q = g_Minigame + 0x1DF4;
    EaPool* pool = EA_POOL;
    u32 stadium;
    u8 vol;
    s32 voice;

    if (lbl_3_common_bss_32724[0x96] != 0) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    if (g_GameLogic[0x11E] == 8) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, pool->desc1A0);
        EA_SPRITE(task, 0)->anim = pool->anim200[EA_MG_FLAGS._1936];
        EA_SPRITE(task, 1)->anim = (task->param != 0) + 0xF;
        task->_1E = pool->stop208[EA_MG_FLAGS._1936];
        task->_20 = pool->end210[EA_MG_FLAGS._1936];
        stadium = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            vol = lbl_3_data_84B8[0x20];
        } else {
            vol = lbl_3_data_8404[stadium * 0x1E + 0x20];
        }
        voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x10, vol, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            vol = lbl_3_data_84B8[0x21];
        } else {
            vol = lbl_3_data_8404[stadium * 0x1E + 0x21];
        }
        sndFXCtrl(voice, 0x5B, vol);
        task->state = 1;
        break;
    case 1:
        if (task->_1E == EA_SPRITE(task, 0)->frame >> 16) {
            if (task->param != 0) {
                stadium = g_d_GameSettings.StadiumID;
                if (g_d_GameSettings.GameModeSelected == 6) {
                    vol = lbl_3_data_84B8[0xE];
                } else {
                    vol = lbl_3_data_8404[stadium * 0x1E + 0xE];
                }
                voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 7, vol, 0x3F, 0);
                if (g_d_GameSettings.GameModeSelected == 6) {
                    vol = lbl_3_data_84B8[0xF];
                } else {
                    vol = lbl_3_data_8404[stadium * 0x1E + 0xF];
                }
                sndFXCtrl(voice, 0x5B, vol);
            } else {
                stadium = g_d_GameSettings.StadiumID;
                if (g_d_GameSettings.GameModeSelected == 6) {
                    vol = lbl_3_data_84B8[0xC];
                } else {
                    vol = lbl_3_data_8404[stadium * 0x1E + 0xC];
                }
                voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 6, vol, 0x3F, 0);
                if (g_d_GameSettings.GameModeSelected == 6) {
                    vol = lbl_3_data_84B8[0xD];
                } else {
                    vol = lbl_3_data_8404[stadium * 0x1E + 0xD];
                }
                sndFXCtrl(voice, 0x5B, vol);
            }
        }
        if (EA_SPRITE(task, 0)->frame >> 16 >= task->_20) {
            q[EA_MG_FLAGS._1936] = 2;
            EA_MG_FLAGS._1934 = 2;
            task->state = 2;
        }
        break;
    case 2:
        break;
    }
}
#endif

extern s16 lbl_80109410[]; // per-game score cap
extern void fn_3_1079C8(u8* out, s32 mode);
extern s32 fn_3_107C40(void);

// Entry filled by fn_3_1079C8: a player and its placing.
typedef struct EaOrder {
    /*0x0*/ u8 player;
    /*0x1*/ u8 rank;
} EaOrder;

// .text:0x000EA454 size:0x4A8 mapped:0x807294E8
// NONMATCHING 83%: pooled lbl_3_data_19770 tables (addi+lhzx form), score-cap regalloc and the /10000 constant spill
#if NONMATCHING
void fn_3_EA454(void) {
    EaTask* task = EA_TASK;
    EaPool* pool = EA_POOL;
    EaOrder order[4];
    u32 i;
    u32 j;
    s16 score;
    s16 cap;
    s8 chara;

    if (lbl_3_common_bss_32724[0x96] != 0) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 6 && lbl_3_common_bss_34C90[0x1D2] == 5) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    if (g_GameLogic[0x11E] == 0x22 && (lbl_3_common_bss_34C90[0x1D2] == 7 || g_GameLogic[0x122] != 0)) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    if (g_GameLogic[0x11E] == 0x26) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    if (g_GameLogic[0x11E] == 0x24) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, pool->desc1280);
        EA_SPRITE(task, 0)->anim = pool->title1800[EA_MG.game];
        if (EA_MG.game != 0 && EA_MG._1909 == 0 && EA_MG._1A3C == 0) {
            if (EA_MG._190A != 0) {
                EA_SPRITE(task, 1)->anim = pool->sub1818[EA_MG._1A2B];
            } else {
                EA_SPRITE(task, 1)->anim = pool->sub1810[EA_MG._1A2B];
            }
        } else {
            EA_SPRITE(task, 1)->anim = 0x175;
        }
        fn_3_1079C8((u8*)order, 0);
        EA_SPRITE(task, 2)->anim = pool->count1820[EA_MG.numPlayers - 1];
        for (i = 0; i < EA_MG.numPlayers; i++) {
            chara = EA_MG.characterIndex[i];
            EA_SPRITE(task, i + 3)->frame = pool->frame1828[EA_MG.game] << 16;
            EA_SPRITE(task, i + 7)->frame = chara << 16;
            if (fn_3_107C40() != 0) {
                EA_SPRITE(task, i + 0x13)->anim = 0x175;
            } else {
                j = 0;
                do {
                    if (i == order[j].player) {
                        EA_SPRITE(task, i + 0x13)->anim = pool->rank1838[order[j].rank];
                        break;
                    }
                    j++;
                } while (j < EA_MG.numPlayers);
            }
            score = EA_MG.points[i];
            cap = lbl_80109410[EA_MG.game];
            if (score > cap) {
                score = cap;
            }
            fn_800363D8(task, i * 4 + 0x1B, 1, 0x66, (score % 10000) / 1000);
            fn_800363D8(task, i * 4 + 0x1C, 1, 0x66, (score % 1000) / 100);
            fn_800363D8(task, i * 4 + 0x1D, 1, 0x66, (score % 100) / 10);
            fn_800363D8(task, i * 4 + 0x1E, 1, 0x66, score % 10);
        }
        task->state = 1;
        // fallthrough
    case 1:
        break;
    }
}
#endif

extern u8 g_Batter[];
extern u8 lbl_3_data_1A730[];
extern u16 lbl_3_data_1A158[][2]; // [numPlayers - 1][g_Batter[0x7B]]
extern s32 fn_3_125424(void* a, s32 i, u32 v);

// .text:0x000EA8FC size:0x5F8 mapped:0x80729990
// NONMATCHING 88%: the batter-side digit offset is computed as 3 & ~((-x | x) >> 31) in the original; loop register allocation
#if NONMATCHING
void fn_3_EA8FC(void) {
    EaTask* task = EA_TASK;
    u32 i;
    s8 who;
    s16 delta;
    s32 anim;

    if (task->param != 0) {
        if (fn_3_EB684()) {
            lbl_3_common_bss_32724[0xD6] = 0;
            fn_800B0A14_removeQueue(fn_80034CEC(task));
            return;
        }
    } else if (fn_3_EBFD4()) {
        lbl_3_common_bss_32724[0xD6] = 0;
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    switch (task->state) {
    case 0:
        fn_80034E20(task, lbl_3_data_1A730);
        if (task->param != 0) {
            EA_SPRITE(task, 0)->frame = 10 << 16;
        } else {
            EA_SPRITE(task, 0)->anim = lbl_3_data_1A158[EA_MG.numPlayers - 1][g_Batter[0x7B]];
            EA_SPRITE(task, 0)->frame = 10 << 16;
            EA_SPRITE(task, 1)->anim = 0x58;
            EA_SPRITE(task, 2)->anim = 0x58;
            EA_SPRITE(task, 3)->anim = 0x58;
            EA_SPRITE(task, 4)->anim = 0x58;
        }
        task->state = 1;
        break;
    case 1:
        for (i = 0; i < EA_MG.numPlayers; i++) {
            if (task->param != 0) {
                who = i;
            } else {
                who = EA_MG.order[(EA_MG.turn + i) % EA_MG.numPlayers];
            }
            delta = EA_MG._18BC[who].delta;
            if (delta != 0) {
                if (delta < 0) {
                    delta *= -1;
                    anim = 0x59;
                } else {
                    anim = 0x5A;
                }
                if (delta > 999) {
                    delta = 999;
                }
                if (task->param != 0) {
                    if (delta >= 100) {
                        EA_SPRITE(task, i + 1)->frame = 2 << 16;
                    } else if (delta >= 10) {
                        EA_SPRITE(task, i + 1)->frame = 1 << 16;
                    } else {
                        EA_SPRITE(task, i + 1)->frame = 0;
                    }
                } else if (delta >= 100) {
                    EA_SPRITE(task, i + 1)->frame = ((g_Batter[0x7B] == 0 ? 3 : 0) + 2) << 16;
                } else if (delta >= 10) {
                    EA_SPRITE(task, i + 1)->frame = ((g_Batter[0x7B] == 0 ? 3 : 0) + 1) << 16;
                } else {
                    EA_SPRITE(task, i + 1)->frame = (g_Batter[0x7B] == 0 ? 3 : 0) << 16;
                }
                fn_800363D8(task, i * 4 + 5, 1, anim, 11);
                fn_800363D8(task, i * 4 + 6, 1, anim, (delta % 1000) / 100);
                fn_800363D8(task, i * 4 + 7, 1, anim, (delta % 100) / 10);
                fn_800363D8(task, i * 4 + 8, 1, anim, delta % 10);
                if (EA_MG._19A0 != 0) {
                    fn_3_125424(task, i * 4 + 5, 8);
                    fn_3_125424(task, i * 4 + 6, 8);
                    fn_3_125424(task, i * 4 + 7, 8);
                    fn_3_125424(task, i * 4 + 8, 8);
                } else {
                    EA_SPRITE(task, i * 4 + 5)->visible = 1;
                    EA_SPRITE(task, i * 4 + 6)->visible = 1;
                    EA_SPRITE(task, i * 4 + 7)->visible = 1;
                    EA_SPRITE(task, i * 4 + 8)->visible = 1;
                }
            }
        }
        break;
    }
}
#endif

// fn_3_EBFD4, size:0x40
s32 fn_3_EBFD4(void) {
    if (lbl_3_common_bss_32724[0x96] != 0 || g_GameLogic[0x11E] == 2 || g_GameLogic[0x11E] == 8) {
        return 1;
    }
    return 0;
}

// fn_3_EB684, size:0x5C
s32 fn_3_EB684(void) {
    if (lbl_3_common_bss_32724[0x96] != 0 || lbl_3_common_bss_32724[0xB7] != 0) {
        return 1;
    }
    if (g_GameLogic[0x11E] != 1 && g_GameLogic[0x11E] != 2 && g_GameLogic[0x11E] != 0xB) {
        return 1;
    }
    return 0;
}

// fn_3_ED244, size:0x64
void fn_3_ED244(void) {
    u8* p = lbl_803CC1B8;
    if (lbl_3_common_bss_32724[0x96] != 0 || ((QEnt*)lbl_80371C30)[*(u16*)(p + 0x14)].p[0x69] == 2) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// fn_3_ED2A8, size:0x4C
void fn_3_ED2A8(void) {
    fn_80034E20(lbl_803CC1B8, lbl_3_data_8FCC);
    *(void**)lbl_803CC1B8 = fn_3_ED244;
}

// fn_3_ED490, size:0x6C
void fn_3_ED490(void) {
    u8* p = lbl_803CC1B8;
    fn_80034E20(p, lbl_3_data_8F24);
    g_Minigame[0x19CC] = 1;
    *(u16*)(p + 0x1C) = 0;
    *(void**)lbl_803CC1B8 = fn_3_ED2F4;
}

// fn_3_ED4FC, size:0x78
void fn_3_ED4FC(void) {
    u8* p = lbl_803CC1B8;
    if (lbl_3_common_bss_32724[0x96] != 0 || g_GameLogic[0x12E] != 0 || g_GameLogic[0x11E] == 3 || g_GameLogic[0x11E] == 0xE || g_GameLogic[0x121] == 0xA) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// fn_3_ED784, size:0x94
void fn_3_ED784(void) {
    u8* p = lbl_803CC1B8;
    if (g_Minigame[0x1920] == 0xB) {
        *(void**)p = fn_3_EC014;
    } else {
        s32 v = ((s16*)lbl_3_data_8EA8)[g_Minigame[0x1920]];
        if (v < 0) {
            fn_800B0A14_removeQueue(p);
        } else {
            *(s16*)(lbl_3_data_8E68 + 2) = (s16)v;
            fn_80034E20(p, lbl_3_data_8E68);
            *(void**)lbl_803CC1B8 = fn_3_ED6E0;
        }
    }
}

// fn_3_ED058, size:0x9C
void fn_3_ED058(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    p->u18++;
    if (lbl_3_common_bss_32724[0x96] != 0 || (g_GameLogic[0x11E] != 2 && g_GameLogic[0x11E] != 1) || ((QEnt*)lbl_80371C30)[p->u14].p[0x69] == 2) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        g_Minigame[0x19CD] = 3;
    }
}

// fn_3_ED6E0, size:0xA4
void fn_3_ED6E0(void) {
    u8* p = lbl_803CC1B8;
    if (lbl_3_common_bss_32724[0x96] != 0 || ((QEnt*)lbl_80371C30)[*(u16*)(p + 0x14)].p[0x69] == 2 || g_GameLogic[0x11E] == 8) {
        if (g_Minigame[0x1921] != 0) {
            fn_800B0A5C_insertQueue(fn_3_ED0F4, 2);
        }
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// fn_3_ED574, size:0x16C
void fn_3_ED574(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    s32 v;
    fn_80034E20(p, lbl_3_data_8EC4);
    fn_800363D8(p, 1, 6, 0x4A, *(s16*)(g_Minigame + 0x19B4) % 10);
    fn_800363D8(p, 1, 5, 0x4A, *(s16*)(g_Minigame + 0x19B4) / 10);
    v = *(s16*)(g_Minigame + 0x19B6);
    if (v > *(s16*)(g_Minigame + 0x19B4)) {
        v = *(s16*)(g_Minigame + 0x19B4);
    }
    fn_800363D8(p, 1, 2, 0x4A, v % 10);
    if (v >= 10) {
        fn_800363D8(p, 1, 1, 0x4A, v / 10);
    } else {
        fn_800363D8(p, 1, 1, 0x4A, 10);
    }
    *(void**)lbl_803CC1B8 = fn_3_ED4FC;
}

// fn_3_ED2F4, size:0x19C
void fn_3_ED2F4(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    u32 stadium;
    u8 v;
    s32 v2;
    if (lbl_3_common_bss_32724[0x96] == 0) {
        if (g_UnkSound_32718[7] == 0) {
            ((QEnt*)lbl_80371C30)[p->u14].p[0x68] = 1;
            if (p->u1C == 0) {
                if (lbl_800EF808[0x398] == 1) {
                    stadium = g_d_GameSettings.StadiumID;
                    if (g_d_GameSettings.GameModeSelected == 6) {
                        v = lbl_3_data_84B8[0x36];
                    } else {
                        v = lbl_3_data_8404[stadium * 0x1E + 0x36];
                    }
                    v2 = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x1B, v, 0x3F, 0);
                    if (g_d_GameSettings.GameModeSelected == 6) {
                        v = lbl_3_data_84B8[0x37];
                    } else {
                        v = lbl_3_data_8404[stadium * 0x1E + 0x37];
                    }
                    sndFXCtrl(v2, 0x5B, v);
                }
                p->u1C = 1;
            }
        } else {
            ((QEnt*)lbl_80371C30)[p->u14].p[0x68] = 0;
        }
        if (((QEnt*)lbl_80371C30)[p->u14].p[0x69] == 2) {
            goto remove;
        }
    } else {
remove:
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        g_Minigame[0x19CC] = 0;
    }
}

// fn_3_ECBB0, size:0x198
void fn_3_ECBB0(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    u8* q = g_Minigame + 0x1DF4;
    u32 j;
    s32 n;
    if (lbl_3_common_bss_32724[0x96] != 0) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        return;
    }
    if (g_GameLogic[0x11E] == 8) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        return;
    }
    switch (p->u1C) {
    case 0:
        fn_80034E20(p, lbl_3_data_19830);
        *(s32*)(((QEnt*)lbl_80371C30)[p->u14 + 1].p + 0x5C) = 0xA0000;
        j = 0;
        do {
            n = p->u14 + j;
            j++;
            *(u32*)(*(u8**)(lbl_80371C30 + (n + 2) * 8) + 0x54) &= ~2;
        } while (j < 4);
        n = p->u14 + (s8)g_Minigame[0x1935];
        *(u32*)(*(u8**)(lbl_80371C30 + (n + 2) * 8) + 0x54) |= 2;
        n = p->u14 + (s8)g_Minigame[0x1936];
        *(u32*)(*(u8**)(lbl_80371C30 + (n + 2) * 8) + 0x54) |= 2;
        q[(s8)g_Minigame[0x1935]] = 1;
        q[(s8)g_Minigame[0x1936]] = 1;
        p->u1C = 1;
        break;
    case 1:
        g_Minigame[0x1934] = 2;
        p->u1C = 2;
        break;
    case 2:
        break;
    }
}

// fn_3_ED818, size:0x224
void fn_3_ED818(void) {
    if (g_GameLogic[0x12D] != 0 && lbl_3_common_bss_32724[0xA5] == 0) {
        lbl_3_common_bss_32724[0xA5] = 1;
        lbl_3_common_bss_32724[0xA6] = 0;
        lbl_3_common_bss_32724[0xA7] = 0xFF;
        fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
        ((QObj*)fn_800B0A5C_insertQueue(fn_3_EA8FC, 2))->u18 = 0;
        fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
    }
    if (*(s16*)(g_Ball + 0x1B64) == 0xF && g_Minigame[0x19CC] == 0 && g_Minigame[0x19CB] > 1 && g_Pitcher[0x159] == 0) {
        fn_800B0A5C_insertQueue(fn_3_ED490, 2);
    }
    if (lbl_3_common_bss_32724[0xA5] != 0 && lbl_3_common_bss_32724[0xA6] < 0xFF) {
        if (lbl_3_common_bss_32724[0xA6] < 0xF0) {
            lbl_3_common_bss_32724[0xA6] = lbl_3_common_bss_32724[0xA6] + 0x10;
        } else {
            lbl_3_common_bss_32724[0xA6] = 0xFF;
        }
    }
    if (lbl_3_common_bss_32724[0xA7] != 0 && lbl_3_common_bss_32724[0xA7] < 0xFF) {
        if (lbl_3_common_bss_32724[0xA7] <= 0x10) {
            lbl_3_common_bss_32724[0xA7] = 0;
            lbl_3_common_bss_32724[0xA5] = 0;
        } else {
            lbl_3_common_bss_32724[0xA7] = lbl_3_common_bss_32724[0xA7] - 0x10;
        }
    } else if (lbl_3_common_bss_32724[0xA5] != 0) {
        if (g_GameLogic[0x11E] == 8) {
            lbl_3_common_bss_32724[0xA7] = 0;
            lbl_3_common_bss_32724[0xA5] = 0;
        } else if (g_GameLogic[0x11E] != 1 && g_GameLogic[0x11E] != 0 && g_GameLogic[0x11E] != 0xB && g_GameLogic[0x11E] != 0xD) {
            lbl_3_common_bss_32724[0xA7] = 0xF0;
        }
    }
    if (g_GameLogic[0x11E] == 0xB && lbl_3_common_bss_34C90[0x1D2] == 1) {
        fn_800B0A5C_insertQueue(fn_3_9894C, 2);
        if (lbl_3_common_bss_32724[0xAA] == 0) {
            fn_800B0A5C_insertQueue(fn_3_98DE0, 2);
        }
    }
}

// fn_3_EDA3C, size:0x2D4
void fn_3_EDA3C(void) {
    if (g_GameLogic[0x11E] >= 0x1C && g_GameLogic[0x11E] <= 0x20 && lbl_3_common_bss_32724[0xD9] == 0 && g_GameLogic[0x122] == 0) {
        fn_800B0A5C_insertQueue(fn_3_12C3F0, 2);
        fn_800B0A5C_insertQueue(fn_80053FE8, 2);
        lbl_8034E978[0] = 0x2E;
        lbl_8034E978[9] = lbl_8034E978[8];
        lbl_8034E978[8] = *(u16*)(lbl_800FEF70 + 0x2E8);
    }
    if (g_GameLogic[0x11E] == 0x1E) {
        if (g_GameLogic[0x125] == 1 && *(u16*)(g_GameLogic + 0xFE) == 0) {
            if (lbl_3_common_bss_32724[0xDC] == 0) {
                fn_800B0A5C_insertQueue(fn_80051D00, 2);
                lbl_3_common_bss_32724[0xDC] = 1;
            }
            if (lbl_3_common_bss_32724[0xDA] != 1) {
                fn_800B0A5C_insertQueue(fn_3_12B7A0, 2);
            }
        }
        if (g_GameLogic[0x125] == 2) {
            if (lbl_3_common_bss_32724[0xDC] == 0 && g_Minigame[0x19DE] != 5 && g_Minigame[0x19DE] != 8) {
                fn_800B0A5C_insertQueue(fn_80051D00, 2);
                lbl_3_common_bss_32724[0xDC] = 1;
            }
            if (g_Minigame[0x19DE] == 1 && *(u16*)(g_GameLogic + 0xFE) == 1) {
                fn_800B0A5C_insertQueue(fn_3_12A6C4, 2);
            }
        }
        if (g_GameLogic[0x125] == 7) {
            fn_80050F78(1);
            lbl_3_common_bss_32724[0xDC] = 0;
        }
        if (g_GameLogic[0x125] == 3 && *(u16*)(g_GameLogic + 0xFE) == 1) {
            fn_8004CC4C(0, 1, 1, 0, 0x89);
            fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
        }
        if (g_GameLogic[0x125] == 5) {
            fn_80050F78(1);
        }
    } else if (g_GameLogic[0x11E] == 0x21) {
        if (g_GameLogic[0x125] == 2 && *(u16*)(g_GameLogic + 0xFE) == 1) {
            fn_800B0A5C_insertQueue(fn_3_126604, 2);
            lbl_8034E978[0] = 0x32;
            lbl_8034E978[9] = lbl_8034E978[8];
            lbl_8034E978[8] = *(u16*)(lbl_800FEF70 + 0x328);
            if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_32724[0xD9] == 0) {
                fn_800B0A5C_insertQueue(fn_3_12C3F0, 2);
            }
        }
    }
}

// fn_3_EDD10, size:0x29C
void fn_3_EDD10(void) {
    if (g_GameLogic[0x11E] == 0x1C || (u8)(g_GameLogic[0x11E] - 0x1D) <= 3 || g_GameLogic[0x11E] == 0x21) {
        fn_3_EDA3C();
        return;
    }
    lbl_3_common_bss_32724[0xDA] = 0;
    fn_3_97144(lbl_3_common_bss_32724);
    fn_3_96914();
    fn_3_ED818();
    fn_3_9143C();
    if (*(s16*)(g_Minigame + 0x18AA) == 1) {
        fn_800B0A5C_insertQueue(fn_3_ED784, 2);
    }
    if (g_Minigame[0x199F] != 0 && lbl_3_common_bss_32724[0xD6] == 0 && g_GameLogic[0x11E] == 2) {
        ((QObj*)fn_800B0A5C_insertQueue(fn_3_EA8FC, 2))->u18 = 1;
        fn_800B0A5C_insertQueue(fn_3_EAEF4, 2);
    }
    if (g_Minigame[0x19CE] != 0 && *(s16*)(g_Minigame + 0x19BA) == 1) {
        fn_800B0A5C_insertQueue(fn_3_ED2A8, 2);
    }
    if (g_GameLogic[0x11E] == 0xE || g_GameLogic[0x11E] == 0x22) {
        fn_3_129458();
    }
    if (g_GameLogic[0x11E] == 5) {
        if (g_Minigame[0x1E02] == 0) {
            fn_800B0A5C_insertQueue(fn_3_1254F8, 2);
        }
    } else if (g_GameLogic[0x11E] == 0x22) {
        if (lbl_3_common_bss_34C90[0x1D2] == 1) {
            fn_800B0A5C_insertQueue(fn_3_9894C, 2);
        }
    } else if (g_GameLogic[0x11E] == 3) {
        if (g_GameLogic[0x125] == 0 && *(u16*)(g_GameLogic + 0xFE) == 0) {
            ((QObj*)fn_800B0A5C_insertQueue(fn_3_E911C, 2))->u18 = 0;
        }
    } else if (g_GameLogic[0x11E] == 0x24) {
        if (g_GameLogic[0x125] == 5 && *(u16*)(g_GameLogic + 0xFE) == 0) {
            fn_800B0A5C_insertQueue(fn_3_1274B4, 2);
        }
    } else if (g_GameLogic[0x11E] == 9) {
    } else if (g_GameLogic[0x11E] == 0xD) {
        if (lbl_3_common_bss_34C90[0x1D2] == 2) {
            fn_800B0A5C_insertQueue(fn_3_128B90, 2);
        }
    } else if (g_GameLogic[0x11E] == 0xB) {
        if (lbl_3_common_bss_34C90[0x1D2] == 8 && lbl_3_common_bss_34C90[0x1D4] == 2) {
            fn_800B0A5C_insertQueue(fn_3_126604, 2);
        }
    }
}

// fn_3_ECD48, size:0x310
void fn_3_ECD48(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    u8* q = g_Minigame + 0x1DF4;
    u32 stadium;
    u32 stadium2;
    u8 v;
    s32 v2;
    u32 j;
    s32 n;
    if (lbl_3_common_bss_32724[0x96] != 0) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        return;
    }
    if (g_GameLogic[0x11E] == 8) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        return;
    }
    switch (p->u1C) {
    case 0:
        fn_80034E20(p, lbl_3_data_19770);
        stadium = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[0x22];
        } else {
            v = lbl_3_data_8404[stadium * 0x1E + 0x22];
        }
        v2 = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x11, v, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[0x23];
        } else {
            v = lbl_3_data_8404[stadium * 0x1E + 0x23];
        }
        sndFXCtrl(v2, 0x5B, v);
        p->u1C = 1;
        p->u1E = 0;
        break;
    case 1:
        if (*(u32*)(((QEnt*)lbl_80371C30)[p->u14].p + 0x5C) >> 16 == 0xA0) {
            j = 0;
            do {
                n = p->u14 + (s8)g_Minigame[0x1936 + j];
                j++;
                *(u8*)(*(u8**)(lbl_80371C30 + (n + 1) * 8) + 0x68) = 1;
            } while (j < (u32)(g_Minigame[0x1906] - 1));
            p->u1C = 2;
        }
        p->u1E = p->u1E + 1;
        if (p->u1E == 0x3C) {
            stadium2 = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[0x24];
            } else {
                v = lbl_3_data_8404[stadium2 * 0x1E + 0x24];
            }
            v2 = sndFXStartEx(lbl_3_data_81DC[stadium2] + 0x12, v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[0x25];
            } else {
                v = lbl_3_data_8404[stadium2 * 0x1E + 0x25];
            }
            sndFXCtrl(v2, 0x5B, v);
        }
        break;
    case 2:
        n = p->u14;
        n += (s8)g_Minigame[0x1936];
        if (*(u32*)(*(u8**)(lbl_80371C30 + (n + 1) * 8) + 0x5C) >> 16 >= 6) {
            j = 0;
            do {
                q[(s8)g_Minigame[0x1936 + j]] = 2;
                j++;
            } while (j < (u32)(g_Minigame[0x1906] - 1));
            g_Minigame[0x1934] = 2;
            p->u1C = 3;
        }
        break;
    case 3:
        break;
    }
}
