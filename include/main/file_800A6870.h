#ifndef __MAIN_FILE_800A6870_H__
#define __MAIN_FILE_800A6870_H__

#include "mssbTypes.h"
#include "Dolphin/os.h"
#include "Dolphin/dvd.h"
#include "Dolphin/ar.h"
#include "Unknown/File_0x800a64e0.h"

// dvdsys.c: streams files from disc (optionally LZSS-compressed, see File_0x800a64e0.c)
// into RAM, ARAM, or a ring buffer, using a monitor thread and a read thread.

// Transfer modes (ARAMLoader.mode / ARAMTransfer's mode argument).
#define DVDSYS_MODE_DISC_LZ_TO_RAM  0 // disc -> RAM, decompressed
#define DVDSYS_MODE_DISC_TO_RAM     1 // disc -> RAM
#define DVDSYS_MODE_DISC_TO_ARAM    2 // disc -> ARAM (dest is an ARAM address)
#define DVDSYS_MODE_ARAM_LZ_TO_RAM  3 // ARAM -> RAM, decompressed
#define DVDSYS_MODE_ARAM_TO_RAM     4 // ARAM -> RAM

#include "main/aramloader.h" // ARAMLoader lbl_803C6CF8, DVDSYS_STATE_*

u32 fn_800A6870(u8 enable, u32 limit);
void fn_800A6890(u32 request);
void fn_800A68D4(u32 request);
void* fn_800A6900(void* arg);
void fn_800A6C80(void);
void fn_800A6D10(s32 consumed);
void fn_800A6E24(AssetLoadInstructions* instr, u8* ringBuf, s32 ringSize);
void fn_800A6F94(s32 result, DVDFileInfo* fileInfo);
void* ARAMTransfer(AssetLoadInstructions* instr, void* dest, u8 mode, u32 aramAddr);
BOOL fn_800A750C(void* unused, DVDFileInfo* fileInfo);
s32 ConvertPathToEntryNum(void* file); // file: a struct whose first member is the path (char*)
void fn_800A7568(void);
void fn_800A75EC(s32 result, DVDCommandBlock* block);
void fn_800A7670(s32 result, DVDCommandBlock* block);
void fn_800A76BC(void);
void* fn_800A77A0(void* arg);
void fn_800A7A80(s32 result, DVDFileInfo* fileInfo);
void fn_800A7AD4(void);
void fn_800A7AD8(void);
void fn_800A7BAC(u8 flag);

#endif
