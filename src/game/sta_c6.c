#include "game/sta_c6.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_000D8A10_text.h"
#include "Dolphin/stl.h"
#include "Dolphin/os.h"
#include "C3/control.h"
#include "C3/geoPalette.h"
#include "main/file_800B4A44.h"
// main/file_800BD3EC.h clashes with UnknownHomes_Static.h (fn_800BD670)
void fn_800BD478(GameActor** actor, struct ActorLayoutFile* layout);
void fn_800BD548(ActorObject* obj, u8 numLights, ...);
#include "main/file_80011640.h"
#include "musyx/musyx.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/rand.h"
#include "static/UnknownHomes_Static.h"

// Toy Field.

#pragma dont_inline on

extern void PSMTXIdentity(Mtx);
extern void* _OSAllocFromHeap(s32 align, s32 size);
extern void DCStoreRange(void* addr, u32 numBytes);
extern s32 fn_8005268C(void);
extern void* fn_80052734(s32);
extern u8 fn_800B3C04(s32 viewIndex, GameActor* actor, Mtx camera);
// rep_1D58 (stadium objects)
void fn_3_B8414(Vec* min, Vec* max);
void fn_3_B8464(Mtx m, void* shadow);
void fn_3_B8574(void);
void fn_3_B97DC(ActorObject* obj, void* animBank);
void fn_3_B9D68(void* names, s32 n, void** files, u32* out);

// View matrix of the current camera.
#define CUR_VIEW() (((camera_803c639c_s*)fn_80052734(fn_8005268C()))->view)
#define CUR_CAMERA_VIEW() (fn_80052768_getCamera(fn_8005268C())->view)

extern StaC6List lbl_3_common_bss_350E4;
extern u8 lbl_3_data_19018[3][4];   // overlay colours picked by fn_3_E6410 / fn_3_E64A8
extern StaC6Data lbl_3_data_19024;
extern u8 lbl_3_data_19610[];       // TODO type: file name table for fn_3_B9D68 (47 files)
extern s8 lbl_3_data_1963F;         // object index the ball touched
extern s8 lbl_3_data_19640;
extern Vec lbl_3_data_19644[7];     // wall panel positions
extern f32 lbl_3_data_19698[7];     // wall panel rotations
extern StaC6Data2 lbl_3_data_196B4;
extern u8 lbl_3_data_1976C;         // nonzero: show the lit overlay (bone 2)
extern u8 lbl_80366158[];
extern u16 lbl_3_data_81DC[];       // per stadium: crowd sound id base
extern MinigameSoundParams lbl_3_data_8404[];
extern MinigameSoundParams lbl_3_data_84B8[];

extern f32 lbl_3_rodata_2B90;
extern f32 lbl_3_rodata_2B94;
extern f32 lbl_3_rodata_2B98;
extern f32 lbl_3_rodata_2B9C;
extern f32 lbl_3_rodata_2BA0;
extern f32 lbl_3_rodata_2BA4;
extern char lbl_3_rodata_2BB0[];
extern char lbl_3_rodata_2BBC[];

