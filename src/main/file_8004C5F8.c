#include "main/file_8004C5F8.h"
#include "main/file_80011640.h"
#include "main/file_8000F150.h"
#include "main/file_8004B284.h"
#include "main/file_80008E00.h"
#include "Dolphin/gx.h"
#include "musyx/musyx.h"
#include "main/file_800B0724.h"
#include "main/file_800263FC.h"
#include "main/file_80034F50.h"

extern LayoutGroup* lbl_803CC1B8;
extern int rand(void);
extern CharTableEntry lbl_800E8558[CHAR_TABLE(54)];
extern u8 lbl_800EFBA4[];
extern u8 lbl_800FDE84[];
extern u8 lbl_800FE5D4[];
extern u8 lbl_800FE930[][6];
extern camera_803c639c_s lbl_803C639C[4];
extern s32 lbl_803CBD14;
extern s32 lbl_803CB880;

void fn_800521B0(void);
extern f32 fn_800335BC(s32 angle);
extern f32 fn_800335EC(s32 angle);
extern BatFxTables lbl_800FC0FC;
extern void* lbl_803CBD0C; // TexArchive* of the effect particles (set by fn_8004B1B8)
extern u8 lbl_803CBBC0;
#include "main/file_800B4A44.h"
extern s16 lbl_800FEB08[5][4];
extern DialogLayout lbl_800FEAAC[11];
extern u8 lbl_800FEAF0[12][2];
extern u8 lbl_800FE93C[][5];
extern u8 lbl_800FE924[][6];
extern u8 lbl_800FE5C8[];
extern u8 lbl_800E854C[];
extern s32 fn_80024C04(s32 index);
extern u8 lbl_800FDE60[];
extern u8 lbl_80361B20[];
// Column-order and layout tables that follow lbl_800FE5D4 / lbl_800FE93C / lbl_800FDE84.
extern u8 lbl_800FE5E0[6][6];
extern u8 lbl_800FDEB8[12][12];
extern SpaniDesc lbl_800FE604[25];
extern SpaniDesc lbl_800FDF48[52];
extern SpaniDesc lbl_800FE96C[10];
#define lbl_800FE5D4_colOrder lbl_800FE5E0
#define lbl_800FE93C_alts lbl_800FE93C
#define lbl_800FDE84_colOrder lbl_800FDEB8
extern u16 lbl_803CB870[];


// Swing effect templates (.stamp is set at runtime).
SwingFx lbl_800FC890 = {
    {
        {NULL, 4, 4, 40000, 10000, {10000, 60, 15, 110000, 102000, 0, 40, 12800000, 1000000, 0, 0}, 0xFFFFFF00, {0, 75000, 0}},
        {NULL, 4, 7, 64999, 10000, {10000, 60, 15, 110000, 101000, 0, 40, 12800000, 3000000, 0, 0}, 0xFFFFFF00, {0, 75000, 0}},
        {NULL, 4, 3, 64999, 0, {10000, 30, 5, 129999, 104999, 0, 60, 12800000, 6000000, 0, 0}, 0xFFFFFF00, {0, 75000, 0}},
    },
    {
        {NULL, 29, {10, 10, 12, 15000, 20000, -3000000, 3000000, 35000, 40000, 500, -1, 5, 10, 0, 0, 3000000, 0, 4500000, 1}},
        {NULL, 29, {15, 10, 20, 20000, 21000, -3000000, 3000000, 40000, 45000, 500, -1, 5, 10, 0, 1000000, 3000000, 1000000, 4500000, 1}},
    },
};

