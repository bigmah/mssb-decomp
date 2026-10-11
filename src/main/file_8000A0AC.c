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

// .text:0x8000A3EC size:0xB30
void fn_8000A3EC(void) {
    return;
}

// .text:0x8000AF1C size:0xAAC
void fn_8000AF1C(void) {
    return;
}

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
