#include "main/file_800639BC.h"
#include "static/GameSettings.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_80008E00.h"
#include "main/file_8000F150.h"
#include "main/file_80069BDC.h"
#include "main/file_800B0724.h"
#include "main/file_800A7C08.h"
#include "main/file_80021308.h"
#include "main/file_80034F50.h"
#include "main/file_8004B284.h"
#include "Unknown/File_0x800a64e0.h"
#include "Dolphin/mtx.h"
#include "string.h"

extern SoundManager lbl_800EF808;
extern AssetLoadInstructions lbl_801092E8; // logo sound data
extern AssetLoadInstructions lbl_80109044; // message table
extern u8 lbl_80109378[]; // TODO type (spani creation desc)
extern void* lbl_803CBD30; // queue node of the logo screen task
extern u16 lbl_803CBD24;

extern u8 lbl_80361B20[0xF8]; // TODO type
extern u8 lbl_800E8754[0x28]; // TODO type
extern u8 lbl_803CB8D0[8];
extern u8 lbl_80108EC4[12];       // character ids to pick from
extern StreamTrack lbl_802E4CE8[16];
extern StreamTrack lbl_8034E478[16];
extern u8 lbl_800E87B4[15][16];   // TODO type: stream file descriptors
extern u8 lbl_800E88A4[16][2];    // stream volumes
extern CharGroupTable lbl_80108EDC;
extern MenuSlotSrc lbl_800E88C4[6][5];
extern MenuSlotSrc lbl_800E8A2C[5];
extern MenuSlotSrc lbl_800E8A68[5];
extern u8 lbl_800E869C[32];
extern u8 lbl_80354720[2][9][4]; // per pick: three copies of the slot index
extern u8 lbl_80108ED0[12];     // captain character ids
extern u8 lbl_8010902C[12];     // class per captain (lbl_80108ED0 order)

extern u8 lbl_803CBD18; // fade-out: step computed
extern u8 lbl_803CBD19; // fade-out: frame counter
extern s16 lbl_803CBD1A;
extern u8 lbl_803CBD1C; // fade-in: step computed
extern u8 lbl_803CBD1D; // fade-in: frame counter
extern u8 lbl_803CBD1E; // fade-in: volume steps per second
extern u8 lbl_803CBD1F; // fade-in: current volume
extern u8 lbl_803CBD20; // fade-out: volume steps per second
extern u8 lbl_80108DB8[0x24]; // character ids in roster order
extern u8 lbl_80108DDC[0x18]; // extra character ids (variants)
extern EffectDesc lbl_80108D48;
extern s32 lbl_803CBD0C;

extern s32 randRange_FUN_80042bf0(s32 lo, s32 hi);
extern void fn_8002B7F8(void* obj, EffectDesc* desc, s32 count);
extern void* ARAMTransfer(AssetLoadInstructions* instr, void* dest, u8 mode, u32 aramAddr);
extern void fn_80034E20(void* task, void* desc);
extern void* fn_80034CEC(void* task);

// .text:0x800639BC size:0x988
void fn_800639BC(void) {
    return;
}

// .text:0x80064344 size:0xEC
void fn_80064344(void* obj, Vec* v) {
    EffectDesc desc;
    f32 scale = 3.0f * PSVECMag(v);

    memcpy(&desc, &lbl_80108D48, sizeof(EffectDesc));
    desc.id = lbl_803CBD0C;
    desc.size[0] *= scale;
    desc.size[1] *= scale;
    desc.size[2] *= scale;
    desc.size[3] *= scale;
    desc.size[4] *= scale;
    desc.size[5] *= scale;
    desc._38 *= scale;
    desc._54[0] *= scale;
    desc._54[1] *= scale;
    desc._54[2] *= scale;
    fn_8002B7F8(obj, &desc, 1);
}

