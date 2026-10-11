#ifndef __MENUS_REP_0AB0_H_
#define __MENUS_REP_0AB0_H_

#include "mssbTypes.h"
#include "main/file_80069BDC.h"

// Same layout as MenuSlot / CharSelectLayout in main/file_800639BC.h, which can't be
// included together with main/file_8004207C.h (both declare lbl_8034E9A0).
typedef struct MenuSlotPos {
    /*0x0*/ s32 id;
    /*0x4*/ s16 x;
    /*0x6*/ s16 y;
} MenuSlotPos; // size: 0x8

// View of lbl_803616CC (lbl_2_bss_1A8240 points at it).
typedef struct MenuCharLayout {
    /*0x000*/ MenuSlotPos head[5];
    /*0x028*/ MenuSlotPos groups[6][5];
    /*0x118*/ MenuSlotPos tail[5];
    /*0x140*/ StatInput stats[32];
    /*0x400*/ u8 _400[0x454 - 0x400];
} MenuCharLayout; // size: 0x454

// Menu task as seen by the rep_0AB0 menu screens (lbl_803CC1B8 while one of them runs).
typedef struct MenuTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct MenuTask* prev;
    /*0x08*/ struct MenuTask* next;
    /*0x0C*/ struct MenuTask* parent;
    /*0x10*/ s16 signal; // set to 1 by a child task when it is done
    /*0x12*/ u16 priority;
    /*0x14*/ u8 _14[2];
    /*0x16*/ s16 arg;
    /*0x18*/ u16 timer;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 subState;
    /*0x20*/ u8 _20[8];
    /*0x28*/ s8 step;
} MenuTask;

// Scene state shared by the menu screens (lbl_2_bss_1A823C -> lbl_800E877C).
typedef struct MenuSceneState {
    /*0x00*/ u8 _00[0x30];
    /*0x30*/ s16 _30;
    /*0x32*/ s16 state;
    /*0x34*/ u8 _34;
} MenuSceneState;

// Menu work buffer (lbl_2_bss_1A8250; lbl_2_bss_1A8234 and lbl_2_bss_1A824C point at it).
typedef struct MenuWorkBuf {
    /*0x000000*/ u8 _000000[0x162600];
    /*0x162600*/ s16 timer;
    /*0x162602*/ u8 _162602[2];
    /*0x162604*/ u8 layerFlags[13][0x46]; // per layout group: start an animation
    /*0x162992*/ u8 done;
    /*0x162993*/ u8 _162993[0x1972BC - 0x162993];
    /*0x1972BC*/ u8 _1972BC;
    /*0x1972BD*/ u8 _1972BD;
    /*0x1972BE*/ s16 modelIndex; // debug: 0..28
    /*0x1972C0*/ u8 _1972C0;
    /*0x1972C1*/ u8 _1972C1[3];
    /*0x1972C4*/ MenuSlotPos head[5];
    /*0x1972EC*/ MenuSlotPos groups[7][5];
    /*0x197404*/ StatInput statIn;
    /*0x19741A*/ StatInput statInCopy;
    /*0x197430*/ StatOutput statOut;
    /*0x197440*/ StatOutput statOutCopy;
    /*0x197450*/ u8 _197450[0x1976A0 - 0x197450];
    /*0x1976A0*/ s32 selection;
    /*0x1976A4*/ s32 subSelection;
    /*0x1976A8*/ u8 _1976A8[0x1976FA - 0x1976A8];
    /*0x1976FA*/ s16 listCursor;
    /*0x1976FC*/ u8 _1976FC[2];
    /*0x1976FE*/ s16 tab; // 0..3: which of the four screens to switch to
    /*0x197700*/ u8 _197700[2];
    /*0x197702*/ s16 _197702;
    /*0x197704*/ u8 _197704[2];
    /*0x197706*/ s16 charId;
    /*0x197708*/ s16 gridX;
    /*0x19770A*/ s16 gridY;
    /*0x19770C*/ u8 _19770C[0x19772E - 0x19770C];
    /*0x19772E*/ s16 listCount;
    /*0x197730*/ s16 mode;
    /*0x197732*/ s16 _197732;
    /*0x197734*/ u8 _197734[0x197746 - 0x197734];
    /*0x197746*/ s16 _197746;
    /*0x197748*/ u8 _197748[0x197845 - 0x197748];
    /*0x197845*/ u8 _197845;
    /*0x197846*/ u8 _197846;
    /*0x197847*/ u8 _197847;
    /*0x197848*/ u8 _197848;
    /*0x197849*/ u8 _197849;
    /*0x19784A*/ u8 _19784A;
    /*0x19784B*/ u8 _19784B[0x197863 - 0x19784B];
    /*0x197863*/ s8 port;
    /*0x197864*/ u8 _197864[0x1978FC - 0x197864];
} MenuWorkBuf; // size: 0x1978FC

// Debug-tunable value per model (0xBC-byte records inside the challenge save block).
typedef struct MenuModelParam {
    /*0x00*/ f32 value;
    /*0x04*/ u8 _04[0xBC - 0x4];
} MenuModelParam; // size: 0xBC

// View of the challenge save block (starMissionCompletionTracker; lbl_2_bss_1A8248 points at it).
typedef struct MenuSaveView {
    /*0x0000*/ u8 _0000[0x2208];
    /*0x2208*/ MenuModelParam modelParams[29];
} MenuSaveView;

void fn_2_5979C(void);
void fn_2_59CF8(void);
void fn_2_5A224(void);
void fn_2_5AE54(void);
void fn_2_5AF24(void);
void fn_2_5AFB0(void);
void fn_2_5B7DC(void);
void fn_2_5C5B8(void);
void fn_2_5CB5C(void);
void fn_2_5D26C(void);
void fn_2_5DC5C(void);
void fn_2_5E104(void);

#endif
