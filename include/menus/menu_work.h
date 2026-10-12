#ifndef __MENUS_MENU_WORK_H__
#define __MENUS_MENU_WORK_H__

// Shared menus.rel types: the menu task/item views of the scene queue and the
// big menus work areas (lbl_2_bss_1A8234 .. lbl_2_bss_1A824C).

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Menu task (queue item) that owns a run of sprites in lbl_80371C30 starting
// at baseIdx. Only the fields used here.
typedef struct MenuTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct MenuTask* prev;
    /*0x08*/ struct MenuTask* next;
    /*0x0C*/ struct MenuTask* parent;
    /*0x10*/ s16 _10;
    /*0x12*/ u16 priority;
    /*0x14*/ u16 baseIdx;
    /*0x16*/ u16 count;
    /*0x18*/ u16 timerA;
    /*0x1A*/ u16 timerB;
    /*0x1C*/ u16 stateA;
    /*0x1E*/ u16 stateB;
    /*0x20*/ u8 _20[0x28 - 0x20];
    /*0x28*/ s8 step;
    /*0x29*/ u8 _29[0x80 - 0x29];
    /*0x80*/ s32 _80;
} MenuTask;

// One animated element of a menu task; func is called every frame with the
// owning task. state is driven by fn_2_53BC8's events.
typedef struct MenuItem {
    /*0x00*/ void (*func)(MenuTask* task, struct MenuItem* item);
    /*0x04*/ s16 state;
    /*0x06*/ s16 timer;
    /*0x08*/ s16 _08;
    /*0x0A*/ s16 _0A;
    /*0x0C*/ s16 key;    // event slot for fn_2_53BC8
    /*0x0E*/ s16 sprite; // index relative to task->baseIdx
    /*0x10*/ s16 _10;
    /*0x12*/ s16 _12;
    /*0x14*/ s16 _14;
} MenuItem;

#define MENU_SPRITE(task, item) (lbl_80371C30[(task)->baseIdx + (item)->sprite].obj)

// High-score style record: a value and two tags.
typedef struct MenuRecord {
    /*0x0*/ s32 value;
    /*0x4*/ s16 _4;
    /*0x6*/ s16 _6;
} MenuRecord; // size: 0x8

typedef struct MenuMission {
    /*0x0*/ u8 _0;
    /*0x1*/ s8 state; // star mission state (-2 / 0 / ...)
} MenuMission; // size: 0x2

// Star-mission state of one character (0x34 bytes); MenuCtx.chars.
typedef struct MenuRosterEntry {
    /*0x00*/ s8* limits; // indexed by [_4415 * 6 + _441C + 4]
    /*0x04*/ u8 _04[2];
    /*0x06*/ s8 value;
    /*0x07*/ u8 _07;
    /*0x08*/ MenuMission missions[10];
    /*0x1C*/ u8 _1C[0x31 - 0x1C];
    /*0x31*/ u8 _31;
    /*0x32*/ u8 _32[2];
} MenuRosterEntry; // size: 0x34

// A moving object of the menu world (0xD8 bytes); MenuCtx.entries.
typedef struct MenuEntry {
    /*0x00*/ Vec position;
    /*0x0C*/ Vec previousPosition;
    /*0x18*/ Vec velocity;
    /*0x24*/ Vec acceleration;
    /*0x30*/ f32 angle30;
    /*0x34*/ f32 angle34;
    /*0x38*/ f32 _38;
    /*0x3C*/ u8 _3C[0x10];
    /*0x4C*/ f32 heading;
    /*0x50*/ f32 _50;
    /*0x54*/ f32 _54;
    /*0x58*/ u8 _58[0x14];
    /*0x6C*/ f32 storedX;
    /*0x70*/ f32 storedZ;
    /*0x74*/ Vec target;
    /*0x80*/ s32 objectId;
    /*0x84*/ u8 _84[0x0C];
    /*0x90*/ f32 bouncePhase;
    /*0x94*/ s16 state;
    /*0x96*/ s16 _96;
    /*0x98*/ s16 _98;
    /*0x9A*/ s16 _9A;
    /*0x9C*/ s16 _9C;
    /*0x9E*/ s16 _9E;
    /*0xA0*/ s16 _A0;
    /*0xA2*/ s16 timer;
    /*0xA4*/ u8 _A4[8];
    /*0xAC*/ s16 _AC;
    /*0xAE*/ s16 _AE;
    /*0xB0*/ s16 targetLocation;
    /*0xB2*/ s16 locationIndex;
    /*0xB4*/ u8 _B4[6];
    /*0xBA*/ u8 mode;
    /*0xBB*/ u8 flagBB;
    /*0xBC*/ u8 flagBC;
    /*0xBD*/ u8 flagBD;
    /*0xBE*/ u8 _BE[2];
    /*0xC0*/ s8 flagC0;
    /*0xC1*/ u8 _C1[2];
    /*0xC3*/ u8 typeC3;
    /*0xC4*/ u8 flagC4;
    /*0xC5*/ u8 _C5[5];
    /*0xCA*/ s8 flagCA;
    /*0xCB*/ s8 flagCB;
    /*0xCC*/ s8 flagCC;
    /*0xCD*/ s8 flagCD;
    /*0xCE*/ s8 flagCE;
    /*0xCF*/ s8 flagCF;
    /*0xD0*/ u8 flagD0;
    /*0xD1*/ u8 _D1[7];
} MenuEntry; // size: 0xD8

