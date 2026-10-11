#ifndef __MAIN_FILE_800DFDD4_H__
#define __MAIN_FILE_800DFDD4_H__

#include "mssbTypes.h"

// HVQM4 1.3 movie codec: IMA ADPCM audio and HVQ video decoder.

// IMA ADPCM decoder state of one audio channel.
typedef struct HVQAudioChan {
    /*0x00*/ u8* src;       // read position after the last decode
    /*0x04*/ s16* dst;      // write position after the last decode
    /*0x08*/ s16 pred;
    /*0x0A*/ u8 hiNibble;   // next sample is in the high nibble
    /*0x0B*/ s8 index;
    /*0x0C*/ u8 _0C[4];
    /*0x10*/ s16* bufStart; // output ring buffer (NULL: linear)
    /*0x14*/ s16* bufEnd;
} HVQAudioChan; // size: 0x18

// MSB-first bit reader over one stream of a frame.
typedef struct HVQBitBuf {
    /*0x0*/ u8* ptr;
    /*0x4*/ u8* start;
    /*0x8*/ u32 size;
    /*0xC*/ u8 byte;
    /*0xD*/ u8 mask; // next bit to read; 0 = load a new byte
    /*0xE*/ u8 _E[2];
} HVQBitBuf; // size: 0x10

// Huffman tree. Nodes >= 0x100 are inner nodes with children node[0][n]/node[1][n];
// nodes < 0x100 are leaves whose value is node[0][n].
typedef struct HVQTree {
    /*0x000*/ s32 pos;  // next free inner node
    /*0x004*/ s32 root;
    /*0x008*/ s16 node[2][0x200];
} HVQTree; // size: 0x808

typedef struct HVQBitBufTree {
    /*0x00*/ HVQBitBuf buf;
    /*0x10*/ HVQTree* tree;
} HVQBitBufTree; // size: 0x14

// Per 4x4 block info kept for the current frame.
typedef struct HVQBlock {
    /*0x0*/ u8 value; // DC value
    /*0x1*/ u8 type;  // basis count / block type
} HVQBlock;

typedef struct HVQPlaneDesc {
    /*0x00*/ HVQBlock* border;        // block grid including the 1-block border
    /*0x04*/ HVQBlock* payload;       // first block inside the border
    /*0x08*/ u16 widthInBlocks;
    /*0x0A*/ u16 heightInBlocks;
    /*0x0C*/ u16 blocksPerRow;        // widthInBlocks + 2
    /*0x0E*/ u16 rowsWithBorder;      // heightInBlocks + 2
    /*0x10*/ u16 blockOffs[4];        // 0, stride, stride + 1, 1
    /*0x18*/ s32 pixelOffs[4];        // 0, width * 4, width * 4 + 4, 4
    /*0x28*/ u16 widthInSamples;
    /*0x2A*/ u16 heightInSamples;
    /*0x2C*/ u32 sizeInSamples;
    /*0x30*/ u8 widthShift;
    /*0x31*/ u8 heightShift;
    /*0x32*/ u8 widthInMB;            // 4x4 blocks per 8x8 macroblock, x
    /*0x33*/ u8 heightInMB;           // 4x4 blocks per 8x8 macroblock, y
    /*0x34*/ u8 blocksPerMB;
    /*0x35*/ u8 _35[3];
} HVQPlaneDesc; // size: 0x38

// Decoder work buffer (HVQM4 "VideoState"); block grids follow at 0x3CD0.
typedef struct HVQState {
    /*0x0000*/ HVQPlaneDesc planes[3];
    /*0x00A8*/ HVQTree dcTree;          // DC values (I frame)
    /*0x08B0*/ HVQTree runTree;         // DC run lengths / basis num runs
    /*0x10B8*/ HVQTree bufTree;         // AOT coefficient values
    /*0x18C0*/ HVQTree basisNumTree;
    /*0x20C8*/ HVQTree mvTree;
    /*0x28D0*/ HVQTree mcTypeTree;
    /*0x30D8*/ HVQBitBufTree dcValues[3];
    /*0x3114*/ HVQBitBufTree dcRle[3];
    /*0x3150*/ HVQBitBufTree bufTree0[3];
    /*0x318C*/ HVQBitBufTree basisNum[2];
    /*0x31B4*/ HVQBitBufTree basisNumRun[2];
    /*0x31DC*/ HVQBitBuf fixvl[3];
    /*0x320C*/ HVQBitBufTree mvX;
    /*0x3220*/ HVQBitBufTree mvY;
    /*0x3234*/ HVQBitBufTree mcbType;
    /*0x3248*/ HVQBitBufTree mcbProc;
    /*0x325C*/ u16 nestWidth;
    /*0x325E*/ u16 nestHeight;
    /*0x3260*/ u8 isLandscape;
    /*0x3261*/ u8 nest[70 * 38];
    /*0x3CC5*/ u8 _3CC5;
    /*0x3CC6*/ s16 dcMax;
    /*0x3CC8*/ s16 dcMin;
    /*0x3CCA*/ u8 basisShift; // fixed-point shift of AOT coefficients
    /*0x3CCB*/ u8 dcShift;
    /*0x3CCC*/ u8 mvXBits[2];   // extra motion vector bits per reference
    /*0x3CCE*/ u8 mvYBits[2];
} HVQState; // size: 0x3CD0

