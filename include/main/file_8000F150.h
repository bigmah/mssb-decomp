#ifndef __MAIN_FILE_8000F150_H__
#define __MAIN_FILE_8000F150_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// One on-screen text string (0x38 bytes). Text is a u16 stream: values with
// bit 0x4000 set are control codes (low 14 bits), others are glyphs.
typedef struct TextEntry {
    /*0x00*/ MtxPtr mtx; // optional transform; NULL means screen space
    /*0x04*/ u16* text;
    /*0x08*/ u32 color;
    /*0x0C*/ u32 shadowColor; // 0 means no shadow
    /*0x10*/ u16 x;
    /*0x12*/ u16 y;
    /*0x14*/ s16 shadowX;
    /*0x16*/ s16 shadowY;
    /*0x18*/ s16 numbers[4];  // printed by control codes 0xF-0x12
    /*0x20*/ s16 strings[4];  // inserted by control codes 0x19-0x1C
    /*0x28*/ s16 charLimit;   // < 0: no typewriter limit
    /*0x2A*/ u8 state;        // 0 free, 1 hidden, 2 visible
    /*0x2B*/ u8 layer;
    /*0x2C*/ u8 fontSize;     // 0 large, 1/2 small
    /*0x2D*/ s8 charSpacing;
    /*0x2E*/ s8 lineSpacing;
    /*0x2F*/ u8 hAlign;
    /*0x30*/ u8 vAlign;
    /*0x31*/ u8 typeSpeed;
    /*0x32*/ u8 typeTimer;
    /*0x33*/ u8 _33;
    /*0x34*/ u8 finished;
    /*0x35*/ u8 _35;
    /*0x36*/ u8 _36;
    /*0x37*/ u8 _37;
} TextEntry; // size: 0x38

// Texture archive as used by convertTextureHeader: 0x20-byte records after a
// 4-byte header; record i's _1C picks the texture object for image i.
typedef struct TexRecord {
    /*0x00*/ u8 _00[0x1C];
    /*0x1C*/ u16 obj;
    /*0x1E*/ u16 _1E;
} TexRecord; // size: 0x20

typedef struct TexArchive {
    /*0x0*/ u32 _00;
    /*0x4*/ TexRecord recs[1];
} TexArchive;

#define TEX_ARCHIVE_OBJ(arc, i) (&(arc)->recs[(arc)->recs[i].obj])

typedef struct SpriteVtx {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
    /*0x08*/ f32 z;
    /*0x0C*/ u32 color;
    /*0x10*/ u16 s;
    /*0x12*/ u16 t;
} SpriteVtx; // size: 0x14

// Message table as loaded from disc; msgs[] hold file offsets until
// fn_800111B4 relocates them.
typedef struct MsgTable {
    /*0x0*/ u16 count;
    /*0x2*/ u16 _02;
    /*0x4*/ u16* msgs[1]; // [count]
} MsgTable;

// Layout (2D scene) object; owned by another unit, only the fields used here.
typedef struct LayoutObj {
    /*0x00*/ void* _00;
    /*0x04*/ u8 _04[0x8];
    /*0x0C*/ Mtx mtx;
    /*0x3C*/ u8 _3C[0x18];
    /*0x54*/ u32 flags;
    /*0x58*/ u32 color;
    /*0x5C*/ u8 _5C[0x8];
    /*0x64*/ u16 _64;
    /*0x66*/ u8 _66;
    /*0x67*/ u8 layer;
} LayoutObj;

typedef struct LayoutSlot {
    /*0x0*/ LayoutObj* obj;
    /*0x4*/ u32 _04;
} LayoutSlot;

extern LayoutSlot lbl_80371C30[];

typedef struct LayoutGroup {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 start;
    /*0x16*/ u16 count;
} LayoutGroup;

typedef struct TextOwner {
    /*0x00*/ void* object;
    /*0x04*/ u16 entry;
    /*0x06*/ u16 _06;
} TextOwner; // size: 0x8

typedef struct TextSystem {
    /*0x000*/ TextEntry entries[30];
    /*0x690*/ TextOwner owners[30];
    /*0x780*/ u32* fontArchive; // 4 file offsets to TexArchives
    /*0x784*/ TexArchive* fontTex[4];
    /*0x794*/ TexArchive* iconArchive;
    /*0x798*/ MsgTable* tables[7];
    /*0x7B4*/ u16** msgs;
    /*0x7B8*/ TexRecord* fontTexObj[4];
    /*0x7C8*/ TexRecord* iconTexObj[9];
    /*0x7EC*/ u16* _7EC;
    /*0x7F0*/ u16* _7F0;
    /*0x7F4*/ u16* _7F4;
    /*0x7F8*/ u16* _7F8;
    /*0x7FC*/ u8 scaleX;
    /*0x7FD*/ u8 scaleY;
    /*0x7FE*/ u8 padMask; // controllers allowed to skip text
    /*0x7FF*/ u8 _7FF;
} TextSystem; // size: 0x800

