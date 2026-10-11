#ifndef __AUTO_00_001293D0_TEXT_GAME_H__
#define __AUTO_00_001293D0_TEXT_GAME_H__

#include "mssbTypes.h"
#include "main/file_8000F150.h" // LayoutSlot
#include "game/auto_00_00097144_text.h" // HudTask, lbl_3_common_bss_32724, lbl_3_common_bss_34C90

// HudTask: see game/auto_00_00097144_text.h

// Barrel Batter CPU: one candidate barrel to aim at (sorted by fn_3_12E084).
typedef struct BbTarget {
    /*0x0*/ s8 barrel; // index into g_Minigame.barrels (3 per row)
    /*0x1*/ s8 chain;  // barrels destroyed by hitting it
    /*0x2*/ s16 score;
} BbTarget; // size: 0x4

// Barrel Batter CPU: copy of one barrel's state/colour (g_Minigame.barrels).
typedef struct BbCell {
    /*0x0*/ u8 state; // 2: standing
    /*0x1*/ u8 colour;
} BbCell;

void fn_3_12DB54(void);
void fn_3_12E808(void);
u32 fn_3_12DD88(void);
void fn_3_1293D0(void);
void fn_3_12C514(void);
void fn_3_12C5CC(void);
void fn_3_129F48(void);
void fn_3_12C684(void);
void fn_3_129458(void);
void fn_3_12E83C(void);
void fn_3_12C74C(void);
void fn_3_12C868(void);
void fn_3_12C984(void);
void fn_3_12C3F0(void);
void fn_3_12BFE8(void);
void fn_3_12C1AC(void);
void fn_3_129C88(void);
void fn_3_129FF8(void);
void fn_3_12BB64(void);
s32 fn_3_12E084(void* a, void* b);
void fn_3_12A2B8(void);
u8 fn_3_12E384(BbCell* grid, s8 idx, u8 colour);
void fn_3_12E17C(s8* chain, s16* score, u8 lookahead);
void fn_3_12DDCC(void);
void fn_3_12DB80(void);
void fn_3_12A3F0(void);
void fn_3_12A6C4(void);
void fn_3_12955C(void);
void fn_3_129A18(void);
void fn_3_12A910(void);
void fn_3_12B7A0(void);
void fn_3_12CA90(void);
void fn_3_12D1F4(void);

#endif