// Cursor over the block rows while decoding an I-frame plane (stack local).
typedef struct HVQIpicCtx {
    /*0x00*/ s32 planeIdx;
    /*0x04*/ HVQBlock* above;
    /*0x08*/ HVQBlock* cur;
    /*0x0C*/ HVQBlock* below;
    /*0x10*/ HVQBlock next;   // block to the right
    /*0x12*/ HVQBlock curBlk; // block being decoded
    /*0x14*/ u8 left;         // DC value of the block to the left
    /*0x15*/ u8 _15[3];
} HVQIpicCtx;

// Per-plane cursor for P/B frame (motion compensated) decoding (stack local).
typedef struct HVQMCPlane {
    /*0x00*/ s32 run;          // basis num run length
    /*0x04*/ s32 dcPred;       // DC predictor for intra macroblocks
    /*0x08*/ HVQBlock* blk;
    /*0x0C*/ HVQBlock* blkRow;
    /*0x10*/ u8* dstRow;
    /*0x14*/ u8* dst;
    /*0x18*/ u8* ref;          // ref0 or ref1
    /*0x1C*/ u8* ref0;
    /*0x20*/ u8* ref1;
    /*0x24*/ u16 mbStepX;      // pixels per macroblock
    /*0x26*/ u8 _26[2];
    /*0x28*/ s32 mbStepY;      // bytes per macroblock row
    /*0x2C*/ s32 blkStepX;     // blocks per macroblock
    /*0x30*/ s32 blkStepY;     // blocks per macroblock row
} HVQMCPlane; // size: 0x34

// Decoder handle (lives inside the movie player).
typedef struct HVQM4SeqObj {
    /*0x00*/ HVQState* state;
    /*0x04*/ u16 frameWidth;
    /*0x06*/ u16 frameHeight;
    /*0x08*/ u8 hSamp;
    /*0x09*/ u8 vSamp;
    /*0x0A*/ u8 _0A[0x16];
} HVQM4SeqObj; // size: 0x20

void fn_800DFDD4(u8* src, u8* dst, u32 numChannels, u32 format, u32 count, void* chans);
void fn_800E0488(void);
void fn_800E07E8(HVQM4SeqObj* seq, s32 planeIdx, u8 hSamp, u8 vSamp);
s16 fn_800E0904(HVQTree* tree, HVQBitBuf* buf);
s16 fn_800E0CC8(HVQBitBufTree* buf);
void fn_800E0D60(HVQState* state);
void fn_800E10B4(HVQState* state);
void fn_800E11C8(HVQState* state, s32 nestX, s32 nestY);
void fn_800E156C(u8* dst, s32 stride, u8 dc, u8 top, u8 bottom, u8 left, u8 right);
s32 fn_800E1708(HVQState* state, u8* basis, s32* sum, u8* src, s32 srcStride, s32 planeIdx);
s32 fn_800E1BB4(HVQState* state, u8* basis, s32* sum, u8* src, s32 srcStride, s32 planeIdx);
s32 fn_800E20A0(HVQState* state, s32* block, u8 count, u8* src, s32 srcStride, s32 planeIdx);
s32 fn_800E2310(HVQState* state, s32* block, u8 count, u8* src, s32 srcStride, s32 planeIdx);
void fn_800E2580(HVQState* state, u8* dst, s32 stride, u8 value, u8 type, s32 planeIdx);
void fn_800E2898(HVQState* state, u8* dst, s32 stride, HVQIpicCtx* ctx);
void fn_800E29DC(HVQState* state, u8* dst, s32 stride, HVQIpicCtx* ctx, s32 count);
void fn_800E2AB0(HVQState* state, s32 planeIdx, u8* dst);
void fn_800E2B8C(HVQState* state, HVQMCPlane* mc, u8* dst, u8* ref0, u8* ref1);
void fn_800E2C18(u8* dst, s32 dstStride, u8* src, s32 srcStride, s32 halfX, s32 halfY);
void fn_800E32E8(HVQState* state, HVQMCPlane* mc, s32 mvX, s32 mvY);
void fn_800E33AC(HVQState* state, HVQMCPlane* mc, s32 flag, s32 proc);
void fn_800E3860(HVQState* state, u8* dst, u8* src, u16 stride, u8 type, u8* nest, u16 nestStride, s32 planeIdx,
                 s32 halfX, s32 halfY);
void fn_800E3E3C(HVQState* state, HVQMCPlane* mc, s32 mvX, s32 mvY);
void fn_800E40E4(HVQState* state, HVQMCPlane* mc);
void fn_800E423C(HVQM4SeqObj* seq, HVQMCPlane* mc);
void fn_800E46D4(HVQM4SeqObj* seq, u8* dst, u8* ref0, u8* ref1);
void fn_800E4AC8(void);
void fn_800E4AE8(void* ctx, void* info);
u32 fn_800E4B1C(void* ctx);
void fn_800E4B90(HVQM4SeqObj* seq, HVQState* state);
void fn_800E4FF4(void* ctx, u8* src, u8* dst);
void fn_800E591C(void* ctx, u8* src, u8* dst, u8* ref);
void fn_800E5940(void* ctx, u8* src, u8* dst, u8* ref0, u8* ref1);

#endif
