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
#include "main/file_80021308.h" // SoundManager
extern SoundManager lbl_800EF808;
extern void fn_2_8EA80(void);
extern void fn_2_8E478(void);
extern void fn_2_47CFC(void);
extern void fn_2_8AEE0(void);
extern void fn_2_8ACB0(s32, s32);
extern void fn_2_68FBC(s32, s32);
extern void fn_2_8CCAC(s32, u8);
#include "main/file_8000F150.h" // TextSystem lbl_80366B18
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
#define MENU_PAD_REPEAT(port) (*(u16*)((u8*)&lbl_803C77B8 + offsetof(MenuPad, repeat) + (port) * sizeof(MenuPad)))
#define MENU_PAD_DOWN(port) (*(u16*)((u8*)&lbl_803C77B8 + offsetof(MenuPad, down) + (port) * sizeof(MenuPad)))

#define ROSTER (lbl_2_bss_1A8248->chars)
#define ROSTER_LIMIT(e) (PTR32_GET(s8, (e)->limits)[lbl_2_bss_1A8248->_4415 * 6 + lbl_2_bss_1A8248->_441C + 4])
extern void fn_8004B1B8(void* tex);
#include "main/aramloader.h"
extern ARAMLoader lbl_803C6CF8;

// Archive loaded from ARAM by fn_2_1B1BC (lbl_2_bss_1034C).
typedef struct MenuArchive {
    /*0x0*/ u8 _0[4];
    /*0x4*/ void* first; // entry 0 (texture archive) after relocation
    /*0x8*/ u32* data; // offset table; entries are relocated in place
} MenuArchive;
extern MenuArchive* lbl_2_data_4BA0;
extern u8 lbl_2_bss_1034C[];
extern MenuAsset lbl_2_data_4B90;
extern MenuData lbl_2_bss_1A8250; // menu work buffer that lbl_2_bss_1A824C points at
#include "main/charsel_state_type.h"
extern CharSelectState lbl_8034E9A0;
extern void* memset(void*, int, size_t);

