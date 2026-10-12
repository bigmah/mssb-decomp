#ifndef __MAIN_ARAMLOADER_H__
#define __MAIN_ARAMLOADER_H__

#include "mssbTypes.h"
#include "Dolphin/os.h"
#include "Dolphin/dvd.h"
#include "Dolphin/ar.h"
#include "Unknown/File_0x800a64e0.h"

// Split out of main/file_800A6870.h so that REL code can use the loader state without that
// header's prototypes (several units still declare ARAMTransfer with a void* argument).
// Transfer modes (ARAMLoader.mode / ARAMTransfer's mode argument).
#define DVDSYS_MODE_DISC_LZ_TO_RAM  0 // disc -> RAM, decompressed
#define DVDSYS_MODE_DISC_TO_RAM     1 // disc -> RAM
#define DVDSYS_MODE_DISC_TO_ARAM    2 // disc -> ARAM (dest is an ARAM address)
#define DVDSYS_MODE_ARAM_LZ_TO_RAM  3 // ARAM -> RAM, decompressed
#define DVDSYS_MODE_ARAM_TO_RAM     4 // ARAM -> RAM

// ARAMLoader.state
#define DVDSYS_STATE_NONE    0
#define DVDSYS_STATE_START   1 // (re)start the transfer from the beginning
#define DVDSYS_STATE_READING 2
#define DVDSYS_STATE_DONE    3 // last ARAM write finished
#define DVDSYS_STATE_RING    4 // ring-buffer streaming (fn_800A6E24)

typedef void (*DriveStatusCallback)(void);

typedef struct ARAMLoader {
    /*0x000*/ OSThread monitorThread; // fn_800A6900
    /*0x318*/ OSThread readThread;    // fn_800A77A0
    /*0x630*/ OSSemaphore aramSem;
    /*0x63C*/ ARQRequest arqRequests[4];
    /*0x6BC*/ u8* tempBufEnd;
    /*0x6C0*/ u32 aramCur; // ARAM address
    /*0x6C4*/ u32 aramStart; // ARAM address
    /*0x6C8*/ u8 arqIndex;
    /*0x6CC*/ DriveStatusCallback* driveStatusCallbacks; // indexed by DVDGetDriveStatus() + 1
    /*0x6D0*/ u32 retryLimit;
    /*0x6D4*/ u32 retryCount;
    /*0x6D8*/ u8 retryEnabled;
    /*0x6DC*/ DVDFileInfo* fileInfo;
    /*0x6E0*/ u32 sizeInfo; // raw copy of AssetLoadInstructions word 1 (flags + original size)
    /*0x6E4*/ s32 diskOffset;
    /*0x6E8*/ u32 bytesRead;
    /*0x6EC*/ u32 totalSize;
    /*0x6F0*/ s32 remaining;
    /*0x6F4*/ s32 chunkSize;
    /*0x6F8*/ u8* bufStart;
    /*0x6FC*/ void* tempBuf;
    /*0x700*/ u8* bufEnd; // output buffer for the decompressing modes
    /*0x704*/ u8* writePos;
    /*0x708*/ u8* readPos;
    /*0x70C*/ s32 ringSize;
    /*0x710*/ s32 buffered;
    /*0x714*/ volatile u8 state; // DVDSYS_STATE_*; written together with idle as one halfword
    /*0x715*/ volatile s8 idle;
    /*0x716*/ u8 _716;
    /*0x717*/ u8 mode; // DVDSYS_MODE_*
    /*0x718*/ s32 entryNum;
    /*0x71C*/ AssetLoadInstructions* instr;
    /*0x720*/ u16 compression;
    /*0x722*/ s8 driveStatus; // DVDGetDriveStatus() result (-1: none)
    /*0x723*/ u8 ringFull;
} ARAMLoader; // size: 0x728 (fields end at 0x724; OSThread makes it 8-aligned)

extern ARAMLoader lbl_803C6CF8;

#endif
