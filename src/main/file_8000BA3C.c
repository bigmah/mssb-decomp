#include "main/file_8000BA3C.h"
#include "stl/math.h"

// main/file_800B0724
void fn_800B12DC(QuadVtx* verts, s32 count); // draw triangle fan
void fn_800B13C0(Vec* pos, u32* colors, s32 count); // draw triangle fan

// Copy four transformed quad corners (in the given order) into the vertex positions.
#define SET_QUAD_POS(a, b, c, d)                          \
    do {                                                  \
        lbl_80366188.v[0].pos.x = q.pt[a].pos.x;          \
        lbl_80366188.v[0].pos.y = q.pt[a].pos.y;          \
        lbl_80366188.v[0].pos.z = q.pt[a].pos.z;          \
        lbl_80366188.v[1].pos.x = q.pt[b].pos.x;          \
        lbl_80366188.v[1].pos.y = q.pt[b].pos.y;          \
        lbl_80366188.v[1].pos.z = q.pt[b].pos.z;          \
        lbl_80366188.v[2].pos.x = q.pt[c].pos.x;          \
        lbl_80366188.v[2].pos.y = q.pt[c].pos.y;          \
        lbl_80366188.v[2].pos.z = q.pt[c].pos.z;          \
        lbl_80366188.v[3].pos.x = q.pt[d].pos.x;          \
        lbl_80366188.v[3].pos.y = q.pt[d].pos.y;          \
        lbl_80366188.v[3].pos.z = q.pt[d].pos.z;          \
    } while (0)

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
// NONMATCHING: ~90%, saved-register allocation differs (count/n/angle); .sdata2 constant names need a split
#if NONMATCHING
void fn_8000E030(CircleElem* elem, Mtx mtx, SpriteDrawParams* params) {
    Vec center;
    Vec pt;
    QuadVtx verts[259];
    QuadVtx* v;
    s32 count;
    s32 n;
    s32 step;
    s16 angle;
    f32 s;
    f32 a;
    f32 c;

    if (!elem->hidden || params->arcSegments != 0) {
        center.x = 128.0f;
        center.y = 128.0f;
        center.z = elem->z;
        PSMTXMultVec(mtx, &center, &verts[0].pos);
        verts[0].color = params->color[0];
        pt.x = 128.0f + center.x;
        pt.y = center.y;
        pt.z = elem->unk18 + elem->z;
        PSMTXMultVec(mtx, &pt, &verts[1].pos);
        verts[1].color = params->color[1];
        if (params->arcSegments != 0) {
            n = params->arcSegments;
            count = params->arcSegments + 2;
        } else {
            count = params->segments + 2;
            n = params->segments - 1;
        }
        step = 0x10000 / params->segments;
        v = &verts[2];
        angle = 0;
        do {
            angle -= step;
            a = 0.0000958738f * angle;
            s = sin(a);
            c = cos(a);
            pt.x = 128.0f * c + center.x;
            pt.y = 128.0f * s + center.y;
            pt.z = elem->z;
            PSMTXMultVec(mtx, &pt, &v->pos);
            v->color = params->color[1];
            v++;
        } while (--n);
        if (params->arcSegments == 0) {
            verts[params->segments + 1].pos.x = verts[1].pos.x;
            verts[params->segments + 1].pos.y = verts[1].pos.y;
            verts[params->segments + 1].pos.z = verts[1].pos.z;
            verts[params->segments + 1].color = params->color[1];
        }
        fn_800B12DC(verts, count);
    }
}
#endif

