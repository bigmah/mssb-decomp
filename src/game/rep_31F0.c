#include "game/rep_31F0.h"
// g_Minigame stays a byte array here (the matched code indexes it as one); MG31 is its typed view.
#define g_Minigame g_Minigame_header_decl
#include "game/UnknownHomes_Game.h"
#undef g_Minigame
#include "main/file_8001FE00.h"
#include "static/GameSettings.h"
#include "game/auto_00_001658F0_text.h"
extern u8 g_Minigame[];
#define MG31 ((MiniGameStruct*)g_Minigame)
// OFFSET_OF(MiniGameStruct, bODCharacterHRStreakTracker), spelled as a literal: the matched code indexes
// the byte array from it and only folds a plain constant (no pointer fields precede it).
#define MG31_HR_STREAK 0x1ACC
#define MG31_HIT_HISTORY 0x1AA0 // OFFSET_OF(MiniGameStruct, bODHitHistory)
#define REP_HEADER_FN repHeader_31F0
#include "header_rep_inline.h"

#include "musyx/musyx.h"
#include "Dolphin/mtx.h"
#include "static/Camera.h"
#include "game/rep_1E08.h"
extern u8 lbl_800EFBA4[];

extern void setInMemBatterConstants(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_8913C(void);
extern void fn_3_58870(void);
extern void fn_3_BF1AC(void);
extern void Set_803cb848(s32);
extern void* memset(void*, int, size_t);

extern void fn_3_5A6D4(s32);
extern u8 lbl_3_common_bss_32220[];
extern f32 lbl_3_rodata_3268;
extern f32 lbl_3_rodata_324C;
extern f32 lbl_3_rodata_3250;
extern f32 lbl_3_rodata_3254;
extern f32 shortAngleToRad(s16);
extern void fn_3_10AD48(void);
extern void fn_3_10F550(s32, s32);
extern u8 lbl_3_common_bss_32724[];
extern void fn_8003A540(u32 value);
extern void fn_3_DE4FC(void);
extern void fn_3_155288(void);
extern void minigamesSetSomePointers(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
extern int rand();
extern s16 lbl_3_data_21448[];
extern s16 lbl_3_data_217A4[];
extern u8 lbl_3_data_2139C[];
extern u8 lbl_3_data_213A4[];
extern int RandomIndexFromWeights(u8* weights, int count);
extern void fn_3_750C4(u8);
extern s16 lbl_3_data_21448[];
extern void changeScene(s32, s32);
extern s16 lbl_3_data_18C48[];
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void changeScene(s32, s32);

// .text:0x00110634 size:0x3D0 mapped:0x8074F6C8
extern s32 fn_3_9E368(s32* weights, s32 n);
extern int RandomInt_Game_Range(int min, int max);
extern GameScores g_Scores;
extern u8 swingSoundFrame[2][4];
extern u8 lbl_3_data_21488[][3];
extern s8 lbl_3_data_214A0[][3][2];
extern s8 lbl_3_data_214B8[][3];
extern s8 lbl_3_data_214C4[][3];
extern s8 lbl_3_data_214D0[][3];
extern s8 lbl_3_data_214DC[][3];
extern s8 lbl_3_data_214E8[][3];
extern s8 lbl_3_data_214F4[][3];

// NONMATCHING 92%: the first weight loop hoists g_Minigame+0x1ACC (lbzx) and allocates the table walkers differently
#if NONMATCHING
static inline void calcWeights_31F0(s32* w, u8* base, s8* streak, s8* special, s8* bonus) {
    s8 i = 0;
    u8 streakCnt = (g_Minigame + MG31_HR_STREAK)[MG31->rosterID * 2];
    do {
        w[i] = base[i];
        w[i] += streakCnt * streak[i];
        if (((u8*)&MG31->_1DF4[0])[2] != 0) {
            w[i] += special[i];
        } else if (MG31->bOD_KingBombInd != 0) {
            w[i] += bonus[i];
        }
        if (w[i] < 0) {
            w[i] = 0;
        }
        i++;
    } while (i < 3);
}

void fn_3_110634(void) {
    s32 zone[3];
    s32 timing[3];
    s32 k;
    s16 frame;
    MiniGameStruct* mg = MG31;
    u8 type = mg->minigameControlStruct[0].aIStrength[mg->rosterID];
    calcWeights_31F0(zone, lbl_3_data_21488[type], lbl_3_data_214B8[type], lbl_3_data_214E8[type], lbl_3_data_214D0[type]);
    calcWeights_31F0(timing, lbl_3_data_21488[type], lbl_3_data_214C4[type], lbl_3_data_214F4[type], lbl_3_data_214DC[type]);
    frame = g_hitShorts.framesUntilChargeIsEnabled;
    switch (fn_3_9E368(zone, 3)) {
    case 0:
    default:
        frame = frame + RandomInt_Game_Range(3, g_Batter.frameFullyCharged - 3);
        break;
    case 1:
        frame = g_Batter.frameFullyCharged +
                (RandomInt_Game_Range(3, g_Batter.frameChargeDownBegins - g_Batter.frameFullyCharged - 3) + frame);
        break;
    case 2:
        frame = g_Batter.frameChargeDownBegins + (RandomInt_Game_Range(3, g_hitShorts.frameChargeDownEnds) + frame);
        break;
    }
    k = fn_3_9E368(timing, 3);
    mg->bB_cpuStickInput =
        swingSoundFrame[1][k] + RandomInt_Game_Range(lbl_3_data_214A0[type][k][0], lbl_3_data_214A0[type][k][1]);
    mg->bB_cpuSwingFrame = frame - (fn_3_110A38() - (s16)mg->bB_cpuStickInput);
    if (mg->bB_cpuSwingFrame < g_hitShorts.framesUntilChargeIsEnabled + 1) {
        mg->bB_cpuSwingFrame = g_hitShorts.framesUntilChargeIsEnabled + 1;
    }
}
#endif

// .text:0x00110A04 size:0x34 mapped:0x8074FA98
void fn_3_110A04(void) {
    memset(&MG31->_1D7C[0], 0, 0x78);
}

// .text:0x00110A38 size:0x9C mapped:0x8074FACC
s32 fn_3_110A38(void) {
    if (g_Pitcher.starPitchInd != 0) {
        switch (g_Pitcher.starPitchType) {
        case 1:
            return 20;
        }
        return 20;
    }
    return (s32)(lbl_3_rodata_3250 * ((f32)MG31->minigamePitchSpeedAdjustment - lbl_3_rodata_3254) + lbl_3_rodata_324C);
}

// .text:0x00110AD4 size:0x564 mapped:0x8074FB68
extern s16 fn_3_9FB8C(f32 x, f32 y);
extern void getComponentsFromSAng(s16 ang, f32* x, f32* y);
extern camera_803c639c_s* fn_80052768_getCamera(int index);
extern u8 lbl_3_data_213E0[4];
extern f32 lbl_3_data_21438[];

// g_Minigame.bODHitHistory: last 10 hit results per roster slot

// Arms the first free slot of the 10 explosion timers at g_Minigame+0x1A96.
static inline void startBombTimer_31F0(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (MG31->bODBombTimers[i] == 0) {
            MG31->bODBombTimers[i] = lbl_3_data_21448[8];
            return;
        }
    }
}

void fn_3_110AD4(void) {
    f32 cosB;
    Vec v;
    s32 i;
    s32 angA;
    s32 angB;
    MiniGameStruct* mg = MG31;
    if (mg->bODRelated3 == 0) {
        for (i = 9; i > 0; i--) {
            (g_Minigame + MG31->rosterID * 10)[i + MG31_HIT_HISTORY] = (g_Minigame + MG31->rosterID * 10)[i + MG31_HIT_HISTORY - 1];
        }
        MG31->bODHitHistory[mg->rosterID][0] = MG31->bODAngleIndexBasedOnHitPower;
        v.x = g_Ball.AtBat_Contact_BallPos.x;
        v.y = -g_Ball.AtBat_Contact_BallPos.y;
        v.z = g_Ball.AtBat_Contact_BallPos.z;
        MG31->bB_bombBarrelHitInd = fn_3_9FB8C(v.x, v.z);
        MG31->bB_bombBarrelID = fn_3_9FB8C(g_Ball.ballDistanceFromHome, -v.y);
        if (g_Pitcher.starPitchInd != 0) {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(0, 3), 1);
        } else if (MG31->bOD_KingBombInd != 0) {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, 13, 1);
        } else {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(8, 12), 1);
        }
        mg->bODRelated3 = 1;
        MG31->hudFlags[3] = 1;
        MG31->_18A0 = 1;
        MG31->_18A6 = RandomInt_Game_Range(lbl_3_data_213E0[0], lbl_3_data_213E0[1]);
        if (g_Pitcher.starPitchInd != 0) {
            MG31->bODControllerInputAllowedInd = 0;
        } else if (MG31->bODCharacterHRStreakTracker[mg->rosterID * 2] <= 1 || MG31->bOD_KingBombInd != 0) {
            MG31->bODControllerInputAllowedInd = 1;
            MG31->hudFlags[4] = 1;
        } else {
            MG31->bODControllerInputAllowedInd = 0;
        }
        fn_3_155288();
        startBombTimer_31F0();
    } else if (mg->bODControllerInputAllowedInd == 0 && --mg->_18A6 <= 0) {
        angA = rand() % lbl_3_data_21448[5];
        if (rand() & 1) {
            angA = -angA;
        }
        angA += MG31->bB_bombBarrelHitInd;
        angB = rand() % lbl_3_data_21448[6];
        if (rand() & 1) {
            angB = -angB;
        }
        angB += MG31->bB_bombBarrelID;
        getComponentsFromSAng(angA, &v.x, &v.z);
        getComponentsFromSAng(angB, &cosB, &v.y);
        v.x *= lbl_3_data_21438[3];
        v.z *= lbl_3_data_21438[3];
        v.y = v.y / cosB;
        v.y = v.y * -lbl_3_data_21438[3];
        if (g_Pitcher.starPitchInd != 0) {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(0, 3), 1);
        } else if (*(u16*)&MG31->_18A0 & 1) {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(4, 7), 1);
        } else {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(8, 12), 1);
        }
        mg->_18A6 = RandomInt_Game_Range(lbl_3_data_213E0[2], lbl_3_data_213E0[3]);
        *(u16*)(&MG31->_18A0) += 1;
        if (g_Pitcher.starPitchInd != 0) {
            if (*(u16*)&MG31->_18A0 >= 10) {
                mg->bODControllerInputAllowedInd = 1;
                MG31->hudFlags[4] = 1;
            }
        } else if (*(u16*)&MG31->_18A0 >= MG31->bODCharacterHRStreakTracker[MG31->rosterID * 2] ||
                   *(u16*)&MG31->_18A0 >= lbl_3_data_21448[7]) {
            mg->bODControllerInputAllowedInd = 1;
            MG31->hudFlags[4] = 1;
        }
        startBombTimer_31F0();
    }
}

