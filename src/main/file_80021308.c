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
extern SoundConfig lbl_800EFBB4;
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
s32 fn_8002158C(u8* state) {
    fn_80021518(0x1E, lbl_800EF808.groups[0]);
    return 0;
}

// .text:0x800215F8 size:0x58
void fn_800215F8(SoundGroupRequest* req) {
    req->task->done = 0;
    fn_80022CB4(&lbl_800EF508[req->group], NULL, 1, 0, fn_80021650, req);
}

// .text:0x80021650 size:0xA8
void fn_80021650(DiskFileEntry* entry, void* dst, void* user) {
    SoundGroupRequest* req = user;
    s32 group = req->group;
    SoundGroupData* data;

    lbl_800EF808.groups[group] = dst;
    data = lbl_800EF808.groups[group];
    relocateSoundGroup(data);
    req->onLoaded(req, data);
    data = lbl_800EF808.groups[group];
    fn_800ACF78(data, (u8*)data->samp - (u8*)data);
    req->task->done = 1;
}

// .text:0x800216F8 size:0x60
void fn_800216F8(u8 group, s32 (*callback)(u8* state)) {
    SoundLoadTask* task = fn_800B0A5C_insertQueue(fn_80021758, 1);
    task->state = 0;
    task->group = group;
    task->callback = callback;
    lbl_803CC1B8->done = 0;
}

// .text:0x80021758 size:0x1FC
void fn_80021758(void) {
    SoundLoadTask* task;
    SoundGroupData* data;
    SoundLoadTask* parent;

    switch ((task = lbl_803CC1B8)->state) {
    case 0:
        if (task->group == 1) {
            if (lbl_800EF808.loadFromAram != 0) {
                lbl_800EF808.groups[task->group] = ARAMTransfer(&lbl_800EF508[task->group], NULL, 3, 0xB44000);
            } else {
                lbl_800EF808.groups[task->group] = ARAMTransfer(&lbl_800EF508[task->group], NULL, 1, 0);
            }
        } else {
            lbl_800EF808.groups[task->group] = ARAMTransfer(&lbl_800EF508[task->group], NULL, 1, 0);
        }
        task->state = 1;
        break;
    case 1:
        if (DVD_STATE_IDLE != 1 || gDataDecompressorValues.ShouldWriteDataFlag != 0) {
            break;
        }
        data = lbl_800EF808.groups[task->group];
        relocateSoundGroup(data);
        task->state = 2;
        task->callbackState = 0;
    case 2:
        if (task->callback(&task->callbackState) == 0) {
            SoundGroupData** slot = &lbl_800EF808.groups[task->group];
            fn_800ACF78(*slot, (u8*)(*slot)->samp - (u8*)*slot);
            parent = task->parent;
            parent->done = 1;
            fn_800B0A14_removeQueue(parent);
        }
        break;
    }
}

// .text:0x80021954 size:0x2C
void fn_80021954(SoundGroupData** slot) {
    SoundGroupData* data = *slot;
    fn_800ACF78(data, (u8*)data->samp - (u8*)data);
}

// .text:0x80021980 size:0x34
void fn_80021980(SoundGroupData* data) {
    relocateSoundGroup(data);
}

// .text:0x800219B4 size:0xEC
void f_initSound(void) {
    u8 mode;
    u8 outputMode;

    *(u32*)lbl_80158740 = 0xABF16D9C;
    lbl_80158740[0] = 'S';
    lbl_80158740[1] = 'N';
    lbl_80158740[2] = 'D';
    lbl_80158740[3] = '@';
    initSound(&lbl_800EFBB4, NULL, lbl_8015C740, 0x21BE0);
    fn_800A8F68();
    fn_800A648C();
    mode = OSGetSoundMode();
    outputMode = 1;
    if (mode != 0) {
        outputMode = mode;
    }
    lbl_800EF808.outputMode = outputMode;
    lbl_800EF808.soundMode = mode;
    sndOutputMode(mode);
    OSSetSoundMode(lbl_800EF808.soundMode != 0);
    sndVolume(lbl_800EF808.volumeA, 0, 0xFD);
    sndVolume(lbl_800EF808.volumeB, 0, 0xFE);
}

