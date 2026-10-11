#include "game/auto_00_001658F0_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "game/auto_00_00097144_text.h"
#include "game/auto_00_0009CD90_text.h"
#include "game/rep_3DA8.h"
#include "game/rep_3310.h"
#include "main/file_80069BDC.h"
#include "main/file_80011640.h"
#include "Dolphin/rand.h"

extern StarChanceState lbl_3_common_bss_37400;
extern StarChanceOdds lbl_80109420[];

void fn_3_163E94(void);

#define SCOUT_FLAGS(t) ((ScoutFlagTable*)(t)->scoutFlagPointer)

// .text:0x001658F0 size:0x88 mapped:0x807A4984
void fn_3_1658F0(void) {
    StarChanceState* sc = &lbl_3_common_bss_37400;
    s32 i;

    for (i = 0; i < 9; i++) {
        sc->slots[i].target = 0;
        sc->slots[i].achieved = 0;
        sc->slots[i].bonus = 0;
        sc->slots[i].active = 0;
        sc->slots[i].charID = 0;
        sc->_00[i][0] = 0;
        sc->_00[i][1] = 0;
    }
}

// .text:0x00165978 size:0x14 mapped:0x807A4A0C
void fn_3_165978(void) {
    lbl_3_common_bss_37400.retry = 0;
}

// .text:0x0016598C size:0x14 mapped:0x807A4A20
void fn_3_16598C(void) {
    lbl_3_common_bss_37400.retry = 0;
}

// .text:0x001659A0 size:0x384 mapped:0x807A4A34
// NONMATCHING 96%: r28 saved in the original but unused; the CPU-roster id copy is unrolled
// with a second base register (0x1E0) in ours.
#if NONMATCHING
// Character ids of the CPU team's roster.
static inline void gatherCpuIds(s16* ids) {
    s32 i;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
}

// Whether the batter/pitcher this chance is about still has scout flags to earn.
static inline BOOL starChanceCharHasFlags(u8 difficulty) {
    ChallengeState* cs = &gChallengeState;
    StarChanceState* sc = &lbl_3_common_bss_37400;
    InMemBatterType* batter = &g_Batter;
    InMemPitcherType* pitcher = &g_Pitcher;
    u8 row = cs->_441C;
    s16 ids[9];
    s32 i;
    s32 charID;
    s32 found = 0; // the original never clears it (stale register)

    gatherCpuIds(ids);
    if (sc->type == 2) {
        charID = pitcher->charID;
    } else if (sc->type == 1) {
        charID = batter->charID;
    }
    for (i = 0; i < 9; i++) {
        if (charID == ids[i] && SCOUT_FLAGS(&cs->trackers[ids[i]])->flags[difficulty][row] != 0) {
            found = 1;
        }
    }
    return found;
}

// Whether anyone on the CPU team still has scout flags to earn.
static inline BOOL starChanceTeamHasFlags(u8 difficulty) {
    ChallengeState* cs = &gChallengeState;
    u8 row = cs->_441C;
    s16 ids[9];
    s32 i;
    s32 found;
    ChallengeTrackingStruct* t;
    s8 target;

    gatherCpuIds(ids);
    found = 0;
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1) {
            t = &cs->trackers[ids[i]];
            target = SCOUT_FLAGS(t)->flags[difficulty][row];
            if (target != 0 && (s8)t->scoutFlagsAchieved < target) {
                found = 1;
            }
        }
    }
    return found;
}

// Whether a star chance of the given type should start: someone still has scout flags
// to earn, then a roll against lbl_80109420[type].
BOOL fn_3_1659A0(s32 type) {
    StarChanceState* sc = &lbl_3_common_bss_37400;
    u8 difficulty = gChallengeState._4415;
    BOOL found;
    s32 roll;
    s32 odds;

    if (sc->type == 2 || sc->type == 1) {
        found = starChanceCharHasFlags(difficulty);
    } else {
        found = starChanceTeamHasFlags(difficulty);
    }
    if (!found) {
        return FALSE;
    }
    roll = rand() % 100;
    if (sc->retry == 0) {
        odds = lbl_80109420[type].chance[difficulty];
    } else {
        odds = lbl_80109420[type].retryChance[difficulty];
    }
    if (roll <= odds) {
        return TRUE;
    }
    return FALSE;
}
#endif

