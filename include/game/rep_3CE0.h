#ifndef __GAME_rep_3CE0_H_
#define __GAME_rep_3CE0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_800A7C08.h"

// Player marker drawn under and above up to four characters (fn_3_15FB84 fills
// it, fn_3_15FF28 draws it from draw list 11).
typedef struct PlayerMarker {
    /*0x00*/ Vec top;   // ring above the character
    /*0x0C*/ Vec base;  // character position (ground shadow)
    /*0x18*/ f32 width;
    /*0x1C*/ f32 radius;
    /*0x20*/ u32 topColor;
    /*0x24*/ u32 baseColor;
    /*0x28*/ s32 active;
} PlayerMarker; // size: 0x2C

typedef struct PlayerMarkerNode {
    /*0x00*/ DrawCallbackNode hdr; // func = fn_3_15FF28
    /*0x08*/ PlayerMarker markers[4];
    /*0xB8*/ struct TexImage* tex;
    /*0xBC*/ u32 fadeColor;
    /*0xC0*/ s32 count;
} PlayerMarkerNode; // size: 0xC4

// Marker offset for one of several markers on the same character (x100000).
typedef struct PlayerMarkerSlot {
    /*0x0*/ s32 dx;
    /*0x4*/ s32 dy;
    /*0x8*/ u32 topColor;
    /*0xC*/ u32 baseColor;
} PlayerMarkerSlot;

// Fade timing, marker slot offsets and the per-frame-buffer marker nodes (lbl_3_data_27F10).
typedef struct PlayerMarkerLayout {
    /*0x000*/ s32 fadeScale;    // final fade level (FadeState.level)
    /*0x004*/ s32 fadeDuration; // frames
    /*0x008*/ PlayerMarkerSlot one[1];
    /*0x018*/ PlayerMarkerSlot two[2];
    /*0x038*/ PlayerMarkerSlot three[3];
    /*0x068*/ s32 height; // marker height above the character (x100000)
    /*0x06C*/ PlayerMarkerNode nodes[2]; // per frame buffer (lbl_803CBBC0)
} PlayerMarkerLayout; // size: 0x1F4

// Screen-fade / stadium-effect state (lbl_3_common_bss_35154); only the fields used by this unit.
typedef struct FadeState {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ u8* effectFile;
    /*0x008*/ u8 _008[0x3B0 - 0x8];
    /*0x3B0*/ u8 _3B0; // busy (rep_60 waits for it to clear)
    /*0x3B1*/ u8 _3B1[0x3B4 - 0x3B1];
    /*0x3B4*/ struct TexImage* fadeImages; // entries of the stadium's fade texture archive (fn_3_5EC0)
    /*0x3B8*/ u8 _3B8[0x3E0 - 0x3B8];
    /*0x3E0*/ u8 _3E0; // set outside scene 1 (fn_3_567C)
    /*0x3E1*/ u8 _3E1[0x468 - 0x3E1];
    /*0x468*/ s32 level;     // current fade amount (0..fadeScale), drawn as the fade colour
    /*0x46C*/ u8 _46C[4];
    /*0x470*/ u8 active;
    /*0x471*/ u8 done;
    /*0x472*/ u8 count;      // number of entries in ids
    /*0x473*/ u8 ids[6];
    /*0x479*/ u8 disabled;
} FadeState;

extern FadeState lbl_3_common_bss_35154;

void fn_3_15F874(s32 useB);
void fn_3_15F998(void);
void fn_3_15F9AC(void);
void fn_3_15F9C0(void);
void fn_3_15FA58(s32 n, s32* ids);
void fn_3_15FB84(s32 count, ...);
void fn_3_15FF28(PlayerMarkerNode* node);

#endif // !__GAME_rep_3CE0_H_
