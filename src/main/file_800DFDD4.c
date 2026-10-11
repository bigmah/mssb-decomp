#include "main/file_800DFDD4.h"

typedef struct HVQDivTables {
    /*0x000*/ s32 divTable[16];
    /*0x040*/ s32 mcdivTable[0x200];
} HVQDivTables;

extern s32 lbl_80117FE0[16]; // IMA ADPCM index table
extern s32 lbl_80118020[89]; // IMA ADPCM step table
extern u8 lbl_80328DA0[0x200]; // clip table: [i] = clamp(i - 0x80, 0, 0xFF)
extern HVQDivTables lbl_80328FA0;
extern s32 lbl_803CC3F8; // tree being read holds signed values
extern s32 lbl_803CC3FC; // left shift applied to tree leaf values

// Macroblock prediction mode transitions, indexed by [bit][current mode].
const s32 lbl_800E82D8[2][3] = {
    { 1, 2, 0 },
    { 2, 0, 1 },
};

// Reads one bit (MSB first) into out; nonzero if set.
#define HVQ_READBIT(b, out)                \
    do {                                   \
        if ((b)->mask == 0) {              \
            (b)->byte = *(b)->ptr++;       \
            (b)->mask = 0x80;              \
        }                                  \
        (out) = (b)->byte & (b)->mask;     \
        (b)->mask >>= 1;                   \
    } while (0)

// Decodes one Huffman symbol from bt (an HVQBitBufTree*) into out (fn_800E0CC8 inlined).
#define HVQ_DECODE(bt, out)                               \
    do {                                                  \
        HVQTree* tree_ = (bt)->tree;                      \
        s16 pos_ = tree_->root;                           \
        u8 bit_;                                          \
        while (pos_ >= 0x100) {                           \
            HVQ_READBIT(&(bt)->buf, bit_);                \
            if (bit_) {                                   \
                pos_ = tree_->node[1][pos_];              \
            } else {                                      \
                pos_ = tree_->node[0][pos_];              \
            }                                             \
        }                                                 \
        (out) = tree_->node[0][pos_];                     \
    } while (0)

#define HVQ_READ_BE32(p) (((u32)(p)[0] << 24) | ((p)[1] << 16) | ((p)[2] << 8) | (p)[3])

// Points b at the stream whose offset (from data) is stored big-endian at offs.
// Each stream starts with its big-endian size.
#define HVQ_INIT_BITBUF(b, data, offs)                     \
    do {                                                   \
        u8* p_ = (data) + HVQ_READ_BE32(offs);             \
        (b)->size = HVQ_READ_BE32(p_);                     \
        if ((b)->size == 0) {                              \
            (b)->start = (b)->ptr = NULL;                  \
        } else {                                           \
            (b)->start = (b)->ptr = p_ + 4;                \
        }                                                  \
        (b)->mask = 0;                                     \
    } while (0)

// Reads the Huffman tree of bt (an HVQBitBufTree) from its own stream.
#define HVQ_READ_TREE(bt, isSigned, shift)                        \
    do {                                                          \
        tree = (bt).tree;                                         \
        lbl_803CC3F8 = (isSigned);                                \
        lbl_803CC3FC = (shift);                                   \
        tree->pos = 0x100;                                        \
        if ((bt).buf.size != 0) {                                 \
            tree->root = fn_800E0904(tree, &(bt).buf);            \
        } else {                                                  \
            tree->root = 0;                                       \
        }                                                         \
    } while (0)

#pragma dont_inline on

// .text:0x800DFDD4 size:0x6B4
void fn_800DFDD4(u8* src, u8* dst, u32 numChannels, u32 format, u32 count, void* chans) {
    return;
}

// .text:0x800E0488 size:0x360
// NONMATCHING 75%: clip and div tables are separate externs here; the original addresses both from one base (static bss in this TU)
#if NONMATCHING
void fn_800E0488(void) {
    s32 i;

    for (i = 0; i < 0x200; i++) {
        s32 v = i - 0x80;
        lbl_80328DA0[i] = v < 0 ? 0 : (v > 0xFF ? 0xFF : v);
    }
    lbl_80328FA0.divTable[0] = 0;
    for (i = 1; i < 16; i++) {
        lbl_80328FA0.divTable[i] = (0x1000 / (i * 16)) * 16;
    }
    lbl_80328FA0.mcdivTable[0] = 0;
    for (i = 1; i < 0x200; i++) {
        lbl_80328FA0.mcdivTable[i] = 0x1000 / i;
    }
}
#endif

// .text:0x800E07E8 size:0x11C
void fn_800E07E8(HVQM4SeqObj* seq, s32 planeIdx, u8 hSamp, u8 vSamp) {
    HVQPlaneDesc* plane = &seq->state->planes[planeIdx];
    u16 stride;
    s32 rowBytes;

    plane->widthShift = hSamp == 2 ? 1 : 0;
    plane->widthInSamples = seq->frameWidth >> plane->widthShift;
    plane->heightShift = vSamp == 2 ? 1 : 0;
    plane->heightInSamples = seq->frameHeight >> plane->heightShift;
    plane->sizeInSamples = plane->widthInSamples * plane->heightInSamples;
    plane->widthInMB = 2 >> plane->widthShift;
    plane->heightInMB = 2 >> plane->heightShift;
    plane->blocksPerMB = plane->widthInMB * plane->heightInMB;
    plane->widthInBlocks = seq->frameWidth / (hSamp * 4);
    plane->heightInBlocks = seq->frameHeight / (vSamp * 4);
    plane->blocksPerRow = plane->widthInBlocks + 2;
    plane->rowsWithBorder = plane->heightInBlocks + 2;
    plane->blockOffs[0] = 0;
    plane->blockOffs[3] = 1;
    stride = plane->blocksPerRow;
    plane->blockOffs[1] = stride;
    plane->blockOffs[2] = stride + 1;
    plane->pixelOffs[0] = 0;
    plane->pixelOffs[3] = 4;
    rowBytes = plane->widthInSamples * 4;
    plane->pixelOffs[1] = rowBytes;
    plane->pixelOffs[2] = rowBytes + 4;
}

