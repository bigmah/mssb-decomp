#include "main/file_8004B284.h"
#include "main/file_800263FC.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "static/Pad.h"
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
void fn_8004B284(CharActor* model, s32 animID, u32 colorIdx, f32 frame) {
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
        untilEnd = lbl_800FB804[model->kind] - frame;
        sinceStart = frame - lbl_800FB798[model->kind];
        break;
    case 0x33:
        slot = 1;
        untilEnd = lbl_800FB8DC[model->kind] - frame;
        sinceStart = frame - lbl_800FB870[model->kind];
        break;
    case 0x34:
        slot = 2;
        untilEnd = lbl_800FB9B4[model->kind] - frame;
        sinceStart = frame - lbl_800FB948[model->kind];
        break;
    case 0x1A:
        slot = 4;
        untilEnd = lbl_800FBA8C[model->kind] - frame;
        sinceStart = frame - lbl_800FBA20[model->kind];
        break;
    case 0x1B:
        slot = 5;
        untilEnd = lbl_800FBB64[model->kind] - frame;
        sinceStart = frame - lbl_800FBAF8[model->kind];
        break;
    case 0x30:
        slot = 6;
        untilEnd = lbl_800FBC3C[model->kind] - frame;
        sinceStart = frame - lbl_800FBBD0[model->kind];
        break;
    default:
        // The original falls through here with slot/untilEnd uninitialised.
        return;
    }

    if (sinceStart < lbl_803CC818 || !(untilEnd >= lbl_803CC818)) {
        return;
    }

    dir.x = -sin(model->rot.y);
    dir.y = lbl_803CC818;
    dir.z = -cos(model->rot.y);
    if (!getAnimRelatedCoordinates(model->index,
                                   lbl_800FC0FC.animIDs[fn_800698F8(model->kind)][slot],
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
        fn_8002955C(&pos, &dir, (ParticleParamsC *)paramsB); // TODO type
        // fallthrough
    case 0:
    case 2:
    case 5:
    case 6:
    case 8:
    case 10:
    case 11:
    case 12:
        fn_80030D88(&pos, &dir, (ParticleParams5 *)params, 5); // TODO type
        break;
    }
}
#endif

// .text:0x8004B6EC size:0xC8
void fn_8004B6EC(CharActor* model, ActorObject* obj) {
    s32 flag;

    if (model == NULL || model->part == NULL) {
        flag = 1;
    } else {
        flag = ((fn_80024D2C(&model->part->player.state) >> 28) & 1) ^ 1;
    }
    if (flag) {
        if (model->jointIdx[75] != 0xFFFF) {
            fn_800B2BE4(obj->actor, model->jointIdx[75]);
        }
        if (model->jointIdx[76] != 0xFFFF) {
            fn_800B2BA8(obj->actor, model->jointIdx[76], NULL, 0);
        }
    } else {
        if (model->jointIdx[75] != 0xFFFF) {
            fn_800B2BA8(obj->actor, model->jointIdx[75], NULL, 0);
        }
        if (model->jointIdx[76] != 0xFFFF) {
            fn_800B2BE4(obj->actor, model->jointIdx[76]);
        }
    }
}

// .text:0x8004B7B4 size:0x40
s32 fn_8004B7B4(CharActor* model, ActorObject* obj) {
    if (model->jointIdx[76] != 0xFFFF) {
        fn_800B2BA8(obj->actor, model->jointIdx[76], NULL, 0);
    }
    return 0;
}

typedef struct PartPair {
    u16 a;
    u16 b;
} PartPair;

extern PartPair lbl_800FC388[];

