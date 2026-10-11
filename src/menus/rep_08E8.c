#include "menus/rep_08E8.h"

extern MenuLineScore lbl_80353A90;
extern MenuRosterRecord lbl_803537E4[2][9];
extern MenuFieldRecord lbl_803535C8[2][9];
extern MenuSelectState lbl_8034E9A0;
#include "string.h"

extern void LITXForm(void* light, void* matrix);

#include "Dolphin/vec.h"
extern s32 fn_2_68690(s32 index);
extern void fn_2_68DAC(s32 index, void* result);
extern u32 lbl_803CBD0C[];
extern u32* lbl_2_data_13374[];
extern void fn_80031CA4(Vec*, u32*);

extern u16 lbl_2_data_13238[];

extern u8 lbl_803CBBC0[];
extern u8 lbl_2_data_13228[];
extern void fn_800A7D4C(s32, void*, u8);

extern const f32 lbl_2_rodata_9B0;

#include "static/UnknownHomes_Static.h"
#include "math.h"

extern const f32 lbl_2_rodata_94C;
extern const f32 lbl_2_rodata_9A8;
extern const f32 lbl_2_rodata_9AC;
extern const f32 lbl_2_rodata_9B4;
extern const f32 lbl_2_rodata_9A0;

extern u8 lbl_8036E548[];
extern u8* lbl_2_bss_1A8248[];

extern u8* lbl_2_bss_1A824C[];

extern void* _OSAllocFromHeap(s32 alignment, s32 size);
extern void* fn_2_4917C(void*, s32, s32, s32, s32);
extern void fn_2_513E0(void*, s32, s32, s32, s32, s32, s32, s32);

extern f32 lbl_2_bss_55B8;
extern Vec lbl_2_data_132EC;
extern Vec lbl_2_data_132F8;

// .text:0x48BE0 size:0x128
void fn_2_48BE0(void) {
    f32 x;
    f32 z;
    Vec position;
    Vec direction;
    u8* menu = lbl_2_bss_1A824C[0];
    u8* parameters = lbl_8036E548 + *(s32*)(menu + 0x19769C) * 0x27C + 0xC04;
    memcpy(&position, parameters + 0x34, sizeof(Vec));
    PSVECSubtract(&position, &lbl_2_data_132F8, &direction);
    z = direction.z * lbl_2_rodata_9A0;
    x = direction.x * lbl_2_rodata_9A0;
    direction.x = x;
    direction.z = z;
    if (lbl_2_rodata_94C != x || lbl_2_rodata_94C != z) {
        lbl_2_bss_55B8 = fn_2_4A1E8(direction.z, x);
    }
    memcpy(&lbl_2_data_132F8, parameters + 0x34, sizeof(Vec));
    *(f32*)(parameters + 0x34) = position.x;
    *(f32*)(parameters + 0x38) = position.y;
    *(f32*)(parameters + 0x3C) = position.z;
    *(f32*)(parameters + 0x40) = lbl_2_data_132EC.x;
    *(f32*)(parameters + 0x44) = lbl_2_bss_55B8;
    *(f32*)(parameters + 0x48) = lbl_2_data_132EC.z;
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
    u8* menu = lbl_2_bss_1A824C[0];
    s32 index = *(s32*)(menu + 0x19769C);
    f32* parameters = (f32*)(lbl_8036E548 + index * 0x27C + 0xC04);
    parameters[13] = lbl_2_rodata_94C;
    parameters[14] = lbl_2_rodata_94C;
    parameters[15] = lbl_2_rodata_94C;
    parameters[16] = lbl_2_rodata_94C;
    parameters[17] = lbl_2_rodata_94C;
    parameters[18] = lbl_2_rodata_94C;
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
    return end - string;
}

s32 fn_2_46D00(void) {
    u8* menu = lbl_2_bss_1A8248[0];
    if (menu[0x441C] == 5 && menu[0x4422] >= 6) return 1;
    return 0;
}

void fn_2_481B8(void) {
    u8* camera = (u8*)fn_80052768_getCamera(0);
    fn_800BD670(*(void**)(lbl_8036E548 + 0x60), (u32)(camera + 0x40));
}

// fn_2_474FC, size:0x44
void fn_2_474FC(void) {
    if (*(void**)(lbl_8036E548 + 0x2C88) != 0) {
        fn_800ACFB0(*(void**)(lbl_8036E548 + 0x2C88));
        *(void**)(lbl_8036E548 + 0x2C88) = 0;
    }
}

