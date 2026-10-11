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

// NONMATCHING 97%: float register allocation only (original also uses f20)
// .text:0x800B516C size:0x4A0
#if NONMATCHING
void Squad(Quaternion* p, Quaternion* a, Quaternion* b, Quaternion* q, Quaternion* r, f32 t) {
    Quaternion pq;
    Quaternion ab;
    f32 t2 = 2.0f * (1.0f - t) * t;

    QuatSlerp(p, q, &pq, t);
    QuatSlerp(a, b, &ab, t);
    QuatSlerp(&pq, &ab, r, t2);
}
#endif

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

// NONMATCHING 82%: result is kept in registers instead of on the stack; (x >> n) & m uses extrwi instead of srawi+clrlwi
// .text:0x800B5DA8 size:0x634
#if NONMATCHING
void DoTranslationAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next) {
    s32 i;
    f32 easeOut;
    f32 easeIn;
    f32 ctrlNext[3];
    f32 ctrlCur[3];
    f32 result[3];
    f32 trans1[3];
    f32 trans0[3];
    u32 vecSize;
    u8 compType;
    u8 interp;
    u32 offset;
    char* data;
    f32 scale;
    f32 t;

    compType = pipe->currentTrack->quantizeInfo >> 4;
    scale = 1.0f / (f32)(1 << (pipe->currentTrack->quantizeInfo & 0xF));
    vecSize = GetCompSize(compType) * 3;

    // Translation follows scale, scale quaternion and rotation in the setting data.
    offset = 0;
    if (pipe->currentTrack->animType & ANIM_SCALE) {
        offset = GetCompSize(compType) * 3;
        if (pipe->currentTrack->animType & ANIM_SCALE_QUAT) {
            offset += GetCompSize(compType) * 4;
        }
    }
    if (pipe->currentTrack->animType & ANIM_ROT_EULER) {
        offset += vecSize;
    }
    if (pipe->currentTrack->animType & ANIM_ROT_QUAT) {
        offset += 8;
    }

    GetData(compType, cur->setting + offset, trans0, 3, scale);
    GetData(compType, next->setting + offset, trans1, 3, scale);

    t = GetInterpTime(pipe, cur, next);

    // Translation follows the scale and rotation tangents in the interpolation data.
    offset = 0;
    if (pipe->currentTrack->animType & ANIM_SCALE) {
        interp = (pipe->currentTrack->interpolationType >> 2) & 3;
        if (interp == ANIM_INTERP_BEZIER) {
            offset = vecSize * 2;
        }
        if (interp == ANIM_INTERP_HERMITE) {
            offset = vecSize * 2 + 4;
        }
    }
    if (pipe->currentTrack->animType & ANIM_ROT_QUAT) {
        interp = (pipe->currentTrack->interpolationType >> 4) & 7;
        if (interp == ANIM_INTERP_SQUAD) {
            offset += 0x10;
        }
        if (interp == ANIM_INTERP_SQUAD_EASE) {
            offset += 0x14;
        }
    } else if (pipe->currentTrack->animType & ANIM_ROT_EULER) {
        interp = (pipe->currentTrack->interpolationType >> 4) & 7;
        if (interp == ANIM_INTERP_BEZIER) {
            offset += vecSize * 2;
        }
        if (interp == ANIM_INTERP_HERMITE) {
            offset += vecSize * 2 + 4;
        }
    }

    switch (pipe->currentTrack->interpolationType & 3) {
    case ANIM_INTERP_NONE:
        for (i = 0; i < 3; i++) {
            result[i] = trans0[i];
        }
        break;
    case ANIM_INTERP_LINEAR:
        for (i = 0; i < 3; i++) {
            result[i] = t * trans1[i] + (1.0f - t) * trans0[i];
        }
        break;
    case ANIM_INTERP_BEZIER:
        GetData(compType, cur->interpolation + (offset + vecSize), ctrlCur, 3, scale);
        GetData(compType, next->interpolation + offset, ctrlNext, 3, scale);
        BezierVec(result, trans0, ctrlCur, ctrlNext, trans1, t);
        break;
    case ANIM_INTERP_HERMITE:
        data = cur->interpolation + (offset + vecSize);
        GetData(compType, data, ctrlCur, 3, scale);
        GetData(lbl_803CBB51, data + (vecSize + 2), &easeIn, 1, lbl_803CBB4C);
        data = next->interpolation + offset;
        GetData(compType, data, ctrlNext, 3, scale);
        GetData(lbl_803CBB51, data + vecSize * 2, &easeOut, 1, lbl_803CBB4C);
        t = EaseTime(t, easeIn, easeOut);
        HermiteVec(result, trans0, ctrlCur, ctrlNext, trans1, t);
        break;
    default:
        OSPanic("animPipe.c", 546, "Unknown pInterpolation pSetting!(未知の補間タイプが指定されています)");
        break;
    }

    CTRLSetTranslation(pipe->control, result[0], result[1], result[2]);
}
#endif

