#ifndef __MAIN_CHALLENGE_MISSION_H__
#define __MAIN_CHALLENGE_MISSION_H__

// Split out of main/file_800527C4.h so that units can use it without that header's
// game/UnknownHomes_Game.h (whose math.h adds literals to .rodata).

#include "mssbTypes.h"

// lbl_8010A768: challenge mission definitions [mission set][mission].
typedef struct ChallengeMission {
    /*0x0*/ s16 msg;
    /*0x2*/ s16 type;
    /*0x4*/ s16 starsNeeded;
    /*0x6*/ s16 _6;
    /*0x8*/ s16 _8;
} ChallengeMission; // size: 0xA

#endif
