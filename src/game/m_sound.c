#include "game/m_sound.h"
#include "header_rep_data.h"
#include "main/file_80011640.h"

typedef struct SndState34C58 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
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
extern SndState34C58 lbl_3_common_bss_34C58;
#define S34C58 lbl_3_common_bss_34C58
#define B34C58 ((u8*)&lbl_3_common_bss_34C58)
extern s32 lbl_3_bss_1780[];
extern u8 lbl_3_common_bss_32B20[];
extern void sndUpdateListener(void*, void*, void*, void*, void*, s32, s32);
extern u8 lbl_3_common_bss_32B20[];
extern void sndRemoveListener(void*);
struct StreamTrack;
extern void fn_800A86B4(s32 cmd); // main/file_800A7C08.h
extern struct StreamTrack* fn_800A88C0(void);
extern s32 fn_800A8B78(struct StreamTrack* track);
extern void OSPanic(const char*, int, const char*, ...);
extern char lbl_3_rodata_1590[];
extern char lbl_3_rodata_15DC[];
extern char lbl_3_rodata_15EC[];
extern u16 lbl_3_data_81FC[];
extern u8 lbl_3_data_84F4[];
extern void* fn_80052734(int);
#include "Dolphin/mtx.h"
extern Vec lbl_3_rodata_1558;
extern Vec lbl_3_rodata_1564;
extern Vec lbl_3_rodata_1570;
extern void sndUpdateEmitter(void*, Vec*, Vec*, u8, void*);
extern u32 sndAddListener(void*, void*, void*, void*, void*, f32, f32, f32, u32, u8, void*);
extern f32 lbl_3_data_88AC;
extern u32 sndCheckEmitter(void*);
extern void sndRemoveEmitter(void*);
extern u8 lbl_3_bss_1760[];
// View over the pooled m_sound .bss statics starting at lbl_3_bss_1760
// (0x10/0x11 live in lbl_3_bss_176C, 0x18/0x1C in lbl_3_bss_1774).
typedef struct Snd1760 {
    u8 starSwingDone;
    u8 on;
    u8 pad2[0xE];
    u8 lo;
    u8 hi;
    u8 pad12[6];
    u32 swingVid;
    u32 pitchVid;
} Snd1760;
extern u16 fn_800A8864(void);
extern void fn_800A8878(u8, u8);
extern s32 fn_3_1650C(int* outX, int* outY, s32 r5, f32 pX, f32 pY, f32 pZ);
extern u8 lbl_3_data_8338[];
extern u8 lbl_800EF808[];

#include "static/UnknownHomes_Static.h"
extern void* lbl_3_bss_1768;
extern void fn_3_8B094(void);
#include "musyx/musyx.h"
extern u16 lbl_3_data_8168[];
extern u8 lbl_3_data_8530[];
extern u8 lbl_3_data_8338[];
extern u32 sndSeqGetValid(u32);
extern u32 sndSeqPlayEx(u16 sgid, u16 sid, void* arrfile, void* para, u8 studio);
extern u32* lbl_3_bss_1774;
extern u8 lbl_3_data_830C[];
extern u8 lbl_3_data_8148[];
extern u8 lbl_800EF808[];
extern void sndSeqVolume(u8 volume, u16 time, u32 seqId, u8 mode);
typedef struct SndEm3C { s32 x, y, z; s32 maxd, comp; u32 f14, f18; u32 fl[7]; u32 f38; } SndEm3C;
typedef struct { u16 a, b, c; } SeqEnt6;