// .text:0x800E0904 size:0x3C4
// NONMATCHING 98%: original frame is 16 bytes larger (unused locals?), r5/r6 swapped; leaf shift written as a multiply (negative values)
#if NONMATCHING
s16 fn_800E0904(HVQTree* tree, HVQBitBuf* buf) {
    u8 bit;
    s32 pos;
    s16 value;
    s16 leaf;

    HVQ_READBIT(buf, bit);
    if (bit) {
        pos = tree->pos++;
        tree->node[0][pos] = fn_800E0904(tree, buf);
        tree->node[1][pos] = fn_800E0904(tree, buf);
        return pos;
    }
    HVQ_READBIT(buf, bit);
    value = bit ? 0x80 : 0;
    HVQ_READBIT(buf, bit);
    value |= bit ? 0x40 : 0;
    HVQ_READBIT(buf, bit);
    value |= bit ? 0x20 : 0;
    HVQ_READBIT(buf, bit);
    value |= bit ? 0x10 : 0;
    HVQ_READBIT(buf, bit);
    value |= bit ? 8 : 0;
    HVQ_READBIT(buf, bit);
    value |= bit ? 4 : 0;
    HVQ_READBIT(buf, bit);
    value |= bit ? 2 : 0;
    HVQ_READBIT(buf, bit);
    value |= bit ? 1 : 0;
    leaf = value;
    if (lbl_803CC3F8 != 0 && value > 0x7F) {
        leaf -= 0x100;
    }
    tree->node[0][value] = leaf * (1 << lbl_803CC3FC);
    return value;
}
#endif

// .text:0x800E0CC8 size:0x98
s16 fn_800E0CC8(HVQBitBufTree* buf) {
    HVQTree* tree = buf->tree;
    s16 pos = tree->root;

    u8 bit;

    while (pos >= 0x100) {
        HVQ_READBIT(&buf->buf, bit);
        if (bit) {
            pos = tree->node[1][pos];
        } else {
            pos = tree->node[0][pos];
        }
    }
    return tree->node[0][pos];
}

// .text:0x800E0D60 size:0x354
// NONMATCHING 87%: register allocation; original frame has extra locals
#if NONMATCHING
void fn_800E0D60(HVQState* state) {
    HVQBlock* blk;
    HVQBlock* blkV;
    u16 width;
    u16 y;
    s32 x;
    s32 run;
    s16 value;

    // luma basis counts
    run = 0;
    blk = state->planes[0].payload;
    width = state->planes[0].widthInBlocks;
    for (y = state->planes[0].heightInBlocks; y > 0; y--) {
        for (x = width; x > 0; x--) {
            if (run == 0) {
                HVQ_DECODE(&state->basisNum[0], value);
                if (value == 0) {
                    HVQ_DECODE(&state->basisNumRun[0], run);
                }
                blk->type = value;
                blk++;
            } else {
                blk->type = 0;
                blk++;
                run--;
            }
        }
        blk += 2;
    }

    // chroma basis counts: U in the low nibble, V in the high nibble
    blk = state->planes[1].payload;
    blkV = state->planes[2].payload;
    width = state->planes[1].widthInBlocks;
    y = state->planes[1].heightInBlocks;
    run = 0;
    for (; y > 0; y--) {
        for (x = width; x > 0; x--) {
            if (run == 0) {
                HVQ_DECODE(&state->basisNum[1], value);
                if (value == 0) {
                    HVQ_DECODE(&state->basisNumRun[1], run);
                }
                blk->type = value & 0xF;
                blk++;
                blkV->type = (value >> 4) & 0xF;
                blkV++;
            } else {
                blk->type = 0;
                run--;
                blk++;
                blkV->type = 0;
                blkV++;
            }
        }
        blk += 2;
        blkV += 2;
    }
}
#endif

// .text:0x800E10B4 size:0x114
// NONMATCHING 79%: register allocation
#if NONMATCHING
void fn_800E10B4(HVQState* state) {
    s32 i;
    HVQPlaneDesc* plane;

    for (i = 0, plane = state->planes; i < 3; i++, plane++) {
        u16 width = plane->widthInBlocks;
        HVQBlock* cur = plane->payload;
        s32 y = plane->heightInBlocks;
        s32 stride = plane->blocksPerRow;
        s32 run = 0;

        for (; y > 0; y--) {
            HVQBlock* above = cur - stride;
            s32 pred = above->value;
            s32 x;

            for (x = width; x > 0; x--) {
                s16 delta;
                u8 dc;
                u8 next;

                if (run == 0) {
                    s16 max = state->dcMax;
                    s16 sum = 0;
                    s16 min = state->dcMin;
                    s16 v;

                    do {
                        do {
                            v = fn_800E0CC8(&state->dcValues[i]);
                            sum += v;
                        } while (min >= v);
                    } while (v >= max);
                    delta = sum;
                    if (delta == 0) {
                        run = fn_800E0CC8(&state->dcRle[i]);
                    }
                } else {
                    delta = 0;
                    run--;
                }
                dc = pred + delta;
                next = above[1].value;
                above++;
                cur->value = dc;
                pred = (next + dc + 1) >> 1;
                cur++;
            }
            cur += 2;
        }
    }
}
#endif

