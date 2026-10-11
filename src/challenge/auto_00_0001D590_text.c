#include "challenge/auto_00_0001D590_text.h"
#include "Dolphin/os.h"
#include "string.h"

// Start of the texture image header (TexImage in main/file_80024184.h).
typedef struct ChTexImage {
    /*0x0*/ u8* data;
    /*0x4*/ void* tlut;
    /*0x8*/ u16 height;
    /*0xA*/ u16 width;
} ChTexImage;

extern s32 fn_80023F0C(struct TexImage* src, struct TexImage* dst, s32 srcX, s32 srcY, s32 width,
                       s32 height, s32 dstX, s32 dstY);
extern u8 lbl_803CBBC0; // frame buffer index (0/1)

// .text:0x0001D590 size:0x104
// Clears `dst` and fills it with cellW x cellH tiles of `src`; map[row * cols + col] picks the tile.
// Only columns with (col & lbl_803CBBC0) set are drawn.
// NONMATCHING 99%: r29/r30 swapped for the inner-loop x and map pointer induction variables
#if NONMATCHING
void fn_1_1D590(struct TexImage* src, struct TexImage* dst, u8* map, s32 cellW, s32 cellH) {
    ChTexImage* img = (ChTexImage*)dst;
    s32 row;
    s32 col;
    s32 rows;
    s32 cols;
    s32 tile;

    memset(img->data, 0, img->width * img->height);
    rows = img->height / cellH;
    cols = img->width / cellW;
    for (row = 0; row < rows; row++) {
        for (col = 0; col < cols; col++) {
            if (col & lbl_803CBBC0) {
                tile = map[row * cols + col];
                fn_80023F0C(src, dst, cellW * (tile % cols), cellH * (tile / cols), cellW, cellH,
                            col * cellW, row * cellH);
            }
        }
    }
    DCStoreRange(img->data, img->width * img->height);
}
#endif
