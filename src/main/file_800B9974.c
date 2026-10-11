#include "main/file_800B9974.h"

// .text:0x800B9974 size:0x50
void SetFogNone(void) {
    return;
}

// .text:0x800B99C4 size:0x6C
void SetFog(void) {
    return;
}

// .text:0x800B9A30 size:0x6C
void SetFogNoneAgain(void) {
    return;
}

extern f32 lbl_803CC218;

extern u32 lbl_803CC21C;

extern u32 lbl_803CC1F0;

// fn_800B9AA8, size:0x8
void fn_800B9AA8(u32 value) {
    lbl_803CC1F0 = value;
}

// fn_800B9A9C, size:0xC
void fn_800B9A9C(u32 flag, f32 value) {
    lbl_803CC21C = flag;
    lbl_803CC218 = value;
}

// .text:0x800B9AB0 size:0x3F8
void fn_800B9AB0(void) {
    return;
}

// .text:0x800B9EA8 size:0x5A4
void fn_800B9EA8(void) {
    return;
}

// .text:0x800BA44C size:0x3FC
void fn_800BA44C(void) {
    return;
}

// .text:0x800BA848 size:0x12E4
void Custom_SetState(void) {
    return;
}

// .text:0x800BBB2C size:0x430
void SetState(void) {
    return;
}

// .text:0x800BBF5C size:0x168
void GetColorFromQuant(void) {
    return;
}

// .text:0x800BC0C4 size:0x724
void DOVARender(void) {
    return;
}

// .text:0x800BC7E8 size:0x3C
void DOVARenderSkin(void) {
    return;
}

// fn_800BC824, size:0x10
void fn_800BC824(u8* object, void* value) {
    if (object != 0) {
        *(void**)(object + 0x50) = value;
    }
}

// .text:0x800BC834 size:0x2C
void DOSetWorldMatrix(void) {
    return;
}

// .text:0x800BC860 size:0x258
void InitDisplayObjWithLayout(void) {
    return;
}

// .text:0x800BCAB8 size:0x8C
void DOGet(void) {
    return;
}

// .text:0x800BCB44 size:0x21C
void LoadGeoPalette(void) {
    return;
}

// .text:0x800BCD60 size:0x5C
void convertGeometryAndSknHeader(void) {
    return;
}

// .text:0x800BCDBC size:0x7C
void fn_800BCDBC(void) {
    return;
}

// .text:0x800BCE38 size:0xC0
void fn_800BCE38(void) {
    return;
}

// .text:0x800BCEF8 size:0x298
void fn_800BCEF8(void) {
    return;
}

extern u32 lbl_803CC20C;

// fn_800BD190, size:0x58
void fn_800BD190(GQRValueGroups* groups, s32 value) {
    u32 i;
    s32 j;
    for (i = 0; i < groups->count; i++) {
        for (j = 0; j < groups->groups[i].group->count; j++) {
            groups->groups[i].group->entries[j].value = value;
        }
    }
}

// __MTGQR5, size:0x8
void __MTGQR5(register u32 value) {
    asm {
        mtspr GQR5, value
    }
}

// fn_800BD1E8, size:0x8
void fn_800BD1E8(u32 value) {
    lbl_803CC20C = value;
}

// __MTGQR6, size:0x8
void __MTGQR6(register u32 value) {
    asm {
        mtspr GQR6, value
    }
}

// __MTGQR7, size:0x8
void __MTGQR7(register u32 value) {
    asm {
        mtspr GQR7, value
    }
}

// .text:0x800BD208 size:0x38
void GQRSetup7(void) {
    return;
}

// .text:0x800BD240 size:0x38
void GQRSetup6(void) {
    return;
}

// .text:0x800BD278 size:0x38
void GQRSetup5(void) {
    return;
}

extern u32 lbl_803CC224;

extern u8 lbl_803CC220;

// fn_800BD2B0, size:0x1C
u8 fn_800BD2B0(u32* value) {
    if (lbl_803CC220 != 0) {
        *value = lbl_803CC224;
    }
    return lbl_803CC220;
}

// fn_800BD2CC, size:0x10
void fn_800BD2CC(u8 flag, u32* value) {
    u32 input = *value;
    lbl_803CC220 = flag;
    lbl_803CC224 = input;
}

// fn_800BD2DC, size:0x24
void fn_800BD2DC(void) {
    lbl_803CC220 = 0;
    ((u8*)&lbl_803CC224)[0] = 0;
    ((u8*)&lbl_803CC224)[2] = 0;
    ((u8*)&lbl_803CC224)[1] = 0;
    ((u8*)&lbl_803CC224)[3] = 0xFF;
}

// .text:0x800BD300 size:0xA0
void LITXForm(void) {
    return;
}

// .text:0x800BD3A0 size:0xC
void LITInitColor(void) {
    return;
}

// .text:0x800BD3AC size:0x10
void LITInitDir(void) {
    return;
}

// .text:0x800BD3BC size:0x10
void LITInitPos(void) {
    return;
}

// .text:0x800BD3CC size:0x20
void LITInitAttn(void) {
    return;
}
