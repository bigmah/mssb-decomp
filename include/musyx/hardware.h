#ifndef _MUSYX_HARDWARE
#define _MUSYX_HARDWARE

#include "musyx/musyx_priv.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DSPADPCMblock {
  // total size: 0x6
  signed short Y0;        // offset 0x0, size 0x2
  signed short Y1;        // offset 0x2, size 0x2
  unsigned char PS;       // offset 0x4, size 0x1
  unsigned char reserved; // offset 0x5, size 0x1
} DSPADPCMblock;

typedef struct DSPADPCMplusInfo {
  // total size: 0x2E
  unsigned short numCoef;     // offset 0x0, size 0x2
  unsigned char initialPS;    // offset 0x2, size 0x1
  unsigned char loopPS;       // offset 0x3, size 0x1
  signed short loopY0;        // offset 0x4, size 0x2
  signed short loopY1;        // offset 0x6, size 0x2
  signed short coefTab[8][2]; // offset 0x8, size 0x20
  DSPADPCMblock blk[1];       // offset 0x28, size 0x6
} DSPADPCMplusInfo;

bool32 hwIsStudioActive(u8 studio);
void* hwGetStreamPlayBuffer(u8 hwStreamHandle);
s32 hwInit(u32* frq, u16 numVoices, u16 numStudios, u32 flags); /* extern */
void hwInitSamplePlayback(u32 v, u16 smpID, void* newsmp, u32 set_defadsr, u32 prio,
                          u32 callbackUserValue, u32 setSRC, u8 itdMode);
void hwSetVolume(u32 v, u8 table, float vol, u32 pan, u32 span, float auxa, float auxb);
void hwSetPitch(u32 v, u16 speed);
void hwEnableIrq();
void hwDisableIrq();
void* hwTransAddr(void* samples);
void hwExitStream(u8 id);
void hwSaveSample(void* header, void* data, void* extra);
void hwRemoveSample(void *header, void *data, void *aramWrite);
u32 hwGetVirtualSampleState(u32 voice);
bool32 hwVoiceInStartup(u32 v);
void hwBreak(s32 vid);
u32 hwGetPos(u32 v);
void hwInitSampleMem(u32 baseAddr, u32 length);
void hwExitSampleMem();
void hwSetVirtualSampleLoopBuffer(u32 voice, void* addr, u32 len);
u16 hwGetSampleID(u32 voice);
u8 hwGetSampleType(u32 voice);
void hwChangeStudioMix(u8 studio, u32 isMaster);
void hwSetStreamLoopPS(u32 voice, u8 ps);
void hwFlushStream(void* base, u32 offset, u32 bytes, unsigned char hwStreamHandle, void (*callback)(u32),
                   u32 user);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 3)
void hwSetFilter(u32 v, unsigned char mode, unsigned short coefA, unsigned short coefB);
void hwLowPassFrqToCoef(u32 frq, unsigned short* _a0, unsigned short* _b1);
#endif

extern u32 aramSize;
extern u8* aramBase;
#ifdef __cplusplus
}
#endif

#endif // _MUSYX_HARDWARE
