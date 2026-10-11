#ifndef __MAIN_FILE_800B516C_H__
#define __MAIN_FILE_800B516C_H__

#include "mssbTypes.h"
#include "Dolphin/os.h"
#include "C3/charPipeline.h"

// animPipe.c: keyframe interpolation for ANIMPipe.

// Component types for quantized keyframe data (high nibble of ANIMAnimTrack.quantizeInfo).
#define ANIM_COMP_U8  0
#define ANIM_COMP_S8  1
#define ANIM_COMP_U16 2
#define ANIM_COMP_S16 3
#define ANIM_COMP_F32 4

// ANIMAnimTrack.animType flags.
#define ANIM_TRANS       0x01
#define ANIM_SCALE       0x02
#define ANIM_ROT_EULER   0x04
#define ANIM_ROT_QUAT    0x08
#define ANIM_MTX         0x10
#define ANIM_SCALE_QUAT  0x20

// Quaternion and ease data are stored as s16 with 1/16384 scale.
extern u8 lbl_803CBB50;  // quaternion component type
extern u8 lbl_803CBB51;  // ease-in/out component type
extern f32 lbl_803CBB48; // quaternion component scale
extern f32 lbl_803CBB4C; // ease-in/out component scale

void Squad(Quaternion* p, Quaternion* a, Quaternion* b, Quaternion* q, Quaternion* r, f32 t);
void GetData(u8 type, void* src, f32* dst, u8 count, f32 scale);
void DoTranslationAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next);
void DoScaleAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next, u8 unused);
void DoEulerAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next);
void DoQuatAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next);

#endif
