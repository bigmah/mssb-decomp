#include "main/file_800A6870.h"
#include "Dolphin/gx.h"

// dvdsys.c

// Same object as lbl_803C7420_s in file_80008E00.c; only the fields used here.
typedef struct {
    /*0x000*/ u8 _000[0x5C];
    /*0x05C*/ OSThreadQueue retraceQueue; // woken every frame
    /*0x064*/ u8 _064[0x31C];
    /*0x380*/ OSThreadQueue queue380;
    /*0x388*/ u8 _388[0xF];
    /*0x397*/ u8 _397;
} SysBlock_803C7420; // size: 0x398
extern SysBlock_803C7420 lbl_803C7420;

typedef struct {
    /*0x0000*/ u8 stacks[2][0x1000]; // [0]: read thread, [1]: monitor thread
    /*0x2000*/ DVDFileInfo fileInfo;
} DvdSysWork; // size: 0x2040
extern DvdSysWork lbl_802EAF80;

typedef struct {
    /*0x000*/ u8 grid[0x150]; // (x, y) byte pairs
    /*0x150*/ GXTlutObj tlut;
    /*0x15C*/ GXTexObj tex;
} Grid_802ECFC0; // size: 0x180
extern Grid_802ECFC0 lbl_802ECFC0;

extern DriveStatusCallback lbl_8010F420[16];
extern u8 lbl_8010F460[]; // 128x128 C4 texture
extern u8 lbl_80110060[]; // 16-entry RGB5A3 palette

// "\nDecode Error Retry : EntryNo%d %x Err:%d\n", "dvdsys.c", and two SJIS panic messages
extern char lbl_800E7730[];
#define STR_DECODE_ERROR (lbl_800E7730)
#define STR_DVDSYS_C (lbl_800E7730 + 0x2C)
#define STR_NEED_DEST (lbl_800E7730 + 0x38)
#define STR_NEED_ARAM_ADDR (lbl_800E7730 + 0x68)

extern void* fn_800ACF34(s32 align, u32 size); // alloc
extern void fn_800ACF14(void* p); // free
extern void* _OSAllocFromHeap(s32 align, u32 size);
extern void ARQRemoveOwnerRequest(u32 owner);

#define DVDSYS_ARQ_OWNER 2000
#define ALIGN32(x) (((x) + 0x1F) & ~0x1F)

// state and idle are stored together with one halfword store in the original.
#if NONMATCHING
#define SET_STATE_IDLE(st, idl) (lbl_803C6CF8.state = (st), lbl_803C6CF8.idle = (idl))
#else
#define SET_STATE_IDLE(st, idl) (*(u16*)&lbl_803C6CF8.state = (u16)(((st) << 8) | (idl)))
#endif

static inline void CancelTransfer(void) {
    DVDCBCallback cb;

    lbl_803C6CF8.state = DVDSYS_STATE_NONE;
    lbl_803C6CF8.driveStatus = 0;
    if (lbl_803C6CF8.idle != 1) {
        if (lbl_803C6CF8.mode == DVDSYS_MODE_DISC_LZ_TO_RAM || lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_LZ_TO_RAM) {
            cb = fn_800A75EC;
        } else {
            cb = fn_800A7670;
        }
        DVDCancelAsync(&lbl_803C6CF8.fileInfo->cBlock, cb);
        ARQRemoveOwnerRequest(DVDSYS_ARQ_OWNER);
    }
}

static inline void PostAramRead(void) {
    ARQPostRequest(&lbl_803C6CF8.arqRequests[lbl_803C6CF8.arqIndex], DVDSYS_ARQ_OWNER, ARAM_DIR_ARAM_TO_MRAM, 0,
                   lbl_803C6CF8.aramCur, (u32)lbl_803C6CF8.readPos, ALIGN32(lbl_803C6CF8.chunkSize), fn_800A68D4);
    lbl_803C6CF8.arqIndex = (lbl_803C6CF8.arqIndex + 1) % 4;
    lbl_803C6CF8.aramCur += ALIGN32(lbl_803C6CF8.chunkSize);
}