// This unit's .bss (AE50..AEE0) as statics, declared in reverse address order.
// AE52..AE7A are single bytes so the pool has no alignment gaps; AE51 is its own
// object so the store compiles to stb 1(base) with no extra addi.
static StaC6Spot* lbl_3_bss_AEB4[11]; // [0]: field panel spots in use
static StaC6Pad* lbl_3_bss_AEB0;      // wall panels in use
static s8 lbl_3_bss_AEAE;             // layout index
static u8 lbl_3_bss_AEAD;             // number of field panel objects
static u8 lbl_3_bss_AEAC;             // number of panels (kinds 0-15)
static s32 lbl_3_bss_AE88[9];
static s32 lbl_3_bss_AE84;
static u8 lbl_3_bss_AE80[4];
static u8 lbl_3_bss_AE7C;
static u8 lbl_3_bss_AE7B;
static u8 lbl_3_bss_AE52, lbl_3_bss_AE53, lbl_3_bss_AE54, lbl_3_bss_AE55, lbl_3_bss_AE56, lbl_3_bss_AE57, lbl_3_bss_AE58, lbl_3_bss_AE59, lbl_3_bss_AE5A, lbl_3_bss_AE5B, lbl_3_bss_AE5C, lbl_3_bss_AE5D, lbl_3_bss_AE5E, lbl_3_bss_AE5F, lbl_3_bss_AE60, lbl_3_bss_AE61, lbl_3_bss_AE62, lbl_3_bss_AE63, lbl_3_bss_AE64, lbl_3_bss_AE65, lbl_3_bss_AE66, lbl_3_bss_AE67, lbl_3_bss_AE68, lbl_3_bss_AE69, lbl_3_bss_AE6A, lbl_3_bss_AE6B, lbl_3_bss_AE6C, lbl_3_bss_AE6D, lbl_3_bss_AE6E, lbl_3_bss_AE6F, lbl_3_bss_AE70, lbl_3_bss_AE71, lbl_3_bss_AE72, lbl_3_bss_AE73, lbl_3_bss_AE74, lbl_3_bss_AE75, lbl_3_bss_AE76, lbl_3_bss_AE77, lbl_3_bss_AE78, lbl_3_bss_AE79, lbl_3_bss_AE7A;
static u8 lbl_3_bss_AE51;
static u8 lbl_3_bss_AE50;

#define BONE(obj, i) ((obj)->actor->boneArray[i])

// .text:0x000E59B4 size:0x68 mapped:0x80724A48
void fn_3_E59B4(StaC6Obj* o) {
    GameActor* actor = o->actorObj->actor;
    if (lbl_3_rodata_2B90 + fn_800B4C40(actor) > lbl_3_rodata_2B94) {
        fn_800B4CA0(actor, lbl_3_rodata_2B98);
    }
    AnimateActorBones(actor);
}

// .text:0x000E5A1C size:0x68 mapped:0x80724AB0
void fn_3_E5A1C(StaC6Obj* o) {
    GameActor* actor = o->actorObj->actor;
    if (lbl_3_rodata_2B90 + fn_800B4C40(actor) > lbl_3_rodata_2B9C) {
        fn_800B4CA0(actor, lbl_3_rodata_2BA0);
    }
    AnimateActorBones(actor);
}

// .text:0x000E5A84 size:0x238 mapped:0x80724B18
// Place the object's bones at its spot.
void fn_3_E5A84(StaC6Obj* o) {
    Control c;
    Mtx m;
    GameBone* bone;
    s32 i;
    PSMTXIdentity(m);
    c.type = 0;
    if (o->kind < 8) {
        CTRLSetTranslation(&c, lbl_3_bss_AEB4[0][o->index].pos.x, lbl_3_bss_AEB4[0][o->index].pos.y, lbl_3_bss_AEB4[0][o->index].pos.z);
        CTRLSetRotation(&c, 0.0f, lbl_3_bss_AEB4[0][o->index].rotY, 0.0f);
    } else {
        CTRLSetTranslation(&c, lbl_3_data_19644[o->slot].x, lbl_3_data_19644[o->slot].y, lbl_3_data_19644[o->slot].z);
        CTRLSetRotation(&c, 0.0f, lbl_3_data_19698[o->slot], 0.0f);
    }
    CTRLBuildMatrix(&c, m);
    for (i = 0; i < o->actorObj->actor->totalBones; i++) {
        bone = o->actorObj->actor->boneArray[i];
        CTRLBuildMatrix(&bone->orientCtrl.base, bone->forwardMtx);
        PSMTXConcat(m, bone->forwardMtx, bone->forwardMtx);
        PSMTXCopy(bone->forwardMtx, bone->dispObj->worldMatrix);
    }
    if (o->subObj != NULL) {
        for (i = 0; i < o->subObj->actor->totalBones; i++) {
            bone = o->subObj->actor->boneArray[i];
            CTRLBuildMatrix(&bone->orientCtrl.base, bone->forwardMtx);
            PSMTXConcat(m, bone->forwardMtx, bone->forwardMtx);
            if (bone->dispObj != NULL) {
                PSMTXCopy(bone->forwardMtx, bone->dispObj->worldMatrix);
            }
        }
        o->subObj->actor->flags = fn_800B3C04(0, o->subObj->actor, CUR_VIEW());
    }
    o->actorObj->actor->flags = fn_800B3C04(0, o->actorObj->actor, CUR_VIEW());
}

