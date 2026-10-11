#include "challenge/rep_0250.h"


#include "static/UnknownHomes_Static.h"
static u8 ch_data_AB0[0xD4] = {1};
static s32 ch_B84 = 1;
static u8 ch_padB88[0x40] = {1};
static u8 ch_BC8[0xA0] = {1};
static u8 ch_C68[0x356] = {1};
static u16 ch_FBE = 1;
extern u8* lbl_803CC1B8[];
extern u8 lbl_1_bss_2FAA;
extern u8 lbl_1_bss_2FB9;
extern void* fn_80034CEC(void*);
extern u8 lbl_1_data_B88[];
extern u8* lbl_80371C30[];
extern void fn_80034E20(void*, void*);
extern u8 lbl_1_data_CC8[];
extern u16 lbl_1_bss_2FAC;
extern u8* lbl_1_bss_2FCC;
extern s16* fn_80035F20(u8, s32, u16, s16);
extern void fn_80035ED0(s32);
extern void fn_80035EEC(s32, s32);
// Versus/score screen state (lbl_1_bss_2FA8).
typedef struct ChalScoreState {
    /*0x00*/ u8 pad00[2];
    /*0x02*/ u8 page;        // 0-11, also lbl_1_bss_2FAA
    /*0x03*/ u8 pad03;
    /*0x04*/ u16 animFrame;  // also lbl_1_bss_2FAC
    /*0x06*/ u8 _06;
    /*0x07*/ u8 mode;        // 0-2
    /*0x08*/ u8 _08;
    /*0x09*/ u8 _09;
    /*0x0A*/ u8 pad0A[0x10 - 0x0A];
    /*0x10*/ u8 _10;
    /*0x11*/ u8 shownPage;   // also lbl_1_bss_2FB9
    /*0x12*/ u8 pad12[0x18 - 0x12];
    /*0x18*/ u16 _18;
    /*0x1A*/ u8 pad1A[2];
    /*0x1C*/ s32 loadIdx;
    /*0x20*/ void* msgData;
    /*0x24*/ u8* scoreObj;   // queue object; also lbl_1_bss_2FCC
    /*0x28*/ u8 step;
} ChalScoreState;
extern ChalScoreState lbl_1_bss_2FA8;
extern u8 lbl_1_data_BC8[];
extern void fn_8003664C(u8, s32, u16, s32);
extern u16 fn_80036824(u8, s32, s32);
extern void fn_1_9290(void);
extern u32 lbl_1_data_B80;
extern u8 lbl_1_data_FBC;
extern void* lbl_80366158[];
extern void fn_80035A00(void*);
extern u8 lbl_8039C3E0[];

// .text:0x96D0 size:0x4
void fn_1_96D0(void) {
}

void fn_1_90B8(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_8F34, 2);
}

void fn_1_96A4(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_9380, 2);
}

void fn_1_97B8(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_973C, 2);
}

// .text:0x96D4 size:0x68
void fn_1_96D4(void) {
    u8* queue = *(u8**)lbl_803CC1B8;
    *(u16*)(queue + 0x18) += 1;
    if ((lbl_803C77B8._02 & 1) || (lbl_803C77B8._02 & 2)) {
        fn_800B0A14_removeQueue(fn_80034CEC(queue));
    }
    lbl_1_bss_2FB9 = lbl_1_bss_2FAA;
}

// .text:0x973C size:0x7C
void fn_1_973C(void* object) {
    u8* queue = *(u8**)lbl_803CC1B8;
    fn_80034E20(queue, lbl_1_data_B88);
    *(u8*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x66) = lbl_1_bss_2FAA;
    *(u16*)(queue + 0x18) = 0;
    **(void***)lbl_803CC1B8 = (void*)fn_1_96D4;
}

// .text:0x8CD4 size:0x78
void fn_1_8CD4(void) {
    s16* result = fn_80035F20(lbl_1_data_CC8[0x14], 1, lbl_1_bss_2FAC, (s16)(lbl_1_bss_2FAC + 2));
    *(f32*)(lbl_80371C30[*(u16*)(lbl_1_bss_2FCC + 0x14) * 2] + 0x48) = result[0x14 / 2];
    *(f32*)(lbl_80371C30[*(u16*)(lbl_1_bss_2FCC + 0x14) * 2] + 0x4C) = result[0x16 / 2];
    fn_80035ED0(1);
    lbl_1_bss_2FAC += 1;
    if (lbl_1_bss_2FAC > 3) {
        lbl_1_bss_2FAC = 0;
    }
}

