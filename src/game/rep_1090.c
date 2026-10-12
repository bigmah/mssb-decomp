#include "game/rep_1090.h"
#define REP_HEADER_FN repHeader_1090
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_000249E8_text.h" // SceneWork
#include "main/file_80011640.h"         // CharMgr lbl_8036E548

extern u8 lbl_3_data_6EF0[];
extern SceneWork* lbl_3_common_bss_1323C;
extern void fn_3_6A25C(void);
extern void fn_3_6A250(void);
extern void fn_3_6A254(void);
extern void fn_3_6A2A4(u8);
extern void fn_3_E07DC(void);
extern int fn_8004ACC4(int);
extern int fn_8004ACDC(int);

#define CLEAR4()                                      \
    {                                                 \
        int k;                                        \
        for (k = 0; k < 4; k++) {                     \
            CharActor* q = lbl_8036E548.active[k + 9]; \
            if (q != NULL) {                          \
                q->mode[0] = 0;                       \
            }                                         \
        }                                             \
    }

// .text:0x0006C4D0 size:0x384 mapped:0x806AB564
void fn_3_6C4D0(void) {
    CharActor* p;
    InMemRunnerType* r;
    u8* d;
    int i;
    if (lbl_8036E548.state != 0) {
        CLEAR4();
        fn_3_6A25C();
        fn_3_6A250();
        return;
    }
    if (g_GameLogic.gameStatus != 0 && g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 2 &&
        g_GameLogic.gameStatus != 8 && g_GameLogic.gameStatus != 0x16) {
        CLEAR4();
        fn_3_6A25C();
        fn_3_6A250();
        if (g_GameLogic.gameStatus == 0xE) {
            fn_3_E07DC();
        }
        return;
    }
    if (g_GameLogic.secondaryGameMode == 0xB) {
        CLEAR4();
        fn_3_6A25C();
        fn_3_6A250();
        return;
    }
    for (i = 0; i < 4; i++) {
        p = lbl_8036E548.active[i + 9];
        r = &g_Runners[i];
        d = &lbl_3_data_6EF0[i];
        if (p != NULL) {
            p->_275 = r->someCollisionCheck;
            if (i == 0) {
                p->_278 = 1;
            }
            if (r->runningToDugoutStage == 3) {
                p->mode[0] = 0;
            } else {
                u8 t;
                if (i == 0 && g_Pitcher.strikeOutOrWalk == 3) {
                    t = *(u8*)&p->kind; // read unsigned: a plain (u8) cast changes the register allocation
                    if ((s8)t == 0x26) {
                        if (fn_8004ACDC(1) != 0) {
                            fn_3_6A254();
                        }
                        goto L50;
                    }
                    if ((u8)(t - 0x30) <= 2U || (s8)t == 0x33) {
                        p->mode[0] = 2;
                        if (fn_8004ACC4(1) != 0) {
                            fn_3_6A2A4(p->kind);
                        }
                    } else {
                        goto L50;
                    }
                } else {
                L50:
                    if (r->runnerOnFieldOrOutOrScored == 0 || r->rosterID < 0) {
                        p->mode[0] = 0;
                    } else if (r->runningToDugoutStage == 3) {
                        p->mode[0] = 0;
                    } else {
                        p->mode[0] = 1;
                        p->pos.x = r->position.x;
                        p->pos.y = r->position.y;
                        p->pos.z = r->position.z;
                        p->rot.x = 0.0f;
                        p->rot.y = r->runningAngle;
                        p->rot.z = 0.0f;
                    }
                    if (g_Stats.replayInd != 0) {
                        p->mode[0] = lbl_3_common_bss_1323C->animSet[i];
                    } else if (*d != 0 && g_GameLogic.sceneID != 3 && g_GameLogic.secondaryGameMode != 0xE &&
                               (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 0 ||
                                g_GameLogic.gameStatus == 7 || g_GameLogic.sceneID == 1)) {
                        p->mode[0] = 0;
                    }
                }
            }
        }
    }
}

