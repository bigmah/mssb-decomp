#ifndef __GAME_AUTO_00_0008B094_TEXT_H_
#define __GAME_AUTO_00_0008B094_TEXT_H_

#include "mssbTypes.h"

// One queued stream request: which track, how far its load has got, and the volume.
typedef struct StreamRequest {
    /*0x0*/ s8 track;  // index into lbl_8034E478 / lbl_800E87B4
    /*0x1*/ s8 step;   // 0 stop current, 1 load, 2 play, 3 wait, 4 stop
    /*0x2*/ s8 volume; // passed to fn_800A8878 for both channels
} StreamRequest; // size: 0x3

// Task running fn_3_8B094 (lbl_803CC1B8): a 14-entry ring buffer of stream requests.
typedef struct StreamQueueTask {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u8 head;
    /*0x15*/ u8 tail;
    /*0x16*/ StreamRequest req[14];
} StreamQueueTask;

void fn_3_8B094(void);

#endif