extern StarChanceState lbl_3_common_bss_37400;
extern s16 lbl_3_data_213EC[];
extern void fn_3_1608F0(s32, s32, u8);

// g_Minigame: Bomb-omb Derby fields
typedef struct {
    u8 pad0[0x1890];
    s16 curPoints[4];
    s16 latestPoints[4];
    u8 pad1[0x1905 - 0x18A0];
    s8 rosterID;
    u8 pad2[0x1A8E - 0x1906];
    s16 hitPower[4];
    u8 pad3[0x1ACC - 0x1A96];
    u8 hrStreak[8];
    u8 pad4;
    u8 kingBomb;
} MgBOD;

// .text:0x00111038 size:0x198 mapped:0x807500CC
void fn_3_111038(void) {
    MgBOD* mg = (MgBOD*)g_Minigame;
    s16 dist = g_Ball.Hit_HorizontalPower;
    u8 cnt;
    s32 off;
    f32 f;
    (g_Minigame + MG31_HR_STREAK)[mg->rosterID * 2]++;
    if (mg->hitPower[mg->rosterID] < dist) {
        mg->hitPower[mg->rosterID] = dist;
    }
    f = dist;
    off = mg->rosterID * 2;
    cnt = (g_Minigame + MG31_HR_STREAK)[off];
    if (cnt > 1) {
        f += lbl_3_data_213EC[8] * cnt;
    }
    if (((MgBOD*)g_Minigame)->kingBomb != 0) {
        f += lbl_3_data_213EC[7];
    }
    *(s16*)((u8*)((MgBOD*)g_Minigame)->latestPoints + off) = f;
    ((MgBOD*)g_Minigame)->curPoints[mg->rosterID] += (s16)f;
    if (g_d_GameSettings.exhibitionMatchInd == 0 && mg->rosterID == lbl_3_common_bss_37400.humanPlayer) {
        fn_3_1608F0(0, f, ((MgBOD*)g_Minigame)->kingBomb);
    }
}

