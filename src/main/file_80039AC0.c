#include "main/file_80039AC0.h"
#include "main/file_80037054.h"
#include "main/file_800B0724.h"
#include "main/file_800BDEA0.h"
#include "Dolphin/GX.h"
#include "Dolphin/OS/OSThread.h"
#include "stl/string.h"
#include "stl/stdlib.h"

extern OSThread* GXGetCurrentGXThread(void);
extern void DrawSprite_TexObj(SpriteVertex* verts, TexDesc* tex);
extern void SetDisplayStateTexture(void* object, s32 map, s32 b);
extern void fn_800A7D4C(s32 list, void* node);
extern void fn_800B24D4(u32);
extern void fn_800BD1E8(void (*func)(Mtx, s32*, s32*, s32*, u8*, u8*));

extern TexDesc lbl_800F7A40;
extern ScreenFxNode lbl_800F7A60[];
extern TexDesc lbl_800F7AE0;
extern u8 lbl_8023DD80[];
extern TrailSystem lbl_802D3D80;
extern ScreenFx lbl_803C5090;
extern f32 lbl_803CB82C;
extern u8 lbl_803CBBC0;

// .text:0x80039AC0 size:0x538
void fn_80039AC0(void) {
    return;
}

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
    lbl_803C5090.scale = 0.5f;
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
    lbl_800F7AE0.image = GetUITexture();
    SetDisplayStateTexture(&lbl_800F7AE0, *map, 0);
    GXSetTevOrder(*stage, *coord, *map, GX_COLOR0A0);
    GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_CPREV);
    GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTexCoordGen2(*coord, GX_TG_MTX2X4, GX_TG_POS, *texMtx * 3 + GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
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
