#include "game/rep_1C0.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"
#include "static/Camera.h"
#include "main/file_8000F150.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_80039AC0.h"
#pragma dont_inline on

typedef struct { u8 b[14]; } Tbl14;

// Sky/backdrop object drawn per camera (two copies, indexed by lbl_803CBBC0).
typedef struct StadiumSkyObj {
    /*0x00*/ u32 link; // draw-list link (fn_800A7D4C)
    /*0x04*/ void (*func)(struct StadiumSkyObj* obj);
    /*0x08*/ Mtx model;
    /*0x38*/ Mtx view;
    /*0x68*/ void* layout; // actor layout drawn by fn_3_3638
    /*0x6C*/ s32 camera;
} StadiumSkyObj; // size: 0x70

// Per-scene screen effect settings copied into lbl_803C5090.
typedef struct StadiumScreenFx {
    /*0x0*/ f32 scale;
    /*0x4*/ f32 jitterX;
    /*0x8*/ f32 jitterY;
    /*0xC*/ u8 flags;
    /*0xD*/ u8 alpha;
    /*0xE*/ u16 lines;
} StadiumScreenFx; // size: 0x10

// Fog settings (fn_3_5BF0 uses the first entry; color.a is the GX fog type).
typedef struct StadiumFog {
    /*0x0*/ GXColor color;
    /*0x4*/ f32 start;
    /*0x8*/ f32 end;
} StadiumFog; // size: 0xC

// Per-stadium visual settings (fog, screen effects, sky speed); copied from lbl_3_data_23C.
typedef struct StadiumVisual {
    /*0x00*/ StadiumFog fog[3]; // read through raw offsets by fn_3_5BF0
    /*0x24*/ StadiumScreenFx screenFx[3]; // scenes 1, 2, other
    /*0x54*/ f32 skySpeed;
    /*0x58*/ GXColor clearColor; // fn_3_35F0
    /*0x5C*/ u8 _5C;
    /*0x5D*/ u8 _5D; // passed to fn_8003AE5C
    /*0x5E*/ u8 _5E[2];
} StadiumVisual; // size: 0x60

// View of g_UNK_StadiumDetails, only the fields used by this unit's sky code.
typedef struct StadiumGfx {
    /*0x000*/ void* textures; // texture list of the loaded stadium archive
    /*0x004*/ void* texArchive;
    /*0x008*/ StadiumSkyObj sky[7][2];
    /*0x628*/ u8 _628[0x70A - 0x628];
    /*0x70A*/ s16 lightCount;
    /*0x70C*/ u8* lights; // relocated offset table
    /*0x710*/ f32 skyAngle;
    /*0x714*/ StadiumVisual visual;
    /*0x774*/ u8 _774;
    /*0x775*/ u8 _775[3];
    /*0x778*/ u8* table2; // relocated offset table
    /*0x77C*/ s16 table2Count;
} StadiumGfx;
#define sStadiumGfx (*(StadiumGfx*)g_UNK_StadiumDetails) // TODO type: g_UNK_StadiumDetails is u8[] here

typedef struct StadiumAnimNode {
    /*0x0*/ u32 link;
    /*0x4*/ void (*func)(struct StadiumAnimNode* node); // fn_3_5C68
    /*0x8*/ void* anim[2];
} StadiumAnimNode;

typedef struct StadiumFogNode {
    /*0x0*/ u32 link;
    /*0x4*/ void (*func)(void); // fn_3_5BF0
} StadiumFogNode;

typedef struct StadiumCameraNode {
    /*0x0*/ u32 link;
    /*0x4*/ void (*func)(struct StadiumCameraNode* node); // fn_3_5BCC
    /*0x8*/ s32 camera;
} StadiumCameraNode;

// lbl_3_data_7EC: per-stadium ARAM loads, then the stadium draw-list nodes.
typedef struct StadiumDrawData {
    /*0x000*/ u32 aram[21][4]; // AssetLoadInstructions words
    /*0x150*/ StadiumAnimNode animNodes[2];
    /*0x170*/ s32 _170;
    /*0x174*/ StadiumFogNode fogNodes[5][2];
    /*0x1C4*/ StadiumCameraNode cameraNodes[4][2];
} StadiumDrawData; // size: 0x224

// lbl_3_data_23C: stadium visual settings, then the two fn_3_3818 nodes.
typedef struct StadiumData23C {
    /*0x000*/ StadiumVisual visuals[15]; // [miniGameStadiumIndicator * 7 + StadiumID]
    /*0x5A0*/ StadiumFogNode drawCallbackNodes[2];
} StadiumData23C;

typedef struct StadiumObjAnims {
    /*0x0*/ u8 _0[8];
    /*0x8*/ void* anim[2];
} StadiumObjAnims; // view of lbl_3_common_bss_350E4 (StadiumObjMgr, game/rep_1D58.c)

extern StadiumObjAnims lbl_3_common_bss_350E4;
extern u8 lbl_3_common_bss_35154[];
extern u8 lbl_8036E548[];
extern ScreenFx lbl_803C5090;
extern void fn_800A7D4C(s32 list, void* node);
extern void fn_8003A2C0(void);
extern void fn_3_BD1D8(Mtx m);
extern void fn_3_BCA20(void);
extern void fn_3_B8C08(Mtx view);

#define STADIUM_EXTRA_CAMERAS 0

extern u8 lbl_3_rodata_214[];
extern void CTRLBuildMatrix(void*, void*);
extern void DOVARender(void* obj, MtxPtr m, u8 flag, void* args); // args: va_list*
extern s32 fn_800B7D3C(s32 index, Vec* box, Mtx m);
extern u8 lbl_803CBBC0;

// .data (laid out in definition order)
u8 lbl_3_data_228[0x14] = {0}; // shared frame counters / random seed (other units view it as a struct)

