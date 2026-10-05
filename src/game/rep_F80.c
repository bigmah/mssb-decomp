#include "game/rep_F80.h"
#include "header_rep_data.h"

extern u8 g_Batter[];
extern u8 g_d_GameSettings[];
extern u8 g_Minigame[];
extern u8 g_Pitcher[];
extern u8 g_Camera[];
extern u8 lbl_3_common_bss_3223C[];
extern u8 lbl_3_common_bss_35154[];
extern f32 game_atan2(f32 x, f32 y);
extern void fn_3_BE174(s32 a, f32 x, f32 y, f32 z);
extern u8 g_Ball[];
extern u8 g_GameLogic[];
extern void fn_3_CB344(int who, u8 a);
extern void fn_3_CB234(int who, int a);
extern void fn_3_CB284(int who, s16 a, f32 f);
extern int getAnimRelatedCoordinates(int who, int a, void* out);
typedef struct { s8 characterIndex[4]; u8 pad[0x12]; } MiniCtl_F80;
extern u8 lbl_3_common_bss_32220[];
extern void fn_3_C07A0(void);
extern void fn_3_C1770(int who);
extern void fn_3_C11CC(int who, int a);
extern void fn_3_C1344(int who, int a, f32 x, f32 y, f32 z);
extern void fn_3_C0770(void);
extern void fn_3_C07B0(void);
extern void fn_3_BF1AC(void);
extern void fn_3_CABB4(void);
extern void fn_80011578(void);

extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_8036E548[];

// .text:0x0006A2A4 size:0x5C mapped:0x806A9338
void fn_3_6A2A4(s8 idx) {
    u8* e = *(u8**)(lbl_8036E548 + 0x64) + (idx - 0x1F) * 0x90 + 0x34;
    lbl_3_common_bss_32724[0xD4] = 1;
    e[0x5B] = 2;
    *(f32*)(e + 0x5C) = 0.0f;
    e[0x59] = 1;
    *(f32*)(e + 0x54) = 1.0f;
    e[0x5A] = 1;
}

// .text:0x0006A300 size:0x100 mapped:0x806A9394
void fn_3_6A300(void) {
    u8* p;
    u8* d;
    if (lbl_3_common_bss_32724[0xD4] == 0) {
        return;
    }
    p = *(u8**)(lbl_8036E548 + 0x2C74);
    if (g_d_GameSettings[7] == 6) {
        p = ((u8**)(lbl_8036E548 + 0x2C50))[*(s8*)(g_Minigame + 0x1905)];
    }
    {
        s8 t = *(s8*)(p + 0x252);
        if (t == 0x30) {
            d = *(u8**)(lbl_8036E548 + 0x2D90) + 0x2A8;
        } else if (t == 0x31) {
            d = *(u8**)(lbl_8036E548 + 0x2D90) + 0x2D0;
        } else if (t == 0x32) {
            d = *(u8**)(lbl_8036E548 + 0x2D90) + 0x2F8;
        } else {
            d = *(u8**)(lbl_8036E548 + 0x2D90) + 0x320;
        }
    }
    d[0x26] = 1;
    *(f32*)(d + 4) = *(f32*)(p + 0x34);
    *(f32*)(d + 8) = -*(f32*)(p + 0x38);
    *(f32*)(d + 0xC) = *(f32*)(p + 0x3C);
    *(f32*)(d + 0x10) = *(f32*)(p + 0x40);
    *(f32*)(d + 0x14) = -*(f32*)(p + 0x44);
    *(f32*)(d + 0x18) = *(f32*)(p + 0x48);
}

// .text:0x0006A400 size:0x14 mapped:0x806A9494

void fn_3_6A400(void) {
    lbl_3_common_bss_32724[0xD4] = 0;
}

// .text:0x0006A414 size:0x428 mapped:0x806A94A8
void fn_3_6A414(void) {
    return;
}

#pragma dont_inline on
// .text:0x0006A83C size:0x174 mapped:0x806A98D0
void fn_3_6A83C(void) {
    f32 v[3];
    s32 who = 0;
    if (*(s16*)(g_Pitcher + 0x11E) <= 0) {
        lbl_3_common_bss_32724[0xC8] = 0;
        return;
    }
    if (lbl_3_common_bss_32724[0xC8] < 2) {
        if (g_d_GameSettings[0x11] != 0) {
            who = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        }
        if (*(s16*)(g_Pitcher + 0x11E) >= 0 && (g_Pitcher[0x161] != 0 || g_Pitcher[0x15F] != 0)) {
            if (lbl_3_common_bss_32724[0xC8] == 0) {
                fn_3_CB344(who, g_Pitcher[0x165]);
                lbl_3_common_bss_32724[0xC8] = 1;
            }
            if (lbl_3_common_bss_32724[0xC8] == 1) {
                if (*(s16*)(g_Ball + 0x1B68) == 1 || g_GameLogic[0x11E] != 1) {
                    fn_3_CB234(who, 1);
                    lbl_3_common_bss_32724[0xC8] = 2;
                    return;
                }
                getAnimRelatedCoordinates(who, g_Pitcher[0x141] != 0 ? 0x14 : 0x1A, v);
                fn_3_CB284(who, *(s16*)(g_Pitcher + 0x126), *(f32*)(g_Pitcher + 0xE4));
            }
        }
    }
}
#pragma dont_inline reset

