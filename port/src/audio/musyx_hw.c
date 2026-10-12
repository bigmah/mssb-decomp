// Dropped from the Strikers 2.0.3 MusyX fork (unused by the game) but still
// referenced by hardware.c.
#include "musyx/dspvoice.h"
bool salAddStudioInput(DSPstudioinfo* stp, SND_STUDIO_INPUT* desc) { (void)stp; (void)desc; return false; }
bool salRemoveStudioInput(DSPstudioinfo* stp, SND_STUDIO_INPUT* desc) { (void)stp; (void)desc; return false; }
void salDeactivateStudio(u8 studio) { dspStudio[studio].state = 0; }
void salReconnectVoice(DSPvoice* dsp_vptr, u8 studio) { (void)dsp_vptr; (void)studio; }
