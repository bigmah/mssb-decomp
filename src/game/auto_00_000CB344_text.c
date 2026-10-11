#include "game/auto_00_000CB344_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern void fn_3_C1770(s32 who);

typedef struct CB344State {
    u8 pad0[0x467];
    s8 val467; // 0x467
} CB344State;

extern CB344State lbl_3_common_bss_35154;

// .text:0x000CB344 size:0x68 mapped:0x8070A3D8
void fn_3_CB344(s32 who, u8 val) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES ||
        (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BOBOMB_DERBY && g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BARREL_BATTER)) {
        fn_3_C1770(who);
    }
    lbl_3_common_bss_35154.val467 = val;
}
