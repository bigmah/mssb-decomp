#ifndef __UNKNOWN_FILE_0x800A64E0_H__
#define __UNKNOWN_FILE_0x800A64E0_H__

#include "types.h"
#include "Dolphin/os.h"

// One entry of the game's ARAM file tables (lbl_800EFD38 and friends); also
// called DiskFileEntry (main/file_80021308.h).
typedef struct AssetLoadInstructions
{
    /* 0x0 */ u32 compressionConstants; // repetition size << 8 | look-back size

    /* 0x4 */ union {
        struct {
            u8 compressionFlag:2;
            u8 unused:2;
            u32 originalDiskSize:28;
        };
        u32 sizeFlags; // low 28 bits: size, top 4 bits: flags
    };
    /* 0x8 */ union {
        u32 diskLocation;
        u32 aramOffset; // relative to the table's ARAM base
    };
    /* 0xC */ u32 compressedSize;
} AssetLoadInstructions; // size: 0x10

u32 ReadBits(u32 bits);

void SetReadParameters(AssetLoadInstructions * instructions, void* pCompressedData, void*pOutData, BOOL param_4);

void *ReadDataFromDisk(void * /* unused */);

void DecompressDiskData();

typedef struct
{
    OSThread t ATTRIBUTE_ALIGN(16);       // 0x000
    OSSemaphore s[2] ATTRIBUTE_ALIGN(16); // 0x320

    int BytesToRead;          // 0x338
    size_t CachedBytesToRead; // 0x33C
    int volatile ReadOffset;  // 0x340
    u32 bitBuffer;            // 0x344
    u8 * volatile DataWriteBottom;      // 0x348
    u8 *DataReadBottom;       // 0x34C
    u8 *CachedDataReadBottom; // 0x350
    void *DataReadTop;        // 0x354
    u8 * volatile DataWriteTop;         // 0x358
    void* _35C;               // 0x35C (freed by dvdsys.c)

    s8 volatile segmentCount; // 0x360
    u8 BitsInBuffer;          // 0x361
    u8 LookBackSize;          // 0x362
    u8 RepetitionSize;        // 0x363
    s8 error;                 // 0x364
    s8 compressedFlag;        // 0x365
    u8 ShouldWriteDataFlag;   // 0x366
} DataVars;

extern DataVars gDataDecompressorValues;

void StartThreadForReadingFromDisk(void);

#endif
