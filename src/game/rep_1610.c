#include "game/rep_1610.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    void (*func)(void);
    u8 _04[0x10];
    u16 _14;
    u8 _16[2];
    u16 _18;
    u8 _1A[2];
    u16 _1C;
} Unk_803CC1B8;

typedef struct {
    u8 _00[0x4C];
    f32 _4C;
    u8 _50[0xC];
    u32 _5C;
} Unk_80371C30_Obj;

extern Unk_803CC1B8 *lbl_803CC1B8;
extern Unk_80371C30_Obj *lbl_80371C30[];
extern u8 lbl_3_data_D5B8[];
void fn_80034E20(Unk_803CC1B8 *, u8 *);
void fn_8003649C(Unk_803CC1B8 *, s32, s32, s32, s32);
void fn_3_911A8(void);

// .text:0x000912B4 size:0x188 mapped:0x806D0348
void fn_3_912B4(void) {
    Unk_803CC1B8 *p;
    s32 target;
    s32 i;

    fn_80034E20(p = lbl_803CC1B8, lbl_3_data_D5B8);
    p->_1C = 9;
    lbl_80371C30[(p->_14 + 1) * 2]->_5C = 0;
    lbl_80371C30[(p->_14 + 2) * 2]->_5C = 0x10000;
    target = g_Strikes.outs;
    if (g_d_GameSettings.GameModeSelected == 6) {
        target = g_Minigame._190D - g_Minigame._1910;
    }
    for (i = 0; i < 2; i++) {
        s32 state = 3;
        if (p->_1C != target) {
            if (target >= i + 1) {
                state = 2;
            }
            fn_8003649C(p, i + 1, i + 1, 0x107, state);
        }
    }
    p->_1C = target;
    if (g_d_GameSettings.GameModeSelected == 6) {
        lbl_80371C30[(p->_14) * 2]->_4C = 56.0f;
        lbl_80371C30[(p->_14 + 1) * 2]->_4C = 56.0f;
        lbl_80371C30[(p->_14 + 2) * 2]->_4C = 56.0f;
    }
    p->_18 = 0;
    lbl_803CC1B8->func = fn_3_911A8;
}
