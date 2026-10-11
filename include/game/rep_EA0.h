#ifndef __GAME_rep_EA0_H_
#define __GAME_rep_EA0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_80022DAC.h" // VecQueue
#include "main/file_80024184.h" // TexImage, TexArchive

// Ball trail ("streak") effect drawn behind a hit or pitched ball, plus the
// ball/shadow model updates that go with it (lbl_8036E548.trail).

// One vertex array set + display list drawn by fn_3_67C34.
typedef struct TrailStrip {
    /*0x00*/ void* displayList;
    /*0x04*/ u32 displayListSize;
    /*0x08*/ Vec* positions;  // GX_VA_POS, index8
    /*0x0C*/ void* texCoords; // GX_VA_TEX0, u16 ST pairs
    /*0x10*/ u32* colors;     // GX_VA_CLR0, RGBA8
} TrailStrip; // size: 0x14

// Draw node queued with fn_800A7D4C (lbl_3_data_69A0, one per frame buffer).
typedef struct TrailNode {
    /*0x00*/ u32 link; // set by fn_800A7D4C
    /*0x04*/ void (*draw)(struct TrailNode* node);
    /*0x08*/ TrailStrip* strips[2]; // drawn in this order
} TrailNode; // size: 0x10

// Per trail type parameters (lbl_3_data_6880, indexed by RepTrailWork.type).
typedef struct BallTrailParams {
    /*0x00*/ union {
        s32 index;       // texture index in the archive, until fn_3_6750C runs
        TexImage* image; // NULL: untextured trail
    } tex;
    /*0x04*/ f32 width;
    /*0x08*/ f32 widthRatio; // fn_3_6750C turns it into a ratio of width
    /*0x0C*/ s32 length;     // points kept in the position history
} BallTrailParams; // size: 0x10

// The mesh data for one frame buffer: the trail body and its head cap.
typedef struct TrailMesh {
    /*0x00*/ TrailStrip body;
    /*0x14*/ TrailStrip cap;
} TrailMesh; // size: 0x28

// lbl_3_bss_200: trail effect state.
typedef struct RepTrailWork {
    /*0x0000*/ u8 _0000[0x4];
    /*0x0004*/ u8 _0004[4];            // lbl_3_bss_204 (a separate variable, see rep_EA0.c)
    /*0x0008*/ s32 fadeFrames;
    /*0x000C*/ s32 delay;              // frames before the fade starts (-1: never)
    /*0x0010*/ u8 _0010[0x20 - 0x10];
    /*0x0020*/ u32 capColors[2][8];
    /*0x0060*/ Vec capPositions[2][8];
    /*0x0120*/ u32 colors[2][64];
    /*0x0320*/ Vec positions[2][120];
    /*0x0E60*/ u8 displayListReversed[0x180];
    /*0x0FE0*/ u8 displayList[0x180];
    /*0x1160*/ Vec history[60];
    /*0x1430*/ VecQueue queue;
    /*0x144C*/ TrailMesh meshes[2];
    /*0x149C*/ u8 _149C[4];            // lbl_3_bss_169C (a separate variable, see rep_EA0.c)
    /*0x14A0*/ s32 type;
    /*0x14A4*/ f32 alphaStep;
    /*0x14A8*/ f32 alpha;              // lbl_3_bss_16A8
} RepTrailWork;

// The task running fn_3_678B8 (lbl_803CC1B8 while it runs); only the fields used here.
typedef struct TrailTask {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ Vec* dir; // fixed trail direction, or NULL to follow the trail
    /*0x18*/ Vec dirBuf;
} TrailTask;

// lbl_3_data_6848.
typedef struct TrailShadowData {
    /*0x00*/ f32 shadowOffset[2]; // y, z offset of the bat shadow (fn_3_69184)
    /*0x08*/ f32 _08[4];
    /*0x18*/ u16 texCoords[8][2]; // GX_U16, 14 fractional bits
} TrailShadowData;

// lbl_3_data_6940.
typedef struct TrailCharData {
    /*0x00*/ u8 charTex[0x40];     // per character id: trail texture (+0x21 in the archive)
    /*0x40*/ u8 capDisplayList[0x20];
} TrailCharData;

// lbl_3_common_bss_32724 (GameHudFlags in game/auto_00_00097144_text.h), only the fields used here.
typedef struct TrailHudView {
    /*0x00*/ u8 _00[0xCB];
    /*0xCB*/ u8 trailType;   // ball trail type
    /*0xCC*/ u8 trailActive; // trail being drawn
} TrailHudView;

// lbl_3_common_bss_34C90 (GamePauseState in game/auto_00_00097144_text.h), only the fields used here.
typedef struct TrailPauseView {
    /*0x000*/ u8 _000[0x1D2];
    /*0x1D2*/ u8 state;
} TrailPauseView;

// lbl_3_common_bss_35154, only the fields used here.
typedef struct TrailFadeView {
    /*0x000*/ u8 _000[4];
    /*0x004*/ TexArchive* archive; // effect textures
    /*0x008*/ u8 _008[0x47A - 0x8];
    /*0x47A*/ u16 garlicFrames[2]; // [currentStarSwing != 3]
} TrailFadeView;

// lbl_3_common_bss_350E4, only the fields used here.
typedef struct TrailStadiumView {
    /*0x00*/ u8 _00[0x4C];
    /*0x4C*/ Vec noteBlockPos;
} TrailStadiumView;

// g_Fielders entry (0x268 bytes), only the fields used here.
typedef struct TrailFielder {
    /*0x000*/ u8 _000[0x17A];
    /*0x17A*/ s16 charID;
    /*0x17C*/ u8 _17C[0x268 - 0x17C];
} TrailFielder;

void fn_3_6750C(TexArchive* archive);
void fn_3_675B8(u16 frames);
void fn_3_67620(s32 type, u16 frames);
void fn_3_678B8(void);
void fn_3_67A48(void);
void fn_3_67C34(TrailNode* node);
s32 fn_3_67EF0(VecQueue* queue, s32 maxPoints, Vec* positions, u32* colors, u32 color, Vec* capPositions,
               u32* capColors, Vec* dir, f32 width);
void fn_3_685F0(void);
void fn_3_68BB4(void);
void fn_3_690FC(void);
void fn_3_6916C(void);
void fn_3_69184(void);
void fn_3_692E0(void);
void fn_3_695F8(s32 flag);
void fn_3_697CC(void);

#endif // !__GAME_rep_EA0_H_