// .text:0x001111D0 size:0x80 mapped:0x80750264
void fn_3_1111D0(void) {
    s32 a;
    InMemRunnerType* r = g_Runners;
    if (lbl_3_common_bss_32220[8] == 4) {
        a = g_Ball.Hit_HorizontalAngle;
        if (a < 0x200) {
            a = 0x200;
        }
        if (a > 0x600) {
            a = 0x600;
        }
        r->runningAngle = -shortAngleToRad(a) - lbl_3_rodata_3268;
    }
}

// .text:0x00111250 size:0x64 mapped:0x807502E4
void fn_3_111250(void) {
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_8003A540(0);
    if (MG31->pointsTargetReachedInd == 1) {
        fn_3_5A6D4(8);
        return;
    }
    fn_3_5A6D4(0);
}

// .text:0x001112B4 size:0x484 mapped:0x80750348
void fn_3_1112B4(void) {
    MiniGameStruct* mg = MG31;
    u8 st = mg->turnOverStatus;
    u8 bd;
    if (st == 0) {
        if (g_Ball.framesOnGroundUntilPickedUp != 0) {
            g_GameLogic.CountdownUntilFade = lbl_3_data_21448[1];
            mg->turnOverStatus = 1;
            mg->bODCharacterHRStreakTracker[mg->rosterID * 2] = 0;
        } else {
            bd = g_Ball.deadBallReason;
            if (bd != 0) {
                if (bd == 1) {
                    g_GameLogic.CountdownUntilFade = lbl_3_data_21448[2];
                    mg->bOD_HRStreak++;
                    fn_3_111038();
                } else {
                    g_GameLogic.CountdownUntilFade = lbl_3_data_21448[2];
                    mg->bODCharacterHRStreakTracker[mg->rosterID * 2] = 0;
                }
                mg->turnOverStatus = 1;
            }
        }
    } else {
        if (st == 1) {
            mg->turnOverStatus = 2;
            if (mg->multiPlayerInd == 0 && mg->soloMinigameDifficulty <= 2 &&
                ((MgBOD*)g_Minigame)->curPoints[((MgBOD*)g_Minigame)->rosterID] >= MG31->pointsReqToWin_challenge) {
                mg->pointsTargetReachedInd = 1;
                mg->_1A37 = 1;
                mg->challenge_minigame_haven_tWonYetIndicator = 0;
                fn_3_10F550(1, lbl_3_data_21448[9]);
            } else if (MG31->miniGameTurnCounter >= MG31->bODRoundStartingNumPitches) {
                if (mg->multiPlayerInd == 0 && MG31->soloMinigameDifficulty == 3 && g_Ball.deadBallReason == 1 && MG31->miniGameTurnCounter < 20) {
                    if (MG31->bODCharacterHRStreakTracker[MG31->rosterID * 2] < MG31->miniGameTurnCounter) {
                        MG31->pointsTargetReachedInd = 1;
                    }
                } else {
                    MG31->pointsTargetReachedInd = 1;
                }
            }
        }
        if (MG31->bODControllerInputAllowedInd != 0 && MG31->bODRelated == 0) {
            g_GameLogic.CountdownUntilFade -= 1;
            if (MG31->pointsTargetReachedInd != 0 &&
                (MG31->multiPlayerInd == 0 ||
                 (MG31->multiPlayerInd != 0 && MG31->turnNumberWithinRound + 1 >= MG31->miniGameNumberOfParticipants && g_Scores.inning >= g_Scores.maxInnings)) &&
                MG31->_1A37 == 0 && g_GameLogic.CountdownUntilFade == 0x43) {
                sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
            }
            if (g_GameLogic.CountdownUntilFade == 7) {
                changeScene(3, 6);
            }
            if (g_GameLogic.CountdownUntilFade <= 0) {
                fn_3_111250();
            }
        }
    }
}

