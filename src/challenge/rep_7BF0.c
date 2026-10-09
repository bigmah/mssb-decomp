#include "challenge/rep_7BF0.h"
#include "static/UnknownHomes_Static.h"

extern void fn_1_273D8(u8* object);
extern void* lbl_80366158[];
extern ChallengeQueueEntry* lbl_803CC1B8;
extern u8 lbl_1_bss_471BC[];
extern u8 lbl_1_bss_471D8[];
extern f32 lbl_1_rodata_7DFC;
extern void fn_1_272DC(void*, u32);
extern void fn_1_AF4(s32, s32, f32);
extern void fn_1_28CE8(u8*);
extern ChallengeSimulationSettings lbl_1_data_11300;
extern const char* lbl_1_data_11424[];
extern void fn_1_26D28(void*, u16, u16, u16, void*);
extern void fn_1_27330(void*);

static struct { u8 pad0[0x38]; s8 sel; u8 pad1[0xE7]; } sA = {{0}};
static u32 sB = 1;
static u32 sC[36] = {0};
static struct { u8 pad0[0x30]; u32 v; u8 pad1[0x444]; } sD = {{0}};
static ChallengeMenuItem* sE[2] = {0};

// fn_1_2948C, size:0x15C
static inline u8 NavigationMask(u16 held) {
    return (held & 0x800) ? 0x91 : ((held & 0x400) ? 0x50 : 0);
}
void fn_1_2948C(u8* object) {
    u16 held;
    u16 pressed;
    u16 repeated;

    repeated = *(u16*)((u8*)&lbl_803C77B8 + 4);
    held = lbl_803C77B8._00;
    pressed = lbl_803C77B8._02;
    if (lbl_803C77B8._02 & 0x1000) {
        object[0x14] ^= 1;
        if (object[0x14] != 0) {
            fn_800A97D0(32, 0);
        } else {
            fn_800A97D0(16, 30);
        }
    } else if (object[0x14] != 0) {
        fn_80048820(lbl_1_bss_471BC, held, pressed, repeated,
            NavigationMask(lbl_803C77B8._00));
        held &= 0xFFFFF3FF;
        pressed &= 0xFFFFF3FF;
        repeated &= 0xFFFFF3FF;
    } else if (lbl_803C77B8._02 & 0x200) {
        fn_1_29A48();
    }
    fn_1_26D28(lbl_1_bss_471D8, held, pressed, repeated, (u8*)&lbl_803C77B8 + 0x10);
    fn_1_27330(lbl_1_bss_471D8);
}


// fn_1_289E0, size:0x100
s32 fn_1_289E0(ChallengeSimulationMenu* menu, u16 buttons) {
    switch (lbl_1_data_11300.simulationState) {
    case 0:
        if (buttons & 0x100) {
            lbl_1_data_11300.simulationState = 2;
        } else if (buttons & 0x400) {
            lbl_1_data_11300.stepRequested = 1;
            lbl_1_data_11300.simulationState = 1;
        }
        break;
    case 1:
        if (buttons & 0x100) {
            lbl_1_data_11300.simulationState = 2;
        } else if (buttons & 0x200) {
            lbl_1_data_11300.simulationState = 0;
        } else if (buttons & 0x400) {
            lbl_1_data_11300.stepRequested = 1;
        }
        break;
    case 2:
        if (buttons & 0x100) {
            lbl_1_data_11300.simulationState = 1;
        } else if (buttons & 0x200) {
            lbl_1_data_11300.simulationState = 0;
        }
        break;
    }
    menu->items[menu->selected].text = lbl_1_data_11424[lbl_1_data_11300.simulationState];
    return 0;
}

// fn_1_2935C, size:0xB8
void fn_1_2935C(void* camera) {
    fn_80037768(camera, 2, lbl_1_data_11300.cameraFlags,
        (f32)lbl_1_data_11300.scaledCamera[0] / 100000.0f,
        (f32)lbl_1_data_11300.scaledCamera[1] / 100000.0f,
        (f32)lbl_1_data_11300.scaledCamera[2] / 100000.0f,
        (f32)lbl_1_data_11300.scaledCamera[3] / 100000.0f);
}

// fn_1_29414, size:0x78
void fn_1_29414(u8* object) {
    if (object[0x14] != 0) {
        fn_80048BEC(lbl_1_bss_471BC, 0, 0);
    }
    fn_1_272DC(lbl_1_bss_471D8, 0);
    fn_1_AF4(10, 10, lbl_1_rodata_7DFC);
    fn_1_28CE8(object);
}

// fn_1_29A48, size:0x54
void fn_1_29A48(void) {
    ChallengeQueueState* state;

    fn_800AD038(lbl_80366158[2]);
    fn_800A97D0(16, 30);
    state = lbl_803CC1B8->state;
    state->state = 1;
    fn_800B0A14_removeQueue(state);
}


// fn_1_289C0, size:0x20
void fn_1_289C0(u8* object) {
    fn_1_273D8(object);
}

// fn_1_28C34, size:0xB4
void fn_1_28C34(ChallengeSimulationMenu* menu, s32 which, void* data) {
    menu->data = data ? data : (void*)sB;
    menu->capacity = 0x10;
    menu->cursor = 0;
    menu->selected = 0;
    menu->flags = 1;
    menu->items = sE[which];
    if (which == 1) {
        if (sD.v == 0) {
            sD.v = sC[sA.sel];
        }
    }
    menu->count = 0;
    while (menu->items[menu->count].text != NULL) {
        menu->count++;
    }
}
