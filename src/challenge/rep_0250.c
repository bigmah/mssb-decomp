#include "challenge/rep_0250.h"
#define REP_HEADER_FN repHeader_0250
#include "header_rep_inline.h"
#include "static/UnknownHomes_Static.h"

extern u8* lbl_803CC1B8[];
extern void fn_80034CEC(void*);
extern u8* lbl_80371C30[];
extern void fn_80034E20(void*, ChSpaniDesc*);
extern s16* fn_80035F20(u8, s32, u16, s16);
extern void fn_80035ED0(s32);
extern void fn_80035EEC(s32, s32);
extern void fn_8003664C(u8, s32, u16, s32);
extern u16 fn_80036824(u8, s32, s32);
extern void* lbl_80366158[];
extern void fn_80035A00(void);
extern u8 lbl_8039C3E0[];


// Viewer menu: entry count, then the entry names.
typedef struct ChalViewerMenu {
    /*0x00*/ u16 count;
    /*0x02*/ u8 pad02[0x1E];
    /*0x20*/ char names[5][0x20];
} ChalViewerMenu;

// Message table as on disc (MsgTable, main/file_8000F150.h): offsets from the
// table start until fn_800111B4 relocates them, then the message tokens.
typedef struct ChalMsgTable {
    /*0x00*/ u16 count;
    /*0x02*/ u16 _02;
    /*0x04*/ u32 msgs[3];
    /*0x10*/ u16 text[42];
} ChalMsgTable;

static ChalViewerMenu lbl_1_data_AB0 = {
    3,
    { 0 },
    { " 2D   VIEWER", "MOVIE VIEWER", "TEST MOVIE 0", "TEST MOVIE 1", "TEST MOVIE 2" },
};
ChFileEntry lbl_1_data_B70 = { 0x40B, 0x4037CF5C, 0x18B3A800, 0x208AF0 }; // loaded by fn_1_8770
static u32 lbl_1_data_B80 = 0x10000;
static s32 lbl_1_data_B84 = 3000; // score shown on page 0, counts down in mode 1
static ChSpaniDesc lbl_1_data_B88[2] = { CH_SPANI(0, 0), CH_SPANI_END };
static ChSpaniDesc lbl_1_data_BC8[5] = { CH_SPANI(0, 0), CH_SPANI(0, 0), CH_SPANI(0, 0), CH_SPANI(2, 0), CH_SPANI_END };
static ChSpaniDesc lbl_1_data_C68[3] = { CH_SPANI(5, 0), CH_SPANI(4, 0), CH_SPANI_END };
static ChSpaniDesc lbl_1_data_CC8[3] = { CH_SPANI(8, 10), CH_SPANI(9, 10), CH_SPANI_END };
static char lbl_1_data_D28[12][0x20] = {
    "TEX_TEST1", "TEX_TEST2", "TEX_TEST3", "TEX_TEST4", "TEX_TEST5", "TEX_TEST6",
    "TEX_TEST7", "TEX_TEST8", "TEX_TEST9", "TEX_TEST10", "TEX_TEST11", "GAME_TD",
};
static ChalMsgTable lbl_1_data_EA8 = {
    3, 0x0D0E, { 0x10, 0x2E, 0x4C },
    {
        0x83A4, 0x8946, 0x4002, 0x8326, 0x8598, 0x4002, 0x007C, 0x004D, 0x008A, 0x003E, 0x0090, 0x4002,
        0x8259, 0x8CC5, 0x4000, 0x0027, 0x0036, 0x0024, 0x0027, 0x0024, 0x0036, 0x0027, 0x0036, 0x0024,
        0x0029, 0x0024, 0x0027, 0x0036, 0x0029, 0x4000, 0x002A, 0x0027, 0x0036, 0x002A, 0x0029, 0x0036,
        0x002B, 0x0029, 0x0036, 0x0036, 0x002B, 0x4000,
    },
};
// The 12 page textures (fn_1_9AB0 loads one per frame).
static ChFileEntry lbl_1_data_F0C[11] = {
    { 0x40B, 0x4005BDE4, 0x0EAB5000, 0x161A0 },
    { 0x40B, 0x40002BDC, 0x0EACB800, 0x1430 },
    { 0x40B, 0x40004E98, 0x0EACD000, 0x1E18 },
    { 0x40B, 0x40011910, 0x0EACF000, 0x6C30 },
    { 0x40B, 0x40006038, 0x0EAD6000, 0x338C },
    { 0x40B, 0x40006044, 0x0EAD9800, 0x3390 },
    { 0x40B, 0x40004380, 0x0EADD000, 0x18DC },
    { 0x40B, 0x4000124C, 0x0EADF000, 0x488 },
    { 0x40B, 0x40000478, 0x0EADF800, 0x208 },
    { 0x40B, 0x40002E6C, 0x0EAE0000, 0x1510 },
    { 0x40B, 0x4000785C, 0x0EAE1800, 0x23A8 },
};
static u8 lbl_1_data_FBC = 1; // set/cleared with Y/X (fn_1_97E4)
static u16 lbl_1_data_FBE = 3; // number shown by the third page mode, 0..9

