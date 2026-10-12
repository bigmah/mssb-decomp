#ifndef __CHALLENGE_REP_0000_H__
#define __CHALLENGE_REP_0000_H__

#include "mssbTypes.h"
#include "challenge/rep_0010.h"

// Model/animation loader task (fn_1_1E0): streams each file of lbl_800F1D78 from ARAM.
typedef struct ChLoaderTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ void* data;  // file being loaded (ARAMTransfer result)
    /*0x18*/ u8 index;    // file index into lbl_800F1D78
} ChLoaderTask;

void fn_1_0(void* bank, char* name);

typedef struct {
    u32 textures;
    u32 actor;
    u32 geometry;
    u32 skin;
    u32 extra;
} ChallengeModelHeader;

void fn_1_20(ChallengeModelHeader* model);
void fn_1_E8(ChallengeModelHeader* model);
void fn_1_1E0(void);
void fn_1_1B0(u32* table, s32 count);
void fn_1_568(void);
void fn_1_58C(void);
void fn_1_5E8(void);

#endif
