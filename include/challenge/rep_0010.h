#ifndef __CHALLENGE_REP_0010_H_
#define __CHALLENGE_REP_0010_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXTypes.h"

// Common header of a process-queue task (see Task in main/file_800A7C08.h).
// Each challenge task overlays its own work area at 0x14.
typedef struct ChTaskHeader {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct ChTaskHeader* prev;
    /*0x08*/ struct ChTaskHeader* next;
    /*0x0C*/ struct ChTaskHeader* parent; // task that queued this one
    /*0x10*/ s16 result;                  // set by child tasks: 1 = done
    /*0x12*/ u16 priority;
} ChTaskHeader; // size: 0x14

// Test-menu task (fn_1_1148 / fn_1_16A0).
typedef struct ChMenuTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ s16 _14;
    /*0x16*/ s16 cursor; // selected test, 0..9
} ChMenuTask;

// Current task (lbl_803CC1B8). Typed SceneTask* in main/file_80069BDC.h; the challenge
// code overlays the Ch*Task structs on it.
extern void* lbl_803CC1B8;

// Texture archive after convertTextureHeader: a count followed by 0x20-byte image records.
typedef struct ChTexArchive {
    /*0x0*/ u32 count;
    /*0x4*/ u8 images[1][0x20]; // struct TexImage records
} ChTexArchive;

// Full-screen texture draw node (two per task, indexed by lbl_803CBBC0), drawn by fn_1_1240.
typedef struct ChTexDrawNode {
    /*0x00*/ void* next; // draw-list link, set by fn_800A7D4C
    /*0x04*/ void (*draw)(struct ChTexDrawNode* node);
    /*0x08*/ ChTexArchive* tex;
    /*0x0C*/ s32 texIdx;
    /*0x10*/ u32 mode; // 0: material color, 1: color * texture alpha, 2: texture only
    /*0x14*/ GXColor color;
} ChTexDrawNode; // size: 0x18

void fn_1_5EC(void);
void fn_1_AF4(s32 rows, s32 cols, f32 spacing);
void fn_1_F2C(GXTevMode tevMode, s32 texFrac, s32 hasNormal);
void fn_1_1148(void);
void fn_1_11D0(void);
void fn_1_1240(ChTexDrawNode* node);

#endif
