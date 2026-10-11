#ifndef __MENUS_MENU_ASSET_H__
#define __MENUS_MENU_ASSET_H__

#include "mssbTypes.h"

// Disc/ARAM file entry (AssetLoadInstructions in Unknown/File_0x800a64e0.h).
typedef struct MenuAsset {
    /*0x0*/ u32 lz;             // repetition size << 8 | look-back size
    /*0x4*/ u32 sizeFlags;      // low 28 bits: size, top 4 bits: flags
    /*0x8*/ u32 aramOffset;
    /*0xC*/ u32 compressedSize;
} MenuAsset;

// Model and animation file tables (defined in rep_0F60.c).
extern MenuAsset lbl_2_data_2F990[13];
extern MenuAsset lbl_2_data_2FA60[54];
extern s32 lbl_2_data_2FDC0[32]; // lbl_2_data_2FA60 index per kind

#endif