// Score screen state. .bss is laid out in reverse definition order, and the
// functions reach these through one pooled base (sScoreUnk00).
static u8 sScoreStep;        // 0x2FD0
static u8* sScoreObj;        // 0x2FCC: queue object of the shown page
static void* sScoreMsgData;  // 0x2FC8
static s32 sScoreLoadIdx;    // 0x2FC4: next page texture to load
static u16 sScoreUnk1A;      // 0x2FC2 (unused)
static u16 sScore18;         // 0x2FC0
static u32 sScoreUnk14;      // 0x2FBC (unused)
static u16 sScoreUnk12;      // 0x2FBA (unused)
static u8 sScoreShownPage;   // 0x2FB9
static u8 sScore10;          // 0x2FB8
static u32 sScoreUnk0C;      // 0x2FB4 (unused)
static u16 sScoreUnk0A;      // 0x2FB2 (unused)
static u8 sScore09;          // 0x2FB1
static u8 sScore08;          // 0x2FB0
static u8 sScoreMode;        // 0x2FAF: 0-2
static u8 sScore06;          // 0x2FAE
static u16 sScoreAnimFrame;  // 0x2FAC
static u8 sScoreUnk03;       // 0x2FAB (unused)
static u8 sScorePage;        // 0x2FAA: 0-11
static u8 sScoreUnk01;       // 0x2FA9 (unused)
static u8 sScoreUnk00;       // 0x2FA8

extern void fn_800111B4(void* data);
extern u8 lbl_1_common_bss_47698[]; // TODO type

