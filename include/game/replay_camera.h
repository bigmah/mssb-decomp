#ifndef __GAME_REPLAY_CAMERA_H_
#define __GAME_REPLAY_CAMERA_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"

/* Replay/cutscene camera view (rep_3090). inMemCamera holds four of these from 0x120 (views[]);
   lbl_3_common_bss_DE94._0000 points at the one being updated. */

/* Replay camera path types. Pointers to arrays of these live in the view. */
typedef struct { struct { f32 x, y, z; } pos; f32 u; f32 v; u8 pad[0x28]; f32 t; } PathPt; /* size 0x40 */
typedef struct { u8 pad0[4]; f32 v[5]; u8 pad18[4]; u32 frame; } SplineKey; /* size 0x20 */
typedef struct { f32 v[5]; u8 pad14[0x34 - 0x14]; } SplineCtrl; /* size 0x34 */

typedef struct { u32 a, b, c; } V3U; /* a Vec copied as three words */

/* Path state at view + 0x1C (fn_3_FD51C clears it). */
typedef struct ReplayCamPath {
    /* 0x00 */ SplineCtrl* ctrl;  // window of 4 spline control points per segment
    /* 0x04 */ s32 nKeys;         // number of spline keys (view + 0x20)
    /* 0x08 */ s32 _08;
    /* 0x0C */ union {
        V3U w;
        Vec v;
    } up; // up vector (0, 1, 0)
    /* 0x18 */ PathPt* pts;       // sampled path (view + 0x34)
    /* 0x1C */ s32 segSamples;    // samples in the current segment
    /* 0x20 */ s32 nPts;          // number of sampled path points
    /* 0x24 */ s32 _24;
    /* 0x28 */ s32 mode;          // 0: cubic B-spline, else Catmull-Rom
    /* 0x2C */ f32 _2C;
    /* 0x30 */ s32 _30;
    /* 0x34 */ s32 _34;
    /* 0x38 */ s32 _38;
    /* 0x3C */ s32 _3C;
    /* 0x40 */ s32 _40;
    /* 0x44 */ f32 _44;
} ReplayCamPath; // size 0x48

struct ReplayAnim;

