#include "game/rep_A00.h"
#define REP_HEADER_FN repHeader_A00
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"
#include "game/auto_00_000249E8_text.h"
#include "main/file_80069BDC.h"
#include "main/file_80039AC0.h"
#include "Dolphin/stl.h"
#include "game/auto_00_000FBCD0_text.h"
#include "game/auto_00_0006C854_text.h"
#include "game/auto_00_0005985C_text.h"
#include "game/rep_E08.h"
#include "main/file_80011640.h"
#include "game/rep_540.h"
#include "game/rep_1200.h"
#include "game/game_batter.h"
#include "game/rep_13B8.h"
#include "game/rep_868.h"
#include "game/rep_AC8.h"
#include "game/auto_00_001658F0_text.h"
#include "game/rep_1330.h"
#include "game/auto_00_000219CC_text.h"
#include "game/rep_3880.h"
#include "game/auto_00_0006B4C8_text.h"
#include "main/file_8001FE00.h"

// Views declared here (other units have their own views of these objects).
extern FielderView g_Fielders[];
extern SceneWork* lbl_3_common_bss_1323C;
extern GameScores g_Scores;
extern ScreenFx lbl_803C5090;
// .data lbl_3_data_1D28..37AC: separate objects that the code reaches through one pooled base.
// Scene actor placements (used by auto_00_000249E8_text).
SceneActorSetup lbl_3_data_1D28[18] = {
    {{0.0f, 0.0f, 15.0f}, 0.0f, 2, 0, 0, 0, 1, 0, 0, 0, {0, 0}},
    {{0.0f, 0.0f, -3.0f}, 0.0f, 2, 0, 1, 0, 1, 0, 0, 0, {0, 0}},
    {{20.0f, 0.0f, 25.0f}, 0.6f, 2, 0, 2, 0, 1, 0, 0, 0, {0, 0}},
    {{12.0f, 0.0f, 40.0f}, 0.0f, 2, 0, 3, 0, 1, 0, 0, 0, {0, 0}},
    {{-20.0f, 0.0f, 25.0f}, -0.6f, 2, 0, 4, 0, 1, 0, 0, 0, {0, 0}},
    {{-12.0f, 0.0f, 40.0f}, 0.0f, 2, 0, 5, 0, 1, 0, 0, 0, {0, 0}},
    {{-40.0f, 0.0f, 67.0f}, 0.0f, 2, 0, 6, 0, 1, 0, 0, 0, {0, 0}},
    {{0.0f, 0.0f, 85.0f}, 0.0f, 2, 0, 7, 0, 1, 0, 0, 0, {0, 0}},
    {{40.0f, 0.0f, 67.0f}, 0.0f, 2, 0, 8, 0, 1, 0, 0, 0, {0, 0}},
    {{-0.0f, 0.0f, 0.6f}, -0.85f, 59, 0, 9, 2, 1, 0, 0, 0, {0, 0}},
    {{0.15f, 0.0f, 0.3f}, -0.85f, 60, 40, 9, 2, 1, 0, 0, 0, {0, 0}},
    {{0.1f, 0.0f, 0.5f}, -0.85f, 60, 0, 9, 2, 1, 0, 0, 0, {0, 0}},
    {{0.0f, -0.09f, 16.8f}, 0.0f, 69, 0, 0, 0, 1, 0, 0, 0, {0, 0}},
    {{0.0f, -0.09f, 16.8f}, 0.0f, 69, 0, 0, 0, 1, 0, 0, 0, {0, 0}},
    {{-1.2f, 0.0f, -2.2f}, -2.9f, 69, 0, 1, 0, 1, 0, 0, 0, {0, 0}},
    {{-1.2f, 0.0f, -2.2f}, -2.9f, 69, 0, 1, 0, 1, 0, 0, 0, {0, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0}},
};
// Actor-setup scripts per mode (0xFE ends a script).
static u8 lbl_3_data_1F20[8] = {18, 23, 11, 14, 10, 254, 0, 0};
static u8 lbl_3_data_1F28[8] = {18, 24, 11, 14, 16, 254, 0, 0};
static u8 lbl_3_data_1F30[8] = {18, 26, 12, 15, 17, 2, 9, 254};
static u8 lbl_3_data_1F38[8] = {18, 25, 13, 14, 17, 4, 10, 254};
u8* lbl_3_data_1F40[4] = {lbl_3_data_1F20, lbl_3_data_1F28, lbl_3_data_1F30, lbl_3_data_1F38};
// Scene events that are blocked outside exhibition matches.
static s8 lbl_3_data_1F50[0x21] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1};
// Scene ids, indexed by SCENE->_260.
static s32 lbl_3_data_1F74[0x21] = {
    85, 86, 87, 88, 85, 86, 87, 88,
    89, 85, 86, 87, 88, 89, 91, 92,
    93, 94, 91, 92, 93, 94, 96, 91,
    92, 93, 94, 96, 96, 90, 90, 96,
    96,
};
// Scene ids per runner character.
static s32 lbl_3_data_1FF8[0x37] = { // fn_3_23CEC
    79, 79, 79, 79, 79, 79, 79, 79,
    79, 79, 79, 79, 79, 79, 79, 79,
    79, 79, 79, 79, 79, 79, 79, 79,
    79, 79, 79, 79, 79, 79, 79, 79,
    79, 79, 79, 79, 79, 79, 79, 79,
    79, 79, 79, 79, 79, 79, 79, 79,
    79, 79, 79, 79, 79, 79, 79,
};
static s32 lbl_3_data_20D4[0x37] = { // runner on first
    82, 82, 82, 82, 82, 82, 82, 82,
    82, 82, 82, 82, 82, 82, 82, 82,
    82, 82, 82, 82, 82, 82, 82, 82,
    82, 82, 82, 82, 82, 82, 82, 82,
    82, 82, 82, 82, 82, 82, 82, 82,
    82, 82, 82, 82, 82, 82, 82, 82,
    82, 82, 82, 82, 82, 82, 82,
};
static s32 lbl_3_data_21B0[0x37] = { // runner on second
    83, 83, 83, 83, 83, 83, 83, 83,
    83, 83, 83, 83, 83, 83, 83, 83,
    83, 83, 83, 83, 83, 83, 83, 83,
    83, 83, 83, 83, 83, 83, 83, 83,
    83, 83, 83, 83, 83, 83, 83, 83,
    83, 83, 83, 83, 83, 83, 83, 83,
    83, 83, 83, 83, 83, 83, 83,
};
static s32 lbl_3_data_228C[0x37] = { // runner on third
    84, 84, 84, 84, 84, 84, 84, 84,
    84, 84, 84, 84, 84, 84, 84, 84,
    84, 84, 84, 84, 84, 84, 84, 84,
    84, 84, 84, 84, 84, 84, 84, 84,
    84, 84, 84, 84, 84, 84, 84, 84,
    84, 84, 84, 84, 84, 84, 84, 84,
    84, 84, 84, 84, 84, 84, 84,
};
// Scene ids by challenge stage (_8A set), and without.
static s32 lbl_3_data_2368[6] = {101, 101, 101, 101, 101, 101};
static s32 lbl_3_data_2380[6] = {102, 102, 102, 102, 102, 102};
// The scene events.
Unk2398Entry lbl_3_data_2398[0x21] = {
    {1, -1, -1, {-1, 1, 0}, -1, -1, -1, 0, 1, -1, 96, {0, 0, 0}},
    {1, -1, -1, {-1, 0, 1}, -1, -1, -1, 0, 1, -1, 97, {0, 0, 0}},
    {1, -1, -1, {0, 1, 1}, -1, -1, -1, 0, 1, -1, 98, {0, 0, 0}},
    {1, -1, -1, {1, 1, 1}, -1, -1, -1, 0, 1, -1, 99, {0, 0, 0}},
    {2, -1, -1, {-1, 1, 0}, 1, -1, -1, 0, 1, -1, 96, {0, 0, 0}},
    {2, -1, -1, {-1, 0, 1}, 1, -1, -1, 0, 1, -1, 97, {0, 0, 0}},
    {2, -1, -1, {0, 1, 1}, 1, -1, -1, 0, 1, -1, 98, {0, 0, 0}},
    {2, -1, -1, {1, 1, 1}, -1, -1, -1, 0, 1, -1, 99, {0, 0, 0}},
    {2, -1, -1, {-1, 1, -1}, -1, -1, 1, 0, 1, 1, 100, {0, 0, 0}},
    {3, -1, -1, {-1, 1, 0}, 1, -1, -1, 0, 1, -1, 96, {0, 0, 0}},
    {3, -1, -1, {-1, 0, 1}, 1, -1, -1, 0, 1, -1, 97, {0, 0, 0}},
    {3, -1, -1, {0, 1, 1}, 1, -1, -1, 0, 1, -1, 98, {0, 0, 0}},
    {3, -1, -1, {1, 1, 1}, -1, -1, -1, 0, 1, -1, 99, {0, 0, 0}},
    {3, -1, -1, {-1, 1, -1}, -1, -1, 1, 0, 1, 1, 100, {0, 0, 0}},
    {1, -1, -1, {-1, 1, 0}, -1, -1, -1, 0, 1, 1, 96, {0, 0, 0}},
    {1, -1, -1, {-1, 0, 1}, -1, -1, -1, 0, 1, 1, 97, {0, 0, 0}},
    {1, -1, -1, {0, 1, 1}, -1, -1, -1, 0, 1, 1, 98, {0, 0, 0}},
    {1, -1, -1, {1, 1, 1}, -1, -1, -1, 0, 1, 1, 99, {0, 0, 0}},
    {2, -1, -1, {-1, 1, 0}, 2, -1, -1, 0, 1, 1, 96, {0, 0, 0}},
    {2, -1, -1, {-1, 0, 1}, 2, -1, -1, 0, 1, 1, 97, {0, 0, 0}},
    {2, -1, -1, {0, 1, 1}, 2, -1, -1, 0, 1, 1, 98, {0, 0, 0}},
    {2, -1, -1, {1, 1, 1}, -1, -1, -1, 0, 1, 1, 99, {0, 0, 0}},
    {2, -1, -1, {-1, 1, -1}, -1, -1, 1, 0, 1, 1, 100, {0, 0, 0}},
    {3, -1, -1, {-1, 1, 0}, 2, -1, -1, 0, 1, 1, 96, {0, 0, 0}},
    {3, -1, -1, {-1, 0, 1}, 2, -1, -1, 0, 1, 1, 97, {0, 0, 0}},
    {3, -1, -1, {0, 1, 1}, 2, -1, -1, 0, 1, 1, 98, {0, 0, 0}},
    {3, -1, -1, {1, 1, 1}, -1, -1, -1, 0, 1, 1, 99, {0, 0, 0}},
    {3, -1, -1, {-1, 1, -1}, -1, -1, 1, 0, 1, 1, 100, {0, 0, 0}},
    {1, -1, -1, {-1, -1, -1}, -1, -1, 1, 1, 1, 1, 100, {0, 0, 0}},
    {4, -1, 2, {-1, -1, -1}, -1, 0, -1, 0, 1, 1, 99, {0, 0, 0}},
    {4, -1, 2, {-1, -1, -1}, -1, 1, -1, 0, 1, 1, 99, {0, 0, 0}},
    {4, -1, -1, {-1, -1, -1}, -1, -1, 1, 0, 1, 1, 100, {0, 0, 0}},
    {4, -1, -1, {-1, -1, -1}, -1, -1, 1, 0, 1, 1, 100, {0, 0, 0}},
};
// [batter][pitcher] captain pairs with a duel cutscene.
static u8 lbl_3_data_2BD8[0x37][0x37] = {
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
extern StarChanceState lbl_3_common_bss_37400;
extern Unk32724 lbl_3_common_bss_32724;
extern StarChanceOdds lbl_80109420[];
extern ARAMLoaderView lbl_803C6CF8;
extern CharVoiceAnim lbl_3_data_7F7C[];

extern const f32 lbl_3_rodata_A50;
extern const f32 lbl_3_rodata_A54; // 0.0f
extern const f64 lbl_3_rodata_A58; // 0.02
extern const f64 lbl_3_rodata_A60; // -0.02
extern const f32 lbl_3_rodata_A68; // 1 degree in radians
extern const f32 lbl_3_rodata_A6C; // 3.0f, arrival distance
// .bss (laid out last-defined-first)
static u8 lbl_3_bss_A4[0x24]; // unused
static s32 lbl_3_bss_A0;
static s32 lbl_3_bss_9C;
static u8 lbl_3_bss_98[0x4]; // unused

void fn_80052798(s32 count); // main/file_8004C5F8.h
f32 fn_3_9FEA8(f32 v);        // game/rep_1838.h: wrap angle
u32 fn_3_90220(s32 idx, s32 off);
void fn_3_8C07C(void);
void fn_3_8C104(s32 v); // game/m_sound.h (conflicts with another header here)

#define SCENE lbl_3_common_bss_1323C
#define FADE_TASK ((FadeTask*)lbl_803CC1B8)

// Inline copy of fn_3_24DBC (auto_00_000249E8_text.c): clears the scene actors and starts scene mode `mode`.
static inline void SceneReset(s32 mode) {
    s32 i;

    for (i = 0; i < 13; i++) {
        SCENE->actorSetup[i] = -1;
        memset(&SCENE->actors[i], 0, sizeof(SceneActorState));
        SCENE->animSet[i] = 0;
    }
    fn_3_6714C(0);
    SCENE->_25C = 1;
    SCENE->_23C = 0;
    SCENE->_27C = 0;
    SCENE->mode = mode;
    SCENE->_25F = 1;
    SCENE->_27D = 0;
    SCENE->busy = 0;
    SCENE->_25A = 0;
    SCENE->_280 = 1;
}

// Plays the batter's voice when actor 9 (the batter) is in its swing animation.
static inline void BatterVoice(void) {
    CharActor* a = lbl_8036E548.active[9];
    if (a->anim[0] == 0x3C && a->_06A[0] == lbl_3_data_7F7C[lbl_800E8558[g_Batter.charID]._2].anim) {
        fn_3_90220(g_Batter.charID, 0);
    }
}

// .text:0x00021C90 size:0x154 mapped:0x80660D24
void fn_3_21C90(void) {
    FadeTask* p = FADE_TASK;
    switch (lbl_3_bss_A0) {
    case 0:
        p->frame = 0;
        p->alpha = 0xFF;
        lbl_803C5090.flags = 9;
        lbl_803C5090.scale = 1.0f;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.repeat = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.r = 0xFF;
        lbl_803C5090.g = 0xFF;
        lbl_803C5090.b = 0xFF;
        lbl_803C5090.alpha = p->alpha;
        lbl_3_bss_A0 += 1;
        return;
    case 1:
        lbl_803C5090.flags = 8;
        lbl_803C5090.scale = lbl_3_rodata_A50;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.repeat = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.r = 0xFF;
        lbl_803C5090.g = 0xFF;
        lbl_803C5090.b = 0xFF;
        lbl_803C5090.alpha = p->alpha;
        p->frame = p->frame + 1;
        if (g_pCamera->_AAC <= p->frame) {
            g_pCamera->_AA8 = 0;
            REMOVE_QUEUE_NOARG();
            lbl_3_bss_A0 = 0;
            return;
        }
        p->alpha = 0xFF - (p->frame * 0xFF) / g_pCamera->_AAC;
        return;
    case 2:
    default:
        return;
    }
}

// .text:0x00021DE4 size:0x130 mapped:0x80660E78
void fn_3_21DE4(void) {
    FadeTask* p = FADE_TASK;
    switch (lbl_3_bss_9C) {
    case 0:
        p->frame = 0;
        p->alpha = 0xFF;
        lbl_803C5090.flags = 9;
        lbl_803C5090.scale = 1.0f;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.repeat = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.r = 0xFF;
        lbl_803C5090.g = 0xFF;
        lbl_803C5090.b = 0xFF;
        lbl_803C5090.alpha = 0xFF;
        lbl_3_bss_9C += 1;
        return;
    case 1:
        lbl_803C5090.flags = 8;
        lbl_803C5090.scale = lbl_3_rodata_A50;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.repeat = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.r = 0xFF;
        lbl_803C5090.g = 0xFF;
        lbl_803C5090.b = 0xFF;
        lbl_803C5090.alpha = 0xFF;
        p->frame = p->frame + 1;
        if (g_pCamera->_AAE <= p->frame) {
            g_pCamera->_AAA = 0;
            REMOVE_QUEUE_NOARG();
            lbl_3_bss_9C = 0;
        }
        return;
    case 2:
    default:
        return;
    }
}

// .text:0x00021F14 size:0x828 mapped:0x80660FA8
// NONMATCHING 96%: register allocation; the original also keeps &e->outs / &e->situation in registers
#if NONMATCHING
// Picks the scripted scene event for the current situation into SCENE->_260.
// Returns 1 when one should play.
s32 fn_3_21F14(void) {
    ChallengeState* cs = &gChallengeState;
    GameInitVariables* gs = &g_d_GameSettings;
    StarChanceState* sch = &lbl_3_common_bss_37400;
    s32 star;
    s32 i;
    s32 ok;
    s32 want;
    s32 duel;
    Unk2398Entry* e;
    s8 idx;
    GameScores* sc;
    inMemStrikes* sk;
    InMemRunnerType* rn;
    GameControlsStruct* gl;
    InMemBatterType* bt;
    InMemPitcherType* pt;

    star = 0;
    if (gs->exhibitionMatchInd == 0) {
        if (cs->_441E == 5 || cs->_16C2 == 0x2A) {
            star = 0;
        } else {
            star = fn_3_165D24();
        }
    }
    if (gs->exhibitionMatchInd == 0) {
        if (star != 0 && lbl_80109420[sch->type]._D != 0) {
            SCENE->_260 = 0x1C;
            cs->_44F1 = 0;
            return 1;
        }
        return 0;
    }

    SCENE->_260 = -1;
    sc = &g_Scores;
    sk = &g_Strikes;
    rn = g_Runners;
    gl = &g_GameLogic;
    bt = &g_Batter;
    pt = &g_Pitcher;
    for (i = 0; i < 0x21; i++) {
        if (i == 0x2D) {
            i = 0x2D;
        }
        e = &lbl_3_data_2398[i];
        ok = 1;
        if (sc->_AC != e->inning) {
            if (e->inning == 1 && sc->_AC != 1 && sc->_AC != 0) {
                ok = 0;
            } else if (e->inning != 1 && (sc->_AC == 1 || sc->_AC == 0)) {
                ok = 0;
            } else if (e->inning == 2 && sc->_AC != 2) {
                ok = 0;
            } else if (e->inning != 2 && sc->_AC == 2) {
                ok = 0;
            } else if (e->inning == 3 && sc->_AC != 3) {
                ok = 0;
            } else if (e->inning != 3 && sc->_AC == 3) {
                ok = 0;
            } else if (e->inning == 4 && sc->_AC < 4) {
                ok = 0;
            } else if (e->inning != 4 && sc->_AC >= 4) {
                ok = 0;
            }
        }
        if (e->outs != -1 && sk->outs != e->outs) {
            ok = 0;
        }
        want = e->runner[0];
        if (want != -1) {
            if (want == 1 && rn[1].rosterID == -1) {
                ok = 0;
            } else if (want == 0 && rn[1].rosterID != -1) {
                ok = 0;
            }
        }
        want = e->runner[1];
        if (want != -1) {
            if (want == 1 && rn[2].rosterID == -1) {
                ok = 0;
            } else if (want == 0 && rn[2].rosterID != -1) {
                ok = 0;
            }
        }
        want = e->runner[2];
        if (want != -1) {
            if (want == 1 && rn[3].rosterID == -1) {
                ok = 0;
            } else if (want == 0 && rn[3].rosterID != -1) {
                ok = 0;
            }
        }
        if (e->situation != -1) {
            // inline copy of fn_3_22ABC
            GameScores* scs = &g_Scores;
            s32 close = 0;
            s32 n = 0;
            s32 sit;
            if (rn[1].rosterID != -1) {
                n = 1;
            }
            if (rn[2].rosterID != -1) {
                n += 1;
            }
            if (rn[3].rosterID != -1) {
                n += 1;
            }
            if (__abs(scs->_A6) <= 4 && n == 3
                && scs->team[gl->homeTeamBattingInd_fieldingTeam].runs[0] <= scs->team[gl->awayTeamBattingInd_battingTeam].runs[0]) {
                close = 1;
            }
            n = 0;
            if (rn[2].rosterID != -1) {
                n = 1;
            }
            if (rn[3].rosterID != -1) {
                n += 1;
            }
            if (__abs(scs->_A6) <= n && n > 0
                && scs->team[gl->homeTeamBattingInd_fieldingTeam].runs[0] <= scs->team[gl->awayTeamBattingInd_battingTeam].runs[0]) {
                close = 1;
            }
            if (close != 0) {
                if (bt->aiControlledInd != 0) {
                    sit = 1;
                } else {
                    sit = 2;
                }
            } else {
                sit = -1;
            }
            want = e->situation;
            if (want == 0 && sit != 0) {
                ok = 0;
            }
            if (want == 1 && sit != 1) {
                ok = 0;
            }
            if (want == 2 && sit != 2) {
                ok = 0;
            }
        }
        want = e->leading;
        if (want != -1) {
            s32 lead;
            if (bt->aiControlledInd != 0) {
                if (g_Scores.team[gl->homeTeamBattingInd_fieldingTeam].runs[0] < g_Scores.team[gl->awayTeamBattingInd_battingTeam].runs[0]) {
                    lead = 0;
                } else {
                    lead = 1;
                }
            } else if (g_Scores.team[gl->homeTeamBattingInd_fieldingTeam].runs[0] < g_Scores.team[gl->awayTeamBattingInd_battingTeam].runs[0]) {
                lead = 1;
            } else {
                lead = 0;
            }
            if (want == 0 && lead != 0) {
                ok = 0;
            } else if (want == 1 && lead != 1) {
                ok = 0;
            }
        }
        duel = e->captainDuel;
        if (duel != -1) {
            if (duel == 1 && lbl_3_data_2BD8[bt->charID][pt->charID] == 0) {
                if (g_GameLogic.Team_CaptainRosterLoc[gl->teamBatting] != bt->charID
                    || g_GameLogic.Team_CaptainRosterLoc[gl->teamFielding] != pt->charID) {
                    ok = 0;
                }
            } else if (duel == 0 && lbl_3_data_2BD8[bt->charID][pt->charID] == 1) {
                ok = 0;
            }
        }
        if (e->once != -1 && e->once != 0 && e->_34[0] != 0) {
            ok = 0;
        }
        if (e->_28 != -1 && e->_28 != 0) {
            if (e->_34[1] != 0) {
                if (duel == 1 && lbl_3_data_2BD8[bt->charID][pt->charID] == 1) {
                    if (g_GameLogic.Team_CaptainRosterLoc[gl->teamBatting] == bt->charID
                        && g_GameLogic.Team_CaptainRosterLoc[gl->teamFielding] == pt->charID) {
                        if (e->_34[2] != 0) {
                            ok = 0;
                        }
                    } else {
                        ok = 0;
                    }
                } else {
                    ok = 0;
                }
            } else if (SCENE->_27B >= e->_30) {
                ok = 0;
            }
        }
        if (ok != 0) {
            SCENE->_260 = i;
        }
    }

    idx = SCENE->_260;
    if (idx != -1) {
        if (gs->exhibitionMatchInd == 0 && lbl_3_data_1F50[idx] == 1) {
            SCENE->_260 = -1;
            return 0;
        }
        e = &lbl_3_data_2398[idx];
        if (e->once == 1) {
            e->_34[0] = 1;
        }
        e = &lbl_3_data_2398[SCENE->_260];
        if (e->_28 == 1) {
            e->_34[1] = 1;
            e = &lbl_3_data_2398[SCENE->_260];
            if (e->captainDuel == 1 && lbl_3_data_2BD8[bt->charID][pt->charID] == 1) {
                if (g_GameLogic.Team_CaptainRosterLoc[gl->teamBatting] == bt->charID
                    && g_GameLogic.Team_CaptainRosterLoc[gl->teamFielding] == pt->charID) {
                    e->_34[2] = 1;
                }
                lbl_3_common_bss_32724._AE = 1;
                lbl_3_common_bss_32724._AF = g_Pitcher.rosterID;
            }
        }
        SCENE->_27B = lbl_3_data_2398[SCENE->_260]._30;
        return 1;
    }
    return 0;
}
#endif

// .text:0x0002273C size:0xE0 mapped:0x806617D0
s32 fn_3_2273C(void) {
    FielderView* f = g_Fielders;
    CharActor* p;
    s32 i;
    for (i = 0; i < 9; i++) {
        if (f->opponentIdx == 0) {
            p = lbl_8036E548.active[i];
            if (p == NULL) {
                return 1;
            }
            if (p->_068 == 0) {
                return 1;
            }
        }
        f++;
    }
    return 0;
}

// .text:0x0002281C size:0x34 mapped:0x806618B0
s32 fn_3_2281C(s32 i) {
    CharActor* p = lbl_8036E548.active[i];
    if (p == NULL) {
        return 1;
    }
    return p->_068 == 0;
}

// .text:0x00022850 size:0xF4 mapped:0x806618E4
void fn_3_22850(void) {
    s32 i;
    for (i = 0; i < 0x21; i++) {
        lbl_3_data_2398[i]._34[1] = 0;
        lbl_3_data_2398[i]._34[2] = 0;
    }
    SCENE->_27B = 0;
}

// .text:0x00022944 size:0x4 mapped:0x806619D8
void fn_3_22944(void) {
    return;
}

// .text:0x00022948 size:0xD8 mapped:0x806619DC
void fn_3_22948(void) {
    s32 i;
    for (i = 0; i < 0x21; i++) {
        lbl_3_data_2398[i]._34[0] = 0;
        lbl_3_data_2398[i]._34[1] = 0;
        lbl_3_data_2398[i]._34[2] = 0;
    }
    SCENE->_27B = 0;
}

// .text:0x00022A20 size:0x9C mapped:0x80661AB4
s32 fn_3_22A20(void) {
    s16 x;
    s16 y;
    GameScoresTeam* t;
    if (g_Batter.aiControlledInd != 0) {
        t = g_Scores.team;
        x = t[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0];
        y = t[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
        return x >= y;
    }
    t = g_Scores.team;
    x = t[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0];
    y = t[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
    return (u32)__cntlzw(x >= y) >> 5; // !(x >= y)
}

// .text:0x00022ABC size:0x154 mapped:0x80661B50
s32 fn_3_22ABC(void) {
    s32 r = 0;
    s32 n = 0;
    s32 m;
    GameScores* sc = &g_Scores;
    InMemRunnerType* r2;
    InMemRunnerType* r3;
    s32 d;
    if (g_Runners[1].rosterID != -1) {
        n = 1;
    }
    r2 = g_Runners;
    if (r2[2].rosterID != -1) {
        n += 1;
    }
    r3 = g_Runners;
    if (r3[3].rosterID != -1) {
        n += 1;
    }
    d = sc->_A6;
    if (__abs(d) <= 4 && n == 3 && sc->team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] <= sc->team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0]) {
        r = 1;
    }
    m = 0;
    if (r2[2].rosterID != -1) {
        m = 1;
    }
    if (r3[3].rosterID != -1) {
        m += 1;
    }
    d = sc->_A6;
    if (__abs(d) <= m && m > 0 && sc->team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] <= sc->team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0]) {
        r = 1;
    }
    if (r != 0) {
        return g_Batter.aiControlledInd != 0 ? 1 : 2;
    }
    return -1;
}

