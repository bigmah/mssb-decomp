#ifndef __CHALLENGE_REP_0610_H__
#define __CHALLENGE_REP_0610_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "C3/control.h"
#include "C3/light.h"
#include "main/file_80011640.h" // CharPart
#include "main/file_80037054.h" // RigidBody
#include "challenge/rep_0010.h"   // ChTaskHeader

// Main challenge-viewer task (fn_1_16978 loader, fn_1_168C8, fn_1_1496C menu).
typedef struct ChMainTask {
    /*0x00*/ ChTaskHeader h; // h.result: loader state
    /*0x14*/ u8 _14[8];
    /*0x1C*/ u32 ticks; // fn_1_135C0 timing (OSGetTick)
    /*0x20*/ u8 page;   // fn_1_1496C menu page
} ChMainTask;

// Script-step task (fn_1_DE1C / fn_1_DF14 / fn_1_E098 / fn_1_D9B8).
typedef struct ChScriptTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ u8 index; // script step being edited / played
    /*0x15*/ u8 step;  // read as s8 for indexing
} ChScriptTask;

// Particle burst task (fn_1_F1D8, queued by fn_1_F0D0).
typedef struct ChBurstTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ u8 _14[0xC];
    /*0x20*/ s32 timer; // frames left
    /*0x24*/ s32 joint; // getAnimRelatedCoordinates joint
} ChBurstTask;

// Fireball task (fn_1_F50C, queued by fn_1_F37C).
typedef struct ChFireballTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ Vec pos;
    /*0x20*/ Vec vel;
    /*0x2C*/ Vec accel;
    /*0x38*/ s32 id;     // fn_8002F258 / fn_8002F1AC emitter id
    /*0x3C*/ u16 timer;  // frames left
    /*0x3E*/ u8 spawn;   // create the emitter on the next frame
    /*0x3F*/ u8 onFeet;  // emit at both feet instead of pos
} ChFireballTask;

// Rigid-body launch task (fn_1_CCC8).
typedef struct ChBodyTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ f32* anim;  // [0] current frame, [1] launch frame
    /*0x18*/ u16 id;
} ChBodyTask;

// Challenge viewer player record (lbl_1_bss_6940.player).
typedef struct ChPlayer {
    /*0x00*/ u8 _00[0x44];
    /*0x44*/ u8 group;   // animation bank (CharActor.banks.b index)
    /*0x45*/ u8 seq;     // sequence in that bank
    /*0x46*/ u8 variant; // model variant
    /*0x47*/ u8 _47;
} ChPlayer; // size: 0x48

// lbl_1_bss_6940: the player record and the parts data its CharActor.part points at.
typedef struct ChPlayerBss {
    /*0x00*/ ChPlayer player[1];
    /*0x48*/ CharPart part[1]; // main/file_80011640.h
    /*0xAC*/ u8 _AC[4];
} ChPlayerBss; // size: 0xB0

// lbl_1_bss_68FC: the scene view matrix and the character shown for each player.
typedef struct ChScene {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ Mtx view;
    /*0x40*/ u8 character[4];
} ChScene; // size: 0x44

// Free/orbit debug camera of the challenge viewer (lbl_1_bss_67E0), driven by fn_1_121D4.
typedef struct ChViewCam {
    /*0x000*/ Mtx view;
    /*0x030*/ Light light; // toggled by the debug menu
    /*0x0F0*/ u16 pitch;
    /*0x0F2*/ u16 yaw;
    /*0x0F4*/ f32 strafe;
    /*0x0F8*/ f32 dist;  // forward speed (mode 0) or orbit distance (mode 1)
    /*0x0FC*/ Vec target;
    /*0x108*/ Vec eye;
    /*0x114*/ s32 mode;  // 0: free fly (fn_1_11F08), 1: orbit (fn_1_11D00)
} ChViewCam; // size: 0x118

typedef struct ChViewer {
    /*0x000*/ ChViewCam cam;
    /*0x118*/ u8 lightOn; // cam.light enabled
    /*0x119*/ u8 _119[3];
} ChViewer;

// One step of the challenge animation script being played/edited (lbl_1_bss_3218, 8 entries).
typedef struct ChallengeStep {
    /* 0x0 */ s16 group;  // < 0: unused slot
    /* 0x2 */ s16 index;
    /* 0x4 */ s16 frame;  // advance when the animation reaches this frame (< 0: on A press)
    /* 0x6 */ s16 sync;
} ChallengeStep;

