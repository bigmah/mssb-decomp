#include "game/sta_c6.h"
#define REP_HEADER_FN repHeader_sta_c6
#include "header_rep_inline.h"
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
// .data lbl_3_data_19018..19770: separate objects that the code reaches through one pooled base.
// overlay colours picked by fn_3_E6410 / fn_3_E64A8
static u8 lbl_3_data_19018[3][4] = {{190, 0, 0, 255}, {200, 118, 0, 255}, {0, 160, 0, 255}};
static StaC6Data lbl_3_data_19024 = {
    {
        {{5, 72, 0, 255}, {13, 180, 0, 255}, {18, 250, 0, 255}},
        {{5, 72, 0, 255}, {13, 180, 0, 255}, {18, 250, 0, 255}},
        {{88, 88, 88, 255}, {200, 200, 200, 200}, {255, 255, 255, 255}},
        {{8, 32, 108, 255}, {12, 56, 200, 255}, {15, 71, 255, 255}},
        {{94, 0, 0, 255}, {220, 0, 0, 255}, {255, 25, 25, 255}},
        {{94, 27, 0, 255}, {220, 62, 0, 255}, {255, 76, 5, 255}},
        {{90, 59, 0, 255}, {220, 145, 0, 255}, {255, 177, 25, 255}},
        {{70, 69, 0, 255}, {210, 208, 0, 255}, {255, 252, 25, 255}},
    },
    {{88, 88, 88, 255}, {200, 200, 200, 255}, {255, 255, 255, 255}},
    {
        {
            {{17.6f, 0.11f, 36.0f}, 40.0f, 4, 1, 1, 4},
            {{0.0f, 0.11f, 52.4f}, 0.0f, 4, 1, 1, 4},
            {{-17.6f, 0.11f, 36.0f}, -40.0f, 4, 1, 1, 4},
            {{34.6f, 0.11f, 53.0f}, 40.0f, 2, 1, 1, 2},
            {{19.4f, 0.11f, 70.0f}, 25.0f, 0, 1, 1, 0},
            {{0.0f, 0.11f, 76.2f}, 0.0f, 5, 1, 1, 5},
            {{-19.4f, 0.11f, 70.0f}, -25.0f, 0, 1, 1, 0},
            {{-34.6f, 0.11f, 53.0f}, -40.0f, 2, 1, 1, 2},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 27, 0, 255, 27},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
        },
        {
            {{17.6f, 0.11f, 36.0f}, 40.0f, 2, 1, 1, 2},
            {{0.0f, 0.11f, 52.4f}, 0.0f, 2, 1, 1, 2},
            {{-17.6f, 0.11f, 36.0f}, -40.0f, 2, 1, 1, 2},
            {{34.6f, 0.11f, 53.0f}, 40.0f, 5, 1, 1, 5},
            {{19.4f, 0.11f, 70.0f}, 25.0f, 0, 1, 1, 0},
            {{0.0f, 0.11f, 76.2f}, 0.0f, 5, 1, 1, 5},
            {{-19.4f, 0.11f, 70.0f}, -25.0f, 0, 1, 1, 0},
            {{-34.6f, 0.11f, 53.0f}, -40.0f, 5, 1, 1, 5},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 27, 0, 255, 27},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
        },
        {
            {{17.6f, 0.11f, 36.0f}, 40.0f, 4, 1, 1, 4},
            {{0.0f, 0.11f, 52.4f}, 0.0f, 4, 1, 1, 4},
            {{-17.6f, 0.11f, 36.0f}, -40.0f, 4, 1, 1, 4},
            {{34.6f, 0.11f, 53.0f}, 40.0f, 2, 1, 1, 2},
            {{19.4f, 0.11f, 70.0f}, 25.0f, 0, 1, 1, 0},
            {{0.0f, 0.11f, 76.2f}, 0.0f, 5, 1, 1, 5},
            {{-19.4f, 0.11f, 70.0f}, -25.0f, 0, 1, 1, 0},
            {{-34.6f, 0.11f, 53.0f}, -40.0f, 2, 1, 1, 2},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 27, 0, 255, 27},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
        },
        {
            {{34.6f, 0.11f, 53.0f}, 40.0f, 7, 1, 1, 7},
            {{17.6f, 0.11f, 36.0f}, 40.0f, 7, 1, 1, 7},
            {{19.4f, 0.11f, 70.0f}, 25.0f, 7, 1, 1, 7},
            {{0.0f, 0.11f, 52.4f}, 0.0f, 7, 1, 1, 7},
            {{0.0f, 0.11f, 76.2f}, 0.0f, 7, 1, 1, 7},
            {{-19.4f, 0.11f, 70.0f}, -25.0f, 7, 1, 1, 7},
            {{-17.6f, 0.11f, 36.0f}, -40.0f, 7, 1, 1, 7},
            {{-34.6f, 0.11f, 53.0f}, -40.0f, 7, 1, 1, 7},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 27, 0, 255, 27},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
        },
    },
    {
        {
            {14, 1, 1, 14},
            {13, 1, 1, 13},
            {10, 1, 1, 10},
            {15, 1, 1, 15},
            {10, 1, 1, 10},
            {13, 1, 1, 13},
            {14, 1, 1, 14},
            {27, 0, 255, 27},
        },
        {
            {10, 1, 1, 10},
            {14, 1, 1, 14},
            {10, 1, 1, 10},
            {15, 1, 1, 15},
            {10, 1, 1, 10},
            {14, 1, 1, 14},
            {10, 1, 1, 10},
            {27, 0, 255, 27},
        },
        {
            {14, 1, 1, 14},
            {13, 1, 1, 13},
            {10, 1, 1, 10},
            {15, 1, 1, 15},
            {10, 1, 1, 10},
            {13, 1, 1, 13},
            {14, 1, 1, 14},
            {27, 0, 255, 27},
        },
        {
            {15, 1, 1, 15},
            {15, 1, 1, 15},
            {15, 1, 1, 15},
            {15, 1, 1, 15},
            {15, 1, 1, 15},
            {15, 1, 1, 15},
            {15, 1, 1, 15},
            {27, 0, 255, 27},
        },
    },
};
static u8 lbl_3_data_19610[0x2F] = { // file kinds for fn_3_B9D68 (47 files)
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 4, 4, 4, 4, 4, 4, 4, 2, 2, 4, 2, 2, 4, 4, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
};
static s8 lbl_3_data_1963F = -1; // object index the ball touched
static s8 lbl_3_data_19640 = -1;
s8 lbl_3_data_19641 = -1; // unused
static Vec lbl_3_data_19644[7] = { // wall panel positions
    {48.443f, 0.1f, 66.104f},
    {35.956f, 0.1f, 80.987f},
    {19.132f, 0.1f, 90.701f},
    {0.0f, 0.1f, 94.074f},
    {-19.132f, 0.1f, 90.701f},
    {-35.956f, 0.1f, 80.987f},
    {-48.443f, 0.1f, 66.104f},
};
// wall panel rotations
static f32 lbl_3_data_19698[7] = {60.0f, 40.0f, 20.0f, 0.0f, -20.0f, -40.0f, -60.0f};
// Targets (objects 16-22): hit flags (read by auto_00_000E587C_text), placement, panel kind results.
u8 lbl_3_data_196B4[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static Vec lbl_3_data_196BC[7] = {
    {-54.758f, 0.0f, 69.75f},
    {-40.643f, 0.0f, 86.573f},
    {-21.625f, 0.0f, 97.552f},
    {0.0f, 0.0f, 101.366f},
    {21.625f, 0.0f, 97.552f},
    {40.643f, 0.0f, 86.573f},
    {54.758f, 0.0f, 69.75f},
};
static f32 lbl_3_data_19710[7] = {-60.0f, -40.0f, -20.0f, 0.0f, 20.0f, 40.0f, 60.0f};
static u32 lbl_3_data_1972C[16] = {10, 9, 11, 2, 3, 4, 5, 6, 10, 9, 11, 2, 3, 4, 5, 6}; // toy field result that lights panel kind n
static u8 lbl_3_data_1976C = 1; // nonzero: show the lit overlay (bone 2)
extern u8 lbl_80366158[];
#ifdef TARGET_PC // the struct holds pointers: reach the byte through it (port/game/views.c)
u8* port_80366158_byte(u32 gcOffset);
#define LBL_80366158_U8(off) (*port_80366158_byte(off))
#else
#define LBL_80366158_U8(off) lbl_80366158[off]
#endif
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

// Place the object's bones at its spot. Uses the caller's locals c, m, bone, i.
#define STA_PLACE(o)                                                                                                                        \
    do {                                                                                                                                    \
        PSMTXIdentity(m);                                                                                                                   \
        c.base.type = 0;                                                                                                                         \
        if (o->kind < 8) {                                                                                                                  \
            CTRLSetTranslation(&c.base, lbl_3_bss_AEB4[0][o->index].pos.x, lbl_3_bss_AEB4[0][o->index].pos.y, lbl_3_bss_AEB4[0][o->index].pos.z);\
            CTRLSetRotation(&c.base, 0.0f, lbl_3_bss_AEB4[0][o->index].rotY, 0.0f);                                                              \
        } else {                                                                                                                            \
            CTRLSetTranslation(&c.base, lbl_3_data_19644[o->slot].x, lbl_3_data_19644[o->slot].y, lbl_3_data_19644[o->slot].z);                  \
            CTRLSetRotation(&c.base, 0.0f, lbl_3_data_19698[o->slot], 0.0f);                                                                     \
        }                                                                                                                                   \
        CTRLBuildMatrix(&c.base, m);                                                                                                             \
        for (i = 0; i < o->actorObj->actor->totalBones; i++) {                                                                              \
            bone = o->actorObj->actor->boneArray[i];                                                                                        \
            CTRLBuildMatrix(&bone->orientCtrl.base, bone->forwardMtx);                                                                      \
            PSMTXConcat(m, bone->forwardMtx, bone->forwardMtx);                                                                             \
            PSMTXCopy(bone->forwardMtx, bone->dispObj->worldMatrix);                                                                        \
        }                                                                                                                                   \
        if (o->subObj != NULL) {                                                                                                            \
            for (i = 0; i < o->subObj->actor->totalBones; i++) {                                                                            \
                bone = o->subObj->actor->boneArray[i];                                                                                      \
                CTRLBuildMatrix(&bone->orientCtrl.base, bone->forwardMtx);                                                                  \
                PSMTXConcat(m, bone->forwardMtx, bone->forwardMtx);                                                                         \
                if (bone->dispObj != NULL) {                                                                                                \
                    PSMTXCopy(bone->forwardMtx, bone->dispObj->worldMatrix);                                                                \
                }                                                                                                                           \
            }                                                                                                                               \
            o->subObj->actor->flags = fn_800B3C04(0, o->subObj->actor, CUR_VIEW());                                                         \
        }                                                                                                                                   \
        o->actorObj->actor->flags = fn_800B3C04(0, o->actorObj->actor, CUR_VIEW());                                                         \
    } while (0)

// .text:0x000E5A84 size:0x238 mapped:0x80724B18
// Place the object's bones at its spot.
void fn_3_E5A84(StaC6Obj* o) {
    GameControl c;
    Mtx m;
    GameBone* bone;
    s32 i;
    STA_PLACE(o);
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
    dst = PTR32_GET(char, cd->colorArray);
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
    dst = PTR32_GET(char, cd->colorArray);
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
// Back to the idle colours (also expanded inline in fn_3_E6D90 and fn_3_E7B20).
#define STA_RESET_COLOR(o)                                \
    do {                                                  \
        memcpy((o)->color, (o)->colorIdle, 4);            \
        (o)->bodyColor = lbl_3_data_19024.bodyColors[1];  \
        (o)->lit = 0;                                     \
    } while (0)

void fn_3_E6528(StaC6Obj* o) {
    STA_RESET_COLOR(o);
}

// Pick the overlay texture for the panel kind. Uses the caller's locals sub, disp, tex.
#define STA_PICK_TEXTURE(o)                                              \
    do {                                                                 \
        sub = o->subObj;                                                 \
        if (sub != NULL) {                                               \
            disp = BONE(sub, 1)->dispObj;                                \
            tex = disp->textureData;                                     \
            if (PTR32_GET(DisplayStateList, disp->displayData->displayStateList)[2].id != 3) { \
                OSPanic(lbl_3_rodata_2BB0, 0x713, lbl_3_rodata_2BBC);    \
            }                                                            \
            if (o->kind == 2) {                                          \
                PTR32_GET(DOTexBank, tex->texturePalette)->tex[4].texIndex = 1; \
            } else if (o->kind == 10) {                                  \
                PTR32_GET(DOTexBank, tex->texturePalette)->tex[4].texIndex = 0; \
            } else {                                                     \
                PTR32_GET(DOTexBank, tex->texturePalette)->tex[4].texIndex = 4; \
            }                                                            \
        }                                                                \
    } while (0)

// .text:0x000E6578 size:0xC0 mapped:0x8072560C
// Pick the overlay texture for the panel kind.
void fn_3_E6578(StaC6Obj* o) {
    ActorObject* sub;
    struct DODisplayObj* disp;
    TextureData* tex;

    STA_PICK_TEXTURE(o);
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
        if (lbl_3_data_196B4[i] != 0) {
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
// (also expanded inline in fn_3_E7B20)
#define STA_RESET_TARGETS()                                                      \
    do {                                                                         \
        u32 i_;                                                                  \
        GameActor* actor_;                                                       \
        ActorObject* obj_;                                                       \
        ActorObjectTable* t_;                                                    \
        for (i_ = 0; i_ < 7; i_++) {                                             \
            lbl_3_data_196B4[i_] = 0;                                        \
            t_ = lbl_8036E548.slots6C;                                           \
            actor_ = t_->objects[i_ + 16].actor;                                 \
            obj_ = &t_->objects[i_ + 16];                                        \
            obj_->time = 20.0f;                                                  \
            obj_->setTime = 1;                                                   \
            fn_800B4CA0(actor_, lbl_8036E548.slots6C->objects[i_ + 16].time);    \
            AnimateActorBones(actor_);                                           \
        }                                                                        \
    } while (0)

void fn_3_E67F4(void) {
    STA_RESET_TARGETS();
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
    if (lbl_3_data_196B4[idx] == 0) {
        fn_800B4CA0(actor, 0.0f);
        AnimateActorBones(actor);
    }
    if (lbl_3_data_196B4[idx] != 0 && t <= 60.0f) {
        AnimateActorBones(actor);
    }
}

// .text:0x000E6A48 size:0x348 mapped:0x80725ADC
// NONMATCHING 99.9%: only the pooled .data base `addi r31` is scheduled one instruction earlier than in
// the original (before the PSMTXIdentity argument)
#if NONMATCHING
#pragma dont_inline off
#pragma inline_max_size(100000)
static inline void E5A84_inl(StaC6Obj* o) {
    Mtx m;
    GameControl c;
    GameBone* bone;
    s32 i;
    STA_PLACE(o);
}
static inline void E6578_inl(StaC6Obj* o) {
    ActorObject* sub;
    struct DODisplayObj* disp;
    TextureData* tex;

    STA_PICK_TEXTURE(o);
}
// Draw a panel: place it, pick its overlay texture and colours, and record a wall panel hit.
void fn_3_E6A48(StaC6Obj* o) {
    E5A84_inl(o);
    E6578_inl(o);

    if (o->subObj != NULL) {
        fn_3_E5FEC(o);
        fn_800BDA94(o->subObj, CUR_CAMERA_VIEW());
    }
    if (g_GameLogic.gameStatus == 2 && g_Minigame.toyFieldBallStateResult != 0) {
        if (g_Minigame.toyFieldBallStateResult == lbl_3_data_1972C[o->kind] && lbl_3_data_1963F == o->index && o->kind >= 8) {
            lbl_3_data_196B4[o->flagIdx] = 1;
        }
    }
}
#endif

// .text:0x000E6D90 size:0x5C0 mapped:0x80725E24
// Play crowd sound n (see playCrowdSound in rep_2998.c).
static inline void playCrowdSound(s32 n) {
    s32 stadium;
    u8 vol;
    SND_VOICEID voice;

    stadium = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[n].vol;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].vol;
    }
    voice = sndFXStartEx(lbl_3_data_81DC[stadium] + n, vol, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[n].ctrl;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].ctrl;
    }
    sndFXCtrl(voice, 0x5B, vol);
}

// NONMATCHING 99.8%: only the pooled .data base `addi r31` is scheduled one instruction earlier (as fn_3_E6A48)
#if NONMATCHING
// Panel pre-draw: place it, light it when the ball touches it, and colour it.
void fn_3_E6D90(StaC6Obj* o) {
    E5A84_inl(o);

    if (g_GameLogic.gameStatus == 0 || g_GameLogic.gameStatus == 1) {
        STA_RESET_COLOR(o);
        if (lbl_3_bss_AE52 != 0) {
            lbl_3_bss_AE52 = 0;
        }
    }
    if (g_GameLogic.gameStatus == 2) {
        if (g_Ball.AtBat_ContactResult != 0) {
            if (lbl_3_data_1963F == o->index && g_Minigame.maybeTFCollisionResultState == lbl_3_data_1972C[o->kind]) {
                memcpy(o->color, o->colorHit, 4);
                o->bodyColor = lbl_3_data_19024.bodyColors[2];
                if (o->lit == 0) {
                    playCrowdSound(0x14);
                }
                o->lit = 1;
                if (g_Minigame.toyFieldBallStateResult != 0 && g_Minigame.toyFieldBallStateResult == lbl_3_data_1972C[o->kind] &&
                    o->kind >= 8) {
                    if (lbl_3_data_196B4[o->flagIdx] == 0) {
                        playCrowdSound(0x17);
                    }
                    lbl_3_data_196B4[o->flagIdx] = 1;
                }
            } else {
                memcpy(o->color, o->colorMiss, 4);
                o->bodyColor = lbl_3_data_19024.bodyColors[0];
                o->lit = 0;
            }
        }
    } else {
        o->_A0 = 0;
    }
    if (lbl_3_bss_AE52 != 0) {
        memcpy(o->color, o->colorHit, 4);
        o->bodyColor = lbl_3_data_19024.bodyColors[2];
        o->lit = 1;
    }
    fn_3_E5FEC(o);
    E6578_inl(o);

    if (o->subObj != NULL) {
        fn_800BDA94(o->subObj, CUR_CAMERA_VIEW());
        BONE(o->subObj, 2)->dispObj = BONE(o->subObj, 2)->baseDispObj;
    }
}
#endif

// .text:0x000E7350 size:0x14 mapped:0x807263E4
void fn_3_E7350(void) {
    lbl_3_data_1963F = lbl_3_data_19640;
}

// .text:0x000E7364 size:0x24 mapped:0x807263F8
void fn_3_E7364(s32 i, s32 hitType, struct _CollisionStruct* hit) {
    // objs[i].index, through a byte pointer to match (lbzx)
    lbl_3_data_19640 = ((u8*)lbl_3_common_bss_350E4.objs + i * sizeof(StaC6Obj))[0xC0];
}

// .text:0x000E7388 size:0x9C mapped:0x8072641C
void fn_3_E7388(MtxPtr unused, E7388Pair* out) {
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
        lbl_3_bss_AE80[0] = g_Minigame._1914[0] != 0;
        lbl_3_bss_AE80[1] = g_Minigame._1914[1] != 0;
        lbl_3_bss_AE80[2] = g_Minigame._1914[2] != 0;
        lbl_3_bss_AE80[3] = g_Minigame._1914[3] != 0;
        lbl_3_data_1963F = -1;
        lbl_3_data_19640 = -1;
    }
    lbl_3_bss_AE7C = lbl_3_bss_AE7B;
    lbl_3_bss_AE7B = g_Minigame.toyFieldBallStateResult;
    lbl_3_bss_AE84 += LBL_80366158_U8(0x28) == 0;
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
    GameControl c;
    Mtx m;
    s32 group;
    s32 j;
    s32 numGroups;
    u32 off;
    StaC6Obj* o;
    StaC6List* list = &lbl_3_common_bss_350E4;

    group = (list->count << 1) + (list->count << 2) + (list->count << 2) + list->count * 0x18;
    if (list->groupBounds == NULL) {
        Vec* b = _OSAllocFromHeap(4, group);
        list->groupBounds = b;
        lbl_3_common_bss_350E4.groupCount = (u32*)(b + list->count * 2);
        lbl_3_common_bss_350E4.groupObjs = (s32*)(lbl_3_common_bss_350E4.groupCount + list->count);
        lbl_3_common_bss_350E4.groupStart = (u16*)(lbl_3_common_bss_350E4.groupObjs + list->count);
    }
    memset(list->groupBounds, 0, group);
    numGroups = 0;
    for (group = 0; group < 10; group++) {
        off = (u16)(lbl_3_common_bss_350E4.groupStart[numGroups - 1] + lbl_3_common_bss_350E4.groupCount[numGroups - 1]);
        lbl_3_common_bss_350E4.groupStart[numGroups] = off;
        fn_3_B8574();
        if (lbl_803C77B8._00 & 0x800 && group != 0) {
            continue;
        }
        if (lbl_803C77B8._00 & 0x400 && j != 0) {
            continue;
        }
        for (j = 0; j < 15; j++) {
            if (group == lbl_3_bss_AEB4[0][j].group && lbl_3_common_bss_350E4.objs[j].hasShadow && lbl_3_common_bss_350E4.objs[j].shadow != NULL) {
                lbl_3_common_bss_350E4.groupObjs[off] = j;
                off++;
                lbl_3_common_bss_350E4.groupCount[numGroups]++;
                c.base.type = 0;
                o = &lbl_3_common_bss_350E4.objs[j];
                CTRLSetTranslation(&c.base, lbl_3_bss_AEB4[0][j].pos.x, lbl_3_bss_AEB4[0][j].pos.y, lbl_3_bss_AEB4[0][j].pos.z);
                CTRLSetRotation(&c.base, 0.0f, lbl_3_bss_AEB4[0][j].rotY, 0.0f);
                CTRLBuildMatrix(&c.base, m);
                fn_3_B8464(m, o->shadow);
            }
        }
        if (lbl_3_common_bss_350E4.groupCount[numGroups] != 0) {
            fn_3_B8414(&list->groupBounds[numGroups * 2], &list->groupBounds[numGroups * 2 + 1]);
            numGroups++;
        }
    }
    for (group = 0; group < 10; group++) {
        off = (u16)(lbl_3_common_bss_350E4.groupStart[numGroups - 1] + lbl_3_common_bss_350E4.groupCount[numGroups - 1]);
        lbl_3_common_bss_350E4.groupStart[numGroups] = off;
        fn_3_B8574();
        for (j = 0; j < 7; j++) {
            if (group == lbl_3_bss_AEB4[0][j].group && lbl_3_common_bss_350E4.objs[j].hasShadow && lbl_3_common_bss_350E4.objs[j].shadow != NULL) {
                lbl_3_common_bss_350E4.groupObjs[off] = j + lbl_3_bss_AEAD;
                off++;
                lbl_3_common_bss_350E4.groupCount[numGroups]++;
                o = &lbl_3_common_bss_350E4.objs[j + lbl_3_bss_AEAD];
                c.base.type = 0;
                CTRLSetTranslation(&c.base, lbl_3_data_19644[j].x, lbl_3_data_19644[j].y, lbl_3_data_19644[j].z);
                CTRLSetRotation(&c.base, 0.0f, lbl_3_data_19698[j], 0.0f);
                CTRLBuildMatrix(&c.base, m);
                fn_3_B8464(m, o->shadow);
            }
        }
        if (lbl_3_common_bss_350E4.groupCount[numGroups] != 0) {
            fn_3_B8414(&list->groupBounds[numGroups * 2], &list->groupBounds[numGroups * 2 + 1]);
            numGroups++;
        }
        lbl_3_common_bss_350E4.numGroups = numGroups;
    }
}