// .text:0x800E11C8 size:0x3A4
// NONMATCHING 51%: copy loops unrolled/allocated differently
#if NONMATCHING
void fn_800E11C8(HVQState* state, s32 nestX, s32 nestY) {
    u16 stride = state->planes[0].blocksPerRow;
    u16 width = state->planes[0].widthInBlocks;
    u16 nestWidth = state->nestWidth;
    u16 height = state->planes[0].heightInBlocks;
    HVQBlock* src = state->planes[0].payload + nestX + nestY * stride;
    u16 copyW;
    s32 mirrorW;
    s32 zeroW;
    u16 copyH;
    s32 mirrorH;
    s32 zeroH;
    u8* dst;
    u8* srcRow;
    u16 y;
    s32 n;

    if (width < nestWidth) {
        mirrorW = nestWidth - width;
        copyW = width;
        if (mirrorW > width) {
            mirrorW = width;
        }
        zeroW = nestWidth - (width + mirrorW);
    } else {
        copyW = nestWidth;
        zeroW = 0;
        mirrorW = 0;
    }
    if (height < state->nestHeight) {
        mirrorH = state->nestHeight - height;
        copyH = height;
        if (mirrorH > height) {
            mirrorH = height;
        }
        zeroH = state->nestHeight - (height + mirrorH);
    } else {
        copyH = state->nestHeight;
        zeroH = 0;
        mirrorH = 0;
    }

    dst = state->nest;
    for (y = copyH; y > 0; y--) {
        HVQBlock* blk = src;
        u16 x;

        for (x = copyW; x > 0; x--) {
            *dst++ = (blk->value >> 4) & 0xF;
            blk++;
        }
        for (n = mirrorW; n > 0; n--) {
            blk--;
            *dst++ = (blk->value >> 4) & 0xF;
        }
        for (n = zeroW; n > 0; n--) {
            *dst++ = 0;
        }
        src += stride;
    }

    srcRow = dst - state->nestWidth;
    for (n = mirrorH; n > 0; n--) {
        u8* p = srcRow;
        u16 x;

        for (x = state->nestWidth; x > 0; x--) {
            *dst++ = *p++;
        }
        srcRow -= state->nestWidth;
    }
    for (n = zeroH; n > 0; n--) {
        u16 x;

        for (x = state->nestWidth; x > 0; x--) {
            *dst++ = 0;
        }
    }
}
#endif

// .text:0x800E156C size:0x19C
// NONMATCHING 31%: clip lookups compile to add+lbz instead of lbzx; register allocation
#if NONMATCHING
void fn_800E156C(u8* dst, s32 stride, u8 dc, u8 top, u8 bottom, u8 left, u8 right) {
    s32 dc2 = dc * 2;
    s32 tb = top - bottom;
    s32 lr = left - right;
    s32 base = ((dc + 0x80) << 3) + 4;
    s32 tl = top + left - dc2;
    s32 tr = top + right - dc2;
    s32 sum = tb + lr;
    s32 diff = tb - lr;
    s32 baseSum = base + sum;
    s32 br = bottom + right - dc2;
    s32 tmL = top - left;
    s32 tmR = top - right;
    s32 baseDiff;
    s32 bl;
    s32 baseNDiff;
    s32 bmL;
    s32 bmR;
    s32 baseNSum;
    u8* clip;

    clip = lbl_80328DA0;
    dst[0] = clip[(tl + baseSum) >> 3];
    baseDiff = base + diff;
    dst[1] = clip[(tmL + baseSum) >> 3];
    bl = left + bottom - dc2;
    dst[2] = clip[(tmR + baseDiff) >> 3];
    baseNDiff = base - diff;
    bmL = bottom - left;
    dst[3] = clip[(tr + baseDiff) >> 3];
    dst += stride;
    dst[0] = clip[(baseSum - tmL) >> 3];
    dst[1] = clip[(base - br) >> 3];
    bmR = bottom - right;
    dst[2] = clip[(base - bl) >> 3];
    baseNSum = base - sum;
    dst[3] = clip[(baseDiff - tmR) >> 3];
    dst += stride;
    dst[0] = clip[(baseNDiff - bmL) >> 3];
    dst[1] = clip[(base - tr) >> 3];
    dst[2] = clip[(base - tl) >> 3];
    dst[3] = clip[(baseNSum - bmR) >> 3];
    dst += stride;
    dst[0] = clip[(bl + baseNDiff) >> 3];
    dst[1] = clip[(bmL + baseNDiff) >> 3];
    dst[2] = clip[(bmR + baseNSum) >> 3];
    dst[3] = clip[(br + baseNSum) >> 3];
}
#endif