static inline void ReadRingChunk(void) {
    s32 len;

    if (lbl_803C6CF8.writePos >= lbl_803C6CF8.readPos) {
        len = lbl_803C6CF8.bufEnd - lbl_803C6CF8.writePos;
    } else {
        len = lbl_803C6CF8.readPos - lbl_803C6CF8.writePos;
    }
    if (len > lbl_803C6CF8.remaining) {
        len = lbl_803C6CF8.remaining;
    }
    len = (len < 0x4000) ? len : 0x4000;
    if (len != 0) {
        DVDReadAsyncPrio(lbl_803C6CF8.fileInfo, lbl_803C6CF8.writePos, len,
                         lbl_803C6CF8.diskOffset + lbl_803C6CF8.bytesRead, fn_800A6F94, 2);
    }
}

// .text:0x800A6870 size:0x20
u32 fn_800A6870(u8 enable, u32 limit) {
    u32 old;

    lbl_803C6CF8.retryEnabled = enable;
    old = lbl_803C6CF8.retryLimit;
    if (enable) {
        lbl_803C6CF8.retryLimit = limit;
    }
    return old;
}

// .text:0x800A6890 size:0x44
void fn_800A6890(u32 request) {
    if (lbl_803C6CF8.remaining == 0) {
        lbl_803C6CF8.state = DVDSYS_STATE_DONE;
    } else {
        OSSignalSemaphore(&lbl_803C6CF8.aramSem);
    }
}

// .text:0x800A68D4 size:0x2C
void fn_800A68D4(u32 request) {
    OSResumeThread(&lbl_803C6CF8.readThread);
}

// .text:0x800A6900 size:0x380
void* fn_800A6900(void* arg) {
    s8 status;

    while (TRUE) {
        OSSleepThread(&lbl_803C7420.retraceQueue);
        lbl_803C6CF8.driveStatus = DVDGetDriveStatus();
        lbl_803C6CF8.driveStatusCallbacks[(s8)lbl_803C6CF8.driveStatus + 1]();

        if (lbl_803C6CF8.retryEnabled && lbl_803C6CF8.state == DVDSYS_STATE_READING &&
            lbl_803C6CF8.retryCount != 0) {
            switch (lbl_803C6CF8.driveStatus) {
            case 0:
                lbl_803C6CF8.retryCount--;
                break;
            default:
                lbl_803C6CF8.retryCount = lbl_803C6CF8.retryLimit;
                break;
            }
        }

        switch (lbl_803C6CF8.state) {
        case DVDSYS_STATE_NONE:
            break;
        case DVDSYS_STATE_START:
            status = DVDGetCommandBlockStatus(&lbl_803C6CF8.fileInfo->cBlock);
            if ((status == 0) | (status == 10)) {
                lbl_803C6CF8.bytesRead = 0;
                lbl_803C6CF8.readPos = lbl_803C6CF8.bufStart;
                lbl_803C6CF8.remaining = lbl_803C6CF8.totalSize;
                if (lbl_803C6CF8.retryEnabled) {
                    lbl_803C6CF8.retryCount = lbl_803C6CF8.retryLimit;
                }
                DVDFastOpen(lbl_803C6CF8.entryNum, lbl_803C6CF8.fileInfo);
                if (lbl_803C6CF8.mode == DVDSYS_MODE_DISC_LZ_TO_RAM) {
                    SetReadParameters(lbl_803C6CF8.instr, lbl_803C6CF8.tempBuf, lbl_803C6CF8.bufEnd, 1);
                } else if (lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_LZ_TO_RAM) {
                    SetReadParameters(lbl_803C6CF8.instr, lbl_803C6CF8.tempBuf, lbl_803C6CF8.bufEnd, 2);
                    lbl_803C6CF8.aramCur = lbl_803C6CF8.aramStart;
                }
                lbl_803C6CF8.chunkSize = (lbl_803C6CF8.remaining >= 0x8000) ? 0x8000 : lbl_803C6CF8.remaining;
                if (lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_LZ_TO_RAM) {
                    DCInvalidateRange(lbl_803C6CF8.readPos, lbl_803C6CF8.chunkSize);
                    PostAramRead();
                } else {
                    DVDReadAsyncPrio(lbl_803C6CF8.fileInfo, lbl_803C6CF8.bufStart, lbl_803C6CF8.chunkSize,
                                     lbl_803C6CF8.diskOffset, fn_800A7A80, 2);
                }
                lbl_803C6CF8.state = DVDSYS_STATE_READING;
            }
            break;
        case DVDSYS_STATE_READING:
            if (lbl_803C6CF8.mode == DVDSYS_MODE_DISC_LZ_TO_RAM || lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_LZ_TO_RAM) {
                if (!gDataDecompressorValues.ShouldWriteDataFlag) {
                    DCFlushRangeNoSync(lbl_803C6CF8.bufEnd, gDataDecompressorValues.CachedBytesToRead);
                    if (lbl_803C6CF8.tempBuf != NULL) {
                        fn_800ACF14(lbl_803C6CF8.tempBuf);
                        lbl_803C6CF8.tempBuf = NULL;
                    }
                    SET_STATE_IDLE(DVDSYS_STATE_NONE, 1);
                } else if (gDataDecompressorValues.error ||
                           (lbl_803C6CF8.retryEnabled && lbl_803C6CF8.retryCount == 0)) {
                    // decode error or stalled drive: restart the decoder and the read thread
                    DVDCancel(&lbl_803C6CF8.fileInfo->cBlock);
                    OSCancelThread(&gDataDecompressorValues.t);
                    StartThreadForReadingFromDisk();
                    OSCancelThread(&lbl_803C6CF8.readThread);
                    OSCreateThread(&lbl_803C6CF8.readThread, fn_800A77A0, NULL,
                                   lbl_802EAF80.stacks[0] + sizeof(lbl_802EAF80.stacks[0]),
                                   sizeof(lbl_802EAF80.stacks[0]), 8, 1);
                    OSResumeThread(&lbl_803C6CF8.readThread);
                    lbl_803C6CF8.state = DVDSYS_STATE_START;
                    OSReport(STR_DECODE_ERROR, lbl_803C6CF8.entryNum, lbl_803C6CF8.instr->diskLocation,
                             gDataDecompressorValues.error);
                }
            }
            break;
        case DVDSYS_STATE_DONE:
            SET_STATE_IDLE(DVDSYS_STATE_NONE, 1);
            if (lbl_803C6CF8.tempBuf != NULL) {
                fn_800ACF14(lbl_803C6CF8.tempBuf);
                lbl_803C6CF8.tempBuf = NULL;
            }
            break;
        case DVDSYS_STATE_RING:
            break;
        }
    }
}