// .text:0x000E7A2C size:0xF4 mapped:0x80726AC0
// Set the callbacks for the object's kind (also expanded inline in fn_3_E7B20).
#define STA_SET_CALLBACKS(o)              \
    do {                                  \
        (o)->update = NULL;               \
        (o)->onHit = NULL;                \
        (o)->preDraw = NULL;              \
        (o)->postDraw = NULL;             \
        switch ((o)->kind) {              \
        case 0:                           \
        case 1:                           \
        case 2:                           \
        case 3:                           \
        case 4:                           \
        case 5:                           \
        case 6:                           \
        case 7:                           \
        case 8:                           \
        case 9:                           \
        case 10:                          \
        case 11:                          \
        case 12:                          \
        case 13:                          \
        case 14:                          \
        case 15:                          \
            (o)->onHit = fn_3_E7364;      \
            (o)->preDraw = fn_3_E6D90;    \
            lbl_3_bss_AEAC++;             \
            break;                        \
        case 16:                          \
        case 17:                          \
        case 18:                          \
        case 19:                          \
        case 20:                          \
        case 21:                          \
        case 22:                          \
            (o)->update = fn_3_E698C;     \
            (o)->preDraw = fn_3_E68A8;    \
            break;                        \
        case 23:                          \
            (o)->preDraw = fn_3_E6798;    \
            (o)->postDraw = fn_3_E671C;   \
            break;                        \
        case 24:                          \
            (o)->preDraw = fn_3_E6684;    \
            (o)->postDraw = fn_3_E6638;   \
            break;                        \
        case 26:                          \
            (o)->update = fn_3_E59B4;     \
            break;                        \
        case 25:                          \
            (o)->update = fn_3_E5A1C;     \
            break;                        \
        }                                 \
    } while (0)

