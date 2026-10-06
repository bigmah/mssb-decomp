#include "game/rep_940.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1200.h"
#include "static/UnknownHomes_Static.h"
extern f32 lbl_3_rodata_990;
extern f32 lbl_3_rodata_994;
extern f32 lbl_3_rodata_998;
extern f32 lbl_3_data_4474[];
extern u8 lbl_3_data_190C[];
extern u8 lbl_3_data_1888[];
extern u8 lbl_3_data_18A8[];
extern u8 lbl_3_data_18B4[];
extern u8 lbl_3_data_18C4[];
extern s8 lbl_3_data_18D8[];
extern u8 g_Scores[];
extern u8 lbl_3_data_18DC[];
extern u8 lbl_3_data_18E0[];
extern f32 lbl_3_data_18F0[];
extern f32 lbl_3_rodata_9AC;
extern u8 lbl_3_data_1880[];
extern u8 lbl_3_data_1924[];
extern s16 lbl_3_data_1934[];
extern u8 lbl_3_common_bss_37400[];
extern u8 g_RunningLogic[];
extern int RandomInt_Game_Range(int, int);
extern int RandomInt_Game(int);


// .text:0x00020CEC size:0x164 mapped:0x8065FD80
s32 fn_3_20CEC(f32 k) {
    f32 d;
    s32 t = g_Ball.pitchHangtimeCounter;
    if (t <= 1) {
        return 0;
    }
    if (lbl_3_rodata_990 == k) {
        return 0;
    }
    d = g_AiLogic.aiPitchCurveEndingX - g_Pitcher.pitchXPosition2;
    if (g_AiLogic.pitchAIDelayCurveStart != 0) {
        s32 r = g_Pitcher.frameWhenUnhittable - t;
        f32 lim;
        if (r <= 0) {
            return 0;
        }
        lim = k * (f32)((r / 2) * r);
        if (d < lbl_3_rodata_990) {
            if (-d < lim) {
                return 0;
            }
        } else if (d < lim) {
            return 0;
        }
        g_AiLogic.pitchAIDelayCurveStart = 0;
    }
    if (d > lbl_3_rodata_994) {
        if ((s8)g_AiLogic.aiPitchDirectionInput == -1) {
            return 0;
        }
        g_AiLogic.aiPitchDirectionInput = 1;
        return 1;
    }
    if (d < lbl_3_rodata_998) {
        if (*(s8*)&g_AiLogic.aiPitchDirectionInput == 1) {
            return 0;
        }
        *(s8*)&g_AiLogic.aiPitchDirectionInput = -1;
        return -1;
    }
    return 0;
}

// .text:0x00020E50 size:0x9C mapped:0x8065FEE4
void fn_3_20E50(void) {
    f32 d;
    if (g_Pitcher.currentStateFrameCounter >= 0x1E && g_AiLogic.aIMoundLocationX != g_Pitcher.pitcher.x) {
        d = g_AiLogic.aIMoundLocationX - g_Pitcher.pitcher.x;
        if (d > lbl_3_rodata_990) {
            if (d <= lbl_3_data_4474[2]) {
                g_Pitcher.pitcher.x = g_AiLogic.aIMoundLocationX;
            } else {
                g_Pitcher.pitcher.x += lbl_3_data_4474[2];
            }
        } else {
            if (d >= -lbl_3_data_4474[2]) {
                g_Pitcher.pitcher.x = g_AiLogic.aIMoundLocationX;
            } else {
                g_Pitcher.pitcher.x -= lbl_3_data_4474[2];
            }
        }
    }
}

// .text:0x00020EEC size:0xC4 mapped:0x8065FF80
void fn_3_20EEC(void) {
    s32 idx;
    f32 lo;
    f32 hi;
    f32 step;
    f32 fi;
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        g_AiLogic.aIMoundLocationX = lbl_3_rodata_990;
        return;
    }
    idx = RandomIndexFromWeights(lbl_3_data_190C + g_Pitcher.charClass * 6, 6);
    if (idx != 5) {
        g_AiLogic.aIMoundLocationIndex = idx;
        hi = lbl_3_data_4474[1];
        lo = lbl_3_data_4474[0];
        step = hi - lo;
        step = step / 5.0f;
        g_AiLogic.aIMoundLocationX = step * (f32)idx + lo;
    }
}

