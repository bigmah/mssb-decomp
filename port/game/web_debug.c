// ?debug on the web build: every two seconds the game's disc loader and OS
// threads are written to the console (which ?debug sends to the site's log),
// to see what a phone is waiting on when it stalls.
#ifdef __EMSCRIPTEN__
#include <stdio.h>

#include "mssbTypes.h"
#include "main/aramloader.h"

void port_debug_threads(void); // port/web/src/os_threads_web.inc

void port_debug_dump(void) {
    ARAMLoader* l = &lbl_803C6CF8;
    printf("[dbg] dvdsys state %d idle %d mode %d entry %d read %u/%u remaining %d drive %d cmd %d decomp write %d err %d\n",
           (int)l->state, (int)l->idle, (int)l->mode, (int)l->entryNum, (unsigned)l->bytesRead,
           (unsigned)l->totalSize, (int)l->remaining, (int)DVDGetDriveStatus(),
           l->fileInfo != NULL ? (int)DVDGetCommandBlockStatus(&l->fileInfo->cb) : -9,
           (int)gDataDecompressorValues.ShouldWriteDataFlag, (int)gDataDecompressorValues.error);
    port_debug_threads();
}
#endif
