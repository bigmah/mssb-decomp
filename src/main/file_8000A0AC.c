#include "main/file_8000A0AC.h"

extern const f32 lbl_803CC428; // 1.0f
extern const f32 lbl_803CC42C; // 0.0f
extern const f32 lbl_803CC430; // 1.0f / 1024
extern const f32 lbl_803CC434; // 4096.0f
extern const f32 lbl_803CC438; // 2 * pi
extern const f32 lbl_803CC448; // 360.0f
extern const f32 lbl_803CC44C; // 0.5f
extern const f32 lbl_803CC450; // pi / 2
extern const f32 lbl_803CC454; // pi / 180

void fn_8000E764(f32* sinCos, f32 angle);

// NONMATCHING 99%: r9/r10/r11 assignment of the handle pointers and &pts[1] differs
// .text:0x8000A0AC size:0x13C
#if NONMATCHING
void fn_8000A0AC(f32 t, BezierPoint* out, LayoutKey* a, LayoutKey* b) {
    s16* outHandle;
    s16* inHandle;
    BezierPoint pts[4];

    if (a->type == 2) {
        outHandle = a->handles;
        inHandle = b->handles;
    } else {
        outHandle = a->handles;
        inHandle = b->handles;
    }
    pts[0].x = a->pos[0];
    pts[0].y = a->pos[1];
    pts[1].x = outHandle[2];
    pts[1].y = outHandle[3];
    pts[2].x = inHandle[0];
    pts[2].y = inHandle[1];
    pts[3].x = b->pos[0];
    pts[3].y = b->pos[1];
    BezierInterpolate(t, out, &pts[0], &pts[1], &pts[2], &pts[3]);
}
#endif

// .text:0x8000A1E8 size:0x204
void interpolatePointsBezier_Vec2s(f32 t, BezierPoint* out, PathPoint* p0, PathPoint* p1, PathPoint* p2,
                                   PathPoint* p3, u32 segment) {
    BezierPoint pts[10];

    pts[0].x = p0->x;
    pts[0].y = p0->y;
    pts[3].x = p1->x;
    pts[3].y = p1->y;
    pts[6].x = p2->x;
    pts[6].y = p2->y;
    pts[9].x = p3->x;
    pts[9].y = p3->y;
    if (segment == 0) {
        interpolatePointsUnknown(3, pts, 1, 0);
        BezierInterpolate(t, out, &pts[0], &pts[1], &pts[2], &pts[3]);
    } else if (segment == 1) {
        interpolatePointsUnknown(3, pts, 1, 0);
        interpolatePointsUnknown(6, pts, 0, 1);
        BezierInterpolate(t, out, &pts[3], &pts[4], &pts[5], &pts[6]);
    } else {
        interpolatePointsUnknown(6, pts, 0, 1);
        BezierInterpolate(t, out, &pts[6], &pts[7], &pts[8], &pts[9]);
    }
}

