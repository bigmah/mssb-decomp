#ifndef __CHALLENGE_AUTO_00_00009EA0_TEXT_H_
#define __CHALLENGE_AUTO_00_00009EA0_TEXT_H_

#include "mssbTypes.h"

// One row of a scrolling list (fn_1_A184 only reads the name).
typedef struct ChListItem {
    /*0x0*/ char* name;
    /*0x4*/ u8 _4[0xC];
} ChListItem; // size: 0x10

// Scrolling list cursor: `cursor` is the selected item, `top` the first visible one.
typedef struct ChListCursor {
    /*0x00*/ ChListItem* items;
    /*0x04*/ s32 cursor;
    /*0x08*/ s32 top;
    /*0x0C*/ s32 visible; // rows per page
    /*0x10*/ s32 count;
} ChListCursor;

// fn_1_A024 directions
#define CH_LIST_UP        0
#define CH_LIST_DOWN      1
#define CH_LIST_PAGE_UP   2
#define CH_LIST_PAGE_DOWN 3

void fn_1_9EA0(u8 group, s32 (*callback)(u8* state));
void fn_1_9F04(void);
void fn_1_A024(ChListCursor* list, s32 dir);
void fn_1_A184(ChListCursor* list);
void fn_1_A1F4(ChListCursor* list, ChListItem* items, s32 count, s32 visible);
char* fn_1_A210(char* path);
void fn_1_A250(void);

#endif
