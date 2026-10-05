#include "game/rep_36D8.h"
#include "header_rep_data.h"

#pragma dont_inline on

extern f32 lbl_3_rodata_3728;
extern u8 g_Minigame[];
extern u8 lbl_3_data_218BC[];
extern s32 lbl_3_bss_B798[];
extern f32 lbl_3_bss_B794;
#include "static/UnknownHomes_Static.h"

// .text:0x0013C7BC size:0xDBC mapped:0x8077B850
void fn_3_13C7BC(void) {
    return;
}

// .text:0x0013D578 size:0x70 mapped:0x8077C60C
u32 fn_3_13D578(s8 a) {
 u8* m = g_Minigame; s16* sp=(s16*)g_Minigame; s16* tp=(s16*)(g_Minigame+0x1890+a*2); s8 i=0;
 do {
     s8 t = *(s8*)(m + 0x18CC);
        if (t >= 0 && t < 4 && *(s16*)((u8*)sp + 0x1890) > *tp) { return 1; }
        i++; m += 1; sp += 1;
    } while (i < 4);
    return 0;
}

// .text:0x0013D5E8 size:0x30 mapped:0x8077C67C
s32 fn_3_13D5E8(f32* a, f32* b) {
    f32 c = lbl_3_rodata_3728;
    f32 y = *b;
    f32 x = *a;
    return (s32)(c * x - c * y);
}

// .text:0x0013D618 size:0x408 mapped:0x8077C6AC
void fn_3_13D618(void) {
    return;
}

// .text:0x0013DA20 size:0x30 mapped:0x8077CAB4
s32 fn_3_13DA20(f32* a, f32* b) {
    f32 c = lbl_3_rodata_3728;
    f32 y = *b;
    f32 x = *a;
    return (s32)(c * x - c * y);
}

// .text:0x0013DA50 size:0x1F8 mapped:0x8077CAE4
void fn_3_13DA50(void) {
    return;
}

// .text:0x0013DC48 size:0x198 mapped:0x8077CCDC
void fn_3_13DC48(void) {
    return;
}

// .text:0x0013DDE0 size:0xC4 mapped:0x8077CE74
void fn_3_13DDE0(void) {
    return;
}

// .text:0x0013DEA4 size:0x118 mapped:0x8077CF38
void fn_3_13DEA4(void) {
    return;
}

// .text:0x0013DFBC size:0x1B8 mapped:0x8077D050
void fn_3_13DFBC(void) {
    return;
}

// .text:0x0013E174 size:0xA8 mapped:0x8077D208
void fn_3_13E174(u8 a) {
    switch (a) {
    case 0:
        lbl_3_bss_B798[0] = (s32)((f32*)lbl_3_data_218BC)[12];
        lbl_3_bss_B794 = ((f32*)lbl_3_data_218BC)[14];
        break;
    case 1:
        lbl_3_bss_B798[0] = (s32)((f32*)lbl_3_data_218BC)[13];
        lbl_3_bss_B794 = ((f32*)lbl_3_data_218BC)[15];
        break;
    default:
        return;
    }
    fn_800528AC((fn_800528AC_parameter)fn_3_13DFBC);
}
// .text:0x0013E21C size:0x188 mapped:0x8077D2B0
void fn_3_13E21C(u8* a) {
    return;
}

// .text:0x0013E3A4 size:0x2CC mapped:0x8077D438
void fn_3_13E3A4(u8* a) {
    return;
}

// .text:0x0013E670 size:0x64 mapped:0x8077D704
void fn_3_13E670(void) {
    u8* m = g_Minigame;
    if (m[0x190B] != 0) {
        *(s8*)(m + 0x1D74) = -1;
        m[0xCCE] = 0;
    } else if (m[0xCCE] != 0) {
        fn_3_13E21C(m + 0xCB0);
    } else {
        fn_3_13E3A4(m + 0xCB0);
    }
}

// .text:0x0013E6D4 size:0x100 mapped:0x8077D768
void fn_3_13E6D4(void) {
    return;
}

// .text:0x0013E7D4 size:0x25C mapped:0x8077D868
void fn_3_13E7D4(void) {
    return;
}

// .text:0x0013EA30 size:0x214 mapped:0x8077DAC4
void fn_3_13EA30(void) {
    return;
}

// .text:0x0013EC44 size:0x840 mapped:0x8077DCD8
void fn_3_13EC44(void) {
    return;
}

// .text:0x0013F484 size:0x244 mapped:0x8077E518
void fn_3_13F484(void) {
    return;
}

// .text:0x0013F6C8 size:0x11C mapped:0x8077E75C
void fn_3_13F6C8(void) {
    return;
}

// .text:0x0013F7E4 size:0xE0 mapped:0x8077E878
void fn_3_13F7E4(void) {
    return;
}

// .text:0x0013F8C4 size:0x360 mapped:0x8077E958
void fn_3_13F8C4(void) {
    return;
}

// .text:0x0013FC24 size:0x660 mapped:0x8077ECB8
void fn_3_13FC24(void) {
    return;
}

// .text:0x00140284 size:0x200 mapped:0x8077F318
void fn_3_140284(void) {
    return;
}

// .text:0x00140484 size:0x154 mapped:0x8077F518
void fn_3_140484(void) {
    return;
}

// .text:0x001405D8 size:0x11C mapped:0x8077F66C
void fn_3_1405D8(void) {
    return;
}

// .text:0x001406F4 size:0x2B8 mapped:0x8077F788
void fn_3_1406F4(void) {
    return;
}

// .text:0x001409AC size:0x220 mapped:0x8077FA40
void fn_3_1409AC(void) {
    return;
}

// .text:0x00140BCC size:0x114 mapped:0x8077FC60
void fn_3_140BCC(void) {
    return;
}

// .text:0x00140CE0 size:0x410 mapped:0x8077FD74
void fn_3_140CE0(void) {
    return;
}

// .text:0x001410F0 size:0x1CC mapped:0x80780184
void fn_3_1410F0(void) {
    return;
}

// .text:0x001412BC size:0x128 mapped:0x80780350
void fn_3_1412BC(void) {
    return;
}

// .text:0x001413E4 size:0xC8 mapped:0x80780478
void fn_3_1413E4(void) {
    return;
}

// .text:0x001414AC size:0x580 mapped:0x80780540
void fn_3_1414AC(void) {
    return;
}

