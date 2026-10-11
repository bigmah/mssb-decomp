#ifndef __MAIN_FILE_800639BC_H__
#define __MAIN_FILE_800639BC_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/UnknownHomes_Game.h"

// Character-select / team-setup state at 0x8034E9A0 (size 0x4C28).
// Only the fields used so far are named.
typedef struct CharSelectState {
    /*0x0000*/ CharacterStats roster[2][9]; // working copy of the rosters
    /*0x0B40*/ u8 _0B40[0x46E0 - 0xB40];
    /*0x46E0*/ s32 captain[2]; // captain character id per team
    /*0x46E8*/ u8 _46E8[0x46F8 - 0x46E8];
    /*0x46F8*/ u8 ports[2];
    /*0x46FA*/ u8 _46FA[0x4709 - 0x46FA];
    /*0x4709*/ s8 captainSlot[2]; // roster slot of the captain per team
    /*0x470B*/ u8 _470B[0x470D - 0x470B];
    /*0x470D*/ s8 captainVariant[2]; // captain costume/colour index (fn_800678CC)
    /*0x470F*/ s8 teamRating[2]; // 0-5, from the average of fn_800670A0
    /*0x4711*/ u8 _4711[0x4757 - 0x4711];
    /*0x4757*/ u8 charFlag[0x36]; // per character id
    /*0x478D*/ u8 _478D[0x47F9 - 0x478D];
    /*0x47F9*/ s8 chemPartners[2][9][9]; // per player: ids of teammates with good chemistry, sorted
    /*0x489B*/ u8 _489B[0x48AE - 0x489B];
    /*0x48AE*/ u8 _48AE;
    /*0x48AF*/ u8 _48AF[0x4C28 - 0x48AF];
} CharSelectState; // size: 0x4C28

extern CharSelectState lbl_8034E9A0;

// Team roster selection at 0x803C6724 (size 0x5C).
typedef struct TeamSelect {
    /*0x00*/ u8 _00[2];
    /*0x02*/ s8 picks[2][9]; // roster index (team * 9 + slot) per pick
    /*0x14*/ u8 _14[0x26 - 0x14];
    /*0x26*/ u8 rating[2][9];
    /*0x38*/ u8 _38[0x5C - 0x38];
} TeamSelect; // size: 0x5C

extern TeamSelect lbl_803C6724;

// Character group table at 0x80108EDC (size 0x11C).
typedef struct CharGroupTable {
    /*0x00*/ s16 groups[9][5];        // character ids that share a model, -1 terminated
    /*0x5A*/ u16 _5A;
    /*0x5C*/ u16 variants[12][2][4];  // per captain (lbl_80108ED0 order), two 4-character sets
} CharGroupTable; // size: 0x11C

// Particle/effect emitter description passed to fn_8002B7F8 (template at lbl_80108D48).
typedef struct EffectDesc {
    /*0x00*/ s32 id;
    /*0x04*/ s32 _04[4];
    /*0x14*/ f32 size[6];
    /*0x2C*/ s32 _2C[3];
    /*0x38*/ f32 _38;
    /*0x3C*/ s32 _3C;
    /*0x40*/ f32 _40;
    /*0x44*/ s32 _44[4];
    /*0x54*/ f32 _54[3];
    /*0x60*/ s32 _60[4];
} EffectDesc; // size: 0x70

void fn_80069A68(void);
void fn_80069A98(void);
void fn_80069AD4(void);
void fn_80069B08(void);
BOOL fn_80069B68(void);
s32 translateStarPitchHitIndex(u8 pitch);
u8 translateStarPitch(u8 star);
u8 translateStarSwing(u8 star);
u8 fn_80064918(s16 charId);
void fn_8006496C(void);
void fn_800649BC(void);
void fn_800671FC(void);
s16 fn_80067AC8(s16 id, s8 col);
void fn_800684A4(void);
void fn_80068720(u8 track);
void fn_8006877C(u8 track);
void fn_80064344(void* obj, Vec* v);
void fn_80064430(void* obj, s32 count, f32 scale2, f32 scale);
BOOL fn_80068514(u32 frames, u8 target);
BOOL fn_8006862C(u32 frames, u8 target);
BOOL fn_800697B0(void);
void fn_80069854(void);
s32 fn_800698F8(s32 charId);
void fn_800670A0(u8 team);
BOOL fn_80067B40(s32 unused, u8 charId, u8 flag);
void fn_80066EAC(u8 team);
u8 fn_80067264(s32 team, s32 captain);
u8 fn_800675C4(s32 team, s32 captain);

#endif