// .text:0x8000E2D4 size:0x490
// NONMATCHING: ~75% (with w left uninitialized as in the original): scheduling and float register allocation differ
#if NONMATCHING
void fn_8000E2D4(Circle2DElem* elem, Mtx mtx, SpriteDrawParams* params) {
    Vec pos[257];
    u32 colors[257];
    Vec* p;
    u32* c;
    s32 i;
    s32 n;
    s32 step;
    s16 angle;
    f32 x;
    f32 y;
    f32 w = 1.0f; // the original reads an uninitialized register here
    f32 px;
    f32 py;
    f32 a;
    f32 s;

    if (!elem->hidden || params->arcSegments != 0) {
        for (p = pos, i = 0; i < 257; i++, p++) {
            p->x = 0.0f;
            p->y = 0.0f;
            p->z = 0.0f;
        }
        colors[0] = params->color[0];
        angle = 0;
        y = 128 - elem->y;
        x = 128 - elem->x;
        pos[0].x = (s32)(mtx[0][0] * x + mtx[0][1] * y + mtx[0][3] * w);
        pos[0].y = (s32)(mtx[1][0] * x + mtx[1][1] * y + mtx[1][3] * w);
        pos[0].z = (s32)(mtx[2][0] * x + mtx[2][1] * y + mtx[2][3] * w);
        colors[1] = params->color[1];
        step = 0x10000 / params->segments;
        pos[1].x = (s32)(mtx[0][0] * (128.0f + x) + mtx[0][1] * (128.0f + y) + mtx[0][3] * w);
        pos[1].y = (s32)(mtx[1][0] * (128.0f + x) + mtx[1][1] * (128.0f + y) + mtx[1][3] * w);
        pos[1].z = (s32)(mtx[2][0] * (128.0f + x) + mtx[2][1] * (128.0f + y) + mtx[2][3] * w);
        n = params->segments;
        if (n != params->arcSegments) {
            n = params->arcSegments + 1;
        }
        p = &pos[n];
        c = &colors[n];
        do {
            angle -= step;
            a = 0.0000958738f * angle;
            s = sin(a);
            py = 128.0f * s + y;
            px = 128.0f * (f32)cos(a) + x;
            p->x = (s32)(mtx[0][0] * px + mtx[0][1] * py + mtx[0][3] * w);
            p->y = (s32)(mtx[1][0] * px + mtx[1][1] * py + mtx[1][3] * w);
            p->z = (s32)(mtx[2][0] * px + mtx[2][1] * py + mtx[2][3] * w);
            p--;
            *c = params->color[1];
            c--;
        } while (--n);
        if (params->segments == params->arcSegments) {
            pos[params->arcSegments + 1].x = pos[1].x;
            pos[params->arcSegments + 1].y = pos[1].y;
            pos[params->arcSegments + 1].z = pos[1].z;
            colors[params->arcSegments + 1] = params->color[1];
        }
        fn_800B13C0(pos, colors, params->arcSegments + 2);
    }
}
#endif

// .text:0x8000E764 size:0x58
void fn_8000E764(f32 angle, Vec2f* out) {
    out->x = sin(angle);
    out->y = cos(angle);
}

// .text:0x8000E7BC size:0x144
// NONMATCHING: matches except .sdata2 constant names (unit needs an .sdata2 split)
#if NONMATCHING
void fn_8000E7BC(SpriteElem* elem, Mtx mtx, SpriteDrawParams* params, s32 perCorner) {
    SpriteQuad q;

    q.xy[0][0] = 0.0f;
    q.xy[0][1] = 0.0f;
    q.xy[3][0] = 256.0f;
    q.xy[3][1] = 256.0f;
    q.xy[1][0] = 256.0f;
    q.xy[1][1] = 0.0f;
    q.xy[2][0] = 0.0f;
    q.xy[2][1] = 256.0f;
    AddVec2iToQuad(&q, mtx, params);
    lbl_80366188.unk7E = 0;
    lbl_80366188.elem = elem;
    lbl_80366188.v[0].color = params->color[0];
    lbl_80366188.v[0].pos.x = q.pt[0].pos.x;
    lbl_80366188.v[0].pos.y = q.pt[0].pos.y;
    lbl_80366188.v[0].pos.z = q.pt[0].pos.z;
    lbl_80366188.v[1].pos.x = q.pt[1].pos.x;
    lbl_80366188.v[1].pos.y = q.pt[1].pos.y;
    lbl_80366188.v[1].pos.z = q.pt[1].pos.z;
    lbl_80366188.v[2].pos.x = q.pt[3].pos.x;
    lbl_80366188.v[2].pos.y = q.pt[3].pos.y;
    lbl_80366188.v[2].pos.z = q.pt[3].pos.z;
    lbl_80366188.v[3].pos.x = q.pt[2].pos.x;
    lbl_80366188.v[3].pos.y = q.pt[2].pos.y;
    lbl_80366188.v[3].pos.z = q.pt[2].pos.z;
    lbl_80366188.perCornerColor = elem->perCorner | (perCorner | (elem->type == 2));
    if (lbl_80366188.perCornerColor) {
        lbl_80366188.v[1].color = params->color[3];
        lbl_80366188.v[2].color = params->color[2];
        lbl_80366188.v[3].color = params->color[1];
    } else {
        lbl_80366188.v[1].color = params->color[0];
        lbl_80366188.v[2].color = params->color[0];
        lbl_80366188.v[3].color = params->color[0];
    }
}
#endif

