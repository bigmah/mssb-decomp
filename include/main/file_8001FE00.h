#ifndef __MAIN_FILE_8001FE00_H__
#define __MAIN_FILE_8001FE00_H__

#include "mssbTypes.h"
#include "main/file_8000F150.h"

// Screen transition (fade) state.
typedef struct SceneFade {
    /*0x00*/ TexArchive* tex;      // loading-screen texture (ARAM)
    /*0x04*/ TexImage* texObj;
    /*0x08*/ u16 duration;
    /*0x0A*/ u16 _0A;
    /*0x0C*/ u16 requestDuration;
    /*0x0E*/ u16 alpha;            // 0..255
    /*0x10*/ u8 state;
    /*0x11*/ u8 request;
    /*0x12*/ u8 done;
    /*0x13*/ u8 _13;
    /*0x14*/ u8 variant;
    /*0x15*/ u8 _15;
    /*0x16*/ u8 _16;
    /*0x17*/ u8 _17;
    /*0x18*/ u8 loadIndex;
    /*0x19*/ u8 loadState;
    /*0x1A*/ u8 fadeAlpha;
    /*0x1B*/ u8 lastPick;
} SceneFade; // size: 0x1C

extern SceneFade lbl_8037169C;

void fn_8001FE00(LayoutGroup* group);
s32 calledWhenStartingMatch(void);
s32 fn_80020218(void);
void fn_8002024C(void);
s32 fn_80020278(s32 index);
s32 fn_80020388(void);
void fn_800203E0(u8 scene, s8 variant);
void changeScene(s32 scene, s32 duration);
void fn_8002059C(void);
void fn_80020624(void);
void fn_800206FC(void);
void fn_80021064(void);
s32 fn_80021188(void);
s32 fn_800211BC(void);

u8 fn_800211F0(void);

void fn_80021204(void);

void fn_80021228(u8 mode);
void fn_8002128C(u8 mode);

#endif
