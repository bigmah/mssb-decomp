#ifndef __MAIN_FILE_80011640_H__
#define __MAIN_FILE_80011640_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "C3/control.h"
#include "main/file_80024D2C.h"
#include "Dolphin/GX/GXTypes.h"

// model.c: character models, their parts data and animation state.

typedef struct CharBoneTrack {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ void* _0C;
} CharBoneTrack;

typedef struct CharJoint {
    /*0x000*/ u16 id;
    /*0x002*/ u8 _02[0x12];
    /*0x014*/ void* display;
    /*0x018*/ u8 _18[0xE8 - 0x18];
    /*0x0E8*/ CharBoneTrack* track;
    /*0x0EC*/ MtxPtr worldMtx;
    /*0x0F0*/ u8 _F0[0x100 - 0xF0];
    /*0x100*/ struct CharJoint* next;
    /*0x104*/ u8 _104[0x136 - 0x104];
    /*0x136*/ u8 _136;
} CharJoint;

typedef struct CharModel {
    /*0x00*/ u8 _00[0x6];
    /*0x06*/ u16 jointCount;
    /*0x08*/ u8 _08[0xC];
    /*0x14*/ void* display;
    /*0x18*/ CharJoint** joints;
    /*0x1C*/ u8 _1C[0x64 - 0x1C];
    /*0x64*/ void* _64;
    /*0x68*/ void* _68;
    /*0x6C*/ u8 _6C[0x74 - 0x6C];
    /*0x74*/ CharJoint* firstJoint;
    /*0x78*/ u8 _78[0x4];
    /*0x7C*/ void* _7C;
    /*0x80*/ u16 _80;
    /*0x82*/ u8 _82[0x8C - 0x82];
    /*0x8C*/ f32 _8C;
    /*0x90*/ u8 _90[0x98 - 0x90];
    /*0x98*/ u8 flags;
    /*0x99*/ u8 _99;
} CharModel;

// One loaded model and its root control.
typedef struct CharSlot {
    /*0x00*/ CharModel* model;
    /*0x04*/ void* act;
    /*0x08*/ void (*callback)(struct CharSlot* slot);
    /*0x0C*/ u8 _0C[0x2];
    /*0x0E*/ u16 animId;
    /*0x10*/ Control ctrl;
    /*0x4C*/ u8 _4C[0x54 - 0x10 - sizeof(Control)];
    /*0x54*/ f32 _54;
    /*0x58*/ u8 _58;
    /*0x59*/ u8 _59;
    /*0x5A*/ u8 _5A;
    /*0x5B*/ u8 _5B;
    /*0x5C*/ f32 _5C;
    /*0x60*/ f32 _60;
    /*0x64*/ u16 _64;
    /*0x66*/ u16 _66;
    /*0x68*/ u16* mirror;
    /*0x6C*/ u8 _6C;
    /*0x6D*/ u8 lightCount;
    /*0x6E*/ u8 _6E[0x2];
    /*0x70*/ void* lights[8];
} CharSlot; // size: 0x90

typedef struct CharSlotList {
    /*0x00*/ u16 count;
    /*0x02*/ u8 _02[0x32];
    /*0x34*/ CharSlot slots[1];
} CharSlotList;

// Character parts data: a file table plus a shape animation player.
typedef struct CharPart {
    /*0x00*/ void** files;
    /*0x04*/ ShapeAnimPlayer player; // player.curIdx at 0x5C
    /*0x60*/ u8 slot;
    /*0x61*/ s8 _61;
    /*0x62*/ u8 _62[0x2];
} CharPart; // size: 0x64

typedef struct CharParts {
    /*0x00*/ CharPart part[2];
    /*0xC8*/ void* tex;
    /*0xCC*/ u8 _CC;
    /*0xCD*/ u8 _CD;
    /*0xCE*/ u8 _CE;
    /*0xCF*/ s8 _CF;
    /*0xD0*/ s8 _D0;
    /*0xD1*/ s8 _D1;
    /*0xD2*/ u8 _D2[0x2];
} CharParts; // size: 0xD4

// Animation bank (ANIMGet'd file).
typedef struct CharAnimBank {
    /*0x00*/ u8 _00[0xA];
    /*0x0A*/ u16 count;
} CharAnimBank;

// Animation banks of an actor (streamed from ARAM, then ANIMGet).
typedef struct CharAnimBanks {
    /*0x00*/ void* b[7];
} CharAnimBanks;

