#include "game/rep_3DA8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"

extern u8 lbl_3_common_bss_37400[];
typedef struct {
    u8 pad[9];
    s8 v;
    u8 pad2[5];
} Rec15;

extern Rec15 lbl_80109420[];

typedef struct {
    u8 pad0;
    u8 trk;
    u8 row;
    u8 pad3[3];
} MissionIdx;

typedef struct {
    s16 type;
    s16 target;
    u8 pad[6];
} MissionRec;

extern MissionIdx lbl_800E8558[];
extern MissionRec lbl_80109AE8[][10];

static inline void gatherIds(s16* ids) {
    s32 i;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
}

// .text:0x00162080 size:0x28C
// 97%: structure matches; only register allocation differs (locals/temps in r0, r3-r9 and the r31 'done' flag)
void fn_3_162080(void) {
    MissionIdx* mi;
    u8* q = lbl_3_common_bss_37400;
    s32 i;
    u8 sp;
    s8* sv;
    s8 st;
    u8 cp;
    s32 k;
    s32 done;
    MissionRec* rec;
    s8* e;
    u8 so;
    u8 sc;
    u8 sw;
    if (*(s16*)(q + 0x40) == g_GameLogic.teamFielding) {
        mi = &lbl_800E8558[g_Pitcher.charID];
        e = (s8*)&starMissionCompletionTracker[mi->trk];
        rec = lbl_80109AE8[mi->row];
        for (i = 0; i < 10; i++, e += 2, rec++) {
            st = e[9];
            if (st >= 0) {
                done = 0;
                if (rec->type == 3) {
                    if (g_Pitcher.starPitchType != 0) {
                        e[9] = st | 1;
                        if (e[9] == 0x11) {
                            e[9] = -1;
                        }
                    }
                } else {
                    sv = e + 9;
                    sp = g_Pitcher.starPitchType;
                    cp = g_Pitcher.ChargePitchType;
                    for (k = 4; k < 13; k++) {
                        if (rec->type == k) {
                            switch (k) {
                            case 11:
                                if (sp != 0) {
                                    *sv += 1;
                                    if (*sv >= rec->target) {
                                        done = 1;
                                    }
                                }
                                break;
                            case 12:
                                if (cp == 3) {
                                    *sv += 1;
                                    if (*sv >= rec->target) {
                                        done = 1;
                                    }
                                }
                                break;
                            }
                            if (done != 0) {
                                *sv = -1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (*(s16*)(q + 0x40) == g_GameLogic.teamBatting) {
        mi = &lbl_800E8558[g_Batter.charID];
        e = (s8*)&starMissionCompletionTracker[mi->trk];
        rec = lbl_80109AE8[mi->row];
        sw = g_Ball.currentStarSwing2;
        sc = g_GameLogic.IsStarChance;
        so = g_GameLogic.stadiumStarObtained;
        for (i = 0; i < 10; i++, e += 2, rec++) {
            st = e[9];
            if (st >= 0) {
                if (rec->type == 3 && sw != 0) {
                    e[9] = st | 0x10;
                    if (e[9] == 0x11) {
                        e[9] = -1;
                    }
                }
                if (rec->type == 2 && (sc == 3 || so != 0)) {
                    e[9] += 1;
                    if (e[9] >= rec->target) {
                        e[9] = -1;
                    }
                }
            }
        }
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

// .text:0x0016440C size:0x148
void fn_3_16440C(s32 id) {
    s16 ids[9];
    s32 i;
    s32 j;
    s32 m;
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    u8* q = lbl_3_common_bss_37400;
    InMemBatterType* ba = &g_Batter;
    u8 a;
    InMemPitcherType* pi = &g_Pitcher;
    u8 b;
    s32 v;
    ChallengeTrackingStruct* e;
    a = *((u8*)starMissionCompletionTracker + 0x441C);
    b = *((u8*)starMissionCompletionTracker + 0x4415);
    v = lbl_80109420[q[0x46]].v;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    if (q[0x46] == 2) {
        id = pi->charID;
    } else if (q[0x46] == 1) {
        id = ba->charID;
    }
    for (j = 0; j < 9; j++) {
        if (id == ids[j]) {
            e = &t[ids[j]];
            m = *((u8*)e->scoutFlagPointer + 4 + b * 6 + a);
            if ((s8)m != 0) {
                q[j * 5 + 0x13] = m;
                q[j * 5 + 0x12] = e->scoutFlagsAchieved;
                q[j * 5 + 0x14] = v;
                v = 0;
                q[j * 5 + 0x15] = 1;
                q[j * 5 + 0x16] = ids[j];
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