// .text:0x800A6C80 size:0x90
void fn_800A6C80(void) {
    CancelTransfer();
    lbl_803C6CF8.remaining = 0;
    lbl_803C6CF8.buffered = 0;
}

// .text:0x800A6D10 size:0x114
void fn_800A6D10(s32 consumed) {
    BOOL intr = OSDisableInterrupts();

    lbl_803C6CF8.readPos += consumed;
    if (lbl_803C6CF8.readPos >= lbl_803C6CF8.bufEnd) {
        lbl_803C6CF8.readPos -= lbl_803C6CF8.ringSize;
    }
    lbl_803C6CF8.buffered -= consumed;
    if (lbl_803C6CF8.ringFull) {
        lbl_803C6CF8.state = DVDSYS_STATE_RING;
        lbl_803C6CF8.ringFull = FALSE;
        ReadRingChunk();
    }
    OSRestoreInterrupts(intr);
}

// .text:0x800A6E24 size:0x170
void fn_800A6E24(AssetLoadInstructions* instr, u8* ringBuf, s32 ringSize) {
    CancelTransfer();
    lbl_803C6CF8.instr = instr;
    lbl_803C6CF8.bytesRead = 0;
    lbl_803C6CF8.diskOffset = instr->diskLocation;
    lbl_803C6CF8.remaining = lbl_803C6CF8.totalSize = ALIGN32(instr->compressedSize);
    lbl_803C6CF8.writePos = ringBuf;
    lbl_803C6CF8.readPos = ringBuf;
    lbl_803C6CF8.bufStart = ringBuf;
    lbl_803C6CF8.buffered = 0;
    lbl_803C6CF8.ringFull = FALSE;
    lbl_803C6CF8.ringSize = ringSize;
    lbl_803C6CF8.bufEnd = ringBuf + ringSize;
    while (lbl_803C6CF8.idle != 1) {
    }
    DVDFastOpen(lbl_803C6CF8.entryNum, lbl_803C6CF8.fileInfo);
    SET_STATE_IDLE(DVDSYS_STATE_RING, 0);
    ReadRingChunk();
}

