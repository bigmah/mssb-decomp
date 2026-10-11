#include "main/file_8004207C.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_800527C4.h"
extern s32 fn_80021410(void);
#include "Dolphin/GX/GXPerf.h"
#include "Dolphin/GX/GXMisc.h"
#include "musyx/musyx.h"
#include "Dolphin/os.h"
#include "Dolphin/mtx.h"
#include "stl/mem.h"

#pragma dont_inline on

extern u32 lbl_803CB750; // random seed
extern u8 lbl_800EFBA4[]; // sound effect volumes

// GP performance counters (debug overlay).
typedef struct GPMetrics {
    /*0x00*/ u32 cur[11];
    /*0x2C*/ u32 min[11];
    /*0x58*/ u32 max[11];
} GPMetrics;

extern GPMetrics lbl_802E4B28;
extern s32 lbl_803CB838; // frames until min/max reset
DECL_SECT(".sdata") extern s32 lbl_803CB83C[2]; // selected GP0/GP1 metric
extern u32 lbl_803CBCE8; // metrics enabled
extern void* lbl_803CC1B8; // current process-queue node
extern MsgDef lbl_800FB5C0[];
extern SwingFxFunc lbl_800FBE64[];
extern s8 lbl_800FBDEC[]; // anim ID -> lbl_800FBE64 index (11 = none)
extern s32 lbl_803CB848;
extern s32 lbl_803CB850;
extern s32 lbl_803CBCF8;
extern s32 lbl_803CBCFC;
extern s32 lbl_803CBD00;
extern u32 lbl_803CBD04;

typedef struct Unk80366158 {
    /*0x00*/ u8 _00[0x28];
    /*0x28*/ u8 _28;
} Unk80366158;
extern Unk80366158 lbl_80366158;

extern void fn_8004CA14(s32 a, u16 msg);
extern void fn_8004CC18(void);
extern void fn_8004CC2C(void);
extern void fn_8004CC4C(u8 first, u8 second, u8 third, s32 selection, u16 value); // TODO: file_8004C5F8.h says s16; callers pass u16 unextended
extern s32 fn_8004CA6C(u16 buttons);
extern void fn_8004D0F0(void);
extern void fn_8004C19C(CharModel* model, s32 animID, u32 colorIdx, f32 frame);
extern void fn_8004C510(CharModel* model, s32 animID, u32 colorIdx, f32 frame);
// Controller status, one 0x20 block per port.
typedef struct PadStatus {
    /*0x00*/ u16 held;
    /*0x02*/ u16 pressed;
    /*0x04*/ u8 _04[0x1C];
} PadStatus;
#define gPads ((PadStatus*)&lbl_803C77B8) // TODO type: lbl_803C77B8_s only describes the first pad

extern void fn_800569C8(void);
extern void fn_800625A4(s32 port, s32 sound);
extern u8 lbl_800FB5B0[]; // TODO type
extern u8 lbl_8010B600[][3]; // innings per challenge difficulty
extern u8 lbl_800FEF70[]; // TODO type
extern s32 lbl_803CBCF0;
extern u8 lbl_80361B20[]; // per character: can be boosted
extern u8 lbl_800E86F0[12]; // stat boosts
extern u8 lbl_802E4B00[2][9];
// Character actor table (owned by another unit; only active[] is used here).
typedef struct CharActors {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ CharModel* active[13];
} CharActors;
extern CharActors lbl_8036E548;
extern BatFxTables lbl_800FC0FC;
extern EffectParams lbl_800FBEA4;
extern EffectParams* lbl_803CB84C; // &lbl_800FBEA4
extern s32 lbl_800FBE90[5];
extern u32 lbl_803CBD0C;
extern void fn_8002F1AC(Vec* pos, s32 idx);
extern void fn_8002F258(Vec* pos, s32 idx, s32* params);
extern char lbl_800E6920[]; // "orderchange.c"
extern char lbl_800E6930[]; // "//OZ" + SJIS "no return value"
extern f32 starMissionMenu(s16 charID);
extern f32 fn_8006CA9C(void);

