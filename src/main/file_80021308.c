#include "main/file_80021308.h"
#include "main/file_800B0724.h"

// Sound heap, disc/ARAM loader queue and sound group management.

extern SoundManager lbl_800EF808;
extern AramLoader lbl_803716B8;
extern DiskFileEntry lbl_800EF508[];
extern DiskFileEntry lbl_800EFD38[];
extern DiskFileEntry lbl_800EFBE8[];
extern DiskFileEntry lbl_800F1D68;
extern DiskFileEntry lbl_800F1D78[];
extern DiskFileEntry lbl_800F5D98[];
extern SoundFileTables lbl_800F71D8;
extern u8 lbl_800EFBB4[];
extern u8 lbl_80118740[];
extern u8 lbl_80158740[];
extern u8 lbl_8015C740[];
extern u32 lbl_8017E320[];
extern u16 lbl_803CB7E0[4];
extern SND_HOOKS lbl_803CB7D8;
extern u8* lbl_803CBC40;
extern SoundLoadTask* lbl_803CC1B8;
extern f32 lbl_803CC548;
extern f32 lbl_803CC54C;
extern f32 lbl_803CC550;
extern f32 lbl_803CC554;
extern f32 lbl_803CC558;
extern f32 lbl_803CC55C;
extern u8 lbl_803C6CF8[];           // TODO type: DVD/ARAM transfer state
extern u8 gDataDecompressorValues[]; // TODO type

// TODO: these belong in their own units' headers.
void* ARAMTransfer(DiskFileEntry* entry, void* dst, s32 mode, u32 aramAddr);
void* _OSAllocFromHeap(u32 align, u32 size);
void fn_800ACF78(void* block, u32 newSize);
void fn_800ACFB0(void* block);
void fn_800ACD44(void);
u32 fn_800A6354(u32 size);
u32 fn_800A6418(u32 size);
void fn_800A6304(void);
void fn_800A648C(void);
void fn_800A7568(void);
void fn_800A8F68(void);
void initSound(void* config, void* aiStack, void* buffer, u32 bufferSize);
u32 sndPushGroup(void* prj_data, u16 gid, void* samples, void* sdir, void* pool);
u32 sndPopGroup(void);
s32 sndSetAuxProcessingCallbacks(u8 studio, SND_AUX_CALLBACK auxA, void* userA, u8 midiA, u16 seqIDA, SND_AUX_CALLBACK auxB,
                                 void* userB, u8 midiB, u16 seqIDB);
u32 OSGetSoundMode(void);
void OSSetSoundMode(u32 mode);
void* memset(void* dst, int c, u32 n);

#define DVD_STATE_IDLE (*(s8*)(lbl_803C6CF8 + 0x715)) // TODO type

// The on-disc group data stores its pointers as offsets from the start of the block.
// TODO port: these 32-bit offset fields can't hold 64-bit pointers.
static inline void relocateSoundGroup(SoundGroupData* data) {
    data->proj = (u8*)data->proj + (u32)data;
    data->sdir = (u8*)data->sdir + (u32)data;
    data->pool = (u8*)data->pool + (u32)data;
    data->samp = (u8*)data->samp + (u32)data;
}

// Advance the ARAM/disc transfer queue; returns 1 once it is empty (inlined into callers).
static inline s32 aramQueueUpdate(void) {
    AramQueueEntry* e;

    if (lbl_803716B8.busy == 0) {
        return 1;
    }
    if (DVD_STATE_IDLE != 1) {
        return 0;
    }
    if (lbl_803716B8.current.callback != NULL) {
        lbl_803716B8.current.callback(lbl_803716B8.current.entry, lbl_803716B8.current.dst, lbl_803716B8.current.user);
    }
    if (lbl_803716B8.tail != lbl_803716B8.head) {
        e = &lbl_803716B8.queue[lbl_803716B8.tail];
        e->dst = ARAMTransfer(e->entry, e->dst, e->mode, e->aramAddr);
        lbl_803716B8.current = *e;
        lbl_803716B8.tail = (lbl_803716B8.tail + 1) % ARAM_QUEUE_LEN;
    } else {
        lbl_803716B8.current.callback = NULL;
        lbl_803716B8.busy = 0;
        return 1;
    }
    return 0;
}

// Add a transfer to the ARAM/disc queue (inlined into callers).
static inline s32 aramQueuePush(DiskFileEntry* entry, void* dst, s32 mode, u32 aramAddr, AramQueueCallback callback, void* user) {
    AramQueueEntry* e;
    s8 next = (lbl_803716B8.head + 1) % ARAM_QUEUE_LEN;

    if (next == lbl_803716B8.tail || (dst == NULL && callback == NULL)) {
        return 0;
    }
    lbl_803716B8.busy = 1;
    e = &lbl_803716B8.queue[lbl_803716B8.head];
    e->entry = entry;
    e->dst = dst;
    e->mode = mode;
    e->aramAddr = aramAddr;
    e->callback = callback;
    e->user = user;
    lbl_803716B8.head = next;
    return 1;
}

// .text:0x80021308 size:0xEC
void fn_80021308(void) {
    lbl_803CBC40 = lbl_80118740;
    sndSetHooks(&lbl_803CB7D8);
    lbl_800EF808.reverb.tempDisableFX = 0;
    lbl_800EF808.reverb.time = lbl_803CC548;
    lbl_800EF808.reverb.preDelay = lbl_803CC54C;
    lbl_800EF808.reverb.damping = lbl_803CC550;
    lbl_800EF808.reverb.coloration = lbl_803CC554;
    lbl_800EF808.reverb.crosstalk = lbl_803CC558;
    lbl_800EF808.reverb.mix = lbl_803CC55C;
    sndAuxCallbackPrepareReverbHI(&lbl_800EF808.reverb);
    lbl_800EF808.chorus.baseDelay = 5;
    lbl_800EF808.chorus.variation = 0;
    lbl_800EF808.chorus.period = 500;
    sndAuxCallbackPrepareChorus(&lbl_800EF808.chorus);
    sndSetAuxProcessingCallbacks(0, sndAuxCallbackReverbHI, &lbl_800EF808.reverb, 0xFF, 0, sndAuxCallbackChorus, &lbl_800EF808.chorus, 0xFF, 0);
}

