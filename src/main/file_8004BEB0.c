#include "main/file_8004BEB0.h"
#include "main/file_800263FC.h"
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
extern s32 lbl_800FC494[][3]; // per-character effect offset, fixed point (x100000)
extern EffectParams* lbl_800FC488[3];
extern s32 lbl_803CBD0C;
extern f32 lbl_803CC82C; // 0.0f
extern f32 lbl_803CC830; // 1.0f

// .text:0x8004BEB0 size:0x1E4
void fn_8004BEB0(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
    Vec pos;
    Vec dir;
    Mtx m;
    GameControl ctrl;
    s32 stamp;

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
    dir.x = lbl_803CC82C;
    dir.y = lbl_803CC82C;
    dir.z = lbl_803CC830;
    PSMTXMultVec(m, &dir, &dir);

    stamp = lbl_803CBD0C;
    lbl_800FC488[2]->stamp = stamp;
    lbl_800FC488[1]->stamp = stamp;
    lbl_800FC488[0]->stamp = stamp;
    fn_80030D88(&pos, &dir, (ParticleParams5 *)lbl_800FC488[0], 5); // TODO type
    fn_80030D88(&pos, &dir, (ParticleParams5 *)lbl_800FC488[1], 5); // TODO type
    fn_80030D88(&pos, &dir, (ParticleParams5 *)lbl_800FC488[2], 5); // TODO type
}

extern EffectParams* lbl_803CB860;
DECL_SECT(".sdata") extern RGB8 lbl_803CB864[4];
extern s32 lbl_803CBD0C;

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
