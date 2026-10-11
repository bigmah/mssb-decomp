#ifndef __CHALLENGE_AUTO_00_0000C2A4_TEXT_H_
#define __CHALLENGE_AUTO_00_0000C2A4_TEXT_H_

#include "mssbTypes.h"

// Actor bone as walked by fn_1_C2DC (only the tree links are used).
typedef struct ChBoneNode {
    /*0x00*/ u8 _00[8];
    /*0x08*/ struct ChBoneNode* next;  // sibling
    /*0x0C*/ u8 _0C[4];
    /*0x10*/ struct ChBoneNode* child; // first child
} ChBoneNode;

void fn_1_C2A4(void);
s32 fn_1_C2DC(ChBoneNode* bone, char* buf, s32 col, s32 width, s32 ret, s32* line, s32* skip,
              s32* remaining);
void fn_1_C5A8(void);

#endif