// .text:0x000E5CBC size:0x158 mapped:0x80724D50
// Blend the overlay colour from colorFrom (t = 0) to colorTo (t = 1).
void fn_3_E5CBC(StaC6Obj* o, f32 t) {
    u8* from = o->colorFrom;
    u8* to = o->colorTo;
    f32 r;
    if (t > 1.0f) {
        t = 1.0f;
    } else if (t < lbl_3_rodata_2BA4) {
        t = lbl_3_rodata_2BA4;
    }
    r = 1.0f - t;
    o->color[0] = (u8)(r * (f32)from[0] + t * (f32)to[0]);
    o->color[1] = (u8)(r * (f32)from[1] + t * (f32)to[1]);
    o->color[2] = (u8)(r * (f32)from[2] + t * (f32)to[2]);
    o->color[3] = (u8)(r * (f32)from[3] + t * (f32)to[3]);
}

// .text:0x000E5E14 size:0x5C mapped:0x80724EA8
// Bytes per colour of a display object's colour array.
s32 fn_3_E5E14(u8* p) {
    switch ((u8)((s32)((struct DODisplayObj*)p)->colorData->quantizeInfo >> 4)) {
    case 0:
    case 3:
        return 2;
    case 5:
        return 4;
    case 1:
    case 2:
    case 4:
        return 3;
    default:
        return 0;
    }
}

// .text:0x000E5E70 size:0x17C mapped:0x80724F04
// Decode one colour of format fmt >> 4 to RGBA.
void fn_3_E5E70(u8* out, u8 fmt, void* src) {
    u16* s16p = src;
    u32* s32p = src;
    s32 f = (fmt >> 4) & 0xF;
    if (out == NULL || src == NULL) {
        return;
    }
    switch (f) {
    case 0:
        out[0] = (*s16p >> 8) & 0xF8;
        out[1] = (*s16p >> 3) & 0xFC;
        out[2] = (*s16p << 3) & 0xF8;
        out[3] = 0xFF;
        break;
    case 3:
        out[0] = (*s16p >> 12) & 0xF;
        out[1] = (*s16p >> 8) & 0xF;
        out[2] = (*s16p >> 4) & 0xF;
        out[3] = *s16p & 0xF;
        out[0] = out[0] | (out[0] << 4);
        out[1] = out[1] | (out[1] << 4);
        out[2] = out[2] | (out[2] << 4);
        out[3] = out[3] | (out[3] << 4);
        break;
    case 5:
        out[0] = *s32p >> 24;
        out[1] = *s32p >> 16;
        out[2] = *s32p >> 8;
        out[3] = *s32p;
        break;
    case 1:
    case 2:
        out[0] = *s32p >> 24;
        out[1] = *s32p >> 16;
        out[2] = *s32p >> 8;
        out[3] = 0xFF;
        break;
    case 4:
        out[0] = __rlwinm(*s16p, 16, 24, 29);
        out[1] = (*s16p >> 10) & 0xFC;
        out[2] = (*s16p >> 4) & 0xFC;
        out[3] = (*s16p << 2) & 0xFC;
        break;
    }
}

