#ifndef __REP_0568_MENUS_H__
#define __REP_0568_MENUS_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

struct CharActor;
struct CharSlotList;

// Scene task (fn_800B0A5C_insertQueue) that streams the menu characters in (fn_2_18748).
typedef struct MenuCharLoadTask {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s16 timer;
    /*0x12*/ u8 _12[2];
    /*0x14*/ struct CharActor* actor;
    /*0x18*/ u8 charId[4];
    /*0x1C*/ u8 _1C;
    /*0x1D*/ u8 state;
    /*0x1E*/ u8 index;
    /*0x1F*/ u8 _1F;
    /*0x20*/ u8 showFlag;
    /*0x21*/ u8 step;
} MenuCharLoadTask;

void fn_2_190B8(u8* object);

void fn_2_16CE0(void);

void fn_2_16D38(void);

s32 fn_2_18650(s32 a);

void fn_2_18FBC(void);

void fn_2_1937C(struct CharSlotList* list, MtxPtr view);

void fn_2_17AB8(void);

void fn_2_18148(MenuCharLoadTask* task);

void fn_2_18748(void);

void fn_2_16DA8(void);
void fn_2_16F0C(u8 index);

#endif