StadiumData23C lbl_3_data_23C = {
    {
        {{{{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}},
         {{40.0f, 1.0f, 1.0f, 0x0, 0x70, 0x10A}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x80, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}},
         {{42.0f, 1.5f, 1.5f, 0xF, 0xA0, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xF, 0x80, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xF, 0x50, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x40, {0x0, 0x0}},
        {{{{0xFF, 0xDC, 0x96, 0x00}, 0.0f, 512.0f}, {{0xFF, 0xDC, 0x96, 0x00}, 0.0f, 512.0f}, {{0xFF, 0xDC, 0x96, 0x00}, 0.0f, 512.0f}},
         {{42.0f, 1.5f, 1.5f, 0xF, 0xA0, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xF, 0x80, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xF, 0x50, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x75, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}},
         {{40.0f, 1.0f, 1.0f, 0xB, 0x70, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xB, 0x40, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xB, 0x40, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x60, {0x0, 0x0}},
        {{{{0x96, 0xAA, 0xDC, 0x02}, 80.0f, 300.0f}, {{0x96, 0xAA, 0xDC, 0x02}, 80.0f, 300.0f}, {{0x96, 0xAA, 0xDC, 0x02}, 80.0f, 300.0f}},
         {{40.0f, 1.0f, 1.0f, 0xB, 0x70, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xB, 0x40, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xB, 0x40, 0x1C0}},
         0.0f, {0x00, 0xFF, 0xFF, 0x00}, 0x8, 0x60, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x07}, 0.0f, 380.0f}, {{0xAA, 0xBE, 0xD2, 0x07}, 0.0f, 380.0f}, {{0xAA, 0xBE, 0xD2, 0x07}, 0.0f, 380.0f}},
         {{50.0f, 1.0f, 1.0f, 0xB, 0x80, 0x1C0}, {50.0f, 1.0f, 1.0f, 0x0, 0x80, 0x1C0}, {50.0f, 1.0f, 1.0f, 0xB, 0x80, 0x1C0}},
         0.00016362462f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x48, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}},
         {{40.0f, 1.0f, 1.0f, 0x0, 0x70, 0x10A}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x80, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}},
         {{40.0f, 1.0f, 1.0f, 0x0, 0x70, 0x10A}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x80, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}},
         {{42.0f, 1.5f, 1.5f, 0xF, 0xA0, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xF, 0x80, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xF, 0x50, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x40, {0x0, 0x0}},
        {{{{0xFF, 0xDC, 0x96, 0x00}, 0.0f, 512.0f}, {{0xFF, 0xDC, 0x96, 0x00}, 0.0f, 512.0f}, {{0xFF, 0xDC, 0x96, 0x00}, 0.0f, 512.0f}},
         {{42.0f, 1.5f, 1.5f, 0xF, 0xA0, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xF, 0x80, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xF, 0x50, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x75, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}},
         {{40.0f, 1.0f, 1.0f, 0xB, 0x70, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xB, 0x40, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xB, 0x40, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x60, {0x0, 0x0}},
        {{{{0x96, 0xAA, 0xDC, 0x02}, 80.0f, 300.0f}, {{0x96, 0xAA, 0xDC, 0x02}, 80.0f, 300.0f}, {{0x96, 0xAA, 0xDC, 0x02}, 80.0f, 300.0f}},
         {{40.0f, 1.0f, 1.0f, 0xB, 0x70, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xB, 0x40, 0x1C0}, {80.0f, 1.0f, 1.0f, 0xB, 0x40, 0x1C0}},
         0.0f, {0x00, 0xFF, 0xFF, 0x00}, 0x8, 0x60, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x07}, 0.0f, 380.0f}, {{0xAA, 0xBE, 0xD2, 0x07}, 0.0f, 380.0f}, {{0xAA, 0xBE, 0xD2, 0x07}, 0.0f, 380.0f}},
         {{50.0f, 1.0f, 1.0f, 0xB, 0x80, 0x1C0}, {50.0f, 1.0f, 1.0f, 0x0, 0x80, 0x1C0}, {50.0f, 1.0f, 1.0f, 0xB, 0x80, 0x1C0}},
         0.00016362462f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x48, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}},
         {{40.0f, 1.0f, 1.0f, 0x0, 0x70, 0x10A}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x80, {0x0, 0x0}},
        {{{{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}, {{0xAA, 0xBE, 0xD2, 0x00}, 80.0f, 450.0f}},
         {{40.0f, 1.0f, 1.0f, 0x0, 0x70, 0x10A}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}, {80.0f, 1.0f, 1.0f, 0x0, 0x40, 0x1C0}},
         2.9088822e-05f, {0x00, 0x00, 0x00, 0x00}, 0x8, 0x80, {0x0, 0x0}},
    },
    {{2, fn_3_3818}, {2, fn_3_3818}},
};

