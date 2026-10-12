#ifndef __MAIN_FILE_80039AC0_H__
#define __MAIN_FILE_80039AC0_H__

#include "mssbTypes.h"
#include "main/file_8000BA3C.h" // QuadVtx
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTypes.h"
#include "main/file_80069BDC.h" // TexDesc

// Full-screen copy / blur effect state (lbl_803C5090).
typedef struct ScreenFx {
    /*0x00*/ f32 scale;
    /*0x04*/ f32 unk4;
    /*0x08*/ f32 jitterX;
    /*0x0C*/ f32 jitterY;
    /*0x10*/ u16 width;    // copy size
    /*0x12*/ u16 height;
    /*0x14*/ u16 lines;    // visible height (0x1C0)
    /*0x16*/ u8 _16;
    /*0x17*/ u8 alpha;
    /*0x18*/ u8 unk18;
    /*0x19*/ u8 repeat;
    /*0x1A*/ u8 r;
    /*0x1B*/ u8 g;
    /*0x1C*/ u8 b;
    /*0x1D*/ u8 flags;
    /*0x1E*/ u8 _1E[2];
} ScreenFx; // size 0x20

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