// .text:0x8004B7F4 size:0x2F8
void fn_8004B7F4(CharActor* model, ActorObject* obj) {
    s32 idx; // table index, then loop counter; only set for charID 40/41 (the original leaves it unset otherwise)
    s32 side;
    CharParts* anim;
    u16 parts[2];
    ShapeAnimState* slots[2];

    switch (model->kind) {
    case 40:
        idx = 1;
        break;
    case 41:
        idx = 2;
        break;
    }

    if ((model->anim[0] >= 0x69 && model->anim[0] < 0x75) || model->anim[0] == -1) {
        fn_8001D180(model->index, lbl_800FC388[idx].a, 0);
        fn_8001D180(model->index, lbl_800FC388[idx].b, 0);
        fn_8001D180(model->index, 0, 0);
        fn_8001D180(model->index, 1, 0);
        return;
    }

    if (g_d_GameSettings.GameModeSelected == 6) {
        if (model->_278) {
            side = !model->_25B;
            fn_8001D180(model->index, !side, 0);
        } else {
            side = !model->_25A;
            fn_8001D180(model->index, !side, 1);
        }
    } else if (g_d_GameSettings.GameModeSelected == 7) {
        side = !model->_25B;
        fn_8001D180(model->index, !side, 0);
    } else if (model->index >= 9) {
        side = !model->_25B;
        fn_8001D180(model->index, !side, 0);
    } else {
        side = !model->_25A;
        fn_8001D180(model->index, !side, 1);
    }
    fn_8001D180(model->index, side, 0);

    anim = model->parts;
    parts[side] = lbl_800FC388[idx].a;
    parts[!side] = lbl_800FC388[idx].b;
    if (anim != NULL) {
        if (!model->_278) {
            fn_8001D180(model->index, parts[0], 0);
            fn_8001D180(model->index, parts[1], 0);
            return;
        }
        slots[side] = &anim->part[0].player.state;
        slots[!side] = &anim->part[1].player.state;
        idx = 1;
        do {
            if (fn_80024D2C(slots[idx]) & 0x20000000) {
                fn_8001D180(model->index, parts[idx], 1);
            } else {
                fn_8001D180(model->index, parts[idx], 0);
            }
        } while (idx-- != 0);
    }
}

// .text:0x8004BAEC size:0x280
void fn_8004BAEC(CharActor* model, ActorObject* obj) {
    s32 idx; // table index, then loop counter; only set for charID 18/38 (the original leaves it unset otherwise)
    s32 side;
    u32 flags;
    u16 parts[2];
    ShapeAnimState* slots[2];

    if (model == NULL) {
        return;
    }
    fn_8001D180(model->index, 0, 0);
    fn_8001D180(model->index, 1, 0);
    switch (model->kind) {
    case 38:
        idx = 0;
        break;
    case 18:
        idx = 3;
        break;
    }

    if ((model->anim[0] >= 0x69 && model->anim[0] < 0x75) || model->anim[0] == -1) {
        fn_8001D180(model->index, lbl_800FC388[idx].a, 0);
        fn_8001D180(model->index, lbl_800FC388[idx].b, 0);
        return;
    }

    if (model->parts == NULL) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 6 || g_d_GameSettings.GameModeSelected == 7) {
        if (model->_278) {
            side = !model->_25B;
        } else {
            side = !model->_25A;
        }
    } else if (model->index >= 9) {
        side = !model->_25B;
    } else {
        side = !model->_25A;
    }
    slots[side] = model->parts->part[0].player.active ? &model->parts->part[0].player.state : NULL;
    slots[!side] = model->parts->part[1].player.active ? &model->parts->part[1].player.state : NULL;
    parts[side] = lbl_800FC388[idx].a;
    parts[!side] = lbl_800FC388[idx].b;
    for (idx = 0; idx < 2; idx++) {
        if (slots[idx] != NULL) {
            flags = fn_80024D2C(slots[idx]);
        } else {
            flags = 0;
        }
        if ((flags & 0x20000000) && (model->_274 || model->_278)) {
            fn_8001D180(model->index, parts[idx], 1);
        } else {
            fn_8001D180(model->index, parts[idx], 0);
        }
    }
}

// .text:0x8004BD6C size:0x144
s32 fn_8004BD6C(CharActor* model, ActorObject* obj) {
    u16 boneA;
    u16 boneB;
    u32 partA;
    u32 partB;

    switch (model->kind) {
    case 38:
        boneA = model->jointIdx[20];
        partA = 2;
        boneB = model->jointIdx[26];
        partB = 3;
        break;
    case 18:
        boneA = model->jointIdx[74];
        partA = 4;
        boneB = model->jointIdx[75];
        partB = 5;
        break;
    case 40:
        boneA = model->jointIdx[60];
        partA = 6;
        boneB = model->jointIdx[61];
        partB = 7;
        break;
    case 41:
        boneA = model->jointIdx[60];
        partA = 6;
        boneB = model->jointIdx[61];
        partB = 7;
        break;
    default:
        return 0;
    }
    fn_8001D180(model->index, 0, 0);
    fn_8001D180(model->index, 1, 0);
    fn_8001D180(model->index, partA, 0);
    fn_8001D180(model->index, partB, 0);
    if (boneA != 0xFFFF) {
        fn_800B2B74(obj->actor, boneA);
    }
    if (boneB != 0xFFFF) {
        fn_800B2B74(obj->actor, boneB);
    }
    return 0;
}
