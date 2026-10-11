#ifndef __MENUS_REP_0DE0_H__
#define __MENUS_REP_0DE0_H__

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtx.h"

#include "main/file_800BD8C4.h"

typedef struct {
    /* 0x00 */ void (*draw)(s32);
    /* 0x04 */ Vec position;
    /* 0x10 */ Vec rotation;
    /* 0x1C */ u8 padding1C[0x0A];
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 padding27;
} MenuDrawState; // size 0x28

// One loaded model: layout passed to fn_800BDC88.
typedef struct {
    /* 0x00 */ void* layout;
    /* 0x04 */ u8 padding04[8];
} MenuModel; // size 0xC

typedef struct {
    /* 0x0000 */ u8 padding[0x68];
    /* 0x0068 */ ActorObjectTable* table;
    /* 0x006C */ u8 padding6C[0x40];
    /* 0x00AC */ struct Light* lights[4];
    /* 0x00BC */ u8 paddingBC[0x2CD8];
    /* 0x2D94 */ MenuDrawState* states;
    /* 0x2D98 */ u8 padding2D98[8];
    /* 0x2DA0 */ MenuModel models[6];
    /* 0x2DE8 */ u8 padding2DE8[0x290];
    /* 0x3078 */ u16 count;
    /* 0x307A */ u8 unk307A;
} MenuDrawWorld;

// Stadium background objects (lbl_2_data_2E608), indexed by stadium.
typedef struct {
    /* 0x0 */ s16 model;
    /* 0x2 */ s16 texSet;
    /* 0x4 */ s16 hasTexSet;
} MenuStageObject;

typedef struct {
    /* 0x000 */ MenuStageObject objects[4][30];
    /* 0x2D0 */ s16 boneCount[6];       // per model
    /* 0x2DC */ s16 texCount[6];        // per model
    /* 0x2E8 */ s16 texIndex[5][8];     // per texSet
    /* 0x338 */ s8 objectCount[4];      // per stadium
} MenuStageData;

typedef struct {
    Mtx view;
    u16 yaw;
    u16 pitch;
    f32 offsetX;
    f32 offsetZ;
    Vec target;
    Vec eye;
    s32 unk54;
} MenuCamera;

// View of one controller entry in lbl_803C77B8 (PadState in main/file_800A7C08.h,
// which can't be included next to UnknownHomes_Static.h).
typedef struct MenuDebugPad {
    /*0x00*/ u16 held;
    /*0x02*/ u16 down;
    /*0x04*/ u16 repeat;
    /*0x06*/ u16 prev;
    /*0x08*/ u8 _08[0x10 - 0x08];
    /*0x10*/ s8 stickX;
    /*0x11*/ s8 stickY;
    /*0x12*/ s8 substickX;
    /*0x13*/ s8 substickY;
    /*0x14*/ u8 triggerLeft;
    /*0x15*/ u8 triggerRight;
    /*0x16*/ u8 _16[0x20 - 0x16];
} MenuDebugPad;

#define g_MenuDebugPad ((MenuDebugPad*)&lbl_803C77B8)

void fn_2_8563C(MenuCamera* camera);

void fn_2_858A4(MenuCamera* camera);

void fn_2_85AC0(MenuCamera* camera);

void fn_2_87114(void);

void fn_2_870D4(f32 value);

void fn_2_869B4(void);

void fn_2_86A0C(void);

void fn_2_86F40(void);

void fn_2_86FEC(void);

void fn_2_868C8(void);

void fn_2_86DCC(void);

void fn_2_87654(s32 unused, s32 start, s32 count, void* animBank, s32 arg5);

void fn_2_87118(void);

void fn_2_87350(void);

#endif
