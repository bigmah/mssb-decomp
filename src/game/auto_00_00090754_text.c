#include "game/auto_00_00090754_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern s32 fn_800698F8(void);
extern u32 lbl_800EF808[];
extern u8* lbl_803CC1B8;
extern u8 lbl_3_common_bss_32724[];
extern void fn_8003649C(void*, s32, s32, s32, s32);
extern u8 lbl_3_data_81D4[];
extern void fn_800216F8(u8, void*);
extern void fn_3_90F48(void);
extern void fn_8006285C(void);

// fn_3_90754, size:0x10
void fn_3_90754(u8* p, s8 a, s8 b) {
    p[0x11820] = a;
    p[0x11821] = b;
}

// fn_3_90764, size:0x34
s32 fn_3_90764(void) {
    fn_80021518(0x33, lbl_800EF808[0xBC / 4]);
    return 0;
}

static inline s32 getStadium(void) {
    if (g_d_GameSettings.GameModeSelected == 6) {
        return 6;
    }
    return g_d_GameSettings.StadiumID;
}

// fn_3_90798, size:0x84
s32 fn_3_90798(void) {
    s32 i;
    s32 s;
    i = getStadium() + 0x27;
    s = getStadium();
    fn_80021518(lbl_3_data_81D4[s], lbl_800EF808[i + 1]);
    return 0;
}

// fn_3_9081C, size:0x44
void fn_3_9081C(void) {
    fn_800214D0();
    fn_800214D0();
    fn_800ACFB0((void*)lbl_800EF808[2]);
    lbl_800EF808[2] = 0;
}

// fn_3_90860, size:0x88
s32 fn_3_90860(void) {
    u8* o = lbl_803CC1B8;
    if (lbl_3_common_bss_34C58._2C == 0) {
        fn_800216F8(1, fn_3_910AC);
        *(s16*)(o + 0x10) = 0;
        lbl_3_common_bss_34C58._2C++;
    } else if (*(s16*)(o + 0x10) != 0) {
        return 1;
    }
    return 0;
}

// fn_3_908E8, size:0x40
void fn_3_908E8(void) {
    fn_800214D0();
    fn_800ACFB0((void*)lbl_800EF808[0x98 / 4]);
    lbl_800EF808[0x98 / 4] = 0;
}

// fn_3_90928, size:0x88
s32 fn_3_90928(void) {
    u8* o = lbl_803CC1B8;
    if (lbl_3_common_bss_34C58._2C == 0) {
        fn_800216F8(0x25, fn_8006285C);
        *(s16*)(o + 0x10) = 0;
        lbl_3_common_bss_34C58._2C++;
    } else if (*(s16*)(o + 0x10) != 0) {
        return 1;
    }
    return 0;
}

// fn_3_909B0, size:0x68
void fn_3_909B0(void) {
    s32 i;
    u32* p;
    fn_800214D0();
    i = 6;
    if (g_d_GameSettings.StadiumID != 6) {
        i = g_d_GameSettings.StadiumID;
    }
    p = lbl_800EF808;
    p += i + 0x27;
    fn_800ACFB0((void*)*(p += 1));
    *p = 0;
}

// fn_3_90A18, size:0x98
s32 fn_3_90A18(void) {
    u8* o = lbl_803CC1B8;
    if (lbl_3_common_bss_34C58._2C == 0) {
        fn_800216F8(g_d_GameSettings.StadiumID + 0x27, fn_3_90798);
        *(s16*)(o + 0x10) = 0;
        lbl_3_common_bss_34C58._2C++;
    } else if (*(s16*)(o + 0x10) != 0) {
        return 1;
    }
    return 0;
}

// fn_3_90AB0, size:0x64
void fn_3_90AB0(s32 a) {
    u32* p;
    s32 i;
    if (a >= 0) {
        i = fn_800698F8() + 5;
        p = lbl_800EF808;
        p += i;
        if (*(p += 1) != 0) {
            fn_800214D0();
            fn_800ACFB0((void*)*p);
            *p = 0;
        }
    }
}

// fn_3_90C14, size:0x9c
s32 fn_3_90C14(s8 a) {
    u8* o = lbl_803CC1B8;
    s32 t;
    if (lbl_3_common_bss_34C58._2C == 0) {
        lbl_3_common_bss_34C58._2D = a;
        t = fn_800698F8();
        *(s16*)(o + 0x10) = 0;
        fn_800216F8(t + 5, fn_3_90F48);
        lbl_3_common_bss_34C58._2C++;
    } else if (*(s16*)(o + 0x10) != 0) {
        lbl_3_common_bss_34C58._2C++;
        return 1;
    }
    return 0;
}

// fn_3_91064, size:0x48
s32 fn_3_91064(void) {
    fn_80021518(0x1C, lbl_800EF808[4]);
    fn_80021518(0x36, lbl_800EF808[4]);
    return 0;
}

// fn_3_910AC, size:0x48
s32 fn_3_910AC(void) {
    fn_80021518(0x1C, lbl_800EF808[2]);
    fn_80021518(0x1D, lbl_800EF808[2]);
    return 0;
}

// fn_3_910F4, size:0xb4
void fn_3_910F4(u8* p) {
    s32 i;
    s32 target = g_Strikes.outs;
    if (g_d_GameSettings.GameModeSelected == 6) {
        target = g_Minigame._190D - g_Minigame._1910;
    }
    i = 0;
    do {
        s32 state = 3;
        if (*(u16*)(p + 0x1C) != target) {
            if (target >= i + 1) {
                state = 2;
            }
            fn_8003649C(p, i + 1, i + 1, 0x107, state);
        }
        i++;
    } while (i < 2);
    *(u16*)(p + 0x1C) = target;
}

// fn_3_911A8, size:0x10c
void fn_3_911A8(void) {
    u8* o = lbl_803CC1B8;
    if (lbl_3_common_bss_32724[0x96] != 0 || g_GameLogic.gameStatus != 2) {
        lbl_3_common_bss_32724[0x97] = 0;
        fn_800B0A14_removeQueue(fn_80034CEC(o));
        return;
    }
    *(u16*)(o + 0x18) = *(u16*)(o + 0x18) + 1;
    fn_3_910F4(o);
}
