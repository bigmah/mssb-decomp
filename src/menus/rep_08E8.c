#include "menus/rep_08E8.h"
#include "main/file_80011640.h"
#include "menus/menu_work.h"
#include "menus/menu_asset.h"
#include "menus/rep_10C0.h" // MenuCamera
#include "main/file_800BD8C4.h"
#include "main/file_80024D2C.h"
#include "C3/control.h"
#include "main/file_800A7C08.h"

extern MenuLineScore lbl_80353A90;
extern MenuRosterRecord lbl_803537E4[2][9];
extern MenuFieldRecord lbl_803535C8[2][9];
extern MenuSelectState lbl_8034E9A0;
#include "string.h"

extern void LITXForm(void* light, void* matrix);

#include "Dolphin/vec.h"
extern s32 fn_2_68690(s32 index);
extern void fn_2_68DAC(s32 index, void* result);
#include "main/particle_params5.h"
extern TexArchive* lbl_803CBD0C; // effect particle textures
extern ParticleParams5* lbl_2_data_13374[];

extern u16 lbl_2_data_13238[];

extern u8 lbl_803CBBC0[];
extern DrawCallbackNode lbl_2_data_13228[2]; // draw nodes queued with fn_800A7D4C

extern const f32 lbl_2_rodata_9B0;

#include "static/UnknownHomes_Static.h"
#include "math.h"

extern const f32 lbl_2_rodata_94C;
extern const f32 lbl_2_rodata_9A8;
extern const f32 lbl_2_rodata_9AC;
extern const f32 lbl_2_rodata_9B4;
extern const f32 lbl_2_rodata_9A0;

extern MenuCtx* lbl_2_bss_1A8248[];

extern MenuData* lbl_2_bss_1A824C[];

extern void* _OSAllocFromHeap(s32 alignment, s32 size);
extern void fn_2_513E0(void* buffer, s32 x, s32 y, s32 option, s32 style, s32 first, s32 second, s32 third);

// This unit's .bss (file statics, emitted in reverse order of definition).
static MenuNumberState lbl_2_bss_55C0;
static f32 lbl_2_bss_55BC;
static f32 lbl_2_bss_55B8;
extern Vec lbl_2_data_132EC;
extern Vec lbl_2_data_132F8;

// .text:0x48BE0 size:0x128
void fn_2_48BE0(void) {
    f32 x;
    f32 z;
    Vec position;
    Vec direction;
    MenuData* menu = lbl_2_bss_1A824C[0];
    CharActor* parameters = &lbl_8036E548.actors[menu->_19769C];
    memcpy(&position, &parameters->pos, sizeof(Vec));
    PSVECSubtract(&position, &lbl_2_data_132F8, &direction);
    z = direction.z * lbl_2_rodata_9A0;
    x = direction.x * lbl_2_rodata_9A0;
    direction.x = x;
    direction.z = z;
    if (lbl_2_rodata_94C != x || lbl_2_rodata_94C != z) {
        lbl_2_bss_55B8 = fn_2_4A1E8(direction.z, x);
    }
    memcpy(&lbl_2_data_132F8, &parameters->pos, sizeof(Vec));
    parameters->pos.x = position.x;
    parameters->pos.y = position.y;
    parameters->pos.z = position.z;
    parameters->rot.x = lbl_2_data_132EC.x;
    parameters->rot.y = lbl_2_bss_55B8;
    parameters->rot.z = lbl_2_data_132EC.z;
}

// .text:0x49DB8 size:0xA4
void fn_2_49DB8(s32 x, s32 y, s32 number, s32 flags, s32 option, s32 digits,
                s32 style, s32 first, s32 second, s32 third) {
    void* buffer = _OSAllocFromHeap(16, 64);
    fn_2_4917C(buffer, number, flags, digits, style);
    fn_2_513E0(buffer, x, y, option, style, first, second, third);
    if (buffer != NULL) {
        fn_800ACFB0(buffer);
    }
}

// .text:0x49E5C size:0xA0
void fn_2_49E5C(s32 x, s32 y, s32 number, s32 flags, s32 digits, s32 style,
                s32 first, s32 second, s32 third) {
    void* buffer = _OSAllocFromHeap(16, 64);
    fn_2_4917C(buffer, number, flags, digits, style);
    fn_2_513E0(buffer, x, y, 0, style, first, second, third);
    if (buffer != NULL) {
        fn_800ACFB0(buffer);
    }
}

// .text:0x4A234 size:0x90
s16 fn_2_4A234(f32 x, f32 y) {
    s16 angle;
    if (lbl_2_rodata_94C == x) {
        if (y >= lbl_2_rodata_94C) {
            return 0x400;
        }
        return 0xC00;
    }
    angle = (s16)((lbl_2_rodata_9B4 * (f32)atan2(y, x)) / lbl_2_rodata_9A8);
    if (angle < 0) {
        angle += 0x1000;
    }
    return angle;
}

// .text:0x48D08 size:0x4C
void fn_2_48D08(void) {
    MenuData* menu = lbl_2_bss_1A824C[0];
    s32 index = menu->_19769C;
    CharActor* parameters = &lbl_8036E548.actors[index];
    parameters->pos.x = lbl_2_rodata_94C;
    parameters->pos.y = lbl_2_rodata_94C;
    parameters->pos.z = lbl_2_rodata_94C;
    parameters->rot.x = lbl_2_rodata_94C;
    parameters->rot.y = lbl_2_rodata_94C;
    parameters->rot.z = lbl_2_rodata_94C;
}

// .text:0x4A064 size:0x4
void fn_2_4A064(void) {
}

// .text:0x474F8 size:0x4
void fn_2_474F8(void) {
}

s16 fn_2_4A150(s16 angle) {
    if (angle < 0) {
        while (angle < 0) angle += 0x1000;
    }
    if (angle >= 0x1000) {
        while (angle >= 0x1000) angle -= 0x1000;
    }
    return angle;
}

s16 fn_2_4A310(s16 a, s16 b) {
    int difference = a - b;
    difference = (s16)((difference < 0) ? -difference : difference);
    if (difference > 0x800) return 0x1000 - difference;
    return difference;
}

u16* fn_2_4A094(u16* destination, const u16* source) {
    u16* result = destination;
    while (*source != 0x4000) *destination++ = *source++;
    *destination = *source;
    return result;
}

s32 fn_2_4A068(const u16* string) {
    const u16* end = string;
    while (*end != 0x4000) end++;
    return (s32)(end - string);
}

s32 fn_2_46D00(void) {
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    if (menu->_441C == 5 && menu->_4422 >= 6) return 1;
    return 0;
}

void fn_2_481B8(void) {
    u8* camera = (u8*)fn_80052768_getCamera(0);
    fn_800BD670((void*)lbl_8036E548.slots, (MtxPtr)(camera + 0x40));
}

// fn_2_474FC, size:0x44
void fn_2_474FC(void) {
    if (lbl_8036E548._2C88 != 0) {
        fn_800ACFB0(lbl_8036E548._2C88);
        lbl_8036E548._2C88 = 0;
    }
}

// fn_2_4777C, size:0x44
void fn_2_4777C(void) {
    if ((void*)lbl_8036E548.fileBuf != 0) {
        fn_800ACFB0((void*)lbl_8036E548.fileBuf);
        lbl_8036E548.fileBuf = 0;
    }
}

// fn_2_4A1E8, size:0x4C
f32 fn_2_4A1E8(f32 x, f32 y) {
    if (x == 0.0f && y == 0.0f) return 0.0f;
    return (f32)atan2(y, x);
}

// fn_2_4A2C4, size:0x4C
s32 fn_2_4A2C4(f32 angle) {
    if (angle < lbl_2_rodata_94C) angle = lbl_2_rodata_9AC + angle;
    return (s32)((lbl_2_rodata_9B4 * angle) / lbl_2_rodata_9A8);
}

// fn_2_47AFC, size:0x28
void fn_2_47AFC(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 13; i++) {}
}

// fn_2_4A18C, size:0x5C
f32 fn_2_4A18C(f32 angle) {
    if (angle >= lbl_2_rodata_9A8) {
        while (angle >= lbl_2_rodata_9A8) angle -= lbl_2_rodata_9AC;
    }
    if (angle < lbl_2_rodata_9B0) {
        while (angle < lbl_2_rodata_9B0) angle = lbl_2_rodata_9AC + angle;
    }
    return angle;
}