extern TextSystem lbl_80366B18;

// lbl_8036E548: character actors and their models (owned by other units;
// only the fields used here).
typedef struct ActorModelAnim {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ void* _14;
} ActorModelAnim;

typedef struct ActorModel {
    /*0x00*/ u8 _00[0x6];
    /*0x06*/ u16 animCount;
    /*0x08*/ u8 _08[0x10];
    /*0x18*/ ActorModelAnim** anims;
    /*0x1C*/ u8 _1C[0x7D];
    /*0x99*/ u8 _99;
} ActorModel;

typedef struct ActorModelSlot {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ ActorModel* model;
    /*0x38*/ u8 _38[0x58];
} ActorModelSlot; // size: 0x90

typedef struct ActorMgrActor {
    /*0x000*/ u8 _000[0x5C];
    /*0x05C*/ u32 _05C;
    /*0x060*/ u8 _060[0x2];
    /*0x062*/ s16 _062;
    /*0x064*/ s16 _064;
    /*0x066*/ s16 _066;
    /*0x068*/ u8 _068[0x4];
    /*0x06C*/ s16 _06C;
    /*0x06E*/ s16 _06E;
    /*0x070*/ u8 _070[0x13A];
    /*0x1AA*/ u16 anim;
    /*0x1AC*/ u8 _1AC[0xA6];
    /*0x252*/ s8 kind;
    /*0x253*/ u8 _253[0x2];
    /*0x255*/ s8 modelIndex;
    /*0x256*/ u8 _256[0x7];
    /*0x25D*/ u8 _25D;
    /*0x25E*/ u8 _25E;
    /*0x25F*/ u8 _25F;
    /*0x260*/ u8 _260;
    /*0x261*/ u8 _261;
    /*0x262*/ u8 _262;
    /*0x263*/ u8 _263;
    /*0x264*/ u8 _264;
    /*0x265*/ u8 _265;
    /*0x266*/ u8 _266;
    /*0x267*/ u8 _267;
    /*0x268*/ u8 _268;
    /*0x269*/ u8 _269;
    /*0x26A*/ u8 _26A;
    /*0x26B*/ u8 _26B;
    /*0x26C*/ u8 _26C;
    /*0x26D*/ u8 _26D;
    /*0x26E*/ u8 _26E;
    /*0x26F*/ u8 _26F[0xD];
} ActorMgrActor; // size: 0x27C

typedef struct ActorMgr {
    /*0x0000*/ u8 _0000[0x60];
    /*0x0060*/ ActorModelSlot* models;
    /*0x0064*/ ActorModelSlot* models2;
    /*0x0068*/ u8 _0068[0xB9C];
    /*0x0C04*/ ActorMgrActor actors[13];
    /*0x2C50*/ ActorMgrActor* active[13];
    /*0x2C84*/ u8 _2C84[0x4D0];
} ActorMgr; // size: 0x3154

typedef struct TextWindow {
    /*0x0*/ u8 _00[0x8];
    /*0x8*/ s32 size;
} TextWindow;

void fn_8000F150(TextWindow* window);
void fn_8000F3E8(s32 arg);
void somethingSetTexturePointer(void);
void fn_8000F4B8(s32 a, s32 b, s32 c, s32 d);
void fn_8000F534(LayoutObj* obj, s32 visible);
void fn_8000F8F4(LayoutGroup* group);
s32 fn_8000F988(LayoutGroup* group, s32 index, u16 arg2, s32 table, s32 msg, s32 shadow);
s32 fn_8000FA9C(s32 index);
void fn_8000FD54(s32 index, s16 a, s16 b, s16 c, s16 d);
void fn_8000FD78(s32 index, s16 a, s16 b, s16 c, s16 d);
void fn_8000FD9C(s32 index, s32 speed, s32 limit);
void fn_8000FE08(s32 index, s32 table, s32 msg);
void fn_8000FE54(void);
void fn_8000FEE8(s32 index);
s32 fn_8000FF04(s32 table, s32 msg, s16 x, s16 y, u8 layer, u32 color, u8 fontSize);
void fn_800100A4(s32 x, s32 y, u16 s, u16 t, u16 w, u32 color, s32 kind, MtxPtr mtx);
void DrawText(s32 index);
void DrawTextOnCondition(s32 layer);
void fn_80010FA0(void);
void fn_80011000(void);
void fn_80011140(void);
void fn_800111B4(MsgTable* table);
ActorModel** fn_800111D8(ActorMgrActor* actor);
ActorMgrActor* fn_800111FC(ActorMgrActor* actor, s32 second);
void fn_80011358(s32 index, s32 kind);
void fn_80011468(void);

u32 fn_80011570(void);

void fn_800115C8(s8 index);

void fn_80011604(s8 index, u32 value);

#endif
