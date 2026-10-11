#include "game/rep_3DA8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/rand.h"

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
    s16 flags; // 1: needs a win, 2/4/8: minimum difficulty 1/2/3, 0x800: ...
    u8 pad[4];
} MissionRec;

extern MissionIdx lbl_800E8558[];
extern MissionRec lbl_80109AE8[][10];

// Only the fields used here.
typedef struct {
    /*0x000*/ u8 _000[0x17A];
    /*0x17A*/ s16 charID;
    /*0x17C*/ u8 _17C[0x268 - 0x17C];
} MissionFielderView; // g_Fielders entry, size 0x268
extern MissionFielderView g_Fielders[9];
extern GameScores g_Scores;
// lbl_803537E4[2][9] per-player game record (BatterRecord in game/auto_00_0015C5F4_text.h).
typedef struct {
    /*0x00*/ u8 _00[0x4];
    /*0x04*/ u8 _04; // at bats
    /*0x05*/ u8 _05; // hits
    /*0x06*/ u8 _06[0x9 - 0x6];
    /*0x09*/ u8 _09;
    /*0x0A*/ u8 _0A[0xD - 0xA];
    /*0x0D*/ u8 _0D;
    /*0x0E*/ u8 _0E[0x26 - 0xE];
} MissionBatterRecord;
extern MissionBatterRecord lbl_803537E4[2][9];

// lbl_80353A90 (GameLineScore in game/auto_00_0009C578_text.h); only the fields used here.
typedef struct {
    /*0x000*/ u8 _000[0xBE];
    /*0x0BE*/ struct {
        s8 player; // roster slot
        u8 _01[0x13];
    } _0BE[2]; // per team
    /*0x0E6*/ u8 _0E6[0x103 - 0xE6];
    /*0x103*/ s8 _103; // mission index (lbl_800E8558)
    /*0x104*/ u8 _104[0x108 - 0x104];
} MissionLineScoreView;
extern MissionLineScoreView lbl_80353A90;
// lbl_803535C8[2][9] per-player pitching record (PitcherRecord in game/auto_00_0015C5F4_text.h).
typedef struct {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ u8 _18;
    /*0x19*/ u8 _19[0x1E - 0x19];
} MissionPitcherRecord;
extern MissionPitcherRecord lbl_803535C8[2][9];
extern struct {
    /*0x0000*/ u8 _0000[0x46E4];
    /*0x46E4*/ s32 _46E4; // a character id (lbl_800E8558 index)
} lbl_8034E9A0;
#include "static/GameSettings.h"

// lbl_3_common_bss_37400 as used by fn_3_164A74 (the other functions here index it as bytes).
typedef struct {
    /*0x00*/ u8 _00[0x12];
    /*0x12*/ struct {
        u8 achieved;
        u8 max;
        s8 bonus;
        u8 active;
        s8 charID;
    } award[9]; // scout flags handed out (fn_3_16440C / fn_3_163E94)
    /*0x3F*/ u8 _3F;
    /*0x40*/ s16 team;
    /*0x42*/ u8 _42[4];
    /*0x46*/ u8 kind;   // lbl_80109420 index (the challenge being played)
    /*0x47*/ u8 result; // 0 running, 1 failed, 2 cleared
    /*0x48*/ u8 _48;
    /*0x49*/ s8 bonus;
} MissionChallengeState;
// g_RunningLogic (GameRunningLogic in game/auto_00_0009CD90_text.h); only the fields used here.
extern struct {
    /*0x00*/ s16 _00;
    /*0x02*/ s16 occupiedBases; // one nibble per base
    /*0x04*/ u8 _04[0x10 - 0x4];
    /*0x10*/ u8 _10;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 _12; // runs scored on the play
    /*0x13*/ u8 _13[0x20 - 0x13];
} g_RunningLogic;

// Star mission status as a signed value (< 0: done).
#define MISSION_STATUS(t, i) (*(s8*)&(t)->inGameMissionTracker[i].starMissionStatus)

static inline void gatherIds(s16* ids) {
    s32 i;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
}

// Advances the counter of mission `type` by one; completes it at the target.
static inline void countMission(ChallengeTrackingStruct* trk, s32 i, MissionRec* rec) {
    MISSION_STATUS(trk, i)++;
    if (MISSION_STATUS(trk, i) >= rec->target) {
        MISSION_STATUS(trk, i) = -1;
    }
}

static inline void countMissionType(ChallengeTrackingStruct* trk, MissionRec* rec, s32 type) {
    s32 i;
    for (i = 0; i < 10; i++, rec++) {
        if (MISSION_STATUS(trk, i) >= 0 && rec->type == type) {
            countMission(trk, i, rec);
        }
    }
}

