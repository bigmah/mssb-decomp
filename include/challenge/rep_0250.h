#ifndef __CHALLENGE_REP_0250_H__
#define __CHALLENGE_REP_0250_H__

#include "mssbTypes.h"
#include "main/scene_task.h" // TASK_PARAM
#include "challenge/ch_data.h"
#include "challenge/rep_0010.h"

// Score-screen task (fn_1_9AB0) and its page tasks (fn_1_973C, fn_1_9380, fn_1_8F34);
// fn_80034E20 lays the page's sprites out from lbl_80371C30[start].
typedef struct ChScoreTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ u16 start; // first slot in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ u16 timer;
    /*0x1A*/ u8 sel;    // 0: page select, 1: value adjust
} ChScoreTask;

// Loaded by fn_1_8770 (auto_00_000085A8_text.c, same source file as this unit).
extern ChFileEntry lbl_1_data_B70;

void fn_1_96D0(void);

void fn_1_90B8(void);

void fn_1_96A4(void);

void fn_1_97B8(void);

void fn_1_96D4(void);

void fn_1_973C(TASK_PARAM(void* object));

void fn_1_8CD4(void);

void fn_1_9290(void);

void fn_1_8DBC(void);

void fn_1_8F34(TASK_PARAM(void* object));

void fn_1_90E4(s32 value);

void fn_1_9380(TASK_PARAM(void* object));

void fn_1_97E4(void);

void fn_1_9AB0(void);

#endif
