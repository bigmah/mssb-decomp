#include "main/file_8004BEB0.h"
#include "main/file_80011640.h"
#include "main/file_800263FC.h"
#include "main/file_8004C19C.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "static/Pad.h"
#include "stl/mem.h"

typedef struct UnkState_80366158 {
    /*0x00*/ u8 pad00[0x28];
    /*0x28*/ u8 unk28;
    /*0x29*/ u8 pad29[7];
} UnkState_80366158;

extern UnkState_80366158 lbl_80366158;
extern s16 lbl_800FBCA8[]; // per-character start frame
extern s16 lbl_800FBD14[]; // per-character end frame
// Effect templates; .stamp is filled in at runtime.
EffectParams lbl_800FC398 = {NULL, 7, 3, 100000, 30000, {10000, 12, 8, 110000, 50000, 0, 60, 4500000, 20000000, 0, 2000000}, 0xFFFFFF00, {0, 75000, 0}};
EffectParams lbl_800FC3E8 = {NULL, 7, 10, 18000, 20000, {60000, 12, 6, 109000, 101000, 0, 60, 4500000, 9400000, -1000000, 4500000}, 0xFFFFFF00, {0, 75000, 0}};
EffectParams lbl_800FC438 = {NULL, 4, 1, 60000, 10000, {50000, 30, 8, 104000, 105999, 0, 90, 12800000, 10000000, 1000000, 6000000}, 0x3C3C3C00, {0, 75000, 0}};
EffectParams* lbl_800FC488[3] = {&lbl_800FC398, &lbl_800FC3E8, &lbl_800FC438};
s32 lbl_800FC494[54][3] = {0}; // per-character effect offset, fixed point (x100000)
extern void* lbl_803CBD0C; // TexArchive* of the effect particles (set by fn_8004B1B8)

// .text:0x8004BEB0 size:0x1E4
void fn_8004BEB0(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    Vec pos;
    Vec dir;
    Mtx m;
    GameControl ctrl;
    void* stamp;

    if (lbl_80366158.unk28 == 1) {
        return;
    }
    if (frame < lbl_800FBCA8[model->kind] || frame > lbl_800FBD14[model->kind]) {
        return;
    }

    pos.x = lbl_800FC494[model->kind][0] / 100000.0f;
    pos.y = lbl_800FC494[model->kind][1] / 100000.0f;
    pos.z = lbl_800FC494[model->kind][2] / 100000.0f;
    fn_8001B728(model->index, 4, &pos);

    ctrl.base.type = 0;
    CTRLSetRotation(&ctrl.base, model->rot.x, model->rot.y, model->rot.z);
    CTRLBuildMatrix(&ctrl.base, m);
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 1.0f;
    PSMTXMultVec(m, &dir, &dir);

    stamp = lbl_803CBD0C;
    lbl_800FC488[2]->stamp = stamp;
    lbl_800FC488[1]->stamp = stamp;
    lbl_800FC488[0]->stamp = stamp;
    fn_80030D88(&pos, &dir, (ParticleParams5 *)lbl_800FC488[0], 5); // TODO type
    fn_80030D88(&pos, &dir, (ParticleParams5 *)lbl_800FC488[1], 5); // TODO type
    fn_80030D88(&pos, &dir, (ParticleParams5 *)lbl_800FC488[2], 5); // TODO type
}

extern EffectParams lbl_800FC720;
EffectParams* lbl_803CB860 = &lbl_800FC720;
DECL_SECT(".sdata") RGB8 lbl_803CB864[4] = {{0xFF, 0xFF, 0xFF}, {0xFF, 0xB6, 0x64}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}};
extern void* lbl_803CBD0C; // TexArchive* of the effect particles (set by fn_8004B1B8)

// .text:0x8004C094 size:0x74
void fn_8004C094(Vec* pos) {
    EffectParams params;
    EffectParams* p = &params;

    if (pos != NULL) {
        memcpy(p, lbl_803CB860, sizeof(EffectParams));
        p->stamp = lbl_803CBD0C;
        p->unk0C = 120000;
        p->unk10 = 60000;
        fn_80031CA4(pos, (ParticleParams5 *)(u32*)p); // TODO type
    }
}

// .text:0x8004C108 size:0x94
void fn_8004C108(Vec* pos, u8 colorIdx) {
    EffectParams params;
    EffectParams* p = &params;

    if (pos != NULL) {
        memcpy(p, lbl_803CB860, sizeof(EffectParams));
        p->stamp = lbl_803CBD0C;
        p->rgb = (lbl_803CB864[colorIdx].r << 24) | ((lbl_803CB864[colorIdx].g & 0xFF) << 16) |
                 (lbl_803CB864[colorIdx].b << 8);
        fn_80031CA4(pos, (ParticleParams5 *)(u32*)p); // TODO type
    }
}
