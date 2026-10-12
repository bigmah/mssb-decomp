#ifndef __AUTO_00_0009CD90_TEXT_GAME_H__
#define __AUTO_00_0009CD90_TEXT_GAME_H__

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

#include "game/running_logic.h" // GameRunningLogic g_RunningLogic

extern InMemFielderType g_Fielders[9];

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
