#include "challenge/auto_00_00001538_text.h"
#include "challenge/rep_0000.h"
#include "challenge/rep_0010.h"
#include "challenge/auto_00_000085A8_text.h"
#include "challenge/auto_00_00026AF8_text.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80008E00.h"
#include "Unknown/File_0x800a64e0.h"

extern void fn_800A7D4C(s32 list, void* node);
extern u8 lbl_803CBBC0; // frame buffer index (0/1)

// Test entry points (other challenge units).
extern void fn_1_66C4(void);
extern void fn_1_17D90(void);
extern void fn_1_28200(void);
extern void fn_1_1D514(void);
extern void fn_1_A2E4(void);
extern void fn_1_24778(void);
extern void fn_1_2852C(void);
extern void fn_1_29A9C(void);

// Texture viewer task (fn_1_1634 -> fn_1_15CC -> fn_1_1538).
typedef struct ChTexViewTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ s32* file;         // loaded file; word 0 is the offset of the texture archive
    /*0x18*/ ChTexArchive* tex; // inside file
} ChTexViewTask;

// lbl_1_data_0
typedef struct ChMenuData {
    /*0x00*/ AssetLoadInstructions files[7];
    /*0x70*/ ChTexDrawNode nodes[2]; // per frame buffer
    /*0xA0*/ u32 mode;
    /*0xA4*/ GXColor color;
} ChMenuData;

extern ChMenuData lbl_1_data_0;
extern s32 lbl_1_bss_0; // texture shown by the viewer
extern ChDrawNode lbl_1_data_298[2];

// .text:0x000015CC size:0x68
void fn_1_15CC(void) {
    ChTexViewTask* task = lbl_803CC1B8;

    if ((s32)lbl_803C6CF8._715 == 1) {
        task->tex = (ChTexArchive*)((u8*)task->file + *task->file);
        convertTextureHeader(task->tex);
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1538;
    }
}

// .text:0x00001634 size:0x6C
void fn_1_1634(void) {
    if ((s32)lbl_803C6CF8._715 == 1) {
        // TODO port: ARAMTransfer returns the destination pointer (declared s32 in UnknownHomes_Static.h)
        ((ChTexViewTask*)lbl_803CC1B8)->file = (s32*)ARAMTransfer(&lbl_1_data_0.files[3], 0, 0, 0);
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_15CC;
    }
}

