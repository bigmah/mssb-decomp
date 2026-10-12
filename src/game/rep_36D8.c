#include "game/rep_36D8.h"
#define REP_HEADER_FN repHeader_36D8
#include "header_rep_inline.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/math_api.h"


extern u8 g_Minigame[];
extern u8 lbl_3_data_21804[];
extern void fn_3_157DB8(s16);
extern void fn_3_14C904(void);
extern u32 fn_3_90064(s32 id);
extern f32 lbl_3_data_2188C[];
extern s16 lbl_3_data_218A8;
extern f64 lbl_3_rodata_3760;
extern const f32 lbl_3_rodata_3734; // 0.0f
extern const f32 lbl_3_rodata_376C; // 1.0f
extern const f64 lbl_3_rodata_3770; // 45.0
extern const f64 lbl_3_rodata_3778; // 2.0
extern const f32 lbl_3_rodata_3780; // 32767.0f
extern const f64 lbl_3_rodata_3788; // 0.5
extern const f32 lbl_3_rodata_3790; // pi / 180
extern f64 sin(f64);
extern f64 cos(f64);
extern void* memcpy(void*, const void*, u32);
extern f32 RandomF32_Game_Range(f32 a, f32 b);
extern const f64 lbl_3_rodata_3798; // 3.0
extern const f64 lbl_3_rodata_37A0; // 0.0
extern int __float_nan[];
extern f64 __frsqrte(f64);
extern s16 fn_3_9FB8C(f32 x, f32 y);
extern s32 fn_3_108854(void);
extern u8 lbl_3_data_2127C[][5];  // AI strength per game mode and difficulty
extern u8 lbl_3_data_21874[5];    // time limit in seconds per difficulty (4: multiplayer)
extern u8 lbl_3_data_21860[5][4]; // per difficulty (4: multiplayer) and slot
extern s32 lbl_3_data_265F0;
extern RepBallView g_Ball;
extern void fn_3_59A90(void);
extern void fn_3_8913C(void);
extern void fn_3_6D964(s32 a, s32 b);
extern void fn_3_9E078(s32* arr, s32 n, BOOL useBallRng);
extern void fn_3_810C4(int idx, int base);
extern void minigamesSetSomePointers2(void);
extern void minigamesGXStuff(void);
extern void fn_3_CC81C(void);
extern void fn_3_F1DC(void);
extern void fn_3_169600(void);
extern void fn_3_7D9DC(int i);
extern u8 lbl_3_data_2187C[3][2]; // kind weights per time stage
extern int RandomIndexFromWeights(u8* weights, int count);
extern int random_fn_3_9EE24(int max);
extern void fn_3_1541C4(u32 slot, u32 kind, Vec* pos);
extern void fn_3_106EB0(void);
extern u8 lbl_3_data_2192C[];
extern u8 lbl_3_data_2195C[];
extern u8 lbl_3_data_2196C[];
extern u8 lbl_3_data_21974[];
extern f32 lbl_3_data_21934[]; // per AI strength: max distance to go for an item
extern const f32 lbl_3_rodata_372C; // 0.001f
extern f64 __fabs(f64);
extern u16 lbl_3_data_81FC[]; // sound ids
// .bss (laid out last-defined-first)
static s32 lbl_3_bss_B798[0xA];
static f32 lbl_3_bss_B794;
static u8 lbl_3_bss_B791;
static u8 lbl_3_bss_B790[0x1]; // unused
extern void fn_800246D4(s32 (*compare)(void* key, void* elem), u8* src, u8* dst, s32 size, s32 count);

// Inlined single-precision sqrt (MSL sqrtf with the rodata constants of this unit).
#define REP_SQRTF(x)                                                                    \
    do {                                                                                \
        if ((x) > lbl_3_rodata_3734) {                                                  \
            f64 xd = (f64)(x);                                                          \
            f64 guess = __frsqrte(xd);                                                  \
            guess = lbl_3_rodata_3788 * guess * (lbl_3_rodata_3798 - guess * guess * xd); \
            guess = lbl_3_rodata_3788 * guess * (lbl_3_rodata_3798 - guess * guess * xd); \
            guess = lbl_3_rodata_3788 * guess * (lbl_3_rodata_3798 - guess * guess * xd); \
            (x) = (f32)(xd * guess);                                                    \
        } else if ((x) < lbl_3_rodata_37A0) {                                           \
            (x) = *(f32*)__float_nan;                                                   \
        } else if (isnan(x)) {                                                          \
            (x) = *(f32*)__float_nan;                                                   \
        }                                                                               \
    } while (0)
extern void fn_8004C094(void*);
extern void fn_3_6C854(int, int);
extern void fn_3_DE4FC(void);
extern f32 lbl_3_data_217F8[];
extern f32 lbl_3_rodata_3768;
extern RepRange8 lbl_3_data_21944[];  // per AI strength
extern RepRange16 lbl_3_data_2194C[]; // per AI strength
extern s8 lbl_3_data_2197C[];        // per AI strength
extern s8 lbl_3_data_21980[];        // per AI strength
extern int RandomInt_Game_Range(int, int);
extern int RandomInt_Game(int);
extern void* memset(void*, int, u32);
extern u8 lbl_800EFBA4[];
extern s16 lbl_3_data_21904[];
extern void fn_3_151798(void);
extern void fn_3_11F480(void);
extern void fn_80011578(void);
extern void fn_3_1578F8(void);
extern u32 sndFXStartEx(s32, u8, u8, u8);
extern RepRunnerView g_Runners[];
extern u8 g_GameLogic[];
extern u8 lbl_3_data_21278[];
extern void changeScene(s32, s32);
extern void fn_3_7DD6C(void);
extern void fn_3_10F550(s32, s32);
extern void fn_3_5A6D4(s32);
extern f32 lbl_3_data_218BC[];
#include "static/UnknownHomes_Static.h"

extern s16 lbl_3_data_21924[];
extern u8 lbl_3_data_218AC[5][3]; // per difficulty (4: multiplayer)
extern u8 lbl_3_data_21884[][2];     // per item kind: [1] = points
extern RepBss37400View lbl_3_common_bss_37400;
extern const f32 lbl_3_rodata_3734; // 0.0f
extern const f32 lbl_3_rodata_376C; // 1.0f
extern const f64 lbl_3_rodata_3770; // 45.0
extern const f64 lbl_3_rodata_3778; // 2.0
extern const f32 lbl_3_rodata_3780; // 32767.0f
extern const f64 lbl_3_rodata_3788; // 0.5
extern const f32 lbl_3_rodata_3790; // pi / 180
extern f64 sin(f64);
extern f64 cos(f64);
extern void* memcpy(void*, const void*, u32);
extern f32 RandomF32_Game_Range(f32 a, f32 b);
extern const f64 lbl_3_rodata_3798; // 3.0
extern const f64 lbl_3_rodata_37A0; // 0.0
extern int __float_nan[];
extern f64 __frsqrte(f64);
extern s16 fn_3_9FB8C(f32 x, f32 y);
extern s32 fn_3_108854(void);
extern u8 lbl_3_data_2127C[][5];  // AI strength per game mode and difficulty
extern u8 lbl_3_data_21874[5];    // time limit in seconds per difficulty (4: multiplayer)
extern u8 lbl_3_data_21860[5][4]; // per difficulty (4: multiplayer) and slot
extern s32 lbl_3_data_265F0;
extern RepBallView g_Ball;
extern void fn_3_59A90(void);
extern void fn_3_8913C(void);
extern void fn_3_6D964(s32 a, s32 b);
extern void fn_3_9E078(s32* arr, s32 n, BOOL useBallRng);
extern void fn_3_810C4(int idx, int base);
extern void minigamesSetSomePointers2(void);
extern void minigamesGXStuff(void);
extern void fn_3_CC81C(void);
extern void fn_3_F1DC(void);
extern void fn_3_169600(void);
extern void fn_3_7D9DC(int i);
extern u8 lbl_3_data_2187C[3][2]; // kind weights per time stage
extern int RandomIndexFromWeights(u8* weights, int count);
extern int random_fn_3_9EE24(int max);
extern void fn_3_1541C4(u32 slot, u32 kind, Vec* pos);
extern void fn_3_106EB0(void);
extern u8 lbl_3_data_2192C[];
extern u8 lbl_3_data_2195C[];
extern u8 lbl_3_data_2196C[];
extern u8 lbl_3_data_21974[];
extern f32 lbl_3_data_21934[]; // per AI strength: max distance to go for an item
extern const f32 lbl_3_rodata_372C; // 0.001f
extern f64 __fabs(f64);
extern u16 lbl_3_data_81FC[]; // sound ids
extern void fn_800246D4(s32 (*compare)(void* key, void* elem), u8* src, u8* dst, s32 size, s32 count);