StadiumDrawData lbl_3_data_7EC = {
    {
        {0x0000040B, 0x40168A6C, 0x06CFD000, 0x000C69A8},
        {0x0000040B, 0x401331E0, 0x06DC4000, 0x000B67C4},
        {0x0000040B, 0x4011924C, 0x06E7A800, 0x000A5764},
        {0x0000040B, 0x400FBAE0, 0x06F20000, 0x000BE038},
        {0x0000040B, 0x400E5AC0, 0x06FDE800, 0x000B4FB8},
        {0x0000040B, 0x40131200, 0x07093800, 0x000A317C},
        {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
        {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
        {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
        {0x0000040B, 0x40141C60, 0x07207800, 0x000CE904},
        {0x0000040B, 0x4013CA40, 0x072D6800, 0x000CA560},
        {0x0000040B, 0x40141C60, 0x07207800, 0x000CE904},
        {0x0000040B, 0x4016C138, 0x073A1000, 0x000ED41C},
        {0x0000040B, 0x401157B8, 0x0748E800, 0x000CA83C},
        {0x0000040B, 0x4016C138, 0x073A1000, 0x000ED41C},
        {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
        {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
        {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
        {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
        {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
        {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
    },
    {{2, (void (*)(StadiumAnimNode*))fn_3_5C68, {NULL, NULL}}, {2, (void (*)(StadiumAnimNode*))fn_3_5C68, {NULL, NULL}}},
    -246,
    {{{2, fn_3_5BF0}, {2, fn_3_5BF0}}, {{2, fn_3_5BF0}, {2, fn_3_5BF0}}, {{2, fn_3_5BF0}, {2, fn_3_5BF0}}, {{2, fn_3_5BF0}, {2, fn_3_5BF0}}, {{2, fn_3_5BF0}, {0, fn_3_5BF0}}},
    {{{2, (void (*)(StadiumCameraNode*))fn_3_5BCC, 0}, {2, (void (*)(StadiumCameraNode*))fn_3_5BCC, 0}}, {{2, (void (*)(StadiumCameraNode*))fn_3_5BCC, 1}, {2, (void (*)(StadiumCameraNode*))fn_3_5BCC, 1}}, {{2, (void (*)(StadiumCameraNode*))fn_3_5BCC, 2}, {2, (void (*)(StadiumCameraNode*))fn_3_5BCC, 2}}, {{2, (void (*)(StadiumCameraNode*))fn_3_5BCC, 3}, {2, (void (*)(StadiumCameraNode*))fn_3_5BCC, 3}}},
};

StadiumDrawFn lbl_3_data_A10[2] = {NULL, NULL}; // per camera set: deferred draw callback

void (*lbl_3_bss_18[6])(void); // extra stadium draw hook (fn_3_35E4); only [0] is used
extern f32 lbl_3_rodata_504;
extern f32 lbl_3_rodata_524;
extern f32 lbl_3_rodata_528;
extern f32 lbl_3_rodata_52C;
extern f32 lbl_3_rodata_530;
extern f32 lbl_3_rodata_520[];
extern f32 lbl_3_rodata_538[];
extern u8 g_UNK_StadiumDetails[];
extern u32 fn_80009028(void);
extern s32 fn_800527BC(void);
extern void fn_80052694(s32 index);
extern camera_803c639c_s* fn_80052734(s32);
extern s32 lbl_3_rodata_210;
extern void DCStoreRange(void*, u32);
extern s32 fn_80023F0C(void*, void*, int, int, int, int, int, int);

// .text:0x000035D4 size:0x10
void (*setFanObjPtr(void))(void) {
    return lbl_3_bss_18[0];
}

// .text:0x000035E4 size:0xC
void fn_3_35E4(void (*val)(void)) {
    lbl_3_bss_18[0] = val;
}

// .text:0x000035F0 size:0x48
void fn_3_35F0(void) {
    if (fn_80009028() == 0) {
        GXSetCopyClear(*(GXColor*)(g_UNK_StadiumDetails + 0x76C), 0xFFFFFF);
    }
}

// .text:0x00003638 size:0x1E0
void fn_3_3638(u8* obj) {
    u8* e;
    u8* pA;
    u8* pB;
    s32 i;
    u8* hdr;
    u8* m26;
    u8* tbl;
    Mtx m;
    f32 pts[24];
    i = 0;
    pA = obj + 8;
    pB = obj + 0x38;
    hdr = *(u8**)(obj + 0x68);
    tbl = *(u8**)(hdr + 0x10);
    e = hdr;
    for (i = 0; i < *(u16*)(hdr + 6); e += 0x1C, i++) {
        u16 idx = *(u16*)(e + 0x34);
        if (idx != 0xFFFF) {
            m26 = *(u8**)(*(u8**)(tbl + 0x10) + idx * 8);
            CTRLBuildMatrix(*(void**)(e + 0x20), m26 + 0x18);
            PSMTXConcat((void*)pA, (void*)(m26 + 0x18), (void*)(m26 + 0x18));
            PSMTXConcat((void*)pB, (void*)(m26 + 0x18), m);
#define F(o) (*(f32*)(m26 + o))
            pts[0] = F(0x58); pts[1] = F(0x60); pts[2] = F(0x64);
            pts[3] = F(0x54); pts[4] = F(0x60); pts[5] = F(0x64);
            pts[6] = F(0x54); pts[7] = F(0x60); pts[8] = F(0x68);
            pts[9] = F(0x58); pts[10] = F(0x60); pts[11] = F(0x68);
            pts[12] = F(0x58); pts[13] = F(0x5C); pts[14] = F(0x64);
            pts[15] = F(0x54); pts[16] = F(0x5C); pts[17] = F(0x64);
            pts[18] = F(0x54); pts[19] = F(0x5C); pts[20] = F(0x68);
            pts[21] = F(0x58); pts[22] = F(0x5C); pts[23] = F(0x68);
            if (fn_800B7D3C(*(s32*)(obj + 0x6C), (Vec*)pts, m)) {
                if (*(u16*)(e + 0x3A) & 1) {
                    GXSetZMode(1, 7, 1);
                } else {
                    GXSetZMode(1, 3, 1);
                }
                switch (*(u16*)(e + 0x3A) & 6) {
                case 2:
                    GXSetBlendMode(1, 1, 1, 0);
                    break;
                case 4:
                    GXSetBlendMode(1, 2, 0, 0);
                    break;
                default:
                    GXSetBlendMode(1, 4, 5, 0);
                    break;
                }
                DOVARender(m26, (MtxPtr)pB, 0, NULL);
            }
        }
    }
}

// .text:0x00003818 size:0xD0
void fn_3_3818(void) {
    s32 i;
    if (lbl_3_data_A10[lbl_803CBBC0 == 0] != NULL) {
        i = fn_800527BC() - 1;
        do {
            fn_80052694(i);
            lbl_3_data_A10[lbl_803CBBC0 == 0](fn_80052734(i)->view, 0, 0);
        } while (i-- != 0);
        lbl_3_data_A10[lbl_803CBBC0 == 0] = NULL;
    }
}

// .text:0x000038E8 size:0x1C
void fn_3_38E8(StadiumDrawFn a) {
    lbl_3_data_A10[lbl_803CBBC0] = a;
}

#pragma dont_inline off
// Glyph codes: wide glyphs (bit 0x8000) are 22x22 cells on a 46-column grid
// spread over font pages; narrow ones are 11x22 cells on page 0.
static inline void DecodeWideGlyph(u16 v, s16* x, s16* y, s16* w, s16* h, s16* page) {
    u16 i = v & 0x7FFF;
    *page = i / 2116;
    i = i % 2116;
    *x = i % 46;
    *y = (i / 46) * 22;
    *x = *x * 22;
    *w = 22;
    *h = 22;
}

static inline void DecodeNarrowGlyph(u16 v, s16* x, s16* y, s16* w, s16* h, s16* page) {
    *x = v % 92;
    *y = (v / 92) * 22;
    *x = (*x % 2 + (*x / 2) * 2) * 11;
    *w = 11;
    *h = 22;
    *page = 0;
}

// Decodes the glyph code at `in`; control codes (bit 0x4000) leave the outputs untouched.
static inline void DecodeGlyph(u16* in, s16* x, s16* y, s16* w, s16* h, s16* page) {
    u16 v = *in;
    if (!(v & 0x4000)) {
        if (v & 0x8000) {
            DecodeWideGlyph(v, x, y, w, h, page);
        } else {
            DecodeNarrowGlyph(v, x, y, w, h, page);
        }
    }
}

extern const f32 lbl_3_rodata_4F8; // 16.0f
extern const f32 lbl_3_rodata_4FC; // 18.0f
extern const f32 lbl_3_rodata_500; // 8.0f

// Draws message `msg` of the first message table with the font glyphs at
// (x, y). Control codes: 0 ends, 1 is a newline, 2/3 are half/full spaces.
// .text:0x00003904 size:0x2E4 mapped:0x80642998
// NONMATCHING 86%: scheduling of the inlined wide-glyph decode (i kept in r0 in the original)
#if NONMATCHING
void fn_3_3904(s16 x, s16 y, s32 msg, GXColor color0, GXColor color1, u8 flags) {
    GXTexObj tex;
    s16 sx;
    s16 sy;
    s16 sw;
    s16 sh;
    u16* text;
    s16 startX;
    u16 c;
    s16 page;
    f32 advance;
    f32 height;

    startX = x;
    text = lbl_80366B18.tables[0]->msgs[msg];

    for (;;) {
        c = *text++;
        if (c & 0x4000) {
            switch (c & 0x3FFF) {
            case 0:
                return;
            case 2:
                x += 11;
                break;
            case 3:
                x += 22;
                break;
            case 1:
                x = startX;
                y += 22;
                break;
            }
            continue;
        }
        if (c & 0x8000) {
            DecodeWideGlyph(c, &sx, &sy, &sw, &sh, &page);
            advance = lbl_3_rodata_4F8;
            height = lbl_3_rodata_4FC;
        } else {
            DecodeNarrowGlyph(c, &sx, &sy, &sw, &sh, &page);
            advance = lbl_3_rodata_500;
            height = lbl_3_rodata_4FC;
        }
        GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        fn_3_42CC(&tex, x, y, x + advance, y + height, sx, sy, sw, sh, color0, color1, flags & 1);
        x += advance;
    }
}
#endif

// Draws the texel rect (u, v, uw, vh) of `img` as a screen quad (x0, y0)-(x1, y1).
// Tex coords are s16 with 9 fractional bits.
// .text:0x00003BE8 size:0x300 mapped:0x80642C7C
// NONMATCHING 94%: float constant pooling (-0.5f reloaded per vertex in the original) and r28/r31 swap
#if NONMATCHING
void fn_3_3BE8(TexImage* img, s16 x0, s16 y0, s16 x1, s16 y1, s16 u, s16 v, s16 uw, s16 vh) {
    GXTexObj tex;
    f32 left = x0;
    f32 top = y0;
    f32 right = x1;
    f32 bottom = y1;
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};

    GXInitTexObj(&tex, img->data, img->width, img->height, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 9);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(GX_TEVREG0, white);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = left;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.s16 = u;
    GXWGFifo.s16 = v;
    GXWGFifo.f32 = right;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.s16 = u + uw;
    GXWGFifo.s16 = v;
    GXWGFifo.f32 = right;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.s16 = u + uw;
    GXWGFifo.s16 = v + vh;
    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.s16 = u;
    GXWGFifo.s16 = v + vh;
}
#endif

// Like fn_3_3BE8 with point sampling and normalized float tex coords.
// .text:0x00003EE8 size:0x3E4 mapped:0x80642F7C
// NONMATCHING 82%: scheduling of the int->float conversions
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
void fn_3_3EE8(TexImage* img, s16 x0, s16 y0, s16 x1, s16 y1, s16 u, s16 v, s16 uw, s16 vh) {
    GXTexObj tex;
    f32 s0 = (f32)u / (f32)img->width;
    f32 t0 = (f32)v / (f32)img->height;
    f32 s1 = (f32)(u + uw) / (f32)img->width;
    f32 t1 = (f32)(v + vh) / (f32)img->height;
    f32 left = x0;
    f32 top = y0;
    f32 right = x1;
    f32 bottom = y1;
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};

    GXInitTexObj(&tex, img->data, img->width, img->height, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, white);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = left;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = s0;
    GXWGFifo.f32 = t0;
    GXWGFifo.f32 = right;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = s1;
    GXWGFifo.f32 = t0;
    GXWGFifo.f32 = right;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = s1;
    GXWGFifo.f32 = t1;
    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = s0;
    GXWGFifo.f32 = t1;
}

// Draws one font glyph: a quad in color0/color1 one pixel larger than the
// glyph (the outline), then the glyph texel rect (sx, sy, sw, sh) on top.
// Bit 0 of flags inverts the glyph.
#endif
#pragma pool_data reset

// .text:0x000042CC size:0x6B8 mapped:0x80643360
// NONMATCHING 99.8%: r0/r5/r11 allocation of the sx/sw/sy/sh int->float temps, f25/f27 swap
#if NONMATCHING
void fn_3_42CC(GXTexObj* tex, s16 x0, s16 y0, s16 x1, s16 y1, s16 sx, s16 sy, s16 sw, s16 sh,
               GXColor color0, GXColor color1, u8 flags) {
    f32 left = x0;
    f32 top = y0;
    f32 right = x1;
    f32 bottom = y1;
    u32 texW = GXGetTexObjWidth(tex);
    u16 texH = GXGetTexObjHeight(tex);
    f32 u0;
    f32 v0;
    f32 u1;
    f32 v1;
    s32 invert;

    u1 = (f32)(sx + sw) / (f32)(u16)texW;
    v0 = (f32)sy / (f32)texH;
    u0 = (f32)sx / (f32)(u16)texW;
    v1 = (f32)(sy + sh) / (f32)texH;

    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTevColor(GX_TEVREG0, color0);
    GXSetTevColor(GX_TEVREG1, color1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    invert = flags & 1;
    if (!invert) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0, GX_CC_C1);
    } else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_C0, GX_CC_C1);
    }
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        f32 ot = top - 1.0f;
        f32 ol = left - 1.0f;
        f32 or = 1.0f + right;
        f32 ob = 1.0f + bottom;
        GXWGFifo.f32 = ol;
        GXWGFifo.f32 = ot;
        GXWGFifo.f32 = -0.5f;
        GXWGFifo.f32 = or;
        GXWGFifo.f32 = ot;
        GXWGFifo.f32 = -0.5f;
        GXWGFifo.f32 = or;
        GXWGFifo.f32 = ob;
        GXWGFifo.f32 = -0.5f;
        GXWGFifo.f32 = ol;
        GXWGFifo.f32 = ob;
        GXWGFifo.f32 = -0.5f;
    }

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(2);
    if (invert == 0) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_C0, GX_CC_C1);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    } else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ONE);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_C0, GX_CC_C1);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    }
    GXLoadTexObj(tex, GX_TEXMAP0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = left;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = u0;
    GXWGFifo.f32 = v0;
    GXWGFifo.f32 = right;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = u1;
    GXWGFifo.f32 = v0;
    GXWGFifo.f32 = right;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = u1;
    GXWGFifo.f32 = v1;
    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = u0;
    GXWGFifo.f32 = v1;
}
#endif