// A placed world object / location (0xBC bytes); MenuCtx.objects.
typedef struct MenuObject {
    /*0x00*/ Vec position;
    /*0x0C*/ u8 _0C[0x28 - 0x0C];
    /*0x28*/ f32 _28;
    /*0x2C*/ u8 _2C[0xBC - 0x2C];
} MenuObject; // size: 0xBC

// 6-byte batting-order slot; MenuCtx.order.
typedef struct MenuOrderSlot {
    /*0x0*/ s16 charId;
    /*0x2*/ u8 _2[4];
} MenuOrderSlot; // size: 0x6

// 10-byte star-mission / location record; MenuCtx.slots.
typedef struct MenuLocSlot {
    /*0x0*/ u8 _0[0x2];
    /*0x2*/ u8 _2;
    /*0x3*/ u8 _3;
    /*0x4*/ u8 _4;
    /*0x5*/ u8 _5;
    /*0x6*/ u8 _6;
    /*0x7*/ u8 _7;
    /*0x8*/ u8 _8;
    /*0x9*/ u8 _9;
} MenuLocSlot; // size: 0xA

// Menus context (lbl_2_bss_1A8248 points at it); only the fields used here.
typedef struct MenuCtx {
    /*0x0000*/ MenuRosterEntry chars[54];
    /*0x0AF8*/ MenuRosterEntry charsBackup[54]; // copy of chars
    /*0x15F0*/ u8 _15F0;
    /*0x15F1*/ u8 _15F1[20]; // indexed; copied into _43C2
    /*0x1605*/ u8 _1605[0x1610 - 0x1605];
    /*0x1610*/ MenuEntry entries[14];
    /*0x21E0*/ MenuObject objects[42];
    /*0x40B8*/ MenuOrderSlot order[9];
    /*0x40EE*/ MenuLocSlot slots[51];
    /*0x42EC*/ s32 _42EC;
    /*0x42F0*/ u8 _42F0[0x43BC - 0x42F0];
    /*0x43BC*/ s16 _43BC;
    /*0x43BE*/ s16 _43BE;
    /*0x43C0*/ u8 _43C0[0x43C2 - 0x43C0];
    /*0x43C2*/ u8 _43C2[20]; // indexed
    /*0x43D6*/ u8 _43D6[0x36]; // indexed by character
    /*0x440C*/ u8 _440C[9]; // indexed by team
    /*0x4415*/ u8 _4415;
    /*0x4416*/ u8 _4416;
    /*0x4417*/ u8 _4417;
    /*0x4418*/ u8 _4418;
    /*0x4419*/ u8 _4419;
    /*0x441A*/ u8 _441A;
    /*0x441B*/ u8 _441B;
    /*0x441C*/ u8 _441C;
    /*0x441D*/ u8 _441D;
    /*0x441E*/ u8 _441E;
    /*0x441F*/ u8 _441F;
    /*0x4420*/ u8 _4420;
    /*0x4421*/ u8 _4421;
    /*0x4422*/ u8 _4422;
    /*0x4423*/ u8 _4423;
    /*0x4424*/ u8 _4424;
    /*0x4425*/ u8 _4425;
    /*0x4426*/ u8 _4426;
    /*0x4427*/ u8 _4427;
    /*0x4428*/ u8 _4428;
    /*0x4429*/ u8 _4429;
    /*0x442A*/ u8 _442A;
    /*0x442B*/ u8 _442B;
    /*0x442C*/ u8 _442C;
    /*0x442D*/ u8 _442D;
    /*0x442E*/ u8 _442E;
    /*0x442F*/ u8 _442F;
    /*0x4430*/ u8 _4430;
    /*0x4431*/ u8 _4431[5]; // indexed
    /*0x4436*/ u8 _4436;
    /*0x4437*/ u8 _4437;
    /*0x4438*/ u8 _4438;
    /*0x4439*/ u8 _4439;
    /*0x443A*/ u8 _443A;
    /*0x443B*/ u8 _443B;
    /*0x443C*/ u8 _443C;
    /*0x443D*/ u8 _443D;
    /*0x443E*/ u8 _443E;
    /*0x443F*/ u8 _443F;
    /*0x4440*/ u8 _4440;
    /*0x4441*/ u8 _4441;
    /*0x4442*/ u8 _4442;
    /*0x4443*/ u8 _4443;
    /*0x4444*/ u8 _4444;
    /*0x4445*/ u8 _4445;
    /*0x4446*/ u8 _4446;
    /*0x4447*/ u8 _4447;
    /*0x4448*/ s8 _4448;
    /*0x4449*/ u8 _4449;
    /*0x444A*/ u8 _444A;
    /*0x444B*/ s8 _444B;
    /*0x444C*/ s8 _444C;
    /*0x444D*/ u8 _444D[0x36]; // indexed by character
    /*0x4483*/ u8 _4483[0x36]; // indexed by character
    /*0x44B9*/ u8 _44B9[0x36]; // indexed by character
    /*0x44EF*/ u8 _44EF;
    /*0x44F0*/ u8 _44F0;
    /*0x44F1*/ u8 _44F1;
    /*0x44F2*/ u8 _44F2;
    /*0x44F3*/ u8 _44F3;
    /*0x44F4*/ u8 _44F4;
    /*0x44F5*/ u8 _44F5;
    /*0x44F6*/ u8 _44F6;
    /*0x44F7*/ u8 _44F7;
    /*0x44F8*/ u8 _44F8[6]; // indexed
    /*0x44FE*/ u8 _44FE[8]; // indexed
} MenuCtx; // size: 0x4508