// fn_2_4777C, size:0x44
void fn_2_4777C(void) {
    if (*(void**)(lbl_8036E548 + 0x2C8C) != 0) {
        fn_800ACFB0(*(void**)(lbl_8036E548 + 0x2C8C));
        *(void**)(lbl_8036E548 + 0x2C8C) = 0;
    }
}

// fn_2_4A1E8, size:0x4C
f32 fn_2_4A1E8(f32 x, f32 y) {
    if (x == 0.0f && y == 0.0f) return 0.0f;
    return (f32)atan2(y, x);
}

// fn_2_4A2C4, size:0x4C
s32 fn_2_4A2C4(f32 angle) {
    if (angle < lbl_2_rodata_94C) angle = lbl_2_rodata_9A8 + angle;
    return (s32)((lbl_2_rodata_9B4 * angle) / lbl_2_rodata_9AC);
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
    *(s16*)(lbl_2_bss_1A8248[0] + 0x43BE) = *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC);
    *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) += delta;
    if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) > 999) {
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 999;
    }
    if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) < 0) {
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 0;
    }
}

// fn_2_489DC, size:0x40
void fn_2_489DC(void) {
    s32 index = lbl_803CBBC0[0];
    fn_800A7D4C(0xC, lbl_2_data_13228 + index * 8, index);
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
void fn_2_46C88(s32 index) {
    Vec position;
    fn_2_68690(0);
    fn_2_68DAC(index, &position);
    PSVECScale(&position, 2.0f, &position);
    *lbl_2_data_13374[0] = lbl_803CBD0C[0];
    fn_80031CA4(&position, lbl_2_data_13374[0]);
}

// fn_2_48D54, size:0x60
void fn_2_48D54(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        u8* camera = (u8*)fn_80052768_getCamera(0);
        LITXForm(*(void**)(lbl_8036E548 + i * 4 + 0xAC), camera + 0x40);
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
    u8* menu;

    fn_2_4B2D0();
    mode = *(u8*)(lbl_2_bss_1A824C[0] + 0x197843);
    if ((s8)mode == 0) {
        s32 add = settings->challengeMinigame_baseCoinsEarned;
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BE) = *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC);
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) += add;
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) > 999) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 999;
        }
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) < 0) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 0;
        }
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197792) = settings->challengeMinigame_baseCoinsEarned;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = settings->challengeMinigame_baseCoinsEarned;
    } else if ((s8)mode == 1) {
        s32 add = lbl_2_data_38B8;
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BE) = *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC);
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) += add;
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) > 999) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 999;
        }
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) < 0) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 0;
        }
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197794) = lbl_2_data_38B8;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = lbl_2_data_38B8;
    } else if ((s8)mode == 2) {
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197796) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = 0;
    }
    menu = lbl_2_bss_1A8248[0];
    if ((s8)menu[0x44FD] > 0) {
        menu[0x44FD] = menu[0x44FD] - 1;
    }
    if (*(s8*)(lbl_2_bss_1A824C[0] + 0x197843) == 0 && *(u8*)(lbl_2_bss_1A8248[0] + 0x4429) == 0) {
        *(u8*)(lbl_2_bss_1A8248[0] + 0x4429) = 1;
    }
}

extern void* fn_800111D8(void*);
extern void ACTSetAnimation(void*, void*, int, u16, f32, f32);
extern void Set_FUN_800b2b6c(void*, s32);
extern void fn_800B4CA0(void*, f32);
extern void fn_800B4C04(void*, f32);
extern void fn_800B4AFC(void*, s32);
extern void fn_800BDA24(void*);
extern u8* fn_80052734(s32);
extern s32 fn_800527BC(void);
extern u8 fn_800B3C04(s32, void*, void*);
extern u8* lbl_2_bss_340140;
extern const f32 lbl_2_rodata_9B0;

