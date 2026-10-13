#include "game/rep_3C28.h"
#define REP_HEADER_FN repHeader_3C28
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/vec.h"

#ifdef PORT_LP64 // offsets for 64-bit pointers (wasm32 uses the GameCube layout)
// PC: the fields where StadiumFxState (rep_1E08.c) has them.
extern union {
    struct { u8 _at__04[0x8]; void* _04; }; // effect archive
    struct { u8 _at__440[0x710]; Vec _440; };
    struct { u8 _at__44C[0x71C]; Vec _44C; };
} lbl_3_common_bss_35154;
#else
extern struct {
    u8 _00[4];
    u32 _04;
    u8 _08[0x438];
    Vec _440;
    Vec _44C;
    u8 _458[0x28];
} lbl_3_common_bss_35154;
#endif
extern BurstParams lbl_3_data_27C98[3];
extern struct {
    u8 _00[LBL_80366158_PAD(0x28)];
    u8 _28;
} lbl_80366158;
void fn_8002C2D0(Vec* pos, Vec* dir, void* prm); // prm: ParticleParams5*

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
#ifdef TARGET_PC
        lbl_3_data_27C98[idx].file = (void*)(uintptr_t)lbl_3_common_bss_35154._04;
#else
        lbl_3_data_27C98[idx]._00 = lbl_3_common_bss_35154._04;
#endif
        if (lbl_80366158._28 == 0) {
            fn_8002C2D0(&lbl_3_common_bss_35154._440, &diff, &lbl_3_data_27C98[idx]);
        }
    }
}


// .data 0x27C98..0x27D58
BurstParams lbl_3_data_27C98[3] = {
    {0, {4, 6, 110000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xFFFFFF00, 0, 50000, 20000}},
    {0, {4, 6, 110000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xFFFFFF00, 0, 50000, 20000}},
    {0, {4, 6, 150000, 1000, 90000, 40, 1, 102000, 101000, 100, 2000000, 0xFFFFFF00, 0, 50000, 20000}},
};

