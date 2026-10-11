#include "main/file_80008E00.h"
#include "main/file_80011640.h"
#include "main/file_800A6870.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "static/Pad.h"
extern PadState lbl_803C77B8[4];
#include "Dolphin/OS/OSReset.h"
#include "Dolphin/OS/OSModule.h"
#include "Dolphin/OS/OSCache.h"
#include "Dolphin/os.h"
#include "Dolphin/vi.h"
#include "musyx/musyx.h"
#include "Dolphin/gx.h"
#include "Dolphin/pad.h"
#include "Dolphin/ai.h"
#include "Dolphin/dvd.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/rand.h"
#include "main/file_80034F50.h"
#include "main/file_800A7C08.h"
#include "main/file_800B0724.h"
#include "main/file_8000F150.h"
#include "main/file_8000BA3C.h"
#include "main/file_80021308.h"

extern void (*lbl_803CBBB8)(void);
extern u32 lbl_803CBBB0;
extern u8 lbl_803CBBB4;
extern u8 lbl_803CBBC1;
extern u8 lbl_803CBBC2;
extern const f32 lbl_803CC400; // 7.0f
extern const f32 lbl_803CC404; // 6.0f
extern const f32 lbl_803CC408; // 12.0f
extern const f32 lbl_803CC40C; // -1.0f
extern const f32 lbl_803CC410; // 3.0f
extern const f32 lbl_803CC414; // -3.0f
extern const f32 lbl_803CC418; // 1.0f
extern const f32 lbl_803CC41C; // -6.0f



void fn_8001D2D4(void);
void fn_80035168(void);
void fn_80010FA0(void);
void fn_80011000(void);
void fn_80021064(void);
void fn_80021308(void);
void fn_800227E4(void);
void fn_80022D58(void);
void fn_80023CF4(u32 progressive);
void fn_80023D44(u32 value);
s32 fn_800A8518(s32 mode);
void fn_800AD01C(void* end);
void fn_800B0C80(void (*draw)(void));
void resetAllDrawingStructs(void);
s32 ConvertPathToEntryNum(void* file);
void DrawShadows(u8 enable);
u8 GetDrawShadows(void);
void fn_800BEC30(s32 value);
void somethingSetTexturePointer(void);
void fn_800A7AD8(void);
void fn_800A76BC(void);
void StartThreadForReadingFromDisk(void);
void f_initSound(void);
void fn_800A983C(void);
void resetAllDrawingStructs_tonop(void);
void fn_800A7D7C(void* buffer, s32 count);
void fn_80021AA0(void);
void fn_80036A3C(void);
void fn_800356B8(void);
void minigamesSetSomePointers2(void);
void fn_8003A2EC(void);
void fn_8004B270(void);
void fn_80052188(void);
void fn_80064534(void);
void fn_8001F16C(void);
void fn_8001AF98(void);
void fn_800A7BAC(u8 enable);
void fn_8001E784(void);
void fn_800A9520(void);
s32 fn_80021188(BOOL (*callback)(void));
s32 fn_800211BC(BOOL (*callback)(void));
void fn_8000F3E8(s32 mode);
void RunDrawScripts_with_stack_variables(void);
void fn_800B251C(void);
void fn_8003A090(void);
void fn_800A7DB0(void);
u32 fn_80023D3C(void);
void soundQuit(void);
void fn_800A94C4(void);
OSThread* GXSetCurrentGXThread(void);
s32 OSWaitSemaphore(volatile OSSemaphore* sem);

extern u8 lbl_803CBBC0; // index of the display list buffer in use
extern u8 lbl_801181A0[2][0x40];
extern s32 lbl_803CBBA8;
extern const GXColor lbl_803CD300;

// Entry of the current draw/process queue (see fn_800B0A5C_insertQueue).
typedef struct {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0xC];
    /*0x10*/ s16 _10;
    /*0x12*/ u16 priority;
    /*0x14*/ OSModuleHeader* module;
    /*0x18*/ u16 state;
    /*0x1A*/ u8 _1A[2];
    /*0x1C*/ u32 moduleSize;
} MainTask;
extern MainTask* lbl_803CC1B8;


