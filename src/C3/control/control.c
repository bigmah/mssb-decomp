#include "C3/charPipeline.h"
#include "stl/math.h"
#include "Dolphin/mtxext.h"

void PSMTXMultVecArray(const Mtx m, const Vec *src, Vec *dst, u32 count);

static f32 cosf(f32 v) { return cos(v); }
static f32 sinf(f32 v) { return sin(v); }

void CTRLSetScale(Control *control, f32 x, f32 y, f32 z) {
    control->type |= CTRL_SCALE;
    control->type &= ~(CTRL_MTX);
    control->controlParams.srt.s.x = x;
    control->controlParams.srt.s.y = y;
    control->controlParams.srt.s.z = z;
}

void CTRLSetRotation(Control *control, f32 x, f32 y, f32 z) {
    control->type |= CTRL_ROT_EULER;
    control->type &= ~(CTRL_ROT_QUAT);
    control->type &= ~(CTRL_MTX);
    control->controlParams.srt.r.x = x;
    control->controlParams.srt.r.y = y;
    control->controlParams.srt.r.z = z;
}

void CTRLSetQuat(Control *control, f32 x, f32 y, f32 z, f32 w) {
    control->type |= CTRL_ROT_QUAT;
    control->type &= ~(CTRL_ROT_EULER);
    control->type &= ~(CTRL_MTX);
    control->controlParams.srt.r.x = x;
    control->controlParams.srt.r.y = y;
    control->controlParams.srt.r.z = z;
    control->controlParams.srt.r.w = w;
}

void CTRLSetTranslation(Control *control, f32 x, f32 y, f32 z) {
    control->type |= CTRL_TRANS;
    control->type &= ~(CTRL_MTX);
    control->controlParams.srt.t.x = x;
    control->controlParams.srt.t.y = y;
    control->controlParams.srt.t.z = z;
}

void CTRLSetMatrix(Control *control, MtxPtr m) {
    control->type = CTRL_MTX;
    PSMTXCopy(m, control->controlParams.m);
}

void CTRLGetScale(Control *control, f32 *x, f32 *y, f32 *z) {
    *x = control->controlParams.srt.s.x;
    *y = control->controlParams.srt.s.y;
    *z = control->controlParams.srt.s.z;
}

void CTRLGetRotation(Control *control, f32 *x, f32 *y, f32 *z) {
    *x = control->controlParams.srt.r.x;
    *y = control->controlParams.srt.r.y;
    *z = control->controlParams.srt.r.z;
}

void CTRLGetQuat(Control *control, f32 *x, f32 *y, f32 *z, f32 *w) {
    *x = control->controlParams.srt.r.x;
    *y = control->controlParams.srt.r.y;
    *z = control->controlParams.srt.r.z;
    *w = control->controlParams.srt.r.w;
}

void CTRLGetTranslation(Control *control, f32 *x, f32 *y, f32 *z) {
    *x = control->controlParams.srt.t.x;
    *y = control->controlParams.srt.t.y;
    *z = control->controlParams.srt.t.z;
}