extern void characterSelectScreen(s32 team);
extern void fn_800415A8(void);
extern void unsure_FillRosterPositions(s32 team);
extern void SetMenuNumber(void);
extern void fn_800671FC(void);
extern void fn_80069854(MenuWork* work);
extern u8 lbl_803CBCC9;
typedef struct Unk803CBD24 {
    /*0x0*/ u8 _0[4];
    /*0x4*/ u8 team;
} Unk803CBD24;
DECL_SECT(".sdata") extern Unk803CBD24 lbl_803CBD24;
extern s16 lbl_8010B42C[]; // star menu entries per character class
extern CharacterStats lbl_803C5144[2]; // picked-up player per team
extern u8 lbl_803CBCCC[2];             // picked-up slot per team
extern OrderEntry lbl_803CBCD0[2];     // picked-up order entry per team
extern u8 lbl_802E4B14[2][9];
extern u8 lbl_803CBCC8;
extern GXPerf0 lbl_800FB4C8[];
extern GXPerf1 lbl_800FB554[];

// .text:0x8004207C size:0x51C
#define SCALE_STAT(field)                    \
    v = scale * (f32)(field);                \
    (field) = v > 100 ? 100 : v

void capApplicationFunction(void) {
    return;
}

// .text:0x80042598 size:0x144
s32 fn_80042598(u8 team, s32 slot) {
    return 0;
}

// .text:0x800426DC size:0x514
void transferStatsToInMemRoster(u8 team) {
    return;
}

// .text:0x80042BF0 size:0x54
s32 randRange_FUN_80042bf0(s32 a, s32 b) {
    return 0;
}

// .text:0x80042C44 size:0xF4
void sndFXRelated(u16 button) {
    switch (button) {
    case 0x100:
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        break;
    case 0x200:
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        break;
    case 0x1:
    case 0x2:
    case 0x4:
    case 0x8:
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        break;
    case 0x3:
    case 0x20:
    case 0x40:
    case 0x400:
    case 0x800:
        break;
    }
}

// .text:0x80042D38 size:0x30
void fn_80042D38(u16 scene) {
    lbl_803CBBCC->prevScene = lbl_803CBBCC->scene;
    lbl_803CBBCC->prevStep = lbl_803CBBCC->step;
    lbl_803CBBCC->scene = scene;
    lbl_803CBBCC->step = 0;
}

// .text:0x80042D68 size:0x40
s32 fn_80042D68(LayoutOwner* owner, s32 idx, s32 value) {
    LayoutObj* obj = lbl_80371C30[owner->baseIdx + idx].obj;
    if ((s32)(obj->_5C >> 16) >= value) {
        obj->_68 = 0;
        return 1;
    }
    return 0;
}

// .text:0x80042DA8 size:0x40
s32 fn_80042DA8(LayoutOwner* owner, s32 idx, s32 value) {
    LayoutObj* obj = lbl_80371C30[owner->baseIdx + idx].obj;
    if ((s32)(obj->_5C >> 16) == value) {
        obj->_68 = 0;
        return 1;
    }
    return 0;
}

// .text:0x80042DE8 size:0x5A4
void challengeStarMenu(void) {
    return;
}

// .text:0x8004338C size:0x4F4
void starMenuCursor(void) {
    return;
}

// .text:0x80043880 size:0x1418
// Order-change menu: left (dir 0) / right (dir 1) on the field view.
void fn_80043880(u8 dir, u8 team) {
    return;
}

// .text:0x80044C98 size:0x14E4
// Order-change menu: up (dir 0) / down (dir 1). On the field view (_CF52 set) the cursor
// jumps between fielding positions; fn_80042598 finds the batting slot of a position.
void fn_80044C98(u8 dir, u8 team) {
    return;
}

// .text:0x8004617C size:0x1078
void fn_8004617C(s32 port) {
    return;
}

