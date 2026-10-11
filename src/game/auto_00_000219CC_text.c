#include "game/auto_00_000219CC_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_720.h"

// Character actor (entries of lbl_8036E548, only the fields used here).
typedef struct GameActorView {
    /*0x000*/ u8 _000[0x257];
    /*0x257*/ s8 team;
    /*0x258*/ u8 _258[0x279 - 0x258];
    /*0x279*/ u8 flags;
} GameActorView;

// Actor manager lbl_8036E548 (see ActorManager in main/file_80026134.h).
typedef struct ActorMgrView {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ GameActorView* actors[13];
} ActorMgrView;
extern ActorMgrView lbl_8036E548;

typedef struct FielderView {
    /*0x000*/ u8 _000[0x218];
    /*0x218*/ u8 opponentIdx; // 0 for the human team's own players, else 1..n
    /*0x219*/ u8 _219[0x268 - 0x219];
} FielderView; // size: 0x268
extern FielderView g_Fielders[];

// Stadium/scene work pointed to by lbl_3_common_bss_1323C (only the fields used here).
typedef struct SceneWorkView {
    /*0x000*/ u8 _000[0x261];
    /*0x261*/ u8 flags261[0x27E - 0x261];
    /*0x27E*/ s8 busy;
} SceneWorkView;
extern SceneWorkView* lbl_3_common_bss_1323C;

typedef struct QueueParentView {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s16 done;
} QueueParentView;

// Running task (lbl_803CC1B8, cf. SceneTask in main/file_80069BDC.h).
typedef struct WaitTaskView {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ QueueParentView* parent;
    /*0x10*/ u8 _10[0x18 - 0x10];
    /*0x18*/ s16 timer;
    /*0x1A*/ u8 _1A[0x22 - 0x1A];
    /*0x22*/ s16 state;
} WaitTaskView;
extern WaitTaskView* lbl_803CC1B8;

// .text:0x000219CC size:0xDC mapped:0x80660A60
// NONMATCHING 85%: original indexes GameLogic with a precomputed (human * 4 + 0xF4) offset (lwzx)
#if NONMATCHING
void fn_3_219CC(void) {
    s32 n = 0;
    s32 i;

    for (i = 0; i < 9; i++) {
        if (g_GameLogic.Team_CaptainRosterLoc[g_d_GameSettings.humanTeamNumber] == lbl_8036E548.actors[i]->team) {
            g_Fielders[i].opponentIdx = 0;
        } else {
            g_Fielders[i].opponentIdx = ++n;
        }
    }
}
#endif

// .text:0x00021AA8 size:0x134 mapped:0x80660B3C
void fn_3_21AA8(void) {
    WaitTaskView* task = lbl_803CC1B8;
    InMemRunnerType* runner = g_Runners;
    GameActorView* actor = lbl_8036E548.actors[9];

    switch (task->state) {
    case 0:
        if (runner->charID == 2 || runner->charID == 9) {
            task->state = 1;
        } else {
            task->state = 3;
        }
        break;
    case 1:
        if (task->timer-- == 0) {
            task->state = 2;
        }
        break;
    case 2:
        if ((actor->flags & 2) || (actor->flags & 1)) {
            fn_3_14E50();
        }
        if (lbl_3_common_bss_1323C->busy == 0) {
            task->state = 3;
        }
        break;
    case 3: {
        QueueParentView* parent;
        fn_3_14E1C();
        lbl_3_common_bss_1323C->busy = 0;
        parent = lbl_803CC1B8->parent;
        parent->done = 1;
        fn_800B0A14_removeQueue(parent);
        task->state = 0;
        break;
    }
    }
}

// .text:0x00021BDC size:0xA0 mapped:0x80660C70
void fn_3_21BDC(void) {
    WaitTaskView* task = lbl_803CC1B8;

    switch (task->state) {
    case 0:
        task->state = 1;
        task->timer = 90;
        break;
    case 1:
        if (task->timer-- == 0) {
            task->state = 2;
        }
        break;
    case 2: {
        QueueParentView* parent = task->parent;
        parent->done = 1;
        fn_800B0A14_removeQueue(parent);
        task->state = 0;
        break;
    }
    }
}

// .text:0x00021C7C size:0x14 mapped:0x80660D10
void fn_3_21C7C(s32 idx, s32 value) {
    lbl_3_common_bss_1323C->flags261[idx] = value;
}
