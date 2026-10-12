#ifndef __MENUS_MENU_WORK_H__
#define __MENUS_MENU_WORK_H__

// Shared menus.rel types: the menu task/item views of the scene queue and the
// big menus work areas (lbl_2_bss_1A8234 .. lbl_2_bss_1A824C).

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// One controller entry of lbl_803C77B8 (PadState in main/file_800A7C08.h,
// which can't be included next to UnknownHomes_Static.h).
typedef struct MenuPad {
    /*0x00*/ u16 held;
    /*0x02*/ u16 down;
    /*0x04*/ u16 repeat;
    /*0x06*/ u16 prev;
    /*0x08*/ s8 err;
    /*0x09*/ u8 _09[0x10 - 0x09];
    /*0x10*/ s8 stickX;
    /*0x11*/ s8 stickY;
    /*0x12*/ s8 substickX;
    /*0x13*/ s8 substickY;
    /*0x14*/ u8 _14[0xC];
} MenuPad; // size: 0x20

#ifndef offsetof
#define offsetof(type, field) ((u32)&((type*)0)->field)
#endif

// A u16 field of controller `port`, addressed as ((u16*)(pads + offset))[port * 16]:
// the original indexes the pad array this way (MenuPad holds no pointers).
#define MENUPAD_U16(field, port) \
    ((u16*)((u8*)&lbl_803C77B8 + offsetof(MenuPad, field)))[(port) * (s32)(sizeof(MenuPad) / sizeof(u16))]

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

// A menu screen task (lbl_803CC1B8 while one of the screens runs): a MenuTask whose
// 0x14.. fields are screen state instead of a sprite run.
typedef struct MenuScreenTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct MenuScreenTask* prev;
    /*0x08*/ struct MenuScreenTask* next;
    /*0x0C*/ struct MenuScreenTask* parent;
    /*0x10*/ s16 signal; // set to 1 by a child task when it is done
    /*0x12*/ u16 priority;
    /*0x14*/ s16 counter;
    /*0x16*/ s16 arg;
    /*0x18*/ s16 timer;
    /*0x1A*/ s16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 subState;
    /*0x20*/ u8 _20[8];
    /*0x28*/ s8 step;
} MenuScreenTask;

// One animated element of a menu screen (rep_0788 naming); same object as MenuItem.
typedef struct MenuItemState {
    /*0x00*/ void (*func)(MenuTask* menu, struct MenuItemState* item);
    /*0x04*/ s16 state;
    /*0x06*/ s16 timer;
    /*0x08*/ u8 _08[2];
    /*0x0A*/ s16 index;
    /*0x0C*/ u8 _0C[2];
    /*0x0E*/ s16 offset; // sprite index relative to menu->baseIdx
    /*0x10*/ s16 unk10;
    /*0x12*/ s16 unk12;
    /*0x14*/ s16 unk14;
} MenuItemState;

// Layout object `i` of `slots` (a LayoutSlot array, main/file_8000F150.h), indexed as
// ((LayoutObj**)slots)[i * 2] the way much of the original code does it.
#define MENU_SLOT_OBJ(slots, i) (((LayoutObj**)(slots))[(i) * (s32)(sizeof(LayoutSlot) / sizeof(LayoutObj*))])

#define MENU_SPRITE(task, item) (lbl_80371C30[(task)->baseIdx + (item)->sprite].obj)

// High-score style record: a value and two tags.
typedef struct MenuRecord {
    /*0x0*/ s32 value;
    /*0x4*/ s16 _4;
    /*0x6*/ s16 _6;
} MenuRecord; // size: 0x8

typedef struct MenuMission {
    /*0x0*/ s8 state; // star mission state (-2 / 0 / ...)
    /*0x1*/ u8 shown; // shown on the pause menu
} MenuMission; // size: 0x2