void fn_3_E7A2C(StaC6Obj* o) {
    STA_SET_CALLBACKS(o);
}

// .text:0x000E7B20 size:0xFA8 mapped:0x80726BB4
// NONMATCHING 93%: keeps two object pointers in the original; register allocation and frame size
// differ. fn_3_E7A2C, fn_3_E6528 and fn_3_E67F4 are inlined (macros here).
#if NONMATCHING
// Create the stadium objects for the current number of players: field panels, wall panels,
// the 7 targets and 4 scenery objects; the rest of the list is cleared.
u8 fn_3_E7B20(void** files, u32* idx) {
    StaC6Obj* o;
    u32 i;
    u32 kind;
    u8 n = 0;
    u8 done = 0;

    if (files == NULL || idx == NULL) {
        return 0;
    }
    lbl_3_bss_AEAC = 0;
    memset(&lbl_3_bss_AE88[1], 0xFF, 8 * sizeof(s32));
    memset(lbl_3_common_bss_350E4.objs, 0, lbl_3_common_bss_350E4.count * sizeof(StaC6Obj));
    o = lbl_3_common_bss_350E4.objs;
    switch (g_Minigame.miniGameNumberOfParticipants) {
    case 2:
        lbl_3_bss_AEB4[0] = lbl_3_data_19024.spots[0];
        lbl_3_bss_AEB0 = lbl_3_data_19024.pads[0];
        break;
    case 3:
        lbl_3_bss_AEB4[0] = lbl_3_data_19024.spots[1];
        lbl_3_bss_AEB0 = lbl_3_data_19024.pads[1];
        break;
    default:
        lbl_3_bss_AEB4[0] = lbl_3_data_19024.spots[2];
        lbl_3_bss_AEB0 = lbl_3_data_19024.pads[2];
        break;
    }
    lbl_3_bss_AEAE = g_Minigame.miniGameNumberOfParticipants - 2;
    if (g_Minigame._19A6 > 1) {
        lbl_3_bss_AE52 = 1;
        lbl_3_bss_AEB4[0] = lbl_3_data_19024.spots[3];
        lbl_3_bss_AEB0 = lbl_3_data_19024.pads[3];
        lbl_3_bss_AEAE = 3;
    }

    // field panels
    for (i = 0; i < 15; i++) {
        if (lbl_3_bss_AEB4[0][i].kind == 27) {
            done = 1;
        }
        if (done) {
            for (; i < 16; i++) {
                memset(&lbl_3_bss_AEB4[0][i], 0, sizeof(StaC6Spot));
                lbl_3_bss_AEB4[0][i].kind = 27;
                lbl_3_bss_AEB4[0][i].group = 10;
            }
            break;
        }
        o->index = i;
        o->kind = lbl_3_bss_AEB4[0][i].kind;
        o->subObj = &lbl_8036E548.slots6C->objects[23];
        o->actorObj = &lbl_8036E548.slots6C->objects[o->kind];
        o->shadow = STADIUM_FILE(files, idx[o->kind + 31]);
        o->visible = 1;
        o->hasShadow = 1;
        o->ctrl.base.type = 0;
        CTRLSetTranslation(&o->ctrl.base, 0.0f, 0.0f, 0.0f);
        o->colorMiss = lbl_3_data_19024.kindColors[o->kind][0];
        o->colorIdle = lbl_3_data_19024.kindColors[o->kind][1];
        o->colorHit = lbl_3_data_19024.kindColors[o->kind][2];
        o->bodyColor = lbl_3_data_19024.bodyColors[1];
        STA_RESET_COLOR(o);
        o->bit5 = 0;
        o->_92 = 0xFF;
        o->_8C = 0;
        o->_94 = 0;
        o->_96 = -1;
        o->_98 = 1;
        STA_SET_CALLBACKS(o);
        o++;
        n++;
    }
    lbl_3_bss_AEAD = n;

    // wall panels
    done = 0;
    for (i = 0; i < 7; i++) {
        if (lbl_3_bss_AEB0[i].kind == 27) {
            done = 1;
        }
        if (done) {
            for (; i < 8; i++) {
                memset(&lbl_3_bss_AEB0[i], 0, sizeof(StaC6Pad));
                lbl_3_bss_AEB0[i].kind = 27;
                lbl_3_bss_AEB0[i].group = 10;
            }
            break;
        }
        o->index = n;
        o->kind = lbl_3_bss_AEB0[i].kind;
        o->slot = i;
        o->flagIdx = 6 - i;
        o->subObj = &lbl_8036E548.slots6C->objects[24];
        o->actorObj = &lbl_8036E548.slots6C->objects[o->kind];
        o->shadow = STADIUM_FILE(files, idx[o->kind + 31]);
        o->visible = 1;
        o->hasShadow = 1;
        o->ctrl.base.type = 0;
        CTRLSetTranslation(&o->ctrl.base, 0.0f, 0.0f, 0.0f);
        o->colorMiss = lbl_3_data_19024.kindColors[o->kind - 8][0];
        o->colorIdle = lbl_3_data_19024.kindColors[o->kind - 8][1];
        o->colorHit = lbl_3_data_19024.kindColors[o->kind - 8][2];
        o->bodyColor = lbl_3_data_19024.bodyColors[1];
        STA_RESET_COLOR(o);
        o->bit5 = 0;
        o->_92 = 0xFF;
        o->_8C = 0;
        o->_94 = 0;
        o->_96 = -1;
        o->_98 = 1;
        STA_SET_CALLBACKS(o);
        o++;
        n++;
    }

    // targets
    for (kind = 16, i = 0; kind < 23; kind++, i++) {
        o->index = n;
        o->kind = kind;
        o->subObj = &lbl_8036E548.slots6C->objects[25];
        o->actorObj = &lbl_8036E548.slots6C->objects[i + 16];
        o->shadow = NULL;
        o->visible = 1;
        o->hasShadow = 1;
        o->ctrl.base.type = 0;
        CTRLSetTranslation(&o->ctrl.base, lbl_3_data_196BC[o->kind - 16].x, lbl_3_data_196BC[o->kind - 16].y,
                           lbl_3_data_196BC[o->kind - 16].z);
        CTRLSetRotation(&o->ctrl.base, 0.0f, lbl_3_data_19710[o->kind - 16], 0.0f);
        o->bit5 = 1;
        o->_92 = 0xFF;
        o->_8C = 0;
        o->_94 = 0;
        o->_96 = -1;
        o->_98 = 1;
        STA_SET_CALLBACKS(o);
        o++;
        n++;
    }

    // scenery: kinds 23, 24, 26, 25 with models 26-29
    o[0].index = n;
    o[0].kind = 23;
    o[0].actorObj = &lbl_8036E548.slots6C->objects[26];
    o[0].shadow = NULL;
    o[0].visible = 1;
    o[0].hasShadow = 0;
    o[0].ctrl.base.type = 0;
    CTRLSetTranslation(&o[0].ctrl.base, 0.0f, 0.0f, 0.0f);
    o[0].bit5 = 0;
    o[0]._92 = 0xFF;
    o[0]._8C = 0;
    o[0]._94 = 0;
    o[0]._96 = -1;
    o[0]._98 = 1;
    STA_SET_CALLBACKS(&o[0]);

    o[1].index = n + 1;
    o[1].kind = 24;
    o[1].actorObj = &lbl_8036E548.slots6C->objects[27];
    o[1].shadow = NULL;
    o[1].visible = 1;
    o[1].hasShadow = 0;
    o[1].ctrl.base.type = 0;
    CTRLSetTranslation(&o[1].ctrl.base, 0.0f, 0.0f, 0.0f);
    o[1].bit5 = 0;
    o[1]._92 = 0xFF;
    o[1]._8C = 0;
    o[1]._94 = 0;
    o[1]._96 = -1;
    o[1]._98 = 1;
    STA_SET_CALLBACKS(&o[1]);

    o[2].index = n + 2;
    o[2].kind = 26;
    o[2].actorObj = &lbl_8036E548.slots6C->objects[28];
    o[2].shadow = NULL;
    o[2].visible = 1;
    o[2].hasShadow = 0;
    o[2].ctrl.base.type = 0;
    CTRLSetTranslation(&o[2].ctrl.base, 0.0f, 0.0f, 0.0f);
    o[2].bit5 = 0;
    o[2]._92 = 0xFF;
    o[2]._8C = 0;
    o[2]._94 = 0;
    o[2]._96 = -1;
    o[2]._98 = 0;
    STA_SET_CALLBACKS(&o[2]);

    o[3].index = n + 3;
    o[3].kind = 25;
    o[3].actorObj = &lbl_8036E548.slots6C->objects[29];
    o[3].shadow = NULL;
    o[3].visible = 1;
    o[3].hasShadow = 0;
    o[3].ctrl.base.type = 0;
    CTRLSetTranslation(&o[3].ctrl.base, 0.0f, 0.0f, 0.0f);
    o[3].bit5 = 0;
    o[3]._92 = 0xFF;
    o[3]._8C = 0;
    o[3]._94 = 0;
    o[3]._96 = -1;
    o[3]._98 = 1;
    STA_SET_CALLBACKS(&o[3]);

    // unused entries
    o += 4;
    for (i = n + 4; i < lbl_3_common_bss_350E4.count; i++) {
        o->kind = 27;
        o->actorObj = NULL;
        o->shadow = NULL;
        o->update = NULL;
        o->onHit = NULL;
        o->visible = 0;
        o->hasShadow = 0;
        o->bit5 = 0;
        o->ctrl.base.type = 0;
        CTRLSetTranslation(&o->ctrl.base, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&o->ctrl.base, 0.0f, 0.0f, 0.0f);
        o->_92 = 0;
        o->_8C = 0;
        o->_94 = 0;
        o->_96 = -1;
        o++;
    }
    fn_3_E763C();
    if (g_GameLogic.gameStatus == 5) {
        STA_RESET_TARGETS();
    }
    return 1;
}
#endif

