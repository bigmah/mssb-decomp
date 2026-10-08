#include "challenge/rep_7730.h"

#include "static/UnknownHomes_Static.h"
extern void fn_1_20BD8(void);

extern void fn_1_246AC(void);

extern u8* lbl_803CC1B8[];

extern f32 lbl_1_bss_6BE4[4];

extern void (*lbl_1_data_1066C[])(s16);

extern f32 lbl_1_bss_6BF4[];
extern void fn_80037B18(void*, Vec*, f32);

extern u8 lbl_1_data_10674[];
extern void fn_1_1DA54(void);

extern u8 lbl_1_bss_6D48[];
extern const f32 lbl_1_rodata_77E4[];
extern void fn_1_272DC(void*, s32);
extern void fn_1_AF4(s32, s32, f32);
extern void fn_1_1E5D0(void*);

extern void fn_1_21408(void);
extern u8 lbl_803C6CF8[];
extern u8 lbl_1_data_104F4[];
extern const f32 lbl_1_rodata_77D8;
extern const f32 lbl_1_rodata_7804;
extern const f32 lbl_1_rodata_7858;
extern const f32 lbl_1_rodata_785C;
extern const f32 lbl_1_rodata_7860;
extern const f32 lbl_1_rodata_7864;
extern const f32 lbl_1_rodata_7868;

// fn_1_23AD8, size:0x7C
void fn_1_23AD8(Mtx44 projection, Vec* camera, Vec* target) {
    camera->x = lbl_1_rodata_77D8;
    camera->y = lbl_1_rodata_77D8;
    camera->z = lbl_1_rodata_7804;
    target->x = lbl_1_rodata_77D8;
    target->y = lbl_1_rodata_77D8;
    target->z = lbl_1_rodata_77D8;
    C_MTXFrustum(projection, lbl_1_rodata_7858, lbl_1_rodata_785C,
        lbl_1_rodata_7860, lbl_1_rodata_7864, lbl_1_rodata_77E4[0], lbl_1_rodata_7868);
}

// fn_1_20F8C, size:0xB4
void fn_1_20F8C(void) {
    s16 phase = *(s16*)(lbl_803CC1B8[0] + 0x10);
    ChallengeTransfer* transfer = *(ChallengeTransfer**)(lbl_803CC1B8[0] + 0x0C);
    switch (phase) {
    case 0:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            transfer->data = (void*)ARAMTransfer(lbl_1_data_104F4, 0, 0, 0);
            (*(s16*)(lbl_803CC1B8[0] + 0x10))++;
        }
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            transfer->complete = 1;
        }
        break;
    }
}

// .text:0x225B8 size:0x8C
void fn_1_225B8(void) {
    u8* queue = lbl_803CC1B8[0];
    switch ((s32)queue[0x25]) {
    case 0:
        fn_1_20DC8();
        queue[0x25]++;
        break;
    case 1:
        if (*(s16*)(queue + 0x10) != 0) {
            *(void (**)(void))queue = fn_1_21408;
        }
        break;
    }
}

// .text:0x1EFF4 size:0x68
void fn_1_1EFF4(void) {
    fn_1_272DC(lbl_1_bss_6D48, 0);
    fn_1_AF4(20, 20, lbl_1_rodata_77E4[0]);
    if (*(u32*)(lbl_803CC1B8[0] + 0x2C) & 2) {
        fn_1_1E5D0(lbl_1_bss_6BF4);
    }
}

// .text:0x1DCE4 size:0x64
void fn_1_1DCE4(void) {
    u8* queue = lbl_803CC1B8[0];
    *(void**)(queue + 0x14) = (void*)ARAMTransfer(lbl_1_data_10674, 0, 0, 0);
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_1DA54;
}

// .text:0x1DD94 size:0x50
void fn_1_1DD94(void) {
    Vec axis;
    axis.x = lbl_1_bss_6BE4[1];
    axis.y = lbl_1_bss_6BE4[2];
    axis.z = lbl_1_bss_6BE4[3];
    fn_80037B18(lbl_1_bss_6BF4, &axis, lbl_1_bss_6BE4[0]);
}

// .text:0x1E8C0 size:0x4C
void fn_1_1E8C0(s32 index) {
    lbl_1_data_1066C[*(s32*)(lbl_803CC1B8[0] + 0x28)]((s16)(index - 8));
}

// .text:0x1DE5C size:0x4
void fn_1_1DE5C(void) {
}

// .text:0x1E28C size:0x4
void fn_1_1E28C(void) {
}

void fn_1_1DDE4(f32 value) {
    lbl_1_bss_6BE4[3] = value;
}

void fn_1_1DDF4(f32 value) {
    lbl_1_bss_6BE4[2] = value;
}

void fn_1_1DE04(f32 value) {
    lbl_1_bss_6BE4[1] = value;
}

void fn_1_1DE14(f32 value) {
    lbl_1_bss_6BE4[0] = value;
}

f32 fn_1_1DE20(void) {
    return lbl_1_bss_6BE4[3];
}

f32 fn_1_1DE30(void) {
    return lbl_1_bss_6BE4[2];
}

f32 fn_1_1DE40(void) {
    return lbl_1_bss_6BE4[1];
}

f32 fn_1_1DE50(void) {
    return lbl_1_bss_6BE4[0];
}

// fn_1_267BC, size:0x38
void fn_1_267BC(void) {
    if (*(s16*)(lbl_803CC1B8[0] + 0x10) != 0) {
        fn_800B0A14_removeQueue(lbl_803CC1B8[0]);
    }
}

// fn_1_24778, size:0x28
void fn_1_24778(void) {
    lbl_803CC1B8[0][0x14] = 0;
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_246AC;
}

// fn_1_20DC8, size:0x38
void fn_1_20DC8(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_1_20BD8, 1);
    object[0x25] = 0;
    *(s16*)(object + 0x10) = 0;
}

// fn_1_1DD48, size:0x4C
f32 fn_1_1DD48(u16 buttons, s32 reverse, f32 value, f32 positive, f32 delta, f32 negative, f32 minimum, f32 maximum) {
    if (buttons & 0x40) delta = positive;
    else if (buttons & 0x20) delta = negative;
    if (reverse) delta = -delta;
    value += delta;
    if (value < minimum) value = minimum;
    if (value > maximum) value = maximum;
    return value;
}
