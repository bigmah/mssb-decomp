#include "game/auto_00_00157DB8_text.h"
#include "game/rep_1200.h"
#include "game/auto_00_0005985C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern s16 lbl_3_data_FC1C;
extern u8 lbl_3_data_BD90[];
extern u8 lbl_3_data_BD50[];
extern u8 lbl_3_data_B3F4[];
extern u8 lbl_800EF808[];
extern void fn_80034E20(void*, void*);
extern void* fn_80033A24(void*, int, int, int, int, int);
extern void fn_3_6B870(void);
extern void* lbl_803CC1B8[];
extern u32 fn_3_157AC4(u8* o);
extern void fn_3_158FE4(void);
extern void fn_3_157E28(void);
extern void fn_3_159114(void);
typedef struct {
    u8* p;
    s32 pad;
} QEnt;
extern void fn_3_158B64(void);
extern void fn_3_5F154(void);
extern void fn_3_5EFEC(void);
extern void fn_3_5EDD8(void);
extern void fn_3_5F3FC(void);
extern void fn_3_5CD24(void);
extern void fn_3_15AE34(void);
extern void fn_3_15B494(void);
extern void fn_3_1586B0(void);
extern void fn_3_9669C(void);
extern u8 lbl_3_data_FAF4[];
extern u8 lbl_3_data_B85C[];
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_3_common_bss_34C90[];
extern u8 lbl_80371C30[];
extern void fn_3_8A350(void);
extern void fn_3_F7B8(void);
extern void fn_3_59338(void);

// fn_3_157DB8, size:0x70
void fn_3_157DB8(s32 arg0) {
    u8* p = fn_80033A24(fn_3_157AC4, 0x80, 0, 1, 1, 0x16);
    if (p != NULL) {
        *(s32*)(p + 0x18) = 0;
        *(s32*)(p + 0x1C) = arg0;
        (*(u8**)(p + 0xC))[0x4D] = 0;
        *(s32*)(*(u8**)(p + 0xC) + 0x40) = -1;
    }
}

// fn_3_1580AC, size:0x60
void fn_3_1580AC(void) {
    u8* o = lbl_803CC1B8[0];
    fn_80034E20(o, lbl_3_data_BD90);
    *(s16*)(o + 0x1C) = 0;
    *(s16*)(o + 0x1E) = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_157E28;
}

// fn_3_15810C, size:0xF0
void fn_3_15810C(void) {
    u8* o = lbl_803CC1B8[0];
    s32 lim;
    if (lbl_3_common_bss_32724[0x96] == 0) {
        lim = 0x96;
        if (g_Practice.practiceType_2 == 0) {
            lim = 0x5A;
        }
        if (g_Practice._186 < lim - 0x14) {
            u8* t = ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2];
            if ((*(u32*)(t + 0x5C) >> 16) >= 0x21) {
                t[0x68] = 0;
            }
        } else {
            (((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2])[0x68] = 1;
        }
        if (g_Practice._1C7 == 0 || lbl_3_common_bss_34C90[0x1D2] != 0) {
            return;
        }
    }
    fn_800B0A14_removeQueue(fn_80034CEC(o));
}

// fn_3_1581FC, size:0x68
void fn_3_1581FC(void) {
    fn_80034E20(lbl_803CC1B8[0], lbl_3_data_BD50);
    if (lbl_800EF808[0x398] == 1) {
        playSoundEffect(0x1AD);
    }
    *(void**)lbl_803CC1B8[0] = fn_3_15810C;
}

// fn_3_158264, size:0x148
void fn_3_158264(u8* o) {
    s32 v;
    s32 c;
    u8* row = lbl_3_data_FAF4 + g_Practice.practiceType_2 * 4;
    v = row[g_Practice.practiceLevel];
    fn_800363D8(o, 1, 3, 0x32, v);
    fn_800363D8(o, 1, 4, 0x32, v);
    c = g_Practice.guidedPracticeCounter;
    fn_800363D8(o, 1, 1, 0x32, c);
    fn_800363D8(o, 1, 2, 0x32, c);
    if (c != *(u16*)(o + 0x1A)) {
        QEnt* t = (QEnt*)(lbl_80371C30 + 8);
        u8* q = t[*(u16*)(o + 0x14)].p;
        if ((*(u32*)(q + 0x5C) >> 16) <= 9) {
            *(u32*)(q + 0x5C) = 0xA0000;
            t[*(u16*)(o + 0x14)].p[0x68] = 1;
        }
        q = t[*(u16*)(o + 0x14)].p;
        if ((*(u32*)(q + 0x5C) >> 16) >= 0x13) {
            *(u32*)(q + 0x5C) = 0x90000;
            t[*(u16*)(o + 0x14)].p[0x68] = 0;
            *(u16*)(o + 0x1A) = c;
        }
    }
}