// .text:0x00022C10 size:0x10 mapped:0x80661CA4
void fn_3_22C10(void) {
    int i;
    for (i = 13; i != 0; i--) {
    }
}

// .text:0x00022C20 size:0x4B4 mapped:0x80661CB4
void fn_3_22C20(void) {
    GameInitVariables* gs = &g_d_GameSettings;
    s32 i;
    lbl_3_common_bss_32A94_s* ch = &lbl_3_common_bss_32A94;
    GameControlsStruct* gl = &g_GameLogic;
    s16 human;
    s16 captain;
    switch (gl->_125) {
    case 0:
        if ((s32)lbl_803C6CF8.idle == 1) {
            fn_3_147DFC();
            lbl_3_common_bss_32724._9A = 0;
            gl->_125 = 1;
        }
        break;
    case 1:
        if (fn_3_6B4C8() != 0) {
            gl->_125 = 2;
        }
        break;
    case 2: {
        ChallengeState* cs;
        fn_3_8C104(-1);
        SceneReset(2);
        cs = &gChallengeState;
        if (ch->_8A != 0) {
            fn_3_FBDAC(lbl_3_data_2368[cs->_441C]);
        } else {
            fn_3_FBDAC(lbl_3_data_2380[cs->_441C]);
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        gl->_125 = 3;
        break;
    }
    case 3:
        if (SCENE->_23C == 9) {
            changeScene(1, 0x5A);
        }
        if (SCENE->_23C < 0x7FFE) {
            SCENE->_23C += 1;
        } else {
            SCENE->_23C = 0x7FFF;
        }
        for (i = 0; i < 13; i++) {
            fn_8001D074(i, 1);
        }
        if (fn_3_6C938(1, 0x1100) != 0 && SCENE->_23C < SCENE->_23E - 0x5B && gs->GameModeSelected != 4) {
            if ((s32)SCENE->_280 == 1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy > 60) {
                SCENE->_23C = SCENE->_23E - 0x5C;
                changeScene(3, 0x5A);
                lbl_3_common_bss_34C58._2A = 1;
                lbl_3_common_bss_34C58._24 = 0x5A;
            }
        } else if (SCENE->_23C == SCENE->_23E - 0x5B) {
            changeScene(3, 0x5A);
            lbl_3_common_bss_34C58._2A = 1;
            lbl_3_common_bss_34C58._24 = 0x5A;
        }
        if (SCENE->_23C == SCENE->_23E) {
            gl->_125 = 4;
        }
        break;
    case 4:
        if (lbl_8037169C._13 != 0) {
            fn_3_24630();
            fn_3_FBD70();
            fn_3_FBD58();
            gl->_125 = 5;
        }
        break;
    case 5:
        gl->_128 = 1;
        gl->framesOfExitingToMenu = 1;
        break;
    }
    human = lbl_3_common_bss_37400.humanPlayer;
    captain = inMemRoster[human][g_GameLogic.Team_CaptainRosterLoc[human]].stats.CharID;
    if (SCENE->_23C == lbl_3_data_7F7C[lbl_800E8558[captain]._2].sceneFrame) {
        fn_3_90220(captain, 7);
    }
}

// .text:0x000230D4 size:0x3E8 mapped:0x80662168
void fn_3_230D4(void) {
    GameInitVariables* gs = &g_d_GameSettings;
    GameControlsStruct* gl = &g_GameLogic;
    s32 i;
    switch (gl->_125) {
    case 0:
        if ((s32)lbl_803C6CF8.idle == 1) {
            changeScene(1, 6);
            fn_3_24630();
            fn_3_FBD70();
            fn_3_FBD58();
            fn_3_5A6D4(0);
        }
        break;
    case 1:
        changeScene(1, 6);
        SceneReset(1);
        fn_3_FBDAC(0x6B);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        gl->_125 = 2;
        break;
    case 2:
        if (SCENE->_23C == 9) {
            changeScene(1, 6);
        }
        if (SCENE->_23C < 0x7FFE) {
            SCENE->_23C += 1;
        } else {
            SCENE->_23C = 0x7FFF;
        }
        for (i = 0; i < 13; i++) {
            fn_8001D074(i, 1);
        }
        if (fn_3_6C938(1, 0x1100) != 0 && SCENE->_23C < SCENE->_23E - 7 && gs->GameModeSelected != 4
            && g_GameLogic.FrameCountOfCurrentAtBat_Copy > 60) {
            SCENE->_23C = SCENE->_23E - 8;
            changeScene(3, 6);
        }
        if (SCENE->_23C == SCENE->_23E) {
            fn_3_24630();
            fn_3_FBD70();
            fn_3_FBD58();
            fn_3_5A6D4(0);
        }
        break;
    }
}

// .text:0x000234BC size:0x3D4 mapped:0x80662550
void fn_3_234BC(void) {
    GameInitVariables* gs = &g_d_GameSettings;
    GameControlsStruct* gl = &g_GameLogic;
    s32 i;
    switch (gl->_125) {
    case 0:
        if ((s32)lbl_803C6CF8.idle == 1) {
            if (gl->playOverInd == 0 && fn_3_21F14() == 0) {
                SCENE->_25C = 0;
                changeScene(1, 6);
                fn_3_FBD58();
                fn_3_5A6D4(0);
            } else {
                fn_3_F1DC();
                fn_3_751B4();
                setDefaultInMemBatter();
                fn_3_8913C();
                fn_3_58870();
                fn_3_1DEB8();
                g_Pitcher.playStartOfGameAnimation = 0;
                g_GameLogic.scoutFlag_VsScreenInd = 1;
                gl->_125 = 1;
            }
        }
        break;
    case 1:
        SceneReset(0);
        if (g_GameLogic.playOverInd == 1) {
            fn_3_FBDAC(0x6A);
        } else {
            fn_3_FBDAC(lbl_3_data_1F74[SCENE->_260]);
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        gl->_125 = 2;
        break;
    case 2:
        fn_3_24708();
        if (SCENE->_23C == 9) {
            changeScene(1, 6);
        }
        if (SCENE->_23C < 0x7FFE) {
            SCENE->_23C += 1;
        } else {
            SCENE->_23C = 0x7FFF;
        }
        for (i = 0; i < 13; i++) {
            fn_8001D074(i, 1);
        }
        if (fn_3_6C938(1, 0x1100) != 0 && SCENE->_23C < SCENE->_23E - 7 && gs->GameModeSelected != 4
            && g_GameLogic.FrameCountOfCurrentAtBat_Copy > 60) {
            SCENE->_23C = SCENE->_23E - 8;
            changeScene(3, 6);
        }
        if (SCENE->_23C == SCENE->_23E) {
            gl->_125 = 3;
        }
        break;
    case 3:
        fn_3_24630();
        fn_3_FBD70();
        fn_3_FBD58();
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x00023890 size:0x45C mapped:0x80662924
void fn_3_23890(void) {
    GameControlsStruct* gl = &g_GameLogic;
    SceneTask* task = lbl_803CC1B8;
    s32 i;
    GameInitVariables* gs = &g_d_GameSettings;
    FadeTask* wait;
    switch (gl->_125) {
    case 0:
        if ((s32)lbl_803C6CF8.idle == 1) {
            g_pCamera->_AAA = 1;
            g_pCamera->_AAE = 2;
            fn_800B0A5C_insertQueue(fn_3_21DE4, 6);
            gl->_125 = 1;
        }
        break;
    case 1:
        SceneReset(4);
        fn_3_FBDAC(0x4C);
        gl->_125 = 2;
        break;
    case 2:
        changeScene(1, 6);
        SCENE->busy = 1;
        wait = fn_800B0A5C_insertQueue(fn_3_21AA8, 4);
        task->_10 = 0;
        wait->state = 0;
        wait->frame = 0;
        gl->_125 = 3;
        break;
    case 3:
        fn_3_24708();
        if (SCENE->_23C < 0x7FFE) {
            SCENE->_23C += 1;
        } else {
            SCENE->_23C = 0x7FFF;
        }
        if (fn_3_6C938(1, 0x1100) != 0 && SCENE->_23C < SCENE->_23E - 0x1F && gs->GameModeSelected != 4
            && g_GameLogic.FrameCountOfCurrentAtBat_Copy > 60 && lbl_3_common_bss_32724._B1 == 0) {
            SCENE->_27C = 1;
            SCENE->_23C = SCENE->_23E - 0x1F;
        }
        if (SCENE->_23C == SCENE->_23E - 0x1F) {
            lbl_3_common_bss_32724._B1 = 1;
        }
        if (SCENE->_23C == SCENE->_23E) {
            gl->_125 = 5;
        }
        for (i = 0; i < 13; i++) {
            if ((u32)i <= 1 || i == 9) {
                fn_8001D074(i, 1);
            } else {
                fn_8001D074(i, 0);
            }
        }
        break;
    case 4:
        break;
    case 5:
        SCENE->busy = 0;
        fn_3_24630();
        fn_3_FBD70();
        fn_3_FBD58();
        gl->_125 = 6;
        break;
    case 6:
        for (i = 0; i < 13; i++) {
            fn_8001D074(i, 1);
        }
        fn_3_8C07C();
        if ((s8)SCENE->_27C != 0) {
            fn_3_5A6D4(g_GameLogic.gameStatus_prev);
            g_Stats._39 = 2;
        } else {
            fn_3_5A6D4(g_GameLogic.gameStatus_prev);
            g_Stats._39 = 2;
        }
        break;
    }
}

// .text:0x00023CEC size:0x40C mapped:0x80662D80
void fn_3_23CEC(void) {
    GameInitVariables* gs = &g_d_GameSettings;
    GameControlsStruct* gl = &g_GameLogic;
    s32 i;
    switch (gl->_125) {
    case 0:
        if ((s32)lbl_803C6CF8.idle == 1) {
            changeScene(1, 6);
            gl->_125 = 1;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        }
        break;
    case 1:
        SceneReset(3);
        fn_3_FBDAC(lbl_3_data_1FF8[g_Runners[0].charID]);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        gl->_125 = 2;
        break;
    case 2:
        fn_3_24708();
        if (SCENE->_23C < 0x7FFE) {
            SCENE->_23C += 1;
        } else {
            SCENE->_23C = 0x7FFF;
        }
        if (fn_3_6C938(1, 0x1100) != 0 && SCENE->_23C < SCENE->_23E - 7 && gs->GameModeSelected != 4) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 60) {
                SCENE->_27C = 1;
                SCENE->_23C = SCENE->_23E - 8;
                changeScene(3, 6);
            }
        } else if (SCENE->_23C == SCENE->_23E - 7) {
            changeScene(3, 6);
        }
        if (SCENE->_23C == SCENE->_23E) {
            gl->_125 = 4;
        }
        for (i = 0; i < 13; i++) {
            if ((u32)i <= 1 || i == 9) {
                fn_8001D074(i, 1);
            } else {
                fn_8001D074(i, 0);
            }
        }
        break;
    case 4:
        fn_3_24630();
        fn_3_FBD70();
        fn_3_FBD58();
        fn_3_7C1FC(1);
        for (i = 0; i < 13; i++) {
            fn_8001D074(i, 1);
        }
        break;
    }
    BatterVoice();
}

// .text:0x000240F8 size:0x4A0 mapped:0x8066318C
void fn_3_240F8(void) {
    GameControlsStruct* gl = &g_GameLogic;
    GameInitVariables* gs = &g_d_GameSettings;
    s32 i;
    CharActor* a;
    switch (gl->_125) {
    case 0:
        if ((s32)lbl_803C6CF8.idle == 1) {
            g_pCamera->_AAA = 1;
            g_pCamera->_AAE = 2;
            fn_800B0A5C_insertQueue(fn_3_21DE4, 6);
            gl->_125 = 1;
        }
        break;
    case 1:
        changeScene(1, 6);
        SceneReset(5);
        if (g_Runners[0].baseStandingOn == 1) {
            fn_3_FBDAC(lbl_3_data_20D4[g_Runners[0].charID]);
        } else if (g_Runners[0].baseStandingOn == 2) {
            fn_3_FBDAC(lbl_3_data_21B0[g_Runners[0].charID]);
        } else if (g_Runners[0].baseStandingOn == 3) {
            fn_3_FBDAC(lbl_3_data_228C[g_Runners[0].charID]);
        } else {
            fn_3_FBDAC(lbl_3_data_20D4[g_Runners[0].charID]);
        }
        gl->_125 = 2;
        break;
    case 2:
        gl->FrameCountOfCurrentAtBat_Copy = 0;
        gl->_125 = 3;
    case 3:
        fn_3_24708();
        if (SCENE->_23C < 0x7FFE) {
            SCENE->_23C += 1;
        } else {
            SCENE->_23C = 0x7FFF;
        }
        if (fn_3_6C938(1, 0x1100) != 0 && SCENE->_23C < SCENE->_23E - 8 && gs->GameModeSelected != 4) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 60) {
                SCENE->_27C = 1;
                SCENE->_23C = SCENE->_23E - 8;
                changeScene(3, 6);
            }
        } else if (SCENE->_23C == SCENE->_23E - 7) {
            changeScene(3, 6);
        }
        if (SCENE->_23C == SCENE->_23E) {
            gl->_125 = 5;
        }
        for (i = 0; i < 13; i++) {
            if ((u32)i <= 1 || i == 9) {
                fn_8001D074(i, 1);
            } else {
                fn_8001D074(i, 0);
            }
        }
        break;
    case 5:
        fn_3_24630();
        fn_3_FBD70();
        fn_3_FBD58();
        fn_3_7C1FC(1);
        for (i = 0; i < 13; i++) {
            fn_8001D074(i, 1);
        }
        break;
    }
    a = lbl_8036E548.active[9];
    if (a->anim[0] == 0x3A && a->_06A[0] == lbl_3_data_7F7C[lbl_800E8558[g_Batter.charID]._2].anim2) {
        fn_3_90220(g_Batter.charID, 0);
    }
}