// NONMATCHING 88%: result is kept in registers instead of on the stack; float register allocation
// .text:0x800B63DC size:0xA30
#if NONMATCHING
void DoScaleAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next, u8 unused) {
    s32 i;
    f32 easeOut;
    f32 easeIn;
    Quaternion quatResult = { 0.0f, 0.0f, 0.0f, 1.0f };
    Quaternion quat1 = { 0.0f, 0.0f, 0.0f, 1.0f };
    Quaternion quat0 = { 0.0f, 0.0f, 0.0f, 1.0f };
    f32 ctrlNext[3];
    f32 ctrlCur[3];
    f32 result[3];
    f32 scale1[3];
    f32 scale0[3];
    u32 vecSize;
    u8 compType;
    u8 interp;
    char* data;
    f32 scale;
    f32 t;

    compType = pipe->currentTrack->quantizeInfo >> 4;
    scale = 1.0f / (f32)(1 << (pipe->currentTrack->quantizeInfo & 0xF));
    vecSize = GetCompSize(compType) * 3;

    GetData(compType, cur->setting, scale0, 3, scale);
    GetData(compType, next->setting, scale1, 3, scale);
    if (pipe->currentTrack->animType & ANIM_SCALE_QUAT) {
        GetData(compType, cur->setting + vecSize, &quat0.x, 4, scale);
        GetData(compType, next->setting + vecSize, &quat1.x, 4, scale);
    }

    t = GetInterpTime(pipe, cur, next);

    switch ((pipe->currentTrack->interpolationType >> 2) & 3) {
    case ANIM_INTERP_NONE:
        for (i = 0; i < 3; i++) {
            result[i] = scale0[i];
        }
        if (pipe->currentTrack->animType & ANIM_SCALE_QUAT) {
            quatResult.x = quat0.x;
            quatResult.y = quat0.y;
            quatResult.z = quat0.z;
            quatResult.w = quat0.w;
        }
        break;
    case ANIM_INTERP_LINEAR:
        for (i = 0; i < 3; i++) {
            result[i] = t * scale1[i] + (1.0f - t) * scale0[i];
        }
        if (pipe->currentTrack->animType & ANIM_SCALE_QUAT) {
            QuatSlerp(&quat0, &quat1, &quatResult, t);
        }
        break;
    case ANIM_INTERP_BEZIER:
        GetData(compType, cur->interpolation + vecSize, ctrlCur, 3, scale);
        GetData(compType, next->interpolation, ctrlNext, 3, scale);
        BezierVec(result, scale0, ctrlCur, ctrlNext, scale1, t);
        if (pipe->currentTrack->animType & ANIM_SCALE_QUAT) {
            QuatSlerp(&quat0, &quat1, &quatResult, t);
        }
        break;
    case ANIM_INTERP_HERMITE:
        data = cur->interpolation + vecSize;
        GetData(compType, data, ctrlCur, 3, scale);
        GetData(lbl_803CBB51, data + (vecSize + 2), &easeIn, 1, lbl_803CBB4C);
        GetData(compType, next->interpolation, ctrlNext, 3, scale);
        GetData(lbl_803CBB51, next->interpolation + vecSize * 2, &easeOut, 1, lbl_803CBB4C);
        t = EaseTime(t, easeIn, easeOut);
        HermiteVec(result, scale0, ctrlCur, ctrlNext, scale1, t);
        if (pipe->currentTrack->animType & ANIM_SCALE_QUAT) {
            QuatSlerp(&quat0, &quat1, &quatResult, t);
        }
        break;
    default:
        OSPanic("animPipe.c", 424, "Unknown pInterpolation pSetting!(未知の補間タイプが指定されています)");
        break;
    }

    CTRLSetScale(pipe->control, result[0], result[1], result[2]);
    CTRL_SetQuatUnk(pipe->control, quatResult.x, quatResult.y, quatResult.z, quatResult.w);
}
#endif