// .text:0x80064430 size:0x104
void fn_80064430(void* obj, s32 count, f32 scale2, f32 scale) {
    EffectDesc desc;

    memcpy(&desc, &lbl_80108D48, sizeof(EffectDesc));
    desc.id = lbl_803CBD0C;
    desc.size[0] *= scale;
    desc.size[1] *= scale;
    desc.size[2] *= scale;
    desc.size[3] *= scale;
    desc.size[4] *= scale;
    desc.size[5] *= scale;
    desc._38 *= scale;
    desc._54[0] *= scale2;
    desc._54[1] *= scale2;
    desc._54[2] *= scale2;
    fn_8002B7F8(obj, &desc, count);
}

// .text:0x80064534 size:0x220
void fn_80064534(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 5; j++) {
            lbl_803616CC.groups[i][j].id = lbl_800E88C4[i][j].id;
            lbl_803616CC.groups[i][j].x = lbl_800E88C4[i][j].x;
            lbl_803616CC.groups[i][j].y = lbl_800E88C4[i][j].y;
        }
    }
    for (j = 0; j < 5; j++) {
        lbl_803616CC.head[j].id = lbl_800E8A2C[j].id;
        lbl_803616CC.head[j].x = lbl_800E8A2C[j].x;
        lbl_803616CC.head[j].y = lbl_800E8A2C[j].y;
    }
    for (j = 0; j < 5; j++) {
        lbl_803616CC.tail[j].id = lbl_800E8A68[j].id;
        lbl_803616CC.tail[j].x = lbl_800E8A68[j].x;
        lbl_803616CC.tail[j].y = lbl_800E8A68[j].y;
    }
    for (i = 0; i < 32; i++) {
        fn_8006C398(&lbl_803616CC.stats[i]);
        lbl_803616CC.stats[i]._14[0] = lbl_800E869C[i];
    }
}

// .text:0x80064754 size:0x8C
s32 translateStarPitchHitIndex(u8 pitch) {
    switch (pitch) {
    case 0: return 6;
    case 1: return 7;
    case 2: return 10;
    case 3: return 11;
    case 4: return 14;
    case 5: return 15;
    case 6: return 16;
    case 7: return 17;
    case 8: return 12;
    case 9: return 13;
    case 10: return 8;
    case 11: return 9;
    }
    return -1;
}

// .text:0x800647E0 size:0x9C
u8 translateStarPitch(u8 star) {
    switch (star) {
    case 0: return 0x85;
    case 1: return 0x87;
    case 2: return 0x91;
    case 3: return 0x93;
    case 4: return 0x99;
    case 5: return 0x9B;
    case 6: return 0x8D;
    case 7: return 0x8F;
    case 8: return 0x89;
    case 9: return 0x8B;
    case 10: return 0x95;
    case 11: return 0x97;
    case 12: return 0xA1;
    case 13: return 0xA0;
    case 14: return 0xA2;
    }
    return star;
}

// .text:0x8006487C size:0x9C
u8 translateStarSwing(u8 star) {
    switch (star) {
    case 0: return 0x84;
    case 1: return 0x86;
    case 2: return 0x90;
    case 3: return 0x92;
    case 4: return 0x98;
    case 5: return 0x9A;
    case 6: return 0x8C;
    case 7: return 0x8E;
    case 8: return 0x88;
    case 9: return 0x8A;
    case 10: return 0x94;
    case 11: return 0x96;
    case 12: return 0x9D;
    case 13: return 0x9E;
    case 14: return 0x9F;
    }
    return star;
}

// .text:0x80064918 size:0x54
u8 fn_80064918(s16 charId) {
    switch (charId) {
    case 0: case 1:
        return 4;
    case 4: case 5: case 11: case 14:
        return 1;
    case 3: case 28: case 33: case 34: case 35: case 36: case 39: case 47:
        return 2;
    case 12: case 16: case 32: case 40: case 44: case 45: case 46: case 48: case 51:
        return 5;
    case 6: case 7: case 8: case 13: case 15: case 18: case 20: case 24: case 25: case 26:
    case 29: case 30: case 31: case 41: case 43:
        return 3;
    }
    return 0;
}

