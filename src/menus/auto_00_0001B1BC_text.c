#include "menus/auto_00_0001B1BC_text.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "menus/menu_work.h"
#include "main/file_80011640.h"

extern MenuData* lbl_2_bss_1A8234[];
extern MenuData* lbl_2_bss_1A824C[];
extern MenuCtx* lbl_2_bss_1A8248;
extern MenuFlags* lbl_2_bss_1A823C[];
extern MenuScreenTask* lbl_803CC1B8;
extern void fn_2_409CC(void);
extern s32 fn_2_4EB2C(void);
extern s32 fn_2_4EAF4(void);
extern s32 fn_2_4E9A8(void);
extern u8 lbl_800EF808[];
extern void fn_2_8EA80(void);
extern void fn_2_8E478(void);
extern void fn_2_47CFC(void);
extern void fn_2_8AEE0(void);
extern void fn_2_8ACB0(s32, s32);
extern void fn_2_68FBC(s32, s32);
extern void fn_2_8CCAC(s32, u8);
extern u8 lbl_80366B18[];
extern void fn_2_68DAC(s32 index, void* result);
extern void fn_80068720(s32);
extern void fn_8001F228(void);
extern s32 fn_80021410(void);
extern void fn_2_54474(void);
extern MenuDrawArea* lbl_2_bss_1A8230[];
extern MenuEntry* lbl_2_bss_1A8238;
extern MenuProgress* lbl_2_bss_1A8244;
extern CharMgr* lbl_2_bss_340140;
extern u8 starMissionCompletionTracker[];
extern MenuFlags lbl_800E877C;
extern MenuProgress lbl_80361B20;
extern u8 lbl_803CB8F0[];
extern GXColor lbl_2_data_4BA8;
extern void fn_8000F4B8(s32 a, s32 b, s32 c, s32 d);
extern void fn_8006C488(void);
extern void fn_8006877C(u8 track);
extern void fn_800216F8(u8 group, s32 (*callback)(u8* state));
extern s32 fn_800627F8(u8* state);
extern s32 fn_2_20CB0(u32 index);
extern void fn_2_207FC(void);
extern void fn_2_20328(void);
extern void fn_2_20D08(void);
extern void fn_2_2460C(void);
extern void fn_2_37460(void);
extern void fn_2_379D0(void);
extern void fn_2_37D98(void);
extern void fn_2_40A9C(void);
extern void fn_2_454E8(void);
extern void fn_2_46418(void);
extern void fn_2_466AC(void);
extern void fn_2_467FC(void);
extern void fn_2_468DC(void);
extern void fn_2_4AB1C(void);
extern s32 fn_2_46D00(void);
extern void fn_2_46D94(s16* sel, s16* scroll, s16 count, s16 page, u32 flags);
extern s32 fn_8006CDC0(s32 team);
extern s32 fn_2_44E2C(s32 ch);

// lbl_800E8558 entries (see StarMissionIndex in main/file_80024184.h).
typedef struct MissionIndex {
    /*0x0*/ u8 _0[2];
    /*0x2*/ u8 missionRow; // row in lbl_80109AE8
    /*0x3*/ u8 hasMissions;
    /*0x4*/ u8 _4[2];
} MissionIndex;
extern MissionIndex lbl_800E8558[54];

// lbl_80109AE8[row][10] (see StarMission in main/file_80024184.h).
typedef struct MissionDef {
    /*0x0*/ s16 type; // -1: unused slot
    /*0x2*/ u8 _2[8];
} MissionDef;
extern MissionDef lbl_80109AE8[][10];

#define MENU_PADS ((MenuPad*)&lbl_803C77B8)
#define MENU_PAD_REPEAT(port) (*(u16*)((u8*)&lbl_803C77B8._04 + (port) * 0x20))
#define MENU_PAD_DOWN(port) (*(u16*)((u8*)&lbl_803C77B8._02 + (port) * 0x20))

#define ROSTER (lbl_2_bss_1A8248->chars)
#define ROSTER_LIMIT(e) ((e)->limits[lbl_2_bss_1A8248->_4415 * 6 + lbl_2_bss_1A8248->_441C + 4])
extern void fn_8004B1B8(void* tex);
extern u8 lbl_803C6CF8[];