// .text:0x00111738 size:0x17C mapped:0x807507CC
extern void ballPhysica(void);
extern void fn_3_8F21C(void);

// g_Minigame +0x18CC: minigameControlStruct[0].characterIndex[]

void fn_3_111738(void) {
    s32 i;
    ballPhysica();
    fn_3_1111D0();
    if (g_Ball.bODQualifyingHitInd != 0 && g_Ball.deadBallReason == 1 &&
        (g_Ball.ballDistanceFromHome > lbl_3_data_21438[3] || MG31->bODRelated3 != 0)) {
        ((void (*)(void))fn_3_110AD4)();
        MG31->bOD_hitFinishedInd = 1;
    }
    for (i = 0; i < 10; i++) {
        if (MG31->bODBombTimers[i] != 0) {
            MG31->bODBombTimers[i]--;
            if (MG31->bODBombTimers[i] == 0) {
                fn_3_6C854(MG31->minigameControlStruct[0].characterIndex[MG31->rosterID], 0);
            }
        }
    }
    if (g_Ball.deadBallReason == 2) {
        MG31->bOD_hitFinishedInd = 1;
    }
    fn_3_8F21C();
    ((void (*)(void))fn_3_1112B4)();
}

// .text:0x001118B4 size:0x1D4 mapped:0x80750948
void fn_3_1118B4(void) {
    s32 lim = lbl_3_data_21448[3];
    u8 flag = 1;
    s32 sel;
    u8 mode = MG31->GameMode_MiniGame;
    s32 isMode3 = mode == 3;
    s32 k;
    if (isMode3) {
        lim = lbl_3_data_217A4[6];
    }
    if (!isMode3) {
        flag = ((u8*)&MG31->_1DF4[0])[0];
    }
    if (g_Pitcher.currentStateFrameCounter > lim && flag != 0) {
        if (MG31->GameMode_MiniGame == 3) {
            MG31->minigamePitchSpeedAdjustment = lbl_3_data_217A4[9];
        } else if ((sel = ((u8*)&MG31->_1DF4[0])[1]) < 3) {
            if (sel < 2) {
                k = sel * 2;
                k += RandomIndexFromWeights(lbl_3_data_213A4 + MG31->barrelBatter_BODPitchSelectionType * 5 + k, 2);
            } else {
                k = 4;
            }
            MG31->minigamePitchSpeedAdjustment = lbl_3_data_2139C[k] + rand() % 7 - 3;
        } else if (sel == 3) {
            MG31->bOD_KingBombInd = 1;
            k = RandomIndexFromWeights(lbl_3_data_213A4 + MG31->barrelBatter_BODPitchSelectionType * 5, 5);
            MG31->minigamePitchSpeedAdjustment = lbl_3_data_2139C[k] + rand() % 7 - 3;
        } else {
            g_Pitcher.starPitchInd = 1;
            g_Pitcher.starPitchType = 1;
        }
        fn_3_750C4(2);
    }
}

// .text:0x00111A88 size:0x3C mapped:0x80750B1C
void fn_3_111A88(void) {
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_3_5A6D4(8);
}