// .text:0x47B24 size:0x1D8
void fn_2_47B24(u16* count) {
    u8* cam;
    u8* o;
    u16 i;
    u16 j;
    u8* p;
    u8* actor;
    u8 f;
    f32 m[3][4];
    if (lbl_2_bss_340140[0x307A] != 3) {
        for (i = 0; i < *count; i++) {
            actor = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
            if (actor != NULL && actor[0x25D] != 0) {
                p = fn_800111D8(actor);
                if (*(void**)p != NULL) {
                    if (p[0x58] != 0) {
                        ACTSetAnimation(*(void**)p, *(void**)(p + 4), 0, *(u16*)(p + 0xE), lbl_2_rodata_9B0, *(f32*)(p + 0x60));
                    }
                    if (p[0x59] != 0) {
                        fn_800B4CA0(*(void**)p, *(f32*)(p + 0x5C));
                    }
                    if (p[0x5A] != 0) {
                        fn_800B4C04(*(void**)p, *(f32*)(p + 0x54));
                    }
                    f = p[0x5B];
                    if (f & 2) {
                        fn_800B4AFC(*(void**)p, (u8)(f & 1));
                    }
                    Set_FUN_800b2b6c(*(void**)p, *(s32*)(p + 0x68));
                    if (p[0x6C] != 0) {
                        fn_800BDA24(p);
                    }
                    for (j = 0; j < fn_800527BC(); j++) {
                        cam = fn_80052734(j) + 0x40;
                        PSMTXTrans(m, *(f32*)(actor + 0x34), *(f32*)(actor + 0x38), *(f32*)(actor + 0x3C));
                        PSMTXConcat((void*)cam, m, m);
                        o = *(u8**)p;
                        o[0x98] = (o[0x98] & (u8)~(3 << (j * 3))) | (fn_800B3C04(j, o, m) << (j * 3));
                    }
                    p[0x58] = 0;
                    p[0x59] = 0;
                    p[0x5A] = 0;
                    p[0x5B] = p[0x5B] & 1;
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
    pad += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
    switch (*(u16*)(pad + 4)) {
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
    pad += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
    switch (*(u16*)(pad + 4)) {
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
    mode = *(u8*)(lbl_2_bss_1A824C[0] + 0x197843);
    if ((s8)mode == 0) {
        *(s16*)(lbl_2_bss_1A824C[0] + 0x19777C) = lbl_2_data_3840[lbl_2_bss_1A8248[0][0x4420]][settings->_3A];
        *(s16*)(lbl_2_bss_1A824C[0] + 0x19777E) = settings->_20[settings->_35][0] * lbl_2_data_3804[lbl_2_bss_1A8248[0][0x4420]][settings->_3A];
        add = *(s16*)(lbl_2_bss_1A824C[0] + 0x19777C) + *(s16*)(lbl_2_bss_1A824C[0] + 0x19777E);
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BE) = *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC);
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) += add;
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) > 999) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 999;
        }
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) < 0) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 0;
        }
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197780) = add;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = add;
    } else if ((s8)mode == 1) {
        add = lbl_2_data_387C[lbl_2_bss_1A8248[0][0x4420]][settings->_3A];
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BE) = *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC);
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) += add;
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) > 999) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 999;
        }
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) < 0) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 0;
        }
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197782) = add;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = add;
    } else if ((s8)mode == 2) {
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197796) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = 0;
    }
    menu = lbl_2_bss_1A8248[0] + lbl_2_bss_1A8248[0][0x4420];
    if ((s8)menu[0x44F8] > 0) {
        menu[0x44F8] = menu[0x44F8] - 1;
    }
    if (*(s8*)(lbl_2_bss_1A824C[0] + 0x197843) == 0 &&
        !(lbl_2_bss_1A8248[0][0x4428] & (1 << lbl_2_bss_1A8248[0][0x4420]))) {
        lbl_2_bss_1A8248[0][0x4423]++;
        lbl_2_bss_1A8248[0][0x4428] |= 1 << lbl_2_bss_1A8248[0][0x4420];
    }
}

#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"
extern void CTRLSetScale(void* control, f32 x, f32 y, f32 z);
extern void CTRLSetRotation(void* control, f32 x, f32 y, f32 z);
extern void CTRLSetTranslation(void* control, f32 x, f32 y, f32 z);
extern void fn_80024DB0(void*);
extern void fn_80024FA4(void*, u32, void*, s32);
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

typedef struct { u8 b : 1; u8 r : 7; } BitFlag08E8;

static inline void attachModel(u8* sub, u8* dst) {
    u8* q = sub + 0xC;
    if (q != NULL) {
        *(f32*)(q + 4) = lbl_2_rodata_970;
    }
    if (q != NULL) {
        ((BitFlag08E8*)(q + 0x11))->b = 1;
    }
    fn_80024DB0(q);
    fn_80024FA4(dst, *(u32*)(sub + 0x2C), sub + 0xC, -1);
}

