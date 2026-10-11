#include "main/file_800A7C08.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"
#include "Dolphin/vi.h"
#include "Dolphin/card.h"
#include "Dolphin/dvd.h"
#include "Dolphin/ai.h"
#include "Dolphin/pad.h"
#include "stl/mem.h"
#include "main/file_800B0724.h"

extern OSThread* GXSetCurrentGXThread(void);
extern s32 OSSignalSemaphore(OSSemaphore* sem);

// .text:0x800A7C08 size:0x144
// NONMATCHING 99%: int->float magic constant and 0.0f/1.0f live in unsplit .sdata2 (reloc names differ); r3/r4 swapped in the callback loop
#if NONMATCHING
void* fn_800A7C08(void* arg) {
    GXRenderModeObj* rmode;
    DrawCallbackNode* node;
    u32 next;

    lbl_803C7420.field = 0;
    while (TRUE) {
        OSSleepThread(&lbl_803C7420.drawQueue);
        GXSetCurrentGXThread();
        rmode = lbl_803C7420.renderMode;
        lbl_803C7420.drawing = TRUE;
        if (rmode->field_rendering) {
            GXSetViewportJitter(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f, VIGetNextField());
        } else {
            GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f);
        }
        GXInvalidateVtxCache();
        node = (DrawCallbackNode*)lbl_803C7420.drawList;
        while (TRUE) {
            next = node->next.raw;
            if (next == 0) {
                break;
            }
            if (!(next & 1) && (next & 2) == lbl_803C7420.field) {
                if (node->func != NULL) {
                    node->func();
                }
            }
            node = (DrawCallbackNode*)(next & ~3);
        }
        lbl_803C7420.drawing = FALSE;
        OSSignalSemaphore(&lbl_803C7420.drawDone);
    }
}
#endif

// .text:0x800A7D4C size:0x30
void fn_800A7D4C(s32 index, DrawCallbackNode* node) {
    node->next.bits.addr = lbl_803C7420.drawList[index].bits.addr;
    lbl_803C7420.drawList[index].raw = (u32)node | 1;
}

// .text:0x800A7D7C size:0x34
void fn_800A7D7C(DrawLink* list, s32 count) {
    lbl_803C7420.drawList = list;
    count--;
    do {
        list->raw = (u32)(list + 1) | 1;
        list++;
    } while (--count != 0);
    list->raw = 0;
}

// .text:0x800A7DB0 size:0x50
void fn_800A7DB0(void) {
    OSSleepThread(&lbl_803C7420.retraceQueue);
    GXSetColorUpdate(GX_TRUE);
    VIFlush();
    GXDrawDone();
    GXCopyDisp(lbl_803C7420.xfb, GX_TRUE);
}