static inline void countMissionTypeOnHit(ChallengeTrackingStruct* trk, MissionRec* rec, s32 type) {
    s32 i;
    for (i = 0; i < 10; i++, rec++) {
        if (MISSION_STATUS(trk, i) >= 0 && rec->type == type && g_Ball.AtBat_ContactResult == 3) {
            countMission(trk, i, rec);
        }
    }
}

// Fielding / batting event for star missions of roster slot `rosterIdx` of the tracked team.
// NONMATCHING 71%: same instruction count; the original tests "type != X" with an inverted
// branch layout and reuses the status byte it loaded for the increment (extsh on rosterIdx differs too)
// .text:0x00161588 size:0xAF8
#if NONMATCHING
void fn_3_161588(s32 event, s16 rosterIdx) {
    MissionIdx* mi = &lbl_800E8558[inMemRoster[*(s16*)(lbl_3_common_bss_37400 + 0x40)][rosterIdx].stats.CharID]; // TODO type
    ChallengeTrackingStruct* trk;
    MissionRec* rec;
    MissionFielderView* fielder;
    s32 i;

    switch (event) {
    case 0:
        countMissionType(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x1F);
        break;
    case 1:
        countMissionType(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x20);
        break;
    case 2:
        trk = &starMissionCompletionTracker[mi->trk];
        rec = lbl_80109AE8[mi->row];
        for (i = 0; i < 10; i++, rec++) {
            if (MISSION_STATUS(trk, i) >= 0) {
                switch (rec->type) {
                case 0x21:
                    countMission(trk, i, rec);
                    break;
                case 0x22:
                    if (g_Ball.AtBat_ContactResult == 3) {
                        countMission(trk, i, rec);
                    }
                    break;
                case 0x23:
                    break;
                case 0x24:
                    if (g_Ball.currentStarSwing == 5 || g_Ball.currentStarSwing == 6) {
                        countMission(trk, i, rec);
                    }
                    break;
                }
            }
        }
        break;
    case 3:
        countMissionType(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x25);
        break;
    case 4:
        countMissionType(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x23);
        break;
    case 5:
        countMissionTypeOnHit(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x26);
        break;
    case 6:
        countMissionType(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x27);
        break;
    case 7:
        // Throw to a given teammate.
        trk = &starMissionCompletionTracker[mi->trk];
        fielder = &g_Fielders[g_Ball.fielderBeingThrownTo];
        rec = lbl_80109AE8[mi->row];
        for (i = 0; i < 10; i++, rec++) {
            if (MISSION_STATUS(trk, i) >= 0 && rec->type == 0x28 &&
                rec->target == lbl_800E8558[fielder->charID].row) {
                MISSION_STATUS(trk, i) = -1;
            }
        }
        break;
    case 8:
        countMissionType(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x29);
        break;
    case 9:
        countMissionTypeOnHit(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x2A);
        break;
    case 10:
        countMissionType(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x2C);
        break;
    case 11:
        countMissionType(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x2D);
        break;
    case 12:
        countMissionType(&starMissionCompletionTracker[mi->trk], lbl_80109AE8[mi->row], 0x2E);
        break;
    }
}
#endif

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