// .text:0x000E5FEC size:0x424 mapped:0x80725080
// Write the overlay colour and the body colour into the models' colour arrays.
// (Format 4 overwrites instead of or-ing, as in the original.)
void fn_3_E5FEC(StaC6Obj* o) {
    ColorData* cd;
    void* dst;

    cd = BONE(o->subObj, 1)->dispObj->colorData;
    dst = cd->colorArray;
    switch ((u8)((s32)cd->quantizeInfo >> 4)) {
    case 0:
        *(u16*)dst = ((u16)(o->color[0] >> 3) & 0x1F) << 11;
        *(u16*)dst = *(u16*)dst | (((u16)(o->color[1] >> 2) & 0x3F) << 5);
        *(u16*)dst = *(u16*)dst | (((u16)(o->color[2] >> 3) & 0x1F));
        DCStoreRange(dst, 2);
        break;
    case 3:
        *(u16*)dst = ((u16)(o->color[0] >> 4) & 0xF) << 12;
        *(u16*)dst = *(u16*)dst | (((u16)(o->color[1] >> 4) & 0xF) << 8);
        *(u16*)dst = *(u16*)dst | (((u16)(o->color[2] >> 4) & 0xF) << 4);
        *(u16*)dst = *(u16*)dst | (((u16)(o->color[3] >> 4) & 0xF));
        DCStoreRange(dst, 2);
        break;
    case 5:
        memcpy(dst, o->color, 4);
        DCStoreRange(dst, 4);
        break;
    case 1:
    case 2:
        *(u32*)dst = o->color[0] << 16;
        *(u32*)dst = *(u32*)dst | (o->color[1] << 8);
        *(u32*)dst = *(u32*)dst | o->color[2];
        DCStoreRange(dst, 3);
        break;
    case 4:
        *(u32*)dst = (o->color[0] << 24) & 0xFC000000;
        *(u32*)dst = (o->color[1] << 18) & 0x3F00000;
        *(u32*)dst = (o->color[2] << 12) & 0xFC000;
        *(u32*)dst = (o->color[3] << 6) & 0x3F00;
        DCStoreRange(dst, 3);
        break;
    }
    if (lbl_3_data_1976C != 0) {
        if (o->lit != 0) {
            BONE(o->subObj, 2)->dispObj = BONE(o->subObj, 2)->baseDispObj;
        } else {
            BONE(o->subObj, 2)->dispObj = NULL;
        }
    } else {
        BONE(o->subObj, 2)->dispObj = NULL;
    }
    cd = BONE(o->actorObj, 0)->dispObj->colorData;
    dst = cd->colorArray;
    switch ((u8)((s32)cd->quantizeInfo >> 4)) {
    case 0:
        *(u16*)dst = ((u16)(o->bodyColor[0] >> 3) & 0x1F) << 11;
        *(u16*)dst = *(u16*)dst | (((u16)(o->bodyColor[1] >> 2) & 0x3F) << 5);
        *(u16*)dst = *(u16*)dst | (((u16)(o->bodyColor[2] >> 3) & 0x1F));
        DCStoreRange(dst, 2);
        break;
    case 3:
        *(u16*)dst = ((u16)(o->bodyColor[0] >> 4) & 0xF) << 12;
        *(u16*)dst = *(u16*)dst | (((u16)(o->bodyColor[1] >> 4) & 0xF) << 8);
        *(u16*)dst = *(u16*)dst | (((u16)(o->bodyColor[2] >> 4) & 0xF) << 4);
        *(u16*)dst = *(u16*)dst | (((u16)(o->bodyColor[3] >> 4) & 0xF));
        DCStoreRange(dst, 2);
        break;
    case 5:
        memcpy(dst, o->bodyColor, 4);
        DCStoreRange(dst, 4);
        break;
    case 1:
    case 2:
        *(u32*)dst = o->bodyColor[0] << 16;
        *(u32*)dst = *(u32*)dst | (o->bodyColor[1] << 8);
        *(u32*)dst = *(u32*)dst | o->bodyColor[2];
        DCStoreRange(dst, 3);
        break;
    case 4:
        *(u32*)dst = (o->bodyColor[0] << 24) & 0xFC000000;
        *(u32*)dst = (o->bodyColor[1] << 18) & 0x3F00000;
        *(u32*)dst = (o->bodyColor[2] << 12) & 0xFC000;
        *(u32*)dst = (o->bodyColor[3] << 6) & 0x3F00;
        DCStoreRange(dst, 3);
        break;
    }
}