// Draw area after the per-layer flags (lbl_2_bss_1A8230 points at it); starts with the
// MenuDrawEntry[10][864] table used by fn_2_53F04.
typedef struct MenuDrawArea {
    /*0x00000*/ u8 _00000[0x32A55];
    /*0x32A55*/ u8 _32A55;
    /*0x32A56*/ u8 _32A56[0x32A86 - 0x32A56];
    /*0x32A86*/ u8 _32A86;
    /*0x32A87*/ u8 _32A87;
} MenuDrawArea;

// Menus work buffer (lbl_2_bss_1A8250; lbl_2_bss_1A8234 and lbl_2_bss_1A824C point at
// it, lbl_2_bss_1A8230 at drawArea); only the fields used here.
typedef struct MenuData {
    /*0x000000*/ u8 _000000[0x162600]; // MenuCell0730[0x46][0x360] (rep_0730.h)
    /*0x162600*/ s16 timer;
    /*0x162602*/ u8 _162602[2];
    /*0x162604*/ u8 layerFlags[13][0x46]; // per layout group: start an animation
    /*0x162992*/ u8 done;
    /*0x162993*/ u8 _162993[0x162998 - 0x162993];
    /*0x162998*/ MenuDrawArea drawArea;
    /*0x195420*/ u8 _195420[0x196FB8 - 0x195420];
    /*0x196FB8*/ s32 _196FB8;
    /*0x196FBC*/ s32 _196FBC;
    /*0x196FC0*/ u8 _196FC0[0x1972A0 - 0x196FC0];
    /*0x1972A0*/ s16 _1972A0;
    /*0x1972A2*/ s16 _1972A2;
    /*0x1972A4*/ u8 _1972A4[0x1972B0 - 0x1972A4];
    /*0x1972B0*/ s16 _1972B0;
    /*0x1972B2*/ u8 _1972B2[0x1972B4 - 0x1972B2];
    /*0x1972B4*/ s16 _1972B4;
    /*0x1972B6*/ u8 _1972B6;
    /*0x1972B7*/ u8 _1972B7;
    /*0x1972B8*/ u8 _1972B8;
    /*0x1972B9*/ u8 _1972B9;
    /*0x1972BA*/ u8 _1972BA[0x1972BC - 0x1972BA];
    /*0x1972BC*/ u8 _1972BC;
    /*0x1972BD*/ u8 _1972BD;
    /*0x1972BE*/ s16 _1972BE;
    /*0x1972C0*/ u8 _1972C0;
    /*0x1972C1*/ u8 _1972C1[3];
    /*0x1972C4*/ MenuRecord records[8][5];
    /*0x197404*/ s16 _197404[6];
    /*0x197410*/ u8 _197410[0x197416 - 0x197410];
    /*0x197416*/ u8 _197416;
    /*0x197417*/ u8 _197417;
    /*0x197418*/ u8 _197418;
    /*0x197419*/ u8 _197419[0x197430 - 0x197419];
    /*0x197430*/ s16 stats[8]; // a StatOutput
    /*0x197440*/ u8 _197440[0x1976A0 - 0x197440];
    /*0x1976A0*/ s32 selection;
    /*0x1976A4*/ s32 secondarySelection;
    /*0x1976A8*/ u32 _1976A8;
    /*0x1976AC*/ u8 _1976AC[0x1976C0 - 0x1976AC];
    /*0x1976C0*/ s32 _1976C0;
    /*0x1976C4*/ u8 _1976C4[0x1976D8 - 0x1976C4];
    /*0x1976D8*/ s16 _1976D8;
    /*0x1976DA*/ u8 _1976DA[0x1976DE - 0x1976DA];
    /*0x1976DE*/ s16 _1976DE;
    /*0x1976E0*/ u8 _1976E0[0x1976E4 - 0x1976E0];
    /*0x1976E4*/ s16 _1976E4;
    /*0x1976E6*/ u8 _1976E6[0x1976F2 - 0x1976E6];
    /*0x1976F2*/ s16 _1976F2;
    /*0x1976F4*/ u8 _1976F4[0x1976FA - 0x1976F4];
    /*0x1976FA*/ s16 _1976FA;
    /*0x1976FC*/ u8 _1976FC[2];
    /*0x1976FE*/ s16 _1976FE;
    /*0x197700*/ u8 _197700[6];
    /*0x197706*/ s16 _197706; // character (index into lbl_800E869C)
    /*0x197708*/ u8 _197708[0x197710 - 0x197708];
    /*0x197710*/ s16 _197710;
    /*0x197712*/ s16 _197712;
    /*0x197714*/ s16 _197714;
    /*0x197716*/ u8 _197716[0x197726 - 0x197716];
    /*0x197726*/ s16 _197726;
    /*0x197728*/ s16 _197728;
    /*0x19772A*/ s16 _19772A;
    /*0x19772C*/ u8 _19772C[0x197730 - 0x19772C];
    /*0x197730*/ s16 _197730;
    /*0x197732*/ u8 _197732[0x197734 - 0x197732];
    /*0x197734*/ s16 _197734;
    /*0x197736*/ s16 _197736;
    /*0x197738*/ u8 _197738[0x19773C - 0x197738];
    /*0x19773C*/ s16 _19773C;
    /*0x19773E*/ s16 _19773E;
    /*0x197740*/ u8 _197740[0x197746 - 0x197740];
    /*0x197746*/ s16 _197746;
    /*0x197748*/ u8 _197748[0x19774C - 0x197748];
    /*0x19774C*/ s16 _19774C;
    /*0x19774E*/ s16 _19774E;
    /*0x197750*/ u8 _197750[0x197766 - 0x197750];
    /*0x197766*/ s16 _197766;
    /*0x197768*/ s16 _197768;
    /*0x19776A*/ s16 _19776A;
    /*0x19776C*/ s16 _19776C;
    /*0x19776E*/ u8 _19776E[0x19779A - 0x19776E];
    /*0x19779A*/ s16 _19779A;
    /*0x19779C*/ s16 _19779C;
    /*0x19779E*/ s16 _19779E;
    /*0x1977A0*/ u8 _1977A0[0x1977A2 - 0x1977A0];
    /*0x1977A2*/ s16 frameSetA[5];
    /*0x1977AC*/ u8 _1977AC[0x19780E - 0x1977AC];
    /*0x19780E*/ s16 frameSetB[5];
    /*0x197818*/ s16 frameSetC[5];
    /*0x197822*/ u8 _197822[0x19782A - 0x197822];
    /*0x19782A*/ u8 _19782A;
    /*0x19782B*/ u8 _19782B;
    /*0x19782C*/ u8 _19782C;
    /*0x19782D*/ u8 _19782D[5]; // indexed
    /*0x197832*/ u8 _197832;
    /*0x197833*/ u8 _197833[0x19783D - 0x197833];
    /*0x19783D*/ u8 _19783D;
    /*0x19783E*/ u8 _19783E;
    /*0x19783F*/ u8 _19783F;
    /*0x197840*/ u8 _197840[0x197843 - 0x197840];
    /*0x197843*/ s8 _197843;
    /*0x197844*/ u8 _197844;
    /*0x197845*/ u8 _197845;
    /*0x197846*/ u8 _197846;
    /*0x197847*/ u8 _197847;
    /*0x197848*/ u8 _197848;
    /*0x197849*/ u8 _197849;
    /*0x19784A*/ u8 _19784A;
    /*0x19784B*/ u8 _19784B[0x197857 - 0x19784B];
    /*0x197857*/ s8 _197857;
    /*0x197858*/ u8 _197858;
    /*0x197859*/ u8 _197859;
    /*0x19785A*/ u8 _19785A[0x19785C - 0x19785A];
    /*0x19785C*/ u8 _19785C;
    /*0x19785D*/ u8 _19785D[0x197862 - 0x19785D];
    /*0x197862*/ u8 _197862;
    /*0x197863*/ s8 port;
    /*0x197864*/ u8 _197864;
    /*0x197865*/ u8 _197865;
    /*0x197866*/ s8 _197866;
    /*0x197867*/ s8 _197867;
    /*0x197868*/ u8 _197868[0x36]; // indexed by _197867
    /*0x19789E*/ u8 _19789E;
    /*0x19789F*/ u8 _19789F[20]; // indexed
    /*0x1978B3*/ u8 _1978B3[20]; // indexed
    /*0x1978C7*/ u8 _1978C7[20]; // indexed
    /*0x1978DB*/ u8 _1978DB[20]; // indexed by _1978F0
    /*0x1978EF*/ u8 _1978EF;
    /*0x1978F0*/ s8 _1978F0;
    /*0x1978F1*/ u8 _1978F1[0x1978F3 - 0x1978F1];
    /*0x1978F3*/ u8 _1978F3;
    /*0x1978F4*/ u8 _1978F4[0x1978F6 - 0x1978F4];
    /*0x1978F6*/ u8 _1978F6;
    /*0x1978F7*/ u8 _1978F7;
    /*0x1978F8*/ u8 _1978F8[0x1978FA - 0x1978F8];
    /*0x1978FA*/ u8 _1978FA;
    /*0x1978FB*/ u8 _1978FB;
    /*0x1978FC*/ u8 _1978FC[0x197900 - 0x1978FC];
} MenuData; // size: 0x197900

