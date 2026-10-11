#ifndef __AUTO_00_0009CD90_TEXT_GAME_H__
#define __AUTO_00_0009CD90_TEXT_GAME_H__

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// g_RunningLogic (0x20 bytes); only the fields used here.
typedef struct GameRunningLogic {
    /*0x00*/ s16 _00; // play-event flags (0x10, 0x1000, ...)
    /*0x02*/ s16 occupiedBases; // one nibble per base (0x1, 0x10, 0x100, 0x1000)
    /*0x04*/ u8 _04[0x10 - 0x4];
    /*0x10*/ u8 _10;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13;
    /*0x14*/ u8 _14;
    /*0x15*/ u8 _15; // runners on base
    /*0x16*/ u8 _16[0x20 - 0x16];
} GameRunningLogic; // size: 0x20

extern GameRunningLogic g_RunningLogic;

// g_Fielders entry (0x268 bytes); only the fields used here.
typedef struct GameFielder {
    /*0x000*/ u8 _000[0x178];
    /*0x178*/ s16 rosterID;
    /*0x17A*/ u8 _17A[0x18C - 0x17A];
    /*0x18C*/ s16 _18C; // base the fielder is covering
    /*0x18E*/ u8 _18E[0x1C4 - 0x18E];
    /*0x1C4*/ u8 _1C4; // index into lbl_3_data_1C30 (fn_3_1DEB8)
    /*0x1C5*/ u8 _1C5[0x1E0 - 0x1C5];
    /*0x1E0*/ u8 _1E0;
    /*0x1E1*/ u8 _1E1[0x268 - 0x1E1];
} GameFielder; // size: 0x268

extern GameFielder g_Fielders[9];

extern GameScores g_Scores;
extern u8 lbl_80361B20[54];

void fn_3_9CD90(void);
void fn_3_9CE78(void);
void fn_3_9D140(void);
s32 fn_3_9D374(void);
void fn_3_9D550(void);
void fn_3_9D594(void);
void fn_3_9D600(void);
void fn_3_9D6A4(void);
void fn_3_9DB5C(void);
void fn_3_9DBE4(void);
void fn_3_9DC18(u8* arr, u32 n, BOOL useBallRng);
void fn_3_9E078(s32* arr, s32 n, BOOL useBallRng);
s32 fn_3_9E368(s32* weights, s32 n);
// RandomIndexFromWeights: declared in game/UnknownHomes_Game.h
void fn_3_9E7D4(s32 i);
s32 fn_3_9E834(void);
s32 fn_3_9EA1C(s32 idx);

#endif