// .text:0x000E6410 size:0x98 mapped:0x807254A4
// Pick a random overlay colour other than colorFrom.
void fn_3_E6410(StaC6Obj* o) {
    u8* list[3];
    u8** w = list;
    s32 i;
    for (i = 0; i < 3; i++) {
        if (o->colorFrom != lbl_3_data_19018[i]) {
            *w++ = lbl_3_data_19018[i];
        }
    }
    o->colorTo = list[rand() % 2];
}

// .text:0x000E64A8 size:0x80 mapped:0x8072553C
u32* fn_3_E64A8(void) {
    u8 v = rand() % 3;
    switch (v) {
    case 0:
        return (u32*)lbl_3_data_19018[0];
    case 1:
        return (u32*)lbl_3_data_19018[1];
    default:
        return (u32*)lbl_3_data_19018[2];
    }
}

// .text:0x000E6528 size:0x50 mapped:0x807255BC
void fn_3_E6528(StaC6Obj* o) {
    memcpy(o->color, o->colorIdle, 4);
    o->bodyColor = lbl_3_data_19024.bodyColors[1];
    o->lit = 0;
}

// .text:0x000E6578 size:0xC0 mapped:0x8072560C
// Pick the overlay texture for the panel kind.
void fn_3_E6578(StaC6Obj* o) {
    ActorObject* sub;
    struct DODisplayObj* disp;
    TextureData* tex;

    sub = o->subObj;
    if (sub == NULL) {
        return;
    }
    disp = BONE(sub, 1)->dispObj;
    tex = disp->textureData;
    if (disp->displayData->displayStateList[2].id != 3) {
        OSPanic(lbl_3_rodata_2BB0, 0x713, lbl_3_rodata_2BBC);
    }
    if (o->kind == 2) {
        tex->texturePalette->tex[4].texIndex = 1;
    } else if (o->kind == 10) {
        tex->texturePalette->tex[4].texIndex = 0;
    } else {
        tex->texturePalette->tex[4].texIndex = 4;
    }
}

// .text:0x000E6638 size:0x4C mapped:0x807256CC
void fn_3_E6638(StaC6Obj* o) {
    GameBone* b;
    b = BONE(o->actorObj, 0);
    b->dispObj = b->baseDispObj;
    b = BONE(o->actorObj, 1);
    b->dispObj = b->baseDispObj;
    b = BONE(o->actorObj, 2);
    b->dispObj = b->baseDispObj;
}

// .text:0x000E6684 size:0x98 mapped:0x80725718
void fn_3_E6684(StaC6Obj* o) {
    GameBone* b;
    s32 i;
    for (i = 0; i < 3; i++) {
        b = BONE(o->actorObj, i);
        if (lbl_3_bss_AE80[i + 1] != 0) {
            b->dispObj = b->baseDispObj;
        } else {
            b->dispObj = NULL;
        }
    }
}

// .text:0x000E671C size:0x7C mapped:0x807257B0
void fn_3_E671C(StaC6Obj* o) {
    GameActor* actor = o->actorObj->actor;
    GameBone* b;
    b = actor->boneArray[0];
    b->dispObj = b->baseDispObj;
    b = actor->boneArray[1];
    b->dispObj = b->baseDispObj;
    b = actor->boneArray[2];
    b->dispObj = b->baseDispObj;
    b = actor->boneArray[3];
    b->dispObj = b->baseDispObj;
    b = actor->boneArray[4];
    b->dispObj = b->baseDispObj;
    b = actor->boneArray[5];
    b->dispObj = b->baseDispObj;
    b = actor->boneArray[6];
    b->dispObj = b->baseDispObj;
}

