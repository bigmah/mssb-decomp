#include "game/auto_00_0006B4C8_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0001D86C_text.h"
#include "game/auto_00_000249E8_text.h"
#include "main/file_800639BC.h"
#include "main/file_8000F150.h"
#include "main/file_80063028.h"
#include "main/file_800BD8C4.h"

// Views declared in the unit headers (kept out of them: other units have their own views).
extern RunningLogicStruct g_RunningLogic;
extern ActorMgrView lbl_8036E548;
extern Unk32724 lbl_3_common_bss_32724;

// main.dol (main/file_80011640.h, which declares a conflicting view of lbl_8036E548)
void fn_8001196C(void);
void fn_80011A60(void);
void fn_80011BE4(s32 index);
s32 fn_8001594C(s32 team);
// game.rel calls pass kind unextended (lwz) or sign-extended (s8): it was built against an s32 kind
s32 fn_80016344(s32 kind, s32 index, s32 arg2, s32 roster);
s32 fn_8001500C(s32 team, s32 roster, s32 index);

typedef struct Unk80353A90 {
    /*0x000*/ u8 _000[0x103];
    /*0x103*/ s8 _103; // character id
    /*0x104*/ u8 _104[0x108 - 0x104];
} Unk80353A90; // size: 0x108
extern Unk80353A90 lbl_80353A90;


extern u8 lbl_3_data_FAA8[0x1C]; // practice roster id -> character id

// .text:0x0006B4C8 size:0x110 mapped:0x806AA55C
s32 fn_3_6B4C8(void) {
    s32 i;

    if (lbl_3_common_bss_32724._9A == 0) {
        fn_80011A60();
        lbl_8036E548._2D77 = 0;
        lbl_3_common_bss_32724._9A = 1;
    }
    if (fn_80016344(lbl_8034E9A0.captain[g_d_GameSettings.humanTeamNumber], 0xC, 1,
                    ((u8*)lbl_8034E9A0.captainSlot)[g_d_GameSettings.humanTeamNumber])) {
        for (i = 0; i < 9; i++) {
            if (lbl_8036E548.actors[i]->kind == lbl_8034E9A0.captain[g_d_GameSettings.humanTeamNumber]) {
                lbl_8036E548.actors[i] = &lbl_8036E548.storage[12];
                lbl_8036E548.actors[12] = NULL;
                break;
            }
        }
        return 1;
    }
    return 0;
}

// .text:0x0006B5D8 size:0x9C mapped:0x806AA66C
s32 fn_3_6B5D8(void) {
    switch (lbl_3_common_bss_32724._9A) {
    case 0:
        lbl_8036E548._2D77 = 0;
        lbl_3_common_bss_34C58._2C = 0;
        lbl_3_common_bss_32724._9A++;
        break;
    case 1:
        if (fn_80016344(lbl_80353A90._103, 9, 0, 0)) {
            return 1;
        }
        break;
    }
    return 0;
}

// .text:0x0006B674 size:0x1FC mapped:0x806AA708
void fn_3_6B674(void) {
    GameActorView* actor;
    s32 i;
    s32 visible;
    u8 status;
    GameActor* model;

    if (!g_d_GameSettings.minigamesEnabled || g_Minigame.GameMode_MiniGame == 0) {
        if (g_GameLogic.sceneID == 1) {
            fn_800BDE8C(2);
        } else {
            fn_800BDE8C(1);
        }
    } else {
        switch (g_Minigame.GameMode_MiniGame) {
        case 1:
        case 3:
            fn_800BDE8C(2);
            break;
        case 2:
        case 4:
        case 5:
        case 6:
            fn_800BDE8C(1);
            break;
        }
    }

    for (i = 0; i < 13; i++) {
        actor = lbl_8036E548.actors[i];
        if (actor != NULL && *fn_800111D8((struct CharActor*)actor) != NULL) {
            visible = 1;
            if (g_d_GameSettings.minigamesEnabled) {
                status = g_GameLogic.gameStatus;
                if (status == 0x1C || (u8)(status - 0x1D) <= 1 || status == 0x1F) {
                    if (status == 0x1F) {
                        visible = 0;
                    }
                }
                if (g_d_GameSettings.GameModeSelected == 6 && g_GameLogic.sceneID == 1 &&
                    (s8)g_Minigame.minigameFielderIndex[i] >= 1) { // TODO type: indexed up to 12
                    visible = 0;
                }
            } else if (g_GameLogic.secondaryGameMode != 0xE && g_Stats.replayInd == 0 && i != 0 && i != 9 &&
                       g_GameLogic.sceneID == 1) {
                visible = 0;
            }
            if (actor->_25D == 2) {
                visible = 0;
            }
            model = *fn_800111D8((struct CharActor*)actor);
            if (visible) {
                model->flags |= 4;
            } else {
                model->flags &= 0xFB;
            }
        }
    }
}

