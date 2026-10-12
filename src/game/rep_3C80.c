#include "game/rep_3C80.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "main/file_800263FC.h"
#include "main/file_8004207C.h"
#include "main/file_8004B284.h"

// Hit-effect particle parameters (lbl_3_data_27D58..27EC0). The thresholds are
// minimum |dir| values, fixed point x100000: [0] burst, [1] sparkA + ring, [2] sparkB.
static ParticleParams5 sHitBurst = {NULL, 4, 10, 70000, 30000, 78000, 30, 10, 109000, 101000, 0, 30, 12800000, 0, 0, 0, 0, -256, 0, 75000};
static ParticleParamsC sHitSparkA = {NULL, 2, 30, 20, 40, 10000, 20000, 0, 0, 50000, 60000, 10, -16777088, 16, 16, 1, 0, 0, 0, 0, 0};
static ParticleParams5 sHitRing = {NULL, 4, 10, 80000, 90000, 50000, 30, 10, 104000, 105999, 0, 60, 12800000, 10000000, 1000000, 6000000, 0x3C3C3C00, 0, 0, 0};
static ParticleParamsC sHitSparkB = {NULL, 29, 15, 20, 30, 13000, 15000, -3000000, 3000000, 50000, 60000, 0, -1, 5, 10, 0, 0, 0, 0, 0, 1};
static s32 sHitMinMag[8] = {30000, 30000, 24000, 0, 0, 0, 0, 0};

extern struct {
    u8 _00[4];
    TexArchive* tex;
} lbl_3_common_bss_35154;
extern BatFxTables lbl_800FC0FC;
void fn_80064344(Vec* pos, Vec* v);

// .text:0x0015F648 size:0x22C mapped:0x8079E6DC
void fn_3_15F648(s32 kind, s32 sub, Vec* pos, Vec* dir) {
    s32 color;

    switch (kind) {
    case 10:
        fn_80064344(pos, dir);
        break;
    default:
        if (sub == 1) {
            if (PSVECMag(dir) >= (f32)sHitMinMag[1] / 100000.0f) {
                sHitSparkA.tex = lbl_3_common_bss_35154.tex;
                sHitRing.tex = lbl_3_common_bss_35154.tex;
                fn_8002955C(pos, NULL, &sHitSparkA);
                fn_80030D88(pos, dir, &sHitRing, 5);
            }
        } else {
            color = fn_8004AD54(g_d_GameSettings.StadiumID, kind);
            if (PSVECMag(dir) >= (f32)sHitMinMag[0] / 100000.0f) {
                sHitBurst.tex = lbl_3_common_bss_35154.tex;
                sHitBurst.unk40 = (lbl_800FC0FC.colors[color].r << 24) | ((lbl_800FC0FC.colors[color].g << 16) & 0xFF0000) |
                                  ((lbl_800FC0FC.colors[color].b << 8) & 0xFF00);
                fn_80031CA4(pos, &sHitBurst);
            }
            if (PSVECMag(dir) >= (f32)sHitMinMag[2] / 100000.0f) {
                switch (color) {
                case 1:
                case 3:
                case 7:
                    sHitSparkB.tex = lbl_3_common_bss_35154.tex;
                    fn_8002955C(pos, NULL, &sHitSparkB);
                    break;
                }
            }
        }
        break;
    }
}
