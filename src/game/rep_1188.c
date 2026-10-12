#include "game/rep_1188.h"
#define REP_HEADER_FN repHeader_1188
#include "header_rep_inline.h"

#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_800639BC.h"
#include "main/menu_globals.h" // SavedSettings

// The saved match settings (gameInitOptions has no symbol: it is this object).
extern SavedSettings lbl_800E8754;

extern u8 aILevel[4];
extern f32 runnerVelocityLookup[];
extern f32 lbl_3_data_4BC4[];
extern s16 lbl_3_data_4C54[];
extern const f32 lbl_3_rodata_11D8;
extern const f32 lbl_3_rodata_11DC;
extern const f32 lbl_3_rodata_11E0;

// .text:0x0006D6D4 size:0x290 mapped:0x806AC768
void fn_3_6D6D4(int idx) {
    InMemRunnerType* r = &g_Runners[idx];
    s32 lo = r->speed / 10;
    s32 base = lo * 10;
    s32 hi = base + 10;
    r->maximumBaseVelocity = LinearInterpolateToNewRange(r->speed, base, hi,
                                                         runnerVelocityLookup[base / 10],
                                                         runnerVelocityLookup[hi / 10]);
    r->baseAcceleration = LinearInterpolateToNewRange(r->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC, lbl_3_data_4BC4[0], lbl_3_data_4BC4[1]);
    r->baseAccelerationWhileChaingingDirection =
        LinearInterpolateToNewRange(r->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC, lbl_3_data_4BC4[2], lbl_3_data_4BC4[3]);
    r->maxMashVeloAdjustment = LinearInterpolateToNewRange(r->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC, lbl_3_data_4BC4[4], lbl_3_data_4BC4[5]);
    r->percentAddedPerMash =
        lbl_3_rodata_11E0 / LinearInterpolateToNewRange(r->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC, lbl_3_data_4BC4[6], lbl_3_data_4BC4[7]);
    r->stamina_MashPercentTakenAwayPerFrame =
        lbl_3_rodata_11E0 / LinearInterpolateToNewRange(r->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC, lbl_3_data_4BC4[8], lbl_3_data_4BC4[9]);
    r->FramesUntilNotSprinting = lbl_3_data_4C54[7];
}

// .text:0x0006D964 size:0x4FC mapped:0x806AC9F8
// setInMemRunnerConstants: fills g_Runners[runnerIdx] from the batting team's roster entry.
extern u8 lbl_3_data_775C; // delay before starting to run

