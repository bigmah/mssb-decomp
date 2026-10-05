#include "game/rep_3520.h"
#include "game/rep_1838.h"
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "stl/math.h"
#pragma dont_inline on


#include "static/UnknownHomes_Static.h"
extern u8 lbl_3_data_21AF0[];
extern s16 lbl_3_bss_B702;
extern f32 lbl_3_rodata_35D0;
extern f32 lbl_3_data_21A48[];
extern f32 lbl_3_rodata_35D8;
extern f32 lbl_3_rodata_35DC;
extern f32 lbl_3_rodata_3638;
extern s16 lbl_3_data_21A3C[];
extern s16 lbl_3_data_21A04[];
extern s16 lbl_3_data_21A44;
extern s16 lbl_3_data_21A60;
extern f32 lbl_3_rodata_3644;

// .text:0x00133200 size:0x120 mapped:0x80772294
void fn_3_133200(void) {
    return;
}

// .text:0x00133320 size:0x2C mapped:0x807723B4
#define G8 ((u8*)&g_Minigame)

#pragma opt_unroll_loops off
void fn_3_133320(void) {
    s8 i = 0;
    do {
        G8[0x1DC8 + i] = 0;
        i++;
    } while (i < 4);
}
#pragma opt_unroll_loops reset

// .text:0x0013334C size:0x1170 mapped:0x807723E0
void fn_3_13334C(void) {
    return;
}

// .text:0x001344BC size:0xF0 mapped:0x80773550
void fn_3_1344BC(void) {
    return;
}

// .text:0x001345AC size:0xAC mapped:0x80773640
void fn_3_1345AC(void) {
    return;
}

// .text:0x00134658 size:0x2B0 mapped:0x807736EC
void fn_3_134658(void) {
    return;
}

// .text:0x00134908 size:0x10 mapped:0x8077399C
s32 fn_3_134908(s16* a, s16* b) {
    return b[2] - a[2];
}

// .text:0x00134918 size:0x24 mapped:0x807739AC
s32 fn_3_134918(f32* a, f32* b) {
    if (*a < *b) {
        return -1;
    }
    return *a > *b;
}

// .text:0x0013493C size:0x344 mapped:0x807739D0
void fn_3_13493C(void) {
    return;
}

// .text:0x00134C80 size:0xCC mapped:0x80773D14
void fn_3_134C80(void) {
    return;
}

// .text:0x00134D4C size:0x370 mapped:0x80773DE0
void fn_3_134D4C(void) {
    return;
}

// .text:0x001350BC size:0x400 mapped:0x80774150
void fn_3_1350BC(void) {
    return;
}

// .text:0x001354BC size:0x64 mapped:0x80774550
int fn_3_1354BC(int idx, f32 x, f32 y) {
    u8* p = G8 + (idx << 6);
    f32 ax = fabs(*(f32*)&p[0xBB0] - x);
    f32 ay = fabs(*(f32*)&p[0xBB8] - y);
    if (ax <= lbl_3_rodata_35D8 && ay <= lbl_3_rodata_35DC) {
        return 1;
    }
    return 0;
}

// .text:0x00135520 size:0xE0 mapped:0x807745B4
void fn_3_135520(void) {
    return;
}

// .text:0x00135600 size:0x4C mapped:0x80774694
void fn_3_135600(f32* outX, f32* outY, f32 x, f32 y) {
    f32 dy = y - lbl_3_data_21A48[2];
    f32 dx = x - lbl_3_data_21A48[0];
    *outX = dx * *(f32*)&G8[0x1DF0] - dy * *(f32*)&G8[0x1DEC];
    *outY = dx * *(f32*)&G8[0x1DEC] + dy * *(f32*)&G8[0x1DF0];
}

// .text:0x0013564C size:0x4C mapped:0x807746E0
int fn_3_13564C(f32 x, f32 y) {
    if (x >= lbl_3_rodata_35D0) {
        if (y >= lbl_3_rodata_35D0) {
            return 0;
        }
        return 3;
    }
    if (y >= lbl_3_rodata_35D0) {
        return 1;
    }
    return 2;
}

// .text:0x00135698 size:0x60 mapped:0x8077472C
int fn_3_135698(u8* a, u8* b) {
    u8 fa = a[0x11];
    if (fa != 0 && b[0x11] == 0) {
        return -1;
    }
    if (fa == 0 && b[0x11] != 0) {
        return 1;
    }
    {
        if (*(f32*)a < *(f32*)b) {
            return -1;
        }
        return *(f32*)a > *(f32*)b;
    }
}

// .text:0x001356F8 size:0xAC mapped:0x8077478C
void fn_3_1356F8(void) {
    return;
}