void CTRLBuildMatrix(Control *control, Mtx m) {
    f32 nRad;
    f32 nSin;
    f32 nCos;
    f32 temp;

    Mtx a, b, c, d, e;

    if (control->type & CTRL_MTX) {
        PSMTXCopy(control->controlParams.m, m);
        return;
    }
    PSMTXIdentity(m);
    PSMTXIdentity(a);
    PSMTXIdentity(b);
    PSMTXIdentity(c);
    PSMTXIdentity(d);
    PSMTXIdentity(e);
    if (control->type & CTRL_ROT_QUAT) {
        PSMTXQuat(a, &control->controlParams.srt.r);
    } else if (control->type & CTRL_ROT_EULER) {
        if (0.0f != control->controlParams.srt.r.x) {
            nRad = 0.0174532925f * control->controlParams.srt.r.x;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = 1.0f;
            a[0][1] = 0.0f;
            a[0][2] = 0.0f;
            a[0][3] = 0.0f;
            a[1][0] = 0.0f;
            a[1][1] = nCos;
            a[1][2] = -nSin;
            a[1][3] = 0.0f;
            a[2][0] = 0.0f;
            a[2][1] = nSin;
            a[2][2] = nCos;
            a[2][3] = 0.0f;
        }
        if (0.0f != control->controlParams.srt.r.y) {
            nRad = 0.0174532925f * control->controlParams.srt.r.y;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = nCos;
            a[0][1] = a[2][1] * nSin;
            a[0][2] = a[2][2] * nSin;
            a[2][0] = -nSin;
            a[2][1] = a[2][1] * nCos;
            a[2][2] = a[2][2] * nCos;
        }
        if (0.0f != control->controlParams.srt.r.z) {
            nRad = 0.0174532925f * control->controlParams.srt.r.z;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[1][0] = a[0][0] * nSin;
            a[0][0] = a[0][0] * nCos;
            temp = a[1][1];
            a[1][1] = (a[0][1] * nSin) + (a[1][1] * nCos);
            a[0][1] = (a[0][1] * nCos) - (temp * nSin);
            temp = m[1][2];
            a[1][2] = (a[0][2] * nSin) + (a[1][2] * nCos);
            a[0][2] = (a[0][2] * nCos) - (temp * nSin);
        }
    }
    
    if (control->type & CTRL_SCALE) {
        b[0][0] = control->controlParams.srt.s.x;
        b[1][1] = control->controlParams.srt.s.y;
        b[2][2] = control->controlParams.srt.s.z;
        if (control->type & CTRL_SCALE_QUAT) {
            PSMTXQuat(c, (Quaternion*)&control->controlParams.q);
            PSMTXInverse(c,d);
        }
    }
    if (control->type & CTRL_TRANS) {
        a[0][3] = control->controlParams.srt.t.x;
        a[1][3] = control->controlParams.srt.t.y;
        a[2][3] = control->controlParams.srt.t.z;
    }

    PSMTXConcat(d,e,e);
    PSMTXConcat(b,e,e);
    PSMTXConcat(c,e,e);
    PSMTXConcat(a,e,e);
    PSMTXCopy(e, m);
}

static Mtx flipY = {{1, 0, 0, 0}, {0, -1, 0, 0}, {0, 0, 1, 0}};

