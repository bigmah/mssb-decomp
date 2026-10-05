#include "game/rep_1330.h"
#include "header_rep_data.h"
#include "Dolphin/stl.h"

extern u8 g_ReplayCopies[];
extern u8 g_GameLogic[];
extern u8 g_Strikes[];
extern u8 g_Scores[];
extern u8 g_Ball[];
extern u8 g_Pitcher[];
extern u8 g_Batter[];
extern u8 g_AiLogic[];
extern u8 g_FieldingLogic[];
extern u8 g_RunningLogic[];
extern u8 g_Fielders[];
extern u8 g_Runners[];
extern u8 lbl_803537E4[];
extern u8 lbl_803535C8[];
extern u8 lbl_3_common_bss_32234[];
extern u8 lbl_3_common_bss_32230[];
extern u8 lbl_3_common_bss_32220[];
extern u8 g_UnkThrowing_31ACC[];
extern u8 g_UnkAnimation_31EAC[];
extern u8 lbl_3_common_bss_321A0[];

// .text:0x0007C4E4 size:0x2C8 mapped:0x806BB578
void fn_3_7C4E4(void) {
    return;
}


// .text:0x0007C7AC size:0x22C
void fn_3_7C7AC(void) {
    memcpy(g_ReplayCopies, g_GameLogic, 0x158);
    memcpy(g_ReplayCopies + 0x158, g_Strikes, 0x24);
    memcpy(g_ReplayCopies + 0x17c, g_Scores, 0xc8);
    memcpy(g_ReplayCopies + 0x244, g_Ball, 0x1bf8);
    memcpy(g_ReplayCopies + 0x1e3c, g_Pitcher, 0x178);
    memcpy(g_ReplayCopies + 0x1fb4, g_Batter, 0xb0);
    memcpy(g_ReplayCopies + 0x2064, g_AiLogic, 0xbc);
    memcpy(g_ReplayCopies + 0x2120, g_FieldingLogic, 0x150);
    memcpy(g_ReplayCopies + 0x2270, g_RunningLogic, 0x20);
    memcpy(g_ReplayCopies + 0x2290, g_Fielders, 0x15a8);
    memcpy(g_ReplayCopies + 0x3838, g_Runners, 0x550);
    memcpy(g_ReplayCopies + 0x4128, lbl_803537E4, 0x2ac);
    memcpy(g_ReplayCopies + 0x43d4, lbl_803535C8, 0x21c);
    memcpy(g_ReplayCopies + 0x3d88, lbl_3_common_bss_32234, 0x6);
    memcpy(g_ReplayCopies + 0x3d8e, lbl_3_common_bss_32230, 0x4);
    memcpy(g_ReplayCopies + 0x3d92, lbl_3_common_bss_32220, 0xe);
    memcpy(g_ReplayCopies + 0x3da0, g_UnkThrowing_31ACC, 0x14);
    memcpy(g_ReplayCopies + 0x3db4, g_UnkAnimation_31EAC, 0x2f4);
    memcpy(g_ReplayCopies + 0x40a8, lbl_3_common_bss_321A0, 0x80);
}
