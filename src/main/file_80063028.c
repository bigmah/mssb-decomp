#include "main/file_80063028.h"
#include "stl/mem.h"
#include "stl/math.h"

#if NONMATCHING
static f32 cosf(f32 v) { return cos(v); }
static f32 sinf(f32 v) { return sin(v); }
#endif

extern f32 lbl_803CC8D8; // 1.0f
extern f32 lbl_803CC8DC; // -1.0f
extern f32 lbl_803CC8E0; // pi
extern f32 lbl_803CC8E4; // 0.0f
extern f32 lbl_803CC8E8; // pi / 180

// Like CTRLBuildMatrix, with a 180-degree rotation about the axes in flipFlags
// (1 = X, 2 = Y, 4 = Z) and the rotation part mirrored in Y.
// .text:0x80063028 size:0x384
// NONMATCHING 99.7%: f1/f2/f3 swapped for the 0.0f/1.0f/cos values in the X-rotation block
#if NONMATCHING
void fn_80063028(Control* control, Mtx m, u32 flipFlags) {
    f32 nRad;
    f32 nSin;
    f32 nCos;
    f32 temp;
    Mtx T, a, b, c, d, e, S, R;

    if (control->type & CTRL_MTX) {
        PSMTXCopy(control->controlParams.m, m);
        return;
    }

    PSMTXScale(S, lbl_803CC8D8, lbl_803CC8DC, lbl_803CC8D8);
    PSMTXIdentity(R);
    if (flipFlags & 1) {
        PSMTXRotRad(R, 'X', lbl_803CC8E0);
    }
    if (flipFlags & 2) {
        PSMTXRotRad(R, 'Y', lbl_803CC8E0);
    }
    if (flipFlags & 4) {
        PSMTXRotRad(R, 'Z', lbl_803CC8E0);
    }

    PSMTXIdentity(m);
    PSMTXIdentity(T);
    PSMTXIdentity(a);
    PSMTXIdentity(b);
    PSMTXIdentity(c);
    PSMTXIdentity(d);
    PSMTXIdentity(e);
    if (control->type & CTRL_ROT_QUAT) {
        PSMTXQuat(a, &control->controlParams.srt.r);
    } else if (control->type & CTRL_ROT_EULER) {
        if (lbl_803CC8E4 != control->controlParams.srt.r.x) {
            nRad = lbl_803CC8E8 * control->controlParams.srt.r.x;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = lbl_803CC8D8;
            a[0][1] = lbl_803CC8E4;
            a[0][2] = lbl_803CC8E4;
            a[0][3] = lbl_803CC8E4;
            a[1][0] = lbl_803CC8E4;
            a[1][1] = nCos;
            a[1][2] = -nSin;
            a[1][3] = lbl_803CC8E4;
            a[2][0] = lbl_803CC8E4;
            a[2][1] = nSin;
            a[2][2] = nCos;
            a[2][3] = lbl_803CC8E4;
        }
        if (lbl_803CC8E4 != control->controlParams.srt.r.y) {
            nRad = lbl_803CC8E8 * control->controlParams.srt.r.y;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = nCos;
            a[0][1] = a[2][1] * nSin;
            a[0][2] = a[2][2] * nSin;
            a[2][0] = -nSin;
            a[2][1] = a[2][1] * nCos;
            a[2][2] = a[2][2] * nCos;
        }
        if (lbl_803CC8E4 != control->controlParams.srt.r.z) {
            nRad = lbl_803CC8E8 * control->controlParams.srt.r.z;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[1][0] = a[0][0] * nSin;
            a[0][0] = a[0][0] * nCos;
            temp = a[1][1];
            a[1][1] = (a[0][1] * nSin) + (a[1][1] * nCos);
            a[0][1] = (a[0][1] * nCos) - (temp * nSin);
            temp = m[1][2]; // original bug: reads m instead of a
            a[1][2] = (a[0][2] * nSin) + (a[1][2] * nCos);
            a[0][2] = (a[0][2] * nCos) - (temp * nSin);
        }
    }

    if (control->type & CTRL_SCALE) {
        b[0][0] = control->controlParams.srt.s.x;
        b[1][1] = control->controlParams.srt.s.y;
        b[2][2] = control->controlParams.srt.s.z;
        if (control->type & CTRL_SCALE_QUAT) {
            PSMTXQuat(c, &control->controlParams.q);
            PSMTXInverse(c, d);
        }
    }
    if (control->type & CTRL_TRANS) {
        T[0][3] = control->controlParams.srt.t.x;
        T[1][3] = control->controlParams.srt.t.y;
        T[2][3] = control->controlParams.srt.t.z;
    }

    PSMTXConcat(e, R, e);
    PSMTXConcat(d, e, e);
    PSMTXConcat(b, e, e);
    PSMTXConcat(c, e, e);
    PSMTXConcat(a, S, a);
    PSMTXConcat(S, a, a);
    PSMTXConcat(a, e, e);
    PSMTXConcat(T, e, e);
    PSMTXCopy(e, m);
}
#endif

