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

// Sprite layout entry handed to fn_80034E20 (SpaniDesc in main/file_80034F50.h,
// which clashes with UnknownHomes_Static.h).
typedef struct MenuSpriteDesc {
    /*0x00*/ u16 type;
    /*0x02*/ u16 animId;
    /*0x04*/ f32 x;
    /*0x08*/ f32 y;
    /*0x0C*/ s32 unkC;
    /*0x10*/ u8 playMode;
    /*0x11*/ u8 layer;
    /*0x12*/ u8 unk12[2];
    /*0x14*/ u8 texId;
    /*0x15*/ u8 unk15[3];
    /*0x18*/ f32 scale;
    /*0x1C*/ u8 is3D;
    /*0x1D*/ u8 unk1D;
    /*0x1E*/ s16 unk1E;
} MenuSpriteDesc; // size 0x20

// Menu grid item initialiser (fn_2_54234 / fn_2_54354).
typedef struct {
    void* w0; // item handler, stored into the menu grid cell
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
} InitEntry;

// Model and animation file tables (defined in rep_0F60.c).
extern MenuAsset lbl_2_data_2F990[13];
extern MenuAsset lbl_2_data_2FA60[54];
extern s32 lbl_2_data_2FDC0[32]; // lbl_2_data_2FA60 index per kind

#endif
