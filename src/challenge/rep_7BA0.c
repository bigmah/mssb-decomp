#include "challenge/rep_7BA0.h"
#include "main/file_800A7C08.h"
#include "main/file_800B0724.h"
#include "main/file_800ADC40.h"
#include "Dolphin/stl.h"
#define REP_HEADER_FN repHeader_7BA0
#include "header_rep_inline.h"

// THP player state for the movie test.
typedef struct ChMovieWork {
    /*0x0*/ u32 readBufSize;
    /*0x4*/ u8* readBuf;
    /*0x8*/ u8* work;
    /*0xC*/ ThpPlayer* player;
} ChMovieWork;

static ChMovieWork lbl_1_bss_47058;
// The two test movies (DVD offset/size pairs, see ThpMovie).
ThpMovie lbl_1_data_112D8[2] = {
    { { 0x00, 0x00, 0x00, 0x00, 0x05, 0x23, 0x34, 0x58, 0x00, 0x01, 0x20, 0x00 }, 0x05233458 },
    { { 0 }, 0 },
};
static u32 lbl_1_data_112F8[2] = { 0, 0 }; // unreferenced, follows the movie table
extern void* lbl_80366158[];
extern PadState lbl_803C77B8[4];

// .text:0x0002852C size:0x60
void fn_1_2852C(void) {
    ChMovieTask* task = lbl_803CC1B8;

    fn_800AD038(lbl_80366158[2]);
    task->state = 0;
    task->movieIdx = 0;
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_284A8;
}

// .text:0x000284A8 size:0x84
void fn_1_284A8(void) {
    ChMovieTask* task = lbl_803CC1B8;
    u16 repeated = lbl_803C77B8[0].repeat;

    if (repeated & 3) {
        task->movieIdx ^= 1;
    } else if (repeated & 0x100) {
        task->state = 0;
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_282F4;
    } else if (repeated & 0x200) {
        ChTaskHeader* parent = task->h.parent;
        parent->result = 1;
        fn_800B0A14_removeQueue(parent);
    }
}

// .text:0x000282F4 size:0x1B4
void fn_1_282F4(void) {
    ChMovieWork* w = &lbl_1_bss_47058;
    ChMovieTask* task = lbl_803CC1B8;
    u32 size;

    switch (task->state) {
    case 0:
        w->player = _OSAllocFromHeap(0x20, sizeof(ThpPlayer));
        memset(w->player, 0, sizeof(ThpPlayer));
        w->readBufSize = 0x400000;
        w->readBuf = _OSAllocFromHeap(0x20, 0x400000);
        fn_800ADC40(w->readBuf, w->readBufSize);
        task->state++;
        break;
    case 1:
        fn_800ADB04(&lbl_1_data_112D8[task->movieIdx], w->player, 1, 0);
        task->state++;
    case 2:
        if (fn_800ADAFC() != 0) {
            size = fn_800AD6BC(w->player);
            w->work = _OSAllocFromHeap(0x20, size);
            fn_800AD500(w->player, w->work);
            fn_800AD95C(w->player, 1);
            task->state++;
        }
        break;
    case 3:
        if (lbl_803C77B8[0].down & 0x200) {
            fn_800AD830(w->player);
            task->state++;
        }
    case 4:
        if (fn_800AD780(w->player)) {
            fn_800AD9F4(w->player);
            fn_800ADBFC();
            fn_800AD038(lbl_80366158[2]);
            task->state = 0;
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_284A8;
        } else {
            fn_800AD070();
        }
        break;
    }
}
