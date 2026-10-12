// NOTE: this code (0xD08-0x121C) is the tail of rep_01A0's translation unit
// (rep_01A0 compiles in reverse source order; the merged file defines these
// functions before fn_2_C74, from fn_2_11D8 down to fn_2_D08). Every function
// matches in the merged unit except fn_2_E84, so the merge waits until fn_2_E84
// matches: rep_01A0 is linked and would lose fn_2_E84's code.
#include "menus/auto_00_00000D08_text.h"
#include "menus/rep_01A0.h"
#include "static/UnknownHomes_Static.h"
#include "menus/menu_work.h"
#include "main/file_80021308.h"

extern SoundManager lbl_800EF808;
extern MenuTask* lbl_803CC1B8[];
extern MenuFlags* lbl_803CBBCC[];
extern u32 lbl_2_bss_D974[];
extern s16 lbl_2_bss_D958[];
extern u8* lbl_2_bss_D984;
extern u32 sndSeqGetValid(u32);
extern void sndSeqStop(u32);
extern void sndSeqVolume(u8, u16, u32, u8);
extern u32 sndSeqPlayEx(u16, u16, void*, void*, u8);

// fn_2_D08, size:0x80
void fn_2_D08(u16 ch, u16 time, u8 mode) {
    if (lbl_2_bss_D974[ch] != -1 && sndSeqGetValid(lbl_2_bss_D974[ch])) {
        sndSeqVolume(0, time, lbl_2_bss_D974[ch], mode);
    }
}

// fn_2_D88, size:0xFC
void fn_2_D88(u16 ch, s16 id) {
    SeqEnt* entry;
    s32 c;
    c = ch;
    if (id == lbl_2_bss_D958[c] && sndSeqGetValid(lbl_2_bss_D974[c])) {
        return;
    }
    entry = &lbl_2_data_128[id];
    if (lbl_2_bss_D974[c] != -1) {
        if (sndSeqGetValid(lbl_2_bss_D974[c])) {
            sndSeqVolume(0, 0, lbl_2_bss_D974[c], 1);
            sndSeqStop(lbl_2_bss_D974[c]);
        }
        lbl_2_bss_D974[c] = -1;
        lbl_2_bss_D958[c] = -1;
    }
    lbl_2_bss_D974[c] = sndSeqPlayEx(entry->a, entry->b, U32_TO_PTR(((u32*)lbl_2_bss_D984)[entry->c]), 0, 0);
    lbl_2_bss_D958[c] = id;
}

// NONMATCHING 96%: lis of lbl_2_data_128 scheduled after the clrlslwi instead of before (same instructions)
#if NONMATCHING
// fn_2_E84, size:0xE0
// Like fn_2_D88 but always restarts the sequence.
void fn_2_E84(u16 ch, s16 id) {
    SeqEnt* entry = &lbl_2_data_128[id];

    if (lbl_2_bss_D974[ch] != -1) {
        if (sndSeqGetValid(lbl_2_bss_D974[ch])) {
            sndSeqVolume(0, 0, lbl_2_bss_D974[ch], 1);
            sndSeqStop(lbl_2_bss_D974[ch]);
        }
        lbl_2_bss_D974[ch] = -1;
        lbl_2_bss_D958[ch] = -1;
    }
    lbl_2_bss_D974[ch] = sndSeqPlayEx(entry->a, entry->b, U32_TO_PTR(((u32*)lbl_2_bss_D984)[entry->c]), 0, 0);
    lbl_2_bss_D958[ch] = id;
}
#endif

// fn_2_F64, size:0xB4
void fn_2_F64(void) {
    u16 i;
    for (i = 0; i < 4; i++) {
        fn_2_1018(i);
    }
}

// fn_2_1018, size:0x94
void fn_2_1018(u16 ch) {
    if (lbl_2_bss_D974[ch] != -1) {
        if (sndSeqGetValid(lbl_2_bss_D974[ch])) {
            sndSeqVolume(0, 0, lbl_2_bss_D974[ch], 1);
            sndSeqStop(lbl_2_bss_D974[ch]);
        }
        lbl_2_bss_D974[ch] = -1;
        lbl_2_bss_D958[ch] = -1;
    }
}

// fn_2_10AC, size:0x50
void fn_2_10AC(u8* data) {
    // Relocates the file's two leading 32-bit song offsets in place.
#ifdef TARGET_PC
    port_swap_offset_table(data, 2);
#endif
    *(u32*)data = *(u32*)data + PTR_TO_U32(data);
    *(u32*)(data + 4) = *(u32*)(data + 4) + PTR_TO_U32(data);
    lbl_2_bss_D974[0] = -1;
    lbl_2_bss_D958[0] = -1;
    lbl_2_bss_D974[1] = -1;
    lbl_2_bss_D958[1] = -1;
    lbl_2_bss_D974[2] = -1;
    lbl_2_bss_D958[2] = -1;
    lbl_2_bss_D974[3] = -1;
    lbl_2_bss_D958[3] = -1;
    lbl_2_bss_D984 = data;
}

// fn_2_10FC, size:0x34
s32 fn_2_10FC(u8* state) {
    fn_80021518(0x1F, lbl_800EF808.groups[2]);
    return 0;
}

// fn_2_1130, size:0x34
void fn_2_1130(s16 value) {
    MenuTask* object = lbl_803CC1B8[0]->parent;
    object->_10 = value;
    REMOVE_QUEUE_NOARG();
}

// fn_2_1164, size:0x38
void fn_2_1164(void) {
    MenuTask* object = lbl_803CC1B8[0]->parent;
    object->_10 = 1;
    fn_800B0A14_removeQueue(object);
}

// fn_2_119C, size:0x4
void fn_2_119C(void) {
}

// fn_2_11A0, size:0x38
void fn_2_11A0(u16 value) {
    lbl_803CBBCC[0]->prevScene = lbl_803CBBCC[0]->scene;
    lbl_803CBBCC[0]->prevStep = lbl_803CBBCC[0]->step;
    lbl_803CBBCC[0]->scene = value;
    lbl_803CBBCC[0]->step = 0;
}

// fn_2_11D8, size:0x44
void fn_2_11D8(void) {
    lbl_2_data_138[lbl_803CBBCC[0]->scene]();
}