// .text:0x0006B870 size:0x1F4 mapped:0x806AA904
void fn_3_6B870(void) {
    s32 i;

    if (g_Strikes.outs >= 3) {
        for (i = 0; i < 4; i++) {
            if (g_d_GameSettings.GameModeSelected != 2 || g_GameLogic.secondaryGameMode != 0xF || i != 0) {
                fn_80011BE4(i + 9);
            }
        }
    } else if (g_GameLogic.gameStatus == 10) {
        for (i = 1; i < 4; i++) {
            if (g_RunningLogic._06[i] == -1) {
                fn_80011BE4(i + 9);
            }
        }
    } else {
        for (i = 1; i < 4; i++) {
            if (g_RunningLogic._06[i] == -1) {
                fn_80011BE4(i + 9);
            }
        }
        if (g_d_GameSettings.GameModeSelected != 2 || g_GameLogic.secondaryGameMode != 0xF) {
            fn_80011BE4(9);
        }
    }
    for (i = 9; i < 13; i++) {
        if (g_d_GameSettings.GameModeSelected != 2 || g_GameLogic.secondaryGameMode != 0xF || i != 9) {
            lbl_8036E548.actors[i] = NULL;
        }
    }
}

// .text:0x0006BA64 size:0x308 mapped:0x806AAAF8
s32 fn_3_6BA64(void) {
    s32 k;
    s32 next;
    u8 mode;

    if (lbl_3_common_bss_32724._9A == 0) {
        lbl_8036E548._2D7A = 0;
        lbl_8036E548._2D77 = 0;
        lbl_3_common_bss_32724._9A = 1;
    }
    do {
        k = 3 - lbl_8036E548._2D7A;
        if (g_Runners[k].rosterID >= 0) {
            if (fn_8001500C(g_GameLogic.teamBatting, g_Runners[k].rosterID, k + 9) == 0) {
                return 0;
            }
        }
    } while (++lbl_8036E548._2D7A < 4);

    mode = g_d_GameSettings.GameModeSelected;
    if (mode == 0 || mode == 4 || mode == 5 || (mode == 2 && g_GameLogic.secondaryGameMode == 0x10)) {
        lbl_3_common_bss_32724._9E = g_Runners[0].charID;
    } else if (mode == 2 && g_GameLogic.secondaryGameMode == 0xF) {
        lbl_3_common_bss_32724._9E = lbl_3_data_FAA8[g_Practice.rosterID];
    }
    if (mode == 0 || mode == 4 || mode == 5 || (mode == 2 && g_GameLogic.secondaryGameMode == 0x10)) {
        next = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] + 1;
        if (next > 9) {
            next = 1;
        }
        lbl_3_common_bss_32724._A0 =
            inMemRoster[g_GameLogic.teamBatting]
                       [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0]]
                           .stats.CharID;
    } else if (mode == 2 && g_GameLogic.secondaryGameMode == 0xF) {
        next = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam];
        lbl_3_common_bss_32724._A0 =
            inMemRoster[g_GameLogic.teamBatting]
                       [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0]]
                           .stats.CharID;
    }
    if (mode == 0 || mode == 5 || mode == 4) {
        next = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] + 1;
        if (next > 9) {
            next = 1;
        }
        lbl_3_common_bss_32724._A2 =
            inMemRoster[g_GameLogic.teamBatting]
                       [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0]]
                           .stats.CharID;
    }
    return 1;
}

// .text:0x0006BD6C size:0x138 mapped:0x806AAE00
s32 fn_3_6BD6C(void) {
    s32 i;
    s32 t;

    if (lbl_3_common_bss_32724._9B == 0) {
        fn_8001196C();
        lbl_8036E548._2D77 = 0;
        lbl_3_common_bss_32724._9B = 1;
        lbl_8036E548._2D7B = 0;
        lbl_8036E548._2D7C = 0;
        if (g_GameLogic.gameStatus == 9) {
            lbl_8036E548._2D7C = 1;
            for (t = 0; t < 2; t++) {
                for (i = 0; i < 9; i++) {
                    if (lbl_800E8558[inMemRoster[t][i].stats.CharID]._2 == 0x19) {
                        inMemRoster[t][i].stats.FieldingArm = 0;
                        inMemRoster[t][i].stats.BattingStance = 1;
                    }
                }
            }
        }
    }
    return !!fn_8001594C(g_GameLogic.teamFielding);
}