// .text:0x001357A4 size:0x98 mapped:0x80774838
void fn_3_1357A4(void) {
    return;
}

// .text:0x0013583C size:0xE8 mapped:0x807748D0
void fn_3_13583C(void) {
    return;
}

// .text:0x00135924 size:0x140 mapped:0x807749B8
void fn_3_135924(void) {
    return;
}

// .text:0x00135A64 size:0x1B4 mapped:0x80774AF8
void fn_3_135A64(void) {
    return;
}

// .text:0x00135C18 size:0x220 mapped:0x80774CAC
void fn_3_135C18(void) {
    return;
}

// .text:0x00135E38 size:0x60 mapped:0x80774ECC
void fn_3_135E38(void) {
    fn_3_135C18();
    if ((u32)(*(s16*)((u8*)lbl_3_data_21A3C + G8[0x1D73] * 4 - 2) * 0x3C) == *(u32*)&G8[0x17C0]) {
        G8[0x1D72] = 3;
        *(s16*)&G8[0x1D62] = 0;
    }
}

// .text:0x00135E98 size:0xB4 mapped:0x80774F2C
void fn_3_135E98(void) {
    s16 t = *(s16*)&G8[0x1D62] + 1;
    *(s16*)&G8[0x1D62] = t;
    *(f32*)&G8[0x1D48] = lbl_3_rodata_3644 - (f32)t / (f32)lbl_3_data_21A60;
    fn_3_135C18();
    if (*(s16*)&G8[0x1D62] >= lbl_3_data_21A60) {
        G8[0x1D72] = 0;
    }
}

// .text:0x00135F4C size:0xA8 mapped:0x80774FE0
void fn_3_135F4C(void) {
    s16 t = *(s16*)&G8[0x1D62] + 1;
    *(s16*)&G8[0x1D62] = t;
    *(f32*)&G8[0x1D48] = (f32)t / (f32)lbl_3_data_21A60;
    fn_3_135C18();
    if (*(s16*)&G8[0x1D62] >= lbl_3_data_21A60) {
        G8[0x1D72] = 2;
    }
}

// .text:0x00135FF4 size:0x54 mapped:0x80775088
void fn_3_135FF4(void) {
    if ((u32)(*(s16*)((u8*)lbl_3_data_21A3C + G8[0x1D73] * 4) * 0x3C) == *(u32*)&G8[0x17C0]) {
        G8[0x1D72] = 1;
        *(s16*)&G8[0x1D62] = 0;
        *(f32*)&G8[0x1D48] = lbl_3_rodata_35D0;
        G8[0x1D73] = G8[0x1D73] + 1;
    }
}

// .text:0x00136048 size:0x74 mapped:0x807750DC
void fn_3_136048(void) {
    s32 i;
    s16* a = (s16*)&g_Minigame;
    for (i = 0; i < 4; i++) {
        a[0xEB2 + i] += lbl_3_data_21A44;
        a[0xEB2 + i] = fn_3_9FE6C_normalizeAngle(a[0xEB2 + i]);
    }
}

// .text:0x001360BC size:0x164 mapped:0x80775150
void fn_3_1360BC(void) {
    return;
}

// .text:0x00136220 size:0x66C mapped:0x807752B4
void fn_3_136220(void) {
    return;
}

// .text:0x0013688C size:0x468 mapped:0x80775920
void fn_3_13688C(void) {
    return;
}

// .text:0x00136CF4 size:0x1B0 mapped:0x80775D88
void fn_3_136CF4(void) {
    return;
}

// .text:0x00136EA4 size:0x1FC mapped:0x80775F38
void fn_3_136EA4(void) {
    return;
}

// .text:0x001370A0 size:0x148 mapped:0x80776134
void fn_3_1370A0(void) {
    return;
}

// .text:0x001371E8 size:0x3C mapped:0x8077627C
void fn_3_1371E8(void) {
    lbl_3_bss_B702 = *(s16*)lbl_3_data_21AF0;
    fn_800528AC((fn_800528AC_parameter)fn_3_1370A0);
}

// .text:0x00137224 size:0x1BC mapped:0x807762B8
void fn_3_137224(void) {
    return;
}

// .text:0x001373E0 size:0x5C0 mapped:0x80776474
void fn_3_1373E0(void) {
    return;
}

// .text:0x001379A0 size:0x170 mapped:0x80776A34
void fn_3_1379A0(void) {
    return;
}

// .text:0x00137B10 size:0x1E8 mapped:0x80776BA4
void fn_3_137B10(void) {
    return;
}

// .text:0x00137CF8 size:0xEC mapped:0x80776D8C
void fn_3_137CF8(void) {
    return;
}

