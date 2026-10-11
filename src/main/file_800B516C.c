#include "main/file_800B516C.h"
#include "Dolphin/os.h"
#include "stl/math.h"

#define ANIM_EPSILON 0.000001f

// Interpolation modes (fields of ANIMAnimTrack.interpolationType).
#define ANIM_INTERP_NONE       0
#define ANIM_INTERP_LINEAR     1
#define ANIM_INTERP_BEZIER     2
#define ANIM_INTERP_HERMITE    3
#define ANIM_INTERP_SQUAD      4
#define ANIM_INTERP_SQUAD_EASE 5
#define ANIM_INTERP_SLERP      6

// Bytes per component for a quantized component type.
static inline u32 GetCompSize(u8 type) {
    switch (type) {
    case ANIM_COMP_U8:
    case ANIM_COMP_S8:
        return 1;
    case ANIM_COMP_U16:
    case ANIM_COMP_S16:
        return 2;
    case ANIM_COMP_F32:
        return 4;
    default:
        return 0;
    }
}

// Fraction of the way from cur to next at the pipe's current time.
static inline f32 GetInterpTime(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next) {
    f32 t;
    f32 elapsed = pipe->time - cur->time;

    if (elapsed == 0.0f) {
        t = 0.0f;
    } else if (next->time > cur->time) {
        t = elapsed / (next->time - cur->time);
    } else if (pipe->currentTrack->animTime >= cur->time) {
        t = 1.0f;
    } else {
        t = elapsed / (pipe->currentTrack->animTime - cur->time);
    }
    return t;
}

// Applies ease-in/ease-out to t (Hermite keys).
static inline f32 EaseTime(f32 t, f32 easeIn, f32 easeOut) {
    f32 sum = easeIn + easeOut;
    f32 inv;
    f32 h;

    if (t != 0.0f && t != 1.0f && sum != 0.0f) {
        if (sum > 1.0f) {
            inv = 1.0f / sum;
            easeIn *= inv;
            easeOut *= inv;
            h = 0.5f - inv;
        } else {
            h = 0.5f - 1.0f / sum;
        }
        if (t < easeIn) {
            t = t * (t * (h / easeIn));
        } else if (t < 1.0f - easeOut) {
            t = h * (2.0f * t - easeIn);
        } else {
            f32 s = 1.0f - t;
            t = 1.0f - s * (s * (h / easeOut));
        }
    }
    return t;
}

// Cubic Bezier between p0 and p1; the control points are stored as offsets from them.
static inline void BezierVec(f32* r, f32* p0, f32* c0, f32* c1, f32* p1, f32 t) {
    f32 t2 = t * t;
    f32 t3t = 3.0f * t;
    f32 t3 = t * t2;
    f32 s = 1.0f - t;
    f32 t3t2 = 3.0f * t2;

    r[0] = s * (t3t2 * (c1[0] + p1[0]) + s * (s * p0[0] + t3t * (c0[0] + p0[0]))) + t3 * p1[0];
    r[1] = s * (t3t2 * (c1[1] + p1[1]) + s * (s * p0[1] + t3t * (c0[1] + p0[1]))) + t3 * p1[1];
    r[2] = s * (t3t2 * (c1[2] + p1[2]) + s * (s * p0[2] + t3t * (c0[2] + p0[2]))) + t3 * p1[2];
}

// Cubic Hermite between p0 and p1 with tangents m0 and m1.
static inline void HermiteVec(f32* r, f32* p0, f32* m0, f32* m1, f32* p1, f32 t) {
    f32 t2 = t * t;
    f32 t3 = t2 * t;
    f32 k = 2.0f * t3 - 3.0f * t2;
    f32 h10 = t3 + (t - 2.0f * t2);
    f32 h11 = -t2 + t3;
    f32 h00 = 1.0f + k;
    f32 h01 = -k;

    r[0] = h00 * p0[0] + h01 * p1[0] + h10 * m0[0] + h11 * m1[0];
    r[1] = h00 * p0[1] + h01 * p1[1] + h10 * m0[1] + h11 * m1[1];
    r[2] = h00 * p0[2] + h01 * p1[2] + h10 * m0[2] + h11 * m1[2];
}