// .text:0x000E6798 size:0x5C mapped:0x8072582C
// Show the bones of the targets that were hit.
void fn_3_E6798(StaC6Obj* o) {
    GameActor* actor = o->actorObj->actor;
    s32 i;
    for (i = 0; i < 7; i++) {
        if (lbl_3_data_196B4.hit[i] != 0) {
            GameBone* b = actor->boneArray[i];
            b->dispObj = b->baseDispObj;
        } else {
            GameBone* b = actor->boneArray[i];
            b->dispObj = NULL;
        }
    }
}

// .text:0x000E67F4 size:0xB4 mapped:0x80725888
// Reset the targets.
void fn_3_E67F4(void) {
    u32 i;
    GameActor* actor;
    ActorObject* obj;
    ActorObjectTable* t;

    for (i = 0; i < 7; i++) {
        lbl_3_data_196B4.hit[i] = 0;
        t = lbl_8036E548.slots6C;
        actor = t->objects[i + 16].actor;
        obj = &t->objects[i + 16];
        obj->time = 20.0f;
        obj->setTime = 1;
        fn_800B4CA0(actor, lbl_8036E548.slots6C->objects[i + 16].time);
        AnimateActorBones(actor);
    }
}

// .text:0x000E68A8 size:0xE4 mapped:0x8072593C
void fn_3_E68A8(StaC6Obj* obj) {
    StaC6Obj* o = (StaC6Obj*)(u8*)obj; // the copy (not the cast) is needed to match
    GameActor* actor = o->subObj->actor;
    f32 t = fn_800B4C40(o->actorObj->actor) - o->actorObj->unk54;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (o->subObj != NULL) {
        memcpy(&o->subObj->worldControl, o, sizeof(GameControl));
        fn_800B4CA0(actor, t);
        fn_800BDA24(o->subObj);
        o->subObj->actor->flags = fn_800B3C04(0, o->subObj->actor, CUR_VIEW());
        fn_800BDA94(o->subObj, CUR_CAMERA_VIEW());
    }
}

// .text:0x000E698C size:0xBC mapped:0x80725A20
void fn_3_E698C(StaC6Obj* o) {
    GameActor* actor;
    f32 t;
    u8 idx;
    GameActor* tmp;

    actor = tmp = o->actorObj->actor;
    t = fn_800B4C40(tmp);
    idx = o->kind - 16;
    if (lbl_3_data_196B4.hit[idx] == 0) {
        fn_800B4CA0(actor, 0.0f);
        AnimateActorBones(actor);
    }
    if (lbl_3_data_196B4.hit[idx] != 0 && t <= 60.0f) {
        AnimateActorBones(actor);
    }
}

// .text:0x000E6A48 size:0x348 mapped:0x80725ADC
void fn_3_E6A48(StaC6Obj* o) {
    return;
}

// .text:0x000E6D90 size:0x5C0 mapped:0x80725E24
void fn_3_E6D90(StaC6Obj* o) {
    return;
}

// .text:0x000E7350 size:0x14 mapped:0x807263E4
void fn_3_E7350(void) {
    lbl_3_data_1963F = lbl_3_data_19640;
}

// .text:0x000E7364 size:0x24 mapped:0x807263F8
void fn_3_E7364(s32 i) {
    // objs[i].index, through a byte pointer to match (lbzx)
    lbl_3_data_19640 = ((u8*)lbl_3_common_bss_350E4.objs + i * sizeof(StaC6Obj))[0xC0];
}

// .text:0x000E7388 size:0x9C mapped:0x8072641C
void fn_3_E7388(s32 unused, E7388Pair* out) {
    StaC6Obj* e;
    E7388Pair* p = out;
    s32 i;
    e = &lbl_3_common_bss_350E4.objs[lbl_3_common_bss_350E4.count - 1];
    i = lbl_3_common_bss_350E4.count - 1;
    do {
        if (!e->visible) {
            p->i = i;
            p++;
        }
        e--;
    } while (i-- != 0);
    e = &lbl_3_common_bss_350E4.objs[lbl_3_common_bss_350E4.count - 1];
    i = lbl_3_common_bss_350E4.count - 1;
    p = out + lbl_3_common_bss_350E4.count;
    do {
        if (e->visible) {
            p--;
            p->i = i;
            p->f = 1.0f;
        }
        e--;
    } while (i-- != 0);
}