// Like fn_80063028, but the whole rotation+translation matrix is mirrored in Y.
// .text:0x800633AC size:0x36C
// NONMATCHING 99.7%: f1/f2/f3 swapped for the 0.0f/1.0f/cos values in the X-rotation block
#if NONMATCHING
void fn_800633AC(Control* control, Mtx m, u32 flipFlags) {
    f32 nRad;
    f32 nSin;
    f32 nCos;
    f32 temp;
    Mtx a, b, c, d, e, S, R;

    if (control->type & CTRL_MTX) {
        PSMTXCopy(control->controlParams.m, m);
        return;
    }

    PSMTXScale(S, lbl_803CC8D8, lbl_803CC8DC, lbl_803CC8D8);
    PSMTXIdentity(R);
    if (flipFlags & 1) {
        PSMTXRotRad(R, 'X', lbl_803CC8E0);
    }
    if (flipFlags & 2) {
        PSMTXRotRad(R, 'Y', lbl_803CC8E0);
    }
    if (flipFlags & 4) {
        PSMTXRotRad(R, 'Z', lbl_803CC8E0);
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
        if (lbl_803CC8E4 != control->controlParams.srt.r.x) {
            nRad = lbl_803CC8E8 * control->controlParams.srt.r.x;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = lbl_803CC8D8;
            a[0][1] = lbl_803CC8E4;
            a[0][2] = lbl_803CC8E4;
            a[0][3] = lbl_803CC8E4;
            a[1][0] = lbl_803CC8E4;
            a[1][1] = nCos;
            a[1][2] = -nSin;
            a[1][3] = lbl_803CC8E4;
            a[2][0] = lbl_803CC8E4;
            a[2][1] = nSin;
            a[2][2] = nCos;
            a[2][3] = lbl_803CC8E4;
        }
        if (lbl_803CC8E4 != control->controlParams.srt.r.y) {
            nRad = lbl_803CC8E8 * control->controlParams.srt.r.y;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[0][0] = nCos;
            a[0][1] = a[2][1] * nSin;
            a[0][2] = a[2][2] * nSin;
            a[2][0] = -nSin;
            a[2][1] = a[2][1] * nCos;
            a[2][2] = a[2][2] * nCos;
        }
        if (lbl_803CC8E4 != control->controlParams.srt.r.z) {
            nRad = lbl_803CC8E8 * control->controlParams.srt.r.z;
            nSin = sinf(nRad);
            nCos = cosf(nRad);
            a[1][0] = a[0][0] * nSin;
            a[0][0] = a[0][0] * nCos;
            temp = a[1][1];
            a[1][1] = (a[0][1] * nSin) + (a[1][1] * nCos);
            a[0][1] = (a[0][1] * nCos) - (temp * nSin);
            temp = m[1][2]; // original bug: reads m instead of a
            a[1][2] = (a[0][2] * nSin) + (a[1][2] * nCos);
            a[0][2] = (a[0][2] * nCos) - (temp * nSin);
        }
    }

    if (control->type & CTRL_SCALE) {
        b[0][0] = control->controlParams.srt.s.x;
        b[1][1] = control->controlParams.srt.s.y;
        b[2][2] = control->controlParams.srt.s.z;
        if (control->type & CTRL_SCALE_QUAT) {
            PSMTXQuat(c, &control->controlParams.q);
            PSMTXInverse(c, d);
        }
    }
    if (control->type & CTRL_TRANS) {
        a[0][3] = control->controlParams.srt.t.x;
        a[1][3] = control->controlParams.srt.t.y;
        a[2][3] = control->controlParams.srt.t.z;
    }

    PSMTXConcat(e, R, e);
    PSMTXConcat(d, e, e);
    PSMTXConcat(b, e, e);
    PSMTXConcat(c, e, e);
    PSMTXConcat(a, e, e);
    PSMTXConcat(e, S, e);
    PSMTXConcat(S, e, e);
    PSMTXCopy(e, m);
}
#endif

extern u32 lbl_803CB890;

// .text:0x80063718 size:0xA4
s32 fn_80063718(GameBone* bone, GameBone* target, Mtx m, f32 t) {
    switch (bone->boneID) {
    case 0x4A:
        fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, t);
        fn_800633AC(&target->animCtrl, m, lbl_803CB890);
        return 1;
    case 0x4B:
        fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, t);
        fn_800633AC(&target->animCtrl, m, lbl_803CB890);
        return 1;
    }
    return 0;
}

// fn_800637BC, size:0x18
s32 fn_800637BC(void* player, GameActor** actor) {
    (*actor)->boneCallback = fn_80063718;
    return 0;
}

// fn_800637D4, size:0x8
s32 fn_800637D4(void) {
    return 0;
}

// .text:0x800637DC size:0xD8
s32 fn_800637DC(GameBone* bone, GameBone* target, Mtx m, f32 t) {
    switch (bone->boneID) {
    case 0x47:
        fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, t);
        CTRLBuildMatrix_Flip(&target->animCtrl, m, 0);
        return 1;
    case 0x40:
        fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, t);
        fn_80063028(&target->animCtrl, m, 4);
        return 1;
    case 0x41:
        fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, t);
        CTRLBuildMatrix_Flip(&target->animCtrl, m, 1);
        return 1;
    }
    return 0;
}

// .text:0x800638B4 size:0x18
s32 fn_800638B4(void* player, GameActor** actor) {
    (*actor)->boneCallback = fn_800637DC;
    return 0;
}

// .text:0x800638CC size:0x8C
void fn_800638CC(void) {
    return;
}

// .text:0x80063958 size:0x64
void fn_80063958(s8 index) {
    return;
}
