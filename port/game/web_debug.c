// ?debug on the web build: every two seconds the game's disc loader and OS
// threads are written to the console (which ?debug sends to the site's log),
// to see what a phone is waiting on when it stalls.
#ifdef __EMSCRIPTEN__
#include <stdio.h>

#include "mssbTypes.h"
#include "main/aramloader.h"
#include "main/file_800ADC40.h"

extern MovPlayer* lbl_803CC170;
extern u8 lbl_803CC17C, lbl_803CC17D, lbl_803CC17E, lbl_803CC181;
extern s32 lbl_803CC19C;

void port_debug_threads(void); // port/web/src/os_threads_web.inc

void port_debug_dump(void) {
    ARAMLoader* l = &lbl_803C6CF8;
    printf("[dbg] dvdsys state %d idle %d mode %d entry %d read %u/%u remaining %d drive %d cmd %d decomp write %d err %d\n",
           (int)l->state, (int)l->idle, (int)l->mode, (int)l->entryNum, (unsigned)l->bytesRead,
           (unsigned)l->totalSize, (int)l->remaining, (int)DVDGetDriveStatus(),
           l->fileInfo != NULL ? (int)DVDGetCommandBlockStatus(&l->fileInfo->cb) : -9,
           (int)gDataDecompressorValues.ShouldWriteDataFlag, (int)gDataDecompressorValues.error);
    if (lbl_803CC170 != NULL) {
        MovPlayer* m = lbl_803CC170;
        printf("[dbg] movie state %d flags %d decoding %d frame %u/%u quit %d 17D %d decodeThread %d inAram %d result %d\n",
               (int)m->state, (int)m->flags, (int)m->decoding, (unsigned)m->curFrame, (unsigned)m->numFrames,
               (int)lbl_803CC17C, (int)lbl_803CC17D, (int)lbl_803CC17E, (int)lbl_803CC181, (int)lbl_803CC19C);
    }
    port_debug_threads();
}
#endif
