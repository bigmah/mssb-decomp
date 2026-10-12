#include "menus/auto_00_00016870_text.h"
#include "menus/rep_04B0.h"
#include "static/UnknownHomes_Static.h"

#include "main/file_80011640.h"
#include "menus/menu_work.h"
#include "menus/rep_0568.h"

extern CaptainSelMenu lbl_2_bss_100B8;
extern Mtx lbl_2_bss_1010C;
extern MenuCharLoadTask* lbl_2_bss_1224;
extern void fn_2_18398(void);

// Queue slot `a` for loading (fn_2_18650 in rep_0568; inlined here).
static inline s32 queueSlot(s32 a) {
    s32 next = (lbl_2_bss_100B8.qHead + 1) % 10;
    if (next != lbl_2_bss_100B8.qTail) {
        if (lbl_2_bss_1224 == NULL) {
            lbl_2_bss_1224 = fn_800B0A5C_insertQueue(fn_2_18398, 0xFFFF);
            if (lbl_2_bss_1224 != NULL) {
                lbl_2_bss_1224->_1C = 0;
                lbl_2_bss_1224->state = 0;
            } else {
                return 0;
            }
        }
        lbl_2_bss_100B8.queue[lbl_2_bss_100B8.qHead] = a;
        lbl_2_bss_100B8.qHead = next;
        lbl_2_bss_100B8.loading[a] = 1;
        return 1;
    }
    return 0;
}

// Flag slots whose model id is 0x6B (fn_2_16CE0 in rep_0568; inlined here).
static inline void markSpecialModels(void) {
    CharActor* actor;
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8.count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL && actor->anim[0] == 0x6B) {
            lbl_2_bss_100B8.animState[i] = 1;
        }
    }
}

// -inline deferred emits functions in reverse source order: these are in reverse address order.

// fn_2_16A74, size:0x24
void fn_2_16A74(s32 index, s32 value) {
    value = value != 0;
    lbl_8036E548.actors[index].mode[0] = value;
}

// fn_2_16A5C, size:0x18
u8 fn_2_16A5C(s32 index) {
    return lbl_8036E548.actors[index].mode[0];
}

// fn_2_16A48, size:0x14
void fn_2_16A48(s32 index, u8 value) {
    lbl_2_bss_100B8._46[index] = value;
}

// fn_2_16A34, size:0x14
u8 fn_2_16A34(s32 index) {
    return lbl_2_bss_100B8._46[index];
}

// .text:0x00016870 size:0x1C4
void fn_2_16870(void) {
    camera_803c639c_s* cam;
    s32 i;

    for (i = 0; i < lbl_2_bss_100B8.count; i++) {
        if (lbl_2_bss_100B8.loadReq[i] != 0 && queueSlot(i)) {
            lbl_2_bss_100B8.loadReq[i] = 0;
        }
    }

    lbl_8036E548._307A = 5;
    lbl_8036E548._307C = 1;
    fn_2_16460();
    cam = fn_80052768_getCamera(0);
    PSMTXCopy(lbl_2_bss_1010C, cam->view);

    markSpecialModels();
}
