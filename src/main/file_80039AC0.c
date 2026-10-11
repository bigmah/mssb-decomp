#include "main/file_80039AC0.h"
#include "main/file_80037054.h"
#include "main/file_800B0724.h"
#include "main/file_800BDEA0.h"
#include "Dolphin/GX.h"
#include "Dolphin/OS/OSThread.h"
#include "stl/string.h"
#include "stl/stdlib.h"

extern OSThread* GXGetCurrentGXThread(void);
extern void fn_800A7D4C(s32 list, void* node);
extern void fn_800BD1E8(void (*func)(Mtx, s32*, s32*, s32*, u8*, u8*));

extern TexImage lbl_800F7A40;
extern ScreenFxNode lbl_800F7A60[];
extern TexImage lbl_800F7AE0;
extern u8 lbl_8023DD80[];
extern TrailSystem lbl_802D3D80;
extern ScreenFx lbl_803C5090;
extern f32 lbl_803CB82C;
extern u8 lbl_803CBBC0;
extern const f32 lbl_803CC7A0; // 640
extern const f32 lbl_803CC7A4; // 1280
extern const f32 lbl_803CC7A8; // 0.5
extern const f32 lbl_803CC7AC; // 0.125
extern const f32 lbl_803CC7B0; // 448
extern const f32 lbl_803CC7B4; // 255
extern const f32 lbl_803CC7B8; // 0
extern const f32 lbl_803CC7BC; // -1

// .text:0x80039AC0 size:0x538
typedef struct GridPoint {
    f32 x;
    f32 y;
} GridPoint;

// NONMATCHING 96%: the original reads r/g/b as one (big-endian) word for the vertex color, and
// the float constants / u16 texture coordinates get different registers.
#if NONMATCHING
void fn_80039AC0(void) {
    GridPoint grid[9][9];
    QuadVtx v[4];
    u32 color;
    s32 y;
    s32 x;
    u16 s;
    u16 t;
    u16 t0;
    f32 z;
    f32 halfW;
    f32 halfH;
    u8 mode;
    f32 rnd;

    if (lbl_803C5090.flags & 8) {
        color = ((lbl_803C5090.r << 24) | (lbl_803C5090.g << 16) | (lbl_803C5090.b << 8)) | lbl_803C5090.alpha;
    } else {
        color = 0xFFFFFF00;
    }
    fn_800B24D4(11);
    fn_800B216C(1, 3, 0);
    mode = 1;
    if (lbl_803C5090.unk18 != 0) {
        mode = 2;
    }
    fn_800B2160(mode);

    if (lbl_803C5090.flags & 4) {
        // 9x9 grid of jittered points
        for (y = 0; y <= 8; y++) {
            for (x = 0; x <= 8; x++) {
                halfW = lbl_803CC7A0 * lbl_803C5090.scale / lbl_803CC7A4;
                halfH = lbl_803CC7B0 * lbl_803C5090.scale / lbl_803CC7A4;
                grid[y][x].x = -halfW * lbl_803CC7A8 + halfW * x * lbl_803CC7AC;
                grid[y][x].y = -halfH * lbl_803CC7A8 + halfH * y * lbl_803CC7AC;
                rnd = (rand() & 0xFF) / lbl_803CC7B4;
                grid[y][x].x += lbl_803C5090.scale * (lbl_803C5090.jitterX * lbl_803CC7A8 - lbl_803C5090.jitterX * rnd) / lbl_803CC7A4;
                if ((x == 0 && grid[y][x].x > lbl_803CC7B8) || (8 - x == 0 && grid[y][x].x < lbl_803CC7B8)) {
                    grid[y][x].x *= lbl_803CC7BC;
                }
                rnd = (rand() & 0xFF) / lbl_803CC7B4;
                grid[y][x].y += lbl_803C5090.scale * (lbl_803C5090.jitterY * lbl_803CC7A8 - lbl_803C5090.jitterY * rnd) / lbl_803CC7A4;
                if ((y == 0 && grid[y][x].y > lbl_803CC7B8) || (8 - y == 0 && grid[y][x].y < lbl_803CC7B8)) {
                    grid[y][x].y *= lbl_803CC7BC;
                }
            }
        }

        t = 0;
        for (y = 0; y < 8; y++) {
            t0 = t;
            t = t0 + 0x80;
            s = 0;
            for (x = 0; x < 8; x++) {
                z = -lbl_803C5090.scale;
                v[0].pos.x = grid[y][x].x;
                v[0].pos.y = grid[y][x].y;
                v[0].pos.z = z;
                v[0].color = color;
                v[0].s = s;
                v[0].t = t0;
                v[1].pos.x = grid[y + 1][x].x;
                v[1].pos.y = grid[y + 1][x].y;
                v[1].pos.z = z;
                v[1].color = color;
                v[1].s = s;
                v[1].t = t;
                v[2].pos.x = grid[y + 1][x + 1].x;
                v[2].pos.y = grid[y + 1][x + 1].y;
                v[2].pos.z = z;
                v[2].color = color;
                v[2].s = s + 0x80;
                v[2].t = t;
                v[3].pos.x = grid[y][x + 1].x;
                v[3].pos.y = grid[y][x + 1].y;
                v[3].pos.z = z;
                v[3].color = color;
                v[3].s = s + 0x80;
                v[3].t = t0;
                do {
                    DrawSprite_TexObj(v, &lbl_800F7A40);
                    lbl_803C5090.repeat -= (lbl_803C5090.repeat != 0);
                } while (lbl_803C5090.repeat != 0);
                s += 0x80;
            }
            if (t >= (lbl_803C5090.lines << 10) / 448) {
                break;
            }
        }
    } else {
        z = -lbl_803C5090.scale;
        halfW = lbl_803CC7A0 * lbl_803C5090.scale / lbl_803CC7A4;
        halfH = lbl_803CC7B0 * lbl_803C5090.scale / lbl_803CC7A4;
        v[0].pos.x = -halfW * lbl_803CC7A8;
        v[0].pos.y = -halfH * lbl_803CC7A8;
        v[0].pos.z = z;
        v[0].color = color;
        v[0].s = 0;
        v[0].t = 0;
        v[1].pos.x = -halfW * lbl_803CC7A8;
        v[1].pos.y = -halfH * lbl_803CC7A8 + lbl_803C5090.lines * lbl_803C5090.scale / lbl_803CC7A4;
        v[1].pos.z = z;
        v[1].color = color;
        v[1].s = 0;
        v[1].t = (lbl_803C5090.lines << 10) / 448;
        v[2].pos.x = halfW * lbl_803CC7A8;
        v[2].pos.y = v[1].pos.y;
        v[2].pos.z = z;
        v[2].color = color;
        v[2].s = 0x400;
        v[2].t = v[1].t;
        v[3].pos.x = halfW * lbl_803CC7A8;
        v[3].pos.y = v[0].pos.y;
        v[3].pos.z = z;
        v[3].color = color;
        v[3].s = 0x400;
        v[3].t = 0;
        do {
            DrawSprite_TexObj(v, &lbl_800F7A40);
            lbl_803C5090.repeat -= (lbl_803C5090.repeat != 0);
        } while (lbl_803C5090.repeat != 0);
    }
}
#endif

