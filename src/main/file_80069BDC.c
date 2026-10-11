#include "main/file_80069BDC.h"
#include "main/file_800B0724.h"
#include "Dolphin/vi.h"
#include "Dolphin/gx.h"

#include "string.h"

extern AnimEventCallback lbl_803CBD38;
extern AnimEventCallback lbl_803CBD3C;
extern GXRenderModeObj* lbl_803CBD34;
extern GXRenderModeObj lbl_80109250;
extern GXRenderModeObj lbl_8010928C;
extern u8 lbl_80366158[0x30]; // TODO type
extern s16 lbl_80109400[8];
extern s16 lbl_80109410[8];
extern f32 lbl_801093E8[6];
extern s16 lbl_803CB8E0[4];
extern s16 lbl_803CB8E8;
extern f32 lbl_8010B590[4][7];
extern f32 lbl_8010B4B4[5][11];
extern s16 lbl_8010B444[5][11];

extern BOOL challengeStarRelatedInd(s32 team, s32 mission);

typedef struct MissionDef {
    /*0x0*/ s16 _0;
    /*0x2*/ s16 type;
    /*0x4*/ s16 starsNeeded;
    /*0x6*/ s16 _6;
    /*0x8*/ s16 _8;
} MissionDef; // size: 0xA

extern MissionDef lbl_8010A768[20][10];
extern u8 lbl_803CB8F0[8];

typedef struct Unk803297E0 {
    /*0x0000*/ u8 _0000[0xCF69];
    /*0xCF69*/ u8 _CF69;
    /*0xCF6A*/ u8 _CF6A;
    /*0xCF6B*/ u8 _CF6B;
    /*0xCF6C*/ u8 _CF6C[4];
} Unk803297E0;

extern Unk803297E0 lbl_803297E0;

typedef struct Unk80366B18 {
    /*0x00*/ u8 _00[0x2F];
    /*0x2F*/ u8 _2F;
    /*0x30*/ u8 _30[8];
} Unk80366B18; // size: 0x38

extern Unk80366B18 lbl_80366B18[36];
extern u8 lbl_801075A8[0xE0]; // TODO type

extern void fn_80034E20(void* task, void* desc);
extern void* fn_80034CEC(void* task);
extern u8 fn_8000F988(void* task, s32 idx, s32 a, s32 b, s32 c, s32 d);
extern void fn_8000FEE8(u8 idx);
extern void fn_8000F8F4(void* task);

// .text:0x80069BDC size:0x5B8
void fn_80069BDC(void) {
    return;
}

// .text:0x8006A194 size:0x36C
void fn_8006A194(void) {
    return;
}

// .text:0x8006A500 size:0x324
void fn_8006A500(void) {
    return;
}

// .text:0x8006A824 size:0x400
void fn_8006A824(void) {
    return;
}

// .text:0x8006AC24 size:0x348
void fn_8006AC24(void) {
    return;
}

// .text:0x8006AF6C size:0x30
void fn_8006AF6C(void) {
    if (lbl_803CC1B8->_3B == 0) {
        fn_800B0A14_removeQueue(lbl_803CC1B8);
    }
}

// .text:0x8006AF9C size:0x294
void fn_8006AF9C(void) {
    return;
}

// .text:0x8006B230 size:0x438
void fn_8006B230(void) {
    return;
}

// .text:0x8006B668 size:0x124
void fn_8006B668(void) {
    return;
}

// .text:0x8006B78C size:0x3D4
void fn_8006B78C(void) {
    return;
}

// .text:0x8006BB60 size:0x2A0
void fn_8006BB60(void) {
    return;
}

// .text:0x8006BE00 size:0x288
void fn_8006BE00(void) {
    return;
}

// .text:0x8006C088 size:0x48
void fn_8006C088(s32 alt) {
    lbl_803CBD34 = alt ? &lbl_8010928C : &lbl_80109250;
    VIConfigure(lbl_803CBD34);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
}

// .text:0x8006C0D0 size:0x30
void fn_8006C0D0(void) {
    fn_800B0A5C_insertQueue(fn_8006BE00, lbl_803CC1B8->priority);
}