typedef struct CharTrail {
    /*0x00*/ u32 _00;
    /*0x04*/ f32 _04[6];
    /*0x1C*/ u8 _1C[0xA];
    /*0x26*/ u8 _26;
    /*0x27*/ u8 _27;
} CharTrail; // size: 0x28

typedef struct CharActor {
    /*0x000*/ CharModel* model;
    /*0x004*/ u8 _004[0x4];
    /*0x008*/ void** files; // file offsets, relocated in place
    /*0x00C*/ void** _0C;
    /*0x010*/ CharAnimBanks banks;
    /*0x02C*/ CharPart* part;
    /*0x030*/ CharParts* parts;
    /*0x034*/ Vec pos;
    /*0x040*/ Vec _040;
    /*0x04C*/ f32 _04C;
    /*0x050*/ u8 _050[0xC];
    /*0x05C*/ s32 _05C;
    // Animation requests: [0] current, [1] next (AnimateCharacter),
    // [2] queued (QueueCharacterAnimation).
    /*0x060*/ s16 _060;
    /*0x062*/ s16 anim[3];
    /*0x068*/ s16 _068;
    /*0x06A*/ s16 _06A[3];
    /*0x070*/ s16 _070;
    /*0x072*/ u16 mirror[0x78]; // left/right joint remap
    /*0x162*/ u16 jointIdx[0x78];
    /*0x252*/ s8 kind;
    /*0x253*/ u8 _253;
    /*0x254*/ s8 index;
    /*0x255*/ s8 modelIndex;
    /*0x256*/ u8 team;
    /*0x257*/ u8 roster;
    /*0x258*/ s8 _258;
    /*0x259*/ u8 _259;
    /*0x25A*/ u8 _25A;
    /*0x25B*/ u8 _25B;
    /*0x25C*/ u8 _25C;
    /*0x25D*/ u8 mode[2];
    /*0x25F*/ u8 _25F[3];
    /*0x262*/ u8 _262[3];
    /*0x265*/ u8 _265[3];
    /*0x268*/ u8 _268;
    /*0x269*/ u8 _269[3];
    /*0x26C*/ u8 _26C[3];
    /*0x26F*/ u8 _26F;
    /*0x270*/ u8 _270[0x3];
    /*0x273*/ u8 _273;
    /*0x274*/ u8 _274;
    /*0x275*/ u8 _275;
    /*0x276*/ u8 _276;
    /*0x277*/ u8 _277;
    /*0x278*/ u8 _278;
    /*0x279*/ u8 _279[0x3];
} CharActor; // size: 0x27C

// A file streamed from ARAM into a fixed buffer.
typedef struct CharPreload {
    /*0x0*/ void* buffer;
    /*0x4*/ u32 size;
    /*0x8*/ s16 id;
    /*0xA*/ u8 state;
} CharPreload; // size: 0xC

// Stadium light: packed source data and the expanded position/colour.
typedef struct LightSrc {
    /*0x0*/ u8 _0[0xA];
} LightSrc;

typedef struct StadiumLights {
    /*0x00*/ LightSrc light[4];
    /*0x28*/ GXColor ambient;
} StadiumLights; // size: 0x2C

typedef struct LightPos {
    /*0x0*/ f32 x;
    /*0x4*/ f32 y;
    /*0x8*/ f32 z;
    /*0xC*/ u32 color;
} LightPos;

// Stadium object files (ARAMTransfer'd into lbl_8036E548.stadiumFiles).
typedef struct StadiumFiles {
    /*0x000*/ struct {
        void* layout;
        void* geo;
        void* tex;
    } obj[24];
    /*0x120*/ void* bank;
    /*0x124*/ u8 _124[0xC];
    /*0x130*/ struct {
        void* shape;
        ShapeAnimSet* set;
    } anim[2];
} StadiumFiles;

