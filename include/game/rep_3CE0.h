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

// lbl_3_data_27F10 (addressed through the lbl_3_data_27EC0 base in the original).
typedef struct PlayerMarkerLayout {
    /*0x000*/ s32 _00;
    /*0x004*/ s32 _04;
    /*0x008*/ PlayerMarkerSlot one[1];
    /*0x018*/ PlayerMarkerSlot two[2];
    /*0x038*/ PlayerMarkerSlot three[3];
    /*0x068*/ s32 height; // marker height above the character (x100000)
    /*0x06C*/ PlayerMarkerNode nodes[2]; // per frame buffer (lbl_803CBBC0)
    /*0x1F4*/ Mtx44 orthoProj;
    /*0x234*/ u8 _234[0x250 - 0x234];
    /*0x250*/ u8 clearDL[0x20];   // display list drawing a full-screen quad
    /*0x270*/ u8 clearVerts[0x70]; // its positions (stride 0xC)
} PlayerMarkerLayout; // size: 0x2E0

// lbl_3_data_27EC0 + lbl_3_data_27F10.
typedef struct PlayerMarkerData {
    /*0x000*/ s32 size[3][2];  // marker width/radius per size class (x100000)
    /*0x018*/ u8 sizeClass[0x38]; // per character kind
    /*0x050*/ PlayerMarkerLayout layout;
} PlayerMarkerData;

void fn_3_15FB84(s32 count, ...);
void fn_3_15FF28(PlayerMarkerNode* node);

#endif // !__GAME_rep_3CE0_H_