// .text:0x8000E900 size:0x30C
// NONMATCHING: matches except .sdata2 constant names (unit needs an .sdata2 split)
#if NONMATCHING
void SetSpriteRect(SpriteRectElem* elem, SpriteBank* bank, Mtx mtx, SpriteDrawParams* params, s32 perCorner) {
    SpriteQuad q;
    SpriteTexInfo* tex;
    f32 x = 0.0f;
    f32 y = 0.0f;

    tex = &bank->tex[bank->tex[elem->texIdx].texIndex];
    lbl_803CBBD8 = tex;
    q.xy[0][0] = x;
    q.xy[0][1] = y;
    q.xy[1][0] = x + tex->width;
    q.xy[1][1] = y;
    q.xy[2][0] = x;
    q.xy[2][1] = y + tex->height;
    q.xy[3][0] = q.xy[1][0];
    q.xy[3][1] = q.xy[2][1];
    AddVec2iToQuad(&q, mtx, params);
    lbl_80366188.unk7E = 0;
    lbl_80366188.v[0].color = params->color[0];
    lbl_80366188.v[1].color = params->color[1];
    lbl_80366188.v[2].color = params->color[2];
    lbl_80366188.v[3].color = params->color[3];
    if (elem->flipX && elem->flipY) {
        SET_QUAD_POS(3, 1, 0, 2);
    } else if (elem->flipX) {
        SET_QUAD_POS(1, 3, 2, 0);
    } else if (elem->flipY) {
        SET_QUAD_POS(2, 0, 1, 3);
    } else {
        SET_QUAD_POS(0, 2, 3, 1);
    }
    lbl_80366188.v[0].s = 0;
    lbl_80366188.v[0].t = 0;
    lbl_80366188.v[1].s = 0;
    lbl_80366188.v[1].t = 0x400;
    lbl_80366188.v[2].s = 0x400;
    lbl_80366188.v[2].t = 0x400;
    lbl_80366188.v[3].s = 0x400;
    lbl_80366188.v[3].t = 0;
    lbl_80366188.bank = bank;
    lbl_80366188.perCornerColor = perCorner | elem->perCorner;
}
#endif

// .text:0x8000EC0C size:0x310
// NONMATCHING: matches except .sdata2 constant names (unit needs an .sdata2 split)
#if NONMATCHING
void fn_8000EC0C(SpriteElem* elem, SpriteBank* bank, Mtx mtx, SpriteDrawParams* params, s32 perCorner) {
    SpriteQuad q;
    SpriteTexInfo* tex;
    f32 x = 0.0f;
    f32 y = 0.0f;

    tex = &bank->tex[bank->tex[elem->texIdx].texIndex];
    lbl_803CBBD8 = tex;
    q.xy[0][0] = x;
    q.xy[0][1] = y;
    q.xy[1][0] = x + tex->width;
    q.xy[1][1] = y;
    q.xy[2][0] = x;
    q.xy[2][1] = y + tex->height;
    q.xy[3][0] = q.xy[1][0];
    q.xy[3][1] = q.xy[2][1];
    AddVec2iToQuad(&q, mtx, params);
    lbl_80366188.unk7E = 0;
    lbl_80366188.elem = elem;
    lbl_80366188.v[0].color = params->color[0];
    lbl_80366188.v[1].color = params->color[1];
    lbl_80366188.v[2].color = params->color[2];
    lbl_80366188.v[3].color = params->color[3];
    if (elem->flipX && elem->flipY) {
        SET_QUAD_POS(3, 1, 0, 2);
    } else if (elem->flipX) {
        SET_QUAD_POS(1, 3, 2, 0);
    } else if (elem->flipY) {
        SET_QUAD_POS(2, 0, 1, 3);
    } else {
        SET_QUAD_POS(0, 2, 3, 1);
    }
    lbl_80366188.v[0].s = 0;
    lbl_80366188.v[0].t = 0;
    lbl_80366188.v[1].s = 0;
    lbl_80366188.v[1].t = 1;
    lbl_80366188.v[2].s = 1;
    lbl_80366188.v[2].t = 1;
    lbl_80366188.v[3].s = 1;
    lbl_80366188.v[3].t = 0;
    lbl_80366188.bank = bank;
    lbl_80366188.perCornerColor = perCorner | elem->perCorner;
}
#endif

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
