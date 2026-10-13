#include "game/auto_00_00090754_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

#include "main/file_80021308.h"         // SoundManager
#include "main/file_80069BDC.h"         // SceneTask lbl_803CC1B8, ChallengeTeamInfo lbl_800E8558
#include "game/auto_00_00097144_text.h" // GameHudFlags lbl_3_common_bss_32724

extern s32 fn_800698F8(s32);
extern SoundManager lbl_800EF808;
extern u8 lbl_3_data_81D4[];
extern u8 lbl_3_data_8148[];
extern void fn_800216F8(u8 group, s32 (*callback)(u8* state));

extern s32 fn_8006285C(u8* state);

static inline s32 getStadium(void) {
    if (g_d_GameSettings.GameModeSelected == 6) {
        return 6;
    }
    return g_d_GameSettings.StadiumID;
}

// fn_3_911A8, size:0x10c
void fn_3_911A8(void) {
    OutsDisplayTask* o = (OutsDisplayTask*)lbl_803CC1B8;
    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.gameStatus != 2) {
        lbl_3_common_bss_32724._97 = 0;
        fn_80034CEC(o);
        REMOVE_QUEUE_NOARG();
        return;
    }
    o->frames = o->frames + 1;
    fn_3_910F4(o);
}

// fn_3_910F4, size:0xb4
void fn_3_910F4(OutsDisplayTask* p) {
    s32 i;
    s32 target = g_Strikes.outs;
    if (g_d_GameSettings.GameModeSelected == 6) {
        target = g_Minigame._190D - g_Minigame._1910;
    }
    i = 0;
    do {
        s32 state = 3;
        if (p->outs != target) {
            if (target >= i + 1) {
                state = 2;
            }
            fn_8003649C((SceneTask*)p, i + 1, i + 1, 0x107, state);
        }
        i++;
    } while (i < 2);
    p->outs = target;
}

// fn_3_910AC, size:0x48
s32 fn_3_910AC(u8* state) {
    fn_80021518(0x1C, lbl_800EF808.groups[1]);
    fn_80021518(0x1D, lbl_800EF808.groups[1]);
    return 0;
}

// fn_3_91064, size:0x48
s32 fn_3_91064(u8* state) {
    fn_80021518(0x1C, lbl_800EF808.groups[3]);
    fn_80021518(0x36, lbl_800EF808.groups[3]);
    return 0;
}

// fn_3_90F48, size:0x11c
s32 fn_3_90F48(u8* state) {
    s32 c;
    s32 n;
    u8 m = g_d_GameSettings.GameModeSelected;
    if (m == 2) {
        c = lbl_3_common_bss_34C58._2D;
    } else if (m == 7 || m == 6) {
        c = g_Minigame.minigameControlStruct[0].charID[(u32)lbl_3_common_bss_34C58._2C >> 1];
    } else if (g_GameLogic.gameStatus == 0xE) {
        c = lbl_3_common_bss_34C58._2D;
    } else {
        c = inMemRoster[lbl_800EF808.unk39A[0] / 9][lbl_800EF808.unk39A[0] % 9].stats.CharID;
    }
    c = fn_800698F8(c);
    n = c + 5;
#ifdef TARGET_PC
    fprintf(stderr, "DBG90F48 c=%d n=%d status=%d 2D=%d 2C=%d unk39A=%d group=%p\n", c, n, g_GameLogic.gameStatus, lbl_3_common_bss_34C58._2D, lbl_3_common_bss_34C58._2C, lbl_800EF808.unk39A[0], (void*)lbl_800EF808.groups[n]);
#endif
    fn_80021518(lbl_3_data_8148[c], lbl_800EF808.groups[n]);
    return 0;
}

// fn_3_90DD8, size:0x170
s32 fn_3_90DD8(void) {
    SceneTask* o = lbl_803CC1B8;
    u8 st = lbl_3_common_bss_34C58._2C;
    s32 i = (st >> 1) & 0x7F;
    MiniGameStruct* g;
    s32 v;
    s32 j;
    s32 t;
    if (st == 0 || st == 2 || st == 4 || st == 6) {
        g = &g_Minigame;
        if (g->minigameControlStruct[0].characterIndex[i] < 0) {
            lbl_3_common_bss_34C58._2C += 2;
            return 0;
        }
        v = lbl_800E8558[g->minigameControlStruct[0].charID[i]].trk;
        if (i != 0) {
            for (j = 0; j < i; j++) {
                if (v == lbl_800E8558[g_Minigame.minigameControlStruct[0].charID[j]].trk) {
                    if ((lbl_3_common_bss_34C58._2C += 2) >= 8) {
                        g_Minigame._19AB = 1;
                        return 1;
                    }
                    return 0;
                }
            }
        }
        t = fn_800698F8(v);
        fn_800216F8(t + 5, fn_3_90F48);
        lbl_3_common_bss_34C58._2C++;
    } else if (o->_10 != 0) {
        if ((lbl_3_common_bss_34C58._2C = st + 1) >= 8) {
            g_Minigame._19AB = 1;
            return 1;
        }
    }
    return 0;
}

