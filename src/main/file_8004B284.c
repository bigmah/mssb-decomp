#include "main/file_8004B284.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "stl/mem.h"
#include "stl/math.h"

typedef struct UnkState_80366158 {
    /*0x00*/ u8 pad00[0x28];
    /*0x28*/ u8 unk28;
    /*0x29*/ u8 pad29[7];
} UnkState_80366158;

extern UnkState_80366158 lbl_80366158;
extern BatFxParams lbl_800FBF10;
extern BatFxTables lbl_800FC0FC;
extern s32 lbl_803CBD0C;
extern f32 lbl_803CC818; // 0.0f

// Per-character [start, end] frame windows (indexed by charID).
extern s16 lbl_800FB798[];
extern s16 lbl_800FB804[];
extern s16 lbl_800FB870[];
extern s16 lbl_800FB8DC[];
extern s16 lbl_800FB948[];
extern s16 lbl_800FB9B4[];
extern s16 lbl_800FBA20[];
extern s16 lbl_800FBA8C[];
extern s16 lbl_800FBAF8[];
extern s16 lbl_800FBB64[];
extern s16 lbl_800FBBD0[];
extern s16 lbl_800FBC3C[];

s32 fn_800698F8(s32 charID);

// Spawns the swing effect when `frame` is inside the character's window for animID.
// .text:0x8004B284 size:0x468
// NONMATCHING 91%: the original addresses lbl_800FC0FC through the lbl_800FBF10 base (same-TU data),
// and its default case runs on with uninitialised values (here it returns)
#if NONMATCHING
void fn_8004B284(CharModel* model, s32 animID, u32 colorIdx, f32 frame) {
    BatFxParams* fx = &lbl_800FBF10;
    s32 slot;
    f32 untilEnd;
    f32 sinceStart;
    EffectParams* params;
    EffectParamsB* paramsB;
    Vec dir;
    Vec pos;

    if (lbl_80366158.unk28 == 1) {
        return;
    }

    switch (animID) {
    case 0x32:
        slot = 0;
        untilEnd = lbl_800FB804[model->charID] - frame;
        sinceStart = frame - lbl_800FB798[model->charID];
        break;
    case 0x33:
        slot = 1;
        untilEnd = lbl_800FB8DC[model->charID] - frame;
        sinceStart = frame - lbl_800FB870[model->charID];
        break;
    case 0x34:
        slot = 2;
        untilEnd = lbl_800FB9B4[model->charID] - frame;
        sinceStart = frame - lbl_800FB948[model->charID];
        break;
    case 0x1A:
        slot = 4;
        untilEnd = lbl_800FBA8C[model->charID] - frame;
        sinceStart = frame - lbl_800FBA20[model->charID];
        break;
    case 0x1B:
        slot = 5;
        untilEnd = lbl_800FBB64[model->charID] - frame;
        sinceStart = frame - lbl_800FBAF8[model->charID];
        break;
    case 0x30:
        slot = 6;
        untilEnd = lbl_800FBC3C[model->charID] - frame;
        sinceStart = frame - lbl_800FBBD0[model->charID];
        break;
    default:
        // The original falls through here with slot/untilEnd uninitialised.
        return;
    }

    if (sinceStart < lbl_803CC818 || !(untilEnd >= lbl_803CC818)) {
        return;
    }

    dir.x = -sin(model->rotY);
    dir.y = lbl_803CC818;
    dir.z = -cos(model->rotY);
    if (!getAnimRelatedCoordinates(model->playerIdx,
                                   lbl_800FC0FC.animIDs[fn_800698F8(model->charID)][slot],
                                   (VecXYZ*)&pos)) {
        memcpy(&pos, &model->pos, sizeof(Vec));
    }

    params = NULL;
    switch (animID) {
    case 0x32:
    case 0x33:
    case 0x34:
        params = &fx->params[0];
        break;
    case 0x1A:
    case 0x1B:
        params = &fx->params[1];
        break;
    case 0x30:
        params = &fx->params[2];
        break;
    }
    paramsB = NULL;
    switch (animID) {
    case 0x32:
    case 0x33:
    case 0x34:
        paramsB = &fx->paramsB[0];
        break;
    case 0x1A:
    case 0x1B:
        paramsB = &fx->paramsB[1];
        break;
    case 0x30:
        paramsB = &fx->paramsB[2];
        break;
    }

    params->stamp = lbl_803CBD0C;
    params->rgb = (lbl_800FC0FC.colors[colorIdx].r << 24) | (lbl_800FC0FC.colors[colorIdx].g << 16) |
                  (lbl_800FC0FC.colors[colorIdx].b << 8);
    paramsB->stamp = lbl_803CBD0C;

    switch (colorIdx) {
    case 1:
    case 3:
    case 7:
        fn_8002955C(&pos, &dir, paramsB);
        // fallthrough
    case 0:
    case 2:
    case 5:
    case 6:
    case 8:
    case 10:
    case 11:
    case 12:
        fn_80030D88(&pos, &dir, params, 5);
        break;
    }
}
#endif

// .text:0x8004B6EC size:0xC8
void fn_8004B6EC(CharModel* model, GameActor** actor) {
    s32 flag;

    if (model == NULL || model->anim == NULL) {
        flag = 1;
    } else {
        flag = ((fn_80024D2C(&model->anim->slots[0]) >> 28) & 1) ^ 1;
    }
    if (flag) {
        if (model->bone1F8 != 0xFFFF) {
            fn_800B2BE4(*actor, model->bone1F8);
        }
        if (model->bone1FA != 0xFFFF) {
            fn_800B2BA8(*actor, model->bone1FA, NULL, 0);
        }
    } else {
        if (model->bone1F8 != 0xFFFF) {
            fn_800B2BA8(*actor, model->bone1F8, NULL, 0);
        }
        if (model->bone1FA != 0xFFFF) {
            fn_800B2BE4(*actor, model->bone1FA);
        }
    }
}

// .text:0x8004B7B4 size:0x40
s32 fn_8004B7B4(CharModel* model, GameActor** actor) {
    if (model->bone1FA != 0xFFFF) {
        fn_800B2BA8(*actor, model->bone1FA, NULL, 0);
    }
    return 0;
}

typedef struct PartPair {
    u16 a;
    u16 b;
} PartPair;

extern PartPair lbl_800FC388[];

// .text:0x8004B7F4 size:0x2F8
void fn_8004B7F4(CharModel* model) {
    return;
}

// .text:0x8004BAEC size:0x280
void fn_8004BAEC(CharModel* model) {
    return;
}

// .text:0x8004BD6C size:0x144
s32 fn_8004BD6C(CharModel* model, GameActor** actor) {
    return 0;
}