// .text:0x80021AA0 size:0x20
void fn_80021AA0(void) {
    fn_800ACD44();
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
void* fn_80021ADC(s32 index, void* dst) {
    if (index < 0 || index >= 0x1D) {
        return NULL;
    }
    if (dst == NULL) {
        dst = _OSAllocFromHeap(0x20, DISK_FILE_SIZE(DISK_FILE_ENTRY(lbl_800EFD38, index + 0x1E6)));
    }
    if (lbl_803716B8.loadedFlags & 8) {
        ARAMTransfer(&lbl_800EFD38[index + 0x1E6], dst, 3, lbl_803716B8.aramAddrs[3][index]);
    } else {
        ARAMTransfer(&lbl_800F71D8.files[index], dst, 0, 0);
    }
    return dst;
}

// .text:0x80021BBC size:0xE8
void* fn_80021BBC(s32 index, void* dst) {
    if (index < 0 || index >= 0x36) {
        return NULL;
    }
    if (dst == NULL) {
        dst = _OSAllocFromHeap(0x20, DISK_FILE_SIZE(DISK_FILE_ENTRY(lbl_800EFD38, index + 0x1B0)));
    }
    if (lbl_803716B8.loadedFlags & 2) {
        ARAMTransfer(&lbl_800EFD38[index + 0x1B0], dst, 3, lbl_803716B8.aramAddrs[2][index]);
    } else {
        ARAMTransfer(&lbl_800F1D78[index * 0x13 + 0xF], dst, 0, 0);
    }
    return dst;
}

// .text:0x80021CA4 size:0x3A8
// NONMATCHING 80%: the original addresses its data tables through one pooled base (lbl_800EFBE8,
// defined in this TU); with extern data we get a separate lis/addi per table.
#if NONMATCHING
void* fn_80021CA4(s32 index, s32 variant, void* dst) {
    s32 base;
    s32 first;
    s32 second;
    s8* pair;

    if (index < 0 || index >= 0x36) {
        return NULL;
    }
    if (variant < 0 || variant >= 6) {
        return NULL;
    }
    base = index * 7;
    pair = lbl_800F71D8.variantFiles[lbl_800F71D8.variantSet[index]][variant];
    first = base + pair[0];
    second = base + pair[1];
    if (dst == NULL) {
        dst = _OSAllocFromHeap(0x20, ((DISK_FILE_SIZE(&lbl_800EFD38[first + 0x36]) + 0x1F) & ~0x1F) +
                                         ((DISK_FILE_SIZE(&lbl_800EFD38[second + 0x36]) + 0x1F) & ~0x1F));
    }
    if (lbl_803716B8.loadedFlags & 2) {
        aramQueuePush(&lbl_800EFD38[first + 0x36], dst, 3, lbl_803716B8.aramAddrs[1][first],
                      (AramQueueCallback)fn_8002244C, (void*)((first << 16) | second));
    } else {
        aramQueuePush(&lbl_800F5D98[variant + index * 6], dst, 0, 0, fn_80022620, NULL);
    }
    lbl_803716B8.keepTask = 1;
    fn_800B0A5C_insertQueue(fn_80022634, 0);
    aramQueueUpdate();
    return dst;
}
#endif

// .text:0x8002204C size:0x400
// NONMATCHING 81%: the original addresses its data tables through one pooled base (lbl_800EFBE8,
// defined in this TU); with extern data we get a separate lis/addi per table.
#if NONMATCHING
void* fn_8002204C(s32 index, void* dst) {
    s8 entry;
    s8 sub;

    if (index < 0 || index >= 0x36) {
        return NULL;
    }
    if (dst == NULL) {
        dst = _OSAllocFromHeap(0x20, DISK_FILE_SIZE(&lbl_800EFD38[index]));
    }
    if (lbl_803716B8.loadedFlags & 1) {
        entry = lbl_800F71D8.aramFiles[index][0];
        sub = lbl_800F71D8.aramFiles[index][1];
        if (sub == -1) {
            aramQueuePush(&lbl_800EFD38[entry], dst, 3, lbl_803716B8.aramAddrs[0][entry], fn_80022620, NULL);
        } else {
            aramQueuePush(&lbl_800EFD38[entry], dst, 3, lbl_803716B8.aramAddrs[0][entry], (AramQueueCallback)fn_8002254C,
                          (void*)(s32)sub);
        }
    } else {
        aramQueuePush(&lbl_800F1D78[index * 0x13], dst, 0, 0, fn_80022620, NULL);
    }
    lbl_803716B8.keepTask = 1;
    fn_800B0A5C_insertQueue(fn_80022634, 0);
    aramQueueUpdate();
    return dst;
}
#endif

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
void fn_8002254C(s32 unused, s32* hdr, s32 index) {
    s32 aramAddr;
    s8 next;
    s32 h;
    hdr = (s32*)((u8*)hdr + *hdr);
    aramAddr = lbl_803716B8.aramAddrs[0][index];
    h = lbl_803716B8.head;
    next = (h + 1) % ARAM_QUEUE_LEN;
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
        e->entry = &lbl_800EFD38[index];
        e->dst = hdr;
        e->mode = 3;
        e->aramAddr = aramAddr;
        e->callback = fn_80022620;
        e->user = NULL;
        lbl_803716B8.head = next;
    }
}

