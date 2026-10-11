#ifndef __MENUS_AUTO_00_0008782C_TEXT_H_
#define __MENUS_AUTO_00_0008782C_TEXT_H_

#include "mssbTypes.h"

struct SceneTask;

// Challenge save-slot select screen state (lbl_2_bss_33FBCC).
// Layout obj indices (relative to the task's objIdx), per save slot i (0..2):
//   4+i slot frame, 7+i slot cursor, 0xB+i team logo, 0x17+i, 0x32+i, 0x35+i,
//   0x38+i slot number, 0x3B+i, 0x3F+i selection marker, 0x42+i,
//   0xE+3i..0x10+3i score digits, 0x1A+8i.. roster faces.
typedef struct SlotSelectState {
    /*0x00*/ u8 _00[5];
    /*0x05*/ u8 mode; // 0..3: which button layout to show
    /*0x06*/ u8 _06[0xD - 0x6];
    /*0x0D*/ s8 prevSlot;
    /*0x0E*/ u8 closing;
    /*0x0F*/ s8 _0F;
    /*0x10*/ s8 _10; // -1: none
    /*0x11*/ u8 _11[0x17 - 0x11];
    /*0x17*/ u8 anim; // 0x49..0x50: which slot animation fn_2_8A824 runs, 0: none
    /*0x18*/ u8 animStarted;
    /*0x19*/ u8 animRunning;
    /*0x1A*/ u8 done;
    /*0x1B*/ u8 _1B;
    /*0x1C*/ s32 _1C;
    /*0x20*/ u8 btnStarted;
    /*0x21*/ u8 btnRunning;
    /*0x22*/ u8 btnAnim; // 0x51..0x53
    /*0x23*/ u8 _23;
} SlotSelectState; // size: 0x24

// lbl_2_bss_F410.
typedef struct SlotSelectInfo {
    /*0x00*/ u8 _00[0x50];
    /*0x50*/ s32 slot; // highlighted save slot
    /*0x54*/ s32 _54;
} SlotSelectInfo; // size: 0x58

typedef struct MenuSceneEntry {
    /*0x00*/ u8 _00[0x26];
    /*0x26*/ u8 _26;
    /*0x27*/ u8 _27;
} MenuSceneEntry; // size: 0x28

// What lbl_2_bss_340140 points at (only the fields used here).
typedef struct MenuSceneWork {
    /*0x0000*/ u8 _0000[0x2D94];
    /*0x2D94*/ MenuSceneEntry* entries;
    /*0x2D98*/ u8 _2D98[4];
    /*0x2D9C*/ u32* resFile; // starts with a table of section offsets
    /*0x2DA0*/ void* res[15]; // 5 x (actor layout, geometry, textures)
    /*0x2DDC*/ u8 _2DDC[0x3078 - 0x2DDC];
    /*0x3078*/ u16 entryCount;
} MenuSceneWork;

// lbl_2_bss_34009C (only the fields used here).
typedef struct MenuSceneTex {
    /*0x00*/ u8 _00[0x64];
    /*0x64*/ void* tex64;
    /*0x68*/ void* tex68;
    /*0x6C*/ u8 _6C[0xA4 - 0x6C];
} MenuSceneTex; // size: 0xA4

typedef struct Unk3401BC {
    /*0x00*/ u8 _00[0x50];
    /*0x50*/ u8 _50[1]; // indexed
} Unk3401BC;

void fn_2_8782C(void);
void fn_2_87998(struct SceneTask* task);
void fn_2_87FB0(struct SceneTask* task);
void fn_2_88250(struct SceneTask* task);
void fn_2_883C8(struct SceneTask* task);
void fn_2_887F8(struct SceneTask* task);
void fn_2_88D90(struct SceneTask* task);
void fn_2_89038(struct SceneTask* task);
s32 fn_2_895F8(u8 alt);
void fn_2_8975C(void);
void fn_2_89F70(void);
void fn_2_8A008(struct SceneTask* task);
void fn_2_8A824(void);
void fn_2_8ABFC(void);
void fn_2_8AC84(s32 index, s32 value);
void fn_2_8ACB0(s32 index, s32 value);
void fn_2_8ACDC(void);

#endif