// .text:0x00165D24 size:0x688 mapped:0x807A4DB8
// NONMATCHING 94%: the original re-tests teamBatting != human with a materialised bool
// (cntlzw/xori), passes a stale r3 to fn_3_16440C, and keeps the 6/7 cases in its switch tree.
// Matching also needs the fn_3_1659A0 calls made through a cast so it is not inlined.
#if NONMATCHING
// Picks the star chance for this at-bat (sets lbl_3_common_bss_37400.type); returns TRUE when one starts.
BOOL fn_3_165D24(void) {
    GameControlsStruct* gl = &g_GameLogic;
    ChallengeState* cs = &gChallengeState;
    StarChanceState* sc = &lbl_3_common_bss_37400;
    InMemRunnerType* runners = g_Runners;
    InMemBatterType* batter = &g_Batter;
    InMemPitcherType* pitcher = &g_Pitcher;
    s16 scoutChar = 0;
    s32 row;
    s32 difficulty;
    ChallengeTrackingStruct* t;
    s8 target;

    sc->_47 = 0;
    row = cs->_441C;
    sc->_42 = 0;
    difficulty = cs->_4415;

    if (sc->state != 0) {
        if (sc->state == 2) {
            sc->type = 0;
            sc->state = 0;
            return FALSE;
        }
        switch (sc->type) {
        case 6:
        case 7:
            break;
        case 8:
            if (lbl_3_common_bss_32A94._48[0x19] >= 4 || g_Scores.team[gl->homeTeamBattingInd_fieldingTeam].runs[g_Scores.inning] != 0) {
                sc->type = 0;
                sc->state = 0;
            }
            break;
        case 9:
        case 10:
            if (sc->runnerRosterID != runners[3].rosterID || g_Strikes.outs == 2) {
                sc->type = 0;
                sc->state = 0;
            }
            break;
        case 11:
            if (sc->runnerRosterID != runners[1].rosterID) {
                sc->type = 0;
                sc->state = 0;
            }
            break;
        }
        return FALSE;
    }

    sc->type = 0;
    lbl_3_common_bss_34C58._32 = 0;
    if (g_d_GameSettings.bJMatchInd == 1) {
        if (fn_3_1659A0(12)) {
            sc->type = 12;
        }
    } else if (gl->teamBatting == g_d_GameSettings.humanTeamNumber) {
        s32* captains = gl->Team_CaptainRosterLoc;

        if (g_RunningLogic._10 >= 2 && batter->rosterID == captains[gl->teamBatting] &&
            pitcher->rosterID == captains[gl->teamFielding]) {
            if (fn_3_1659A0(3)) {
                sc->type = 3;
            }
        } else if (g_RunningLogic._10 >= 2 &&
                   g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] < g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0] &&
                   g_Scores._A6 <= 3) {
            if (fn_3_1659A0(4)) {
                sc->type = 4;
            }
        } else if ((g_RunningLogic._00 & 0x1000) && g_Strikes.outs <= 1) {
            u8 cls = g_Batter.characterClass;
            if (cls == 0 || cls == 1) {
                if (fn_3_1659A0(9)) {
                    sc->type = 9;
                }
            } else if (cls == 2 || cls == 3) {
                if (fn_3_1659A0(10)) {
                    sc->type = 10;
                }
            }
        } else if (g_RunningLogic._00 == 0x11 && inMemRoster[g_GameLogic.teamBatting][runners[1].rosterID].stats.CharacterClass == 2) {
            if (fn_3_1659A0(11)) {
                sc->type = 11;
            }
        } else {
            scoutChar = pitcher->scoutFlagRelated;
            if (scoutChar != -1) {
                t = &cs->trackers[scoutChar];
                target = SCOUT_FLAGS(t)->flags[difficulty][row];
                if (target != 0 && (s8)t->scoutFlagsAchieved < target) {
                    if (fn_3_1659A0(2)) {
                        sc->type = 2;
                    }
                }
            }
        }
    } else {
        if (g_RunningLogic._10 >= 3 && g_Scores.team[g_Scores._AD].runs[g_Scores.inning] == 0) {
            if (fn_3_1659A0(5)) {
                sc->type = 5;
            }
        } else if ((g_RunningLogic._00 & 0x10) && g_Strikes.outs <= 1) {
            if (fn_3_1659A0(6)) {
                sc->type = 6;
            }
        } else if (g_Batter.rosterID == g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamBatting]) {
            if (fn_3_1659A0(7)) {
                sc->type = 7;
            }
        } else if (g_Scores._C6 == 1) {
            if (fn_3_1659A0(8)) {
                sc->type = 8;
            }
        } else {
            scoutChar = batter->charIDForScoutFlagMission;
            if (scoutChar != -1) {
                t = &cs->trackers[scoutChar];
                target = SCOUT_FLAGS(t)->flags[difficulty][row];
                if (target != 0 && (s8)t->scoutFlagsAchieved < target) {
                    if (fn_3_1659A0(1)) {
                        sc->type = 1;
                    }
                }
            }
        }
    }

    switch (sc->type) {
    case 9:
        sc->runnerRosterID = runners[3].rosterID;
        break;
    case 10:
        sc->runnerRosterID = runners[3].rosterID;
        break;
    case 11:
        sc->runnerRosterID = runners[1].rosterID;
        break;
    }

    if (sc->type != 0) {
        fn_3_1658F0();
        if (sc->type == 2 || sc->type == 1) {
            fn_3_16440C(scoutChar);
        } else {
            fn_3_163E94();
        }
        cs->_43C0 = scoutChar;
        cs->_44F1 = 1;
        lbl_3_common_bss_32724._B3 = 1;
        g_GameLogic.IsStarChance = 0;
        lbl_3_common_bss_32724._AC = 0;
        lbl_3_common_bss_37400.retry = 0;
        return TRUE;
    }
    return FALSE;
}
#endif

// .text:0x001663AC size:0x9C mapped:0x807A5440
void fn_3_1663AC(void) {
    CharMgr* mgr;
    s32 i;

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU ||
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_LOAD_PRACTICE_SCREEN) {
        mgr = &lbl_8036E548;
        if (mgr->_3078 != 0) {
            for (i = 0; i < mgr->_3078; i++) {
                if (&mgr->trail2[i] != NULL) {
                    mgr->trail2[i]._26 = 0;
                }
            }
        }
    } else if (g_Practice.practiceLevel == 4) {
        fn_3_11AB2C();
    }
}
