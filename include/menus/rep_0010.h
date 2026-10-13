#ifndef __REP_0010_MENUS_H__
#define __REP_0010_MENUS_H__

#include "mssbTypes.h"
#include "menus/menu_work.h"

// Menus command queue task (lbl_2_bss_4, fn_2_374): a ring of 32 byte commands.
typedef struct MenuCmdQueue {
    /*0x00*/ void (*func)(void);
    /*0x04*/ void* prev;
    /*0x08*/ void* next;
    /*0x0C*/ void* parent;
    /*0x10*/ s16 _10;
    /*0x12*/ u16 priority;
#ifdef TARGET_PC
    void* _u14align[0]; // SceneTask.u14 is pointer-aligned on PC
#endif
    /*0x14*/ u8 state;
    /*0x15*/ u8 head;
    /*0x16*/ u8 tail;
    /*0x17*/ u8 cmds[32];
} MenuCmdQueue;

// The menus boot task (fn_2_708 / fn_2_554).
typedef struct MenuBootTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ void* prev;
    /*0x08*/ void* next;
    /*0x0C*/ MenuTask* parent;
    /*0x10*/ s16 _10;
    /*0x12*/ u16 priority;
#ifdef TARGET_PC
    void* _u14align[0]; // SceneTask.u14 is pointer-aligned on PC
#endif
    /*0x14*/ u16 state;
} MenuBootTask;

// Layer entry passed to fn_800A7D4C: a draw callback for layer 0.
typedef struct {
    s32 unk0;
    void (*callback)(void* node); // draw-list callbacks get their node
} MenuLayerCallback;

void fn_2_0(void* node);
void fn_2_3C(void);
void fn_2_110(void);
void fn_2_160(void);
s32 fn_2_1A8(u8 idx, u8 kind, u16 mask);
void fn_2_2D8(void);
void fn_2_2DC(void);
void fn_2_328(void);
s32 fn_2_4C4(MenuCmdQueue* q, s8 value);
u8 fn_2_510(MenuCmdQueue* q);
void fn_2_940(void);
void fn_2_A14(void);
void _prolog(void);
void _epilog(void);
void fn_2_708(void);
void fn_2_664(void);
void fn_2_554(void);
void fn_2_374(void);
void fn_2_794(void);
void fn_2_978(void);

#endif