// .text:0x800A6F94 size:0x148
void fn_800A6F94(s32 result, DVDFileInfo* fileInfo) {
    if (result > 0) {
        lbl_803C6CF8.buffered += result;
        lbl_803C6CF8.bytesRead += result;
        lbl_803C6CF8.writePos += result;
        lbl_803C6CF8.remaining -= result;
        if (lbl_803C6CF8.writePos == lbl_803C6CF8.bufEnd) {
            lbl_803C6CF8.writePos = lbl_803C6CF8.bufStart;
        }
        if (lbl_803C6CF8.buffered == lbl_803C6CF8.ringSize) {
            lbl_803C6CF8.ringFull = TRUE;
            lbl_803C6CF8.state = DVDSYS_STATE_NONE;
        } else if (lbl_803C6CF8.bytesRead == lbl_803C6CF8.totalSize) {
            SET_STATE_IDLE(DVDSYS_STATE_NONE, 1);
        } else {
            ReadRingChunk();
        }
    } else if (result == -3) {
        lbl_803C6CF8.state = DVDSYS_STATE_NONE;
        DVDClose(fileInfo);
    }
}

// .text:0x800A70DC size:0x430
// NONMATCHING 97%: modes 0/3 schedule the fn_800ACF34 result through r25 instead of r4 (same code otherwise)
#if NONMATCHING
void* ARAMTransfer(AssetLoadInstructions* instr, void* dest, u8 mode, u32 aramAddr) {
    u32 size;
    void* result;
    u32 t;
    char* strings = lbl_800E7730;

    CancelTransfer();
    lbl_803C6CF8.compression = instr->compressionConstants;
    lbl_803C6CF8.bytesRead = 0;
    lbl_803C6CF8.chunkSize = 0;
    lbl_803C6CF8.diskOffset = instr->diskLocation;
    lbl_803C6CF8.sizeInfo = ((u32*)instr)[1]; // TODO type: whole flags/size word
    gDataDecompressorValues.compressedFlag = instr->compressionFlag;
    lbl_803C6CF8.instr = instr;
    lbl_803C6CF8.mode = mode;
    while (lbl_803C6CF8.idle != 1) {
    }
    DVDFastOpen(lbl_803C6CF8.entryNum, lbl_803C6CF8.fileInfo);
    size = ALIGN32(instr->compressedSize);

    if (dest == NULL) {
        if (lbl_803C6CF8.mode == DVDSYS_MODE_DISC_LZ_TO_RAM || lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_LZ_TO_RAM) {
            dest = _OSAllocFromHeap(0x20, ALIGN32(lbl_803C6CF8.sizeInfo & 0x0FFFFFFF));
        } else if (lbl_803C6CF8.mode == DVDSYS_MODE_DISC_TO_ARAM) {
            OSPanic(strings + 0x2C, 554, strings + 0x38);
        } else {
            dest = _OSAllocFromHeap(0x20, size);
        }
    }
    if (aramAddr == 0) {
        if (lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_LZ_TO_RAM) {
            OSPanic(strings + 0x2C, 564, strings + 0x68);
        }
        if (lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_TO_RAM) {
            OSPanic(strings + 0x2C, 568, strings + 0x68);
        }
    }

    lbl_803C6CF8.totalSize = size;
    lbl_803C6CF8.remaining = size;
    lbl_803C6CF8.chunkSize = (lbl_803C6CF8.remaining >= 0x8000) ? 0x8000 : lbl_803C6CF8.remaining;
    result = dest;

    if (lbl_803C6CF8.mode == DVDSYS_MODE_DISC_LZ_TO_RAM) {
        lbl_803C6CF8.bufEnd = dest;
        dest = fn_800ACF34(0x20, 0x20000);
        lbl_803C6CF8.tempBuf = dest;
        SetReadParameters(instr, lbl_803C6CF8.tempBuf, lbl_803C6CF8.bufEnd, 1);
    } else if (lbl_803C6CF8.mode == DVDSYS_MODE_DISC_TO_ARAM) {
        OSInitSemaphore(&lbl_803C6CF8.aramSem, 3);
        lbl_803C6CF8.aramStart = (u32)dest; // dest is an ARAM address in this mode
        lbl_803C6CF8.aramCur = (u32)dest;
        lbl_803C6CF8.tempBuf = fn_800ACF34(0x20, 0x20000);
        dest = lbl_803C6CF8.tempBuf;
        lbl_803C6CF8.tempBufEnd = (u8*)lbl_803C6CF8.tempBuf + 0x20000;
        lbl_803C6CF8.arqIndex = 0;
    } else if (lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_LZ_TO_RAM) {
        lbl_803C6CF8.aramStart = aramAddr;
        lbl_803C6CF8.aramCur = aramAddr;
        lbl_803C6CF8.bufEnd = dest;
        lbl_803C6CF8.tempBuf = fn_800ACF34(0x20, 0x20000);
        dest = lbl_803C6CF8.tempBuf;
        lbl_803C6CF8.arqIndex = 0;
        SetReadParameters(instr, dest, lbl_803C6CF8.bufEnd, 2);
    } else if (lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_TO_RAM) {
        lbl_803C6CF8.aramStart = aramAddr;
        lbl_803C6CF8.aramCur = aramAddr;
        lbl_803C6CF8.bufEnd = dest;
        lbl_803C6CF8.chunkSize = lbl_803C6CF8.remaining;
    }

    lbl_803C6CF8.bufStart = dest;
    lbl_803C6CF8.readPos = dest;
    SET_STATE_IDLE(DVDSYS_STATE_READING, 0);
    if (lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_LZ_TO_RAM || lbl_803C6CF8.mode == DVDSYS_MODE_ARAM_TO_RAM) {
        DCInvalidateRange(lbl_803C6CF8.readPos, lbl_803C6CF8.chunkSize);
        PostAramRead();
    } else {
        DVDReadAsyncPrio(lbl_803C6CF8.fileInfo, dest, lbl_803C6CF8.chunkSize, lbl_803C6CF8.diskOffset, fn_800A7A80, 2);
    }

    if (lbl_803C6CF8.retryEnabled) {
        t = size * 180;
        lbl_803C6CF8.retryCount = lbl_803C6CF8.retryLimit = ((t >> 21) < 180) ? 180 : (t >> 22);
    }
    return result;
}
#endif

