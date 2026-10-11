#include "challenge/rep_7BA0.h"
#include "main/file_800A7C08.h"
#include "main/file_800B0724.h"
#include "main/file_800ADC40.h"
#include "Dolphin/stl.h"

// THP player state for the movie test.
typedef struct ChMovieWork {
    /*0x0*/ u32 readBufSize;
    /*0x4*/ u8* readBuf;
    /*0x8*/ u8* work;
    /*0xC*/ ThpPlayer* player;
} ChMovieWork;

ChMovieWork lbl_1_bss_47058;
extern ThpMovie lbl_1_data_112D8[];
extern void* lbl_80366158[];
extern PadState lbl_803C77B8[4];

// .text:0x000282F4 size:0x1B4
void fn_1_282F4(void) {
    return;
}

// .text:0x000284A8 size:0x84
void fn_1_284A8(void) {
    return;
}

// .text:0x0002852C size:0x60
void fn_1_2852C(void) {
    ChMovieTask* task = lbl_803CC1B8;

    fn_800AD038(lbl_80366158[2]);
    task->state = 0;
    task->movieIdx = 0;
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_284A8;
}
