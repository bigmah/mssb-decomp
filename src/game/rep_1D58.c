#include "game/rep_1D58.h"
#define REP_HEADER_FN repHeader_1D58
#include "header_rep_inline.h"
#include "C3/control.h"
#include "C3/light.h"
#include "main/file_800BD8C4.h"
#include "main/file_800B9974.h"
#include "main/file_80024D2C.h"
#include "main/file_800BD3EC.h"
#include "main/file_8004C5F8.h"
#include "main/file_800BDEA0.h"
#include "main/file_800B2C44.h"
#include "main/file_80008E00.h"
#include "game/rep_1C0.h"
#include "main/file_80034F50.h" // SpaniDesc

extern void* memcpy(void*, const void*, u32);
extern f64 cos(f64);
extern f64 sin(f64);
extern int rand(void);
extern s32 fn_3_8BBC4(s32 id, f32* pos, f32* vel, s32 kind);
typedef struct { f32 x, y, z; } V3;

typedef struct SortEnt SortEnt;

// Expanded stadium light: position and colour.
typedef struct LitPos {
    f32 x, y, z;
    GXColor color;
} LitPos;

// Shape (texture) animation attached to a stadium object.
typedef struct StadiumObjShape {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ ShapeAnimState anim;
    /* 0x2C */ ShapeData* shape;
} StadiumObjShape;

// One 0xE8-byte stadium object (lbl_3_common_bss_350E4.objs[]).
typedef struct StadiumObj {
    /* 0x00 */ Control ctrl;
    /* 0x3C */ u8 pad3C[8];
    /* 0x44 */ Mtx mtx;
    /* 0x74 */ ActorObject* actor;
    /* 0x78 */ void* unk78; // collision model
    /* 0x7C */ u8 pad7C[4];
    /* 0x80 */ void (*func)(int, int, void*);
    /* 0x84 */ void (*preDraw)(struct StadiumObj* obj);
    /* 0x88 */ void (*postDraw)(struct StadiumObj* obj);
    /* 0x8C */ StadiumObjShape* shapeAnim;
    /* 0x90 */ u8 visible : 1;
    /* 0x90 */ u8 flag40 : 1;
    /* 0x90 */ u8 depthFade : 1; // sorted by depth; alpha scaled by the sort factor
    /* 0x90 */ u8 customZ : 1;   // use the z mode bits below
    /* 0x90 */ u8 zCompare : 1;
    /* 0x90 */ u8 zAlways : 1;   // GX_ALWAYS instead of GX_LEQUAL
    /* 0x90 */ u8 zUpdate : 1;
    /* 0x90 */ u8 flag01 : 1;
    /* 0x91 */ u8 pad91;
    /* 0x92 */ u8 alpha;
    /* 0x93 */ u8 viewFlags;     // low 2 bits: fn_800B3C04 result
    /* 0x94 */ u16 attached;
    /* 0x96 */ s16 attachJoint;  // -1: attach to the camera matrix
    /* 0x98 */ u8 layer;
    /* 0x99 */ u8 pad99;
    /* 0x9A */ u8 castShadow;
    /* 0x9B */ u8 pad9B[0xE8 - 0x9B];
} StadiumObj; // size: 0xE8

// lbl_3_common_bss_350E4: the stadium object manager.
typedef struct StadiumObjMgr {
    /* 0x00 */ StadiumObj* objs;
    /* 0x04 */ StadiumObj* saved;
    /* 0x08 */ u8 pad8[0xC];
    /* 0x14 */ SortEnt* sort;
    /* 0x18 */ u8 pad18[8];
    /* 0x20 */ Light* lights[4];
    /* 0x30 */ s32 count;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ void* data;
    /* 0x3C */ u8 pad3C[0x30];
    /* 0x6C */ u8 sortByDepth;
    /* 0x6D */ u8 pad6D[3];
} StadiumObjMgr; // size: 0x70
// TODO type: older functions in this file still view the manager as u8[].
#define sStadiumMgr (*(StadiumObjMgr*)lbl_3_common_bss_350E4)

// Stadium setup functions, indexed by stadium type (see fn_3_B9FB8).
extern void fn_3_C9DB4(void** files);
extern void fn_3_C8650(void** files);
extern void fn_3_D67CC(void** files);
extern void fn_3_E4FC4(void** files);
extern void fn_3_FA58C(void** files);
extern void fn_3_F6FDC(void** files);
extern void fn_3_E8B24(void** files);

// .data (initialized data is laid out in definition order)
void (*lbl_3_data_10AB0[7])(void** files) = {
    fn_3_C9DB4, fn_3_C8650, fn_3_D67CC, fn_3_E4FC4, fn_3_FA58C, fn_3_F6FDC, fn_3_E8B24,
};

// Stadium archive load instructions (AssetLoadInstructions words), one per stadium type.
u32 lbl_3_data_10ACC[7][4] = {
    0x0000040B, 0x40022EF0, 0x07684800, 0x00016B18,
    0x0000040B, 0x40020260, 0x0769B800, 0x00012864,
    0x0000040B, 0x4002FDC0, 0x076AE800, 0x000207F8,
    0x0000040B, 0x40024E2C, 0x076CF000, 0x000159AC,
    0x0000040B, 0x4001CB88, 0x076E5000, 0x0000EE60,
    0x0000040B, 0x40035BD0, 0x076F4000, 0x000257FC,
    0x0000040B, 0x400397CC, 0x07719800, 0x00023FF4,
};