// Inlined single-precision sqrt (MSL sqrtf with the rodata constants of this unit).
#define REP_SQRTF(x)                                                                    \
    do {                                                                                \
        if ((x) > lbl_3_rodata_3734) {                                                  \
            f64 xd = (f64)(x);                                                          \
            f64 guess = __frsqrte(xd);                                                  \
            guess = lbl_3_rodata_3788 * guess * (lbl_3_rodata_3798 - guess * guess * xd); \
            guess = lbl_3_rodata_3788 * guess * (lbl_3_rodata_3798 - guess * guess * xd); \
            guess = lbl_3_rodata_3788 * guess * (lbl_3_rodata_3798 - guess * guess * xd); \
            (x) = (f32)(xd * guess);                                                    \
        } else if ((x) < lbl_3_rodata_37A0) {                                           \
            (x) = *(f32*)__float_nan;                                                   \
        } else if (isnan(x)) {                                                          \
            (x) = *(f32*)__float_nan;                                                   \
        }                                                                               \
    } while (0)
extern void fn_3_152AB4(u8 item, u8 runner);
extern u32 fn_3_90220(s32 idx, s32 off);
extern void fn_3_1608F0(s32 kind, s32 value, s32 extra);
extern const f32 lbl_3_rodata_3758; // 2.0f
extern void fn_3_16C394(s8 a);
extern void fn_3_7FED4(f32* out, f32 dist, f32 frame);
extern void fn_800115C8(s8 index);

#define REP_MG ((RepMinigameView*)g_Minigame)
#define REP_GL ((RepGameLogicView*)g_GameLogic)


extern const f32 lbl_3_rodata_3738; // 4.0f
extern const f32 lbl_3_rodata_373C; // 0.15f
extern const f32 lbl_3_rodata_3728; // 100.0f
extern const f32 lbl_3_rodata_3748; // 1000.0f
extern const f64 lbl_3_rodata_3750; // 1000.0
extern int rand(void);
extern void fn_800528B4(void);
extern const f32 lbl_3_rodata_3730; // 10.0f
extern const f32 lbl_3_rodata_375C; // 0.5f