// The unit's .data (0x8148-0x8D88). Defined here: the original reaches these tables through one
// pooled base. Address order (initialized data keeps declaration order).
u8 lbl_3_data_8148[0x20] = {
    0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0F, 0x0E, 0x0D, 0x0C,
    0x0B, 0x0A, 0x23, 0x07, 0x09, 0x21, 0x22, 0x08, 0x30, 0x2E, 0x27, 0x2F, 0x32, 0x25, 0x24, 0x26,
};
u16 lbl_3_data_8168[0x36] = { // per character: first voice sound id
    0x0144, 0x0137, 0x012A, 0x011D, 0x0110, 0x0103, 0x00F6, 0x00E9, 0x00DC, 0x00CF, 0x00C2, 0x00B5,
    0x00A8, 0x009B, 0x008E, 0x0081, 0x0074, 0x0067, 0x0201, 0x0040, 0x005A, 0x01E7, 0x01E7, 0x01E7,
    0x01F4, 0x01F4, 0x01F4, 0x004D, 0x0277, 0x009B, 0x009B, 0x009B, 0x009B, 0x025D, 0x025D, 0x025D,
    0x025D, 0x0235, 0x026A, 0x02C9, 0x021B, 0x020E, 0x00A8, 0x005A, 0x0074, 0x0074, 0x0074, 0x0074,
    0x0228, 0x0228, 0x0228, 0x0228, 0x004D, 0x004D,
};
u8 lbl_3_data_81D4[0x8] = {
    0x2A, 0x2B, 0x2C, 0x34, 0x02, 0x01, 0x06, 0x00,
};
u16 lbl_3_data_81DC[0x10] = { // per stadium: crowd sound id base
    0x0248, 0x024A, 0x0252, 0x030F, 0x0010, 0x0001, 0x0022, 0x0000, 0x0249, 0x0251, 0x0258, 0x000F,
    0x0017, 0x000F, 0x003F, 0x0000,
};
u16 lbl_3_data_81FC[0x39] = { // sound ids
    0x02D6, 0x02D7, 0x02D8, 0x02D9, 0x02E1, 0x02E2, 0x02E3, 0x02E4, 0x02E5, 0x02E6, 0x02DD, 0x02DE,
    0x02DF, 0x02E0, 0x02DA, 0x02DB, 0x02DC, 0x02E7, 0x02E8, 0x02E9, 0x02EA, 0x02EB, 0x02EC, 0x02ED,
    0x02EE, 0x02EF, 0x02F0, 0x02F1, 0x02F2, 0x02F3, 0x02F4, 0x02F5, 0x02F6, 0x02F7, 0x02F8, 0x02F9,
    0x02FA, 0x02FB, 0x02FC, 0x02FD, 0x02FE, 0x02FF, 0x0300, 0x0301, 0x0302, 0x0303, 0x0304, 0x0305,
    0x0306, 0x0307, 0x0308, 0x0309, 0x030A, 0x030B, 0x030C, 0x030D, 0x030E,
};
u8 lbl_3_data_8270[7] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }; // minigame crowd ctrl (fn_3_8B318 mode 6)
u8 lbl_3_data_8278[12] = { 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78 }; // voice ctrl
u8 lbl_3_data_8284[102] = { // FX ctrl (fn_3_8B318 mode 6)
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
};
u8 lbl_3_data_82EC[0x20] = {
    0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 lbl_3_data_830C[0x2C] = {
    0x4B, 0x28, 0x4B, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28,
    0x55, 0x28, 0x5A, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28, 0x55, 0x28,
    0x5A, 0x28, 0x5F, 0x28, 0x69, 0x28, 0x00, 0x00, 0x55, 0x28, 0x00, 0x00,
};
u8 lbl_3_data_8338[0xCC] = { // FX volume/ctrl pairs, from sound id 0x151
    0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x46, 0x00, 0x4B, 0x00, 0x55, 0x00, 0x5A, 0x00, 0x5A, 0x00,
    0x64, 0x00, 0x7F, 0x00, 0x64, 0x00, 0x78, 0x00, 0x64, 0x00, 0x7F, 0x00, 0x64, 0x00, 0x64, 0x00,
    0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00,
    0x7F, 0x00, 0x64, 0x00, 0x6E, 0x00, 0x7F, 0x00, 0x75, 0x00, 0x75, 0x00, 0x64, 0x00, 0x64, 0x00,
    0x57, 0x00, 0x64, 0x00, 0x64, 0x00, 0x57, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x7F, 0x00,
    0x7F, 0x00, 0x75, 0x00, 0x54, 0x00, 0x64, 0x00, 0x64, 0x00, 0x50, 0x00, 0x5A, 0x00, 0x7F, 0x00,
    0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00,
    0x75, 0x00, 0x6B, 0x00, 0x64, 0x00, 0x73, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00,
    0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x6B, 0x00, 0x55, 0x00, 0x6B, 0x00,
    0x6B, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x75, 0x00, 0x66, 0x00, 0x75, 0x00, 0x7F, 0x00, 0x55, 0x00,
    0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x6E, 0x00, 0x64, 0x00, 0x64, 0x00,
    0x73, 0x00, 0x6E, 0x00, 0x5A, 0x00, 0x6E, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x6B, 0x00, 0x7F, 0x00,
    0x75, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x73, 0x00, 0x7F, 0x00, 0x7F, 0x00,
};
u8 lbl_3_data_8404[0xB4] = { // per stadium: 15 crowd sounds (volume, ctrl)
    0x3C, 0x00, 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00,
    0x7F, 0x00, 0x7F, 0x00, 0x69, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x7F, 0x00,
    0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00,
    0x64, 0x00, 0x7F, 0x00, 0x41, 0x00, 0x46, 0x00, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x32, 0x00,
    0x4D, 0x00, 0x4D, 0x00, 0x57, 0x00, 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x64, 0x00, 0x64, 0x00, 0x64, 0x00, 0x7F, 0x00,
    0x7F, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x69, 0x00, 0x7F, 0x00, 0x6E, 0x00, 0x7F, 0x00, 0x6E, 0x00,
    0x7F, 0x00, 0x7F, 0x00,
};
u8 lbl_3_data_84B8[0x3C] = { // minigame crowd sounds (volume, ctrl)
    0x7F, 0x00, 0x6B, 0x00, 0x64, 0x00, 0x5F, 0x00, 0x75, 0x00, 0x70, 0x00, 0x6B, 0x00, 0x7F, 0x00,
    0x6B, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x4B, 0x00, 0x7F, 0x00, 0x7F, 0x00, 0x7F, 0x00,
    0x64, 0x00, 0x64, 0x00, 0x69, 0x00, 0x75, 0x00, 0x69, 0x00, 0x5F, 0x00, 0x5F, 0x00, 0x69, 0x00,
    0x64, 0x00, 0x6E, 0x00, 0x78, 0x00, 0x6E, 0x00, 0x6E, 0x00, 0x7F, 0x00,
};
u8 lbl_3_data_84F4[0x3C] = {
    0x6B, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x4D, 0x4D, 0x7F, 0x61, 0x6B, 0x61, 0x61, 0x7F, 0x6B,
    0x5F, 0x69, 0x43, 0x37, 0x7F, 0x7F, 0x7F, 0x69, 0x7F, 0x61, 0x75, 0x75, 0x64, 0x5F, 0x7F, 0x64,
    0x64, 0x7F, 0x69, 0x5A, 0x64, 0x6B, 0x7F, 0x7F, 0x5A, 0x7F, 0x7F, 0x75, 0x7F, 0x7F, 0x73, 0x64,
    0x73, 0x6E, 0x6E, 0x7F, 0x73, 0x73, 0x7F, 0x7F, 0x78, 0x00, 0x00, 0x00,
};
u8 lbl_3_data_8530[0x300] = { // voice volume [0x180], then ctrl [0x180]
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
f32 lbl_3_data_8830 = 0.6f;
f32 lbl_3_data_8834[6][4] = {
    { 50.0f, 0.0f, 127.0f, 10.0f },
    { 50.0f, 0.0f, 127.0f, 10.0f },
    { 50.0f, 0.0f, 127.0f, 10.0f },
    { 50.0f, 0.0f, 127.0f, 10.0f },
    { 100.0f, 0.0f, 127.0f, 10.0f },
    { 100.0f, 0.0f, 127.0f, 10.0f },
};
u32 lbl_3_data_8894[6] = { 0x1, 0x1, 0x1, 0x1, 0x61, 0x61 };
f32 lbl_3_data_88AC = 50.0f;
f32 lbl_3_data_88B0 = 50.0f;
f32 lbl_3_data_88B4 = 1.0f;
s16 lbl_3_data_88B8[18] = {
    8192, 15104, 3, 45, 70, 0, 8192, 16383, 1, 60, 127, 0, 8192, 16383, 20, 165, 127, 0,
};
u8 lbl_3_data_88DC = 0x03;
u8 lbl_3_data_88DD = 0x03;
SeqEnt6 lbl_3_data_88E0[19] = {
    { 0x1D, 0x0, 0x0 },
    { 0x1D, 0x1, 0x1 },
    { 0x1D, 0x2, 0x2 },
    { 0x1D, 0x3, 0x3 },
    { 0x1D, 0x4, 0x4 },
    { 0x1D, 0x6, 0x5 },
    { 0x1D, 0x5, 0x6 },
    { 0x1D, 0x7, 0x7 },
    { 0x1D, 0x8, 0x8 },
    { 0x1D, 0x9, 0x9 },
    { 0x1D, 0xA, 0xA },
    { 0x1D, 0xB, 0xB },
    { 0x1D, 0xC, 0xC },
    { 0x1D, 0xD, 0xD },
    { 0x1D, 0xE, 0xE },
    { 0x1D, 0xF, 0xF },
    { 0x1D, 0x10, 0x10 },
    { 0x1D, 0x11, 0x11 },
    { 0x1D, 0x12, 0x12 },
};
SeqEnt6 lbl_3_data_8954 = { 0x36, 0x15, 0x0 };
u8 lbl_3_data_895C[0x16] = {
    0x16, 0x17, 0x19, 0x1A, 0x1D, 0x1E, 0x1F, 0x20, 0x22, 0x23, 0x24, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E,
    0x2F, 0x31, 0x32, 0x33, 0x34, 0x35,
};
SndEm3C lbl_3_data_8974[17] = {
    { -5000000, -4000000, 23000000, 30000000, 0, 0x6E, 0x1E, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, 0x1 },
    { -5000000, 0, 19000000, 40000000, 0, 0x7F, 0x32, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, 0x1 },
    { 0, 0, 6000000, 8000000, 0, 0x5A, 0x1E, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, 0x10 },
    { 0, 0, 0, 20000000, 0, 0x5A, 0x1E, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x20 },
    { -5000000, -1000000, 5000000, 30000000, 0, 0x46, 0xA, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x20 },
    { 0, 0, 5000000, 20000000, 0, 0x32, 0xF, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x20 },
    { -5000000, 0, 19000000, 40000000, 0, 0x5A, 0x23, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, 0x1 },
    { 0, 0, 0, 20000000, 0, 0x3C, 0x28, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x8 },
    { 0, 0, 0, 20000000, 0, 0x6E, 0x5A, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x2 },
    { 0, 0, 0, 20000000, 0, 0x7F, 0x64, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x2 },
    { 0, 0, 0, 20000000, 0, 0x7F, 0x64, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x4 },
    { 0, 0, 0, 20000000, 0, 0x7F, 0x64, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x4 },
    { 0, 0, 0, 20000000, 0, 0x7F, 0x64, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x4 },
    { 0, 0, 0, 20000000, 0, 0x7F, 0x64, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x4 },
    { 0, 0, 0, 20000000, 0, 0x7F, 0x64, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40 }, 0x4 },
    { 0, 0, 0, 20000000, 0, 0x7F, 0x0, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, 0x1 },
    { 0, 0, 0, 20000000, 0, 0x7F, 0x0, { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, 0x1 },
};
f32 lbl_3_data_8D70[3] = { 0.0f, -1.0f, 0.0f };
Vec lbl_3_data_8D7C = { 0.0f, 0.0f, 0.0f };

void fn_3_902FC(void) {
    sndVolume(0, 10, 0xFF);
}

// .text:0x0008B258 size:0x8C
s32 fn_3_8B258(u8 a, u8 b, u8 c) {
    u8 w;
    if (((u8**)&lbl_3_bss_1768)[0] == NULL || (w = ((u8**)&lbl_3_bss_1768)[0][0x14], ((u8**)&lbl_3_bss_1768)[0][0x15] == (u32)(u8)((w + 1) % 14))) {
        return 0;
    }
    ((u8**)&lbl_3_bss_1768)[0][0x14] = (u32)(u8)((w + 1) % 14);
    ((u8**)&lbl_3_bss_1768)[0][w * 3 + 0x16] = b;
    ((u8**)&lbl_3_bss_1768)[0][w * 3 + 0x17] = a;
    ((u8**)&lbl_3_bss_1768)[0][w * 3 + 0x18] = c;
    return 1;
}

void fn_3_8B2E4(void) {
    lbl_3_bss_1768 = fn_800B0A5C_insertQueue(fn_3_8B094, 0);
}

// .text:0x0008B318 size:0x400
// Sets the per-voice reverb/ctrl tables:
//   lbl_3_data_8270 (7 bytes)   -> lbl_3_data_84B8, odd bytes
//   lbl_3_data_8278 (12 bytes)  -> lbl_3_data_8530 + 0x180
//   lbl_3_data_8284 (102 bytes) -> lbl_3_data_8338, odd bytes (ctrl of each FX pair)
typedef struct SndFxPair { u8 vol, ctrl; } SndFxPair;
void fn_3_8B318(s32 mode) {
    s32 i;
    u32 n;
    if (mode == -1) {
        for (i = 0; i < 12; i++) {
            lbl_3_data_8530[0x180 + i] = lbl_3_data_8278[i];
        }
    } else if (mode == 6) {
        for (i = 0; i < 7; i++) {
            ((SndFxPair*)lbl_3_data_84B8)[i].ctrl = lbl_3_data_8270[i];
        }
        for (i = 0; i < 12; i++) {
            lbl_3_data_8530[0x180 + i] = lbl_3_data_8278[i];
        }
        for (n = 0; n < 102; n++) {
            ((SndFxPair*)lbl_3_data_8338)[n].ctrl = lbl_3_data_8284[n];
        }
    } else {
        for (i = 0; i < 7; i++) {
            ((SndFxPair*)lbl_3_data_84B8)[i].ctrl = 0;
        }
        for (i = 0; i < 12; i++) {
            lbl_3_data_8530[0x180 + i] = 0;
        }
        for (n = 0; n < 102; n++) {
            ((SndFxPair*)lbl_3_data_8338)[n].ctrl = 0;
        }
    }
}

// .text:0x0008B718 size:0xC4 mapped:0x806CA7AC
void fn_3_8B718(f32* a, f32* b, f32* c) {
    u8* cam = fn_80052734(0);
    if (a != NULL) {
        a[0] = *(f32*)(cam + 0x70);
        a[1] = *(f32*)(cam + 0x74);
        a[2] = *(f32*)(cam + 0x78);
    }
    if (b != NULL) {
        b[0] = 0.0f;
        b[1] = 0.0f;
        b[2] = 0.0f;
    }
    if (c != NULL) {
        PSVECSubtract((Vec*)(cam + 0x7C), (Vec*)(cam + 0x70), (Vec*)c);
        if (PSVECMag((Vec*)c)) {
            PSVECNormalize((Vec*)c, (Vec*)c);
        }
    }
}

// .text:0x0008B7DC size:0x28 mapped:0x806CA870
void fn_3_8B7DC(void) {
    sndRemoveListener(lbl_3_common_bss_32B20);
}

// .text:0x0008B804 size:0x8C mapped:0x806CA898
void fn_3_8B804(void) {
    s32 i;
    for (i = 0; i < 100; i++) {
        if (lbl_3_common_bss_32B20[0x2034 + i] != 0) {
            if (sndCheckEmitter(lbl_3_common_bss_32B20 + 0x90 + i * 0x50) != 0) {
                sndRemoveEmitter(lbl_3_common_bss_32B20 + 0x90 + i * 0x50);
            }
            lbl_3_common_bss_32B20[0x2034 + i] = 0;
        }
    }
}

// .text:0x0008B890 size:0xD4 mapped:0x806CA924
void fn_3_8B890(s32 i) {
    u8* em;
    if (i < 0 || i >= 100 || lbl_3_common_bss_32B20[0x2034 + i] == 0) {
        return;
    }
    em = lbl_3_common_bss_32B20 + 0x90 + i * 0x50;
    if (sndCheckEmitter(em) != 0) {
        Vec pos = lbl_3_rodata_1564;
        Vec dir = lbl_3_rodata_1570;
        sndUpdateEmitter(em, &pos, &dir, 0, 0);
        sndRemoveEmitter(em);
    }
}

// .text:0x0008B964 size:0x58 mapped:0x806CA9F8
void fn_3_8B964(void* a, void* b, void* c) {
    if (*(u32*)(lbl_3_common_bss_32B20 + 8) != 0) {
        sndUpdateListener(lbl_3_common_bss_32B20, a, b, c, lbl_3_data_8D70, 0x7F, 0);
    }
}

// .text:0x0008B9BC size:0xA4 mapped:0x806CAA50
void fn_3_8B9BC(void* pos) {
    f32 head[3];
    f32 dir[3];
    head[0] = 0.0f;
    head[1] = 0.0f;
    head[2] = -1.0f;
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = 0.0f;
    sndRemoveListener(lbl_3_common_bss_32B20);
    sndAddListener(lbl_3_common_bss_32B20, pos, dir, head, lbl_3_data_8D70, lbl_3_data_88AC, lbl_3_data_88AC, lbl_3_data_88AC, 1, 0x7F, 0);
}

// .text:0x0008BA60 size:0x164 mapped:0x806CAAF4
extern SndEm3C lbl_3_data_8974[];
extern Vec lbl_3_data_8D7C;
void fn_3_8BA60(s32 i, f32* pos, f32* dir) {
    f32 tmp[3];
    u8* em;
    u8 type;
    if (i < 0 || i >= 100 || lbl_3_common_bss_32B20[0x2034 + i] == 0) {
        return;
    }
    em = lbl_3_common_bss_32B20 + i * 0x50 + 0x90;
    if (sndCheckEmitter(em) == 0) {
        lbl_3_common_bss_32B20[0x2034 + i] = 0;
        return;
    }
    type = lbl_3_common_bss_32B20[0x1FD0 + i];
    if (pos == NULL) {
        tmp[0] = lbl_3_data_8974[type].x / 100000.0f;
        tmp[1] = lbl_3_data_8974[type].y / 100000.0f;
        tmp[2] = lbl_3_data_8974[type].z / 100000.0f;
        pos = tmp;
    }
    if (dir == NULL) {
        dir = (f32*)&lbl_3_data_8D7C;
    }
    sndUpdateEmitter(em, (Vec*)pos, (Vec*)dir, lbl_3_data_8974[type].f14, 0);
}

// .text:0x0008BBC4 size:0x230 mapped:0x806CAC58
extern char lbl_3_rodata_159C[];
extern u32 sndAddEmitter(void*, void*, void*, f32, f32, u32, u16, u8, u8, void*);
s32 fn_3_8BBC4(s32 id, f32* pos, f32* dir, s32 type) {
    f32 tmp[3];
    s32 i;
    for (i = 0; i < 100; i++) {
        if (lbl_3_common_bss_32B20[0x2034 + i] == 0 || sndCheckEmitter(lbl_3_common_bss_32B20 + i * 0x50 + 0x90) == 0) {
            lbl_3_common_bss_32B20[0x1FD0 + i] = type;
            lbl_3_common_bss_32B20[0x2034 + i] = 1;
            lbl_3_common_bss_32B20[0x2098 + i] = 0;
            if (pos == NULL) {
                tmp[0] = lbl_3_data_8974[type].x / 100000.0f;
                tmp[1] = lbl_3_data_8974[type].y / 100000.0f;
                tmp[2] = lbl_3_data_8974[type].z / 100000.0f;
                pos = tmp;
            }
            if (dir == NULL) {
                dir = (f32*)&lbl_3_data_8D7C;
            }
            sndAddEmitter(lbl_3_common_bss_32B20 + i * 0x50 + 0x90, pos, dir,
                          lbl_3_data_8974[type].maxd / 100000.0f, lbl_3_data_8974[type].comp / 100000.0f,
                          lbl_3_data_8974[type].fl[0] | lbl_3_data_8974[type].fl[1] | lbl_3_data_8974[type].fl[2] |
                              lbl_3_data_8974[type].fl[3] | lbl_3_data_8974[type].fl[4] | lbl_3_data_8974[type].fl[5] |
                              lbl_3_data_8974[type].fl[6],
                          (u16)id, lbl_3_data_8974[type].f14, lbl_3_data_8974[type].f18, 0);
            return i;
        }
    }
    if (i == 100) {
        OSPanic(lbl_3_rodata_1590, 0xE4C, lbl_3_rodata_159C);
    }
    return -1;
}

// .text:0x0008BDF4 size:0x98 mapped:0x806CAE88
void fn_3_8BDF4(void) {
    fn_3_8B804();
    fn_3_8B7DC();
}

// .text:0x0008BE8C size:0x1F0 mapped:0x806CAF20
void fn_3_8BE8C(void) {
    Vec pos = lbl_3_rodata_1558;
    s32 i;
    for (i = 0; i < 100; i++) {
        lbl_3_common_bss_32B20[0x1FD0 + i] = 0xFF;
        lbl_3_common_bss_32B20[0x2034 + i] = 0;
        lbl_3_common_bss_32B20[0x2098 + i] = 0;
    }
    lbl_3_common_bss_32B20[0x20FC] = 0xFF;
    lbl_3_common_bss_32B20[0x20FD] = 0;
    fn_3_8B9BC(&pos);
    fn_3_8B804();
}

// .text:0x0008C07C size:0x88 mapped:0x806CB110
typedef struct SndQ1768 {
    u8 pad[0x14];
    u8 head;
    u8 tail;
    struct { u8 a, b, c; } e[14];
} SndQ1768;
void fn_3_8C07C(void) {
    SndQ1768** pp = (SndQ1768**)&lbl_3_bss_1768;
    u8 cur;
    u8 next;
    if (*pp != NULL) {
        cur = (*pp)->head;
        if ((*pp)->tail != (next = (cur + 1) % 14)) {
            (*pp)->head = next;
            (*pp)->e[cur].a = 0;
            (*pp)->e[cur].b = 4;
            (*pp)->e[cur].c = 0;
        }
    }
}

// .text:0x0008C104 size:0x1D8 mapped:0x806CB198
extern u8 lbl_800E88A4[][2];
extern u8 g_GameLogic[];
void fn_3_8C104(s32 v) {
    u8 b;
    u32 a;
    u32 j = 0;
    if (lbl_800EF808[0x398] == 0) {
        return;
    }
    if (v == -2) {
        j = 1;
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        a = 9;
        b = lbl_800E88A4[9][j];
    } else if (g_GameLogic[0x11E] == 0x24) {
        a = 7;
        b = lbl_800E88A4[7][j];
    } else if (*(s16*)(B34C58 + 0x20) == 0x16) {
        a = 6;
        b = lbl_800E88A4[6][j];
    } else if (*(s16*)(B34C58 + 0x20) == 0x17) {
        a = 0xE;
        b = lbl_800E88A4[0xE][j];
    } else if (g_GameLogic[0x11E] == 0xE) {
        a = 7;
        b = lbl_800E88A4[7][j];
    } else if (g_GameLogic[0x11E] == 0x17) {
        a = 8;
        b = lbl_800E88A4[8][j];
    } else {
        a = g_d_GameSettings.StadiumID;
        b = lbl_800E88A4[a][j];
    }
    if (v >= 0) {
        b = v;
    }
    {
        SndQ1768** pp = (SndQ1768**)&lbl_3_bss_1768;
        u8 cur;
        u8 next;
        if (*pp != NULL) {
            cur = (*pp)->head;
            if ((*pp)->tail != (next = (cur + 1) % 14)) {
                (*pp)->head = next;
                (*pp)->e[cur].a = a;
                (*pp)->e[cur].b = 0;
                (*pp)->e[cur].c = b;
            }
        }
    }
    if ((u8)b == 0) {
        fn_800A8878(b, b);
    }
}

// .text:0x0008C2DC size:0x214 mapped:0x806CB370
extern f32 lbl_3_bss_1764;
extern f32 lbl_3_bss_176C;
s32 fn_3_8C2DC(u32 div, u8 k) {
    u16 v;
    f32 hi;
    v = fn_800A8864();
    if (g_d_GameSettings.GameModeSelected == 6) {
        k = lbl_800E88A4[9][k];
    } else if (*(s16*)(B34C58 + 0x20) == 0x16) {
        k = lbl_800E88A4[6][k];
    } else if (g_GameLogic[0x11E] == 0xE) {
        k = lbl_800E88A4[7][k];
    } else if (g_GameLogic[0x11E] == 0x17) {
        k = lbl_800E88A4[8][k];
    } else {
        k = lbl_800E88A4[g_d_GameSettings.StadiumID][k];
    }
    hi = (s32)((v >> 8) & 0xFF);
    if (hi > lbl_3_bss_1764) {
        lbl_3_bss_1764 = hi;
    }
    if (S34C58.unk2F == 0) {
        lbl_3_bss_176C = (f32)k / (f32)div;
        S34C58.unk2F = 1;
        lbl_3_bss_1764 = hi;
    }
    lbl_3_bss_1764 += lbl_3_bss_176C;
    fn_800A8878((u8)lbl_3_bss_1764, (u8)lbl_3_bss_1764);
    if (lbl_3_bss_1764 >= (f32)k) {
        S34C58.unk2F = 0;
        return 0;
    }
    return 1;
}

// .text:0x0008C4F0 size:0xD8 mapped:0x806CB584
s32 fn_3_8C4F0(u32 div, u8 lim) {
    Snd1760* st = (Snd1760*)lbl_3_bss_1760;
    u16 v;
    u8 hi;
    u8 lo;
    v = fn_800A8864();
    S34C58.unk2F = 0;
    hi = (v >> 8) & 0xFF;
    lo = v & 0xFF;
    if (st->on == 0) {
        st->on = 1;
        st->hi = hi / div;
        st->lo = lo / div;
    }
    if ((s16)(hi - st->hi) <= lim || div == 1) {
        st->on = 0;
        fn_800A8878(lim, lim);
        return 0;
    }
    fn_800A8878(hi - st->hi, lo - st->lo);
    return 1;
}

extern u8 g_Practice[];
// .text:0x0008C5C8 size:0x7AC mapped:0x806CB65C
// Ball-collision sound: pick an FX by stadium and collision code and play it
// panned to the ball position (fn_3_8FF5C is inlined in the original).
extern u8 g_Ball[];
#define BALL_POS ((f32*)(g_Ball + 0x0))            // TODO type: InMemBallType.AtBat_Contact_BallPos
#define BALL_VELOCITY (*(f32*)(g_Ball + 0x1A14))   // TODO type: InMemBallType.ballVelocity
#define BALL_COLLISION (*(s32*)(g_Ball + 0x1B44))  // TODO type: InMemBallType.collisionCode
extern const f32 lbl_3_rodata_15B8; // 0.2f
extern const f64 lbl_3_rodata_15C8; // -0.09
extern const f64 lbl_3_rodata_15D0; // -0.1
extern const f32 lbl_3_rodata_15D8; // -3.0f
void fn_3_8C5C8(void) {
    s32 code = BALL_COLLISION & 0x7F;
    s32 stadium;
    u32 vid;
    if (BALL_VELOCITY < lbl_3_rodata_15B8) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 7) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        stadium = g_d_GameSettings.StadiumID;
        vid = sndFXStartEx((u16)(lbl_3_data_81DC[stadium] + 0x18),
                           g_d_GameSettings.GameModeSelected == 6 ? lbl_3_data_84B8[0x30] : (lbl_3_data_8404 + stadium * 0x1E)[0x30],
                           0x3F, 0);
        sndFXCtrl(vid, 0x5B,
                  g_d_GameSettings.GameModeSelected == 6 ? lbl_3_data_84B8[0x31] : (lbl_3_data_8404 + stadium * 0x1E)[0x31]);
        return;
    }
    if (g_d_GameSettings.StadiumID == 1) {
        if (code == 8) {
            fn_3_8FF5C(0x1A2, BALL_POS[0], BALL_POS[1], BALL_POS[2]);
        } else {
            fn_3_8FF5C(0x1A1, BALL_POS[0], BALL_POS[1], BALL_POS[2]);
        }
        return;
    }
    if (g_d_GameSettings.StadiumID == 3) {
        if (code == 1) {
            fn_3_8FF5C(0x1A4, BALL_POS[0], BALL_POS[1], BALL_POS[2]);
            return;
        }
    } else if (g_d_GameSettings.StadiumID == 4) {
        if (code == 6) {
            fn_3_8FF5C(0x1A1, BALL_POS[0], BALL_POS[1], BALL_POS[2]);
            return;
        }
        if (code == 10) {
            fn_3_8FF5C(0x1A2, BALL_POS[0], BALL_POS[1], BALL_POS[2]);
            return;
        }
        if (code == 9) {
            fn_3_8FF5C(0x1A0, BALL_POS[0], BALL_POS[1], BALL_POS[2]);
            return;
        }
    } else if (g_d_GameSettings.StadiumID == 5) {
        if (code == 10) {
            fn_3_8FF5C(0x1A2, BALL_POS[0], BALL_POS[1], BALL_POS[2]);
            return;
        }
    }
    fn_3_8FF5C(0x17E, BALL_POS[0], BALL_POS[1], BALL_POS[2]);
}