// .text:0x00137DE4 size:0x130 mapped:0x80776E78
void fn_3_137DE4(void) {
    return;
}

// .text:0x00137F14 size:0x118 mapped:0x80776FA8
void fn_3_137F14(void) {
    return;
}

// .text:0x0013802C size:0x2B4 mapped:0x807770C0
void fn_3_13802C(void) {
    return;
}

// .text:0x001382E0 size:0x168 mapped:0x80777374
void fn_3_1382E0(void) {
    return;
}

// .text:0x00138448 size:0x6C mapped:0x807774DC
void fn_3_138448(u8* a) {
    if (G8[0x72A] == 0) {
        s16* t = (s16*)(a + 0x3A);
        if (*t < 0x7FFE) {
            *t += 1;
        } else {
            *t = 0x7FFF;
        }
        if (*(s16*)(a + 0x3A) >= *(s16*)(a + 0x38)) {
            a[0x3E] = 0;
            fn_3_1384B4();
        }
    }
}

// .text:0x001384B4 size:0x5F0 mapped:0x80777548
void fn_3_1384B4(void) {
    return;
}

// .text:0x00138AA4 size:0x71C mapped:0x80777B38
void fn_3_138AA4(void) {
    return;
}

// .text:0x001391C0 size:0x540 mapped:0x80778254
void fn_3_1391C0(void) {
    return;
}

// .text:0x00139700 size:0x4C mapped:0x80778794
void fn_3_139700(void) {
    u8* m = G8;
    if (m[0xBAC] != 0) {
        if (m[0x190B] != 0) {
            m[0xBAC] = 0;
            return;
        }
        fn_3_1391C0();
    }
}

// .text:0x0013974C size:0xBC mapped:0x807787E0
void fn_3_13974C(void) {
    return;
}

// .text:0x00139808 size:0x498 mapped:0x8077889C
void fn_3_139808(void) {
    return;
}

// .text:0x00139CA0 size:0x2E4 mapped:0x80778D34
void fn_3_139CA0(void) {
    return;
}

// .text:0x00139F84 size:0xC4 mapped:0x80779018
void fn_3_139F84(void) {
    return;
}

// .text:0x0013A048 size:0x64 mapped:0x807790DC
void fn_3_13A048(int i, int j) {
    s16* arr = (s16*)(G8 + 0x1890);
    s16 v = arr[j];
    s16 c = lbl_3_data_21A04[7];
    if (v < c) {
        arr[i] += v;
        arr[j] = 0;
    } else {
        arr[i] += c;
        arr[j] -= c;
    }
}

// .text:0x0013A0AC size:0x678 mapped:0x80779140
void fn_3_13A0AC(void) {
    return;
}

// .text:0x0013A724 size:0x178 mapped:0x807797B8
void fn_3_13A724(void) {
    return;
}

// .text:0x0013A89C size:0x1DC mapped:0x80779930
void fn_3_13A89C(void) {
    return;
}

// .text:0x0013AA78 size:0x23C mapped:0x80779B0C
void fn_3_13AA78(void) {
    return;
}

// .text:0x0013ACB4 size:0x10C mapped:0x80779D48
void fn_3_13ACB4(void) {
    return;
}

// .text:0x0013ADC0 size:0x5C mapped:0x80779E54
void fn_3_13ADC0(f32* out, f32* a, f32* b) {
    f32 d = (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
    d = d * lbl_3_rodata_3638;
    out[0] = a[0] - d * b[0];
    out[1] = a[1] - d * b[1];
    out[2] = a[2] - d * b[2];
}

// .text:0x0013AE1C size:0x1C8 mapped:0x80779EB0
void fn_3_13AE1C(void) {
    return;
}

// .text:0x0013AFE4 size:0x2A0 mapped:0x8077A078
void fn_3_13AFE4(void) {
    return;
}

// .text:0x0013B284 size:0x740 mapped:0x8077A318
void fn_3_13B284(void) {
    return;
}

// .text:0x0013B9C4 size:0x16C mapped:0x8077AA58
void fn_3_13B9C4(void) {
    return;
}

// .text:0x0013BB30 size:0xC4 mapped:0x8077ABC4
void fn_3_13BB30(void) {
    return;
}

// .text:0x0013BBF4 size:0xC4 mapped:0x8077AC88
void fn_3_13BBF4(void) {
    return;
}

// .text:0x0013BCB8 size:0x7AC mapped:0x8077AD4C
void fn_3_13BCB8(void) {
    return;
}

// .text:0x0013C464 size:0x4 mapped:0x8077B4F8
void fn_3_13C464(void) {
    return;
}

// .text:0x0013C468 size:0x328 mapped:0x8077B4FC
void fn_3_13C468(void) {
    return;
}