// fn_2_46D34, size:0x60
void fn_2_46D34(s32 delta) {
    lbl_2_bss_1A8248[0]->_43BE = lbl_2_bss_1A8248[0]->_43BC;
    lbl_2_bss_1A8248[0]->_43BC += delta;
    if (lbl_2_bss_1A8248[0]->_43BC > 999) {
        lbl_2_bss_1A8248[0]->_43BC = 999;
    }
    if (lbl_2_bss_1A8248[0]->_43BC < 0) {
        lbl_2_bss_1A8248[0]->_43BC = 0;
    }
}

// fn_2_489DC, size:0x40
void fn_2_489DC(void) {
    s32 index = lbl_803CBBC0[0];
    fn_800A7D4C(0xC, &lbl_2_data_13228[index]);
}

// fn_2_49EFC, size:0x80
s32 fn_2_49EFC(const u16* string, u16 style) {
    u32 character;
    s32 width = 0;
    while ((character = *string) != 0x4000) {
        if (character == 0x4003) {
            width += lbl_2_data_13238[style];
        } else if (character == 0x4002) {
            width += (u32)lbl_2_data_13238[style] >> 1;
        } else if (!(character & 0x4000)) {
            if (character & 0x8000) {
                width += lbl_2_data_13238[style];
            } else {
                width += (u32)lbl_2_data_13238[style] >> 1;
            }
        }
        string++;
    }
    return width;
}

// fn_2_46C88, size:0x78
void fn_2_46C88(s32 index, s32 unused) {
    Vec position;
    fn_2_68690(0);
    fn_2_68DAC(index, &position);
    PSVECScale(&position, 2.0f, &position);
    lbl_2_data_13374[0]->tex = lbl_803CBD0C;
    fn_80031CA4(&position, lbl_2_data_13374[0]);
}

// fn_2_48D54, size:0x60
void fn_2_48D54(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        u8* camera = (u8*)fn_80052768_getCamera(0);
        LITXForm((void*)lbl_8036E548.lights[i], camera + 0x40);
    }
}

// fn_2_4A0C4, size:0x8C
s32 fn_2_4A0C4(const u16* a, const u16* b) {
    while (1) {
        if ((*a & 0xC000) == 0xC000) return -1;
        if ((*b & 0xC000) == 0xC000) return 1;
        if (*a == 0x4000 && *b == 0x4000) break;
        if (*a == 0x4000) return -1;
        if (*b == 0x4000) return 1;
        if (*a - *b != 0) return *a - *b;
        a++;
        b++;
    }
    return 0;
}

extern s32 lbl_2_data_38B8;
extern void fn_2_4B2D0();

// .text:0x4ACF8 size:0x1EC
void fn_2_4ACF8(void) {
    GameInitVariables* settings = &g_d_GameSettings;
    s16 mode;
    MenuCtx* menu;

    fn_2_4B2D0();
    mode = *(u8*)&lbl_2_bss_1A824C[0]->_197843;
    if ((s8)mode == 0) {
        s32 add = settings->challengeMinigame_baseCoinsEarned;
        lbl_2_bss_1A8248[0]->_43BE = lbl_2_bss_1A8248[0]->_43BC;
        lbl_2_bss_1A8248[0]->_43BC += add;
        if (lbl_2_bss_1A8248[0]->_43BC > 999) {
            lbl_2_bss_1A8248[0]->_43BC = 999;
        }
        if (lbl_2_bss_1A8248[0]->_43BC < 0) {
            lbl_2_bss_1A8248[0]->_43BC = 0;
        }
        lbl_2_bss_1A824C[0]->_197792 = settings->challengeMinigame_baseCoinsEarned;
        lbl_2_bss_1A824C[0]->_197798 = settings->challengeMinigame_baseCoinsEarned;
    } else if ((s8)mode == 1) {
        s32 add = lbl_2_data_38B8;
        lbl_2_bss_1A8248[0]->_43BE = lbl_2_bss_1A8248[0]->_43BC;
        lbl_2_bss_1A8248[0]->_43BC += add;
        if (lbl_2_bss_1A8248[0]->_43BC > 999) {
            lbl_2_bss_1A8248[0]->_43BC = 999;
        }
        if (lbl_2_bss_1A8248[0]->_43BC < 0) {
            lbl_2_bss_1A8248[0]->_43BC = 0;
        }
        lbl_2_bss_1A824C[0]->_197794 = lbl_2_data_38B8;
        lbl_2_bss_1A824C[0]->_197798 = lbl_2_data_38B8;
    } else if ((s8)mode == 2) {
        lbl_2_bss_1A824C[0]->_197796 = 0;
        lbl_2_bss_1A824C[0]->_197798 = 0;
    }
    menu = lbl_2_bss_1A8248[0];
    if ((s8)menu->_44F8[5] > 0) {
        menu->_44F8[5] = menu->_44F8[5] - 1;
    }
    if (lbl_2_bss_1A824C[0]->_197843 == 0 && lbl_2_bss_1A8248[0]->_4429 == 0) {
        lbl_2_bss_1A8248[0]->_4429 = 1;
    }
}

extern struct GameActor** fn_800111D8(struct CharActor* actor);
extern void ACTSetAnimation(GameActor* actor, void* animBank, char* sequenceName, u16 seqNum, f32 time, f32 blendSpeed);
extern void Set_FUN_800b2b6c(GameActor* actor, u16* boneRemap);
extern void fn_800B4CA0(GameActor* actor, f32 time);
extern void fn_800B4C04(GameActor* actor, f32 speed);
extern void fn_800B4AFC(GameActor* actor, u8 loop);
extern u8* fn_80052734(s32);
extern s32 fn_800527BC(void);
extern u8 fn_800B3C04(s32 viewIndex, GameActor* actor, Mtx camera);
extern MenuCharMgr* lbl_2_bss_340140;
extern const f32 lbl_2_rodata_9B0;

// .text:0x47B24 size:0x1D8
void fn_2_47B24(u16* count) {
    u8* cam;
    GameActor* o;
    u16 i;
    u16 j;
    ActorObject* p;
    CharActor* actor;
    u8 f;
    f32 m[3][4];
    if (lbl_2_bss_340140->_307A != 3) {
        for (i = 0; i < *count; i++) {
            actor = lbl_8036E548.active[i];
            if (actor != NULL && actor->mode[0] != 0) {
                p = (ActorObject*)fn_800111D8(actor);
                if (p->actor != NULL) {
                    if (p->setAnimation != 0) {
                        ACTSetAnimation(p->actor, p->animBank, NULL, p->seqNum, lbl_2_rodata_94C, p->speed);
                    }
                    if (p->setTime != 0) {
                        fn_800B4CA0(p->actor, p->time);
                    }
                    if (p->setSpeed != 0) {
                        fn_800B4C04(p->actor, p->unk54);
                    }
                    f = p->visFlags;
                    if (f & 2) {
                        fn_800B4AFC(p->actor, (u8)(f & 1));
                    }
                    Set_FUN_800b2b6c(p->actor, p->boneRemap);
                    if (p->animateBones != 0) {
                        fn_800BDA24(p);
                    }
                    for (j = 0; j < fn_800527BC(); j++) {
                        cam = fn_80052734(j) + 0x40;
                        PSMTXTrans(m, actor->pos.x, actor->pos.y, actor->pos.z);
                        PSMTXConcat((void*)cam, m, m);
                        o = p->actor;
                        o->flags = (o->flags & (u8)~(3 << (j * 3))) | (fn_800B3C04(j, o, m) << (j * 3));
                    }
                    p->setAnimation = 0;
                    p->setTime = 0;
                    p->setSpeed = 0;
                    p->visFlags = p->visFlags & 1;
                }
            }
        }
    }
}

#include "musyx/musyx.h"
extern u8 lbl_800EFBA4[];

