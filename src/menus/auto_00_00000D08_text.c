#include "menus/auto_00_00000D08_text.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_800EF808[];
extern u8* lbl_803CC1B8[];
extern u8* lbl_803CBBCC[];
extern u8 lbl_2_data_138[];
extern u32 lbl_2_bss_D974[];
extern s16 lbl_2_bss_D958[];
extern u8* lbl_2_bss_D984;
typedef struct {
    u16 a;
    u16 b;
    u16 c;
} SeqEnt;
extern SeqEnt lbl_2_data_128[];
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
    *(u32*)data = *(u32*)data + (u32)data;
    *(u32*)(data + 4) = *(u32*)(data + 4) + (u32)data;
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
s32 fn_2_10FC(void) {
    fn_80021518(0x1F, *(s32*)(lbl_800EF808 + 0xC));
    return 0;
}

// fn_2_1130, size:0x34
void fn_2_1130(s16 value) {
    u8* object = *(u8**)(lbl_803CC1B8[0] + 0xC);
    *(s16*)(object + 0x10) = value;
    ((void (*)(void))fn_800B0A14_removeQueue)();
}