// .text:0x0008CD74 size:0xC4C mapped:0x806CBE08
// Game-state views used by the crowd-reaction code below.
// TODO type: m_sound.c can't include game/UnknownHomes_Game.h yet (its local
// u8[] declarations conflict); these macros name the real fields so the
// switch-over is mechanical.
extern u8 g_Runners[];        // InMemRunnerType[4], stride 0x154
extern u8 g_FieldingLogic[];
extern u8 g_Strikes[];
extern u8 g_Stats[];
extern u8 g_Batter[];
extern u8 g_RunningLogic[];
extern u8 g_Scores[];
extern u8 lbl_3_common_bss_32A94[];
extern int fn_3_B7D6C(f32 a, f32 b);
extern int fn_3_B7E10(f32 a, f32 b);
#define RUNNER(i) (g_Runners + (i) * 0x154)
#define RUNNER_STATUS(i) (RUNNER(i)[0x123])                      // runnerOnFieldOrOutOrScored
#define RUNNER_CUR_BASE(i) (RUNNER(i)[0x125])                    // currentBase
#define RUNNER_WALK_FORCED(i) (RUNNER(i)[0x14D])                 // furthestBaseForcedToGoToOnWalk
#define RUNNER_BASE_STANDING(i) (*(s16*)(RUNNER(i) + 0xE6))      // baseStandingOn
#define RUNNER_FORCE_OUT(i) (*(s16*)(RUNNER(i) + 0xEE))          // forceOutCd
#define RUNNER_FRAMES_SINCE_OUT(i) (*(s16*)(RUNNER(i) + 0xF4))   // framesSinceOut
#define RUNNER_BASES_RAN(i) (*(f32*)(RUNNER(i) + 0x64))          // fractionalBasesRan
#define GAME_STATUS (g_GameLogic[0x11E])                         // g_GameLogic.gameStatus
#define FIELDING_107 (g_FieldingLogic[0x107])                    // g_FieldingLogic._107
#define STRIKES_OUTS (*(s32*)(g_Strikes + 0x8))                  // g_Strikes.outs
#define STRIKES_STORED_OUTS (*(s32*)(g_Strikes + 0xC))           // g_Strikes.storedOuts
#define STATS_REPLAY (g_Stats[0x36])                             // g_Stats.replayInd
#define BATTER_BUNTING (g_Batter[0x8E])                          // g_Batter.isBunting
#define RUNNING_LOGIC_2 (*(s16*)(g_RunningLogic + 0x2))
#define SCORES_C2 (g_Scores[0xC2])
#define BSS32A94_2 (*(s16*)(lbl_3_common_bss_32A94 + 0x2))
#define BALL_FRAMES_SINCE_HIT (*(s16*)(g_Ball + 0x1B66))         // framesSinceHit
#define BALL_PITCH_HANGTIME (*(s16*)(g_Ball + 0x1B68))           // pitchHangtimeCounter
#define BALL_FRAMES_SINCE_GROUND (*(s16*)(g_Ball + 0x1B72))      // framesSinceBallHitGroundOrWasCaught
#define BALL_CONTACT_RESULT (*(s16*)(g_Ball + 0x1B7A))           // AtBat_ContactResult
#define BALL_HIT_VANGLE (*(s16*)(g_Ball + 0x1B9A))               // Hit_VerticalAngle
#define BALL_HIT_HANGLE (*(s16*)(g_Ball + 0x1B9C))               // Hit_HorizontalAngle
#define BALL_HIT_POWER (*(s16*)(g_Ball + 0x1B9E))                // Hit_HorizontalPower
#define BALL_OVER_WALL_FRAMES (*(s16*)(g_Ball + 0x1BA4))         // matchFramesAndBallAngle.ballOverWallFrames
#define BALL_ZONE (g_Ball[0x1BBE])                               // ballZoneAwayFromHome
#define BALL_HIT_DONE (g_Ball[0x1BC6])                           // ballInitialHitDoneInd
#define BALL_DEAD_REASON (g_Ball[0x1BD1])                        // deadBallReason
#define BALL_DEADBALL_LOC ((f32*)(g_Ball + 0x1A3C))              // deadballLastLoc
#define BALL_LANDING_SPOT ((f32*)(g_Ball + 0x1A2C))              // landingSpotLocation (x, z)
extern u8 g_Pitcher[];
extern u8 g_Minigame[];
#define PITCHER_WINDUP (*(s16*)(g_Pitcher + 0x126))          // windupCountdownUntilBallReleased
#define PITCHER_CHAR (*(s16*)(g_Pitcher + 0x11A))            // charID
#define PITCHER_STRIKEOUT_WALK (g_Pitcher[0x14E])            // strikeOutOrWalk
#define PITCHER_UNHITTABLE (g_Pitcher[0x155])                // framesUntilUnhittable
#define PITCHER_CHARGE_TYPE (g_Pitcher[0x15F])               // ChargePitchType
#define PITCHER_PITCH_TYPE (g_Pitcher[0x161])                // TypeOfPitch
#define PITCHER_STAR_IND (g_Pitcher[0x164])                  // starPitchInd
#define PITCHER_STAR_TYPE (g_Pitcher[0x165])                 // starPitchType
#define MINIGAME_ROSTER_ID (*(s8*)(g_Minigame + 0x1905))     // rosterID
#define MINIGAME_CHAR_INDEX(i) (((s8*)(g_Minigame + 0x18CC))[i]) // minigameControlStruct[0].characterIndex
#define MINIGAME_MODE (g_Minigame[0x1A2A])                   // GameMode_MiniGame
#define MINIGAME_PAUSED (g_Minigame[0x1A3B])                 // pauseInd
#define PRACTICE_LEVEL (g_Practice[0x194])                   // practiceLevel
#define GAME_PAUSE_FRAMES (g_GameLogic[0x14E])               // PauseSimulationFrameCount
#define BATTER_CHAR (*(s16*)(g_Batter + 0x62))               // charID
#define BATTER_CHARGE_DOWN (*(s16*)(g_Batter + 0x72))        // frameChargeDownBegins
#define BATTER_CHARGE_FRAMES (*(s16*)(g_Batter + 0x74))      // chargeFrames
#define BATTER_CONTACT_TYPE (g_Batter[0x92])                 // contactType
#define BATTER_CONTACT_SPRITE (g_Batter[0x97])               // displayContactSprite
#define BATTER_CHARGE_STATUS (g_Batter[0x9D])                // chargeStatus
#define BATTER_CAPTAIN_STAR (g_Batter[0xA2])                 // captainStarSwingActivated
#define BALL_STAR_SWING (g_Ball[0x1BE7])                     // currentStarSwing
#define BALL_31C (*(f32*)(g_Ball + 0x31C))                   // physicsSubstruct + 0x19C