// fn_3_1589C4, size:0x1A0
void fn_3_1589C4(void) {
    if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2) {
        if (g_Practice.tutorialState == 3 && g_Practice._1C7 == 0) {
            if (lbl_3_common_bss_32724[0xC6] == 0) {
                fn_800B0A5C_insertQueue(fn_3_1586B0, 2);
                lbl_3_common_bss_32724[0xC6] = 1;
            }
            if (g_Practice.practiceType_2 == 2 && g_Ball.totalFramesAtPlay == 1) {
                fn_800B0A5C_insertQueue(fn_3_9669C, 2);
            }
            if (g_Practice.practiceType_2 == 2) {
                if (g_Practice._186 == 0x3C) {
                    fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
                }
            } else if (g_Practice._186 == 1) {
                fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
            }
        }
    } else if (g_Practice.practiceType_2 == 3) {
        if (g_Practice.tutorialState == 3 && g_Practice._1C7 == 0) {
            if (lbl_3_common_bss_32724[0xC7] == 0) {
                fn_800B0A5C_insertQueue(fn_3_1586B0, 2);
                fn_800B0A5C_insertQueue(fn_3_9669C, 2);
            }
            if (g_Practice._186 == 1) {
                fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
            }
        }
    }
}

// fn_3_1590C8, size:0x4C
void fn_3_1590C8(void) {
    if (g_Practice.tutorialState == 0 && g_Practice.practiceState == 7) {
        fn_800B0A5C_insertQueue(fn_3_158FE4, 2);
    }
}

// fn_3_159590, size:0x64
void fn_3_159590(void) {
    u8* o = lbl_803CC1B8[0];
    fn_80034E20(o, lbl_3_data_B3F4);
    *(s16*)(o + 0x18) = 0;
    *(s16*)(o + 0x1A) = 0;
    *(s16*)(o + 0x1C) = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_159114;
}

// fn_3_15AD94, size:0x40
void fn_3_15AD94(void) {
    if (g_Pitcher.currentStateFrameCounter > lbl_3_data_FC1C) {
        fn_3_750C4(2);
    }
}

// fn_3_15ADD4, size:0x60
void fn_3_15ADD4(void) {
    fn_3_6B870();
    g_GameLogic._135 = 0;
    g_GameLogic._136 = 0;
    if (g_GameLogic.secondaryGameMode == 0xF && g_Strikes.outs >= 3) {
        g_Strikes.outs = 0;
    }
    fn_3_5A6D4(7);
}


// fn_3_15AF78, size:0x160
void fn_3_15AF78(void) {
    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Practice.frames_sinceMovedToFromMenu < 0xFFFE) {
        g_Practice.frames_sinceMovedToFromMenu++;
    } else {
        g_Practice.frames_sinceMovedToFromMenu = 0xFFFF;
    }
    switch (g_GameLogic.gameStatus) {
    case 0:
        fn_3_5F154();
        break;
    case 1:
        fn_3_5EFEC();
        break;
    case 2:
        fn_3_5EDD8();
        break;
    case 7:
        fn_3_5F3FC();
        if (g_GameLogic.FrameCountOfCurrentPitch == 1) {
            fn_3_15AE34();
        }
        break;
    case 8:
        fn_3_15ADD4();
        break;
    case 10:
        fn_3_5CD24();
        break;
    }
    if (g_Practice.practiceLevel != 7 && g_Practice.practiceLevel != 6) {
        g_Strikes.outs = 0;
    }
}

// fn_3_15B610, size:0x18C
void fn_3_15B610(void) {
    switch (g_Practice.tutorialState) {
    case 0:
        fn_3_15B494();
        break;
    case 3:
        fn_3_15AF78();
        break;
    }
}

// fn_3_158FE4, size:0xE4
void fn_3_158FE4(void) {
    u8* o;
    u8* w;
    u8* e;
    fn_80034E20(o = lbl_803CC1B8[0], lbl_3_data_B85C);
    e = lbl_80371C30;
    e += *(u16*)(o + 0x14) * 8;
    w = *(u8**)(e + 0x40);
    *(u32*)(w + 0x54) &= ~2;
    fn_800363D8(o, 0xD, 1, 0xE, g_Practice.practiceLevel);
    fn_800363D8(o, 0xD, 2, 0xE, g_Practice.practiceLevel);
    g_Practice.laukituTextChannelIndex = -1;
    g_Practice.diagramTextChannelIndex = -1;
    *(s16*)(o + 0x18) = 0;
    *(s16*)(o + 0x1A) = 0;
    *(s16*)(o + 0x1C) = 0;
    *(s16*)(o + 0x1E) = 0;
    *(s16*)(o + 0x20) = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_158B64;
}
