#ifndef __GAME_rep_3090_H_
#define __GAME_rep_3090_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"

#include "game/replay_camera.h" /* PathPt, SplineKey, SplineCtrl, the camera view */

/* Replay camera animation file (relocated in place by fn_3_105C84). */
typedef struct ReplayAnimKey { u16 frame; u8 pad2[2]; struct { f32 x, y, z; } pos; f32 a; f32 b; } ReplayAnimKey; /* stride varies by track type */
typedef struct ReplayAnimTrack { s16 parent; u8 pad2[2]; u16 count; u8 type; u8 flags; s32 target; u8 keys[1]; } ReplayAnimTrack; /* keys at 0xC */
typedef struct ReplayAnimKeyF { u16 frame; u8 pad2[2]; f32 f[15]; } ReplayAnimKeyF; /* generic view of a key: groups of Vec3 */
typedef struct ReplayAnim { u8 pad0[4]; u16 numFrames; s16 numTracks; u16* frameTbl; ReplayAnimTrack* tracks[1]; } ReplayAnim;

/* Camera parameters decoded from one camera animation frame (fn_3_1048E0). */
typedef struct CamFrame {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec target;
    /* 0x18 */ Vec up;
    /* 0x24 */ Vec fwd;
    /* 0x30 */ Vec back;
    /* 0x3C */ f32 fov;
    /* 0x40 */ Vec scale;
    /* 0x4C */ f32 rx;
    /* 0x50 */ f32 ry;
    /* 0x54 */ u8 type;
    /* 0x55 */ u8 _55[3];
} CamFrame; /* size 0x58 */

struct CamMtx;

/* Cutscene actor placement (lbl_3_data_1F18C, script commands 0x46/0x63/0x66). */
typedef struct ScenePlacement {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 speed;
    /* 0x10 */ u8 actor;
    /* 0x11 */ u8 _11[3];
} ScenePlacement; /* size 0x14 */

/* Scene task running fn_3_FDA1C (script command 0x5B): loads the fielder models one by one,
   then sets parent->_10 = 1. Only the fields used here. */
typedef struct ModelLoadTask {
    /* 0x00 */ u8 _00[0xC];
    /* 0x0C */ struct SceneTask* parent;
    /* 0x10 */ s16 _10;
    /* 0x12 */ u8 _12[0x1E - 0x12];
    /* 0x1E */ u16 idx;   // fielder whose model is loading
    /* 0x20 */ u8 _20[2];
    /* 0x22 */ s16 state;
} ModelLoadTask;

void fn_3_FC448(void);
void fn_3_FC938(void);
s32 fn_3_FCE38(s32 i, f32 t);
void fn_3_FCEAC(void);
s32 fn_3_FCEB0(f32 t);
void fn_3_FCF20(void);
void fn_3_FCF24(void);
void fn_3_FD408(u32 i, void* out, f32* uv);
void fn_3_FD4DC(void);
void fn_3_FD51C(s32 i);
void fn_3_FD5A8(void);
void fn_3_FD670(void);
s32 fn_3_FD9FC(void);
void fn_3_FDA1C(void);
s32 fn_3_FDB30(void);
s32 fn_3_100018(void);
void fn_3_100038(void);
s32 fn_3_10007C(void);
void fn_3_1000D8(void);
void fn_3_101CC4(void);
void fn_3_103C30(struct Vec* p);
void fn_3_103E7C(f32* p);
void fn_3_1040D8(void);
void fn_3_104338(void);
void fn_3_1045A8(void);
void fn_3_104740(void);
void fn_3_1048E0(ReplayAnim* a, s32 b, s32 c, s32 d, CamFrame* out);
void fn_3_104A3C(void* dst, void* mtx);
void fn_3_104A88(void* dst, void* mtx);
void fn_3_104AD4(void* dst, void* mtx);
void fn_3_104B20(struct Vec* dst, f32 (*src)[4]);
void fn_3_104B3C(ReplayAnim* a, s32 b, s32 c, s32 d, struct CamMtx* m);
void fn_3_1054CC(void);
void fn_3_1054D0(ReplayAnim* anim, u32 key, s16 track);
void fn_3_105A10(f32* out, f32* a, f32* b, f32 t);
void fn_3_105ACC(f32* q, f32 (*out)[4]);
void fn_3_105BD8(struct CamMtx* p);
u32 fn_3_105C28(ReplayAnim* p, u32 key);
void fn_3_105C84(ReplayAnim* p);
void fn_3_105CDC(void);
void fn_3_105E00(s32 x, s32 y, s32 a, s32 b);
void fn_3_106014(f32 x, f32 y, f32 z);
void fn_3_1060D8(void);
s32 fn_3_10617C(s32 idx, s32 j, struct Vec* out);
void fn_3_106270(struct Vec* out);
s32 fn_3_10698C(u32* p);
void* fn_3_1069B0(s32* base, s32 idx);
void fn_3_1069C0(void);
void fn_3_106BA0(void);

#endif // !__GAME_rep_3090_H_
