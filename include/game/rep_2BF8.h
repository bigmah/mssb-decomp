#ifndef __GAME_rep_2BF8_H_
#define __GAME_rep_2BF8_H_

#include "mssbTypes.h"
#include "main/scene_task.h" // SCENE_TASK_VIEW_LINKS

// Minigame results-board task (queue item in lbl_803CC1B8 while fn_3_E911C runs).
typedef struct ResultsTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ SCENE_TASK_VIEW_LINKS
    /*0x14*/ u16 baseIdx; // first sprite in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ u16 mode;    // set by the creator (fn_3_EDD10)
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 kind;
    /*0x20*/ u16 round;
    /*0x22*/ u16 timer;
    /*0x24*/ u16 score[4];
    /*0x2C*/ u16 bonus[4];
    /*0x34*/ u8 cursor;
    /*0x35*/ u8 spins;
} ResultsTask;

// Entry filled by fn_3_1079C8: a player and its placing.
typedef struct ResultsOrder {
    /*0x0*/ u8 player;
    /*0x1*/ u8 rank;
} ResultsOrder;

void fn_3_E911C(void);
void fn_3_E9D30(void);
s32 fn_3_EBFD4(void);
s32 fn_3_EB684(void);
void fn_3_ED244(void);
void fn_3_ED2A8(void);
void fn_3_ED490(void);
void fn_3_ED4FC(void);
void fn_3_ED784(void);
void fn_3_ED058(void);
void fn_3_ED6E0(void);
void fn_3_ED574(void);
void fn_3_ED2F4(void);
void fn_3_ECBB0(void);
void fn_3_ED818(void);
void fn_3_EDA3C(void);
void fn_3_EDD10(void);
void fn_3_ECD48(void);
void fn_3_EA340(void);
void fn_3_EA454(void);
void fn_3_EA8FC(void);
void fn_3_EAEF4(void);
void fn_3_EB6E0(void);
void fn_3_EC014(void);
void fn_3_EC804(void);
void fn_3_ED0F4(void);

#endif // !__GAME_rep_2BF8_H_