// Pitch / swing / star-move sounds.
// NONMATCHING 99%: the pause early-out branches differently (beq; b) and r28/r29 are swapped
#if NONMATCHING
void fn_3_8CD74(void) {
    Snd1760* st = (Snd1760*)lbl_3_bss_1760;
    if (GAME_STATUS == 0xB) {
        return;
    }
    if (MINIGAME_PAUSED != 0) {
        return;
    }
    if (GAME_STATUS == 1) {
        if (PITCHER_WINDUP == 0 && BALL_PITCH_HANGTIME == 0) {
            if (S34C58.unk34 == 0) {
                if (g_d_GameSettings.GameModeSelected == 2 && PRACTICE_LEVEL == 4) {
                    playSoundEffect(0x1AE);
                } else if (MINIGAME_MODE != 1 && MINIGAME_MODE != 3) {
                    if (GAME_PAUSE_FRAMES == 5) {
                        fn_3_90220(PITCHER_CHAR, 6);
                    } else if (PITCHER_CHARGE_TYPE == 3) {
                        playSoundEffect(0x188);
                        fn_3_90220(PITCHER_CHAR, 6);
                    } else if (PITCHER_CHARGE_TYPE != 0) {
                        if (PITCHER_STAR_TYPE == 0) {
                            fn_3_90220(PITCHER_CHAR, 5);
                        }
                        playSoundEffect(0x187);
                    } else if (PITCHER_PITCH_TYPE == 2) {
                        playSoundEffect(0x17D);
                    } else {
                        playSoundEffect(0x186);
                    }
                }
            }
            S34C58.unk34 = 1;
        }
        if (MINIGAME_MODE == 1 && BALL_PITCH_HANGTIME == 1 && PITCHER_STAR_IND != 0) {
            playSoundEffect(0x19E);
            st->pitchVid = playSoundEffect(0x18F);
        }
        if (GAME_PAUSE_FRAMES == 1 && PITCHER_STAR_TYPE != 0) {
            playSoundEffect(0x19E);
            switch (PITCHER_STAR_TYPE) {
            case 1:
            case 2:
                st->pitchVid = playSoundEffect(0x18F);
                break;
            case 3:
            case 4:
                st->pitchVid = playSoundEffect(0x18C);
                break;
            case 5:
            case 6:
                st->pitchVid = playSoundEffect(0x18D);
                break;
            case 7:
            case 8:
                st->pitchVid = playSoundEffect(0x190);
                break;
            case 9:
            case 10:
                st->pitchVid = playSoundEffect(0x18E);
                break;
            case 11:
            case 12:
                st->pitchVid = playSoundEffect(0x19A);
                break;
            }
        }
        if (BALL_PITCH_HANGTIME > 0 && PITCHER_UNHITTABLE < 30 && lbl_8036E548._307D == 0) {
            CharActor* batter = lbl_8036E548.active[9];
            if (g_d_GameSettings.minigamesEnabled) {
                batter = &lbl_8036E548.actors[MINIGAME_CHAR_INDEX(MINIGAME_ROSTER_ID)];
            }
            if (batter != NULL && batter->anim[0] == 0x60 && batter->_06A[0] == 5) {
                fn_3_90220(BATTER_CHAR, 3);
            }
        }
    }
    if (lbl_8036E548._307D == 0) {
        if (S34C58.unk2B != 0 && BALL_FRAMES_SINCE_HIT == 2) {
            S34C58.unk2B = 0;
            sndFXKeyOff(st->pitchVid);
            if (BATTER_BUNTING != 0) {
                playSoundEffect(0x153);
            } else if (BATTER_CAPTAIN_STAR != 0) {
                switch (BATTER_CAPTAIN_STAR) {
                case 1:
                case 2:
                    st->swingVid = playSoundEffect(0x194);
                    break;
                case 3:
                case 4:
                    st->swingVid = playSoundEffect(0x191);
                    break;
                case 5:
                case 6:
                    st->swingVid = playSoundEffect(0x192);
                    break;
                case 7:
                case 8:
                    st->swingVid = playSoundEffect(0x195);
                    break;
                case 9:
                case 10:
                    st->swingVid = playSoundEffect(0x193);
                    break;
                case 11:
                case 12:
                    st->swingVid = playSoundEffect(0x199);
                    st->starSwingDone = 0;
                    break;
                }
                playSoundEffect(0x184);
                playSoundEffect(0x185);
                fn_3_90220(BATTER_CHAR, 0);
            } else if (BATTER_CHAR == 2) {
                playSoundEffect(0x1AF);
            } else if (BATTER_CHAR == 0x26) {
                playSoundEffect(0x1B0);
            } else if (BATTER_CONTACT_SPRITE != 0) {
                playSoundEffect(0x184);
                playSoundEffect(0x185);
            } else if (BATTER_CONTACT_TYPE == 2) {
                playSoundEffect(0x184);
                fn_3_90220(BATTER_CHAR, 0);
            } else if (BATTER_CONTACT_TYPE >= 1 && BATTER_CONTACT_TYPE <= 3) {
                fn_3_90220(BATTER_CHAR, 0);
                playSoundEffect(0x184);
            } else {
                playSoundEffect(0x183);
            }
        }
        if (BATTER_CHARGE_STATUS == 1 && GAME_STATUS == 1 && BATTER_CHARGE_FRAMES < BATTER_CHARGE_DOWN &&
            BATTER_CHARGE_FRAMES == 1) {
            S34C58.unk1C = fn_3_90220(BATTER_CHAR, 2);
        }
    }
    if (BATTER_CAPTAIN_STAR == 11 && st->starSwingDone == 0 && BALL_31C <= lbl_3_rodata_15C8 && BALL_31C >= lbl_3_rodata_15D0) {
        sndFXKeyOff(st->pitchVid);
        st->swingVid = playSoundEffect(0x19B);
        st->starSwingDone = 1;
    }
    if (GAME_STATUS != 1 && GAME_STATUS != 2 && st->pitchVid != 0) {
        sndFXKeyOff(st->pitchVid);
    }
    if (BALL_POS[2] < lbl_3_rodata_15D8 && st->pitchVid != 0) {
        sndFXKeyOff(st->pitchVid);
    }
    if (PITCHER_STRIKEOUT_WALK == 3) {
        sndFXKeyOff(st->pitchVid);
    }
    if (st->swingVid != 0 && (BALL_STAR_SWING == 0 || BALL_DEAD_REASON != 0)) {
        sndFXKeyOff(st->swingVid);
    }
}
#endif