// Sprite animation descriptors (each list ends with a type 3 entry); the
// stadium units extern the lists they use.
SpaniDesc lbl_3_data_10B3C[7] = {
    {0, 0x12, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x11, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x15, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x13, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x14, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {3, 0x0, 0.0f, 0.0f, 0, 0, 0, {0, 0x0}, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
SpaniDesc lbl_3_data_10C1C[9] = {
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {3, 0x0, 0.0f, 0.0f, 0, 0, 0, {0, 0x0}, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
SpaniDesc lbl_3_data_10D3C[11] = {
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {3, 0x0, 0.0f, 0.0f, 0, 0, 0, {0, 0x0}, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
SpaniDesc lbl_3_data_10E9C[7] = {
    {0, 0x12, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x11, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x15, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x16, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x13, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {0, 0x14, 0.0f, 0.0f, -1, 3, 10, {0, 0xFF}, 5, {0, 0, 0}, 0.055f, 0, 0, 0},
    {3, 0x0, 0.0f, 0.0f, 0, 0, 0, {0, 0x0}, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};

// Byte tables for the sta_c0/sta_c4 stadium sequences.
u8 lbl_3_data_10F7C[8] = {
    0x00, 0x01, 0x02, 0x03, 0x02, 0x01, 0x00, 0x00,
};
u8 lbl_3_data_10F84[4] = {
    0x00, 0x01, 0x00, 0x00,
};
u8 lbl_3_data_10F88[0x80] = {
    0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x01, 0x00, 0x01, 0x01, 0x01, 0x02, 0x01, 0x03,
    0x02, 0x00, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x03, 0x00, 0x03, 0x01, 0x03, 0x02, 0x03, 0x03,
    0x04, 0x00, 0x04, 0x01, 0x04, 0x02, 0x04, 0x03, 0x05, 0x00, 0x05, 0x01, 0x05, 0x02, 0x05, 0x03,
    0x06, 0x00, 0x06, 0x01, 0x06, 0x02, 0x06, 0x03, 0x07, 0x00, 0x07, 0x01, 0x07, 0x02, 0x07, 0x03,
    0x00, 0x04, 0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x01, 0x04, 0x01, 0x05, 0x01, 0x06, 0x01, 0x07,
    0x02, 0x04, 0x02, 0x05, 0x02, 0x06, 0x02, 0x07, 0x03, 0x04, 0x03, 0x05, 0x03, 0x06, 0x03, 0x07,
    0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0x04, 0x07, 0x05, 0x04, 0x05, 0x05, 0x05, 0x06, 0x05, 0x07,
    0x06, 0x04, 0x06, 0x05, 0x06, 0x06, 0x06, 0x07, 0x07, 0x04, 0x07, 0x05, 0x07, 0x06, 0x07, 0x07,
};
u8 lbl_3_data_11008[0x40] = {
    0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x02, 0x00, 0x02, 0x01, 0x03, 0x00, 0x03, 0x01,
    0x04, 0x00, 0x04, 0x01, 0x05, 0x00, 0x05, 0x01, 0x06, 0x00, 0x06, 0x01, 0x07, 0x00, 0x07, 0x01,
    0x00, 0x02, 0x00, 0x03, 0x01, 0x02, 0x01, 0x03, 0x02, 0x02, 0x02, 0x03, 0x03, 0x02, 0x03, 0x03,
    0x04, 0x02, 0x04, 0x03, 0x05, 0x02, 0x05, 0x03, 0x06, 0x02, 0x06, 0x03, 0x07, 0x02, 0x07, 0x03,
};
u8 lbl_3_data_11048[32][3] = {
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00,
    0x08, 0x01, 0x01, 0x09, 0x01, 0x01, 0x0A, 0x00, 0x00, 0x0B, 0x00, 0x00,
    0x0C, 0x01, 0x01, 0x0D, 0x01, 0x01, 0x0E, 0x00, 0x00, 0x0F, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x0A, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x0C, 0x03, 0x04, 0x0D, 0x03, 0x04,
    0x0E, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x08, 0x03, 0x04, 0x09, 0x03, 0x04,
};
u8 lbl_3_data_110A8[32][3] = {
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00,
    0x08, 0x01, 0x01, 0x09, 0x01, 0x01, 0x0A, 0x00, 0x00, 0x0B, 0x00, 0x00,
    0x0C, 0x01, 0x01, 0x0D, 0x01, 0x01, 0x0E, 0x00, 0x00, 0x0F, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x0A, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x0C, 0x03, 0x04, 0x0D, 0x03, 0x04,
    0x0E, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x08, 0x03, 0x04, 0x09, 0x03, 0x04,
};
u8 lbl_3_data_11108[16][3] = {
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00,
    0x08, 0x01, 0x01, 0x09, 0x01, 0x01, 0x0A, 0x00, 0x00, 0x0B, 0x00, 0x00,
    0x0C, 0x01, 0x01, 0x0D, 0x01, 0x01, 0x0E, 0x00, 0x00, 0x0F, 0x00, 0x00,
};
u8 lbl_3_data_11138[16][3] = {
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00,
    0x08, 0x01, 0x01, 0x09, 0x01, 0x01, 0x0A, 0x00, 0x00, 0x0B, 0x00, 0x00,
    0x0C, 0x01, 0x01, 0x0D, 0x01, 0x01, 0x0E, 0x00, 0x00, 0x0F, 0x00, 0x00,
};
u8 lbl_3_data_11168[16] = {0}; // per TEV stage: reset to direct after the draw (fn_3_B9510)
f32 lbl_3_data_11178[5] = {
    18.0f, 90.0f, 162.0f, 234.0f, 306.0f,
};

// .bss (laid out last-defined-first)
static u32 lbl_3_bss_9944[3]; // unused
void* lbl_3_bss_9940; // one-shot callback run by fn_3_B95EC
u8 lbl_3_bss_1940[0x8000]; // texture buffer handed out once by fn_3_B9534
f32 lbl_3_bss_1910[12]; // bounding box: min xyz, max xyz
StadiumObj* lbl_3_bss_190C;
f32 lbl_3_bss_1908; // depth fade floor
void* lbl_3_bss_1904; // saved copy of the stadium objects
static u8 lbl_3_bss_1903; // unused
u8 lbl_3_bss_1902;
u8 lbl_3_bss_1901;
static u8 lbl_3_bss_1900; // unused

typedef struct DspObj DspObj;
struct DspObj {
    u8 pad0[0x14];
    void* w14;
    u8 pad18[0x4C];
    void* w64;
    void* w68;
    u8 pad6C[8];
    DspObj* child;
    u8 pad78[4];
    void* w7C;
    u8 pad80[0x6C];
    void* wEC;
    u8 padF0[0x10];
    DspObj* next;
};
extern void fn_8003A548(void (*callback)(void));
extern u8 g_Ball[];
typedef struct StadW78 {
    u8 pad[0x78];
    void* w78;
} StadW78;
typedef struct StadObj78 {
    u8 pad[0x78];
    void* w78;
    u8 pad7C[0xE8 - 0x7C];
} StadObj78;
extern void* fn_3_C823C(s32 idx, Mtx out);
extern void* fn_3_E4BE8(s32 idx, Mtx m);
extern void* fn_3_F6504(s32 idx, Mtx m);
extern void* fn_3_E751C(s32 idx, Mtx m);
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern u8 lbl_803C6CF8[];
extern u8 lbl_8036E548[];
extern void* memset(void*, int, u32);
extern void* ARAMTransfer(void* instr, void* dest, u8 mode, u32 aramAddr);
extern void minigamesSetSomePointers(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
extern void fn_8001B200(void);
extern void fn_3_C1964(void);
extern void fn_3_16E328(void);
extern void fn_800528B4(void);
extern void fn_8001E474(void);
extern void fn_8003A8A0(void* model, Mtx viewMtx, s32 unused);
extern u8 lbl_3_common_bss_350E4[];
extern void fn_800ACFB0(void* block);
extern void* _OSAllocFromHeap(s32, s32);

typedef struct StadExtra {
    f32 a, b, c;
    s32 d, e;
    s16 i;
    u8 f, g, h;
} StadExtra;
typedef struct StadEnt {
    u8 pad[0xE8];
    StadExtra* extra;
} StadEnt;
typedef struct StadHdr {
    u8 pad0[6];
    u16 count;
    u8 pad8[0x10];
    StadEnt** list;
} StadHdr;

typedef struct StadObj {
    u8 pad0[0x80];
    void (*fn)(int, int, void*);
    u8 pad84[0xE8 - 0x84];
} StadObj;
typedef struct StadObjList {
    StadObj* objs;
    u8 pad4[0x2C];
    s32 count;
} StadObjList;

struct SortEnt {
    f32 z;
    s32 idx;
};
extern void* fn_800ACF34(s32, s32);
extern void fn_800ACF14(void*);
extern void fn_800C07BC(void* base, void* tmp, u32 count, u32 size, s32 (*compare)(const void*, const void*)); // main/file_800BDEA0.h

extern LitPos lbl_80367318[4];
// Per-stadium light setup (packed lights for fn_80023B90, then the ambient colour).
typedef struct StadiumLightRow {
    /* 0x00 */ u8 light[4][0xA];
    /* 0x28 */ GXColor ambient;
} StadiumLightRow; // size: 0x2C
extern StadiumLightRow lbl_800F7478[];

// Draw callback: draws the visible stadium objects of one layer, in sort order.

struct CharActor;
extern u8 g_GameLogic[];
extern void fn_8001E460(void (*draw)(MtxPtr view, s32 a, s32 b)); // CharDrawCallback, main/file_80011640.h
extern void fn_800116DC(struct CharActor* actor, Mtx m, u16 joint);
extern void fn_800117CC(Mtx src, Mtx m, Mtx dst);
extern void fn_800B2BFC(GameActor* actor, u16 boneA, u16 boneB);
extern void fn_3_D55EC(MtxPtr view, SortEnt* sort);
extern void fn_3_F6084(MtxPtr view, SortEnt* sort);
extern void fn_3_E7388(MtxPtr view, void* sort); // sort: E7388Pair* in sta_c6

// Per-frame update of the stadium objects: matrices, attachments, shadows and
// shape animations, then the per-stadium sort/fade pass.

extern u8 lbl_3_common_bss_350E4[];

extern void fn_800638CC(void);
typedef struct StadObjFn {
    u8 pad[0x7C];
    void (*fn)(struct StadObjFn*);
    u8 pad80[0xE8 - 0x80];
} StadObjFn;

extern void fn_3_35E4(void (*val)(void));
extern void fn_80023B90(void*, LitPos*);
extern void fn_8001B214(void (*)(void));
extern void fn_800B0A14_removeQueue(void* unused);

// fn_800B0A14_removeQueue ignores its argument. Some callers pass nothing: r3 is
// whatever the previous call left (e.g. right after fn_80034CEC). The matching
// build calls it through a (void) cast there; the port passes NULL.
#ifndef REMOVE_QUEUE_NOARG
#if NONMATCHING
#define REMOVE_QUEUE_NOARG() fn_800B0A14_removeQueue(NULL)
#else
#define REMOVE_QUEUE_NOARG() ((void (*)(void))fn_800B0A14_removeQueue)()
#endif
#endif

// Relocates a packed archive in place. `kinds` gives the content type of each
// file group; `table` starts with a list of u32 offsets (relative to `table`)
// that are turned into pointers. `outIdx` (optional) receives the first table
// slot of each group.

// .text:0x000B9FB8 size:0x198 mapped:0x806F904C
void fn_3_B9FB8(u32 type, void* p) {
    LitPos pos;
    Light* lit;
    GXColor color;
    s32 i;
    fn_8001E474();
    memset(lbl_3_common_bss_350E4, 0, 0x70);
    fn_3_35E4(NULL);
    if (p != NULL) {
        for (i = 0; i < 4; i++) {
            fn_80023B90(lbl_800F7478[g_d_GameSettings._54].light[i], &pos);
            LITAlloc(&lit);
            LITInitAttn(lit, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            LITInitPos(lit, pos.x, pos.y, pos.z);
            color = pos.color;
            LITInitColor(lit, &color);
            *(void**)(lbl_3_common_bss_350E4 + 0x20 + i * 4) = lit;
        }
        *(void**)(lbl_3_common_bss_350E4 + 0x38) = p;
        *(u32*)(lbl_3_common_bss_350E4 + 0x8) = 0;
        *(u32*)(lbl_3_common_bss_350E4 + 0xC) = 0;
        lbl_3_data_10AB0[type](p);
        *(void**)(lbl_3_common_bss_350E4 + 0x14) = _OSAllocFromHeap(4, *(s32*)(lbl_3_common_bss_350E4 + 0x30) * 8);
        fn_8001B214(fn_3_B8298);
        *(s16*)(lbl_3_common_bss_350E4 + 0x66) = rand();
        lbl_8036E548[0x3088] = 1;
        lbl_3_bss_1901 = 0;
    }
}

// .text:0x000B9D68 size:0x250 mapped:0x806F8DFC
void fn_3_B9D68(u8* kinds, s32 count, u8* table, s32* outIdx) {
    s32* out = outIdx;
    void* tex = NULL;
    void* skn = NULL;
    s32 idx = 0;
    s32 i = 0;
    void* layout;
    void* geo;

    do {
        if (outIdx != NULL) {
            *out = idx;
        }
        switch (kinds[i]) {
        case 1:
            tex = table + ((u32*)table)[idx++];
            convertTextureHeader(tex);
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            layout = table + ((u32*)table)[idx++];
            geo = table + ((u32*)table)[idx++];
            if ((u8)(kinds[i] - 2) > 1) {
                void* anim = table + ((u32*)table)[idx++];
                ANIMGet(anim);
            }
            if (kinds[i] == 3 || kinds[i] == 5) {
                skn = table + ((u32*)table)[idx++];
            }
            LoadActorLayout(layout);
            convertGeometryAndSknHeader(geo, skn);
            skn = NULL;
            fn_800BD190(geo, tex);
            haveActLayoutPointToGeoHeader(layout, geo);
            break;
        case 6: {
            u8* sub = table + ((u32*)table)[idx++];
            s32 n;
            s32 i;
            u32* q;
            n = *(u16*)sub;
            q = (u32*)(sub + 4);
            for (i = n; i >= 0; i--) {
                *q += (u32)sub; // TODO type: offsets become pointers in place
                q++;
            }
            break;
        }
        case 7: {
            void* anim = table + ((u32*)table)[idx++];
            ANIMGet(anim);
            break;
        }
        case 0:
        case 8:
        case 9:
        default:
            idx++;
            break;
        }
        out++;
        i++;
    } while (--count != 0);
    while (idx-- != 0) {
        ((u32*)table)[idx] += (u32)table; // TODO type: offsets become pointers in place
    }
}

// .text:0x000B9BB4 size:0x1B4 mapped:0x806F8C48
s32 fn_3_B9BB4(u32 type) {
    if ((s32)lbl_803C6CF8[0x715] == 1) {
    switch (type) {
        case 0:
            *(void**)(lbl_8036E548 + 8) = ARAMTransfer(lbl_3_data_10ACC[0], 0, 0, 0);
            break;
        case 1:
            *(void**)(lbl_8036E548 + 8) = ARAMTransfer(lbl_3_data_10ACC[1], 0, 0, 0);
            break;
        case 2:
            *(void**)(lbl_8036E548 + 8) = ARAMTransfer(lbl_3_data_10ACC[2], 0, 0, 0);
            break;
        case 3:
            *(void**)(lbl_8036E548 + 8) = ARAMTransfer(lbl_3_data_10ACC[3], 0, 0, 0);
            break;
        case 4:
            *(void**)(lbl_8036E548 + 8) = ARAMTransfer(lbl_3_data_10ACC[4], 0, 0, 0);
            break;
        case 5:
            *(void**)(lbl_8036E548 + 8) = ARAMTransfer(lbl_3_data_10ACC[5], 0, 0, 0);
            break;
        case 6:
            *(void**)(lbl_8036E548 + 8) = ARAMTransfer(lbl_3_data_10ACC[6], 0, 0, 0);
            break;
        default:
            return -1;
    }
    fn_800B0A5C_insertQueue(fn_3_B99E4, 0);
    lbl_3_common_bss_350E4[0x6A] = 1;
    return 1;
    }
    return 0;
}

// .text:0x000B99E4 size:0x1D0 mapped:0x806F8A78
void fn_3_B99E4(void) {
    if ((s32)lbl_803C6CF8[0x715] == 1) {
        lbl_3_common_bss_350E4[0x6A] = 0;
        fn_3_B9FB8(g_d_GameSettings.StadiumID, *(void**)(lbl_8036E548 + 8));
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x000B98E8 size:0xFC mapped:0x806F897C
void fn_3_B98E8(void* p) {
    StadHdr** pp = (StadHdr**)p;
    f32 one;
    f32 zero;
    s32 off;
    u32 i;
    zero = 0.0f;
    one = 1.0f;
    i = 0;
    off = 0;
    for (; i < (*pp)->count; i++) {
        StadEnt* e = *(StadEnt**)((u8*)(*pp)->list + off);
        e->extra = _OSAllocFromHeap(0x20, 0x1C);
        off += 4;
        e->extra->a = zero;
        e->extra->b = zero;
        e->extra->c = one;
        e->extra->d = 0;
        e->extra->e = 0;
        e->extra->f = 0;
        e->extra->g = 1;
        e->extra->h = 1;
        e->extra->i = 0;
    }
}

// .text:0x000B97DC size:0x10C mapped:0x806F8870
void fn_3_B97DC(u8* p, void* f) {
    if (p == NULL || f == NULL) {
        return;
    }
    *(void**)(p + 4) = f;
    *(u16*)(p + 0xE) = 0;
    *(f32*)(p + 0x5C) = 0.0f;
    p[0x58] = 1;
    p[0x59] = (f != NULL);
    p[0x5A] = (f != NULL);
    *(f32*)(p + 0x60) = 0.0f;
    p[0x5B] = 3;
    *(f32*)(p + 0x5C) = 0.0f;
    p[0x59] = 1;
    *(f32*)(p + 0x54) = 1.0f;
    p[0x5A] = 1;
    *(u32*)(p + 0x68) = 0;
    p[0x58] = 1;
    if (p[0x58] != 0) {
        ACTSetAnimation(*(void**)p, *(void**)(p + 4), 0, *(u16*)(p + 0xE), 0.0f, *(f32*)(p + 0x60));
        fn_800B4BC8(*(void**)p, 1);
    }
    if (p[0x59] != 0) {
        fn_800B4CA0(*(void**)p, *(f32*)(p + 0x5C));
    }
    if (p[0x5A] != 0) {
        fn_800B4C04(*(void**)p, *(f32*)(p + 0x54));
    }
    if (p[0x5B] & 1) {
        fn_800B4AFC(*(void**)p, p[0x5B] & 1);
    }
}

// .text:0x000B97C8 size:0x14 mapped:0x806F885C
void fn_3_B97C8(void* p) {
    if (p != NULL) {
        lbl_3_bss_9940 = p;
    }
}

// .text:0x000B95EC size:0x1DC mapped:0x806F8680
void fn_3_B95EC(void) {
    u8 n;
    u8* c;
    u8* d;
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
    if (lbl_3_bss_9940 != 0) {
        ((void (*)(void))lbl_3_bss_9940)();
        lbl_3_bss_9940 = 0;
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_8001B200();
        if (*(void**)(lbl_3_common_bss_350E4 + 0x14) != 0) {
            fn_800ACFB0(*(void**)(lbl_3_common_bss_350E4 + 0x14));
        }
        if (*(void**)(lbl_3_common_bss_350E4 + 0x48) != 0) {
            fn_800ACFB0(*(void**)(lbl_3_common_bss_350E4 + 0x48));
        }
        if (*(void**)(lbl_3_common_bss_350E4 + 0x4) != 0) {
            fn_800ACFB0(*(void**)(lbl_3_common_bss_350E4 + 0x4));
        }
        if (*(void**)(lbl_3_common_bss_350E4 + 0x0) != 0) {
            fn_800ACFB0(*(void**)(lbl_3_common_bss_350E4 + 0x0));
        }
        d = lbl_8036E548;
        if (*(void**)(d + 0x6C) != 0) {
            n = lbl_3_common_bss_350E4[0x6D];
            while (n != 0) {
                fn_800B4278(*(void**)(*(u8**)(d + 0x6C) + n * 0x90 - 0x5C));
                n--;
            }
            fn_800ACFB0(*(void**)(d + 0x6C));
            *(void**)(d + 0x6C) = 0;
        }
        if (*(void**)(lbl_3_common_bss_350E4 + 0x34) != 0) {
            fn_800ACFB0(*(void**)(lbl_3_common_bss_350E4 + 0x34));
        }
        c = lbl_3_common_bss_350E4;
        n = 4;
        while (n != 0) {
            if (((void**)(c + 0x1C))[n] != 0) {
                fn_800ACFB0(((void**)(c + 0x1C))[n]);
            }
            n--;
        }
        if (*(void**)(lbl_3_common_bss_350E4 + 0x38) != 0) {
            fn_800ACFB0(*(void**)(lbl_3_common_bss_350E4 + 0x38));
        }
        lbl_8036E548[0x3088] = 0;
        fn_3_C1964();
        fn_3_16E328();
        fn_800528B4();
        fn_8001E474();
        lbl_3_bss_1902 = 0;
        memset(lbl_3_common_bss_350E4, 0, 0x70);
        lbl_3_bss_1901 = 1;
    }
}

// .text:0x000B9534 size:0xB8 mapped:0x806F85C8
void* fn_3_B9534(u32 w, u32 h, void* tex) {
    if (lbl_3_bss_1902 != 0 || tex == 0) {
        return 0;
    }
    lbl_3_bss_1902 = 1;
    GXInitTexObj(tex, lbl_3_bss_1940, (u16)w, (u16)h, 3, 1, 1, 0);
    GXInitTexObjLOD(tex, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    return lbl_3_bss_1940;
}

// .text:0x000B9524 size:0x10 mapped:0x806F85B8
void fn_3_B9524(void) {
    lbl_3_bss_1902 = 0;
}

// .text:0x000B9510 size:0x14 mapped:0x806F85A4
void fn_3_B9510(s32 i) {
    lbl_3_data_11168[i] = 1;
}

// .text:0x000B950C size:0x4 mapped:0x806F85A0
void fn_3_B950C(void) {
    return;
}

// .text:0x000B93CC size:0x140 mapped:0x806F8460
void fn_3_B93CC(void) {
    s32 i;
    if (g_d_GameSettings._55 == 0) {
        if (g_GameLogic[0x11E] == 0) {
            *(s16*)(lbl_3_common_bss_350E4 + 0x66) = rand();
        }
        if (lbl_80366158._28 != 0) {
            if (g_d_GameSettings.GameModeSelected == 2 && *(void**)(lbl_3_common_bss_350E4 + 0x1C) != NULL) {
                (*(void (**)(void))(lbl_3_common_bss_350E4 + 0x1C))();
            }
        } else {
            if (*(void**)(lbl_3_common_bss_350E4 + 0x18) != NULL) {
                (*(void (**)(void))(lbl_3_common_bss_350E4 + 0x18))();
            }
            if (*(void**)(lbl_3_common_bss_350E4 + 0x1C) != NULL) {
                (*(void (**)(void))(lbl_3_common_bss_350E4 + 0x1C))();
            }
            if (g_GameLogic[0x11E] == 0) {
                fn_800638CC();
            }
            for (i = 0; i < *(s32*)(lbl_3_common_bss_350E4 + 0x30); i++) {
                if (((StadObjFn**)lbl_3_common_bss_350E4)[0][i].fn != NULL) {
                    ((StadObjFn**)lbl_3_common_bss_350E4)[0][i].fn(&((StadObjFn**)lbl_3_common_bss_350E4)[0][i]);
                }
            }
        }
    }
}

// .text:0x000B93C8 size:0x4 mapped:0x806F845C
void fn_3_B93C8(s32 unused) {
    return;
}

// .text:0x000B93C4 size:0x4 mapped:0x806F8458
void fn_3_B93C4(void) {
    return;
}

// .text:0x000B939C size:0x28 mapped:0x806F8430
void fn_3_B939C(void) {
    lbl_3_common_bss_350E4[0x6C] = (g_GameLogic[0x11E] == 2);
}

// .text:0x000B91C8 size:0x1D4 mapped:0x806F825C
void* fn_3_B91C8(s32 type, s32 idx0, Mtx arg) {
    s32 idx = idx0;
    if (type == 1) {
        return fn_3_C823C(idx, arg);
    }
    if (type == 2) {
        if (*(s16*)(g_Ball + 0x1B7A) >= 2) {
            return 0;
        }
        CTRLBuildMatrix(&sStadiumMgr.objs[idx].ctrl, arg);
        return sStadiumMgr.objs[idx].unk78;
    }
    if (type == 3) {
        if ((g_Ball[0x1BE8] == 0xB) | (g_Ball[0x1BE8] == 0xC)) {
            return 0;
        }
        return fn_3_E4BE8(idx, arg);
    }
    if (type == 4) {
        if ((*(s16*)(g_Ball + 0x1B7A) >= 2) | (g_Ball[0x1BE8] == 0xB) | (g_Ball[0x1BE8] == 0xC)) {
            return 0;
        }
        CTRLBuildMatrix(&sStadiumMgr.objs[idx].ctrl, arg);
        return sStadiumMgr.objs[idx].unk78;
    }
    if (type == 5) {
        if (*(s16*)(g_Ball + 0x1B7A) >= 2) {
            return 0;
        }
        return fn_3_F6504(idx, arg);
    }
    if (type == 6) {
        return fn_3_E751C(idx, arg);
    }
    CTRLBuildMatrix(&sStadiumMgr.objs[idx].ctrl, arg);
    return sStadiumMgr.objs[idx].unk78;
}

// .text:0x000B916C size:0x5C mapped:0x806F8200
void processStadiumObjectFunction(int stadium, void* a, int b, void* c) {
    StadObjList* l = (StadObjList*)lbl_3_common_bss_350E4;
    s32 i = (s32)a;
    if (i < l->count) {
        void (*f)(int, int, void*) = l->objs[i].fn;
        if (f != 0) {
            f(i, b, c);
        }
    }
}

// .text:0x000B9124 size:0x48 mapped:0x806F81B8
void fn_3_B9124(void) {
    memcpy(*(void**)(lbl_3_common_bss_350E4 + 4), *(void**)lbl_3_common_bss_350E4, *(s32*)(lbl_3_common_bss_350E4 + 0x30) * 0xE8);
    *(s16*)(lbl_3_common_bss_350E4 + 0x68) = *(s16*)(lbl_3_common_bss_350E4 + 0x66);
}

// .text:0x000B908C size:0x98 mapped:0x806F8120
void fn_3_B908C(void) {
    if (lbl_3_bss_1904 == NULL) {
        u8* c = lbl_3_common_bss_350E4;
        lbl_3_bss_1904 = _OSAllocFromHeap(0x20, *(s32*)(c + 0x30) * 0xE8);
        memcpy(lbl_3_bss_1904, *(void**)lbl_3_common_bss_350E4, *(s32*)(c + 0x30) * 0xE8);
    }
    memcpy(*(void**)lbl_3_common_bss_350E4, *(void**)(lbl_3_common_bss_350E4 + 4), *(s32*)(lbl_3_common_bss_350E4 + 0x30) * 0xE8);
    *(s16*)(lbl_3_common_bss_350E4 + 0x66) = *(s16*)(lbl_3_common_bss_350E4 + 0x68);
}

// .text:0x000B902C size:0x60 mapped:0x806F80C0
void fn_3_B902C(void) {
    if (lbl_3_bss_1904 != NULL) {
        memcpy(*(void**)lbl_3_common_bss_350E4, lbl_3_bss_1904, *(s32*)(lbl_3_common_bss_350E4 + 0x30) * 0xE8);
        fn_800ACFB0(lbl_3_bss_1904);
        lbl_3_bss_1904 = NULL;
    }
}

// .text:0x000B8C08 size:0x424 mapped:0x806F7C9C
void fn_3_B8C08(MtxPtr view) {
    Vec shadowPos;
    Mtx world;
    Mtx modelView;
    StadiumObj* obj;
    GameActor* actor;
    SortEnt* e;
    s32 i;

    if (sStadiumMgr.data == NULL) {
        return;
    }
    fn_3_38E8(fn_3_B8828);
    fn_8001E460((void (*)(MtxPtr, s32, s32))fn_3_B8828);
    for (i = 0; i < sStadiumMgr.count; i++) {
        obj = &sStadiumMgr.objs[i];
        if (obj->visible && obj->actor != NULL) {
            actor = obj->actor->actor;
            fn_800B2BFC(obj->actor->actor, obj->actor->unk64, obj->actor->unk66);
            fn_800B3F20(actor);
            fn_800B313C(actor);
            CTRLBuildMatrix(&obj->ctrl, world);
            PSMTXCopy(world, obj->mtx);
            PSMTXConcat(view, obj->mtx, modelView);
            if (obj->attached != 0) {
                if (obj->attachJoint == -1) {
                    fn_800117CC(obj->mtx, view, obj->mtx);
                } else {
                    fn_800116DC((struct CharActor*)obj->actor, modelView, obj->attachJoint); // TODO type
                }
            }
            obj->viewFlags = (obj->viewFlags & 0xFC) | fn_800B3C04(0, obj->actor->actor, modelView);
            if (obj->castShadow) {
                Vec pos = {0.0f, 0.0f, 0.0f};
                PSMTXMultVec(world, &pos, &pos);
                shadowPos = pos;
                fn_800BEA04(shadowPos);
            }
            if (obj->shapeAnim != NULL && lbl_80366158._28 == 0 && obj->viewFlags != 0) {
                fn_80024DB0(&obj->shapeAnim->anim);
                fn_80024FA4((ShapeModel**)obj->actor, obj->shapeAnim->shape, &obj->shapeAnim->anim, -1); // TODO type
            }
        }
    }
    if (g_d_GameSettings.StadiumID == 2 && g_d_GameSettings.GameModeSelected != 7) {
        fn_3_D55EC(view, sStadiumMgr.sort);
    } else if (g_d_GameSettings.StadiumID == 5 && g_d_GameSettings.GameModeSelected != 7) {
        fn_3_F6084(view, sStadiumMgr.sort);
    } else if (g_d_GameSettings.StadiumID == 6) {
        fn_3_E7388(view, sStadiumMgr.sort);
    } else {
        fn_3_B867C(view, sStadiumMgr.sort);
        if (sStadiumMgr.sortByDepth) {
            Vec ballPos;
            lbl_3_bss_1908 = g_GameLogic[0x11E] == 2 ? 0.25f : 0.0f; // TODO type: g_GameLogic field 0x11E
            memcpy(&ballPos, g_Ball, sizeof(Vec)); // the ball position
            PSMTXMultVec(view, &ballPos, &ballPos);
            for (i = 0; i < sStadiumMgr.count; i++) {
                e = &sStadiumMgr.sort[i];
                if (sStadiumMgr.objs[e->idx].visible) {
                    if (e->z < 2.0f + ballPos.z) {
                        e->z = 1.0f;
                    } else if (e->z > 22.0f + ballPos.z) {
                        e->z = 1.0 - (1.0f - lbl_3_bss_1908);
                    } else {
                        e->z = 1.0 - (1.0f - lbl_3_bss_1908) *
                                                       ((e->z - (2.0f + ballPos.z)) / 20.0f);
                    }
                }
            }
        } else {
            for (i = 0; i < sStadiumMgr.count; i++) {
                sStadiumMgr.sort[i].z = 1.0f;
            }
        }
    }
}

// .text:0x000B8828 size:0x3E0 mapped:0x806F78BC
void fn_3_B8828(MtxPtr view, s32 translucent, u32 layer) {
    Light light;
    Mtx inv;
    Mtx modelView;
    Vec dir;
    GXColor drawColor;
    GXColor ambient;
    GXColor color;
    LitPos* lights;
    StadiumObj* obj;
    s32 i;
    s32 j;

    drawColor = lbl_800F7478[g_d_GameSettings._54].ambient;
    ambient = drawColor;
    lights = lbl_80367318;
    if (lbl_8036E548[0x3088] == 0) { // TODO type: CharMgr._3088 (stadium loaded)
        return;
    }
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < 4; i++) {
        if (sStadiumMgr.lights[i] != NULL) {
            LITInitAttn(sStadiumMgr.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            LITInitPos(sStadiumMgr.lights[i], lights[i].x, lights[i].y, lights[i].z);
            color = lights[i].color;
            LITInitColor(sStadiumMgr.lights[i], &color);
            dir.x = lights[i].x;
            dir.y = lights[i].y;
            dir.z = lights[i].z;
            if (PSVECMag(&dir)) {
                PSVECNormalize(&dir, &dir);
                LITInitDir(sStadiumMgr.lights[i], dir.x, dir.y, dir.z);
            }
        }
    }
    GXSetProjection(fn_80052768_getCamera(fn_8005268C())->proj, GX_PERSPECTIVE);
    for (i = 0; i < sStadiumMgr.count; i++) {
        obj = &sStadiumMgr.objs[sStadiumMgr.sort[i].idx];
        if (obj->visible && obj->actor != NULL && layer == obj->layer &&
            (layer != 1 || translucent == obj->depthFade)) {
            PSMTXConcat(view, obj->mtx, modelView);
            if (obj->depthFade) {
                drawColor.a = obj->alpha * sStadiumMgr.sort[i].z;
            } else {
                drawColor.a = obj->alpha;
            }
            fn_800BD2CC(1, drawColor);
            for (j = 0; j < 4; j++) {
                LITXForm(sStadiumMgr.lights[j], view);
            }
            CTRLBuildMatrix(&obj->ctrl, inv);
            PSMTXInverse(inv, inv);
            light = *sStadiumMgr.lights[0];
            PSMTXMultVecSR(inv, &light.direction, &light.direction);
            fn_800B9AA8(&light);
            obj->actor->actor->flags = obj->viewFlags;
            if (obj->customZ) {
                GXSetZMode(obj->zCompare, obj->zAlways ? GX_ALWAYS : GX_LEQUAL, obj->zUpdate);
            } else if (translucent) {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            } else {
                GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
            }
            if (obj->preDraw != NULL) {
                obj->preDraw(obj);
            }
            fn_800BDA94(obj->actor, modelView);
            for (j = 0; j < 16; j++) {
                if (lbl_3_data_11168[j] != 0) {
                    GXSetTevDirect(j);
                    lbl_3_data_11168[j] = 0;
                }
            }
            fn_800BD2CC(1, ambient);
            if (obj->postDraw != NULL) {
                obj->postDraw(obj);
            }
        }
    }
    fn_800B9AA8(sStadiumMgr.lights[0]);
}

// .text:0x000B867C size:0x1AC mapped:0x806F7710
void fn_3_B867C(void* mtx, SortEnt* out) {
    StadiumObjMgr* c = &sStadiumMgr;
    Vec v;
    StadiumObj* obj;
    s32 i;
    s32 k;
    s32 n;
    void* tmp;
    if (c->sortByDepth != 0) {
        n = 0;
        obj = &c->objs[c->count - 1];
        i = c->count - 1;
        do {
            if (!obj->visible) {
                out[n].z = -512.0f;
                out[n].idx = i;
                n++;
            }
            obj--;
        } while (i-- != 0);
        k = c->count;
        i = c->count - 1;
        obj = &sStadiumMgr.objs[i];
        do {
            if (obj->visible) {
                if (obj->depthFade) {
                    CTRLGetTranslation(&obj->ctrl, &v.x, &v.y, &v.z);
                    PSMTXMultVec(mtx, &v, &v);
                    k--;
                    out[k].z = v.z;
                    out[k].idx = i;
                } else {
                    out[n].z = -512.0f;
                    out[n].idx = i;
                    n++;
                }
            }
            obj--;
        } while (i-- != 0);
        tmp = fn_800ACF34(0x20, (c->count - k) * 8);
        fn_800C07BC(out + k, tmp, c->count - k, 8, (s32 (*)(const void*, const void*))fn_3_B8658);
        fn_800ACF14(tmp);
    } else {
        for (i = 0; i < c->count; i++) {
            out[i].idx = i;
        }
    }
}

// .text:0x000B8658 size:0x24 mapped:0x806F76EC
s32 fn_3_B8658(f32* a, f32* b) {
    f32 x = *a;
    f32 y = *b;
    if (x < y) {
        return -1;
    }
    return x > y;
}

// .text:0x000B85DC size:0x7C mapped:0x806F7670
void fn_3_B85DC(s32 i, void* a, void* b) {
    u8* c = lbl_3_common_bss_350E4;
    memcpy(a, *(u8**)(c + 0x48) + i * 0x18, 0xC);
    memcpy(b, *(u8**)(c + 0x48) + (i * 2 + 1) * 0xC, 0xC);
}

// .text:0x000B85A8 size:0x34 mapped:0x806F763C
u32 fn_3_B85A8(int idx, u32** out) {
    *out = *(u32**)(lbl_3_common_bss_350E4 + 0x44) + *(u16*)(*(u8**)(lbl_3_common_bss_350E4 + 0x40) + idx * 2);
    return (*(u32**)(lbl_3_common_bss_350E4 + 0x3C))[idx];
}

// .text:0x000B8574 size:0x34 mapped:0x806F7608
void fn_3_B8574(void) {
    lbl_3_bss_1910[0] = 10000.0f;
    lbl_3_bss_1910[1] = 10000.0f;
    lbl_3_bss_1910[2] = 10000.0f;
    lbl_3_bss_1910[3] = -10000.0f;
    lbl_3_bss_1910[4] = -10000.0f;
    lbl_3_bss_1910[5] = -10000.0f;
}

// .text:0x000B8464 size:0x110 mapped:0x806F74F8
void fn_3_B8464(void* mtx, void* obj) {
    f32 out[3];
    u16 cnt;
    s32 n;
    u8* p = *(u8**)((u8*)obj + 8);
    while (1) {
        cnt = *(u16*)(p + 2);
        if (cnt == 0) {
            break;
        }
        if (p[1] != 0) {
            n = cnt + 2;
        } else {
            n = cnt * 3;
        }
        p += 4;
        do {
            PSMTXMultVec(mtx, (Vec*)p, (Vec*)out);
            p += 0x10;
            if (lbl_3_bss_1910[0] > out[0]) {
                lbl_3_bss_1910[0] = out[0];
            }
            if (lbl_3_bss_1910[1] > out[1]) {
                lbl_3_bss_1910[1] = out[1];
            }
            if (lbl_3_bss_1910[2] > out[2]) {
                lbl_3_bss_1910[2] = out[2];
            }
            if (lbl_3_bss_1910[3] < out[0]) {
                lbl_3_bss_1910[3] = out[0];
            }
            if (lbl_3_bss_1910[4] < out[1]) {
                lbl_3_bss_1910[4] = out[1];
            }
            if (lbl_3_bss_1910[5] < out[2]) {
                lbl_3_bss_1910[5] = out[2];
            }
            n--;
        } while (n != 0);
    }
}

// .text:0x000B8414 size:0x50 mapped:0x806F74A8
void fn_3_B8414(void* a, void* b) {
    memcpy(a, lbl_3_bss_1910, 0xC);
    memcpy(b, lbl_3_bss_1910 + 3, 0xC);
}

// .text:0x000B8298 size:0x17C mapped:0x806F732C
void fn_3_B8298(void) {
    s32 off;
    u32 i;
    u8* c;
    void* pp;
    u8* e;
    switch (g_d_GameSettings.StadiumID) {
        case 3:
            fn_8003A548(fn_3_B80D0);
            break;
    }
    c = lbl_3_common_bss_350E4;
    i = 0;
    off = 0;
    for (; i < *(u32*)(c + 0x30); i++) {
        e = *(u8**)c + off;
        if (((e[0x90] >> 7) & 1) && *(void**)(e + 0x74) != 0 && e[0x9A] != 0) {
            lbl_3_bss_190C = (StadiumObj*)e;
            fn_3_B8184(*(void**)(e + 0x74), *(u8**)((u8*)fn_800BF068() + 0x14) + 0x40);
        }
        off += 0xE8;
    }
    fn_8003A548(NULL);
}

// .text:0x000B828C size:0xC mapped:0x806F7320
void fn_3_B828C(StadiumObj* val) {
    lbl_3_bss_190C = val;
}

// .text:0x000B827C size:0x10 mapped:0x806F7310
StadiumObj* fn_3_B827C(void) {
    return lbl_3_bss_190C;
}

// .text:0x000B8184 size:0xF8 mapped:0x806F7218
void fn_3_B8184(void* pp, void* cam) {
    Mtx m2;
    Mtx m;
    DspObj* o;
    DspObj* n;
    CTRLBuildMatrix(&lbl_3_bss_190C->ctrl, m);
    if (!(m[1][3] > 0.0f) || g_d_GameSettings.StadiumID != 1) {
        PSMTXConcat(cam, m, m2);
        o = *(DspObj**)pp;
        n = o->child;
        if (o->w14 != 0) {
            if (o->w7C != 0) {
                fn_8003A8A0(o->w14, m2, 1);
            } else {
                DOVARenderSkin(o->w14, m2, o->w64, o->w68, 0, 0);
            }
        }
        while (n != 0) {
            if (n->w14 != 0) {
                DOSetWorldMatrix(n->w14, n->wEC);
                fn_8003A8A0(n->w14, m2, 0);
            }
            n = n->next;
        }
    }
}

// .text:0x000B80D0 size:0xB4 mapped:0x806F7164
void fn_3_B80D0(void) {
    GXSetBlendMode(1, 4, 5, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorIn(0, 0xA, 0xF, 0xF, 0xF);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(0, 4, 7, 7, 7);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
}

// .text:0x000B7FC8 size:0x108 mapped:0x806F705C
s32 fn_3_B7FC8(s32 a, s32 b) {
    V3 v = {0.0f, 0.0f, 37.0f};
    f32 ang;
    ang = 0.017453292f * lbl_3_data_11178[rand() % 5];
    v.x = 100.0f * (f32)cos(ang) + v.x;
    v.y += -30.0f;
    v.z = 100.0f * (f32)sin(ang) + v.z;
    return fn_3_8BBC4(a, (f32*)&v, NULL, b);
}

