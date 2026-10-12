// High-level emulation of the GameCube DSP audio microcode used by MusyX (an
// "AX"-style command-list ucode). See dsp_ax.cpp.
#pragma once

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

// Executes the command list at physical address `listAddr` (a game-heap
// offset, as mailed by MusyX's salStartDsp) to completion.
void dsp_ax_execute(u32 listAddr);

// Forget all mixer state (DSP reset).
void dsp_ax_reset(void);

#ifdef __cplusplus
}
#endif
