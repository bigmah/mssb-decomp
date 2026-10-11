#ifndef __MAIN_FILE_8004C19C_H__
#define __MAIN_FILE_8004C19C_H__

#include "mssbTypes.h"

struct CharActor;
#include "main/file_8004B284.h"

typedef struct RepeatFxData { // lbl_800FC720; frames are fixed point (x100000)
    /*0x00*/ EffectParams unk00;
    /*0x50*/ s32 firstFrame[3];
    /*0x5C*/ s32 endFrame[3];
    /*0x68*/ s32 interval[3];
    /*0x74*/ s32 flagWindow[3];
    /*0x80*/ EffectParams params[3];
} RepeatFxData;

void fn_80062D94(struct CharActor* model, s32 animID, u32 colorIdx, f32 frame);

void fn_8004C19C(struct CharActor* model, s32 animID, u32 colorIdx, f32 frame);
void fn_8004C510(struct CharActor* model, s32 animID, u32 colorIdx, f32 frame);

#endif
