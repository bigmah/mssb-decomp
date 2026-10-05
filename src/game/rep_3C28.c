#include "game/rep_3C28.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/vec.h"

extern struct {
    u8 _00[4];
    u32 _04;
    u8 _08[0x438];
    Vec _440;
    Vec _44C;
    u8 _458[0x28];
} lbl_3_common_bss_35154;
extern struct {
    u32 _00;
    u8 _04[0x3C];
} lbl_3_data_27C98[];
extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;
void fn_8002C2D0(Vec *, Vec *);

// 95%: only the store addressing differs (orig: add r5,r3,r5; stw 0(r5); ours: stwx) and lwz/lbz order
// .text:0x0015F574 size:0xD4 mapped:0x8079E608
void fn_3_15F574(void) {
    Vec diff;
    s32 idx;
    u32 *dst;
    f32 mag;

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        idx = 2;
    } else {
        idx = g_Ball.framesSinceHit > 0;
    }
    PSVECSubtract(&lbl_3_common_bss_35154._44C, &lbl_3_common_bss_35154._440, &diff);
    mag = PSVECMag(&diff);
    if (mag) {
        lbl_3_data_27C98[idx]._00 = lbl_3_common_bss_35154._04;
        if (lbl_80366158._28 == 0) {
            fn_8002C2D0(&lbl_3_common_bss_35154._440, &diff);
        }
    }
}
