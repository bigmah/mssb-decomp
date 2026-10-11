#include "game/rep_3CE0.h"
#include "header_rep_data.h"
#include "stl/stdarg.h"
#include "stl/mem.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "static/Camera.h"
#include "main/file_80011640.h"
#include "main/file_80024184.h"
#include "main/file_8004C5F8.h"

extern PlayerMarkerData lbl_3_data_27EC0;
extern u8 lbl_803CBBC0; // frame buffer index
// Stadium effect state (lbl_3_common_bss_35154); only the fields used here.
extern struct {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ u8* effectFile;
    /*0x008*/ u8 _008[0x468 - 0x8];
    /*0x468*/ u32 fadeColor;
    /*0x46C*/ u8 _46C[0x471 - 0x46C];
    /*0x471*/ u8 _471;
    /*0x472*/ u8 _472;
} lbl_3_common_bss_35154;

// NONMATCHING 69%: the original addresses each table (size, sizeClass, layout, nodes) through its own
// pooled base register (separate static objects in the original TU); ours folds them into one struct
// Places one marker per argument (each argument is a player slot 0-3); several
// markers on the same player are spread out using the layout slots.
// .text:0x0015FB84 size:0x3A4 mapped:0x8079EC18
#if NONMATCHING
void fn_3_15FB84(s32 count, ...) {
    PlayerMarkerData* d = &lbl_3_data_27EC0;
    PlayerMarkerLayout* lay = &d->layout;
    s32 perPlayer[4];
    va_list args;
    PlayerMarker* m;
    PlayerMarkerSlot* slot;
    CharActor* actor;
    f32 yOffset;
    s32 i;
    s32 n;
    PlayerMarkerNode* node;

    yOffset = -((f32)lay->height / 100000.0f);
    node = &lay->nodes[lbl_803CBBC0];
    node->count = count;
    node->tex = (TexImage*)(lbl_3_common_bss_35154.effectFile + 0x344); // TODO type
    node->fadeColor = lbl_3_common_bss_35154.fadeColor;

    memset(perPlayer, 0, sizeof(perPlayer));
    va_start(args, count);
    for (i = 0; i < count; i++) {
        perPlayer[va_arg(args, s32)]++;
    }

    n = 0;
    m = lay->nodes[lbl_803CBBC0].markers;
    for (i = 0; i < 4; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL) {
            switch (perPlayer[i]) {
            case 0:
                break;
            case 1:
                slot = lay->one;
                break;
            case 2:
                slot = lay->two;
                break;
            case 3:
            default:
                slot = lay->three;
                break;
            }
            while (perPlayer[i]-- != 0) {
                m->active = 1;
                n++;
                m->top.x = actor->pos.x + (f32)slot->dx / 100000.0f;
                m->top.y = yOffset + (actor->pos.y + (f32)slot->dy / 100000.0f);
                m->top.z = actor->pos.z;
                m->base.x = actor->pos.x;
                m->base.y = actor->pos.y;
                m->base.z = actor->pos.z;
                m->width = (f32)d->size[d->sizeClass[actor->kind]][0] / 100000.0f;
                m->radius = (f32)d->size[d->sizeClass[actor->kind]][1] / 100000.0f;
                m->topColor = slot->topColor;
                m->baseColor = slot->baseColor;
                slot++;
                m++;
            }
        }
    }
    for (; n < 4; n++) {
        m->active = 0;
        m++;
    }
    fn_800A7D4C(11, &lay->nodes[lbl_803CBBC0].hdr);
}

#endif

// .text:0x0015FF28 size:0x650 mapped:0x8079EFBC
void fn_3_15FF28(PlayerMarkerNode* node) {
    return;
}
