#ifndef __GAME_m_sound_H_
#define __GAME_m_sound_H_

#include "mssbTypes.h"

// Sound state (lbl_3_common_bss_34C58, 0x38 bytes).
typedef struct SndState34C58 {
    void* unk0; // file loaded by ARAMTransfer (relocated in place)
    s32 unk4;
    s32 unk8;
    s32 unkC[4]; // sound voice ids, -1 = none
    s32 unk1C;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    u8 unk26; // crowd reaction level for the current play
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B; // swing sound pending
    u8 unk2C;
    u8 unk2D;
    u8 unk2E; // victory jingle playing
    u8 unk2F;
    u8 unk30;
    u8 unk31;
    u8 unk32; // 1: game-start fanfare, 2: inning fanfare
    u8 unk33;
    u8 unk34; // pitch-release sound played
} SndState34C58;

#ifdef _MUSYX_MUSYX // needs SND_LISTENER
// 3D sound space (lbl_3_common_bss_32B20, 0x2138 bytes).
typedef struct SoundSpace {
    /*0x0000*/ SND_LISTENER listener;
#ifdef TARGET_PC
    u8 emitters[100][sizeof(SND_EMITTER)]; // MusyX's emitters hold pointers: bigger on PC
#else
    /*0x0090*/ u8 emitters[100][0x50]; // emitters as the game's MusyX build lays them out (0x50 bytes each)
#endif
    /*0x1FD0*/ u8 type[100];
    /*0x2034*/ u8 active[100];
    /*0x2098*/ u8 _2098[100];
    /*0x20FC*/ u8 _20FC;
    /*0x20FD*/ u8 _20FD;
    /*0x20FE*/ u8 _20FE[0x2138 - 0x20FE];
} SoundSpace;
#endif

// Sound request queue task (the fn_800B0A5C_insertQueue slot in lbl_3_bss_1768): the scene-task
// header, then a ring of 14 requests.
typedef struct SndQ1768 {
    /*0x00*/ void (*func)(void);
    /*0x04*/ void* prev;
    /*0x08*/ void* next;
    /*0x0C*/ void* parent;
    /*0x10*/ s16 _10;
    /*0x12*/ u16 priority;
    /*0x14*/ u8 head;
    /*0x15*/ u8 tail;
    /*0x16*/ struct { u8 a, b, c; } e[14];
} SndQ1768;

void fn_3_8B718(f32* a, f32* b, f32* c);
void fn_3_8B7DC(void);
void fn_3_8B804(void);
void fn_3_8B890(s32 i);
void fn_3_8B964(void* a, void* b, void* c);
void fn_3_8B9BC(void* pos);
void fn_3_8BA60(s32 i, f32* pos, f32* dir);
s32 fn_3_8BBC4(s32 id, f32* pos, f32* dir, s32 type);
void fn_3_8BDF4(void);
void fn_3_8BE8C(void);
void fn_3_8C07C(void);
void fn_3_8C104(s32 v);
s32 fn_3_8C2DC(u32 div, u8 k);
s32 fn_3_8C4F0(u32 div, u8 lim);
void fn_3_8C5C8(void);
void fn_3_8CD74(void);
void fn_3_8D9C0(void);
void fn_3_8DA80(void);
void fn_3_8F1C8(void);
void fn_3_8F21C(void);
void fn_3_8FC0C(void);
void fn_3_8FC80(void);
void fn_3_8FF18(void);
u32 fn_3_8FF5C(s32 id, f32 x, f32 y, f32 z);
u32 fn_3_90064(s32 id); // returns the voice id
u32 fn_3_90150(s32 a, s32 b);

void fn_3_902FC(void);
u32 fn_3_90220(s32 idx, s32 off);
u32 playSoundEffect(s32 id);
void fn_3_90328(s32 vol);
void fn_3_903B8(void);
void fn_3_90434(void);
u32 fn_3_9056C(s32 idx);
void fn_3_90674(s32 idx);
void fn_3_906FC(void);

s32 fn_3_8B258(u8 a, u8 b, u8 c);
void fn_3_8B2E4(void);
void fn_3_8B318(s32 mode);

#endif // !__GAME_m_sound_H_