// .text:0x000E8AC8 size:0x5C mapped:0x80727B5C
s32 fn_3_E8AC8(void) {
    if (g_d_GameSettings.StadiumID != 6) {
        return 0;
    }
    return fn_3_E7B20(lbl_3_common_bss_350E4.files, lbl_3_common_bss_350E4.fileIdx) != 0;
}

// .text:0x000E8B24 size:0x5F8 mapped:0x80727BB8
// Stadium setup: load the models, create the objects and place them (fn_3_E7B20).
void fn_3_E8B24(void** files) {
    StaC6List* list = &lbl_3_common_bss_350E4;
    u32* idx;
    u32 i;
    ActorObject* obj;

    list->draw = fn_3_E7424;
    list->_6C = 0;
    idx = list->fileIdx = _OSAllocFromHeap(4, 0xBC);
    fn_3_B9D68(lbl_3_data_19610, 0x2F, files, idx);
    lbl_8036E548.slots6C = ActorObjectInitTable(30);
    fn_800BDC88(lbl_8036E548.slots6C, 0, 0, STADIUM_FILE(files, idx[1]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 1, 1, STADIUM_FILE(files, idx[2]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 2, 2, STADIUM_FILE(files, idx[3]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 3, 3, STADIUM_FILE(files, idx[4]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 4, 4, STADIUM_FILE(files, idx[5]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 5, 5, STADIUM_FILE(files, idx[6]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 6, 6, STADIUM_FILE(files, idx[7]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 7, 7, STADIUM_FILE(files, idx[8]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 8, 8, STADIUM_FILE(files, idx[9]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 9, 9, STADIUM_FILE(files, idx[10]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 10, 10, STADIUM_FILE(files, idx[11]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 11, 11, STADIUM_FILE(files, idx[12]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 12, 12, STADIUM_FILE(files, idx[13]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 13, 13, STADIUM_FILE(files, idx[14]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 14, 14, STADIUM_FILE(files, idx[15]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 15, 15, STADIUM_FILE(files, idx[16]), NULL, NULL);
    for (i = 0; i < 7; i++) {
        fn_800BDC88(lbl_8036E548.slots6C, i + 16, i + 16, STADIUM_FILE(files, idx[i + 17]), NULL, NULL);
        fn_3_B97DC(&lbl_8036E548.slots6C->objects[i + 16], STADIUM_FILE(files, idx[i + 17] + 2));
    }
    fn_800BDC88(lbl_8036E548.slots6C, 23, 23, STADIUM_FILE(files, idx[24]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 24, 24, STADIUM_FILE(files, idx[25]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 25, 25, STADIUM_FILE(files, idx[26]), NULL, NULL);
    fn_3_B97DC(&lbl_8036E548.slots6C->objects[25], STADIUM_FILE(files, idx[26] + 2));
    fn_800BDC88(lbl_8036E548.slots6C, 26, 26, STADIUM_FILE(files, idx[27]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 27, 27, STADIUM_FILE(files, idx[28]), NULL, NULL);
    fn_800BDC88(lbl_8036E548.slots6C, 28, 28, STADIUM_FILE(files, idx[29]), NULL, NULL);
    fn_3_B97DC(&lbl_8036E548.slots6C->objects[28], STADIUM_FILE(files, idx[29] + 2));
    obj = &lbl_8036E548.slots6C->objects[28];
    obj->time = lbl_3_rodata_2B98;
    obj->setTime = 1;
    fn_800B4CA0(lbl_8036E548.slots6C->objects[28].actor, lbl_8036E548.slots6C->objects[28].time);
    fn_800BDC88(lbl_8036E548.slots6C, 29, 29, STADIUM_FILE(files, idx[30]), NULL, NULL);
    fn_3_B97DC(&lbl_8036E548.slots6C->objects[29], STADIUM_FILE(files, idx[30] + 2));
    obj = &lbl_8036E548.slots6C->objects[29];
    obj->time = lbl_3_rodata_2BA0;
    obj->setTime = 1;
    fn_800B4CA0(lbl_8036E548.slots6C->objects[29].actor, lbl_8036E548.slots6C->objects[29].time);

    lbl_3_common_bss_350E4.numActorObjs = 30;
    for (i = 0; i < lbl_3_common_bss_350E4.numActorObjs; i++) {
        fn_800BD478(&lbl_8036E548.slots6C->objects[i].actor, STADIUM_FILE(files, idx[i + 1]));
    }
    for (i = 0; i < 30; i++) {
        fn_800BD548(&lbl_8036E548.slots6C->objects[i], 4, lbl_3_common_bss_350E4.lights[0], lbl_3_common_bss_350E4.lights[1],
                    lbl_3_common_bss_350E4.lights[2], lbl_3_common_bss_350E4.lights[3]);
    }

    lbl_3_common_bss_350E4.count = 32;
    lbl_3_common_bss_350E4.objs = _OSAllocFromHeap(0x20, lbl_3_common_bss_350E4.count * sizeof(StaC6Obj));
    memset(lbl_3_common_bss_350E4.objs, 0, lbl_3_common_bss_350E4.count * sizeof(StaC6Obj));
    lbl_3_common_bss_350E4.objsBackup = _OSAllocFromHeap(0x20, lbl_3_common_bss_350E4.count * sizeof(StaC6Obj));
    memset(lbl_3_common_bss_350E4.objsBackup, 0, lbl_3_common_bss_350E4.count * sizeof(StaC6Obj));
    lbl_3_common_bss_350E4.groupBounds = NULL;
    fn_3_E7B20(files, idx);
    lbl_3_bss_AE88[0] = 0;
}