// .text:0x00009AB0 size:0x3F0
// Score-screen task: loads the messages and 12 pages, then runs the page handlers and
// (in mode 1) counts the displayed score down.
void fn_1_9AB0(void) {
    u8* task;
    s32 i;
    u8* p;
    task = *(u8**)lbl_803CC1B8;
    switch (*(s16*)(task + 0x10)) {
    case 0:
        fn_800111B4(&lbl_1_data_EA8);
        sScoreMsgData = lbl_1_data_EA8.msgs;
        *(u16*)lbl_1_common_bss_47698 = 0;
        p = lbl_1_common_bss_47698 + 0xA;
        i = 10;
        do {
            p[2] = 0;
            p--;
        } while (--i != 0);
        lbl_1_common_bss_47698[0xC] = 0;
        task[0x1A] = 0;
        sScoreLoadIdx = 0;
        sScorePage = 0;
        sScoreMode = 0;
        sScore09 = 1;
        sScoreStep = 0;
        *(s16*)(*(u8**)lbl_803CC1B8 + 0x10) = 1;
        break;
    case 1:
        if (sScoreLoadIdx > 11) {
            *(s16*)(*(u8**)lbl_803CC1B8 + 0x10) = 2;
            break;
        }
        if (fn_80035838(&lbl_1_data_F0C[sScoreLoadIdx], (u8)sScoreLoadIdx) != 0) {
            sScoreLoadIdx++;
        }
        break;
    case 2:
        fn_1_97E4();
        switch ((s8)sScorePage) {
        case 0:
            if (sScoreStep == 0) {
                sScoreStep = 1;
                break;
            }
            if (sScoreMode == 1) {
                if (--lbl_1_data_B84 < 0) {
                    lbl_1_data_B84 = 3000;
                }
                if (lbl_1_data_B84 % 10 == 0) {
                    fn_1_90E4(lbl_1_data_B84);
                }
            }
            sScoreStep = 2;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if (sScoreStep == 0) {
                sScoreStep = 1;
                break;
            }
            if (sScoreStep == 1) {
                fn_800B0A5C_insertQueue((void*)fn_1_973C, 2);
            }
            sScoreStep = 2;
            break;
        case 11:
            if (sScoreStep == 0) {
                sScoreStep = 1;
                break;
            }
            sScoreStep = 2;
            break;
        case 10:
            if (sScoreStep == 0) {
                sScoreStep = 1;
                break;
            }
            if (sScoreStep == 1) {
                if (sScoreMode == 1 || sScoreMode == 3) {
                    fn_800B0A5C_insertQueue((void*)fn_1_8F34, 2);
                } else {
                    fn_800B0A5C_insertQueue((void*)fn_1_8F34, 2);
                }
            }
            sScoreStep = 2;
            break;
        }
        break;
    }
}

// .text:0x97E4 size:0x2CC
void fn_1_97E4(void) {
    u8* queue = *(u8**)lbl_803CC1B8;
    switch ((s32)*(u16*)((u8*)&lbl_803C77B8 + 4)) {
    case 0x100: {
        s32 n;
        sScore08 = 0;
        n = sScoreMode + 1;
        sScore09 = 0;
        sScoreStep = 0;
        sScoreMode = n;
        if ((u8)n == 3) {
            sScoreMode = 0;
        }
        if ((s32)sScorePage != 0xB) {
            fn_80034CEC(sScoreObj);
        }
        sScore06 = 0;
        break;
    }
    case 0x200:
        fn_80034CEC(sScoreObj);
        fn_80035A00(); // r3 still holds fn_80034CEC's leftover; fn_80035A00 takes none
        fn_800AD038(lbl_80366158[2]);
        *(s16*)(*(u8**)(queue + 0xC) + 0x10) = 1;
        break;
    case 0x800:
        lbl_1_data_FBC = 1;
        break;
    case 0x400:
        lbl_1_data_FBC = 0;
        break;
    case 0x20:
        lbl_1_data_B80 = 0;
        break;
    case 0x1000:
        lbl_1_data_B80 = 0x10000;
        break;
    case 8:
        if (queue[0x1A] != 0) {
            queue[0x1A] = queue[0x1A] - 1;
        } else {
            queue[0x1A] = 1;
        }
        break;
    case 4:
        queue[0x1A] = queue[0x1A] + 1;
        if (queue[0x1A] == 2) {
            queue[0x1A] = 0;
        }
        break;
    case 1:
        switch (queue[0x1A]) {
        case 0: {
            s32 n;
            sScore10 = 0;
            n = sScorePage + 1;
            sScorePage = n;
            if ((s8)(u8)n >= 12) {
                sScorePage = 0;
            }
            break;
        }
        case 1:
            lbl_1_data_B80 += 1000;
            if (lbl_1_data_B80 > 0x70000) {
                lbl_1_data_B80 = 0x70000;
            }
            break;
        }
        sScoreStep = 0;
        break;
    case 2:
        switch (queue[0x1A]) {
        case 0: {
            s32 n;
            sScore10 = 0;
            n = sScorePage - 1;
            sScorePage = n;
            if ((s8)(u8)n < 0) {
                sScorePage = 0xB;
            }
            break;
        }
        case 1:
            lbl_1_data_B80 -= 1000;
            if (lbl_1_data_B80 >= (u32)-1000) {
                lbl_1_data_B80 = 0;
            }
            break;
        }
        sScoreStep = 0;
        break;
    case 3:
    case 0x10:
    case 0x40:
        break;
    }
}

