#include "game/rep_3DA8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"

extern u8 lbl_3_common_bss_37400[];

static inline void gatherIds(s16* ids) {
    s32 i;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
}

// .text:0x0016230C size:0xA48 mapped:0x807A13A0
void fn_3_16230C(void) {
    return;
}


// .text:0x00164554 size:0x110
void fn_3_164554(void) {
    s16 ids[9];
    s8* p;
    s8* q;
    s32 i;
    s32 k;
    u8 a;
    u8 b;
    u8 m;
    ChallengeTrackingStruct* e;
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    a = *((u8*)starMissionCompletionTracker + 0x441C);
    b = *((u8*)starMissionCompletionTracker + 0x4415);
    q = (s8*)lbl_3_common_bss_37400;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    p = q;
    { s32 t6 = b * 6; k = t6 + a; }
    for (i = 0; i < 9; i++, p += 5) {
        if (ids[i] != -1 && p[0x15] == 1) {
            e = &t[ids[i]];
            if (*((s8*)e->scoutFlagPointer + 4 + k) != 0) {
                e->scoutFlagsAchieved += p[0x14];
                if ((s8)e->scoutFlagsAchieved > (s8)(m = *((u8*)e->scoutFlagPointer + 4 + k))) {
                    e->scoutFlagsAchieved = m;
                }
            }
        }
    }
}
