#include "game/auto_00_0008B094_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_800A7C08.h"

extern void* lbl_803CC1B8;
extern StreamTrack lbl_8034E478[16];
extern u8 lbl_800E87B4[15][16]; // TODO type: stream file descriptors

// .text:0x0008B094 size:0x1C4 mapped:0x806CA128
// NONMATCHING 93%: original keeps i*3+0x17 in r30 and uses lbzx/stbx for req[i].step
#if NONMATCHING
void fn_3_8B094(void) {
    StreamQueueTask* task = lbl_803CC1B8;
    u8 i;
    s8 track;
    s32 volume;
    u8 next;

    if (task->head != task->tail && fn_800A88C8() != 3) {
        i = task->tail;
        volume = task->req[i].volume;
        track = task->req[i].track;
        next = (i + 1) % 14;
        switch (task->req[i].step) {
        case 0:
            fn_800A8878(volume, volume);
            if (&lbl_8034E478[track] == fn_800A88C0()) {
                task->req[i].step = 2;
                return;
            }
            fn_800A8AB8(NULL);
            task->req[i].step++;
            return;
        case 1:
            fn_800A8AB0(2);
            LoadFile(lbl_800E87B4[track], &lbl_8034E478[track], 0, NULL, 1);
            task->req[i].step++;
        case 2:
            if (fn_800A8518(1) != 0) {
                task->tail = next;
            }
            break;
        case 3:
            if (fn_800A88D0() == 0 || fn_800A8518(2) != 0) {
                task->tail = next;
            }
            break;
        case 4:
            if (fn_800A8518(3) != 0) {
                task->tail = next;
            }
            break;
        }
    }
}
#endif