// NONMATCHING 86%: Bezier scheduling, keyframe-time compare operand order, f5/f6 swap
// .text:0x800B6E0C size:0x3B4
#if NONMATCHING
void DoEulerAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next) {
    f32 rot0[3];
    f32 rot1[3];
    f32 result[3];
    f32 ctrlCur[3];
    f32 ctrlNext[3];
    u32 vecSize;
    u8 compType;
    u8 interp;
    u32 offset;
    f32 scale;
    f32 t;
    s32 i;

    compType = pipe->currentTrack->quantizeInfo >> 4;
    scale = 1.0f / (f32)(1 << (pipe->currentTrack->quantizeInfo & 0xF));
    vecSize = GetCompSize(compType) * 3;

    // Euler angles follow the scale in the setting data.
    offset = 0;
    if (pipe->currentTrack->animType & ANIM_SCALE) {
        offset = vecSize;
    }

    GetData(compType, cur->setting + offset, rot0, 3, scale);
    GetData(compType, next->setting + offset, rot1, 3, scale);

    t = GetInterpTime(pipe, cur, next);

    offset = 0;
    if (pipe->currentTrack->animType & ANIM_SCALE) {
        interp = (pipe->currentTrack->interpolationType >> 2) & 3;
        if (interp == ANIM_INTERP_BEZIER) {
            offset = vecSize * 2;
        }
        if (interp == ANIM_INTERP_HERMITE) {
            offset = vecSize * 2 + 4;
        }
    }

    switch ((pipe->currentTrack->interpolationType >> 4) & 7) {
    case ANIM_INTERP_NONE:
        result[0] = rot0[0];
        result[1] = rot0[1];
        result[2] = rot0[2];
        break;
    case ANIM_INTERP_LINEAR:
        // Take the short way around.
        for (i = 0; i < 3; i++) {
            f32 diff = rot0[i] - rot1[i];
            if (diff > 180.0f) {
                rot0[i] -= 360.0f;
            } else if (diff < -180.0f) {
                rot1[i] -= 360.0f;
            }
            result[i] = t * rot1[i] + (1.0f - t) * rot0[i];
        }
        break;
    case ANIM_INTERP_BEZIER:
        GetData(compType, cur->interpolation + (offset + vecSize), ctrlCur, 3, scale);
        GetData(compType, next->interpolation + offset, ctrlNext, 3, scale);
        BezierVec(result, rot0, ctrlCur, ctrlNext, rot1, t);
        break;
    case ANIM_INTERP_HERMITE:
        OSPanic("animPipe.c", 301, "Hermite pInterpolation not yet supported for Euler angles(Hermite補間はオイラー角制御ではサポートされていません)");
        break;
    default:
        OSPanic("animPipe.c", 304, "Unknown pInterpolation pSetting!(未知の補間タイプが指定されています)");
        break;
    }

    CTRLSetRotation(pipe->control, result[0], result[1], result[2]);
}
#endif

