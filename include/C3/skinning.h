#ifndef _DOLPHIN_CP_SKINNING_H_
#define _DOLPHIN_CP_SKINNING_H_

typedef struct _sStats {
    /* 0x00 */ u32 cycles[2];
    /* 0x08 */ u32 loadStores[2];
    /* 0x10 */ u32 missCycles[2];
    /* 0x18 */ u32 instructions[2];
    /* 0x20 */ u32 cycleTotal;
    /* 0x24 */ u32 loadStoreTotal;
    /* 0x28 */ u32 missCycleTotal;
    /* 0x2C */ u32 instructionTotal;
    /* 0x30 */ u32 hits;
} sStats;

typedef struct sBone {
    /* 0x00 */ u16 boneID;
    /* 0x02 */ u8 inheritanceFlag;
    /* 0x03 */ u8 drawingPriority;
    /* 0x04 */ DSBranch branch;
    /* 0x14 */ struct DODisplayObj * dispObj;
    /* 0x18 */ Control orientationCtrl;
    /* 0x4C */ Control animationCtrl;
    /* 0x80 */ struct ANIMPipe * animPipe;
    /* 0x84 */ MtxPtr forwardMtx;
    /* 0x88 */ MtxPtr skinMtx;
    /* 0x8C */ MtxPtr skinInvTransposeMtx;
    /* 0x90 */ MtxPtr orientationInvMtx;
    /* 0x94 */ DSLink drawPriorityLink;
} sBone;

// MSSB's skinning (the SDK's SKNControl.c / SKNMath.c, with the game's own
// list layout): sHdr, the SKN* functions and GQRSetup6/7 are declared in
// main/file_800BDEA0.h and main/file_800B9974.h.

#define GQR_SCALE_MAX 32

#endif // _DOLPHIN_CP_SKINNING_H_