// .text:0x800471F4 size:0xAEC
// Field-by-field CharacterStats copy, in the original's order.
#define COPY_CHAR_STATS(d, s)                                                         \
    do {                                                                              \
        s32 k_;                                                                       \
        memcpy((d), (s), 0x1E);                                                       \
        (d)->stats.CharID = (s)->stats.CharID;                                        \
        (d)->stats.FieldingArm = (s)->stats.FieldingArm;                              \
        (d)->stats.BattingStance = (s)->stats.BattingStance;                          \
        memcpy(&(d)->stats.SlapContactSize, &(s)->stats.SlapContactSize, 2);          \
        memcpy(&(d)->stats.SlapHitPower, &(s)->stats.SlapHitPower, 2);                \
        (d)->stats.BuntingContactSize = (s)->stats.BuntingContactSize;                \
        (d)->stats.HitTrajectoryPushPull = (s)->stats.HitTrajectoryPushPull;          \
        (d)->stats.HitTrajectoryHighLow = (s)->stats.HitTrajectoryHighLow;            \
        (d)->stats.Speed = (s)->stats.Speed;                                          \
        (d)->stats.ThrowingArm = (s)->stats.ThrowingArm;                              \
        (d)->stats.CharacterClass = (s)->stats.CharacterClass;                        \
        (d)->stats.Weight = (s)->stats.Weight;                                        \
        (d)->stats.Captain = (s)->stats.Captain;                                      \
        (d)->stats.CaptainStarHitPitch = (s)->stats.CaptainStarHitPitch;              \
        memcpy(&(d)->stats.NonCaptainStarSwing, &(s)->stats.NonCaptainStarSwing, 2);  \
        (d)->stats.FieldingStats = (s)->stats.FieldingStats;                          \
        memcpy(&(d)->stats.BattingStatBar, &(s)->stats.BattingStatBar, 4);            \
        memcpy(&(d)->chemistry, &(s)->chemistry, sizeof(ChemistryTable));             \
        (d)->BytesAfterChemistry[0] = (s)->BytesAfterChemistry[0];                    \
        for (k_ = 0; k_ < 21; k_++) {                                                 \
            (d)->UnusedShorts[k_] = (s)->UnusedShorts[k_];                            \
        }                                                                             \
    } while (0)

u8 fn_800471F4(u8 mode, u8 team) {
    return 0;
}

// .text:0x80047CE0 size:0x304
void fn_80047CE0(void) {
    return;
}

// .text:0x80047FE4 size:0x6FC
// Inline form of fn_80042D38.
#define SET_SCENE(id)                                          \
    lbl_803CBBCC->prevScene = lbl_803CBBCC->scene;            \
    lbl_803CBBCC->prevStep = lbl_803CBBCC->step;              \
    lbl_803CBBCC->scene = (id);                               \
    lbl_803CBBCC->step = 0

void pauseMenuSelection(void) {
    return;
}

// .text:0x800486E0 size:0x84
void fn_800486E0(s32 priority, s8 a, s8 b) {
    fn_800B0A5C_insertQueue(pauseMenuSelection, priority);
    lbl_803297E0._CF38 = 0;
    lbl_803297E0._CF3A = a;
    lbl_803297E0._CF42 = 0;
    if (g_d_GameSettings._06 != 2) {
        lbl_803297E0._CF3B = 0;
    } else {
        lbl_803297E0._CF3B = b;
    }
}

// .text:0x80048764 size:0xBC
void fn_80048764(void) {
    switch (lbl_803CBBCC->step) {
    case 0:
        if (lbl_803C66B0.busy0 == 0 && lbl_803C66B0.busy1 == 0) {
            fn_800B0A5C_insertQueue(pauseMenuSelection, 0x1000);
            lbl_803297E0._CF38 = 0;
            lbl_803297E0._CF3A = -1;
            lbl_803297E0._CF42 = 0;
            if (g_d_GameSettings._06 != 2) {
                lbl_803297E0._CF3B = 0;
            } else {
                lbl_803297E0._CF3B = 0;
            }
            lbl_803CBBCC->step++;
        }
        break;
    case 1:
        break;
    }
}

// .text:0x80048820 size:0x3CC
s32 fn_80048820(void* menuPtr, u16 held, u16 trig, u16 repeat, u8 holdTime) {
    return 0;
}

// fn_80048BEC, size:0x28
void fn_80048BEC(void* menuPtr, u32 a, u32 b) {
    DebugMenu* menu = menuPtr;
    s32 count = menu->count < menu->visible ? menu->count : menu->visible;
    while (count > 0) {
        count--;
    }
}

// fn_80048C14, size:0x8
void fn_80048C14(u32 value) {
    lbl_803CBCE8 = value;
}

// fn_80048C1C, size:0xC
void fn_80048C1C(void) {
    if (lbl_803CBCE8 != 0) {
        return;
    }
}

// .text:0x80048C28 size:0x124
void fn_80048C28(void) {
    return;
}

// .text:0x80048D4C size:0xB4
void fn_80048D4C(void) {
    if (lbl_803CBCE8 == 0) {
        return;
    }
    GXSetGPMetric(lbl_800FB4C8[lbl_803CB83C[0]], lbl_800FB554[lbl_803CB83C[1]]);
    GXClearGPMetric();
    if (lbl_800FB4C8[lbl_803CB83C[0]] == GX_PERF0_CLOCKS) {
        GXReadGP0Metric();
    }
    if (lbl_800FB554[lbl_803CB83C[1]] == GX_PERF1_CLOCKS) {
        GXReadGP1Metric();
    }
    GXSetVCacheMetric(GX_VC_ALL);
    GXClearVCacheMetric();
    GXClearPixMetric();
}