// lbl_8036E548
typedef struct CharMgr {
    /*0x0000*/ u8 _0000[0x4];
    /*0x0004*/ u32 _0004[2];
    /*0x000C*/ u32 _000C[21];
    /*0x0060*/ CharSlotList* slots;
    /*0x0064*/ CharSlotList* slots64;
    /*0x0068*/ CharSlotList* slots68;
    /*0x006C*/ CharSlotList* slots6C;
    /*0x0070*/ u32 _0070;
    /*0x0074*/ u8 _0074[0xAC - 0x74];
    /*0x00AC*/ void* lights[4];
    /*0x00BC*/ u8 _00BC[0x13C - 0xBC];
    /*0x013C*/ CharSlotList* partSlots;
    /*0x0140*/ CharParts partsPool[13];
    /*0x0C04*/ CharActor actors[13];
    /*0x2C50*/ CharActor* active[13];
    /*0x2C84*/ StadiumFiles* stadiumFiles;
    /*0x2C88*/ void* _2C88;
    /*0x2C8C*/ u8* fileBuf;
    /*0x2C90*/ u32 bankSize[5];
    /*0x2CA4*/ u32 _2CA4;
    /*0x2CA8*/ u8 _2CA8[0x4];
    /*0x2CAC*/ void* animBufs[16]; // [1..4]: shared bank buffers, [14]/[15]: extra banks
    /*0x2CEC*/ void* bankSets[4][5];
    /*0x2D3C*/ CharPreload preload[3];
    /*0x2D60*/ u32 _2D60;
    /*0x2D64*/ u32 _2D64;
    /*0x2D68*/ s16 _2D68;
    /*0x2D6A*/ s8 _2D6A[13];
    /*0x2D77*/ u8 state;
    /*0x2D78*/ u8 _2D78;
    /*0x2D79*/ u8 _2D79;
    /*0x2D7A*/ u8 _2D7A[0x2];
    /*0x2D7C*/ u8 _2D7C;
    /*0x2D7D*/ u8 _2D7D[0x2];
    /*0x2D7F*/ s8 _2D7F[9];
    /*0x2D88*/ s8 loadActor;
    /*0x2D89*/ s8 bankOwner[4];
    /*0x2D8D*/ u8 loadStep;
    /*0x2D8E*/ u8 _2D8E;
    /*0x2D8F*/ u8 _2D8F;
    /*0x2D90*/ CharTrail* trail; // [25]
    /*0x2D94*/ CharTrail* trail2; // [30]
    /*0x2D98*/ u32 _2D98;
    /*0x2D9C*/ u32* trailFile;
    /*0x2DA0*/ void* trailLayout;
    /*0x2DA4*/ void* trailGeo;
    /*0x2DA8*/ void* trailTex;
    /*0x2DAC*/ u8 _2DAC[0x3078 - 0x2DAC];
    /*0x3078*/ s16 _3078;
    /*0x307A*/ u8 _307A;
    /*0x307B*/ u8 _307B;
    /*0x307C*/ u8 _307C;
    /*0x307D*/ u8 _307D;
    /*0x307E*/ u8 _307E[0x3082 - 0x307E];
    /*0x3082*/ u8 _3082;
    /*0x3083*/ u8 _3083[0x2];
    /*0x3085*/ u8 _3085;
    /*0x3086*/ u8 _3086;
    /*0x3087*/ u8 _3087;
    /*0x3088*/ u8 _3088[0x308C - 0x3088];
    /*0x308C*/ void (*callback)(void);
    /*0x3090*/ u8 _3090[0x309C - 0x3090];
    /*0x309C*/ ShapeAnimPlayer stadiumAnim[2];
} CharMgr; // size: 0x3154

extern CharMgr lbl_8036E548;
extern CharActor lbl_8036C4FC[13]; // backup of lbl_8036E548.actors

struct CharQueueTask;

// Task object (lbl_803CC1B8) running fn_800177B4.
typedef struct CharLoadTask {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ struct CharQueueTask* parent;
    /*0x10*/ u8 _10[0x4];
    /*0x14*/ u8 state;
    /*0x15*/ u8 index;
    /*0x16*/ u8 kind;
    /*0x17*/ u8 _17[0x2];
    /*0x19*/ u8 team;
    /*0x1A*/ u8 roster;
    /*0x1B*/ s8 _1B;
    /*0x1C*/ u8 actor;
    /*0x1D*/ u8 _1D;
} CharLoadTask;

// Drawing-queue task returned by fn_800B0A5C_insertQueue.
typedef struct CharQueueTask {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ struct CharQueueTask* parent;
    /*0x10*/ s16 _10;
    /*0x12*/ u8 _12[0x2];
    /*0x14*/ u8 _14;
} CharQueueTask;

void fn_80011640(Mtx a, Mtx out);
void fn_800116DC(CharActor* actor, Mtx m, u16 joint);
void fn_800117CC(Mtx src, Mtx m, Mtx dst);
MtxPtr fn_800118AC(Mtx m, Mtx out);
void fn_8001196C(void);
void fn_80011A60(void);
void fn_80011B64(s32 index);
void fn_80011BE4(s32 index);