// .text:0x46D94 size:0x530
// Move a list cursor with the d-pad: 4/8 step the cursor down/up (scrolling the
// page when it leaves the visible window), 0x20/0x40 page down/up.
// flags: 1 wrap, 2 wrap pages, 4 last page may be partial, 8 no paging, 0x10 silent.
void fn_2_46D94(s16* sel, s16* scroll, s16 count, s16 page, u32 flags) {
    s16 last;
    s32 rem;
    s16 max;
    s32 v;
    s16 step;
    s16 back;
    u8* pad;
    u32 partial;

    if (count == 0) {
        return;
    }
    if ((page == 0) | (count < page)) {
        page = count;
    }
    rem = count % page;
    if (rem != 0) {
        last = rem;
    } else {
        last = page;
    }
    partial = flags & 4;
    if (partial) {
        max = count - last;
    } else {
        max = count - page;
    }
    pad = (u8*)&lbl_803C77B8;
    pad += lbl_2_bss_1A824C[0]->port * sizeof(MenuPad);
    switch (((MenuPad*)pad)->repeat) {
    case 0x8:
        if (scroll != NULL) {
            *sel = v = (s16)(*sel - 1);
            if (v < 0) {
                if (*scroll != 0) {
                    *scroll -= 1;
                    if (!(flags & 0x10)) {
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                } else if (flags & 1) {
                    if (partial) {
                        *sel = last - 1;
                    } else {
                        *sel = page - 1;
                    }
                    *scroll = max;
                    if (!(flags & 0x10)) {
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                    break;
                }
                *sel += 1;
            } else if (!(flags & 0x10)) {
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else {
            *sel = v = (s16)(*sel - 1);
            if (v < 0) {
                if (flags & 1) {
                    *sel = count - 1;
                    if (!(flags & 0x10)) {
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                } else {
                    *sel += 1;
                }
            } else if (!(flags & 0x10)) {
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
        break;
    case 0x4:
        if (scroll != NULL) {
            if (*sel + *scroll >= count - 1) {
                if (*scroll < max) {
                    *scroll += 1;
                    *sel -= 1;
                } else if (flags & 1) {
                    *sel = 0;
                    *scroll = 0;
                } else {
                    break;
                }
                if (!(flags & 0x10)) {
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            } else if (*sel >= page - 1) {
                if (*scroll < max) {
                    *scroll += 1;
                } else if (flags & 1) {
                    *sel = 0;
                    *scroll = 0;
                } else {
                    break;
                }
                if (!(flags & 0x10)) {
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            } else {
                *sel += 1;
                if (!(flags & 0x10)) {
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        } else {
            if (++*sel >= count) {
                if (flags & 1) {
                    *sel = 0;
                } else {
                    *sel -= 1;
                    break;
                }
            }
            if (!(flags & 0x10)) {
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
        break;
    case 0x20:
        if (!(flags & 8) && scroll != NULL && count > page) {
            v = *scroll;
            step = page - v % page;
            if (v == max) {
                if (flags & 2) {
                    *scroll = 0;
                } else {
                    *scroll = max;
                    return;
                }
            } else {
                *scroll = v = (s16)(v + step);
                if (v > max) {
                    *scroll = max;
                }
            }
            *sel = 0;
            if (!(flags & 0x10)) {
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        }
        break;
    case 0x40:
        if (!(flags & 8) && scroll != NULL && count > page) {
            back = *scroll % page;
            if (back == 0) {
                back = page;
            }
            if (*scroll <= 0) {
                if (flags & 2) {
                    *scroll = max;
                    *sel = 0;
                    if (!(flags & 0x10)) {
                        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    }
                }
            } else {
                *scroll -= back;
                *sel = 0;
                if (!(flags & 0x10)) {
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                }
            }
        }
        break;
    }
}

// .text:0x472C4 size:0x234
void fn_2_472C4(s16* sel, s16* scroll, s16 count, s16 page, s16 flags) {
    s16 last;
    s32 rem;
    s16 max;
    s32 v;
    s16 step;
    s16 back;
    u8* pad;

    if (count == 0) {
        return;
    }
    if ((page == 0) | (count < page)) {
        page = count;
    }
    rem = count % page;
    if (rem != 0) {
        last = rem;
    } else {
        last = page;
    }
    if (flags & 4) {
        max = count - last;
    } else {
        max = count - page;
    }
    pad = (u8*)&lbl_803C77B8;
    pad += lbl_2_bss_1A824C[0]->port * sizeof(MenuPad);
    switch (((MenuPad*)pad)->repeat) {
    case 0x4:
    case 0x20:
        if (!(flags & 8) && scroll != NULL && count > page) {
            v = *scroll;
            step = page - v % page;
            if (v == max) {
                if (flags & 2) {
                    *scroll = 0;
                } else {
                    *scroll = max;
                    return;
                }
            } else {
                *scroll = v = (s16)(v + step);
                if (v > max) {
                    *scroll = max;
                }
            }
            *sel = 0;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        }
        break;
    case 0x8:
    case 0x40:
        if (!(flags & 8) && scroll != NULL && count > page) {
            back = *scroll % page;
            if (back == 0) {
                back = page;
            }
            if (*scroll <= 0) {
                if (flags & 2) {
                    *scroll = max;
                    *sel = 0;
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                }
            } else {
                *scroll -= back;
                *sel = 0;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        }
        break;
    }
}

extern s32 lbl_2_data_3840[][3];
extern f32 lbl_2_data_3804[][3];
extern s32 lbl_2_data_387C[][3];

// .text:0x4AEE4 size:0x2C8
void fn_2_4AEE4(void) {
    GameInitVariables* settings = &g_d_GameSettings;
    s16 mode;
    s32 add;
    u8* menu;

    fn_2_4B2D0();
    mode = *(u8*)&lbl_2_bss_1A824C[0]->_197843;
    if ((s8)mode == 0) {
        lbl_2_bss_1A824C[0]->_19777C = lbl_2_data_3840[lbl_2_bss_1A8248[0]->_4420][settings->_3A];
        lbl_2_bss_1A824C[0]->_19777E = settings->_20[settings->_35][0] * lbl_2_data_3804[lbl_2_bss_1A8248[0]->_4420][settings->_3A];
        add = lbl_2_bss_1A824C[0]->_19777C + lbl_2_bss_1A824C[0]->_19777E;
        lbl_2_bss_1A8248[0]->_43BE = lbl_2_bss_1A8248[0]->_43BC;
        lbl_2_bss_1A8248[0]->_43BC += add;
        if (lbl_2_bss_1A8248[0]->_43BC > 999) {
            lbl_2_bss_1A8248[0]->_43BC = 999;
        }
        if (lbl_2_bss_1A8248[0]->_43BC < 0) {
            lbl_2_bss_1A8248[0]->_43BC = 0;
        }
        lbl_2_bss_1A824C[0]->_197780 = add;
        lbl_2_bss_1A824C[0]->_197798 = add;
    } else if ((s8)mode == 1) {
        add = lbl_2_data_387C[lbl_2_bss_1A8248[0]->_4420][settings->_3A];
        lbl_2_bss_1A8248[0]->_43BE = lbl_2_bss_1A8248[0]->_43BC;
        lbl_2_bss_1A8248[0]->_43BC += add;
        if (lbl_2_bss_1A8248[0]->_43BC > 999) {
            lbl_2_bss_1A8248[0]->_43BC = 999;
        }
        if (lbl_2_bss_1A8248[0]->_43BC < 0) {
            lbl_2_bss_1A8248[0]->_43BC = 0;
        }
        lbl_2_bss_1A824C[0]->_197782 = add;
        lbl_2_bss_1A824C[0]->_197798 = add;
    } else if ((s8)mode == 2) {
        lbl_2_bss_1A824C[0]->_197796 = 0;
        lbl_2_bss_1A824C[0]->_197798 = 0;
    }
    menu = (u8*)lbl_2_bss_1A8248[0] + lbl_2_bss_1A8248[0]->_4420;
    if ((s8)menu[offsetof(MenuCtx, _44F8)] > 0) {
        menu[offsetof(MenuCtx, _44F8)] = menu[offsetof(MenuCtx, _44F8)] - 1;
    }
    if (lbl_2_bss_1A824C[0]->_197843 == 0 &&
        !(lbl_2_bss_1A8248[0]->_4428 & (1 << lbl_2_bss_1A8248[0]->_4420))) {
        lbl_2_bss_1A8248[0]->_4423++;
        lbl_2_bss_1A8248[0]->_4428 |= 1 << lbl_2_bss_1A8248[0]->_4420;
    }
}

#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"
extern void fn_2_8D024(void);
extern Vec lbl_2_data_12EA8;
extern Vec lbl_2_data_12EB4;
extern const f32 lbl_2_rodata_950;
extern const f32 lbl_2_rodata_954;
extern const f32 lbl_2_rodata_958;
extern const f32 lbl_2_rodata_95C;
extern const f32 lbl_2_rodata_960;
extern const f32 lbl_2_rodata_964;
extern const f32 lbl_2_rodata_968;
extern const f32 lbl_2_rodata_96C;
extern const f32 lbl_2_rodata_970;


static inline void attachModel(ShapeAnimPlayer* sub, ActorObject* dst) {
    ShapeAnimState* q = &sub->state;
    if (q != NULL) {
        q->speed = lbl_2_rodata_970;
    }
    if (q != NULL) {
        q->active = 1;
    }
    fn_80024DB0(q);
    fn_80024FA4((ShapeModel**)dst, (ShapeData*)sub->model, &sub->state, -1);
}

// .text:0x47CFC size:0x2FC
void fn_2_47CFC(void) {
    ActorObject* c;
    CharParts* o;
    CharActor* p;
    s32 i;
    s32 j;
    Mtx44 proj;
    Vec scale;
    CharMgr* base;

    C_MTXFrustum(proj, lbl_2_rodata_950, lbl_2_rodata_954, lbl_2_rodata_958, lbl_2_rodata_95C, lbl_2_rodata_960, lbl_2_rodata_964);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_2_8D024();
    base = &lbl_8036E548;
    for (i = 0; i < lbl_2_bss_1A824C[0]->_197746; i++) {
        p = &base->actors[i];
        c = &base->slots->objects[i];
        c->animateBones = p->mode[0] & 1;
        CTRLSetTranslation((Control*)&c->worldControl, p->pos.x, p->pos.y, p->pos.z);
        CTRLSetRotation((Control*)&c->worldControl, lbl_2_rodata_968 * p->rot.x, lbl_2_rodata_968 * p->rot.y, lbl_2_rodata_968 * p->rot.z);
        if (lbl_2_bss_1A824C[0]->_197848 == 0) {
            memcpy(&scale, &lbl_2_data_12EA8, sizeof(Vec));
            if (lbl_2_bss_1A8248[0]->_441C == 5 && i == 0) {
                PSVECScale(&scale, lbl_2_rodata_96C, &scale);
                CTRLSetScale((Control*)&c->worldControl, scale.x, scale.y, scale.z);
            } else {
                CTRLSetScale((Control*)&c->worldControl, scale.x, scale.y, scale.z);
            }
        } else {
            memcpy(&scale, &lbl_2_data_12EB4, sizeof(Vec));
            CTRLSetScale((Control*)&c->worldControl, scale.x, scale.y, scale.z);
        }
        c->unk54 = lbl_2_rodata_970;
        c->setSpeed = 1;
        o = p->parts;
        if (o != NULL) {
            ShapeAnimPlayer* sub = &o->part[0].player;
            if (sub->set != NULL && o->part[1].player.set != NULL && o->_CC != 0) {
                attachModel(sub, &base->partSlots->objects[o->part[0].slot]);
                attachModel(&p->parts->part[1].player, &base->partSlots->objects[p->parts->part[1].slot]);
            }
        }
    }
    fn_2_47B24(&base->slots->count);
}

#include "Dolphin/gx.h"
extern f32 lbl_2_rodata_98C;
extern f32 lbl_2_rodata_990;

// .text:0x487A0 size:0x23C
void fn_2_487A0(void) {
    s32 i;
    s32 j;
    f32 z;
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetColorUpdate(GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, (GXLogicOp)3);
    for (i = -24; i < 25; i++) {
        z = i;
        GXBegin(GX_LINES, GX_VTXFMT0, 4);
        GXWGFifo.f32 = *(volatile f32*)&lbl_2_rodata_98C;
        GXWGFifo.f32 = *(volatile f32*)&lbl_2_rodata_94C;
        GXWGFifo.f32 = z;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xC8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_2_rodata_990;
        GXWGFifo.f32 = *(volatile f32*)&lbl_2_rodata_94C;
        GXWGFifo.f32 = z;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xC8;
        GXWGFifo.f32 = z;
        GXWGFifo.f32 = *(volatile f32*)&lbl_2_rodata_94C;
        GXWGFifo.f32 = *(volatile f32*)&lbl_2_rodata_98C;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xC8;
        GXWGFifo.f32 = z;
        GXWGFifo.f32 = *(volatile f32*)&lbl_2_rodata_94C;
        GXWGFifo.f32 = *(volatile f32*)&lbl_2_rodata_990;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xC8;
    }
}

extern void fn_2_6A87C(void);
extern void fn_2_9007C(void);
extern void fn_80052968(void);
extern MenuCamera lbl_2_bss_1A81D4; // menus/rep_10C0.h

// .text:0x47FF8 size:0x1C0
void fn_2_47FF8(void) {
    Mtx44 proj;
    u8 mode;

    C_MTXFrustum(proj, lbl_2_rodata_950, lbl_2_rodata_954, lbl_2_rodata_958, lbl_2_rodata_95C, lbl_2_rodata_960, lbl_2_rodata_964);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_2_48D54();
    if (lbl_2_bss_1A824C[0]->_19784A != 0) {
        mode = lbl_2_bss_1A824C[0]->_197846;
        if (mode == 1) {
            if (lbl_2_bss_1A824C[0]->_197847 == 0) {
                fn_2_6A87C();
            } else {
                fn_2_6A87C();
                fn_2_93BF8(&lbl_2_bss_1A81D4);
            }
        } else if (mode == 2) {
            fn_2_9007C();
        } else {
            fn_2_93BF8(&lbl_2_bss_1A81D4);
        }
    } else {
        fn_2_93BF8(&lbl_2_bss_1A81D4);
    }
    memcpy(&fn_80052768_getCamera(0)->eye, &lbl_2_bss_1A81D4.pos, sizeof(Vec));
    memcpy(&fn_80052768_getCamera(0)->target, &lbl_2_bss_1A81D4.target, sizeof(Vec));
    fn_80052768_getCamera(0)->zoom = lbl_2_bss_1A81D4.fov;
    PSMTXCopy(lbl_2_bss_1A81D4.view, fn_80052768_getCamera(0)->view);
    fn_80052968();
}

extern Vec lbl_2_data_13304;
extern Vec lbl_2_data_13310;

// .text:0x48A1C size:0x1C4
void fn_2_48A1C(void) {
    f32 x;
    f32 z;
    Vec position;
    Vec direction;
    MenuData* menu = lbl_2_bss_1A824C[0];
    CharActor* parameters = &lbl_8036E548.actors[menu->_19769C];
    memcpy(&position, &parameters->pos, sizeof(Vec));
    PSVECSubtract(&position, &lbl_2_data_13310, &direction);
    x = direction.x * lbl_2_rodata_9A0;
    z = direction.z * lbl_2_rodata_9A0;
    direction.x = x;
    direction.z = z;
    position.x += ((s8*)((u8*)&lbl_803C77B8 + offsetof(MenuPad, stickX)))[lbl_2_bss_1A824C[0]->port * sizeof(MenuPad)] / 768.0f;
    position.z += ((s8*)((u8*)&lbl_803C77B8 + offsetof(MenuPad, stickY)))[lbl_2_bss_1A824C[0]->port * sizeof(MenuPad)] / 768.0f;
    if (0.0f != x || 0.0f != z) {
        lbl_2_bss_55BC = fn_2_4A1E8(direction.z, x);
    }
    memcpy(&lbl_2_data_13310, &parameters->pos, sizeof(Vec));
    parameters->pos.x = position.x;
    parameters->pos.y = position.y;
    parameters->pos.z = position.z;
    parameters->rot.x = lbl_2_data_13304.x;
    parameters->rot.y = lbl_2_bss_55BC;
    parameters->rot.z = lbl_2_data_13304.z;
}

#include "main/file_8000F150.h" // TextSystem lbl_80366B18

// .text:0x4906C size:0x110
void fn_2_4906C(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 15; i++) {
        // = msgs[i] = tables[_1972B8]->msgs[i], spelled so that it matches
        ((u16**)lbl_2_bss_1A824C[0])[i + (s32)(offsetof(MenuData, msgs) / sizeof(u16*))] =
            ((u16**)((u8*)lbl_80366B18.tables[lbl_2_bss_1A824C[0]->_1972B8] + offsetof(MsgTable, msgs)))[i];
    }
}

extern MenuAsset lbl_2_data_12EC0[];


// .text:0x477C0 size:0x134
void fn_2_477C0(void) {
    u32 max = 0;
    u32 v;
    s32 i;
    s32 j;
    s32 size;
    u8* buf;
    for (i = 0; i < 54; i++) {
        j = i * 19;
        v = lbl_2_data_12EC0[j].sizeFlags & 0x0FFFFFFF;
        if (max < v) max = v;
    }
    size = (max + 0x1F) & ~0x1F;
    buf = _OSAllocFromHeap(0x20, size * 4);
    lbl_8036E548.fileBuf = buf;
    for (i = 0; i < 4; i++) {
        lbl_8036E548.actors[i].files = (void**)buf;
        buf += size;
    }
}

// .text:0x47540 size:0x23C
// NONMATCHING 98.7%: same instructions; volatile register assignment of the four maxima and the saved regs of the aligned sizes differ (decl permutations tried)
#if NONMATCHING
void fn_2_47540(void) {
    u32 max2 = 0;
    u32 max3 = 0;
    u32 max0 = 0;
    u32 max1 = 0;
    u32 size;
    u32 s1;
    u32 s3;
    u32 s2;
    u32 s0;
    s32 k;
    s32 m;
    u8* p;
    MenuAsset* f;

    for (k = 0; k < 4; k++) {
        f = &lbl_2_data_12EC0[k * 19];
        size = f[4].sizeFlags & 0x0FFFFFFF;
        if (max0 < size) max0 = size;
        size = f[3].sizeFlags & 0x0FFFFFFF;
        if (max1 < size) max1 = size;
        size = f[5].sizeFlags & 0x0FFFFFFF;
        if (max2 < size) max2 = size;
        size = f[2].sizeFlags & 0x0FFFFFFF;
        if (max3 < size) max3 = size;
    }
    s1 = (max1 + 0x1F) & ~0x1F;
    s2 = (max2 + 0x1F) & ~0x1F;
    s3 = (max3 + 0x1F) & ~0x1F;
    s0 = (max0 + 0x1F) & ~0x1F;
    lbl_8036E548.bankSize[2] = s0;
    lbl_8036E548.bankSize[1] = s1;
    lbl_8036E548.bankSize[3] = s2;
    lbl_8036E548.bankSize[0] = s3;
    p = _OSAllocFromHeap(0x20, (s0 + (s1 + s2 + s3)) * 4);
    lbl_8036E548._2C88 = p;
    for (m = 0; m < 4; m++) {
        lbl_8036E548.bankSets[m][0] = p;
        p += s0;
        lbl_8036E548.bankSets[m][1] = p;
        p += s1;
        lbl_8036E548.bankSets[m][2] = p;
        p += s2;
        lbl_8036E548.bankSets[m][3] = p;
        p += s3;
        lbl_8036E548.actors[m].banks.b[0] = NULL;
        lbl_8036E548.actors[m].banks.b[3] = NULL;
        lbl_8036E548.actors[m].banks.b[4] = NULL;
        lbl_8036E548.actors[m].banks.b[1] = NULL;
        lbl_8036E548.actors[m].banks.b[2] = NULL;
    }
}
#endif
extern void fn_80023B04(s32);
extern void fn_80014204(s32);
extern void* fn_80023AA4(void);

// .text:0x478F4 size:0x208
void fn_2_478F4(void) {
    s32 i;
    fn_2_477C0();
    fn_2_47540();
    fn_80023B04(0xD);
    fn_80014204(4);
    lbl_8036E548.partSlots = fn_80023AA4();
    for (i = 0; i < 4; i++) {
        lbl_8036E548.actors[i].modelIndex = i;
        lbl_8036E548.active[i] = NULL;
        lbl_8036E548._2D6A[i] = -1;
        *(s8*)&lbl_8036E548.actors[i].roster = -1;
    }
    for (i = 0; i < 9; i++) {
        lbl_8036E548._2D7F[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        lbl_8036E548.bankOwner[i] = -1;
    }
    lbl_8036E548.state = 0;
    lbl_8036E548._2D7A[1] = 0;
    lbl_8036E548._2D7C = 0;
}

// .text:0x49F7C size:0xE8
// NONMATCHING 89%: original places the copy loop's pointer init after the final blr (out-of-line preheader, docs/patterns/unsolved.md); a goto layout gets within one extra blr
#if NONMATCHING
u16* fn_2_49F7C(u16* string, s32 capacity, u16 character, s32 position) {
    s32 length = fn_2_4A068(string);
    s32 i;
    u16* p;
    if (length < position || character == 0x4000 || length + 2 > capacity) {
        return NULL;
    }
    p = &string[length];
    for (i = length; i >= position; i--) {
        p[1] = p[0];
        p--;
    }
    string[position] = character;
    return string;
}
#endif

extern void starMissionRelated2(void);

// .text:0x4AB1C size:0x1DC
// NONMATCHING 89%: the original keeps the dead clamp of lbl_80353A90.scores[0/1][0] to 0..99 (13 insns); every form we tried lets CW drop it
#if NONMATCHING
void fn_2_4AB1C(void) {
    s32 mode;
    s32 hits;
    s32 runs;
    MenuCtx* menu;

    fn_2_4B2D0();
    hits = lbl_80353A90.scores[0][0];
    runs = lbl_80353A90.scores[1][0];
    if (hits < 0) hits = 0;
    if (hits > 99) hits = 99;
    if (runs > 99) runs = 99;
    mode = *(u8*)&lbl_2_bss_1A824C[0]->_197843;
    if ((s8)mode == 0) {
        lbl_2_bss_1A824C[0]->_197756[12] = 0;
        lbl_2_bss_1A824C[0]->_197772 = 0;
        lbl_2_bss_1A824C[0]->_197776 = 0;
        lbl_2_bss_1A824C[0]->_197798 = lbl_2_bss_1A824C[0]->_197756[12] + lbl_2_bss_1A824C[0]->_197772 + lbl_2_bss_1A824C[0]->_197776;
    } else if ((s8)mode == 1) {
        lbl_2_bss_1A824C[0]->_197756[13] = 0;
        lbl_2_bss_1A824C[0]->_197774 = 0;
        lbl_2_bss_1A824C[0]->_197798 = lbl_2_bss_1A824C[0]->_197756[13] +
            lbl_2_bss_1A824C[0]->_197774;
    } else if ((s8)mode == 2) {
        lbl_2_bss_1A824C[0]->_197796 = 0;
        lbl_2_bss_1A824C[0]->_197798 = 0;
    }
    menu = lbl_2_bss_1A8248[0];
    if (menu->_441C != 5 || (s8)menu->_44EF != 1) {
        if (!(menu->_4427 & (1 << menu->_441E))) {
            menu->_4427 |= (1 << menu->_441E);
        }
    }
    if (lbl_2_bss_1A824C[0]->_197843 == 0) {
        menu = lbl_2_bss_1A8248[0];
        if (menu->_441C == 5 && (s8)menu->_44EF == 1) {
            menu->_4422++;
        } else if (!(menu->_4426 & (1 << menu->_441E))) {
            menu->_4422++;
            lbl_2_bss_1A8248[0]->_4426 |= (1 << lbl_2_bss_1A8248[0]->_441E);
        }
    }
    starMissionRelated2();
}
#endif

struct Light;
void LITAlloc(struct Light** light);
void LITInitColor(struct Light* light, GXColor* color);
void LITInitDir(struct Light* light, f32 x, f32 y, f32 z);
void LITInitPos(struct Light* light, f32 x, f32 y, f32 z);
void LITInitAttn(struct Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
extern const GXColor lbl_2_rodata_938;
extern const GXColor lbl_2_rodata_93C;
extern const GXColor lbl_2_rodata_940[2];

extern const f32 lbl_2_rodata_960;
extern const f32 lbl_2_rodata_974;
extern const f32 lbl_2_rodata_978;
extern const f32 lbl_2_rodata_97C;
extern const f32 lbl_2_rodata_980;
extern const f32 lbl_2_rodata_984;
extern const f32 lbl_2_rodata_988;

// .text:0x48DB4 size:0x2B8
// Set up the four menu lights.
// NONMATCHING 93%: same instructions; prologue scheduling of the GXColor copies and the LITInitAttn 1.0/0.0 load order (docs/patterns/unsolved.md, rep_74A0 (a))
#if NONMATCHING
void fn_2_48DB4(void) {
    GXColor color2 = lbl_2_rodata_938;
    GXColor color1 = lbl_2_rodata_93C;
    GXColor color0 = lbl_2_rodata_940[0];
    GXColor c0;
    GXColor c1;
    GXColor c2;
    GXColor c3;

    LITAlloc((struct Light**)&lbl_8036E548.lights[0]);
    LITAlloc((struct Light**)&lbl_8036E548.lights[1]);
    LITAlloc((struct Light**)&lbl_8036E548.lights[2]);
    LITAlloc((struct Light**)&lbl_8036E548.lights[3]);

    LITInitAttn(lbl_8036E548.lights[0], lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(lbl_8036E548.lights[0], lbl_2_rodata_974, lbl_2_rodata_978, lbl_2_rodata_97C);
    LITInitDir(lbl_8036E548.lights[0], lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    c0 = color0;
    LITInitColor(lbl_8036E548.lights[0], &c0);
    LITInitDir(lbl_8036E548.lights[0], lbl_2_rodata_980, lbl_2_rodata_978, lbl_2_rodata_97C);

    LITInitAttn(lbl_8036E548.lights[1], lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(lbl_8036E548.lights[1], lbl_2_rodata_980, lbl_2_rodata_984, lbl_2_rodata_988);
    LITInitDir(lbl_8036E548.lights[1], lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    c1 = color1;
    LITInitColor(lbl_8036E548.lights[1], &c1);

    LITInitAttn(lbl_8036E548.lights[2], lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(lbl_8036E548.lights[2], lbl_2_rodata_94C, lbl_2_rodata_978, lbl_2_rodata_97C);
    LITInitDir(lbl_8036E548.lights[2], lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    c2 = color2;
    LITInitColor(lbl_8036E548.lights[2], &c2);

    LITInitAttn(lbl_8036E548.lights[3], lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(lbl_8036E548.lights[3], lbl_2_rodata_94C, lbl_2_rodata_978, lbl_2_rodata_97C);
    LITInitDir(lbl_8036E548.lights[3], lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    c3 = color2;
    LITInitColor(lbl_8036E548.lights[3], &c3);
}
#endif


// .text:0x4A340 size:0x3A8
// Debug/default line score and roster setup.
// NONMATCHING 93%: register rotation in the prologue, and the original addresses lbl_8034E9A0+0x4908 directly (we get base + 0x4909 offsets)
#if NONMATCHING
void fn_2_4A340(void) {
    s32 home = g_d_GameSettings.home_AwaySetting;
    s32 away = home ^ 1;
    s32 i;
    s32 t;
    s32 p;
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    u8 homeAway2;

    g_d_GameSettings.maybeHomeAway = menu->_441C;
    homeAway2 = menu->slots[menu->entries[0].locationIndex]._5;
    lbl_80353A90.innings = 9;
    lbl_80353A90.scores[0][0] = 0;
    lbl_80353A90.scores[0][1] = 4;
    lbl_80353A90.scores[0][2] = 0;
    lbl_80353A90.scores[0][3] = 2;
    lbl_80353A90.scores[0][4] = 0;
    lbl_80353A90.scores[0][5] = 10;
    lbl_80353A90.scores[0][6] = 0;
    lbl_80353A90.scores[0][7] = 0;
    lbl_80353A90.scores[0][8] = 0;
    lbl_80353A90.scores[0][9] = 0;
    lbl_80353A90.scores[home][10] = 0;
    lbl_80353A90.scores[1][0] = 0;
    lbl_80353A90.scores[1][1] = 0;
    lbl_80353A90.scores[1][2] = 0;
    lbl_80353A90.scores[1][3] = 0;
    lbl_80353A90.scores[1][4] = 0;
    lbl_80353A90.scores[1][5] = 0;
    lbl_80353A90.scores[1][6] = 0;
    lbl_80353A90.scores[1][7] = 0;
    lbl_80353A90.scores[1][8] = 0;
    lbl_80353A90.scores[1][9] = 0;
    lbl_80353A90.scores[1][10] = 0;
    lbl_80353A90.scores[1][11] = 0;
    lbl_80353A90.scores[2 + home][0] = 0;
    lbl_80353A90.scores[2 + away][0] = 0;
    lbl_80353A90.scores[2][0] = 0;
    lbl_80353A90.scores[2][1] = 0;
    lbl_80353A90.scores[2][2] = 1;
    lbl_80353A90.scores[2][3] = 2;
    lbl_80353A90.scores[2][4] = 0;
    lbl_80353A90.scores[2][5] = 0;
    lbl_80353A90.scores[2][6] = 0;
    lbl_80353A90.scores[2][7] = 3;
    lbl_80353A90.scores[2][8] = 0;
    lbl_80353A90.scores[2][9] = 0;
    lbl_80353A90.scores[2][10] = 0;
    lbl_80353A90.scores[2][11] = 0;
    lbl_80353A90.scores[3][0] = 1;
    lbl_80353A90.scores[3][1] = 0;
    lbl_80353A90.scores[3][2] = 0;
    lbl_80353A90.scores[3][3] = 3;
    lbl_80353A90.scores[3][4] = 0;
    lbl_80353A90.scores[3][5] = 0;
    lbl_80353A90.scores[3][6] = 0;
    lbl_80353A90.scores[3][7] = 0;
    lbl_80353A90.scores[3][8] = 0;
    lbl_80353A90.scores[3][9] = 12;
    lbl_80353A90.scores[3][10] = 0;
    lbl_80353A90.scores[3][11] = 0;
    lbl_80353A90._F0[home] = 1;
    g_d_GameSettings.maybeHomeAway2 = homeAway2;
    lbl_80353A90._F0[away] = 1;

    for (i = 1; i <= lbl_80353A90.innings; i++) {
        lbl_80353A90.scores[0][0] += lbl_80353A90.scores[0][i];
        lbl_80353A90.scores[1][0] += lbl_80353A90.scores[1][i];
        lbl_80353A90.scores[2][0] += lbl_80353A90.scores[2][i];
        lbl_80353A90.scores[3][0] += lbl_80353A90.scores[3][i];
    }
    if (lbl_80353A90.scores[0][0] > lbl_80353A90.scores[1][0]) {
        lbl_80353A90.result = 0;
    } else if (lbl_80353A90.scores[0][0] < lbl_80353A90.scores[1][0]) {
        lbl_80353A90.result = 1;
    } else {
        lbl_80353A90.result = 2;
    }
    for (i = 0; i < 30; i++) {
        lbl_80353A90._A0[i] = -1;
    }

    for (i = 0; i < 3; i++) {
        lbl_8034E9A0._4908[i]._2 = 0;
        lbl_8034E9A0._4908[i]._1_lo = 1;
        lbl_8034E9A0._4908[i]._3 = 10;
        lbl_80353A90._A0[i] = i;
    }

    for (t = 0; t < 2; t++) {
        for (p = 0; p < 9; p++) {
            lbl_803537E4[t][p]._04 = (1 - t) * 12 + p * t;
            lbl_803535C8[t][p]._1A = t * 10 + p * 3;
            lbl_803537E4[t][p]._05 = t + p;
            lbl_803537E4[t][p]._18 = p;
            lbl_803537E4[t][p]._10 = p * 2;
            lbl_803535C8[t][p]._1C = 2;
            lbl_803535C8[t][p]._0A = t + p + 2;
            lbl_803537E4[t][p]._12 = t + 1;
            lbl_803535C8[t][p]._02 = 3;
        }
    }
}
#endif

extern u8* lbl_2_bss_1A823C[];


// .text:0x4A6E8 size:0x434
// Fill the result screen values (0x197766..0x19776C) for the finished challenge.
void fn_2_4A6E8(void) {
    s16 kind = *(s16*)(lbl_2_bss_1A823C[0] + 0x30);
    s32 mode;

    if (kind == 3) {
        mode = *(u8*)&lbl_2_bss_1A824C[0]->_197843;
        if ((s8)mode == 0) {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197756[12]);
            (lbl_2_bss_1A824C[0]->_197756[9]) = (lbl_2_bss_1A824C[0]->_197772);
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
        } else if ((s8)mode == 1) {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197756[13]);
            (lbl_2_bss_1A824C[0]->_197756[9]) = (lbl_2_bss_1A824C[0]->_197774);
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
        } else {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197796);
            (lbl_2_bss_1A824C[0]->_197756[9]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
        }
    } else if (kind == 5) {
        mode = *(u8*)&lbl_2_bss_1A824C[0]->_197843;
        if ((s8)mode == 0) {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_19777C);
            (lbl_2_bss_1A824C[0]->_197756[9]) = (lbl_2_bss_1A824C[0]->_19777E);
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
            lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0xE);
        } else if ((s8)mode == 1) {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197782);
            (lbl_2_bss_1A824C[0]->_197756[9]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
            lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0xF);
        } else {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197796);
            (lbl_2_bss_1A824C[0]->_197756[9]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
            lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0xF);
        }
    } else if (kind == 4) {
        mode = *(u8*)&lbl_2_bss_1A824C[0]->_197843;
        if ((s8)mode == 0) {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197778);
            (lbl_2_bss_1A824C[0]->_197756[9]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
        } else if ((s8)mode == 1) {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_19777A);
            (lbl_2_bss_1A824C[0]->_197756[9]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
        } else {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197796);
            (lbl_2_bss_1A824C[0]->_197756[9]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
        }
    } else {
        mode = *(u8*)&lbl_2_bss_1A824C[0]->_197843;
        if ((s8)mode == 0) {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197792);
            (lbl_2_bss_1A824C[0]->_197756[9]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
            lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0xE);
        } else if ((s8)mode == 1) {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197794);
            (lbl_2_bss_1A824C[0]->_197756[9]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
            lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0xF);
        } else {
            (lbl_2_bss_1A824C[0]->_197756[8]) = (lbl_2_bss_1A824C[0]->_197796);
            (lbl_2_bss_1A824C[0]->_197756[9]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[10]) = 10000;
            (lbl_2_bss_1A824C[0]->_197756[11]) = (lbl_2_bss_1A824C[0]->_197798);
            lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0xF);
        }
    }
}

#undef RESULT_S16

extern MenuSceneTask* lbl_803CC1B8;
extern s32 fn_80016710(u8 kind, s32 index);
extern void fn_2_93C64(void);

// .text:0x481F4 size:0x5AC
// Menu character viewer: set everything up (state 0), then wait for the
// requested character to load and reset its transform (state 1).
// NONMATCHING 92%: the original inlines fn_2_48DB4 and fn_2_478F4 (fn_2_48DB4 is equivalent-only)
#if NONMATCHING
void fn_2_481F4(void) {
    MenuSceneTask* task = lbl_803CC1B8;
    CharActor* actor;

    switch (lbl_2_bss_55C0.viewerState) {
    case 0:
        lbl_2_bss_1A824C[0]->heapLo = lbl_803C7898.lo;
        lbl_2_bss_1A824C[0]->heapHi = lbl_803C7898.hi;
        fn_2_48DB4();
        fn_2_93C64();
        fn_2_478F4();
        lbl_8036E548.state = 0;
        lbl_2_bss_55C0.viewerState = 1;
        break;
    case 1:
        if (fn_80016710(lbl_2_bss_1A8248[0]->_441D, task->_16)) {
            lbl_2_bss_1A824C[0]->_19769C = task->_16;
            lbl_2_bss_55C0.viewerState = 0;
            actor = &lbl_8036E548.actors[lbl_2_bss_1A824C[0]->_19769C];
            actor->pos.x = lbl_2_rodata_94C;
            actor->pos.y = lbl_2_rodata_94C;
            actor->pos.z = lbl_2_rodata_94C;
            actor->rot.x = lbl_2_rodata_94C;
            actor->rot.y = lbl_2_rodata_94C;
            actor->rot.z = lbl_2_rodata_94C;
            lbl_8036E548.state = 0;
            lbl_803CC1B8->parent->_10 = 1;
            fn_800B0A14_removeQueue(lbl_803CC1B8->parent);
        }
        break;
    }
}
#endif

#include "string.h"


// .text:0x4917C size:0xC3C
// Format a number into the static glyph string lbl_2_bss_55C0.text (copied to
// buffer if given). flags: 1 large glyphs, 4 pad with glyph spaces, 8 hex,
// 0x10 alternate font, 0x20/0x40/0x80 group with separators (3/4/2 digits).
// `style` is unused.
// NONMATCHING 78%: the original keeps the file-static bss base (lbl_2_bss_55C0 is part of this unit's .bss) in r31; inlined fn_2_49F7C layout (see there)
#if NONMATCHING
u16* fn_2_4917C(u16* buffer, s32 number, s32 flags, s32 digits, s32 style) {
    char buf[12];
    s32 count = 0;
    s32 i;
    s32 v;
    s32 d;
    char* p;
    u16* out;
    s8 c;
    MenuData* menu;

    if (flags & 0x20) {
        flags |= 4;
        if (number < 0) {
            digits = 3;
        } else {
            digits = 3;
        }
    } else if (flags & 0x40) {
        flags |= 4;
        digits = 4;
    } else if (flags & 0x80) {
        flags |= 4;
        digits = 2;
    }

    if (flags & 8) {
        if (number == 0) {
            buf[0] = ' ';
            buf[1] = ' ';
            buf[2] = ' ';
            buf[3] = ' ';
            buf[4] = ' ';
            buf[5] = ' ';
            buf[6] = ' ';
            buf[7] = '0';
            buf[8] = 0;
        } else {
            v = number;
            buf[8] = 0;
            i = 7;
            while (v != 0) {
                d = v % 16;
                if (d < 10) {
                    buf[i] = d + '0';
                } else {
                    buf[i] = d + ('a' - 10);
                }
                i--;
                v /= 16;
            }
            for (; i >= 0; i--) {
                buf[i] = ' ';
            }
        }
    } else if (number == 0) {
        for (i = 0; i < 9; i++) {
            buf[i] = ' ';
        }
        buf[9] = '0';
        buf[10] = 0;
    } else {
        i = (number < -999999999) + 10;
        buf[i] = 0;
        i--;
        v = number;
        if (number < 0) {
            v = number * -1;
        }
        while (v != 0) {
            buf[i--] = v % 10 + '0';
            v /= 10;
        }
        if (number < 0) {
            if ((flags & 0x20) || (flags & 0x40) || (flags & 0x80)) {
                buf[i] = ' ';
            } else {
                buf[i] = '-';
            }
            i--;
        }
        for (; i >= 0; i--) {
            buf[i] = ' ';
        }
    }

    if (!(flags & 6)) {
        digits = 0;
    }
    p = buf + strlen(buf) - digits;
    while (p != buf && p[-1] != ' ') {
        p--;
    }

    if ((flags & 4) && (flags & 1)) {
        lbl_2_bss_55C0.space = *(lbl_2_bss_1A824C[0]->msgs[8]);
    } else if ((flags & 4) && (flags & 0x10)) {
        lbl_2_bss_55C0.space = *(lbl_2_bss_1A824C[0]->msgs[14]);
    } else if (flags & 4) {
        lbl_2_bss_55C0.space = *(lbl_2_bss_1A824C[0]->msgs[13]);
    } else if (flags & 1) {
        lbl_2_bss_55C0.space = 0x4003;
    } else {
        lbl_2_bss_55C0.space = 0x4002;
    }
    lbl_2_bss_55C0.halfSpace = (flags & 1) + 0x4002;

    menu = lbl_2_bss_1A824C[0];
    out = lbl_2_bss_55C0.text;
    while ((c = *p) != 0) {
        if (c == ' ') {
            *out = lbl_2_bss_55C0.space;
        } else if (c == '-') {
            if (flags & 0x10) {
                *out = *(menu->msgs[12]);
            } else if (flags & 1) {
                *out = *(menu->msgs[11]);
            } else {
                *out = *(menu->msgs[12]);
            }
        } else if (c >= '0' && c <= '9') {
            if (flags & 0x10) {
                *out = (menu->msgs[14])[c - '0'];
            } else if (flags & 1) {
                *out = (menu->msgs[8])[c - '0'];
            } else {
                *out = (menu->msgs[13])[c - '0'];
            }
        } else if (flags & 0x10) {
            *out = (menu->msgs[14])[c - 'a' + 12];
        } else if (flags & 1) {
            *out = (menu->msgs[6])[c - 'a'];
        } else {
            *out = (menu->msgs[9])[c - 'a'];
        }
        out++;
        count++;
        p++;
    }
    lbl_2_bss_55C0.text[count] = 0x4000;

    if (flags & 0x10) {
        lbl_2_bss_55C0.space = (lbl_2_bss_1A824C[0]->msgs[14])[10];
    } else if (flags & 1) {
        lbl_2_bss_55C0.space = (lbl_2_bss_1A824C[0]->msgs[13])[10];
    } else {
        lbl_2_bss_55C0.space = (lbl_2_bss_1A824C[0]->msgs[13])[10];
    }
    if (flags & 0x10) {
        lbl_2_bss_55C0.minus = *(lbl_2_bss_1A824C[0]->msgs[12]);
    } else if (flags & 1) {
        lbl_2_bss_55C0.minus = *(lbl_2_bss_1A824C[0]->msgs[11]);
    } else {
        lbl_2_bss_55C0.minus = *(lbl_2_bss_1A824C[0]->msgs[12]);
    }

    if (flags & 0x20) {
        fn_2_49F7C(lbl_2_bss_55C0.text, 16, lbl_2_bss_55C0.space, count - 2);
        if (number < 0) {
            fn_2_49F7C(lbl_2_bss_55C0.text, 16, lbl_2_bss_55C0.minus, count - 4);
        }
    } else if (flags & 0x40) {
        fn_2_49F7C(lbl_2_bss_55C0.text, 16, lbl_2_bss_55C0.space, count - 3);
        if (number < 0) {
            fn_2_49F7C(lbl_2_bss_55C0.text, 16, lbl_2_bss_55C0.minus, count - 5);
        }
    } else if (flags & 0x80) {
        fn_2_49F7C(lbl_2_bss_55C0.text, 16, lbl_2_bss_55C0.space, count - 1);
        if (number < 0) {
            fn_2_49F7C(lbl_2_bss_55C0.text, 16, lbl_2_bss_55C0.minus, count - 3);
        }
    }
    if (buffer != NULL) {
        fn_2_4A094(buffer, lbl_2_bss_55C0.text);
    }
    return lbl_2_bss_55C0.text;
}
#endif

#undef NUM_GLYPHS
#undef LOOP_GLYPHS

// .data 0x12EA8-0x13460. The jump tables at the end belong to functions in auto 3C03C
// (fn_2_42708/42BE8/439D0): that text is the start of this TU.
extern void fn_2_42708(void);
extern void fn_2_42BE8(void);
extern void fn_2_439D0(void);
Vec lbl_2_data_12EA8 = {0.8f, 0.8f, 0.8f};
Vec lbl_2_data_12EB4 = {0.8f, 0.8f, 0.8f};
// ARAM load instructions of the character files, 19 per character.
// PORT: fn_2_477C0 and fn_2_47540 index this as [character * 19 + n] for all 54 characters,
// reading far past the 54 entries defined here (the original does the same).
MenuAsset lbl_2_data_12EC0[54] = {
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x400431B4, 0x0EB1D800, 0x0002B22C},
    {0x0000040B, 0x400396A0, 0x0EB49000, 0x00026ED4},
    {0x0000040B, 0x4003ED8C, 0x0EB70000, 0x00028C4C},
    {0x0000040B, 0x40036944, 0x0EB99000, 0x00022DF4},
    {0x0000040B, 0x40039B44, 0x0EBBC000, 0x00026618},
    {0x0000040B, 0x400320E4, 0x0EBE2800, 0x00021E2C},
    {0x0000040B, 0x40030878, 0x0EC04800, 0x0001DD80},
    {0x0000040B, 0x4002D3C4, 0x0EC22800, 0x0001B3EC},
    {0x0000040B, 0x40035258, 0x0EC3E000, 0x000238DC},
    {0x0000040B, 0x40041ED0, 0x0EC62000, 0x00029B84},
    {0x0000040B, 0x400414AC, 0x0EC8C000, 0x0002D160},
    {0x0000040B, 0x4002E988, 0x0ECB9800, 0x0001E0BC},
    {0x0000040B, 0x4002FED0, 0x0ECD8000, 0x0001C398},
    {0x0000040B, 0x4001FF28, 0x0ECF4800, 0x00015000},
    {0x0000040B, 0x40032CF4, 0x0ED09800, 0x0001F4E4},
    {0x0000040B, 0x40021EF4, 0x0ED29000, 0x00015114},
    {0x0000040B, 0x40038998, 0x0ED3E800, 0x00023948},
    {0x0000040B, 0x4001CE38, 0x0ED62800, 0x00011B30},
    {0x0000040B, 0x40032FDC, 0x0ED74800, 0x00021154},
    {0x0000040B, 0x4002ED24, 0x0ED96000, 0x0001E94C},
    {0x0000040B, 0x40031490, 0x0EDB5000, 0x0001F824},
    {0x0000040B, 0x40030370, 0x0EDD5000, 0x0001EB70},
    {0x0000040B, 0x40030370, 0x0EDF4000, 0x0001EB70},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x40032428, 0x0EE58000, 0x0001F020},
    {0x0000040B, 0x40036CD8, 0x0EE77800, 0x00023828},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x40029748, 0x0F08B800, 0x0001ABF4},
    {0x0000040B, 0x40029748, 0x0F08B800, 0x0001ABF4},
    {0x0000040B, 0x40029748, 0x0F08B800, 0x0001ABF4},
    {0x0000040B, 0x40029748, 0x0F08B800, 0x0001ABF4},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
    {0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8},
};
extern u8 lbl_800F5D98[];
extern u8 lbl_800F71D8[];
void* lbl_2_data_13220[2] = {lbl_800F5D98, lbl_800F71D8}; // unreferenced by code
DrawCallbackNode lbl_2_data_13228[2] = {{{2}, fn_2_487A0}, {{2}, fn_2_487A0}};
u16 lbl_2_data_13238[2] = {22, 11};
MenuAsset lbl_2_data_1323C = {0x0000040B, 0x400B2CB8, 0x18E3F000, 0x00053454};
MenuAsset lbl_2_data_1324C = {0x0000040B, 0x40076AE0, 0x18ED7000, 0x00036BC8};
MenuAsset lbl_2_data_1325C = {0x0000040B, 0x4011EC24, 0x18F0E000, 0x000D8818};
u8 lbl_2_data_1326C[112] = {
    0, 0, 4, 11, 64, 6, 157, 252, 24, 233, 40, 0, 0, 4, 8, 208,
    0, 0, 4, 11, 64, 9, 148, 124, 24, 254, 112, 0, 0, 2, 247, 88,
    0, 0, 4, 11, 64, 6, 220, 96, 25, 1, 104, 0, 0, 2, 79, 80,
    0, 0, 4, 11, 64, 10, 42, 180, 25, 3, 184, 0, 0, 3, 113, 248,
    0, 0, 4, 11, 64, 10, 151, 244, 25, 7, 48, 0, 0, 4, 142, 236,
    0, 0, 4, 11, 64, 7, 178, 208, 25, 11, 192, 0, 0, 2, 181, 32,
    0, 0, 4, 11, 64, 10, 244, 232, 25, 14, 120, 0, 0, 4, 216, 4,
};
MenuAsset lbl_2_data_132DC = {0x0000040B, 0x4023491C, 0x19135800, 0x00082928};
Vec lbl_2_data_132EC = {0.0f, 0.0f, 0.0f};
Vec lbl_2_data_132F8 = {0.0f, 0.0f, 0.0f};
Vec lbl_2_data_13304 = {0.0f, 0.0f, 0.0f};
Vec lbl_2_data_13310 = {0.0f, 0.0f, 0.0f};
DrawCallbackNode lbl_2_data_1331C = {{2}, fn_2_481B8}; // unreferenced by code
ParticleParams5 lbl_2_data_13324 = {
    NULL, 4, 20, 80000, 30000, 78000, 60, 10,
    109000, 101000, 0, 60, 12800000, 0, 0, 0,
    0xFFFFFF00, 0, 75000, 0,
}; // particle parameters (x100000 fixed point); tex is set before use
ParticleParams5* lbl_2_data_13374[1] = {&lbl_2_data_13324};

#if !NONMATCHING
// Switch jump table of fn_2_42708; mwcc emits it itself once the function matches.
void* jumptable_2_data_13378[21] = {
    (u8*)fn_2_42708 + 0x488, (u8*)fn_2_42708 + 0xC0, (u8*)fn_2_42708 + 0x488, (u8*)fn_2_42708 + 0xF4,
    (u8*)fn_2_42708 + 0x124, (u8*)fn_2_42708 + 0x154, (u8*)fn_2_42708 + 0x184, (u8*)fn_2_42708 + 0x1B4,
    (u8*)fn_2_42708 + 0x1E4, (u8*)fn_2_42708 + 0x220, (u8*)fn_2_42708 + 0x25C, (u8*)fn_2_42708 + 0x298,
    (u8*)fn_2_42708 + 0x2D4, (u8*)fn_2_42708 + 0x310, (u8*)fn_2_42708 + 0x350, (u8*)fn_2_42708 + 0x390,
    (u8*)fn_2_42708 + 0x3D0, (u8*)fn_2_42708 + 0x410, (u8*)fn_2_42708 + 0x488, (u8*)fn_2_42708 + 0x488,
    (u8*)fn_2_42708 + 0x450,
};
#endif

#if !NONMATCHING
// Switch jump table of fn_2_42BE8; mwcc emits it itself once the function matches.
void* jumptable_2_data_133CC[27] = {
    (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0xC0, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270,
    (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270,
    (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270,
    (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270,
    (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270,
    (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0x270, (u8*)fn_2_42BE8 + 0xF4, (u8*)fn_2_42BE8 + 0x270,
    (u8*)fn_2_42BE8 + 0x128, (u8*)fn_2_42BE8 + 0x164, (u8*)fn_2_42BE8 + 0x1A0,
};
#endif

#if !NONMATCHING
// Switch jump table of fn_2_439D0; mwcc emits it itself once the function matches.
void* jumptable_2_data_13438[10] = {
    (u8*)fn_2_439D0 + 0xE0, (u8*)fn_2_439D0 + 0xB4, (u8*)fn_2_439D0 + 0x14C, (u8*)fn_2_439D0 + 0x218,
    (u8*)fn_2_439D0 + 0x250, (u8*)fn_2_439D0 + 0x47C, (u8*)fn_2_439D0 + 0x128, (u8*)fn_2_439D0 + 0x2F0,
    (u8*)fn_2_439D0 + 0x3B8, (u8*)fn_2_439D0 + 0x104,
};
#endif