// Spherical linear interpolation (Shoemake). Falls back to lerp when p and q
// are nearly equal, and to a perpendicular quaternion when they are opposite.
static inline void QuatSlerp(Quaternion* p, Quaternion* q, Quaternion* r, f32 t) {
    f32 omega;
    f32 tomega;
    f32 sinom;
    f32 sclp;
    f32 sclq;
    f32 cosom = p->x * q->x + p->y * q->y + p->z * q->z + p->w * q->w;

    if ((1.0f + cosom) > ANIM_EPSILON) {
        if ((1.0f - cosom) > ANIM_EPSILON) {
            omega = acos(cosom);
            tomega = t * omega;
            sinom = 1.0f / (f32)sin(omega);
            sclp = sinom * (f32)sin(omega - tomega);
            sclq = sinom * (f32)sin(tomega);
        } else {
            sclp = 1.0f - t;
            sclq = t;
        }
        r->x = sclp * p->x + sclq * q->x;
        r->y = sclp * p->y + sclq * q->y;
        r->z = sclp * p->z + sclq * q->z;
        r->w = sclp * p->w + sclq * q->w;
    } else {
        r->x = -q->y;
        r->y = q->x;
        r->z = -q->w;
        r->w = q->z;
        omega = HALF_PI * t;
        sclp = sin(HALF_PI - omega);
        sclq = sin(omega);
        r->x = sclp * p->x + sclq * r->x;
        r->y = sclp * p->y + sclq * r->y;
        r->z = sclp * p->z + sclq * r->z;
        r->w = sclp * p->w + sclq * r->w;
    }
}

// .text:0x800B516C size:0x4A0
void Squad(Quaternion* p, Quaternion* a, Quaternion* b, Quaternion* q, Quaternion* r, f32 t) {
    return;
}

// .text:0x800B560C size:0x79C
void GetData(u8 type, void* src, f32* dst, u8 count, f32 scale) {
    u8 i;

    switch (type) {
    case ANIM_COMP_U8:
        for (i = 0; i < count; i++) {
            dst[i] = scale * ((u8*)src)[i];
        }
        break;
    case ANIM_COMP_S8:
        for (i = 0; i < count; i++) {
            dst[i] = scale * ((s8*)src)[i];
        }
        break;
    case ANIM_COMP_U16:
        for (i = 0; i < count; i++) {
            dst[i] = scale * ((u16*)src)[i];
        }
        break;
    case ANIM_COMP_S16:
        for (i = 0; i < count; i++) {
            dst[i] = scale * ((s16*)src)[i];
        }
        break;
    case ANIM_COMP_F32:
        for (i = 0; i < count; i++) {
            dst[i] = ((f32*)src)[i];
        }
        break;
    }
}

// .text:0x800B5DA8 size:0x634
void DoTranslationAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next) {
    return;
}

// .text:0x800B63DC size:0xA30
void DoScaleAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next, u8 unused) {
    return;
}

// .text:0x800B6E0C size:0x3B4
void DoEulerAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next) {
    return;
}

// .text:0x800B71C0 size:0x558
void DoQuatAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next) {
    return;
}

// .text:0x800B7718 size:0x288
void ANIMTick(struct ANIMPipe* pipe, u8 arg1) {
    return;
}

// .text:0x800B79A0 size:0x30
void ANIMBind(struct ANIMPipe* pipe, Control* control, struct ANIMAnimTrack* track, f32 time) {
    if (track != NULL) {
        control->type = 0;
        pipe->control = control;
        pipe->currentTrack = track;
        pipe->time = time;
        pipe->prevTime = time;
        pipe->replaceHierarchyCtrl = track->replaceHierarchyCtrl;
        pipe->keyFrameCache = 0;
    }
}
