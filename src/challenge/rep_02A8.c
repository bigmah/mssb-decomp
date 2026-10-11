#include "challenge/rep_02A8.h"
#include "challenge/rep_0010.h"


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
extern void fn_1_A250(void);

extern u8 lbl_1_bss_2FEE[];
extern void fn_1_9F04(void);
extern void fn_1_A464(void);

extern u8 lbl_1_bss_2FE8[];
extern ChSound3DTest lbl_1_common_bss_49994;
extern ChSoundEmitterParams lbl_1_common_bss_49980;
extern ChSoundListenerParams lbl_1_common_bss_49970;
extern void fn_1_A95C(void);

extern u8 lbl_1_bss_2FDD[];
extern void fn_1_BFB0(void);
extern void fn_1_BC00(void);
extern u8 lbl_1_bss_2FDE[];

extern s8 lbl_1_common_bss_49A78[];
extern void (*lbl_1_data_1C8C[])(void);
extern void fn_1_C2A4(void);

extern s16 lbl_1_data_1CA4;
extern s16 lbl_1_bss_3056[];
extern u16 lbl_1_data_17C4[];
extern s16 lbl_1_bss_3054[];
extern u16 lbl_1_data_17E8[];
extern u32 lbl_1_data_1CA8;
extern u8 lbl_1_bss_2FDF;

// TODO type: these are all part of the file's .bss / .data pools (lbl_1_bss_2FD8, lbl_1_data_FC0).
extern u8 lbl_1_bss_2FE0;  // sound test page: 0 = test active, 1 = paused (Y/X)
extern u8 lbl_1_bss_2FE1;  // sound test row 0..3
extern s16 lbl_1_bss_2FE2; // row 1 index into lbl_1_data_188C, 0..47
extern s16 lbl_1_bss_2FE4; // row 2 index into lbl_1_data_18EC, 0..23
extern s16 lbl_1_bss_2FE6; // row 3 argument for fn_80062890, 0..68
extern u32 lbl_1_bss_3044; // fn_80062890 result
extern u32 lbl_1_bss_3048; // row 2 voice
extern u32 lbl_1_bss_304C; // row 1 voice
extern u32 lbl_1_bss_3050; // row 0 voice
extern s16 lbl_1_data_1CA2; // row 0 sound effect id, 0x151..0x1B6
extern u16 lbl_1_data_188C[48];
extern u16 lbl_1_data_18EC[24];
extern s16 lbl_1_bss_2FEA; // 3D test: index into lbl_1_data_188C, 0..2
extern s8 lbl_1_bss_2FEC;  // 3D test: listener row 0..12
extern s8 lbl_1_bss_2FED;  // 3D test: emitter row 0..6
extern f32 lbl_1_bss_2FF0[7];  // 3D test: emitter values shown on screen
extern f32 lbl_1_bss_300C[13]; // 3D test: listener values shown on screen

// MusyX 3D API (src/musyx/snd3d.c); the update calls take a trailing room argument.
extern u32 sndAddEmitter(SND_EMITTER* em, SND_FVECTOR* pos, SND_FVECTOR* dir, f32 maxDis, f32 comp, u32 flags,
                         u16 fxid, u8 maxVol, u8 minVol, SND_ROOM* room);
extern u32 sndRemoveEmitter(SND_EMITTER* em);
extern u32 sndUpdateEmitter(SND_EMITTER* em, SND_FVECTOR* pos, SND_FVECTOR* dir, u8 maxVol, SND_ROOM* room);
extern u32 sndAddListener(SND_LISTENER* li, SND_FVECTOR* pos, SND_FVECTOR* dir, SND_FVECTOR* heading,
                          SND_FVECTOR* up, f32 frontSur, f32 backSur, f32 soundSpeed, u32 flags, u8 vol,
                          f32* unk);
