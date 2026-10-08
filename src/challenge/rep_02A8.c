#include "challenge/rep_02A8.h"


#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"
#include "Dolphin/os.h"

extern s32 lbl_800EF808[];

extern u8 lbl_1_bss_2FDB[];
extern u8 lbl_1_data_1884[];
extern u8 lbl_1_data_1CA0[];
extern u8 lbl_1_data_17A4[];
extern u8 lbl_1_bss_2FD9[];

extern u8 lbl_1_bss_2FDA[];
extern u8* lbl_803CC1B8[];
extern void fn_1_A250(void);

extern u8 lbl_1_bss_2FEE[];
extern void fn_1_9F04(void);
extern void fn_1_A464(void);

extern u8 lbl_1_bss_2FE8[];
extern u8 lbl_1_common_bss_49994[];
extern void fn_1_A95C(void);

extern u8 lbl_1_bss_2FDD[];
extern void fn_1_BFB0(void);
extern void fn_1_BC00(void);
extern u8 lbl_1_bss_2FDE[];

extern s8 lbl_1_common_bss_49A78[];
extern void (*lbl_1_data_1C8C[])(void);
extern void fn_1_C2A4(void);

extern s16 lbl_1_data_1CA4;
extern u32 lbl_1_data_1CA8;

// fn_1_A464, size:0x1D0
void fn_1_A464(void) {
    u16 pressed = *(u16*)((u8*)&lbl_803C77B8 + 2);
    u16 held = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (pressed & 0x100) {
        fn_1_BEF4((s16)lbl_1_data_1CA8);
        lbl_1_data_1CA8 = fn_1_BF34(lbl_1_data_1CA4);
    } else if (pressed & 0x1200) {
        fn_1_A718();
        fn_800ACFB0((void*)lbl_800EF808[4]);
        *(void (**)(void))lbl_803CC1B8[0] = fn_1_A348;
    } else if (held & 1) {
        if (held & 0x800) {
            lbl_1_data_1CA4 -= 10;
        } else {
            lbl_1_data_1CA4--;
        }
        if (lbl_1_data_1CA4 < 0x1AD) {
            lbl_1_data_1CA4 = 0x1B6;
        }
    } else if (held & 2) {
        s16 next = lbl_1_data_1CA4 + 1;
        if (held & 0x800) {
            next = lbl_1_data_1CA4 + 10;
        }
        lbl_1_data_1CA4 = next;
        if (next > 0x1B6) {
            lbl_1_data_1CA4 = 0x151;
        }
    }
}

// fn_1_A348, size:0x11C
void fn_1_A348(void) {
    u16 held = *(u16*)((u8*)&lbl_803C77B8 + 4);
    u16 pressed = *(u16*)((u8*)&lbl_803C77B8 + 2);
    if (held & 8) {
        lbl_1_common_bss_49A78[0] = (lbl_1_common_bss_49A78[0] + 4) % 5;
        return;
    }
    if (held & 4) {
        lbl_1_common_bss_49A78[0] = (lbl_1_common_bss_49A78[0] + 6) % 5;
        return;
    }
    if (pressed & 0x100) {
        *(void (**)(void))lbl_803CC1B8[0] = lbl_1_data_1C8C[lbl_1_common_bss_49A78[0]];
        lbl_1_common_bss_49A78[1] = 0;
        return;
    }
    if (pressed & 0x1200) {
        lbl_1_bss_2FDA[0] = 0;
        lbl_1_bss_2FD9[0] = 0;
        *(void (**)(void))lbl_803CC1B8[0] = fn_1_C2A4;
    }
}

// fn_1_C188, size:0x11C
void fn_1_C188(void) {
    u8* queue = lbl_803CC1B8[0];
    switch ((s32)lbl_1_bss_2FDD[0]) {
    case 0: {
        s32 option;
        u8* child;
        *(s16*)(queue + 0x10) = 0;
        option = lbl_1_bss_2FD9[0] + 5;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child[0x18] = 0;
        child[0x19] = option;
        *(s32 (**)(void))(child + 0x14) = fn_1_A908;
        *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
        lbl_1_bss_2FDD[0]++;
        break;
    }
    case 1:
        if (*(s16*)(queue + 0x10) != 0) {
            if (lbl_1_bss_2FD9[0] != 17) {
                lbl_1_bss_2FD9[0]++;
                lbl_1_bss_2FDD[0] = 0;
            } else {
                *(s16*)(queue + 0x10) = 0;
                lbl_1_bss_2FDD[0]++;
            }
        }
        break;
    case 2:
        *(void (**)(void))queue = fn_1_BFB0;
        lbl_1_bss_2FDD[0] = 0;
        break;
    }
}

// fn_1_B4A4, size:0x114
void fn_1_B4A4(void) {
    u8* queue = lbl_803CC1B8[0];
    switch ((s32)lbl_1_bss_2FE8[0]) {
    case 0: {
        u8* child;
        *(s16*)(queue + 0x10) = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child[0x18] = 0;
        child[0x19] = 0x2A;
        *(s32 (**)(void))(child + 0x14) = fn_1_A7E4;
        *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
        lbl_1_bss_2FE8[0]++;
        break;
    }
    case 1:
        if (*(s16*)(queue + 0x10) != 0) {
            ((u8*)lbl_800EF808)[0x396] = 2;
            sndOutputMode(SND_OUTPUTMODE_SURROUND);
            *(s16*)(queue + 0x10) = 0;
            lbl_1_bss_2FE8[0]++;
        }
        break;
    case 2:
        *(void (**)(void))queue = fn_1_A95C;
        lbl_1_common_bss_49994[0xE0] = 0;
        lbl_1_bss_2FE8[0] = 0;
        break;
    }
}