// .text:0x800E1708 size:0x4AC
// NONMATCHING 85%: row pointer arithmetic order and register allocation
#if NONMATCHING
s32 fn_800E1708(HVQState* state, u8* basis, s32* sum, u8* src, s32 srcStride, s32 planeIdx) {
    u8 hi = *state->fixvl[planeIdx].ptr++;
    u8 lo = *state->fixvl[planeIdx].ptr++;
    u16 bits = (hi << 8) | lo;
    u8* row;
    u8* p;
    s32 xStep;
    s32 yStep;
    u8 max;
    u8 min;
    s16 value;
    s32 inverse;

    if (state->isLandscape) {
        row = src + ((bits >> 6) & 0x1F) * srcStride;
        row += bits & 0x3F;
        xStep = 1 << ((bits >> 11) & 1);
        yStep = srcStride << ((bits >> 12) & 1);
    } else {
        row = src + (bits & 0x3F) * srcStride;
        row += (bits >> 6) & 0x1F;
        xStep = 1 << ((bits >> 12) & 1);
        yStep = srcStride << ((bits >> 11) & 1);
    }
    // 4x4 samples, unrolled; track the value range
    basis[0] = *row;
    max = min = basis[0];
    p = row + xStep;
    if ((basis[1] = *p) > max) {
        max = basis[1];
    }
    if (basis[1] < min) {
        min = basis[1];
    }
    p += xStep;
    if ((basis[2] = *p) > max) {
        max = basis[2];
    }
    if (basis[2] < min) {
        min = basis[2];
    }
    p += xStep;
    if ((basis[3] = *p) > max) {
        max = basis[3];
    }
    if (basis[3] < min) {
        min = basis[3];
    }
    row += yStep;
    if ((basis[4] = *row) > max) {
        max = basis[4];
    }
    if (basis[4] < min) {
        min = basis[4];
    }
    p = row + xStep;
    if ((basis[5] = *p) > max) {
        max = basis[5];
    }
    if (basis[5] < min) {
        min = basis[5];
    }
    p += xStep;
    if ((basis[6] = *p) > max) {
        max = basis[6];
    }
    if (basis[6] < min) {
        min = basis[6];
    }
    p += xStep;
    if ((basis[7] = *p) > max) {
        max = basis[7];
    }
    if (basis[7] < min) {
        min = basis[7];
    }
    row += yStep;
    if ((basis[8] = *row) > max) {
        max = basis[8];
    }
    if (basis[8] < min) {
        min = basis[8];
    }
    p = row + xStep;
    if ((basis[9] = *p) > max) {
        max = basis[9];
    }
    if (basis[9] < min) {
        min = basis[9];
    }
    p += xStep;
    if ((basis[10] = *p) > max) {
        max = basis[10];
    }
    if (basis[10] < min) {
        min = basis[10];
    }
    p += xStep;
    if ((basis[11] = *p) > max) {
        max = basis[11];
    }
    if (basis[11] < min) {
        min = basis[11];
    }
    row += yStep;
    if ((basis[12] = *row) > max) {
        max = basis[12];
    }
    if (basis[12] < min) {
        min = basis[12];
    }
    p = row + xStep;
    if ((basis[13] = *p) > max) {
        max = basis[13];
    }
    if (basis[13] < min) {
        min = basis[13];
    }
    p += xStep;
    if ((basis[14] = *p) > max) {
        max = basis[14];
    }
    if (basis[14] < min) {
        min = basis[14];
    }
    p += xStep;
    if ((basis[15] = *p) > max) {
        max = basis[15];
    }
    if (basis[15] < min) {
        min = basis[15];
    }
    HVQ_DECODE(&state->bufTree0[planeIdx], value);
    *sum += value;
    inverse = lbl_80328FA0.divTable[max - min];
    if (bits & 0x8000) {
        inverse = -inverse;
    }
    return (*sum + ((bits >> 13) & 3)) * inverse;
}
#endif

// .text:0x800E1BB4 size:0x4EC
// NONMATCHING 85%: row pointer arithmetic order and register allocation
#if NONMATCHING
s32 fn_800E1BB4(HVQState* state, u8* basis, s32* sum, u8* src, s32 srcStride, s32 planeIdx) {
    u8 hi = *state->fixvl[planeIdx].ptr++;
    u8 lo = *state->fixvl[planeIdx].ptr++;
    u16 bits = (hi << 8) | lo;
    u8* row;
    u8* p;
    s32 xStep;
    s32 yStep;
    u8 max;
    u8 min;
    s16 value;
    s32 inverse;

    if (state->isLandscape) {
        row = src + ((bits >> 6) & 0x1F) * srcStride;
        row += bits & 0x3F;
        xStep = 1 << ((bits >> 11) & 1);
        yStep = srcStride << ((bits >> 12) & 1);
    } else {
        row = src + (bits & 0x3F) * srcStride;
        row += (bits >> 6) & 0x1F;
        xStep = 1 << ((bits >> 12) & 1);
        yStep = srcStride << ((bits >> 11) & 1);
    }
    // 4x4 samples, unrolled; track the value range
    basis[0] = (*row >> 4) & 0xF;
    max = min = basis[0];
    p = row + xStep;
    if ((basis[1] = (*p >> 4) & 0xF) > max) {
        max = basis[1];
    }
    if (basis[1] < min) {
        min = basis[1];
    }
    p += xStep;
    if ((basis[2] = (*p >> 4) & 0xF) > max) {
        max = basis[2];
    }
    if (basis[2] < min) {
        min = basis[2];
    }
    p += xStep;
    if ((basis[3] = (*p >> 4) & 0xF) > max) {
        max = basis[3];
    }
    if (basis[3] < min) {
        min = basis[3];
    }
    row += yStep;
    if ((basis[4] = (*row >> 4) & 0xF) > max) {
        max = basis[4];
    }
    if (basis[4] < min) {
        min = basis[4];
    }
    p = row + xStep;
    if ((basis[5] = (*p >> 4) & 0xF) > max) {
        max = basis[5];
    }
    if (basis[5] < min) {
        min = basis[5];
    }
    p += xStep;
    if ((basis[6] = (*p >> 4) & 0xF) > max) {
        max = basis[6];
    }
    if (basis[6] < min) {
        min = basis[6];
    }
    p += xStep;
    if ((basis[7] = (*p >> 4) & 0xF) > max) {
        max = basis[7];
    }
    if (basis[7] < min) {
        min = basis[7];
    }
    row += yStep;
    if ((basis[8] = (*row >> 4) & 0xF) > max) {
        max = basis[8];
    }
    if (basis[8] < min) {
        min = basis[8];
    }
    p = row + xStep;
    if ((basis[9] = (*p >> 4) & 0xF) > max) {
        max = basis[9];
    }
    if (basis[9] < min) {
        min = basis[9];
    }
    p += xStep;
    if ((basis[10] = (*p >> 4) & 0xF) > max) {
        max = basis[10];
    }
    if (basis[10] < min) {
        min = basis[10];
    }
    p += xStep;
    if ((basis[11] = (*p >> 4) & 0xF) > max) {
        max = basis[11];
    }
    if (basis[11] < min) {
        min = basis[11];
    }
    row += yStep;
    if ((basis[12] = (*row >> 4) & 0xF) > max) {
        max = basis[12];
    }
    if (basis[12] < min) {
        min = basis[12];
    }
    p = row + xStep;
    if ((basis[13] = (*p >> 4) & 0xF) > max) {
        max = basis[13];
    }
    if (basis[13] < min) {
        min = basis[13];
    }
    p += xStep;
    if ((basis[14] = (*p >> 4) & 0xF) > max) {
        max = basis[14];
    }
    if (basis[14] < min) {
        min = basis[14];
    }
    p += xStep;
    if ((basis[15] = (*p >> 4) & 0xF) > max) {
        max = basis[15];
    }
    if (basis[15] < min) {
        min = basis[15];
    }
    HVQ_DECODE(&state->bufTree0[planeIdx], value);
    *sum += value;
    inverse = lbl_80328FA0.divTable[max - min];
    if (bits & 0x8000) {
        inverse = -inverse;
    }
    return (*sum + ((bits >> 13) & 3)) * inverse;
}
#endif

