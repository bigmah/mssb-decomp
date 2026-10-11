#ifndef __MAIN_FILE_8000F150_H__
#define __MAIN_FILE_8000F150_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_80024184.h" // TexImage, TexArchive
#include "main/file_8000BA3C.h" // QuadVtx
#include "main/file_80011640.h" // CharMgr, CharActor

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
    /*0x5C*/ u32 _5C;
    /*0x60*/ u8 _60[0x4];
    /*0x64*/ u16 _64;
    /*0x66*/ u8 _66;
    /*0x67*/ u8 layer;
    /*0x68*/ u8 _68;
    /*0x69*/ u8 _69;
    /*0x6A*/ u8 _6A[0x72 - 0x6A];
    /*0x72*/ s16 _72;
} LayoutObj;

typedef struct LayoutSlot {
    /*0x0*/ LayoutObj* obj;
    /*0x4*/ u32 _04;
} LayoutSlot;

extern LayoutSlot lbl_80371C30[];

// Also the queue item that lbl_803CC1B8 points at.
typedef struct LayoutGroup {
    /*0x00*/ void (*callback)(void);
    /*0x04*/ u8 _04[0x10];
    /*0x14*/ u16 start;
    /*0x16*/ u16 count;
    /*0x18*/ u16 timer;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 textIndex;
    /*0x1E*/ u16 _1E;
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
    /*0x7B8*/ TexImage* fontTexObj[4];
    /*0x7C8*/ TexImage* iconTexObj[9];
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
GameActor** fn_800111D8(CharActor* actor);
CharActor* fn_800111FC(CharActor* actor, s32 second);
void fn_80011358(s32 index, s32 kind);
void fn_80011468(void);

CharActor* fn_80011570(void); // actor being drawn (lbl_803CBC18)

void fn_800115C8(s8 index);

void fn_80011604(s8 index, DOTevHook value);

#endif
