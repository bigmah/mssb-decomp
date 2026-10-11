#ifndef __GAME_AUTO_00_000759BC_TEXT_H_
#define __GAME_AUTO_00_000759BC_TEXT_H_

#include "mssbTypes.h"
#include "game/auto_00_0007CE90_text.h"

// Saturating counters used by the box-score bookkeeping.
#define STAT_INC_U8(x)                \
    do {                              \
        u8* stat_ = &(x);             \
        if (*stat_ < 0xFE) {          \
            *stat_ += 1;              \
        } else {                      \
            *stat_ = 0xFF;            \
        }                             \
    } while (0)
#define STAT_INC_U16(x)               \
    do {                              \
        u16* stat_ = &(x);            \
        if (*stat_ < 0xFFFE) {        \
            *stat_ += 1;              \
        } else {                      \
            *stat_ = 0xFFFF;          \
        }                             \
    } while (0)

// lbl_803537E4: per-player batting/fielding record, [2 teams][9].
typedef struct BattingRecord {
    /*0x00*/ u8 rosterSlot;
    /*0x01*/ u8 _01[2];
    /*0x03*/ u8 plateAppearances;
    /*0x04*/ u8 atBats;
    /*0x05*/ u8 hits;
    /*0x06*/ u8 singles;
    /*0x07*/ u8 doubles;
    /*0x08*/ u8 triples;
    /*0x09*/ u8 homeRuns;
    /*0x0A*/ u8 _0A; // result 13
    /*0x0B*/ u8 _0B; // result 14
    /*0x0C*/ u8 _0C; // result 15
    /*0x0D*/ u8 strikeouts; // result 1
    /*0x0E*/ u8 walks;      // result 2
    /*0x0F*/ u8 hitByPitch; // result 3
    /*0x10*/ u8 rbi;
    /*0x11*/ u8 runs;
    /*0x12*/ u8 _12; // advanced a base
    /*0x13*/ u8 _13; // at-bats with runners on (g_RunningLogic._15)
    /*0x14*/ u8 _14; // hits with runners on
    /*0x15*/ u8 _15;
    /*0x16*/ u8 _16;
    /*0x17*/ u8 _17; // rbi with runners on
    /*0x18*/ u8 _18; // home runs with runners on
    /*0x19*/ u8 _19[0x22 - 0x19];
    /*0x22*/ u8 _22;
    /*0x23*/ u8 _23;
    /*0x24*/ u8 _24[2];
} BattingRecord; // size: 0x26

// lbl_803535C8: per-player pitching record, [2 teams][9].
typedef struct PitchingRecord {
    /*0x00*/ u16 battersFaced;
    /*0x02*/ u16 _02;
    /*0x04*/ u16 _04;
    /*0x06*/ u16 walks;
    /*0x08*/ u16 hitByPitch;
    /*0x0A*/ u16 hitsAllowed;
    /*0x0C*/ u16 homeRunsAllowed;
    /*0x0E*/ u16 _0E;
    /*0x10*/ u8 _10[3];
    /*0x13*/ u8 wins;
    /*0x14*/ u8 losses;
    /*0x15*/ u8 saves;
    /*0x16*/ u8 _16;
    /*0x17*/ u8 _17;
    /*0x18*/ u8 _18;
    /*0x19*/ u8 _19;
    /*0x1A*/ u8 outsPitched;
    /*0x1B*/ u8 _1B;
    /*0x1C*/ u8 strikeouts;
    /*0x1D*/ u8 _1D;
} PitchingRecord; // size: 0x1E

// lbl_80353A90: line score and game summary (size 0x108).
typedef struct LineScore {
    /*0x000*/ u8 _000[8];
    /*0x008*/ u16 runs[2][19]; // [team][0] total, [team][n] inning n
    /*0x054*/ u16 hits[2][19];
    /*0x0A0*/ s8 _0A0[0x46]; // [0..49] home-run log (roster index, +9 for team 1);
                             // [0x1E + team * 0x14 (+2)] also read per team
    /*0x0E6*/ u8 _0E6[0xA];
    /*0x0F0*/ u8 errors[2];
    /*0x0F2*/ u8 winner; // team index, 2: tie
    /*0x0F3*/ s8 winningPitcher;
    /*0x0F4*/ s8 losingPitcher;
    /*0x0F5*/ s8 savePitcher;
    /*0x0F6*/ u8 innings;
    /*0x0F7*/ u8 _0F7;
    /*0x0F8*/ u8 _0F8[2];
    /*0x0FA*/ s8 _0FA;
    /*0x0FB*/ s8 _0FB;
    /*0x0FC*/ u8 _0FC;
    /*0x0FD*/ s8 _0FD;
    /*0x0FE*/ s8 _0FE;
    /*0x0FF*/ s8 _0FF;
    /*0x100*/ s8 _100;
    /*0x101*/ s8 mvp[2]; // roster index per team
    /*0x103*/ u8 mvpCharID;
    /*0x104*/ u8 mvpKind;
    /*0x105*/ u8 _105[3];
} LineScore; // size: 0x108

// lbl_3_common_bss_32A38: per-pitcher game counters, [2 teams][9].
typedef struct PitcherGameStat {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 _1;
    /*0x2*/ u8 _2[3];
} PitcherGameStat; // size: 0x5

// lbl_8034E9A0 + 0x4908: play-by-play log, [2 teams][100].
typedef struct PlayLogEntry {
    /*0x0*/ u16 inning : 5;
    /*0x0*/ u16 batter : 4;
    /*0x1*/ u16 detail : 4;
    /*0x1*/ u16 rbi : 3;
    /*0x2*/ s8 batterSlot;
    /*0x3*/ s8 result;
} PlayLogEntry; // size: 0x4

// lbl_8034E9A0 (size 0x4C28), only the fields used here.
typedef struct Bss8034E9A0View {
    /*0x0000*/ u8 _0000[0x4908];
    /*0x4908*/ PlayLogEntry playLog[2][100];
} Bss8034E9A0View; // size: 0x4C28

// lbl_3_data_60F8: MVP score weights.
typedef struct MvpWeights {
    /*0x0*/ u8 winningPitcher;
    /*0x1*/ u8 _1;
    /*0x2*/ u8 homeRuns;
    /*0x3*/ u8 _3;
    /*0x4*/ u8 _4;
    /*0x5*/ u8 _5;
    /*0x6*/ u8 strikeouts;
    /*0x7*/ u8 rbi;
    /*0x8*/ u8 onBase;
    /*0x9*/ u8 _9;
} MvpWeights;

// g_Fielders (stride 0x268), only the fields used here.
typedef struct FielderView {
    /*0x000*/ u8 _000[0x178];
    /*0x178*/ s16 rosterID;
    /*0x17A*/ u8 _17A[0x268 - 0x17A];
} FielderView; // size: 0x268

// lbl_3_common_bss_37400, only the fields used here.
typedef struct Bss37400View {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ s16 _40; // team whose stats feed fn_3_161588
} Bss37400View;

void fn_3_759BC(void);
void fn_3_76174(void);
void fn_3_76558(void);
void fn_3_76A9C(void);
void fn_3_76C78(void);
void fn_3_76D08(s32 batterSlot, s32 result, u8 detail, s32 rbi);

#endif