// .text:0x00004984 size:0xB4 mapped:0x80643A18
void fn_3_4984(void) {
    Mtx mtx;
    Mtx44 proj;
    GXSetZMode(1, 7, 1);
    GXSetScissor(0, 0, 0x280, 0x1C0);
    C_MTXOrtho(proj, lbl_3_rodata_504, lbl_3_rodata_524, lbl_3_rodata_504, lbl_3_rodata_528, lbl_3_rodata_52C, lbl_3_rodata_530);
    GXSetProjection(proj, 1);
    GXSetCullMode(0);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
}

extern GameScores g_Scores;

// Draws the scoreboard numbers of `stadium`: runs per inning for both teams
// and the two totals. From extra innings on, the board starts at the inning
// after the stadium's last regular column.
// .text:0x00004A38 size:0x558 mapped:0x80643ACC
// NONMATCHING 98%: stack layout and register allocation; control flow and calls match.
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
void fn_3_4A38(u8 stadium) {
    GXColor colors[7][2] = {
        {{0x66, 0x66, 0x66, 0xFF}, {0x00, 0x00, 0x00, 0xFF}}, {{0x66, 0x66, 0x66, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
        {{0x66, 0x66, 0x66, 0xFF}, {0x00, 0x00, 0x00, 0xFF}}, {{0x66, 0x66, 0x66, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
        {{0x66, 0x66, 0x66, 0xFF}, {0x00, 0x00, 0x00, 0xFF}}, {{0x66, 0x66, 0x66, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
        {{0x66, 0x66, 0x66, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
    };
    s16 lastColumn[7] = {10, 9, 0, 0, 0, 0, 0};
    s16 awayPos[7][2] = {{28, 192}, {18, 138}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    s16 homePos[7][2] = {{28, 214}, {18, 159}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    s16 awayTotalPos[7][2] = {{250, 192}, {180, 138}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    s16 homeTotalPos[7][2] = {{250, 214}, {180, 159}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    u8 totalWidth[7] = {1, 1, 0, 0, 0, 0, 0};
    s16 spacing[7][2] = {{22, 18}, {18, 18}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    GXTexObj tex;
    s32 first;
    s32 end;
    s32 inning;
    s16 xoff;
    u8 boxed;

    GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    first = 1;
    if (g_Scores.inning >= lastColumn[stadium] + 1) {
        first = lastColumn[stadium] + 1;
    }

    end = g_Scores.inning;
    xoff = 0;
    for (inning = first; inning <= end; inning++) {
        if (inning == g_Scores.inning && g_Scores.team[0].runs[inning] == 0 && g_Scores._AD == 0 &&
            g_GameLogic.EventTriggers_EndOfGame == 0) {
            break;
        }
        fn_3_4F90(&tex, awayPos[stadium][0] + xoff, awayPos[stadium][1], g_Scores.team[0].runs[inning], 1,
                  colors[stadium][0], colors[stadium][1], 0);
        xoff += spacing[stadium][0];
    }
    fn_3_4F90(&tex, awayTotalPos[stadium][0], awayTotalPos[stadium][1], g_Scores.team[0].runs[0],
              totalWidth[stadium], colors[stadium][0], colors[stadium][1], 0);

    if (g_GameLogic.EventTriggers_EndOfGame == 0) {
        end = g_Scores.inning + g_Scores._AD;
    } else {
        end = g_Scores.maxInnings + 1;
    }
    xoff = 0;
    for (inning = first; inning < end; inning++) {
        // From the last regular inning on, a winning home score is drawn boxed.
        if (inning >= g_Scores.maxInnings && g_Scores.team[1].runs[0] > g_Scores.team[0].runs[0]) {
            boxed = 1;
        } else {
            boxed = 0;
        }
        if (inning == g_Scores.inning && g_Scores.team[1].runs[inning] == 0 && !boxed &&
            g_GameLogic.EventTriggers_EndOfGame == 0) {
            break;
        }
        fn_3_4F90(&tex, homePos[stadium][0] + xoff, homePos[stadium][1], g_Scores.team[1].runs[inning], 1,
                  colors[stadium][0], colors[stadium][1], boxed);
        xoff += spacing[stadium][0];
    }
    fn_3_4F90(&tex, homeTotalPos[stadium][0], homeTotalPos[stadium][1], g_Scores.team[1].runs[0],
              totalWidth[stadium], colors[stadium][0], colors[stadium][1], 0);
}

// Draws `value` (clamped to 99) right-aligned in a field of `width` 16-pixel
// cells, using the digit messages 0-9. `boxed` first draws a box in color0
// in front of the digits.
#endif
#pragma pool_data reset

// .text:0x00004F90 size:0x450 mapped:0x80644024
// NONMATCHING 95%: saved-register allocation; right/bottom kept unextended in the original
#if NONMATCHING
void fn_3_4F90(GXTexObj* tex, s16 x, s16 y, s16 value, u8 width, GXColor color0, GXColor color1, u8 boxed) {
    u16** digitMsgs = lbl_80366B18.tables[0]->msgs;
    s16 digits;
    s16 cellW;
    s16 n;
    s16 right;
    s16 bottom;
    s16 sx;
    s16 sy;
    s16 sw;
    s16 sh;
    s16 page;
    s32 count;
    s32 i;

    if (value > 99) {
        value = 99;
    }
    digits = (value >= 10) + 1;
    if (boxed) {
        if (value != 0) {
            digits++;
        } else {
            digits = 1;
        }
    }
    if (digits > width) {
        cellW = (width * 16) / digits;
    } else {
        cellW = 16;
    }
    n = value;
    x = x + width * 16 - cellW;
    if (boxed) {
        GXClearVtxDesc();
        GXSetTevColor(GX_TEVREG0, color0);
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0, GX_CC_C0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetNumTexGens(0);
        GXSetNumChans(1);
        GXSetNumTevStages(1);
        GXSetLineWidth(18, GX_TO_ZERO);
        GXBegin(GX_LINES, GX_VTXFMT0, 4);
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
        GXWGFifo.f32 = -0.5f;
        GXWGFifo.f32 = x + cellW;
        GXWGFifo.f32 = y + 18;
        GXWGFifo.f32 = -0.5f;
        GXWGFifo.f32 = x + cellW;
        GXWGFifo.f32 = y;
        GXWGFifo.f32 = -0.5f;
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y + 18;
        GXWGFifo.f32 = -0.5f;
        GXSetLineWidth(6, GX_TO_ZERO);
        x -= cellW;
        digits--;
    }
    right = x + cellW;
    bottom = y + 18;
    count = digits;
    for (i = 0; i < count; i++) {
        DecodeGlyph(digitMsgs[(s16)(n % 10)], &sx, &sy, &sw, &sh, &page);
        fn_3_42CC(tex, x, y, right, bottom, sx, sy, sw, sh, color0, color1, 0);
        right -= cellW;
        x -= cellW;
        n = n / 10;
    }
}
#endif

// .text:0x000053E0 size:0x138 mapped:0x80644474
void fn_3_53E0(u16* in, s16* x, s16* y, s16* w, s16* h, s16* page) {
    DecodeGlyph(in, x, y, w, h, page);
}

// .text:0x00005518 size:0x164 mapped:0x806445AC
// NONMATCHING 99.8%: r29/r31 swapped between the texture list and the image offset
#if NONMATCHING
// Copies the rendered scoreboard into the stadium's scoreboard texture.
void fn_3_5518(void) {
    s16 boardImage[7] = {0x49, 0x95, 0x1DB, 0x121, 0x1B2, 0xFB, 0};
    TexImage* images;
    Mtx44 proj;
    Mtx mtx;
    s32 idx;

    images = sStadiumGfx.textures;
    idx = boardImage[g_d_GameSettings.StadiumID];
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetScissor(0, 0, 640, 448);
    C_MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.5f, 1.5f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXSetCullMode(GX_CULL_NONE);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetTexCopySrc(0, 0, 512, 480);
    GXSetTexCopyDst(512, 480, GX_CTF_R4, GX_FALSE);
    fn_3_4A38(g_d_GameSettings.StadiumID);
    GXDrawDone();
    GXCopyTex(images[idx].data, GX_TRUE);
    GXPixModeSync();
}
#endif


// Per-frame stadium update: queues the sky objects and draw nodes of every
// camera and sets up the screen effect for the current scene.
// .text:0x0000567C size:0x530 mapped:0x80644710
// NONMATCHING 81%: the original reaches lbl_3_data_23C/7EC through one pooled .data base
// (lbl_3_data_228 + offset), ours addresses each symbol; register allocation. Defining the
// .data in this file (as globals or statics) does not make MWCC pool them here.
#if NONMATCHING
void fn_3_567C(void) {
    StadiumScreenFx* fx;
    StadiumSkyObj* obj;
    s32 i;

    switch (g_GameLogic.sceneID) {
    case 1:
    case 2:
        fx = &sStadiumGfx.visual.screenFx[g_GameLogic.sceneID - 1];
        break;
    default:
        fx = &sStadiumGfx.visual.screenFx[2];
        break;
    }
    if (lbl_8036E548[0x307E] == 0) { // TODO type: CharMgr._307E
        return;
    }
    lbl_3_common_bss_35154[0x3E0] = g_GameLogic.sceneID != 1; // TODO type: FadeState field 0x3E0
    if (lbl_3_common_bss_35154[0x3E0]) {
        fn_3_BD1D8(fn_80052768_getCamera(0)->view);
    }
    fn_3_B8C08(fn_80052768_getCamera(0)->view);
    sStadiumGfx.skyAngle += sStadiumGfx.visual.skySpeed;
    if (sStadiumGfx.skyAngle >= 6.2831855f) {
        sStadiumGfx.skyAngle -= 6.2831855f;
    }

    if (fn_800527BC() >= 2) {
        obj = &sStadiumGfx.sky[3][lbl_803CBBC0];
        obj->camera = 1;
        PSMTXCopy(fn_80052734(1)->view, obj->view);
        fn_800A7D4C(0, obj);
        fn_800A7D4C(0, &lbl_3_data_7EC.fogNodes[1][lbl_803CBBC0]);
        obj = &sStadiumGfx.sky[2][lbl_803CBBC0];
        obj->camera = 1;
        PSMTXRotRad(obj->model, 'Y', sStadiumGfx.skyAngle);
        PSMTXCopy(fn_80052734(1)->view, obj->view);
        if (g_GameLogic.secondaryGameMode != 3) {
            fn_800A7D4C(0, obj);
        }
        fn_800A7D4C(0, &lbl_3_data_7EC.cameraNodes[1][lbl_803CBBC0]);
    }
    if (fn_800527BC() > 2) {
        for (i = 0; i < STADIUM_EXTRA_CAMERAS; i++) {
            obj = &sStadiumGfx.sky[6 + i][lbl_803CBBC0];
            obj->camera = i + 2;
            PSMTXCopy(fn_80052734(i + 2)->view, obj->view);
            fn_800A7D4C(0, obj);
            fn_800A7D4C(0, &lbl_3_data_7EC.fogNodes[i + 2][lbl_803CBBC0]);
            obj = &sStadiumGfx.sky[4 + i][lbl_803CBBC0];
            obj->camera = i + 2;
            PSMTXRotRad(obj->model, 'Y', sStadiumGfx.skyAngle);
            PSMTXCopy(fn_80052734(i + 2)->view, obj->view);
            if (g_GameLogic.secondaryGameMode != 3) {
                fn_800A7D4C(0, obj);
            }
            fn_800A7D4C(0, &lbl_3_data_7EC.cameraNodes[i + 2][lbl_803CBBC0]);
        }
    }

    obj = &sStadiumGfx.sky[1][lbl_803CBBC0];
    obj->camera = 0;
    PSMTXCopy(fn_80052734(0)->view, obj->view);
    fn_800A7D4C(0, obj);
    fn_800A7D4C(0, &lbl_3_data_7EC.fogNodes[0][lbl_803CBBC0]);
    fn_800A7D4C(0, &lbl_3_data_23C.drawCallbackNodes[lbl_803CBBC0]);
    obj = &sStadiumGfx.sky[0][lbl_803CBBC0];
    obj->camera = 0;
    PSMTXRotRad(obj->model, 'Y', sStadiumGfx.skyAngle);
    PSMTXCopy(fn_80052734(0)->view, obj->view);
    fn_800A7D4C(0, obj);
    fn_800A7D4C(0, &lbl_3_data_7EC.cameraNodes[0][lbl_803CBBC0]);

    switch (g_d_GameSettings.StadiumID) {
    case 0:
    case 4:
        if (g_d_GameSettings.GameModeSelected != 2) {
            lbl_3_data_7EC.animNodes[lbl_803CBBC0].anim[0] = lbl_3_common_bss_350E4.anim[0];
            lbl_3_data_7EC.animNodes[lbl_803CBBC0].anim[1] = lbl_3_common_bss_350E4.anim[1];
            break;
        }
    default:
        lbl_3_data_7EC.animNodes[lbl_803CBBC0].anim[0] = NULL;
        lbl_3_data_7EC.animNodes[lbl_803CBBC0].anim[1] = NULL;
        break;
    }
    fn_800A7D4C(0, &lbl_3_data_7EC.animNodes[lbl_803CBBC0]);
    if (lbl_3_common_bss_35154[0x3E0]) {
        fn_3_BCA20();
    }
    lbl_803C5090.flags = fx->flags;
    lbl_803C5090.scale = fx->scale;
    lbl_803C5090.unk4 = 1.0f / fn_80052768_getCamera(0)->zoom;
    lbl_803C5090.alpha = fx->alpha;
    lbl_803C5090.jitterX = fx->jitterX;
    lbl_803C5090.jitterY = fx->jitterY;
    lbl_803C5090.lines = fx->lines;
    lbl_803C5090.unk18 = 0;
    lbl_803C5090.r = 0xFF;
    lbl_803C5090.g = 0xFF;
    lbl_803C5090.b = 0xFF;
    fn_8003A2C0();
}
#endif

// .text:0x00005BAC size:0x20 mapped:0x80644C40
void fn_3_5BAC(void) {
    fn_3_567C();
}

// .text:0x00005BCC size:0x24 mapped:0x80644C60

void fn_3_5BCC(u8* p) {
    fn_80052694(*(s32*)(p + 8));
}

// .text:0x00005BF0 size:0x78 mapped:0x80644C84
void fn_3_5BF0(void) {
    s32 col;
    u8* d = g_UNK_StadiumDetails;
    if (lbl_3_bss_18[0] != NULL) {
        lbl_3_bss_18[0]();
    }
    col = *(s32*)(d + 0x714);
    SetFog(d[0x717], (GXColor *)&col, *(f32*)(d + 0x718), *(f32*)(d + 0x71C), lbl_3_rodata_520[0], lbl_3_rodata_538[0]); // TODO type
}

// .text:0x00005C68 size:0x1F8 mapped:0x80644CFC
void fn_3_5C68(u8* obj) {
    s32 col;
    u8* p;
    s32 i;
    s32 k;
    s32 cnt;
    GXSetCullMode(2);
    col = lbl_3_rodata_210;
    SetFog(0, (GXColor *)&col, lbl_3_rodata_504, lbl_3_rodata_504, lbl_3_rodata_504, lbl_3_rodata_504); // TODO type
    GXSetBlendMode(1, 4, 5, 0);
    k = 2;
    while (k-- != 0) {
        p = *(u8**)(obj + 8 + k * 4);
        if (p != NULL) {
            cnt = 0;
            for (i = 0; i < *(u16*)(p + 0x14); i++) {
                u8* st = *(u8**)(p + 0x10);
                if (st[(i * 3) + 2]-- == 0) {
                    u8* e;
                    s32 m;
                    u8* t;
                    s32 x, y, ax, ay; u8* tb;
                    u8* st2 = *(u8**)(p + 0x10);
                    st2[(i * 3) + 1] = (st2[(i * 3) + 1] + 1) % *(u16*)(p + 0x18);
                    ay = (i / 8) << 6;
                    ax = (i % 8) << 5;
                    e = *(u8**)(p + 0x10) + (i * 3);
                    m = (*(u8**)(p + 0xC))[e[1]];
                    if (k != 0) {
                        tb = *(u8**)(p + 8);
                        x = tb[e[0] * 4 + m * 2] << 5;
                        y = tb[e[0] * 4 + m * 2 + 1] << 6;
                    } else {
                        tb = *(u8**)(p + 8);
                        x = tb[e[0] * 8 + m * 2] << 5;
                        y = tb[e[0] * 8 + m * 2 + 1] << 6;
                    }
                    fn_80023F0C(*(void**)p, *(void**)(p + 4), x, y, 0x20, 0x40, ax, ay);
                    cnt++;
                    (*(u8**)(p + 0x10))[(i * 3) + 2] = *(u16*)(p + 0x16);
                }
            }
            if (cnt != 0) {
                u8* tex = *(u8**)(p + 4);
                DCStoreRange(*(void**)tex, *(u16*)(tex + 0xA) * *(u16*)(tex + 8));
            }
        }
    }
    if (lbl_3_bss_18[0] != NULL) {
        lbl_3_bss_18[0]();
    }
    GXSetZCompLoc(0);
}


extern u8 lbl_8036E548[];
extern void fn_80035CA4(int);
extern void fn_800BCDBC(void*);
extern void fn_800ACFB0(void*);

// .text:0x00005E60 size:0x60
void fn_3_5E60(void) {
    u8* b = lbl_8036E548;
    u8* p = *(u8**)(b + 4);
    fn_80035CA4(5);
    fn_800BCDBC(p + *(s32*)(p + 0x10));
    fn_800BCDBC(p + *(s32*)(p + 0xC));
    fn_800ACFB0(*(void**)(b + 4));
}

// Offsets (from the archive start) of the parts of a loaded stadium archive.
typedef struct StadiumArchive {
    /*0x00*/ u32 layout;
    /*0x04*/ u32 skyLayout;
    /*0x08*/ u32 lights;
    /*0x0C*/ u32 geometry;
    /*0x10*/ u32 skyGeometry;
    /*0x14*/ u32 textures;
    /*0x18*/ u32 _18[4];
    /*0x28*/ u32 fadeTextures;
    /*0x2C*/ u32 table2;   // optional
    /*0x30*/ u32 textures3; // optional
} StadiumArchive;

struct LoadedActorLayout;
extern void fn_800B2AC8(struct LoadedActorLayout* layout);
extern void fn_8003AE5C(u8 value);
extern void fn_8003AD84(void* archive);
extern void fn_800BF038(void (*callback)(Mtx view, s32 arg));
extern void fn_3_BD434(int stadium, int variant);

// Sets up a freshly loaded stadium archive: relocates and links its models
// and textures, fills the per-camera sky objects and copies the stadium's
// visual settings.
// .text:0x00005EC0 size:0x564
// NONMATCHING 97%: fn_800BD190's s32 texture parameter makes us keep an extra copy of `textures`
// (a void* prototype gives the original 4-register allocation)
#if NONMATCHING
void fn_3_5EC0(StadiumArchive* arc) {
    void* layout = (u8*)arc + arc->layout;
    void* geometry = (u8*)arc + arc->geometry;
    void* textures = (u8*)arc + arc->textures;
    s32 i;

    sStadiumGfx.lightCount = fn_3_6424((u8*)arc + arc->lights, &sStadiumGfx.lights);
    fn_800B49E4(layout);
    fn_800BCE38(geometry);
    convertTextureHeader(textures);
    fn_800BD190(geometry, textures);
    haveActLayoutPointToGeoHeader(layout, geometry);
    fn_800B2AC8(layout);
    sStadiumGfx.texArchive = textures;
    PSMTXIdentity(sStadiumGfx.sky[1][0].model);
    sStadiumGfx.sky[1][0].link = 2;
    sStadiumGfx.sky[1][0].func = (void (*)(StadiumSkyObj*))fn_3_3638;
    sStadiumGfx.sky[1][0].layout = layout;
    sStadiumGfx.sky[1][1] = sStadiumGfx.sky[1][0];
    sStadiumGfx.sky[3][0] = sStadiumGfx.sky[1][0];
    sStadiumGfx.sky[3][1] = sStadiumGfx.sky[1][0];
    for (i = 0; i < STADIUM_EXTRA_CAMERAS; i++) {
        sStadiumGfx.sky[6 + i][0] = sStadiumGfx.sky[1][0];
        sStadiumGfx.sky[6 + i][1] = sStadiumGfx.sky[1][0];
    }

    // The sky model shares the stadium textures.
    layout = (u8*)arc + arc->skyLayout;
    geometry = (u8*)arc + arc->skyGeometry;
    fn_800B49E4(layout);
    fn_800BCE38(geometry);
    fn_800BD190(geometry, textures);
    haveActLayoutPointToGeoHeader(layout, geometry);
    sStadiumGfx.sky[0][0].link = 2;
    sStadiumGfx.sky[0][0].func = (void (*)(StadiumSkyObj*))fn_3_3638;
    sStadiumGfx.sky[0][0].layout = layout;
    sStadiumGfx.sky[0][1] = sStadiumGfx.sky[0][0];
    sStadiumGfx.sky[2][0] = sStadiumGfx.sky[0][0];
    sStadiumGfx.sky[2][1] = sStadiumGfx.sky[0][0];
    for (i = 0; i < STADIUM_EXTRA_CAMERAS; i++) {
        sStadiumGfx.sky[4 + i][0] = sStadiumGfx.sky[0][0];
        sStadiumGfx.sky[4 + i][1] = sStadiumGfx.sky[0][0];
    }

    sStadiumGfx.visual =
        lbl_3_data_23C.visuals[g_d_GameSettings.miniGameStadiumIndicator * 7 + g_d_GameSettings.StadiumID];
    sStadiumGfx.textures = (u8*)textures + 4; // TODO type: TexArchive entries
    sStadiumGfx._774 = 0;
    fn_8003AE5C(sStadiumGfx.visual._5D);

    geometry = (u8*)arc + arc->fadeTextures;
    convertTextureHeader(geometry);
    *(void**)(lbl_3_common_bss_35154 + 0x3B4) = (u8*)geometry + 4; // TODO type: FadeState field 0x3B4
    fn_3_BD434(g_d_GameSettings.StadiumID, g_d_GameSettings.miniGameStadiumIndicator);

    if (arc->table2 != 0) {
        sStadiumGfx.table2Count = fn_3_6424((u8*)arc + arc->table2, &sStadiumGfx.table2);
    } else {
        sStadiumGfx.table2Count = 0;
    }
    if (arc->textures3 != 0) {
        geometry = (u8*)arc + arc->textures3;
        convertTextureHeader(geometry);
        fn_8003AD84(geometry);
    }
    fn_800BF038((void (*)(Mtx, s32))fn_3_35F0);
}
#endif

// .text:0x000064DC size:0x54
void fn_3_64DC(void) {
    ARAMTransfer(lbl_3_data_7EC.aram[g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3], 0, 0, 0);
}

// .text:0x00006424 size:0xB8
s16 fn_3_6424(u8* base, u8** out) {
    s16 n = *(u16*)base;
    u32* p;
    s32 i;
    p = (u32*)(*out = base + 4);
    for (i = n; i >= 0; i--) {
        *p += (u32)base;
        p++;
    }
    return n;
}