typedef struct lbl_3_common_bss_DE94_s2 {
    union {
        /* 0x0000 */ s32 _0000; // from lbl_3_data_20E0C[_092C]
        /* 0x0000 */ s32* script; // current script word
    };
    /* 0x0004 */ s32* loopStart; // script command 0x43/0x44
    /* 0x0008 */ s32 _0008;      // wait counter (command 0x03/0x62)
    /* 0x000C */ s32 loopCount;
    /* 0x0010 */ s32 loopIter;
    /* 0x0014 */ s32 _0014;      // wait counter (command 0x17)
    /* 0x0018 */ s32 _0018;      // 1: script ended
    /* 0x001C */ ReplayCamPath path;
    /* 0x0064 */ Vec eye;        // script camera eye
    /* 0x0070 */ u8 _0070[0x88 - 0x70];
    /* 0x0088 */ Vec target;     // script camera look-at
    /* 0x0094 */ u32* animList;  // offsets of the camera animations (relative to the list)
    /* 0x0098 */ Vec* dbgPts;    // debug path points (1000)
    /* 0x009C */ SplineKey* keys;
    /* 0x00A0 */ f32 _00A0;      // field of view
    /* 0x00A4 */ f32 rx;
    /* 0x00A8 */ f32 ry;
    /* 0x00AC */ Vec eyePrev;    // eye smoothing state
    /* 0x00B8 */ Vec eyeSmooth;
    /* 0x00C4 */ Vec tgtPrev;    // look-at smoothing state
    /* 0x00D0 */ Vec tgtSmooth;
    /* 0x00DC */ Vec lastTarget; // tracked target (actor 15 reuses it)
    /* 0x00E8 */ Vec jointHold;  // tracked joint position, held for a few frames
    /* 0x00F4 */ u8 _00F4[0x100 - 0xF4];
    /* 0x0100 */ f32 eyeW[3];    // eye smoothing weights (script command 0x0C)
    /* 0x010C */ f32 tgtW[3];    // look-at smoothing weights (command 0x0D)
    union {
        /* 0x0118 */ s32 _0118;
        /* 0x0118 */ u32 frame;  // animation frame << 16
    };
    /* 0x011C */ u32 frameEnd;   // numFrames << 16
    /* 0x0120 */ s32 nAnims;
    /* 0x0124 */ s32 nSplineKeys;  // spline keys collected (starts at 1; keys[0] is a copy of the first)
    /* 0x0128 */ s32 segLen[0x200]; // frames per spline segment
    /* 0x0928 */ u32 _0928;
    /* 0x092C */ s32 _092C;      // scene index
    /* 0x0930 */ s32 _0930;
    /* 0x0934 */ s32 rand;       // random_fn_3_9EE24(0x10000) (command 0x2E)
    /* 0x0938 */ s32 joint;      // tracked joint (-1: pick from the character)
    /* 0x093C */ s32 jointPrev;
    /* 0x0940 */ s16 anim;       // camera animation index
    /* 0x0942 */ s16 animPrev;
    /* 0x0944 */ s16 _0944;      // state
    /* 0x0946 */ s16 track;      // tracked actor: 0-8 fielder, 9-12 runner, 13 ball, 14 keep, 15 last
    /* 0x0948 */ s16 trackPrev;
    /* 0x094A */ s16 _094A;
    /* 0x094C */ s16 offsetIdx;  // index into lbl_3_data_1DB00
    /* 0x094E */ s16 charPrev;
    /* 0x0950 */ s16 hold;       // frames the joint position has been held
    /* 0x0952 */ s16 _0952;      // frame counter (wraps at 10000)
    // Recorded event frames (script wait commands 0x0F..0x3C).
    /* 0x0954 */ s16 _0954;
    /* 0x0956 */ s16 _0956;
    /* 0x0958 */ s16 _0958;
    /* 0x095A */ s16 _095A;
    /* 0x095C */ s16 _095C;
    /* 0x095E */ s16 _095E;
    /* 0x0960 */ s16 _0960;
    /* 0x0962 */ s16 _0962;
    /* 0x0964 */ s16 _0964[4];
    /* 0x096C */ s16 _096C[4];
    /* 0x0974 */ s16 _0974;
    /* 0x0976 */ s16 _0976;
    /* 0x0978 */ s16 _0978[2];
    /* 0x097C */ s16 _097C;
    /* 0x097E */ s16 _097E[3];
    /* 0x0984 */ s16 _0984;
    /* 0x0986 */ s16 _0986;
    /* 0x0988 */ u16 _0988;      // fade-out active
    /* 0x098A */ u16 _098A;      // fade-in active
    /* 0x098C */ u16 _098C;      // fade-out length in frames
    /* 0x098E */ u16 _098E;      // fade-in length in frames
    /* 0x0990 */ struct ReplayAnim* animData; // current camera animation (relocated)
    /* 0x0994 */ u8 _0994[0x99B - 0x994];
    /* 0x099B */ u8 _099B[4];    // event frames by index (command 0x16)
    /* 0x099F */ u8 _099F;
    /* 0x09A0 */ u8 _09A0[0x9A7 - 0x9A0];
    /* 0x09A7 */ u8 type;        // camera animation type of the current frame
    /* 0x09A8 */ u8 ballCam;     // nonzero: ball-follow mode (ballMode)
    /* 0x09A9 */ u8 ballMode;
    /* 0x09AA */ u8 orbit;       // 1: orbit the eye about the tracked actor
    /* 0x09AB */ u8 _09AB;
    /* 0x09AC */ u8 _09AC;
    /* 0x09AD */ u8 _09AD;       // 1: play the camera animation
    /* 0x09AE */ u8 _09AE;       // 1: run the script
    /* 0x09AF */ u8 _09AF;
    /* 0x09B0 */ u8 _09B0;
    /* 0x09B1 */ u8 loop;        // 1: loop the camera animation
    /* 0x09B2 */ u8 _09B2;
    /* 0x09B3 */ u8 _09B3;
    /* 0x09B4 */ u8 smooth;      // smooth the eye and look-at
    /* 0x09B5 */ u8 lookAtMode;  // 1: type-2 tracks aim at the tracked actor
    /* 0x09B6 */ u8 _09B6;
    /* 0x09B7 */ u8 _09B7;       // nonzero: don't hold the joint position
    /* 0x09B8 */ u8 _09B8;
    /* 0x09B9 */ u8 _09B9;
    /* 0x09BA */ u8 _09BA[2];
} lbl_3_common_bss_DE94_s2; // size 0x9BC

typedef lbl_3_common_bss_DE94_s2 ReplayCamView;

#endif // !__GAME_REPLAY_CAMERA_H_
