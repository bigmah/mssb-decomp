#include "game/auto_00_0015C230_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80024184.h"
#include "Dolphin/gx.h"

extern struct {
    u8 _00[4];
    TexArchive* textures;
} lbl_3_common_bss_35154;

// .text:0x0015C230 size:0x1C8 mapped:0x8079B2C4
void fn_3_15C230(BallQuad* q) {
    s32 sel;
    u32 color;

    gOz_GXSetTexture(0, 0, 0);
    GXSetBlendMode(1, 4, 1, 0);
    GXSetZMode(1, 3, 0);
    SetDisplayStateTexture(&lbl_3_common_bss_35154.textures->entries[23], 0, 0);
    GXSetProjectionv(q->proj);
    GXLoadPosMtxImm(q->m, 0);
    GXSetCurrentMtx(0);
    GXSetCullMode(0);
    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        sel = 2;
    } else {
        sel = g_Ball.framesSinceHit > 0;
    }
    if (sel == 2) {
        color = lbl_3_data_273D4.color | 0xFFFFFF00;
    } else {
        color = lbl_3_data_273CC.color | 0xFFFFFF00;
    }
    GXBegin(0x80, 0, 4);
    GXPosition3f32(q->v[0].x, q->v[0].y, q->v[0].z);
    GXColor1u32(color);
    GXTexCoord2s16(0, 0);
    GXPosition3f32(q->v[1].x, q->v[1].y, q->v[1].z);
    GXColor1u32(color);
    GXTexCoord2s16(1, 0);
    GXPosition3f32(q->v[2].x, q->v[2].y, q->v[2].z);
    GXColor1u32(color);
    GXTexCoord2s16(1, 1);
    GXPosition3f32(q->v[3].x, q->v[3].y, q->v[3].z);
    GXColor1u32(color);
    GXTexCoord2s16(0, 1);
    (*q->counter)--;
}

