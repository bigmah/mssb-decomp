#ifndef __CHALLENGE_REP_7BA0_H_
#define __CHALLENGE_REP_7BA0_H_

#include "mssbTypes.h"
#include "challenge/rep_0010.h"

// Movie-player test task (fn_1_282F4 / fn_1_284A8).
typedef struct ChMovieTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ u8 state;
    /*0x15*/ u8 movieIdx; // 0 or 1, index into lbl_1_data_112D8
} ChMovieTask;

void fn_1_282F4(void);
void fn_1_284A8(void);
void fn_1_2852C(void);

#endif