// .text:0x00111AC4 size:0x198 mapped:0x80750B58
void fn_3_111AC4(void) {
    MiniGameStruct* mg = MG31;
    u8 st = mg->turnOverStatus;
    if (st == 0) {
        if (g_Pitcher.pitcherActionState == 4) {
            if (mg->miniGameTurnCounter >= mg->bODRoundStartingNumPitches) {
                mg->turnOverStatus = 1;
                mg->pointsTargetReachedInd = 1;
            }
            MG31->bODCharacterHRStreakTracker[MG31->rosterID * 2] = 0;
            fn_3_155288();
        }
    } else {
        if (st == 1) {
            mg->turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_21448[0];
        }
        g_GameLogic.CountdownUntilFade -= 1;
        if (MG31->pointsTargetReachedInd != 0 &&
            (MG31->multiPlayerInd == 0 ||
             (MG31->multiPlayerInd != 0 && MG31->turnNumberWithinRound + 1 >= MG31->miniGameNumberOfParticipants && g_Scores.inning >= g_Scores.maxInnings)) &&
            MG31->_1A37 == 0 && g_GameLogic.CountdownUntilFade == 0x43) {
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }
        if (g_GameLogic.CountdownUntilFade == 7) {
            changeScene(3, 6);
        }
        if (g_GameLogic.CountdownUntilFade <= 0) {
            g_GameLogic.pre_PostMiniGameInd = 1;
            g_GameLogic.minigameLastTurnSuccessInd = 1;
            g_GameLogic.hudLoadingRelated = 1;
            fn_3_5A6D4(8);
        }
    }
}

// .text:0x00111C5C size:0x324 mapped:0x80750CF0
extern s32 fn_3_108854(void);
extern void fn_3_75560(void);
extern void atBat_batter(void);
extern void fn_3_2EA24(void);
extern void fn_3_8A958(void);

static inline void clearHitFlags_31F0(void) {
    s8 i = 0;
    do {
        MG31->_1DBC[i] = 0;
        i++;
    } while (i < 4);
}

// NONMATCHING 97%: the inlined fn_3_111AC4 tail reuses a different g_Minigame base; one extsb is CSE'd
#if NONMATCHING
void fn_3_111C5C(void) {
    InputStruct* e;
    u8 ci;
    s8 i;
    if (MG31->turnOverStatus == 0) {
        if (fn_3_108854() != 0) {
            return;
        }
        fn_3_75560();
        clearHitFlags_31F0();
        i = 0;
        do {
            ci = (u8)MG31->minigameControlStruct[0].characterIndex[i];
            if ((s8)ci >= 0 && (s8)ci < 4 && i == MG31->rosterID && MG31->minigameControlStruct[0].battingHandedness[i] != 0) {
                e = &MG31->_1D7C[(s8)ci];
                MG31->_1DBC[((s8)ci)] = 1;
                memset(e, 0, sizeof(InputStruct));
                switch (g_Pitcher.pitcherActionState) {
                case 2:
                    if ((u8)MG31->bB_cpuSwingStep == 0) {
                        ((void (*)(void))fn_3_110634)(); // a call in the original (not inlined)
                        MG31->bB_cpuSwingStep = 1;
                    }
                    if (g_Pitcher.windupCountdownUntilBallReleased <= MG31->bB_cpuSwingFrame) {
                        e->buttonInput |= 0x100;
                    }
                    break;
                case 3:
                    if (g_Ball.pitchHangtimeCounter < g_Pitcher.frameWhenUnhittable - (s16)MG31->bB_cpuStickInput) {
                        e->buttonInput |= 0x100;
                    }
                    break;
                }
            }
            i++;
        } while (i < 4);
        atBat_batter();
        clearHitFlags_31F0();
        fn_3_2EA24();
        fn_3_8A958();
    }
    fn_3_111AC4();
}
#endif

// .text:0x00111F80 size:0xF0 mapped:0x80751014
void fn_3_111F80(void) {
    GameControlsStruct* gl = &g_GameLogic;
    switch (gl->_125) {
    case 0:
        changeScene(1, 6);
        gl->_125 = 1;
        break;
    case 1: {
        s32 t = gl->FrameCountOfCurrentPitch;
        if (t >= lbl_3_data_18C48[2] ||
            (t >= lbl_3_data_18C48[1] && fn_3_6C938(1, 0x1100) != 0)) {
            changeScene(3, 6);
            gl->_125 = 2;
        }
        break;
    }
    case 2:
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            gl->_125 = 3;
        }
        break;
    case 3:
        fn_3_5A6D4(7);
        break;
    }
}

// .text:0x00112070 size:0x70 mapped:0x80751104
void fn_3_112070(void) {
    fn_3_DE4FC();
    fn_3_5A6D4(14);
    MG31->_18A6 = rand() % 30 + 15;
    fn_3_155288();
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
}

// .text:0x001120E0 size:0x48 mapped:0x80751174

void fn_3_1120E0(void) {
    if (g_Scores.inning >= g_Scores.maxInnings) {
        fn_3_5A6D4(0xF);
    } else {
        fn_3_5A6D4(6);
    }
}

