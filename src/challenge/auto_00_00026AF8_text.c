#include "challenge/auto_00_00026AF8_text.h"
#include "challenge/rep_0010.h"

extern void fn_80035A00(void);
extern void fn_1_26928(void);

// Music test task (rep_7730 accesses it by offset).
typedef struct ChMusicTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ u8 _14[0x1E - 0x14];
    /*0x1E*/ u8 step;
    /*0x1F*/ u8 count; // entries in lbl_1_data_FB98
    /*0x20*/ u8 sel;
    /*0x21*/ u8 _21;
    /*0x22*/ u8 _22;
} ChMusicTask;

// lbl_1_data_FB98 entry (ARAM file record for fn_80035838); a zero id ends the table.
typedef struct ChMusicEntry {
    /*0x0*/ u32 id;
    /*0x4*/ u8 _4[0xC];
} ChMusicEntry;

extern ChMusicEntry lbl_1_data_FB98[];

// .text:0x00026AF8 size:0x84
void fn_1_26AF8(void) {
    ChMusicTask* task = lbl_803CC1B8;

    task->step = 0;
    task->sel = 0;
    task->_21 = 0;
    task->count = 0;
    task->_22 = 0;
    while (lbl_1_data_FB98[task->count].id != 0) {
        task->count++;
    }
    fn_80035A00();
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_26928;
}