// .text:0x0008D9C0 size:0xC0 mapped:0x806CCA54
void fn_3_8D9C0(void) {
    f32 pos[3];
    f32 up[3];
    Vec dir;
    u8* cam;
    ((void (*)(void))fn_3_8CD74)();
    cam = fn_80052734(0);
    pos[0] = *(f32*)(cam + 0x70);
    pos[1] = *(f32*)(cam + 0x74);
    pos[2] = *(f32*)(cam + 0x78);
    up[0] = 0.0f;
    up[1] = 0.0f;
    up[2] = 0.0f;
    PSVECSubtract((Vec*)(cam + 0x7C), (Vec*)(cam + 0x70), &dir);
    if (PSVECMag(&dir)) {
        PSVECNormalize(&dir, &dir);
    }
    if (*(u32*)(lbl_3_common_bss_32B20 + 8) != 0) {
        sndUpdateListener(lbl_3_common_bss_32B20, pos, up, &dir, lbl_3_data_8D70, 0x7F, 0);
    }
}

// .text:0x0008DA80 size:0x1748 mapped:0x806CCB14
extern u8 lbl_3_common_bss_34C90[];
extern u8 lbl_3_common_bss_37400[];
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_3_common_bss_134C4[];
extern u8* lbl_3_common_bss_DE94;
extern void sndSeqLoop(u32 seqId, bool on);
#define GAME_TEAM_FIELDING (*(s32*)(g_GameLogic + 0x8))        // teamFielding
#define GAME_PITCH_FRAME (*(u16*)(g_GameLogic + 0xFC))          // FrameCountOfCurrentPitch
#define GAME_SECONDARY_MODE (g_GameLogic[0x121])                // secondaryGameMode
#define GAME_EXITING_TO_MENU (g_GameLogic[0x122])               // framesOfExitingToMenu
#define GAME_TRANSITION (g_GameLogic[0x125])                    // _125
#define GAME_END_OF_GAME (g_GameLogic[0x127])                   // EventTriggers_EndOfGame
#define GAME_133(team) (g_GameLogic[0x133 + (team)])            // _133[team]
#define GAME_PLAY_OVER (g_GameLogic[0x139])                     // playOverInd
#define PRACTICE_TYPE2 (g_Practice[0x193])                      // practiceType_2
#define PRACTICE_STATE (g_Practice[0x195])                      // practiceState
#define PRACTICE_TUTORIAL (g_Practice[0x196])                   // tutorialState
#define PRACTICE_19F (g_Practice[0x19F])
#define PRACTICE_1C7 (g_Practice[0x1C7])
#define MINIGAME_1907 (g_Minigame[0x1907])
#define MINIGAME_1908 (*(s8*)(g_Minigame + 0x1908))
#define MINIGAME_MULTIPLAYER (g_Minigame[0x1909])               // multiPlayerInd
#define MINIGAME_CTRL_1C(i) (g_Minigame[0x18E8 + (i)])          // minigameControlStruct[0]._1C[i]
#define MINIGAME_NOT_WON (g_Minigame[0x19A8])                   // challenge_minigame_haven_tWonYetIndicator
#define MINIGAME_19CE (g_Minigame[0x19CE])
#define MINIGAME_DIFFICULTY (g_Minigame[0x1A2B])                // soloMinigameDifficulty
#define MINIGAME_1A37 (g_Minigame[0x1A37])
#define MINIGAME_1A3C (g_Minigame[0x1A3C])
#define MINIGAME_1A43 (g_Minigame[0x1A43])
#define MINIGAME_1D6D (*(s8*)(g_Minigame + 0x1D6D))
#define STATS_PLAY_FRAMES (*(s32*)(g_Stats + 0x24))             // playFrameCounter
#define STATS_28 (*(s16*)(g_Stats + 0x28))
#define STATS_39 (g_Stats[0x39])                                // 1: replay offered, 2: replay done
#define PITCHER_WALKED_IN_RUN (g_Pitcher[0x175])                // walkedInRunInd
#define BSS34C90_1D1 (lbl_3_common_bss_34C90[0x1D1])
#define BSS34C90_1D2 (lbl_3_common_bss_34C90[0x1D2])
#define BSS32A94_3E (lbl_3_common_bss_32A94[0x3E])
#define DE94_92C (*(s32*)(lbl_3_common_bss_DE94 + 0x92C))      // lbl_3_common_bss_DE94._0000->_92C
extern u16 lbl_3_data_81FC[];
extern u8 lbl_3_data_84F4[];