void fn_3_6D964(int rosterID, int runnerIdx) {
    int index;
    CharacterStats* char_stats = &inMemRoster[g_GameLogic.teamBatting][rosterID];
    InMemRunnerType* r = &g_Runners[runnerIdx];
    ChallengeTrackingStruct* starMissions = starMissionCompletionTracker;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2 ||
            g_Practice.practiceType_2 == 3) {
            char_stats = &inMemRoster[g_GameLogic.teamBatting][rosterID];
        }
    } else if (g_d_GameSettings.minigamesEnabled) {
        char_stats = &inMemRoster[0][rosterID];
    }

    r->rosterID = rosterID;
    r->charID = char_stats->stats.CharID;
    r->speed = char_stats->stats.Speed;
    r->weight = char_stats->stats.Weight;
    r->delayBeforeStartingToRun = lbl_3_data_775C;
    r->aIStrength0Special3Weak = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];
    r->characterClass = char_stats->stats.CharacterClass;
    if (r->speed > 200) {
        r->speed = 200;
    }

    if (!g_d_GameSettings.exhibitionMatchInd) {
        r->unused_starMissionCharID = -1;
        for (index = 0; index < 54; index++) {
            if ((r->charID == index) && (starMissions[index].variantClassification <= 3)) {
                r->unused_starMissionCharID = index;
                break;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 idx = g_Minigame.minigameControlStruct[0].characterIndex[rosterID];
        if (g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
            r->aIStrength0Special3Weak = aILevel[g_Minigame.minigameControlStruct[0].aIStrength[idx]];
        }
    }

    fn_3_6D6D4(runnerIdx);
}

// .text:0x0006DE60 size:0x374 mapped:0x806ACEF4
void setInMemBatterConstants(int rosterID) {
    int battingOrderCounter;
    int index;
    int batterID;

    CharacterStats* char_stats = &inMemRoster[g_GameLogic.teamBatting][rosterID];
    ChallengeTrackingStruct* starMissions = starMissionCompletionTracker;
    g_Batter.easyBatting = 0;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2 ||
            g_Practice.practiceType_2 == 3) {
            char_stats = inMemRoster[g_GameLogic.teamBatting];
        }
    } else if (g_d_GameSettings.minigamesEnabled) {
        rosterID = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID];
        char_stats = &inMemRoster[0][rosterID];
    } else {
        g_Batter.easyBatting =
            lbl_800E8754.port[g_d_GameSettings.PlayerPorts[g_GameLogic.teamBatting] % 4]._6; // easy batting
    }

    g_Batter.rosterID = rosterID;
    g_Batter.charID = char_stats->stats.CharID;
    g_Batter.contactSize_raw[BAT_CONTACT_TYPE_SLAP] = char_stats->stats.SlapContactSize;
    g_Batter.contactSize_raw[BAT_CONTACT_TYPE_CHARGE] = char_stats->stats.ChargeContactSize;
    g_Batter.hitPower_raw[BAT_CONTACT_TYPE_SLAP] = char_stats->stats.SlapHitPower;
    g_Batter.hitPower_raw[BAT_CONTACT_TYPE_CHARGE] = char_stats->stats.ChargeHitPower;
    g_Batter.buntingContactSize = char_stats->stats.BuntingContactSize;
    g_Batter.trajectoryPushPull = char_stats->stats.HitTrajectoryPushPull;
    g_Batter.trajectoryHighLow = char_stats->stats.HitTrajectoryHighLow;
    g_Batter.batterHand = char_stats->stats.BattingStance;
    g_Batter.characterClass = char_stats->stats.CharacterClass;
    g_Batter.trimmedBat = BatterHitbox[g_Batter.charID].TrimmedBat;
    g_Batter.chemLinksOnBase = 0;
    g_Batter.aiLevel = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];

    if (g_d_GameSettings.minigamesEnabled) {
        g_Batter.captainStarHitPitch = 0;
        g_Batter.noncaptainStarSwing = 0;
    } else {
        g_Batter.captainStarHitPitch = (char_stats->stats).CaptainStarHitPitch;
        g_Batter.noncaptainStarSwing = (char_stats->stats).NonCaptainStarSwing;
    }

    if (!g_d_GameSettings.exhibitionMatchInd) {
        g_Batter.charIDForScoutFlagMission = -1;
        for (index = 0; index < 54; index++) {
            if ((g_Batter.charID == index) && (starMissions[index].variantClassification <= 3)) {
                g_Batter.charIDForScoutFlagMission = index;
                break;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 bVar1;
        // This should match target's struct access pattern
        if (g_Minigame.battingHandedness[rosterID] & 1) {
            g_Batter.batterHand = 1;
        } else {
            g_Batter.batterHand = 0;
        }

        bVar1 = g_Minigame.minigameControlStruct[0].characterIndex[rosterID];

        if (g_Minigame.minigameControlStruct[0].battingHandedness[bVar1] != 0) {
            g_Pitcher.aiLevel = aILevel[g_Minigame.minigameControlStruct[0].aIStrength[bVar1]];
        }
    }
}

// .text:0x0006E1D4 size:0x78 mapped:0x806AD268
extern u8 lbl_3_data_4744[];
extern s32 LERPToNewRange_Float(s32 v, s32 lo, s32 hi, s32 a, s32 b);

u8 fn_3_6E1D4(u8 v) {
    s32 lo = (v / 10) * 10;
    s32 hi = lo + 10;
    return LERPToNewRange_Float(v, lo, hi, lbl_3_data_4744[lo / 10], lbl_3_data_4744[hi / 10]);
}

// .text:0x0006E24C size:0x968 mapped:0x806AD2E0
// setInMemFielderConstants: fills g_Fielders[fielderIdx] from the fielding team's roster entry.
extern InMemFielderView g_Fielders[9];
extern f32 lbl_3_data_4640[2][22]; // fielder max velocity by speed/10 ([1] in game mode 6)
extern s16 lbl_3_data_79B4[55][8]; // reach per character (x0.01), row 54 = minimums
extern s16 lbl_3_data_7F10[54];

static inline u32 fielderAbilities(int rosterID) {
    int team = g_GameLogic.teamFielding;
    if (g_d_GameSettings.minigamesEnabled) {
        team = 0;
    }
    return inMemRoster[team][rosterID].stats.FieldingStats;
}

// NONMATCHING 99%: the original keeps &g_GameLogic in r30 for the captain check instead of
// re-materializing it, and schedules the reach loads slightly differently
#if NONMATCHING
void fn_3_6E24C(int rosterID, int fielderIdx) {
    int index;
    f32 r2;
    f32 third;
    InMemFielderView* f = &g_Fielders[fielderIdx];
    CharacterStats* char_stats = &inMemRoster[g_GameLogic.teamFielding][rosterID];
    ChallengeTrackingStruct* starMissions = starMissionCompletionTracker;
    s16 charID;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2 ||
            g_Practice.practiceType_2 == 3) {
            char_stats = &inMemRoster[g_GameLogic.teamFielding][fielderIdx];
        }
    } else if (g_d_GameSettings.minigamesEnabled) {
        char_stats = &inMemRoster[0][g_Minigame.minigameControlStruct[0].characterIndex[rosterID]];
    }

    f->rosterID = rosterID;
    f->charID = charID = char_stats->stats.CharID;
    f->handedness = char_stats->stats.FieldingArm;
    f->weight = char_stats->stats.Weight;
    f->aiLevel = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam];

    if (fielderAbilities(f->rosterID) >> 7 & 1) { // FIELDING_ABILITIES_MAGICAL_CATCH
        f->catchType = 5;
    } else {
        f->catchType = f->weight;
    }

    if (!g_d_GameSettings.exhibitionMatchInd) {
        f->starMissionCharID = -1;
        for (index = 0; index < 54; index++) {
            if ((f->charID == index) && (starMissions[index].variantClassification <= 3)) {
                f->starMissionCharID = index;
                break;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 idx = g_Minigame.minigameControlStruct[0].characterIndex[rosterID];
        if (g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
            f->aiLevel = aILevel[g_Minigame.minigameControlStruct[0].aIStrength[idx]];
        }
    }

    if (g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding] == f->rosterID) {
        f->opponentIdx = 0;
    } else {
        f->opponentIdx = ++g_GameLogic.rosterLoc_skippingCap;
    }

    if (g_d_GameSettings.minigamesEnabled) {
        if (g_Minigame.battingHandedness[rosterID] <= 1) {
            f->handedness = 0;
        } else {
            f->handedness = 1;
        }
    }

    f->speed = char_stats->stats.Speed;
    if (f->speed > 200) {
        f->speed = 200;
    }
    {
        u8 spd = f->speed;
        s32 lo = (spd / 10) * 10;
        s32 hi = lo + 10;
        if (g_d_GameSettings.GameModeSelected == 6) {
            f->maxVelocity = LinearInterpolateToNewRange(spd, lo, hi, lbl_3_data_4640[1][lo / 10], lbl_3_data_4640[1][hi / 10]);
        } else {
            f->maxVelocity = LinearInterpolateToNewRange(spd, lo, hi, lbl_3_data_4640[0][lo / 10], lbl_3_data_4640[0][hi / 10]);
        }
    }
    f->velocityPerWeight = f->maxVelocity / f->_1D1;

    f->throwingArm = char_stats->stats.ThrowingArm;
    {
        s32 lo = (f->throwingArm / 10) * 10;
        s32 hi = lo + 10;
        f->throwStrength = LERPToNewRange_Float(f->throwingArm, lo, hi, lbl_3_data_4744[lo / 10], lbl_3_data_4744[hi / 10]);
    }
    if (f->throwStrength > 200) {
        f->throwStrength = 200;
    }

    f->characterClass = char_stats->stats.CharacterClass;
    f->wallAbility = 0;
    if (fielderAbilities(f->rosterID) & FIELDING_ABILITIES_WALL_SPLAT) {
        f->wallAbility = 1;
    } else {
        if (fielderAbilities(f->rosterID) >> 1 & 1) { // FIELDING_ABILITIES_WALL_JUMP
            f->wallAbility = 2;
        } else {
            if (fielderAbilities(f->rosterID) & FIELDING_ABILITIES_CLAMBER) {
                f->wallAbility = 3;
            }
        }
    }

    f->superJump = 0;
    if (fielderAbilities(f->rosterID) & FIELDING_ABILITIES_SUPER_JUMP) {
        f->superJump = 1;
    }

    f->reach[0] = 0.01f * lbl_3_data_79B4[charID][0] * charSizeMultipliers[charID][0];
    f->reach[1] = 0.01f * lbl_3_data_79B4[charID][1] * charSizeMultipliers[charID][0];
    f->reach[2] = 0.01f * lbl_3_data_79B4[charID][2] * charSizeMultipliers[charID][0];
    f->reach[3] = 0.01f * lbl_3_data_79B4[charID][3] * charSizeMultipliers[charID][0];
    f->reach[6] = 0.01f * lbl_3_data_79B4[charID][5] * charSizeMultipliers[charID][0];
    r2 = 0.01f * lbl_3_data_79B4[charID][2] * charSizeMultipliers[charID][0];
    third = r2 / 3.0f;
    f->reach[7] = 0.01f * lbl_3_data_79B4[charID][6] * charSizeMultipliers[charID][0];
    f->reach[8] = 0.01f * lbl_3_data_79B4[charID][7] * charSizeMultipliers[charID][0];
    f->reach[4] = r2 + third;
    f->reach[5] = r2 - third;
    if (f->reach[0] < 0.01f * lbl_3_data_79B4[54][0]) {
        f->reach[0] = 0.01f * lbl_3_data_79B4[54][0];
    }
    if (f->reach[3] < 0.01f * lbl_3_data_79B4[54][1]) {
        f->reach[3] = 0.01f * lbl_3_data_79B4[54][1];
    }
    if (f->reach[6] < 0.01f * lbl_3_data_79B4[54][3]) {
        f->reach[6] = 0.01f * lbl_3_data_79B4[54][3];
    }
    if (f->reach[7] < 0.01f * lbl_3_data_79B4[54][4]) {
        f->reach[7] = 0.01f * lbl_3_data_79B4[54][4];
    }
    if (f->reach[8] < 0.01f * lbl_3_data_79B4[54][5]) {
        f->reach[8] = 0.01f * lbl_3_data_79B4[54][5];
    }
    f->_16C = 0.01f * lbl_3_data_7F10[charID] * charSizeMultipliers[charID][0];
}
#endif