// .text:0x80039FF8 size:0x98
void fn_80039FF8(ScreenFxNode* node) {
    u16 width;
    u16 height;

    if (node->fx.flags & 1) {
        height = node->fx.height;
        width = node->fx.width;
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(width, height, GX_TF_RGB565, width != 640);
        GXCopyTex(lbl_8023DD80, GX_FALSE);
        GXPixModeSync();
        lbl_800F7A40.width = width;
        lbl_800F7A40.height = height;
    }
}

// .text:0x8003A090 size:0xB4
void fn_8003A090(void) {
    OSThread* thread = OSGetCurrentThread();
    u16 width;
    u16 height;

    if (GXGetCurrentGXThread() == thread && (lbl_803C5090.flags & 0x11)) {
        height = lbl_803C5090.height;
        width = lbl_803C5090.width;
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(width, height, GX_TF_RGB565, width != 640);
        GXCopyTex(lbl_8023DD80, GX_FALSE);
        GXPixModeSync();
        lbl_800F7A40.width = width;
        lbl_800F7A40.height = height;
    }
}

// .text:0x8003A144 size:0x8C
void fn_8003A144(void) {
    OSThread* thread = OSGetCurrentThread();

    if (GXGetCurrentGXThread() == thread) {
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(640, 448, GX_TF_RGB565, GX_FALSE);
        GXCopyTex(lbl_8023DD80, GX_FALSE);
        GXPixModeSync();
        lbl_800F7A40.width = 640;
        lbl_800F7A40.height = 448;
    }
}