// .text:0x47CFC size:0x2FC
void fn_2_47CFC(void) {
    u8* c;
    u8* o;
    u8* p;
    s32 i;
    s32 j;
    Mtx44 proj;
    Vec scale;
    u8* base;

    C_MTXFrustum(proj, lbl_2_rodata_950, lbl_2_rodata_954, lbl_2_rodata_958, lbl_2_rodata_95C, lbl_2_rodata_960, lbl_2_rodata_964);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_2_8D024();
    base = lbl_8036E548;
    for (i = 0; i < *(s16*)(lbl_2_bss_1A824C[0] + 0x197746); i++) {
        p = base + i * 0x27C + 0xC04;
        c = *(u8**)(base + 0x60) + i * 0x90 + 0x34;
        c[0x6C] = p[0x25D] & 1;
        CTRLSetTranslation(c + 0x10, *(f32*)(p + 0x34), *(f32*)(p + 0x38), *(f32*)(p + 0x3C));
        CTRLSetRotation(c + 0x10, lbl_2_rodata_968 * *(f32*)(p + 0x40), lbl_2_rodata_968 * *(f32*)(p + 0x44), lbl_2_rodata_968 * *(f32*)(p + 0x48));
        if (lbl_2_bss_1A824C[0][0x197848] == 0) {
            memcpy(&scale, &lbl_2_data_12EA8, sizeof(Vec));
            if (lbl_2_bss_1A8248[0][0x441C] == 5 && i == 0) {
                PSVECScale(&scale, lbl_2_rodata_96C, &scale);
                CTRLSetScale(c + 0x10, scale.x, scale.y, scale.z);
            } else {
                CTRLSetScale(c + 0x10, scale.x, scale.y, scale.z);
            }
        } else {
            memcpy(&scale, &lbl_2_data_12EB4, sizeof(Vec));
            CTRLSetScale(c + 0x10, scale.x, scale.y, scale.z);
        }
        *(f32*)(c + 0x54) = lbl_2_rodata_970;
        c[0x5A] = 1;
        o = *(u8**)(p + 0x30);
        if (o != NULL) {
            c = o + 4;
            if (*(u32*)c != 0 && *(u32*)(o + 0x68) != 0 && o[0xCC] != 0) {
                attachModel(c, *(u8**)(base + 0x13C) + o[0x60] * 0x90 + 0x34);
                attachModel(*(u8**)(p + 0x30) + 0x68, *(u8**)(base + 0x13C) + (*(u8**)(p + 0x30))[0xC4] * 0x90 + 0x34);
            }
        }
    }
    fn_2_47B24(*(u16**)(base + 0x60));
}

#include "Dolphin/gx.h"
extern f32 lbl_2_rodata_98C;
extern f32 lbl_2_rodata_990;

