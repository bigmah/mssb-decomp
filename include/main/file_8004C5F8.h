#ifndef __MAIN_FILE_8004C5F8_H__
#define __MAIN_FILE_8004C5F8_H__

#include "mssbTypes.h"
#include "static/UnknownHomes_Static.h"

// Yes/no confirmation dialog (lbl_803C5F74).
typedef struct ConfirmDialog {
    /*0x00*/ u8 active;
    /*0x01*/ u8 kind;      // dialog type, indexes the layout tables
    /*0x02*/ u8 cursor;    // 0 yes, 1 no
    /*0x03*/ u8 state;     // 0 open, 1 opening, 2 input, 3 closing, 4 closed
    /*0x04*/ u8 _04;
    /*0x05*/ u8 _05;
    /*0x06*/ s16 textRect[4];
    /*0x0E*/ s16 textRect2[4];
    /*0x16*/ u16 textIdx;
    /*0x18*/ u16 msg;
    /*0x1A*/ s8 table;     // < 0: no message
    /*0x1B*/ u8 hasTextRect;
    /*0x1C*/ u8 hasTextRect2;
    /*0x1D*/ u8 _1D;
    /*0x1E*/ u8 _1E;
    /*0x1F*/ u8 _1F[0xB4 - 0x1F];
} ConfirmDialog; // size: 0xB4

extern ConfirmDialog lbl_803C5F74;

// Per-dialog-kind layout (lbl_800FEAAC).
typedef struct DialogLayout {
    /*0x0*/ u16 anim0;
    /*0x2*/ u16 anim1;
    /*0x4*/ u16 msgId;
} DialogLayout; // size: 0x6

typedef struct DialogTables {
    /*0x00*/ DialogLayout layouts[11];
    /*0x42*/ u8 _42[2];
    /*0x44*/ u8 colors[12][2];
} DialogTables; // size: 0x5C

// Sprite layout descriptor handed to fn_80034E20 (only the fields used here).
typedef struct LayoutDesc {
    /*0x00*/ u8 _00[0x42];
    /*0x42*/ u16 _42;
} LayoutDesc;

// Character select state for up to 4 cursors (lbl_803C6028).
typedef struct RosterSelect {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ s16 cursor[4];   // slot index, < 0: inactive
    /*0x20*/ s16 charId[4];
    /*0x28*/ s8 slotOwner[0x24];
    /*0x4C*/ s8 slotLocked[0x24];
    /*0x70*/ u8 _70[4];
    /*0x74*/ u8 _74[4];
    /*0x78*/ u8 _78[4];
    /*0x7C*/ u8 state7C;
    /*0x7D*/ u8 state7D;
    /*0x7E*/ u8 state7E;
    /*0x7F*/ s8 _7F[4];
    /*0x83*/ u8 _83[9];
    /*0x8C*/ u8 _8C;
    /*0x8D*/ s8 _8D;
    /*0x8E*/ u8 _8E;
    /*0x8F*/ u8 _8F;
    /*0x90*/ u8 _90;
    /*0x91*/ u8 _91;
    /*0x92*/ u8 _92;
    /*0x93*/ u8 _93;
} RosterSelect; // size: 0x94

extern RosterSelect lbl_803C6028;

// lbl_800E8558 entries (one per character).
typedef struct CharTableEntry {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 id;
    /*0x2*/ u8 _2[4];
} CharTableEntry; // size: 0x6

// Character actor (only the fields used here).
typedef struct CharActor {
    /*0x000*/ u8 _000[0x44];
    /*0x044*/ f32 angle;
    /*0x048*/ u8 _048[0x62 - 0x48];
    /*0x062*/ s16 anim;
    /*0x064*/ u8 _064[0x252 - 0x64];
    /*0x252*/ u8 kind;
    /*0x253*/ u8 _253;
    /*0x254*/ s8 _254;
    /*0x255*/ u8 _255[0x25C - 0x255];
    /*0x25C*/ u8 _25C;
    /*0x25D*/ u8 _25D[0x276 - 0x25D];
    /*0x276*/ u8 flags;
    /*0x277*/ u8 meterAlpha;
    /*0x278*/ u8 _278[2];
    /*0x27A*/ u8 _27A;
} CharActor;

// Animation controller handed to fn_80052634.
typedef struct AnimCtl {
    /*0x00*/ s32 id;
    /*0x04*/ u8 _04[0x59 - 0x04];
    /*0x59*/ u8 hasFrame;
    /*0x5A*/ u8 _5A[2];
    /*0x5C*/ f32 frame;
} AnimCtl;

// Queue task created by fn_80052634.
typedef struct MeterTask {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ AnimCtl* anim;
    /*0x18*/ CharActor* actor;
    /*0x1C*/ u8 kind;
} MeterTask;

void fn_8004C9FC(void);

void fn_8004CA08(u32 value);

void fn_8004CA14(s32 table, s32 msg);

void fn_8004CA48(s16 a, s16 b, s16 c, s16 d);

s32 fn_8004CA6C(u16 buttons);

void fn_8004CCC0(void);

void fn_8004D0F0(void);

void fn_8004DB90(void);

void fn_8004E2EC(void);

void fn_8004CC18(void);

void fn_8004CC2C(void);

void fn_8004CC4C(u8 first, u8 second, u8 third, s32 selection, s16 value);

void fn_8004D460(s32 byId, s32 entry);

void fn_8004D4F0(s8 owner, s32 entry, s32 set);

void fn_8004E504(s32 byId, s32 entry0, s32 entry1, s32 entry2, s32 entry3);

void fn_8004E5B4(s8 owner, s32 entry, s32 set);

void fn_800506E8(s8 owner, s32 entry, s32 set);

void fn_8005240C(CharActor* actor, AnimCtl* anim);

void fn_80052634(CharActor* actor, AnimCtl* anim);

void fn_80052694(s32 index);

s32 fn_8004D93C(s32 arg);

void fn_8004D990(s8 arg0, s32 arg1, u8 table);

void fn_8004EEF4(s32 p0, s32 p1, s32 p2, s32 p3, s32 arg4);

s32 fn_8004EE84(s32 arg);

s32 fn_8004FD64(s32 player);

void fn_8004FDA0(s32 id);

s32 fn_80050F78(s32 arg);

void fn_80052188(void);

s32 fn_8005268C(void);

void* fn_80052734(s32 index);

camera_803c639c_s* fn_80052768_getCamera(int index);

s32 fn_800527BC(void);

void fn_80052798(s32 count);

#endif