// Archive loaded from ARAM by fn_2_1B1BC (lbl_2_bss_1034C).
typedef struct MenuArchive {
    /*0x0*/ u8 _0[4];
    /*0x4*/ void* first; // entry 0 (texture archive) after relocation
    /*0x8*/ u32* data; // offset table; entries are relocated in place
} MenuArchive;
extern MenuArchive* lbl_2_data_4BA0;
extern u8 lbl_2_bss_1034C[];
extern u8 lbl_2_data_4B90[]; // ARAM load instructions
extern MenuData lbl_2_bss_1A8250; // menu work buffer that lbl_2_bss_1A824C points at
extern u8 lbl_8034E9A0[];
extern void* memset(void*, int, unsigned long);

// NONMATCHING 87%: the original keeps the relocation loop (count 1, index 0) as a real loop; CW folds and unrolls ours
#if NONMATCHING
// Turn the first `count` offsets of an archive into pointers; returns entry `index`.
static inline void* relocateArchive(u32* data, s32 index, s32 count) {
    void* entry = (u8*)data + data[index];
    u32* p = data + count;
    while (count-- != 0) {
        p--;
        *p += (u32)data; // TODO: 32-bit file offsets relocated in place
    }
    return entry;
}

// fn_2_1B1BC, size:0x158
void fn_2_1B1BC(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)(u8)o->step) {
    case 0:
        lbl_2_data_4BA0 = (MenuArchive*)lbl_2_bss_1034C;
        lbl_2_data_4BA0->data = (u32*)ARAMTransfer(lbl_2_data_4B90, 0, 0, 0);
        o->step = 1;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            o->step = 2;
        }
        break;
    case 2:
        lbl_2_data_4BA0->first = relocateArchive(lbl_2_data_4BA0->data, 0, 1);
        convertTextureHeader(lbl_2_data_4BA0->first);
        fn_8004B1B8(lbl_2_data_4BA0->first);
        o->step = 3;
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
}
#endif

// NONMATCHING 94%: register allocation and stack frame size (0x30 vs 0x40) differ; the scene-18
// sub-switch compare tree lacks one bge
#if NONMATCHING
// Same as fn_2_1A420 (auto_00_000194BC_text), inlined here.
static inline s32 starMissionBonusActive(void) {
    s32 result = 0;
    if (lbl_2_bss_1A823C[0]->mode == 3) {
        fn_2_4AB1C();
        if (lbl_2_bss_1A824C[0]->_197843 == 0) {
            if (lbl_2_bss_1A8248->_441C == 5) {
                if (fn_2_46D00() != 0) {
                    result = 1;
                }
            } else if (lbl_2_bss_1A8248->_4426 & 0x20) {
                result = 1;
            }
        }
    }
    return !!result;
}

// Start a child task and wait for it (o->_10 set to 1 when it finishes).
#define START_CHILD(func, next)                          \
    do {                                                 \
        MenuScreenTask* child = fn_800B0A5C_insertQueue(func, 2); \
        child->step = 0;                                 \
        o->signal = 0;                                   \
        lbl_2_bss_1A823C[0]->state = (next);             \
    } while (0)

#define WAIT_CHILD(next)                                 \
    if (o->signal == 1) {                                \
        lbl_2_bss_1A823C[0]->state = (next);             \
    }