// .text:0x800E20A0 size:0x270
s32 fn_800E20A0(HVQState* state, s32* block, u8 count, u8* src, s32 srcStride, s32 planeIdx) {
    s32 sum;
    u8 basis[16];
    s32 unused; // keeps the original stack layout

    sum = 0;
    block[0] = block[1] = block[2] = block[3] = block[4] = block[5] = block[6] = block[7] = block[8] = block[9] =
        block[10] = block[11] = block[12] = block[13] = block[14] = block[15] = 0;
    while (count--) {
        s32 factor = fn_800E1708(state, basis, &sum, src, srcStride, planeIdx);

        block[0] += factor * basis[0];
        block[1] += factor * basis[1];
        block[2] += factor * basis[2];
        block[3] += factor * basis[3];
        block[4] += factor * basis[4];
        block[5] += factor * basis[5];
        block[6] += factor * basis[6];
        block[7] += factor * basis[7];
        block[8] += factor * basis[8];
        block[9] += factor * basis[9];
        block[10] += factor * basis[10];
        block[11] += factor * basis[11];
        block[12] += factor * basis[12];
        block[13] += factor * basis[13];
        block[14] += factor * basis[14];
        block[15] += factor * basis[15];
    }
    return (block[0] + block[1] + block[2] + block[3] + block[4] + block[5] + block[6] + block[7] + block[8] +
            block[9] + block[10] + block[11] + block[12] + block[13] + block[14] + block[15]) >> 4;
}

// .text:0x800E2310 size:0x270
s32 fn_800E2310(HVQState* state, s32* block, u8 count, u8* src, s32 srcStride, s32 planeIdx) {
    s32 sum;
    u8 basis[16];
    s32 unused; // keeps the original stack layout

    sum = 0;
    block[0] = block[1] = block[2] = block[3] = block[4] = block[5] = block[6] = block[7] = block[8] = block[9] =
        block[10] = block[11] = block[12] = block[13] = block[14] = block[15] = 0;
    while (count--) {
        s32 factor = fn_800E1BB4(state, basis, &sum, src, srcStride, planeIdx);

        block[0] += factor * basis[0];
        block[1] += factor * basis[1];
        block[2] += factor * basis[2];
        block[3] += factor * basis[3];
        block[4] += factor * basis[4];
        block[5] += factor * basis[5];
        block[6] += factor * basis[6];
        block[7] += factor * basis[7];
        block[8] += factor * basis[8];
        block[9] += factor * basis[9];
        block[10] += factor * basis[10];
        block[11] += factor * basis[11];
        block[12] += factor * basis[12];
        block[13] += factor * basis[13];
        block[14] += factor * basis[14];
        block[15] += factor * basis[15];
    }
    return (block[0] + block[1] + block[2] + block[3] + block[4] + block[5] + block[6] + block[7] + block[8] +
            block[9] + block[10] + block[11] + block[12] + block[13] + block[14] + block[15]) >> 4;
}

// .text:0x800E2580 size:0x318
// NONMATCHING 69%: original unrolls the raw copy and clip loops differently
#if NONMATCHING
void fn_800E2580(HVQState* state, u8* dst, s32 stride, u8 value, u8 type, s32 planeIdx) {
    s32 block[16];
    s32 shift;
    s32 bias;
    s32 i;

    if (type == 6) {
        // raw 4x4 pixels
        HVQBitBuf* fixvl = &state->fixvl[planeIdx];

        for (i = 0; i < 4; i++) {
            dst[0] = *fixvl->ptr++;
            dst[1] = *fixvl->ptr++;
            dst[2] = *fixvl->ptr++;
            dst[3] = *fixvl->ptr++;
            dst += stride;
        }
        return;
    }
    shift = state->basisShift;
    bias = ((value + 0x80) << shift) - fn_800E20A0(state, block, type, state->nest, state->nestWidth, planeIdx);
    for (i = 0; i < 4; i++) {
        dst[0] = lbl_80328DA0[(block[i * 4 + 0] + bias) >> shift];
        dst[1] = lbl_80328DA0[(block[i * 4 + 1] + bias) >> shift];
        dst[2] = lbl_80328DA0[(block[i * 4 + 2] + bias) >> shift];
        dst[3] = lbl_80328DA0[(block[i * 4 + 3] + bias) >> shift];
        dst += stride;
    }
}
#endif

