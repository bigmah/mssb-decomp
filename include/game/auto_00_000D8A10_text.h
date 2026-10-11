#ifndef __GAME_AUTO_00_000D8A10_TEXT_H_
#define __GAME_AUTO_00_000D8A10_TEXT_H_

#include "mssbTypes.h"

// Crowd sound settings (lbl_3_data_8404: [stadium * 15 + sound], lbl_3_data_84B8: [sound] for GameModeSelected 6).
// Sound n plays id lbl_3_data_81DC[stadium] + n; some n are >= 15 and run into the next stadium's row.
typedef struct MinigameSoundParams {
    /*0x0*/ u8 vol;
    /*0x1*/ u8 ctrl;
} MinigameSoundParams;

// Toy field slot machine data (lbl_3_data_189C4).
typedef struct MinigameSlotData {
    /*0x00*/ s16 reels[3][7];          // symbols on each reel
    /*0x2A*/ u8 _2A[2];
    /*0x2C*/ u8 weights[3][3][3][8];  // [participants - 2][progress][standing]: result weights
} MinigameSlotData; // size: 0x104

void fn_3_1079C8(u8* out, s32 mode);
void fn_3_1608F0(s32 a, s32 b);

void fn_3_D8A10(void);
void fn_3_D8CD0(void);
void fn_3_D9868(void);
void fn_3_D9A30(void);

#endif