// .text:0x00024598 size:0x98 mapped:0x8066362C
void fn_3_24598(void) {
    if (SCENE->_23C < 0x7FFE) {
        SCENE->_23C += 1;
    } else {
        SCENE->_23C = 0x7FFF;
    }
    if (SCENE->_23C == SCENE->_23E - 7) {
        changeScene(3, 6);
    }
    if (SCENE->_23C == SCENE->_23E) {
        g_GameLogic._125 += 1;
    }
}

// .text:0x00024630 size:0xD8 mapped:0x806636C4
void fn_3_24630(void) {
    s32 i;
    fn_80052798(1);
    for (i = 0; i < 13; i++) {
        SCENE->animSet[i] = 0;
    }
    SCENE->_25C = 0;
}

// .text:0x00024708 size:0x2E0 mapped:0x8066379C
// Walks each scripted actor toward its scene target; marks it arrived when close enough
// (or, in mode 3, when its animation has finished).
void fn_3_24708(void) {
    Mtx m;
    Vec v;
    CharActor* a;
    SceneActorState* st;
    InMemRunnerType* r;
    s32 i;
    f32 dist;
    f32 diff;

    i = 0;

    do {
        a = lbl_8036E548.active[i];
        if (a != NULL && (st = &SCENE->actors[i])->moving == 1) {
            if ((s32)SCENE->_27F != 3 || !(st->_1C > a->_068)) {
                if (i <= 8) {
                    dist = PSVECDistance((Vec*)&g_Fielders[i].pos, (Vec*)&st->pos);
                } else if (i <= 12) {
                    r = &g_Runners[i - 9];
                    SCENE->actors[i].targetRotY = atan2(-(st->pos.x - r->position.x), -(st->pos.z - r->position.z));
                    PSMTXRotRad(m, 'Y', SCENE->actors[i].rotY);
                    v.x = lbl_3_rodata_A54;
                    v.y = lbl_3_rodata_A54;
                    v.z = SCENE->actors[i].speed;
                    PSMTXMultVec(m, &v, &v);
                    r->position.x = r->position.x - v.x;
                    r->position.z = r->position.z - v.z;
                    st = &SCENE->actors[i];
                    diff = fn_3_9FEA8(st->rotY - st->targetRotY);
                    if (!((diff < lbl_3_rodata_A58 && diff > lbl_3_rodata_A54) || (diff > lbl_3_rodata_A60 && diff < lbl_3_rodata_A54))) {
                        if (diff < lbl_3_rodata_A54) {
                            SCENE->actors[i].rotY += lbl_3_rodata_A68;
                        } else {
                            SCENE->actors[i].rotY -= lbl_3_rodata_A68;
                        }
                    }
                    r->runningAngle = SCENE->actors[i].rotY;
                    dist = PSVECDistance((Vec*)&r->position, (Vec*)&SCENE->actors[i].pos);
                }
            }
            if ((s32)SCENE->_27F == 3) {
                if (a->_068 == 0) {
                    SCENE->actors[i].arrived = 1;
                    SCENE->actors[i].moving = 0;
                }
            } else if (dist < lbl_3_rodata_A6C) {
                SCENE->actors[i].arrived = 1;
                SCENE->actors[i].moving = 0;
            }
        }
        i++;
    } while (i < 13);
}