// .text:0x80048E00 size:0xA8
s32 fn_80048E00(s32 index, s32 value) {
    s32 count = 35;
    if (index != 0) {
        count = 23;
    }
    if (value >= count) {
        value = 0;
    } else if (value < 0) {
        value = count - 1;
    }
    if (value != lbl_803CB83C[index]) {
        lbl_803CB83C[index] = value;
        memset(lbl_802E4B28.max, 0, sizeof(lbl_802E4B28.max));
        memset(lbl_802E4B28.min, 0xFF, sizeof(lbl_802E4B28.min));
        lbl_803CB838 = 300;
    }
    return value;
}

// fn_80048EA8, size:0x10
s32 fn_80048EA8(s32 index) {
    return lbl_803CB83C[index];
}

// .text:0x80048EB8 size:0x368
void startGameRelated(void) {
    return;
}

// .text:0x80049220 size:0x2AC
void fn_80049220(u8 team) {
    return;
}

// .text:0x800494CC size:0x3AC
void fn_800494CC(u8 team) {
    return;
}

// .text:0x80049878 size:0x408
#define RESET_MATCH_OPTIONS(i) \
    lbl_803C5F04.option[0] = 0; \
    lbl_803C5F04.prevOption[0] = 0; \
    lbl_803C5F04.option[1] = 1; \
    lbl_803C5F04.option[2] = 1; \
    lbl_803C5F04.option[3] = 2; \
    lbl_803C5F04.option[4] = 0; \
    lbl_803C5F04.prevOption[1] = 1; \
    lbl_803C5F04.prevOption[2] = 1; \
    lbl_803C5F04.prevOption[3] = 2; \
    lbl_803C5F04.prevOption[4] = 0; \
    for (i = 0; i < 4; i++) { \
        lbl_803C5F04.playerOption[i][0] = 0; \
        lbl_803C5F04.playerOption[i][1] = 0; \
        lbl_803C5F04.playerOption[i][2] = 0; \
        lbl_803C5F04.playerOption[i][3] = 1; \
        lbl_803C5F04.prevPlayerOption[i][0] = 0; \
        lbl_803C5F04.prevPlayerOption[i][1] = 0; \
        lbl_803C5F04.prevPlayerOption[i][2] = 0; \
        lbl_803C5F04.prevPlayerOption[i][3] = 1; \
    }


void possiblyTransferDataBetweenDifferentRels(void) {
    return;
}

// .text:0x80049C80 size:0xBC
void fn_80049C80(void) {
    if (lbl_803C66B0.busy0 != 0 || lbl_803C66B0.busy1 != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 5 && lbl_8037169C.done == 0) {
        changeScene(1, 6);
    }
    lbl_803C5EA4._36 = 1;
    lbl_803C5EA4.prevMode = lbl_803C5EA4.mode;
    lbl_803C5EA4.mode = 3;
    possiblyTransferDataBetweenDifferentRels();
    memset(&lbl_803C5EE0, 0, 0x16);
    fn_800569C8();
    fn_800625A4(0, 0x29);
}

// .text:0x80049D3C size:0x50
void fn_80049D3C(void) {
    u8 mode = g_d_GameSettings.GameModeSelected;
    s32 i;

    if (mode == 6) {
        return;
    }
    if (lbl_803C5F04._36 == 0) {
        return;
    }
    for (i = 0; i < (mode == 6 ? 4 : 2); i++) {
    }
}

// .text:0x80049D8C size:0x370
void fn_80049D8C(u8 dir, u8 team) {
    return;
}

// .text:0x8004A0FC size:0xC0
void fn_8004A0FC(void) {
    s32 i;

    RESET_MATCH_OPTIONS(i);
}

// .text:0x8004A1BC size:0x100
void fn_8004A1BC(void) {
    return;
}

// .text:0x8004A2BC size:0x6C
void fn_8004A2BC(void) {
    switch (lbl_803CBBCC->step) {
    case 0:
        fn_800B0A5C_insertQueue(fn_8004A1BC, 0x2000);
        lbl_803C5F04._2C = 0;
        lbl_803CBBCC->step++;
        break;
    case 1:
        break;
    }
}

