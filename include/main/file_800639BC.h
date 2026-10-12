#ifndef __MAIN_FILE_800639BC_H__
#define __MAIN_FILE_800639BC_H__

#include "mssbTypes.h"

struct SoundGroupRequest;
struct SoundGroupData;
#include "Dolphin/mtx.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_80069BDC.h"
#include "main/menu_globals.h"
#include "main/charsel_state.h"

extern CharSelectState lbl_8034E9A0;

// Team roster selection at 0x803C6724 (size 0x5C).
typedef struct TeamSelect {
    /*0x00*/ u8 _00[2];
    /*0x02*/ s8 picks[2][9]; // roster index (team * 9 + slot) per pick
    /*0x14*/ u8 pos[2][9]; // saved field position per pick
    /*0x26*/ u8 rating[2][9];
    /*0x38*/ u8 _38[0x5C - 0x38];
} TeamSelect; // size: 0x5C

extern TeamSelect lbl_803C6724;


typedef struct MenuSlot {
    /*0x0*/ s32 id;
    /*0x4*/ s16 x;
    /*0x6*/ s16 y;
} MenuSlot; // size: 0x8

// Character-select layout/work data at 0x803616CC (size 0x454).
typedef struct CharSelectLayout {
    /*0x000*/ MenuSlot head[5];
    /*0x028*/ MenuSlot groups[6][5];
    /*0x118*/ MenuSlot tail[5];
    /*0x140*/ StatInput stats[32];
    /*0x400*/ u8 _400[0x454 - 0x400];
} CharSelectLayout; // size: 0x454

extern CharSelectLayout lbl_803616CC;

// Character group table at 0x80108EDC (size 0x11C).
typedef struct CharGroupTable {
    /*0x00*/ s16 groups[9][5];        // character ids that share a model, -1 terminated
    /*0x5A*/ u16 _5A;
    /*0x5C*/ u16 variants[12][2][4];  // per captain (lbl_80108ED0 order), two 4-character sets
} CharGroupTable; // size: 0x11C

// Effect descriptions for fn_8002B7F8 are ParticleParamsE (main/file_800263FC.h).

void fn_80069A68(struct SoundGroupRequest* req, struct SoundGroupData* data); // SoundGroupRequest.onLoaded
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
void fn_80064344(Vec* pos, Vec* v);
void fn_80064430(Vec* pos, u8 count, f32 scale2, f32 scale);
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
void fn_800678CC(s32 team);
void fn_80064534(void);
void fn_80067C48(u8 team);
void fn_80067F70(u8 team);
s32 fn_800639BC(s8 idx, Vec* a, Vec* b);
void fn_80068838(void);
void unsure_FillRosterPositions(u8 team);
void characterSelectScreen(u8 team);

#endif