// Per-frame music director: picks the BGM sequence for the current game state,
// cross-fades between tracks and handles crowd/ambience volume ramps.
// NONMATCHING 84%: register allocation differs and the original reaches the .bss statics
// (lbl_3_bss_1760-1780) through one pooled base
#if NONMATCHING
void fn_3_8DA80(void) {
    s16 bgm = -1;
    s32 cut = 0;
    Snd1760* st = (Snd1760*)lbl_3_bss_1760;
    u8 status;

    switch (g_d_GameSettings.GameModeSelected) {
    case 2:
        if (PRACTICE_TUTORIAL == 0 && PRACTICE_STATE == 0) {
            fn_3_8B318(g_d_GameSettings.StadiumID);
        }
        break;
    default:
        if (GAME_STATUS == 5 && GAME_PITCH_FRAME == 1) {
            fn_3_8B318(g_d_GameSettings.StadiumID);
        }
        break;
    }

    if (GAME_EXITING_TO_MENU != 0) {
        return;
    }
    status = GAME_STATUS;
    if (status == 0x17) {
        return;
    }
    if (status == 0xE && !g_d_GameSettings.minigamesEnabled) {
        return;
    }
    if (S34C58.unk33 != 0 && status == 0) {
        S34C58.unk33--;
    }
    fn_3_8D9C0();

    if (lbl_800EF808[0x398] == 0) {
        if ((u32)S34C58.unk4 != 0xFFFFFFFF) {
            if (sndSeqGetValid(S34C58.unk4)) {
                sndSeqVolume(0, 0, S34C58.unk4, 1);
            }
            S34C58.unk4 = -1;
        }
        return;
    }

    S34C58.unk22 = S34C58.unk20;

    if (g_d_GameSettings.GameModeSelected == 2) {
        u8 sec = GAME_SECONDARY_MODE;
        if (sec == 0xA || sec == 0x11 || sec == 0x12) {
            bgm = -1;
            goto apply;
        }
        if (PRACTICE_TUTORIAL == 0) {
            bgm = -1;
            goto apply;
        }
        if (PRACTICE_19F != 0 && (BSS34C90_1D2 == 6 || BSS34C90_1D2 == 7 || BSS34C90_1D2 == 8 || BSS34C90_1D2 == 9)) {
            bgm = -1;
            goto apply;
        }
        if (PRACTICE_1C7 != 0 && (BSS34C90_1D2 == 6 || BSS34C90_1D2 == 7)) {
            bgm = -1;
            goto apply;
        }
        if (PRACTICE_TYPE2 == 4) {
            if (GAME_STATUS == 5) {
                return;
            }
            goto common;
        }
        bgm = 0x15;
        if (BALL_DEAD_REASON != 1 || sec == 0xB) {
            goto apply;
        }
        bgm = 0;
        goto common;
    }

    if (g_d_GameSettings.minigamesEnabled && GAME_STATUS == 0x21) {
        bgm = -1;
        goto apply;
    }
    status = GAME_STATUS;
    if ((status == 0x27 || status == 0x24 || status == 0x22) && MINIGAME_1908 >= 0 && MINIGAME_1A3C != 0) {
        if (status == 0x22) {
            return;
        }
        if (status == 0x24) {
            if (GAME_PITCH_FRAME == 1) {
                fn_3_8C104(-1);
            }
            return;
        }
        if (MINIGAME_CTRL_1C(MINIGAME_1908) == 1 && MINIGAME_NOT_WON == 0) {
            bgm = 0xC;
        } else {
            bgm = 0xD;
        }
        goto apply;
    }

    if (g_d_GameSettings.minigamesEnabled &&
        (status == 0xE || status == 0x24 || GAME_TRANSITION == 8 || status == 0x22 || status == 0x27 || status == 0x26)) {
        if (status == 0xE || status == 0x24 || status == 0x22 || status == 0x26 || status == 0x27) {
            if (status == 0x22) {
                if (g_d_GameSettings.GameModeSelected == 6) {
                    if (BSS34C90_1D2 == 10 || BSS34C90_1D2 == 4 || BSS34C90_1D2 == 5) {
                        goto fade_out_quick;
                    }
                } else if (BSS34C90_1D2 == 9 || BSS34C90_1D2 == 6 || BSS34C90_1D2 == 7) {
                    goto fade_out_quick;
                }
            }
            if (status == 0x26) {
                return;
            }
            if (!g_d_GameSettings.exhibitionMatchInd) {
                if (MINIGAME_MODE == 1 || MINIGAME_MODE == 3) {
                    if (MINIGAME_1A37 == 1) {
                        bgm = 0xC;
                    } else {
                        bgm = 0xD;
                    }
                } else if (MINIGAME_CTRL_1C(MINIGAME_1908) == 1 && MINIGAME_NOT_WON == 0) {
                    bgm = 0xC;
                } else {
                    bgm = 0xD;
                }
                goto apply;
            }
            if (g_d_GameSettings.GameModeSelected == 6) {
                if (MINIGAME_1908 >= 0) {
                    if (MINIGAME_CTRL_1C(MINIGAME_1908) == 1 && MINIGAME_NOT_WON == 0) {
                        bgm = 5;
                    } else {
                        bgm = 7;
                    }
                } else {
                    bgm = 5;
                }
                goto apply;
            }
            if (MINIGAME_MULTIPLAYER != 0) {
                if (MINIGAME_1A3C != 0 && MINIGAME_1907 == 1) {
                    if (MINIGAME_CTRL_1C(MINIGAME_1908) == 1 && MINIGAME_NOT_WON == 0) {
                        bgm = 5;
                    } else {
                        bgm = 7;
                    }
                } else if (MINIGAME_NOT_WON != 0) {
                    bgm = 7;
                } else {
                    bgm = 5;
                }
                goto apply;
            }
            if (MINIGAME_DIFFICULTY == 3 && MINIGAME_1A3C == 0) {
                if (GAME_PITCH_FRAME == 0) {
                    return;
                }
                if (MINIGAME_1A43 == 1) {
                    bgm = 0xE;
                } else if (MINIGAME_1A43 != 0) {
                    bgm = 0xF;
                } else {
                    bgm = 7;
                }
                goto apply;
            }
            if (MINIGAME_1A37 == 1) {
                bgm = 5;
            } else {
                bgm = 7;
            }
            goto apply;
        }
        if (GAME_TRANSITION == 8) {
            sndSeqLoop(S34C58.unk8, 0);
        }
        goto by_status;
    }

    if (g_d_GameSettings.GameModeSelected == 7) {
        if (status >= 0x1B) {
            bgm = -1;
            goto apply;
        }
        if (status == 5) {
            bgm = 6;
            goto apply;
        }
        // BGM volume table entry -1 (lbl_3_data_830C[-2]), i.e. the last bytes of lbl_3_data_81FC
        sndSeqVolume(((u8*)lbl_3_data_81FC)[0x10E], 15, S34C58.unk4, 0);
        if (MINIGAME_MODE == 6) {
            if (MINIGAME_1D6D >= 0) {
                cut = 1;
                if (MINIGAME_PAUSED != 0) {
                    sndFXKeyOff(S34C58.unk4);
                } else if (S34C58.unk20 == 0x13 && sndFXCheck(S34C58.unk4) == 0xFFFFFFFF) {
                    /* fn_3_90064(0x2ED), keeping the voice id */
                    s32 i;
                    if (g_d_GameSettings.GameModeSelected != 7) {
                        OSPanic(lbl_3_rodata_1590, 0x402, lbl_3_rodata_15DC);
                    }
                    for (i = 0; i < 0x39; i++) {
                        if (lbl_3_data_81FC[i] == 0x2ED) {
                            break;
                        }
                    }
                    if (i == 0x39) {
                        OSPanic(lbl_3_rodata_1590, 0x40D, lbl_3_rodata_15EC);
                    }
                    S34C58.unk4 = sndFXStartEx(0x2ED, lbl_3_data_84F4[i], 0x3F, 0);
                }
                bgm = 0x13;
            } else {
                if (sndFXCheck(S34C58.unk4) != 0xFFFFFFFF) {
                    sndFXKeyOff(S34C58.unk4);
                }
                bgm = 0x15;
            }
        } else {
            bgm = 0x15;
        }
        if (MINIGAME_PAUSED != 0) {
            if (BSS34C90_1D2 == 7 || BSS34C90_1D2 == 9) {
                bgm = -1;
            } else {
                fn_800A8878(lbl_800E88A4[g_d_GameSettings.StadiumID][1], lbl_800E88A4[g_d_GameSettings.StadiumID][1]);
            }
        } else {
            fn_800A8878(lbl_800E88A4[g_d_GameSettings.StadiumID][0], lbl_800E88A4[g_d_GameSettings.StadiumID][0]);
        }
        goto apply;
    }

    if (g_d_GameSettings.minigamesEnabled) {
        if (status == 0x22 || status == 0xB || status == 0xD || MINIGAME_19CE != 0) {
            if (S34C58.unk22 != -1) {
                fn_800A8878(lbl_800E88A4[9][1], lbl_800E88A4[9][1]);
            }
            S34C58.unk20 = -1;
            return;
        }
        fn_800A8878(lbl_800E88A4[9][0], lbl_800E88A4[9][0]);
        if (GAME_STATUS >= 0x1B) {
            return;
        }
        if (GAME_STATUS == 5) {
            bgm = 0;
        } else {
            bgm = 0x15;
        }
        goto apply;
    }

by_status:
    status = GAME_STATUS;
    if (status == 5 && g_d_GameSettings.GameModeSelected != 2) {
        bgm = 0;
        goto apply;
    }
    if (status == 9) {
        bgm = 1;
        goto apply;
    }
    if (status == 3) {
        bgm = 2;
        goto apply;
    }
    if (status == 8) {
        bgm = -1;
        cut = 1;
        if (STRIKES_OUTS != 3 && STATS_39 == 0) {
            if (PITCHER_WALKED_IN_RUN != 0) {
                playSoundEffect(0x198);
            } else if (GAME_END_OF_GAME == 0) {
                playSoundEffect(0x197);
            }
        }
        goto apply;
    }

common:
    if (GAME_STATUS == 0xB) {
        if (BSS34C90_1D1 == 1) {
            goto apply;
        }
        if (S34C58.unk20 != 0x15) {
            S34C58.unk20 = 0x15;
            S34C58.unk22 = 0x15;
            fn_3_8C104(0);
        }
    }
    if (STATS_REPLAY != 0) {
        bgm = 0x16;
        if (STATS_39 == 4) {
            bgm = -1;
            cut = 1;
        }
        if (STATS_PLAY_FRAMES > STATS_28 - 30) {
            bgm = -1;
            cut = 1;
        }
        goto apply;
    }
    status = GAME_STATUS;
    if (status == 0x13) {
        bgm = 0x17;
        goto apply;
    }
    if (status == 7 || status == 0) {
        return;
    }
    if (lbl_8036E548.preload[0].state != 0 || lbl_8036E548.preload[1].state != 0) {
        return;
    }
    if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x46] != 0) {
        if (status == 0x16 && GAME_133(GAME_TEAM_FIELDING) == 0) {
            bgm = 9;
            S34C58.unk32 = 1;
            goto apply;
        }
        if (S34C58.unk32 == 0) {
            if (status == 1 && GAME_133(GAME_TEAM_FIELDING) == 0) {
                S34C58.unk32 = 2;
                bgm = 0x12;
                goto apply;
            }
        } else if (S34C58.unk32 == 2 && lbl_3_common_bss_32724[0xB3] != 0) {
            S34C58.unk32 = 2;
            bgm = 0x12;
            goto apply;
        }
        if ((status == 1 || status == 2) && STATS_REPLAY == 0) {
            if (lbl_3_common_bss_37400[0x47] == 1) {
                if (BALL_DEAD_REASON != 1) {
                    bgm = 0xB;
                    if (FIELDING_107 != 0) {
                        S34C58.unk33 = 2;
                    }
                    goto apply;
                }
            } else if (lbl_3_common_bss_37400[0x47] == 2 && BALL_DEAD_REASON != 1) {
                bgm = 0xA;
                if (FIELDING_107 != 0) {
                    S34C58.unk33 = 2;
                }
                goto apply;
            }
        }
    }
    if (status == 0x16 && GAME_PLAY_OVER != 0) {
        bgm = 0x10;
        goto apply;
    }
    if (status == 0x15) {
        bgm = 0x11;
        goto apply;
    }
    if (status == 0x16 && DE94_92C == 0x60 && g_d_GameSettings.GameModeSelected != 5) {
        DE94_92C = 0;
        bgm = 8;
        S34C58.unk2E = 1;
        goto apply;
    }
    if (S34C58.unk2E != 0) {
        if (S34C58.unk27 == 0) {
            S34C58.unk2E = 0;
        }
        bgm = 8;
        goto apply;
    }
    if (lbl_3_common_bss_134C4[0x25C] != 0 && BALL_DEAD_REASON != 1 && DE94_92C != 0) {
        bgm = 4;
        goto apply;
    }
    if (status == 0x13) {
        return;
    }
    if (BALL_DEAD_REASON == 1) {
        if (g_d_GameSettings.GameModeSelected != 2) {
            bgm = 3;
            goto apply;
        }
        bgm = 0;
    }

    /* crowd/ambience fade out */
    if (S34C58.unk2A == 1 && S34C58.unk24 != 0) {
        s16 n = --S34C58.unk24;
        if (n == 0) {
            fn_3_8B258(3, 0, 0);
        } else {
            fn_3_8C4F0(n, 0);
        }
    }
    /* crowd/ambience fade in */
    if (S34C58.unk2A == 2) {
        if (S34C58.unk33 != 0) {
            S34C58.unk33 = 0;
            S34C58.unk20 = 0x15;
        }
        if (S34C58.unk24 == 0x78) {
            fn_3_8C104(0);
        }
        if (fn_3_8C2DC(S34C58.unk24, GAME_STATUS == 0xB ? 1 : 0) == 0) {
            S34C58.unk2A = 0;
        }
        S34C58.unk24--;
    }

    if (BALL_DEAD_REASON == 1 && g_d_GameSettings.GameModeSelected == 2) {
        goto apply;
    }
    status = GAME_STATUS;
    if (status == 2) {
        if (S34C58.unk29 != 0) {
            S34C58.unk29--;
        }
        return;
    }
    if (S34C58.unk2A != 0 || status == 0xB) {
        return;
    }
    if (S34C58.unk33 != 0) {
        bgm = 0x15;
        goto apply;
    }
    if (STRIKES_STORED_OUTS == 0) {
        bgm = 0x15;
        goto apply;
    }
    if (BSS32A94_3E != 0) {
        bgm = 0x15;
        goto apply;
    }
    fn_3_90328(-1);
    S34C58.unk20 = -1;
    return;