// One step of a stored animation script (ChScriptRecord.steps).
typedef struct ChScriptStep {
    /* 0x0 */ s8 used;
    /* 0x1 */ s8 sync;
    /* 0x2 */ s16 group;
    /* 0x4 */ s16 index;
    /* 0x6 */ s16 frame; // -2: the animation's length
} ChScriptStep;

// Stored animation script (lbl_1_data_F2F4); a record whose first step is unused ends the list.
typedef struct ChScriptRecord {
    /* 0x00 */ char name[0x10];
    /* 0x10 */ ChScriptStep steps[8];
} ChScriptRecord; // size: 0x50

struct ChDrawMtxNode;

void fn_1_163FC(void);

void fn_1_D2F0(void);

void fn_1_D650(void);

void fn_1_D67C(u8 value);

void fn_1_106B4(void);

void* fn_1_106A4(void);

void fn_1_10670(void);

void fn_1_176EC(u8* object);

u8 fn_1_D638(void);

s32 fn_1_D660(void);

void fn_1_D688(void);

void fn_1_D6B4(void);

const char* fn_1_D6E4(void);

s32 fn_1_160D8(s8 a, s8 b);

void fn_1_116EC(void* object);

void fn_1_14928(void);

void fn_1_148CC(void);

void fn_1_15170(void);

void fn_1_14888(ActorObject* object);

void fn_1_E9F8(GameActor* object, s32 index, s32 count);

void fn_1_10AA4(ActorObject* object, f32 value);

void fn_1_161D0(void);

void* fn_1_16558(s32 group, s32 index);

void fn_1_17954(void);

void fn_1_1073C(CharActor* object);

void fn_1_12F18(struct ChDrawMtxNode* object);

void fn_1_106C4(void);

void fn_1_F2F8(void);

void fn_1_CB9C(s32 reset);

void fn_1_11C98(void);

f32 fn_1_D71C(s32 index);

void fn_1_F040(void);

void fn_1_F6E4(void);

void fn_1_160F8(s32 direction);

void fn_1_D4BC(void);

void fn_1_F0D0(void);

void fn_1_CCC8(void);

void* fn_1_16590(void);
void fn_1_168C8(void);
void fn_1_10560(void* object);
void fn_1_D8A0(void);
void fn_1_CC24(void);
void fn_1_D590(void* row, s32 id, f32 value);

void fn_1_DE1C(void);

void fn_1_D7A4(s32 index);

void fn_1_10CEC(struct ChDrawMtxNode* object);

void fn_1_E8D4(void);

void fn_1_1644C(void);

void fn_1_1347C(void);

void fn_1_17D90(void);

void fn_1_14710(CharActor* object);

void fn_1_14FB8(void);

void fn_1_11D00(ChViewCam* camera);

void fn_1_131E4(void);

void fn_1_11F08(ChViewCam* camera);

void fn_1_165E0(void);

void fn_1_1540C(void);

void fn_1_F798(void* paramsArg, void* typesArg, s32 count);

void fn_1_121D4(ChViewCam* camera);

void fn_1_15CE0(void);

void fn_1_126CC(void);

void fn_1_179CC(void);

void fn_1_12820(void* table, void* matrix);

void fn_1_D13C(void);

void fn_1_D300(CharActor* row);

void fn_1_17B5C(void);

void fn_1_1770C(u8* object);

void fn_1_12F8C(void* table, void* matrix);

void fn_1_EA20(void);

void fn_1_107B8(void);

void fn_1_ECF8(u8 player, u8 group, u8 flag);

void fn_1_CDC8(void);

void fn_1_10044(void);

void fn_1_10E2C(Mtx model, Mtx view, u32 colorX, u32 colorY, u32 colorZ);

void fn_1_C5AC(void);

void fn_1_D9B8(void);

void fn_1_1125C(struct ChDrawMtxNode* object);

void fn_1_FB98(void);

void fn_1_129D0(void);

void fn_1_15760(void);

void fn_1_11714(struct ChDrawMtxNode* object);

void fn_1_1496C(u8* object);

void fn_1_E098(void);

void fn_1_16978(void);

void fn_1_135C0(void);

#endif