static Mtx flipX = {{-1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};

void CTRLBuildMatrix_FlipY(Control *control, Mtx m) {
    f32 nRad;
    f32 nSin;
    f32 nCos;
    f32 temp;

    Mtx a, b, c, d, e;

    if (control->type & CTRL_MTX) {
        PSMTXCopy(control->controlParams.m, m);
        return;
    }
    PSMTXIdentity(m);
    PSMTXIdentity(a);
    PSMTXIdentity(b);
    PSMTXIdentity(c);
    PSMTXIdentity(d);
    PSMTXIdentity(e);
    if (control->type & CTRL_ROT_QUAT) {
        PSMTXQuat(a, &control->controlParams.srt.r);
    } else if (control->type & CTRL_ROT_EULER) {
        if (0.0f != control->controlParams.srt.r.x) {
            nRad = 0.0174532925f * control->controlParams.srt.r.x;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = 1.0f;
            a[0][1] = 0.0f;
            a[0][2] = 0.0f;
            a[0][3] = 0.0f;
            a[1][0] = 0.0f;
            a[1][1] = nCos;
            a[1][2] = -nSin;
            a[1][3] = 0.0f;
            a[2][0] = 0.0f;
            a[2][1] = nSin;
            a[2][2] = nCos;
            a[2][3] = 0.0f;
        }
        if (0.0f != control->controlParams.srt.r.y) {
            nRad = 0.0174532925f * control->controlParams.srt.r.y;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = nCos;
            a[0][1] = a[2][1] * nSin;
            a[0][2] = a[2][2] * nSin;
            a[2][0] = -nSin;
            a[2][1] = a[2][1] * nCos;
            a[2][2] = a[2][2] * nCos;
        }
        if (0.0f != control->controlParams.srt.r.z) {
            nRad = 0.0174532925f * control->controlParams.srt.r.z;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[1][0] = a[0][0] * nSin;
            a[0][0] = a[0][0] * nCos;
            temp = a[1][1];
            a[1][1] = (a[0][1] * nSin) + (a[1][1] * nCos);
            a[0][1] = (a[0][1] * nCos) - (temp * nSin);
            temp = m[1][2];
            a[1][2] = (a[0][2] * nSin) + (a[1][2] * nCos);
            a[0][2] = (a[0][2] * nCos) - (temp * nSin);
        }
    }
    
    if (control->type & CTRL_SCALE) {
        b[0][0] = control->controlParams.srt.s.x;
        b[1][1] = control->controlParams.srt.s.y;
        b[2][2] = control->controlParams.srt.s.z;
        if (control->type & CTRL_SCALE_QUAT) {
            PSMTXQuat(c, (Quaternion*)&control->controlParams.q);
            PSMTXInverse(c,d);
        }
    }
    if (control->type & CTRL_TRANS) {
        a[0][3] = control->controlParams.srt.t.x;
        a[1][3] = control->controlParams.srt.t.y;
        a[2][3] = control->controlParams.srt.t.z;
    }

    PSMTXConcat(d,e,e);
    PSMTXConcat(b,e,e);
    PSMTXConcat(c,e,e);
    PSMTXConcat(a,e,e);

    PSMTXConcat(e, flipY, e);
    PSMTXConcat(flipY, e, e);

    PSMTXCopy(e, m);
}

void CTRLBuildMatrix_FlipX(Control *control, Mtx m) {
    f32 nRad;
    f32 nSin;
    f32 nCos;
    f32 temp;

    Mtx a, b, c, d, e;

    if (control->type & CTRL_MTX) {
        PSMTXCopy(control->controlParams.m, m);
        return;
    }
    PSMTXIdentity(m);
    PSMTXIdentity(a);
    PSMTXIdentity(b);
    PSMTXIdentity(c);
    PSMTXIdentity(d);
    PSMTXIdentity(e);
    if (control->type & CTRL_ROT_QUAT) {
        PSMTXQuat(a, &control->controlParams.srt.r);
    } else if (control->type & CTRL_ROT_EULER) {
        if (0.0f != control->controlParams.srt.r.x) {
            nRad = 0.0174532925f * control->controlParams.srt.r.x;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = 1.0f;
            a[0][1] = 0.0f;
            a[0][2] = 0.0f;
            a[0][3] = 0.0f;
            a[1][0] = 0.0f;
            a[1][1] = nCos;
            a[1][2] = -nSin;
            a[1][3] = 0.0f;
            a[2][0] = 0.0f;
            a[2][1] = nSin;
            a[2][2] = nCos;
            a[2][3] = 0.0f;
        }
        if (0.0f != control->controlParams.srt.r.y) {
            nRad = 0.0174532925f * control->controlParams.srt.r.y;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = nCos;
            a[0][1] = a[2][1] * nSin;
            a[0][2] = a[2][2] * nSin;
            a[2][0] = -nSin;
            a[2][1] = a[2][1] * nCos;
            a[2][2] = a[2][2] * nCos;
        }
        if (0.0f != control->controlParams.srt.r.z) {
            nRad = 0.0174532925f * control->controlParams.srt.r.z;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[1][0] = a[0][0] * nSin;
            a[0][0] = a[0][0] * nCos;
            temp = a[1][1];
            a[1][1] = (a[0][1] * nSin) + (a[1][1] * nCos);
            a[0][1] = (a[0][1] * nCos) - (temp * nSin);
            temp = m[1][2];
            a[1][2] = (a[0][2] * nSin) + (a[1][2] * nCos);
            a[0][2] = (a[0][2] * nCos) - (temp * nSin);
        }
    }
    
    if (control->type & CTRL_SCALE) {
        b[0][0] = control->controlParams.srt.s.x;
        b[1][1] = control->controlParams.srt.s.y;
        b[2][2] = control->controlParams.srt.s.z;
        if (control->type & CTRL_SCALE_QUAT) {
            PSMTXQuat(c, (Quaternion*)&control->controlParams.q);
            PSMTXInverse(c,d);
        }
    }
    if (control->type & CTRL_TRANS) {
        a[0][3] = control->controlParams.srt.t.x;
        a[1][3] = control->controlParams.srt.t.y;
        a[2][3] = control->controlParams.srt.t.z;
    }

    PSMTXConcat(d,e,e);
    PSMTXConcat(b,e,e);
    PSMTXConcat(c,e,e);
    PSMTXConcat(a,e,e);

    PSMTXConcat(e, flipY, e);
    PSMTXConcat(flipY, e, e);

    PSMTXCopy(e, m);
}

void CTRLBuildMatrix_Flip(Control *control, Mtx m, u32 r5) {
    f32 nRad;
    f32 nSin;
    f32 nCos;
    f32 temp;

    Mtx a, b, c, d, e, f;

    if (control->type & CTRL_MTX) {
        PSMTXCopy(control->controlParams.m, m);
        return;
    }

    PSMTX44Identity(f);

    if (r5 & 1)
    {
        f[0][0] = -1.0;
    }
    if (r5 & 2)
    {
        f[1][1] = -1.0;
    }
    if (r5 & 4)
    {
        f[2][2] = -1.0;
    }

    PSMTXIdentity(m);
    PSMTXIdentity(a);
    PSMTXIdentity(b);
    PSMTXIdentity(c);
    PSMTXIdentity(d);
    PSMTXIdentity(e);
    if (control->type & CTRL_ROT_QUAT) {
        PSMTXQuat(a, &control->controlParams.srt.r);
    } else if (control->type & CTRL_ROT_EULER) {
        if (0.0f != control->controlParams.srt.r.x) {
            nRad = 0.0174532925f * control->controlParams.srt.r.x;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = 1.0f;
            a[0][1] = 0.0f;
            a[0][2] = 0.0f;
            a[0][3] = 0.0f;
            a[1][0] = 0.0f;
            a[1][1] = nCos;
            a[1][2] = -nSin;
            a[1][3] = 0.0f;
            a[2][0] = 0.0f;
            a[2][1] = nSin;
            a[2][2] = nCos;
            a[2][3] = 0.0f;
        }
        if (0.0f != control->controlParams.srt.r.y) {
            nRad = 0.0174532925f * control->controlParams.srt.r.y;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = nCos;
            a[0][1] = a[2][1] * nSin;
            a[0][2] = a[2][2] * nSin;
            a[2][0] = -nSin;
            a[2][1] = a[2][1] * nCos;
            a[2][2] = a[2][2] * nCos;
        }
        if (0.0f != control->controlParams.srt.r.z) {
            nRad = 0.0174532925f * control->controlParams.srt.r.z;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[1][0] = a[0][0] * nSin;
            a[0][0] = a[0][0] * nCos;
            temp = a[1][1];
            a[1][1] = (a[0][1] * nSin) + (a[1][1] * nCos);
            a[0][1] = (a[0][1] * nCos) - (temp * nSin);
            temp = m[1][2];
            a[1][2] = (a[0][2] * nSin) + (a[1][2] * nCos);
            a[0][2] = (a[0][2] * nCos) - (temp * nSin);
        }
    }
    
    if (control->type & CTRL_SCALE) {
        b[0][0] = control->controlParams.srt.s.x;
        b[1][1] = control->controlParams.srt.s.y;
        b[2][2] = control->controlParams.srt.s.z;
        if (control->type & CTRL_SCALE_QUAT) {
            PSMTXQuat(c, (Quaternion*)&control->controlParams.q);
            PSMTXInverse(c,d);
        }
    }
    if (control->type & CTRL_TRANS) {
        a[0][3] = control->controlParams.srt.t.x;
        a[1][3] = control->controlParams.srt.t.y;
        a[2][3] = control->controlParams.srt.t.z;
    }

    PSMTXConcat(d,e,e);
    PSMTXConcat(b,e,e);
    PSMTXConcat(c,e,e);
    PSMTXConcat(a,e,e);

    PSMTXConcat(e, f, e);
    PSMTXConcat(f, e, e);

    PSMTXCopy(e, m);
}

void CTRLBuildInverseMatrix(Control *control, Mtx m) {
    f32 nRad;
    f32 nSin;
    f32 nCos;
    f32 temp;
    Quaternion q;

    if (control->type & CTRL_MTX) {
        PSMTXInverse(control->controlParams.m, m);
        return;
    }
    if (control->type & CTRL_ROT_QUAT) {
        q.x = -control->controlParams.srt.r.x;
        q.y = -control->controlParams.srt.r.y;
        q.z = -control->controlParams.srt.r.z;
        q.w = -control->controlParams.srt.r.w;
        MTXQuat(m, &q);
    } else if (control->type & CTRL_ROT_EULER) {
        if (0.0f != control->controlParams.srt.r.z) {
            nRad = 0.0174532925f * -control->controlParams.srt.r.x;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            m[0][0] = nCos;
            m[0][1] = -nSin;
            m[0][2] = 0.0f;
            m[0][3] = 0.0f;
            m[1][0] = nSin;
            m[1][1] = nCos;
            m[1][2] = 0.0f;
            m[1][3] = 0.0f;
            m[2][0] = 0.0f;
            m[2][1] = 0.0f;
            m[2][2] = 1.0f;
            m[2][3] = 0.0f;
        } else {
            PSMTXIdentity(m);
        }
        if (0.0f != control->controlParams.srt.r.y) {
            nRad = 0.0174532925f * -control->controlParams.srt.r.y;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            m[2][0] = m[0][0] * -nSin;
            m[2][1] = m[0][1] * -nSin;
            m[2][2] = nCos;
            m[0][0] = m[0][0] * nCos;
            m[0][1] = m[0][1] * nCos;
            m[0][2] = nSin;
        }
        if (0.0f != control->controlParams.srt.r.x) {
            nRad = 0.0174532925f * -control->controlParams.srt.r.x;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            m[1][2] = m[2][2] * -nSin;
            m[2][2] = m[2][2] * nCos;
            temp = m[1][0];
            m[1][0] = (m[1][0] * nCos) - (m[2][0] * nSin);
            m[2][0] = (m[2][0] * nCos) + (temp * nSin);
            temp = m[1][1];
            m[1][1] = (m[1][1] * nCos) - (m[2][1] * nSin);
            m[2][1] = (m[2][1] * nCos) + (temp * nSin);
        }
    } else {
        PSMTXIdentity(m);
    }
    if (control->type & CTRL_TRANS) {
        if ((control->type & CTRL_ROT_QUAT) || (control->type & CTRL_ROT_EULER)) {
            m[0][3] = -((m[0][2] * control->controlParams.srt.t.z) + ((m[0][0] * control->controlParams.srt.t.x) + (m[0][1] * control->controlParams.srt.t.y)));
            m[1][3] = -((m[1][2] * control->controlParams.srt.t.z) + ((m[1][0] * control->controlParams.srt.t.x) + (m[1][1] * control->controlParams.srt.t.y)));
            m[2][3] = -((m[2][2] * control->controlParams.srt.t.z) + ((m[2][0] * control->controlParams.srt.t.x) + (m[2][1] * control->controlParams.srt.t.y)));
        } else {
            m[0][3] = -control->controlParams.srt.t.x;
            m[1][3] = -control->controlParams.srt.t.y;
            m[2][3] = -control->controlParams.srt.t.z;
        }
    }
    if (control->type & CTRL_SCALE) {
        q.x = 1.0f / control->controlParams.srt.s.x;
        q.y = 1.0f / control->controlParams.srt.s.y;
        q.z = 1.0f / control->controlParams.srt.s.z;
        m[0][0] *= q.x;
        m[0][1] *= q.x;
        m[0][2] *= q.x;
        m[0][3] *= q.x;
        m[1][0] *= q.y;
        m[1][1] *= q.y;
        m[1][2] *= q.y;
        m[1][3] *= q.y;
        m[2][0] *= q.z;
        m[2][1] *= q.z;
        m[2][2] *= q.z;
        m[2][3] *= q.z;
    }
}

// The game's Control is 0x44 bytes: 8 more than the SDK layout in C3/control.h.
// Blending copies whole controls, so it goes through this full-size view.
typedef struct ControlFull {
    Control ctrl;
    u32 unk3C[2]; // TODO type
} ControlFull;

// Set by fn_800B313C before blending: also blend scale and the scale quaternion.
extern s32 lbl_803CC1E8;

// Blends two controls: dst = from * (1 - t) + to * t. Rotations use slerp (quaternion) or
// shortest-way lerp (Euler degrees). If the controls differ in kind, dst takes `to`.
void fn_800B84AC(Control *dst, Control *from, Control *to, f32 t)
{
    f32 s = 1.0f - t;
    Quaternion *qFrom = &from->controlParams.srt.r;
    Quaternion *qTo = &to->controlParams.srt.r;
    Quaternion *qDst = &dst->controlParams.srt.r;
    Quaternion neg;

    if (t >= 1.0f || from == NULL || from->type != to->type) {
        if (to->type & CTRL_SCALE) {
            *(ControlFull *)dst = *(ControlFull *)to;
        } else {
            *(ControlFull *)dst = *(ControlFull *)to;
        }
        return;
    }

    dst->type = to->type;
    if (from->type & CTRL_ROT_QUAT) {
        if (PSQUATDotProduct(qFrom, qTo) >= 0.0f) {
            C_QUATSlerp(qFrom, qTo, qDst, t);
        } else {
            PSQUATScale(qFrom, -1.0f, &neg);
            C_QUATSlerp(&neg, qTo, qDst, t);
        }
    } else if (from->type & CTRL_ROT_EULER) {
        f32 *a = &qFrom->x;
        f32 *b = &qTo->x;
        f32 *d = &qDst->x;
        s32 i;
        for (i = 0; i < 3; i++) {
            f32 diff = a[i] - b[i];
            if (diff > 180.0f) {
                a[i] -= 360.0f;
            } else if (diff < -180.0f) {
                b[i] -= 360.0f;
            }
            d[i] = t * b[i] + s * a[i];
        }
    } else {
        *qDst = *qTo;
    }

    if (lbl_803CC1E8 != 0 && (from->type & CTRL_SCALE)) {
        dst->controlParams.srt.s.x = to->controlParams.srt.s.x * t + from->controlParams.srt.s.x * s;
        dst->controlParams.srt.s.y = to->controlParams.srt.s.y * t + from->controlParams.srt.s.y * s;
        dst->controlParams.srt.s.z = to->controlParams.srt.s.z * t + from->controlParams.srt.s.z * s;
        dst->controlParams.q.x = to->controlParams.q.x * t + from->controlParams.q.x * s;
        dst->controlParams.q.y = to->controlParams.q.y * t + from->controlParams.q.y * s;
        dst->controlParams.q.z = to->controlParams.q.z * t + from->controlParams.q.z * s;
        dst->controlParams.q.w = to->controlParams.q.w * t + from->controlParams.q.w * s;
    } else {
        dst->controlParams.srt.s = to->controlParams.srt.s;
        dst->controlParams.q = to->controlParams.q;
    }

    if (from->type & CTRL_TRANS) {
        dst->controlParams.srt.t.x = to->controlParams.srt.t.x * t + from->controlParams.srt.t.x * s;
        dst->controlParams.srt.t.y = to->controlParams.srt.t.y * t + from->controlParams.srt.t.y * s;
        dst->controlParams.srt.t.z = to->controlParams.srt.t.z * t + from->controlParams.srt.t.z * s;
    } else {
        dst->controlParams.srt.t = to->controlParams.srt.t;
    }
}

void CTRL_SetQuatUnk(Control *control, float x, float y, float z, float w)
{
    control->type |= CTRL_SCALE_QUAT;
    control->type &= ~CTRL_MTX;
    control->controlParams.q.x = x;
    control->controlParams.q.y = y;
    control->controlParams.q.z = z;
    control->controlParams.q.w = w;
}

void CTRL_GetQuatUnk(const Control *control, float *x, float *y, float *z, float *w)
{
    *x = control->controlParams.q.x;
    *y = control->controlParams.q.y;
    *z = control->controlParams.q.z;
    *w = control->controlParams.q.w;
}

// View volume used for visibility tests: the 8 corners of the frustum in view space,
// its projection matrix and the near/far distances.
typedef struct CTRLFrustum {
    /* 0x00 */ Vec corners[8];
    /* 0x60 */ Mtx44 proj;
    /* 0xA0 */ f32 near;
    /* 0xA4 */ f32 far;
} CTRLFrustum; // size 0xA8

static CTRLFrustum sFrustums[4];

// Box edges and faces by corner index (box corners in the same order as CTRLFrustum.corners).
// TODO: these live just before control.c's .data in the DOL (0x80111670 / 0x80111688)
u8 sBoxEdges[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7},
};
u8 sBoxFaces[6][4] = {
    {0, 3, 7, 4}, {2, 1, 5, 6}, {0, 1, 2, 3}, {7, 6, 5, 4}, {3, 2, 6, 7}, {0, 4, 5, 1},
};