// .text:0x8004C5F8 size:0x404
// NONMATCHING 93%: register allocation (saved-register order)
#if NONMATCHING
void fn_8004C5F8(CharActor* actor, s32 unused, u32 kind) {
    SwingFx* tbl = &lbl_800FC890;
    Vec dir;
    Vec pos;
    s32 hasBat;
    EffectParams* fx;
    EffectParamsB* trail;

    if (lbl_80366158._28 == 1) {
        return;
    }
    dir.x = fn_800335EC((s32)(0.5f + 1024.0f * actor->rot.y / 3.1415927f));
    dir.z = fn_800335BC((s32)(0.5f + 1024.0f * actor->rot.y / 3.1415927f));
    dir.y = 0.0f;
    hasBat = actor->_276 & 1;
    switch (kind) {
    case 1:
    case 3:
    case 7:
        if (hasBat) {
            trail = &tbl->trails[1];
            fx = &tbl->params[1];
            if (actor->_279[1] != 0) {
                fx = &tbl->params[2];
            }
            fx->stamp = lbl_803CBD0C;
            fx->rgb = (lbl_800FC0FC.colors[kind].r << 24) | ((lbl_800FC0FC.colors[kind].g & 0xFF) << 16) |
                      (lbl_800FC0FC.colors[kind].b << 8);
        } else {
            trail = &tbl->trails[0];
        }
        trail->stamp = lbl_803CBD0C;
        if (hasBat && actor->_279[1] != 0) {
            actor->_279[1] = 0;
            if (lbl_803CBBC0 != 0) {
                getAnimRelatedCoordinates(actor->index, 0x1E, &pos);
                pos.y = 0.0f;
                fn_80030D88(&pos, &dir, (ParticleParams5 *)fx, 5);
            } else {
                getAnimRelatedCoordinates(actor->index, 0x22, &pos);
                pos.y = 0.0f;
                fn_80030D88(&pos, &dir, (ParticleParams5 *)fx, 5);
            }
        }
        if ((actor->_276 & 0xA) == 2) {
            getAnimRelatedCoordinates(actor->index, 0x1E, &pos);
            pos.y = 0.0f;
            if (hasBat && actor->_279[1] == 0) {
                fn_80030D88(&pos, &dir, (ParticleParams5 *)fx, 5);
            }
            fn_8002955C(&pos, &dir, (ParticleParamsC *)trail);
        }
        if ((actor->_276 & 0x14) == 4) {
            getAnimRelatedCoordinates(actor->index, 0x22, &pos);
            pos.y = 0.0f;
            if (hasBat && actor->_279[1] == 0) {
                fn_80030D88(&pos, &dir, (ParticleParams5 *)fx, 5);
            }
            fn_8002955C(&pos, &dir, (ParticleParamsC *)trail);
        }
        break;
    case 0:
    case 2:
    case 5:
    case 6:
    case 8:
    case 10:
    case 11:
    case 12:
        if (!hasBat) {
            fx = &tbl->params[0];
        } else if (actor->_279[1] != 0) {
            fx = &tbl->params[2];
        } else {
            fx = &tbl->params[1];
        }
        fx->stamp = lbl_803CBD0C;
        fx->rgb = (lbl_800FC0FC.colors[kind].r << 24) | ((lbl_800FC0FC.colors[kind].g & 0xFF) << 16) |
                  (lbl_800FC0FC.colors[kind].b << 8);
        if (hasBat && actor->_279[1] != 0) {
            actor->_279[1] = 0;
            if (lbl_803CBBC0 != 0) {
                getAnimRelatedCoordinates(actor->index, 0x1E, &pos);
                pos.y = 0.0f;
                fn_80030D88(&pos, &dir, (ParticleParams5 *)fx, 5);
            } else {
                getAnimRelatedCoordinates(actor->index, 0x22, &pos);
                pos.y = 0.0f;
                fn_80030D88(&pos, &dir, (ParticleParams5 *)fx, 5);
            }
            break;
        }
        if ((actor->_276 & 0xA) == 2) {
            getAnimRelatedCoordinates(actor->index, 0x1E, &pos);
            pos.y = 0.0f;
            fn_80030D88(&pos, &dir, (ParticleParams5 *)fx, 5);
        }
        if ((actor->_276 & 0x14) == 4) {
            getAnimRelatedCoordinates(actor->index, 0x22, &pos);
            pos.y = 0.0f;
            fn_80030D88(&pos, &dir, (ParticleParams5 *)fx, 5);
        }
        break;
    }
}
#endif