// .text:0x800A7E00 size:0x110
// NONMATCHING 98%: int->float magic constant lives in unsplit .sdata2 (reloc name differs); lis order of &GXNtsc480Int vs &lbl_803C7420 swapped
#if NONMATCHING
void fn_800A7E00(void) {
    GXRenderModeObj* rmode = &lbl_803C7420.renderModeCopy;
    GXAdjustForOverscan(&GXNtsc480Int, rmode, 0, 16);
    lbl_803C7420.renderMode = rmode;
    VIConfigure(rmode);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GXSetDispCopySrc(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
    GXSetDispCopyDst(lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->xfbHeight);
    GXSetDispCopyYScale((f32)lbl_803C7420.renderMode->xfbHeight / (f32)lbl_803C7420.renderMode->efbHeight);
    GXSetScissor(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
    GXSetCopyFilter(lbl_803C7420.renderMode->aa, lbl_803C7420.renderMode->sample_pattern, GX_TRUE,
                    lbl_803C7420.renderMode->vfilter);
}
#endif

// .text:0x800A7F10 size:0x1D8
// NONMATCHING 99%: int->float magic constant lives in unsplit .sdata2 (reloc name differs); lis order of &GXNtsc480Int vs &lbl_803C7420 swapped
#if NONMATCHING
void fn_800A7F10(BOOL reset) {
    if (reset) {
        GXRenderModeObj* rmode = &lbl_803C7420.renderModeCopy;
        GXAdjustForOverscan(&GXNtsc480Int, rmode, 0, 16);
        lbl_803C7420.renderMode = rmode;
        VIConfigure(rmode);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
        GXSetDispCopySrc(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
        GXSetDispCopyDst(lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->xfbHeight);
        GXSetDispCopyYScale((f32)lbl_803C7420.renderMode->xfbHeight / (f32)lbl_803C7420.renderMode->efbHeight);
        GXSetScissor(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
        GXSetCopyFilter(lbl_803C7420.renderMode->aa, lbl_803C7420.renderMode->sample_pattern, GX_TRUE,
                        lbl_803C7420.renderMode->vfilter);
    } else {
        VIConfigure(lbl_803C7420.renderMode);
        VIFlush();
        VIWaitForRetrace();
        VIWaitForRetrace();
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
        GXSetDispCopySrc(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
        GXSetDispCopyDst(lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->xfbHeight);
        GXSetDispCopyYScale((f32)lbl_803C7420.renderMode->xfbHeight / (f32)lbl_803C7420.renderMode->efbHeight);
        GXSetScissor(0, 0, lbl_803C7420.renderMode->fbWidth, lbl_803C7420.renderMode->efbHeight);
        GXSetCopyFilter(lbl_803C7420.renderMode->aa, lbl_803C7420.renderMode->sample_pattern, GX_TRUE,
                        lbl_803C7420.renderMode->vfilter);
    }
}
#endif

// .text:0x800A80E8 size:0x3DC
void initRenderMode(void) {
    return;
}

// .text:0x800A84C4 size:0x54
void fn_800A84C4(u32 retraceCount) {
    if (!lbl_803C7420.drawing) {
        if (--lbl_803C7420.retraceCounter < 0) {
            lbl_803C7420.retraceCounter = lbl_803C7420.retraceInterval;
            OSWakeupThread(&lbl_803C7420.retraceQueue);
        }
    }
}

extern void (*lbl_803CC128)(void); // called once the stream has been shut down
extern volatile u32 lbl_803CC12C;           // stream error reported; skip the next play-address poll
extern volatile u32 lbl_803CC130;
extern volatile u8 lbl_803CC134;            // right volume
extern volatile u8 lbl_803CC135;            // left volume
extern volatile u32 lbl_803CC138;           // AI stream trigger interval
extern volatile u32 lbl_803CC13C;           // last stream play address
extern volatile u32 lbl_803CC140;           // playlist mode (STREAM_MODE_*)
extern volatile u32 lbl_803CC144;           // state saved while skipping tracks
extern volatile u32 lbl_803CC148;           // STREAM_STATE_*
extern StreamTrack* lbl_803CC14C;  // playlist tail
extern StreamTrack* lbl_803CC150;  // playlist head
extern StreamTrack* lbl_803CC154;  // current track

extern DVDCommandBlock lbl_802EF140;
extern DVDCommandBlock lbl_802EF170;
extern DVDCommandBlock lbl_802EF1A0;
extern DVDCommandBlock lbl_802EF1D0;
extern DVDCommandBlock lbl_802EF200;
extern DVDCommandBlock lbl_802EF230;
extern DVDCommandBlock lbl_802EF260;
extern DVDCommandBlock lbl_802EF290;

extern GlobalState6CF8 lbl_803C6CF8;

extern s32 ConvertPathToEntryNum(void* file);
extern BOOL fn_800A750C(void* file, DVDFileInfo* fileInfo);
extern BOOL DVDPrepareStreamAsync(DVDFileInfo* fileInfo, u32 length, u32 offset, DVDCallback callback);
extern BOOL DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback);
extern BOOL DVDGetStreamErrorStatusAsync(DVDCommandBlock* block, DVDCBCallback callback);
extern BOOL DVDGetStreamPlayAddrAsync(DVDCommandBlock* block, DVDCBCallback callback);

// Shared by fn_800A8518 and fn_800A86B4 (inlined into both).
static inline s32 StreamCommand(s32 cmd) {
    StreamTrack* track;
    BOOL enabled;

    if (lbl_803CC154 != NULL) {
        if (lbl_803CC148 == STREAM_STATE_BUSY) {
            return 0;
        }
        switch (cmd) {
        case 1:
            fn_800A88D8(STREAM_STATE_PLAY);
            break;
        case 2:
            fn_800A88D8(STREAM_STATE_PAUSE);
            break;
        case 3:
            fn_800A88D8(STREAM_STATE_STOP);
            break;
        case 4:
            if (lbl_803CC148 != STREAM_STATE_BUSY && lbl_803CC154 != NULL) {
                lbl_803CC144 = lbl_803CC148;
                lbl_803CC148 = STREAM_STATE_BUSY;
                if (lbl_803CC144 == STREAM_STATE_PLAY) {
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    DVDCancelStreamAsync(&lbl_802EF170, fn_800A9034);
                } else {
                    enabled = OSDisableInterrupts();
                    if (lbl_803CC154 != NULL && (track = lbl_803CC154->next) != NULL) {
                        lbl_803CC154 = track;
                    }
                    OSRestoreInterrupts(enabled);
                    lbl_803CC148 = lbl_803CC144;
                }
            }
            break;
        case 5:
            if (lbl_803CC148 != STREAM_STATE_BUSY && lbl_803CC154 != NULL) {
                lbl_803CC144 = lbl_803CC148;
                lbl_803CC148 = STREAM_STATE_BUSY;
                if (lbl_803CC144 == STREAM_STATE_PLAY) {
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    DVDCancelStreamAsync(&lbl_802EF140, fn_800A8FDC);
                } else {
                    enabled = OSDisableInterrupts();
                    if (lbl_803CC154 != NULL && (track = lbl_803CC154->prev) != NULL) {
                        lbl_803CC154 = track;
                    }
                    OSRestoreInterrupts(enabled);
                    lbl_803CC148 = lbl_803CC144;
                }
            }
            break;
        }
    }
    return 1;
}

// .text:0x800A8518 size:0x19C
s32 fn_800A8518(s32 cmd) {
    return StreamCommand(cmd);
}

// .text:0x800A86B4 size:0x1B0
void fn_800A86B4(s32 cmd) {
    while (StreamCommand(cmd) == 0) {
    }
}

// fn_800A8864, size:0x14
u16 fn_800A8864(void) {
    u16 value = lbl_803CC135;
    value = (value << 8) | lbl_803CC134;
    return value;
}

// .text:0x800A8878 size:0x48
void fn_800A8878(u8 left, u8 right) {
    lbl_803CC135 = left;
    lbl_803CC134 = right;
    if (lbl_803CC148 == STREAM_STATE_PLAY) {
        AISetStreamVolLeft(left);
        AISetStreamVolRight(right);
    }
}

// fn_800A88C0, size:0x8
StreamTrack* fn_800A88C0(void) {
    return lbl_803CC154;
}

// fn_800A88C8, size:0x8
u32 fn_800A88C8(void) {
    return lbl_803CC148;
}

// fn_800A88D0, size:0x8
u32 fn_800A88D0(void) {
    return lbl_803CC140;
}

// .text:0x800A88D8 size:0x1D8
// NONMATCHING 99%: the early 'state == BUSY' return compiles to beq instead of the original's bne/b pair
#if NONMATCHING
void fn_800A88D8(u32 state) {
    StreamTrack* track;

    if (lbl_803CC148 == state) {
        return;
    }
    if (lbl_803CC148 == STREAM_STATE_BUSY) {
        return;
    }
    switch (state) {
    case STREAM_STATE_STOP:
        if (lbl_803CC154 != NULL) {
            lbl_803CC148 = STREAM_STATE_BUSY;
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            DVDCancelStreamAsync(&lbl_802EF1A0, fn_800A908C);
        }
        break;
    case STREAM_STATE_PLAY:
        if (lbl_803CC148 == STREAM_STATE_PAUSE) {
            AISetStreamVolLeft(lbl_803CC135);
            AISetStreamVolRight(lbl_803CC134);
            AIResetStreamSampleCount();
            AISetStreamTrigger(lbl_803CC138);
            AISetStreamPlayState(1);
            track = lbl_803CC154;
            lbl_803CC148 = STREAM_STATE_PLAY;
            if (track != NULL) {
                STREAM_NOTIFY(track, STREAM_EVENT_PLAY);
            }
        } else if (lbl_803CC154 != NULL) {
            lbl_803CC148 = STREAM_STATE_BUSY;
            DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
        } else {
            lbl_803CC148 = STREAM_STATE_PLAY;
        }
        lbl_803CC12C = 0;
        break;
    case 4:
        if (lbl_803CC148 == STREAM_STATE_STOP) {
            if (lbl_803CC154 != NULL) {
                lbl_803CC148 = STREAM_STATE_BUSY;
                DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A93AC);
            }
            lbl_803CC12C = 0;
        }
        break;
    case STREAM_STATE_PAUSE:
        AISetStreamPlayState(0);
        if (lbl_803CC148 == STREAM_STATE_PLAY) {
            lbl_803CC148 = STREAM_STATE_PAUSE;
        }
        track = lbl_803CC154;
        STREAM_NOTIFY(track, STREAM_EVENT_PAUSE);
        break;
    }
}
#endif

// fn_800A8AB0, size:0x8
void fn_800A8AB0(u32 value) {
    lbl_803CC140 = value;
}

// .text:0x800A8AB8 size:0xC0
void fn_800A8AB8(void (*onShutdown)(void)) {
    StreamTrack* track;
    u32 prev;

    if (lbl_803CC148 == STREAM_STATE_BUSY) {
        return;
    }
    prev = lbl_803CC148;
    lbl_803CC128 = onShutdown;
    lbl_803CC148 = STREAM_STATE_BUSY;
    if (prev == STREAM_STATE_PLAY) {
        DVDCancelStreamAsync(&lbl_802EF1D0, fn_800A90E4);
        return;
    }
    AISetStreamPlayState(0);
    for (track = lbl_803CC150; track != NULL; track = track->next) {
        DVDClose(&track->fileInfo);
    }
    lbl_803CC150 = NULL;
    lbl_803CC14C = NULL;
    lbl_803CC154 = NULL;
    lbl_803CC148 = STREAM_STATE_STOP;
    if (lbl_803CC128 != NULL) {
        lbl_803CC128();
        lbl_803CC128 = NULL;
    }
    lbl_803CC148 = STREAM_STATE_STOP;
    lbl_803CC130 = 0;
}

// .text:0x800A8B78 size:0x144
s32 fn_800A8B78(StreamTrack* track) {
    BOOL enabled;

    if (track == lbl_803CC154) {
        return 2;
    }
    enabled = OSDisableInterrupts();
    DVDClose(&track->fileInfo);
    if (track == lbl_803CC150 && track == lbl_803CC14C) {
        lbl_803CC150 = NULL;
        lbl_803CC14C = NULL;
        OSRestoreInterrupts(enabled);
        return 0;
    }
    if (track == lbl_803CC150) {
        lbl_803CC150 = track->next;
        lbl_803CC150->prev = NULL;
        if (lbl_803CC140 == STREAM_MODE_LOOP) {
            lbl_803CC14C->next = lbl_803CC150;
        }
        OSRestoreInterrupts(enabled);
        return 0;
    }
    if (track == lbl_803CC14C) {
        lbl_803CC14C = track->prev;
        lbl_803CC14C->next = NULL;
        if (lbl_803CC140 == STREAM_MODE_LOOP) {
            lbl_803CC14C->next = lbl_803CC150;
        }
        OSRestoreInterrupts(enabled);
        return 0;
    }
    if (track->prev != NULL && track->next != NULL) {
        track->prev->next = track->next;
        track->next->prev = track->prev;
    }
    OSRestoreInterrupts(enabled);
    return 0;
}

// .text:0x800A8CBC size:0x174
s32 LoadFile(void* file, StreamTrack* track, u32 flags, void (*callback)(u32 event), u32 options) {
    StreamTrack* it;
    s32 savedEntry;
    BOOL startPlaying;
    BOOL enabled;

    if ((options & 1) && lbl_803CC150 != NULL) {
        for (it = lbl_803CC150; it != NULL; it = it->next) {
            if (it == track) {
                return 0x100;
            }
        }
    }
    startPlaying = FALSE;
    savedEntry = lbl_803C6CF8.entryNum;
    lbl_803C6CF8.entryNum = ConvertPathToEntryNum(file);
    if (fn_800A750C(file, &track->fileInfo) == FALSE) {
        return 1;
    }
    lbl_803C6CF8.entryNum = savedEntry;
    enabled = OSDisableInterrupts();
    track->file = file;
    track->flags = flags;
    track->callback = callback;
    if (lbl_803CC150 == NULL) {
        lbl_803CC150 = track;
        lbl_803CC14C = track;
        track->prev = NULL;
        track->next = NULL;
        if (lbl_803CC148 == STREAM_STATE_PLAY) {
            startPlaying = TRUE;
        }
    } else {
        lbl_803CC14C->next = track;
        track->prev = lbl_803CC14C;
        lbl_803CC154 = track;
        track->next = NULL;
    }
    if (lbl_803CC154 == NULL) {
        lbl_803CC154 = track;
    }
    OSRestoreInterrupts(enabled);
    STREAM_NOTIFY(track, STREAM_EVENT_LOADED);
    if (startPlaying) {
        lbl_803CC148 = STREAM_STATE_BUSY;
        DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
    }
    return 0;
}

// .text:0x800A8E30 size:0x138
s32 fn_800A8E30(void* file, StreamTrack* track, u32 flags, void (*callback)(u32 event)) {
    BOOL startPlaying;
    s32 savedEntry;
    BOOL enabled;

    startPlaying = FALSE;
    savedEntry = lbl_803C6CF8.entryNum;
    lbl_803C6CF8.entryNum = ConvertPathToEntryNum(file);
    if (fn_800A750C(file, &track->fileInfo) == FALSE) {
        return 1;
    }
    lbl_803C6CF8.entryNum = savedEntry;
    enabled = OSDisableInterrupts();
    track->file = file;
    track->flags = flags;
    track->callback = callback;
    if (lbl_803CC150 == NULL) {
        lbl_803CC150 = track;
        lbl_803CC14C = track;
        track->prev = NULL;
        track->next = NULL;
        if (lbl_803CC148 == STREAM_STATE_PLAY) {
            startPlaying = TRUE;
        }
    } else {
        lbl_803CC14C->next = track;
        track->prev = lbl_803CC14C;
        lbl_803CC154 = track;
        track->next = NULL;
    }
    if (lbl_803CC154 == NULL) {
        lbl_803CC154 = track;
    }
    OSRestoreInterrupts(enabled);
    STREAM_NOTIFY(track, STREAM_EVENT_LOADED);
    if (startPlaying) {
        lbl_803CC148 = STREAM_STATE_BUSY;
        DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
    }
    return 0;
}

// .text:0x800A8F68 size:0x74
void fn_800A8F68(void) {
    lbl_803CC148 = STREAM_STATE_STOP;
    lbl_803CC140 = STREAM_MODE_ONCE;
    lbl_803CC13C = 0;
    lbl_803CC138 = 12000;
    lbl_803CC135 = 255;
    lbl_803CC154 = NULL;
    lbl_803CC150 = NULL;
    lbl_803CC14C = NULL;
    lbl_803CC134 = 255;
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AIRegisterStreamCallback(fn_800A9168);
    AIResetStreamSampleCount();
    AISetStreamPlayState(0);
}

// .text:0x800A8FDC size:0x58
void fn_800A8FDC(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;
    BOOL enabled;

    AISetStreamPlayState(0);
    enabled = OSDisableInterrupts();
    if (lbl_803CC154 != NULL && (track = lbl_803CC154->prev) != NULL) {
        lbl_803CC154 = track;
    }
    OSRestoreInterrupts(enabled);
    lbl_803CC148 = STREAM_STATE_STOP;
    fn_800A88D8(lbl_803CC144);
}

// .text:0x800A9034 size:0x58
void fn_800A9034(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;
    BOOL enabled;

    AISetStreamPlayState(0);
    enabled = OSDisableInterrupts();
    if (lbl_803CC154 != NULL && (track = lbl_803CC154->next) != NULL) {
        lbl_803CC154 = track;
    }
    OSRestoreInterrupts(enabled);
    lbl_803CC148 = STREAM_STATE_STOP;
    fn_800A88D8(lbl_803CC144);
}

// .text:0x800A908C size:0x58
void fn_800A908C(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;

    AISetStreamPlayState(0);
    track = lbl_803CC154;
    STREAM_NOTIFY(track, STREAM_EVENT_STOP);
    lbl_803CC148 = STREAM_STATE_STOP;
}

// .text:0x800A90E4 size:0x84
void fn_800A90E4(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;

    AISetStreamPlayState(0);
    for (track = lbl_803CC150; track != NULL; track = track->next) {
        DVDClose(&track->fileInfo);
    }
    lbl_803CC150 = NULL;
    lbl_803CC14C = NULL;
    lbl_803CC154 = NULL;
    lbl_803CC148 = STREAM_STATE_STOP;
    if (lbl_803CC128 != NULL) {
        lbl_803CC128();
        lbl_803CC128 = NULL;
    }
    lbl_803CC148 = STREAM_STATE_STOP;
    lbl_803CC130 = 0;
}

// .text:0x800A9168 size:0x48
void fn_800A9168(u32 count) {
    AISetStreamTrigger(count + lbl_803CC138);
    if (lbl_803CC154 != NULL) {
        DVDGetStreamPlayAddrAsync(&lbl_802EF200, fn_800A91B0);
    }
}

// .text:0x800A91B0 size:0x1FC
// NONMATCHING 91%: the two STREAM_MODE_ONCE branches are laid out in the opposite order
#if NONMATCHING
void fn_800A91B0(s32 result, DVDCommandBlock* block) {
    StreamTrack* track;

    lbl_803CC13C = result;
    if (lbl_803CC12C != 0) {
        track = lbl_803CC154;
        lbl_803CC12C = 0;
        STREAM_NOTIFY(track, STREAM_EVENT_END);
        lbl_803CC148 = STREAM_STATE_BUSY;
        switch (lbl_803CC140) {
        case STREAM_MODE_LOOP:
            if (lbl_803CC154 != NULL) {
                if (lbl_803CC154->next != NULL) {
                    lbl_803CC154 = lbl_803CC154->next;
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    AISetStreamPlayState(0);
                    DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
                } else {
                    lbl_803CC154 = lbl_803CC150;
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    AISetStreamPlayState(0);
                    DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
                }
            }
            break;
        case STREAM_MODE_ONCE:
            if (lbl_803CC154 != NULL) {
                if (lbl_803CC154->next != NULL) {
                    lbl_803CC154 = lbl_803CC154->next;
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    AISetStreamPlayState(0);
                    DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
                } else {
                    lbl_803CC154 = lbl_803CC150;
                    AISetStreamVolLeft(0);
                    AISetStreamVolRight(0);
                    AISetStreamPlayState(0);
                    lbl_803CC148 = STREAM_STATE_STOP;
                }
            }
            break;
        case STREAM_MODE_REPEAT:
            if (lbl_803CC154 != NULL) {
                AISetStreamVolLeft(0);
                AISetStreamVolRight(0);
                AISetStreamPlayState(0);
                DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
            }
            break;
        }
    } else {
        DVDGetStreamErrorStatusAsync(&lbl_802EF230, fn_800A94A8);
    }
}
#endif

// .text:0x800A93AC size:0x78
void fn_800A93AC(s32 result, DVDFileInfo* fileInfo) {
    StreamTrack* track;

    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AISetStreamPlayState(0);
    DVDStopStreamAtEndAsync(&lbl_802EF260, NULL);
    track = lbl_803CC154;
    lbl_803CC148 = STREAM_STATE_PAUSE;
    STREAM_NOTIFY(track, STREAM_EVENT_PREPARED);
}

// .text:0x800A9424 size:0x84
void fn_800A9424(s32 result, DVDFileInfo* fileInfo) {
    StreamTrack* track;

    AISetStreamVolLeft(lbl_803CC135);
    AISetStreamVolRight(lbl_803CC134);
    AIResetStreamSampleCount();
    AISetStreamTrigger(lbl_803CC138);
    AISetStreamPlayState(1);
    DVDStopStreamAtEndAsync(&lbl_802EF290, NULL);
    track = lbl_803CC154;
    lbl_803CC148 = STREAM_STATE_PLAY;
    STREAM_NOTIFY(track, STREAM_EVENT_PLAY);
}

// fn_800A94A8, size:0x1C
void fn_800A94A8(s32 result, DVDCommandBlock* block) {
    if ((u8)result == 0) {
        lbl_803CC12C = 1;
        lbl_803CC13C = 0;
    }
}

extern void SISetSamplingRate(u32 msec);
extern PadConfig lbl_80110080;
extern PadState lbl_803C77B8[PAD_MAX_CONTROLLERS];

// .text:0x800A94C4 size:0x5C
void fn_800A94C4(void) {
    u32 mask = 0;
    PadState* pad = lbl_803C77B8;
    s32 i = 0;

    do {
        if (pad->err == PAD_ERR_NONE) {
            mask |= PAD_CHAN0_BIT >> i;
        }
        i++;
        pad++;
    } while (i < PAD_MAX_CONTROLLERS);
    PADRecalibrate(mask);
}

// .text:0x800A9520 size:0x2B0
// NONMATCHING 73%: the stick-direction bits are merged with rlwimi instead of the original's rlwinm/or chain, so more saved registers and a larger frame
#if NONMATCHING
void fn_800A9520(void) {
    PADStatus status[PAD_MAX_CONTROLLERS];
    PADStatus* st;
    PadState* pad;
    u32 i;
    PadConfig* cfg;
    u32 dirs;
    u16 prev;

    lbl_80110080.readMask = PADRead(status);
    PADClamp(status);
    st = status;
    pad = lbl_803C77B8;
    cfg = &lbl_80110080;
    for (i = 0; i < PAD_MAX_CONTROLLERS; i++, st++, pad++) {
        pad->err = st->err;
        if (pad->err == PAD_ERR_NO_CONTROLLER) {
            PADReset(PAD_CHAN0_BIT >> i);
        }
        if (pad->rumbleCmd == 1) {
            pad->rumbleCmd = 0;
            if (pad->rumbleMode == 0) {
                PADControlMotor(i, PAD_MOTOR_STOP_HARD);
            } else {
                PADControlMotor(i, PAD_MOTOR_RUMBLE);
                pad->rumbleCmd = 2;
            }
        } else if (pad->rumbleCmd == 2) {
            if (--pad->rumbleTimer == 0) {
                pad->rumbleCmd = 0;
                PADControlMotor(i, pad->rumbleMode & ~1);
            }
        }
        pad->analog = *(PadAnalog*)&st->triggerLeft;
        pad->sticks = *(PadSticks*)&st->stickX;
        dirs = ((pad->sticks.stickY > cfg->stickPos) << 19) | ((pad->sticks.stickY < cfg->stickNeg) << 18) |
               ((pad->sticks.stickX < cfg->stickNeg) << 16) | ((pad->sticks.stickX > cfg->stickPos) << 17) |
               ((pad->sticks.substickY < cfg->stickNeg) << 2) | ((pad->sticks.substickY > cfg->stickPos) << 3) |
               (pad->sticks.substickX < cfg->stickNeg) | ((pad->sticks.substickX > cfg->stickPos) << 1);
        pad->stickDirs = dirs;
        prev = pad->prev;
        pad->held = st->button | (dirs >> cfg->stickShift);
        pad->prev = pad->held;
        pad->down = pad->held & ~prev;
        pad->repeat = pad->down;
        if (pad->prev == prev) {
            if (pad->repeatDelay < 0) {
                if (--pad->repeatTimer <= 0) {
                    pad->repeat = pad->prev;
                    pad->repeatTimer = cfg->repeatRate;
                }
            } else if (--pad->repeatDelay < 0) {
                pad->repeat = pad->prev;
                pad->repeatTimer = cfg->repeatRate;
            }
        } else {
            pad->repeatDelay = cfg->repeatDelay;
        }
    }
}
#endif

// fn_800A97EC, size:0x50
void fn_800A97EC(s32 index, u32 duration, u8 mode) {
    PadState* pad = &lbl_803C77B8[index];
    if (!(lbl_80110080.rumbleLockMask & (1 << index))) {
        pad->rumbleTimer = duration;
        pad->rumbleMode = 0;
        if (duration != 0) {
            pad->rumbleMode = mode;
        }
        pad->rumbleCmd = 1;
    }
}

// fn_800A97D0, size:0x1C
void fn_800A97D0(u8 shift, s32 threshold) {
    lbl_80110080.stickShift = shift;
    lbl_80110080.stickNeg = -threshold;
    lbl_80110080.stickPos = threshold;
}

// .text:0x800A983C size:0x28
void fn_800A983C(void) {
    PADInit();
    SISetSamplingRate(0);
}

extern CardSystem lbl_803C7838;
extern Task* lbl_803CC1B8;            // currently running task
extern u64 lbl_802EF2C0[2];           // expected serial number per slot
extern CARDMemoryCard lbl_802EF3A0;   // CARD work area
extern CARDStat lbl_802EF330;
extern u16 lbl_800E7800[256];         // CRC-16 table
extern char lbl_803CCEE0[8];          // OSPanic file name
extern char lbl_800E7B28[];           // OSPanic message

extern s32 CARDGetResultCode(s32 chan);
extern s32 CARDGetXferredBytes(s32 chan);
extern s32 CARDCheckAsync(s32 chan, CARDCallback callback);
extern s32 CARDFormatAsync(s32 chan, CARDCallback callback);
extern s32 CARDDeleteAsync(s32 chan, const char* fileName, CARDCallback callback);
extern s32 CARDFastDelete(s32 chan, char* fileName);
extern void CARDInit(void);

// Classifies lbl_803C7838.status: 0 = still busy, 1 = ready, 2 = error.
static inline s32 CardStatusClass(void) {
    u8 status = lbl_803C7838.status;
    if (status == CARD_STATUS_BUSY) {
        return 0;
    }
    if (status == CARD_STATUS_READY) {
        return 1;
    }
    return 2;
}

// .text:0x800A9864 size:0x98
void fn_800A9864(u8 chan, u8 mode, u64 serial) {
    CardMountTask* task;

    lbl_803C7838.op = 6;
    task = fn_800B0A5C_insertQueue(fn_800A98FC, 0xFF);
    memset(&task->step, 0, sizeof(Task) - OFFSET_OF(Task, data));
    task->chan = chan;
    task->mode = mode;
    lbl_802EF2C0[chan] = serial;
    lbl_803CC1B8->result = 0;
}

// .text:0x800A98FC size:0x3FC
// NONMATCHING 89%: switch jump table lives in unsplit .data (reloc names differ); status classification compiled into a different branch layout
#if NONMATCHING
void fn_800A98FC(void) {
    CardMountTask* task = (CardMountTask*)lbl_803CC1B8;
    u8 chan;
    s32 res;
    s32 cls;
    BOOL busy;
    u64 serial;

    switch (task->step) {
    case 0:
        chan = task->chan;
        fn_800ACD64(CARDUnmount(chan));
        fn_800ACD64(lbl_803C7838.slots[chan].probeResult);
        cls = CardStatusClass();
        if (cls == 1) {
            fn_800ACD64(lbl_803C7838.slots[chan].sectorSize == 0x2000 ? CARD_RESULT_READY
                                                                     : CARD_RESULT_BAD_SECTOR_SIZE);
            cls = CardStatusClass();
        }
        switch (cls) {
        case 1:
            task->step = 1;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 1:
        if (task->mode == 1) {
            res = CARDMountAsync(task->chan, &lbl_802EF3A0, NULL, NULL);
            if (res == CARD_RESULT_BUSY) {
                busy = TRUE;
            } else {
                fn_800ACD64(res);
                busy = FALSE;
            }
        } else {
            fn_800ACD64(CARDMount(task->chan, &lbl_802EF3A0, NULL));
            busy = FALSE;
        }
        if (!busy) {
            task->step = 2;
        }
        break;
    case 2:
        fn_800ACD64(CARDGetResultCode(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case 1:
        case 2:
        case CARD_STATUS_READY:
            task->step = 3;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 3:
        if (task->mode == 1) {
            res = CARDCheckAsync(task->chan, NULL);
            if (res == CARD_RESULT_BUSY) {
                busy = TRUE;
            } else {
                fn_800ACD64(res);
                busy = FALSE;
            }
        } else {
            fn_800ACD64(CARDCheck(task->chan));
            busy = FALSE;
        }
        if (!busy) {
            task->step = 4;
        }
        break;
    case 4:
        fn_800ACD64(CARDGetResultCode(task->chan));
        if (lbl_803C7838.status != CARD_STATUS_BUSY) {
            task->step = 5;
        }
        break;
    case 5:
        if (lbl_803C7838.status == CARD_STATUS_READY) {
            chan = task->chan;
            serial = 0;
            res = CARDGetSerialNo(chan, &serial);
            lbl_803C7838.slots[chan].serial = serial;
            if (res != CARD_RESULT_BUSY) {
                if (lbl_803C7838.slots[task->chan].serial == lbl_802EF2C0[task->chan]) {
                    task->step = 6;
                } else {
                    lbl_803C7838.status = CARD_STATUS_SERIAL_MISMATCH;
                    task->step = 9;
                }
            }
        } else {
            task->step = 6;
        }
        break;
    case 6:
        memset(((Task*)fn_800B0A5C_insertQueue(fn_800A9CF8, 0xFF))->data, 0, sizeof(((Task*)0)->data));
        lbl_803CC1B8->result = 0;
        task->step = 7;
        break;
    case 7:
        switch (task->result) {
        case 1:
            task->step = 8;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 8:
        fn_800ACD64(CARDUnmount(task->chan));
        switch (lbl_803C7838.status) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            task->step = 10;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        task->step = 10;
        break;
    case 10:
        task->parent->result = 1;
        fn_800B0A14_removeQueue(task->parent);
        break;
    }
}
#endif

// .text:0x800A9CF8 size:0x13C
void fn_800A9CF8(void) {
    char* fileName = lbl_802EF330.fileName;
    CardMountTask* task = (CardMountTask*)lbl_803CC1B8;
    CardMountTask* parent = (CardMountTask*)task->parent;
    s32 res;

    switch (task->step) {
    case 0:
        if (parent->mode == 1) {
            res = CARDDeleteAsync(parent->chan, fileName, NULL);
            if (res < 0) {
                fn_800ACD64(res);
                task->step = 3;
            } else {
                task->step++;
            }
        } else {
            res = CARDFastDelete(parent->chan, fileName);
            if (res < 0) {
                fn_800ACD64(res);
                task->step = 3;
            } else {
                task->step += 2;
            }
        }
        break;
    case 1:
        fn_800ACD64(CARDGetResultCode(parent->chan));
        switch (lbl_803CC1B8->result) {
        case CARD_STATUS_BUSY:
            break;
        case CARD_STATUS_READY:
            task->step++;
            break;
        default:
            task->step = 3;
            break;
        }
        break;
    case 2:
        parent->result = 1;
        fn_800B0A14_removeQueue(parent);
        break;
    case 3:
        parent->result = 2;
        fn_800B0A14_removeQueue(parent);
        break;
    }
}

// .text:0x800A9E34 size:0x98
void fn_800A9E34(u8 chan, u8 mode, u64 serial) {
    CardMountTask* task;

    lbl_803C7838.op = 4;
    task = fn_800B0A5C_insertQueue(fn_800A9ECC, 0xFF);
    memset(&task->step, 0, sizeof(Task) - OFFSET_OF(Task, data));
    task->chan = chan;
    task->mode = mode;
    lbl_802EF2C0[chan] = serial;
    lbl_803CC1B8->result = 0;
}

// .text:0x800A9ECC size:0x480
void fn_800A9ECC(void) {
    return;
}

// .text:0x800AA34C size:0x100
void fn_800AA34C(void) {
    return;
}

// .text:0x800AA44C size:0x4E4
void fn_800AA44C(void) {
    return;
}

// .text:0x800AA930 size:0x140
void fn_800AA930(void) {
    return;
}

// .text:0x800AAA70 size:0x474
void fn_800AAA70(void) {
    return;
}

// .text:0x800AAEE4 size:0x108
void fn_800AAEE4(void) {
    return;
}

// .text:0x800AAFEC size:0x488
void fn_800AAFEC(void) {
    return;
}

// .text:0x800AB474 size:0xC0
void fn_800AB474(void) {
    return;
}

// .text:0x800AB534 size:0x5E0
void fn_800AB534(void) {
    return;
}

// .text:0x800ABB14 size:0x4C
u16 fn_800ABB14(u8* data, s32 len) {
    u16 crc = 0xFFFF;
    while (--len >= 0) {
        crc = (crc << 8) ^ lbl_800E7800[(u8)(crc >> 8) ^ *data++];
    }
    return ~crc;
}

// .text:0x800ABB60 size:0x70
// NONMATCHING 96%: removeQueue is called with whatever r3 holds; our call passes &lbl_803C7838 explicitly
#if NONMATCHING
void fn_800ABB60(void) {
    CardSlot* slot = lbl_803C7838.slots;
    s32 chan;

    if (lbl_803C7838.op == 7) {
        fn_800B0A14_removeQueue(slot);
        return;
    }
    for (chan = 0; chan < 2; chan++, slot++) {
        slot->probeResult = CARDProbeEx(chan, &slot->memSize, &slot->sectorSize);
    }
}
#endif

// .text:0x800ABBD0 size:0x374
void fn_800ABBD0(void) {
    return;
}

// .text:0x800ABF44 size:0x5C4
void fn_800ABF44(void) {
    return;
}

// .text:0x800AC508 size:0x764
void fn_800AC508(void) {
    return;
}

// fn_800ACCD4, size:0x14
void fn_800ACCD4(void) {
    lbl_803C7838.op = 7;
}

// fn_800ACC6C, size:0x68
s32 fn_800ACC6C(s32 mode, s32 a, s32 b) {
    s32 base = mode;
    s32 total;
    s32 q;
    switch (mode) {
    case 0:
        base = 0;
        break;
    case 1:
        base = 0x1800;
        break;
    case 2:
        base = 0xE00;
        break;
    }
    total = base + a + b;
    q = total / 0x2000;
    if (total % 0x2000 != 0) {
        q++;
    }
    return q;
}

// .text:0x800ACCE8 size:0x5C
void fn_800ACCE8(void) {
    s32 i;
    memset(&lbl_803C7838, 0, sizeof(CardSystem));
    lbl_803C7838.status = CARD_STATUS_BUSY;
    for (i = 0; i < 2; i++) {
        lbl_803C7838.slots[i].probeResult = CARD_RESULT_BUSY;
    }
    fn_800B0A5C_insertQueue(fn_800ABB60, 0xF0);
}

// .text:0x800ACD44 size:0x20
void fn_800ACD44(void) {
    CARDInit();
}

// .text:0x800ACD64 size:0x1B0
void fn_800ACD64(s32 result) {
    lbl_803C7838.lastResult = result;
    switch (result) {
    case CARD_RESULT_READY:
        lbl_803C7838.status = CARD_STATUS_READY;
        break;
    case CARD_RESULT_BUSY:
        lbl_803C7838.status = CARD_STATUS_BUSY;
        break;
    case CARD_RESULT_NOCARD:
        lbl_803C7838.status = 0;
        break;
    case CARD_RESULT_BROKEN:
        lbl_803C7838.status = 1;
        break;
    case CARD_RESULT_ENCODING:
        lbl_803C7838.status = 2;
        break;
    case CARD_RESULT_IOERROR:
    case CARD_RESULT_FATAL_ERROR:
        lbl_803C7838.status = 3;
        break;
    case CARD_RESULT_WRONGDEVICE:
        lbl_803C7838.status = 4;
        break;
    case CARD_RESULT_NOENT:
        lbl_803C7838.status = 5;
        break;
    case CARD_RESULT_INSSPACE:
        lbl_803C7838.status = 6;
        break;
    case CARD_RESULT_EXIST:
        lbl_803C7838.status = 8;
        break;
    case CARD_RESULT_CANCELED:
    case CARD_RESULT_NOPERM:
    case CARD_RESULT_LIMIT:
        if (lbl_803C7838.op == 1) {
            lbl_803C7838.status = 9;
        } else if (lbl_803C7838.op == 2) {
            lbl_803C7838.status = 10;
        }
        break;
    case CARD_RESULT_NOFILE:
        if (lbl_803C7838.op == 1) {
            lbl_803C7838.status = 9;
        } else if (lbl_803C7838.op == 2) {
            lbl_803C7838.status = 14;
        }
        break;
    case CARD_RESULT_NAMETOOLONG:
        OSPanic(lbl_803CCEE0, 0xEC, lbl_800E7B28);
        break;
    case CARD_RESULT_BAD_SECTOR_SIZE:
        lbl_803C7838.status = 7;
        break;
    }
}

// Simple two-ended arena: blocks are allocated upward from lo or downward from hi.
typedef struct HeapArena {
    /*0x0*/ s32 freeSize;
    /*0x4*/ u8* lo;
    /*0x8*/ u8* hi;
} HeapArena;

// Header placed just before every block handed out by the arena.
typedef struct HeapBlockHeader {
    /*0x0*/ u8* prev; // arena end (lo or hi) before this allocation
    /*0x4*/ s32 size;
} HeapBlockHeader;

extern HeapArena lbl_803C7898;

// .text:0x800ACF14 size:0x20
void fn_800ACF14(void* block) {
    u8* hi = ((HeapBlockHeader*)block)[-1].prev;
    lbl_803C7898.hi = hi;
    lbl_803C7898.freeSize = hi - lbl_803C7898.lo;
}

// .text:0x800ACF34 size:0x44
// NONMATCHING 97%: register allocation (heap pointer in r4 instead of r5, lo/result regs differ)
#if NONMATCHING
void* fn_800ACF34(s32 align, s32 size) {
    HeapArena* heap = &lbl_803C7898;
    u8* lo;
    u8* oldHi;
    u8* block;
    u8* newHi;
    size = (size + 3) & ~3;
    oldHi = heap->hi;
    lo = heap->lo;
    block = (u8*)(-align & (u32)(oldHi - size));
    newHi = block - sizeof(HeapBlockHeader);
    ((HeapBlockHeader*)block)[-1].prev = oldHi;
    ((HeapBlockHeader*)block)[-1].size = oldHi - newHi;
    heap->freeSize = newHi - lo;
    heap->hi = newHi;
    return block;
}
#endif

// .text:0x800ACF78 size:0x38
// NONMATCHING 96%: register allocation (base/total/diff registers rotated)
#if NONMATCHING
void fn_800ACF78(void* block, s32 size) {
    HeapArena* heap;
    u8* base = ((HeapBlockHeader*)block)[-1].prev;
    s32 total;
    heap = &lbl_803C7898;
    total = ((size + 3) & ~3) + ((u8*)block - base);
    heap->lo = base + total;
    heap->freeSize = heap->hi - heap->lo;
    ((HeapBlockHeader*)block)[-1].size = total;
}
#endif

// .text:0x800ACFB0 size:0x20
void fn_800ACFB0(void* block) {
    u8* lo = ((HeapBlockHeader*)block)[-1].prev;
    lbl_803C7898.lo = lo;
    lbl_803C7898.freeSize = lbl_803C7898.hi - lo;
}

// .text:0x800ACFD0 size:0x4C
// NONMATCHING 72%: original computes (align + 7) before adding lo; ours reassociates to (lo + align) + 7
#if NONMATCHING
void* _OSAllocFromHeap(s32 align, s32 size) {
    u8* lo = lbl_803C7898.lo;
    u8* hi = lbl_803C7898.hi;
    u8* block;
    size = (size + 3) & ~3;
    block = (u8*)(-align & (u32)(lo + (align + 7)));
    ((HeapBlockHeader*)block)[-1].prev = lo;
    ((HeapBlockHeader*)block)[-1].size = (block - lo) + size;
    lo = size + block;
    lbl_803C7898.freeSize = hi - lo;
    lbl_803C7898.lo = lo;
    return block;
}
#endif

// .text:0x800AD01C size:0x1C
void fn_800AD01C(void* hi) {
    lbl_803C7898.hi = hi;
    lbl_803C7898.freeSize = (u8*)hi - lbl_803C7898.lo;
}

// .text:0x800AD038 size:0x1C
void fn_800AD038(void* lo) {
    lbl_803C7898.lo = lo;
    lbl_803C7898.freeSize = lbl_803C7898.hi - (u8*)lo;
}

// .text:0x800AD054 size:0x1C
void fn_800AD054(void* lo, void* hi) {
    lbl_803C7898.lo = lo;
    lbl_803C7898.hi = hi;
    lbl_803C7898.freeSize = (u8*)hi - (u8*)lo;
}

// .text:0x800AD070 size:0x420
void fn_800AD070(void) {
    return;
}

// .text:0x800AD490 size:0x70
void fn_800AD490(void) {
    return;
}

// .text:0x800AD500 size:0x1BC
void fn_800AD500(void) {
    return;
}

// .text:0x800AD6BC size:0xC4
void fn_800AD6BC(void) {
    return;
}

// .text:0x800AD780 size:0xB0
void fn_800AD780(void) {
    return;
}

// .text:0x800AD830 size:0xE4
void fn_800AD830(void) {
    return;
}

// .text:0x800AD914 size:0x48
void fn_800AD914(void) {
    return;
}

// .text:0x800AD95C size:0x98
void fn_800AD95C(void) {
    return;
}

// .text:0x800AD9F4 size:0x108
void fn_800AD9F4(void) {
    return;
}

extern u8 lbl_803CC17D;

// fn_800ADAFC, size:0x8
u8 fn_800ADAFC(void) {
    return lbl_803CC17D;
}

// .text:0x800ADB04 size:0xF8
void fn_800ADB04(void) {
    return;
}

// .text:0x800ADBFC size:0x44
void fn_800ADBFC(void) {
    return;
}