// .text:0x8006496C size:0x50
void fn_8006496C(void) {
    CharSelectState* cs = &lbl_8034E9A0;

    g_d_GameSettings.PlayerPorts[0] = cs->ports[0];
    if (g_d_GameSettings._10 == 0) {
        if (cs->ports[0] == 0) {
            g_d_GameSettings.PlayerPorts[1] = 5;
        } else {
            g_d_GameSettings.PlayerPorts[1] = 4;
        }
    } else {
        g_d_GameSettings.PlayerPorts[1] = cs->ports[1];
    }
}

// .text:0x800649BC size:0x48
void fn_800649BC(void) {
    g_d_GameSettings.home_AwaySetting = randRange_FUN_80042bf0(0, 1);
    lbl_800E8754[0] = 3;
    lbl_800E8754[3] = lbl_803CB8D0[0];
}

// .text:0x80064A04 size:0x13E8
void unsure_FillRosterPositions(void) {
    return;
}

// .text:0x80065DEC size:0x10C0
void characterSelectScreen(void) {
    return;
}

// .text:0x80066EAC size:0x1F4
// NONMATCHING 95%: saved-register assignment of the roster pointers differs
#if NONMATCHING
void fn_80066EAC(u8 team) {
    // The sort pass compares against buf[9] as well (one past the 9 ids); the
    // original buffer is 9 bytes there, so that byte is uninitialised.
    s8 buf[10];
    s32 i;
    s32 j;
    s32 k;
    s16 id;
    u8 chem;
    s8 t;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            id = inMemRoster[team][j].stats.CharID;
            chem = ((u8*)&inMemRoster[team][i])[id + 0x3B]; // chemistry[id]
            if (chem < 90 || chem == 100) {
                buf[j] = -1;
            } else {
                buf[j] = id;
            }
        }
        for (j = 0; j < 9; j++) {
            for (k = 0; k < 10; k++) {
                if (buf[j] > buf[k]) {
                    t = buf[j];
                    buf[j] = buf[k];
                    buf[k] = t;
                }
            }
        }
        memcpy(lbl_8034E9A0.chemPartners[team][i], buf, 9);
    }
}
#endif

// .text:0x800670A0 size:0x15C
void fn_800670A0(u8 team) {
    s32 i;
    s32 sum = 0;
    s32 avg = 0;
    s32 count = 0;
    s8 rating = 0;

    for (i = 0; i < 9; i++) {
        if (lbl_803C6724.rating[team][i] != 0 && lbl_803C6724.picks[team][i] != lbl_8034E9A0.captain[team]) {
            sum += lbl_803C6724.rating[team][i];
            count++;
        }
    }
    if (count != 0) {
        avg = sum / count;
    }
    if (avg >= 70) {
        rating = 5;
    } else if (avg <= 69 && avg >= 55) {
        rating = 4;
    } else if (avg <= 54 && avg >= 35) {
        rating = 3;
    } else if (avg <= 34 && avg >= 15) {
        rating = 2;
    } else if (avg <= 14 && avg > 0) {
        rating = 1;
    }
    lbl_8034E9A0.teamRating[team] = rating;
}

// .text:0x800671FC size:0x68
void fn_800671FC(void) {
    u8 stadium;

    if (lbl_80361B20[0xF5] != 0) {
        stadium = randRange_FUN_80042bf0(0, 5);
    } else {
        do {
            stadium = randRange_FUN_80042bf0(0, 5);
        } while (stadium == 1);
    }
    g_d_GameSettings.StadiumID = stadium;
}