apply:
    if (S34C58.unk22 == bgm) {
        return;
    }
    if (S34C58.unk20 == 8 && sndSeqGetValid(S34C58.unk8)) {
        return;
    }
    if (S34C58.unk28 == 0) {
        S34C58.unk28 = 1;
        S34C58.unk27 = 20;
        fn_3_903B8();
    } else if (S34C58.unk27 != 0) {
        S34C58.unk27--;
    }
    if (S34C58.unk27 != 0 && cut == 0) {
        return;
    }
    if ((u32)S34C58.unk4 != 0xFFFFFFFF) {
        if (sndSeqGetValid(S34C58.unk4)) {
            sndSeqVolume(0, 0, S34C58.unk4, 1);
        }
        S34C58.unk4 = -1;
        return;
    }
    S34C58.unk28 = 0;
    S34C58.unk20 = bgm;
    if (bgm == -1) {
        if (cut) {
            fn_3_8B258(3, 0, 0);
        } else {
            fn_3_8C07C();
        }
    } else if (bgm == 0x15 || bgm == 0x16 || bgm == 0x17) {
        if ((u16)(bgm - 0x15) <= 1 || bgm == 0x17) {
            if (bgm != S34C58.unk22) {
                fn_3_8C104(-1);
            }
        } else {
            fn_3_8C07C();
            fn_3_90674(S34C58.unk20);
        }
    } else {
        fn_3_9056C(bgm);
        if (!(bgm == 4 || bgm == 0)) {
            fn_3_8C07C();
        }
    }
    return;

fade_out_quick:
    fn_3_90328(12);
    S34C58.unk20 = -1;
}
#endif

// .text:0x0008F1C8 size:0x54 mapped:0x806CE25C
void fn_3_8F1C8(void) {
    *(s16*)(B34C58 + 0x20) = -1;
    *(s16*)(B34C58 + 0x22) = -1;
    B34C58[0x29] = 0;
    B34C58[0x2A] = 0;
    lbl_3_bss_1768 = fn_800B0A5C_insertQueue(fn_3_8B094, 0);
}

// .text:0x0008F21C size:0x9F0 mapped:0x806CE2B0

// Crowd-reaction sounds (cheer / groan / "ooh") for the current play.
void fn_3_8F21C(void) {
    s32 stop = 0;
    s32 special = 0;
    s32 i;
    if (!(g_d_GameSettings.StadiumID != 1 && g_d_GameSettings.StadiumID != 2 && g_d_GameSettings.StadiumID != 3 && g_d_GameSettings.StadiumID != 5)) {
        special = 1;
    }
    special = special != 0;
    if (special) {
        if (FIELDING_107 != 0) {
            for (i = 1; i < 4; i++) {
                if (S34C58.unk26 <= 1 && RUNNER_STATUS(i) == 2) {
                    stop = 1;
                    goto stop_sounds;
                }
            }
        }
        if (BALL_FRAMES_SINCE_HIT > 0 &&
            ((BALL_HIT_DONE != 0 && BALL_CONTACT_RESULT == 1 && BALL_ZONE >= 3 && S34C58.unk26 < 2) ||
             (RUNNER_STATUS(0) == 1 && RUNNER_CUR_BASE(0) != 0 && RUNNER_FORCE_OUT(0) == 0 &&
              (BALL_CONTACT_RESULT == 1 || BALL_CONTACT_RESULT == 2) && STRIKES_OUTS == STRIKES_STORED_OUTS))) {
            S34C58.unk26 = 2;
            if ((u32)S34C58.unk14 == 0xFFFFFFFF) {
                S34C58.unk14 = sndFXStartEx(0x156, 0, 0x3F, 0);
                if (STATS_REPLAY == 0 && g_d_GameSettings.GameModeSelected != 7) {
                    playSoundEffect(0x196);
                }
            }
        }
        return;
    }

    if (GAME_STATUS == 3) {
        stop = 1;
    } else if (GAME_STATUS == 1) {
        if (BALL_PITCH_HANGTIME == 10) {
            for (i = 1; i < 4; i++) {
                if (RUNNER_STATUS(i) == 1 && RUNNER_WALK_FORCED(i) != 0) {
                    if ((u32)S34C58.unk10 == 0xFFFFFFFF) {
                        S34C58.unk10 = playSoundEffect(0x155);
                    }
                    break;
                }
            }
        }
    } else if (FIELDING_107 != 0) {
        for (i = 1; i < 4; i++) {
            if (S34C58.unk26 == 0 &&
                ((RUNNER_STATUS(i) == 1 && RUNNER_BASE_STANDING(i) > i) || RUNNER_STATUS(i) == 3)) {
                S34C58.unk26 = 1;
                if ((u32)S34C58.unk10 == 0xFFFFFFFF) {
                    S34C58.unk10 = playSoundEffect(0x155);
                }
            } else if (S34C58.unk26 <= 1 && RUNNER_STATUS(i) == 2) {
                S34C58.unk26 = 2;
                playSoundEffect(0x158);
                stop = 1;
                break;
            }
        }
    } else if (BALL_FRAMES_SINCE_HIT > 0) {
        if (BALL_FRAMES_SINCE_HIT > 20 && S34C58.unk26 == 0) {
            S34C58.unk26 = 1;
            if (BATTER_BUNTING != 0) {
                if ((RUNNING_LOGIC_2 == 1 || (RUNNING_LOGIC_2 & 0x1000)) && (u32)S34C58.unk10 == 0xFFFFFFFF) {
                    S34C58.unk10 = playSoundEffect(0x155);
                }
            } else if (BALL_HIT_POWER > 150 && (BALL_HIT_VANGLE > 0xF80 || BALL_HIT_VANGLE < 0x200) &&
                       BALL_HIT_HANGLE > 0x80 && BALL_HIT_HANGLE < 0x780 && (u32)S34C58.unk10 == 0xFFFFFFFF) {
                S34C58.unk10 = playSoundEffect(0x155);
            }
        }
        if ((BALL_HIT_DONE != 0 && BALL_CONTACT_RESULT == 1 && BALL_ZONE >= 3 && S34C58.unk26 < 2) ||
            (RUNNER_STATUS(0) == 1 && RUNNER_CUR_BASE(0) != 0 && RUNNER_FORCE_OUT(0) == 0 &&
             (BALL_CONTACT_RESULT == 1 || BALL_CONTACT_RESULT == 2) && STRIKES_OUTS == STRIKES_STORED_OUTS)) {
            S34C58.unk26 = 2;
            if ((u32)S34C58.unk14 == 0xFFFFFFFF) {
                S34C58.unk14 = playSoundEffect(0x156);
                if (STATS_REPLAY == 0 && g_d_GameSettings.GameModeSelected != 7) {
                    playSoundEffect(0x196);
                }
            }
        }
        if (BALL_DEAD_REASON == 1 && S34C58.unk26 < 9) {
            S34C58.unk26 = 9;
            if ((u32)S34C58.unk14 == 0xFFFFFFFF) {
                S34C58.unk14 = playSoundEffect(0x156);
            }
        }
        if (BALL_CONTACT_RESULT == -1 && S34C58.unk26 < 9) {
            if (BALL_DEAD_REASON == 2) {
                if (BALL_OVER_WALL_FRAMES == 30) {
                    S34C58.unk26 = 9;
                    stop = 1;
                    if (fn_3_B7D6C(BALL_DEADBALL_LOC[0], BALL_DEADBALL_LOC[2])) {
                        playSoundEffect(0x158);
                    }
                }
            } else if (BALL_FRAMES_SINCE_GROUND == 30) {
                S34C58.unk26 = 9;
                stop = 1;
                if (fn_3_B7D6C(BALL_LANDING_SPOT[0], BALL_LANDING_SPOT[1]) &&
                    (BALL_ZONE == 4 || (BALL_HIT_POWER > 150 && (BALL_HIT_VANGLE > 0xFC0 || BALL_HIT_VANGLE < 0x200)))) {
                    playSoundEffect(0x157);
                }
            }
        }
        if (RUNNER_STATUS(0) == 2 && RUNNER_FRAMES_SINCE_OUT(0) == 20 && SCORES_C2 == 0 &&
            (RUNNER_STATUS(3) != 1 || !(RUNNER_BASES_RAN(3) > 3.5f))) {
            s32 react = 0;
            if (BSS32A94_2 == 0x15 || BSS32A94_2 == 0x18 || BSS32A94_2 == 0x16) {
                react = 1;
            }
            if (BSS32A94_2 == 0x12 && (BALL_ZONE <= 1 || fn_3_B7E10(BALL_POS[0], BALL_POS[2]))) {
                react = 1;
            }
            if (BSS32A94_2 == 0x13 && BALL_ZONE <= 1 && BALL_HIT_POWER > 180) {
                react = 1;
            }
            if (react) {
                stop = 1;
                playSoundEffect(0x157);
            }
        }
    }

stop_sounds:
    if (stop) {
        if ((u32)S34C58.unk10 != 0xFFFFFFFF) {
            sndFXKeyOff(S34C58.unk10);
            S34C58.unk10 = -1;
        }
        if ((u32)S34C58.unk14 != 0xFFFFFFFF) {
            sndFXKeyOff(S34C58.unk14);
            S34C58.unk14 = -1;
        }
    }
    if (GAME_STATUS == 0xB) {
        for (i = 0; i < 3; i++) {
            if ((u32)(&S34C58.unkC)[i] != 0xFFFFFFFF) {
                sndFXKeyOff((&S34C58.unkC)[i]);
                (&S34C58.unkC)[i] = -1;
            }
        }
    }
}