typedef struct {
    /*0x000*/ DiskFileEntry dll[3];
    /*0x030*/ DiskFileEntry boot[3];
    /*0x060*/ DiskFileEntry files[62];
} FileTable; // size: 0x440
extern FileTable lbl_800E8AA8;

// Path descriptor passed to ConvertPathToEntryNum.
typedef struct {
    /*0x00*/ char* path;
    /*0x04*/ u32 _04[3];
} FilePath;
extern FilePath lbl_800E8EE8; // "aaaa.dat"
extern FilePath lbl_800E8EF8; // "ZZZZ.dat"




typedef struct {
    /*0x00*/ u8 _00[5];
    /*0x05*/ u8 _05;
    /*0x06*/ u8 _06[0xA];
} lbl_80110080_s; // size: 0x10
extern lbl_80110080_s lbl_80110080;


extern s32 lbl_803CBBD0;
extern s32 lbl_803CBBD4;
extern char lbl_800E6568[]; // "s32ProgId=%d\n"
extern char lbl_800E6578[]; // "s32DataId=%d\n"
extern char lbl_800E6588[]; // "Load dll. (%d) at %x\n"
extern char lbl_800E65A0[]; // "Call first function of the current dll.\n"

// fn_80008E00, size:0x8
void fn_80008E00(void (*value)(void)) {
    lbl_803CBBB8 = value;
}

extern ThpPlayer* lbl_803CBBBC;

extern s32 lbl_803CBBAC;

extern s32 lbl_803CBBA0;
extern u8 lbl_803CBBA4;

static inline u8 updateInGameFlag(void) {
    switch (lbl_803C6CF8.driveStatus) {
    case 0:
        lbl_803CBBA4 = 0;
        break;
    case -1:
    case 4:
    case 5:
    case 6:
    case 11:
        lbl_803CBBA0 = lbl_803C6CF8.driveStatus;
        lbl_803CBBA4 = 1;
        break;
    }
    return lbl_803CBBA4;
}