// fn_2_1B7B4, size:0x79C
// Star challenge menu scene: sets up the work-area pointers and runs the scene state machine.
void fn_2_1B7B4(void) {
    MenuScreenTask* o;
    GXColor clear;

    lbl_2_bss_1A8248 = (MenuCtx*)starMissionCompletionTracker;
    o = lbl_803CC1B8;
    lbl_2_bss_1A824C[0] = &lbl_2_bss_1A8250;
    lbl_2_bss_1A8238 = ((MenuCtx*)starMissionCompletionTracker)->entries;
    lbl_2_bss_1A8244 = &lbl_80361B20;
    lbl_2_bss_1A823C[0] = &lbl_800E877C;
    lbl_2_bss_1A8234[0] = &lbl_2_bss_1A8250;
    lbl_2_bss_1A8230[0] = &lbl_2_bss_1A8250.drawArea;
    lbl_2_bss_340140 = &lbl_8036E548;

    switch (lbl_2_bss_1A823C[0]->state) {
    case 0:
        fn_8006C488();
        fn_8001F228();
        fn_2_1C0D4();
        fn_8000F4B8(0, -1, -1, -1);
        lbl_2_bss_1A823C[0]->state = 2;
        break;
    case 1:
        WAIT_CHILD(2);
        break;
    case 2:
        lbl_2_bss_1A823C[0]->state = 3;
        break;
    case 3:
        lbl_2_bss_1A823C[0]->state = 4;
        break;
    case 4:
        lbl_2_bss_1A8248->_44F4 = starMissionBonusActive();
        if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
            lbl_2_bss_1A823C[0]->state = 0xC;
        } else {
            clear = lbl_2_data_4BA8;
            GXSetCopyClear(clear, 0xFFFFFF);
            changeScene(1, 6);
            if (lbl_2_bss_1A8248->_4415 >= 3) {
                if (fn_2_4E970() == 1) {
                    lbl_2_bss_1A823C[0]->state = 5;
                }
            } else {
                lbl_2_bss_1A823C[0]->state = 0xC;
            }
        }
        break;
    case 5:
        START_CHILD(fn_2_37460, 6);
        break;
    case 6:
        WAIT_CHILD(7);
        break;
    case 7:
        lbl_2_bss_1A8234[0]->done = 0;
        lbl_2_bss_1A8230[0]->_32A86 = 0;
        fn_2_54474();
        fn_2_2460C();
        lbl_2_bss_1A823C[0]->state = 8;
        break;
    case 8:
        fn_8006877C(0xD);
        START_CHILD(fn_2_37D98, 9);
        break;
    case 9:
        WAIT_CHILD(0xA);
        break;
    case 10:
        START_CHILD(fn_2_40A9C, 0xB);
        break;
    case 11:
        WAIT_CHILD(0xC);
        break;
    case 12:
        if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
            START_CHILD(fn_2_1B6CC, 0xD);
        } else {
            START_CHILD(fn_2_1B5C0, 0xD);
        }
        break;
    case 13:
        WAIT_CHILD(0xE);
        break;
    case 14:
        fn_800216F8(0x26, fn_800627F8);
        o->signal = 0;
        lbl_2_bss_1A823C[0]->state = 0xF;
        break;
    case 15:
        WAIT_CHILD(0x12);
        break;
    case 18:
        switch (lbl_2_bss_1A823C[0]->mode) {
        case 0:
            lbl_2_bss_1A8248->_441C = fn_2_20CB0(*(u32*)(lbl_8034E9A0 + 0x46E0));
            lbl_2_bss_1A8248->_441D = lbl_803CB8F0[lbl_2_bss_1A8248->_441C];
            if ((s8)lbl_2_bss_1A8248->_1606 == 0) {
                lbl_2_bss_1A8248->_1605 = 0;
                fn_2_207FC();
                fn_2_466AC();
            } else {
                fn_2_20328();
                fn_2_46418();
                fn_2_468DC();
                fn_2_466AC();
                fn_2_467FC();
                fn_2_454E8();
            }
            START_CHILD(fn_2_379D0, 0x13);
            break;
        case 1:
            fn_2_468DC();
            lbl_2_bss_1A823C[0]->state = 0x17;
            break;
        case 8:
            lbl_2_bss_1A8248->_44F2 = 0;
            lbl_2_bss_1A823C[0]->state = 0x17;
            break;
        default:
            lbl_2_bss_1A8248->_44F2 = 0;
            lbl_2_bss_1A823C[0]->state = 0x17;
            break;
        }
        break;
    case 19:
        WAIT_CHILD(0x17);
        break;
    case 20:
        lbl_2_bss_1A824C[0]->_197746 = 7;
        START_CHILD(fn_2_1B314, 0x15);
        break;
    case 21:
        WAIT_CHILD(0x16);
        break;
    case 22:
        START_CHILD(fn_2_1B1BC, 0x17);
        break;
    case 23:
        if (o->signal == 1) {
            o->signal = 0;
            *(void (**)(void))lbl_803CC1B8 = fn_2_20D08;
            lbl_2_bss_1A823C[0]->state = 0;
        }
        break;
    }
    g_d_GameSettings.FrameCountWhileNotAtMainMenu++;
    (lbl_2_bss_1A824C[0]->_1976C0)++;
}
#endif