// .text:0x8004A328 size:0x24
s32 fn_8004A328(MsgBox* box) {
    if (box->state != 0) {
        return 0;
    }
    box->state = 2;
    return 1;
}

// .text:0x8004A34C size:0x26C
s32 fn_8004A34C(MsgBox* box, s8 a, u8 msgId, s8 b, u8 arg) {
    return 0;
}

// .text:0x8004A5B8 size:0x218
void fn_8004A5B8(void) {
    return;
}

// .text:0x8004A7D0 size:0x210
void fn_8004A7D0(void) {
    return;
}

// .text:0x8004A9E0 size:0x1F8
void fn_8004A9E0(void) {
    return;
}

extern s32 lbl_803CBCFC;
extern s32 lbl_803CBD00;

extern s32 lbl_803CB848;

// Set_803cb848, size:0x8
void Set_803cb848(s32 value) {
    lbl_803CB848 = value;
}

// fn_8004ABE0, size:0x8
s32 fn_8004ABE0(void) {
    return lbl_803CBCFC;
}

// fn_8004ABE8, size:0x18
s32 fn_8004ABE8(s32 clear) {
    s32 value = lbl_803CBD00;
    if (clear != 0) {
        lbl_803CBD00 = 0;
    }
    return value;
}

// .text:0x8004AC00 size:0xC4
void fn_8004AC00(CharModel* model, s32 animID, u32 colorIdx, f32 frame) {
    if (lbl_80366158._28 == 1) {
        return;
    }
    if (model->charID == 0) {
        if (frame >= (f32)lbl_803CBCF8 && frame <= (f32)lbl_803CB850) {
            lbl_803CBD00 = 1;
            if (frame == 0.5) {
                lbl_803CBCFC = 1;
            } else {
                lbl_803CBCFC = 0;
            }
        }
    } else if (model->charID == 0x12) {
        fn_8004C19C(model, animID, colorIdx, frame);
    }
}

extern u32 lbl_803CBD08;

extern u32 lbl_803CBD04;

// fn_8004ACC4, size:0x18
u32 fn_8004ACC4(s32 clear) {
    u32 value = lbl_803CBD04;
    if (clear != 0) {
        lbl_803CBD04 = 0;
    }
    return value;
}

// fn_8004ACDC, size:0x18
u32 fn_8004ACDC(s32 clear) {
    u32 value = lbl_803CBD08;
    if (clear != 0) {
        lbl_803CBD08 = 0;
    }
    return value;
}

// .text:0x8004ACF4 size:0x60
void fn_8004ACF4(CharModel* model, s32 animID, u32 colorIdx, f32 frame) {
    switch (model->charID) {
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
        if (frame < 0.5f) {
            lbl_803CBD04 = 1;
        }
        break;
    }
    lbl_800FBE64[2](model, animID, colorIdx, frame);
}

// .text:0x8004AD54 size:0xC4
s32 fn_8004AD54(u32 stadium, u8 flags) {
    return 0;
}

// .text:0x8004AE18 size:0x190
void fn_8004AE18(s32 idx) {
    return;
}

// .text:0x8004AFA8 size:0x210
void fn_8004AFA8(s32 idx) {
    return;
}

// fn_8004B1B8, size:0x8
void fn_8004B1B8(u32 value) {
    lbl_803CBD0C = value;
}

// .text:0x8004B1C0 size:0x48
void fn_8004B1C0(s32 kind, CharModel* model, s32 animID, u32 colorIdx, f32 frame) {
    if (kind != 11) {
        lbl_800FBE64[kind](model, animID, colorIdx, frame);
    }
}

// .text:0x8004B208 size:0x68
void fn_8004B208(CharModel* model, s32 animID, u32 colorIdx, f32 frame) {
    s8 kind;

    if (lbl_803CB848 != 0 && animID >= 0 && animID < 0x75) {
        kind = lbl_800FBDEC[animID];
        if (kind != 11) {
            lbl_800FBE64[kind](model, animID, colorIdx, frame);
        }
    }
}

extern u32 lbl_803CBD04;

extern u32 lbl_803CBD08;

extern u32 lbl_803CBD0C;

// fn_8004B270, size:0x14
void fn_8004B270(void) {
    lbl_803CBD0C = 0;
    lbl_803CBD08 = 0;
    lbl_803CBD04 = 0;
}
