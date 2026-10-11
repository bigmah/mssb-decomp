#ifndef __GAME_rep_3448_H_
#define __GAME_rep_3448_H_

#include "mssbTypes.h"

// This unit's view of a layout sprite (main/file_8000F150.h LayoutObj); only the fields used here.
typedef struct RepObj {
    /*0x00*/ u8 _00[0x48];
    /*0x48*/ f32 x;
    /*0x4C*/ f32 y;
    /*0x50*/ u8 _50[0x4];
    /*0x54*/ u32 flags;
    /*0x58*/ u32 color;
    /*0x5C*/ u32 frame; // animation frame << 16
    /*0x60*/ u8 _60[0x4];
    /*0x64*/ u16 anim;
    /*0x66*/ u8 _66[0x2];
    /*0x68*/ u8 mode;   // 0 hidden, 1 play, 4 rewind
    /*0x69*/ u8 status; // 2 when the animation finished
    /*0x6A*/ u8 _6A[0x72 - 0x6A];
    /*0x72*/ s16 _72;
} RepObj;

// One entry of lbl_80371C30 (main/file_8000F150.h LayoutSlot).
typedef struct RepSlot {
    /*0x0*/ RepObj* obj;
    /*0x4*/ u32 _04;
} RepSlot;

// HUD task (lbl_803CC1B8 while one of this unit's tasks runs); only the fields used here.
typedef struct RepTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x8];
    /*0x0C*/ struct RepTask* parent;
    /*0x10*/ u8 _10[0x4];
    /*0x14*/ u16 baseIdx; // first slot in lbl_80371C30
    /*0x16*/ u16 count;
    /*0x18*/ u16 timer;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 _1E;
    /*0x20*/ u16 _20;
    /*0x22*/ u16 _22;
    /*0x24*/ u8 _24[4]; // per-player "counting" flags (fn_3_11F02C)
} RepTask;

// Runner position (game/UnknownHomes_Game.h InMemRunnerType, size 0x154).
typedef struct RepRunner {
    /*0x000*/ f32 x;
    /*0x004*/ f32 y;
    /*0x008*/ f32 z;
    /*0x00C*/ u8 _00C[0x154 - 0xC];
} RepRunner;

// Fielder position (game/UnknownHomes_Game.h InMemFielderType, size 0x268).
typedef struct RepFielder {
    /*0x000*/ f32 x;
    /*0x004*/ f32 y;
    /*0x008*/ f32 z;
    /*0x00C*/ u8 _00C[0x268 - 0xC];
} RepFielder;

// Roster entry (game/UnknownHomes_Game.h CharacterStats, size 0xA0).
typedef struct RepRosterEnt {
    /*0x00*/ u8 _00[0x24];
    /*0x24*/ s16 charId;
    /*0x26*/ u8 _26[0xA0 - 0x26];
} RepRosterEnt;

#define REP_TASK ((RepTask*)lbl_803CC1B8)
#define REP_OBJ(t, i) (*(RepObj**)((u8*)lbl_80371C30 + ((t)->baseIdx + (i)) * sizeof(RepSlot)))

void fn_3_11EC28(void);
void fn_3_11F02C(void);
void fn_3_11F480(void);
void fn_3_11F4B4(s32 idx, s32 flag);
void fn_3_11F508(void);
void fn_3_11F778(void);
void fn_3_11FA58(void);
void fn_3_11FDB0(void);
void fn_3_12026C(void);
void fn_3_12089C(void);
s32 fn_3_120F5C(void);
void fn_3_120FF8(void);
void fn_3_121304(void);
void fn_3_121908(void);
void fn_3_122334(void);
void fn_3_1226D4(void);
void fn_3_122D24(void);
void fn_3_1231D4(void);
void fn_3_1235B8(void);
void fn_3_123990(void);
void fn_3_123EBC(void);
void fn_3_1243A4(void);
void fn_3_124738(void);
void fn_3_124CE0(void);
u32 fn_3_12536C(void);
s32 fn_3_125424(u8* a, s32 i, u32 v);
s32 fn_3_125480(u8* a);
void fn_3_1254F8(void);
void fn_3_125604(void);
void fn_3_125850(void);
void fn_3_1258C0(void);
void fn_3_126604(void);
void fn_3_1274B4(void);
void fn_3_127B68(void);
void fn_3_128A38(void);
void fn_3_128B90(void);
void fn_3_128C18(void);
void fn_3_129370(void);

#endif // !__GAME_rep_3448_H_