// lbl_2_bss_1A823C points at this; only the fields used here.
typedef struct MenuFlags {
    /*0x00*/ u8 _00[0x30];
    /*0x30*/ s16 mode;
    /*0x32*/ s16 state;
    /*0x34*/ u8 _34;
} MenuFlags;

typedef struct MenuCharRecord {
    /*0x00*/ u8 _00[0x13];
    /*0x13*/ u8 _13;
    /*0x14*/ u8 _14[2];
} MenuCharRecord; // size: 0x16

// Saved record tables (lbl_2_bss_1A8240 points at them): 8 lists of 5.
typedef struct MenuRecords {
    /*0x000*/ MenuRecord lists[8][5];
    /*0x140*/ MenuCharRecord chars[32];
    /*0x400*/ u8 _400[1]; // indexed by character
} MenuRecords;

// lbl_2_bss_1A8244 points at this; only the fields used here.
typedef struct MenuProgress {
    /*0x00*/ u8 _00[0xC6]; // indexed by lbl_800E869C[character]
    /*0xC6*/ u8 _C6[5][4];
    /*0xDA*/ u8 _DA[0xE4 - 0xDA];
    /*0xE4*/ u8 _E4[4]; // indexed by level
    /*0xE8*/ u8 _E8[0xF4 - 0xE8];
    /*0xF4*/ u8 _F4;
    /*0xF5*/ u8 _F5;
    /*0xF6*/ u8 _F6[0xF8 - 0xF6];
} MenuProgress;

#endif