// fn_2_1B314, size:0x218
void fn_2_1B314(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    s32 i;
    switch ((s8)(u8)o->step) {
    case 0:
        lbl_2_bss_1A824C[0]->_197746 = 7;
        q = fn_800B0A5C_insertQueue(fn_2_8EA80, 2);
        q->step = 0;
        o->signal = 0;
        o->step = 1;
        break;
    case 1:
        if (o->signal == 1) {
            o->step = 2;
        }
        break;
    case 2:
        q = fn_800B0A5C_insertQueue(fn_2_8E478, 2);
        q->step = 0;
        o->signal = 0;
        o->step = 3;
        break;
    case 3:
        if (o->signal == 1) {
            o->step = 0xC;
        }
        break;
    case 4:
        for (i = 0; i < lbl_2_bss_1A824C[0]->_197746; i++) {
            fn_2_8CCAC(i, 1);
            fn_2_68FBC(i, 1);
        }
        o->step = 5;
        break;
    case 5:
        fn_2_47CFC();
        o->step = 6;
        break;
    case 6:
        for (i = 0; i < lbl_2_bss_1A824C[0]->_197746; i++) {
            fn_2_8CCAC(i, 0);
        }
        fn_2_47CFC();
        o->step = 7;
        break;
    case 7:
        fn_2_47CFC();
        o->step = 8;
        break;
    case 8:
        o->step = 9;
        break;
    case 9:
        fn_2_8AEE0();
        o->step = 10;
        break;
    case 10:
        for (i = 0; i < 0x1D; i++) {
            fn_2_8ACB0(i, 0);
        }
        fn_2_8AEE0();
        o->step = 11;
        break;
    case 11:
        fn_2_8AEE0();
        o->step = 12;
        break;
    case 12:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
}

// fn_2_1B52C, size:0x94
void fn_2_1B52C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)(u8)o->step) {
    case 0:
        if (fn_2_4E970() == 1) {
            o->step = 1;
        }
        break;
    case 1:
        o->step = 6;
        break;
    case 6:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
}

// fn_2_1B5C0, size:0x10C
void fn_2_1B5C0(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)(u8)o->step) {
    case 0:
        q = fn_800B0A5C_insertQueue(fn_2_409CC, 2);
        q->step = 0;
        o->signal = 0;
        o->step = 1;
        break;
    case 1:
        if (o->signal == 1) {
            o->step = 2;
        }
        break;
    case 2:
        if (fn_2_4EB64() == 1) {
            o->step = 3;
        }
        break;
    case 3:
        if (fn_2_4EB2C() == 1) {
            o->step = 4;
        }
        break;
    case 4:
        if (fn_2_4EAF4() == 1) {
            o->step = 5;
        }
        break;
    case 5:
        if (fn_2_4E9A8() == 1) {
            o->step = 6;
        }
        break;
    case 6:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
}

// fn_2_1B6CC, size:0xE8
void fn_2_1B6CC(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)(u8)o->step) {
    case 0:
        q = fn_800B0A5C_insertQueue(fn_2_409CC, 2);
        q->step = 0;
        o->signal = 0;
        o->step = 1;
        break;
    case 1:
        if (o->signal == 1) {
            o->step = 2;
        }
        break;
    case 2:
        if (fn_2_4EB64() == 1) {
            o->step = 3;
        }
        break;
    case 3:
        if (fn_2_4EB2C() == 1) {
            o->step = 4;
        }
        break;
    case 4:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
}

// fn_2_1BF50, size:0x80
void fn_2_1BF50(void) {
    fn_80068720(0xD);
    lbl_2_bss_1A824C[0]->_1972BC = 1;
    lbl_2_bss_1A824C[0]->_1972C0 = 1;
    lbl_2_bss_1A824C[0]->_1976D6 = 0;
    lbl_2_bss_1A8248->_44F2 = 0;
    fn_2_4E898();
    lbl_2_bss_1A823C[0]->_34 = 0;
}

// fn_2_1BFD0, size:0x104
void fn_2_1BFD0(void) {
    fn_80068720(0xA);
    lbl_2_bss_1A824C[0]->_1972BC = 1;
    lbl_2_bss_1A824C[0]->_1972C0 = 1;
    lbl_2_bss_1A824C[0]->_1976D6 = 0;
    lbl_2_bss_1A8248->_44F2 = 0;
    if (lbl_2_bss_1A824C[0]->_197864 == 0) {
        fn_2_4E7EC();
    }
    fn_8001F228();
    fn_80021410();
    fn_800ACFB0(*(void**)(lbl_800EF808 + 0x9C));
    if ((s8)lbl_2_bss_1A8248->_44F4 != 0) {
        fn_2_4E8BC();
        fn_2_4E904();
        fn_2_4E928();
    } else {
        fn_2_4E928();
    }
    fn_2_4E94C();
    if (*(u32*)(lbl_80366B18 + 0x7A8) != 0) {
        fn_800ACFB0(*(void**)(lbl_80366B18 + 0x7A8));
        *(u32*)(lbl_80366B18 + 0x7A8) = 0;
    }
    lbl_2_bss_1A823C[0]->_34 = 0;
}