// fn_3_90CB0, size:0x128
void fn_3_90CB0(void) {
    s32 slot;
    s32 j;
    s32 k;
    s32 dup;
    struct SoundGroupData** p;

    if (g_Minigame._19AB != 0) {
        for (slot = 3; slot >= 0; slot--) {
            for (j = 0; j < 4; j++) {
                if (g_Minigame.minigameControlStruct[0].characterIndex[j] != slot) {
                    continue;
                }
                dup = 0;
                for (k = 0; k < j; k++) {
                    if (lbl_800E8558[g_Minigame.minigameControlStruct[0].charID[j]].trk ==
                        lbl_800E8558[g_Minigame.minigameControlStruct[0].charID[k]].trk) {
                        dup = 1;
                        break;
                    }
                }
                if (dup == 0) {
                    break;
                }
            }
            if (j < 4) {
                p = &lbl_800EF808.groups[fn_800698F8(inMemRoster[0][slot].stats.CharID) + 5];
                if (*p != NULL) {
                    fn_800214D0();
                    fn_800ACFB0(*p);
                    *p = NULL;
                }
            }
        }
    }
}

// fn_3_90C14, size:0x9c
s32 fn_3_90C14(s32 a) {
    SceneTask* o = lbl_803CC1B8;
    s32 t;
    if (lbl_3_common_bss_34C58._2C == 0) {
        lbl_3_common_bss_34C58._2D = a;
        t = fn_800698F8(a);
        o->_10 = 0;
        fn_800216F8(t + 5, fn_3_90F48);
        lbl_3_common_bss_34C58._2C++;
    } else if (o->_10 != 0) {
        lbl_3_common_bss_34C58._2C++;
        return 1;
    }
    return 0;
}

// fn_3_90B14, size:0x100
s32 fn_3_90B14(s32 a, s32 b) {
    SceneTask* o = lbl_803CC1B8;
    s32 t;
    if (lbl_3_common_bss_34C58._2C == 0) {
        lbl_3_common_bss_34C58._2C = 1;
    }
    if (lbl_3_common_bss_34C58._2C == 1 || lbl_3_common_bss_34C58._2C == 3) {
        if (lbl_3_common_bss_34C58._2C == 1) {
            lbl_3_common_bss_34C58._2D = a;
        } else {
            if (b < 0) {
                return 1;
            }
            lbl_3_common_bss_34C58._2D = b;
        }
        t = fn_800698F8(lbl_3_common_bss_34C58._2D);
        o->_10 = 0;
        fn_800216F8(t + 5, fn_3_90F48);
        lbl_3_common_bss_34C58._2C++;
    } else if (o->_10 != 0) {
        if (++lbl_3_common_bss_34C58._2C == 5) {
            return 1;
        }
    }
    return 0;
}

// fn_3_90AB0, size:0x64
void fn_3_90AB0(s32 a) {
    struct SoundGroupData** p;
    s32 i;
    if (a >= 0) {
        i = fn_800698F8(a) + 5;
        p = lbl_800EF808.groups - 1;
        p += i;
        if (*(p += 1) != NULL) {
            fn_800214D0();
            fn_800ACFB0(*p);
            *p = NULL;
        }
    }
}

// fn_3_90A18, size:0x98
s32 fn_3_90A18(void) {
    SceneTask* o = lbl_803CC1B8;
    if (lbl_3_common_bss_34C58._2C == 0) {
        fn_800216F8(g_d_GameSettings.StadiumID + 0x27, fn_3_90798);
        o->_10 = 0;
        lbl_3_common_bss_34C58._2C++;
    } else if (o->_10 != 0) {
        return 1;
    }
    return 0;
}

// fn_3_909B0, size:0x68
void fn_3_909B0(void) {
    s32 i;
    struct SoundGroupData** p;
    fn_800214D0();
    i = 6;
    if (g_d_GameSettings.StadiumID != 6) {
        i = g_d_GameSettings.StadiumID;
    }
    p = lbl_800EF808.groups - 1;
    p += i + 0x27;
    fn_800ACFB0(*(p += 1));
    *p = NULL;
}

// fn_3_90928, size:0x88
s32 fn_3_90928(void) {
    SceneTask* o = lbl_803CC1B8;
    if (lbl_3_common_bss_34C58._2C == 0) {
        fn_800216F8(0x25, fn_8006285C);
        o->_10 = 0;
        lbl_3_common_bss_34C58._2C++;
    } else if (o->_10 != 0) {
        return 1;
    }
    return 0;
}

// fn_3_908E8, size:0x40
void fn_3_908E8(void) {
    fn_800214D0();
    fn_800ACFB0(lbl_800EF808.groups[37]);
    lbl_800EF808.groups[37] = NULL;
}

// fn_3_90860, size:0x88
s32 fn_3_90860(void) {
    SceneTask* o = lbl_803CC1B8;
    if (lbl_3_common_bss_34C58._2C == 0) {
        fn_800216F8(1, fn_3_910AC);
        o->_10 = 0;
        lbl_3_common_bss_34C58._2C++;
    } else if (o->_10 != 0) {
        return 1;
    }
    return 0;
}

// fn_3_9081C, size:0x44
void fn_3_9081C(void) {
    fn_800214D0();
    fn_800214D0();
    fn_800ACFB0(lbl_800EF808.groups[1]);
    lbl_800EF808.groups[1] = NULL;
}

// fn_3_90798, size:0x84
s32 fn_3_90798(u8* state) {
    s32 i;
    s32 s;
    i = getStadium() + 0x27;
    s = getStadium();
    fn_80021518(lbl_3_data_81D4[s], lbl_800EF808.groups[i]);
    return 0;
}

// fn_3_90764, size:0x34
s32 fn_3_90764(u8* state) {
    fn_80021518(0x33, lbl_800EF808.groups[46]);
    return 0;
}

// fn_3_90754, size:0x10
void fn_3_90754(u8* p, s8 a, s8 b) { // TODO type: p's struct (>= 0x11822 bytes) is unknown; no C callers yet
    p[0x11820] = a;
    p[0x11821] = b;
}