// .text:0x80067264 size:0x360
// NONMATCHING 66%: loop unrolling/scheduling of the class-count loops differs
#if NONMATCHING
u8 fn_80067264(s32 team, s32 captain) {
    s32 counts[4];
    s32 classes[2][9];
    s32 i;
    u8 cls; // uninitialised if the captain is not in lbl_80108ED0 (as in the original)

    counts[0] = 0;
    counts[1] = 0;
    counts[2] = 0;
    counts[3] = 0;
    for (i = 0; i < 9; i++) {
        classes[team][i] = 0;
        classes[team][i] = lbl_8034E9A0.roster[lbl_803C6724.picks[team][i] / 9][lbl_803C6724.picks[team][i] % 9].stats.CharacterClass;
    }
    for (i = 0; i < 12; i++) {
        if (captain == lbl_80108ED0[i]) {
            cls = lbl_8010902C[i];
            break;
        }
    }
    for (i = 0; i < 9; i++) {
        counts[classes[team][i]]++;
    }
    for (i = 0; i < 4; i++) {
        if (counts[cls] <= counts[i] && i != cls) {
            return 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (counts[i] >= 3 && i == cls) {
            return 3;
        }
    }
    return 0;
}
#endif

// .text:0x800675C4 size:0x308
// NONMATCHING 82%: the original addresses lbl_80108ED0/lbl_80108EDC relative to lbl_80108DB8 (data defined in this TU)
#if NONMATCHING
u8 fn_800675C4(s32 team, s32 captain) {
    s32 found[4];
    s32 idx = -1;
    s32 count = 0;
    s32 set;
    s32 k;
    s32 i;
    s32 row;
    s32 m;
    u16 want;

    found[0] = 0;
    found[1] = 0;
    found[2] = 0;
    found[3] = 0;
    for (i = 0; i < 12; i++) {
        if (captain == lbl_80108ED0[i]) {
            idx = i;
            break;
        }
    }
    for (set = 0; set < 2; set++) {
        // Count the set's characters that were picked directly.
        for (k = 0; k < 4; k++) {
            want = lbl_80108EDC.variants[idx][set][k];
            for (i = 0; i < 9; i++) {
                if (lbl_803C6724.picks[team][i] == want) {
                    found[k] = 1;
                    count++;
                }
            }
            lbl_80108EDC.variants[idx][set][k] = want;
        }
        if (count == 4) {
            return set + 1;
        }
        // For the rest, accept any character from the same group.
        for (k = 0; k < 4; k++) {
            if (found[k] == 1) {
                continue;
            }
            want = lbl_80108EDC.variants[idx][set][k];
            for (row = 0; row < 9; row++) {
                for (m = 0; m < 5; m++) {
                    if (want == lbl_80108EDC.groups[row][m]) {
                        goto found_row;
                    }
                }
            }
            row = -1;
        found_row:
            if (row == -1) {
                continue;
            }
            for (m = 1; m < 5; m++) {
                for (i = 0; i < 9; i++) {
                    if (lbl_803C6724.picks[team][i] == lbl_80108EDC.groups[row][m]) {
                        count++;
                        found[k] = 1;
                        if (count == 4) {
                            return set + 1;
                        }
                        goto next;
                    }
                }
            }
        next:;
        }
        found[0] = 0;
        found[1] = 0;
        found[2] = 0;
        found[3] = 0;
        count = 0;
    }
    return 0;
}
#endif

// .text:0x800678CC size:0x1FC
void fn_800678CC(s32 team) {
    s8 idx = -1;
    s32 captain;
    s32 i;
    u8 variant;

    if (g_d_GameSettings.GameModeSelected == 5) {
        if (team == 0) {
            captain = lbl_8034E9A0.captain[team] = gChallengeState._441D;
        } else {
            captain = lbl_8034E9A0.captain[team] = (s8)gChallengeState._441F;
        }
    } else {
        captain = lbl_8034E9A0.captain[team];
    }
    for (i = 0; i < 12; i++) {
        if (captain == lbl_80108ED0[i]) {
            idx = i;
            break;
        }
    }
    variant = fn_800675C4(team, captain);
    if (variant == 0) {
        variant = fn_80067264(team, captain);
        if (variant != 0) {
            lbl_8034E9A0.captainVariant[team] = idx * 4 + (variant - 1);
        } else {
            lbl_8034E9A0.captainVariant[team] = (idx + 1) * 4 - 1;
        }
    } else {
        lbl_8034E9A0.captainVariant[team] = idx * 4 + (variant - 1);
    }
}

// .text:0x80067AC8 size:0x78
s16 fn_80067AC8(s16 id, s8 col) {
    s32 row;
    s32 i;

    for (row = 0; row < 9; row++) {
        for (i = 0; i < 5; i++) {
            if (id == lbl_80108EDC.groups[row][i]) {
                if (col == -1) {
                    return id;
                }
                return lbl_80108EDC.groups[row][col];
            }
            if (lbl_80108EDC.groups[row][i] == -1) {
                break;
            }
        }
    }
    return -1;
}

// .text:0x80067B40 size:0x108
BOOL fn_80067B40(s32 unused, u8 charId, u8 flag) {
    s32 row;
    s32 i;
    s16* group;

    if (charId == -1) {
        return FALSE;
    }
    for (row = 0; row < 9; row++) {
        for (i = 0; i < 5; i++) {
            if (charId == lbl_80108EDC.groups[row][i]) {
                group = lbl_80108EDC.groups[row];
                for (i = 0; i < 5; i++) {
                    if (group[i] != -1 && flag != 2) {
                        lbl_8034E9A0.charFlag[group[i]] = flag;
                    }
                }
                return TRUE;
            }
        }
    }
    return FALSE;
}

// .text:0x80067C48 size:0x328
// NONMATCHING 96%: order of the roster[c / 9][c % 9] address arithmetic differs
#if NONMATCHING
void fn_80067C48(u8 team) {
    u8 order[0x36];
    u8 chem[0x36];
    CharacterStats* captain;
    s32 i;
    s32 j;
    u8 best;
    u8 to;
    u8 tc;

    captain = &lbl_8034E9A0.roster[0][lbl_8034E9A0.captain[team] % 9] + (lbl_8034E9A0.captain[team] / 9) * 9;
    for (i = 0; i < 0x36; i++) {
        chem[i] = ((u8*)captain)[i + 0x3B];
        order[i] = i;
    }
    for (i = 0; i < 0x36; i++) {
        best = chem[i];
        for (j = i + 1; j < 0x36; j++) {
            if (best < chem[j]) {
                tc = chem[i];
                best = chem[j];
                to = order[i];
                chem[i] = chem[j];
                order[i] = order[j];
                chem[j] = tc;
                order[j] = to;
            }
        }
    }
    for (i = 0; i < 0x36; i++) {
        lbl_8034E9A0.chemOrder[team][i] = order[i];
    }
}
#endif

// .text:0x80067F70 size:0x534
// Fills the rest of a CPU team: picks random characters among the 20 with the
// best chemistry with the captain that are still free.
void fn_80067F70(u8 team) {
    s8 buf[0x36];
    s32 i;
    s32 j;
    s32 slot;
    s32 row;
    s32 m;
    s8 r;
    s8 c;
    s8 t;
    s16 g;
    s32 captain;

    captain = lbl_8034E9A0.captain[team];
    lbl_803C6724.picks[team][0] = captain;
    fn_80067C48(team);
    memset(buf, -1, sizeof(buf));
    for (i = 0; i < 0x36; i++) {
        if (lbl_8034E9A0.charFlag[lbl_8034E9A0.chemOrder[team][i]] == 0) {
            buf[i] = lbl_8034E9A0.chemOrder[team][i];
        }
    }
    for (slot = 1; slot < 9; slot++) {
        // Move the remaining candidates to the front.
        for (i = 0; i < 0x36; i++) {
            for (j = i; j < 0x36; j++) {
                if (buf[i] == -1 && buf[j] != -1) {
                    t = buf[i];
                    buf[i] = buf[j];
                    buf[j] = t;
                    break;
                }
            }
        }
        do {
            r = randRange_FUN_80042bf0(0, 19);
            c = buf[r];
        } while (c == -1);
        buf[r] = -1;
        lbl_8034E9A0.charFlag[c] = 1;
        fn_80067B40(team, c, 1);
        // Take the whole group out of the candidates; the pick becomes the group's base character.
        for (row = 0; row < 9; row++) {
            for (m = 0; m < 5; m++) {
                if (c == lbl_80108EDC.groups[row][m]) {
                    c = lbl_80108EDC.groups[row][0];
                    for (m = 0; m < 5; m++) {
                        g = lbl_80108EDC.groups[row][m];
                        if (g != -1) {
                            for (i = 0; i < 0x36; i++) {
                                if (buf[i] == g) {
                                    buf[i] = -1;
                                }
                            }
                        }
                    }
                    goto done;
                }
            }
        }
    done:
        lbl_803C6724.picks[team][slot] = c;
        // roster[c / 9][c % 9].chemistry[captain] (0x3B: offset of chemistry)
        lbl_803C6724.rating[team][slot] = (((u8*)lbl_8034E9A0.roster) + captain)[(c / 9) * sizeof(lbl_8034E9A0.roster[0]) + (c % 9) * sizeof(CharacterStats) + 0x3B];
    }
    for (i = 0; i < 9; i++) {
        lbl_80354720[team][i][0] = lbl_80354720[team][i][1] = lbl_80354720[team][i][2] = i;
    }
    fn_800670A0(team);
}

// .text:0x800684A4 size:0x70
void fn_800684A4(void) {
    s32* cap = lbl_8034E9A0.captain;

    cap[0] = lbl_80108EC4[randRange_FUN_80042bf0(0, 12)];
    do {
        cap[1] = lbl_80108EC4[randRange_FUN_80042bf0(0, 12)];
    } while (cap[0] == cap[1]);
}

// .text:0x80068514 size:0x118
BOOL fn_80068514(u32 frames, u8 target) {
    u8 vol = fn_800A8864() >> 8;

    lbl_803CBD1F = vol;
    if (vol >= target) {
        lbl_803CBD1F = target;
        return FALSE;
    }
    if (lbl_803CBD1C == 0) {
        lbl_803CBD1E = target / (frames / 60);
        if (lbl_803CBD1E > 60) {
            lbl_803CBD1E = 60;
        }
        lbl_803CBD1C = 1;
    }
    if (lbl_803CBD1D % (60 / lbl_803CBD1E) == 0) {
        lbl_803CBD1D = 0;
        lbl_803CBD1F++;
    }
    if (lbl_803CBD1F >= target) {
        lbl_803CBD1D = 0;
        lbl_803CBD1E = 0;
        lbl_803CBD1C = 0;
        fn_800A8878(target, target);
        return FALSE;
    }
    fn_800A8878(lbl_803CBD1F, lbl_803CBD1F);
    lbl_803CBD1D++;
    return TRUE;
}

// .text:0x8006862C size:0xF4
BOOL fn_8006862C(u32 frames, u8 target) {
    u8 vol = fn_800A8864() >> 8;

    if (lbl_803CBD18 == 0) {
        lbl_803CBD20 = vol / (frames / 60);
        if (lbl_803CBD20 > 60) {
            lbl_803CBD20 = 60;
        }
        lbl_803CBD18 = 1;
    }
    if (lbl_803CBD19 % (60 / lbl_803CBD20) == 0) {
        vol--;
        lbl_803CBD19 = 0;
    }
    if (vol <= target || frames == 1) {
        lbl_803CBD19 = 0;
        lbl_803CBD1A = 0;
        lbl_803CBD20 = 0;
        lbl_803CBD18 = 0;
        return FALSE;
    }
    fn_800A8878(vol, vol);
    lbl_803CBD19++;
    return TRUE;
}

// .text:0x80068720 size:0x5C
void fn_80068720(u8 track) {
    if (lbl_800EF808.unk398 != 0) {
        fn_800A86B4(3);
        fn_800A8B78(&lbl_802E4CE8[track]);
    }
}

// .text:0x8006877C size:0xBC
void fn_8006877C(u8 track) {
    if (lbl_800EF808.unk398 != 0) {
        fn_800A8878(lbl_800E88A4[track][0], lbl_800E88A4[track][0]);
        if (track == 12) {
            fn_800A8AB0(0);
        } else {
            fn_800A8AB0(2);
        }
        fn_800A8E30(lbl_800E87B4[track], &lbl_8034E478[track], 0, NULL);
        fn_800A86B4(4);
        fn_800A86B4(1);
    }
}

// .text:0x80068838 size:0xF78
void fn_80068838(void) {
    return;
}

// .text:0x800697B0 size:0xA4
BOOL fn_800697B0(void) {
    switch (lbl_803CBD24) {
    case 0:
        lbl_80366B18.tables[1] = ARAMTransfer(&lbl_80109044, NULL, 1, 0);
        lbl_803CBD24++;
        break;
    case 1:
        if ((s8)lbl_803C6CF8._715 == 1) {
            fn_800111B4(lbl_80366B18.tables[1]);
            lbl_803CBD24 = 0;
            return FALSE;
        }
        break;
    }
    return TRUE;
}

// .text:0x80069854 size:0xA4
void fn_80069854(void) {
    s32 team;
    s32 i;

    for (team = 0; team < 2; team++) {
        for (i = 0; i < 9; i++) {
            if (lbl_8034E9A0.captain[team] == inMemRoster[team][i].stats.CharID) {
                lbl_8034E9A0.captainSlot[team] = i;
            }
        }
    }
}

// .text:0x800698F8 size:0x170
s32 fn_800698F8(s32 charId) {
    s32 i;

    for (i = 0; i < 32; i++) {
        if (lbl_80108DB8[i] == charId) {
            if (i == 17 && lbl_8034E9A0._48AE != 0) {
                i = 32;
            }
            lbl_8034E9A0._48AE = 0;
            return i;
        }
    }
    if (i == 32) {
        for (i = 0; i < 22; i++) {
            if (lbl_80108DDC[i] == charId) {
                switch (i) {
                case 0: case 1:
                    charId = 0x15;
                    break;
                case 2: case 3:
                    charId = 0x16;
                    break;
                case 4: case 5: case 6: case 7:
                    charId = 0xD;
                    break;
                case 8: case 9: case 10:
                    charId = 0x19;
                    break;
                case 11:
                    charId = 0xC;
                    break;
                case 12:
                    charId = 0x14;
                    break;
                case 13: case 14: case 15: case 16:
                    charId = 0x10;
                    break;
                case 17: case 18: case 19:
                    charId = 0x1F;
                    break;
                case 20: case 21:
                    charId = 0x17;
                    break;
                }
                lbl_8034E9A0._48AE = 0;
                return charId;
            }
        }
        if (i == 22) {
            OSPanic("mb_subfunc.c", 0x95, "The character doesn't exist");
        }
    }
    OSPanic("mb_subfunc.c", 0x99, "//OZ 戻り値がありません\n");
    return 0;
}

// .text:0x80069A68 size:0x30
void fn_80069A68(void) {
    fn_80021518(0x35, lbl_800EF808.groups[47]);
}

// .text:0x80069A98 size:0x3C
void fn_80069A98(void) {
    fn_80034CEC(lbl_803CBD30);
    lbl_803CBD30 = NULL;
    lbl_80366158._2A = 2;
}

// .text:0x80069AD4 size:0x34
void fn_80069AD4(void) {
    if (lbl_80366158._2A == 2) {
        fn_800B0A14_removeQueue(&lbl_80366158);
    }
}

// .text:0x80069B08 size:0x60
void fn_80069B08(void) {
    SceneTask* task = lbl_803CC1B8;

    if (lbl_80366158._2A != 0) {
        lbl_80371C30[task->u14.objIdx].obj->_5C = 0;
        lbl_80371C30[task->u14.objIdx].obj->flags |= 2;
        lbl_803CC1B8->func = fn_80069AD4;
    }
}

// .text:0x80069B68 size:0x74
// NONMATCHING 97%: the original called fn_80035838 without its u8 return prototype (cmpwi, no clrlwi.)
#if NONMATCHING
BOOL fn_80069B68(void) {
    if (fn_80035838(&lbl_801092E8, 0x16) != 0) {
        lbl_803CBD30 = fn_800B0A5C_insertQueue(fn_80069B08, lbl_803CC1B8->priority);
        fn_80034E20(lbl_803CBD30, lbl_80109378);
        lbl_80366158._2A = 0;
        return TRUE;
    }
    return FALSE;
}
#endif