// Star-mission state of one character (0x34 bytes); MenuCtx.chars. Same layout as
// ChallengeTrackingStruct in game/UnknownHomes_Game.h.
typedef struct MenuRosterEntry {
    /*0x00*/ s8* limits; // indexed by [_4415 * 6 + _441C + 4]
    /*0x04*/ s8 _04;
    /*0x05*/ s8 _05;
    /*0x06*/ s8 value;
    /*0x07*/ u8 _07;
    /*0x08*/ u8 _08;
    /*0x09*/ MenuMission missions[10];
    /*0x1D*/ MenuMission savedMissions[10];
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
    /*0x3C*/ f32 _3C;
    /*0x40*/ f32 _40;
    /*0x44*/ f32 _44;
    /*0x48*/ u8 _48[0x4C - 0x48];
    /*0x4C*/ f32 heading;
    /*0x50*/ f32 _50;
    /*0x54*/ f32 _54;
    /*0x58*/ u8 _58[0x14];
    /*0x6C*/ f32 storedX;
    /*0x70*/ f32 storedZ;
    /*0x74*/ Vec target;
    /*0x80*/ s32 objectId;
    /*0x84*/ s32 _84;
    /*0x88*/ f32 _88;
    /*0x8C*/ f32 progress;
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
    /*0xB4*/ s16 _B4;
    /*0xB6*/ u8 _B6;
    /*0xB7*/ u8 _B7;
    /*0xB8*/ u8 _B8;
    /*0xB9*/ u8 _B9;
    /*0xBA*/ u8 mode;
    /*0xBB*/ u8 flagBB;
    /*0xBC*/ u8 flagBC;
    /*0xBD*/ u8 flagBD;
    /*0xBE*/ u8 _BE;
    /*0xBF*/ u8 _BF;
    /*0xC0*/ s8 flagC0;
    /*0xC1*/ u8 _C1[2]; // indexed
    /*0xC3*/ u8 typeC3;
    /*0xC4*/ u8 flagC4;
    /*0xC5*/ u8 _C5;
    /*0xC6*/ s8 _C6;
    /*0xC7*/ u8 _C7[0xCA - 0xC7];
    /*0xCA*/ s8 flagCA;
    /*0xCB*/ s8 flagCB;
    /*0xCC*/ s8 flagCC;
    /*0xCD*/ s8 flagCD;
    /*0xCE*/ s8 flagCE;
    /*0xCF*/ s8 flagCF;
    /*0xD0*/ u8 flagD0;
    /*0xD1*/ u8 _D1[3];
    /*0xD4*/ void (*update)(struct MenuEntry* entry); // per-type behaviour (lbl_2_data_2A2EC)
} MenuEntry; // size: 0xD8