// fn_1_A634, size:0xE0
void fn_1_A634(void) {
    u8* queue = lbl_803CC1B8[0];
    switch ((s32)lbl_1_bss_2FEE[0]) {
    case 0: {
        u8* child;
        *(s16*)(queue + 0x10) = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child[0x18] = 0;
        child[0x19] = 3;
        *(s32 (**)(void))(child + 0x14) = fn_1_A838;
        *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
        lbl_1_bss_2FEE[0]++;
        break;
    }
    case 1:
        if (*(s16*)(queue + 0x10) != 0) {
            *(s16*)(queue + 0x10) = 0;
            lbl_1_bss_2FEE[0]++;
        }
        break;
    case 2:
        *(void (**)(void))queue = fn_1_A464;
        lbl_1_bss_2FEE[0] = 0;
        break;
    }
}

extern const char lbl_1_rodata_5C8[];
extern const char lbl_1_rodata_5C0[];
extern const char lbl_1_rodata_5D0[];

// fn_1_BF34, size:0x7C
static inline const char* ReverbStatusName(u32 success) {
    const char* status = lbl_1_rodata_5C8;
    if (success != 0) {
        status = lbl_1_rodata_5C0;
    }
    return status;
}

u32 fn_1_BF34(u32 effect) {
    u32 voice = sndFXStartEx(effect, 127, 63, 0);
    const char* status = ReverbStatusName(sndFXCtrl(voice, 0x5B, fn_800211F0()));
    OSReport(lbl_1_rodata_5D0, status);
    return voice;
}

// fn_1_A2E4, size:0x64
void fn_1_A2E4(void) {
    switch ((s32)lbl_1_bss_2FDA[0]) {
    case 0:
        lbl_1_bss_2FDA[0]++;
        break;
    case 1:
        lbl_1_bss_2FDA[0]++;
        break;
    case 2:
        *(void (**)(void))lbl_803CC1B8[0] = fn_1_A250;
        break;
    }
}

// fn_1_A718, size:0x64
s32 fn_1_A718(void) {
    s16 count = *(s8*)((u8*)lbl_800EF808 + 0x390);
    s8 remaining = count - 1;
    while (remaining > 0) {
        if (fn_800214D0() == 0) {
            return 0;
        }
        remaining--;
    }
    return 1;
}

static inline s32 SoundOptionValue(s32 index) {
    return lbl_800EF808[index + 1];
}

// fn_1_A908, size:0x54
s32 fn_1_A908(void) {
    s32 index = lbl_1_bss_2FD9[0];
    fn_80021518(lbl_1_data_17A4[index], SoundOptionValue(index + 5));
    return 0;
}

// fn_1_A8B4, size:0x54
s32 fn_1_A8B4(void) {
    s32 index = lbl_1_data_1CA0[0];
    fn_80021518(lbl_1_data_17A4[index], SoundOptionValue(index + 5));
    return 0;
}

// fn_1_A7E4, size:0x54
s32 fn_1_A7E4(void) {
    s32 index = lbl_1_bss_2FDB[0];
    fn_80021518(lbl_1_data_1884[index], SoundOptionValue(index + 0x2A));
    return 0;
}

// .text:0xA714 size:0x4
void fn_1_A714(void) {
}

// fn_1_A77C, size:0x34
s32 fn_1_A77C(void) {
    fn_80021518(0x31, lbl_800EF808[0x2A]);
    return 0;
}

// fn_1_A7B0, size:0x34
s32 fn_1_A7B0(void) {
    fn_80021518(0x33, lbl_800EF808[0x32]);
    return 0;
}

// fn_1_A880, size:0x34
s32 fn_1_A880(void) {
    fn_80021518(0x1C, lbl_800EF808[0x2]);
    return 0;
}

// fn_1_A838, size:0x48
s32 fn_1_A838(void) {
    fn_80021518(0x1C, lbl_800EF808[4]);
    fn_80021518(0x36, lbl_800EF808[4]);
    return 0;
}

// fn_1_BEF4, size:0x40
void fn_1_BEF4(s16 voice) {
    sndFXKeyOff(voice);
    sndFXCtrl(voice, 7, 0);
}

// fn_1_BDD8, size:0x11C
void fn_1_BDD8(void) {
    u8* queue = lbl_803CC1B8[0];
    switch ((s32)lbl_1_bss_2FDE[0]) {
    case 0: {
        s32 option;
        u8* child;
        *(s16*)(queue + 0x10) = 0;
        option = lbl_1_data_1CA0[0] + 5;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child[0x18] = 0;
        child[0x19] = option;
        *(s32 (**)(void))(child + 0x14) = fn_1_A8B4;
        *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
        lbl_1_bss_2FDE[0]++;
        break;
    }
    case 1:
        if (*(s16*)(queue + 0x10) != 0) {
            if (lbl_1_data_1CA0[0] != 31) {
                lbl_1_data_1CA0[0]++;
                lbl_1_bss_2FDE[0] = 0;
            } else {
                *(s16*)(queue + 0x10) = 0;
                lbl_1_bss_2FDE[0]++;
            }
        }
        break;
    case 2:
        *(void (**)(void))queue = fn_1_BC00;
        lbl_1_bss_2FDE[0] = 0;
        break;
    }
}
