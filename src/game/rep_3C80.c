#include "game/rep_3C80.h"
#define REP_HEADER_FN repHeader_3C80
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "main/file_800263FC.h"
#include "main/file_8004207C.h"
#include "main/file_8004B284.h"

// Hit-effect particle parameters (lbl_3_data_27D58). The thresholds are
// minimum |dir| values, fixed point x100000.
typedef struct HitFxParams {
    /*0x000*/ ParticleParams5 burst;
    /*0x050*/ ParticleParamsC sparkA;
    /*0x0A4*/ ParticleParams5 ring;
    /*0x0F4*/ ParticleParamsC sparkB;
    /*0x148*/ s32 minMag[8]; // [0] burst, [1] sparkA + ring, [2] sparkB
} HitFxParams;

extern HitFxParams lbl_3_data_27D58;
extern struct {
    u8 _00[4];
    TexArchive* tex;
} lbl_3_common_bss_35154;
extern BatFxTables lbl_800FC0FC;
void fn_80064344(Vec* pos, Vec* v);

// NONMATCHING 79%: orig reaches minMag[1]/[2] and the int->float double via addi base; lwz 4(rX) (unfolded),
// and passes kind to fn_8004AD54 without clrlwi (its game-side prototype likely took an int); rest is scheduling
// .text:0x0015F648 size:0x22C mapped:0x8079E6DC
#if NONMATCHING
void fn_3_15F648(s32 kind, s32 sub, Vec* pos, Vec* dir) {
    HitFxParams* fx = &lbl_3_data_27D58;
    s32 color;

    switch (kind) {
    case 10:
        fn_80064344(pos, dir);
        break;
    default:
        if (sub == 1) {
            if (PSVECMag(dir) >= (f32)fx->minMag[1] / 100000.0f) {
                fx->sparkA.tex = lbl_3_common_bss_35154.tex;
                fx->ring.tex = lbl_3_common_bss_35154.tex;
                fn_8002955C(pos, NULL, &fx->sparkA);
                fn_80030D88(pos, dir, &fx->ring, 5);
            }
        } else {
            color = fn_8004AD54(g_d_GameSettings.StadiumID, kind);
            if (PSVECMag(dir) >= (f32)fx->minMag[0] / 100000.0f) {
                fx->burst.tex = lbl_3_common_bss_35154.tex;
                fx->burst.unk40 = (lbl_800FC0FC.colors[color].r << 24) | ((lbl_800FC0FC.colors[color].g << 16) & 0xFF0000) |
                                  ((lbl_800FC0FC.colors[color].b << 8) & 0xFF00);
                fn_80031CA4(pos, &fx->burst);
            }
            if (PSVECMag(dir) >= (f32)fx->minMag[2] / 100000.0f) {
                switch (color) {
                case 1:
                case 3:
                case 7:
                    fx->sparkB.tex = lbl_3_common_bss_35154.tex;
                    fn_8002955C(pos, NULL, &fx->sparkB);
                    break;
                }
            }
        }
        break;
    }
}
#endif