// .text:0x0006EBB4 size:0x368 mapped:0x806ADC48
// setInMemPitcherConstants: pitcher counterpart of setInMemBatterConstants.
// Default pitcher stats used when no pitcher is selected (rosterID < 0):
// curve ball speed, fast ball speed, cursed ball, curve control, curve, captain star pitch.
extern s16 lbl_3_data_460C[6];

void fn_3_6EBB4(int rosterID) {
    int index;
    CharacterStats* char_stats;
    CharacterStats* team = inMemRoster[g_GameLogic.teamFielding];
    ChallengeTrackingStruct* starMissions = starMissionCompletionTracker;

    char_stats = &team[rosterID];
    if (rosterID < 0) {
        g_Pitcher.rosterID = 0;
        g_Pitcher.charID = 0;
        g_Pitcher.handedness = 0;
        g_Pitcher.curveBallSpeed = lbl_3_data_460C[0];
        g_Pitcher.fastBallSpeed = lbl_3_data_460C[1];
        g_Pitcher.cursedBallStat = lbl_3_data_460C[2];
        g_Pitcher.curveControlStat = lbl_3_data_460C[3];
        g_Pitcher.curveStat = lbl_3_data_460C[4];
        g_Pitcher.captainStarPitch = lbl_3_data_460C[5];
        return;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2 ||
            g_Practice.practiceType_2 == 3) {
            rosterID = 0;
            char_stats = &team[g_Minigame.minigamePlayerSelectedOrder];
        }
    } else if (g_d_GameSettings.minigamesEnabled) {
        rosterID = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        char_stats = &inMemRoster[0][rosterID];
    }

    g_Pitcher.rosterID = rosterID;
    g_Pitcher.charID = (u8)char_stats->stats.CharID;
    g_Pitcher.handedness = char_stats->stats.FieldingArm;
    g_Pitcher.curveBallSpeed = char_stats->stats.CurveBallSpeed;
    g_Pitcher.fastBallSpeed = char_stats->stats.FastBallSpeed;
    g_Pitcher.cursedBallStat = char_stats->stats.cursedBall;
    g_Pitcher.curveControlStat = char_stats->stats.curveControl;
    g_Pitcher.curveStat = char_stats->stats.Curve;
    g_Pitcher.charClass = char_stats->stats.CharacterClass;
    g_Pitcher.aiLevel = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam];

    if (!g_d_GameSettings.exhibitionMatchInd) {
        g_Pitcher.scoutFlagRelated = -1;
        for (index = 0; index < 54; index++) {
            if ((g_Pitcher.charID == index) && (starMissions[index].variantClassification <= 3)) {
                g_Pitcher.scoutFlagRelated = index;
                break;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 idx;
        g_Pitcher.captainStarPitch = 0;
        g_Pitcher.nonCaptainStarPitch = 0;
        if (g_Minigame.battingHandedness[rosterID] <= 1) {
            g_Pitcher.handedness = 0;
        } else {
            g_Pitcher.handedness = 1;
        }
        idx = g_Minigame.minigameControlStruct[0].characterIndex[rosterID];
        if (g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
            g_Pitcher.aiLevel = aILevel[g_Minigame.minigameControlStruct[0].aIStrength[idx]];
        }
    } else {
        g_Pitcher.captainStarPitch = char_stats->stats.CaptainStarHitPitch;
        g_Pitcher.nonCaptainStarPitch = char_stats->stats.NonCaptainStarPitch;
    }
}

// .text:0x0006EF1C size:0x5CC mapped:0x806ADFB0
// Batting order per team, filled in on the order screen (see game/auto_00_0015C5F4_text.h).
typedef struct OrderEntry {
    /*0x0*/ s8 rosterID;
    /*0x1*/ s8 row; // batting-order row, 9 = pitcher only (not batting)
    /*0x2*/ s8 position;
    /*0x3*/ u8 _3;
} OrderEntry;
extern OrderEntry lbl_80354720[2][9];
extern CharSelectState lbl_8034E9A0;
// Captain-star stat multipliers bought in challenge mode:
// [0] contact, [2] power, [4] pitch speed bonus, [5] curve, [7] throwing arm, [8] speed.
extern f32 lbl_3_data_5FC4[12];

#define CAPTAIN_STAR(id, bought, value)                                                                          \
    if (stats->CharID == (id)) {                                                                                 \
        if (bought) {                                                                                            \
            stats->CaptainStarHitPitch = (value);                                                                \
        } else {                                                                                                 \
            stats->CaptainStarHitPitch = 0;                                                                      \
        }                                                                                                        \
    }

// NONMATCHING 83%: the batting-order stores go through an indexed address (stwx) instead of
// team base + row*8 with 0x44/0x48 displacements; the rest is register allocation (r20..r31 vs r21..r31)
#if NONMATCHING
void fn_3_6EF1C(void) {
    int team;
    int j;

    for (team = 0; team < 2; team++) {
        int t = team ^ g_GameLogic._000;
        OrderEntry* e = lbl_80354720[team];
        g_GameLogic.battingOrderAndPositionMapping[t][0][1] = 0;
        for (j = 0; j < 9; j++, e++) {
            if (e->row == 9) {
                g_GameLogic.battingOrderAndPositionMapping[t][0][0] = e->rosterID;
            } else {
                g_GameLogic.battingOrderAndPositionMapping[t][e->row + 1][0] = e->rosterID;
                g_GameLogic.battingOrderAndPositionMapping[t][e->row + 1][1] = e->position;
                if (e->position == 0) {
                    g_GameLogic.battingOrderAndPositionMapping[t][0][0] = e->rosterID;
                }
            }
        }
    }

    g_GameLogic.Team_CaptainRosterLoc[0] = lbl_8034E9A0.captainSlot[0];
    g_GameLogic.Team_CaptainRosterLoc[1] = lbl_8034E9A0.captainSlot[1];

    if (!g_d_GameSettings.exhibitionMatchInd) {
        CharacterStats* roster = inMemRoster[g_d_GameSettings.humanTeamNumber];
        s8* bought = (s8*)g_d_GameSettings.challengeCaptainStarBought;
        s8 contact = bought[0];
        s8 all = g_d_GameSettings._4F;
        s8 power = bought[1];
        s8 pitch = bought[2];
        s8 arm = bought[3];
        s8 speed = bought[4];
        s8 star0 = bought[6];
        s8 star1 = bought[7];
        s8 star2 = bought[0xE];
        s8 star3 = bought[0xF];
        s8 star4 = bought[8];
        s8 star5 = bought[9];
        s8 star6 = bought[0xC];
        s8 star11 = bought[0xD];
        s8 starA = bought[0xA];
        s8 starB = bought[0xB];
        s8 star9 = bought[0x10];
        s8 star13 = bought[0x11];
        f32 contactMul = lbl_3_data_5FC4[0];
        f32 powerMul = lbl_3_data_5FC4[2];
        f32 pitchAdd = lbl_3_data_5FC4[4];
        f32 curveMul = lbl_3_data_5FC4[5];
        f32 armMul = lbl_3_data_5FC4[7];
        f32 speedMul = lbl_3_data_5FC4[8];
        for (j = 0; j < 9; j++, roster++) {
            StatTable* stats = &roster->stats;
            if (contact || all) {
                stats->SlapContactSize = stats->SlapContactSize * contactMul;
                stats->ChargeContactSize = stats->ChargeContactSize * contactMul;
            }
            if (power || all) {
                stats->SlapHitPower = stats->SlapHitPower * powerMul;
                stats->ChargeHitPower = stats->ChargeHitPower * powerMul;
            }
            // the original tests bought[2] twice (not _4F)
            if (pitch || pitch) {
                stats->CurveBallSpeed += (s32)pitchAdd;
                stats->FastBallSpeed += (s32)pitchAdd;
                stats->Curve = stats->Curve * curveMul;
            }
            if (arm || all) {
                stats->ThrowingArm = stats->ThrowingArm * armMul;
            }
            if (speed || all) {
                stats->Speed = stats->Speed * speedMul;
            }
            CAPTAIN_STAR(0, star0, 1)
            CAPTAIN_STAR(1, star1, 2)
            CAPTAIN_STAR(2, star2, 5)
            CAPTAIN_STAR(3, star3, 6)
            CAPTAIN_STAR(4, star4, 0xB)
            CAPTAIN_STAR(5, star5, 0xC)
            CAPTAIN_STAR(6, star6, 9)
            CAPTAIN_STAR(0x11, star11, 0xA)
            CAPTAIN_STAR(0xA, starA, 3)
            CAPTAIN_STAR(0xB, starB, 4)
            CAPTAIN_STAR(9, star9, 7)
            CAPTAIN_STAR(0x13, star13, 8)
        }
    }
}
#endif