// .text:0x487A0 size:0x23C
void fn_2_487A0(void) {
    s32 i;
    s32 j;
    f32 z;
    GXLoadPosMtxImm((MtxPtr)((u8*)fn_80052768_getCamera(0) + 0x40), GX_PNMTX0);
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
extern void fn_2_93BF8(void*);
extern void fn_80052968(void);
extern u8 lbl_2_bss_1A81D4[];

// .text:0x47FF8 size:0x1C0
void fn_2_47FF8(void) {
    Mtx44 proj;
    u8 mode;

    C_MTXFrustum(proj, lbl_2_rodata_950, lbl_2_rodata_954, lbl_2_rodata_958, lbl_2_rodata_95C, lbl_2_rodata_960, lbl_2_rodata_964);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_2_48D54();
    if (lbl_2_bss_1A824C[0][0x19784A] != 0) {
        mode = lbl_2_bss_1A824C[0][0x197846];
        if (mode == 1) {
            if (lbl_2_bss_1A824C[0][0x197847] == 0) {
                fn_2_6A87C();
            } else {
                fn_2_6A87C();
                fn_2_93BF8(lbl_2_bss_1A81D4);
            }
        } else if (mode == 2) {
            fn_2_9007C();
        } else {
            fn_2_93BF8(lbl_2_bss_1A81D4);
        }
    } else {
        fn_2_93BF8(lbl_2_bss_1A81D4);
    }
    memcpy((u8*)fn_80052768_getCamera(0) + 0x70, lbl_2_bss_1A81D4 + 0x4C, sizeof(Vec));
    memcpy((u8*)fn_80052768_getCamera(0) + 0x7C, lbl_2_bss_1A81D4 + 0x40, sizeof(Vec));
    *(f32*)((u8*)fn_80052768_getCamera(0) + 0xA4) = *(f32*)(lbl_2_bss_1A81D4 + 0x3C);
    PSMTXCopy((MtxPtr)lbl_2_bss_1A81D4, (MtxPtr)((u8*)fn_80052768_getCamera(0) + 0x40));
    fn_80052968();
}

extern f32 lbl_2_bss_55BC;
extern Vec lbl_2_data_13304;
extern Vec lbl_2_data_13310;

// .text:0x48A1C size:0x1C4
void fn_2_48A1C(void) {
    f32 x;
    f32 z;
    Vec position;
    Vec direction;
    u8* menu = lbl_2_bss_1A824C[0];
    u8* parameters = lbl_8036E548 + *(s32*)(menu + 0x19769C) * 0x27C + 0xC04;
    memcpy(&position, parameters + 0x34, sizeof(Vec));
    PSVECSubtract(&position, &lbl_2_data_13310, &direction);
    x = direction.x * lbl_2_rodata_9A0;
    z = direction.z * lbl_2_rodata_9A0;
    direction.x = x;
    direction.z = z;
    position.x += ((s8*)((u8*)&lbl_803C77B8 + 0x10))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20] / 768.0f;
    position.z += ((s8*)((u8*)&lbl_803C77B8 + 0x11))[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20] / 768.0f;
    if (0.0f != x || 0.0f != z) {
        lbl_2_bss_55BC = fn_2_4A1E8(direction.z, x);
    }
    memcpy(&lbl_2_data_13310, parameters + 0x34, sizeof(Vec));
    *(f32*)(parameters + 0x34) = position.x;
    *(f32*)(parameters + 0x38) = position.y;
    *(f32*)(parameters + 0x3C) = position.z;
    *(f32*)(parameters + 0x40) = lbl_2_data_13304.x;
    *(f32*)(parameters + 0x44) = lbl_2_bss_55BC;
    *(f32*)(parameters + 0x48) = lbl_2_data_13304.z;
}

extern u8 lbl_80366B18[];

// .text:0x4906C size:0x110
void fn_2_4906C(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 15; i++) {
        ((u32*)lbl_2_bss_1A824C[0])[i + 0x19542C / 4] =
            ((u32*)(*(u8**)(lbl_80366B18 + 0x798 + lbl_2_bss_1A824C[0][0x1972B8] * 4) + 4))[i];
    }
}

extern u8 lbl_2_data_12EC0[];


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
        v = ((Entry08E8*)lbl_2_data_12EC0)[j].size & 0x0FFFFFFF;
        if (max < v) max = v;
    }
    size = (max + 0x1F) & ~0x1F;
    buf = _OSAllocFromHeap(0x20, size * 4);
    *(u8**)(lbl_8036E548 + 0x2C8C) = buf;
    for (i = 0; i < 4; i++) {
        *(u8**)(lbl_8036E548 + i * 0x27C + 0xC0C) = buf;
        buf += size;
    }
}

// .text:0x47540 size:0x23C
// NONMATCHING ~85%: same instructions; volatile register assignment of the four maxima and the saved regs of the aligned sizes differ (decl permutations tried)
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
    Entry08E8* f;

    for (k = 0; k < 4; k++) {
        f = &((Entry08E8*)lbl_2_data_12EC0)[k * 19];
        size = f[4].size & 0x0FFFFFFF;
        if (max0 < size) max0 = size;
        size = f[3].size & 0x0FFFFFFF;
        if (max1 < size) max1 = size;
        size = f[5].size & 0x0FFFFFFF;
        if (max2 < size) max2 = size;
        size = f[2].size & 0x0FFFFFFF;
        if (max3 < size) max3 = size;
    }
    s1 = (max1 + 0x1F) & ~0x1F;
    s2 = (max2 + 0x1F) & ~0x1F;
    s3 = (max3 + 0x1F) & ~0x1F;
    s0 = (max0 + 0x1F) & ~0x1F;
    MENU_CHARMGR.bankSize[2] = s0;
    MENU_CHARMGR.bankSize[1] = s1;
    MENU_CHARMGR.bankSize[3] = s2;
    MENU_CHARMGR.bankSize[0] = s3;
    p = _OSAllocFromHeap(0x20, (s0 + (s1 + s2 + s3)) * 4);
    MENU_CHARMGR.bankBuf = p;
    for (m = 0; m < 4; m++) {
        MENU_CHARMGR.bankSets[m][0] = p;
        p += s0;
        MENU_CHARMGR.bankSets[m][1] = p;
        p += s1;
        MENU_CHARMGR.bankSets[m][2] = p;
        p += s2;
        MENU_CHARMGR.bankSets[m][3] = p;
        p += s3;
        MENU_CHARMGR.actors[m].banks[0] = NULL;
        MENU_CHARMGR.actors[m].banks[3] = NULL;
        MENU_CHARMGR.actors[m].banks[4] = NULL;
        MENU_CHARMGR.actors[m].banks[1] = NULL;
        MENU_CHARMGR.actors[m].banks[2] = NULL;
    }
}
#endif
extern void fn_80023B04(s32);
extern void fn_80014204(s32);
extern u32 fn_80023AA4(void);