// .text:0x00020FB0 size:0x2F0 mapped:0x80660044
#pragma dont_inline on
void fn_3_20FB0(void) {
    u8 t;
    s32 tries;
    s32 pick;
    s32 r;
    s32 m;
    s32 i;
    if (g_AiLogic.aiPitchCurveType == 0) {
        g_AiLogic.aiPitchCurveType = 3;
        if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
            g_AiLogic.aiPitchCurveType = 1;
        }
    }
    if (g_AiLogic.aiPitchCurveType == 1) {
        g_AiLogic.aiPitchCurveEndingX = lbl_3_rodata_990;
    } else if (g_AiLogic.aiPitchCurveType == 2) {
        g_AiLogic.aiPitchCurveEndingX = lbl_3_rodata_9AC * (f32)RandomInt_Game_Range(-10, 10);
    } else if (g_AiLogic.aiPitchCurveType == 3) {
        tries = 0;
        if (RandomInt_Game(100) < lbl_3_data_18DC[g_AiLogic._49]) {
            while (1) {
                pick = g_AiLogic.aIMoundLocationIndex + RandomInt_Game(3);
                if (g_AiLogic.aIPitchDesiredEndingLocIndex == pick && tries < 2) {
                    tries++;
                    continue;
                }
                break;
            }
        } else {
            while (1) {
                r = RandomInt_Game(4);
                m = g_AiLogic.aIMoundLocationIndex;
                for (i = 0; i < 7; i++) {
                    if (i == m || i == m + 1 || i == m + 2) {
                        continue;
                    }
                    if (r == 0) {
                        break;
                    }
                    r--;
                }
                pick = i;
                if (g_AiLogic.aIPitchDesiredEndingLocIndex == pick && tries < 2) {
                    tries++;
                    continue;
                }
                break;
            }
        }
        g_AiLogic.aIPitchDesiredEndingLocIndex = pick;
        g_AiLogic.aiPitchCurveEndingX = lbl_3_data_18F0[pick];
    }
    g_AiLogic.pitchAIDelayCurveStart = 0;
    t = (lbl_3_data_18E0 + g_Pitcher.charClass * 4)[g_AiLogic._49];
    if (t < RandomInt_Game(100)) {
        g_AiLogic.pitchAIDelayCurveStart = 1;
    }
}

// .text:0x000212A0 size:0x30C mapped:0x80660334
void fn_3_212A0(void) {
    s32 f;
    s32 t;
    g_AiLogic.aIPitchType = 0;
    if (g_d_GameSettings.GameModeSelected != 2) {
        if (g_d_GameSettings.minigamesEnabled == 0) {
            u8 stars = g_GameLogic.TeamStars[g_GameLogic.teamFielding];
            if (stars != 0) {
                f = 0;
                if (*(s32*)g_Scores >= g_Scores[0xAA] && (u8*)g_Scores + g_GameLogic.awayTeamBattingInd_battingTeam * 0x26 + 4 > (u8*)g_Scores + g_GameLogic.homeTeamBattingInd_fieldingTeam * 0x26 + 4 && g_Strikes.outs >= 2) {
                    f = 1;
                } else if (*(s32*)g_Scores >= g_Scores[0xAB] && g_Scores[0xAD] != 0 && g_Strikes.outs >= 2) {
                    f = 1;
                } else if (*(s16*)(g_RunningLogic + 2) == 0x101 || *(s16*)(g_RunningLogic + 2) == 0x1101 || *(s16*)(g_RunningLogic + 2) == 0x1111) {
                    f = 1;
                }
                if (f != 0) {
                    t = (lbl_3_data_18C4 + stars * 4)[g_AiLogic._49 - 4];
                    if (g_AiLogic.nStarPitchesThrownThisAB != 0) {
                        t += lbl_3_data_18D8[0];
                    } else if (g_Strikes.strikes != 0) {
                        t += g_Strikes.strikes * lbl_3_data_18D8[1];
                    }
                    if (RandomInt_Game(100) < t) {
                        g_AiLogic.aIPitchType = 2;
                        g_Pitcher.starPitchInd = 1;
                        return;
                    }
                }
            }
        }
        if (*(s16*)g_RunningLogic == 1 || *(s16*)g_RunningLogic == 0x1101 || *(s16*)g_RunningLogic == 0x1111 || *(s16*)g_RunningLogic == 0x1001) {
            t = (lbl_3_data_1888 + g_Pitcher.charClass * 4)[g_AiLogic._49];
        } else {
            t = (lbl_3_data_1888 + g_Pitcher.charClass * 4)[g_AiLogic._49 + 0x10];
        }
        if (RandomInt_Game(100) < t) {
            g_AiLogic.aIPitchType = 1;
            if (RandomInt_Game(100) < (lbl_3_data_18B4 + g_Pitcher.charClass * 4)[g_AiLogic._49]) {
                g_AiLogic.aIPitchType = 3;
                g_Pitcher.TypeOfPitch = 2;
                return;
            }
            t = (lbl_3_data_18A8 + g_Strikes.strikes * 4)[g_AiLogic._49];
            if (RandomInt_Game(100) < t) {
                g_AiLogic.aIPerfectCharge = 1;
            }
        }
    }
}
#pragma dont_inline reset