// NONMATCHING 91%: keyframe-time compare branch shape, float register allocation
// .text:0x800B71C0 size:0x558
#if NONMATCHING
void DoQuatAnimation(struct ANIMPipe* pipe, KeyFrame* cur, KeyFrame* next) {
    Quaternion result;
    Quaternion quat0;
    Quaternion quat1;
    Quaternion ctrlCur;
    Quaternion ctrlNext;
    f32 easeIn;
    f32 easeOut;
    u32 vecSize;
    u8 compType;
    u8 interp;
    u32 offset;
    f32 t;
    f32 squadT;

    compType = pipe->currentTrack->quantizeInfo >> 4;
    vecSize = GetCompSize(compType) * 3;

    // The quaternion follows the scale and scale quaternion in the setting data.
    offset = 0;
    if (pipe->currentTrack->animType & ANIM_SCALE) {
        offset = GetCompSize(compType) * 3;
        if (pipe->currentTrack->animType & ANIM_SCALE_QUAT) {
            offset += GetCompSize(compType) * 4;
        }
    }

    GetData(lbl_803CBB50, cur->setting + offset, &quat0.x, 4, lbl_803CBB48);
    GetData(lbl_803CBB50, next->setting + offset, &quat1.x, 4, lbl_803CBB48);

    t = GetInterpTime(pipe, cur, next);
    squadT = t;

    offset = 0;
    if (pipe->currentTrack->animType & ANIM_SCALE) {
        interp = (pipe->currentTrack->interpolationType >> 2) & 3;
        if (interp == ANIM_INTERP_BEZIER) {
            offset = vecSize * 2;
        }
        if (interp == ANIM_INTERP_HERMITE) {
            offset = vecSize * 2 + 4;
        }
    }

    switch ((pipe->currentTrack->interpolationType >> 4) & 7) {
    case ANIM_INTERP_NONE:
        result.x = quat0.x;
        result.y = quat0.y;
        result.z = quat0.z;
        result.w = quat0.w;
        break;
    case ANIM_INTERP_SQUAD_EASE:
        GetData(lbl_803CBB51, next->interpolation + (offset + 0x10), &easeOut, 1, lbl_803CBB4C);
        GetData(lbl_803CBB51, cur->interpolation + (offset + 0x12), &easeIn, 1, lbl_803CBB4C);
        t = EaseTime(t, easeIn, easeOut);
        squadT = t;
        // fallthrough
    case ANIM_INTERP_SQUAD:
        GetData(lbl_803CBB50, cur->interpolation + (offset + 8), &ctrlCur.x, 4, lbl_803CBB48);
        GetData(lbl_803CBB50, next->interpolation + offset, &ctrlNext.x, 4, lbl_803CBB48);
        Squad(&quat0, &ctrlCur, &ctrlNext, &quat1, &result, squadT);
        break;
    case ANIM_INTERP_SLERP:
        QuatSlerp(&quat0, &quat1, &result, t);
        break;
    default:
        OSPanic("animPipe.c", 225, "Unknown pInterpolation pSetting!");
        break;
    }

    CTRLSetQuat(pipe->control, result.x, result.y, result.z, result.w);
}
#endif

// .text:0x800B7718 size:0x288
void ANIMTick(struct ANIMPipe* pipe, u8 arg1) {
    KeyFrame* cur;
    KeyFrame* next;
    KeyFrame* frame;
    f32 scale;

    if (pipe == NULL || pipe->currentTrack == NULL) {
        return;
    }

    ANIMGetKeyFrameFromTrack(pipe->currentTrack, pipe->time, &cur, &next, &pipe->keyFrameCache);

    if (pipe->currentTrack->animType & ANIM_MTX) {
        frame = cur;
        scale = 1.0f / (f32)(1 << (pipe->currentTrack->quantizeInfo & 0xF));
        ((MtxPtr)frame->setting)[0][0] *= scale;
        ((MtxPtr)frame->setting)[0][1] *= scale;
        ((MtxPtr)frame->setting)[0][2] *= scale;
        ((MtxPtr)frame->setting)[0][3] *= scale;
        ((MtxPtr)frame->setting)[1][0] *= scale;
        ((MtxPtr)frame->setting)[1][1] *= scale;
        ((MtxPtr)frame->setting)[1][2] *= scale;
        ((MtxPtr)frame->setting)[1][3] *= scale;
        ((MtxPtr)frame->setting)[2][0] *= scale;
        ((MtxPtr)frame->setting)[2][1] *= scale;
        ((MtxPtr)frame->setting)[2][2] *= scale;
        ((MtxPtr)frame->setting)[2][3] *= scale;
        CTRLSetMatrix(pipe->control, (MtxPtr)frame->setting);
        return;
    }

    if (pipe->currentTrack->animType & ANIM_SCALE) {
        DoScaleAnimation(pipe, cur, next, arg1);
    }
    if (pipe->currentTrack->animType & ANIM_ROT_QUAT) {
        DoQuatAnimation(pipe, cur, next);
    } else if (pipe->currentTrack->animType & ANIM_ROT_EULER) {
        DoEulerAnimation(pipe, cur, next);
    }
    if (pipe->currentTrack->animType & ANIM_TRANS) {
        DoTranslationAnimation(pipe, cur, next);
    }

    pipe->prevTime = pipe->time;
    if (pipe->forward == 1) {
        pipe->time += pipe->speed;
        if (pipe->time > pipe->currentTrack->animTime) {
            if (pipe->loop) {
                pipe->time -= pipe->currentTrack->animTime;
            } else {
                pipe->time = pipe->currentTrack->animTime;
            }
        }
    } else {
        pipe->time -= pipe->speed;
        if (pipe->time < 0.0f) {
            if (pipe->loop) {
                pipe->time += pipe->currentTrack->animTime;
            } else {
                pipe->time = 0.0f;
            }
        }
    }
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
