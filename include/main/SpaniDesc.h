#ifndef __MAIN_SPANIDESC_H_
#define __MAIN_SPANIDESC_H_

#include "types.h"

// Creation parameters for fn_80034F50.
typedef struct SpaniDesc {
    /*0x00*/ u16 type;
    /*0x02*/ u16 animId;
    /*0x04*/ f32 x;
    /*0x08*/ f32 y;
    /*0x0C*/ s32 unkC;
    /*0x10*/ u8 playMode;
    /*0x11*/ u8 layer;
    /*0x12*/ s16 parent; // index of the parent within the group (0xFF: none)
    /*0x14*/ u8 texId;
    /*0x15*/ u8 unk15[3];
    /*0x18*/ f32 scale;
    /*0x1C*/ u8 is3D;
    /*0x1D*/ u8 unk1D;
    /*0x1E*/ s16 unk1E;
} SpaniDesc;

#endif