void fn_8001AAF0(void);
void fn_800189B8(void);
void fn_8001FDD4(CharSlot* slot);
void fn_8001B2D0(void);
void fn_8001D110(s32 index, f32 x, f32 y, f32 z);
void fn_8001D148(s32 index, f32 x, f32 y, f32 z);
void fn_80018B38(void);
void fn_8001D0D0(s32 index, f32 scale);
void fn_8001AAA4(void);
void fn_8001B308(s32 index, s32 enable);
void fn_8001D074(s32 index, s32 enable);
void fn_800177B4(void);
void fn_8001C528(void);
void QueueCharacterAnimation(s32 index, s32 anim, s32 a, s32 b, s32 c, s32 d, s32 e);
void AnimateCharacter(s32 index, s32 anim, s32 a, u8 mode, s32 b, s32 c, s32 d, s32 e);
s32 fn_8001758C(u8* state, s32 actor, u8 kind, u8 team, u8 roster, s8 arg5, u8 index, u8 arg7);
void challengeMapRelated(void);

void fn_80014990(s32 index, void* model, ShapeAnimSet* set);
void fn_80017D28(CharActor* src);
void fn_8001B224(void);
void fn_8001F16C(void);
s32 fn_80014F40(s32 id);
s32 fn_80014E50(s32 id);
s32 fn_80014D4C(s32 id);
void fn_80017814(CharActor* actor, s32 modelIndex, s32 index, void (*callback)(CharSlot*));
void fn_8001BE50(s32 index, s32 anim, u8 a, u8 b, s16 c, u8 d, u8 e);

void fn_8001CA40(u8 stadium);
void fn_8001CB10(LightSrc* src, s32 count);
void fn_8001CBD4(void);
s32 fn_8001C588(s32 id);
s32 fn_8001C920(s32 id);
s32 fn_8001B728(s32 index, s32 joint, Vec* out);
void fn_800188C0(void);
BOOL getAnimRelatedCoordinates(s32 index, s32 joint, Vec* out);
void fn_8001B4D8(s32 index, s32 enable);
s32 fn_80016F7C(void);
s32 fn_80016B60(CharActor* actor);
void challengeMapMaybe(void);

void fn_8001FC4C(CharActor* actor);

s32 fn_80011CA8(CharActor* actor, s32 a, s32 b);
void fn_800126EC(CharPart* part, void* tex, u8* fileIdx);
u8 LoadModel(CharActor* actor);

void fn_8001B5EC(s32 index, s32 enable);
void fn_8001D180(s32 index, s32 which, s32 enable);
void fn_800189E4(void);
void fn_8001DD58(CharModel* model, s32 pass, MtxPtr view, s32 n, ...);

s32 fn_8001B35C(s32 index, s32 kind);
void fn_80019A60(void);
void fn_800196D8(void);

void fn_8001A25C(void);
void fn_80019C00(void);
void fn_8001CCC8(void);
void fn_8001DB74(CharSlotList* list);

void fn_8001CE74(void);
void fn_8001DEA4(CharSlot* slot, s32 pass, MtxPtr view);

s32 fn_80017340(s32 actorIdx);
void fn_80018024(void);

void fn_80018B74(void);

void fn_8001AF98(void);
void fn_8001AB10(CharSlot* slot, s32 a, s32 b);

void fn_80017DBC(CharActor* actor, s32 modelIndex);

void fn_8001F228(void);

int fn_8001C67C_animation(int id, int index);

s32 fn_80017098(s32 team, s32 roster, s32 arg2, s32 index, s32 arg4, s32 kind);

void fn_8001A3FC(s32 arg);
void fn_800145F8(s32 arg);
void fn_80018DEC(s32 arg);
void fn_80018270(s32 mode);

void fn_8001C234(u32* doneMask);
void fn_8001F5E8(void);
void fn_8001BA44(s32 index, s32 anim, u8 a, u8 b, s16 c, u8 d, u8 e);

void fn_8001E0D8(CharSlotList* list, s32 pass, Mtx view);
void fn_8001E488(void);

void fn_8001F8A4(void);

s32 fn_80014A18(void);

void fn_80014204(s32 count);

s32 fn_8001594C(s32 team);

s32 fn_80015468(s32 team);
u8 fn_80013680(CharActor* actor);

void fn_8001B200(void);

void fn_8001B214(void (*callback)(void));

void fn_8001E460(void* value);

void fn_8001E474(void);

#endif