extern u32 sndRemoveListener(SND_LISTENER* li);
extern u32 sndUpdateListener(SND_LISTENER* li, SND_FVECTOR* pos, SND_FVECTOR* dir, SND_FVECTOR* heading,
                             SND_FVECTOR* up, u8 vol, SND_ROOM* room);

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
        *(void (**)(void))((u8*)lbl_803CC1B8) = fn_1_A348;
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
        *(void (**)(void))((u8*)lbl_803CC1B8) = lbl_1_data_1C8C[lbl_1_common_bss_49A78[0]];
        lbl_1_common_bss_49A78[1] = 0;
        return;
    }
    if (pressed & 0x1200) {
        lbl_1_bss_2FDA[0] = 0;
        lbl_1_bss_2FD9[0] = 0;
        *(void (**)(void))((u8*)lbl_803CC1B8) = fn_1_C2A4;
    }
}

// fn_1_C188, size:0x11C
void fn_1_C188(void) {
    u8* queue = ((u8*)lbl_803CC1B8);
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
        *(s16*)(((u8*)lbl_803CC1B8) + 0x10) = 0;
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
    u8* queue = ((u8*)lbl_803CC1B8);
    switch ((s32)lbl_1_bss_2FE8[0]) {
    case 0: {
        u8* child;
        *(s16*)(queue + 0x10) = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child[0x18] = 0;
        child[0x19] = 0x2A;
        *(s32 (**)(void))(child + 0x14) = fn_1_A7E4;
        *(s16*)(((u8*)lbl_803CC1B8) + 0x10) = 0;
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
        lbl_1_common_bss_49994.active = 0;
        lbl_1_bss_2FE8[0] = 0;
        break;
    }
}

// fn_1_A634, size:0xE0
void fn_1_A634(void) {
    u8* queue = ((u8*)lbl_803CC1B8);
    switch ((s32)lbl_1_bss_2FEE[0]) {
    case 0: {
        u8* child;
        *(s16*)(queue + 0x10) = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child[0x18] = 0;
        child[0x19] = 3;
        *(s32 (**)(void))(child + 0x14) = fn_1_A838;
        *(s16*)(((u8*)lbl_803CC1B8) + 0x10) = 0;
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
        *(void (**)(void))((u8*)lbl_803CC1B8) = fn_1_A250;
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
    u8* queue = ((u8*)lbl_803CC1B8);
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
        *(s16*)(((u8*)lbl_803CC1B8) + 0x10) = 0;
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

// fn_1_BFB0, size:0x1D8
void fn_1_BFB0(void) {
    u16 pressed = *(u16*)((u8*)&lbl_803C77B8 + 2);
    u16 held = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (pressed & 0x100) {
        u16 effect = lbl_1_bss_3056[0] % 13 + lbl_1_data_17C4[lbl_1_bss_3056[0] / 13];
        fn_1_BF34(effect);
    } else if (pressed & 0x1200) {
        fn_1_A718();
        *(void (**)(void))((u8*)lbl_803CC1B8) = fn_1_A348;
    } else if (held & 1) {
        if (held & 0x800) {
            lbl_1_bss_3056[0] -= 10;
        } else {
            lbl_1_bss_3056[0]--;
        }
        if (lbl_1_bss_3056[0] < 0) {
            lbl_1_bss_3056[0] = 0xE9;
        }
    } else if (held & 2) {
        s16 next = lbl_1_bss_3056[0] + 1;
        if (held & 0x800) {
            next = lbl_1_bss_3056[0] + 10;
        }
        lbl_1_bss_3056[0] = next;
        if (next > 0xE9) {
            lbl_1_bss_3056[0] = 0;
        }
    }
}

// fn_1_BC00, size:0x1D8
void fn_1_BC00(void) {
    u16 pressed = *(u16*)((u8*)&lbl_803C77B8 + 2);
    u16 held = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (pressed & 0x100) {
        u16 effect = lbl_1_bss_3054[0] % 13 + lbl_1_data_17E8[lbl_1_bss_3054[0] / 13];
        fn_1_BF34(effect);
    } else if (pressed & 0x1200) {
        fn_1_A718();
        *(void (**)(void))((u8*)lbl_803CC1B8) = fn_1_A348;
    } else if (held & 1) {
        if (held & 0x800) {
            lbl_1_bss_3054[0] -= 10;
        } else {
            lbl_1_bss_3054[0]--;
        }
        if (lbl_1_bss_3054[0] < 0) {
            lbl_1_bss_3054[0] = 0xB5;
        }
    } else if (held & 2) {
        s16 next = lbl_1_bss_3054[0] + 1;
        if (held & 0x800) {
            next = lbl_1_bss_3054[0] + 10;
        }
        lbl_1_bss_3054[0] = next;
        if (next > 0xB5) {
            lbl_1_bss_3054[0] = 0;
        }
    }
}

// .text:0x0000BA64 size:0x19C
// Sound test: loads the menu sound groups, then hands over to fn_1_B5B8.
void fn_1_BA64(void) {
    ChTaskHeader* task = lbl_803CC1B8;
    ChSoundGroupTask* child;

    switch (lbl_1_bss_2FDF) {
    case 0:
        task->result = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child->step = 0;
        child->group = 1;
        child->callback = fn_1_A880;
        ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
        lbl_1_bss_2FDF++;
        break;
    case 1:
        if (task->result != 0) {
            task->result = 0;
            lbl_1_bss_2FDF++;
        }
        break;
    case 2:
        task->result = 0;
        lbl_1_bss_2FDF++;
        break;
    case 3:
        task->result = 0;
        lbl_1_bss_2FDF++;
        break;
    case 4:
        lbl_1_bss_2FDF++;
        break;
    case 5:
        lbl_1_bss_2FDF++;
        break;
    case 6:
        task->result = 0;
        child = fn_800B0A5C_insertQueue((void*)fn_1_9F04, 1);
        child->step = 0;
        child->group = 0x29;
        child->callback = fn_1_A77C;
        ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
        lbl_1_bss_2FDF++;
        break;
    case 7:
        if (task->result != 0) {
            task->result = 0;
            lbl_1_bss_2FDF++;
        }
        break;
    case 8:
        task->func = fn_1_B5B8;
        lbl_1_bss_2FDF = 0;
        break;
    }
}

// .text:0x0000B5B8 size:0x4AC
// NONMATCHING: the original addresses lbl_1_bss_2FD8 / lbl_1_data_FC0 as pools through a base register
// nmverify: lbl_1_bss_2FE0 lbl_1_bss_2FE1 lbl_1_bss_2FE2 lbl_1_bss_2FE4 lbl_1_bss_2FE6 lbl_1_bss_3044 lbl_1_bss_3048 lbl_1_bss_304C lbl_1_bss_3050 lbl_1_data_188C lbl_1_data_18EC lbl_1_data_1CA2 reached through a pooled base in original
#if NONMATCHING
void fn_1_B5B8(void) {
    u16 down = lbl_803C77B8._02;
    u16 repeat = lbl_803C77B8._04;
    s16 next;

    if (repeat & 0x800) {
        lbl_1_bss_2FE0 = 0;
    } else if (repeat & 0x400) {
        lbl_1_bss_2FE0 = 1;
    } else if (lbl_1_bss_2FE0 == 0) {
        if (down & 0x100) {
            if (lbl_1_bss_2FE1 == 0) {
                fn_1_BEF4((s16)lbl_1_bss_3050);
                lbl_1_bss_3050 = fn_1_BF34(lbl_1_data_1CA2);
            } else if (lbl_1_bss_2FE1 == 1) {
                u16 effect = lbl_1_data_188C[lbl_1_bss_2FE2];
                fn_1_BEF4((s16)lbl_1_bss_304C);
                lbl_1_bss_304C = fn_1_BF34(effect);
            } else if (lbl_1_bss_2FE1 == 2) {
                u16 effect = lbl_1_data_18EC[lbl_1_bss_2FE4];
                fn_1_BEF4((s16)lbl_1_bss_3048);
                lbl_1_bss_3048 = fn_1_BF34(effect);
            } else if (lbl_1_bss_2FE1 == 3) {
                lbl_1_bss_3044 = fn_80062890(lbl_1_bss_2FE6);
            }
        } else if (down & 0x1200) {
            fn_1_A718();
            // TODO type: lbl_800EF808 is the sound manager (groups[41], groups[1])
            fn_800ACFB0((void*)lbl_800EF808[0x2A]);
            fn_800ACFB0((void*)lbl_800EF808[2]);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_A348;
        } else if (repeat & 1) {
            if (lbl_1_bss_2FE1 == 0) {
                if (repeat & 0x800) {
                    lbl_1_data_1CA2 -= 10;
                } else {
                    lbl_1_data_1CA2--;
                }
                if (lbl_1_data_1CA2 < 0x151) {
                    lbl_1_data_1CA2 = 0x1B6;
                }
            } else if (lbl_1_bss_2FE1 == 1) {
                if (--lbl_1_bss_2FE2 < 0) {
                    lbl_1_bss_2FE2 = 47;
                }
            } else if (lbl_1_bss_2FE1 == 2) {
                if (--lbl_1_bss_2FE4 < 0) {
                    lbl_1_bss_2FE4 = 23;
                }
            } else if (lbl_1_bss_2FE1 == 3) {
                if (--lbl_1_bss_2FE6 < 0) {
                    lbl_1_bss_2FE6 = 68;
                }
            }
        } else if (repeat & 2) {
            if (lbl_1_bss_2FE1 == 0) {
                next = lbl_1_data_1CA2 + 1;
                if (repeat & 0x800) {
                    next = lbl_1_data_1CA2 + 10;
                }
                lbl_1_data_1CA2 = next;
                if (next > 0x1B6) {
                    lbl_1_data_1CA2 = 0x151;
                }
            } else if (lbl_1_bss_2FE1 == 1) {
                if (++lbl_1_bss_2FE2 > 47) {
                    lbl_1_bss_2FE2 = 0;
                }
            } else if (lbl_1_bss_2FE1 == 2) {
                if (++lbl_1_bss_2FE4 > 23) {
                    lbl_1_bss_2FE4 = 0;
                }
            } else if (lbl_1_bss_2FE1 == 3) {
                if (++lbl_1_bss_2FE6 > 68) {
                    lbl_1_bss_2FE6 = 0;
                }
            }
        } else if (repeat & 8) {
            lbl_1_bss_2FE1--;
        } else if (repeat & 4) {
            if (++lbl_1_bss_2FE1 > 3) {
                lbl_1_bss_2FE1 = 0;
            }
        }
    }
}
#endif

extern const f32 lbl_1_rodata_5E8; // 127.0f
extern const f32 lbl_1_rodata_5EC; // 0.0f
extern const f32 lbl_1_rodata_5F0; // 100.0f
extern const f32 lbl_1_rodata_5F4; // 10.0f
extern const f32 lbl_1_rodata_5F8; // 1.0f
extern const f32 lbl_1_rodata_5FC; // -1.0f
extern const f64 lbl_1_rodata_600; // 0.1
extern const f64 lbl_1_rodata_608; // 10.0

// .text:0x0000A95C size:0xB48
// 3D sound test: A starts an emitter + listener, Y/X + left/right edits listener/emitter values.
// NONMATCHING 92%: the original addresses the lbl_1_bss_2FD8 pool through a base register
// nmverify: lbl_1_bss_2FEA lbl_1_bss_2FEC lbl_1_bss_2FED lbl_1_bss_2FF0 lbl_1_bss_300C reached through a pooled base in original
#if NONMATCHING
void fn_1_A95C(void) {
    u16 down = lbl_803C77B8._02;
    u16 held = lbl_803C77B8._00;
    u16 repeat = lbl_803C77B8._04;
    s32 i;

    if (down & 0x100) {
        u16 effect = lbl_1_data_188C[lbl_1_bss_2FEA];

        if (lbl_1_common_bss_49994.active) {
            sndRemoveListener(&lbl_1_common_bss_49994.listener);
            sndRemoveEmitter(&lbl_1_common_bss_49994.emitter);
        }
        lbl_1_common_bss_49980.fxid = effect;
        lbl_1_common_bss_49980.maxVol = lbl_1_rodata_5E8;
        lbl_1_common_bss_49980.minVol = lbl_1_rodata_5EC;
        lbl_1_common_bss_49980.comp = lbl_1_rodata_5EC;
        lbl_1_common_bss_49980.maxDis = lbl_1_rodata_5F0;
        sndAddEmitter(&lbl_1_common_bss_49994.emitter, &lbl_1_common_bss_49994.emitter.pos, &lbl_1_common_bss_49994.emitter.dir, lbl_1_common_bss_49980.maxDis,
                      lbl_1_common_bss_49980.comp, SND_EMITTER_CONTINUOUS, lbl_1_common_bss_49980.fxid,
                      (u8)lbl_1_common_bss_49980.maxVol, (u8)lbl_1_common_bss_49980.minVol, NULL);

        lbl_1_common_bss_49970.frontSur = lbl_1_rodata_5F0;
        lbl_1_common_bss_49970.backSur = lbl_1_rodata_5F4;
        lbl_1_common_bss_49970.vol = 127;
        lbl_1_common_bss_49970.soundSpeed = lbl_1_rodata_5F8;
        lbl_1_common_bss_49994.listener.heading.x = lbl_1_rodata_5EC;
        lbl_1_common_bss_49994.listener.heading.y = lbl_1_rodata_5EC;
        lbl_1_common_bss_49994.listener.heading.z = lbl_1_rodata_5FC;
        lbl_1_common_bss_49994.listener.up.x = lbl_1_rodata_5EC;
        lbl_1_common_bss_49994.listener.up.y = lbl_1_rodata_5F8;
        lbl_1_common_bss_49994.listener.up.z = lbl_1_rodata_5EC;
        sndAddListener(&lbl_1_common_bss_49994.listener, &lbl_1_common_bss_49994.listener.pos, &lbl_1_common_bss_49994.listener.dir, &lbl_1_common_bss_49994.listener.heading,
                       &lbl_1_common_bss_49994.listener.up, lbl_1_common_bss_49970.frontSur, lbl_1_common_bss_49970.backSur,
                       lbl_1_common_bss_49970.soundSpeed, 0, lbl_1_common_bss_49970.vol, NULL);
        lbl_1_common_bss_49994.active = 1;
    } else if (down & 0x1200) {
        lbl_1_common_bss_49994.active = 0;
        fn_1_A718();
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_A348;
    } else if (held & 0x800) {
        // Y held: edit the listener (note rows 3 and 4 both edit dir.y)
        if (repeat & 1) {
            switch (lbl_1_bss_2FEC) {
            case 0: lbl_1_common_bss_49994.listener.pos.x -= lbl_1_rodata_600; break;
            case 1: lbl_1_common_bss_49994.listener.pos.y -= lbl_1_rodata_600; break;
            case 2: lbl_1_common_bss_49994.listener.pos.z -= lbl_1_rodata_600; break;
            case 3: lbl_1_common_bss_49994.listener.dir.y -= lbl_1_rodata_600; break;
            case 4: lbl_1_common_bss_49994.listener.dir.y -= lbl_1_rodata_600; break;
            case 5: lbl_1_common_bss_49994.listener.dir.z -= lbl_1_rodata_600; break;
            case 6: lbl_1_common_bss_49994.listener.heading.x -= lbl_1_rodata_600; break;
            case 7: lbl_1_common_bss_49994.listener.heading.y -= lbl_1_rodata_600; break;
            case 8: lbl_1_common_bss_49994.listener.heading.z -= lbl_1_rodata_600; break;
            case 9: lbl_1_common_bss_49994.listener.up.x -= lbl_1_rodata_600; break;
            case 10: lbl_1_common_bss_49994.listener.up.y -= lbl_1_rodata_600; break;
            case 11: lbl_1_common_bss_49994.listener.up.z -= lbl_1_rodata_600; break;
            case 12: lbl_1_common_bss_49994.listener.vol -= lbl_1_rodata_608; break;
            }
        } else if (repeat & 2) {
            switch (lbl_1_bss_2FEC) {
            case 0: lbl_1_common_bss_49994.listener.pos.x += lbl_1_rodata_600; break;
            case 1: lbl_1_common_bss_49994.listener.pos.y += lbl_1_rodata_600; break;
            case 2: lbl_1_common_bss_49994.listener.pos.z += lbl_1_rodata_600; break;
            case 3: lbl_1_common_bss_49994.listener.dir.y += lbl_1_rodata_600; break;
            case 4: lbl_1_common_bss_49994.listener.dir.y += lbl_1_rodata_600; break;
            case 5: lbl_1_common_bss_49994.listener.dir.z += lbl_1_rodata_600; break;
            case 6: lbl_1_common_bss_49994.listener.heading.x += lbl_1_rodata_600; break;
            case 7: lbl_1_common_bss_49994.listener.heading.y += lbl_1_rodata_600; break;
            case 8: lbl_1_common_bss_49994.listener.heading.z += lbl_1_rodata_600; break;
            case 9: lbl_1_common_bss_49994.listener.up.x += lbl_1_rodata_600; break;
            case 10: lbl_1_common_bss_49994.listener.up.y += lbl_1_rodata_600; break;
            case 11: lbl_1_common_bss_49994.listener.up.z += lbl_1_rodata_600; break;
            case 12: lbl_1_common_bss_49994.listener.vol += lbl_1_rodata_608; break;
            }
        } else if (repeat & 8) {
            if (--lbl_1_bss_2FEC < 0) {
                lbl_1_bss_2FEC = 12;
            }
        } else if (repeat & 4) {
            if (++lbl_1_bss_2FEC == 13) {
                lbl_1_bss_2FEC = 0;
            }
        }
    } else if (held & 0x400) {
        // X held: edit the emitter (note rows 3 and 4 both edit dir.y)
        if (repeat & 1) {
            switch (lbl_1_bss_2FED) {
            case 0: lbl_1_common_bss_49994.emitter.pos.x -= lbl_1_rodata_600; break;
            case 1: lbl_1_common_bss_49994.emitter.pos.y -= lbl_1_rodata_600; break;
            case 2: lbl_1_common_bss_49994.emitter.pos.z -= lbl_1_rodata_600; break;
            case 3: lbl_1_common_bss_49994.emitter.dir.y -= lbl_1_rodata_600; break;
            case 4: lbl_1_common_bss_49994.emitter.dir.y -= lbl_1_rodata_600; break;
            case 5: lbl_1_common_bss_49994.emitter.dir.z -= lbl_1_rodata_600; break;
            case 6: lbl_1_common_bss_49994.emitter.maxVol -= lbl_1_rodata_608; break;
            }
        } else if (repeat & 2) {
            switch (lbl_1_bss_2FED) {
            case 0: lbl_1_common_bss_49994.emitter.pos.x += lbl_1_rodata_600; break;
            case 1: lbl_1_common_bss_49994.emitter.pos.y += lbl_1_rodata_600; break;
            case 2: lbl_1_common_bss_49994.emitter.pos.z += lbl_1_rodata_600; break;
            case 3: lbl_1_common_bss_49994.emitter.dir.y += lbl_1_rodata_600; break;
            case 4: lbl_1_common_bss_49994.emitter.dir.y += lbl_1_rodata_600; break;
            case 5: lbl_1_common_bss_49994.emitter.dir.z += lbl_1_rodata_600; break;
            case 6: lbl_1_common_bss_49994.emitter.maxVol += lbl_1_rodata_608; break;
            }
        } else if (repeat & 8) {
            if (--lbl_1_bss_2FED < 0) {
                lbl_1_bss_2FED = 6;
            }
        } else if (repeat & 4) {
            if (++lbl_1_bss_2FED == 7) {
                lbl_1_bss_2FED = 0;
            }
        }
    } else if (repeat & 1) {
        if (--lbl_1_bss_2FEA < 0) {
            lbl_1_bss_2FEA = 1;
        }
    } else if (repeat & 2) {
        if (++lbl_1_bss_2FEA > 2) {
            lbl_1_bss_2FEA = 0;
        }
    }

    if (lbl_1_common_bss_49994.active) {
        sndUpdateListener(&lbl_1_common_bss_49994.listener, &lbl_1_common_bss_49994.listener.pos, &lbl_1_common_bss_49994.listener.dir, &lbl_1_common_bss_49994.listener.heading,
                          &lbl_1_common_bss_49994.listener.up, 0x80, NULL);
        sndUpdateEmitter(&lbl_1_common_bss_49994.emitter, &lbl_1_common_bss_49994.emitter.pos, &lbl_1_common_bss_49994.emitter.dir, 0x80, NULL);
    }

    // The original switches on the selected row rather than on i, so only that row's value is refreshed.
    for (i = 0; i < 13; i++) {
        switch (lbl_1_bss_2FEC) {
        case 0: lbl_1_bss_300C[0] = lbl_1_common_bss_49994.listener.pos.x; break;
        case 1: lbl_1_bss_300C[1] = lbl_1_common_bss_49994.listener.pos.y; break;
        case 2: lbl_1_bss_300C[2] = lbl_1_common_bss_49994.listener.pos.z; break;
        case 3: lbl_1_bss_300C[3] = lbl_1_common_bss_49994.listener.dir.y; break;
        case 4: lbl_1_bss_300C[4] = lbl_1_common_bss_49994.listener.dir.y; break;
        case 5: lbl_1_bss_300C[5] = lbl_1_common_bss_49994.listener.dir.z; break;
        case 6: lbl_1_bss_300C[6] = lbl_1_common_bss_49994.listener.heading.x; break;
        case 7: lbl_1_bss_300C[7] = lbl_1_common_bss_49994.listener.heading.y; break;
        case 8: lbl_1_bss_300C[8] = lbl_1_common_bss_49994.listener.heading.z; break;
        case 9: lbl_1_bss_300C[9] = lbl_1_common_bss_49994.listener.up.x; break;
        case 10: lbl_1_bss_300C[10] = lbl_1_common_bss_49994.listener.up.y; break;
        case 11: lbl_1_bss_300C[11] = lbl_1_common_bss_49994.listener.up.z; break;
        case 12: lbl_1_bss_300C[12] = lbl_1_common_bss_49994.listener.vol; break;
        }
    }
    for (i = 0; i < 7; i++) {
        switch (lbl_1_bss_2FED) {
        case 0: lbl_1_bss_2FF0[0] = lbl_1_common_bss_49994.emitter.pos.x; break;
        case 1: lbl_1_bss_2FF0[1] = lbl_1_common_bss_49994.emitter.pos.y; break;
        case 2: lbl_1_bss_2FF0[2] = lbl_1_common_bss_49994.emitter.pos.z; break;
        case 3: lbl_1_bss_2FF0[3] = lbl_1_common_bss_49994.emitter.dir.y; break;
        case 4: lbl_1_bss_2FF0[4] = lbl_1_common_bss_49994.emitter.dir.y; break;
        case 5: lbl_1_bss_2FF0[5] = lbl_1_common_bss_49994.emitter.dir.z; break;
        case 6: lbl_1_bss_2FF0[6] = lbl_1_common_bss_49994.emitter.maxVol; break;
        }
    }
}
#endif