// Star mission progress after an at-bat (result: play result code, rbi: runs batted in).
// NONMATCHING 65%: control flow and stores line up; register allocation differs throughout, the original
// keeps q on the stack and the opponent's mission row as a byte pointer, and rbi is not re-masked there
// .text:0x0016230C size:0xA48 mapped:0x807A13A0
#if NONMATCHING
void fn_3_16230C(s32 result, u8 rbi) {
    u8* q = lbl_3_common_bss_37400;
    InMemPitcherType* pi;
    GameScores* sc;
    InMemBallType* ball;
    MissionIdx* mi;
    MissionIdx* other;
    ChallengeTrackingStruct* trk;
    MissionRec* rec;
    s32 i;
    s32 k;
    s32 f;
    s32 p;
    s32 done;
    s32 flags;
    s32 n;
    s8 fielder;

    if (*(s16*)(q + 0x40) == g_GameLogic.teamFielding) { // TODO type
        // Pitcher missions.
        mi = &lbl_800E8558[g_Pitcher.charID];
        trk = &starMissionCompletionTracker[mi->trk];
        rec = lbl_80109AE8[mi->row];
        for (i = 0; i < 10; i++, rec++) {
            if (MISSION_STATUS(trk, i) >= 0) {
                done = 0;
                if (rec->type == 2) {
                    if (g_GameLogic.IsStarChance == 2) {
                        MISSION_STATUS(trk, i)++;
                        if (MISSION_STATUS(trk, i) >= rec->target) {
                            MISSION_STATUS(trk, i) = -1;
                        }
                    }
                } else {
                    other = &lbl_800E8558[g_Batter.charID];
                    for (k = 4; k < 13; k++) {
                        if (rec->type == k) {
                            switch (k) {
                            case 4:
                                if (result == 1 && rec->target == other->row) {
                                    done = 1;
                                }
                                break;
                            case 5:
                                if (result == 3 && rec->target == other->row) {
                                    done = 1;
                                }
                                break;
                            case 10:
                                if (result == 1) {
                                    MISSION_STATUS(trk, i)++;
                                    if (MISSION_STATUS(trk, i) >= rec->target) {
                                        done = 1;
                                    }
                                }
                                break;
                            }
                            if (done) {
                                MISSION_STATUS(trk, i) = -1;
                            }
                        }
                    }
                }
            }
        }

        // Fielder missions (type 43: take part in a double play with a given teammate).
        for (f = 0; f < 9; f++) {
            mi = &lbl_800E8558[g_Fielders[f].charID];
            trk = &starMissionCompletionTracker[mi->trk];
            rec = lbl_80109AE8[mi->row];
            for (i = 0; i < 10; i++, rec++) {
                if (MISSION_STATUS(trk, i) >= 0 && rec->type == 0x2B &&
                    g_Strikes.storedOuts + 2 <= g_Strikes.outs) {
                    flags = 0;
                    for (p = 0; p < 5; p++) {
                        fielder = lbl_3_common_bss_32A94.plays[p].fielder;
                        if (fielder >= 0) {
                            if (fielder == f) {
                                flags |= 1;
                            } else if (rec->target == lbl_800E8558[g_Fielders[fielder].charID].row) {
                                flags |= 0x10;
                            }
                            if (p == 1 && lbl_3_common_bss_32A94.plays[p].outs == 2) {
                                break;
                            }
                        }
                    }
                    if (flags == 0x11) {
                        MISSION_STATUS(trk, i) = -1;
                    }
                }
            }
        }
    }

    if (*(s16*)(q + 0x40) == g_GameLogic.teamBatting) { // TODO type
        // Batter missions.
        mi = &lbl_800E8558[g_Batter.charID];
        pi = &g_Pitcher;
        sc = &g_Scores;
        ball = &g_Ball;
        trk = &starMissionCompletionTracker[mi->trk];
        rec = lbl_80109AE8[mi->row];
        for (i = 0; i < 10; i++, rec++) {
            if (MISSION_STATUS(trk, i) >= 0) {
                done = 0;
                if (rec->type == 2) {
                    if (g_GameLogic.IsStarChance == 3 || g_GameLogic.stadiumStarObtained != 0) {
                        MISSION_STATUS(trk, i)++;
                        if (MISSION_STATUS(trk, i) >= rec->target) {
                            MISSION_STATUS(trk, i) = -1;
                        }
                    }
                } else {
                    other = &lbl_800E8558[pi->charID];
                    for (k = 13; k <= 32; k++) {
                        if (rec->type == k) {
                            switch (k) {
                            case 13:
                                if (result == 10 && sc->inning == rec->target) {
                                    done = 1;
                                }
                                break;
                            case 14:
                                if (result == 10 && rbi >= rec->target) {
                                    done = 1;
                                }
                                break;
                            case 15:
                                if (result >= rec->target + 6 && result <= 10) {
                                    done = 1;
                                }
                                break;
                            case 16:
                                if (result >= 7 && result <= 10 && pi->charID == rec->target) {
                                    done = 1;
                                }
                                break;
                            case 17:
                                if (result == 10 && rec->target == other->row) {
                                    done = 1;
                                }
                                break;
                            case 18:
                                if (rbi != 0 && rec->target == other->row) {
                                    done = 1;
                                }
                                break;
                            case 19:
                                if (result >= 7 && result <= 10) {
                                    MISSION_STATUS(trk, i)++;
                                    if (MISSION_STATUS(trk, i) >= rec->target) {
                                        done = 1;
                                    }
                                }
                                break;
                            case 20:
                            case 21:
                                if (result == 13) {
                                    if (k == 21) {
                                        if (sc->team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] > sc->_A0 &&
                                            g_Runners[3].runnerOnFieldOrOutOrScored != 0 &&
                                            g_Runners[3].furthestBaseForcedToGoToOnWalk != 0) {
                                            MISSION_STATUS(trk, i)++;
                                            if (MISSION_STATUS(trk, i) >= rec->target) {
                                                done = 1;
                                            }
                                        }
                                    } else {
                                        MISSION_STATUS(trk, i)++;
                                        if (MISSION_STATUS(trk, i) >= rec->target) {
                                            done = 1;
                                        }
                                    }
                                }
                                break;
                            case 22:
                                if (rbi != 0) {
                                    MISSION_STATUS(trk, i) += rbi;
                                    if (MISSION_STATUS(trk, i) >= rec->target) {
                                        done = 1;
                                    }
                                }
                                break;
                            case 23:
                                if (result == 10) {
                                    MISSION_STATUS(trk, i)++;
                                    if (MISSION_STATUS(trk, i) >= rec->target) {
                                        done = 1;
                                    }
                                }
                                break;
                            case 24:
                                if (ball->currentStarSwing2 != 0 && rbi != 0) {
                                    MISSION_STATUS(trk, i) += rbi;
                                    if (MISSION_STATUS(trk, i) >= rec->target) {
                                        done = 1;
                                    }
                                }
                                break;
                            case 27:
                                if (result >= 7 && result <= 10 && g_Batter.hitGeneralType == 1 && g_Batter.chargeUp >= 1.0f &&
                                    g_Batter.nonCaptainStarSwingActivated == 0) {
                                    MISSION_STATUS(trk, i)++;
                                    if (MISSION_STATUS(trk, i) >= rec->target) {
                                        done = 1;
                                    }
                                }
                                break;
                            case 28:
                                if (result == 10) {
                                    n = 0;
                                    if (g_Runners[1].runnerOnFieldOrOutOrScored != 0 &&
                                        (g_Runners[1].charID == 3 || g_Runners[1].charID == 0x27)) {
                                        n = 1;
                                    }
                                    if (g_Runners[2].runnerOnFieldOrOutOrScored != 0 &&
                                        (g_Runners[2].charID == 3 || g_Runners[2].charID == 0x27)) {
                                        n++;
                                    }
                                    if (g_Runners[3].runnerOnFieldOrOutOrScored != 0 &&
                                        (g_Runners[3].charID == 3 || g_Runners[3].charID == 0x27)) {
                                        n++;
                                    }
                                    if (n == 2) {
                                        done = 1;
                                    }
                                }
                                break;
                            case 29:
                                if (result >= 7 && result <= 10 && g_Batter.hitGeneralType == 3) {
                                    MISSION_STATUS(trk, i)++;
                                    if (MISSION_STATUS(trk, i) >= rec->target) {
                                        done = 1;
                                    }
                                }
                                break;
                            case 30:
                                if (result == 10) {
                                    for (p = 0; p < 9; p++) {
                                        if (rec->target == lbl_800E8558[inMemRoster[*(s16*)(q + 0x40)][p].stats.CharID].row &&
                                            lbl_803537E4[*(s16*)(q + 0x40)][p]._09 != 0) {
                                            MISSION_STATUS(trk, i) = -1;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                            if (done) {
                                MISSION_STATUS(trk, i) = -1;
                            }
                        }
                    }
                }
            }
        }

        // A home run also completes teammates' type-30 missions naming this batter.
        if (result == 10) {
            other = &lbl_800E8558[g_Batter.charID];
            for (p = 0; p < 9; p++) {
                mi = &lbl_800E8558[inMemRoster[*(s16*)(q + 0x40)][p].stats.CharID];
                trk = &starMissionCompletionTracker[mi->trk];
                rec = lbl_80109AE8[mi->row];
                for (i = 0; i < 10; i++, rec++) {
                    if (MISSION_STATUS(trk, i) >= 0 && rec->type == 30 &&
                        rec->target == other->row && lbl_803537E4[*(s16*)(q + 0x40)][p]._09 != 0) {
                        MISSION_STATUS(trk, i) = -1;
                    }
                }
            }
        }
    }
}
#endif


// End-of-game star mission evaluation, then the in-game statuses are folded
// into "completed" (-2) / "not completed" (0).
// NONMATCHING 87%: register allocation and switch layout differ (case 7 tested first in the original)
// .text:0x00162D54 size:0xA98
#if NONMATCHING
void fn_3_162D54(void) {
    u8* q = lbl_3_common_bss_37400;
    s32 side;
    s32 p;
    s32 i;
    s32 t;
    s32 player;
    MissionIdx* mi;
    ChallengeTrackingStruct* trk;
    MissionRec* rec;
    MissionBatterRecord* br;

    side = *(s16*)(q + 0x40) ^ g_GameLogic._000; // TODO type
    if (g_d_GameSettings.bJMatchInd != 1) {
        if (lbl_3_common_bss_32A94._4C[side] == 1) {
            player = lbl_80353A90._0BE[*(s16*)(q + 0x40)].player;
            t = lbl_800E8558[inMemRoster[*(s16*)(q + 0x40)][player].stats.CharID].trk;
            trk = &starMissionCompletionTracker[t];
            rec = lbl_80109AE8[lbl_800E8558[t].row];
            for (i = 0; i < 10; i++, rec++) {
                if (MISSION_STATUS(trk, i) >= 0) {
                    switch (rec->type) {
                    case 7:
                        if (lbl_3_common_bss_32A94._63[side] == 1) {
                            MISSION_STATUS(trk, i) = -1;
                        }
                        break;
                    case 6:
                    case 9:
                        if (lbl_803535C8[*(s16*)(q + 0x40)][player]._18 != 0) {
                            if (rec->type == 6) {
                                if (rec->target == lbl_800E8558[lbl_8034E9A0._46E4].row) {
                                    MISSION_STATUS(trk, i) = -1;
                                }
                            } else {
                                MISSION_STATUS(trk, i) = -1;
                            }
                        }
                        break;
                    case 8:
                        MISSION_STATUS(trk, i) = -1;
                        break;
                    }
                }
            }
        }

        // Batting average (type 25) and type 26 missions.
        for (p = 0; p < 9; p++) {
            br = &lbl_803537E4[*(s16*)(q + 0x40)][p];
            t = lbl_800E8558[inMemRoster[*(s16*)(q + 0x40)][p].stats.CharID].trk;
            trk = &starMissionCompletionTracker[t];
            rec = lbl_80109AE8[lbl_800E8558[t].row];
            for (i = 0; i < 10; i++, rec++) {
                if (MISSION_STATUS(trk, i) >= 0) {
                    if (rec->type == 25 && br->_04 != 0 && (br->_05 * 10) / br->_04 >= rec->target) {
                        MISSION_STATUS(trk, i) = -1;
                    }
                    if (rec->type == 26 && br->_0D == 0) {
                        MISSION_STATUS(trk, i) = -1;
                    }
                }
            }
        }

        if (g_Scores._A4 == side) {
            // Won the game.
            mi = &lbl_800E8558[lbl_80353A90._103];
            rec = lbl_80109AE8[mi->row];
            trk = &starMissionCompletionTracker[mi->trk];
            for (i = 0; i < 10; i++, rec++) {
                if (MISSION_STATUS(trk, i) >= 0 && rec->type == 1) {
                    MISSION_STATUS(trk, i) = -1;
                }
            }
            for (p = 0; p < 9; p++) {
                t = lbl_800E8558[inMemRoster[*(s16*)(q + 0x40)][p].stats.CharID].trk;
                trk = &starMissionCompletionTracker[t];
                rec = lbl_80109AE8[lbl_800E8558[t].row];
                for (i = 0; i < 10; i++, rec++) {
                    if (MISSION_STATUS(trk, i) >= 0 && rec->type == 0 && g_d_GameSettings.StadiumID == rec->target) {
                        MISSION_STATUS(trk, i) = -1;
                    }
                }
            }
        } else {
            // Lost: missions flagged "needs a win" are not completed.
            for (p = 0; p < 9; p++) {
                t = lbl_800E8558[inMemRoster[*(s16*)(q + 0x40)][p].stats.CharID].trk;
                trk = &starMissionCompletionTracker[t];
                rec = lbl_80109AE8[lbl_800E8558[t].row];
                for (i = 0; i < 10; i++, rec++) {
                    if (MISSION_STATUS(trk, i) == -1 && (rec->flags & 1)) {
                        MISSION_STATUS(trk, i) = 0;
                    }
                }
            }
        }
    }

    // Missions that need a minimum difficulty.
    for (p = 0; p < 9; p++) {
        t = lbl_800E8558[inMemRoster[*(s16*)(q + 0x40)][p].stats.CharID].trk;
        trk = &starMissionCompletionTracker[t];
        rec = lbl_80109AE8[lbl_800E8558[t].row];
        for (i = 0; i < 10; i++, rec++) {
            if (MISSION_STATUS(trk, i) == -1) {
                if (rec->flags & 2) {
                    if (g_d_GameSettings.challengeDifficulty < 1) {
                        MISSION_STATUS(trk, i) = 0;
                    }
                } else if (rec->flags & 4) {
                    if (g_d_GameSettings.challengeDifficulty < 2) {
                        MISSION_STATUS(trk, i) = 0;
                    }
                } else if ((rec->flags & 8) && g_d_GameSettings.challengeDifficulty < 3) {
                    MISSION_STATUS(trk, i) = 0;
                }
            }
        }
    }

    for (p = 0; p < 9; p++) {
        t = lbl_800E8558[inMemRoster[*(s16*)(q + 0x40)][p].stats.CharID].trk;
        trk = &starMissionCompletionTracker[t];
        rec = lbl_80109AE8[lbl_800E8558[t].row];
        for (i = 0; i < 10; i++, rec++) {
            if (MISSION_STATUS(trk, i) == -1 && (rec->flags & 0x800) && lbl_8034E9A0._46E4 != 9 &&
                *(s16*)((u8*)starMissionCompletionTracker + 0x16C2) != 0x2A) { // TODO type
                MISSION_STATUS(trk, i) = 0;
            }
        }
    }

    for (t = 0; t < 54; t++) {
        for (i = 0; i < 10; i++) {
            if (MISSION_STATUS(&starMissionCompletionTracker[t], i) <= -1) {
                MISSION_STATUS(&starMissionCompletionTracker[t], i) = -2;
            } else {
                MISSION_STATUS(&starMissionCompletionTracker[t], i) = 0;
            }
        }
    }
}
#endif

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

// Hands out the mission's bonus scout flags one at a time, round-robin from a
// random roster slot, recording each award for the results screen.
// NONMATCHING 98%: register allocation only (inlined fn_3_163D34/fn_3_163BD4/fn_3_163948 copies)
// .text:0x00163E94 size:0x578
#if NONMATCHING
void fn_3_163E94(void) {
    s16 ids[9];
    s32 i;
    u8 a;
    u8 b;
    s32 bonus;
    s32 r;
    s32 id;
    s32 m;
    u8* q = lbl_3_common_bss_37400;
    ChallengeTrackingStruct* e;
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    a = *((u8*)starMissionCompletionTracker + 0x441C);
    b = *((u8*)starMissionCompletionTracker + 0x4415);
    bonus = lbl_80109420[q[0x46]].v;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    fn_3_163D34();
    i = rand() % 9;
    r = fn_3_163BD4();
    if (bonus > 0 && r) {
        while (bonus > 0) {
            id = ids[i];
            if (id != -1) {
                m = q[i * 2 + 1];
                e = &t[id];
                if ((s8)m != 0 && (s8)q[i * 2] < (s8)m) {
                    bonus--;
                    q[i * 5 + 0x13] = *((u8*)e->scoutFlagPointer + 4 + b * 6 + a);
                    q[i * 5 + 0x12] = e->scoutFlagsAchieved;
                    q[i * 5 + 0x14]++;
                    q[i * 5 + 0x15] = 1;
                    q[i * 5 + 0x16] = id;
                    q[i * 2]++;
                }
            }
            i = (i + 1) % 9;
            if (!fn_3_163948()) {
                break;
            }
        }
    }
}
#endif

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

// Hands out the mission's bonus scout flags (lbl_80109420[].v) one at a time,
// round-robin over the roster, while some player still has flags to earn.
// NONMATCHING 98.6%: register allocation only (the inlined fn_3_163BD4 copies use one register higher)
// .text:0x00164664 size:0x410
#if NONMATCHING
void fn_3_164664(void) {
    s16 ids[9];
    s32 i;
    u8 a;
    u8 b;
    s32 bonus;
    s32 r;
    s32 m;
    ChallengeTrackingStruct* e;
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    u8* q = lbl_3_common_bss_37400;
    a = *((u8*)starMissionCompletionTracker + 0x441C);
    b = *((u8*)starMissionCompletionTracker + 0x4415);
    bonus = lbl_80109420[q[0x46]].v;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    i = 0;
    r = fn_3_163BD4();
    if (bonus > 0 && r) {
        while (bonus > 0) {
            if (ids[i] != -1) {
                e = &t[ids[i]];
                m = *((u8*)e->scoutFlagPointer + 4 + b * 6 + a);
                if ((s8)m != 0 && (s8)e->scoutFlagsAchieved < (s8)m) {
                    bonus--;
                    e->scoutFlagsAchieved++;
                }
            }
            i = (i + 1) % 9;
            if (!fn_3_163BD4()) {
                break;
            }
        }
    }
}
#endif

// Decides whether the current challenge (lbl_80109420[kind]) was cleared after a play
// and hands out its scout flag reward.
// NONMATCHING 88%: register allocation; the original also preloads the scout-flag indices and g_Runners
// at entry and compares the award flags signed
// .text:0x00164A74 size:0xE7C
#if NONMATCHING
void fn_3_164A74(void) {
    MissionChallengeState* st = (MissionChallengeState*)lbl_3_common_bss_37400; // TODO type
    s32 reward = 0;
    s32 outcome = 0;
    s32 forced;
    s8 v;
    s32 j;
    ChallengeTrackingStruct* e;
    u8 m;

    st->result = 1;
    st->bonus = lbl_80109420[st->kind].v;
    switch (st->kind) {
    case 1:
        if (g_FieldingLogic._107 != 0) {
            if (g_Strikes.outs >= 3) {
                st->result = 2;
            } else if (g_Pitcher.strikeOutOrWalk == 1) {
                st->_48 = 0;
            } else {
                st->result = 0;
            }
        } else if ((g_Strikes.outs > g_Strikes.storedOuts && lbl_3_common_bss_32A94._22 == 0) ||
                   g_Pitcher.strikeOutOrWalk == 1) {
            if (g_Pitcher.strikeOutOrWalk == 1 || lbl_3_common_bss_32A94._24 == 0xE) {
                reward = 1;
                st->result = 2;
            } else {
                reward = 0;
                st->result = 2;
            }
        }
        break;
    case 2:
        if (g_FieldingLogic._107 != 0) {
            if (g_Strikes.outs >= 3) {
                st->_48 = 0;
            } else if (g_Pitcher.strikeOutOrWalk == 1) {
                st->_48 = 0;
            } else {
                st->result = 0;
            }
        } else if ((g_Strikes.allForcedRunnersReachedTheirBaseInd == 1 || lbl_3_common_bss_32A94._22 >= 1) &&
                   lbl_3_common_bss_32A94._24 == 0 && lbl_3_common_bss_32A94._20 <= 0) {
            if (lbl_3_common_bss_32A94._23 == 1) {
                if ((u8)lbl_3_common_bss_32A94._26 == 1) {
                    reward = 1;
                } else if ((u8)lbl_3_common_bss_32A94._26 >= 2) {
                    reward = 2;
                } else {
                    reward = 0;
                }
            } else if (lbl_3_common_bss_32A94._23 == 2) {
                reward = 1;
            } else if (lbl_3_common_bss_32A94._23 >= 3) {
                reward = 2;
            }
            st->result = 2;
        }
        break;
    case 3:
        if (g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] > g_Scores._A0 || g_Ball.deadBallReason == 1 ||
            ((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) && g_RunningLogic._12 >= 4)) {
            st->result = 2;
            st->_48 = 0;
        } else if (g_Strikes.outs >= 3 ||
                   (g_Strikes.outs == 2 && g_Pitcher.strikeOutOrWalk == 1 && g_FieldingLogic._107 == 0)) {
            st->_48 = 0;
        } else {
            st->_48 = 1;
            st->result = 0;
        }
        break;
    case 4: {
        s16 batting = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
        if (g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] > batting ||
            (g_Ball.deadBallReason == 1 && g_Scores._A0 + g_RunningLogic._12 > batting) ||
            ((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) && g_RunningLogic._12 >= 4 &&
             g_Scores._A0 == batting)) {
            st->result = 2;
            st->_48 = 0;
        } else if (g_Strikes.outs >= 3 || (g_Strikes.outs == 2 && g_Pitcher.strikeOutOrWalk == 1)) {
            st->_48 = 0;
        } else {
            st->_48 = 1;
            st->result = 0;
        }
        break;
    }
    case 5:
        if (g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] > g_Scores._A0 || g_Ball.deadBallReason == 1 ||
            (g_RunningLogic.occupiedBases == 0x1111 && (g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3))) {
            st->_48 = 0;
        } else if ((g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == 1 && g_FieldingLogic._107 == 0) ||
                   g_Strikes.outs >= 3) {
            st->result = 2;
            st->_48 = 0;
        } else {
            st->_48 = 1;
            st->result = 0;
        }
        break;
    case 6:
        if (g_Strikes.outs >= g_Strikes.storedOuts + 2) {
            st->result = 2;
            st->_48 = 0;
        } else if (g_FieldingLogic._107 != 0) {
            st->_48 = 1;
            st->result = 0;
        } else {
            st->_48 = 0;
        }
        break;
    case 7:
        if (g_Pitcher.strikeOutOrWalk == 1) {
            st->result = 2;
            st->_48 = 0;
        } else if (g_FieldingLogic._107 != 0) {
            if (g_Strikes.outs >= 3) {
                st->_48 = 0;
            } else {
                st->_48 = 1;
                st->result = 0;
            }
        }
        break;
    case 8:
        if (lbl_3_common_bss_32A94._61 == 3 &&
            ((g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == 1 && g_FieldingLogic._107 == 0) || g_Strikes.outs >= 3)) {
            st->result = 2;
            st->_48 = 0;
        } else {
            forced = 0;
            if (g_Ball.deadBallReason == 3) {
                if (g_RunningLogic.occupiedBases & 0x1100) {
                    forced = 1;
                }
            } else if (g_Ball.deadBallReason == 4) {
                if (g_RunningLogic.occupiedBases & 0x1100) {
                    forced = 1;
                } else {
                    if (g_Runners[1].runnerOnFieldOrOutOrScored == 1 && g_Runners[1].baseReachedAtTimeOfThrow >= 2) {
                        forced = 1;
                    }
                    if (g_Runners[0].runnerOnFieldOrOutOrScored == 1 && g_Runners[0].baseReachedAtTimeOfThrow >= 2) {
                        forced = 1;
                    }
                }
            }
            if (lbl_3_common_bss_32A94._61 == 3 && g_FieldingLogic._107 == 0) {
                st->_48 = 0;
            } else if (g_Scores._A0 < g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0]) {
                st->_48 = 0;
            } else if (g_Ball.deadBallReason == 1 || forced) {
                st->_48 = 0;
            } else {
                st->_48 = 1;
                st->result = 0;
            }
        }
        break;
    case 9:
        if (lbl_3_common_bss_32A94._24 == 1) {
            st->result = 2;
            st->_48 = 0;
        } else if (g_FieldingLogic._107 != 0) {
            if (g_Strikes.outs >= 3) {
                st->_48 = 0;
            } else if (g_Pitcher.strikeOutOrWalk == 1) {
                st->_48 = 0;
            } else {
                st->_48 = 1;
                st->result = 0;
            }
        } else {
            st->_48 = 0;
        }
        break;
    case 10:
        if (g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] > g_Scores._A0 &&
            g_Runners[3].furthestBaseForcedToGoToOnWalk != 0 && g_Ball.maybeBuntInd != 0) {
            outcome = 1;
        }
        if (outcome) {
            st->result = 2;
            st->_48 = 0;
        } else if (g_FieldingLogic._107 != 0) {
            if (g_Strikes.outs >= 3) {
                st->_48 = 0;
            } else if (g_Pitcher.strikeOutOrWalk == 1) {
                st->_48 = 0;
            } else if (g_Runners[3].runnerOnFieldOrOutOrScored != 1) {
                st->_48 = 0;
            } else {
                st->_48 = 1;
                st->result = 0;
            }
        } else {
            st->_48 = 0;
        }
        break;
    case 11:
        if (g_FieldingLogic._107 == 1 || g_FieldingLogic._107 == 2) {
            if ((g_Runners[1].runnerOnFieldOrOutOrScored == 1 || g_Runners[1].runnerOnFieldOrOutOrScored == 3) &&
                g_Runners[1].currentBase > 1) {
                outcome = 1;
            }
            if (g_Runners[1].runnerOnFieldOrOutOrScored == 2) {
                outcome = 2;
            }
        }
        if (outcome == 2) {
            st->result = 1;
            st->_48 = 0;
        } else if (outcome != 0) {
            st->result = 2;
            st->_48 = 0;
        } else if (g_FieldingLogic._107 != 0) {
            if (g_Strikes.outs >= 3) {
                st->_48 = 0;
            } else if (g_Pitcher.strikeOutOrWalk == 1) {
                st->_48 = 0;
            } else {
                st->_48 = 1;
                st->result = 0;
            }
        } else {
            st->_48 = 0;
        }
        break;
    case 12:
        if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            if ((g_GameLogic._000 ^ (g_Scores._A4 == g_d_GameSettings.humanTeamNumber)) != 0 && g_Scores._A4 != 2) {
                st->result = 2;
            } else {
                st->result = 1;
            }
            st->_48 = 0;
        } else if (g_Scores.inning >= g_Scores.maxInnings && g_Scores._AD != 0) {
            if (g_Ball.deadBallReason == 1 &&
                g_Scores._A0 + g_RunningLogic._12 > g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0]) {
                if (g_GameLogic.teamBatting == g_d_GameSettings.humanTeamNumber) {
                    st->result = 2;
                }
                st->_48 = 0;
            } else if (g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == 1) {
                if ((g_Scores.team[1].runs[0] > g_Scores.team[0].runs[0] && st->team == g_GameLogic.teamBatting) ||
                    (g_Scores.team[1].runs[0] < g_Scores.team[0].runs[0] && st->team == g_GameLogic.teamFielding)) {
                    st->result = 2;
                }
                st->_48 = 0;
            } else if (g_RunningLogic._10 == 4 && (g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3)) {
                if (g_Scores.team[1].runs[0] == g_Scores.team[0].runs[0]) {
                    if (g_GameLogic.teamBatting == g_d_GameSettings.humanTeamNumber) {
                        st->result = 2;
                    }
                    st->_48 = 0;
                } else {
                    st->_48 = 1;
                    st->result = 0;
                }
            } else {
                st->_48 = 1;
                st->result = 0;
            }
        } else {
            st->_48 = 1;
            st->result = 0;
        }
        break;
    }

    if (st->result == 2) {
        if (st->kind == 2 || st->kind == 1) {
            // Reward (lbl_80109420[kind].v + reward) for the scouted character.
            v = (&lbl_80109420[st->kind].v)[reward];
            e = &starMissionCompletionTracker[*((u8*)starMissionCompletionTracker + 0x43C0)]; // TODO type
            for (j = 0; j < 9; j++) {
                if (st->award[j].active == 1) {
                    st->award[j].bonus = v;
                }
            }
            e->scoutFlagsAchieved += v;
            m = *((u8*)e->scoutFlagPointer + 4 + *((u8*)starMissionCompletionTracker + 0x4415) * 6 +
                  *((u8*)starMissionCompletionTracker + 0x441C));
            if ((s8)e->scoutFlagsAchieved > (s8)m) {
                e->scoutFlagsAchieved = m;
            }
        } else {
            fn_3_164554();
        }
    }
}
#endif
