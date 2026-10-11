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
void fn_800E0488(void) {
    return;
}

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
s16 fn_800E0904(HVQTree* tree, HVQBitBuf* buf) {
    return 0;
}

// .text:0x800E0CC8 size:0x98
s16 fn_800E0CC8(HVQBitBufTree* buf) {
    return 0;
}

// .text:0x800E0D60 size:0x354
void fn_800E0D60(HVQState* state) {
    return;
}

// .text:0x800E10B4 size:0x114
void fn_800E10B4(HVQState* state) {
    return;
}

// .text:0x800E11C8 size:0x3A4
void fn_800E11C8(HVQState* state, s32 nestX, s32 nestY) {
    return;
}

// .text:0x800E156C size:0x19C
void fn_800E156C(u8* dst, s32 stride, u8 dc, u8 top, u8 bottom, u8 left, u8 right) {
    return;
}

// .text:0x800E1708 size:0x4AC
s32 fn_800E1708(HVQState* state, u8* basis, s32* sum, u8* src, s32 srcStride, s32 planeIdx) {
    return 0;
}

// .text:0x800E1BB4 size:0x4EC
s32 fn_800E1BB4(HVQState* state, u8* basis, s32* sum, u8* src, s32 srcStride, s32 planeIdx) {
    return 0;
}

// .text:0x800E20A0 size:0x270
s32 fn_800E20A0(HVQState* state, s32* block, u8 count, u8* src, s32 srcStride, s32 planeIdx) {
    return 0;
}

// .text:0x800E2310 size:0x270
s32 fn_800E2310(HVQState* state, s32* block, u8 count, u8* src, s32 srcStride, s32 planeIdx) {
    return 0;
}

// .text:0x800E2580 size:0x318
void fn_800E2580(HVQState* state, u8* dst, s32 stride, u8 value, u8 type, s32 planeIdx) {
    return;
}

// .text:0x800E2898 size:0x144
void fn_800E2898(HVQState* state, u8* dst, s32 stride, HVQIpicCtx* ctx) {
    return;
}

// .text:0x800E29DC size:0xD4
void fn_800E29DC(HVQState* state, u8* dst, s32 stride, HVQIpicCtx* ctx, s32 count) {
    return;
}

// .text:0x800E2AB0 size:0xDC
void fn_800E2AB0(HVQState* state, s32 planeIdx, u8* dst) {
    return;
}

// .text:0x800E2B8C size:0x8C
void fn_800E2B8C(HVQState* state, HVQMCPlane* mc, u8* dst, u8* ref0, u8* ref1) {
    return;
}

// .text:0x800E2C18 size:0x6D0
void fn_800E2C18(u8* dst, s32 dstStride, u8* src, s32 srcStride, s32 halfX, s32 halfY) {
    return;
}

// .text:0x800E32E8 size:0xC4
void fn_800E32E8(HVQState* state, HVQMCPlane* mc, s32 mvX, s32 mvY) {
    return;
}

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
    return;
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