// .text:0x800E2898 size:0x144
void fn_800E2898(HVQState* state, u8* dst, s32 stride, HVQIpicCtx* ctx) {
    u8 type = ctx->curBlk.type;

    if (type == 0) {
        u8 value = ctx->curBlk.value;
        u8 top = (ctx->above->type & 0x77) ? value : ctx->above->value;
        u8 bottom = (ctx->below->type & 0x77) ? value : ctx->below->value;
        u8 right = (ctx->next.type & 0x77) ? value : ctx->next.value;

        fn_800E156C(dst, stride, value, top, bottom, ctx->left, right);
        ctx->left = value;
    } else if (type == 8) {
        u8 value = ctx->curBlk.value;
        u8* row = dst + stride;

        dst[3] = value;
        dst[2] = value;
        dst[1] = value;
        dst[0] = value;
        row[3] = value;
        row[2] = value;
        row[1] = value;
        row[0] = value;
        row += stride;
        row[3] = value;
        row[2] = value;
        row[1] = value;
        row[0] = value;
        row += stride;
        row[3] = value;
        row[2] = value;
        row[1] = value;
        row[0] = value;
        ctx->left = value;
    } else {
        fn_800E2580(state, dst, stride, ctx->curBlk.value, ctx->curBlk.type, ctx->planeIdx);
        ctx->left = ctx->next.value;
    }
    ctx->above++;
    ctx->below++;
}

// .text:0x800E29DC size:0xD4
void fn_800E29DC(HVQState* state, u8* dst, s32 stride, HVQIpicCtx* ctx, s32 count) {
    s32 i;

    ctx->next = *ctx->cur;
    ctx->left = ctx->cur->value;
    for (i = count - 1; i > 0; i--) {
        ctx->curBlk = ctx->next;
        ctx->next = *++ctx->cur;
        fn_800E2898(state, dst, stride, ctx);
        dst += 4;
    }
    // last block: its right neighbour is itself; skip the border to the next row
    ctx->curBlk = ctx->next;
    ctx->cur += 3;
    fn_800E2898(state, dst, stride, ctx);
    ctx->above += 2;
    ctx->below += 2;
}

// .text:0x800E2AB0 size:0xDC
// NONMATCHING 71%: register allocation and stack layout
#if NONMATCHING
void fn_800E2AB0(HVQState* state, s32 planeIdx, u8* dst) {
    HVQPlaneDesc* plane = &state->planes[planeIdx];
    u16 width = plane->widthInSamples;
    u16 widthInBlocks = plane->widthInBlocks;
    HVQIpicCtx ctx;
    s32 y;

    ctx.planeIdx = planeIdx;
    ctx.above = plane->payload;
    ctx.cur = plane->payload;
    ctx.below = plane->payload + plane->blocksPerRow;
    fn_800E29DC(state, dst, width, &ctx, widthInBlocks);
    dst += width * 4;
    ctx.above = plane->payload;
    for (y = plane->heightInBlocks - 2; y > 0; y--) {
        fn_800E29DC(state, dst, width, &ctx, widthInBlocks);
        dst += width * 4;
    }
    ctx.below = ctx.cur;
    fn_800E29DC(state, dst, width, &ctx, widthInBlocks);
}
#endif

// .text:0x800E2B8C size:0x8C
void fn_800E2B8C(HVQState* state, HVQMCPlane* mc, u8* dst, u8* ref0, u8* ref1) {
    HVQPlaneDesc* plane = state->planes;
    s32 i;

    for (i = 0; i < 3; i++, plane++, mc++) {
        mc->run = 0;
        mc->dcPred = 0x7F;
        mc->dstRow = dst;
        mc->ref0 = ref0;
        mc->ref1 = ref1;
        mc->blkRow = mc->blk = plane->payload;
        mc->mbStepX = 8 >> plane->widthShift;
        mc->mbStepY = (8 >> plane->heightShift) * plane->widthInSamples;
        mc->blkStepX = plane->widthInMB;
        mc->blkStepY = plane->blocksPerRow * plane->heightInMB;
        dst += plane->sizeInSamples;
        ref0 += plane->sizeInSamples;
        ref1 += plane->sizeInSamples;
    }
}

