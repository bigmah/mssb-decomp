#ifndef __GAME_FIELDING_TYPES_H__
#define __GAME_FIELDING_TYPES_H__

#include "mssbTypes.h"

// Fielder speed-boost / charge state, one per minigame fielder (fn_3_51220).
typedef struct FieldingBoost {
    /*0x00*/ f32 dirX;
    /*0x04*/ f32 dirZ;
    /*0x08*/ f32 scale;
    /*0x0C*/ s16 timer;
    /*0x0E*/ s16 timer2;
    /*0x10*/ s16 power;
    /*0x12*/ s16 frames;
    /*0x14*/ s16 fielder;
    /*0x16*/ s16 taps;
    /*0x18*/ s16 decay;
    /*0x1A*/ u8 state;
} FieldingBoost; // size: 0x1C

// Per minigame fielder stick state (g_FieldingLogic.padRec).
typedef struct FieldingPadRec {
    /*0x0*/ s16 stickAngle;
    /*0x2*/ u8 _2;
    /*0x3*/ u8 _3;
    /*0x4*/ u8 _4;
    /*0x5*/ u8 _5;
} FieldingPadRec; // size: 0x6

#endif
