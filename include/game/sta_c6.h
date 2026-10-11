#ifndef __GAME_sta_c6_H_
#define __GAME_sta_c6_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_800BD8C4.h" // ActorObject, GameActor, GameControl

// Toy Field stadium objects.
// Object kinds (StaC6Obj.kind):
//   0-7   field panels (StaC6Spot, coloured by StaC6Data.kindColors[kind])
//   8-15  wall panels (StaC6Pad, coloured by StaC6Data.kindColors[kind - 8])
//   16-22 the 7 targets (StaC6Data2.hit flags)
//   23-26 other scenery; 27 = unused / end of list

// One field panel spot (StaC6Data.spots).
typedef struct StaC6Spot {
    /*0x00*/ Vec pos;
    /*0x0C*/ f32 rotY;
    /*0x10*/ u8 kind;  // 27: end of the list
    /*0x11*/ u8 _11;
    /*0x12*/ u8 group; // draw group (fn_3_E763C)
    /*0x13*/ u8 _13;
} StaC6Spot; // size: 0x14

// One wall panel (StaC6Data.pads).
typedef struct StaC6Pad {
    /*0x0*/ u8 kind; // 27: end of the list
    /*0x1*/ u8 _1;
    /*0x2*/ u8 group;
    /*0x3*/ u8 _3;
} StaC6Pad; // size: 0x4

// lbl_3_data_19024
typedef struct StaC6Data {
    /*0x000*/ u8 kindColors[8][3][4]; // [kind][0 miss, 1 idle, 2 hit] RGBA
    /*0x060*/ u8 bodyColors[3][4];    // 0 miss, 1 idle, 2 hit
    /*0x06C*/ StaC6Spot spots[4][16]; // [layout]: 2, 3, 4 players, 2-4 players (_19A6 > 1)
    /*0x56C*/ StaC6Pad pads[4][8];
} StaC6Data; // size: 0x5EC

// lbl_3_data_196B4
typedef struct StaC6Data2 {
    /*0x00*/ u8 hit[8];            // targets 16-22 hit (see also fn_3_E587C)
    /*0x08*/ Vec targetPos[7];
    /*0x5C*/ f32 targetRotY[7];
    /*0x78*/ u32 kindResult[16];   // toy field result that lights panel kind n
} StaC6Data2; // size: 0xB8

// One 0xE8-byte entry of lbl_3_common_bss_350E4.objs.
typedef struct StaC6Obj {
    /*0x00*/ GameControl ctrl;
    /*0x44*/ u8 _44[0x74 - 0x44];
    /*0x74*/ ActorObject* actorObj;
    /*0x78*/ void* shadow;          // passed to fn_3_B8464
    /*0x7C*/ void (*update)(struct StaC6Obj* o);
    /*0x80*/ void (*onHit)(s32 idx);
    /*0x84*/ void (*preDraw)(struct StaC6Obj* o);
    /*0x88*/ void (*postDraw)(struct StaC6Obj* o);
    /*0x8C*/ s32 _8C;
    /*0x90*/ u8 visible : 1;
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 bit5 : 1;
    /*0x90*/ u8 bits : 5;
    /*0x91*/ u8 _91;
    /*0x92*/ u8 _92;
    /*0x93*/ u8 _93;
    /*0x94*/ s16 _94;
    /*0x96*/ s16 _96;
    /*0x98*/ u8 _98;
    /*0x99*/ u8 _99[3];
    /*0x9C*/ ActorObject* subObj;   // coloured overlay model, may be NULL
    /*0xA0*/ s32 _A0;
    /*0xA4*/ u8 color[4];           // overlay colour (RGBA)
    /*0xA8*/ u8* colorTo;
    /*0xAC*/ u8* colorFrom;
    /*0xB0*/ u8* colorHit;
    /*0xB4*/ u8* colorIdle;
    /*0xB8*/ u8* colorMiss;
    /*0xBC*/ u8* bodyColor;
    /*0xC0*/ u8 index;
    /*0xC1*/ u8 kind;
    /*0xC2*/ u8 lit;
    /*0xC3*/ u8 slot;               // wall panels: index into StaC6Data2 / lbl_3_data_19644
    /*0xC4*/ u8 flagIdx;            // wall panels: index into StaC6Data2.hit
    /*0xC5*/ u8 _C5[0xE8 - 0xC5];
} StaC6Obj; // size: 0xE8

// lbl_3_common_bss_350E4: the stadium object list.
typedef struct StaC6List {
    /*0x00*/ StaC6Obj* objs;
    /*0x04*/ StaC6Obj* objsBackup;
    /*0x08*/ u8 _08[0x18 - 0x08];
    /*0x18*/ void (*draw)(void);
    /*0x1C*/ void (*update)(void);
    /*0x20*/ void* lights[4];
    /*0x30*/ s32 count;
    /*0x34*/ u32* fileIdx;          // indices into the stadium file table
    /*0x38*/ void** files;
    /*0x3C*/ u32* groupCount;       // per draw group: number of objects
    /*0x40*/ u16* groupStart;       // per draw group: first entry in groupObjs
    /*0x44*/ s32* groupObjs;
    /*0x48*/ Vec* groupBounds;      // per draw group: min and max corner
    /*0x4C*/ u8 _4C[0x64 - 0x4C];
    /*0x64*/ s16 numGroups;
    /*0x66*/ u8 _66[0x6C - 0x66];
    /*0x6C*/ u8 _6C;
    /*0x6D*/ u8 numActorObjs;
} StaC6List;

typedef struct E7388Pair { f32 f; s32 i; } E7388Pair;

void fn_3_E59B4(StaC6Obj* o);
void fn_3_E5A1C(StaC6Obj* o);
void fn_3_E5A84(StaC6Obj* o);
void fn_3_E5CBC(StaC6Obj* o, f32 t);
s32 fn_3_E5E14(u8* p);
void fn_3_E5E70(u8* out, u8 fmt, void* src);
void fn_3_E5FEC(StaC6Obj* o);
void fn_3_E6410(StaC6Obj* o);
u32* fn_3_E64A8(void);
void fn_3_E6528(StaC6Obj* o);
void fn_3_E6578(StaC6Obj* o);
void fn_3_E6638(StaC6Obj* o);
void fn_3_E6684(StaC6Obj* o);
void fn_3_E671C(StaC6Obj* o);
void fn_3_E6798(StaC6Obj* o);
void fn_3_E67F4(void);
void fn_3_E68A8(StaC6Obj* o);
void fn_3_E698C(StaC6Obj* o);
void fn_3_E6A48(StaC6Obj* o);
void fn_3_E6D90(StaC6Obj* o);
void fn_3_E7350(void);
void fn_3_E7364(s32 i);
void fn_3_E7388(s32 unused, E7388Pair* out);
void fn_3_E7424(void);
void* fn_3_E751C(s32 idx, Mtx m);
void fn_3_E763C(void);
void fn_3_E7A2C(StaC6Obj* o);
u8 fn_3_E7B20(void** files, u32* idx);
s32 fn_3_E8AC8(void);
void fn_3_E8B24(void** files);

#endif // !__GAME_sta_c6_H_