// .text:0x0006A9B0 size:0xE8 mapped:0x806A9A44
void fn_3_6A9B0(void) {
    s32 who;
    if (g_d_GameSettings[0x11]) {
        who = ((MiniCtl_F80*)(g_Minigame + 0x18CC))[0].characterIndex[*(s8*)(g_Minigame + 0x1905)];
    } else {
        who = 9;
    }
    if (g_Batter[0x9D] == 1) {
        if (*(s16*)(g_Batter + 0x74) == 1) {
            fn_3_C1770(who);
            lbl_3_common_bss_32724[0xC9] = 1;
            return;
        }
        {
            f32 k = 100.0f;
            f32 y = *(f32*)(g_Batter + 0x5C);
            f32 x = *(f32*)(g_Batter + 0x58);
            x = k * x;
            y = k * y;
            fn_3_C1344(who, x >= k, x, y, k);
        }
        return;
    }
    if (lbl_3_common_bss_32724[0xC9] != 0) {
        fn_3_C11CC(who, 1);
        lbl_3_common_bss_32724[0xC9] = 0;
    }
}

// .text:0x0006AA98 size:0x98 mapped:0x806A9B2C
void fn_3_6AA98(void) {
    if (*(s16*)(g_Batter + 0x62) == 2 || *(s16*)(g_Batter + 0x62) == 3 || *(s16*)(g_Batter + 0x62) == 6) {
        return;
    }
    {
        u8 t = lbl_3_common_bss_32220[0xA];
        if (t == 0) {
            return;
        }
        if (t == 3 || t == 4) {
            fn_3_C07A0();
        } else if (t == 9) {
            fn_3_C0770();
        } else if (*(s16*)(lbl_3_common_bss_32220 + 2) == 2 && t == 2) {
            fn_3_C07B0();
        }
    }
}

// .text:0x0006AB30 size:0x28 mapped:0x806A9BC4
void fn_3_6AB30(void) {
    fn_3_BF1AC();
    fn_3_CABB4();
    fn_80011578();
}

static inline void fn_3_6A9B0_i(void) {
    s32 who;
    if (g_d_GameSettings[0x11]) {
        who = ((MiniCtl_F80*)(g_Minigame + 0x18CC))[0].characterIndex[*(s8*)(g_Minigame + 0x1905)];
    } else {
        who = 9;
    }
    if (g_Batter[0x9D] == 1) {
        if (*(s16*)(g_Batter + 0x74) == 1) {
            fn_3_C1770(who);
            lbl_3_common_bss_32724[0xC9] = 1;
            return;
        }
        {
            f32 k = 100.0f;
            f32 x = *(f32*)(g_Batter + 0x58);
            f32 y = *(f32*)(g_Batter + 0x5C);
            x = k * x;
            y = k * y;
            fn_3_C1344(who, x >= k, x, y, k);
        }
        return;
    }
    if (lbl_3_common_bss_32724[0xC9] != 0) {
        fn_3_C11CC(who, 1);
        lbl_3_common_bss_32724[0xC9] = 0;
    }
}

// .text:0x0006AB58 size:0x368 mapped:0x806A9BEC
void fn_3_6AB58(void) {
    s32 mode;
    *(f32*)(lbl_3_common_bss_3223C + 4) =
        game_atan2(*(f32*)(g_Camera + 0x2854) - *(f32*)(g_Camera + 0x2848), *(f32*)(g_Camera + 0x284C) - *(f32*)(g_Camera + 0x2840));
    fn_3_6AA98();
    fn_3_6A9B0_i();
    fn_3_6A83C();
    ((void (*)(void))fn_3_6A414)();
    fn_3_6A300();
    if (*(s16*)(g_Ball + 0x1B66) == 0 && (*(u32*)(lbl_3_common_bss_35154 + 0x3AC) & 3) == 0) {
        if (g_Batter[0xA2] != 0 || g_Batter[0xA0] != 0) {
            mode = 4;
        } else if (g_Batter[0x8B] == 3) {
            mode = 0;
        } else if (g_Batter[0x97] != 0) {
            mode = 3;
        } else if (g_Batter[0x92] == 2) {
            mode = 2;
        } else {
            mode = 1;
        }
        if (g_Batter[0x7B] == 0) {
            fn_3_BE174(mode, *(f32*)(g_Batter + 0x24), -*(f32*)(g_Batter + 0x28), *(f32*)(g_Batter + 0x2C));
        } else {
            fn_3_BE174(mode, -*(f32*)(g_Batter + 0x24), -*(f32*)(g_Batter + 0x28), *(f32*)(g_Batter + 0x2C));
        }
    }
}