// NONMATCHING 94%: color/pivot code differs in register use and bit extraction (flags are
// probably bitfields); compiler-generated int-to-float constants live in the unsplit .sdata2
// .text:0x8000A3EC size:0xB30
#if NONMATCHING
BOOL fn_8000A3EC(Mtx out, LayoutFrame* frame, LayoutKey* a, LayoutKey* b, f32* offset, f32 t, f32 z) {
    Mtx rot;
    Mtx scale;
    Mtx trans;
    u8 color[4];
    f32 u;
    f32 pivotX;
    f32 pivotY;
    f32 angle;
    s16* rotA;
    s16* rotB;
    s32 axis;
    s32 i;
    s32 j;
    s32 step;
    u8* colorA;
    u8* colorB;
    u32* dst;
    BOOL rotated;

    pivotX = lbl_803CC42C;
    pivotY = pivotX;
    u = lbl_803CC428 - t;
    if (a->type == 2) {
        // NOTE: compares a->_1C against b->_28 (as in the original)
        frame->_30 = a->u.text._1C != b->u.text._28 ? (f32)a->u.text._28 * u + (f32)b->u.text._28 * t : (f32)a->u.text._28;
        frame->_34 = a->u.text._1E != b->u.text._1E ? (f32)a->u.text._1E * u + (f32)b->u.text._1E * t : (f32)a->u.text._1E;
        frame->_36 = a->u.text._2A != b->u.text._2A ? (f32)a->u.text._2A * u + (f32)b->u.text._2A * t : (f32)a->u.text._2A;
        if (a->u.text.colors[0] != b->u.text.colors[0]) {
            ((u8*)&frame->colors[0])[0] = t * ((u8*)&b->u.text.colors[0])[0] + u * ((u8*)&a->u.text.colors[0])[0];
            ((u8*)&frame->colors[0])[1] = t * ((u8*)&b->u.text.colors[0])[1] + u * ((u8*)&a->u.text.colors[0])[1];
            ((u8*)&frame->colors[0])[2] = t * ((u8*)&b->u.text.colors[0])[2] + u * ((u8*)&a->u.text.colors[0])[2];
            ((u8*)&frame->colors[0])[3] = t * ((u8*)&b->u.text.colors[0])[3] + u * ((u8*)&a->u.text.colors[0])[3];
        } else {
            frame->colors[0] = a->u.text.colors[0];
        }
        if (a->u.text.colors[1] != b->u.text.colors[1]) {
            ((u8*)&frame->colors[1])[0] = t * ((u8*)&b->u.text.colors[1])[0] + u * ((u8*)&a->u.text.colors[1])[0];
            ((u8*)&frame->colors[1])[1] = t * ((u8*)&b->u.text.colors[1])[1] + u * ((u8*)&a->u.text.colors[1])[1];
            ((u8*)&frame->colors[1])[2] = t * ((u8*)&b->u.text.colors[1])[2] + u * ((u8*)&a->u.text.colors[1])[2];
            ((u8*)&frame->colors[1])[3] = t * ((u8*)&b->u.text.colors[1])[3] + u * ((u8*)&a->u.text.colors[1])[3];
        } else {
            frame->colors[1] = a->u.text.colors[1];
        }
    } else {
        frame->corners[0][0] = (f32)a->_40[0] * u + (f32)b->_40[0] * t;
        frame->corners[0][1] = (f32)a->_40[1] * u + (f32)b->_40[1] * t;
        frame->corners[1][0] = (f32)a->_40[2] * u + (f32)b->_40[2] * t;
        frame->corners[1][1] = (f32)a->_40[3] * u + (f32)b->_40[3] * t;
        frame->corners[2][0] = (f32)a->_40[4] * u + (f32)b->_40[4] * t;
        frame->corners[2][1] = (f32)a->_40[5] * u + (f32)b->_40[5] * t;
        frame->corners[3][0] = (f32)a->_40[6] * u + (f32)b->_40[6] * t;
        frame->corners[3][1] = (f32)a->_40[7] * u + (f32)b->_40[7] * t;
        step = (((a->flags >> 2) & 1) | ((b->flags >> 2) & 1)) * 4;
        colorA = a->u.colors[0];
        colorB = b->u.colors[0];
        dst = frame->colors;
        for (i = 0; i < 4; i++) {
            for (j = 3; j >= 0; j--) {
                if (colorA[j] != colorB[j]) {
                    color[j] = u * colorA[j] + t * colorB[j];
                } else {
                    color[j] = colorA[j];
                }
                if (a->blend == 2 && j <= 2) {
                    color[j] = color[3] * color[j] / 255;
                }
            }
            colorA += step;
            *dst = *(u32*)color;
            colorB += step;
            dst++;
        }
    }
    rotA = a->rot;
    rotB = b->rot;

    if (a->pivot[0] != b->pivot[0]) {
        pivotX = (f32)a->pivot[0] * u + (f32)b->pivot[0] * t;
    } else if (a->pivot[0] != 0) {
        pivotX = a->pivot[0];
    }
    if (a->pivot[1] != b->pivot[1]) {
        pivotY = (f32)a->pivot[1] * u + (f32)b->pivot[1] * t;
    } else if (a->pivot[1] != 0) {
        pivotY = a->pivot[1];
    }
    PSMTXTrans(trans, -pivotX, -pivotY, lbl_803CC42C);
    PSMTXScale(scale, (f32)a->scale[0] * lbl_803CC430 * u + (f32)b->scale[0] * lbl_803CC430 * t,
               (f32)a->scale[1] * lbl_803CC430 * u + (f32)b->scale[1] * lbl_803CC430 * t, lbl_803CC428);
    PSMTXConcat(scale, trans, scale);

    rotated = FALSE;
    for (axis = 2; axis >= 0; axis--) {
        angle = u * (rotA[axis] / lbl_803CC434) + t * (rotB[axis] / lbl_803CC434);
        rotated |= angle != lbl_803CC42C;
        if (angle != lbl_803CC42C) {
            angle *= lbl_803CC438;
            switch (axis) {
            case 0:
                PSMTXRotRad(rot, 'X', angle);
                break;
            case 1:
                PSMTXRotRad(rot, 'Y', angle);
                break;
            case 2:
                PSMTXRotRad(rot, 'Z', angle);
                break;
            }
            PSMTXConcat(rot, scale, scale);
        }
    }

    PSMTXTrans(trans, pivotX, pivotY, lbl_803CC42C);
    if ((a->flags >> 4) & 1) {
        trans[0][3] += offset[0];
        trans[1][3] += offset[1];
    } else {
        trans[0][3] += (f32)a->pos[0] * u + (f32)b->pos[0] * t;
        trans[1][3] += (f32)a->pos[1] * u + (f32)b->pos[1] * t;
    }
    trans[2][3] = z;
    PSMTXConcat(trans, scale, out);
    return rotated;
}
#endif