// A placed world object / location (0xBC bytes); MenuCtx.objects.
typedef struct MenuObject {
    /*0x00*/ Vec position;
    /*0x0C*/ f32 _0C;
    /*0x10*/ u8 _10[0x14 - 0x10];
    /*0x14*/ f32 _14;
    /*0x18*/ f32 _18;
    /*0x1C*/ f32 _1C;
    /*0x20*/ f32 _20;
    /*0x24*/ f32 _24;
    /*0x28*/ f32 _28;
    /*0x2C*/ f32 _2C;
    /*0x30*/ f32 _30;
    /*0x34*/ u8 _34[0x38 - 0x34];
    /*0x38*/ f32 _38;
    /*0x3C*/ f32 _3C;
    /*0x40*/ u8 _40[0x44 - 0x40];
    /*0x44*/ f32 _44;
    /*0x48*/ u8 _48[0x78 - 0x48];
    /*0x78*/ s32 _78;
    /*0x7C*/ s32 _7C;
    /*0x80*/ f32 _80;
    /*0x84*/ f32 _84;
    /*0x88*/ f32 _88;
    /*0x8C*/ f32 _8C;
    /*0x90*/ s16 state; // index into the object's state callback table
    /*0x92*/ s16 _92;
    /*0x94*/ s16 _94;
    /*0x96*/ u8 _96[0x9C - 0x96];
    /*0x9C*/ s16 _9C;
    /*0x9E*/ u8 _9E[0xA0 - 0x9E];
    /*0xA0*/ s16 _A0;
    /*0xA2*/ u8 _A2[0xA6 - 0xA2];
    /*0xA6*/ s16 _A6;
    /*0xA8*/ u8 _A8;
    /*0xA9*/ u8 _A9;
    /*0xAA*/ u8 _AA;
    /*0xAB*/ u8 active;
    /*0xAC*/ u8 _AC;
    /*0xAD*/ u8 _AD;
    /*0xAE*/ s8 _AE;
    /*0xAF*/ u8 _AF[0xB2 - 0xAF];
    /*0xB2*/ u8 _B2;
    /*0xB3*/ u8 _B3;
    /*0xB4*/ u8 _B4;
    /*0xB5*/ u8 _B5;
    /*0xB6*/ u8 _B6[0xB8 - 0xB6];
    /*0xB8*/ void (*update)(struct MenuObject* object); // lbl_2_data_308B4[active]
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
    /*0x1605*/ u8 _1605;
    /*0x1606*/ u8 _1606;
    /*0x1607*/ u8 _1607[0x1610 - 0x1607];
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

// Animation archive the menus load (lbl_2_bss_3401BC); the bank entries are
// relocated in place.
typedef struct MenuAnimArchive {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ void* banks[17]; // ANIMBank*, indexed like MenuCtx.objects
    /*0x50*/ u8 _50[1];       // indexed
} MenuAnimArchive;

typedef struct MenuSortEntry {
    /*0x0*/ s32 k;
    /*0x4*/ s32 v;
} MenuSortEntry; // size: 0x8

// One cell of the menu draw grids (MenuData.cells, MenuDrawArea.entries).
typedef struct MenuDrawEntry {
    /*0x00*/ void (*draw)(void* context, struct MenuDrawEntry* entry);
    /*0x04*/ s16 _04;
    /*0x06*/ s16 _06;
    /*0x08*/ s16 column;
    /*0x0A*/ s16 _0A;
    /*0x0C*/ s16 row;
    /*0x0E*/ s16 _0E; // layout object index
    /*0x10*/ s16 _10;
    /*0x12*/ s16 _12;
    /*0x14*/ s16 _14;
    /*0x16*/ u8 _16[2];
} MenuDrawEntry; // size: 0x18

// Draw area after the per-layer flags (lbl_2_bss_1A8230 points at it); starts with the
// MenuDrawEntry[10][864] table used by fn_2_53F04.
typedef struct MenuDrawArea {
    /*0x00000*/ MenuDrawEntry entries[10][864];
    /*0x32A00*/ u8 _32A00[4];
    /*0x32A04*/ u8 _32A04[13][10]; // indexed
    /*0x32A86*/ u8 _32A86;
    /*0x32A87*/ u8 _32A87;
} MenuDrawArea;

// Menus work buffer (lbl_2_bss_1A8250; lbl_2_bss_1A8234 and lbl_2_bss_1A824C point at
// it, lbl_2_bss_1A8230 at drawArea); only the fields used here.
typedef struct MenuData {
    /*0x000000*/ MenuDrawEntry cells[0x46][864];
    /*0x162600*/ s16 timer;
    /*0x162602*/ u8 _162602[2];
    /*0x162604*/ u8 layerFlags[13][0x46]; // per layout group: start an animation
    /*0x162992*/ u8 done;
    /*0x162993*/ u8 _162993[0x162998 - 0x162993];
    /*0x162998*/ MenuDrawArea drawArea;
    /*0x195420*/ u8 _195420[0x195424 - 0x195420];
    /*0x195424*/ void* _195424;
    /*0x195428*/ void* _195428;
    /*0x19542C*/ u8 _19542C; // start of the block cleared by fn_2_515DC (up to _1972BC)
    /*0x19542D*/ u8 _19542D[0x1954AC - 0x19542D];
    /*0x1954AC*/ s32 _1954AC[2]; // per text channel
    /*0x1954B4*/ u8 _1954B4[0x196F1C - 0x1954B4];
    /*0x196F1C*/ s32* msScript;  // message script interpreter (fn_2_4EB9C)
    /*0x196F20*/ s32 msSavedOp;
    /*0x196F24*/ s32 _196F24;
    /*0x196F28*/ s32 _196F28;
    /*0x196F2C*/ u8 _196F2C[0x196F30 - 0x196F2C];
    /*0x196F30*/ s32 _196F30;
    /*0x196F34*/ s32 _196F34;
    /*0x196F38*/ s32 _196F38[32]; // script variables
    /*0x196FB8*/ s32 _196FB8[2]; // per text channel
    /*0x196FC0*/ s16 _196FC0;
    /*0x196FC2*/ u8 _196FC2[0x196FCA - 0x196FC2];
    /*0x196FCA*/ s16 _196FCA[2]; // per text channel
    /*0x196FCE*/ u8 _196FCE[0x196FD2 - 0x196FCE];
    /*0x196FD2*/ s16 _196FD2;
    /*0x196FD4*/ s16 _196FD4;
    /*0x196FD6*/ s16 _196FD6;
    /*0x196FD8*/ u8 _196FD8[0x196FE0 - 0x196FD8];
    /*0x196FE0*/ s16 _196FE0;
    /*0x196FE2*/ u8 _196FE2[0x196FE4 - 0x196FE2];
    /*0x196FE4*/ s16 _196FE4;
    /*0x196FE6*/ u8 _196FE6[0x197298 - 0x196FE6];
    /*0x197298*/ s16 _197298[2]; // indexed
    /*0x19729C*/ s16 _19729C;
    /*0x19729E*/ s16 _19729E;
    /*0x1972A0*/ s16 _1972A0;
    /*0x1972A2*/ s16 _1972A2;
    /*0x1972A4*/ s16 _1972A4;
    /*0x1972A6*/ s16 _1972A6;
    /*0x1972A8*/ u8 _1972A8[0x1972AA - 0x1972A8];
    /*0x1972AA*/ s16 _1972AA;
    /*0x1972AC*/ s16 _1972AC[2]; // indexed
    /*0x1972B0*/ s16 _1972B0;
    /*0x1972B2*/ s16 _1972B2;
    /*0x1972B4*/ s16 _1972B4;
    /*0x1972B6*/ u8 _1972B6;
    /*0x1972B7*/ u8 _1972B7;
    /*0x1972B8*/ u8 _1972B8;
    /*0x1972B9*/ u8 _1972B9;
    /*0x1972BA*/ u8 _1972BA;
    /*0x1972BB*/ u8 _1972BB;
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
    /*0x197440*/ u8 _197440[0x197450 - 0x197440];
    /*0x197450*/ MenuSortEntry sortList[55];
    /*0x197608*/ u8 _197608[0x197684 - 0x197608];
    /*0x197684*/ u32* scriptPc; // menu script interpreter (fn_2_422FC)
    /*0x197688*/ s32 _197688;
    /*0x19768C*/ s32 _19768C;
    /*0x197690*/ s32 _197690;
    /*0x197694*/ s32 _197694;
    /*0x197698*/ u8 _197698[0x1976A0 - 0x197698];
    /*0x1976A0*/ s32 selection;
    /*0x1976A4*/ s32 secondarySelection;
    /*0x1976A8*/ u32 _1976A8;
    /*0x1976AC*/ u8 _1976AC[0x1976B0 - 0x1976AC];
    /*0x1976B0*/ s32 _1976B0;
    /*0x1976B4*/ s32 _1976B4;
    /*0x1976B8*/ s32 _1976B8;
    /*0x1976BC*/ s32 _1976BC;
    /*0x1976C0*/ s32 _1976C0;
    /*0x1976C4*/ u8 _1976C4[0x1976D8 - 0x1976C4];
    /*0x1976D8*/ s16 _1976D8;
    /*0x1976DA*/ s16 _1976DA;
    /*0x1976DC*/ s16 _1976DC;
    /*0x1976DE*/ s16 _1976DE;
    /*0x1976E0*/ s16 _1976E0;
    /*0x1976E2*/ u8 _1976E2[0x1976E4 - 0x1976E2];
    /*0x1976E4*/ s16 _1976E4;
    /*0x1976E6*/ u8 _1976E6[0x1976F2 - 0x1976E6];
    /*0x1976F2*/ s16 _1976F2;
    /*0x1976F4*/ u8 _1976F4[0x1976FA - 0x1976F4];
    /*0x1976FA*/ s16 _1976FA;
    /*0x1976FC*/ u8 _1976FC[2];
    /*0x1976FE*/ s16 _1976FE;
    /*0x197700*/ u8 _197700[6];
    /*0x197706*/ s16 _197706; // character (index into lbl_800E869C)
    /*0x197708*/ s16 _197708;
    /*0x19770A*/ s16 _19770A;
    /*0x19770C*/ s16 _19770C;
    /*0x19770E*/ s16 _19770E;
    /*0x197710*/ s16 _197710;
    /*0x197712*/ s16 _197712;
    /*0x197714*/ s16 _197714;
    /*0x197716*/ u8 _197716[0x197726 - 0x197716];
    /*0x197726*/ s16 _197726;
    /*0x197728*/ s16 _197728;
    /*0x19772A*/ s16 _19772A;
    /*0x19772C*/ s16 _19772C;
    /*0x19772E*/ u8 _19772E[0x197730 - 0x19772E];
    /*0x197730*/ s16 _197730;
    /*0x197732*/ u8 _197732[0x197734 - 0x197732];
    /*0x197734*/ s16 _197734;
    /*0x197736*/ s16 _197736;
    /*0x197738*/ s16 _197738;
    /*0x19773A*/ s16 _19773A;
    /*0x19773C*/ s16 _19773C;
    /*0x19773E*/ s16 _19773E;
    /*0x197740*/ s16 _197740;
    /*0x197742*/ u8 _197742[0x197746 - 0x197742];
    /*0x197746*/ s16 _197746;
    /*0x197748*/ u8 _197748[0x19774C - 0x197748];
    /*0x19774C*/ s16 _19774C;
    /*0x19774E*/ s16 _19774E;
    /*0x197750*/ u8 _197750[0x197752 - 0x197750];
    /*0x197752*/ s16 _197752;
    /*0x197754*/ s16 _197754;
    /*0x197756*/ s16 _197756[14]; // animation per entry (MenuEntry.objectId)
    /*0x197772*/ u8 _197772[0x197778 - 0x197772];
    /*0x197778*/ s16 _197778;
    /*0x19777A*/ s16 _19777A;
    /*0x19777C*/ u8 _19777C[0x197796 - 0x19777C];
    /*0x197796*/ s16 _197796;
    /*0x197798*/ s16 _197798;
    /*0x19779A*/ s16 _19779A;
    /*0x19779C*/ s16 _19779C;
    /*0x19779E*/ s16 _19779E;
    /*0x1977A0*/ s16 _1977A0;
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
    /*0x197840*/ u8 _197840;
    /*0x197841*/ u8 _197841;
    /*0x197842*/ u8 _197842;
    /*0x197843*/ s8 _197843;
    /*0x197844*/ u8 _197844;
    /*0x197845*/ u8 _197845;
    /*0x197846*/ u8 _197846;
    /*0x197847*/ u8 _197847;
    /*0x197848*/ u8 _197848;
    /*0x197849*/ u8 _197849;
    /*0x19784A*/ u8 _19784A;
    /*0x19784B*/ u8 _19784B[0x197851 - 0x19784B];
    /*0x197851*/ s8 _197851;
    /*0x197852*/ u8 _197852[0x197854 - 0x197852];
    /*0x197854*/ s8 _197854;
    /*0x197855*/ u8 _197855[0x197857 - 0x197855];
    /*0x197857*/ s8 _197857;
    /*0x197858*/ u8 _197858;
    /*0x197859*/ u8 _197859;
    /*0x19785A*/ u8 _19785A;
    /*0x19785B*/ u8 _19785B;
    /*0x19785C*/ u8 _19785C;
    /*0x19785D*/ u8 _19785D[0x197862 - 0x19785D];
    /*0x197862*/ u8 _197862;
    /*0x197863*/ s8 port;
    /*0x197864*/ u8 _197864;
    /*0x197865*/ u8 _197865;
    /*0x197866*/ s8 _197866;
    /*0x197867*/ s8 _197867;
    /*0x197868*/ s8 _197868[0x36]; // indexed by _197867
    /*0x19789E*/ u8 _19789E;
    /*0x19789F*/ u8 _19789F[20]; // indexed
    /*0x1978B3*/ u8 _1978B3[20]; // indexed
    /*0x1978C7*/ u8 _1978C7[20]; // indexed
    /*0x1978DB*/ u8 _1978DB[20]; // indexed by _1978F0
    /*0x1978EF*/ u8 _1978EF;
    /*0x1978F0*/ s8 _1978F0;
    /*0x1978F1*/ u8 _1978F1;
    /*0x1978F2*/ u8 _1978F2;
    /*0x1978F3*/ u8 _1978F3;
    /*0x1978F4*/ u8 _1978F4;
    /*0x1978F5*/ u8 _1978F5;
    /*0x1978F6*/ u8 _1978F6;
    /*0x1978F7*/ u8 _1978F7;
    /*0x1978F8*/ u8 _1978F8;
    /*0x1978F9*/ u8 _1978F9;
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
    /*0xDA*/ u8 _DA[0xDE - 0xDA];
    /*0xDE*/ u8 _DE[6]; // indexed by stadium (MenuCtx._441C)
    /*0xE4*/ u8 _E4[4]; // indexed by level
    /*0xE8*/ u8 _E8[6]; // indexed by stadium (MenuCtx._441C)
    /*0xEE*/ u8 _EE[0xF4 - 0xEE];
    /*0xF4*/ u8 _F4;
    /*0xF5*/ u8 _F5;
    /*0xF6*/ u8 _F6[0xF8 - 0xF6];
} MenuProgress;

#endif