static inline BOOL checkResetRequested(u8 inGame) {
    u16 buttons = lbl_803C77B8[0].held;

    if (lbl_803CBBAC != 0) {
        if ((buttons & 0x1600) != 0x1600) {
            if ((lbl_80366158._20 == 0 || lbl_80366158._23 == 0) && lbl_803CBBB4 >= 5) {
                lbl_80366158._23 = 1;
            }
            lbl_803CBBB0 = 0;
            lbl_803CBBB4++;
        } else if (lbl_80366158._20 != 0 && lbl_80366158._23 != 0) {
            lbl_803CBBB4 = 0;
            lbl_803CBBB0++;
        }
        if (lbl_803CBBB0 >= 30) {
            lbl_803CBBC1 = 1;
        }
    }
    if (lbl_80366158.resetRequested) {
        return TRUE;
    }
    if ((lbl_803CBBC2 || lbl_803CBBC1) && !OSGetResetButtonState() && (!inGame || lbl_803C6CF8.driveStatus != -1) &&
        lbl_80366158._20) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x80008E08 size:0x1C8
BOOL fn_80008E08(void) {
    return checkResetRequested(updateInGameFlag());
}

// .text:0x80008FD0 size:0x3C
void PostRetraceCallback(u32 retraceCount) {
    if (OSGetResetButtonState() && lbl_803CBBAC != 0) {
        lbl_803CBBC2 = 1;
    }
}

// fn_8000900C, size:0xC
void fn_8000900C(void) {
    lbl_803CBBAC = 0x1;
}

// fn_80009018, size:0x10
void* fn_80009018(void* value) {
    void* previous = lbl_803CBBBC;
    lbl_803CBBBC = value;
    return previous;
}

// fn_80009028, size:0x6C
u8 fn_80009028(void) {
    return updateInGameFlag();
}

// .text:0x80009094 size:0x20
void fn_80009094(void) {
    fn_80035168();
}

// .text:0x800090B4 size:0x90
void fn_800090B4(void) {
    if (fn_80009028() != 1) {
        fn_8001D2D4();
    }
}

// .text:0x80009144 size:0x3C
void fn_80009144(void) {
    fn_800B0A5C_insertQueue(fn_800090B4, 0x6000);
    fn_800B0A5C_insertQueue(fn_80009094, 0x7000);
}

static inline void updateStream(s32 inGame) {
    u32 status;

    if (lbl_803CBBBC != NULL) {
        status = fn_800AD490(lbl_803CBBBC);
        if (inGame && (status == 1 || (status & 0x80000000))) {
            fn_800AD914(lbl_803CBBBC);
        } else if (!inGame && fn_800AD490(lbl_803CBBBC) == 2) {
            fn_800AD95C(lbl_803CBBBC, lbl_803CBBBC->flags);
        }
    }
}

static inline void stopAllMotors(void) {
    PADControlMotor(0, PAD_MOTOR_STOP_HARD);
    PADControlMotor(1, PAD_MOTOR_STOP_HARD);
    PADControlMotor(2, PAD_MOTOR_STOP_HARD);
    PADControlMotor(3, PAD_MOTOR_STOP_HARD);
}

// .text:0x80009180 size:0x55C
void main(void) {
    u8 inGame;
    BOOL reset;
    OSSemaphore* sem;
    u32 wasInGame;
    s32 result;
    u16 token;

    wasInGame = 0;
    initRenderMode(0, 0x40000, 0x10);
    fn_800BEC30(1);
    somethingSetTexturePointer();
    fn_800A7AD8();
    fn_800A76BC();
    fn_800A6870(1, 0x438);
    StartThreadForReadingFromDisk();
    f_initSound();
    fn_800A983C();
    resetAllDrawingStructs_tonop();
    fn_800A7D7C(lbl_801181A0[lbl_803CBBC0], 0x10);
    fn_80021AA0();
    DrawShadows(0);
    fn_80036A3C();
    fn_800356B8();
    lbl_803CBBC2 = 0;
    lbl_803CBBC1 = 0;
    VISetPostRetraceCallback(PostRetraceCallback);
    lbl_80366158._20 = 0;
    lbl_80366158._23 = 0;
    lbl_80366158.resetRequested = 0;
    lbl_80366158.resetCode = OSGetResetCode();
    minigamesSetSomePointers2();
    fn_8003A2EC();
    fn_8004B270();
    lbl_80366158._28 = 0;
    fn_80052188();
    fn_80064534();
    sem = &lbl_803C7420.drawDone;

    do {
        if (!wasInGame) {
            fn_8001F16C();
            fn_8001AF98();
        }
        fn_800A7BAC(1);
        OSWaitSemaphore(sem);
        GXSetCurrentGXThread();
        if (!wasInGame) {
            fn_8001E784();
        }
        fn_800A7BAC(0);
        lbl_803CBBC0 ^= 1;
        fn_800A9520();
        fn_800A7D7C(lbl_801181A0[lbl_803CBBC0], 0x10);

        inGame = updateInGameFlag();
        if (wasInGame != inGame) {
            if (inGame == 0) {
                result = fn_80021188(fn_80008E08);
                lbl_803CBBA8 = 0;
            } else {
                result = fn_800211BC(fn_80008E08);
                lbl_803CBBA8 = 1;
            }
            if (result != 0) {
                break;
            }
        }
        wasInGame = inGame;

        updateStream(inGame);
        if (inGame) {
            fn_8000F3E8(lbl_803CBBA0);
        } else {
            RunDrawScripts_with_stack_variables();
            fn_800B251C();
        }
        OSWaitSemaphore(sem);
        GXSetCurrentGXThread();
        fn_8003A090();
        while (*(volatile u8*)&lbl_803C7420.drawing != 0) {
        }
        GXSetCurrentGXThread();
        GXFlush();
        if (GetDrawShadows()) {
            GXSetCopyClear(lbl_803CD300, 0xFFFFFF);
        }
        fn_800A7DB0();
        if (lbl_803CBBB8 != NULL) {
            VISetBlack(TRUE);
            VIFlush();
            VIWaitForRetrace();
            fn_80023D3C();
            lbl_803CBBB8();
            VISetBlack(FALSE);
            VIFlush();
            VIWaitForRetrace();
        }
        lbl_803CBBB8 = NULL;
    } while (!checkResetRequested(inGame));

    DVDDumpWaitingQueue();
    GXSetCurrentGXThread();
    token = rand();
    GXSetDrawSync(token);
    GXFlush();
    while (token != GXReadDrawSync()) {
    }
    AIRegisterStreamCallback(NULL);
    AIResetStreamSampleCount();
    AISetStreamPlayState(0);
    soundQuit();
    VISetBlack(TRUE);
    VIFlush();
    VIWaitForRetrace();
    fn_800A94C4();
    if (lbl_80366158.resetRequested) {
        stopAllMotors();
        OSResetSystem(TRUE, 0, TRUE);
        return;
    }
    reset = FALSE;
    if (DVDCheckDisk() && lbl_803CBBA8 == 0) {
        reset = TRUE;
    }
    reset = (reset == FALSE);
    stopAllMotors();
    OSResetSystem(reset, (fn_80023D3C() ? 2 : 0) | 1, FALSE);
}

// .text:0x800096DC size:0xC4
void PrepFilesToBeLoaded(void) {
    MainTask* task;

    lbl_80366158.arenaStart = lbl_803C7420.heapLo;
    task = lbl_803CC1B8;
    lbl_80366158.arenaEnd = lbl_803C7420.heapHi;
    lbl_803CBBD4 = ConvertPathToEntryNum(&lbl_800E8EE8);
    lbl_803CBBD0 = ConvertPathToEntryNum(&lbl_800E8EF8);
    task->state = 0;
    lbl_803CC1B8->func = fn_800097A0;
    OSReport(lbl_800E6568, lbl_803CBBD4);
    OSReport(lbl_800E6578, lbl_803CBBD0);
    lbl_80110080._05 = 4;
    lbl_80366158._1D = 1;
}

// NONMATCHING 95%: the original addresses lbl_800E8AA8 and the tables after it through one pooled
// base register (they are data of this unit, not split yet); fn_80009144 is not inlined (pragma)
// .text:0x800097A0 size:0x6F4
#if NONMATCHING
#pragma dont_inline on
void fn_800097A0(void) {
    MainTask* task;
    OSModuleHeader* module;
    DiskFileEntry* file;
    BOOL progressive;
    FileTable* table = &lbl_800E8AA8;

    lbl_80366158._26 = 0;
    lbl_80366158._25 = 0;
    task = lbl_803CC1B8;
    switch (task->state) {
    case 0:
        g_d_GameSettings._06 = 0;
        fn_800AD054(lbl_80366158.arenaStart, lbl_80366158.arenaEnd);
        fn_80021308();
        lbl_803C6CF8.entryNum = lbl_803CBBD0;
        lbl_80366B18.fontArchive = ARAMTransfer(table->boot, 0, 0, 0);
        task->state = 1;
        break;
    case 1:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            lbl_80366B18.iconArchive = ARAMTransfer(&table->boot[2], 0, 1, 0);
            task->state = 2;
        }
        break;
    case 2:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            fn_80011000();
            lbl_80366B18.tables[0] = ARAMTransfer(&table->boot[1], 0, 1, 0);
            task->state = 3;
        }
        break;
    case 3:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            fn_800111B4(lbl_80366B18.tables[0]);
            fn_80010FA0();
            task->state = 4;
        }
        break;
    case 4:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            task->state = 5;
        }
        break;
    case 5:
        if (fn_80035838(&table->files[0x25], 0)) {
            fn_800B0C80(fn_80021064);
            task->state = 6;
        }
        break;
    case 6:
        if (fn_80035838(&table->files[0xF], 1)) {
            fn_800216F8(0, fn_8002158C);
            task->_10 = 0;
            task->state = 7;
        }
        break;
    case 7:
        if (task->_10 == 0) {
            break;
        }
        lbl_80366158.arenaStart = lbl_803C7898.lo;
        if ((lbl_80366158.resetCode & 1) && (lbl_80366158.resetCode & 0x80000000)) {
            fn_80023CF4((lbl_80366158.resetCode >> 1) & 1);
            progressive = FALSE;
        } else if (VIGetDTVStatus() == 0) {
            fn_80023D44(0);
            progressive = FALSE;
        } else {
            progressive = FALSE;
            if (OSGetProgressiveMode() == 1 ||
                ((lbl_803C77B8[0].held | lbl_803C77B8[1].held | lbl_803C77B8[2].held | lbl_803C77B8[3].held) & 0x200)) {
                progressive = TRUE;
            }
        }
        if (progressive) {
            lbl_80366158._1D = 0;
        } else {
            lbl_80366158._1D = 9;
        }
        if ((lbl_80366158.resetCode & 1) && (lbl_80366158.resetCode & 0x80000000)) {
            lbl_80366158._29 = 1;
        } else {
            lbl_80366158._29 = 0;
        }
        fn_800AD01C(lbl_80366158.arenaEnd);
        fn_80022D58();
        fn_800227E4();
        fn_80009144();
        // fallthrough
    case 8:
        g_d_GameSettings._06 = 1;
        fn_800AD038(lbl_80366158.arenaStart);
        lbl_803C6CF8.entryNum = lbl_803CBBD4;
        task->module = (OSModuleHeader*)ARAMTransfer(&table->dll[0], 0, 0, 0);
        task->moduleSize = table->dll[0].sizeFlags & 0x0FFFFFFF;
        OSReport(lbl_800E6588, 0, task->module);
        task->state = 9;
        break;
    case 9:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            module = task->module;
            lbl_803C6CF8.entryNum = lbl_803CBBD0;
            OSLink(&module->info, _OSAllocFromHeap(0x20, module->bssSize));
            ICInvalidateRange(task->module, task->moduleSize);
            lbl_80366158.arenaAfterDll = lbl_803C7898.lo;
            ((void (*)(void))module->prolog)(); // TODO type: relocated by OSLink
            task->_10 = 0;
            OSReport(lbl_800E65A0);
            task->state = 10;
        }
        break;
    case 10:
        if (task->_10 != 0) {
            fn_80021410();
            resetAllDrawingStructs();
            fn_80009144();
            module = task->module;
            ((void (*)(void))module->epilog)();
            OSUnlink(&module->info);
            switch (task->_10) {
            case 1:
                task->state = 11;
                break;
            }
        }
        break;
    case 11:
        g_d_GameSettings._06 = 2;
        fn_800AD038(lbl_80366158.arenaStart);
        lbl_803C6CF8.entryNum = lbl_803CBBD4;
        file = &table->dll[1];
        task->module = (OSModuleHeader*)ARAMTransfer(file, 0, 0, 0);
        task->moduleSize = file->sizeFlags & 0x0FFFFFFF;
        OSReport(lbl_800E6588, 1, task->module);
        task->state = 12;
        lbl_80366158._1C = 0;
        break;
    case 12:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            module = task->module;
            lbl_803C6CF8.entryNum = lbl_803CBBD0;
            OSLink(&module->info, _OSAllocFromHeap(0x20, module->bssSize));
            ICInvalidateRange(task->module, task->moduleSize);
            lbl_80366158.arenaAfterDll = lbl_803C7898.lo;
            ((void (*)(void))module->prolog)();
            task->_10 = 0;
            OSReport(lbl_800E65A0);
            task->state = 13;
        }
        break;
    case 13:
        if (lbl_80366158._1C) {
            DrawShadows(0);
            sndSilence();
        }
        task->state = 14;
        // fallthrough
    case 14:
        if (lbl_80366158._1C != 0 && fn_800A8518(3) != 0) {
            fn_800A8B78(fn_800A88C0());
            fn_80021410();
            resetAllDrawingStructs();
            fn_80009144();
            module = task->module;
            ((void (*)(void))module->epilog)();
            OSUnlink(&module->info);
            task->state = 8;
            g_d_GameSettings.miniGameStadiumIndicator = 0;
            if (g_d_GameSettings.GameModeSelected == 4) {
                lbl_80366158._1D = 7;
                lbl_80366158._29 = 2;
            } else if (!g_d_GameSettings.exhibitionMatchInd) {
                if (g_d_GameSettings.GameModeSelected == 5 && g_d_GameSettings.bJMatchInd == 0) {
                    lbl_80366158._1D = 1;
                } else {
                    g_d_GameSettings.GameModeSelected = 5;
                }
            } else if ((u8)(g_d_GameSettings.GameModeSelected - 6) <= 1 || g_d_GameSettings.GameModeSelected == 2) {
                lbl_80366158._1D = 1;
            } else if (lbl_80366158._1C == 1) {
                lbl_80366158._1D = 1;
            } else {
                lbl_80366158._1D = 1;
            }
        }
        break;
    }
}
#pragma dont_inline reset
#endif

