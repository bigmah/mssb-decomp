#ifndef __STATIC_PAD_H_
#define __STATIC_PAD_H_

#include "mssbTypes.h"

// Controller bookkeeping (lbl_803C77B8), one per port.
typedef struct PadSticks {
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
} PadSticks;

typedef struct PadAnalog {
    u8 triggerLeft;
    u8 triggerRight;
    u8 analogA;
    u8 analogB;
} PadAnalog;

typedef struct PadState {
    /*0x00*/ u16 held;
    /*0x02*/ u16 down;
    /*0x04*/ u16 repeat;
    /*0x06*/ u16 prev;
    /*0x08*/ s8 err;
    /*0x09*/ u8 rumbleCmd; // 1 = start requested, 2 = rumbling
    /*0x0A*/ u8 rumbleTimer;
    /*0x0B*/ u8 rumbleMode;
    /*0x0C*/ s8 repeatDelay;
    /*0x0D*/ s8 repeatTimer;
    /*0x0E*/ u8 _0E[2];
    /*0x10*/ PadSticks sticks;
    /*0x14*/ PadAnalog analog;
    /*0x18*/ u32 stickDirs;
    /*0x1C*/ u8 _1C[4];
} PadState;

// PadState.stickDirs bits (shifted right by PadConfig.stickShift and ORed into the buttons).
#define PAD_STICK_UP 0x80000
#define PAD_STICK_DOWN 0x40000
#define PAD_STICK_RIGHT 0x20000
#define PAD_STICK_LEFT 0x10000
#define PAD_SUBSTICK_UP 0x8
#define PAD_SUBSTICK_DOWN 0x4
#define PAD_SUBSTICK_RIGHT 0x2
#define PAD_SUBSTICK_LEFT 0x1

extern PadState lbl_803C77B8[4];

#endif // !__STATIC_PAD_H_