// .text:0x0008FC0C size:0x74 mapped:0x806CECA0
void fn_3_8FC0C(void) {
    B34C58[0x26] = 0;
    if (*(u32*)(B34C58 + 0x10) != 0xFFFFFFFF) {
        sndFXKeyOff(*(u32*)(B34C58 + 0x10));
        *(s32*)(B34C58 + 0x10) = -1;
    }
    if (*(u32*)(B34C58 + 0x14) != 0xFFFFFFFF) {
        sndFXKeyOff(*(u32*)(B34C58 + 0x14));
        *(s32*)(B34C58 + 0x14) = -1;
    }
}

// .text:0x0008FC80 size:0x298 mapped:0x806CED14
extern s16 lbl_3_data_88B8[];
extern f32 lbl_3_rodata_1604;
extern f32 lbl_3_rodata_1608;
extern f32 lbl_3_rodata_160C;
extern f32 lbl_3_rodata_157C;
void fn_3_8FC80(void) {
    u8 st = g_GameLogic[0x121];
    if ((st == 0 || (u8)(st - 0xB) <= 4 || st == 0x10)
        && (g_d_GameSettings.GameModeSelected != 2 || (g_Practice[0x19F] == 0 && g_Practice[0x196] != 0))
        && g_GameLogic[0x11E] == 2
        && *(f32*)(g_Ball + 0x4) > lbl_3_rodata_1604
        && *(f32*)(g_Ball + 0x19D4) > lbl_3_rodata_1608
        && (!(*(f32*)(g_Ball + 0x4) < lbl_3_rodata_160C) || !(*(f32*)(g_Ball + 0x31C) < lbl_3_rodata_157C))
        && *(s16*)(g_Ball + 0x1B96) == 0
        && g_Ball[0x1BF4] == 0
        && g_Ball[0x1BD1] == 0
        && *(s16*)(g_Ball + 0x1B7A) != 1
        && !(*(s16*)(g_Ball + 0x1B7A) == 2 || *(s16*)(g_Ball + 0x1B7A) == 3)) {
        s32 v;
        s32 r;
        f32 f;
        if ((u32)S34C58.unk18 == 0xFFFFFFFF) {
            u32 vid = playSoundEffect(0x17F);
            S34C58.unk18 = vid;
            sndFXCtrl(vid, 7, lbl_3_data_88B8[4]);
        }
        r = *(f32*)(g_Ball + 0x4);
        v = r;
        if (r > lbl_3_data_88B8[3]) {
            v = lbl_3_data_88B8[3];
        }
        v -= lbl_3_data_88B8[2];
        f = (f32)v / (f32)(lbl_3_data_88B8[3] - lbl_3_data_88B8[2]);
        sndFXCtrl14(S34C58.unk18, 0x80, lbl_3_data_88B8[0] + (s32)(f * (f32)(lbl_3_data_88B8[1] - lbl_3_data_88B8[0])));
    } else {
        if ((u32)S34C58.unk18 != 0xFFFFFFFF) {
            sndFXKeyOff(S34C58.unk18);
            S34C58.unk18 = -1;
        }
    }
}

// .text:0x0008FF18 size:0x44 mapped:0x806CEFAC
void fn_3_8FF18(void) {
    S34C58.unkC = -1;
    S34C58.unk10 = -1;
    S34C58.unk14 = -1;
    S34C58.unk18 = -1;
    S34C58.unk1C = -1;
    S34C58.unk28 = 0;
    lbl_3_bss_1780[0] = -1;
    S34C58.unk4 = -1;
    S34C58.unk8 = -1;
    S34C58.unk2F = 0;
    S34C58.unk33 = 0;
}

extern const f32 lbl_3_rodata_15BC; // 127.0f
extern const f32 lbl_3_rodata_15C0; // 640.0f
// .text:0x0008FF5C size:0x108 mapped:0x806CEFF0
u32 fn_3_8FF5C(s32 id, f32 x, f32 y, f32 z) {
    int sx;
    int sy;
    u32 pan = 0x3F;
    u32 vid;
    if (lbl_800EF808[0x396] == 1) {
        fn_3_1650C(&sx, &sy, 1, x, -y, z);
        if (sx < 0) {
            pan = 0;
        } else if (sx > 640) {
            pan = 0x7F;
        } else {
            pan = (s32)(lbl_3_rodata_15BC * ((f32)sx / lbl_3_rodata_15C0));
        }
    }
    vid = sndFXStartEx(id, lbl_3_data_8338[id * 2 - 0x2A2], pan, 0);
    sndFXCtrl(vid, 0x5B, lbl_3_data_8338[id * 2 - 0x2A1]);
    return vid;
}

// .text:0x00090064 size:0xEC mapped:0x806CF0F8
u32 fn_3_90064(s32 id) {
    s32 i;
    if (g_d_GameSettings.GameModeSelected != 7) {
        OSPanic(lbl_3_rodata_1590, 0x402, lbl_3_rodata_15DC);
    }
    for (i = 0; i < 0x39; i++) {
        if (id == lbl_3_data_81FC[i]) {
            break;
        }
    }
    if (i == 0x39) {
        OSPanic(lbl_3_rodata_1590, 0x40D, lbl_3_rodata_15EC);
    }
    return sndFXStartEx((u16)id, lbl_3_data_84F4[i], 0x3F, 0);
}

// .text:0x00090150 size:0xD0 mapped:0x806CF1E4
// NONMATCHING 68%: scheduling: the original converts vol before ctrl (stack slots swapped) and loads the
// conversion constant with addi
#if NONMATCHING
u32 fn_3_90150(s32 a, s32 b) {
    s32 v1;
    s32 v2;
    u32 h;
    v1 = (s32)lbl_3_data_8530[b] * lbl_3_data_8830;
    v2 = (s32)lbl_3_data_8530[b + 0x180] * lbl_3_data_8830;
    h = sndFXStartEx(b + lbl_3_data_8168[a], v1, 0x3F, 0);
    sndFXCtrl(h, 0x5B, v2);
    return h;
}
#endif



// .text:0x00090220 size:0x74 mapped:0x806CF2B4
u32 fn_3_90220(s32 idx, s32 off) {
    u32 id = off + lbl_3_data_8168[idx];
    u32 vol = lbl_3_data_8530[off];
    u32 ctrl = lbl_3_data_8530[off + 0x180];
    u32 vid = sndFXStartEx(id, vol, 0x3F, 0);
    sndFXCtrl(vid, 0x5B, ctrl);
    return vid;
}

// .text:0x00090294 size:0x68 mapped:0x806CF328
u32 playSoundEffect(s32 id) {
    u32 vid = sndFXStartEx(id, lbl_3_data_8338[id * 2 - 0x2A2], 0x3F, 0);
    sndFXCtrl(vid, 0x5B, lbl_3_data_8338[id * 2 - 0x2A1]);
    return vid;
}

// .text:0x00090328 size:0x90 mapped:0x806CF3BC
void fn_3_90328(s32 vol) {
    if (vol < 0) {
        vol = 3000;
    }
    {
        SndState34C58* s = &S34C58;
        if (sndSeqGetValid(s->unk4)) {
            sndSeqVolume(0, vol, s->unk4, 1);
        }
    }
    {
        SndState34C58* s = &S34C58;
        if (sndSeqGetValid(s->unk8)) {
            sndSeqVolume(0, vol, s->unk8, 1);
        }
    }
}

// .text:0x000903B8 size:0x7C mapped:0x806CF44C
void fn_3_903B8(void) {
    SndState34C58* s = &S34C58;
    if (sndSeqGetValid(s->unk4)) {
        sndSeqVolume(0, 0xA0, s->unk4, 1);
    }
    s = &S34C58;
    if (sndSeqGetValid(s->unk8)) {
        sndSeqVolume(0, 0xA0, s->unk8, 1);
    }
}

// .text:0x00090434 size:0x138
void fn_3_90434(void) {
    SndState34C58* s;
    s32 i;
    fn_800A86B4(3);
    fn_800A8B78(fn_800A88C0());
    s = &S34C58;
    if (sndSeqGetValid(s->unk4)) {
        sndSeqVolume(0, 0, s->unk4, 1);
    }
    s = &S34C58;
    if (sndSeqGetValid(s->unk8)) {
        sndSeqVolume(0, 0, s->unk8, 1);
    }
    for (i = 0; i < 3; i++) {
        if (*(u32*)(B34C58 + 0xC + i * 4) != 0xFFFFFFFF) {
            sndFXKeyOff(*(u32*)(B34C58 + 0xC + i * 4));
            *(s32*)(B34C58 + 0xC + i * 4) = -1;
        }
    }
    fn_3_8BDF4();
}

// .text:0x00090674 size:0x88 mapped:0x806CF708
void fn_3_90674(s32 idx) {
    SeqEnt6* e = &lbl_3_data_88E0[idx];
    S34C58.unk4 = sndSeqPlayEx(e->a, e->b, (void*)lbl_3_bss_1774[idx], 0, 0);
    sndSeqVolume(lbl_3_data_830C[idx * 2], 0, S34C58.unk4, 0);
}

// .text:0x000906FC size:0x58 mapped:0x806CF790
void fn_3_906FC(void) {
    u32* p;
    u32 base;
    s32 i;
    base = S34C58.unk0;
    p = (u32*)base;
    for (i = 0; i < (g_d_GameSettings.GameModeSelected == 2 ? 1 : 0x14); i++) {
        *p += base;
        p++;
    }
    lbl_3_bss_1774 = (u32*)base;
}

// .text:0x0009056C size:0x108 mapped:0x806CF600
typedef struct { u8 v, pad; } SeqVol2;
u32 fn_3_9056C(s32 idx) {
    SeqEnt6* e;
    SndState34C58* s;
    u8 vol;
    if (g_d_GameSettings.GameModeSelected != 2) {
        e = lbl_3_data_88E0;
        e += idx;
    } else {
        e = &lbl_3_data_8954;
        e += idx;
    }
    s = &S34C58;
    if (sndSeqGetValid(s->unk8)) {
        sndSeqVolume(0, 0, s->unk8, 1);
        return 0;
    }
    s->unk8 = sndSeqPlayEx(e->a, e->b, (void*)lbl_3_bss_1774[idx], 0, 0);
    lbl_800EF808[0x391] = vol = ((SeqVol2*)lbl_3_data_830C)[idx].v;
    sndSeqVolume(vol, 0, s->unk8, 0);
    return 1;
}
