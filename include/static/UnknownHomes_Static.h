#ifndef __UNKNOWN_HOMES_STATIC_H_
#define __UNKNOWN_HOMES_STATIC_H_

#include "mssbtypes.h"
#include "Dolphin/mtx.h"

#include "static/GameSettings.h"
#include "Dolphin/GX/GXTypes.h"
#include "Dolphin/GX/GXEnum.h"

// Types of main.dol functions declared below (defined in include/main/*.h).
struct ActorLayout;
struct ActorObjectTable;
struct AssetLoadInstructions;
struct DODisplayData;
struct Emitter;
struct GameActor;
struct Light;
struct ParticleParams5;
struct ParticleParamsC;
struct RigidBody;
struct SoundGroupData;
struct SpaniGroup;
struct SpaniOwner;
struct TexArchive;
struct TexImage;

#include "static/Camera.h"
#include "main/file_800B993C.h" // fn_800B9948 (DOTevHook)

extern BOOL getAnimRelatedCoordinates(s32 index, s32 joint, Vec* out); // main/file_80011640.h

extern void fn_800528AC(fn_800528AC_parameter);
extern camera_803c639c_s* fn_80052768_getCamera(int);
extern int fn_8001C67C_animation(int, int);
extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);
extern void* fn_800339F0(void* after, u8 type); // TODO type: Emitter* (Emitter*, u8)
extern void* fn_80034CEC(void*); // TODO type: void (SpaniGroup*); REL callers pass its "result" on to fn_800B0A14_removeQueue
// TODO types: kept as before until a claimed unit (see comment) is updated; the real
// prototype is in the defining main/ header.
extern s32 ARAMTransfer(void*, int, int, int); // menus/rep_0568, rep_0F60: void* (AssetLoadInstructions*, void*, u8, u32)
extern void sndFXRelated(u16);
extern void fn_800B0A14_removeQueue(void*);
extern void* fn_800B0A5C_insertQueue(void* draw, s32 priority); // TODO type: u16 priority in main/file_800B0724.h; REL callers match with s32
extern void fn_800BD670(void*, u32); // TODO type: menus/rep_08E8 passes the camera as u32; (ActorObjectTable*, MtxPtr)
extern void LITXForm(void* light, void* matrix); // TODO type: menus/rep_08E8; (Light*, MtxPtr)
extern void fn_80048D4C(void);
extern void fn_80062A94(void);
extern s32 fn_80048EA8(s32 index);
extern s32 fn_80048E00(s32 index, s32 value);
extern void fn_80048C14(u32 value);
extern void SetFog(GXFogType type, GXColor* color, f64 startz, f64 endz, f64 nearz, f64 farz);
extern void SetFogNoneAgain(void);
extern void fn_800B49E4(struct ActorLayout* layout);
extern void fn_800BCE38(struct DODisplayData* pal);
extern void convertTextureHeader(void* textures); // TODO type: menus/rep_0F60; (TexArchive*)
extern void haveActLayoutPointToGeoHeader(void* actor, void* geometry); // TODO type: menus/rep_0F60; (ActorLayout*, DODisplayData*)
struct GQRValueGroups;
extern void fn_800BD190(struct GQRValueGroups* groups, s32 value);
extern void fn_800B806C(s32 index, f32 bottom, f32 top, f32 left, f32 right,
                      f32 near, f32 far, f32 focalLength);
extern void pitchingMachinePitching(u8);

// TODO type: lbl_803C77B8 is PadState[4] (static/Pad.h); this one-pad view stays until
// challenge/rep_7730 stops using it.
typedef struct {
    /* 0x00 */ u16 _00;
    /* 0x02 */ u16 _02;
    /* 0x04 */ u16 _04; // repeat (PadState in static/Pad.h)
    artificial_padding(4, 0x22, u16);
    /* 0x22 */ u16 _22;
    artificial_padding(0x22, 0x42, u16);
    /* 0x42 */ u16 _42;
    artificial_padding(0x42, 0x62, u16);
    /* 0x62 */ u16 _62;
} lbl_803C77B8_s;
extern lbl_803C77B8_s lbl_803C77B8;

// TODO type: really s32 (u16, SoundGroupData*) (main/file_80021308.h); game/auto_00_00090754_text
// (claimed) passes pointers held in u32 tables.
extern void fn_80021518(s32 id, s32 value);
extern s32 fn_800214D0(void);
extern u8 fn_800211F0(void);
extern u32 fn_80062890(s32 index);

extern void fn_80048C28(void);
extern void fn_80048C1C(void);

extern void fn_800B9AA8(struct Light* light);

extern void SetDisplayStateTexture(struct TexImage* tex, s32 map, u32 tlutName);

extern void fn_800AD038(void* object);
extern void fn_800A97D0(u8 shift, s32 threshold);
extern void fn_80048BEC(void*, u32, u32);
extern s32 fn_80048820(void*, u16, u16, u16, u8);
extern void fn_800B2D5C(struct GameActor* actor);
extern void fn_800B2C88(struct GameActor* actor, u16 bone, Mtx m);
extern void fn_800385F0(struct RigidBody* rb, f32 len, f32 frac, f32 radius, f32 mass);
extern void fn_800B24D4(s32 layer);
extern void fn_800B1188(void);
extern void fn_80037768(struct RigidBody* rb, s32 axis, s32 steps, f32 len, f32 frac, f32 radius, f32 mass);

extern void fn_800ACFB0(void* object);

#include "Dolphin/GX/GXTypes.h"
extern void fn_800BD2CC(s32 channel, GXColor color);

extern void fn_800B9A9C(u32 flag, f32 value);

extern f32 fn_800B4A94(struct GameActor* actor);

extern void fn_80035B50(int id);

extern s32 fn_80035838(void* aramAddr, u8 id);

extern void fn_800AD054(void* first, void* second);

extern void changeScene(s32 scene, s32 state);
extern void minigamesSetSomePointers(void);


extern void fn_800363D8(void*, s32, s32, s32, s32); // TODO type: menus/rep_0788; (SpaniOwner*, s32, u32, u16, u32)

extern void fn_8002955C(Vec* pos, Vec* axis, struct ParticleParamsC* prm);
extern void fn_80031CA4(Vec*, u32*); // TODO type: menus/rep_08E8; (Vec*, ParticleParams5*)

extern void* fn_80037AA0(void*, s32, void*, u16, void*); // TODO type: void (RigidBody*, s32, void (*)(void), u16, void*); challenge/rep_0610 passes its "result" to fn_800B0A14_removeQueue

#include "Unknown/File_0x800a6304.h" // ARAM stack allocator

// DVD stream (main/file_800A6870.c)
extern void fn_800A6C80(void);
extern void fn_800A6D10(s32 consumed);
extern void fn_800A6E24(struct AssetLoadInstructions* instr, u8* ringBuf, s32 ringSize);
// HVQM4 decoder
extern void fn_800DFDD4(u8* src, u8* dst, u32 numChannels, u32 format, u32 count, void* chans);
extern void fn_800E4AC8(void);
extern void fn_800E4AE8(void* ctx, void* info);
extern u32 fn_800E4B1C(void* ctx);
extern void fn_800E4FF4(void* ctx, u8* src, u8* dst);
extern void fn_800E591C(void* ctx, u8* src, u8* dst, u8* ref);
extern void fn_800E5940(void* ctx, u8* src, u8* dst, u8* ref0, u8* ref1);

#endif // !__UNKNOWN_HOMES_STATIC_H_
