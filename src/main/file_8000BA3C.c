#include "main/file_8000BA3C.h"
#include "stl/math.h"

// .text:0x8000BA3C size:0x758
void fn_8000BA3C(void) {
    return;
}

// .text:0x8000C194 size:0xAB8
void fn_8000C194(void) {
    return;
}

// .text:0x8000CC4C size:0x2A4
void fn_8000CC4C(void) {
    return;
}

// .text:0x8000CEF0 size:0x274
void fn_8000CEF0(void) {
    return;
}

// .text:0x8000D164 size:0x6D4
void fn_8000D164(void) {
    return;
}

// .text:0x8000D838 size:0x6C
void fn_8000D838(void) {
    return;
}

// .text:0x8000D8A4 size:0x3F8
void fn_8000D8A4(void) {
    return;
}

// .text:0x8000DC9C size:0x394
void fn_8000DC9C(void) {
    return;
}

// .text:0x8000E030 size:0x2A4
void fn_8000E030(void) {
    return;
}

// .text:0x8000E2D4 size:0x490
void fn_8000E2D4(void) {
    return;
}

// .text:0x8000E764 size:0x58
void fn_8000E764(f32 angle, Vec2f* out) {
    out->x = sin(angle);
    out->y = cos(angle);
}

// .text:0x8000E7BC size:0x144
void fn_8000E7BC(void) {
    return;
}

// .text:0x8000E900 size:0x30C
void SetSpriteRect(void) {
    return;
}

// .text:0x8000EC0C size:0x310
void fn_8000EC0C(void) {
    return;
}

// .text:0x8000EF1C size:0x234
// NONMATCHING ~85%: saved-register/scheduling differences; float constants
// are unnamed until this unit's .sdata2 is split.
#if NONMATCHING
void AddVec2iToQuad(SpriteQuad* quad, Mtx mtx, SpriteDrawParams* params) {
    Mtx m;
    QuadPoint pts[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        pts[i].pos.x = quad->xy[i][0] + params->ofs[i][0];
        pts[i].pos.y = quad->xy[i][1] + params->ofs[i][1];
        pts[i].pos.z = 0.0f;
    }
    PSMTXCopy(mtx, m);
    PSMTXMultVec(m, &pts[0].pos, &pts[0].pos);
    PSMTXMultVec(m, &pts[1].pos, &pts[1].pos);
    PSMTXMultVec(m, &pts[2].pos, &pts[2].pos);
    PSMTXMultVec(m, &pts[3].pos, &pts[3].pos);
    for (i = 0; i < 4; i++) {
        quad->pt[i].pos.x = pts[i].pos.x;
        quad->pt[i].pos.y = pts[i].pos.y;
    }
    for (i = 0; i < 4; i++) {
        quad->pt[i].pos.z = pts[i].pos.z;
    }
}
#endif
