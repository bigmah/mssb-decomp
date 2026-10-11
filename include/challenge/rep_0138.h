#ifndef __CHALLENGE_REP_0138_H__
#define __CHALLENGE_REP_0138_H__

#include "mssbTypes.h"
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"

struct DODisplayObj;
struct ActorLayout;

typedef struct ChallengeModelOffsets {
    u32 mainActor;
    u32 secondaryActor;
    u32 effects;
    u32 mainGeometry;
    u32 secondaryGeometry;
    u32 textures;
} ChallengeModelOffsets;

// A static model queued with fn_800A7D4C (same layout as main.dol's StaticModel).
typedef struct ChallengeModel {
    /*0x00*/ void* link;
    /*0x04*/ void (*draw)(struct ChallengeModel* model);
    /*0x08*/ Mtx world;
    /*0x38*/ Mtx camera;
    /*0x68*/ struct ActorLayout* layout;
} ChallengeModel; // size 0x6C

// The running task (lbl_803CC1B8); same layout as main.dol's SceneTask.
typedef struct ChalTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct ChalTask* prev;
    /*0x08*/ struct ChalTask* next;
    /*0x0C*/ struct ChalTask* parent;
    /*0x10*/ s16 state;
    /*0x12*/ u16 priority;
    /*0x14*/ ChallengeModelOffsets* model; // loaded with ARAMTransfer
    /*0x18*/ s16 modelIdx;
} ChalTask;

// Viewer state (lbl_1_common_bss_472B4); fn_1_66C4 clears the first 0x240 bytes.
typedef struct ChallengeWork {
    /*0x000*/ Mtx view;
    /*0x030*/ u16 pitch;
    /*0x032*/ u16 yaw;
    /*0x034*/ f32 strafe;
    /*0x038*/ f32 forward;
    /*0x03C*/ Vec at;  // look-at point
    /*0x048*/ Vec pos; // camera position
    /*0x054*/ f32 zoom;
    /*0x058*/ void* texBank;
    /*0x05C*/ ChallengeModel stage[2];  // per frame buffer (lbl_803CBBC0)
    /*0x134*/ ChallengeModel object[2]; // per frame buffer
    /*0x20C*/ u8 pad20C[0x21C - 0x20C];
    /*0x21C*/ void* heapBuf;
    /*0x220*/ u8 pad220[0x228 - 0x220];
    /*0x228*/ s16 boneCount;
    /*0x22A*/ u16 totalBones;
    /*0x22C*/ s16 drawnBones;
    /*0x22E*/ s16 selBone; // -1: all bones
    /*0x230*/ s8 stageSel;
    /*0x231*/ s8 variantSel;
    /*0x232*/ u8 menuOpen;
    /*0x233*/ s8 menuItem;
    /*0x234*/ u8 _234;
    /*0x235*/ s8 menuActive;
    /*0x236*/ u8 pad236[2];
    /*0x238*/ s8 _238;
    /*0x239*/ u8 _239;
    /*0x23A*/ u16 spin;
    /*0x23C*/ s8 fogItem;
    /*0x23D*/ u8 pad23D[3];
} ChallengeWork; // size 0x240

void fn_1_5540(void);

void fn_1_7848(void);

void fn_1_77EC(ChallengeModel* model);

void fn_1_54E0(MtxPtr view);

void fn_1_786C(void);

void fn_1_78E4(void);

void fn_1_7EF8(void);

void fn_1_7E04(f32 scale);

void fn_1_717C(ChallengeModelOffsets* model);

void fn_1_7280(void);

void fn_1_6578(GXTexObj* obj, void* image, s32 width, s32 height);

void fn_1_66C4(void);

void fn_1_5544(GXTevStageID stage, GXIndTexStageID indStage, GXIndTexMtxID mtx, GXTexCoordID coord, GXTexMapID map);
s32 fn_1_5924(s32 width, s32 x, s32 y, s32 bpp, s32 alt);
void fn_1_8368(void);
void fn_1_5698(void);
void fn_1_7FF8(void);
void fn_1_4E98(struct DODisplayObj* obj, MtxPtr camera);
void fn_1_6050(u16* image, s32 width, s32 height, f32 scale);
void fn_1_73B8(ChallengeModel* model, u8 numLights, ...);
void fn_1_6848(void);
void fn_1_6E14(void);
void fn_1_7960(void);
void fn_1_5AC0(u16* image, s32 width, s32 height, f32 scale);

#endif
