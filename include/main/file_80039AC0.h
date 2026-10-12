#ifndef __MAIN_FILE_80039AC0_H__
#define __MAIN_FILE_80039AC0_H__

#include "mssbTypes.h"
#include "main/file_8000BA3C.h" // QuadVtx
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTypes.h"
#include "main/file_80069BDC.h" // TexDesc

#include "main/screenfx.h" // ScreenFx

typedef struct ScreenFxNode {
    /*0x00*/ u32 link;
    /*0x04*/ void (*func)(struct ScreenFxNode* node);
    /*0x08*/ ScreenFx fx;
} ScreenFxNode; // size 0x28




void fn_80039AC0(void);
void fn_80039FF8(ScreenFxNode* node);
void fn_8003A090(void);
void fn_8003A144(void);
void fn_8003A1D0(void);
void fn_8003A2C0(void);
void fn_8003A2EC(void);

#endif
