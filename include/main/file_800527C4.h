#ifndef __MAIN_FILE_800527C4_H__
#define __MAIN_FILE_800527C4_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_80063028.h"

// Character actor as seen by the sound helpers here (only the fields used).
typedef struct CharSoundObj {
    /*0x000*/ u8 _000[0x252];
    /*0x252*/ s8 _252;
    /*0x253*/ u8 _253;
    /*0x254*/ s8 charIndex;
} CharSoundObj;

// Per-character model object: maps game joint ids to model joints.
typedef struct CharJointMapObj {
    /*0x000*/ u8 _000[0x162];
    /*0x162*/ u16 jointMap[0x79];
} CharJointMapObj;

// lbl_8036E548 (character actors and models), only the fields used here.
typedef struct CharModelTable {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ CharJointMapObj* chars[13];
} CharModelTable;

void fn_800528B4(void);

BOOL fn_80062578(void);
void fn_800626EC(s32 index);
void fn_80062674(s32 index);
void fn_80062744(void);
void fn_80062764(struct SoundLoadTask* task);
BOOL fn_80062794(s32 voice);
s32 fn_800627C4(void);
s32 fn_800627F8(void);
void fn_8006282C(void);
s32 fn_8006285C(void);
u32 fn_800628D4(s32 kind);
void fn_80062948(void);
void fn_80062A74(void);
void fn_80062BE4(Vec* pos);
void fn_80062C24(Vec* pos);
void fn_80062C60(CharSoundObj* obj, s32 a, s32 b, f32 frame);
void fn_80062D94(CharSoundObj* obj);
void fn_80062E6C(CharSoundObj* obj, s32 kind, s32 c);
s32 fn_80062ED4(void* player, GameActor** actor);
s32 fn_80062F38(GameBone* bone, GameBone* target, Mtx m, f32 t);
s32 fn_80063010(void* player, GameActor** actor);

#endif