// .text:0x000097B8 size:0x2C
void fn_1_97B8(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_973C, 2);
}

// .text:0x973C size:0x7C
void fn_1_973C(void* object) {
    u8* queue = *(u8**)lbl_803CC1B8;
    fn_80034E20(queue, lbl_1_data_B88);
    *(u8*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x66) = sScorePage;
    *(u16*)(queue + 0x18) = 0;
    **(void***)lbl_803CC1B8 = (void*)fn_1_96D4;
}

// .text:0x96D4 size:0x68
void fn_1_96D4(void) {
    u8* queue = *(u8**)lbl_803CC1B8;
    *(u16*)(queue + 0x18) += 1;
    if ((lbl_803C77B8._02 & 1) || (lbl_803C77B8._02 & 2)) {
        fn_80034CEC(queue);
        REMOVE_QUEUE_NOARG();
    }
    sScoreShownPage = sScorePage;
}

// .text:0x96D0 size:0x4
void fn_1_96D0(void) {
}

// .text:0x000096A4 size:0x2C
void fn_1_96A4(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_9380, 2);
}

// .text:0x9380 size:0x324
void fn_1_9380(void* object) {
    u8* queue;
    u8 id;
    s32 value;
    ChSpaniDesc* p;
    queue = *(u8**)lbl_803CC1B8;
    p = lbl_1_data_BC8;
    id = p->texId;
    sScoreObj = queue;
    if (sScoreMode == 0) {
        fn_80034E20(queue, p);
        { u16 n = fn_80036824(id, 1, 4); fn_8003664C(id, 0, n, 2); }
        fn_8003664C(id, 1, 0x11, 3);
    } else if (sScoreMode == 1) {
        fn_80034E20(queue, p);
        value = lbl_1_data_B84;
        *(s32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2] + 0x5C) = 0x80000;
        fn_8003664C(id, 0, (u16)(value / 1000 + 10), 4);
        value %= 1000;
        *(s32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2 + 2] + 0x5C) = 0xC0000;
        fn_8003664C(id, 1, (u16)(value / 100 + 10), 5);
        value %= 100;
        *(s32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2 + 4] + 0x5C) = 0x100000;
        fn_8003664C(id, 2, (u16)(value / 10 + 10), 6);
    } else {
        s16* result;
        ChSpaniDesc* p2;
        fn_80034E20(queue, lbl_1_data_C68);
        p2 = lbl_1_data_C68;
        result = fn_80035F20(p2->texId, 1, sScore18, -1);
        *(f32*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x48) = result[0x14 / 2] / 2;
        *(f32*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x4C) = result[0x16 / 2] / 2;
        fn_80035ED0(1);
        fn_8003664C(p2->texId, 0, lbl_1_data_FBE, 1);
        sScore18 += 1;
        if (sScore18 > 7) {
            sScore18 = 0;
        }
        lbl_1_data_FBE += 1;
        if (lbl_1_data_FBE > 9) {
            lbl_1_data_FBE = 0;
        }
    }
    *(u16*)(queue + 0x18) = 0;
    **(void***)lbl_803CC1B8 = (void*)fn_1_9290;
}

