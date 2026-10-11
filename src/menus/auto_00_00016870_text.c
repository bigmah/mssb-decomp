#include "menus/auto_00_00016870_text.h"
#include "menus/rep_04B0.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_2_bss_100B8[];
extern u8 lbl_8036E548[];
extern Mtx lbl_2_bss_1010C;
extern u8* lbl_2_bss_1224;
extern void fn_2_18398(void);

// Menu-wide work area at lbl_8036E548 (only the fields used here).
typedef struct MenuWork16870 {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ u8* models[15]; // per-slot model; s16 at +0x62 is the model id
    /*0x2C8C*/ u8 _2C8C[0x307A - 0x2C8C];
    /*0x307A*/ u8 _307A;
    /*0x307B*/ u8 _307B;
    /*0x307C*/ u8 _307C;
} MenuWork16870;
#define MENU_WORK ((MenuWork16870*)lbl_8036E548)

// Queue slot `a` for loading (fn_2_18650 in rep_0568; inlined here).
static inline s32 queueSlot(s32 a) {
    s32 next = (*(s8*)&lbl_2_bss_100B8[0] + 1) % 10;
    if (next != *(s8*)&lbl_2_bss_100B8[1]) {
        if (lbl_2_bss_1224 == NULL) {
            lbl_2_bss_1224 = fn_800B0A5C_insertQueue(fn_2_18398, 0xFFFF);
            if (lbl_2_bss_1224 != NULL) {
                lbl_2_bss_1224[0x1C] = 0;
                lbl_2_bss_1224[0x1D] = 0;
            } else {
                return 0;
            }
        }
        lbl_2_bss_100B8[*(s8*)&lbl_2_bss_100B8[0] + 2] = a;
        lbl_2_bss_100B8[0] = next;
        lbl_2_bss_100B8[a + 0x42] = 1;
        return 1;
    }
    return 0;
}

// Flag slots whose model id is 0x6B (fn_2_16CE0 in rep_0568; inlined here).
static inline void markSpecialModels(void) {
    u8* model;
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        model = MENU_WORK->models[i];
        if (model != NULL && *(s16*)(model + 0x62) == 0x6B) {
            lbl_2_bss_100B8[i + 0x40] = 1;
        }
    }
}

// .text:0x00016870 size:0x1C4
void fn_2_16870(void) {
    camera_803c639c_s* cam;
    s32 i;

    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        if (lbl_2_bss_100B8[i + 0x14] != 0 && queueSlot(i)) {
            lbl_2_bss_100B8[i + 0x14] = 0;
        }
    }

    MENU_WORK->_307A = 5;
    MENU_WORK->_307C = 1;
    fn_2_16460();
    cam = fn_80052768_getCamera(0);
    PSMTXCopy(lbl_2_bss_1010C, cam->view);

    markSpecialModels();
}


// fn_2_16A34, size:0x14
u8 fn_2_16A34(s32 index) {
    u8* entry = lbl_2_bss_100B8 + index;
    return entry[0x46];
}

// fn_2_16A48, size:0x14
void fn_2_16A48(s32 index, u8 value) {
    u8* entry = lbl_2_bss_100B8 + index;
    entry[0x46] = value;
}

// fn_2_16A5C, size:0x18
u8 fn_2_16A5C(s32 index) {
    u8* entry = lbl_8036E548;
    entry += index * 0x27C;
    return entry[0xE61];
}

// fn_2_16A74, size:0x24
void fn_2_16A74(s32 index, s32 value) {
    s32 offset = index * 0x27C;
    u8* entry;
    value = value != 0;
    entry = lbl_8036E548;
    entry += offset;
    entry[0xE61] = value;
}