// .text:0x800E2C18 size:0x6D0
// NONMATCHING 99%: register allocation of the row pointers
#if NONMATCHING
void fn_800E2C18(u8* dst, s32 dstStride, u8* src, s32 srcStride, s32 halfX, s32 halfY) {
    if (halfX == 0 && halfY == 0) {
        u8* s0 = src + srcStride;
        u8* d = dst + dstStride;

        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        d[0] = s0[0];
        d[1] = s0[1];
        d[2] = s0[2];
        d[3] = s0[3];
        s0 += srcStride;
        d += dstStride;
        d[0] = s0[0];
        d[1] = s0[1];
        d[2] = s0[2];
        d[3] = s0[3];
        s0 += srcStride;
        d += dstStride;
        d[0] = s0[0];
        d[1] = s0[1];
        d[2] = s0[2];
        d[3] = s0[3];
        return;
    }
    if (halfX != 0 && halfY == 0) {
        u8* s0 = src + srcStride;
        u8* d = dst + dstStride;

        dst[0] = (src[0] + src[1] + 1) >> 1;
        dst[1] = (src[1] + src[2] + 1) >> 1;
        dst[2] = (src[2] + src[3] + 1) >> 1;
        dst[3] = (src[3] + src[4] + 1) >> 1;
        d[0] = (s0[0] + s0[1] + 1) >> 1;
        d[1] = (s0[1] + s0[2] + 1) >> 1;
        d[2] = (s0[2] + s0[3] + 1) >> 1;
        d[3] = (s0[3] + s0[4] + 1) >> 1;
        s0 += srcStride;
        d += dstStride;
        d[0] = (s0[0] + s0[1] + 1) >> 1;
        d[1] = (s0[1] + s0[2] + 1) >> 1;
        d[2] = (s0[2] + s0[3] + 1) >> 1;
        d[3] = (s0[3] + s0[4] + 1) >> 1;
        s0 += srcStride;
        d += dstStride;
        d[0] = (s0[0] + s0[1] + 1) >> 1;
        d[1] = (s0[1] + s0[2] + 1) >> 1;
        d[2] = (s0[2] + s0[3] + 1) >> 1;
        d[3] = (s0[3] + s0[4] + 1) >> 1;
        return;
    }
    if (halfX == 0 && halfY != 0) {
        u8* s0;
        u8* s1 = src + srcStride;
        u8* d = dst + dstStride;

        dst[0] = (src[0] + s1[0] + 1) >> 1;
        dst[1] = (src[1] + s1[1] + 1) >> 1;
        dst[2] = (src[2] + s1[2] + 1) >> 1;
        dst[3] = (src[3] + s1[3] + 1) >> 1;
        s0 = s1;
        s1 += srcStride;
        d[0] = (s0[0] + s1[0] + 1) >> 1;
        d[1] = (s0[1] + s1[1] + 1) >> 1;
        d[2] = (s0[2] + s1[2] + 1) >> 1;
        d[3] = (s0[3] + s1[3] + 1) >> 1;
        s0 += srcStride;
        s1 += srcStride;
        d += dstStride;
        d[0] = (s0[0] + s1[0] + 1) >> 1;
        d[1] = (s0[1] + s1[1] + 1) >> 1;
        d[2] = (s0[2] + s1[2] + 1) >> 1;
        d[3] = (s0[3] + s1[3] + 1) >> 1;
        s0 += srcStride;
        s1 += srcStride;
        d += dstStride;
        d[0] = (s0[0] + s1[0] + 1) >> 1;
        d[1] = (s0[1] + s1[1] + 1) >> 1;
        d[2] = (s0[2] + s1[2] + 1) >> 1;
        d[3] = (s0[3] + s1[3] + 1) >> 1;
        return;
    }
    if (halfX != 0 && halfY != 0) {
        u8* s0;
        u8* s1 = src + srcStride;
        u8* d = dst + dstStride;

        dst[0] = (src[0] + src[1] + s1[0] + s1[1] + 2) >> 2;
        dst[1] = (src[1] + src[2] + s1[1] + s1[2] + 2) >> 2;
        dst[2] = (src[2] + src[3] + s1[2] + s1[3] + 2) >> 2;
        dst[3] = (src[3] + src[4] + s1[3] + s1[4] + 2) >> 2;
        s0 = s1;
        s1 += srcStride;
        d[0] = (s0[0] + s0[1] + s1[0] + s1[1] + 2) >> 2;
        d[1] = (s0[1] + s0[2] + s1[1] + s1[2] + 2) >> 2;
        d[2] = (s0[2] + s0[3] + s1[2] + s1[3] + 2) >> 2;
        d[3] = (s0[3] + s0[4] + s1[3] + s1[4] + 2) >> 2;
        s0 += srcStride;
        s1 += srcStride;
        d += dstStride;
        d[0] = (s0[0] + s0[1] + s1[0] + s1[1] + 2) >> 2;
        d[1] = (s0[1] + s0[2] + s1[1] + s1[2] + 2) >> 2;
        d[2] = (s0[2] + s0[3] + s1[2] + s1[3] + 2) >> 2;
        d[3] = (s0[3] + s0[4] + s1[3] + s1[4] + 2) >> 2;
        s0 += srcStride;
        s1 += srcStride;
        d += dstStride;
        d[0] = (s0[0] + s0[1] + s1[0] + s1[1] + 2) >> 2;
        d[1] = (s0[1] + s0[2] + s1[1] + s1[2] + 2) >> 2;
        d[2] = (s0[2] + s0[3] + s1[2] + s1[3] + 2) >> 2;
        d[3] = (s0[3] + s0[4] + s1[3] + s1[4] + 2) >> 2;
    }
}
#endif

// .text:0x800E32E8 size:0xC4
// NONMATCHING 91%: register allocation
#if NONMATCHING
void fn_800E32E8(HVQState* state, HVQMCPlane* mc, s32 mvX, s32 mvY) {
    HVQPlaneDesc* plane = state->planes;
    s32 i;

    for (i = 0; i < 3; i++, plane++, mc++) {
        s32* pixelOffs = plane->pixelOffs;
        s32 k;
        u8 blocksPerMB = plane->blocksPerMB;
        u8* ref = mc->ref + (mvX >> (plane->widthShift + 1)) + (mvY >> (plane->heightShift + 1)) * plane->widthInSamples;

        for (k = 0; k < blocksPerMB; k++) {
            s32 off = *pixelOffs++;

            fn_800E2C18(mc->dst + off, plane->widthInSamples, ref + off, plane->widthInSamples, mvX & 1, mvY & 1);
        }
    }
}
#endif