// .text:0x8006C100 size:0x3C
// NONMATCHING 80%: the original keeps a rolled pointer-walk loop with an int counter; CW unrolls it here (u8 counter adds clrlwi)
#if NONMATCHING
u8 fn_8006C100(s16 value) {
    u32 i;

    for (i = 0; i < 7; i++) {
        if (value >= lbl_80109400[i]) {
            return i;
        }
    }
    return 6;
}
#endif

// .text:0x8006C13C size:0x12C
void fn_8006C13C(void) {
    return;
}

// .text:0x8006C268 size:0x4C
// NONMATCHING 70%: the original keeps the 6-iteration sum loop rolled; CW fully unrolls it here
#if NONMATCHING
s16 fn_8006C268(StatOutput* stats) {
    s16 total = 0;
    u32 i;

    for (i = 0; i < 6; i++) {
        total += stats->vals[i];
    }
    total += stats->_C + stats->_E;
    if (total > 9999) {
        total = 9999;
    }
    return total;
}
#endif

// .text:0x8006C2B4 size:0xE4
// NONMATCHING 90%: CW unrolls the 6-iteration loop 2x (ctr loop); the original keeps it rolled with cmplwi/blt
#if NONMATCHING
void fn_8006C2B4(StatOutput* out, StatInput* in) {
    u32 i;
    u8 k;
    s16 v;
    s16 r;

    for (i = 0; i < 6; i++) {
        k = in->order[i];
        v = in->vals[k - 1];
        if (v > lbl_80109410[k]) {
            v = lbl_80109410[k];
        }
        r = v * lbl_801093E8[k - 1];
        if (r > 999) {
            r = 999;
        }
        out->vals[k - 1] = r;
    }
    v = lbl_803CB8E0[in->_12];
    if (v > 999) {
        v = 999;
    }
    out->_C = v;
    v = in->_13 * lbl_803CB8E8;
    if (v > 999) {
        v = 999;
    }
    out->_E = v;
}
#endif

// .text:0x8006C398 size:0x58
// NONMATCHING 75%: the original keeps the 6-iteration order[] init loop rolled; CW fully unrolls it here
#if NONMATCHING
void fn_8006C398(StatInput* in) {
    u32 i;

    memset(in, 0, sizeof(StatInput));
    for (i = 0; i < 6; i++) {
        in->order[i] = i + 1;
    }
    in->_12 = 3;
}
#endif

// .text:0x8006C3F0 size:0x8
void fn_8006C3F0(AnimEventCallback cb) {
    lbl_803CBD38 = cb;
}

// .text:0x8006C3F8 size:0x44
void fn_8006C3F8(void* obj, f32 frame, s32 a, s32 b) {
    if (lbl_80366158[0x28] != 1 && lbl_803CBD38 != NULL) {
        lbl_803CBD38(obj, frame, a, b);
    }
}

// .text:0x8006C43C size:0x8
void fn_8006C43C(AnimEventCallback cb) {
    lbl_803CBD3C = cb;
}

// .text:0x8006C444 size:0x44
void fn_8006C444(void* obj, f32 frame, s32 a, s32 b) {
    if (lbl_80366158[0x28] != 1 && lbl_803CBD3C != NULL) {
        lbl_803CBD3C(obj, frame, a, b);
    }
}

// .text:0x8006C488 size:0x4
void fn_8006C488(void) {
}

// .text:0x8006C48C size:0x140
void challengeDrawStarsOnMissionMenu(void) {
    return;
}

// .text:0x8006C5CC size:0xF8
BOOL fn_8006C5CC(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 54; i++) {
        s32 status = starMissionCompletionTracker[i]._31;
        if (status == 1) {
            s32 captain = starMissionCompletionTracker[i].challengeCaptain;
            if (captain != 5) {
                count++;
            }
        }
    }
    return count >= 28;
}

// .text:0x8006C6C4 size:0xD8
s32 fn_8006C6C4(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 54; i++) {
        s32 status = starMissionCompletionTracker[i]._31;
        if (status == 1) {
            count++;
        }
    }
    return count;
}