// .text:0x00112128 size:0x7C mapped:0x807511BC
void fn_3_112128(void) {
    MG31->turnNumberWithinRound += 1;
    if (MG31->multiPlayerInd == 0) {
        fn_3_5A6D4(0xF);
    } else if (MG31->turnNumberWithinRound >= MG31->miniGameNumberOfParticipants) {
        fn_3_5A6D4(0x19);
    } else {
        fn_3_5A6D4(7);
    }
    lbl_3_common_bss_32724[0xB7] = 1;
}

// .text:0x001121A4 size:0x8C mapped:0x80751238
void fn_3_1121A4(void) {
    setInMemBatterConstants(MG31->rosterID);
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    memset(&MG31->_1D7C[0], 0, 0x78);
    fn_3_BF1AC();
    Set_803cb848(1);
    g_FieldingLogic._0AE = 0;
    unkSimulationRelatedStruct._05 = 0;
    unkSimulationRelatedStruct._06 = 4;
}

// .text:0x00112230 size:0x220 mapped:0x807512C4
extern void fn_3_8FC0C(void);
extern u8 lbl_3_data_213D4[];
extern u8 lbl_3_data_213DC[];

void fn_3_112230(void) {
    s32 i;
    s32 n;
    fn_3_1121A4();
    MG31->turnOverStatus = 0;
    MG31->bODRelated2 = 0;
    MG31->bODRelated3 = 0;
    MG31->bODControllerInputAllowedInd = 1;
    MG31->bOD_KingBombInd = 0;
    MG31->bOD_hitFinishedInd = 0;
    for (i = 0; i < 10; i++) {
        MG31->bODBombTimers[i] = 0;
    }
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic._110 = 0;
    g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_21448[4];
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    if (MG31->miniGameNumberOfParticipants > 1) {
        MG31->barrelBatter_BODPitchSelectionType = lbl_3_data_213DC[g_Scores.inning - 1];
    } else if (MG31->soloMinigameDifficulty == 3) {
        n = MG31->miniGameTurnCounter / 5;
        if (n > 4) {
            n = 4;
        }
        MG31->barrelBatter_BODPitchSelectionType = n;
    } else if (MG31->miniGameTurnCounter < 5) {
        MG31->barrelBatter_BODPitchSelectionType = lbl_3_data_213D4[MG31->soloMinigameDifficulty * 2];
    } else {
        MG31->barrelBatter_BODPitchSelectionType = lbl_3_data_213D4[MG31->soloMinigameDifficulty * 2 + 1];
    }
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
    fn_3_8FC0C();
    changeScene(1, 6);
    fn_3_5A6D4(1);
}

// .text:0x00112450 size:0x108 mapped:0x807514E4
extern void fn_3_F578(void);
extern void fn_3_753E8(s32);
extern void fn_3_6EBB4(s32);
extern void setBatterContactConstants(void);
extern s32 someAnimationIndFunction(void);
extern u8 lbl_803CBC3C[];
extern u8 lbl_3_common_bss_32234[];