// .text:0x800A750C size:0x38
// The original passes its own second argument straight through as DVDFastOpen's fileInfo.
BOOL fn_800A750C(void* unused, DVDFileInfo* fileInfo) {
    return DVDFastOpen(lbl_803C6CF8.entryNum, fileInfo) != 0;
}

// .text:0x800A7544 size:0x24
s32 ConvertPathToEntryNum(void* file) {
    return DVDConvertPathToEntrynum(*(char**)file);
}

// .text:0x800A7568 size:0x84
// NONMATCHING 94%: original materializes the callback via r0 + mr r4,r0; the inlined copies in callers match
#if NONMATCHING
void fn_800A7568(void) {
    CancelTransfer();
}
#endif

// .text:0x800A75EC size:0x84
void fn_800A75EC(s32 result, DVDCommandBlock* block) {
    OSCancelThread(&gDataDecompressorValues.t);
    StartThreadForReadingFromDisk();
    SET_STATE_IDLE(DVDSYS_STATE_NONE, 1);
    if (gDataDecompressorValues._35C != NULL) {
        fn_800ACF14(gDataDecompressorValues._35C);
        gDataDecompressorValues._35C = NULL;
    }
    if (lbl_803C6CF8.tempBuf != NULL) {
        fn_800ACF14(lbl_803C6CF8.tempBuf);
        lbl_803C6CF8.tempBuf = NULL;
    }
}

// .text:0x800A7670 size:0x4C
void fn_800A7670(s32 result, DVDCommandBlock* block) {
    SET_STATE_IDLE(DVDSYS_STATE_NONE, 1);
    if (lbl_803C6CF8.tempBuf != NULL) {
        fn_800ACF14(lbl_803C6CF8.tempBuf);
        lbl_803C6CF8.tempBuf = NULL;
    }
}

// .text:0x800A76BC size:0xE4
void fn_800A76BC(void) {
    return;
}

// .text:0x800A77A0 size:0x2E0
void* fn_800A77A0(void* arg) {
    return 0;
}

// .text:0x800A7A80 size:0x54
void fn_800A7A80(s32 result, DVDFileInfo* fileInfo) {
    if (result == -3) {
        lbl_803C6CF8.remaining = 0;
        lbl_803C6CF8.chunkSize = 0;
    } else if (result != -1) {
        OSResumeThread(&lbl_803C6CF8.readThread);
    }
}

// fn_800A7AD4, size:0x4
void fn_800A7AD4(void) {
}

// .text:0x800A7AD8 size:0xD4
void fn_800A7AD8(void) {
    return;
}

// .text:0x800A7BAC size:0x5C
void fn_800A7BAC(u8 flag) {
    return;
}