// .text:0x80022634 size:0x16C
void fn_80022634(void) {
    if (aramQueueUpdate() && lbl_803716B8.keepTask == 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// .text:0x800227A0 size:0x44
void fn_800227A0(DiskFileEntry* entry, void* dst, void* user) {
    lbl_803716B8.loadedFlags |= 1;
    lbl_803716B8.loading = 0;
    lbl_803716B8.loadedFlags |= 2;
    lbl_803716B8.loadedFlags |= 4;
    lbl_803716B8.loadedFlags |= 8;
}

// .text:0x800227E4 size:0x1E8
void fn_800227E4(void) {
    s32 j;
    s32 i;
    u32* addrs;
    s32 k;

    lbl_803716B8.aramBase = fn_800A6418(0x4D6600);
    lbl_803716B8.loading = 1;
    k = 0;
    addrs = lbl_8017E320;
    for (i = 0; i < 4; i++) {
        lbl_803716B8.aramAddrs[i] = addrs;
        addrs += lbl_803CB7E0[i];
        for (j = 0; j < lbl_803CB7E0[i]; j++, k++) {
            lbl_803716B8.aramAddrs[i][j] = lbl_803716B8.aramBase + lbl_800EFD38[k].aramOffset;
        }
    }
    aramQueuePush(&lbl_800F1D68, (void*)lbl_803716B8.aramBase, 2, 0, fn_800227A0, NULL);
}

// .text:0x800229CC size:0x58
void fn_800229CC(void) {
    if (lbl_803716B8.stadiumAramPending != 0) {
        fn_800A7568();
    } else if (lbl_803716B8.stadiumAram != 0) {
        lbl_803716B8.stadiumAram = 0;
    } else {
        return;
    }
    fn_800A6304();
}

// .text:0x80022A24 size:0xF0
s32 fn_80022A24(s32 stadium, s32 variant) {
    if (lbl_803716B8.stadiumAramPending != 0) {
        fn_800A7568();
    } else {
        if (DVD_STATE_IDLE != 1) {
            return 0;
        }
        if (lbl_803716B8.stadiumAram != 0) {
            lbl_803716B8.stadiumAramPending = lbl_803716B8.stadiumAram;
        } else {
            lbl_803716B8.stadiumAramPending = fn_800A6354(0xED440);
        }
    }
    lbl_803716B8.stadiumAram = 0;
    ARAMTransfer(&lbl_800EFBE8[variant + stadium * 3], (void*)lbl_803716B8.stadiumAramPending, 2, 0);
    fn_800B0A5C_insertQueue(fn_80022B14, lbl_803CC1B8->priority + 1);
    return 1;
}

// .text:0x80022B14 size:0x54
void fn_80022B14(void) {
    if (DVD_STATE_IDLE == 1) {
        if (lbl_803716B8.stadiumAramPending != 0) {
            lbl_803716B8.stadiumAram = lbl_803716B8.stadiumAramPending;
            lbl_803716B8.stadiumAramPending = 0;
        }
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// .text:0x80022B68 size:0x14C
s32 fn_80022B68(void) {
    return aramQueueUpdate();
}

// .text:0x80022CB4 size:0xA4
s32 fn_80022CB4(DiskFileEntry* entry, void* dst, s32 mode, u32 aramAddr, AramQueueCallback callback, void* user) {
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

// .text:0x80022D58 size:0x54
void fn_80022D58(void) {
    lbl_803716B8.tail = 0;
    lbl_803716B8.head = 0;
    memset(&lbl_803716B8.current, 0, sizeof(AramQueueEntry));
    memset(lbl_803716B8.queue, 0, sizeof(lbl_803716B8.queue));
}