// .text:0x800E33AC size:0x4B4
void fn_800E33AC(HVQState* state, HVQMCPlane* mc, s32 flag, s32 proc) {
    return;
}

// .text:0x800E3860 size:0x5DC
void fn_800E3860(HVQState* state, u8* dst, u8* src, u16 stride, u8 type, u8* nest, u16 nestStride, s32 planeIdx,
                 s32 halfX, s32 halfY) {
    return;
}

// .text:0x800E3E3C size:0x2A8
void fn_800E3E3C(HVQState* state, HVQMCPlane* mc, s32 mvX, s32 mvY) {
    return;
}

// .text:0x800E40E4 size:0x158
void fn_800E40E4(HVQState* state, HVQMCPlane* mc) {
    return;
}

// .text:0x800E423C size:0x498
void fn_800E423C(HVQM4SeqObj* seq, HVQMCPlane* mc) {
    return;
}

// .text:0x800E46D4 size:0x3F4
void fn_800E46D4(HVQM4SeqObj* seq, u8* dst, u8* ref0, u8* ref1) {
    return;
}

// .text:0x800E4AC8 size:0x20
void fn_800E4AC8(void) {
    fn_800E0488();
}

// .text:0x800E4AE8 size:0x34
void fn_800E4AE8(void* ctx, void* info) {
    HVQM4SeqObj* seq = ctx;
    u8* p = info;

    seq->frameWidth = (p[0] << 8) | p[1];
    seq->frameHeight = (p[2] << 8) | p[3];
    seq->hSamp = p[4];
    seq->vSamp = p[5];
}

// .text:0x800E4B1C size:0x74
u32 fn_800E4B1C(void* ctx) {
    HVQM4SeqObj* seq = ctx;
    s32 lumaW = seq->frameWidth / 4;
    s32 chromaW = seq->hSamp == 2 ? lumaW >> 1 : lumaW;
    s32 lumaH = seq->frameHeight / 4;
    s32 chromaH = seq->vSamp == 2 ? lumaH >> 1 : lumaH;

    return sizeof(HVQState) + ((lumaW + 2) * (lumaH + 2) + (chromaW + 2) * (chromaH + 2) * 2) * sizeof(HVQBlock);
}

// .text:0x800E4B90 size:0x464
void fn_800E4B90(HVQM4SeqObj* seq, HVQState* state) {
    HVQBlock* blocks;
        s32 i;
    HVQBlock* p;
    s32 n;

    seq->state = state;
    fn_800E07E8(seq, 0, 1, 1);
    fn_800E07E8(seq, 1, seq->hSamp, seq->vSamp);
    fn_800E07E8(seq, 2, seq->hSamp, seq->vSamp);
    if ((state->isLandscape = seq->frameWidth >= seq->frameHeight)) {
        state->nestWidth = 70;
        state->nestHeight = 38;
    } else {
        state->nestWidth = 38;
        state->nestHeight = 70;
    }
    state->basisNum[0].tree = state->basisNum[1].tree = &state->basisNumTree;
    state->basisNumRun[0].tree = state->basisNumRun[1].tree = &state->runTree;
    state->dcValues[0].tree = state->dcValues[1].tree = state->dcValues[2].tree = &state->dcTree;
    state->dcRle[0].tree = state->dcRle[1].tree = state->dcRle[2].tree = &state->runTree;
    state->bufTree0[0].tree = state->bufTree0[1].tree = state->bufTree0[2].tree = &state->bufTree;
    state->mvX.tree = state->mvY.tree = &state->mvTree;
    state->mcbType.tree = state->mcbProc.tree = &state->mcTypeTree;

    // block grids follow the state; fill each grid's border with "no block"
    blocks = (HVQBlock*)(state + 1);
    for (i = 0; i < 3; i++) {
        HVQPlaneDesc* plane = &state->planes[i];
        plane->border = blocks;
        plane->payload = blocks + plane->blocksPerRow + 1;
        blocks += plane->blocksPerRow * plane->rowsWithBorder;

        p = plane->border;
        for (n = plane->blocksPerRow; n > 0; n--) {
            p->value = 0x7F;
            p->type = 0xFF;
            p++;
        }
        p = blocks;
        for (n = plane->blocksPerRow; n > 0; n--) {
            p[-1].value = 0x7F;
            p[-1].type = 0xFF;
            p--;
        }
        p = plane->border + plane->blocksPerRow;
        for (n = plane->rowsWithBorder - 2; n > 0; n--) {
            p->value = 0x7F;
            p->type = 0xFF;
            p += plane->blocksPerRow;
        }
        p = plane->border + plane->blocksPerRow * 2 - 1;
        for (n = plane->rowsWithBorder - 2; n > 0; n--) {
            p->value = 0x7F;
            p->type = 0xFF;
            p += plane->blocksPerRow;
        }
    }
}

// .text:0x800E4FF4 size:0x928
void fn_800E4FF4(void* ctx, u8* src, u8* dst) {
    return;
}

// .text:0x800E591C size:0x24
void fn_800E591C(void* ctx, u8* src, u8* dst, u8* ref) {
    fn_800E5940(ctx, src, dst, ref, dst);
}

// .text:0x800E5940 size:0x9F0
void fn_800E5940(void* ctx, u8* src, u8* dst, u8* ref0, u8* ref1) {
    return;
}