// .text:0x478F4 size:0x208
void fn_2_478F4(void) {
    s32 i;
    fn_2_477C0();
    fn_2_47540();
    fn_80023B04(0xD);
    fn_80014204(4);
    *(u32*)(lbl_8036E548 + 0x13C) = fn_80023AA4();
    for (i = 0; i < 4; i++) {
        (lbl_8036E548 + i * 0x27C)[0xE59] = i;
        ((u32*)(lbl_8036E548 + 0x2C50))[i] = 0;
        ((s8*)lbl_8036E548)[0x2D6A + i] = -1;
        ((s8*)lbl_8036E548)[i * 0x27C + 0xE5B] = -1;
    }
    for (i = 0; i < 9; i++) {
        ((s8*)lbl_8036E548)[0x2D7F + i] = -1;
    }
    for (i = 0; i < 4; i++) {
        ((s8*)lbl_8036E548)[0x2D89 + i] = -1;
    }
    lbl_8036E548[0x2D77] = 0;
    lbl_8036E548[0x2D7B] = 0;
    lbl_8036E548[0x2D7C] = 0;
}

// .text:0x49F7C size:0xE8
// NONMATCHING 98%: original places the copy loop's pointer init after the final blr (out-of-line preheader, docs/patterns/unsolved.md); a goto layout gets within one extra blr
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
    u8* menu;

    fn_2_4B2D0();
    hits = lbl_80353A90.scores[0][0];
    runs = lbl_80353A90.scores[1][0];
    if (hits < 0) hits = 0;
    if (hits > 99) hits = 99;
    if (runs > 99) runs = 99;
    mode = *(u8*)(lbl_2_bss_1A824C[0] + 0x197843);
    if ((s8)mode == 0) {
        *(s16*)(lbl_2_bss_1A824C[0] + 0x19776E) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197772) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197776) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = *(s16*)(lbl_2_bss_1A824C[0] + 0x19776E) + *(s16*)(lbl_2_bss_1A824C[0] + 0x197772) + *(s16*)(lbl_2_bss_1A824C[0] + 0x197776);
    } else if ((s8)mode == 1) {
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197770) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197774) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = *(s16*)(lbl_2_bss_1A824C[0] + 0x197770) +
            *(s16*)(lbl_2_bss_1A824C[0] + 0x197774);
    } else if ((s8)mode == 2) {
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197796) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = 0;
    }
    menu = lbl_2_bss_1A8248[0];
    if (menu[0x441C] != 5 || (s8)menu[0x44EF] != 1) {
        if (!(menu[0x4427] & (1 << menu[0x441E]))) {
            menu[0x4427] |= (1 << menu[0x441E]);
        }
    }
    if (*(s8*)(lbl_2_bss_1A824C[0] + 0x197843) == 0) {
        menu = lbl_2_bss_1A8248[0];
        if (menu[0x441C] == 5 && (s8)menu[0x44EF] == 1) {
            menu[0x4422]++;
        } else if (!(menu[0x4426] & (1 << menu[0x441E]))) {
            menu[0x4422]++;
            lbl_2_bss_1A8248[0][0x4426] |= (1 << lbl_2_bss_1A8248[0][0x441E]);
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
// NONMATCHING ~93%: same instructions; prologue scheduling of the GXColor copies and the LITInitAttn 1.0/0.0 load order (docs/patterns/unsolved.md, rep_74A0 (a))
#if NONMATCHING
void fn_2_48DB4(void) {
    GXColor color2 = lbl_2_rodata_938;
    GXColor color1 = lbl_2_rodata_93C;
    GXColor color0 = lbl_2_rodata_940[0];
    GXColor c0;
    GXColor c1;
    GXColor c2;
    GXColor c3;

    LITAlloc(&MENU_CHARMGR.lights[0]);
    LITAlloc(&MENU_CHARMGR.lights[1]);
    LITAlloc(&MENU_CHARMGR.lights[2]);
    LITAlloc(&MENU_CHARMGR.lights[3]);

    LITInitAttn(MENU_CHARMGR.lights[0], lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(MENU_CHARMGR.lights[0], lbl_2_rodata_974, lbl_2_rodata_978, lbl_2_rodata_97C);
    LITInitDir(MENU_CHARMGR.lights[0], lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    c0 = color0;
    LITInitColor(MENU_CHARMGR.lights[0], &c0);
    LITInitDir(MENU_CHARMGR.lights[0], lbl_2_rodata_980, lbl_2_rodata_978, lbl_2_rodata_97C);

    LITInitAttn(MENU_CHARMGR.lights[1], lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(MENU_CHARMGR.lights[1], lbl_2_rodata_980, lbl_2_rodata_984, lbl_2_rodata_988);
    LITInitDir(MENU_CHARMGR.lights[1], lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    c1 = color1;
    LITInitColor(MENU_CHARMGR.lights[1], &c1);

    LITInitAttn(MENU_CHARMGR.lights[2], lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(MENU_CHARMGR.lights[2], lbl_2_rodata_94C, lbl_2_rodata_978, lbl_2_rodata_97C);
    LITInitDir(MENU_CHARMGR.lights[2], lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    c2 = color2;
    LITInitColor(MENU_CHARMGR.lights[2], &c2);

    LITInitAttn(MENU_CHARMGR.lights[3], lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_960, lbl_2_rodata_94C, lbl_2_rodata_94C);
    LITInitPos(MENU_CHARMGR.lights[3], lbl_2_rodata_94C, lbl_2_rodata_978, lbl_2_rodata_97C);
    LITInitDir(MENU_CHARMGR.lights[3], lbl_2_rodata_94C, lbl_2_rodata_94C, lbl_2_rodata_94C);
    c3 = color2;
    LITInitColor(MENU_CHARMGR.lights[3], &c3);
}
#endif


// .text:0x4A340 size:0x3A8
// Debug/default line score and roster setup.
// NONMATCHING ~93%: register rotation in the prologue, and the original addresses lbl_8034E9A0+0x4908 directly (we get base + 0x4909 offsets)
#if NONMATCHING
void fn_2_4A340(void) {
    s32 home = g_d_GameSettings.home_AwaySetting;
    s32 away = home ^ 1;
    s32 i;
    s32 t;
    s32 p;
    u8* menu = lbl_2_bss_1A8248[0];
    u8 homeAway2;

    g_d_GameSettings.maybeHomeAway = menu[0x441C];
    homeAway2 = menu[*(s16*)(menu + 0x16C2) * 10 + 0x40F3];
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

#define RESULT_S16(off) (*(s16*)(lbl_2_bss_1A824C[0] + (off))) // TODO type

// .text:0x4A6E8 size:0x434
// Fill the result screen values (0x197766..0x19776C) for the finished challenge.
void fn_2_4A6E8(void) {
    s16 kind = *(s16*)(lbl_2_bss_1A823C[0] + 0x30);
    s32 mode;

    if (kind == 3) {
        mode = *(u8*)(lbl_2_bss_1A824C[0] + 0x197843);
        if ((s8)mode == 0) {
            RESULT_S16(0x197766) = RESULT_S16(0x19776E);
            RESULT_S16(0x197768) = RESULT_S16(0x197772);
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
        } else if ((s8)mode == 1) {
            RESULT_S16(0x197766) = RESULT_S16(0x197770);
            RESULT_S16(0x197768) = RESULT_S16(0x197774);
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
        } else {
            RESULT_S16(0x197766) = RESULT_S16(0x197796);
            RESULT_S16(0x197768) = 10000;
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
        }
    } else if (kind == 5) {
        mode = *(u8*)(lbl_2_bss_1A824C[0] + 0x197843);
        if ((s8)mode == 0) {
            RESULT_S16(0x197766) = RESULT_S16(0x19777C);
            RESULT_S16(0x197768) = RESULT_S16(0x19777E);
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
            *(u32*)(lbl_2_bss_1A824C[0] + 0x1976A8) = fn_80062890(0xE);
        } else if ((s8)mode == 1) {
            RESULT_S16(0x197766) = RESULT_S16(0x197782);
            RESULT_S16(0x197768) = 10000;
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
            *(u32*)(lbl_2_bss_1A824C[0] + 0x1976A8) = fn_80062890(0xF);
        } else {
            RESULT_S16(0x197766) = RESULT_S16(0x197796);
            RESULT_S16(0x197768) = 10000;
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
            *(u32*)(lbl_2_bss_1A824C[0] + 0x1976A8) = fn_80062890(0xF);
        }
    } else if (kind == 4) {
        mode = *(u8*)(lbl_2_bss_1A824C[0] + 0x197843);
        if ((s8)mode == 0) {
            RESULT_S16(0x197766) = RESULT_S16(0x197778);
            RESULT_S16(0x197768) = 10000;
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
        } else if ((s8)mode == 1) {
            RESULT_S16(0x197766) = RESULT_S16(0x19777A);
            RESULT_S16(0x197768) = 10000;
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
        } else {
            RESULT_S16(0x197766) = RESULT_S16(0x197796);
            RESULT_S16(0x197768) = 10000;
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
        }
    } else {
        mode = *(u8*)(lbl_2_bss_1A824C[0] + 0x197843);
        if ((s8)mode == 0) {
            RESULT_S16(0x197766) = RESULT_S16(0x197792);
            RESULT_S16(0x197768) = 10000;
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
            *(u32*)(lbl_2_bss_1A824C[0] + 0x1976A8) = fn_80062890(0xE);
        } else if ((s8)mode == 1) {
            RESULT_S16(0x197766) = RESULT_S16(0x197794);
            RESULT_S16(0x197768) = 10000;
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
            *(u32*)(lbl_2_bss_1A824C[0] + 0x1976A8) = fn_80062890(0xF);
        } else {
            RESULT_S16(0x197766) = RESULT_S16(0x197796);
            RESULT_S16(0x197768) = 10000;
            RESULT_S16(0x19776A) = 10000;
            RESULT_S16(0x19776C) = RESULT_S16(0x197798);
            *(u32*)(lbl_2_bss_1A824C[0] + 0x1976A8) = fn_80062890(0xF);
        }
    }
}

#undef RESULT_S16

extern u8 lbl_2_bss_55C0;
extern u32 lbl_803C7898[];
extern MenuSceneTask* lbl_803CC1B8;
extern s32 fn_80016710(u8 kind, s32 index);
extern void fn_2_93C64(void);

// .text:0x481F4 size:0x5AC
// Menu character viewer: set everything up (state 0), then wait for the
// requested character to load and reset its transform (state 1).
// NONMATCHING: the original inlines fn_2_48DB4 and fn_2_478F4 (both equivalent-only)
#if NONMATCHING
void fn_2_481F4(void) {
    MenuSceneTask* task = lbl_803CC1B8;
    MenuCharActor* actor;

    switch (lbl_2_bss_55C0) {
    case 0:
        *(u32*)(lbl_2_bss_1A824C[0] + 0x195424) = lbl_803C7898[1]; // TODO type
        *(u32*)(lbl_2_bss_1A824C[0] + 0x195428) = lbl_803C7898[2];
        fn_2_48DB4();
        fn_2_93C64();
        fn_2_478F4();
        lbl_8036E548[0x2D77] = 0;
        lbl_2_bss_55C0 = 1;
        break;
    case 1:
        if (fn_80016710(lbl_2_bss_1A8248[0][0x441D], task->_16)) {
            *(s32*)(lbl_2_bss_1A824C[0] + 0x19769C) = task->_16;
            lbl_2_bss_55C0 = 0;
            actor = &MENU_CHARMGR.actors[*(s32*)(lbl_2_bss_1A824C[0] + 0x19769C)];
            actor->pos.x = lbl_2_rodata_94C;
            actor->pos.y = lbl_2_rodata_94C;
            actor->pos.z = lbl_2_rodata_94C;
            actor->rot.x = lbl_2_rodata_94C;
            actor->rot.y = lbl_2_rodata_94C;
            actor->rot.z = lbl_2_rodata_94C;
            lbl_8036E548[0x2D77] = 0;
            lbl_803CC1B8->parent->_10 = 1;
            fn_800B0A14_removeQueue(lbl_803CC1B8->parent);
        }
        break;
    }
}
#endif