// .text:0x8003A1D0 size:0xF0
void fn_8003A1D0(void) {
    ScreenFxNode* node;

    if (lbl_803C5090.flags & 2) {
        lbl_803C5090.width = 320;
        lbl_803C5090.height = 224;
        lbl_800F7A40.width = 320;
        lbl_800F7A40.height = 224;
    } else {
        lbl_803C5090.width = 640;
        lbl_803C5090.height = 448;
        lbl_800F7A40.width = 640;
        lbl_800F7A40.height = 448;
    }
    if ((lbl_803C5090.flags & 0x11) == 1) {
        node = &lbl_800F7A60[lbl_803CBBC0];
        node->fx = lbl_803C5090;
        fn_800A7D4C(8, node);
    }
    fn_80039AC0();
    ((void (*)(void))fn_800B0A14_removeQueue)();
}

// .text:0x8003A2C0 size:0x2C
void fn_8003A2C0(void) {
    fn_800B0A5C_insertQueue((void*)fn_8003A1D0, 0x6001);
}

// .text:0x8003A2EC size:0x90
void fn_8003A2EC(void) {
    lbl_803C5090.flags = 1;
    lbl_803C5090.alpha = 0x60;
    lbl_803C5090.scale = 30.0f;
    lbl_803C5090.jitterX = 1.0f;
    lbl_803C5090.jitterY = 1.0f;
    lbl_803C5090.width = 320;
    lbl_803C5090.height = 224;
    memset(lbl_8023DD80, 0, 0x96000);
    lbl_803C5090.lines = 448;
    lbl_803C5090.r = 0xFF;
    lbl_803C5090.g = 0xFF;
    lbl_803C5090.b = 0xFF;
}

// .text:0x8003A37C size:0x14C
void fn_8003A37C(Mtx mtx, s32* stage, s32* coord, s32* map, u8* count, u8* texMtx) {
    lbl_800F7AE0.data = GetUITexture();
    SetDisplayStateTexture(&lbl_800F7AE0, *map, 0);
    GXSetTevOrder(*stage, *coord, *map, GX_COLOR0A0);
    GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_CPREV);
    GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, GX_TG_POS, *texMtx * 3 + GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXLoadTexMtxImm(mtx, *texMtx * 3 + GX_TEXMTX0, GX_MTX3x4);
    (*count)++;
    (*texMtx)++;
    (*stage)++;
    (*coord)++;
    (*map)++;
}

// .text:0x8003A4C8 size:0x70
void fn_8003A4C8(void) {
    if (GetDrawShadows()) {
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(640, 448, GX_TF_RGB565, GX_FALSE);
        GXCopyTex(GetUITexture(), GX_TRUE);
        GXPixModeSync();
        fn_800BEB3C();
        fn_800BD1E8(fn_8003A37C);
    }
}

extern u32 lbl_803CBCA8;

extern u32 lbl_803CBCB0;

// fn_8003A538, size:0x8
u32 fn_8003A538(void) {
    return lbl_803CBCB0;
}

// fn_8003A540, size:0x8
void fn_8003A540(u32 value) {
    lbl_803CBCB0 = value;
}

// fn_8003A548, size:0x8
void fn_8003A548(u32 value) {
    lbl_803CBCA8 = value;
}

// .text:0x8003A550 size:0x138
void fn_8003A550(s32 type, Vec* pos, Vec* dir, u8 flag) {
    f32 tmp;
    u16 head;

    head = lbl_802D3D80.head;
    if (lbl_802D3D80.enabled) {
        lbl_802D3D80.entries[head].type = type;
        lbl_802D3D80.entries[head].pos = *pos;
        PSVECNormalize(dir, &lbl_802D3D80.entries[head].dir);
        PSVECScale(&lbl_802D3D80.entries[head].dir, lbl_802D3D80.params[type].speed, &lbl_802D3D80.entries[head].vel);
        tmp = -lbl_802D3D80.entries[head].vel.z;
        lbl_802D3D80.entries[head].vel.z = lbl_802D3D80.entries[head].vel.x;
        lbl_802D3D80.entries[head].vel.x = tmp;
        PSVECScale(&lbl_802D3D80.entries[head].dir, lbl_802D3D80.params[type].spread, &lbl_802D3D80.entries[head].dir);
        lbl_802D3D80.entries[head].dir.y = lbl_803CB82C;
        lbl_802D3D80.entries[head].alpha = 0xFF;
        lbl_802D3D80.entries[head].flag = flag;
        {
            s32 next = (head + 1) % 64;
            lbl_802D3D80.head = next;
            lbl_802D3D80.tail = (lbl_802D3D80.tail + ((u16)next == lbl_802D3D80.tail)) % 64;
        }
    }
}
