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
void fn_8006C2B4(void) {
    return;
}

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
void starMissionMenu(void) {
    return;
}

// .text:0x8006CBE4 size:0xC0
void challengeRelated(void) {
    return;
}

// .text:0x8006CCA4 size:0x11C
void determineIfMissionDescriptionIsShown(void) {
    return;
}

// .text:0x8006CDC0 size:0xFC
void fn_8006CDC0(void) {
    return;
}

// .text:0x8006CEBC size:0xB0
void fn_8006CEBC(void) {
    return;
}

// .text:0x8006CF6C size:0xB8
void fn_8006CF6C(void) {
    return;
}