// .text:0x000E7424 size:0xF8 mapped:0x807264B8
void fn_3_E7424(void) {
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 0) {
        lbl_3_bss_AE88[0]++;
        lbl_3_bss_AE80[0] = g_Minigame._1914 != 0;
        lbl_3_bss_AE80[1] = g_Minigame._1915 != 0;
        lbl_3_bss_AE80[2] = g_Minigame._1916 != 0;
        lbl_3_bss_AE80[3] = g_Minigame._1917 != 0;
        lbl_3_data_1963F = -1;
        lbl_3_data_19640 = -1;
    }
    lbl_3_bss_AE7C = lbl_3_bss_AE7B;
    lbl_3_bss_AE7B = g_Minigame.toyFieldBallStateResult;
    lbl_3_bss_AE84 += lbl_80366158[0x28] == 0;
    if (lbl_3_bss_AE7C != lbl_3_bss_AE7B) {
        lbl_3_bss_AE84 = 0;
    }
    lbl_3_bss_AE51 = 0;
}

// .text:0x000E751C size:0x120 mapped:0x807265B0
// Shadow matrix of object idx; returns its shadow.
void* fn_3_E751C(s32 idx, Mtx m) {
    Control c;
    StaC6Obj* o;
    c.type = 0;
    o = &lbl_3_common_bss_350E4.objs[idx];
    if (o->kind <= 7) {
        CTRLSetTranslation(&c, lbl_3_bss_AEB4[0][idx].pos.x, -0.04f, lbl_3_bss_AEB4[0][idx].pos.z);
        CTRLSetRotation(&c, 0.0f, lbl_3_bss_AEB4[0][idx].rotY, 0.0f);
    } else {
        CTRLSetTranslation(&c, lbl_3_data_19644[o->slot].x, -0.04f, lbl_3_data_19644[o->slot].z);
        CTRLSetRotation(&c, 0.0f, lbl_3_data_19698[o->slot], 0.0f);
    }
    CTRLBuildMatrix(&c, m);
    return o->shadow;
}

// .text:0x000E763C size:0x3F0 mapped:0x807266D0
void fn_3_E763C(void) {
    return;
}

// .text:0x000E7A2C size:0xF4 mapped:0x80726AC0
// Set the callbacks for the object's kind.
void fn_3_E7A2C(StaC6Obj* o) {
    o->update = NULL;
    o->onHit = NULL;
    o->preDraw = NULL;
    o->postDraw = NULL;
    switch (o->kind) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        o->onHit = fn_3_E7364;
        o->preDraw = fn_3_E6D90;
        lbl_3_bss_AEAC++;
        break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
        o->update = fn_3_E698C;
        o->preDraw = fn_3_E68A8;
        break;
    case 23:
        o->preDraw = fn_3_E6798;
        o->postDraw = fn_3_E671C;
        break;
    case 24:
        o->preDraw = fn_3_E6684;
        o->postDraw = fn_3_E6638;
        break;
    case 26:
        o->update = fn_3_E59B4;
        break;
    case 25:
        o->update = fn_3_E5A1C;
        break;
    }
}

// .text:0x000E7B20 size:0xFA8 mapped:0x80726BB4
u8 fn_3_E7B20(void** files, u32* idx) {
    return 0;
}

// .text:0x000E8AC8 size:0x5C mapped:0x80727B5C
s32 fn_3_E8AC8(void) {
    if (g_d_GameSettings.StadiumID != 6) {
        return 0;
    }
    return fn_3_E7B20(lbl_3_common_bss_350E4.files, lbl_3_common_bss_350E4.fileIdx) != 0;
}

// .text:0x000E8B24 size:0x5F8 mapped:0x80727BB8
void fn_3_E8B24(void** files) {
    return;
}