// .text:0x0013C7BC size:0xDBC mapped:0x8077B850
// CPU players: per frame, decide whether to run forward/back to grab items or to
// get out of the ball's way, and press the matching buttons.
// NONMATCHING 88%: loop shapes, stack layout and register allocation differ
#if NONMATCHING
void fn_3_13C7BC(void) {
    RepAITarget tgt[16];
    u8 list[16];
    s8 dirOut;
    s8 special;
    s8 target3;
    s8 n;
    s8 i;
    s8 k;
    s8 j;
    s8 c;
    s8 t;
    u8 str;
    s32 lim;
    s32 behind;
    f32 f;
    f32 fwd;
    f32 back;
    f32 pos;
    RepAISlot* ai;
    RepPad* pad;
    RepRunnerView* r;

    special = -1;
    target3 = -1;
    n = 0;
    for (i = 0; i < 4; i++) {
        REP_MG->_1DC0[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        for (k = 0; k < 2; k++) {
            t = REP_MG->_1B20.it.pair[i][k];
            if (t < 0) {
                continue;
            }
            switch (REP_MG->_1B1A[t]) {
            case 4:
                special = REP_MG->_1B20.it.pos[t];
                break;
            case 3:
                target3 = REP_MG->_1B20.it.pos[t] + 1;
                for (j = 0; j < 15; j++) {
                    if (REP_MG->itemState[j] - 1 == t) {
                        f = lbl_3_rodata_372C + REP_MG->itemBases[j];
                        if ((s32)(lbl_3_rodata_3728 * f) == target3 * 10) {
                            break;
                        }
                        list[n++] = (s32)(lbl_3_rodata_3730 * f);
                    }
                }
                if (j >= 15) {
                    target3 = -1;
                }
                break;
            case 2:
                list[n++] = REP_MG->_1B20.it.pos[t];
                break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        c = REP_MG->characterIndex[i];
        if (c < 0 || c >= 4 || REP_MG->_18D8[i] == 0) {
            continue;
        }
        ai = &REP_MG->ai[i];
        r = &g_Runners[i];
        pad = &REP_MG->pad[c];
        REP_MG->_1DC0[c] = 1;
        memset(pad, 0, sizeof(RepPad));
        str = REP_MG->aiStrength[i];
        if ((ai->state < 10 || ai->state > 13) && (REP_MG->phase == 1 || REP_MG->_1B06 - REP_MG->frames <= ai->timer)) {
            ai->state = 10;
        }
        switch (ai->state) {
        case 0:
            if (REP_MG->frames / 120 == ai->_6 - 1 && REP_MG->frames % 120 >= 48) {
                ai->state = 7;
                break;
            }
            if (ai->_4-- <= 0) {
                pad->trig = pad->held |= 0x200;
                ai->_4 = RandomInt_Game_Range(((RepRange8*)lbl_3_data_2192C)[str].min, ((RepRange8*)lbl_3_data_2192C)[str].max);
            }
            if (ai->_7-- > 0) {
                break;
            }
            ai->_7 = RandomInt_Game_Range(lbl_3_data_21944[str].min, lbl_3_data_21944[str].max);
            ai->reason = 0;
            if (special >= 0) {
                pos = special / lbl_3_rodata_3730;
                fwd = fn_3_13DDE0(r->fractionalBasesRan, pos, 1);
                if (r->runningDirectionCode == 3) {
                    fwd += lbl_3_rodata_373C;
                }
                back = fn_3_13DDE0(r->fractionalBasesRan, pos, 0);
                if (r->runningDirectionCode == 1) {
                    back += lbl_3_rodata_373C;
                }
                if (fwd < back) {
                    ai->state = 1;
                } else if (fwd > back) {
                    ai->state = 4;
                } else if (r->runningDirectionCode == 2 || r->_136 == 2) {
                    ai->state = RandomInt_Game(2) ? 1 : 4;
                }
                ai->reason = 4;
            } else if (target3 >= 0) {
                if (fn_3_13D618(i, target3 / lbl_3_rodata_3730, &dirOut) <= lbl_3_data_21934[str]) {
                    ai->state = dirOut == 1 ? 1 : 4;
                    ai->reason = 3;
                }
            }
            if (ai->reason == 0 && n != 0) {
                for (j = 0; j < n; j++) {
                    tgt[j].pos = list[j];
                    tgt[j].dist = fn_3_13DA50(i, tgt[j].pos / lbl_3_rodata_3730, &tgt[j].dir);
                }
                fn_800246D4(fn_3_13D5E8, (u8*)tgt, (u8*)tgt, sizeof(RepAITarget), n);
                for (j = 0; j < n; j++) {
                    if (fn_3_13D618(i, tgt[j].pos / lbl_3_rodata_3730, &dirOut) <= lbl_3_data_21934[str]) {
                        ai->state = dirOut == 1 ? 1 : 4;
                        ai->reason = 2;
                        break;
                    }
                }
            }
            if (ai->reason == 0 && (r->runningDirectionCode == 2 || r->_136 == 2)) {
                ai->state = RandomInt_Game(2) ? 1 : 4;
            }
            break;
        case 1:
            if (r->runningDirectionCode == 1 || r->_136 == 1) {
                ai->state = 0;
            } else {
                pad->trig = pad->held |= 0x800;
                ai->state = 2;
            }
            break;
        case 2:
            ai->state = 3;
            break;
        case 3:
            pad->trig = pad->held |= 0x800;
            ai->state = 0;
            break;
        case 4:
            if (r->runningDirectionCode == 3 || r->_136 == 3) {
                ai->state = 0;
            } else {
                pad->trig = pad->held |= 0x400;
                ai->state = 5;
            }
            break;
        case 5:
            ai->state = 6;
            break;
        case 6:
            pad->trig = pad->held |= 0x400;
            ai->state = 0;
            break;
        case 7:
            if (r->runningDirectionCode == 1) {
                pad->trig = pad->held |= 0x400;
            } else if (r->runningDirectionCode == 3) {
                pad->trig = pad->held |= 0x800;
            }
            ai->state = 8;
            break;
        case 8:
            if (r->runningDirectionCode == 2 || r->_136 == 2) {
                ai->state = 9;
            } else {
                ai->state = 7;
            }
            break;
        case 9:
            if (REP_MG->frames % 120 < 96) {
                break;
            }
            if (RandomInt_Game(100) < lbl_3_data_2197C[str]) {
                lim = REP_MG->_1B06 / 120 + 1;
                if (REP_MG->frames / 120 + 2 < lim) {
                    ai->_6 = RandomInt_Game_Range(REP_MG->frames / 120 + 2, lim);
                } else {
                    ai->_6 = lim;
                }
            } else {
                ai->_6 = 0x7F;
            }
            ai->state = 0;
            break;
        case 10:
            if (r->runningDirectionCode == 2 || r->_136 == 2) {
                ai->state = 13;
                break;
            }
            if (ai->reason == 4) {
                ai->wait = RandomInt_Game_Range(((RepRange8*)lbl_3_data_21974)[str].min, ((RepRange8*)lbl_3_data_21974)[str].max);
            } else {
                ai->wait = RandomInt_Game_Range(((RepRange8*)lbl_3_data_2196C)[str].min, ((RepRange8*)lbl_3_data_2196C)[str].max);
            }
            ai->state = 11;
            // fallthrough
        case 11:
            if (ai->wait-- <= 0) {
                if (r->runningDirectionCode == 1) {
                    pad->trig = pad->held |= 0x400;
                } else if (r->runningDirectionCode == 3) {
                    pad->trig = pad->held |= 0x800;
                }
                ai->state = 12;
            }
            break;
        case 12:
            if (r->runningDirectionCode == 2 || r->_136 == 2) {
                ai->state = 13;
            } else {
                ai->wait = 1;
                ai->state = 11;
            }
            break;
        case 13:
            if (REP_MG->phase != 0 && REP_MG->phase != 4) {
                break;
            }
            behind = 0;
            for (j = 0; j < 4; j++) {
                if (REP_MG->characterIndex[j] >= 0 && REP_MG->characterIndex[j] < 4 && REP_MG->points[j] > REP_MG->points[i]) {
                    behind = 1;
                    break;
                }
            }
            if (behind || REP_MG->_17C4 <= 1200) {
                ai->timer = RandomInt_Game_Range(((RepRange16*)lbl_3_data_2195C)[str].min, ((RepRange16*)lbl_3_data_2195C)[str].max);
            } else {
                ai->timer = RandomInt_Game_Range(lbl_3_data_2194C[str].min, lbl_3_data_2194C[str].max);
            }
            if (RandomInt_Game(100) < lbl_3_data_2197C[str]) {
                lim = REP_MG->_1B06 / 120 + 1;
                if (lbl_3_data_21980[str] < lim) {
                    ai->_6 = RandomInt_Game_Range(lbl_3_data_21980[str], lim);
                } else {
                    ai->_6 = lim;
                }
            } else {
                ai->_6 = 0x7F;
            }
            ai->state = 0;
            break;
        }
    }
}
#endif

// .text:0x0013D578 size:0x70 mapped:0x8077C60C
u32 fn_3_13D578(s8 a) {
    // byte cursors over g_Minigame, stepped per player the way the original does
    u8* m = (u8*)REP_MG;
    s16* sp = (s16*)REP_MG;
    s16* tp = &REP_MG->points[a];
    s8 i = 0;
    do {
        s8 t = *(s8*)(m + OFFSET_OF(RepMinigameView, characterIndex));
        if (t >= 0 && t < 4 && *(s16*)((u8*)sp + OFFSET_OF(RepMinigameView, points)) > *tp) {
            return 1;
        }
        i++;
        m += 1;
        sp += 1;
    } while (i < 4);
    return 0;
}

// .text:0x0013D5E8 size:0x30 mapped:0x8077C67C
s32 fn_3_13D5E8(void* a, void* b) {
    f32 c = 100.0f;
    f32 y = *(f32*)b;
    f32 x = *(f32*)a;
    return (s32)(c * x - c * y);
}

// .text:0x0013D618 size:0x408 mapped:0x8077C6AC
// NONMATCHING 94%: the 4.0f/0.15f constants are hoisted out of the runner loop (the original reloads them)
#if NONMATCHING
// Shortest distance (and direction, see fn_3_13DA50) from runner idx to base
// position ang, minus the shortest such distance over all active runners.
f32 fn_3_13D618(s8 idx, f32 ang, s8* dir) {
    f32 dist[4];
    f32 best;
    f32 fwd;
    f32 back;
    s8 n;
    s8 j;
    best = fn_3_13DA50(idx, ang, dir);
    n = 0;
    for (j = 0; j < 4; j++) {
        if (REP_MG->characterIndex[j] >= 0 && REP_MG->characterIndex[j] < 4 && REP_MG->_1B15[j] == 0) {
            fn_3_13DC48(j, ang, &fwd, &back);
            dist[n++] = fwd < back ? fwd : back;
        }
    }
    fn_800246D4(fn_3_13DA20, (u8*)dist, (u8*)dist, 4, n);
    return best - dist[0];
}
#endif

// .text:0x0013DA20 size:0x30 mapped:0x8077CAB4
s32 fn_3_13DA20(void* a, void* b) {
    f32 c = 100.0f;
    f32 y = *(f32*)b;
    f32 x = *(f32*)a;
    return (s32)(c * x - c * y);
}

// .text:0x0013DA50 size:0x1F8 mapped:0x8077CAE4
f32 fn_3_13DA50(s8 idx, f32 ang, s8* dir) {
    f32 fwd;
    f32 back;
    fwd = fn_3_13DDE0(g_Runners[idx].fractionalBasesRan, ang, 1);
    if (g_Runners[idx].runningDirectionCode == 3) {
        fwd += lbl_3_rodata_373C;
    }
    back = fn_3_13DDE0(g_Runners[idx].fractionalBasesRan, ang, 0);
    if (g_Runners[idx].runningDirectionCode == 1) {
        back += lbl_3_rodata_373C;
    }
    if (fwd < back) {
        *dir = 1;
        return fwd;
    }
    if (fwd > back) {
        *dir = 3;
        return back;
    }
    *dir = RandomInt_Game(2) ? 1 : 3;
    return fwd;
}

// .text:0x0013DC48 size:0x198 mapped:0x8077CCDC
void fn_3_13DC48(s8 idx, f32 ang, f32* out1, f32* out2) {
    *out1 = fn_3_13DDE0(g_Runners[idx].fractionalBasesRan, ang, 1);
    if (g_Runners[idx].runningDirectionCode == 3) {
        *out1 += lbl_3_rodata_373C;
    }
    *out2 = fn_3_13DDE0(g_Runners[idx].fractionalBasesRan, ang, 0);
    if (g_Runners[idx].runningDirectionCode == 1) {
        *out2 += lbl_3_rodata_373C;
    }
}

// .text:0x0013DDE0 size:0xC4 mapped:0x8077CE74
f32 fn_3_13DDE0(f32 a, f32 b, u8 mode) {
    if (a < 0.0f) {
        a += 4.0f;
    } else if (a >= 4.0f) {
        a -= 4.0f;
    }
    if (b < 0.0f) {
        b += 4.0f;
    } else if (b >= 4.0f) {
        b -= 4.0f;
    }
    if (mode == 1) {
        if (a > b) {
            return (4.0f + b) - a;
        }
        return b - a;
    }
    if (a < b) {
        return (4.0f + a) - b;
    }
    return a - b;
}

// .text:0x0013DEA4 size:0x118 mapped:0x8077CF38
void fn_3_13DEA4(void) {
    RepAISlot* p;
    u32 k;
    RepAISlot* e;
    s16* t;
    s8 i;
    e = &REP_MG->ai[0];
    memset(&REP_MG->pad[0], 0, 0x78);
    i = 0;
    do {
        p = e + i;
        k = REP_MG->aiStrength[i];
        t = &lbl_3_data_2194C[k].min;
        p->timer = RandomInt_Game_Range(t[0], t[1]);
        if (RandomInt_Game(100) < lbl_3_data_2197C[k]) {
            if (lbl_3_data_21980[k] < 8) {
                p->_6 = RandomInt_Game_Range(lbl_3_data_21980[k], 8);
            } else {
                p->_6 = 8;
            }
        } else {
            p->_6 = 0x7F;
        }
        p->reason = 2;
        p->_7 = RandomInt_Game_Range(lbl_3_data_21944[k].min, lbl_3_data_21944[k].max);
        i++;
    } while (i < 4);
}
// .text:0x0013DFBC size:0x1B8 mapped:0x8077D050
// Camera shake callback (installed with fn_800528AC): jitter the eye and target
// by up to +-lbl_3_bss_B794 on the view-space x/y axes for lbl_3_bss_B798[0] frames.
void fn_3_13DFBC(camera_803c639c_s* cam) {
    Vec d;
    Mtx inv;
    s32 range;
    range = (s32)(lbl_3_rodata_3748 * lbl_3_bss_B794);
    d.x = (rand() % range - range / 2) / lbl_3_rodata_3750;
    d.y = (rand() % range - range / 2) / lbl_3_rodata_3750;
    d.z = lbl_3_rodata_3734;
    PSMTXInverse(cam->view, inv);
    PSMTXMultVecSR(inv, &d, &d);
    cam->eye.x += d.x;
    cam->eye.y += d.y;
    cam->eye.z += d.z;
    cam->target.x += d.x;
    cam->target.y += d.y;
    cam->target.z += d.z;
    if (--lbl_3_bss_B798[0] <= 0) {
        lbl_3_bss_B798[0] = 0;
        lbl_3_bss_B794 = lbl_3_rodata_3734;
        fn_800528B4();
    }
}

// .text:0x0013E174 size:0xA8 mapped:0x8077D208
void fn_3_13E174(u8 a) {
    switch (a) {
    case 0:
        lbl_3_bss_B798[0] = (s32)lbl_3_data_218BC[12];
        lbl_3_bss_B794 = lbl_3_data_218BC[14];
        break;
    case 1:
        lbl_3_bss_B798[0] = (s32)lbl_3_data_218BC[13];
        lbl_3_bss_B794 = lbl_3_data_218BC[15];
        break;
    default:
        return;
    }
    fn_800528AC(fn_3_13DFBC);
}
// .text:0x0013E21C size:0x188 mapped:0x8077D2B0
// NONMATCHING 97%: register allocation and prologue scheduling differ in the 4-runner loop
#if NONMATCHING
void fn_3_13E21C(RepTarget* t) {
    s32 hits[4];
    s32* out;
    s32 n;
    s32 i;
    s32 pick;
    f32 d;
    f32 lim;
    lim = lbl_3_data_218BC[11];
    out = hits;
    n = 0;
    for (i = 0; i < 4; i++) {
        hits[i] = 0;
        if (REP_MG->_18FC[i] >= 0) {
            d = t->bases - g_Runners[i].fractionalBasesRan;
            if (d < 0.0f) {
                d += lbl_3_rodata_3738;
            }
            if (d > lbl_3_rodata_3758) {
                d = lbl_3_rodata_3738 - d;
            }
            if (d <= lim) {
                *out++ = i;
                n++;
            }
        }
    }
    if (n != 0) {
        pick = hits[RandomInt_Game(n)];
        REP_MG->_1D74 = pick;
        REP_MG->_1D58 = lbl_3_data_21924[2];
        t->active = 0;
        t->timer = lbl_3_data_21924[0];
        fn_3_90064(0x2F6);
        fn_3_16C394(pick);
        return;
    }
    if (REP_MG->phase != 2 && REP_MG->phase != 3) {
        t->timer--;
    }
    if (t->timer <= 0) {
        t->active = 0;
        t->timer = lbl_3_data_21924[0];
    }
}
#endif

// .text:0x0013E3A4 size:0x2CC mapped:0x8077D438
void fn_3_13E3A4(RepTarget* t) {
    s32 cand[2];
    s32* p;
    s32 last;
    s32 i;
    s32 lo;
    s32 hi;
    f32 f;
    RepRunnerView* r;
    if (REP_MG->_1D74 != -1) {
        if (REP_MG->phase != 2 && REP_MG->phase != 3) {
            REP_MG->_1D58--;
        }
        if (REP_MG->_1D58 <= 0) {
            fn_800115C8(REP_MG->_1D74);
            REP_MG->_1D74 = -1;
        }
    } else {
        t->timer--;
        if (t->timer <= 0) {
            t->active = 1;
            last = 0;
            for (i = 1; i < 4; i++) {
                if (REP_MG->points[last] > REP_MG->points[i]) {
                    last = i;
                }
            }
            r = &g_Runners[last];
            f = r->fractionalBasesRan;
            lo = (s32)f * 10;
            hi = lo + 10;
            if (hi >= 40) {
                hi = 0;
            }
            if ((f32)((s32)(lbl_3_rodata_3728 * f) % 100) < lbl_3_rodata_375C) {
                cand[0] = lo;
                cand[1] = hi;
            } else {
                cand[0] = hi;
                cand[1] = lo;
            }
            p = &cand[0];
            for (i = 0; i < 15; i++) {
                if (REP_MG->_1B20.pos[i] == cand[0]) {
                    p = &cand[1];
                    break;
                }
            }
            t->bases = *p / lbl_3_rodata_3730;
            fn_3_7FED4(&t->pos.x, t->bases, 0.0f);
            memset(&t->vel, 0, sizeof(Vec));
            t->timer = lbl_3_data_21924[1];
        }
    }
}

// .text:0x0013E670 size:0x64 mapped:0x8077D704
void fn_3_13E670(void) {
    RepMinigameView* m = REP_MG;
    if (m->turnOverStatus != 0) {
        m->_1D74 = -1;
        m->target.active = 0;
    } else if (m->target.active != 0) {
        fn_3_13E21C(&m->target);
    } else {
        fn_3_13E3A4(&m->target);
    }
}

// .text:0x0013E6D4 size:0x100 mapped:0x8077D768
void fn_3_13E6D4(void) {
    s16 t;
    u32 i;
    for (i = 15; i < 0x23; i++) {
        if (&REP_MG->itemState[0] != NULL) {
            PSVECAdd(&REP_MG->coinPos[i], &REP_MG->coinVel[i], &REP_MG->coinPos[i]);
            REP_MG->coinVel[i].y = REP_MG->coinVel[i].y + lbl_3_data_2188C[4];
            if (REP_MG->coinPos[i].y < lbl_3_rodata_3760) {
                REP_MG->coinPos[i].y = lbl_3_rodata_3768;
                REP_MG->coinVel[i].x = REP_MG->coinVel[i].x * lbl_3_data_2188C[5];
                REP_MG->coinVel[i].z = REP_MG->coinVel[i].z * lbl_3_data_2188C[5];
                REP_MG->coinVel[i].y = REP_MG->coinVel[i].y * -lbl_3_data_2188C[6];
            }
            t = REP_MG->coinFrames[i] + 1;
            REP_MG->coinFrames[i] = t;
            if (t >= lbl_3_data_218A8) {
                REP_MG->itemState[i] = 0;
            }
        }
    }
}

// Single-precision sin/cos; the original inlines these (each call result is
// rounded to f32 before use).
static inline f32 sinF(f32 x) {
    return sin(x);
}

static inline f32 cosF(f32 x) {
    return cos(x);
}

// .text:0x0013E7D4 size:0x25C mapped:0x8077D868
// Throw out coins from player p's runner: one per two points (at most 5), into
// free slots 15..34, flying in the runner's direction +-45 degrees.
void fn_3_13E7D4(s32 p) {
    RepRunnerView* r;
    s32 n;
    u32 i;
    Vec dir;
    f32 ang;
    f32 speed;
    f32 vy;
    r = &g_Runners[REP_MG->_1900[p]];
    n = REP_MG->points[p] / 2;
    if (n == 0) {
        return;
    }
    if (n > 5) {
        n = 5;
    }
    for (i = 15; i < 35; i++) {
        if (REP_MG->itemState[i] == 1) {
            continue;
        }
        REP_MG->itemState[i] = 1;
        REP_MG->coinPos[i].x = r->pos.x;
        REP_MG->coinPos[i].y = r->pos.y;
        REP_MG->coinPos[i].z = r->pos.z;
        memcpy(&dir, &r->_018, sizeof(Vec));
        dir.y = lbl_3_rodata_3734;
        if (!PSVECMag(&dir)) {
            dir.z = lbl_3_rodata_376C;
        }
        PSVECNormalize(&dir, &dir);
        ang = lbl_3_rodata_3790 * (f32)(lbl_3_rodata_3770 * (lbl_3_rodata_3778 * ((f32)rand() / lbl_3_rodata_3780 - lbl_3_rodata_3788)));
        dir.x = dir.x * cosF(ang) + -dir.z * sinF(ang);
        dir.z = dir.x * sinF(ang) + dir.z * cosF(ang);
        speed = RandomF32_Game_Range(lbl_3_data_2188C[2], lbl_3_data_2188C[3]);
        vy = RandomF32_Game_Range(lbl_3_data_2188C[0], lbl_3_data_2188C[1]);
        REP_MG->coinVel[i].x = speed * dir.x;
        REP_MG->coinVel[i].y = vy;
        REP_MG->coinVel[i].z = speed * dir.z;
        REP_MG->coinFrames[i] = 0;
        if (--n == 0) {
            break;
        }
    }
}

// .text:0x0013EA30 size:0x214 mapped:0x8077DAC4
// Award items lying near a runner: each item on the field goes to a random runner
// within the pickup range of its kind, adding the kind's points.
// NONMATCHING 91%: register allocation and scheduling in the runner loop differ
#if NONMATCHING
void fn_3_13EA30(void) {
    s32 i;
    s32 kind;
    s32 hits[4];
    s32 n;
    u8 type;
    s32* out;
    f32 d;
    s32 j;
    s32 pick;
    for (i = 0; i < 15; i++) {
        type = REP_MG->itemState[i];
        if (type >= 1 && type <= 6) {
            kind = REP_MG->_1B1A[type - 1] - 2;
            out = hits;
            n = 0;
            for (j = 0; j < 4; j++) {
                hits[j] = 0;
                if (REP_MG->_18FC[j] >= 0) {
                    d = REP_MG->itemBases[i] - g_Runners[j].fractionalBasesRan;
                    if (d < lbl_3_rodata_3734) {
                        d += lbl_3_rodata_3738;
                    }
                    if (d > lbl_3_rodata_3758) {
                        d = lbl_3_rodata_3738 - d;
                    }
                    if (d <= lbl_3_data_218BC[8 + kind]) {
                        *out++ = j;
                        n++;
                    }
                }
            }
            if (n != 0) {
                pick = hits[RandomInt_Game(n)];
                REP_MG->points[REP_MG->_18FC[pick]] += lbl_3_data_21884[kind][1];
                type = REP_MG->itemState[i];
                REP_MG->itemState[i] = type + 100;
                fn_3_152AB4(i, pick);
                if (kind == 2) {
                    fn_3_90064(0x2EA);
                    fn_3_90220(g_Runners[pick]._0E2, 0);
                } else {
                    fn_3_90064(0x2DD);
                }
                if (!g_d_GameSettings.exhibitionMatchInd && pick == lbl_3_common_bss_37400.humanPlayer) {
                    fn_3_1608F0(3, kind, 0);
                }
            }
        }
    }
}
#endif

// .text:0x0013EC44 size:0x840 mapped:0x8077DCD8
// Spawn a new group of items of the given type: pick its kind and a free spot on
// the base path, then place the kind's item count there, 0.05 bases apart.
// NONMATCHING 91%: loop shapes and register allocation differ (spawn-slot search, unrolled step pick)
#if NONMATCHING
void fn_3_13EC44(s32 type) {
    s32 occ[4];   // per base: runners (and the target) near it / pair use
    s32 occ2[4];  // per base: the target
    s32 cand[4];
    s32 nSpecial;
    s32 n;
    s32 i;
    s32 b;
    s32 skip;
    s32 r;
    s32 pos;
    s32 count;
    s32 slot;
    s32 k;
    u8* kind;
    for (nSpecial = 0; nSpecial < 6; nSpecial++) {
        if (REP_MG->_1B1A[nSpecial] == 3) {
            break;
        }
    }
    if (REP_MG->_1B20.it._E < 2 && REP_MG->_17C0 > (u32)REP_MG->_18A2_4[REP_MG->_1B20.it._E]) {
        REP_MG->_1B1A[type] = 4;
        count = lbl_3_data_21884[2][0];
        REP_MG->_1B20.it._E++;
    } else if (nSpecial < 6) {
        count = lbl_3_data_21884[0][0];
        REP_MG->_1B1A[type] = 2;
    } else {
        if (REP_MG->_17C0 < 1800) {
            k = 0;
        } else if (REP_MG->_17C0 < 3600) {
            k = 1;
        } else {
            k = 2;
        }
        k = RandomIndexFromWeights(lbl_3_data_2187C[k], 2);
        REP_MG->_1B1A[type] = k + 2;
        count = lbl_3_data_21884[k][0];
    }
    kind = &REP_MG->_1B1A[type];
    for (;;) {
        n = 0;
        if (*kind == 4) {
            for (b = 0; b < 4; b++) {
                occ[b] = 0;
                occ2[b] = 0;
            }
            for (i = 0; i < 4; i++) {
                if (REP_MG->_18FC[i] >= 0) {
                    if (g_Runners[i].runningDirectionCode == 1) {
                        occ[g_Runners[i]._126 & 3]++;
                    } else if (g_Runners[i].runningDirectionCode == 3) {
                        occ[g_Runners[i]._125]++;
                    } else if (g_Runners[i]._068 < lbl_3_rodata_375C) {
                        occ[g_Runners[i]._125]++;
                    } else {
                        occ[g_Runners[i]._125]++;
                    }
                }
            }
            if (REP_MG->target.active != 0) {
                b = (s8)(s32)REP_MG->target.bases;
                occ[b]++;
                occ2[b]++;
            }
            for (b = 0; b < 4; b++) {
                if (occ[b] == 0) {
                    cand[n++] = b;
                }
            }
            if (n != 0) {
                pos = cand[random_fn_3_9EE24(n)] * 10;
            } else {
                for (b = 0; b < 4; b++) {
                    if (occ2[b] == 0) {
                        cand[n++] = b;
                    }
                }
                pos = cand[random_fn_3_9EE24(n)] * 10;
            }
            break;
        }
        for (b = 0; b < 4; b++) {
            occ[b] = 0;
            cand[b] = -1;
            if (REP_MG->_1B20.it.pair[b][1] >= 0) {
                occ[b] = 2;
            } else if (REP_MG->_1B20.it.pair[b][0] >= 0) {
                if (REP_MG->_1B1A[REP_MG->_1B20.it.pair[b][0]] == 3) {
                    occ[b] = 5;
                } else {
                    occ[b] = 1;
                    if (*kind != 3) {
                        cand[n++] = b;
                    }
                }
            } else {
                cand[n++] = b;
            }
        }
        if (*kind == 3) {
            if (n == 0) {
                count = lbl_3_data_21884[0][0];
                *kind = 2;
                continue;
            }
            b = cand[random_fn_3_9EE24(n)];
            pos = random_fn_3_9EE24(6) + b * 10 + 2;
        } else {
            b = cand[random_fn_3_9EE24(n)];
            if (occ[b] == 0) {
                pos = random_fn_3_9EE24(8) + b * 10 + 1;
            } else {
                // Pick a step 1..8 other than the one already used on this base.
                pos = b * 10;
                skip = REP_MG->_1B20.it.pos[REP_MG->_1B20.it.pair[b][0]] % 10;
                r = random_fn_3_9EE24(8) + 1;
                for (k = 0; k < 10; k++) {
                    if (k == skip) {
                        continue;
                    }
                    if (r == 0) {
                        pos += k;
                        break;
                    }
                    r--;
                }
            }
        }
        break;
    }
    if (REP_MG->_1B20.it.pair[pos / 10][0] < 0) {
        REP_MG->_1B20.it.pair[pos / 10][0] = type;
    } else {
        REP_MG->_1B20.it.pair[pos / 10][1] = type;
    }
    REP_MG->_1B20.it.pos[type] = pos;
    pos *= 10;
    slot = 0;
    for (i = 0; i < count; i++) {
        for (; slot < 15; slot++) {
            if (REP_MG->itemState[slot] == 0) {
                REP_MG->itemState[slot] = type + 1;
                REP_MG->itemBases[slot] = pos / lbl_3_rodata_3728;
                REP_MG->coinFrames[slot] = 0;
                fn_3_7FED4(&REP_MG->coinPos[slot].x, REP_MG->itemBases[slot], (pos % 100) / lbl_3_rodata_3728);
                fn_3_1541C4(slot, *kind, &REP_MG->coinPos[slot]);
                break;
            }
        }
        pos += 5;
    }
    if (REP_MG->_1B1A[type] == 4) {
        fn_3_106EB0();
    }
}
#endif

// .text:0x0013F484 size:0x244 mapped:0x8077E518
// Per item type: count down the respawn delay, spawn new items (fn_3_13EC44), or
// once enough items of the type are collected, clear them and start the delay.
void fn_3_13F484(void) {
    s32 k;
    s32 i;
    s32 collected;
    s32 n;
    for (k = 0; k < 6; k++) {
        if (REP_MG->_1B1A[k] == 1) {
            REP_MG->_1B08[k]--;
            if (REP_MG->_1B08[k] <= 0) {
                REP_MG->_1B1A[k] = 0;
            }
        } else if (REP_MG->_1B1A[k] == 0) {
            fn_3_13EC44(k);
        } else {
            collected = k + 101;
            n = 0;
            for (i = 0; i < 15; i++) {
                if (REP_MG->itemState[i] == collected) {
                    n++;
                }
            }
            if (n >= lbl_3_data_21884[REP_MG->_1B1A[k] - 2][0]) {
                for (i = 0; i < 15; i++) {
                    if (REP_MG->itemState[i] == collected) {
                        REP_MG->itemState[i] = 0;
                    }
                }
                REP_MG->_1B1A[k] = 1;
                for (i = 0; i < 4; i++) {
                    if (REP_MG->_1B20.it.pair[i][0] == k) {
                        REP_MG->_1B20.it.pair[i][0] = -1;
                        break;
                    }
                    if (REP_MG->_1B20.it.pair[i][1] == k) {
                        REP_MG->_1B20.it.pair[i][1] = -1;
                        break;
                    }
                }
                REP_MG->_1B08[k] = RandomInt_Game_Range(lbl_3_data_21904[3], lbl_3_data_21904[4]);
            }
        }
    }
}

// .text:0x0013F6C8 size:0x11C mapped:0x8077E75C
// Byte cursors over g_Minigame for coin slots 15..34 (one Vec, s16 and u8 per slot), as the original steps them.
#define COIN_F(a, f) (*(f32*)((a) + OFFSET_OF(RepMinigameView, f)))
void fn_3_13F6C8(void) {
    f32* d;
    u32 i;
    u8* a;
    u8* b;
    u8* c;
    u8* fl;
    s16 t;
    if (REP_MG->turnOverStatus == 0) {
        fn_3_13F484();
        fn_3_13EA30();
        a = (u8*)REP_MG + 15 * sizeof(Vec);
        d = lbl_3_data_2188C;
        b = (u8*)REP_MG + 15 * sizeof(s16);
        c = (u8*)REP_MG + 15;
        fl = REP_MG->itemState;
        for (i = 15; i < 0x23; i++, a += sizeof(Vec), b += sizeof(s16), c += 1) {
            if (fl != NULL) {
                PSVECAdd((Vec*)(a + OFFSET_OF(RepMinigameView, coinPos)), (Vec*)(a + OFFSET_OF(RepMinigameView, coinVel)),
                         (Vec*)(a + OFFSET_OF(RepMinigameView, coinPos)));
                COIN_F(a, coinVel[0].y) = COIN_F(a, coinVel[0].y) + d[4];
                if (COIN_F(a, coinPos[0].y) < lbl_3_rodata_3760) {
                    COIN_F(a, coinPos[0].y) = lbl_3_rodata_3768;
                    COIN_F(a, coinVel[0].x) = COIN_F(a, coinVel[0].x) * d[5];
                    COIN_F(a, coinVel[0].z) = COIN_F(a, coinVel[0].z) * d[5];
                    COIN_F(a, coinVel[0].y) = COIN_F(a, coinVel[0].y) * -d[6];
                }
                t = *(s16*)(b + OFFSET_OF(RepMinigameView, coinFrames)) + 1;
                *(s16*)(b + OFFSET_OF(RepMinigameView, coinFrames)) = t;
                if (t >= lbl_3_data_218A8) {
                    c[OFFSET_OF(RepMinigameView, itemState)] = 0;
                }
            }
        }
    }
}
#undef COIN_F
// .text:0x0013F7E4 size:0xE0 mapped:0x8077E878
void fn_3_13F7E4(void) {
    RepMinigameView* m = REP_MG;
    u8* p;
    s16* q; // byte cursors over g_Minigame, stepped per runner slot
    s32 i;
    if (m->phase != 1) {
        return;
    }
    if (m->frames <= 0) {
        m->_1AFE[0] = 0;
        m->_1AFE[1] = 0;
        m->_1AFE[2] = 0;
        m->_1AFE[3] = 0;
    }
    for (p = (u8*)REP_MG, q = (s16*)REP_MG, i = 0; i < 4; p++, q++, i++) {
        s8 r = *(s8*)(p + OFFSET_OF(RepMinigameView, _1900));
        if (r >= 0) {
            u8 st = g_Runners[r].runningDirectionCode;
            if (st == 1 || st == 3) {
                *(s16*)((u8*)q + OFFSET_OF(RepMinigameView, _1AFE)) += 1;
            }
        }
    }
}
// .text:0x0013F8C4 size:0x360 mapped:0x8077E958
// Phase 4: the ball rolls back to its start position (lbl_3_data_217F8), bouncing.
void fn_3_13F8C4(void) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 s;
    if (REP_MG->frames <= 1) {
        dz = lbl_3_data_217F8[2] - REP_MG->ballPos.z;
        dx = lbl_3_data_217F8[0] - REP_MG->ballPos.x;
        dist = dx * dx + dz * dz;
        REP_SQRTF(dist);
        s = lbl_3_data_218BC[2] / dist;
        REP_MG->ballVel.x = dx * s;
        REP_MG->ballVel.z = dz * s;
        REP_MG->_1AF8 = fn_3_9FB8C(dx, dz);
    }
    dz = lbl_3_data_217F8[2] - REP_MG->ballPos.z;
    dx = lbl_3_data_217F8[0] - REP_MG->ballPos.x;
    dist = dx * dx + dz * dz;
    REP_SQRTF(dist);
    if (dist <= lbl_3_data_218BC[2]) {
        REP_MG->ballPos.x = lbl_3_data_217F8[0];
        REP_MG->ballPos.y = lbl_3_data_217F8[1];
        REP_MG->ballPos.z = lbl_3_data_217F8[2];
        REP_MG->phase = 0;
        REP_MG->frames = 0;
        return;
    }
    REP_MG->ballPos.x += REP_MG->ballVel.x;
    REP_MG->ballPos.y += REP_MG->ballVel.y;
    REP_MG->ballPos.z += REP_MG->ballVel.z;
    if (REP_MG->ballPos.y <= 0.0f) {
        REP_MG->ballPos.y = 0.0f;
        REP_MG->ballVel.y = lbl_3_data_218BC[5];
        fn_8004C094(&REP_MG->ballPos);
        fn_3_90064(0x2DF);
    } else {
        REP_MG->ballVel.y -= lbl_3_data_218BC[6];
    }
}

// .text:0x0013FC24 size:0x660 mapped:0x8077ECB8
// Phase 3: once the marked runners have stopped, throw the ball at each of them
// in turn; a hit shakes the camera, knocks out coins and halves the points.
// NONMATCHING 92%: original jumps into the hit code with a goto; register allocation differs
#if NONMATCHING
void fn_3_13FC24(void) {
    RepRunnerView* r;
    s32 i;
    s32 hit;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 s;
    f32 vy;
    if (REP_MG->_1AFC < 1) {
        for (i = 0; i < 4; i++) {
            if (REP_MG->_1B2F[i] == 1) {
                r = &g_Runners[REP_MG->_1900[i]];
                if (__fabs(r->pos.x - r->prevPos.x) > lbl_3_rodata_3760 || __fabs(r->pos.z - r->prevPos.z) > lbl_3_rodata_3760) {
                    return;
                }
            }
        }
    }
    hit = 0;
    if (++REP_MG->_1AFC <= 1) {
        for (i = 0; i < 4; i++) {
            if (REP_MG->_1B2F[i] == 1) {
                REP_MG->_1B14 = i;
                REP_MG->_1B2F[i] = 0;
                break;
            }
        }
        r = &g_Runners[REP_MG->_1900[i]];
        dz = r->pos.z - REP_MG->ballPos.z;
        dx = r->pos.x - REP_MG->ballPos.x;
        dist = dx * dx + dz * dz;
        REP_SQRTF(dist);
        REP_MG->_1AF8 = fn_3_9FB8C(dx, dz);
        if (dist < lbl_3_data_218BC[0]) {
            REP_MG->ballVel.x = dx;
            REP_MG->ballVel.z = dz;
            hit = 1;
        } else {
            s = lbl_3_data_218BC[1] / dist;
            REP_MG->ballVel.x = dx * s;
            REP_MG->ballVel.z = dz * s;
        }
    }
    if (!hit) {
        vy = REP_MG->ballVel.y;
        r = &g_Runners[REP_MG->_1900[REP_MG->_1B14]];
        REP_MG->ballPos.x += REP_MG->ballVel.x;
        REP_MG->ballPos.y += vy;
        REP_MG->ballPos.z += REP_MG->ballVel.z;
        if (REP_MG->ballPos.y <= lbl_3_rodata_3734) {
            REP_MG->ballPos.y = lbl_3_rodata_3734;
            REP_MG->ballVel.y = lbl_3_data_218BC[4];
            fn_8004C094(&REP_MG->ballPos);
            fn_3_90064(0x2DF);
        } else {
            REP_MG->ballVel.y = vy - lbl_3_data_218BC[6];
            if (vy > lbl_3_rodata_3734 && REP_MG->ballVel.y <= lbl_3_rodata_3734) {
                fn_3_90064(0x2DE);
            }
        }
        dz = r->pos.z - REP_MG->ballPos.z;
        dx = r->pos.x - REP_MG->ballPos.x;
        dist = dx * dx + dz * dz;
        REP_SQRTF(dist);
        if (dist < lbl_3_data_218BC[0]) {
            hit = 1;
        }
    }
    if (!hit) {
        return;
    }
    fn_3_13E174(1);
    REP_MG->_1B15[REP_MG->_1B14] = 1;
    fn_3_7D9DC(REP_MG->_1900[REP_MG->_1B14]);
    fn_3_13E7D4(REP_MG->_1B14);
    if (REP_MG->_1D74 == REP_MG->_1B14) {
        fn_800115C8(REP_MG->_1D74);
        REP_MG->_1D74 = -1;
    }
    REP_MG->points[REP_MG->_1B14] /= 2;
    REP_MG->_1DFC[REP_MG->_1B14] = 1;
    fn_3_6C854(REP_MG->_1B14, 2);
    if (--REP_MG->_1B33 == 0) {
        REP_MG->phase = 4;
        REP_MG->frames = 0;
        REP_MG->_1B14 = -1;
        REP_MG->ballVel.y = lbl_3_data_218BC[5];
        return;
    }
    REP_MG->_1AFC = 0;
}
#endif

// .text:0x00140284 size:0x200 mapped:0x8077F318
void fn_3_140284(void) {
    RepMinigameView* mg = REP_MG;
    u8* flags = mg->_1B2F;
    s32 best;
    s32 who;
    s32 limit;
    s32 i;
    mg->_1E00 = 1;
    best = 0;
    flags[0] = 0xFF;
    who = -1;
    flags[1] = 0xFF;
    flags[2] = 0xFF;
    flags[3] = 0xFF;
    mg->_1B33 = 0;
    if (mg->multiPlayerInd != 0) {
        limit = lbl_3_data_218AC[4][mg->_1A3A];
    } else {
        limit = lbl_3_data_218AC[mg->difficulty][mg->_1A3A];
    }
    for (i = 0; i < 4; i++) {
        if (REP_MG->_1900[i] >= 0 && REP_MG->_1AFE[i] > best) {
            best = REP_MG->_1AFE[i];
            who = i;
        }
    }
    if (who >= 0 && best * 100 / 60 <= limit) {
        who = -1;
    }
    if (who < 0) {
        REP_MG->phase = 0;
        REP_MG->frames = 0;
        return;
    }
    flags[who] = 1;
    mg->_1B33 = 1;
    for (i = who + 1; i < 4; i++) {
        if (REP_MG->_1900[i] >= 0 && REP_MG->_1AFE[who] == REP_MG->_1AFE[i]) {
            REP_MG->_1B2F[i] = 1;
            mg->_1B33++;
        }
    }
    REP_MG->_1AFC = 0;
    REP_MG->phase = 3;
    REP_MG->frames = 0;
}

// .text:0x00140484 size:0x154 mapped:0x8077F518
void fn_3_140484(void) {
    RepMinigameView* m = REP_MG;
    f32 a;
    f32 b;
    f32 c;
    s32 i;
    if (m->turnOverStatus == 0) {
        m->ballPos.y += m->ballVel.y;
        a = m->ballPos.y;
        b = m->ballVel.y;
        if (a <= 0.0f && b < -lbl_3_data_218BC[6]) {
            m->ballVel.y = 0.0f;
            m->ballPos.y = 0.0f;
            fn_8004C094(&m->ballPos);
            fn_3_90064(0x2DF);
            lbl_3_bss_B798[0] = (s32)lbl_3_data_218BC[12];
            lbl_3_bss_B794 = lbl_3_data_218BC[14];
            fn_800528AC(fn_3_13DFBC);
            i = 0;
            do {
                fn_3_6C854(i, 1);
                i++;
            } while (i < 4);
        } else if (a > 0.0f) {
            m->ballVel.y -= lbl_3_data_218BC[6];
        }
        if (REP_MG->frames >= lbl_3_data_21904[9]) {
            REP_MG->phase = 2;
            REP_MG->frames = 0;
            m->ballVel.y = lbl_3_data_218BC[4];
        }
    }
}

// .text:0x001405D8 size:0x11C mapped:0x8077F66C
void fn_3_1405D8(void) {
    s16* tbl;
    u8 sel;
    s16 i;
    s16 rnd;
    RepMinigameView* m = REP_MG;
    s16 v = m->frames;
    s16 t;
    if (v <= 1) {
        if (m->multiPlayerInd != 0) {
            sel = 4;
        } else {
            sel = m->difficulty;
        }
        rnd = RandomInt_Game_Range(0, 1000);
        REP_MG->_1B06 = 0;
        tbl = (s16*)(lbl_3_data_21804 + sel * 0x12);
        do {
            i = REP_MG->_1B06;
            rnd -= tbl[i];
            REP_MG->_1B06 = ++i;
        } while (rnd > 0 && tbl[i] >= 0);
        t = REP_MG->_1B06 * 0x78;
        REP_MG->_1B06 = t;
        t = t - 0x30;
        REP_MG->_1B06 = t;
        fn_3_157DB8(t);
    } else {
        m->_1AF8 = 0xE00;
        if (v >= m->_1B06) {
            m->phase = 1;
            m->frames = 0;
            m->ballVel.y = lbl_3_data_218BC[3];
            fn_3_14C904();
            fn_3_90064(0x2E0);
        }
    }
}

// .text:0x001406F4 size:0x2B8
void fn_3_1406F4(void) {
    RepMinigameView* a = REP_MG;
    RepMinigameView* m;
    s16 rnd;
    s16* tbl;
    u8 sel;
    s16 i;
    s16 t;
    s16 v;
    f32 x;
    f32 y;
    s32 k;
    if (a->frames < 0x7FFE) {
        a->frames = a->frames + 1;
    } else {
        a->frames = 0x7FFF;
    }
    m = REP_MG;
    switch (m->phase) {
    case 0:
        v = a->frames;
        if (v <= 1) {
            if (m->multiPlayerInd != 0) {
                sel = 4;
            } else {
                sel = m->difficulty;
            }
            rnd = RandomInt_Game_Range(0, 1000);
            REP_MG->_1B06 = 0;
            tbl = (s16*)(lbl_3_data_21804 + sel * 0x12);
            do {
                i = REP_MG->_1B06;
                rnd -= tbl[i];
                REP_MG->_1B06 = ++i;
            } while (rnd > 0 && tbl[i] >= 0);
            t = REP_MG->_1B06 * 0x78;
            REP_MG->_1B06 = t;
            t = t - 0x30;
            REP_MG->_1B06 = t;
            fn_3_157DB8(t);
        } else {
            m->_1AF8 = 0xE00;
            if (v >= m->_1B06) {
                m->phase = 1;
                a->frames = 0;
                m->ballVel.y = lbl_3_data_218BC[3];
                fn_3_14C904();
                fn_3_90064(0x2E0);
            }
        }
        break;
    case 1:
        if (m->turnOverStatus == 0) {
            m->ballPos.y += m->ballVel.y;
            x = m->ballPos.y;
            y = m->ballVel.y;
            if (x <= 0.0f && y < -lbl_3_data_218BC[6]) {
                m->ballVel.y = 0.0f;
                m->ballPos.y = 0.0f;
                fn_8004C094(&m->ballPos);
                fn_3_90064(0x2DF);
                lbl_3_bss_B798[0] = (s32)lbl_3_data_218BC[12];
                lbl_3_bss_B794 = lbl_3_data_218BC[14];
                fn_800528AC(fn_3_13DFBC);
                k = 0;
                do {
                    fn_3_6C854(k, 1);
                    k++;
                } while (k < 4);
            } else if (x > 0.0f) {
                m->ballVel.y -= lbl_3_data_218BC[6];
            }
            if (a->frames >= lbl_3_data_21904[9]) {
                m->phase = 2;
                a->frames = 0;
                m->ballVel.y = lbl_3_data_218BC[4];
            }
        }
        break;
    case 2:
        fn_3_140284();
        break;
    case 3:
        fn_3_13FC24();
        break;
    case 4:
        fn_3_13F8C4();
        break;
    }
}

// .text:0x001409AC size:0x220 mapped:0x8077FA40
void fn_3_1409AC(void) {
    RepMinigameView* m;
    u32 i;
    fn_3_DE4FC();
    m = REP_MG;
    if (m->difficulty <= 2 && m->multiPlayerInd == 0) {
        if (m->_18E8[((s8)(u8)m->_1908)] == 1 && m->_19A8 == 0) {
            m->_1A37 = 1;
        } else {
            REP_MG->_1A37 = 2;
        }
    }
    fn_3_5A6D4(0xE);
    m = REP_MG;
    m->_1AF8 = 0;
    m->phase = 0;
    m->ballPos.x = lbl_3_data_217F8[0];
    m->ballPos.y = lbl_3_data_217F8[1];
    m->ballPos.z = lbl_3_data_217F8[2];
    m->ballVel.x = 0.0f;
    m->ballVel.y = 0.0f;
    m->ballVel.z = 0.0f;
    m->frames = 0;
    m->_1AF8 = 0xE00;
    for (i = 0; i < 100; i++) {
        REP_MG->itemState[i] = 0;
        REP_MG->coinFrames[i] = 0;
    }
    REP_MG->_1B1A[0] = 0;
    REP_MG->_1B08[0] = 0;
    REP_MG->_1B1A[1] = 0;
    REP_MG->_1B08[1] = 0;
    REP_MG->_1B1A[2] = 0;
    REP_MG->_1B08[2] = 0;
    REP_MG->_1B1A[3] = 0;
    REP_MG->_1B08[3] = 0;
    REP_MG->_1B1A[4] = 0;
    REP_MG->_1B08[4] = 0;
    REP_MG->_1B1A[5] = 0;
    REP_MG->_1B08[5] = 0;
    REP_MG->_1B20.it.pair[0][0] = -1;
    REP_MG->_1B20.it.pair[0][1] = -1;
    REP_MG->_1B20.it.pair[1][0] = -1;
    REP_MG->_1B20.it.pair[1][1] = -1;
    REP_MG->_1B20.it.pair[2][0] = -1;
    REP_MG->_1B20.it.pair[2][1] = -1;
    REP_MG->_1B20.it.pair[3][0] = -1;
    REP_MG->_1B20.it.pair[3][1] = -1;
    REP_MG->_1B20.pos[14] = 0;
    REP_MG->target.active = 0;
}

// .text:0x00140BCC size:0x114 mapped:0x8077FC60
void fn_3_140BCC(void) {
    RepMinigameView* m = REP_MG;
    RepGameLogicView* g;
    if (m->turnOverStatus == 0) {
        if (m->_17C4 == 0) {
            fn_3_10F550(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
            fn_3_151798();
            fn_3_11F480();
            fn_80011578();
            REP_MG->target.active = 0;
            m->turnOverStatus = 1;
        }
    } else {
        if (m->turnOverStatus == 1) {
            m->turnOverStatus = 2;
            REP_GL->_100 = lbl_3_data_21904[0];
        }
        if (REP_MG->phase != 3) {
            REP_GL->_100 -= 1;
        }
        g = REP_GL;
        if (g->_100 == 7) {
            changeScene(3, 6);
            fn_3_1578F8();
        }
        if (g->_100 <= 0) {
            fn_3_1409AC();
        }
    }
}
// .text:0x00140CE0 size:0x410 mapped:0x8077FD74
// NONMATCHING 91%: register allocation differs around the inlined fn_3_13F7E4/13F6C8/13E670/140BCC
#if NONMATCHING
// Per-frame update of the minigame.
void fn_3_140CE0(void) {
    s8 i;
    if (fn_3_108854() != 0) {
        return;
    }
    if (lbl_3_bss_B791 != 0) {
        lbl_3_bss_B791 = 0;
    }
    if (REP_MG->turnOverStatus == 0) {
        if (++REP_MG->_17C0 >= 3600) {
            REP_MG->_1A3A = 2;
        } else if (REP_MG->_17C0 >= 1800) {
            REP_MG->_1A3A = 1;
        }
    }
    if (REP_MG->_17C4 != 0) {
        REP_MG->_17C4--;
        if (REP_MG->_17C4 < 600 && REP_MG->_17C4 != 0 && REP_MG->_17C4 % 60 == 0) {
            fn_3_90064(lbl_3_data_81FC[0x28]);
        }
    }
    fn_3_13C7BC();
    fn_3_7DD6C();
    i = 0;
    do {
        REP_MG->_1DC0[i] = 0;
        i++;
    } while (i < 4);
    fn_3_13F7E4();
    fn_3_13F6C8();
    fn_3_1406F4();
    fn_3_13E670();
    fn_3_140BCC();
}
#endif

// .text:0x001410F0 size:0x1CC mapped:0x80780184
void fn_3_1410F0(void) {
    RepMinigameView* m;
    u32 i;
    fn_3_DE4FC();
    fn_3_5A6D4(0xE);
    m = REP_MG;
    m->_1AF8 = 0;
    m->phase = 0;
    m->ballPos.x = lbl_3_data_217F8[0];
    m->ballPos.y = lbl_3_data_217F8[1];
    m->ballPos.z = lbl_3_data_217F8[2];
    m->ballVel.x = 0.0f;
    m->ballVel.y = 0.0f;
    m->ballVel.z = 0.0f;
    m->frames = 0;
    m->_1AF8 = 0xE00;
    for (i = 0; i < 100; i++) {
        REP_MG->itemState[i] = 0;
        REP_MG->coinFrames[i] = 0;
    }
    REP_MG->_1B1A[0] = 0;
    REP_MG->_1B08[0] = 0;
    REP_MG->_1B1A[1] = 0;
    REP_MG->_1B08[1] = 0;
    REP_MG->_1B1A[2] = 0;
    REP_MG->_1B08[2] = 0;
    REP_MG->_1B1A[3] = 0;
    REP_MG->_1B08[3] = 0;
    REP_MG->_1B1A[4] = 0;
    REP_MG->_1B08[4] = 0;
    REP_MG->_1B1A[5] = 0;
    REP_MG->_1B08[5] = 0;
    REP_MG->_1B20.it.pair[0][0] = -1;
    REP_MG->_1B20.it.pair[0][1] = -1;
    REP_MG->_1B20.it.pair[1][0] = -1;
    REP_MG->_1B20.it.pair[1][1] = -1;
    REP_MG->_1B20.it.pair[2][0] = -1;
    REP_MG->_1B20.it.pair[2][1] = -1;
    REP_MG->_1B20.it.pair[3][0] = -1;
    REP_MG->_1B20.it.pair[3][1] = -1;
    REP_MG->_1B20.pos[14] = 0;
    REP_MG->target.active = 0;
    fn_80011578();
    fn_3_5A6D4(0xE);
}

// .text:0x001412BC size:0x128 mapped:0x80780350
void fn_3_1412BC(void) {
    fn_3_13DEA4();
    changeScene(1, 6);
    fn_3_5A6D4(2);
}
// .text:0x001413E4 size:0xC8 mapped:0x80780478
void fn_3_1413E4(void) {
    RepGameLogicView* g;
    fn_3_7DD6C();
    g = REP_GL;
    switch (g->_125) {
    case 0:
        fn_3_10F550(2, lbl_3_data_21278[0]);
        changeScene(1, 6);
        REP_GL->_0FE = 0;
        g->_125 = 1;
        break;
    case 1:
        if (g->_0FE > lbl_3_data_21278[0] + lbl_3_data_21278[1]) {
            g->_125 = 2;
        }
        break;
    case 2:
        fn_3_5A6D4(0);
        break;
    }
}
// .text:0x001414AC size:0x580 mapped:0x80780540
// Minigame setup (step 0), then hand over to fn_3_5A6D4(5).
// NONMATCHING 91%: register allocation, stack layout and some store order differ
#if NONMATCHING
void fn_3_1414AC(void) {
    s32 order[4];
    s32 i;
    s8 n;
    s8 p;
    if (REP_GL->_125 == 0) {
        fn_3_59A90();
        REP_GL->_121 = 6;
        REP_MG->_17C0 = 0;
        REP_MG->_1A3A = 0;
        REP_MG->turnOverStatus = 0;
        REP_MG->_1A37 = 0;
        for (i = 0; i < 4; i++) {
            REP_MG->points[i] = 0;
            REP_MG->latestPoints[i] = 0;
            REP_MG->pointsPair[i][0] = 0;
            REP_MG->pointsPair[i][1] = 0;
            REP_MG->slotPlayer[i] = -1;
            REP_MG->playerSlot[i] = -1;
            REP_MG->_18FC[i] = -1;
            REP_MG->_1900[i] = -1;
            REP_MG->_18F0[i] = 1;
        }
        REP_MG->pointsReqToWin = 0;
        REP_MG->currentPlayer = -1;
        REP_MG->rosterID = -1;
        if (REP_MG->multiPlayerInd == 0) {
            REP_MG->_17C4 = lbl_3_data_21874[REP_MG->difficulty] * 60;
            REP_MG->aiStrength[0] = REP_MG->aiStrength[1] = REP_MG->aiStrength[2] = REP_MG->aiStrength[3] =
                lbl_3_data_2127C[REP_MG->gameMode][REP_MG->difficulty];
        } else {
            if (REP_MG->_1A3C != 0) {
                REP_MG->aiStrength[0] = REP_MG->aiStrength[1] = REP_MG->aiStrength[2] = REP_MG->aiStrength[3] =
                    lbl_3_data_2127C[7][0];
            }
            REP_MG->_17C4 = lbl_3_data_21874[4] * 60;
        }
        fn_3_8913C();
        n = 0;
        for (p = 0; p < 4; p++) {
            if (REP_MG->characterIndex[p] >= 0) {
                REP_MG->_18FC[n] = p;
                REP_MG->_1900[p] = n;
                REP_MG->_1AFE[n] = 0;
                REP_MG->points[n] = 0;
                REP_MG->_1B15[p] = 0;
                g_Runners[n]._152 = p;
                order[p] = n;
                fn_3_6D964(p, n);
                g_Runners[n]._123 = 1;
                if (REP_MG->_18D8[p] == 0) {
                    g_Runners[n]._11A = 0;
                } else {
                    g_Runners[n]._11A = 1;
                }
                g_Runners[n]._133 = 0;
                n++;
            }
        }
        if (REP_MG->multiPlayerInd != 0) {
            fn_3_9E078(order, REP_MG->numParticipants, 0);
            for (i = 0; i < 4; i++) {
                if (REP_MG->_18FC[i] >= 0) {
                    fn_3_810C4(i, lbl_3_data_21860[4][order[i]]);
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (REP_MG->_18FC[i] >= 0) {
                    fn_3_810C4(i, lbl_3_data_21860[REP_MG->difficulty][i]);
                }
            }
        }
        minigamesSetSomePointers();
        minigamesGXStuff();
        minigamesSetSomePointers2();
        REP_MG->_1AF8 = 0;
        REP_MG->phase = 0;
        REP_MG->ballPos.x = lbl_3_data_217F8[0];
        REP_MG->ballPos.y = lbl_3_data_217F8[1];
        REP_MG->ballPos.z = lbl_3_data_217F8[2];
        REP_MG->ballVel.x = lbl_3_rodata_3734;
        REP_MG->ballVel.y = lbl_3_rodata_3734;
        REP_MG->ballVel.z = lbl_3_rodata_3734;
        REP_MG->frames = 0;
        REP_MG->_1AF8 = 0xE00;
        fn_3_CC81C();
        g_Ball.pos.z = lbl_3_rodata_3734;
        g_Ball.pos.y = lbl_3_rodata_3734;
        g_Ball.pos.x = lbl_3_rodata_3734;
        lbl_3_bss_B791 = 0;
        lbl_3_data_265F0 = -1;
        for (i = 0; i < 100; i++) {
            REP_MG->itemState[i] = 0;
            REP_MG->coinFrames[i] = 0;
        }
        for (i = 0; i < 6; i++) {
            REP_MG->_1B1A[i] = 0;
            REP_MG->_1B08[i] = 0;
        }
        for (i = 0; i < 4; i++) {
            REP_MG->_1B20.it.pair[i][0] = -1;
            REP_MG->_1B20.it.pair[i][1] = -1;
        }
        REP_MG->_1B20.it._E = 0;
        REP_MG->_18A2_4[0] = RandomInt_Game_Range(lbl_3_data_21904[5], lbl_3_data_21904[6]) * 60;
        REP_MG->_18A2_4[1] = RandomInt_Game_Range(lbl_3_data_21904[7], lbl_3_data_21904[8]) * 60;
        fn_3_F1DC();
        REP_MG->target.active = 0;
        REP_MG->target.timer = lbl_3_data_21924[0];
        REP_MG->_1D74 = -1;
        fn_3_169600();
        REP_GL->_125++;
    } else {
        fn_3_5A6D4(5);
    }
}
#endif