// .text:0x80009E94 size:0x178
void interpolatePointsUnknown(s32 i, BezierPoint* pts, u32 first, u32 last) {
    BezierPoint* p0 = &pts[i - 3];
    BezierPoint* p1 = &pts[i];
    BezierPoint* p2 = &pts[i + 3];
    BezierPoint* a0 = &pts[i - 2];
    BezierPoint* a1 = &pts[i - 1];
    BezierPoint* b0 = &pts[i + 1];
    BezierPoint* b1 = &pts[i + 2];

    if (first) {
        a0->x = (lbl_803CC400 * p0->x + lbl_803CC404 * p1->x - p2->x) / lbl_803CC408;
        a0->y = (lbl_803CC400 * p0->y + lbl_803CC404 * p1->y - p2->y) / lbl_803CC408;
    }
    a1->x = (lbl_803CC404 * p1->x + p0->x - p2->x) / lbl_803CC404;
    a1->y = (lbl_803CC404 * p1->y + p0->y - p2->y) / lbl_803CC404;
    b0->x = (p2->x + (lbl_803CC40C * p0->x + lbl_803CC404 * p1->x)) / lbl_803CC404;
    b0->y = (p2->y + (lbl_803CC40C * p0->y + lbl_803CC404 * p1->y)) / lbl_803CC404;
    if (last) {
        b1->x = (lbl_803CC40C * p0->x + lbl_803CC404 * p1->x + lbl_803CC400 * p2->x) / lbl_803CC408;
        b1->y = (lbl_803CC40C * p0->y + lbl_803CC404 * p1->y + lbl_803CC400 * p2->y) / lbl_803CC408;
    }
}

// NONMATCHING 90%: float register allocation only (constants/temps in different fN)
// .text:0x8000A00C size:0x88
#if NONMATCHING
void BezierInterpolate(f32 t, BezierPoint* out, BezierPoint* p0, BezierPoint* p1, BezierPoint* p2, BezierPoint* p3) {
    f32 b0, b1, b2, b3;
    f32 t2 = t * t;
    f32 t3 = t2 * t;

    b0 = -t3 + lbl_803CC410 * t2 + lbl_803CC414 * t + lbl_803CC418;
    b1 = lbl_803CC410 * t3 + lbl_803CC41C * t2 + lbl_803CC410 * t;
    b2 = lbl_803CC414 * t3 + lbl_803CC410 * t2;
    b3 = t3;
    out->x = p0->x * b0 + p1->x * b1 + p2->x * b2 + b3 * p3->x;
    out->y = p0->y * b0 + p1->y * b1 + p2->y * b2 + b3 * p3->y;
}
#endif

// .text:0x8000A094 size:0x18
QuadCallback fn_8000A094(QuadCallback value) {
    QuadCallback previous = lbl_80366188.callback;
    lbl_80366188.callback = value;
    return previous;
}
