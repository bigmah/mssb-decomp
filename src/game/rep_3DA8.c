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


// .text:0x001637EC size:0x15C
void fn_3_1637EC(void) {
    s32 i;
    s16 ids[9];
    u8 b;
    u8 a;
    s32 m;
    s32 j;
    ChallengeTrackingStruct* e;
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    a = *((u8*)starMissionCompletionTracker + 0x441C);
    b = *((u8*)starMissionCompletionTracker + 0x4415);
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    for (j = 0; j < 9; j++) {
        if (ids[j] != -1) {
            e = &t[ids[j]];
            m = *((u8*)e->scoutFlagPointer + 4 + b * 6 + a);
            if ((s8)m != 0 && (s8)e->scoutFlagsAchieved < (s8)m) {
                e->scoutFlagsAchieved = m;
            }
        }
    }
}

// .text:0x00163948 size:0x134
s32 fn_3_163948(void) {
    s16 ids[9];
    u8* q;
    u8* p;
    s32 i;
    s32 r;
    s32 m;
    s32 j;
    q = lbl_3_common_bss_37400;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    p = q;
    r = 0;
    for (j = 0; j < 9; j++) {
        if (ids[j] != -1) {
            m = p[j * 2 + 1];
            if ((s8)m != 0 && (s8)p[j * 2] < (s8)m) {
                r = 1;
            }
        }
    }
    return r;
}

// .text:0x00163A7C size:0x158
s32 fn_3_163A7C(s32 r) {
    s16 ids[9];
    s32 i;
    u8 a;
    u8 b;
    ChallengeTrackingStruct* e;
    s32 id;
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    u8* q = lbl_3_common_bss_37400;
    InMemBatterType* ba = &g_Batter;
    InMemPitcherType* pi = &g_Pitcher;
    a = *((u8*)starMissionCompletionTracker + 0x441C);
    b = *((u8*)starMissionCompletionTracker + 0x4415);
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    if (q[0x46] == 2) {
        id = pi->charID;
    } else if (q[0x46] == 1) {
        id = ba->charID;
    }
    for (i = 0; i < 9; i++) {
        if (id == ids[i]) {
            e = &t[ids[i]];
            if ((s8)*((u8*)e->scoutFlagPointer + 4 + b * 6 + a) != 0) {
                r = 1;
            }
        }
    }
    return r;
}

// .text:0x00163BD4 size:0x160
s32 fn_3_163BD4(void) {
    s16 ids[9];
    s32 i;
    s32 r;
    u8 a;
    u8 b;
    s32 m;
    s32 j;
    ChallengeTrackingStruct* e;
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    a = *((u8*)starMissionCompletionTracker + 0x441C);
    b = *((u8*)starMissionCompletionTracker + 0x4415);
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    r = 0;
    for (j = 0; j < 9; j++) {
        if (ids[j] != -1) {
            e = &t[ids[j]];
            m = *((u8*)e->scoutFlagPointer + 4 + b * 6 + a);
            if ((s8)m != 0 && (s8)e->scoutFlagsAchieved < (s8)m) {
                r = 1;
            }
        }
    }
    return r;
}

// .text:0x00163D34 size:0x160
void fn_3_163D34(void) {
    s16 ids[9];
    s32 i;
    u8* q;
    u8 a;
    u8 b;
    u8* p;
    ChallengeTrackingStruct* e;
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    a = *((u8*)starMissionCompletionTracker + 0x441C);
    b = *((u8*)starMissionCompletionTracker + 0x4415);
    q = lbl_3_common_bss_37400;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    p = q;
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1) {
            e = &t[ids[i]];
            if ((s8)*((u8*)e->scoutFlagPointer + 4 + b * 6 + a) != 0) {
                p[i * 2] = e->scoutFlagsAchieved;
                p[i * 2 + 1] = *((u8*)e->scoutFlagPointer + 4 + b * 6 + a);
            }
        }
    }
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