// .text:0x9290 size:0xF0
void fn_1_9290(void) {
    ChalScoreState* b = &lbl_1_bss_2FA8;
    u8* queue = *(u8**)lbl_803CC1B8;
    *(u16*)(queue + 0x18) += 1;
    if (b->mode == 0) {
        fn_80035EEC(3, 0);
        fn_80035EEC(7, 1);
        fn_80035ED0(2);
    } else if (b->mode == 1) {
        fn_80035EEC(0xB, 0);
        fn_80035EEC(0xF, 1);
        fn_80035EEC(0x13, 2);
    } else {
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    if (b->shownPage != (s8)b->page) {
        fn_800B0A14_removeQueue(fn_80034CEC(queue));
    }
    if (lbl_803C77B8._02 & 0x200) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// .text:0x8DBC size:0x178
void fn_1_8DBC(void) {
    ChalScoreState* b = &lbl_1_bss_2FA8;
    u8* queue = *(u8**)lbl_803CC1B8;
    *(u16*)(queue + 0x18) += 1;
    if (b->mode == 1 || b->mode == 3) {
        if (lbl_8039C3E0[0x69] == 1) {
            s16* result;
            if (b->_06 == 0) {
                ((void (*)(void))fn_800B0A14_removeQueue)();
                b->_06 = 1;
                return;
            }
            result = fn_80035F20(lbl_1_data_CC8[0x14], 1, b->animFrame, (s16)(b->animFrame + 2));
            *(f32*)(lbl_80371C30[*(u16*)(b->scoreObj + 0x14) * 2] + 0x48) = result[0x14 / 2];
            *(f32*)(lbl_80371C30[*(u16*)(b->scoreObj + 0x14) * 2] + 0x4C) = result[0x16 / 2];
            fn_80035ED0(1);
            b->animFrame += 1;
            if (b->animFrame > 3) {
                b->animFrame = 0;
            }
        }
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    if ((lbl_803C77B8._02 & 1) || (lbl_803C77B8._02 & 2)) {
        fn_800B0A14_removeQueue(fn_80034CEC(queue));
    }
}

// .text:0x8F34 size:0x184
void fn_1_8F34(void* object) {
    ChalScoreState* b = &lbl_1_bss_2FA8;
    u8* queue = *(u8**)lbl_803CC1B8;
    if (lbl_803C77B8._02 & 0x200) {
        fn_800B0A14_removeQueue(fn_80034CEC(b->scoreObj));
        return;
    }
    b->scoreObj = queue;
    fn_80034E20(queue, lbl_1_data_CC8);
    if (b->mode == 1 || b->mode == 3) {
        s16* result = fn_80035F20(lbl_1_data_CC8[0x14], 1, b->animFrame, (s16)(b->animFrame + 2));
        *(f32*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x48) = result[0x14 / 2];
        *(f32*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x4C) = result[0x16 / 2];
        fn_80035ED0(1);
        b->animFrame += 1;
        if (b->animFrame > 3) {
            b->animFrame = 0;
        }
    } else {
        *(s16*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x64) = 7;
        fn_80035ED0(1);
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    **(void***)lbl_803CC1B8 = (void*)fn_1_8DBC;
}

// .text:0x90E4 size:0x1AC
void fn_1_90E4(s32 value) {
    fn_80034CEC(lbl_1_bss_2FCC);
    fn_80034E20(lbl_1_bss_2FCC, lbl_1_data_BC8);
    *(s32*)(lbl_80371C30[*(u16*)(lbl_1_bss_2FCC + 0x14) * 2] + 0x5C) = 0x80000;
    fn_8003664C(lbl_1_data_BC8[0x14], 0, (u16)(value / 1000 + 10), 4);
    value %= 1000;
    *(s32*)(lbl_80371C30[*(u16*)(lbl_1_bss_2FCC + 0x14) * 2 + 2] + 0x5C) = 0xC0000;
    fn_8003664C(lbl_1_data_BC8[0x14], 1, (u16)(value / 100 + 10), 5);
    value %= 100;
    *(s32*)(lbl_80371C30[*(u16*)(lbl_1_bss_2FCC + 0x14) * 2 + 4] + 0x5C) = 0x100000;
    fn_8003664C(lbl_1_data_BC8[0x14], 2, (u16)(value / 10 + 10), 6);
}

// .text:0x9380 size:0x324
void fn_1_9380(void* object) {
    u8* queue;
    ChalScoreState* b;
    u8 id;
    s32 value;
    u8* p;
    b = &lbl_1_bss_2FA8;
    queue = *(u8**)lbl_803CC1B8;
    p = ch_BC8;
    id = p[0x14];
    b->scoreObj = queue;
    if (b->mode == 0) {
        fn_80034E20(queue, p);
        { u16 n = fn_80036824(id, 1, 4); fn_8003664C(id, 0, n, 2); }
        fn_8003664C(id, 1, 0x11, 3);
    } else if (b->mode == 1) {
        fn_80034E20(queue, p);
        value = ch_B84;
        *(s32*)(lbl_80371C30[*(u16*)(b->scoreObj + 0x14) * 2] + 0x5C) = 0x80000;
        fn_8003664C(id, 0, (u16)(value / 1000 + 10), 4);
        value %= 1000;
        *(s32*)(lbl_80371C30[*(u16*)(b->scoreObj + 0x14) * 2 + 2] + 0x5C) = 0xC0000;
        fn_8003664C(id, 1, (u16)(value / 100 + 10), 5);
        value %= 100;
        *(s32*)(lbl_80371C30[*(u16*)(b->scoreObj + 0x14) * 2 + 4] + 0x5C) = 0x100000;
        fn_8003664C(id, 2, (u16)(value / 10 + 10), 6);
    } else {
        s16* result;
        u8* p2;
        fn_80034E20(queue, ch_C68);
        p2 = ch_C68;
        result = fn_80035F20(p2[0x14], 1, b->_18, -1);
        *(f32*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x48) = result[0x14 / 2] / 2;
        *(f32*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x4C) = result[0x16 / 2] / 2;
        fn_80035ED0(1);
        fn_8003664C(p2[0x14], 0, ch_FBE, 1);
        b->_18 += 1;
        if (b->_18 > 7) {
            b->_18 = 0;
        }
        ch_FBE += 1;
        if (ch_FBE > 9) {
            ch_FBE = 0;
        }
    }
    *(u16*)(queue + 0x18) = 0;
    **(void***)lbl_803CC1B8 = (void*)fn_1_9290;
}

// .text:0x97E4 size:0x2CC
void fn_1_97E4(void) {
    ChalScoreState* b = &lbl_1_bss_2FA8;
    u8* queue = *(u8**)lbl_803CC1B8;
    switch ((s32)*(u16*)((u8*)&lbl_803C77B8 + 4)) {
    case 0x100: {
        s32 n;
        b->_08 = 0;
        n = b->mode + 1;
        b->_09 = 0;
        b->step = 0;
        b->mode = n;
        if ((u8)n == 3) {
            b->mode = 0;
        }
        if ((s32)b->page != 0xB) {
            fn_80034CEC(b->scoreObj);
        }
        b->_06 = 0;
        break;
    }
    case 0x200:
        fn_80035A00(fn_80034CEC(b->scoreObj));
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
            b->_10 = 0;
            n = b->page + 1;
            b->page = n;
            if ((s8)(u8)n >= 12) {
                b->page = 0;
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
        b->step = 0;
        break;
    case 2:
        switch (queue[0x1A]) {
        case 0: {
            s32 n;
            b->_10 = 0;
            n = b->page - 1;
            b->page = n;
            if ((s8)(u8)n < 0) {
                b->page = 0xB;
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
        b->step = 0;
        break;
    case 3:
    case 0x10:
    case 0x40:
        break;
    }
}

extern void fn_800111B4(void* data);
extern u8 lbl_1_common_bss_47698[]; // TODO type

// fn_1_9AB0, size:0x3F0
// Score-screen task: loads the messages and 12 pages, then runs the page handlers and
// (in mode 1) counts the displayed score down.
// NONMATCHING 67%: the original reaches .data/.bss through pooled bases and keeps the clear loop rolled
#if NONMATCHING
void fn_1_9AB0(void) {
    ChalScoreState* b;
    u8* task;
    u8* p;
    s32 i;

    b = &lbl_1_bss_2FA8;
    task = *(u8**)lbl_803CC1B8;
    switch (*(s16*)(task + 0x10)) {
    case 0:
        fn_800111B4(lbl_1_data_CC8 + 0x1E0); // TODO type: message table inside lbl_1_data_CC8
        b->msgData = lbl_1_data_CC8 + 0x1E4;
        *(u16*)lbl_1_common_bss_47698 = 0;
        p = lbl_1_common_bss_47698 + 0xA;
        i = 10;
        do {
            p[2] = 0;
            p--;
        } while (--i != 0);
        lbl_1_common_bss_47698[0xC] = 0;
        task[0x1A] = 0;
        b->loadIdx = 0;
        b->page = 0;
        b->mode = 0;
        b->_09 = 1;
        b->step = 0;
        *(s16*)(*(u8**)lbl_803CC1B8 + 0x10) = 1;
        break;
    case 1:
        if (b->loadIdx > 11) {
            *(s16*)(task + 0x10) = 2;
            break;
        }
        // TODO type: 12 load records of 0x10 bytes inside lbl_1_data_CC8
        if (fn_80035838(lbl_1_data_CC8 + 0x244 + b->loadIdx * 0x10, (u8)b->loadIdx) != 0) {
            b->loadIdx++;
        }
        break;
    case 2:
        fn_1_97E4();
        switch ((s8)b->page) {
        case 0:
            if (b->step == 0) {
                b->step = 1;
                break;
            }
            if (b->mode == 1) {
                if (--ch_B84 < 0) {
                    ch_B84 = 3000;
                }
                if (ch_B84 % 10 == 0) {
                    fn_1_90E4(ch_B84);
                }
            }
            b->step = 2;
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
            if (b->step == 0) {
                b->step = 1;
                break;
            }
            if (b->step == 1) {
                fn_800B0A5C_insertQueue((void*)fn_1_973C, 2);
            }
            b->step = 2;
            break;
        case 11:
            if (b->step == 0) {
                b->step = 1;
                break;
            }
            b->step = 2;
            break;
        case 10:
            if (b->step == 0) {
                b->step = 1;
                break;
            }
            if (b->step == 1) {
                if (b->mode == 1 || b->mode == 3) {
                    fn_800B0A5C_insertQueue((void*)fn_1_8F34, 2);
                } else {
                    fn_800B0A5C_insertQueue((void*)fn_1_8F34, 2);
                }
            }
            b->step = 2;
            break;
        }
        break;
    }
}
#endif