// .text:0x8006C79C size:0x28
BOOL fn_8006C79C(s32 idx) {
    return (s8)gChallengeState.trackers[idx]._31 == 1;
}

// .text:0x8006C7C4 size:0x214
void starMissionRelated2(void) {
    return;
}

// .text:0x8006C9D8 size:0xC4
void fn_8006C9D8(void) {
    return;
}

// .text:0x8006CA9C size:0x2C
f32 fn_8006CA9C(void) {
    return lbl_8010B590[gChallengeState._4415][gChallengeState._4422];
}

// .text:0x8006CAC8 size:0x11C
f32 starMissionMenu(s32 team) {
    ChallengeTrackingStruct* t = &starMissionCompletionTracker[team];
    s32 count;
    s32 i;

    if (lbl_800E8558[team].hasMissions == 0) {
        count = 0;
    } else {
        count = 0;
        for (i = 0; i < 10; i++) {
            if ((s8)t->inGameMissionTracker[i].starMissionStatus < 0) {
                count++;
            }
        }
    }
    return lbl_8010B4B4[t->variantClassification][count];
}

// .text:0x8006CBE4 size:0xC0
// NONMATCHING 99%: the original copies count into i (mr r30,r31) instead of a second li 0
#if NONMATCHING
s16 challengeRelated(s32 team) {
    s32 count;
    s32 i;
    ChallengeTrackingStruct* t = &starMissionCompletionTracker[team];

    if (lbl_800E8558[team].hasMissions == 0) {
        count = 0;
    } else {
        count = 0;
        for (i = 0; i < 10; i++) {
            if (challengeStarRelatedInd(team, i)) {
                count++;
            }
        }
    }
    return lbl_8010B444[t->variantClassification][count];
}
#endif

// .text:0x8006CCA4 size:0x11C
s16 determineIfMissionDescriptionIsShown(s32 team) {
    ChallengeTrackingStruct* t = &starMissionCompletionTracker[team];
    s32 count;
    s32 i;

    if (lbl_800E8558[team].hasMissions == 0) {
        count = 0;
    } else {
        count = 0;
        for (i = 0; i < 10; i++) {
            if ((s8)t->inGameMissionTracker[i].starMissionStatus < 0) {
                count++;
            }
        }
    }
    return lbl_8010B444[t->variantClassification][count];
}

// .text:0x8006CDC0 size:0xFC
s32 fn_8006CDC0(s32 team) {
    ChallengeTrackingStruct* base = starMissionCompletionTracker;
    ChallengeTrackingStruct* t;
    s32 count;
    s32 i;

    if (lbl_800E8558[team].hasMissions == 0) {
        return 0;
    }
    count = 0;
    t = &base[team];
    for (i = 0; i < 10; i++) {
        if ((s8)t->inGameMissionTracker[i].starMissionStatus < 0) {
            count++;
        }
    }
    return count;
}

// .text:0x8006CEBC size:0xB0
void fn_8006CEBC(void) {
    SceneTask* task = lbl_803CC1B8;
    s32 i;

    if (lbl_803297E0._CF6B != 0) {
        lbl_803297E0._CF6B = 0;
        for (i = 0; i < 4; i++) {
            fn_8000FEE8(lbl_803297E0._CF6C[i]);
        }
        fn_8000F8F4(task);
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
    if (lbl_803297E0._CF69 == 0) {
        lbl_803297E0._CF69 = 1;
        lbl_803297E0._CF6A = 1;
    }
}

// .text:0x8006CF6C size:0xB8
void fn_8006CF6C(void) {
    void* task = lbl_803CC1B8;
    s32 i;

    lbl_803297E0._CF6B = 0;
    fn_80034E20(task, lbl_801075A8);
    for (i = 0; i < 4; i++) {
        lbl_803297E0._CF6C[i] = fn_8000F988(task, i + 2, 0, 0, i + 0x1C1, 0);
        lbl_80366B18[lbl_803297E0._CF6C[i]]._2F = 1;
    }
    lbl_803CC1B8->func = fn_8006CEBC;
}