// NONMATCHING 96%: register allocation and the pivot compares (xor. in the original) differ
// .text:0x8000AF1C size:0xAAC
#if NONMATCHING
BOOL fn_8000AF1C(Mtx out, LayoutFrame* frame, LayoutKey2* a, LayoutKey2* b, void* palette, f32* offset, f32 t) {
    Mtx trans;
    Mtx local;
    Mtx rot;
    Quaternion q;
    f32 sc[2];
    u8 color[4];
    f32 u;
    f32 pivotX;
    f32 pivotY;
    f32 angle;
    f32 axisA;
    f32 axisB;
    f32 sx;
    f32 sy;
    s32 i;
    u32 flipA;
    u32 flipB;
    u8 type;
    u32* colorsA; // TODO type: palette entries are 16 bytes, colors start at +4
    u32* colorsB;

    pivotX = lbl_803CC42C;
    pivotY = pivotX;
    u = lbl_803CC428 - t;
    if (a->pivot[0] != b->pivot[0]) {
        pivotX = (f32)a->pivot[0] * u + (f32)b->pivot[0] * t;
    } else if (a->pivot[0] != 0) {
        pivotX = a->pivot[0];
    }
    if (a->pivot[1] != b->pivot[1]) {
        pivotY = (f32)a->pivot[1] * u + (f32)b->pivot[1] * t;
    } else if (a->pivot[1] != 0) {
        pivotY = a->pivot[1];
    }

    PSMTXIdentity(local);
    sx = (f32)a->scale[0] * lbl_803CC430 * u + (f32)b->scale[0] * lbl_803CC430 * t;
    local[0][0] = sx;
    local[0][3] = sx * -pivotX;
    sy = (f32)a->scale[1] * lbl_803CC430 * u + (f32)b->scale[1] * lbl_803CC430 * t;
    local[1][1] = sy;
    local[1][3] = sy * -pivotY;

    if (a->rot != b->rot) {
        angle = a->rot / lbl_803CC434 * u + b->rot / lbl_803CC434 * t;
    } else {
        angle = a->rot / lbl_803CC434;
    }
    if (angle != lbl_803CC42C) {
        flipA = (a->flags >> 1) & 1;
        flipB = (b->flags >> 1) & 1;
        angle *= lbl_803CC448;
        if (flipA != flipB) {
            // the rotation axis changes between z and y: blend it over the segment
            angle *= lbl_803CC44C;
            fn_8000E764(sc, lbl_803CC450 * t);
            axisA = sc[flipA];
            axisB = sc[flipB];
            fn_8000E764(sc, lbl_803CC454 * angle);
            q.x = lbl_803CC42C;
            q.y = axisA * sc[0];
            q.z = axisB * sc[0];
            q.w = sc[1];
            PSMTXQuat(rot, &q);
        } else if (flipA) {
            PSMTXRotRad(rot, 'Y', lbl_803CC454 * angle);
        } else {
            PSMTXRotRad(rot, 'Z', lbl_803CC454 * angle);
        }
        PSMTXConcat(rot, local, local);
    }

    PSMTXTrans(trans, pivotX, pivotY, lbl_803CC42C);
    if ((a->flags >> 3) & 1) {
        trans[0][3] += offset[0];
        trans[1][3] += offset[1];
    } else if (a->pos[0] != b->pos[0] || a->pos[1] != b->pos[1]) {
        trans[0][3] += (f32)a->pos[0] * u + (f32)b->pos[0] * t;
        trans[1][3] += (f32)a->pos[1] * u + (f32)b->pos[1] * t;
    } else {
        trans[0][3] += (f32)a->pos[0];
        trans[1][3] += (f32)a->pos[1];
    }
    PSMTXConcat(trans, local, out);

    for (i = 0; i < 4; i++) {
        if (*(u32*)a->u.corners[i] != *(u32*)b->u.corners[i]) {
            frame->corners[i][0] = (f32)a->u.corners[i][0] * u + (f32)b->u.corners[i][0] * t;
            frame->corners[i][1] = (f32)a->u.corners[i][1] * u + (f32)b->u.corners[i][1] * t;
        } else {
            frame->corners[i][0] = a->u.corners[i][0];
            frame->corners[i][1] = a->u.corners[i][1];
        }
    }

    type = a->type & 0xF;
    if (type == 3) {
        frame->_30 = a->u.text._18 != b->u.text._18 ? (f32)a->u.text._18 * u + (f32)b->u.text._18 * t : (f32)a->u.text._18;
        frame->_34 = a->u.text._1A != b->u.text._1A ? (f32)a->u.text._1A * u + (f32)b->u.text._1A * t : (f32)a->u.text._1A;
        frame->_36 = a->u.text._26 != b->u.text._26 ? (f32)a->u.text._26 * u + (f32)b->u.text._26 * t : (f32)a->u.text._26;
        frame->colors[0] = a->u.text._1C != b->u.text._1C ? (f32)a->u.text._1C * u + (f32)b->u.text._1C * t : (f32)a->u.text._1C;
        frame->colors[1] = a->u.text._20 != b->u.text._20 ? (f32)a->u.text._20 * u + (f32)b->u.text._20 * t : (f32)a->u.text._20;
    } else if (type != 2) {
        if (*(u32*)a->color != *(u32*)b->color) {
            color[0] = t * b->color[0] + u * a->color[0];
            color[1] = t * b->color[1] + u * a->color[1];
            color[2] = t * b->color[2] + u * a->color[2];
            color[3] = t * b->color[3] + u * a->color[3];
            frame->colors[3] = frame->colors[2] = frame->colors[1] = frame->colors[0] = *(u32*)color;
        } else {
            frame->colors[3] = frame->colors[2] = frame->colors[1] = frame->colors[0] = *(u32*)a->color;
        }
    } else {
        for (i = 0; i < 4; i++) {
            colorsA = (u32*)((u8*)palette + (a->palette << 4)) + 1;
            colorsB = (u32*)((u8*)palette + (b->palette << 4)) + 1;
            if (colorsA[i] != colorsB[i]) {
                color[0] = t * ((u8*)&colorsB[i])[0] + u * ((u8*)&colorsA[i])[0];
                color[1] = t * ((u8*)&colorsB[i])[1] + u * ((u8*)&colorsA[i])[1];
                color[2] = t * ((u8*)&colorsB[i])[2] + u * ((u8*)&colorsA[i])[2];
                color[3] = t * ((u8*)&colorsB[i])[3] + u * ((u8*)&colorsA[i])[3];
                frame->colors[i] = *(u32*)color;
            } else {
                frame->colors[i] = colorsA[i];
            }
        }
    }
    return angle != lbl_803CC42C;
}
#endif

// .text:0x8000B9C8 size:0x74
void fn_8000B9C8(void* file) {
    // TODO port: converts 32-bit file offsets into pointers in place
    u32* header = (u32*)file;
    u32* entry;
    u32* item;
    u32 count;
    u32 n;
    u32* group;
    u32* table;

    header[2] += (u32)header;
    if (((u16*)header)[3] == 0) {
        header[3] += (u32)header;
    }
    table = (u32*)header[2];
    count = table[0];
    entry = table;
    do {
        entry[2] += (u32)table;
        group = (u32*)entry[2];
        n = group[0] & 0x7FFFFFFF;
        item = group;
        do {
            item[2] += (u32)group;
            item++;
        } while (--n != 0);
        entry++;
    } while (--count != 0);
}