// NONMATCHING 87%: the original keeps the relocation loop (count 1, index 0) as a real loop; CW folds and unrolls ours
#if NONMATCHING
// Turn the first `count` offsets of an archive into pointers; returns entry `index`.
static inline void* relocateArchive(u32* data, s32 index, s32 count) {
    void* entry;
    u32* p;
#ifdef TARGET_PC
    port_swap_offset_table(data, count);
#endif
    entry = (u8*)data + data[index];
    p = data + count;
    while (count-- != 0) {
        p--;
        *p += PTR_TO_U32(data); // TODO(port): 32-bit file offsets relocated in place
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
        lbl_2_data_4BA0->data = (u32*)ARAMTransfer(&lbl_2_data_4B90, 0, 0, 0);
        o->step = 1;
        break;
    case 1:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
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

#if !NONMATCHING
// Switch jump table of fn_2_1B7B4; mwcc emits it itself once the function matches.
void* jumptable_2_data_4C04[24] = {
    (u8*)fn_2_1B7B4 + 0xCC, (u8*)fn_2_1B7B4 + 0x224, (u8*)fn_2_1B7B4 + 0x23C, (u8*)fn_2_1B7B4 + 0x248,
    (u8*)fn_2_1B7B4 + 0x254, (u8*)fn_2_1B7B4 + 0x384, (u8*)fn_2_1B7B4 + 0x3B8, (u8*)fn_2_1B7B4 + 0x3D0,
    (u8*)fn_2_1B7B4 + 0x404, (u8*)fn_2_1B7B4 + 0x440, (u8*)fn_2_1B7B4 + 0x458, (u8*)fn_2_1B7B4 + 0x48C,
    (u8*)fn_2_1B7B4 + 0x4A4, (u8*)fn_2_1B7B4 + 0x518, (u8*)fn_2_1B7B4 + 0x530, (u8*)fn_2_1B7B4 + 0x560,
    (u8*)fn_2_1B7B4 + 0x760, (u8*)fn_2_1B7B4 + 0x760, (u8*)fn_2_1B7B4 + 0x578, (u8*)fn_2_1B7B4 + 0x690,
    (u8*)fn_2_1B7B4 + 0x6A8, (u8*)fn_2_1B7B4 + 0x6E8, (u8*)fn_2_1B7B4 + 0x700, (u8*)fn_2_1B7B4 + 0x734,
};
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
            lbl_2_bss_1A8248->_441C = fn_2_20CB0(lbl_8034E9A0.captain[0]);
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
    fn_800ACFB0(lbl_800EF808.groups[38]);
    if ((s8)lbl_2_bss_1A8248->_44F4 != 0) {
        fn_2_4E8BC();
        fn_2_4E904();
        fn_2_4E928();
    } else {
        fn_2_4E928();
    }
    fn_2_4E94C();
    if (lbl_80366B18.tables[4] != NULL) {
        fn_800ACFB0(lbl_80366B18.tables[4]);
        lbl_80366B18.tables[4] = NULL;
    }
    lbl_2_bss_1A823C[0]->_34 = 0;
}

// fn_2_1C0D4, size:0x148
// Reset the menu work buffer.
void fn_2_1C0D4(void) {
    CharSelectState* sel = &lbl_8034E9A0;
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
    *(u8*)&lbl_2_bss_1A824C[0]->port = sel->ports[0];
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

// .data 0x2E40-0x4C68 (menu tables read by many units, then this TU's jump tables).
// .data 0x00002E40..0x00004C68
u8 lbl_2_data_2E40[1] = {5};
u8 lbl_2_data_2E41[3] = {3, 2, 1}; // unreferenced
s16 lbl_2_data_2E44[4][4] = {{0, 0, 0, 1}, {20, 20, 10, 1}, {30, 20, 10, 1}, {50, 20, 10, 1}};
u8 lbl_2_data_2E64[8] = {1, 2, 4, 3, 5, 0, 0, 0};
s16 lbl_2_data_2E6C[10] = {80, 100, 120, 150, 14, 14, 14, 14, 14, 20};
s16 lbl_2_data_2E80[18] = {16, 7, 15, 22, 8, 19, 17, 8, 17, 20, 9, 19, 14, 7, 14, 36, 13, 31};
Vec lbl_2_data_2EA4[57] = {
    {-4.331f, 0.0f, -5.65f},
    {-4.056f, 0.0f, -4.13f},
    {-5.567f, 0.0f, -3.839f},
    {-7.37f, 0.0f, -3.48f},
    {-5.352f, 0.0f, -2.462f},
    {-5.007f, 0.0f, -1.103f},
    {-5.571f, 0.0f, -0.885f},
    {-4.665f, 0.0f, 0.173f},
    {-6.349f, 0.0f, 0.677f},
    {-7.38f, 0.0f, 1.3f},
    {-4.688f, 0.0f, 1.332f},
    {-4.93f, 0.0f, 1.896f},
    {-1.96f, 0.0f, -4.5f},
    {-1.31f, 0.0f, -4.44f},
    {0.5f, 0.0f, -6.42f},
    {0.348f, 0.0f, -4.369f},
    {-3.836f, 0.0f, -2.923f},
    {-3.405f, 0.0f, -1.548f},
    {-3.073f, 0.0f, -0.285f},
    {-2.101f, 0.0f, -0.276f},
    {-0.681f, 0.0f, -0.204f},
    {1.376f, 0.0f, -0.214f},
    {-3.6f, 0.0f, 2.0f},
    {-2.59f, 0.0f, 2.11f},
    {-0.81f, 0.0f, 1.95f},
    {0.764f, 0.0f, 1.706f},
    {0.354f, 0.0f, 2.577f},
    {1.56f, 0.0f, 2.0f},
    {1.35f, 0.0f, 3.51f},
    {2.437f, 0.0f, -0.823f},
    {3.578f, 0.0f, -1.647f},
    {3.878f, 0.0f, -2.361f},
    {4.257f, 0.0f, -3.175f},
    {4.459f, 0.0f, -4.542f},
    {4.49f, 0.0f, -5.736f},
    {4.96f, 0.0f, -2.977f},
    {5.718f, 0.0f, -2.848f},
    {6.013f, 0.0f, -3.712f},
    {4.464f, 0.0f, -1.51f},
    {5.393f, 0.0f, -1.484f},
    {5.393f, 0.0f, -0.565f},
    {6.459f, 0.0f, 1.049f},
    {6.845f, 0.0f, 2.242f},
    {-6.27f, 0.0f, -3.58f},
    {-0.47f, 0.0f, -5.54f},
    {1.66f, 0.0f, 2.59f},
    {-3.1f, 0.0f, -4.31f},
    {1.18f, 0.0f, 0.79f},
    {-2.98f, 0.0f, 0.11f},
    {-0.56f, 0.0f, -13.19f},
    {-0.45f, 0.0f, -13.19f},
    {-6.75f, 0.0f, -2.5f},
    {-7.4f, 0.0f, 1.3f},
    {4.5f, 0.0f, -5.8f},
    {0.9f, 0.0f, 3.95f},
    {-0.25f, 0.0f, -4.4f},
    {5.79f, 0.0f, -0.37f},
};
Vec lbl_2_data_3150[6] = {
    {-4.83f, 0.0f, -5.43f},
    {-5.93f, 0.0f, 3.55f},
    {7.2f, 0.0f, -4.56f},
    {-1.25f, 0.0f, 3.66f},
    {1.26f, 0.0f, -3.38f},
    {6.49f, 0.0f, 2.6f},
};
MenuSpot lbl_2_data_3198[42] = {
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{-9.94f, 0.0f, -13.66f}, 0.4f, 1},
    {{-12.0f, 0.0f, 7.0f}, -0.6f, 1},
    {{14.6f, 0.0f, -10.02f}, 0.5f, 1},
    {{-1.35f, 0.0f, 7.98f}, -0.0f, 1},
    {{2.62f, 0.0f, -8.31f}, 0.8f, 1},
    {{15.05f, 0.0f, 7.84f}, 0.3f, 1},
    {{14.6f, 0.0f, -10.02f}, 0.5f, 1},
    {{12.04f, 0.0f, 0.93f}, 0.4f, 1},
    {{12.04f, 0.0f, 0.93f}, 0.4f, 1},
    {{-9.98f, 0.4f, -14.31f}, 0.0f, 1},
    {{-11.04f, -1.0f, 3.95f}, -0.0f, 1},
    {{12.53f, -2.05f, -10.65f}, 0.0f, 1},
    {{-2.0f, -0.5f, 6.25f}, 0.0f, 1},
    {{3.02f, -1.35f, -11.38f}, 0.0f, 1},
    {{12.98f, -1.2f, 6.35f}, 0.0f, 1},
    {{-9.98f, 0.4f, -14.31f}, 0.0f, 0},
    {{-11.04f, -1.0f, 3.95f}, -0.0f, 0},
    {{12.53f, -2.05f, -10.65f}, 0.0f, 0},
    {{-2.0f, -0.5f, 6.25f}, 0.0f, 0},
    {{3.02f, -1.35f, -11.38f}, 0.0f, 0},
    {{12.98f, -1.2f, 6.35f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 1},
    {{-12.96f, 0.0f, -0.8f}, -0.8f, 0},
    {{-1.0f, 0.0f, -2.63f}, 0.0f, 1},
    {{-5.74f, 0.0f, 1.54f}, 0.0f, 1},
    {{-3.02f, 0.0f, -26.57f}, 0.0f, 1},
    {{2.5f, 0.0f, -25.4f}, 0.0f, 1},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 1},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 1},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0},
};
s32 lbl_2_data_34E0[48] = {
    50, 120, 921, 130, 240, 922, 250, 320,
    923, 330, 430, 924, 440, 500, 925, -1,
    -1, 0, -1, -1, 0, -1, -1, 0,
    50, 120, 931, 130, 240, 932, 250, 320,
    933, 330, 430, 934, 440, 500, 935, -1,
    -1, 0, -1, -1, 0, -1, -1, 0,
};
s32 lbl_2_data_35A0[63] = {
    2, 2, 8, 0, 3, 3, 3, 0,
    0, 6, 4, 7, 2, 0, 2, 0,
    0, 2, 1, 2, 3, 8, 0, 2,
    0, 2, 4, 5, 0, 1, 1, 2,
    337123614, 0, 65793, 16843266, 33686019, 50529027, 0, 0,
    0, 0, 16843009, 16843266, 33686018, 50529027, 50528256, 0,
    0, 65793, 16843266, 33686019, 50529027, 67372036, 67108864, 0,
    0, 16843009, 16843266, 33686018, 50529027, 50529284, 67372036,
};
MenuSpot lbl_2_data_369C[4] = {
    {{2.49f, 0.15f, -1.0f}, -0.2f, 0},
    {{3.09f, 0.15f, -1.0f}, -0.0f, 0},
    {{3.72f, 0.15f, -1.0f}, 0.0f, 0},
    {{4.38f, 0.2f, -0.64f}, 0.2f, 0},
};
s16 lbl_2_data_36EC[20] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
s16 lbl_2_data_3714[20] = {0, 0, 0, 0, 0, 0, 0, 1, 4, 5, 10, 11, 6, 17, 2, 3, 9, 19, 0, 0};
s16 lbl_2_data_373C[20] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
s16 lbl_2_data_3764[20][4] = {
    {100, 150, 180, 200},
    {100, 150, 180, 200},
    {100, 150, 180, 200},
    {100, 150, 180, 200},
    {100, 150, 180, 200},
    {100, 150, 180, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {200, 200, 200, 200},
    {500, 500, 500, 500},
    {600, 700, 800, 900},
};
f32 lbl_2_data_3804[5][3] = {
    {0.1f, 0.1f, 0.1f},
    {0.3f, 0.5f, 1.0f},
    {3.0f, 5.0f, 7.0f},
    {0.1f, 0.1f, 0.1f},
    {1.0f, 1.5f, 2.0f},
};
s32 lbl_2_data_3840[5][3] = {{100, 150, 200}, {100, 150, 200}, {100, 150, 200}, {100, 150, 200}, {100, 150, 200}};
s32 lbl_2_data_387C[5][3] = {{-50, -100, -150}, {-50, -100, -150}, {-50, -100, -150}, {-50, -100, -150}, {-50, -100, -150}};
s32 lbl_2_data_38B8 = -100;
s32 lbl_2_data_38BC = 100;
s16 lbl_2_data_38C0[6] = {18, 15, 38, 39, 8, 27};
s16 lbl_2_data_38CC[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
f32 lbl_2_data_38E0[180] = {
    -0.730432f, -0.705668f, -9.87143f, -0.47468f, -0.79242f, -8.908588f, 906.0f, 2708.0f, 1.0f,
    3.395215f, -0.1973047f, -6.424299f, 3.396461f, -0.1760224f, -5.424527f, 65314.0f, 0.0f, 1.0f,
    1.952406f, -1.27543f, -12.41054f, 1.917041f, -1.291824f, -11.4113f, 171.0f, 65167.0f, 1.0f,
    2.369277f, -1.208047f, -17.374329f, 2.358071f, -1.251752f, -16.374329f, 456.0f, 65419.0f, 1.0f,
    1.690731f, -1.132852f, -12.603273f, 1.679518f, -1.158735f, -11.603671f, 270.0f, 65419.0f, 1.0f,
    1.807158f, -1.073281f, -12.883222f, 1.795947f, -1.104052f, -11.883758f, 321.0f, 65419.0f, 1.0f,
    1.681485f, -0.96f, -11.779107f, 1.670277f, -0.998244f, -10.779902f, 399.0f, 65419.0f, 1.0f,
    4.063792f, -1.052774f, -21.944992f, 4.009405f, -1.123852f, -20.949005f, 742.0f, 64967.0f, 1.0f,
    2.823607f, -0.674844f, -16.09472f, 2.768934f, -0.745922f, -15.098749f, 742.0f, 64964.0f, 1.0f,
    2.154075f, -1.307656f, -16.29751f, 2.142866f, -1.3459f, -15.298305f, 399.0f, 65419.0f, 1.0f,
    1.91661f, -1.14457f, -14.170815f, 1.905402f, -1.182814f, -13.17161f, 399.0f, 65419.0f, 1.0f,
    0.0f, -20.5f, -28.5f, 0.0f, -20.0f, -28.0f, 59449.0f, 0.0f, 1.0f, 3.12677f, -70.07641f,
    -154.09785f, 3.107514f, -69.64202f, -153.19734f, 60849.0f, 65313.0f, 1.0f, 0.0f, -20.5f, -28.5f,
    0.0f, -20.0f, -28.0f, 59449.0f, 0.0f, 1.2f, -9.216555f, -27.851788f, -50.533867f, -9.216555f,
    -27.28859f, -49.707546f, 59296.0f, 0.0f, 1.0f, -11.228273f, -27.851788f, -34.756523f,
    -11.228273f, -27.28859f, -33.930202f, 59296.0f, 0.0f, 1.0f, 12.525633f, -27.851788f, -49.13543f,
    12.525633f, -27.28859f, -48.30911f, 59296.0f, 0.0f, 1.0f, -0.747805f, -27.851788f, -34.233086f,
    -0.747805f, -27.28859f, -34.406765f, 59296.0f, 0.0f, 1.0f, 1.916258f, -27.851788f, -47.1159f,
    1.916258f, -27.28859f, -46.289577f, 59296.0f, 0.0f, 1.0f, 11.974852f, -27.851788f, -36.096367f,
    11.974852f, -27.28859f, -35.270046f, 59296.0f, 0.0f, 1.0f,
};
f32 lbl_2_data_3BB0[18] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 8.0f, 2.0f, 0.001f, 8.0f, 2.0f, 0.001f, 14.0f, 8.0f, 0.001f,
    14.0f, 8.0f, 0.001f,
};
s16 lbl_2_data_3BF8[2] = {4, 7};
// Unreferenced: four values, a pointer to lbl_2_data_3BF8 and one to itself.
typedef struct Menu3BFC {
    s16 v[4];
    s16* list;
    struct Menu3BFC* self;
} Menu3BFC;
Menu3BFC lbl_2_data_3BFC = {{30, 31, 2, 2}, lbl_2_data_3BF8, &lbl_2_data_3BFC};
s16 lbl_2_data_3C0C[2] = {3, 43};
s16 lbl_2_data_3C10[2] = {9, 8};
s16 lbl_2_data_3C14[2] = {34, 33};
s16 lbl_2_data_3C18[2] = {28, 45};
s16 lbl_2_data_3C1C[2] = {14, 44};
s16 lbl_2_data_3C20[6] = {2, 2, 2, 2, 2, 0};
extern s16 lbl_2_data_3C0C[];
extern s16 lbl_2_data_3C10[];
extern s16 lbl_2_data_3C14[];
extern s16 lbl_2_data_3C18[];
extern s16 lbl_2_data_3C1C[];
s16 *lbl_2_data_3C2C[5] = {lbl_2_data_3C0C, lbl_2_data_3C10, lbl_2_data_3C14, lbl_2_data_3C18, lbl_2_data_3C1C};
s32 lbl_2_data_3C40[7] = {20, 25, 30, 35, 40, 45, 50};
s32 lbl_2_data_3C5C[10] = {21, 26, 31, 36, 41, 46, 51, 1, 262147, 131077};
MenuAnimation lbl_2_data_3C84[10] = {
    {0, 0, 1, 0},
    {1, 0, 1, 0},
    {2, 0, 0, 0},
    {3, 0, 0, 0},
    {4, 0, 0, 0},
    {5, 0, 1, 0},
    {6, 0, 1, 0},
    {7, 0, 1, 0},
    {8, 0, 0, 0},
    {9, 0, 1, 0},
};
u8 lbl_2_data_3CC0[8] = {0, 4, 2, 5, 3, 1, 6, 0};
u8 lbl_2_data_3CC8[8] = {0, 1, 2, 4, 3, 5, 0, 0};
u8 lbl_2_data_3CD0[16] = {0, 19, 21, 13, 33, 12, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0};
u8 lbl_2_data_3CE0[8] = {0, 1, 4, 3, 2, 5, 0, 0};
s16 lbl_2_data_3CE8[6][6] = {
    {0, 1, 4, 3, 2, 5},
    {1, 0, 3, 2, 4, 5},
    {2, 3, 1, 4, 0, 5},
    {3, 4, 2, 0, 1, 5},
    {4, 2, 0, 1, 3, 5},
    {5, 2, 4, 3, 1, 0},
};
s16 lbl_2_data_3D30[51][4] = {
    {1, -1, -1, -1},
    {16, 0, 2, 46},
    {4, -1, 43, 1},
    {-1, -1, -1, 43},
    {5, 2, -1, -1},
    {7, 4, 6, -1},
    {-1, -1, -1, 5},
    {10, 5, 8, 18},
    {-1, -1, 9, 7},
    {-1, -1, -1, 8},
    {11, 7, -1, 22},
    {-1, 10, -1, -1},
    {-1, -1, 46, 13},
    {-1, 44, 12, 15},
    {44, -1, 44, -1},
    {-1, -1, 13, -1},
    {17, 1, -1, -1},
    {18, 16, -1, -1},
    {48, 17, 7, 19},
    {-1, -1, 18, 20},
    {-1, -1, 19, 21},
    {47, -1, 20, 29},
    {-1, -1, 10, 23},
    {-1, -1, 22, 24},
    {-1, -1, 23, 25},
    {26, 47, 24, 27},
    {-1, 25, -1, -1},
    {45, -1, 25, -1},
    {-1, 45, -1, -1},
    {21, 30, 21, 30},
    {29, 31, 29, 38},
    {30, 32, -1, -1},
    {31, 33, -1, 35},
    {32, 34, -1, -1},
    {33, -1, -1, -1},
    {-1, -1, 32, 36},
    {39, 37, 35, -1},
    {36, -1, -1, -1},
    {-1, -1, 30, 39},
    {40, 36, 38, -1},
    {41, 39, -1, 41},
    {42, 40, -1, -1},
    {-1, 41, -1, -1},
    {-1, -1, 3, 2},
    {13, 14, 13, 14},
    {28, 27, -1, -1},
    {-1, -1, 1, 12},
    {25, 21, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, -1, -1},
    {-1, -1, 49, -1},
};
s16 lbl_2_data_3EC8[6] = {0, 11, 37, 26, 15, 42};
s16 lbl_2_data_3ED4[6] = {3, 9, 34, 28, 14, 0};
s16 lbl_2_data_3EE0[6] = {43, 8, 33, 45, 44, 0};
s16 lbl_2_data_3EEC[2] = {4, 7};
s16 lbl_2_data_3EF0[2] = {30, 31};
f32 lbl_2_data_3EF4[6] = {0.4f, 0.4f, 0.4f, 0.5f, 0.4f, 0.5f};
f32 lbl_2_data_3F0C[8] = {0.35f, 0.35f, 0.35f, 0.35f, 0.35f, 0.35f, 0.35f, 0.35f};
f32 lbl_2_data_3F2C[6] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};
f32 lbl_2_data_3F44[6] = {0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.024f};
f32 lbl_2_data_3F5C = 0.35f;
u8 lbl_2_data_3F60[6][9] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
};
u8 lbl_2_data_3F96[2] = {0}; // alignment padding (unused)
u8 lbl_2_data_3F98[6][0x1FE] = {
    {
        0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 1, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 2, 0, 0, 2, 255, 0, 255, 0, 0, 0, 3,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 4, 0, 0, 2, 255, 0, 255,
        0, 0, 0, 5, 1, 0, 2, 255, 0, 255, 0, 0, 0, 6, 1, 0,
        6, 255, 0, 255, 0, 0, 0, 7, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 8, 1, 0, 2, 255, 0, 255, 0, 0, 0, 9, 1, 0, 2, 255,
        0, 255, 0, 0, 0, 10, 1, 0, 2, 255, 0, 255, 0, 0, 0, 11,
        1, 0, 0, 1, 0, 255, 0, 0, 0, 12, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 13, 4, 0, 2, 255, 0, 255, 0, 0, 0, 14, 4, 0,
        2, 255, 0, 255, 0, 0, 0, 15, 4, 0, 0, 4, 0, 255, 0, 0,
        0, 16, 0, 0, 2, 255, 0, 255, 0, 0, 0, 17, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 18, 1, 0, 2, 255, 0, 255, 0, 0, 0, 19,
        1, 0, 2, 255, 0, 255, 0, 0, 0, 20, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 21, 3, 0, 2, 255, 0, 255, 0, 0, 0, 22, 1, 0,
        2, 255, 0, 255, 0, 0, 0, 23, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 24, 3, 0, 2, 255, 0, 255, 0, 0, 0, 25, 3, 0, 2, 255,
        0, 255, 0, 0, 0, 26, 3, 0, 0, 3, 0, 255, 0, 0, 0, 27,
        3, 0, 2, 255, 0, 255, 0, 0, 0, 28, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 29, 3, 0, 2, 255, 0, 255, 0, 0, 0, 30, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 31, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 32, 2, 0, 2, 255, 0, 255, 0, 0, 0, 33, 2, 0, 2, 255,
        0, 255, 0, 0, 0, 34, 2, 0, 2, 255, 0, 255, 0, 0, 0, 35,
        2, 0, 2, 255, 0, 255, 0, 0, 0, 36, 2, 0, 2, 255, 0, 255,
        0, 0, 0, 37, 2, 0, 0, 2, 0, 255, 0, 0, 0, 38, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 39, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 40, 5, 0, 5, 255, 0, 255, 0, 0, 0, 41, 5, 0, 2, 255,
        1, 255, 0, 0, 0, 42, 5, 0, 0, 5, 0, 255, 0, 0, 0, 43,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 44, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 45, 3, 0, 2, 255, 0, 255, 0, 0, 0, 46, 0, 0,
        2, 255, 0, 255, 0, 0, 0, 47, 3, 0, 2, 255, 0, 255, 0, 0,
        0, 48, 1, 0, 7, 255, 0, 255, 0, 0, 0, 49, 1, 0, 8, 255,
        0, 255, 0, 0, 0, 50, 1, 0, 4, 255, 0, 255, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 1, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 2, 0, 0, 2, 255, 0, 255, 0, 0, 0, 3,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 4, 0, 0, 2, 255, 0, 255,
        0, 0, 0, 5, 1, 0, 2, 255, 0, 255, 0, 0, 0, 6, 1, 0,
        6, 255, 0, 255, 0, 0, 0, 7, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 8, 1, 0, 2, 255, 0, 255, 0, 0, 0, 9, 1, 0, 2, 255,
        0, 255, 0, 0, 0, 10, 1, 0, 2, 255, 0, 255, 0, 0, 0, 11,
        1, 0, 0, 1, 0, 255, 0, 0, 0, 12, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 13, 4, 0, 2, 255, 0, 255, 0, 0, 0, 14, 4, 0,
        2, 255, 0, 255, 0, 0, 0, 15, 4, 0, 0, 4, 0, 255, 0, 0,
        0, 16, 0, 0, 2, 255, 0, 255, 0, 0, 0, 17, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 18, 1, 0, 2, 255, 0, 255, 0, 0, 0, 19,
        1, 0, 2, 255, 0, 255, 0, 0, 0, 20, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 21, 3, 0, 2, 255, 0, 255, 0, 0, 0, 22, 1, 0,
        2, 255, 0, 255, 0, 0, 0, 23, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 24, 3, 0, 2, 255, 0, 255, 0, 0, 0, 25, 3, 0, 2, 255,
        0, 255, 0, 0, 0, 26, 3, 0, 0, 3, 0, 255, 0, 0, 0, 27,
        3, 0, 2, 255, 0, 255, 0, 0, 0, 28, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 29, 3, 0, 2, 255, 0, 255, 0, 0, 0, 30, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 31, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 32, 2, 0, 2, 255, 0, 255, 0, 0, 0, 33, 2, 0, 2, 255,
        0, 255, 0, 0, 0, 34, 2, 0, 2, 255, 0, 255, 0, 0, 0, 35,
        2, 0, 2, 255, 0, 255, 0, 0, 0, 36, 2, 0, 2, 255, 0, 255,
        0, 0, 0, 37, 2, 0, 0, 2, 0, 255, 0, 0, 0, 38, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 39, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 40, 5, 0, 5, 255, 0, 255, 0, 0, 0, 41, 5, 0, 2, 255,
        1, 255, 0, 0, 0, 42, 5, 0, 0, 5, 0, 255, 0, 0, 0, 43,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 44, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 45, 3, 0, 2, 255, 0, 255, 0, 0, 0, 46, 0, 0,
        2, 255, 0, 255, 0, 0, 0, 47, 3, 0, 2, 255, 0, 255, 0, 0,
        0, 48, 1, 0, 7, 255, 0, 255, 0, 0, 0, 49, 1, 0, 8, 255,
        0, 255, 0, 0, 0, 50, 1, 0, 4, 255, 0, 255, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 1, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 2, 0, 0, 2, 255, 0, 255, 0, 0, 0, 3,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 4, 0, 0, 2, 255, 0, 255,
        0, 0, 0, 5, 1, 0, 2, 255, 0, 255, 0, 0, 0, 6, 1, 0,
        6, 255, 0, 255, 0, 0, 0, 7, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 8, 1, 0, 2, 255, 0, 255, 0, 0, 0, 9, 1, 0, 2, 255,
        0, 255, 0, 0, 0, 10, 1, 0, 2, 255, 0, 255, 0, 0, 0, 11,
        1, 0, 0, 1, 0, 255, 0, 0, 0, 12, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 13, 4, 0, 2, 255, 0, 255, 0, 0, 0, 14, 4, 0,
        2, 255, 0, 255, 0, 0, 0, 15, 4, 0, 0, 4, 0, 255, 0, 0,
        0, 16, 0, 0, 2, 255, 0, 255, 0, 0, 0, 17, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 18, 1, 0, 2, 255, 0, 255, 0, 0, 0, 19,
        1, 0, 2, 255, 0, 255, 0, 0, 0, 20, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 21, 3, 0, 2, 255, 0, 255, 0, 0, 0, 22, 1, 0,
        2, 255, 0, 255, 0, 0, 0, 23, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 24, 3, 0, 2, 255, 0, 255, 0, 0, 0, 25, 3, 0, 2, 255,
        0, 255, 0, 0, 0, 26, 3, 0, 0, 3, 0, 255, 0, 0, 0, 27,
        3, 0, 2, 255, 0, 255, 0, 0, 0, 28, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 29, 3, 0, 2, 255, 0, 255, 0, 0, 0, 30, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 31, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 32, 2, 0, 2, 255, 0, 255, 0, 0, 0, 33, 2, 0, 2, 255,
        0, 255, 0, 0, 0, 34, 2, 0, 2, 255, 0, 255, 0, 0, 0, 35,
        2, 0, 2, 255, 0, 255, 0, 0, 0, 36, 2, 0, 2, 255, 0, 255,
        0, 0, 0, 37, 2, 0, 0, 2, 0, 255, 0, 0, 0, 38, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 39, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 40, 5, 0, 5, 255, 0, 255, 0, 0, 0, 41, 5, 0, 2, 255,
        1, 255, 0, 0, 0, 42, 5, 0, 0, 5, 0, 255, 0, 0, 0, 43,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 44, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 45, 3, 0, 2, 255, 0, 255, 0, 0, 0, 46, 0, 0,
        2, 255, 0, 255, 0, 0, 0, 47, 3, 0, 2, 255, 0, 255, 0, 0,
        0, 48, 1, 0, 7, 255, 0, 255, 0, 0, 0, 49, 1, 0, 8, 255,
        0, 255, 0, 0, 0, 50, 1, 0, 4, 255, 0, 255, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 1, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 2, 0, 0, 2, 255, 0, 255, 0, 0, 0, 3,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 4, 0, 0, 2, 255, 0, 255,
        0, 0, 0, 5, 1, 0, 2, 255, 0, 255, 0, 0, 0, 6, 1, 0,
        6, 255, 0, 255, 0, 0, 0, 7, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 8, 1, 0, 2, 255, 0, 255, 0, 0, 0, 9, 1, 0, 2, 255,
        0, 255, 0, 0, 0, 10, 1, 0, 2, 255, 0, 255, 0, 0, 0, 11,
        1, 0, 0, 1, 0, 255, 0, 0, 0, 12, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 13, 4, 0, 2, 255, 0, 255, 0, 0, 0, 14, 4, 0,
        2, 255, 0, 255, 0, 0, 0, 15, 4, 0, 0, 4, 0, 255, 0, 0,
        0, 16, 0, 0, 2, 255, 0, 255, 0, 0, 0, 17, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 18, 1, 0, 2, 255, 0, 255, 0, 0, 0, 19,
        1, 0, 2, 255, 0, 255, 0, 0, 0, 20, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 21, 3, 0, 2, 255, 0, 255, 0, 0, 0, 22, 1, 0,
        2, 255, 0, 255, 0, 0, 0, 23, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 24, 3, 0, 2, 255, 0, 255, 0, 0, 0, 25, 3, 0, 2, 255,
        0, 255, 0, 0, 0, 26, 3, 0, 0, 3, 0, 255, 0, 0, 0, 27,
        3, 0, 2, 255, 0, 255, 0, 0, 0, 28, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 29, 3, 0, 2, 255, 0, 255, 0, 0, 0, 30, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 31, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 32, 2, 0, 2, 255, 0, 255, 0, 0, 0, 33, 2, 0, 2, 255,
        0, 255, 0, 0, 0, 34, 2, 0, 2, 255, 0, 255, 0, 0, 0, 35,
        2, 0, 2, 255, 0, 255, 0, 0, 0, 36, 2, 0, 2, 255, 0, 255,
        0, 0, 0, 37, 2, 0, 0, 2, 0, 255, 0, 0, 0, 38, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 39, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 40, 5, 0, 5, 255, 0, 255, 0, 0, 0, 41, 5, 0, 2, 255,
        1, 255, 0, 0, 0, 42, 5, 0, 0, 5, 0, 255, 0, 0, 0, 43,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 44, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 45, 3, 0, 2, 255, 0, 255, 0, 0, 0, 46, 0, 0,
        2, 255, 0, 255, 0, 0, 0, 47, 3, 0, 2, 255, 0, 255, 0, 0,
        0, 48, 1, 0, 7, 255, 0, 255, 0, 0, 0, 49, 1, 0, 8, 255,
        0, 255, 0, 0, 0, 50, 1, 0, 4, 255, 0, 255, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 1, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 2, 0, 0, 2, 255, 0, 255, 0, 0, 0, 3,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 4, 0, 0, 2, 255, 0, 255,
        0, 0, 0, 5, 1, 0, 2, 255, 0, 255, 0, 0, 0, 6, 1, 0,
        6, 255, 0, 255, 0, 0, 0, 7, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 8, 1, 0, 2, 255, 0, 255, 0, 0, 0, 9, 1, 0, 2, 255,
        0, 255, 0, 0, 0, 10, 1, 0, 2, 255, 0, 255, 0, 0, 0, 11,
        1, 0, 0, 1, 0, 255, 0, 0, 0, 12, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 13, 4, 0, 2, 255, 0, 255, 0, 0, 0, 14, 4, 0,
        2, 255, 0, 255, 0, 0, 0, 15, 4, 0, 0, 4, 0, 255, 0, 0,
        0, 16, 0, 0, 2, 255, 0, 255, 0, 0, 0, 17, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 18, 1, 0, 2, 255, 0, 255, 0, 0, 0, 19,
        1, 0, 2, 255, 0, 255, 0, 0, 0, 20, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 21, 3, 0, 2, 255, 0, 255, 0, 0, 0, 22, 1, 0,
        2, 255, 0, 255, 0, 0, 0, 23, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 24, 3, 0, 2, 255, 0, 255, 0, 0, 0, 25, 3, 0, 2, 255,
        0, 255, 0, 0, 0, 26, 3, 0, 0, 3, 0, 255, 0, 0, 0, 27,
        3, 0, 2, 255, 0, 255, 0, 0, 0, 28, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 29, 3, 0, 2, 255, 0, 255, 0, 0, 0, 30, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 31, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 32, 2, 0, 2, 255, 0, 255, 0, 0, 0, 33, 2, 0, 2, 255,
        0, 255, 0, 0, 0, 34, 2, 0, 2, 255, 0, 255, 0, 0, 0, 35,
        2, 0, 2, 255, 0, 255, 0, 0, 0, 36, 2, 0, 2, 255, 0, 255,
        0, 0, 0, 37, 2, 0, 0, 2, 0, 255, 0, 0, 0, 38, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 39, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 40, 5, 0, 5, 255, 0, 255, 0, 0, 0, 41, 5, 0, 2, 255,
        1, 255, 0, 0, 0, 42, 5, 0, 0, 5, 0, 255, 0, 0, 0, 43,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 44, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 45, 3, 0, 2, 255, 0, 255, 0, 0, 0, 46, 0, 0,
        2, 255, 0, 255, 0, 0, 0, 47, 3, 0, 2, 255, 0, 255, 0, 0,
        0, 48, 1, 0, 7, 255, 0, 255, 0, 0, 0, 49, 1, 0, 8, 255,
        0, 255, 0, 0, 0, 50, 1, 0, 4, 255, 0, 255, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 1, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 2, 0, 0, 2, 255, 0, 255, 0, 0, 0, 3,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 4, 0, 0, 2, 255, 0, 255,
        0, 0, 0, 5, 1, 0, 2, 255, 0, 255, 0, 0, 0, 6, 1, 0,
        6, 255, 0, 255, 0, 0, 0, 7, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 8, 1, 0, 2, 255, 0, 255, 0, 0, 0, 9, 1, 0, 2, 255,
        0, 255, 0, 0, 0, 10, 1, 0, 2, 255, 0, 255, 0, 0, 0, 11,
        1, 0, 0, 1, 0, 255, 0, 0, 0, 12, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 13, 4, 0, 2, 255, 0, 255, 0, 0, 0, 14, 4, 0,
        2, 255, 0, 255, 0, 0, 0, 15, 4, 0, 0, 4, 0, 255, 0, 0,
        0, 16, 0, 0, 2, 255, 0, 255, 0, 0, 0, 17, 0, 0, 2, 255,
        0, 255, 0, 0, 0, 18, 1, 0, 2, 255, 0, 255, 0, 0, 0, 19,
        1, 0, 2, 255, 0, 255, 0, 0, 0, 20, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 21, 3, 0, 2, 255, 0, 255, 0, 0, 0, 22, 1, 0,
        2, 255, 0, 255, 0, 0, 0, 23, 1, 0, 2, 255, 0, 255, 0, 0,
        0, 24, 3, 0, 2, 255, 0, 255, 0, 0, 0, 25, 3, 0, 2, 255,
        0, 255, 0, 0, 0, 26, 3, 0, 0, 3, 0, 255, 0, 0, 0, 27,
        3, 0, 2, 255, 0, 255, 0, 0, 0, 28, 3, 0, 2, 255, 0, 255,
        0, 0, 0, 29, 3, 0, 2, 255, 0, 255, 0, 0, 0, 30, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 31, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 32, 2, 0, 2, 255, 0, 255, 0, 0, 0, 33, 2, 0, 2, 255,
        0, 255, 0, 0, 0, 34, 2, 0, 2, 255, 0, 255, 0, 0, 0, 35,
        2, 0, 2, 255, 0, 255, 0, 0, 0, 36, 2, 0, 2, 255, 0, 255,
        0, 0, 0, 37, 2, 0, 0, 2, 0, 255, 0, 0, 0, 38, 2, 0,
        2, 255, 0, 255, 0, 0, 0, 39, 2, 0, 2, 255, 0, 255, 0, 0,
        0, 40, 5, 0, 2, 255, 0, 255, 0, 0, 0, 41, 5, 0, 2, 255,
        0, 255, 0, 0, 0, 42, 5, 0, 0, 5, 0, 255, 0, 0, 0, 43,
        0, 0, 2, 255, 0, 255, 0, 0, 0, 44, 4, 0, 2, 255, 0, 255,
        0, 0, 0, 45, 3, 0, 2, 255, 0, 255, 0, 0, 0, 46, 0, 0,
        2, 255, 0, 255, 0, 0, 0, 47, 3, 0, 2, 255, 0, 255, 0, 0,
        0, 48, 1, 0, 7, 255, 0, 255, 0, 0, 0, 49, 1, 0, 8, 255,
        0, 255, 0, 0, 0, 50, 1, 0, 4, 255, 0, 255, 0, 0,
    },
};
u8 lbl_2_data_4B8C[4] = {0}; // alignment padding (unused)
MenuAsset lbl_2_data_4B90 = {0x0000040B, 0x40046100, 0x0E641000, 0x00024B48}; // ARAM load instructions
MenuArchive *lbl_2_data_4BA0 = (void*)&lbl_2_bss_1034C;
u32 lbl_2_data_4BA4 = 0x11775500; // unreferenced
GXColor lbl_2_data_4BA8 = {0, 0, 0, 0};
GXColor lbl_2_data_4BAC[2] = {{1, 0, 0, 1}, {2, 1, 0, 0}}; // follows lbl_2_data_4BA8 (unreferenced)