// fn_2_1C0D4, size:0x148
// Reset the menu work buffer.
void fn_2_1C0D4(void) {
    u8* sel = lbl_8034E9A0;
    s32 i;
    lbl_2_bss_1A823C[0]->_34 = 1;
    memset(&lbl_2_bss_1A8250, 0, sizeof(MenuData));
    for (i = 0; i < 8; i++) {
        lbl_2_bss_1A824C[0]->_197756[i] = -1;
    }
    fn_2_54474();
    lbl_2_bss_1A8248->_44F2 = 0;
    lbl_2_bss_1A824C[0]->_1976D6 = 0;
    lbl_2_bss_1A824C[0]->_197833 = 0;
    lbl_2_bss_1A8234[0]->done = 0;
    lbl_2_bss_1A824C[0]->_197838 = 0;
    lbl_2_bss_1A824C[0]->_197835 = 0;
    g_d_GameSettings.StadiumID = 0;
    *(u8*)&lbl_2_bss_1A824C[0]->port = sel[0x46F8];
    lbl_2_bss_1A824C[0]->_197848 = 0;
}

// NONMATCHING 95%: first lbl_2_bss_1A824C load per case should be a direct lwz sym@l (unsolved, see
// docs/patterns/unsolved.md), mission-slot check re-tests hasMissions as int, dead loop counter
#if NONMATCHING
// fn_2_1C860, size:0x734
void fn_2_1C860(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuData* w;
    MenuRosterEntry* e;
    MissionIndex* idx;
    u16 buttons;
    s32 i;
    s32 k;
    s32 a;
    s32 b;
    s16 m;
    switch ((s8)(u8)o->step) {
    case 0:
        lbl_2_bss_1A824C[0]->_19771A = 0;
        lbl_2_bss_1A824C[0]->_19771C = 0;
        lbl_2_bss_1A824C[0]->_197720 = 0;
        lbl_2_bss_1A824C[0]->_197722 = 0;
        lbl_2_bss_1A824C[0]->_19771E = 0x36;
        lbl_2_bss_1A824C[0]->_197724 = 10;
        o->step = 1;
        break;
    case 1:
        w = lbl_2_bss_1A824C[0];
        buttons = MENU_PADS[w->port].repeat;
        if (buttons == 8 || buttons == 4) {
            fn_2_46D94(&w->_19771A, &w->_19771C, w->_19771E, 10, 9);
        }
        lbl_2_bss_1A824C[0]->_197716 =
            lbl_2_bss_1A824C[0]->_19771A + lbl_2_bss_1A824C[0]->_19771C;
        buttons = MENU_PAD_DOWN(lbl_2_bss_1A824C[0]->port);
        if (buttons & 0x100) {
            o->step = 2;
        } else if (buttons & 0x200) {
            o->step = 3;
        }
        buttons = MENU_PAD_DOWN(lbl_2_bss_1A824C[0]->port);
        if (buttons & 0x40) {
            for (i = 0; i < 0x36; i++) {
                e = &ROSTER[i];
                if (lbl_800E8558[i].hasMissions == 1) {
                    for (k = 0; k < 10; k++) {
                        if (lbl_80109AE8[lbl_800E8558[i].missionRow][k].type != -1) {
                            e->missions[k].state = 0;
                        }
                    }
                }
            }
        } else if (buttons & 0x20) {
            for (i = 0; i < 0x36; i++) {
                e = &ROSTER[i];
                if (lbl_800E8558[i].hasMissions == 1) {
                    for (k = 0; k < 10; k++) {
                        if (lbl_80109AE8[lbl_800E8558[i].missionRow][k].type != -1) {
                            e->missions[k].state = -2;
                        }
                    }
                }
            }
        }
        break;
    case 2:
        w = lbl_2_bss_1A824C[0];
        buttons = MENU_PADS[w->port].repeat;
        if (buttons == 8 || buttons == 4) {
            fn_2_46D94(&w->_197720, &w->_197722, w->_197724, 10, 9);
        }
        lbl_2_bss_1A824C[0]->_197718 =
            lbl_2_bss_1A824C[0]->_197720 + lbl_2_bss_1A824C[0]->_197722;
        a = fn_8006CDC0(lbl_2_bss_1A824C[0]->_197716);
        b = fn_2_44E2C(lbl_2_bss_1A824C[0]->_197716);
        buttons = MENU_PAD_DOWN(lbl_2_bss_1A824C[0]->port);
        e = &ROSTER[lbl_2_bss_1A824C[0]->_197716];
        if ((buttons & 0x103) && a != b &&
            lbl_800E8558[lbl_2_bss_1A824C[0]->_197716].hasMissions == 1) {
            idx = &lbl_800E8558[lbl_2_bss_1A824C[0]->_197716];
            m = lbl_2_bss_1A824C[0]->_197718;
            if (idx->hasMissions == 1 && lbl_80109AE8[idx->missionRow][m].type != -1) {
                if (e->missions[m].state < 0) {
                    e->missions[m].state = 0;
                } else {
                    e->missions[m].state = -2;
                }
                fn_8006CDC0(lbl_2_bss_1A824C[0]->_197716);
            }
        } else if (buttons & 0x200) {
            o->step = 1;
        }
        buttons = MENU_PAD_DOWN(lbl_2_bss_1A824C[0]->port);
        if (buttons & 0x40) {
            for (k = 0; k < 10; k++) {
                idx = &lbl_800E8558[lbl_2_bss_1A824C[0]->_197716];
                if (idx->hasMissions == 1 && lbl_80109AE8[idx->missionRow][k].type != -1) {
                    e->missions[k].state = 0;
                }
            }
        } else if (buttons & 0x20) {
            for (k = 0; k < 10; k++) {
                idx = &lbl_800E8558[lbl_2_bss_1A824C[0]->_197716];
                if (idx->hasMissions == 1 && lbl_80109AE8[idx->missionRow][k].type != -1) {
                    e->missions[k].state = -2;
                }
            }
        }
        break;
    case 3: {
        MenuScreenTask* q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    }
}
#endif

// NONMATCHING 97%: register allocation (o/pad base swapped r30/r31); the original also keeps a dead
// induction register (+4 per unrolled group) in the 10x inner loops
#if NONMATCHING
// fn_2_1CF94, size:0x4AC
void fn_2_1CF94(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuRosterEntry* e;
    u16 buttons;
    s32 i;
    s32 j;
    s8 limit;
    switch ((s8)(u8)o->step) {
    case 0:
        lbl_2_bss_1A824C[0]->_19771A = 0;
        lbl_2_bss_1A824C[0]->_19771C = 0;
        lbl_2_bss_1A824C[0]->_19771E = 0x36;
        o->step = 1;
        break;
    case 1:
        buttons = MENU_PAD_REPEAT(lbl_2_bss_1A824C[0]->port);
        if (buttons == 8 || buttons == 4) {
            fn_2_46D94(&lbl_2_bss_1A824C[0]->_19771A, &lbl_2_bss_1A824C[0]->_19771C,
                       lbl_2_bss_1A824C[0]->_19771E, 10, 9);
        }
        lbl_2_bss_1A824C[0]->_197716 =
            lbl_2_bss_1A824C[0]->_19771A + lbl_2_bss_1A824C[0]->_19771C;
        buttons = MENU_PAD_REPEAT(lbl_2_bss_1A824C[0]->port);
        e = &ROSTER[lbl_2_bss_1A824C[0]->_197716];
        if (buttons & 1) {
            if (e->value > 0 && e->value != ROSTER_LIMIT(e)) {
                e->value--;
            }
        } else if (buttons & 2) {
            if (e->value < ROSTER_LIMIT(e)) {
                e->value++;
            }
        }
        if (MENU_PAD_DOWN(lbl_2_bss_1A824C[0]->port) & 0x300) {
            o->counter = 0x10;
            o->step = 2;
        }
        buttons = MENU_PAD_DOWN(lbl_2_bss_1A824C[0]->port);
        if (buttons & 0x40) {
            for (i = 0; i < 0x36; i++) {
                e = &ROSTER[i];
                for (j = 0; j < 10; j++) {
                    if (ROSTER_LIMIT(e) != 0) {
                        e->value = 0;
                    }
                }
                lbl_2_bss_1A8248->_444D[i] = 0;
                e->_31 = 0;
            }
        } else if (buttons & 0x20) {
            for (i = 0; i < 0x36; i++) {
                e = &ROSTER[i];
                for (j = 0; j < 10; j++) {
                    limit = ROSTER_LIMIT(e);
                    if (limit != 0) {
                        e->value = limit;
                    }
                }
            }
        }
        break;
    case 2: {
        MenuScreenTask* q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    }
}
#endif

// fn_2_1C21C, size:0x28
void fn_2_1C21C(void) {
    u8 buf[0x18];
    fn_2_68DAC(0, buf);
}

// NONMATCHING 96%: ours emits a dead blr after the final hang loop (original ends on the loop)
#if NONMATCHING
// fn_2_1C33C, size:0x68
// Debug sanity checks: hang if the menu state is out of range.
void fn_2_1C33C(void) {
    MenuCtx* g = lbl_2_bss_1A8248;
    s16 v;
    if (g->_441C >= 6) {
        while (1) {
        }
    }
    if (g->_4415 >= 4) {
        while (1) {
        }
    }
    v = g->_43BC;
    if (v < 0 || v > 999) {
        while (1) {
        }
    }
    if (lbl_2_bss_1A823C[0]->mode == 5 && g->_4420 >= 5) {
        while (1) {
        }
    }
}
#endif

// fn_2_1C3A4, size:0x4
void fn_2_1C3A4(void) {
    return;
}

// fn_2_1C3A8, size:0x74
void fn_2_1C3A8(void) {
    if ((s32)lbl_2_bss_1A824C[0]->_1978FB == 1) {
        lbl_2_bss_1A8234[0]->layerFlags[1][64] = 1;
        lbl_2_bss_1A8234[0]->layerFlags[8][64] = 0;
        return;
    }
    lbl_2_bss_1A8234[0]->layerFlags[8][64] = 1;
    lbl_2_bss_1A8234[0]->layerFlags[1][64] = 0;
}

// fn_2_1C41C, size:0x74
void fn_2_1C41C(void) {
    lbl_2_bss_1A8234[0]->layerFlags[1][13] = 1;
    lbl_2_bss_1A8234[0]->layerFlags[1][44] = 1;
    lbl_2_bss_1A8234[0]->layerFlags[1][45] = 1;
    lbl_2_bss_1A8234[0]->layerFlags[1][46] = 1;
    lbl_2_bss_1A8234[0]->layerFlags[8][13] = 0;
    lbl_2_bss_1A8234[0]->layerFlags[8][44] = 0;
    lbl_2_bss_1A8234[0]->layerFlags[8][45] = 0;
    lbl_2_bss_1A8234[0]->layerFlags[8][46] = 0;
}

// fn_2_1C490, size:0x74
void fn_2_1C490(void) {
    lbl_2_bss_1A8234[0]->layerFlags[8][13] = 1;
    lbl_2_bss_1A8234[0]->layerFlags[8][44] = 1;
    lbl_2_bss_1A8234[0]->layerFlags[8][45] = 1;
    lbl_2_bss_1A8234[0]->layerFlags[8][46] = 1;
    lbl_2_bss_1A8234[0]->layerFlags[1][13] = 0;
    lbl_2_bss_1A8234[0]->layerFlags[1][44] = 0;
    lbl_2_bss_1A8234[0]->layerFlags[1][45] = 0;
    lbl_2_bss_1A8234[0]->layerFlags[1][46] = 0;
}

// fn_2_1C504, size:0xC4
void fn_2_1C504(s32 arg) {
    s32 i;
    for (i = 0; i < 0x33; i++) {
        if (arg == lbl_2_bss_1A8248->slots[i]._2 && (lbl_2_bss_1A8248->slots[i]._3 == 1 || lbl_2_bss_1A8248->slots[i]._3 == 0)) {
            if (lbl_2_bss_1A8248->_441C == 5) {
                if (lbl_2_bss_1A8248->slots[i]._4 == 1) {
                    lbl_2_bss_1A8248->slots[i]._3 = 3;
                } else {
                    lbl_2_bss_1A8248->slots[i]._3 = 0;
                }
            } else {
                lbl_2_bss_1A8248->slots[i]._3 = 0;
            }
        }
    }
    lbl_2_bss_1A8248->_440C[arg] = 1;
    if (!(lbl_2_bss_1A8248->_4428 & (1 << arg))) {
        lbl_2_bss_1A8248->_4423++;
        lbl_2_bss_1A8248->_4428 |= 1 << arg;
    }
}

typedef struct {
    u32 w0;
    u8 pad[0x14];
} Cell18;

// fn_2_1C244, size:0xF8
void fn_2_1C244(void) {
    s32 row;
    s32 col;
    for (row = 0; row < 70; row++) {
        for (col = 0; col < 864; col++) {
            Cell18* c = &((Cell18(*)[864])lbl_2_bss_1A8234[0])[row][col];
            if (row >= 35 && col >= 100 && c->w0 != 0) {
                return;
            }
        }
    }
}

// fn_2_1C714, size:0x14C
void fn_2_1C714(s32 arg) {
    s32 i;
    s32 t;
    for (i = 0; i < 0x33; i++) {
        if (arg == lbl_2_bss_1A8248->slots[i]._2 && (lbl_2_bss_1A8248->slots[i]._3 == 1 || lbl_2_bss_1A8248->slots[i]._3 == 0)) {
            if (lbl_2_bss_1A8248->slots[i]._4 == 0 && lbl_2_bss_1A8248->_441C != arg) {
                if (lbl_2_bss_1A8248->_441C == 5) {
                    lbl_2_bss_1A8248->slots[i]._3 = 3;
                } else {
                    lbl_2_bss_1A8248->slots[i]._3 = 0;
                }
            } else {
                lbl_2_bss_1A8248->slots[i]._3 = 0;
            }
            if (lbl_2_bss_1A8248->slots[i]._4 == 2) {
                lbl_2_bss_1A8248->slots[i]._3 = 0;
            }
        }
        if (lbl_2_bss_1A8248->slots[i]._2 == 6 || lbl_2_bss_1A8248->slots[i]._2 == 7 || lbl_2_bss_1A8248->slots[i]._2 == 8) {
            lbl_2_bss_1A8248->slots[i]._3 = 0;
            lbl_2_bss_1A8248->_440C[6] = 1;
            lbl_2_bss_1A8248->_440C[7] = 1;
            lbl_2_bss_1A8248->_440C[8] = 1;
        }
    }
    lbl_2_bss_1A8248->_440C[arg] = 1;
    if (lbl_2_bss_1A8248->_441C != arg) {
        t = 1 << arg;
        if (!(lbl_2_bss_1A8248->_4426 & t)) {
            lbl_2_bss_1A8248->_4422 = lbl_2_bss_1A8248->_4422 + 1;
            lbl_2_bss_1A8248->_4426 = lbl_2_bss_1A8248->_4426 | t;
        }
    }
}

// fn_2_1C5C8, size:0x14C
void fn_2_1C5C8(s32 arg) {
    s32 i;
    s32 t;
    for (i = 0; i < 0x33; i++) {
        if (arg == lbl_2_bss_1A8248->slots[i]._2 && (lbl_2_bss_1A8248->slots[i]._3 == 1 || lbl_2_bss_1A8248->slots[i]._3 == 0)) {
            if (lbl_2_bss_1A8248->slots[i]._4 == 0 && lbl_2_bss_1A8248->_441C != arg) {
                if (lbl_2_bss_1A8248->_441C == 5) {
                    lbl_2_bss_1A8248->slots[i]._3 = 3;
                } else {
                    lbl_2_bss_1A8248->slots[i]._3 = 2;
                }
            } else {
                lbl_2_bss_1A8248->slots[i]._3 = 0;
            }
            if (lbl_2_bss_1A8248->slots[i]._4 == 2) {
                lbl_2_bss_1A8248->slots[i]._3 = 0;
            }
        }
        if (lbl_2_bss_1A8248->slots[i]._2 == 6 || lbl_2_bss_1A8248->slots[i]._2 == 7 || lbl_2_bss_1A8248->slots[i]._2 == 8) {
            lbl_2_bss_1A8248->slots[i]._3 = 0;
            lbl_2_bss_1A8248->_440C[6] = 1;
            lbl_2_bss_1A8248->_440C[7] = 1;
            lbl_2_bss_1A8248->_440C[8] = 1;
        }
    }
    lbl_2_bss_1A8248->_440C[arg] = 1;
    if (lbl_2_bss_1A8248->_441C != arg) {
        t = 1 << arg;
        if (!(lbl_2_bss_1A8248->_4426 & t)) {
            lbl_2_bss_1A8248->_4422 = lbl_2_bss_1A8248->_4422 + 1;
            lbl_2_bss_1A8248->_4426 = lbl_2_bss_1A8248->_4426 | t;
        }
    }
}
