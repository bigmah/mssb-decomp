#include "game/rep_23E8.h"
#define REP_HEADER_FN repHeader_23E8
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1E08.h"
#include "static/UnknownHomes_Static.h"

#include "main/scene_task.h"

extern Rep23E8Bss35154 lbl_3_common_bss_35154;
extern SceneTask* lbl_803CC1B8;

// .text:0x000CB7E8 size:0xC0 mapped:0x8070A87C
void fn_3_CB7E8(f32 x, f32 y, f32 z) {
    Rep23E8Bss35154* b = &lbl_3_common_bss_35154;
    b->starPos.x = x;
    b->starPos.y = y;
    b->starPos.z = z;
    b->starRot.z = 0.0f;
    b->starRot.y = 0.0f;
    b->starRot.x = 0.0f;
    b->starTimer = 0x50;
    b->starActive = 1;
    b->flags |= 4;
    fn_800B0A5C_insertQueue(fn_3_CB738, (u16)(lbl_803CC1B8->priority + 1));
    playSoundEffect(0x19D);
    if (g_GameLogic.TeamStars[g_GameLogic.teamBatting] < 5) {
        g_GameLogic.TeamStars[g_GameLogic.teamBatting]++;
    }
    g_GameLogic.stadiumStarObtained = 1;
}

// .text:0x000CB7D4 size:0x14 mapped:0x8070A868
void fn_3_CB7D4(void) {
    lbl_3_common_bss_35154.starTimer = 0;
}

// .text:0x000CB738 size:0x9C mapped:0x8070A7CC
void fn_3_CB738(void) {
    Rep23E8Bss35154* b = &lbl_3_common_bss_35154;
    if (g_d_GameSettings._55 != 0 || b->disabled != 0 || b->starTimer-- == 0) {
        b->starActive = 0;
        REMOVE_QUEUE_NOARG();
    } else {
        fn_3_BD8D8();
        b->starPos.y += -0.03125f;
        b->starRot.y += 0.15707964f;
    }
}

