#include "main/file_800A7C08.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"
#include "Dolphin/vi.h"
#include "Dolphin/card.h"
#include "Dolphin/dvd.h"
#include "Dolphin/ai.h"

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
    return 0;
}

// .text:0x800A86B4 size:0x1B0
void fn_800A86B4(s32 cmd) {
    return;
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
    return 0;
}

// .text:0x800A8E30 size:0x138
s32 fn_800A8E30(void* file, StreamTrack* track, u32 flags, void (*callback)(u32 event)) {
    return 0;
}

// .text:0x800A8F68 size:0x74
void fn_800A8F68(void) {
    return;
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

// .text:0x800A94C4 size:0x5C
void fn_800A94C4(void) {
    return;
}

// .text:0x800A9520 size:0x2B0
void fn_800A9520(void) {
    return;
}

extern u8 lbl_80110080[];

extern u8 lbl_803C77B8[];

// fn_800A97EC, size:0x50
void fn_800A97EC(s32 index, u32 enable, u8 type) {
    u8* entry = lbl_803C77B8 + index * 0x20;
    if (!(lbl_80110080[6] & (1 << index))) {
        entry[0xA] = enable;
        entry[0xB] = 0;
        if (enable != 0) {
            entry[0xB] = type;
        }
        entry[9] = 1;
    }
}

// fn_800A97D0, size:0x1C
void fn_800A97D0(u8 value, s32 index) {
    lbl_80110080[7] = value;
    lbl_80110080[8] = -index;
    lbl_80110080[9] = index;
}

// .text:0x800A983C size:0x28
void fn_800A983C(void) {
    return;
}

// .text:0x800A9864 size:0x98
void fn_800A9864(void) {
    return;
}

// .text:0x800A98FC size:0x3FC
void fn_800A98FC(void) {
    return;
}

// .text:0x800A9CF8 size:0x13C
void fn_800A9CF8(void) {
    return;
}

// .text:0x800A9E34 size:0x98
void fn_800A9E34(void) {
    return;
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
void fn_800ABB14(void) {
    return;
}

// .text:0x800ABB60 size:0x70
void fn_800ABB60(void) {
    return;
}

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

extern u8 lbl_803C7838[];

// fn_800ACCD4, size:0x14
void fn_800ACCD4(void) {
    *(u8*)(lbl_803C7838 + 0x55) = 0x7;
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
    return;
}

// .text:0x800ACD44 size:0x20
void fn_800ACD44(void) {
    return;
}

// .text:0x800ACD64 size:0x1B0
void fn_800ACD64(void) {
    return;
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