void fn_3_112450(void) {
    GameControlsStruct* gl = &g_GameLogic;
    MiniGameStruct* mg;
    switch (gl->_125) {
    case 0:
        mg = MG31;
        mg->rosterID = mg->minigameControlStruct[0].turnOrder[mg->turnNumberWithinRound];
        gl->pre_PostMiniGameInd = 1;
        mg->miniGameTurnCounter = 0;
        mg->pointsTargetReachedInd = 0;
        mg->bOD_HRStreak = 0;
        fn_3_F578();
        fn_3_753E8(0);
        fn_3_6EBB4(-1);
        setBatterContactConstants();
        setInMemBatterConstants(mg->rosterID);
        lbl_803CBC3C[2] = 0;
        gl->_125 += 1;
        break;
    case 1:
        if (someAnimationIndFunction() != 0) {
            lbl_3_common_bss_32234[1] = 1;
            gl->_125 += 1;
        }
        break;
    default:
        lbl_3_common_bss_32724[0xB6] = 1;
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x00112558 size:0x78 mapped:0x807515EC
void fn_3_112558(void) {
    g_Scores.inning += 1;
    MG31->turnNumberWithinRound = 0;
    if (MG31->multiPlayerInd == 0) {
        fn_3_5A6D4(7);
        return;
    }
    if (g_Scores.inning == 1) {
        fn_3_10AD48();
    }
    fn_3_5A6D4(7);
    fn_3_10F550(4, 0);
}

// .text:0x001125D0 size:0x40 mapped:0x80751664
void fn_3_1125D0(void) {
    sndFXStartEx(0x1BD, lbl_800EFBA4[6], 0x3F, 0);
    fn_3_5A6D4(6);
}

// .text:0x00112610 size:0x2D8 mapped:0x807516A4
extern void fn_3_59A90(void);
extern int RandomInt_Game_Range(int min, int max);
extern u8 lbl_3_data_2127C[];
extern u8 lbl_3_data_213E4[];
typedef struct { s16 count; s16 time; } MgModeParam_31F0;
extern MgModeParam_31F0 lbl_3_data_21400[];

// NONMATCHING 96%: scheduling of the mode-table loads and zero/base register picks in the reset loop
#if NONMATCHING
void fn_3_112610(void) {
    GameControlsStruct* gl = &g_GameLogic;
    MiniGameStruct* mg;
    s32 i;
    u8 c;
    if (gl->_125 == 0) {
        fn_3_59A90();
        g_GameLogic.secondaryGameMode = 3;
        MG31->_17C0 = 0;
        for (i = 0; i < 4; i++) {
            MG31->miniGameCurrentPoints[i] = 0;
            MG31->miniGameLatestPoints[i] = 0;
            MG31->minigamePoints_current_Latest[i].current = 0;
            MG31->minigamePoints_current_Latest[i].latest = 0;
            MG31->minigameControlStruct[0].fieldOrder[i] = -1;
            MG31->_18FC[i] = -1;
            MG31->_1900[i] = -1;
            MG31->minigameControlStruct[0]._24[i] = 1;
            MG31->minigameFielderIndex[i] = -1;
            MG31->bOD_HitPowerOfEachChar[i] = 0;
            MG31->bODCharacterHRStreakTracker[i * 2] = 0;
            MG31->bODCharacterHRStreakTracker[i * 2 + 1] = 0;
        }
        mg = MG31;
        g_Scores.inning = 0;
        mg->turnNumberWithinRound = 0;
        mg->pointsReqToWin_challenge = 0;
        mg->_1A37 = 0;
        mg->minigamePlayerSelectedOrder = -1;
        mg->rosterID = -1;
        MG31->_17C0 = 0;
        mg->bOD_KingBombInd = 0;
        mg->bODAngleIndexBasedOnHitPower = 0;
        mg->_18A0 = 0;
        mg->bB_bombBarrelHitInd = 0;
        mg->bB_bombBarrelID = 0;
        mg->_18A6 = 30;
        mg->bODControllerInputAllowedInd = 0;
        if (mg->multiPlayerInd == 0) {
            g_Scores.maxInnings = 1;
            mg->bODRoundStartingNumPitches = lbl_3_data_21400[mg->soloMinigameDifficulty].count;
            c = (lbl_3_data_2127C + mg->GameMode_MiniGame * 5)[mg->soloMinigameDifficulty];
            mg->pointsReqToWin_challenge = lbl_3_data_21400[mg->soloMinigameDifficulty].time;
            mg->minigameControlStruct[0].aIStrength[0] = c;
            mg->minigameControlStruct[0].aIStrength[1] = c;
            mg->minigameControlStruct[0].aIStrength[2] = c;
            mg->minigameControlStruct[0].aIStrength[3] = c;
        } else {
            if (mg->_1A3C != 0) {
                mg->minigameControlStruct[0].aIStrength[0] = lbl_3_data_2127C[0x23];
                mg->minigameControlStruct[0].aIStrength[1] = lbl_3_data_2127C[0x23];
                mg->minigameControlStruct[0].aIStrength[2] = lbl_3_data_2127C[0x23];
                mg->minigameControlStruct[0].aIStrength[3] = lbl_3_data_2127C[0x23];
            }
            g_Scores.maxInnings = lbl_3_data_213E4[(MG31->miniGameNumberOfParticipants - 2) * 2];
            MG31->bODRoundStartingNumPitches = lbl_3_data_213E4[(MG31->miniGameNumberOfParticipants - 2) * 2 + 1];
        }
        if (mg->multiPlayerInd == 0 && MG31->_1A3C == 0) {
            if (MG31->multiPlayerInd == 0 && MG31->_1A3C == 0 && MG31->soloMinigameDifficulty == 3) {
                MG31->_1AD8 = 9;
            } else {
                MG31->_1AD8 = RandomInt_Game_Range(4, 9);
            }
            MG31->_1AD9 = 1;
        } else if (MG31->_1A3C != 0) {
            MG31->_1AD8 = RandomInt_Game_Range(0, 2);
            MG31->_1AD9 = RandomInt_Game_Range(2, 3);
        } else {
            MG31->_1AD8 = 9;
            MG31->_1AD9 = 1;
        }
        gl->_125++;
    } else {
        fn_3_5A6D4(5);
    }
}
#endif

// .text:0x001128E8 size:0x4 mapped:0x8075197C
void fn_3_1128E8(void) {
    return;
}

// .text:0x001128EC size:0x2EC mapped:0x80751980
// View returned by fn_80052734: only the fields used here.
typedef struct {
    u8 pad0[0x40];
    Mtx view;   // 0x40
    Vec pos;    // 0x70
    Vec target; // 0x7C
} CamView_31F0;

void* fn_80052734(s32 index);
void fn_8003414C(Mtx view);

// .bss (laid out last-defined-first)
static u8 lbl_3_bss_B69A[0x1E]; // unused
static u8 lbl_3_bss_B699;
static u8 lbl_3_bss_B698[0x1]; // unused
extern const f32 lbl_3_rodata_326C; // 200.0f
extern const f32 lbl_3_rodata_3274; // 250.0f
extern const f32 lbl_3_rodata_3278; // 100.0f
extern const f32 lbl_3_rodata_327C; // 0.0f
extern const f32 lbl_3_rodata_3280; // -55.0f
extern const f32 lbl_3_rodata_3284; // -10.0f
extern const f32 lbl_3_rodata_3288; // 32767.0f

void fn_3_1128EC(void) {
    CamView_31F0* cam = fn_80052734(0);
    Vec pos;
    Vec dir;
    Vec ofs;
    Mtx inv;
    u8 idx;
    if (MG31->_18A6 <= 0) {
        pos = cam->pos;
        dir = cam->target;
        PSVECSubtract(&dir, &pos, &dir);
        PSVECNormalize(&dir, &dir);
        PSVECScale(&dir, lbl_3_rodata_326C, &dir);
        PSVECAdd(&pos, &dir, &dir);
        if (dir.y > 55.0f) {
            dir.y = 55.0f;
        }
        PSMTXInverse(cam->view, inv);
        ofs.x = (rand() % 10000 - 5000) / lbl_3_rodata_3274;
        ofs.y = (rand() % 1000 - 500) / lbl_3_rodata_3278;
        ofs.z = lbl_3_rodata_327C;
        PSMTXMultVecSR(inv, &ofs, &ofs);
        PSVECAdd(&dir, &ofs, &dir);
        if (dir.y > lbl_3_rodata_3280) {
            dir.y = lbl_3_rodata_3284 * ((f32)rand() / lbl_3_rodata_3288) + lbl_3_rodata_3280;
        }
        if (lbl_3_bss_B699 != 0) {
            idx = rand() % 5 + 8;
        } else {
            idx = rand() % 4 + 4;
        }
        fn_3_BC6D8(&dir, &cam->pos, idx, 0);
        lbl_3_bss_B699 = !lbl_3_bss_B699;
        MG31->_18A6 = rand() % 60 + 60;
    } else {
        MG31->_18A6 -= 1;
    }
    fn_8003414C(cam->view);
}

// The original expands fn_3_111C5C into fn_3_112BD8. CW only does that with a larger inline size
// limit (with -inline deferred, the value in effect at the end of the file counts) and only from a
// copy that is always visible (fn_3_111C5C itself is NONMATCHING).
#pragma inline_max_size(100000)
// Inline copy of fn_3_111C5C.
static inline void fn_3_111C5C_inline(void) {
    InputStruct* e;
    u8 ci;
    s8 i;
    if (MG31->turnOverStatus == 0) {
        if (fn_3_108854() != 0) {
            return;
        }
        fn_3_75560();
        clearHitFlags_31F0();
        i = 0;
        do {
            ci = (u8)MG31->minigameControlStruct[0].characterIndex[i];
            if ((s8)ci >= 0 && (s8)ci < 4 && i == MG31->rosterID && MG31->minigameControlStruct[0].battingHandedness[i] != 0) {
                e = &MG31->_1D7C[(s8)ci];
                MG31->_1DBC[((s8)ci)] = 1;
                memset(e, 0, sizeof(InputStruct));
                switch (g_Pitcher.pitcherActionState) {
                case 2:
                    if ((u8)MG31->bB_cpuSwingStep == 0) {
                        ((void (*)(void))fn_3_110634)(); // a call in the original (not inlined)
                        MG31->bB_cpuSwingStep = 1;
                    }
                    if (g_Pitcher.windupCountdownUntilBallReleased <= MG31->bB_cpuSwingFrame) {
                        e->buttonInput |= 0x100;
                    }
                    break;
                case 3:
                    if (g_Ball.pitchHangtimeCounter < g_Pitcher.frameWhenUnhittable - (s16)MG31->bB_cpuStickInput) {
                        e->buttonInput |= 0x100;
                    }
                    break;
                }
            }
            i++;
        } while (i < 4);
        atBat_batter();
        clearHitFlags_31F0();
        fn_3_2EA24();
        fn_3_8A958();
    }
    fn_3_111AC4();
}

// .text:0x00112BD8 size:0x7C0 mapped:0x80751C6C
// Bomb-omb Derby state machine: dispatches on the game state (g_GameLogic+0x11E).
// NONMATCHING 99%: register allocation in the inlined fn_3_111C5C copy (as in fn_3_111C5C itself).
#if NONMATCHING
void fn_3_112BD8(void) {
    switch (g_GameLogic.gameStatus) {
    case 4:
        fn_3_112610();
        break;
    case 26:
        fn_3_1125D0();
        break;
    case 6:
        fn_3_112558();
        break;
    case 7:
        fn_3_112450();
        break;
    case 0:
        fn_3_112230();
        break;
    case 1:
        fn_3_111C5C_inline();
        break;
    case 2:
        fn_3_111738();
        break;
    case 8:
        fn_3_112128();
        break;
    case 25:
        fn_3_1120E0();
        break;
    case 3:
        fn_3_111F80();
        break;
    case 15:
        fn_3_112070();
        break;
    }
}
#endif

