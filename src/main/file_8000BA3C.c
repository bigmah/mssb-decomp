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
void AddVec2iToQuad(SpriteQuad* quad, Mtx mtx, SpriteDrawParams* params) {
    Mtx m;
    QuadPoint pts[4];

    pts[0].pos.x = quad->xy[0][0] + params->ofs[0][0];
    pts[0].pos.y = quad->xy[0][1] + params->ofs[0][1];
    pts[0].pos.z = 0.0f;
    pts[1].pos.x = quad->xy[1][0] + params->ofs[1][0];
    pts[1].pos.y = quad->xy[1][1] + params->ofs[1][1];
    pts[1].pos.z = 0.0f;
    pts[2].pos.x = quad->xy[2][0] + params->ofs[2][0];
    pts[2].pos.y = quad->xy[2][1] + params->ofs[2][1];
    pts[2].pos.z = 0.0f;
    pts[3].pos.x = quad->xy[3][0] + params->ofs[3][0];
    pts[3].pos.y = quad->xy[3][1] + params->ofs[3][1];
    pts[3].pos.z = 0.0f;
    PSMTXCopy(mtx, m);
    PSMTXMultVec(m, &pts[0].pos, &pts[0].pos);
    PSMTXMultVec(m, &pts[1].pos, &pts[1].pos);
    PSMTXMultVec(m, &pts[2].pos, &pts[2].pos);
    PSMTXMultVec(m, &pts[3].pos, &pts[3].pos);
    quad->pt[0].pos.x = pts[0].pos.x;
    quad->pt[0].pos.y = pts[0].pos.y;
    quad->pt[1].pos.x = pts[1].pos.x;
    quad->pt[1].pos.y = pts[1].pos.y;
    quad->pt[2].pos.x = pts[2].pos.x;
    quad->pt[2].pos.y = pts[2].pos.y;
    quad->pt[3].pos.x = pts[3].pos.x;
    quad->pt[3].pos.y = pts[3].pos.y;
    quad->pt[0].pos.z = pts[0].pos.z;
    quad->pt[1].pos.z = pts[1].pos.z;
    quad->pt[2].pos.z = pts[2].pos.z;
    quad->pt[3].pos.z = pts[3].pos.z;
}
