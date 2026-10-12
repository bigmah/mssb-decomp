#include "game/rep_1038.h"
#define REP_HEADER_FN repHeader_1038
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_000249E8_text.h" // SceneWork, Unk32724
#include "main/file_80011640.h" // CharMgr

extern void fn_3_690FC(void);
extern void fn_3_6AEE0(void);
extern void fn_3_6C454(void);
extern void fn_3_6C410(void);
extern void fn_3_697CC(void);
extern void fn_3_685F0(void);
extern void fn_3_6B144(void);
extern void fn_3_6C4D0(void);
extern void fn_3_6C428(void);
extern void fn_3_6B674(void);
extern void fn_3_6AB58(void);
extern void fn_3_15A9F4(void);
extern void fn_3_973EC(void);
extern SceneWork* lbl_3_common_bss_1323C;
extern InMemFielderType g_Fielders[9];

extern f32 lbl_3_data_18DD4[];

extern Unk32724 lbl_3_common_bss_32724;

extern void fn_3_B93C8(s32);

extern GameScores g_Scores;

extern void fn_3_6916C(void);
extern void fn_3_674E0(void);
extern void fn_3_97800(void);

// .text:0x0006C1D8 size:0x238 mapped:0x806AB26C
void fn_3_6C1D8(void) {
    u8 mode = g_GameLogic.gameStatus;
    if (mode != 4) {
        u8 gm = g_d_GameSettings.GameModeSelected;
        if (gm == 2 && g_GameLogic.secondaryGameMode == 0xA && g_Practice.practiceType_1 == 6) {
            fn_3_6C000();
        } else if (mode != 5 && lbl_8036E548._307A != 0) {
            if (lbl_3_common_bss_1323C->_25C != 0) {
                fn_3_6BEA4();
            } else if ((((u8)(mode - 0xB) <= 1) || g_GameLogic.secondaryGameMode == 0xA || g_GameLogic.secondaryGameMode == 0x12
                        || (gm == 2 && g_Practice.tutorialState == 0))
                       && (gm != 6 || mode != 0xB)) {
                fn_3_690FC();
                fn_3_6AEE0();
                fn_3_6C454();
                fn_3_6C410();
                g_UnkSound_32718._07 = 0;
            } else {
                fn_3_697CC();
                fn_3_685F0();
                fn_3_6B144();
                fn_3_6C4D0();
                fn_3_6C428();
                fn_3_6B674();
                fn_3_6AB58();
            }
        }
        if (g_d_GameSettings.GameModeSelected == 2) {
            fn_3_15A9F4();
        } else {
            fn_3_973EC();
        }
    }
}

// .text:0x0006C150 size:0x88 mapped:0x806AB1E4
void fn_3_6C150(void) {
    lbl_3_common_bss_32724._9E = -1;
    lbl_3_common_bss_32724._A0 = -1;
    lbl_3_common_bss_32724._A2 = -1;
    fn_3_6916C();
    fn_3_674E0();
    fn_3_97800();
    if (g_d_GameSettings.minigamesEnabled != 0) {
        lbl_8036E548._307E = 0;
        return;
    }
    if (g_d_GameSettings.GameModeSelected != 2) {
        lbl_8036E548._307A = 1;
        lbl_8036E548._307E = 1;
    }
}

// .text:0x0006C13C size:0x14 mapped:0x806AB1D0
void fn_3_6C13C(void) {
    g_Scores._C3[0] = 0;
}

// .text:0x0006C108 size:0x34 mapped:0x806AB19C
void fn_3_6C108(void) {
    fn_3_B93C8(1);
    lbl_3_common_bss_32724._AE = 0;
}

// .text:0x0006C0E0 size:0x28 mapped:0x806AB174
void fn_3_6C0E0(void) {
    lbl_3_common_bss_32724._90 = -1;
    lbl_3_common_bss_32724._92 = 0;
    lbl_3_common_bss_32724._A9 = 0;
    lbl_3_common_bss_32724._D3 = 0;
    lbl_3_common_bss_32724._B5 = 0;
}

// .text:0x0006C000 size:0xE0 mapped:0x806AB094
void fn_3_6C000(void) {
    int i;
    CharActor* p;
    CharActor* q;
    lbl_8036E548._2D68 = -1;
    for (i = 0; i < 13; i++) {
        p = lbl_8036E548.active[i];
        if (p != NULL) {
            p->mode[0] = 0;
        }
    }
    if (g_Practice.practiceState != 6 && g_Practice.practiceState > 1 && (q = lbl_8036E548.active[9]) != NULL
        && g_Minigame._1A13[0] == 0 && g_Minigame._19E8[0]._2 >= 0 && g_Minigame._19E8[0]._7 != 0
        && g_Minigame._19DA[0] >= 0) {
        f32* d = lbl_3_data_18DD4;
        q->mode[0] = 1;
        q->pos.x = d[0];
        q->pos.y = -d[1];
        q->pos.z = d[2];
        q->rot.x = 0.0f;
        q->rot.y = 0.0f;
        q->rot.z = 0.0f;
    }
}

// .text:0x0006BEA4 size:0x15C mapped:0x806AAF38
void fn_3_6BEA4(void) {
    int i;
    fn_3_690FC();
    fn_3_6AEE0();
    fn_3_6C454();
    g_UnkSound_32718._07 = 0;
    for (i = 0; i < 13; i++) {
        SceneWork* o = lbl_3_common_bss_1323C;
        CharActor* p;
        if (o->actorSetup[i] >= 0) {
            p = lbl_8036E548.active[i];
            if (p != NULL) {
                p->mode[0] = o->animSet[i];
                if (i <= 8) {
                    InMemFielderType* f = &g_Fielders[i];
                    lbl_3_common_bss_1323C->posSet[i] = 0;
                    if (f->rosterID != -1) {
                        p->pos.x = f->pos.x;
                        p->pos.y = f->pos.y;
                        p->pos.z = f->pos.z;
                        p->rot.y = f->facing;
                    }
                } else if (i <= 12) {
                    InMemRunnerType* r = &g_Runners[i - 9];
                    lbl_3_common_bss_1323C->posSet[i] = 0;
                    if (r->rosterID != -1) {
                        p->pos.x = r->position.x;
                        p->pos.y = r->position.y;
                        p->pos.z = r->position.z;
                        p->rot.y = r->runningAngle;
                    }
                }
                p->rot.x = 0.0f;
                p->rot.z = 0.0f;
            }
        }
    }
}