// fn_800213F4, size:0x4
void fn_800213F4(void* p) {
}

// fn_800213F8, size:0x18
void* fn_800213F8(u32 size) {
    void* result = lbl_803CBC40;
    lbl_803CBC40 += (size + 31) & ~31;
    return result;
}

// .text:0x80021410 size:0x8C
s32 fn_80021410(void) {
    s8 i;

    for (i = (s8)lbl_800EF808.groupStackCount - 1; i > 0; i--) {
        s32 ok;
        if (sndPopGroup() == 0) {
            ok = 0;
        } else {
            lbl_800EF808.groupStackCount--;
            ok = 1;
        }
        if (!ok) {
            return 0;
        }
    }
    return 1;
}

// .text:0x8002149C size:0x34
void fn_8002149C(s32 group) {
    fn_800ACFB0(lbl_800EF808.groups[group]);
}

// .text:0x800214D0 size:0x48
s32 fn_800214D0(void) {
    if (sndPopGroup() == 0) {
        return 0;
    }
    lbl_800EF808.groupStackCount--;
    return 1;
}

// .text:0x80021518 size:0x74
s32 fn_80021518(u16 gid, SoundGroupData* data) {
    if (sndPushGroup(data->proj, gid, data->samp, data->sdir, data->pool) == 0) {
        return 0;
    }
    lbl_800EF808.groupStack[lbl_800EF808.groupStackCount++] = gid;
    return 1;
}

// .text:0x8002158C size:0x6C
void fn_8002158C(void) {
    return;
}

// .text:0x800215F8 size:0x58
void fn_800215F8(void) {
    return;
}

// .text:0x80021650 size:0xA8
void fn_80021650(void) {
    return;
}

// .text:0x800216F8 size:0x60
void fn_800216F8(void) {
    return;
}

// .text:0x80021758 size:0x1FC
void fn_80021758(void) {
    return;
}

// .text:0x80021954 size:0x2C
void fn_80021954(void) {
    return;
}

// .text:0x80021980 size:0x34
void fn_80021980(void) {
    return;
}

// .text:0x800219B4 size:0xEC
void f_initSound(void) {
    return;
}

// .text:0x80021AA0 size:0x20
void fn_80021AA0(void) {
    return;
}

// fn_80021AC0, size:0x4
void fn_80021AC0(void) {
}

// fn_80021AC4, size:0x4
void fn_80021AC4(void) {
}

// fn_80021AC8, size:0x14
void fn_80021AC8(void) {
    lbl_803716B8.unk55C = 0;
}

// .text:0x80021ADC size:0xE0
void fn_80021ADC(void) {
    return;
}

// .text:0x80021BBC size:0xE8
void fn_80021BBC(void) {
    return;
}

// .text:0x80021CA4 size:0x3A8
void fn_80021CA4(void) {
    return;
}

// .text:0x8002204C size:0x400
void fn_8002204C(void) {
    return;
}

// fn_80022620, size:0x14
void fn_80022620(DiskFileEntry* entry, void* dst, void* user) {
    lbl_803716B8.keepTask = 0;
}

// fn_8002244C, size:0x100
void fn_8002244C(s32 unused, s32* hdr, s32 arg) {
    s32 v;
    s8 next;
    s32 h;
    s32 len = DISK_FILE_SIZE(DISK_FILE_ENTRY(lbl_800EFD38, (arg >> 16) + 0x36));
    len = (len + 0x1F) & ~0x1F;
    hdr[3] = len;
    hdr = (s32*)(len + (u32)hdr); // TODO port: pointer through u32 (needed to match)
    v = *(s32*)((u8*)lbl_803716B8.aramAddrs[1] + (u16)arg * 4);
    h = lbl_803716B8.head;
    next = (h + 1) % 18;
    if (next == lbl_803716B8.tail) {
        return;
    }
    if (hdr == NULL && fn_80022620 == NULL) {
        return;
    }
    {
        AramQueueEntry* e;
        lbl_803716B8.busy = 1;
        e = &lbl_803716B8.queue[lbl_803716B8.head];
        e->entry = DISK_FILE_ENTRY(lbl_800EFD38, (u16)arg + 0x36);
        e->dst = hdr;
        e->mode = 3;
        e->aramAddr = v;
        e->callback = fn_80022620;
        e->user = NULL;
        lbl_803716B8.head = next;
    }
}

// .text:0x8002254C size:0xD4
void fn_8002254C(void) {
    return;
}

// .text:0x80022634 size:0x16C
void fn_80022634(void) {
    return;
}

// .text:0x800227A0 size:0x44
void fn_800227A0(void) {
    return;
}

// .text:0x800227E4 size:0x1E8
void fn_800227E4(void) {
    return;
}

// .text:0x800229CC size:0x58
void fn_800229CC(void) {
    return;
}

// .text:0x80022A24 size:0xF0
void fn_80022A24(void) {
    return;
}

// .text:0x80022B14 size:0x54
void fn_80022B14(void) {
    return;
}

// .text:0x80022B68 size:0x14C
void fn_80022B68(void) {
    return;
}

// .text:0x80022CB4 size:0xA4
void fn_80022CB4(void) {
    return;
}

// .text:0x80022D58 size:0x54
void fn_80022D58(void) {
    return;
}