// .text:0x000215AC size:0x1BC mapped:0x80660640
void fn_3_215AC(void) {
    f32 d;
    f32 b;
    f32 a;
    f32 s;
    if (g_Pitcher.currentStateFrameCounter == 1) {
        fn_3_20EEC();
    }
    if (g_Pitcher.currentStateFrameCounter >= 0x1E && (a = g_AiLogic.aIMoundLocationX) != (b = g_Pitcher.pitcher.x)) {
        d = a - b;
        if (d > lbl_3_rodata_990) {
            if (d <= lbl_3_data_4474[2]) {
                g_Pitcher.pitcher.x = a;
            } else {
                g_Pitcher.pitcher.x = b + lbl_3_data_4474[2];
            }
        } else {
            s = lbl_3_data_4474[2];
            if (d >= -s) {
                g_Pitcher.pitcher.x = a;
            } else {
                g_Pitcher.pitcher.x = b - s;
            }
        }
    }
    if (g_Pitcher.currentStateFrameCounter >= *(s16*)&g_AiLogic.AIFrameToBeginPitch && g_Batter.beginningOfABAnimationOccuring == 0) {
        fn_3_212A0();
        fn_3_20FB0();
        fn_3_750C4(2);
        *((u8*)&g_Stats + 0x38) = 1;
    }
}

// .text:0x00021768 size:0x238 mapped:0x806607FC
void fn_3_21768(void) {
    int r;
    g_AiLogic.pitcherAIPitchDownTheMiddleInd = 0;
    if (g_d_GameSettings.GameModeSelected == 2) {
        if (g_Practice.practiceType_2 == 1) {
            g_AiLogic.pitcherAIPitchDownTheMiddleInd = 1;
        } else if (g_Practice.practiceType_2 == 2) {
            g_AiLogic.pitcherAIPitchDownTheMiddleInd = 1;
        } else if (g_Practice.practiceType_2 == 3) {
            g_AiLogic.pitcherAIPitchDownTheMiddleInd = 1;
        } else if (g_Practice.practiceLevel == 4) {
            g_AiLogic.pitcherAIPitchDownTheMiddleInd = 1;
        }
    }
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        g_AiLogic.aiPitchCurveEndingX = lbl_3_rodata_990;
    }
    g_AiLogic._49 = lbl_3_data_1880[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam]];
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        g_AiLogic.AIFrameToBeginPitch = lbl_3_data_1934[2];
    } else {
        g_AiLogic.AIFrameToBeginPitch = RandomInt_Game_Range(lbl_3_data_1934[0], lbl_3_data_1934[1]);
    }
    if (g_d_GameSettings.exhibitionMatchInd == 0 && *(u8*)(lbl_3_common_bss_37400 + 0x46) != 0 && g_Pitcher.nPitchesThisAB == 0) {
        g_AiLogic.AIFrameToBeginPitch = lbl_3_data_1934[1] + 0x3C;
    }
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd == 0) {
        g_AiLogic.aIPitcherPickOffInd = 0;
        if (*(s16*)(g_RunningLogic + 2) != 1 && *(s16*)(g_RunningLogic + 2) != 0x1111) {
            if (g_AiLogic.always0_AIPickoffRelated != 0) {
                r = 5;
            } else {
                r = (lbl_3_data_1924 + g_Pitcher.charClass * 4)[g_AiLogic._49];
            }
            if (RandomInt_Game(100) < r) {
                g_AiLogic.aIPitcherPickOffInd = 1;
            }
        }
    }
    g_AiLogic.aiPitchCurveType = 0;
    g_AiLogic.aiPitchDirectionInput = 0;
    g_AiLogic.pitchAIDelayCurveStart = 0;
    g_AiLogic.aIPerfectCharge = 0;
}

// .text:0x000219A0 size:0x2C mapped:0x80660A34
void fn_3_219A0(void) {
    g_AiLogic.nStarPitchesThrownThisAB = 0;
    g_AiLogic.aIMoundLocationX = lbl_3_rodata_990;
    g_AiLogic.aIMoundLocationIndex = 2;
    g_AiLogic.always0_AIPickoffRelated = 0;
}