// .text:0x9290 size:0xF0
void fn_1_9290(void) {
    u8* queue = *(u8**)lbl_803CC1B8;
    *(u16*)(queue + 0x18) += 1;
    if (sScoreMode == 0) {
        fn_80035EEC(3, 0);
        fn_80035EEC(7, 1);
        fn_80035ED0(2);
    } else if (sScoreMode == 1) {
        fn_80035EEC(0xB, 0);
        fn_80035EEC(0xF, 1);
        fn_80035EEC(0x13, 2);
    } else {
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    if (sScoreShownPage != (s8)sScorePage) {
        fn_80034CEC(queue);
        REMOVE_QUEUE_NOARG();
    }
    if (lbl_803C77B8._02 & 0x200) {
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x90E4 size:0x1AC
void fn_1_90E4(s32 value) {
    fn_80034CEC(sScoreObj);
    fn_80034E20(sScoreObj, lbl_1_data_BC8);
    *(s32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2] + 0x5C) = 0x80000;
    fn_8003664C(lbl_1_data_BC8[0].texId, 0, (u16)(value / 1000 + 10), 4);
    value %= 1000;
    *(s32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2 + 2] + 0x5C) = 0xC0000;
    fn_8003664C(lbl_1_data_BC8[0].texId, 1, (u16)(value / 100 + 10), 5);
    value %= 100;
    *(s32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2 + 4] + 0x5C) = 0x100000;
    fn_8003664C(lbl_1_data_BC8[0].texId, 2, (u16)(value / 10 + 10), 6);
}

// .text:0x000090B8 size:0x2C
void fn_1_90B8(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_8F34, 2);
}

// .text:0x8F34 size:0x184
void fn_1_8F34(void* object) {
    u8* queue = *(u8**)lbl_803CC1B8;
    if (lbl_803C77B8._02 & 0x200) {
        fn_80034CEC(sScoreObj);
        REMOVE_QUEUE_NOARG();
        return;
    }
    sScoreObj = queue;
    fn_80034E20(queue, lbl_1_data_CC8);
    if (sScoreMode == 1 || sScoreMode == 3) {
        s16* result = fn_80035F20(lbl_1_data_CC8[0].texId, 1, sScoreAnimFrame, (s16)(sScoreAnimFrame + 2));
        *(f32*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x48) = result[0x14 / 2];
        *(f32*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x4C) = result[0x16 / 2];
        fn_80035ED0(1);
        sScoreAnimFrame += 1;
        if (sScoreAnimFrame > 3) {
            sScoreAnimFrame = 0;
        }
    } else {
        *(s16*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x64) = 7;
        fn_80035ED0(1);
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    **(void***)lbl_803CC1B8 = (void*)fn_1_8DBC;
}

// .text:0x8DBC size:0x178
void fn_1_8DBC(void) {
    u8* queue = *(u8**)lbl_803CC1B8;
    *(u16*)(queue + 0x18) += 1;
    if (sScoreMode == 1 || sScoreMode == 3) {
        if (lbl_8039C3E0[0x69] == 1) {
            s16* result;
            if (sScore06 == 0) {
                REMOVE_QUEUE_NOARG();
                sScore06 = 1;
                return;
            }
            result = fn_80035F20(lbl_1_data_CC8[0].texId, 1, sScoreAnimFrame, (s16)(sScoreAnimFrame + 2));
            *(f32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2] + 0x48) = result[0x14 / 2];
            *(f32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2] + 0x4C) = result[0x16 / 2];
            fn_80035ED0(1);
            sScoreAnimFrame += 1;
            if (sScoreAnimFrame > 3) {
                sScoreAnimFrame = 0;
            }
        }
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    if ((lbl_803C77B8._02 & 1) || (lbl_803C77B8._02 & 2)) {
        fn_80034CEC(queue);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x8CD4 size:0x78
void fn_1_8CD4(void) {
    s16* result = fn_80035F20(lbl_1_data_CC8[0].texId, 1, sScoreAnimFrame, (s16)(sScoreAnimFrame + 2));
    *(f32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2] + 0x48) = result[0x14 / 2];
    *(f32*)(lbl_80371C30[*(u16*)(sScoreObj + 0x14) * 2] + 0x4C) = result[0x16 / 2];
    fn_80035ED0(1);
    sScoreAnimFrame += 1;
    if (sScoreAnimFrame > 3) {
        sScoreAnimFrame = 0;
    }
}
