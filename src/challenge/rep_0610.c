#include "math.h" // static dolsqrtf2 (the extern one from UnknownHomes_Game.h would emit its constants)
#undef SQRT2_LINKAGE
#include "challenge/rep_0610.h"
#define REP_HEADER_FN repHeader_0610
#include "header_rep_inline.h"

// .bss of this file, laid out in reverse definition order. The functions reach
// most of it through one pooled base (lbl_1_bss_3070).
static ChPlayerBss lbl_1_bss_6940;  // player record and its parts slot
static ChScene lbl_1_bss_68FC;      // view matrix and per-player character
static ChViewer lbl_1_bss_67E0;     // also covers 0x68F8
static void* lbl_1_bss_67B8[0xA];
static u8 lbl_1_bss_62B8[0x500];     // unused
static ShapeAnimPlayer lbl_1_bss_60EC[5]; // shape (facial) animation players
static void* lbl_1_bss_60E8;
static u8* lbl_1_bss_60E4;
static ActorObjectTable* lbl_1_bss_60E0;
static u8* lbl_1_bss_60DC;
static u8 lbl_1_bss_60DB;            // unused
static u8 lbl_1_bss_60DA;            // unused
static u8 lbl_1_bss_60A4[0x36];
static void* lbl_1_bss_60A0;
static void* lbl_1_bss_5F7C[0x49];
static u8 lbl_1_bss_5F7B;            // unused
static u8 lbl_1_bss_5F7A;            // unused
static u8 lbl_1_bss_5F79;            // unused
static u8 lbl_1_bss_5F78;
static f32 lbl_1_bss_5F74;
// Read through a byte pointer in the volume editors: with a plain f32 access mwcc
// keeps it in other registers than the original (alias analysis).
#define SND_LEVEL (*(f32*)(u8*)&lbl_1_bss_5F74)
static u8 lbl_1_bss_5F73;
static u8 lbl_1_bss_5F72;
static u8 lbl_1_bss_5F71;
static s8 lbl_1_bss_5F70;
static u32 lbl_1_bss_5F6C;
static u8 lbl_1_bss_5F6B;            // unused
static u8 lbl_1_bss_5F6A;            // unused
static u8 lbl_1_bss_5F69;
static u8 lbl_1_bss_5F68;
static f32 lbl_1_bss_5F64;
static u8 lbl_1_bss_5F63;            // unused
static s8 lbl_1_bss_5F62;
static u16 lbl_1_bss_5F60;
static s32 lbl_1_bss_5F5C;
static s32 lbl_1_bss_5F58;
static ShapeKey lbl_1_bss_3758[8][5][0x40]; // keys of the saved shape animations
static ShapeAnimState lbl_1_bss_3258[8][5]; // shape animations saved per script step
static ChallengeStep lbl_1_bss_3218[8]; // animation script being played/edited
static u8 lbl_1_bss_3217;            // unused
static u8 lbl_1_bss_3216;
static u8 lbl_1_bss_3215;
static u8 lbl_1_bss_3214;
static RigidBody lbl_1_bss_30C0;
static s32 lbl_1_bss_30BC;
static u8 lbl_1_bss_30BB;            // unused
static u8 lbl_1_bss_30BA;            // unused
static u8 lbl_1_bss_30B9;            // unused
static u8 lbl_1_bss_30B8;
static u8 lbl_1_bss_30B7;
static u8 lbl_1_bss_30B6;
static s16 lbl_1_bss_30B4;
static s32 lbl_1_bss_30B0;
static u32 lbl_1_bss_30AC;           // unused
static s32 lbl_1_bss_30A8;           // lbl_1_data_F278 entry edited by fn_1_F0D0
static u16 lbl_1_bss_30A6;           // unused
static u16 lbl_1_bss_30A4;
static s32 lbl_1_bss_30A0;
static s32 lbl_1_bss_309C;
static struct TexArchive* lbl_1_bss_3098; // texture archive inside the file at lbl_1_bss_3094
static void* lbl_1_bss_3094;         // loaded texture file
static u8 lbl_1_bss_3093;            // unused
static u8 lbl_1_bss_3092;            // unused
static u8 lbl_1_bss_3091;            // unused
static u8 lbl_1_bss_3090;
static s32 lbl_1_bss_308C;
static s32 lbl_1_bss_3088;
static s32 lbl_1_bss_3084;
static u8 lbl_1_bss_3083;            // unused
static u8 lbl_1_bss_3082;            // unused
static u8 lbl_1_bss_3081;
static u8 lbl_1_bss_3080;
static s32 lbl_1_bss_307C;
static u8 lbl_1_bss_307B;            // unused
static u8 lbl_1_bss_307A;            // unused
static u8 lbl_1_bss_3079;            // unused
static u8 lbl_1_bss_3078;
typedef struct ChLoadOptions {
    /* 0x0 */ u8 parts;    // also load the character's CharPart files
    /* 0x1 */ u8 _1[3];
    /* 0x4 */ s32 fileBase; // 0 or 0x402: which half of lbl_1_data_2398 to load from
} ChLoadOptions;
static ChLoadOptions lbl_1_bss_3070;

extern u8 lbl_803CBBC0[];
extern void fn_800A7D4C(s32 list, void* node);

struct ChParticleParamsB;
extern struct ChParticleParamsB lbl_80108B90;
extern void fn_800324EC(u16, s32, s32, struct ChParticleParamsB*);


extern void fn_1_12820(void*, void*);

#include "Dolphin/vec.h"
extern void fn_80026134(s32, Vec*);
extern void fn_80026130(s32 unused0, void* unused1, f32 unused2);

#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"
extern const f32 lbl_1_rodata_73CC[];
extern const f32 lbl_1_rodata_73D0[];
extern const f32 lbl_1_rodata_73D4[];
extern const f32 lbl_1_rodata_73D8[];
extern const f32 lbl_1_rodata_73DC[];
extern const f32 lbl_1_rodata_73E0[];

#include "main/file_80011640.h" // CharMgr lbl_8036E548
#include "C3/anim.h"
// lbl_8036E548 shifted by `i` actors, so that ->actors[0] is actors[i]: the original indexes
// "mgr + i * sizeof(CharActor)" and adds the field offset afterwards.
#define CHARMGR_AT(i) ((CharMgr*)((CharActor*)&lbl_8036E548 + (i)))
#include "C3/light.h"
typedef struct { void* data; u32 pad4; u32 pad8; } ChallengeEntry;

extern void LITXForm(void* light, void* matrix);





extern void* lbl_80366158[];
#include "challenge/rep_0010.h" // ChTaskHeader, lbl_803CC1B8
#define CH_TASK ((ChTaskHeader*)lbl_803CC1B8)

extern void fn_1_1496C(u8* object);
#include "static/UnknownHomes_Static.h"
#include "challenge/ch_data.h" // ChParticleParams*
extern void fn_1_10560(TASK_PARAM(void* object));

typedef struct {
    f32 position;
    u8 padding04[8];
    void* track;
} ChallengeAnimation;

typedef struct {
    u8 padding[0xE8];
    ChallengeAnimation* animation;
} ChallengeAnimationNode;

typedef struct {
    u8 padding00[6];
    u16 count;
    u8 padding08[0x10];
    ChallengeAnimationNode** nodes;
} ChallengeAnimationModel;

typedef struct {
    u8 padding00[0x34];
    ChallengeAnimationModel* model;
    u8 padding38[0x58];
} ChallengeRenderObject;

typedef struct { s32 words[3]; } ChallengeCommand;
extern const ChallengeCommand lbl_1_rodata_7344;

extern ChallengeCommand lbl_1_rodata_731C;
extern void fn_1_F798(void*, void*, s32);

extern const f32 lbl_1_rodata_7430;
extern const f32 lbl_1_rodata_73F8;
extern f32 lbl_1_rodata_73BC;
extern const f32 lbl_1_rodata_7394;

extern const f32 lbl_1_rodata_73C8;

extern void fn_1_F1D8(TASK_PARAM(void*));

extern f32 lbl_1_rodata_73C0[];
extern f32 lbl_1_rodata_73C4[];
extern f32 lbl_1_rodata_73A4[];

#include "Dolphin/OS/OSUtil.h"
extern void fn_1_135C0(void);
extern void fn_1_1770C(u8* object);

#include "main/aramloader.h" // ARAMLoader lbl_803C6CF8

typedef struct { u8 b[0x38]; } Ch38;
extern void fn_1_179CC(void);
extern void fn_1_129D0(void);


#include "C3/control.h"
struct ChParticleParams5;
extern void fn_80030D88(Vec*, Vec*, struct ChParticleParams5*, u8);

extern void fn_8004B208(void* row, s32 id, u32 variant, f32 frame);

extern void fn_1_D9B8(void);
extern void fn_1_DF14(void);


extern void fn_1_10E2C(Mtx, Mtx, u32, u32, u32);

extern void fn_1_17B5C(void);

extern void fn_1_ECF8(u8, u8, u8);

#ifdef TARGET_PC
typedef struct { u8 rest : 3; u8 mode : 2; u8 pad : 3; } ChallengeFlagBits; // MWCC bit order
#else
typedef struct { u8 pad : 3; u8 mode : 2; u8 rest : 3; } ChallengeFlagBits;
#endif

extern const f32 lbl_1_rodata_7480;
extern const f32 lbl_1_rodata_7484;
extern const f32 lbl_1_rodata_7488;
extern const f32 lbl_1_rodata_748C;
extern const f32 lbl_1_rodata_7490;
extern const f32 lbl_1_rodata_7494;
extern const f32 lbl_1_rodata_7498;
extern const f32 lbl_1_rodata_749C;

typedef struct { u16 a; u16 b; } ChPair;

#include <string.h>
extern void fn_1_107B8(void);

extern const f32 lbl_1_rodata_73FC;
extern void fn_1_F50C(void);

struct ChParticleParams;
extern void fn_8002F258(Vec*, s32, struct ChParticleParams*);
extern s32 fn_8002F1AC(Vec*, s32);

#include "Dolphin/gx.h"


extern Vec lbl_1_rodata_730C;
extern const f32 lbl_1_rodata_7448;
extern const f32 lbl_1_rodata_744C;
extern const f32 lbl_1_rodata_7450;
extern void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);

typedef struct { u8 r, g, b, a; } ChallengeLightColor;
extern void LITAlloc(void**);
extern void LITInitAttn(void*, f32, f32, f32, f32, f32, f32);
extern void LITInitPos(void*, f32, f32, f32);
extern void LITInitDir(void*, f32, f32, f32);
// LITInitColor takes a GXColor*. These callers pass the color by value (the PPC ABI hands
// over a pointer to a fresh copy), so only the matching build declares it that way.
#if NONMATCHING
extern void LITInitColor(void* light, ChallengeLightColor* color);
#define LIT_COLOR(c) (&(c))
#else
extern void LITInitColor(void* light, ChallengeLightColor color);
#define LIT_COLOR(c) (c)
#endif
extern ChallengeLightColor lbl_1_rodata_72F0;
extern const f32 lbl_1_rodata_7474;
extern const f32 lbl_1_rodata_7478;
extern const f32 lbl_1_rodata_747C;

extern Vec lbl_1_rodata_7300;
extern const f32 lbl_1_rodata_7454;

extern s32 fn_1_C2DC(void*, void*, s32, s32, s32, s32*, s32*, s32*);
struct GameActor;
extern struct DODisplayObj* fn_800B2BA8(struct GameActor* actor, u16 bone, struct GameActor* src, u16 srcBone); // main/file_800B0724.h

typedef struct {
    u8 pad0[0x34];
    u8* actor;
    u8 pad38[0x58];
} ChallengeModelEntry;


extern void fn_80052968(void);



#include "main/file_800BD8C4.h"
extern GXColor lbl_1_rodata_72FC;

struct GameActor;
extern void fn_800B2B74(struct GameActor* actor, u16 bone);
extern void fn_1_CDC8(void);

extern void fn_80052D70(void);

#include "main/screenfx.h"
extern ScreenFx lbl_803C5090;
extern void fn_8003A2C0(void);

#include "Dolphin/OS/OSError.h"
struct GameActor;
extern void Set_FUN_800b2b6c(struct GameActor* actor, u16* boneRemap); // main/file_800B0724.h
struct GameActor;
extern u8 fn_800B3C04(s32 viewIndex, struct GameActor* actor, Mtx camera); // main/file_800B2C44.h
#include "main/file_800B4A44.h"

extern void fn_80039A4C(void);


struct ShapeAnimState;
extern u32 fn_80024D2C(struct ShapeAnimState* st);

// Debug particle emitter settings edited by fn_1_10044 (lbl_1_data_ADE0 + 0x10).
typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 count;
    /* 0x08 */ f32 speed;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ Vec pos;
    /* 0x20 */ s16 pitch;
    /* 0x22 */ s16 yaw;
    /* 0x24 */ Vec dir;
} ChallengeEmitterParams;

extern void fn_800330CC(s32 count, u32 type, Vec* pos, Vec* dir, s32 arg4, void* tex, f32 speed, f32 arg7);

extern f32 lbl_1_rodata_7428;
extern f32 lbl_1_rodata_742C;
extern f32 lbl_1_rodata_7434;
extern f32 lbl_1_rodata_743C;
extern f32 lbl_1_rodata_7438;

// lbl_1_data_F570 viewed as the challenge screen-overlay settings.
typedef struct {
    /* 0x00 */ f32 scale;
    /* 0x04 */ u32 color;
    /* 0x08 */ f32 far;
    /* 0x0C */ f32 depth;
    /* 0x10 */ u32 colorTop;
    /* 0x14 */ u32 colorBottom;
} ChallengeOverlay;

typedef struct { Mtx m; } ChallengeMtx;
extern const ChallengeMtx lbl_1_rodata_7364;

static inline void fn_1_C5AC_quad(f32 z, u32 color) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, z);
    GXColor1u32(color);
    GXPosition3f32(640.0f, 0.0f, z);
    GXColor1u32(color);
    GXPosition3f32(640.0f, 448.0f, z);
    GXColor1u32(color);
    GXPosition3f32(0.0f, 448.0f, z);
    GXColor1u32(color);
}


// Effect parameters edited by fn_1_FB98 (lbl_1_data_D838 + 0x184C = 0xF084).
typedef struct {
    /* 0x00 */ s32 count;
    /* 0x04 */ s32 alpha;
    /* 0x08 */ f32 values[4];
    /* 0x18 */ u8 pad18[4];
    /* 0x1C */ f32 scale;
} ChallengeFxParams;


// main/file_80024D2C.h and main/file_80037054.h clash with this file's externs, so declare what is needed.
struct ShapeModel;
struct ShapeData;
struct CharModelObj;
struct Model;
extern s32 fn_80024DB0(struct ShapeAnimState* st);
extern void fn_80024FA4(struct ShapeModel** model, struct ShapeData* shape, struct ShapeAnimState* st, s32 forceTarget);
extern void fn_80038EC4(struct CharModelObj* obj, struct Model** model, s32 joint);
extern void fn_8003414C(void* camera);
extern const f32 lbl_1_rodata_7460;

struct ChallengeAnimation;
extern void fn_1_26B7C(struct ChallengeAnimation* animation); // challenge/rep_7920.h (its typedef clashes with this file's)

extern void fn_800245EC(Mtx44 proj, Mtx view, Vec* points, f32* out, s32 count, s32 ySign);
extern void* fn_80039AB4(void);

extern void fn_1_16978(void);

// C3/actor.h and C3/anim.h clash with this file's ACTSetAnimation prototype, so forward-declare.
struct ANIMBank;
struct DODisplayData;
struct ActorLayout;
extern void ANIMGet(struct ANIMBank* animBank);
extern void fn_8004B1B8(void* tex);
extern void convertGeometryAndSknHeader(struct DODisplayData* pal, void* sknHeader);
extern void LoadActorLayout(struct ActorLayout* layout);
extern ActorObjectTable* ActorObjectInitTable(u16 count);

#define CH_ARAM_DONE() ((s32)lbl_803C6CF8.idle == 1)

// main.dol helpers used by fn_1_135C0. Declared from this call site's asm: several main headers
// (file_8004B284.h, file_80024D2C.h, ...) clash with this file's externs or give a void return
// where the original stores r3.
struct ActorSlot;
struct DOListEntry;
extern void fn_80023B04(s32 count);
extern void fn_8002399C(struct ActorSlot* slot, u16 index, s16 id, void* layout, void* anim, void* arg5);
extern void fn_80025C58(struct ShapeData* shape, struct ShapeModel** model);
extern void fn_800BD548(struct DOListEntry* entry, u8 numArgs, ...);
extern void fn_800B2C08(struct GameActor* actor, u16 bone);
struct CharActor;
extern s32 fn_80063010(struct CharActor* player, struct ActorObject* obj); // main/file_800527C4.h
extern s32 fn_8004B7B4(struct CharActor* model, struct ActorObject* obj); // main/file_8004B284.h
extern void* fn_80052634(void* player, void* obj); // (CharActor*, ActorObject*); returns its MeterTask
extern s32 fn_80062ED4(void* player, void* obj); // (CharActor*, ActorObject*); returns 0

extern u8 lbl_800F787C[]; // main.dol spawn template (main/file_800263FC.h)
void fn_1_10458(void);
void fn_1_151F8(void);
void fn_1_C9E0(struct ChDrawMtxNode* object);
void fn_1_F37C(void);
// .rodata strings referenced by the tables below.
extern const char lbl_1_rodata_660[];
extern const char lbl_1_rodata_66C[];
extern const char lbl_1_rodata_678[];
extern const char lbl_1_rodata_684[];
extern const char lbl_1_rodata_690[];
extern const char lbl_1_rodata_69C[];
extern const char lbl_1_rodata_6A8[];
extern const char lbl_1_rodata_6B4[];
extern const char lbl_1_rodata_6C0[];
extern const char lbl_1_rodata_6CC[];
extern const char lbl_1_rodata_6D8[];
extern const char lbl_1_rodata_6E4[];
extern const char lbl_1_rodata_6F0[];
extern const char lbl_1_rodata_6FC[];
extern const char lbl_1_rodata_708[];
extern const char lbl_1_rodata_714[];
extern const char lbl_1_rodata_720[];
extern const char lbl_1_rodata_72C[];
extern const char lbl_1_rodata_738[];
extern const char lbl_1_rodata_744[];
extern const char lbl_1_rodata_750[];
extern const char lbl_1_rodata_75C[];
extern const char lbl_1_rodata_768[];
extern const char lbl_1_rodata_774[];
extern const char lbl_1_rodata_780[];
extern const char lbl_1_rodata_78C[];
extern const char lbl_1_rodata_798[];
extern const char lbl_1_rodata_7A4[];
extern const char lbl_1_rodata_7B0[];
extern const char lbl_1_rodata_7BC[];
extern const char lbl_1_rodata_7C8[];
extern const char lbl_1_rodata_7D4[];
extern const char lbl_1_rodata_7E0[];
extern const char lbl_1_rodata_7EC[];
extern const char lbl_1_rodata_7F8[];
extern const char lbl_1_rodata_804[];
extern const char lbl_1_rodata_810[];
extern const char lbl_1_rodata_81C[];
extern const char lbl_1_rodata_828[];
extern const char lbl_1_rodata_834[];
extern const char lbl_1_rodata_840[];
extern const char lbl_1_rodata_84C[];
extern const char lbl_1_rodata_858[];
extern const char lbl_1_rodata_864[];
extern const char lbl_1_rodata_870[];
extern const char lbl_1_rodata_87C[];
extern const char lbl_1_rodata_888[];
extern const char lbl_1_rodata_894[];
extern const char lbl_1_rodata_8A0[];
extern const char lbl_1_rodata_8AC[];
extern const char lbl_1_rodata_8B8[];
extern const char lbl_1_rodata_8C4[];
extern const char lbl_1_rodata_8D0[];
extern const char lbl_1_rodata_8DC[];
extern const char lbl_1_rodata_8E8[];
extern const char lbl_1_rodata_8F0[];
extern const char lbl_1_rodata_8F8[];
extern const char lbl_1_rodata_900[];
extern const char lbl_1_rodata_908[];
extern const char lbl_1_rodata_910[];
extern const char lbl_1_rodata_914[];
extern const char lbl_1_rodata_91C[];
extern const char lbl_1_rodata_934[];
extern const char lbl_1_rodata_94C[];
extern const char lbl_1_rodata_960[];
extern const char lbl_1_rodata_974[];
extern const char lbl_1_rodata_988[];
extern const char lbl_1_rodata_99C[];
extern const char lbl_1_rodata_9B0[];
extern const char lbl_1_rodata_9C4[];
extern const char lbl_1_rodata_9D8[];
extern const char lbl_1_rodata_9F0[];
extern const char lbl_1_rodata_A08[];
extern const char lbl_1_rodata_A20[];
extern const char lbl_1_rodata_A38[];
extern const char lbl_1_rodata_A50[];
extern const char lbl_1_rodata_A68[];
extern const char lbl_1_rodata_A80[];
extern const char lbl_1_rodata_A98[];
extern const char lbl_1_rodata_AB0[];
extern const char lbl_1_rodata_AC8[];
extern const char lbl_1_rodata_AE0[];
extern const char lbl_1_rodata_AF8[];
extern const char lbl_1_rodata_B0C[];
extern const char lbl_1_rodata_B20[];
extern const char lbl_1_rodata_B34[];
extern const char lbl_1_rodata_B48[];
extern const char lbl_1_rodata_B5C[];
extern const char lbl_1_rodata_B70[];
extern const char lbl_1_rodata_B84[];
extern const char lbl_1_rodata_B9C[];
extern const char lbl_1_rodata_BB4[];
extern const char lbl_1_rodata_BCC[];
extern const char lbl_1_rodata_BE4[];
extern const char lbl_1_rodata_BFC[];
extern const char lbl_1_rodata_C14[];
extern const char lbl_1_rodata_C2C[];
extern const char lbl_1_rodata_C44[];
extern const char lbl_1_rodata_C5C[];
extern const char lbl_1_rodata_C74[];
extern const char lbl_1_rodata_C8C[];
extern const char lbl_1_rodata_CA4[];
extern const char lbl_1_rodata_CB8[];
extern const char lbl_1_rodata_CCC[];
extern const char lbl_1_rodata_CE0[];
extern const char lbl_1_rodata_CF4[];
extern const char lbl_1_rodata_D08[];
extern const char lbl_1_rodata_D1C[];
extern const char lbl_1_rodata_D30[];
extern const char lbl_1_rodata_D48[];
extern const char lbl_1_rodata_D60[];
extern const char lbl_1_rodata_D78[];
extern const char lbl_1_rodata_D90[];
extern const char lbl_1_rodata_DA8[];
extern const char lbl_1_rodata_DC0[];
extern const char lbl_1_rodata_DD8[];
extern const char lbl_1_rodata_DF0[];
extern const char lbl_1_rodata_E08[];
extern const char lbl_1_rodata_E20[];
extern const char lbl_1_rodata_E38[];
extern const char lbl_1_rodata_E50[];
extern const char lbl_1_rodata_E64[];
extern const char lbl_1_rodata_E78[];
extern const char lbl_1_rodata_E8C[];
extern const char lbl_1_rodata_EA0[];
extern const char lbl_1_rodata_EB4[];
extern const char lbl_1_rodata_EC8[];
extern const char lbl_1_rodata_EDC[];
extern const char lbl_1_rodata_EF4[];
extern const char lbl_1_rodata_F0C[];
extern const char lbl_1_rodata_F24[];
extern const char lbl_1_rodata_F3C[];
extern const char lbl_1_rodata_F54[];
extern const char lbl_1_rodata_F6C[];
extern const char lbl_1_rodata_F84[];
extern const char lbl_1_rodata_F9C[];
extern const char lbl_1_rodata_FB4[];
extern const char lbl_1_rodata_FCC[];
extern const char lbl_1_rodata_FE4[];
extern const char lbl_1_rodata_FFC[];
extern const char lbl_1_rodata_1010[];
extern const char lbl_1_rodata_1024[];
extern const char lbl_1_rodata_1038[];
extern const char lbl_1_rodata_104C[];
extern const char lbl_1_rodata_1060[];
extern const char lbl_1_rodata_1074[];
extern const char lbl_1_rodata_1088[];
extern const char lbl_1_rodata_10A0[];
extern const char lbl_1_rodata_10B8[];
extern const char lbl_1_rodata_10D0[];
extern const char lbl_1_rodata_10E8[];
extern const char lbl_1_rodata_1100[];
extern const char lbl_1_rodata_1118[];
extern const char lbl_1_rodata_1130[];
extern const char lbl_1_rodata_1148[];
extern const char lbl_1_rodata_1160[];
extern const char lbl_1_rodata_1178[];
extern const char lbl_1_rodata_1190[];
extern const char lbl_1_rodata_11A8[];
extern const char lbl_1_rodata_11BC[];
extern const char lbl_1_rodata_11D0[];
extern const char lbl_1_rodata_11E4[];
extern const char lbl_1_rodata_11F8[];
extern const char lbl_1_rodata_120C[];
extern const char lbl_1_rodata_1220[];
extern const char lbl_1_rodata_1234[];
extern const char lbl_1_rodata_124C[];
extern const char lbl_1_rodata_1264[];
extern const char lbl_1_rodata_127C[];
extern const char lbl_1_rodata_1294[];
extern const char lbl_1_rodata_12AC[];
extern const char lbl_1_rodata_12C4[];
extern const char lbl_1_rodata_12DC[];
extern const char lbl_1_rodata_12F4[];
extern const char lbl_1_rodata_130C[];
extern const char lbl_1_rodata_1324[];
extern const char lbl_1_rodata_133C[];
extern const char lbl_1_rodata_1354[];
extern const char lbl_1_rodata_1368[];
extern const char lbl_1_rodata_137C[];
extern const char lbl_1_rodata_1390[];
extern const char lbl_1_rodata_13A4[];
extern const char lbl_1_rodata_13B8[];
extern const char lbl_1_rodata_13CC[];
extern const char lbl_1_rodata_13E0[];
extern const char lbl_1_rodata_13F8[];
extern const char lbl_1_rodata_1410[];
extern const char lbl_1_rodata_1428[];
extern const char lbl_1_rodata_1440[];
extern const char lbl_1_rodata_1458[];
extern const char lbl_1_rodata_1470[];
extern const char lbl_1_rodata_1488[];
extern const char lbl_1_rodata_14A0[];
extern const char lbl_1_rodata_14B8[];
extern const char lbl_1_rodata_14D0[];
extern const char lbl_1_rodata_14E8[];
extern const char lbl_1_rodata_1500[];
extern const char lbl_1_rodata_1514[];
extern const char lbl_1_rodata_1528[];
extern const char lbl_1_rodata_153C[];
extern const char lbl_1_rodata_1550[];
extern const char lbl_1_rodata_1564[];
extern const char lbl_1_rodata_1578[];
extern const char lbl_1_rodata_158C[];
extern const char lbl_1_rodata_15A4[];
extern const char lbl_1_rodata_15BC[];
extern const char lbl_1_rodata_15D4[];
extern const char lbl_1_rodata_15EC[];
extern const char lbl_1_rodata_1604[];
extern const char lbl_1_rodata_161C[];
extern const char lbl_1_rodata_1634[];
extern const char lbl_1_rodata_164C[];
extern const char lbl_1_rodata_1664[];
extern const char lbl_1_rodata_167C[];
extern const char lbl_1_rodata_1694[];
extern const char lbl_1_rodata_16AC[];
extern const char lbl_1_rodata_16C0[];
extern const char lbl_1_rodata_16D4[];
extern const char lbl_1_rodata_16E8[];
extern const char lbl_1_rodata_16FC[];
extern const char lbl_1_rodata_1710[];
extern const char lbl_1_rodata_1724[];
extern const char lbl_1_rodata_1738[];
extern const char lbl_1_rodata_1750[];
extern const char lbl_1_rodata_1768[];
extern const char lbl_1_rodata_1780[];
extern const char lbl_1_rodata_1798[];
extern const char lbl_1_rodata_17B0[];
extern const char lbl_1_rodata_17C8[];
extern const char lbl_1_rodata_17E0[];
extern const char lbl_1_rodata_17F8[];
extern const char lbl_1_rodata_1810[];
extern const char lbl_1_rodata_1828[];
extern const char lbl_1_rodata_1840[];
extern const char lbl_1_rodata_1858[];
extern const char lbl_1_rodata_186C[];
extern const char lbl_1_rodata_1880[];
extern const char lbl_1_rodata_1894[];
extern const char lbl_1_rodata_18A8[];
extern const char lbl_1_rodata_18BC[];
extern const char lbl_1_rodata_18D0[];
extern const char lbl_1_rodata_18E4[];
extern const char lbl_1_rodata_18FC[];
extern const char lbl_1_rodata_1914[];
extern const char lbl_1_rodata_192C[];
extern const char lbl_1_rodata_1944[];
extern const char lbl_1_rodata_195C[];
extern const char lbl_1_rodata_1974[];
extern const char lbl_1_rodata_198C[];
extern const char lbl_1_rodata_19A4[];
extern const char lbl_1_rodata_19BC[];
extern const char lbl_1_rodata_19D4[];
extern const char lbl_1_rodata_19EC[];
extern const char lbl_1_rodata_1A04[];
extern const char lbl_1_rodata_1A18[];
extern const char lbl_1_rodata_1A2C[];
extern const char lbl_1_rodata_1A40[];
extern const char lbl_1_rodata_1A54[];
extern const char lbl_1_rodata_1A68[];
extern const char lbl_1_rodata_1A7C[];
extern const char lbl_1_rodata_1A90[];
extern const char lbl_1_rodata_1AA8[];
extern const char lbl_1_rodata_1AC0[];
extern const char lbl_1_rodata_1AD8[];
extern const char lbl_1_rodata_1AF0[];
extern const char lbl_1_rodata_1B08[];
extern const char lbl_1_rodata_1B20[];
extern const char lbl_1_rodata_1B38[];
extern const char lbl_1_rodata_1B50[];
extern const char lbl_1_rodata_1B68[];
extern const char lbl_1_rodata_1B80[];
extern const char lbl_1_rodata_1B98[];
extern const char lbl_1_rodata_1BB0[];
extern const char lbl_1_rodata_1BC4[];
extern const char lbl_1_rodata_1BD8[];
extern const char lbl_1_rodata_1BEC[];
extern const char lbl_1_rodata_1C00[];
extern const char lbl_1_rodata_1C14[];
extern const char lbl_1_rodata_1C28[];
extern const char lbl_1_rodata_1C3C[];
extern const char lbl_1_rodata_1C54[];
extern const char lbl_1_rodata_1C6C[];
extern const char lbl_1_rodata_1C84[];
extern const char lbl_1_rodata_1C9C[];
extern const char lbl_1_rodata_1CB4[];
extern const char lbl_1_rodata_1CCC[];
extern const char lbl_1_rodata_1CE4[];
extern const char lbl_1_rodata_1CFC[];
extern const char lbl_1_rodata_1D14[];
extern const char lbl_1_rodata_1D2C[];
extern const char lbl_1_rodata_1D44[];
extern const char lbl_1_rodata_1D5C[];
extern const char lbl_1_rodata_1D70[];
extern const char lbl_1_rodata_1D84[];
extern const char lbl_1_rodata_1D98[];
extern const char lbl_1_rodata_1DAC[];
extern const char lbl_1_rodata_1DC0[];
extern const char lbl_1_rodata_1DD4[];
extern const char lbl_1_rodata_1DE8[];
extern const char lbl_1_rodata_1E00[];
extern const char lbl_1_rodata_1E18[];
extern const char lbl_1_rodata_1E30[];
extern const char lbl_1_rodata_1E48[];
extern const char lbl_1_rodata_1E60[];
extern const char lbl_1_rodata_1E78[];
extern const char lbl_1_rodata_1E90[];
extern const char lbl_1_rodata_1EA8[];
extern const char lbl_1_rodata_1EC0[];
extern const char lbl_1_rodata_1ED8[];
extern const char lbl_1_rodata_1EF0[];
extern const char lbl_1_rodata_1F08[];
extern const char lbl_1_rodata_1F1C[];
extern const char lbl_1_rodata_1F30[];
extern const char lbl_1_rodata_1F44[];
extern const char lbl_1_rodata_1F58[];
extern const char lbl_1_rodata_1F6C[];
extern const char lbl_1_rodata_1F80[];
extern const char lbl_1_rodata_1F94[];
extern const char lbl_1_rodata_1FAC[];
extern const char lbl_1_rodata_1FC4[];
extern const char lbl_1_rodata_1FDC[];
extern const char lbl_1_rodata_1FF4[];
extern const char lbl_1_rodata_200C[];
extern const char lbl_1_rodata_2024[];
extern const char lbl_1_rodata_203C[];
extern const char lbl_1_rodata_2054[];
extern const char lbl_1_rodata_206C[];
extern const char lbl_1_rodata_2084[];
extern const char lbl_1_rodata_209C[];
extern const char lbl_1_rodata_20B4[];
extern const char lbl_1_rodata_20C8[];
extern const char lbl_1_rodata_20DC[];
extern const char lbl_1_rodata_20F0[];
extern const char lbl_1_rodata_2104[];
extern const char lbl_1_rodata_2118[];
extern const char lbl_1_rodata_212C[];
extern const char lbl_1_rodata_2140[];
extern const char lbl_1_rodata_2158[];
extern const char lbl_1_rodata_2170[];
extern const char lbl_1_rodata_2188[];
extern const char lbl_1_rodata_21A0[];
extern const char lbl_1_rodata_21B8[];
extern const char lbl_1_rodata_21D0[];
extern const char lbl_1_rodata_21E8[];
extern const char lbl_1_rodata_2200[];
extern const char lbl_1_rodata_2218[];
extern const char lbl_1_rodata_2230[];
extern const char lbl_1_rodata_2248[];
extern const char lbl_1_rodata_2260[];
extern const char lbl_1_rodata_2274[];
extern const char lbl_1_rodata_2288[];
extern const char lbl_1_rodata_229C[];
extern const char lbl_1_rodata_22B0[];
extern const char lbl_1_rodata_22C4[];
extern const char lbl_1_rodata_22D8[];
extern const char lbl_1_rodata_22EC[];
extern const char lbl_1_rodata_2304[];
extern const char lbl_1_rodata_231C[];
extern const char lbl_1_rodata_2334[];
extern const char lbl_1_rodata_234C[];
extern const char lbl_1_rodata_2364[];
extern const char lbl_1_rodata_237C[];
extern const char lbl_1_rodata_2394[];
extern const char lbl_1_rodata_23AC[];
extern const char lbl_1_rodata_23C4[];
extern const char lbl_1_rodata_23DC[];
extern const char lbl_1_rodata_23F4[];
extern const char lbl_1_rodata_240C[];
extern const char lbl_1_rodata_2420[];
extern const char lbl_1_rodata_2434[];
extern const char lbl_1_rodata_2448[];
extern const char lbl_1_rodata_245C[];
extern const char lbl_1_rodata_2470[];
extern const char lbl_1_rodata_2484[];
extern const char lbl_1_rodata_2498[];
extern const char lbl_1_rodata_24B0[];
extern const char lbl_1_rodata_24C8[];
extern const char lbl_1_rodata_24E0[];
extern const char lbl_1_rodata_24F8[];
extern const char lbl_1_rodata_2510[];
extern const char lbl_1_rodata_2528[];
extern const char lbl_1_rodata_2540[];
extern const char lbl_1_rodata_2558[];
extern const char lbl_1_rodata_2570[];
extern const char lbl_1_rodata_2588[];
extern const char lbl_1_rodata_25A0[];
extern const char lbl_1_rodata_25B8[];
extern const char lbl_1_rodata_25CC[];
extern const char lbl_1_rodata_25E0[];
extern const char lbl_1_rodata_25F4[];
extern const char lbl_1_rodata_2608[];
extern const char lbl_1_rodata_261C[];
extern const char lbl_1_rodata_2630[];
extern const char lbl_1_rodata_2644[];
extern const char lbl_1_rodata_265C[];
extern const char lbl_1_rodata_2674[];
extern const char lbl_1_rodata_268C[];
extern const char lbl_1_rodata_26A4[];
extern const char lbl_1_rodata_26BC[];
extern const char lbl_1_rodata_26D4[];
extern const char lbl_1_rodata_26EC[];
extern const char lbl_1_rodata_2704[];
extern const char lbl_1_rodata_271C[];
extern const char lbl_1_rodata_2734[];
extern const char lbl_1_rodata_274C[];
extern const char lbl_1_rodata_2764[];
extern const char lbl_1_rodata_2778[];
extern const char lbl_1_rodata_278C[];
extern const char lbl_1_rodata_27A0[];
extern const char lbl_1_rodata_27B4[];
extern const char lbl_1_rodata_27C8[];
extern const char lbl_1_rodata_27DC[];
extern const char lbl_1_rodata_27F0[];
extern const char lbl_1_rodata_2808[];
extern const char lbl_1_rodata_2820[];
extern const char lbl_1_rodata_2838[];
extern const char lbl_1_rodata_2850[];
extern const char lbl_1_rodata_2868[];
extern const char lbl_1_rodata_2880[];
extern const char lbl_1_rodata_2898[];
extern const char lbl_1_rodata_28B0[];
extern const char lbl_1_rodata_28C8[];
extern const char lbl_1_rodata_28E0[];
extern const char lbl_1_rodata_28F8[];
extern const char lbl_1_rodata_2910[];
extern const char lbl_1_rodata_2924[];
extern const char lbl_1_rodata_2938[];
extern const char lbl_1_rodata_294C[];
extern const char lbl_1_rodata_2960[];
extern const char lbl_1_rodata_2974[];
extern const char lbl_1_rodata_2988[];
extern const char lbl_1_rodata_299C[];
extern const char lbl_1_rodata_29B4[];
extern const char lbl_1_rodata_29CC[];
extern const char lbl_1_rodata_29E4[];
extern const char lbl_1_rodata_29FC[];
extern const char lbl_1_rodata_2A14[];
extern const char lbl_1_rodata_2A2C[];
extern const char lbl_1_rodata_2A44[];
extern const char lbl_1_rodata_2A5C[];
extern const char lbl_1_rodata_2A74[];
extern const char lbl_1_rodata_2A8C[];
extern const char lbl_1_rodata_2AA4[];
extern const char lbl_1_rodata_2ABC[];
extern const char lbl_1_rodata_2AD0[];
extern const char lbl_1_rodata_2AE4[];
extern const char lbl_1_rodata_2AF8[];
extern const char lbl_1_rodata_2B0C[];
extern const char lbl_1_rodata_2B20[];
extern const char lbl_1_rodata_2B34[];
extern const char lbl_1_rodata_2B48[];
extern const char lbl_1_rodata_2B60[];
extern const char lbl_1_rodata_2B78[];
extern const char lbl_1_rodata_2B90[];
extern const char lbl_1_rodata_2BA8[];
extern const char lbl_1_rodata_2BC0[];
extern const char lbl_1_rodata_2BD8[];
extern const char lbl_1_rodata_2BF0[];
extern const char lbl_1_rodata_2C08[];
extern const char lbl_1_rodata_2C20[];
extern const char lbl_1_rodata_2C38[];
extern const char lbl_1_rodata_2C50[];
extern const char lbl_1_rodata_2C68[];
extern const char lbl_1_rodata_2C7C[];
extern const char lbl_1_rodata_2C90[];
extern const char lbl_1_rodata_2CA4[];
extern const char lbl_1_rodata_2CB8[];
extern const char lbl_1_rodata_2CCC[];
extern const char lbl_1_rodata_2CE0[];
extern const char lbl_1_rodata_2CF4[];
extern const char lbl_1_rodata_2D0C[];
extern const char lbl_1_rodata_2D24[];
extern const char lbl_1_rodata_2D3C[];
extern const char lbl_1_rodata_2D54[];
extern const char lbl_1_rodata_2D6C[];
extern const char lbl_1_rodata_2D84[];
extern const char lbl_1_rodata_2D9C[];
extern const char lbl_1_rodata_2DB4[];
extern const char lbl_1_rodata_2DCC[];
extern const char lbl_1_rodata_2DE4[];
extern const char lbl_1_rodata_2DFC[];
extern const char lbl_1_rodata_2E14[];
extern const char lbl_1_rodata_2E2C[];
extern const char lbl_1_rodata_2E44[];
extern const char lbl_1_rodata_2E5C[];
extern const char lbl_1_rodata_2E74[];
extern const char lbl_1_rodata_2E88[];
extern const char lbl_1_rodata_2E9C[];
extern const char lbl_1_rodata_2EB0[];
extern const char lbl_1_rodata_2EC4[];
extern const char lbl_1_rodata_2ED8[];
extern const char lbl_1_rodata_2EEC[];
extern const char lbl_1_rodata_2F00[];
extern const char lbl_1_rodata_2F18[];
extern const char lbl_1_rodata_2F30[];
extern const char lbl_1_rodata_2F48[];
extern const char lbl_1_rodata_2F60[];
extern const char lbl_1_rodata_2F78[];
extern const char lbl_1_rodata_2F90[];
extern const char lbl_1_rodata_2FA8[];
extern const char lbl_1_rodata_2FC0[];
extern const char lbl_1_rodata_2FD8[];
extern const char lbl_1_rodata_2FF0[];
extern const char lbl_1_rodata_3008[];
extern const char lbl_1_rodata_3020[];
extern const char lbl_1_rodata_3038[];
extern const char lbl_1_rodata_3050[];
extern const char lbl_1_rodata_3068[];
extern const char lbl_1_rodata_3080[];
extern const char lbl_1_rodata_3094[];
extern const char lbl_1_rodata_30A8[];
extern const char lbl_1_rodata_30BC[];
extern const char lbl_1_rodata_30D0[];
extern const char lbl_1_rodata_30E4[];
extern const char lbl_1_rodata_30F8[];
extern const char lbl_1_rodata_310C[];
extern const char lbl_1_rodata_3124[];
extern const char lbl_1_rodata_313C[];
extern const char lbl_1_rodata_3154[];
extern const char lbl_1_rodata_316C[];
extern const char lbl_1_rodata_3184[];
extern const char lbl_1_rodata_319C[];
extern const char lbl_1_rodata_31B4[];
extern const char lbl_1_rodata_31CC[];
extern const char lbl_1_rodata_31E4[];
extern const char lbl_1_rodata_31FC[];
extern const char lbl_1_rodata_3214[];
extern const char lbl_1_rodata_322C[];
extern const char lbl_1_rodata_3240[];
extern const char lbl_1_rodata_3254[];
extern const char lbl_1_rodata_3268[];
extern const char lbl_1_rodata_327C[];
extern const char lbl_1_rodata_3290[];
extern const char lbl_1_rodata_32A4[];
extern const char lbl_1_rodata_32B8[];
extern const char lbl_1_rodata_32D0[];
extern const char lbl_1_rodata_32E8[];
extern const char lbl_1_rodata_3300[];
extern const char lbl_1_rodata_3318[];
extern const char lbl_1_rodata_3330[];
extern const char lbl_1_rodata_3348[];
extern const char lbl_1_rodata_3360[];
extern const char lbl_1_rodata_3378[];
extern const char lbl_1_rodata_3390[];
extern const char lbl_1_rodata_33A8[];
extern const char lbl_1_rodata_33C0[];
extern const char lbl_1_rodata_33D8[];
extern const char lbl_1_rodata_33F0[];
extern const char lbl_1_rodata_3408[];
extern const char lbl_1_rodata_3420[];
extern const char lbl_1_rodata_3438[];
extern const char lbl_1_rodata_3450[];
extern const char lbl_1_rodata_3468[];
extern const char lbl_1_rodata_3480[];
extern const char lbl_1_rodata_3498[];
extern const char lbl_1_rodata_34AC[];
extern const char lbl_1_rodata_34C0[];
extern const char lbl_1_rodata_34D4[];
extern const char lbl_1_rodata_34E8[];
extern const char lbl_1_rodata_34FC[];
extern const char lbl_1_rodata_3510[];
extern const char lbl_1_rodata_3524[];
extern const char lbl_1_rodata_353C[];
extern const char lbl_1_rodata_3554[];
extern const char lbl_1_rodata_356C[];
extern const char lbl_1_rodata_3584[];
extern const char lbl_1_rodata_359C[];
extern const char lbl_1_rodata_35B4[];
extern const char lbl_1_rodata_35CC[];
extern const char lbl_1_rodata_35E4[];
extern const char lbl_1_rodata_35FC[];
extern const char lbl_1_rodata_3614[];
extern const char lbl_1_rodata_362C[];
extern const char lbl_1_rodata_3644[];
extern const char lbl_1_rodata_365C[];
extern const char lbl_1_rodata_3674[];
extern const char lbl_1_rodata_368C[];
extern const char lbl_1_rodata_36A4[];
extern const char lbl_1_rodata_36BC[];
extern const char lbl_1_rodata_36D4[];
extern const char lbl_1_rodata_36E8[];
extern const char lbl_1_rodata_36FC[];
extern const char lbl_1_rodata_3710[];
extern const char lbl_1_rodata_3724[];
extern const char lbl_1_rodata_3738[];
extern const char lbl_1_rodata_374C[];
extern const char lbl_1_rodata_3760[];
extern const char lbl_1_rodata_3778[];
extern const char lbl_1_rodata_3790[];
extern const char lbl_1_rodata_37A8[];
extern const char lbl_1_rodata_37C0[];
extern const char lbl_1_rodata_37D8[];
extern const char lbl_1_rodata_37F0[];
extern const char lbl_1_rodata_3808[];
extern const char lbl_1_rodata_3820[];
extern const char lbl_1_rodata_3838[];
extern const char lbl_1_rodata_3850[];
extern const char lbl_1_rodata_3868[];
extern const char lbl_1_rodata_3880[];
extern const char lbl_1_rodata_3894[];
extern const char lbl_1_rodata_38A8[];
extern const char lbl_1_rodata_38BC[];
extern const char lbl_1_rodata_38D0[];
extern const char lbl_1_rodata_38E4[];
extern const char lbl_1_rodata_38F8[];
extern const char lbl_1_rodata_390C[];
extern const char lbl_1_rodata_3924[];
extern const char lbl_1_rodata_393C[];
extern const char lbl_1_rodata_3954[];
extern const char lbl_1_rodata_396C[];
extern const char lbl_1_rodata_3984[];
extern const char lbl_1_rodata_399C[];
extern const char lbl_1_rodata_39B4[];
extern const char lbl_1_rodata_39CC[];
extern const char lbl_1_rodata_39E4[];
extern const char lbl_1_rodata_39FC[];
extern const char lbl_1_rodata_3A14[];
extern const char lbl_1_rodata_3A2C[];
extern const char lbl_1_rodata_3A40[];
extern const char lbl_1_rodata_3A54[];
extern const char lbl_1_rodata_3A68[];
extern const char lbl_1_rodata_3A7C[];
extern const char lbl_1_rodata_3A90[];
extern const char lbl_1_rodata_3AA4[];
extern const char lbl_1_rodata_3AB8[];
extern const char lbl_1_rodata_3AD0[];
extern const char lbl_1_rodata_3AE8[];
extern const char lbl_1_rodata_3B00[];
extern const char lbl_1_rodata_3B18[];
extern const char lbl_1_rodata_3B30[];
extern const char lbl_1_rodata_3B48[];
extern const char lbl_1_rodata_3B60[];
extern const char lbl_1_rodata_3B78[];
extern const char lbl_1_rodata_3B90[];
extern const char lbl_1_rodata_3BA8[];
extern const char lbl_1_rodata_3BC0[];
extern const char lbl_1_rodata_3BD8[];
extern const char lbl_1_rodata_3BEC[];
extern const char lbl_1_rodata_3C00[];
extern const char lbl_1_rodata_3C14[];
extern const char lbl_1_rodata_3C28[];
extern const char lbl_1_rodata_3C3C[];
extern const char lbl_1_rodata_3C50[];
extern const char lbl_1_rodata_3C64[];
extern const char lbl_1_rodata_3C7C[];
extern const char lbl_1_rodata_3C94[];
extern const char lbl_1_rodata_3CAC[];
extern const char lbl_1_rodata_3CC4[];
extern const char lbl_1_rodata_3CDC[];
extern const char lbl_1_rodata_3CF4[];
extern const char lbl_1_rodata_3D0C[];
extern const char lbl_1_rodata_3D24[];
extern const char lbl_1_rodata_3D3C[];
extern const char lbl_1_rodata_3D54[];
extern const char lbl_1_rodata_3D6C[];
extern const char lbl_1_rodata_3D84[];
extern const char lbl_1_rodata_3D98[];
extern const char lbl_1_rodata_3DAC[];
extern const char lbl_1_rodata_3DC0[];
extern const char lbl_1_rodata_3DD4[];
extern const char lbl_1_rodata_3DE8[];
extern const char lbl_1_rodata_3DFC[];
extern const char lbl_1_rodata_3E10[];
extern const char lbl_1_rodata_3E28[];
extern const char lbl_1_rodata_3E40[];
extern const char lbl_1_rodata_3E58[];
extern const char lbl_1_rodata_3E70[];
extern const char lbl_1_rodata_3E88[];
extern const char lbl_1_rodata_3EA0[];
extern const char lbl_1_rodata_3EB8[];
extern const char lbl_1_rodata_3ED0[];
extern const char lbl_1_rodata_3EE8[];
extern const char lbl_1_rodata_3F00[];
extern const char lbl_1_rodata_3F18[];
extern const char lbl_1_rodata_3F30[];
extern const char lbl_1_rodata_3F48[];
extern const char lbl_1_rodata_3F60[];
extern const char lbl_1_rodata_3F78[];
extern const char lbl_1_rodata_3F90[];
extern const char lbl_1_rodata_3FA8[];
extern const char lbl_1_rodata_3FC0[];
extern const char lbl_1_rodata_3FD8[];
extern const char lbl_1_rodata_3FF0[];
extern const char lbl_1_rodata_4008[];
extern const char lbl_1_rodata_4020[];
extern const char lbl_1_rodata_4038[];
extern const char lbl_1_rodata_4050[];
extern const char lbl_1_rodata_4064[];
extern const char lbl_1_rodata_4078[];
extern const char lbl_1_rodata_408C[];
extern const char lbl_1_rodata_40A0[];
extern const char lbl_1_rodata_40B4[];
extern const char lbl_1_rodata_40C8[];
extern const char lbl_1_rodata_40DC[];
extern const char lbl_1_rodata_40F4[];
extern const char lbl_1_rodata_410C[];
extern const char lbl_1_rodata_4124[];
extern const char lbl_1_rodata_413C[];
extern const char lbl_1_rodata_4154[];
extern const char lbl_1_rodata_416C[];
extern const char lbl_1_rodata_4184[];
extern const char lbl_1_rodata_419C[];
extern const char lbl_1_rodata_41B4[];
extern const char lbl_1_rodata_41CC[];
extern const char lbl_1_rodata_41E4[];
extern const char lbl_1_rodata_41FC[];
extern const char lbl_1_rodata_4214[];
extern const char lbl_1_rodata_422C[];
extern const char lbl_1_rodata_4244[];
extern const char lbl_1_rodata_425C[];
extern const char lbl_1_rodata_4274[];
extern const char lbl_1_rodata_428C[];
extern const char lbl_1_rodata_42A4[];
extern const char lbl_1_rodata_42BC[];
extern const char lbl_1_rodata_42D4[];
extern const char lbl_1_rodata_42EC[];
extern const char lbl_1_rodata_4304[];
extern const char lbl_1_rodata_431C[];
extern const char lbl_1_rodata_4334[];
extern const char lbl_1_rodata_434C[];
extern const char lbl_1_rodata_4364[];
extern const char lbl_1_rodata_437C[];
extern const char lbl_1_rodata_4394[];
extern const char lbl_1_rodata_43AC[];
extern const char lbl_1_rodata_43C4[];
extern const char lbl_1_rodata_43DC[];
extern const char lbl_1_rodata_43F4[];
extern const char lbl_1_rodata_440C[];
extern const char lbl_1_rodata_4424[];
extern const char lbl_1_rodata_443C[];
extern const char lbl_1_rodata_4454[];
extern const char lbl_1_rodata_446C[];
extern const char lbl_1_rodata_4484[];
extern const char lbl_1_rodata_449C[];
extern const char lbl_1_rodata_44B4[];
extern const char lbl_1_rodata_44CC[];
extern const char lbl_1_rodata_44E4[];
extern const char lbl_1_rodata_44FC[];
extern const char lbl_1_rodata_4514[];
extern const char lbl_1_rodata_452C[];
extern const char lbl_1_rodata_4544[];
extern const char lbl_1_rodata_455C[];
extern const char lbl_1_rodata_4574[];
extern const char lbl_1_rodata_458C[];
extern const char lbl_1_rodata_45A4[];
extern const char lbl_1_rodata_45BC[];
extern const char lbl_1_rodata_45D4[];
extern const char lbl_1_rodata_45EC[];
extern const char lbl_1_rodata_4604[];
extern const char lbl_1_rodata_461C[];
extern const char lbl_1_rodata_4634[];
extern const char lbl_1_rodata_464C[];
extern const char lbl_1_rodata_4664[];
extern const char lbl_1_rodata_467C[];
extern const char lbl_1_rodata_4694[];
extern const char lbl_1_rodata_46AC[];
extern const char lbl_1_rodata_46C4[];
extern const char lbl_1_rodata_46DC[];
extern const char lbl_1_rodata_46F4[];
extern const char lbl_1_rodata_470C[];
extern const char lbl_1_rodata_4724[];
extern const char lbl_1_rodata_473C[];
extern const char lbl_1_rodata_4754[];
extern const char lbl_1_rodata_476C[];
extern const char lbl_1_rodata_4784[];
extern const char lbl_1_rodata_479C[];
extern const char lbl_1_rodata_47B4[];
extern const char lbl_1_rodata_47CC[];
extern const char lbl_1_rodata_47E4[];
extern const char lbl_1_rodata_47FC[];
extern const char lbl_1_rodata_4814[];
extern const char lbl_1_rodata_482C[];
extern const char lbl_1_rodata_4844[];
extern const char lbl_1_rodata_485C[];
extern const char lbl_1_rodata_4874[];
extern const char lbl_1_rodata_488C[];
extern const char lbl_1_rodata_48A4[];
extern const char lbl_1_rodata_48BC[];
extern const char lbl_1_rodata_48D4[];
extern const char lbl_1_rodata_48EC[];
extern const char lbl_1_rodata_4904[];
extern const char lbl_1_rodata_491C[];
extern const char lbl_1_rodata_4934[];
extern const char lbl_1_rodata_494C[];
extern const char lbl_1_rodata_4964[];
extern const char lbl_1_rodata_497C[];
extern const char lbl_1_rodata_4994[];
extern const char lbl_1_rodata_49AC[];
extern const char lbl_1_rodata_49C4[];
extern const char lbl_1_rodata_49DC[];
extern const char lbl_1_rodata_49F4[];
extern const char lbl_1_rodata_4A0C[];
extern const char lbl_1_rodata_4A24[];
extern const char lbl_1_rodata_4A3C[];
extern const char lbl_1_rodata_4A54[];
extern const char lbl_1_rodata_4A6C[];
extern const char lbl_1_rodata_4A84[];
extern const char lbl_1_rodata_4A9C[];
extern const char lbl_1_rodata_4AB4[];
extern const char lbl_1_rodata_4ACC[];
extern const char lbl_1_rodata_4AE4[];
extern const char lbl_1_rodata_4AFC[];
extern const char lbl_1_rodata_4B14[];
extern const char lbl_1_rodata_4B2C[];
extern const char lbl_1_rodata_4B44[];
extern const char lbl_1_rodata_4B5C[];
extern const char lbl_1_rodata_4B74[];
extern const char lbl_1_rodata_4B8C[];
extern const char lbl_1_rodata_4BA4[];
extern const char lbl_1_rodata_4BBC[];
extern const char lbl_1_rodata_4BD4[];
extern const char lbl_1_rodata_4BEC[];
extern const char lbl_1_rodata_4C04[];
extern const char lbl_1_rodata_4C1C[];
extern const char lbl_1_rodata_4C34[];
extern const char lbl_1_rodata_4C4C[];
extern const char lbl_1_rodata_4C64[];
extern const char lbl_1_rodata_4C7C[];
extern const char lbl_1_rodata_4C94[];
extern const char lbl_1_rodata_4CAC[];
extern const char lbl_1_rodata_4CC4[];
extern const char lbl_1_rodata_4CDC[];
extern const char lbl_1_rodata_4CF4[];
extern const char lbl_1_rodata_4D0C[];
extern const char lbl_1_rodata_4D24[];
extern const char lbl_1_rodata_4D3C[];
extern const char lbl_1_rodata_4D54[];
extern const char lbl_1_rodata_4D6C[];
extern const char lbl_1_rodata_4D84[];
extern const char lbl_1_rodata_4D9C[];
extern const char lbl_1_rodata_4DB4[];
extern const char lbl_1_rodata_4DCC[];
extern const char lbl_1_rodata_4DE4[];
extern const char lbl_1_rodata_4DFC[];
extern const char lbl_1_rodata_4E14[];
extern const char lbl_1_rodata_4E2C[];
extern const char lbl_1_rodata_4E44[];
extern const char lbl_1_rodata_4E5C[];
extern const char lbl_1_rodata_4E74[];
extern const char lbl_1_rodata_4E8C[];
extern const char lbl_1_rodata_4EA4[];
extern const char lbl_1_rodata_4EBC[];
extern const char lbl_1_rodata_4ED4[];
extern const char lbl_1_rodata_4EEC[];
extern const char lbl_1_rodata_4F04[];
extern const char lbl_1_rodata_4F1C[];
extern const char lbl_1_rodata_4F34[];
extern const char lbl_1_rodata_4F4C[];
extern const char lbl_1_rodata_4F64[];
extern const char lbl_1_rodata_4F7C[];
extern const char lbl_1_rodata_4F94[];
extern const char lbl_1_rodata_4FAC[];
extern const char lbl_1_rodata_4FC4[];
extern const char lbl_1_rodata_4FDC[];
extern const char lbl_1_rodata_4FF4[];
extern const char lbl_1_rodata_500C[];
extern const char lbl_1_rodata_5024[];
extern const char lbl_1_rodata_503C[];
extern const char lbl_1_rodata_5054[];
extern const char lbl_1_rodata_506C[];
extern const char lbl_1_rodata_5084[];
extern const char lbl_1_rodata_509C[];
extern const char lbl_1_rodata_50B4[];
extern const char lbl_1_rodata_50CC[];
extern const char lbl_1_rodata_50E4[];
extern const char lbl_1_rodata_50FC[];
extern const char lbl_1_rodata_5114[];
extern const char lbl_1_rodata_512C[];
extern const char lbl_1_rodata_5144[];
extern const char lbl_1_rodata_515C[];
extern const char lbl_1_rodata_5174[];
extern const char lbl_1_rodata_518C[];
extern const char lbl_1_rodata_51A4[];
extern const char lbl_1_rodata_51BC[];
extern const char lbl_1_rodata_51D4[];
extern const char lbl_1_rodata_51EC[];
extern const char lbl_1_rodata_5204[];
extern const char lbl_1_rodata_521C[];
extern const char lbl_1_rodata_5234[];
extern const char lbl_1_rodata_524C[];
extern const char lbl_1_rodata_5264[];
extern const char lbl_1_rodata_527C[];
extern const char lbl_1_rodata_5294[];
extern const char lbl_1_rodata_52AC[];
extern const char lbl_1_rodata_52C4[];
extern const char lbl_1_rodata_52DC[];
extern const char lbl_1_rodata_52F4[];
extern const char lbl_1_rodata_530C[];
extern const char lbl_1_rodata_5324[];
extern const char lbl_1_rodata_533C[];
extern const char lbl_1_rodata_5354[];
extern const char lbl_1_rodata_536C[];
extern const char lbl_1_rodata_5384[];
extern const char lbl_1_rodata_539C[];
extern const char lbl_1_rodata_53B4[];
extern const char lbl_1_rodata_53CC[];
extern const char lbl_1_rodata_53E4[];
extern const char lbl_1_rodata_53FC[];
extern const char lbl_1_rodata_5414[];
extern const char lbl_1_rodata_542C[];
extern const char lbl_1_rodata_5444[];
extern const char lbl_1_rodata_545C[];
extern const char lbl_1_rodata_5474[];
extern const char lbl_1_rodata_548C[];
extern const char lbl_1_rodata_54A4[];
extern const char lbl_1_rodata_54BC[];
extern const char lbl_1_rodata_54D4[];
extern const char lbl_1_rodata_54EC[];
extern const char lbl_1_rodata_5504[];
extern const char lbl_1_rodata_551C[];
extern const char lbl_1_rodata_5534[];
extern const char lbl_1_rodata_554C[];
extern const char lbl_1_rodata_5564[];
extern const char lbl_1_rodata_557C[];
extern const char lbl_1_rodata_5594[];
extern const char lbl_1_rodata_55AC[];
extern const char lbl_1_rodata_55C4[];
extern const char lbl_1_rodata_55DC[];
extern const char lbl_1_rodata_55F4[];
extern const char lbl_1_rodata_560C[];
extern const char lbl_1_rodata_5624[];
extern const char lbl_1_rodata_563C[];
extern const char lbl_1_rodata_5654[];
extern const char lbl_1_rodata_566C[];
extern const char lbl_1_rodata_5684[];
extern const char lbl_1_rodata_569C[];
extern const char lbl_1_rodata_56B4[];
extern const char lbl_1_rodata_56CC[];
extern const char lbl_1_rodata_56E4[];
extern const char lbl_1_rodata_56FC[];
extern const char lbl_1_rodata_5714[];
extern const char lbl_1_rodata_572C[];
extern const char lbl_1_rodata_5744[];
extern const char lbl_1_rodata_575C[];
extern const char lbl_1_rodata_5774[];
extern const char lbl_1_rodata_578C[];
extern const char lbl_1_rodata_57A4[];
extern const char lbl_1_rodata_57BC[];
extern const char lbl_1_rodata_57D4[];
extern const char lbl_1_rodata_57EC[];
extern const char lbl_1_rodata_5804[];
extern const char lbl_1_rodata_581C[];
extern const char lbl_1_rodata_5834[];
extern const char lbl_1_rodata_584C[];
extern const char lbl_1_rodata_5864[];
extern const char lbl_1_rodata_587C[];
extern const char lbl_1_rodata_5894[];
extern const char lbl_1_rodata_58AC[];
extern const char lbl_1_rodata_58C4[];
extern const char lbl_1_rodata_58DC[];
extern const char lbl_1_rodata_58F4[];
extern const char lbl_1_rodata_590C[];
extern const char lbl_1_rodata_5924[];
extern const char lbl_1_rodata_593C[];
extern const char lbl_1_rodata_5954[];
extern const char lbl_1_rodata_596C[];
extern const char lbl_1_rodata_5984[];
extern const char lbl_1_rodata_599C[];
extern const char lbl_1_rodata_59B4[];
extern const char lbl_1_rodata_59CC[];
extern const char lbl_1_rodata_59E4[];
extern const char lbl_1_rodata_59FC[];
extern const char lbl_1_rodata_5A14[];
extern const char lbl_1_rodata_5A2C[];
extern const char lbl_1_rodata_5A44[];
extern const char lbl_1_rodata_5A5C[];
extern const char lbl_1_rodata_5A74[];
extern const char lbl_1_rodata_5A8C[];
extern const char lbl_1_rodata_5AA4[];
extern const char lbl_1_rodata_5ABC[];
extern const char lbl_1_rodata_5AD4[];
extern const char lbl_1_rodata_5AEC[];
extern const char lbl_1_rodata_5B04[];
extern const char lbl_1_rodata_5B1C[];
extern const char lbl_1_rodata_5B34[];
extern const char lbl_1_rodata_5B4C[];
extern const char lbl_1_rodata_5B64[];
extern const char lbl_1_rodata_5B7C[];
extern const char lbl_1_rodata_5B94[];
extern const char lbl_1_rodata_5BAC[];
extern const char lbl_1_rodata_5BC4[];
extern const char lbl_1_rodata_5BDC[];
extern const char lbl_1_rodata_5BF4[];
extern const char lbl_1_rodata_5C0C[];
extern const char lbl_1_rodata_5C24[];
extern const char lbl_1_rodata_5C3C[];
extern const char lbl_1_rodata_5C54[];
extern const char lbl_1_rodata_5C6C[];
extern const char lbl_1_rodata_5C84[];
extern const char lbl_1_rodata_5C9C[];
extern const char lbl_1_rodata_5CB4[];
extern const char lbl_1_rodata_5CCC[];
extern const char lbl_1_rodata_5CE4[];
extern const char lbl_1_rodata_5CFC[];
extern const char lbl_1_rodata_5D14[];
extern const char lbl_1_rodata_5D2C[];
extern const char lbl_1_rodata_5D44[];
extern const char lbl_1_rodata_5D5C[];
extern const char lbl_1_rodata_5D74[];
extern const char lbl_1_rodata_5D8C[];
extern const char lbl_1_rodata_5DA4[];
extern const char lbl_1_rodata_5DBC[];
extern const char lbl_1_rodata_5DD4[];
extern const char lbl_1_rodata_5DEC[];
extern const char lbl_1_rodata_5E04[];
extern const char lbl_1_rodata_5E1C[];
extern const char lbl_1_rodata_5E34[];
extern const char lbl_1_rodata_5E4C[];
extern const char lbl_1_rodata_5E64[];
extern const char lbl_1_rodata_5E7C[];
extern const char lbl_1_rodata_5E94[];
extern const char lbl_1_rodata_5EAC[];
extern const char lbl_1_rodata_5EC4[];
extern const char lbl_1_rodata_5EDC[];
extern const char lbl_1_rodata_5EF4[];
extern const char lbl_1_rodata_5F0C[];
extern const char lbl_1_rodata_5F24[];
extern const char lbl_1_rodata_5F3C[];
extern const char lbl_1_rodata_5F54[];
extern const char lbl_1_rodata_5F6C[];
extern const char lbl_1_rodata_5F84[];
extern const char lbl_1_rodata_5F9C[];
extern const char lbl_1_rodata_5FB4[];
extern const char lbl_1_rodata_5FCC[];
extern const char lbl_1_rodata_5FE4[];
extern const char lbl_1_rodata_5FFC[];
extern const char lbl_1_rodata_6014[];
extern const char lbl_1_rodata_602C[];
extern const char lbl_1_rodata_6044[];
extern const char lbl_1_rodata_605C[];
extern const char lbl_1_rodata_6074[];
extern const char lbl_1_rodata_608C[];
extern const char lbl_1_rodata_60A4[];
extern const char lbl_1_rodata_60BC[];
extern const char lbl_1_rodata_60D4[];
extern const char lbl_1_rodata_60EC[];
extern const char lbl_1_rodata_6104[];
extern const char lbl_1_rodata_611C[];
extern const char lbl_1_rodata_6134[];
extern const char lbl_1_rodata_614C[];
extern const char lbl_1_rodata_6164[];
extern const char lbl_1_rodata_617C[];
extern const char lbl_1_rodata_6194[];
extern const char lbl_1_rodata_61AC[];
extern const char lbl_1_rodata_61C4[];
extern const char lbl_1_rodata_61DC[];
extern const char lbl_1_rodata_61F4[];
extern const char lbl_1_rodata_620C[];
extern const char lbl_1_rodata_6224[];
extern const char lbl_1_rodata_623C[];
extern const char lbl_1_rodata_6254[];
extern const char lbl_1_rodata_626C[];
extern const char lbl_1_rodata_6284[];
extern const char lbl_1_rodata_629C[];
extern const char lbl_1_rodata_62B4[];
extern const char lbl_1_rodata_62CC[];
extern const char lbl_1_rodata_62E4[];
extern const char lbl_1_rodata_62FC[];
extern const char lbl_1_rodata_6314[];
extern const char lbl_1_rodata_632C[];
extern const char lbl_1_rodata_6344[];
extern const char lbl_1_rodata_635C[];
extern const char lbl_1_rodata_6374[];
extern const char lbl_1_rodata_638C[];
extern const char lbl_1_rodata_63A4[];
extern const char lbl_1_rodata_63BC[];
extern const char lbl_1_rodata_63D4[];
extern const char lbl_1_rodata_63EC[];
extern const char lbl_1_rodata_6404[];
extern const char lbl_1_rodata_641C[];
extern const char lbl_1_rodata_6434[];
extern const char lbl_1_rodata_644C[];
extern const char lbl_1_rodata_6464[];
extern const char lbl_1_rodata_647C[];
extern const char lbl_1_rodata_6494[];
extern const char lbl_1_rodata_64AC[];
extern const char lbl_1_rodata_64C4[];
extern const char lbl_1_rodata_64DC[];
extern const char lbl_1_rodata_64F4[];
extern const char lbl_1_rodata_650C[];
extern const char lbl_1_rodata_6524[];
extern const char lbl_1_rodata_653C[];
extern const char lbl_1_rodata_6554[];
extern const char lbl_1_rodata_656C[];
extern const char lbl_1_rodata_6584[];
extern const char lbl_1_rodata_659C[];
extern const char lbl_1_rodata_65B4[];
extern const char lbl_1_rodata_65CC[];
extern const char lbl_1_rodata_65E4[];
extern const char lbl_1_rodata_65FC[];
extern const char lbl_1_rodata_6614[];
extern const char lbl_1_rodata_662C[];
extern const char lbl_1_rodata_6644[];
extern const char lbl_1_rodata_665C[];
extern const char lbl_1_rodata_6674[];
extern const char lbl_1_rodata_668C[];
extern const char lbl_1_rodata_66A4[];
extern const char lbl_1_rodata_66BC[];
extern const char lbl_1_rodata_66D4[];
extern const char lbl_1_rodata_66EC[];
extern const char lbl_1_rodata_6704[];
extern const char lbl_1_rodata_671C[];
extern const char lbl_1_rodata_6734[];
extern const char lbl_1_rodata_674C[];
extern const char lbl_1_rodata_6764[];
extern const char lbl_1_rodata_677C[];
extern const char lbl_1_rodata_6794[];
extern const char lbl_1_rodata_67AC[];
extern const char lbl_1_rodata_67C4[];
extern const char lbl_1_rodata_67DC[];
extern const char lbl_1_rodata_67F4[];
extern const char lbl_1_rodata_680C[];
extern const char lbl_1_rodata_6824[];
extern const char lbl_1_rodata_683C[];
extern const char lbl_1_rodata_6854[];
extern const char lbl_1_rodata_686C[];
extern const char lbl_1_rodata_6884[];
extern const char lbl_1_rodata_689C[];
extern const char lbl_1_rodata_68B4[];
extern const char lbl_1_rodata_68CC[];
extern const char lbl_1_rodata_68E4[];
extern const char lbl_1_rodata_68FC[];
extern const char lbl_1_rodata_6914[];
extern const char lbl_1_rodata_692C[];
extern const char lbl_1_rodata_6944[];
extern const char lbl_1_rodata_695C[];
extern const char lbl_1_rodata_6974[];
extern const char lbl_1_rodata_698C[];
extern const char lbl_1_rodata_69A4[];
extern const char lbl_1_rodata_69BC[];
extern const char lbl_1_rodata_69D4[];
extern const char lbl_1_rodata_69EC[];
extern const char lbl_1_rodata_6A04[];
extern const char lbl_1_rodata_6A1C[];
extern const char lbl_1_rodata_6A34[];
extern const char lbl_1_rodata_6A4C[];
extern const char lbl_1_rodata_6A64[];
extern const char lbl_1_rodata_6A7C[];
extern const char lbl_1_rodata_6A94[];
extern const char lbl_1_rodata_6AAC[];
extern const char lbl_1_rodata_6AC4[];
extern const char lbl_1_rodata_6ADC[];
extern const char lbl_1_rodata_6AF4[];
extern const char lbl_1_rodata_6B0C[];
extern const char lbl_1_rodata_6B24[];
extern const char lbl_1_rodata_6B3C[];
extern const char lbl_1_rodata_6B54[];
extern const char lbl_1_rodata_6B6C[];
extern const char lbl_1_rodata_6B84[];
extern const char lbl_1_rodata_6B9C[];
extern const char lbl_1_rodata_6BB4[];
extern const char lbl_1_rodata_6BCC[];
extern const char lbl_1_rodata_6BE4[];
extern const char lbl_1_rodata_6BFC[];
extern const char lbl_1_rodata_6C14[];
extern const char lbl_1_rodata_6C2C[];
extern const char lbl_1_rodata_6C44[];
extern const char lbl_1_rodata_6C5C[];
extern const char lbl_1_rodata_6C74[];
extern const char lbl_1_rodata_6C8C[];
extern const char lbl_1_rodata_6CA4[];
extern const char lbl_1_rodata_6CBC[];
extern const char lbl_1_rodata_6CD4[];
extern const char lbl_1_rodata_6CEC[];
extern const char lbl_1_rodata_6D04[];
extern const char lbl_1_rodata_6D1C[];
extern const char lbl_1_rodata_6D34[];
extern const char lbl_1_rodata_6D4C[];
extern const char lbl_1_rodata_6D64[];
extern const char lbl_1_rodata_6D7C[];
extern const char lbl_1_rodata_6D94[];
extern const char lbl_1_rodata_6DAC[];
extern const char lbl_1_rodata_6DC4[];
extern const char lbl_1_rodata_6DDC[];
extern const char lbl_1_rodata_6DF4[];
extern const char lbl_1_rodata_6E0C[];
extern const char lbl_1_rodata_6E24[];
extern const char lbl_1_rodata_6E3C[];
extern const char lbl_1_rodata_6E54[];
extern const char lbl_1_rodata_6E6C[];
extern const char lbl_1_rodata_6E84[];
extern const char lbl_1_rodata_6E9C[];
extern const char lbl_1_rodata_6EB4[];
extern const char lbl_1_rodata_6ECC[];
extern const char lbl_1_rodata_6EE4[];
extern const char lbl_1_rodata_6EFC[];
extern const char lbl_1_rodata_6F14[];
extern const char lbl_1_rodata_6F2C[];
extern const char lbl_1_rodata_6F44[];
extern const char lbl_1_rodata_6F5C[];
extern const char lbl_1_rodata_6F74[];
extern const char lbl_1_rodata_6F8C[];
extern const char lbl_1_rodata_6FA4[];
extern const char lbl_1_rodata_6FBC[];
extern const char lbl_1_rodata_6FD4[];
extern const char lbl_1_rodata_6FEC[];
extern const char lbl_1_rodata_7004[];
extern const char lbl_1_rodata_701C[];
extern const char lbl_1_rodata_7034[];
extern const char lbl_1_rodata_704C[];
extern const char lbl_1_rodata_7064[];
extern const char lbl_1_rodata_707C[];
extern const char lbl_1_rodata_7094[];
extern const char lbl_1_rodata_70AC[];
extern const char lbl_1_rodata_70C4[];
extern const char lbl_1_rodata_70DC[];
extern const char lbl_1_rodata_70F4[];
extern const char lbl_1_rodata_710C[];
extern const char lbl_1_rodata_7124[];
extern const char lbl_1_rodata_713C[];
extern const char lbl_1_rodata_7154[];
extern const char lbl_1_rodata_716C[];
extern const char lbl_1_rodata_7184[];
extern const char lbl_1_rodata_719C[];
extern const char lbl_1_rodata_71B4[];
extern const char lbl_1_rodata_71CC[];
extern const char lbl_1_rodata_71E4[];
extern const char lbl_1_rodata_71FC[];
extern const char lbl_1_rodata_7214[];
extern const char lbl_1_rodata_722C[];
extern const char lbl_1_rodata_7244[];
extern const char lbl_1_rodata_725C[];
extern const char lbl_1_rodata_7274[];
extern const char lbl_1_rodata_728C[];
extern const char lbl_1_rodata_72A4[];
extern const char lbl_1_rodata_72BC[];
extern const char lbl_1_rodata_72C4[];
extern const char lbl_1_rodata_72CC[];
extern const char lbl_1_rodata_72D8[];
extern const char lbl_1_rodata_72E4[];
extern const char lbl_1_rodata_72E8[];
extern const char lbl_1_rodata_7328[];
extern const char lbl_1_rodata_7330[];
extern const char lbl_1_rodata_733C[];
extern const char lbl_1_rodata_7350[];
extern const char lbl_1_rodata_7354[];
extern const char lbl_1_rodata_7358[];

// .data of this file (0x1DC0-0xF588), in address order. The switch jump tables after it (0xF588-0xF888)
// stay in an auto unit while some of their functions are NONMATCHING.
// File statics are the objects the original reaches through the pooled .data base; the rest are globals.
typedef struct ChAramAsset { // AssetLoadInstructions without the bitfields (CW rejects initialisers for those)
    u32 compression;
    u32 sizeInfo; // top 4 bits: flags, rest: size
    u32 diskLocation;
    u32 compressedSize;
} ChAramAsset;
// Debug-build file entry: the path replaces the compression word (ARAMTransfer gets the entry).
typedef struct ChFileDesc {
    const char* path;
    u32 sizeInfo;
    u32 diskLocation;
    u32 compressedSize;
} ChFileDesc;
// Draw-list node with its model matrix (fn_800A7D4C), one per frame buffer.
typedef struct ChDrawMtxNode {
    uintptr_t link; // (pointer-sized on PC, like DrawLink) next node | flags in bits 0-1, set by fn_800A7D4C (TODO port: tagged 32-bit pointer)
    void (*draw)(struct ChDrawMtxNode* object);
    Mtx m;
} ChDrawMtxNode;
// Draw-list node without matrix.
typedef struct ChDrawNode8 {
    u32 link;
    void (*draw)(void);
} ChDrawNode8;
ChPair lbl_1_data_1DC0[22] = { // 0xFFFF-terminated lists
    {0x0016, 0x0010}, {0x0017, 0x0011}, {0x0018, 0x0012}, {0x0019, 0x0013}, {0x001A, 0x0014}, {0x001B, 0x0015}, {0x0020, 0x001C}, {0x0021, 0x001D},
    {0x0022, 0x001E}, {0x0023, 0x001F}, {0x0026, 0x0025}, {0x0028, 0x0027}, {0x003D, 0x003C}, {0xFFFF, 0x0000}, {0x004A, 0x004B}, {0xFFFF, 0x0000},
    {0x002F, 0x0034}, {0x0030, 0x0035}, {0x0031, 0x0036}, {0x0032, 0x0037}, {0x0033, 0x0038}, {0xFFFF, 0x0000},
};
ChPair lbl_1_data_1E18[40] = {
    {0x0041, 0x0047}, {0x0042, 0x0048}, {0x0043, 0x0049}, {0x0044, 0x004A}, {0x0045, 0x004B}, {0x0046, 0x004C}, {0xFFFF, 0x0000}, {0x002F, 0x0034},
    {0xFFFF, 0x0000}, {0x0000, 0x0001}, {0x0002, 0x0003}, {0x0004, 0x0005}, {0x0006, 0x0007}, {0x0008, 0x0009}, {0x000E, 0x000F}, {0x000D, 0x000C},
    {0x000B, 0x000A}, {0x0016, 0x0017}, {0x0018, 0x0019}, {0x001A, 0x001B}, {0x0010, 0x0011}, {0x0012, 0x0013}, {0x0014, 0x0015}, {0x0020, 0x0021},
    {0x0022, 0x0023}, {0x001C, 0x001D}, {0x001E, 0x001F}, {0x0024, 0x0026}, {0x0025, 0x0028}, {0x0027, 0x0029}, {0x002A, 0x002B}, {0x002C, 0x002D},
    {0x002E, 0x002F}, {0x0030, 0x0031}, {0x0032, 0x0033}, {0x0034, 0x0035}, {0x0036, 0x0037}, {0x0038, 0x0039}, {0x003A, 0x003B}, {0x003D, 0x003C},
};
u8 lbl_1_data_1EB8[98] = { // byte table; nothing in the code reads it
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x00, 0x0E,
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01,
};
static u8 lbl_1_data_1F1A = 1;
const char* lbl_1_data_1F1C[54] = {
    lbl_1_rodata_660, lbl_1_rodata_66C, lbl_1_rodata_678, lbl_1_rodata_684,
    lbl_1_rodata_690, lbl_1_rodata_69C, lbl_1_rodata_6A8, lbl_1_rodata_6B4,
    lbl_1_rodata_6C0, lbl_1_rodata_6CC, lbl_1_rodata_6D8, lbl_1_rodata_6E4,
    lbl_1_rodata_6F0, lbl_1_rodata_6FC, lbl_1_rodata_708, lbl_1_rodata_714,
    lbl_1_rodata_720, lbl_1_rodata_72C, lbl_1_rodata_738, lbl_1_rodata_744,
    lbl_1_rodata_750, lbl_1_rodata_75C, lbl_1_rodata_768, lbl_1_rodata_774,
    lbl_1_rodata_780, lbl_1_rodata_78C, lbl_1_rodata_798, lbl_1_rodata_7A4,
    lbl_1_rodata_7B0, lbl_1_rodata_7BC, lbl_1_rodata_7C8, lbl_1_rodata_7D4,
    lbl_1_rodata_7E0, lbl_1_rodata_7EC, lbl_1_rodata_7F8, lbl_1_rodata_804,
    lbl_1_rodata_810, lbl_1_rodata_81C, lbl_1_rodata_828, lbl_1_rodata_834,
    lbl_1_rodata_840, lbl_1_rodata_84C, lbl_1_rodata_858, lbl_1_rodata_864,
    lbl_1_rodata_870, lbl_1_rodata_87C, lbl_1_rodata_888, lbl_1_rodata_894,
    lbl_1_rodata_8A0, lbl_1_rodata_8AC, lbl_1_rodata_8B8, lbl_1_rodata_8C4,
    lbl_1_rodata_8D0, lbl_1_rodata_8DC,
};
char lbl_1_data_1FF4[14][0x40] = {
    "PITCHER", "CATCHER", "1B     ", "2B     ",
    "3B     ", "SS     ", "LEFT   ", "CENTER ",
    "RIGHT  ", "BATTER ", "RUNNER1", "RUNNER2",
    "RUNNER3", "",
};
const char* lbl_1_data_2374[7] = {
    lbl_1_rodata_8E8, lbl_1_rodata_8F0, lbl_1_rodata_8F8, lbl_1_rodata_900,
    lbl_1_rodata_908, lbl_1_rodata_910, lbl_1_rodata_914,
};
static u8 lbl_1_data_2390[8] = {
    1, 1, 1, 1, 1, 1, 1, 0,
};
ChFileDesc lbl_1_data_2398[2052] = { // character model/animation files
    {lbl_1_rodata_91C, 0x4001E0CC, 0x00000000, 0x00012DE4},
    {lbl_1_rodata_934, 0x4000D740, 0x00000000, 0x00009230},
    {lbl_1_rodata_94C, 0x400EA74C, 0x00000000, 0x0008FEF4},
    {lbl_1_rodata_960, 0x400696D4, 0x00000000, 0x00040DAC},
    {lbl_1_rodata_974, 0x400ECCFC, 0x00000000, 0x000892A8},
    {lbl_1_rodata_988, 0x4009DD04, 0x00000000, 0x000656A0},
    {lbl_1_rodata_99C, 0x4000FC7C, 0x00000000, 0x000087A0},
    {lbl_1_rodata_9B0, 0x400C2230, 0x00000000, 0x00072BB4},
    {lbl_1_rodata_9C4, 0x40060268, 0x00000000, 0x00039908},
    {lbl_1_rodata_9D8, 0x4008D6F4, 0x00000000, 0x00053DF0},
    {lbl_1_rodata_9F0, 0x400BADCC, 0x00000000, 0x000704B4},
    {lbl_1_rodata_A08, 0x40041A00, 0x00000000, 0x00027948},
    {lbl_1_rodata_A20, 0x4001BC38, 0x00000000, 0x0000E598},
    {lbl_1_rodata_A38, 0x40093038, 0x00000000, 0x00051784},
    {lbl_1_rodata_A50, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_A68, 0x4002CAC0, 0x00000000, 0x00018C18},
    {lbl_1_rodata_A80, 0x4008BA3C, 0x00000000, 0x0004FE44},
    {lbl_1_rodata_A98, 0x400301D4, 0x00000000, 0x0001C0F0},
    {lbl_1_rodata_AB0, 0x400828E4, 0x00000000, 0x00053C38},
    {lbl_1_rodata_AC8, 0x40025734, 0x00000000, 0x0001803C},
    {lbl_1_rodata_AE0, 0x40010340, 0x00000000, 0x0000B790},
    {lbl_1_rodata_AF8, 0x40100160, 0x00000000, 0x0009D384},
    {lbl_1_rodata_B0C, 0x40069784, 0x00000000, 0x000409A8},
    {lbl_1_rodata_B20, 0x400E8B28, 0x00000000, 0x00087AB4},
    {lbl_1_rodata_B34, 0x40089BBC, 0x00000000, 0x000566C8},
    {lbl_1_rodata_B48, 0x4000FC7C, 0x00000000, 0x00008570},
    {lbl_1_rodata_B5C, 0x400B302C, 0x00000000, 0x00066244},
    {lbl_1_rodata_B70, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_B84, 0x4009DA84, 0x00000000, 0x0005D858},
    {lbl_1_rodata_B9C, 0x400C460C, 0x00000000, 0x000767C0},
    {lbl_1_rodata_BB4, 0x40042F70, 0x00000000, 0x00028638},
    {lbl_1_rodata_BCC, 0x400204E8, 0x00000000, 0x00011D9C},
    {lbl_1_rodata_BE4, 0x4008CF48, 0x00000000, 0x0004E724},
    {lbl_1_rodata_BFC, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_C14, 0x40027438, 0x00000000, 0x00014B1C},
    {lbl_1_rodata_C2C, 0x400863B4, 0x00000000, 0x0004C15C},
    {lbl_1_rodata_C44, 0x400277A8, 0x00000000, 0x00014E10},
    {lbl_1_rodata_C5C, 0x4007AFC0, 0x00000000, 0x0004C7B8},
    {lbl_1_rodata_C74, 0x4001D3B8, 0x00000000, 0x00015034},
    {lbl_1_rodata_C8C, 0x4000EDE0, 0x00000000, 0x0000AD10},
    {lbl_1_rodata_CA4, 0x400F472C, 0x00000000, 0x00095260},
    {lbl_1_rodata_CB8, 0x40069908, 0x00000000, 0x0003F9B0},
    {lbl_1_rodata_CCC, 0x400E570C, 0x00000000, 0x000879FC},
    {lbl_1_rodata_CE0, 0x40096B74, 0x00000000, 0x0005E200},
    {lbl_1_rodata_CF4, 0x4000FF1C, 0x00000000, 0x0000882C},
    {lbl_1_rodata_D08, 0x4009C3E8, 0x00000000, 0x0005DC00},
    {lbl_1_rodata_D1C, 0x40033688, 0x00000000, 0x0001FBB8},
    {lbl_1_rodata_D30, 0x4009347C, 0x00000000, 0x000558C8},
    {lbl_1_rodata_D48, 0x400C845C, 0x00000000, 0x0007A080},
    {lbl_1_rodata_D60, 0x4004A9F0, 0x00000000, 0x0002BACC},
    {lbl_1_rodata_D78, 0x40021EB4, 0x00000000, 0x000118F0},
    {lbl_1_rodata_D90, 0x40082C64, 0x00000000, 0x000484F4},
    {lbl_1_rodata_DA8, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_DC0, 0x400237BC, 0x00000000, 0x00013898},
    {lbl_1_rodata_DD8, 0x40062D70, 0x00000000, 0x000373DC},
    {lbl_1_rodata_DF0, 0x40032BD8, 0x00000000, 0x00020010},
    {lbl_1_rodata_E08, 0x40078EE0, 0x00000000, 0x00049DD4},
    {lbl_1_rodata_E20, 0x40021A44, 0x00000000, 0x00015E08},
    {lbl_1_rodata_E38, 0x40013E80, 0x00000000, 0x0000C09C},
    {lbl_1_rodata_E50, 0x40111BC8, 0x00000000, 0x000AE460},
    {lbl_1_rodata_E64, 0x40087BCC, 0x00000000, 0x00051D60},
    {lbl_1_rodata_E78, 0x40131100, 0x00000000, 0x000B959C},
    {lbl_1_rodata_E8C, 0x400A6764, 0x00000000, 0x00068C0C},
    {lbl_1_rodata_EA0, 0x40012FBC, 0x00000000, 0x0000B8B4},
    {lbl_1_rodata_EB4, 0x400D8264, 0x00000000, 0x0007FB2C},
    {lbl_1_rodata_EC8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_EDC, 0x40097B24, 0x00000000, 0x0005BFD4},
    {lbl_1_rodata_EF4, 0x400DB6D8, 0x00000000, 0x0008A5A8},
    {lbl_1_rodata_F0C, 0x4005C2A8, 0x00000000, 0x00037D20},
    {lbl_1_rodata_F24, 0x40028810, 0x00000000, 0x000166D8},
    {lbl_1_rodata_F3C, 0x400B49C8, 0x00000000, 0x0006945C},
    {lbl_1_rodata_F54, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_F6C, 0x40033FDC, 0x00000000, 0x0001CBB8},
    {lbl_1_rodata_F84, 0x400B0014, 0x00000000, 0x0006799C},
    {lbl_1_rodata_F9C, 0x4001FD7C, 0x00000000, 0x00010980},
    {lbl_1_rodata_FB4, 0x4007D1FC, 0x00000000, 0x0004E52C},
    {lbl_1_rodata_FCC, 0x4001DA50, 0x00000000, 0x00014788},
    {lbl_1_rodata_FE4, 0x40012940, 0x00000000, 0x0000C298},
    {lbl_1_rodata_FFC, 0x4013237C, 0x00000000, 0x000B23F4},
    {lbl_1_rodata_1010, 0x40081A98, 0x00000000, 0x0004CB58},
    {lbl_1_rodata_1024, 0x40111B24, 0x00000000, 0x000960A8},
    {lbl_1_rodata_1038, 0x400A2B98, 0x00000000, 0x0005F0C8},
    {lbl_1_rodata_104C, 0x40012EA4, 0x00000000, 0x00009728},
    {lbl_1_rodata_1060, 0x400E90EC, 0x00000000, 0x0007A0E0},
    {lbl_1_rodata_1074, 0x40041E74, 0x00000000, 0x00028DE4},
    {lbl_1_rodata_1088, 0x400C3950, 0x00000000, 0x0006D9C4},
    {lbl_1_rodata_10A0, 0x400E86C4, 0x00000000, 0x00085C5C},
    {lbl_1_rodata_10B8, 0x400533EC, 0x00000000, 0x00031060},
    {lbl_1_rodata_10D0, 0x40025F4C, 0x00000000, 0x00013D14},
    {lbl_1_rodata_10E8, 0x400B0F20, 0x00000000, 0x0005D338},
    {lbl_1_rodata_1100, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_1118, 0x40031884, 0x00000000, 0x00016B50},
    {lbl_1_rodata_1130, 0x4008C71C, 0x00000000, 0x00043DC0},
    {lbl_1_rodata_1148, 0x400549C4, 0x00000000, 0x0002FF4C},
    {lbl_1_rodata_1160, 0x400809E8, 0x00000000, 0x0004A090},
    {lbl_1_rodata_1178, 0x40022118, 0x00000000, 0x000187C0},
    {lbl_1_rodata_1190, 0x400123C0, 0x00000000, 0x0000BFF0},
    {lbl_1_rodata_11A8, 0x401105D8, 0x00000000, 0x0009DEE4},
    {lbl_1_rodata_11BC, 0x4007C9BC, 0x00000000, 0x0004BF30},
    {lbl_1_rodata_11D0, 0x400E14AC, 0x00000000, 0x00080610},
    {lbl_1_rodata_11E4, 0x400998D8, 0x00000000, 0x0005BACC},
    {lbl_1_rodata_11F8, 0x400106DC, 0x00000000, 0x00008198},
    {lbl_1_rodata_120C, 0x4009FA28, 0x00000000, 0x000539A0},
    {lbl_1_rodata_1220, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1234, 0x400A8E34, 0x00000000, 0x0006014C},
    {lbl_1_rodata_124C, 0x400D54C0, 0x00000000, 0x0007955C},
    {lbl_1_rodata_1264, 0x400515E0, 0x00000000, 0x000313A8},
    {lbl_1_rodata_127C, 0x400222F4, 0x00000000, 0x00011BC4},
    {lbl_1_rodata_1294, 0x4008C8EC, 0x00000000, 0x0004B990},
    {lbl_1_rodata_12AC, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_12C4, 0x40027FD0, 0x00000000, 0x00016A28},
    {lbl_1_rodata_12DC, 0x4007C894, 0x00000000, 0x00041110},
    {lbl_1_rodata_12F4, 0x400215A8, 0x00000000, 0x0000F608},
    {lbl_1_rodata_130C, 0x40078314, 0x00000000, 0x00047044},
    {lbl_1_rodata_1324, 0x40018A20, 0x00000000, 0x00012304},
    {lbl_1_rodata_133C, 0x4000F780, 0x00000000, 0x0000AB70},
    {lbl_1_rodata_1354, 0x4013CF18, 0x00000000, 0x000B1C0C},
    {lbl_1_rodata_1368, 0x4007C0F4, 0x00000000, 0x00043FEC},
    {lbl_1_rodata_137C, 0x40168A8E, 0x00000000, 0x000C7B48},
    {lbl_1_rodata_1390, 0x400CB844, 0x00000000, 0x00070960},
    {lbl_1_rodata_13A4, 0x400148AC, 0x00000000, 0x0000A648},
    {lbl_1_rodata_13B8, 0x400EE648, 0x00000000, 0x0007AE00},
    {lbl_1_rodata_13CC, 0x40047D12, 0x00000000, 0x0002EC54},
    {lbl_1_rodata_13E0, 0x400C2BF0, 0x00000000, 0x0006A444},
    {lbl_1_rodata_13F8, 0x40101FDC, 0x00000000, 0x00091AE8},
    {lbl_1_rodata_1410, 0x400539F4, 0x00000000, 0x0002D7C0},
    {lbl_1_rodata_1428, 0x40020FAC, 0x00000000, 0x0000FF98},
    {lbl_1_rodata_1440, 0x400C0E98, 0x00000000, 0x00069510},
    {lbl_1_rodata_1458, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_1470, 0x4002E910, 0x00000000, 0x00016C4C},
    {lbl_1_rodata_1488, 0x4008244C, 0x00000000, 0x00042898},
    {lbl_1_rodata_14A0, 0x40068A10, 0x00000000, 0x000349DC},
    {lbl_1_rodata_14B8, 0x400A0264, 0x00000000, 0x00059150},
    {lbl_1_rodata_14D0, 0x4001C328, 0x00000000, 0x0001365C},
    {lbl_1_rodata_14E8, 0x4000EAE0, 0x00000000, 0x00008F28},
    {lbl_1_rodata_1500, 0x4010FA88, 0x00000000, 0x000A27D4},
    {lbl_1_rodata_1514, 0x40066668, 0x00000000, 0x0003D364},
    {lbl_1_rodata_1528, 0x400E652C, 0x00000000, 0x00086F50},
    {lbl_1_rodata_153C, 0x4009AC90, 0x00000000, 0x00059FFC},
    {lbl_1_rodata_1550, 0x4000E7B8, 0x00000000, 0x00006DB8},
    {lbl_1_rodata_1564, 0x4008726C, 0x00000000, 0x00046644},
    {lbl_1_rodata_1578, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_158C, 0x400A53A0, 0x00000000, 0x000630CC},
    {lbl_1_rodata_15A4, 0x400D6FAC, 0x00000000, 0x0007DF0C},
    {lbl_1_rodata_15BC, 0x40044700, 0x00000000, 0x00029814},
    {lbl_1_rodata_15D4, 0x4001C324, 0x00000000, 0x0000F15C},
    {lbl_1_rodata_15EC, 0x400886A4, 0x00000000, 0x0004B898},
    {lbl_1_rodata_1604, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_161C, 0x40022B8C, 0x00000000, 0x00012974},
    {lbl_1_rodata_1634, 0x40063D64, 0x00000000, 0x00034018},
    {lbl_1_rodata_164C, 0x4001C110, 0x00000000, 0x0000C51C},
    {lbl_1_rodata_1664, 0x40076714, 0x00000000, 0x0004493C},
    {lbl_1_rodata_167C, 0x4001D77C, 0x00000000, 0x00014104},
    {lbl_1_rodata_1694, 0x400103C0, 0x00000000, 0x00009A1C},
    {lbl_1_rodata_16AC, 0x40117B00, 0x00000000, 0x000A6F84},
    {lbl_1_rodata_16C0, 0x4006BCEC, 0x00000000, 0x00040324},
    {lbl_1_rodata_16D4, 0x400D98F8, 0x00000000, 0x0007FB74},
    {lbl_1_rodata_16E8, 0x40093A58, 0x00000000, 0x00058A8C},
    {lbl_1_rodata_16FC, 0x4000E7B8, 0x00000000, 0x00006DB8},
    {lbl_1_rodata_1710, 0x4007CFC8, 0x00000000, 0x00040EC8},
    {lbl_1_rodata_1724, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1738, 0x400AB488, 0x00000000, 0x000661EC},
    {lbl_1_rodata_1750, 0x400E19AC, 0x00000000, 0x000845D0},
    {lbl_1_rodata_1768, 0x4003FADC, 0x00000000, 0x00026A5C},
    {lbl_1_rodata_1780, 0x4001999C, 0x00000000, 0x0000DA24},
    {lbl_1_rodata_1798, 0x4007BA70, 0x00000000, 0x00044304},
    {lbl_1_rodata_17B0, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_17C8, 0x40016644, 0x00000000, 0x0000A0DC},
    {lbl_1_rodata_17E0, 0x4005C0D0, 0x00000000, 0x0002FB84},
    {lbl_1_rodata_17F8, 0x4001F4FC, 0x00000000, 0x0000E1F0},
    {lbl_1_rodata_1810, 0x400709A4, 0x00000000, 0x00044690},
    {lbl_1_rodata_1828, 0x40018B54, 0x00000000, 0x00012A70},
    {lbl_1_rodata_1840, 0x4000D540, 0x00000000, 0x00009CC0},
    {lbl_1_rodata_1858, 0x40107C04, 0x00000000, 0x0009D8F4},
    {lbl_1_rodata_186C, 0x400B8928, 0x00000000, 0x00074F60},
    {lbl_1_rodata_1880, 0x40151EC8, 0x00000000, 0x000C9210},
    {lbl_1_rodata_1894, 0x400A1FFC, 0x00000000, 0x00062E00},
    {lbl_1_rodata_18A8, 0x400168E4, 0x00000000, 0x0000AF00},
    {lbl_1_rodata_18BC, 0x400DD0B8, 0x00000000, 0x00078630},
    {lbl_1_rodata_18D0, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_18E4, 0x400A4474, 0x00000000, 0x0005F184},
    {lbl_1_rodata_18FC, 0x400D4484, 0x00000000, 0x0007D28C},
    {lbl_1_rodata_1914, 0x4008874C, 0x00000000, 0x00057EDC},
    {lbl_1_rodata_192C, 0x4002F2D8, 0x00000000, 0x0001BCEC},
    {lbl_1_rodata_1944, 0x400CCDA4, 0x00000000, 0x00071998},
    {lbl_1_rodata_195C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_1974, 0x4003275C, 0x00000000, 0x0001A2A0},
    {lbl_1_rodata_198C, 0x40089B0C, 0x00000000, 0x000497A4},
    {lbl_1_rodata_19A4, 0x4004B5A0, 0x00000000, 0x000285D0},
    {lbl_1_rodata_19BC, 0x400853B4, 0x00000000, 0x0005016C},
    {lbl_1_rodata_19D4, 0x40020F10, 0x00000000, 0x000147E0},
    {lbl_1_rodata_19EC, 0x400124A0, 0x00000000, 0x0000C3F4},
    {lbl_1_rodata_1A04, 0x400F9290, 0x00000000, 0x00096FD0},
    {lbl_1_rodata_1A18, 0x4006B574, 0x00000000, 0x0003CF38},
    {lbl_1_rodata_1A2C, 0x400EE1BC, 0x00000000, 0x00087D8C},
    {lbl_1_rodata_1A40, 0x400AB2C4, 0x00000000, 0x00068094},
    {lbl_1_rodata_1A54, 0x40010A54, 0x00000000, 0x00007F68},
    {lbl_1_rodata_1A68, 0x400E1784, 0x00000000, 0x0007F724},
    {lbl_1_rodata_1A7C, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1A90, 0x40091F94, 0x00000000, 0x00056A60},
    {lbl_1_rodata_1AA8, 0x400BE518, 0x00000000, 0x00073388},
    {lbl_1_rodata_1AC0, 0x40047DD8, 0x00000000, 0x00029650},
    {lbl_1_rodata_1AD8, 0x4001C698, 0x00000000, 0x0000E3C8},
    {lbl_1_rodata_1AF0, 0x40086AF0, 0x00000000, 0x00047900},
    {lbl_1_rodata_1B08, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_1B20, 0x400308B8, 0x00000000, 0x0001A5FC},
    {lbl_1_rodata_1B38, 0x40076A98, 0x00000000, 0x0003FAD4},
    {lbl_1_rodata_1B50, 0x40056B08, 0x00000000, 0x000305E4},
    {lbl_1_rodata_1B68, 0x4007A8D4, 0x00000000, 0x000499BC},
    {lbl_1_rodata_1B80, 0x4001F64C, 0x00000000, 0x00017088},
    {lbl_1_rodata_1B98, 0x40012BE0, 0x00000000, 0x0000CC14},
    {lbl_1_rodata_1BB0, 0x400E6588, 0x00000000, 0x0008F334},
    {lbl_1_rodata_1BC4, 0x40067440, 0x00000000, 0x0003F104},
    {lbl_1_rodata_1BD8, 0x400DE890, 0x00000000, 0x00084AB0},
    {lbl_1_rodata_1BEC, 0x40092E84, 0x00000000, 0x0005A534},
    {lbl_1_rodata_1C00, 0x4000FC7C, 0x00000000, 0x00008638},
    {lbl_1_rodata_1C14, 0x400BE42C, 0x00000000, 0x0006D45C},
    {lbl_1_rodata_1C28, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1C3C, 0x4008E150, 0x00000000, 0x000578B0},
    {lbl_1_rodata_1C54, 0x400BA6DC, 0x00000000, 0x0007140C},
    {lbl_1_rodata_1C6C, 0x400454DC, 0x00000000, 0x00029F28},
    {lbl_1_rodata_1C84, 0x40020BD4, 0x00000000, 0x00012240},
    {lbl_1_rodata_1C9C, 0x40088D90, 0x00000000, 0x0004D564},
    {lbl_1_rodata_1CB4, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_1CCC, 0x40035530, 0x00000000, 0x0001D674},
    {lbl_1_rodata_1CE4, 0x40093360, 0x00000000, 0x000538BC},
    {lbl_1_rodata_1CFC, 0x40024AAC, 0x00000000, 0x00013A1C},
    {lbl_1_rodata_1D14, 0x40073F90, 0x00000000, 0x00045BD0},
    {lbl_1_rodata_1D2C, 0x40020FDC, 0x00000000, 0x00017938},
    {lbl_1_rodata_1D44, 0x4000DFC0, 0x00000000, 0x0000A1FC},
    {lbl_1_rodata_1D5C, 0x40104EE0, 0x00000000, 0x0009854C},
    {lbl_1_rodata_1D70, 0x4009AEF8, 0x00000000, 0x0005A6AC},
    {lbl_1_rodata_1D84, 0x40119934, 0x00000000, 0x0009E218},
    {lbl_1_rodata_1D98, 0x400A1054, 0x00000000, 0x0005F8A4},
    {lbl_1_rodata_1DAC, 0x400134A4, 0x00000000, 0x00009148},
    {lbl_1_rodata_1DC0, 0x40093E94, 0x00000000, 0x00048400},
    {lbl_1_rodata_1DD4, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1DE8, 0x400A18B4, 0x00000000, 0x0005CD34},
    {lbl_1_rodata_1E00, 0x400C7D2C, 0x00000000, 0x00070F4C},
    {lbl_1_rodata_1E18, 0x4007BD40, 0x00000000, 0x000495C0},
    {lbl_1_rodata_1E30, 0x400454C4, 0x00000000, 0x00023B4C},
    {lbl_1_rodata_1E48, 0x400B3964, 0x00000000, 0x0006004C},
    {lbl_1_rodata_1E60, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_1E78, 0x40024D38, 0x00000000, 0x0001112C},
    {lbl_1_rodata_1E90, 0x40067F14, 0x00000000, 0x00032FC0},
    {lbl_1_rodata_1EA8, 0x40026204, 0x00000000, 0x000113EC},
    {lbl_1_rodata_1EC0, 0x4008892C, 0x00000000, 0x000514F0},
    {lbl_1_rodata_1ED8, 0x400195B0, 0x00000000, 0x0000F888},
    {lbl_1_rodata_1EF0, 0x4000E380, 0x00000000, 0x00009378},
    {lbl_1_rodata_1F08, 0x400EF6F4, 0x00000000, 0x00087E20},
    {lbl_1_rodata_1F1C, 0x40072704, 0x00000000, 0x000451F4},
    {lbl_1_rodata_1F30, 0x400EBFF4, 0x00000000, 0x00087764},
    {lbl_1_rodata_1F44, 0x40089EA0, 0x00000000, 0x00052F04},
    {lbl_1_rodata_1F58, 0x400141B4, 0x00000000, 0x0000A2C8},
    {lbl_1_rodata_1F6C, 0x40094FF8, 0x00000000, 0x0004F18C},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1F94, 0x4009616C, 0x00000000, 0x00052220},
    {lbl_1_rodata_1FAC, 0x400C5080, 0x00000000, 0x0006ED60},
    {lbl_1_rodata_1FC4, 0x4005176C, 0x00000000, 0x00030F20},
    {lbl_1_rodata_1FDC, 0x4001DED8, 0x00000000, 0x0000F9A0},
    {lbl_1_rodata_1FF4, 0x40098430, 0x00000000, 0x00052CC8},
    {lbl_1_rodata_200C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2024, 0x40024050, 0x00000000, 0x00012908},
    {lbl_1_rodata_203C, 0x4006A1CC, 0x00000000, 0x00038C18},
    {lbl_1_rodata_2054, 0x40026AA8, 0x00000000, 0x00011794},
    {lbl_1_rodata_206C, 0x40070630, 0x00000000, 0x000434F4},
    {lbl_1_rodata_2084, 0x40015CE0, 0x00000000, 0x0000E0D0},
    {lbl_1_rodata_209C, 0x40010700, 0x00000000, 0x00009E1C},
    {lbl_1_rodata_20B4, 0x40154778, 0x00000000, 0x0008BE88},
    {lbl_1_rodata_20C8, 0x4007F278, 0x00000000, 0x00035D84},
    {lbl_1_rodata_20DC, 0x4012CA1C, 0x00000000, 0x000861DC},
    {lbl_1_rodata_20F0, 0x400A8F9C, 0x00000000, 0x0004CE10},
    {lbl_1_rodata_2104, 0x40019014, 0x00000000, 0x0000AF08},
    {lbl_1_rodata_2118, 0x400BBE68, 0x00000000, 0x0004AB50},
    {lbl_1_rodata_212C, 0x400338F0, 0x00000000, 0x0001FCB0},
    {lbl_1_rodata_2140, 0x400C4404, 0x00000000, 0x0004C890},
    {lbl_1_rodata_2158, 0x401286C4, 0x00000000, 0x00078574},
    {lbl_1_rodata_2170, 0x4007973C, 0x00000000, 0x0003346C},
    {lbl_1_rodata_2188, 0x40031838, 0x00000000, 0x000141E8},
    {lbl_1_rodata_21A0, 0x400C2CC0, 0x00000000, 0x000536A8},
    {lbl_1_rodata_21B8, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_21D0, 0x40034FAC, 0x00000000, 0x00014150},
    {lbl_1_rodata_21E8, 0x400943AC, 0x00000000, 0x0003BBA8},
    {lbl_1_rodata_2200, 0x400224C0, 0x00000000, 0x0000CC9C},
    {lbl_1_rodata_2218, 0x400A5C48, 0x00000000, 0x0004B294},
    {lbl_1_rodata_2230, 0x40019EF0, 0x00000000, 0x00010BDC},
    {lbl_1_rodata_2248, 0x400118C0, 0x00000000, 0x0000A8D8},
    {lbl_1_rodata_2260, 0x40126028, 0x00000000, 0x000AD834},
    {lbl_1_rodata_2274, 0x4008C048, 0x00000000, 0x00052820},
    {lbl_1_rodata_2288, 0x4013496C, 0x00000000, 0x000B4438},
    {lbl_1_rodata_229C, 0x400AB858, 0x00000000, 0x000691C4},
    {lbl_1_rodata_22B0, 0x400190E8, 0x00000000, 0x0000E258},
    {lbl_1_rodata_22C4, 0x400A9A90, 0x00000000, 0x0005FFE0},
    {lbl_1_rodata_22D8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_22EC, 0x400B5FB8, 0x00000000, 0x0006A600},
    {lbl_1_rodata_2304, 0x400F0C14, 0x00000000, 0x0008C2A0},
    {lbl_1_rodata_231C, 0x400622F8, 0x00000000, 0x0003919C},
    {lbl_1_rodata_2334, 0x400267BC, 0x00000000, 0x00014688},
    {lbl_1_rodata_234C, 0x400B9E90, 0x00000000, 0x00067DE4},
    {lbl_1_rodata_2364, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_237C, 0x40028F0C, 0x00000000, 0x00017220},
    {lbl_1_rodata_2394, 0x40078D24, 0x00000000, 0x00044850},
    {lbl_1_rodata_23AC, 0x40027374, 0x00000000, 0x00012BB8},
    {lbl_1_rodata_23C4, 0x4008B838, 0x00000000, 0x000552E4},
    {lbl_1_rodata_23DC, 0x40016320, 0x00000000, 0x0000E1B8},
    {lbl_1_rodata_23F4, 0x40012C40, 0x00000000, 0x0000B6EC},
    {lbl_1_rodata_240C, 0x400FF80C, 0x00000000, 0x0008E938},
    {lbl_1_rodata_2420, 0x40070840, 0x00000000, 0x0003FCE8},
    {lbl_1_rodata_2434, 0x4010B5D0, 0x00000000, 0x00090E6C},
    {lbl_1_rodata_2448, 0x400997A4, 0x00000000, 0x00053410},
    {lbl_1_rodata_245C, 0x400166A4, 0x00000000, 0x0000A878},
    {lbl_1_rodata_2470, 0x4008C894, 0x00000000, 0x00044A10},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_2498, 0x400A2460, 0x00000000, 0x00056EEC},
    {lbl_1_rodata_24B0, 0x400CCDD4, 0x00000000, 0x00071018},
    {lbl_1_rodata_24C8, 0x4004E51C, 0x00000000, 0x0002BC28},
    {lbl_1_rodata_24E0, 0x40023648, 0x00000000, 0x00012090},
    {lbl_1_rodata_24F8, 0x400A5574, 0x00000000, 0x000547BC},
    {lbl_1_rodata_2510, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2528, 0x40025C04, 0x00000000, 0x00011890},
    {lbl_1_rodata_2540, 0x40060CEC, 0x00000000, 0x0002FA5C},
    {lbl_1_rodata_2558, 0x40023608, 0x00000000, 0x0000EFA0},
    {lbl_1_rodata_2570, 0x4007F2C4, 0x00000000, 0x00044BE0},
    {lbl_1_rodata_2588, 0x4001D724, 0x00000000, 0x00012518},
    {lbl_1_rodata_25A0, 0x40012F00, 0x00000000, 0x0000AB08},
    {lbl_1_rodata_25B8, 0x40116F08, 0x00000000, 0x000AD338},
    {lbl_1_rodata_25CC, 0x40084C24, 0x00000000, 0x00053D9C},
    {lbl_1_rodata_25E0, 0x40135798, 0x00000000, 0x000B8394},
    {lbl_1_rodata_25F4, 0x400AADDC, 0x00000000, 0x0006CCDC},
    {lbl_1_rodata_2608, 0x4001C178, 0x00000000, 0x0000F070},
    {lbl_1_rodata_261C, 0x4009FD44, 0x00000000, 0x00059D14},
    {lbl_1_rodata_2630, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_2644, 0x400A7920, 0x00000000, 0x00065C10},
    {lbl_1_rodata_265C, 0x400E9BD8, 0x00000000, 0x0008FE10},
    {lbl_1_rodata_2674, 0x40060FF0, 0x00000000, 0x0003D40C},
    {lbl_1_rodata_268C, 0x40021838, 0x00000000, 0x000124B0},
    {lbl_1_rodata_26A4, 0x400AB3E4, 0x00000000, 0x00061F70},
    {lbl_1_rodata_26BC, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_26D4, 0x4002D7C4, 0x00000000, 0x00018638},
    {lbl_1_rodata_26EC, 0x40074AAC, 0x00000000, 0x00041518},
    {lbl_1_rodata_2704, 0x40024294, 0x00000000, 0x00011B30},
    {lbl_1_rodata_271C, 0x4008A608, 0x00000000, 0x000585B8},
    {lbl_1_rodata_2734, 0x40017DE0, 0x00000000, 0x00010298},
    {lbl_1_rodata_274C, 0x4000F020, 0x00000000, 0x00008B10},
    {lbl_1_rodata_2764, 0x400DAAA8, 0x00000000, 0x0007AA20},
    {lbl_1_rodata_2778, 0x40061E2C, 0x00000000, 0x0003B288},
    {lbl_1_rodata_278C, 0x400F2DE8, 0x00000000, 0x0009193C},
    {lbl_1_rodata_27A0, 0x4008BA4C, 0x00000000, 0x0004EDD0},
    {lbl_1_rodata_27B4, 0x4001759C, 0x00000000, 0x0000CE34},
    {lbl_1_rodata_27C8, 0x400902F4, 0x00000000, 0x00048998},
    {lbl_1_rodata_27DC, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_27F0, 0x40083B34, 0x00000000, 0x0004AA34},
    {lbl_1_rodata_2808, 0x400B496C, 0x00000000, 0x00065A40},
    {lbl_1_rodata_2820, 0x40044404, 0x00000000, 0x00029CC4},
    {lbl_1_rodata_2838, 0x4001BFB0, 0x00000000, 0x0000F618},
    {lbl_1_rodata_2850, 0x40090A20, 0x00000000, 0x00051B98},
    {lbl_1_rodata_2868, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2880, 0x4002B970, 0x00000000, 0x00015D70},
    {lbl_1_rodata_2898, 0x4006C460, 0x00000000, 0x00036D80},
    {lbl_1_rodata_28B0, 0x4001D874, 0x00000000, 0x0000C284},
    {lbl_1_rodata_28C8, 0x40071AF0, 0x00000000, 0x00040218},
    {lbl_1_rodata_28E0, 0x4001ABB8, 0x00000000, 0x0001390C},
    {lbl_1_rodata_28F8, 0x4000D5C0, 0x00000000, 0x00008CF0},
    {lbl_1_rodata_2910, 0x40101EE8, 0x00000000, 0x000961F4},
    {lbl_1_rodata_2924, 0x40079200, 0x00000000, 0x00048440},
    {lbl_1_rodata_2938, 0x400E8CEC, 0x00000000, 0x0008A344},
    {lbl_1_rodata_294C, 0x4009BE4C, 0x00000000, 0x0005D480},
    {lbl_1_rodata_2960, 0x4000D450, 0x00000000, 0x000074AC},
    {lbl_1_rodata_2974, 0x40076AB0, 0x00000000, 0x0003CB84},
    {lbl_1_rodata_2988, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_299C, 0x400950D0, 0x00000000, 0x00055BA4},
    {lbl_1_rodata_29B4, 0x400D9190, 0x00000000, 0x0007EA58},
    {lbl_1_rodata_29CC, 0x4004C4EC, 0x00000000, 0x0002D318},
    {lbl_1_rodata_29E4, 0x4001D8DC, 0x00000000, 0x0000FA14},
    {lbl_1_rodata_29FC, 0x400865F0, 0x00000000, 0x0004B7A8},
    {lbl_1_rodata_2A14, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2A2C, 0x40024D68, 0x00000000, 0x00012400},
    {lbl_1_rodata_2A44, 0x4004F114, 0x00000000, 0x00027734},
    {lbl_1_rodata_2A5C, 0x4001E6D4, 0x00000000, 0x0000DF94},
    {lbl_1_rodata_2A74, 0x4007E95C, 0x00000000, 0x0004B314},
    {lbl_1_rodata_2A8C, 0x40022D3C, 0x00000000, 0x00019184},
    {lbl_1_rodata_2AA4, 0x4000FD40, 0x00000000, 0x0000B93C},
    {lbl_1_rodata_2ABC, 0x4010D3F0, 0x00000000, 0x00096260},
    {lbl_1_rodata_2AD0, 0x40070C74, 0x00000000, 0x00040B74},
    {lbl_1_rodata_2AE4, 0x4010A880, 0x00000000, 0x0008BDC4},
    {lbl_1_rodata_2AF8, 0x4008BAF0, 0x00000000, 0x0004FA1C},
    {lbl_1_rodata_2B0C, 0x4001396C, 0x00000000, 0x00009320},
    {lbl_1_rodata_2B20, 0x4008AF98, 0x00000000, 0x000421C4},
    {lbl_1_rodata_2B34, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_2B48, 0x4008CB38, 0x00000000, 0x0004AE80},
    {lbl_1_rodata_2B60, 0x400E3B50, 0x00000000, 0x0007ECDC},
    {lbl_1_rodata_2B78, 0x4004EE38, 0x00000000, 0x0002CF3C},
    {lbl_1_rodata_2B90, 0x40021FD0, 0x00000000, 0x0001206C},
    {lbl_1_rodata_2BA8, 0x400A16DC, 0x00000000, 0x000501F8},
    {lbl_1_rodata_2BC0, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2BD8, 0x4002324C, 0x00000000, 0x0000FFB0},
    {lbl_1_rodata_2BF0, 0x400670B8, 0x00000000, 0x00030B0C},
    {lbl_1_rodata_2C08, 0x40020080, 0x00000000, 0x0000DC28},
    {lbl_1_rodata_2C20, 0x40072C38, 0x00000000, 0x0004023C},
    {lbl_1_rodata_2C38, 0x4001881C, 0x00000000, 0x00010B50},
    {lbl_1_rodata_2C50, 0x4000F500, 0x00000000, 0x00009DA8},
    {lbl_1_rodata_2C68, 0x4012453C, 0x00000000, 0x000A4390},
    {lbl_1_rodata_2C7C, 0x40082A20, 0x00000000, 0x000450B4},
    {lbl_1_rodata_2C90, 0x40110178, 0x00000000, 0x000931C8},
    {lbl_1_rodata_2CA4, 0x400A61F8, 0x00000000, 0x0005ABAC},
    {lbl_1_rodata_2CB8, 0x40014210, 0x00000000, 0x00009180},
    {lbl_1_rodata_2CCC, 0x400BE25C, 0x00000000, 0x000631D8},
    {lbl_1_rodata_2CE0, 0x4004F674, 0x00000000, 0x0002E878},
    {lbl_1_rodata_2CF4, 0x400B3CE8, 0x00000000, 0x00061BE4},
    {lbl_1_rodata_2D0C, 0x400DFDF0, 0x00000000, 0x0007AF30},
    {lbl_1_rodata_2D24, 0x40058578, 0x00000000, 0x0002E368},
    {lbl_1_rodata_2D3C, 0x40023878, 0x00000000, 0x00011438},
    {lbl_1_rodata_2D54, 0x4009152C, 0x00000000, 0x00048EC4},
    {lbl_1_rodata_2D6C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2D84, 0x4002D680, 0x00000000, 0x000171F0},
    {lbl_1_rodata_2D9C, 0x400937B4, 0x00000000, 0x0004E564},
    {lbl_1_rodata_2DB4, 0x40027844, 0x00000000, 0x00011304},
    {lbl_1_rodata_2DCC, 0x40084428, 0x00000000, 0x00048514},
    {lbl_1_rodata_2DE4, 0x400176FC, 0x00000000, 0x0000FEA4},
    {lbl_1_rodata_2DFC, 0x4000F500, 0x00000000, 0x00009D94},
    {lbl_1_rodata_2C68, 0x4012453C, 0x00000000, 0x000A4390},
    {lbl_1_rodata_2C7C, 0x40082A20, 0x00000000, 0x000450B4},
    {lbl_1_rodata_2C90, 0x40110178, 0x00000000, 0x000931C8},
    {lbl_1_rodata_2CA4, 0x400A61F8, 0x00000000, 0x0005ABAC},
    {lbl_1_rodata_2CB8, 0x40014210, 0x00000000, 0x00009180},
    {lbl_1_rodata_2CCC, 0x400BE25C, 0x00000000, 0x000631D8},
    {lbl_1_rodata_2CE0, 0x4004F674, 0x00000000, 0x0002E878},
    {lbl_1_rodata_2CF4, 0x400B3CE8, 0x00000000, 0x00061BE4},
    {lbl_1_rodata_2D0C, 0x400DFDF0, 0x00000000, 0x0007AF30},
    {lbl_1_rodata_2D24, 0x40058578, 0x00000000, 0x0002E368},
    {lbl_1_rodata_2D3C, 0x40023878, 0x00000000, 0x00011438},
    {lbl_1_rodata_2D54, 0x4009152C, 0x00000000, 0x00048EC4},
    {lbl_1_rodata_2D6C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2D84, 0x4002D680, 0x00000000, 0x000171F0},
    {lbl_1_rodata_2D9C, 0x400937B4, 0x00000000, 0x0004E564},
    {lbl_1_rodata_2DB4, 0x40027844, 0x00000000, 0x00011304},
    {lbl_1_rodata_2DCC, 0x40084428, 0x00000000, 0x00048514},
    {lbl_1_rodata_2E14, 0x400176FC, 0x00000000, 0x0000FEA4},
    {lbl_1_rodata_2E2C, 0x4000F500, 0x00000000, 0x00009D90},
    {lbl_1_rodata_2C68, 0x4012453C, 0x00000000, 0x000A4390},
    {lbl_1_rodata_2C7C, 0x40082A20, 0x00000000, 0x000450B4},
    {lbl_1_rodata_2C90, 0x40110178, 0x00000000, 0x000931C8},
    {lbl_1_rodata_2CA4, 0x400A61F8, 0x00000000, 0x0005ABAC},
    {lbl_1_rodata_2CB8, 0x40014210, 0x00000000, 0x00009180},
    {lbl_1_rodata_2CCC, 0x400BE25C, 0x00000000, 0x000631D8},
    {lbl_1_rodata_2CE0, 0x4004F674, 0x00000000, 0x0002E878},
    {lbl_1_rodata_2CF4, 0x400B3CE8, 0x00000000, 0x00061BE4},
    {lbl_1_rodata_2D0C, 0x400DFDF0, 0x00000000, 0x0007AF30},
    {lbl_1_rodata_2D24, 0x40058578, 0x00000000, 0x0002E368},
    {lbl_1_rodata_2D3C, 0x40023878, 0x00000000, 0x00011438},
    {lbl_1_rodata_2D54, 0x4009152C, 0x00000000, 0x00048EC4},
    {lbl_1_rodata_2D6C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2D84, 0x4002D680, 0x00000000, 0x000171F0},
    {lbl_1_rodata_2D9C, 0x400937B4, 0x00000000, 0x0004E564},
    {lbl_1_rodata_2DB4, 0x40027844, 0x00000000, 0x00011304},
    {lbl_1_rodata_2DCC, 0x40084428, 0x00000000, 0x00048514},
    {lbl_1_rodata_2E44, 0x40011810, 0x00000000, 0x0000BAFC},
    {lbl_1_rodata_2E5C, 0x4000BC80, 0x00000000, 0x00007764},
    {lbl_1_rodata_2E74, 0x4011C51C, 0x00000000, 0x000A1BA4},
    {lbl_1_rodata_2E88, 0x400732B8, 0x00000000, 0x000432D8},
    {lbl_1_rodata_2E9C, 0x400ECA2C, 0x00000000, 0x00083E64},
    {lbl_1_rodata_2EB0, 0x4009A664, 0x00000000, 0x00057A54},
    {lbl_1_rodata_2EC4, 0x4000DEF8, 0x00000000, 0x000066DC},
    {lbl_1_rodata_2ED8, 0x400956A8, 0x00000000, 0x0004AAD8},
    {lbl_1_rodata_2EEC, 0x4009C7A4, 0x00000000, 0x0005C22C},
    {lbl_1_rodata_2F00, 0x400AE2B0, 0x00000000, 0x000609E0},
    {lbl_1_rodata_2F18, 0x400D85CC, 0x00000000, 0x00079608},
    {lbl_1_rodata_2F30, 0x4004BE48, 0x00000000, 0x0002BA30},
    {lbl_1_rodata_2F48, 0x4001A5AC, 0x00000000, 0x0000D794},
    {lbl_1_rodata_2F60, 0x40090514, 0x00000000, 0x0004AA8C},
    {lbl_1_rodata_2F78, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2F90, 0x400240C4, 0x00000000, 0x00011A08},
    {lbl_1_rodata_2FA8, 0x400735D8, 0x00000000, 0x0003972C},
    {lbl_1_rodata_2FC0, 0x400201E4, 0x00000000, 0x0000E91C},
    {lbl_1_rodata_2FD8, 0x40075470, 0x00000000, 0x00042EC8},
    {lbl_1_rodata_2FF0, 0x40011810, 0x00000000, 0x0000BB1C},
    {lbl_1_rodata_3008, 0x4000BC80, 0x00000000, 0x00007784},
    {lbl_1_rodata_2E74, 0x4011C51C, 0x00000000, 0x000A1BA4},
    {lbl_1_rodata_2E88, 0x400732B8, 0x00000000, 0x000432D8},
    {lbl_1_rodata_2E9C, 0x400ECA2C, 0x00000000, 0x00083E64},
    {lbl_1_rodata_2EB0, 0x4009A664, 0x00000000, 0x00057A54},
    {lbl_1_rodata_2EC4, 0x4000DEF8, 0x00000000, 0x000066DC},
    {lbl_1_rodata_2ED8, 0x400956A8, 0x00000000, 0x0004AAD8},
    {lbl_1_rodata_2EEC, 0x4009C7A4, 0x00000000, 0x0005C22C},
    {lbl_1_rodata_2F00, 0x400AE2B0, 0x00000000, 0x000609E0},
    {lbl_1_rodata_2F18, 0x400D85CC, 0x00000000, 0x00079608},
    {lbl_1_rodata_2F30, 0x4004BE48, 0x00000000, 0x0002BA30},
    {lbl_1_rodata_2F48, 0x4001A5AC, 0x00000000, 0x0000D794},
    {lbl_1_rodata_2F60, 0x40090514, 0x00000000, 0x0004AA8C},
    {lbl_1_rodata_2F78, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2F90, 0x400240C4, 0x00000000, 0x00011A08},
    {lbl_1_rodata_2FA8, 0x400735D8, 0x00000000, 0x0003972C},
    {lbl_1_rodata_2FC0, 0x400201E4, 0x00000000, 0x0000E91C},
    {lbl_1_rodata_2FD8, 0x40075470, 0x00000000, 0x00042EC8},
    {lbl_1_rodata_3020, 0x40011810, 0x00000000, 0x0000BB48},
    {lbl_1_rodata_3038, 0x4000BC80, 0x00000000, 0x000077B0},
    {lbl_1_rodata_2E74, 0x4011C51C, 0x00000000, 0x000A1BA4},
    {lbl_1_rodata_2E88, 0x400732B8, 0x00000000, 0x000432D8},
    {lbl_1_rodata_2E9C, 0x400ECA2C, 0x00000000, 0x00083E64},
    {lbl_1_rodata_2EB0, 0x4009A664, 0x00000000, 0x00057A54},
    {lbl_1_rodata_2EC4, 0x4000DEF8, 0x00000000, 0x000066DC},
    {lbl_1_rodata_2ED8, 0x400956A8, 0x00000000, 0x0004AAD8},
    {lbl_1_rodata_2EEC, 0x4009C7A4, 0x00000000, 0x0005C22C},
    {lbl_1_rodata_2F00, 0x400AE2B0, 0x00000000, 0x000609E0},
    {lbl_1_rodata_2F18, 0x400D85CC, 0x00000000, 0x00079608},
    {lbl_1_rodata_2F30, 0x4004BE48, 0x00000000, 0x0002BA30},
    {lbl_1_rodata_2F48, 0x4001A5AC, 0x00000000, 0x0000D794},
    {lbl_1_rodata_2F60, 0x40090514, 0x00000000, 0x0004AA8C},
    {lbl_1_rodata_2F78, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2F90, 0x400240C4, 0x00000000, 0x00011A08},
    {lbl_1_rodata_2FA8, 0x400735D8, 0x00000000, 0x0003972C},
    {lbl_1_rodata_2FC0, 0x400201E4, 0x00000000, 0x0000E91C},
    {lbl_1_rodata_2FD8, 0x40075470, 0x00000000, 0x00042EC8},
    {lbl_1_rodata_3050, 0x4001A71C, 0x00000000, 0x0001128C},
    {lbl_1_rodata_3068, 0x4000F8E0, 0x00000000, 0x000098E4},
    {lbl_1_rodata_3080, 0x400D9004, 0x00000000, 0x0007DC34},
    {lbl_1_rodata_3094, 0x4005828C, 0x00000000, 0x000318E8},
    {lbl_1_rodata_30A8, 0x400E77C8, 0x00000000, 0x00084D44},
    {lbl_1_rodata_30BC, 0x40071294, 0x00000000, 0x0003E188},
    {lbl_1_rodata_30D0, 0x40011370, 0x00000000, 0x00008FA8},
    {lbl_1_rodata_30E4, 0x40077E54, 0x00000000, 0x0003C340},
    {lbl_1_rodata_30F8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_310C, 0x40089DEC, 0x00000000, 0x0004C700},
    {lbl_1_rodata_3124, 0x400B74D8, 0x00000000, 0x00069C9C},
    {lbl_1_rodata_313C, 0x4003EDC8, 0x00000000, 0x00021E78},
    {lbl_1_rodata_3154, 0x4001D924, 0x00000000, 0x0000E02C},
    {lbl_1_rodata_316C, 0x40084518, 0x00000000, 0x0004750C},
    {lbl_1_rodata_3184, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_319C, 0x40020AD0, 0x00000000, 0x0000F47C},
    {lbl_1_rodata_31B4, 0x4005013C, 0x00000000, 0x000274E4},
    {lbl_1_rodata_31CC, 0x40021F9C, 0x00000000, 0x0000FB58},
    {lbl_1_rodata_31E4, 0x4005E514, 0x00000000, 0x00033954},
    {lbl_1_rodata_31FC, 0x4001CE58, 0x00000000, 0x000132DC},
    {lbl_1_rodata_3214, 0x4000FE80, 0x00000000, 0x0000A0FC},
    {lbl_1_rodata_322C, 0x400F38AC, 0x00000000, 0x000848BC},
    {lbl_1_rodata_3240, 0x4006DC14, 0x00000000, 0x0003DA58},
    {lbl_1_rodata_3254, 0x401076B0, 0x00000000, 0x00097430},
    {lbl_1_rodata_3268, 0x40089EA0, 0x00000000, 0x0004D280},
    {lbl_1_rodata_327C, 0x400141B4, 0x00000000, 0x00009724},
    {lbl_1_rodata_3290, 0x4009A9F4, 0x00000000, 0x0004C6B4},
    {lbl_1_rodata_32A4, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_32B8, 0x400A0788, 0x00000000, 0x00056398},
    {lbl_1_rodata_32D0, 0x400C9238, 0x00000000, 0x0006CF14},
    {lbl_1_rodata_32E8, 0x40055184, 0x00000000, 0x000303B4},
    {lbl_1_rodata_3300, 0x40027E0C, 0x00000000, 0x000144D4},
    {lbl_1_rodata_3318, 0x4009E0C0, 0x00000000, 0x00055EF0},
    {lbl_1_rodata_3330, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_3348, 0x4002CAC0, 0x00000000, 0x00015C1C},
    {lbl_1_rodata_3360, 0x4006D92C, 0x00000000, 0x00035D1C},
    {lbl_1_rodata_3378, 0x40026AA8, 0x00000000, 0x00010FC8},
    {lbl_1_rodata_3390, 0x40070630, 0x00000000, 0x0003F0AC},
    {lbl_1_rodata_33A8, 0x400195B0, 0x00000000, 0x0000F9DC},
    {lbl_1_rodata_33C0, 0x4000E380, 0x00000000, 0x0000961C},
    {lbl_1_rodata_1F08, 0x400EF6F4, 0x00000000, 0x00087E20},
    {lbl_1_rodata_1F1C, 0x40072704, 0x00000000, 0x000451F4},
    {lbl_1_rodata_1F30, 0x400EBFF4, 0x00000000, 0x00087764},
    {lbl_1_rodata_1F44, 0x40089EA0, 0x00000000, 0x00052F04},
    {lbl_1_rodata_1F58, 0x400141B4, 0x00000000, 0x0000A2C8},
    {lbl_1_rodata_1F6C, 0x40094FF8, 0x00000000, 0x0004F18C},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1F94, 0x4009616C, 0x00000000, 0x00052220},
    {lbl_1_rodata_1FAC, 0x400C5080, 0x00000000, 0x0006ED60},
    {lbl_1_rodata_1FC4, 0x4005176C, 0x00000000, 0x00030F20},
    {lbl_1_rodata_1FDC, 0x4001DED8, 0x00000000, 0x0000F9A0},
    {lbl_1_rodata_1FF4, 0x40098430, 0x00000000, 0x00052CC8},
    {lbl_1_rodata_200C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2024, 0x40024050, 0x00000000, 0x00012908},
    {lbl_1_rodata_203C, 0x4006A1CC, 0x00000000, 0x00038C18},
    {lbl_1_rodata_2054, 0x40026AA8, 0x00000000, 0x00011794},
    {lbl_1_rodata_206C, 0x40070630, 0x00000000, 0x000434F4},
    {lbl_1_rodata_33D8, 0x400195B0, 0x00000000, 0x0000F9BC},
    {lbl_1_rodata_33F0, 0x4000E380, 0x00000000, 0x00009368},
    {lbl_1_rodata_1F08, 0x400EF6F4, 0x00000000, 0x00087E20},
    {lbl_1_rodata_1F1C, 0x40072704, 0x00000000, 0x000451F4},
    {lbl_1_rodata_1F30, 0x400EBFF4, 0x00000000, 0x00087764},
    {lbl_1_rodata_1F44, 0x40089EA0, 0x00000000, 0x00052F04},
    {lbl_1_rodata_1F58, 0x400141B4, 0x00000000, 0x0000A2C8},
    {lbl_1_rodata_1F6C, 0x40094FF8, 0x00000000, 0x0004F18C},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1F94, 0x4009616C, 0x00000000, 0x00052220},
    {lbl_1_rodata_1FAC, 0x400C5080, 0x00000000, 0x0006ED60},
    {lbl_1_rodata_1FC4, 0x4005176C, 0x00000000, 0x00030F20},
    {lbl_1_rodata_1FDC, 0x4001DED8, 0x00000000, 0x0000F9A0},
    {lbl_1_rodata_1FF4, 0x40098430, 0x00000000, 0x00052CC8},
    {lbl_1_rodata_200C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2024, 0x40024050, 0x00000000, 0x00012908},
    {lbl_1_rodata_203C, 0x4006A1CC, 0x00000000, 0x00038C18},
    {lbl_1_rodata_2054, 0x40026AA8, 0x00000000, 0x00011794},
    {lbl_1_rodata_206C, 0x40070630, 0x00000000, 0x000434F4},
    {lbl_1_rodata_3408, 0x400195B0, 0x00000000, 0x0000F8B0},
    {lbl_1_rodata_3420, 0x4000E380, 0x00000000, 0x0000926C},
    {lbl_1_rodata_1F08, 0x400EF6F4, 0x00000000, 0x00087E20},
    {lbl_1_rodata_1F1C, 0x40072704, 0x00000000, 0x000451F4},
    {lbl_1_rodata_1F30, 0x400EBFF4, 0x00000000, 0x00087764},
    {lbl_1_rodata_1F44, 0x40089EA0, 0x00000000, 0x00052F04},
    {lbl_1_rodata_1F58, 0x400141B4, 0x00000000, 0x0000A2C8},
    {lbl_1_rodata_1F6C, 0x40094FF8, 0x00000000, 0x0004F18C},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1F94, 0x4009616C, 0x00000000, 0x00052220},
    {lbl_1_rodata_1FAC, 0x400C5080, 0x00000000, 0x0006ED60},
    {lbl_1_rodata_1FC4, 0x4005176C, 0x00000000, 0x00030F20},
    {lbl_1_rodata_1FDC, 0x4001DED8, 0x00000000, 0x0000F9A0},
    {lbl_1_rodata_1FF4, 0x40098430, 0x00000000, 0x00052CC8},
    {lbl_1_rodata_200C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2024, 0x40024050, 0x00000000, 0x00012908},
    {lbl_1_rodata_203C, 0x4006A1CC, 0x00000000, 0x00038C18},
    {lbl_1_rodata_2054, 0x40026AA8, 0x00000000, 0x00011794},
    {lbl_1_rodata_206C, 0x40070630, 0x00000000, 0x000434F4},
    {lbl_1_rodata_3438, 0x400195B0, 0x00000000, 0x0000F8B0},
    {lbl_1_rodata_3450, 0x4000E380, 0x00000000, 0x00009278},
    {lbl_1_rodata_1F08, 0x400EF6F4, 0x00000000, 0x00087E20},
    {lbl_1_rodata_1F1C, 0x40072704, 0x00000000, 0x000451F4},
    {lbl_1_rodata_1F30, 0x400EBFF4, 0x00000000, 0x00087764},
    {lbl_1_rodata_1F44, 0x40089EA0, 0x00000000, 0x00052F04},
    {lbl_1_rodata_1F58, 0x400141B4, 0x00000000, 0x0000A2C8},
    {lbl_1_rodata_1F6C, 0x40094FF8, 0x00000000, 0x0004F18C},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1F94, 0x4009616C, 0x00000000, 0x00052220},
    {lbl_1_rodata_1FAC, 0x400C5080, 0x00000000, 0x0006ED60},
    {lbl_1_rodata_1FC4, 0x4005176C, 0x00000000, 0x00030F20},
    {lbl_1_rodata_1FDC, 0x4001DED8, 0x00000000, 0x0000F9A0},
    {lbl_1_rodata_1FF4, 0x40098430, 0x00000000, 0x00052CC8},
    {lbl_1_rodata_200C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2024, 0x40024050, 0x00000000, 0x00012908},
    {lbl_1_rodata_203C, 0x4006A1CC, 0x00000000, 0x00038C18},
    {lbl_1_rodata_2054, 0x40026AA8, 0x00000000, 0x00011794},
    {lbl_1_rodata_206C, 0x40070630, 0x00000000, 0x000434F4},
    {lbl_1_rodata_3468, 0x400150EC, 0x00000000, 0x0000DD9C},
    {lbl_1_rodata_3480, 0x4000F000, 0x00000000, 0x00009BF8},
    {lbl_1_rodata_3498, 0x400EFFB8, 0x00000000, 0x0008D04C},
    {lbl_1_rodata_34AC, 0x4006C0A4, 0x00000000, 0x0004229C},
    {lbl_1_rodata_34C0, 0x401017BC, 0x00000000, 0x0009B64C},
    {lbl_1_rodata_34D4, 0x40090558, 0x00000000, 0x00058584},
    {lbl_1_rodata_34E8, 0x4000FC10, 0x00000000, 0x00008628},
    {lbl_1_rodata_34FC, 0x400A5928, 0x00000000, 0x0005A998},
    {lbl_1_rodata_3510, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_3524, 0x40091AB4, 0x00000000, 0x000547C8},
    {lbl_1_rodata_353C, 0x400C424C, 0x00000000, 0x00072464},
    {lbl_1_rodata_3554, 0x4004C1F0, 0x00000000, 0x0002ED08},
    {lbl_1_rodata_356C, 0x40021FE8, 0x00000000, 0x00012E2C},
    {lbl_1_rodata_3584, 0x400A2334, 0x00000000, 0x0005C0D0},
    {lbl_1_rodata_359C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_35B4, 0x4002E9C8, 0x00000000, 0x00019388},
    {lbl_1_rodata_35CC, 0x40077034, 0x00000000, 0x0004100C},
    {lbl_1_rodata_35E4, 0x400278B8, 0x00000000, 0x00012EBC},
    {lbl_1_rodata_35FC, 0x40075074, 0x00000000, 0x000467B0},
    {lbl_1_rodata_3614, 0x400150EC, 0x00000000, 0x0000DD6C},
    {lbl_1_rodata_362C, 0x4000F000, 0x00000000, 0x00009BCC},
    {lbl_1_rodata_3498, 0x400EFFB8, 0x00000000, 0x0008D04C},
    {lbl_1_rodata_34AC, 0x4006C0A4, 0x00000000, 0x0004229C},
    {lbl_1_rodata_34C0, 0x401017BC, 0x00000000, 0x0009B64C},
    {lbl_1_rodata_34D4, 0x40090558, 0x00000000, 0x00058584},
    {lbl_1_rodata_34E8, 0x4000FC10, 0x00000000, 0x00008628},
    {lbl_1_rodata_34FC, 0x400A5928, 0x00000000, 0x0005A998},
    {lbl_1_rodata_3510, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_3524, 0x40091AB4, 0x00000000, 0x000547C8},
    {lbl_1_rodata_353C, 0x400C424C, 0x00000000, 0x00072464},
    {lbl_1_rodata_3554, 0x4004C1F0, 0x00000000, 0x0002ED08},
    {lbl_1_rodata_356C, 0x40021FE8, 0x00000000, 0x00012E2C},
    {lbl_1_rodata_3584, 0x400A2334, 0x00000000, 0x0005C0D0},
    {lbl_1_rodata_359C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_35B4, 0x4002E9C8, 0x00000000, 0x00019388},
    {lbl_1_rodata_35CC, 0x40077034, 0x00000000, 0x0004100C},
    {lbl_1_rodata_35E4, 0x400278B8, 0x00000000, 0x00012EBC},
    {lbl_1_rodata_35FC, 0x40075074, 0x00000000, 0x000467B0},
    {lbl_1_rodata_3644, 0x400150EC, 0x00000000, 0x0000DD50},
    {lbl_1_rodata_365C, 0x4000F000, 0x00000000, 0x00009BAC},
    {lbl_1_rodata_3498, 0x400EFFB8, 0x00000000, 0x0008D04C},
    {lbl_1_rodata_34AC, 0x4006C0A4, 0x00000000, 0x0004229C},
    {lbl_1_rodata_34C0, 0x401017BC, 0x00000000, 0x0009B64C},
    {lbl_1_rodata_34D4, 0x40090558, 0x00000000, 0x00058584},
    {lbl_1_rodata_34E8, 0x4000FC10, 0x00000000, 0x00008628},
    {lbl_1_rodata_34FC, 0x400A5928, 0x00000000, 0x0005A998},
    {lbl_1_rodata_3510, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_3524, 0x40091AB4, 0x00000000, 0x000547C8},
    {lbl_1_rodata_353C, 0x400C424C, 0x00000000, 0x00072464},
    {lbl_1_rodata_3554, 0x4004C1F0, 0x00000000, 0x0002ED08},
    {lbl_1_rodata_356C, 0x40021FE8, 0x00000000, 0x00012E2C},
    {lbl_1_rodata_3584, 0x400A2334, 0x00000000, 0x0005C0D0},
    {lbl_1_rodata_359C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_35B4, 0x4002E9C8, 0x00000000, 0x00019388},
    {lbl_1_rodata_35CC, 0x40077034, 0x00000000, 0x0004100C},
    {lbl_1_rodata_35E4, 0x400278B8, 0x00000000, 0x00012EBC},
    {lbl_1_rodata_35FC, 0x40075074, 0x00000000, 0x000467B0},
    {lbl_1_rodata_3674, 0x400150EC, 0x00000000, 0x0000DE80},
    {lbl_1_rodata_368C, 0x4000F000, 0x00000000, 0x00009CDC},
    {lbl_1_rodata_3498, 0x400EFFB8, 0x00000000, 0x0008D04C},
    {lbl_1_rodata_34AC, 0x4006C0A4, 0x00000000, 0x0004229C},
    {lbl_1_rodata_34C0, 0x401017BC, 0x00000000, 0x0009B64C},
    {lbl_1_rodata_34D4, 0x40090558, 0x00000000, 0x00058584},
    {lbl_1_rodata_34E8, 0x4000FC10, 0x00000000, 0x00008628},
    {lbl_1_rodata_34FC, 0x400A5928, 0x00000000, 0x0005A998},
    {lbl_1_rodata_3510, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_3524, 0x40091AB4, 0x00000000, 0x000547C8},
    {lbl_1_rodata_353C, 0x400C424C, 0x00000000, 0x00072464},
    {lbl_1_rodata_3554, 0x4004C1F0, 0x00000000, 0x0002ED08},
    {lbl_1_rodata_356C, 0x40021FE8, 0x00000000, 0x00012E2C},
    {lbl_1_rodata_3584, 0x400A2334, 0x00000000, 0x0005C0D0},
    {lbl_1_rodata_359C, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_35B4, 0x4002E9C8, 0x00000000, 0x00019388},
    {lbl_1_rodata_35CC, 0x40077034, 0x00000000, 0x0004100C},
    {lbl_1_rodata_35E4, 0x400278B8, 0x00000000, 0x00012EBC},
    {lbl_1_rodata_35FC, 0x40075074, 0x00000000, 0x000467B0},
    {lbl_1_rodata_36A4, 0x40017300, 0x00000000, 0x0000F260},
    {lbl_1_rodata_36BC, 0x40011D40, 0x00000000, 0x0000AED0},
    {lbl_1_rodata_36D4, 0x4016C2F8, 0x00000000, 0x0009905C},
    {lbl_1_rodata_36E8, 0x4009E950, 0x00000000, 0x00044F2C},
    {lbl_1_rodata_36FC, 0x40132D08, 0x00000000, 0x000896B4},
    {lbl_1_rodata_3710, 0x400B28B8, 0x00000000, 0x00051A74},
    {lbl_1_rodata_3724, 0x40019014, 0x00000000, 0x0000AF08},
    {lbl_1_rodata_3738, 0x400B1238, 0x00000000, 0x00046194},
    {lbl_1_rodata_374C, 0x4009C9B8, 0x00000000, 0x0005C2D0},
    {lbl_1_rodata_3760, 0x400DBF84, 0x00000000, 0x00059B44},
    {lbl_1_rodata_3778, 0x401286C4, 0x00000000, 0x00078570},
    {lbl_1_rodata_3790, 0x4007973C, 0x00000000, 0x0003346C},
    {lbl_1_rodata_37A8, 0x40031838, 0x00000000, 0x000141E8},
    {lbl_1_rodata_37C0, 0x400C2CC0, 0x00000000, 0x000536A8},
    {lbl_1_rodata_37D8, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_37F0, 0x40034FAC, 0x00000000, 0x00014150},
    {lbl_1_rodata_3808, 0x400943AC, 0x00000000, 0x0003BBA8},
    {lbl_1_rodata_3820, 0x40017890, 0x00000000, 0x0000812C},
    {lbl_1_rodata_3838, 0x400AE4E8, 0x00000000, 0x0004F564},
    {lbl_1_rodata_3850, 0x400196C0, 0x00000000, 0x000126C0},
    {lbl_1_rodata_3868, 0x40010B60, 0x00000000, 0x0000B3F4},
    {lbl_1_rodata_3880, 0x401469B0, 0x00000000, 0x000B5088},
    {lbl_1_rodata_3894, 0x400A7004, 0x00000000, 0x0005C5E4},
    {lbl_1_rodata_38A8, 0x4012F150, 0x00000000, 0x000A76AC},
    {lbl_1_rodata_38BC, 0x400CD6A4, 0x00000000, 0x00077B20},
    {lbl_1_rodata_38D0, 0x400159C8, 0x00000000, 0x00008A78},
    {lbl_1_rodata_38E4, 0x400C3D8C, 0x00000000, 0x00063808},
    {lbl_1_rodata_38F8, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_390C, 0x400CD4AC, 0x00000000, 0x0006EFF0},
    {lbl_1_rodata_3924, 0x400FC938, 0x00000000, 0x00089CE4},
    {lbl_1_rodata_393C, 0x40076214, 0x00000000, 0x000414C8},
    {lbl_1_rodata_3954, 0x40023D98, 0x00000000, 0x00012730},
    {lbl_1_rodata_396C, 0x400B5CE8, 0x00000000, 0x0005F11C},
    {lbl_1_rodata_3984, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_399C, 0x4002B1B0, 0x00000000, 0x00017084},
    {lbl_1_rodata_39B4, 0x40096400, 0x00000000, 0x0004CF34},
    {lbl_1_rodata_39CC, 0x40028124, 0x00000000, 0x00011734},
    {lbl_1_rodata_39E4, 0x4009A71C, 0x00000000, 0x0005935C},
    {lbl_1_rodata_39FC, 0x4001F27C, 0x00000000, 0x000154D0},
    {lbl_1_rodata_3A14, 0x40012B00, 0x00000000, 0x0000C0A4},
    {lbl_1_rodata_3A2C, 0x401041C0, 0x00000000, 0x000A9E48},
    {lbl_1_rodata_3A40, 0x4006D470, 0x00000000, 0x00044114},
    {lbl_1_rodata_3A54, 0x4010B85C, 0x00000000, 0x000A4514},
    {lbl_1_rodata_3A68, 0x4009F540, 0x00000000, 0x0006531C},
    {lbl_1_rodata_3A7C, 0x40011B3C, 0x00000000, 0x000098E8},
    {lbl_1_rodata_3A90, 0x400A65DC, 0x00000000, 0x00066AD4},
    {lbl_1_rodata_3AA4, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_3AB8, 0x400A0A34, 0x00000000, 0x00067B98},
    {lbl_1_rodata_3AD0, 0x400D7318, 0x00000000, 0x0008B49C},
    {lbl_1_rodata_3AE8, 0x4004E644, 0x00000000, 0x0002F990},
    {lbl_1_rodata_3B00, 0x40023494, 0x00000000, 0x00013660},
    {lbl_1_rodata_3B18, 0x400967E0, 0x00000000, 0x00056794},
    {lbl_1_rodata_3B30, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_3B48, 0x4002CADC, 0x00000000, 0x00018AF8},
    {lbl_1_rodata_3B60, 0x4007BB38, 0x00000000, 0x0004AE10},
    {lbl_1_rodata_3B78, 0x40022A98, 0x00000000, 0x00013AA4},
    {lbl_1_rodata_3B90, 0x40081590, 0x00000000, 0x00051810},
    {lbl_1_rodata_3BA8, 0x400118C8, 0x00000000, 0x0000D7B8},
    {lbl_1_rodata_3BC0, 0x40007C20, 0x00000000, 0x000052E8},
    {lbl_1_rodata_3BD8, 0x4010B7D8, 0x00000000, 0x00087980},
    {lbl_1_rodata_3BEC, 0x40074414, 0x00000000, 0x0003C1CC},
    {lbl_1_rodata_3C00, 0x40120094, 0x00000000, 0x0009206C},
    {lbl_1_rodata_3C14, 0x400A5EBC, 0x00000000, 0x00053990},
    {lbl_1_rodata_3C28, 0x40010618, 0x00000000, 0x00007A0C},
    {lbl_1_rodata_3C3C, 0x400A163D, 0x00000000, 0x0004B0B8},
    {lbl_1_rodata_3C50, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_3C64, 0x400A4308, 0x00000000, 0x00051EFC},
    {lbl_1_rodata_3C7C, 0x400D5F64, 0x00000000, 0x0006BD0C},
    {lbl_1_rodata_3C94, 0x40054A7C, 0x00000000, 0x0002BA10},
    {lbl_1_rodata_3CAC, 0x400224B8, 0x00000000, 0x000109F4},
    {lbl_1_rodata_3CC4, 0x400C11B0, 0x00000000, 0x0005E198},
    {lbl_1_rodata_3CDC, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_3CF4, 0x4002F914, 0x00000000, 0x00015D64},
    {lbl_1_rodata_3D0C, 0x40074258, 0x00000000, 0x0003581C},
    {lbl_1_rodata_3D24, 0x40024291, 0x00000000, 0x0000F6F4},
    {lbl_1_rodata_3D3C, 0x40084644, 0x00000000, 0x00041AB0},
    {lbl_1_rodata_3D54, 0x40018028, 0x00000000, 0x00012FD0},
    {lbl_1_rodata_3D6C, 0x4000A1E0, 0x00000000, 0x00006CCC},
    {lbl_1_rodata_3D84, 0x4011D304, 0x00000000, 0x0009DFAC},
    {lbl_1_rodata_3D98, 0x4008971C, 0x00000000, 0x0004FFB8},
    {lbl_1_rodata_3DAC, 0x40126484, 0x00000000, 0x000A5438},
    {lbl_1_rodata_3DC0, 0x400A5EC0, 0x00000000, 0x0005C6F4},
    {lbl_1_rodata_3DD4, 0x40010618, 0x00000000, 0x0000832C},
    {lbl_1_rodata_3DE8, 0x400C4011, 0x00000000, 0x0005EA3C},
    {lbl_1_rodata_3DFC, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_3E10, 0x400B0F10, 0x00000000, 0x0005EE14},
    {lbl_1_rodata_3E28, 0x400E50F0, 0x00000000, 0x0007EC0C},
    {lbl_1_rodata_3E40, 0x4006141C, 0x00000000, 0x0003792C},
    {lbl_1_rodata_3E58, 0x40024608, 0x00000000, 0x00013E28},
    {lbl_1_rodata_3E70, 0x400C5024, 0x00000000, 0x0006A138},
    {lbl_1_rodata_3E88, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_3EA0, 0x40037600, 0x00000000, 0x00019A98},
    {lbl_1_rodata_3EB8, 0x400918E4, 0x00000000, 0x00045684},
    {lbl_1_rodata_3ED0, 0x400295D9, 0x00000000, 0x00012568},
    {lbl_1_rodata_3EE8, 0x40086FE8, 0x00000000, 0x0004B62C},
    {lbl_1_rodata_3F00, 0x40020FDC, 0x00000000, 0x00017934},
    {lbl_1_rodata_3F18, 0x4000DFC0, 0x00000000, 0x0000A1F4},
    {lbl_1_rodata_1D5C, 0x40104EE0, 0x00000000, 0x0009854C},
    {lbl_1_rodata_1D70, 0x4009AEF8, 0x00000000, 0x0005A6AC},
    {lbl_1_rodata_1D84, 0x40119934, 0x00000000, 0x0009E218},
    {lbl_1_rodata_1D98, 0x400A1054, 0x00000000, 0x0005F8A4},
    {lbl_1_rodata_1DAC, 0x400134A4, 0x00000000, 0x00009148},
    {lbl_1_rodata_1DC0, 0x40093E94, 0x00000000, 0x00048400},
    {lbl_1_rodata_1DD4, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_1DE8, 0x400A18B4, 0x00000000, 0x0005CD34},
    {lbl_1_rodata_1E00, 0x400C7D2C, 0x00000000, 0x00070F4C},
    {lbl_1_rodata_1E18, 0x4007BD40, 0x00000000, 0x000495C0},
    {lbl_1_rodata_1E30, 0x400454C4, 0x00000000, 0x00023B4C},
    {lbl_1_rodata_1E48, 0x400B3964, 0x00000000, 0x0006004C},
    {lbl_1_rodata_1E60, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_1E78, 0x40024D38, 0x00000000, 0x0001112C},
    {lbl_1_rodata_1E90, 0x40067F14, 0x00000000, 0x00032FC0},
    {lbl_1_rodata_1EA8, 0x40026204, 0x00000000, 0x000113EC},
    {lbl_1_rodata_1EC0, 0x4008892C, 0x00000000, 0x000514F0},
    {lbl_1_rodata_3F30, 0x40022D3C, 0x00000000, 0x000191A4},
    {lbl_1_rodata_3F48, 0x4000FD40, 0x00000000, 0x0000B958},
    {lbl_1_rodata_2ABC, 0x4010D3F0, 0x00000000, 0x00096260},
    {lbl_1_rodata_2AD0, 0x40070C74, 0x00000000, 0x00040B74},
    {lbl_1_rodata_2AE4, 0x4010A880, 0x00000000, 0x0008BDC4},
    {lbl_1_rodata_2AF8, 0x4008BAF0, 0x00000000, 0x0004FA1C},
    {lbl_1_rodata_2B0C, 0x4001396C, 0x00000000, 0x00009320},
    {lbl_1_rodata_2B20, 0x4008AF98, 0x00000000, 0x000421C4},
    {lbl_1_rodata_2B34, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_2B48, 0x4008CB38, 0x00000000, 0x0004AE80},
    {lbl_1_rodata_2B60, 0x400E3B50, 0x00000000, 0x0007ECDC},
    {lbl_1_rodata_2B78, 0x4004EE38, 0x00000000, 0x0002CF3C},
    {lbl_1_rodata_2B90, 0x40021FD0, 0x00000000, 0x0001206C},
    {lbl_1_rodata_2BA8, 0x400A16DC, 0x00000000, 0x000501F8},
    {lbl_1_rodata_2BC0, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2BD8, 0x4002324C, 0x00000000, 0x0000FFB0},
    {lbl_1_rodata_2BF0, 0x400670B8, 0x00000000, 0x00030B0C},
    {lbl_1_rodata_2C08, 0x40020080, 0x00000000, 0x0000DC28},
    {lbl_1_rodata_2C20, 0x40072C38, 0x00000000, 0x0004023C},
    {lbl_1_rodata_3F60, 0x40016320, 0x00000000, 0x0000E1BC},
    {lbl_1_rodata_3F78, 0x40012C40, 0x00000000, 0x0000B6F0},
    {lbl_1_rodata_240C, 0x400FF80C, 0x00000000, 0x0008E938},
    {lbl_1_rodata_2420, 0x40070840, 0x00000000, 0x0003FCE8},
    {lbl_1_rodata_2434, 0x4010B5D0, 0x00000000, 0x00090E6C},
    {lbl_1_rodata_2448, 0x400997A4, 0x00000000, 0x00053410},
    {lbl_1_rodata_245C, 0x400166A4, 0x00000000, 0x0000A878},
    {lbl_1_rodata_2470, 0x4008C894, 0x00000000, 0x00044A10},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_2498, 0x400A2460, 0x00000000, 0x00056EEC},
    {lbl_1_rodata_24B0, 0x400CCDD4, 0x00000000, 0x00071018},
    {lbl_1_rodata_24C8, 0x4004E51C, 0x00000000, 0x0002BC28},
    {lbl_1_rodata_24E0, 0x40023648, 0x00000000, 0x00012090},
    {lbl_1_rodata_24F8, 0x400A5574, 0x00000000, 0x000547BC},
    {lbl_1_rodata_2510, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2528, 0x40025C04, 0x00000000, 0x00011890},
    {lbl_1_rodata_2540, 0x40060CEC, 0x00000000, 0x0002FA5C},
    {lbl_1_rodata_2558, 0x40023608, 0x00000000, 0x0000EFA0},
    {lbl_1_rodata_2570, 0x4007F2C4, 0x00000000, 0x00044BE0},
    {lbl_1_rodata_3F90, 0x40016320, 0x00000000, 0x0000E198},
    {lbl_1_rodata_3FA8, 0x40012C40, 0x00000000, 0x0000B6CC},
    {lbl_1_rodata_240C, 0x400FF80C, 0x00000000, 0x0008E938},
    {lbl_1_rodata_2420, 0x40070840, 0x00000000, 0x0003FCE8},
    {lbl_1_rodata_2434, 0x4010B5D0, 0x00000000, 0x00090E6C},
    {lbl_1_rodata_2448, 0x400997A4, 0x00000000, 0x00053410},
    {lbl_1_rodata_245C, 0x400166A4, 0x00000000, 0x0000A878},
    {lbl_1_rodata_2470, 0x4008C894, 0x00000000, 0x00044A10},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_2498, 0x400A2460, 0x00000000, 0x00056EEC},
    {lbl_1_rodata_24B0, 0x400CCDD4, 0x00000000, 0x00071018},
    {lbl_1_rodata_24C8, 0x4004E51C, 0x00000000, 0x0002BC28},
    {lbl_1_rodata_24E0, 0x40023648, 0x00000000, 0x00012090},
    {lbl_1_rodata_24F8, 0x400A5574, 0x00000000, 0x000547BC},
    {lbl_1_rodata_2510, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2528, 0x40025C04, 0x00000000, 0x00011890},
    {lbl_1_rodata_2540, 0x40060CEC, 0x00000000, 0x0002FA5C},
    {lbl_1_rodata_2558, 0x40023608, 0x00000000, 0x0000EFA0},
    {lbl_1_rodata_2570, 0x4007F2C4, 0x00000000, 0x00044BE0},
    {lbl_1_rodata_3FC0, 0x40016320, 0x00000000, 0x0000E1C4},
    {lbl_1_rodata_3FD8, 0x40012C40, 0x00000000, 0x0000B6F8},
    {lbl_1_rodata_240C, 0x400FF80C, 0x00000000, 0x0008E938},
    {lbl_1_rodata_2420, 0x40070840, 0x00000000, 0x0003FCE8},
    {lbl_1_rodata_2434, 0x4010B5D0, 0x00000000, 0x00090E6C},
    {lbl_1_rodata_2448, 0x400997A4, 0x00000000, 0x00053410},
    {lbl_1_rodata_245C, 0x400166A4, 0x00000000, 0x0000A878},
    {lbl_1_rodata_2470, 0x4008C894, 0x00000000, 0x00044A10},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_2498, 0x400A2460, 0x00000000, 0x00056EEC},
    {lbl_1_rodata_24B0, 0x400CCDD4, 0x00000000, 0x00071018},
    {lbl_1_rodata_24C8, 0x4004E51C, 0x00000000, 0x0002BC28},
    {lbl_1_rodata_24E0, 0x40023648, 0x00000000, 0x00012090},
    {lbl_1_rodata_24F8, 0x400A5574, 0x00000000, 0x000547BC},
    {lbl_1_rodata_2510, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2528, 0x40025C04, 0x00000000, 0x00011890},
    {lbl_1_rodata_2540, 0x40060CEC, 0x00000000, 0x0002FA5C},
    {lbl_1_rodata_2558, 0x40023608, 0x00000000, 0x0000EFA0},
    {lbl_1_rodata_2570, 0x4007F2C4, 0x00000000, 0x00044BE0},
    {lbl_1_rodata_3FF0, 0x40016320, 0x00000000, 0x0000E0FC},
    {lbl_1_rodata_4008, 0x40012C40, 0x00000000, 0x0000B630},
    {lbl_1_rodata_240C, 0x400FF80C, 0x00000000, 0x0008E938},
    {lbl_1_rodata_2420, 0x40070840, 0x00000000, 0x0003FCE8},
    {lbl_1_rodata_2434, 0x4010B5D0, 0x00000000, 0x00090E6C},
    {lbl_1_rodata_2448, 0x400997A4, 0x00000000, 0x00053410},
    {lbl_1_rodata_245C, 0x400166A4, 0x00000000, 0x0000A878},
    {lbl_1_rodata_2470, 0x4008C894, 0x00000000, 0x00044A10},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_2498, 0x400A2460, 0x00000000, 0x00056EEC},
    {lbl_1_rodata_24B0, 0x400CCDD4, 0x00000000, 0x00071018},
    {lbl_1_rodata_24C8, 0x4004E51C, 0x00000000, 0x0002BC28},
    {lbl_1_rodata_24E0, 0x40023648, 0x00000000, 0x00012090},
    {lbl_1_rodata_24F8, 0x400A5574, 0x00000000, 0x000547BC},
    {lbl_1_rodata_2510, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_2528, 0x40025C04, 0x00000000, 0x00011890},
    {lbl_1_rodata_2540, 0x40060CEC, 0x00000000, 0x0002FA5C},
    {lbl_1_rodata_2558, 0x40023608, 0x00000000, 0x0000EFA0},
    {lbl_1_rodata_2570, 0x4007F2C4, 0x00000000, 0x00044BE0},
    {lbl_1_rodata_4020, 0x40012910, 0x00000000, 0x0000CF04},
    {lbl_1_rodata_4038, 0x4000D4C0, 0x00000000, 0x000089BC},
    {lbl_1_rodata_4050, 0x40106D94, 0x00000000, 0x000924E8},
    {lbl_1_rodata_4064, 0x40074128, 0x00000000, 0x00042BDC},
    {lbl_1_rodata_4078, 0x40114C60, 0x00000000, 0x000A0C5C},
    {lbl_1_rodata_408C, 0x4009AB80, 0x00000000, 0x000583A8},
    {lbl_1_rodata_40A0, 0x400168E4, 0x00000000, 0x00009DF0},
    {lbl_1_rodata_40B4, 0x400AE6A9, 0x00000000, 0x0005270C},
    {lbl_1_rodata_40C8, 0x4004E820, 0x00000000, 0x0002E358},
    {lbl_1_rodata_40DC, 0x400A7AD0, 0x00000000, 0x0005BAD0},
    {lbl_1_rodata_40F4, 0x400D7814, 0x00000000, 0x00078FA8},
    {lbl_1_rodata_410C, 0x400552FC, 0x00000000, 0x00031338},
    {lbl_1_rodata_4124, 0x40026710, 0x00000000, 0x00013EAC},
    {lbl_1_rodata_413C, 0x400A77B8, 0x00000000, 0x0005C8E0},
    {lbl_1_rodata_4154, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_416C, 0x4002A408, 0x00000000, 0x000141AC},
    {lbl_1_rodata_4184, 0x4007E20C, 0x00000000, 0x0003BAA4},
    {lbl_1_rodata_419C, 0x40028491, 0x00000000, 0x0001175C},
    {lbl_1_rodata_41B4, 0x4007DF38, 0x00000000, 0x00047EFC},
    {lbl_1_rodata_41CC, 0x40012910, 0x00000000, 0x0000CEDC},
    {lbl_1_rodata_41E4, 0x4000D4C0, 0x00000000, 0x00008994},
    {lbl_1_rodata_4050, 0x40106D94, 0x00000000, 0x000924E8},
    {lbl_1_rodata_4064, 0x40074128, 0x00000000, 0x00042BDC},
    {lbl_1_rodata_4078, 0x40114C60, 0x00000000, 0x000A0C5C},
    {lbl_1_rodata_408C, 0x4009AB80, 0x00000000, 0x000583A8},
    {lbl_1_rodata_40A0, 0x400168E4, 0x00000000, 0x00009DF0},
    {lbl_1_rodata_40B4, 0x400AE6A9, 0x00000000, 0x0005270C},
    {lbl_1_rodata_40C8, 0x4004E820, 0x00000000, 0x0002E358},
    {lbl_1_rodata_40DC, 0x400A7AD0, 0x00000000, 0x0005BAD0},
    {lbl_1_rodata_40F4, 0x400D7814, 0x00000000, 0x00078FA8},
    {lbl_1_rodata_410C, 0x400552FC, 0x00000000, 0x00031338},
    {lbl_1_rodata_4124, 0x40026710, 0x00000000, 0x00013EAC},
    {lbl_1_rodata_413C, 0x400A77B8, 0x00000000, 0x0005C8E0},
    {lbl_1_rodata_4154, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_416C, 0x4002A408, 0x00000000, 0x000141AC},
    {lbl_1_rodata_4184, 0x4007E20C, 0x00000000, 0x0003BAA4},
    {lbl_1_rodata_419C, 0x40028491, 0x00000000, 0x0001175C},
    {lbl_1_rodata_41B4, 0x4007DF38, 0x00000000, 0x00047EFC},
    {lbl_1_rodata_41FC, 0x40013AD4, 0x00000000, 0x0000DDC8},
    {lbl_1_rodata_4214, 0x4000D7E0, 0x00000000, 0x00008C38},
    {lbl_1_rodata_4050, 0x40106D94, 0x00000000, 0x000924E8},
    {lbl_1_rodata_4064, 0x40074128, 0x00000000, 0x00042BDC},
    {lbl_1_rodata_4078, 0x40114C60, 0x00000000, 0x000A0C5C},
    {lbl_1_rodata_408C, 0x4009AB80, 0x00000000, 0x000583A8},
    {lbl_1_rodata_40A0, 0x400168E4, 0x00000000, 0x00009DF0},
    {lbl_1_rodata_40B4, 0x400AE6A9, 0x00000000, 0x0005270C},
    {lbl_1_rodata_40C8, 0x4004E820, 0x00000000, 0x0002E358},
    {lbl_1_rodata_40DC, 0x400A7AD0, 0x00000000, 0x0005BAD0},
    {lbl_1_rodata_40F4, 0x400D7814, 0x00000000, 0x00078FA8},
    {lbl_1_rodata_410C, 0x400552FC, 0x00000000, 0x00031338},
    {lbl_1_rodata_4124, 0x40026710, 0x00000000, 0x00013EAC},
    {lbl_1_rodata_413C, 0x400A77B8, 0x00000000, 0x0005C8E0},
    {lbl_1_rodata_4154, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_416C, 0x4002A408, 0x00000000, 0x000141AC},
    {lbl_1_rodata_4184, 0x4007E20C, 0x00000000, 0x0003BAA4},
    {lbl_1_rodata_419C, 0x40028491, 0x00000000, 0x0001175C},
    {lbl_1_rodata_41B4, 0x4007DF38, 0x00000000, 0x00047EFC},
    {lbl_1_rodata_422C, 0x40012910, 0x00000000, 0x0000CEB0},
    {lbl_1_rodata_4244, 0x4000D4C0, 0x00000000, 0x00008968},
    {lbl_1_rodata_4050, 0x40106D94, 0x00000000, 0x000924E8},
    {lbl_1_rodata_4064, 0x40074128, 0x00000000, 0x00042BDC},
    {lbl_1_rodata_4078, 0x40114C60, 0x00000000, 0x000A0C5C},
    {lbl_1_rodata_408C, 0x4009AB80, 0x00000000, 0x000583A8},
    {lbl_1_rodata_40A0, 0x400168E4, 0x00000000, 0x00009DF0},
    {lbl_1_rodata_40B4, 0x400AE6A9, 0x00000000, 0x0005270C},
    {lbl_1_rodata_40C8, 0x4004E820, 0x00000000, 0x0002E358},
    {lbl_1_rodata_40DC, 0x400A7AD0, 0x00000000, 0x0005BAD0},
    {lbl_1_rodata_40F4, 0x400D7814, 0x00000000, 0x00078FA8},
    {lbl_1_rodata_410C, 0x400552FC, 0x00000000, 0x00031338},
    {lbl_1_rodata_4124, 0x40026710, 0x00000000, 0x00013EAC},
    {lbl_1_rodata_413C, 0x400A77B8, 0x00000000, 0x0005C8E0},
    {lbl_1_rodata_4154, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_416C, 0x4002A408, 0x00000000, 0x000141AC},
    {lbl_1_rodata_4184, 0x4007E20C, 0x00000000, 0x0003BAA4},
    {lbl_1_rodata_419C, 0x40028491, 0x00000000, 0x0001175C},
    {lbl_1_rodata_41B4, 0x4007DF38, 0x00000000, 0x00047EFC},
    {lbl_1_rodata_425C, 0x4001AE1C, 0x00000000, 0x0001157C},
    {lbl_1_rodata_4274, 0x4000FFE0, 0x00000000, 0x00009BD8},
    {lbl_1_rodata_3080, 0x400D9004, 0x00000000, 0x0007DC34},
    {lbl_1_rodata_3094, 0x4005828C, 0x00000000, 0x000318E8},
    {lbl_1_rodata_30A8, 0x400E77C8, 0x00000000, 0x00084D44},
    {lbl_1_rodata_30BC, 0x40071294, 0x00000000, 0x0003E188},
    {lbl_1_rodata_30D0, 0x40011370, 0x00000000, 0x00008FA8},
    {lbl_1_rodata_30E4, 0x40077E54, 0x00000000, 0x0003C340},
    {lbl_1_rodata_30F8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_310C, 0x40089DEC, 0x00000000, 0x0004C700},
    {lbl_1_rodata_3124, 0x400B74D8, 0x00000000, 0x00069C9C},
    {lbl_1_rodata_313C, 0x4003EDC8, 0x00000000, 0x00021E78},
    {lbl_1_rodata_3154, 0x4001D924, 0x00000000, 0x0000E02C},
    {lbl_1_rodata_316C, 0x40084518, 0x00000000, 0x0004750C},
    {lbl_1_rodata_3184, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_319C, 0x40020AD0, 0x00000000, 0x0000F47C},
    {lbl_1_rodata_31B4, 0x4005013C, 0x00000000, 0x000274E4},
    {lbl_1_rodata_31CC, 0x40021F9C, 0x00000000, 0x0000FB58},
    {lbl_1_rodata_31E4, 0x4005E514, 0x00000000, 0x00033954},
    {lbl_1_rodata_428C, 0x4001A71C, 0x00000000, 0x000112D0},
    {lbl_1_rodata_42A4, 0x4000F8E0, 0x00000000, 0x00009924},
    {lbl_1_rodata_3080, 0x400D9004, 0x00000000, 0x0007DC34},
    {lbl_1_rodata_3094, 0x4005828C, 0x00000000, 0x000318E8},
    {lbl_1_rodata_30A8, 0x400E77C8, 0x00000000, 0x00084D44},
    {lbl_1_rodata_30BC, 0x40071294, 0x00000000, 0x0003E188},
    {lbl_1_rodata_30D0, 0x40011370, 0x00000000, 0x00008FA8},
    {lbl_1_rodata_30E4, 0x40077E54, 0x00000000, 0x0003C340},
    {lbl_1_rodata_30F8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_310C, 0x40089DEC, 0x00000000, 0x0004C700},
    {lbl_1_rodata_3124, 0x400B74D8, 0x00000000, 0x00069C9C},
    {lbl_1_rodata_313C, 0x4003EDC8, 0x00000000, 0x00021E78},
    {lbl_1_rodata_3154, 0x4001D924, 0x00000000, 0x0000E02C},
    {lbl_1_rodata_316C, 0x40084518, 0x00000000, 0x0004750C},
    {lbl_1_rodata_3184, 0x40008818, 0x00000000, 0x000020E4},
    {lbl_1_rodata_319C, 0x40020AD0, 0x00000000, 0x0000F47C},
    {lbl_1_rodata_31B4, 0x4005013C, 0x00000000, 0x000274E4},
    {lbl_1_rodata_31CC, 0x40021F9C, 0x00000000, 0x0000FB58},
    {lbl_1_rodata_31E4, 0x4005E514, 0x00000000, 0x00033954},
    {lbl_1_rodata_91C, 0x4001E0CC, 0x00000000, 0x00012DE4},
    {lbl_1_rodata_934, 0x4000D740, 0x00000000, 0x00009230},
    {lbl_1_rodata_42BC, 0x4006B68A, 0x00000000, 0x000482D0},
    {lbl_1_rodata_42D4, 0x4003530A, 0x00000000, 0x00022FBC},
    {lbl_1_rodata_42EC, 0x4006C460, 0x00000000, 0x000461C4},
    {lbl_1_rodata_4304, 0x400463F6, 0x00000000, 0x0002F958},
    {lbl_1_rodata_431C, 0x40004F52, 0x00000000, 0x000032A0},
    {lbl_1_rodata_4334, 0x4004134C, 0x00000000, 0x0002B6C4},
    {lbl_1_rodata_9C4, 0x40060268, 0x00000000, 0x00039908},
    {lbl_1_rodata_434C, 0x4003EF10, 0x00000000, 0x00028C6C},
    {lbl_1_rodata_4364, 0x40053C78, 0x00000000, 0x000379C4},
    {lbl_1_rodata_437C, 0x4002151A, 0x00000000, 0x00014F54},
    {lbl_1_rodata_4394, 0x4000E51E, 0x00000000, 0x00008184},
    {lbl_1_rodata_43AC, 0x4003FA2A, 0x00000000, 0x00026DB4},
    {lbl_1_rodata_43C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_43DC, 0x4000EFCE, 0x00000000, 0x00008CDC},
    {lbl_1_rodata_43F4, 0x4002A1AE, 0x00000000, 0x0001BA08},
    {lbl_1_rodata_440C, 0x40014CC8, 0x00000000, 0x0000D1DC},
    {lbl_1_rodata_4424, 0x40039BD8, 0x00000000, 0x00026FD4},
    {lbl_1_rodata_AC8, 0x40025734, 0x00000000, 0x0001803C},
    {lbl_1_rodata_AE0, 0x40010340, 0x00000000, 0x0000B790},
    {lbl_1_rodata_443C, 0x40071B74, 0x00000000, 0x0004CBE0},
    {lbl_1_rodata_4454, 0x400330EA, 0x00000000, 0x00021CB8},
    {lbl_1_rodata_446C, 0x4006E90E, 0x00000000, 0x0004798C},
    {lbl_1_rodata_4484, 0x4003E156, 0x00000000, 0x0002A490},
    {lbl_1_rodata_449C, 0x400051F6, 0x00000000, 0x0000356C},
    {lbl_1_rodata_44B4, 0x400381B0, 0x00000000, 0x00025678},
    {lbl_1_rodata_B70, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_44CC, 0x40042B48, 0x00000000, 0x0002B5FC},
    {lbl_1_rodata_44E4, 0x40057066, 0x00000000, 0x0003A394},
    {lbl_1_rodata_44FC, 0x40020BB4, 0x00000000, 0x000150B8},
    {lbl_1_rodata_4514, 0x40010964, 0x00000000, 0x00009CE8},
    {lbl_1_rodata_452C, 0x4003F8D8, 0x00000000, 0x0002706C},
    {lbl_1_rodata_4544, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_455C, 0x4000E896, 0x00000000, 0x00008ADC},
    {lbl_1_rodata_4574, 0x40029E6C, 0x00000000, 0x0001B9A4},
    {lbl_1_rodata_458C, 0x4000FB9C, 0x00000000, 0x00009A00},
    {lbl_1_rodata_45A4, 0x40036258, 0x00000000, 0x00024C3C},
    {lbl_1_rodata_C74, 0x4001D3B8, 0x00000000, 0x00015034},
    {lbl_1_rodata_C8C, 0x4000EDE0, 0x00000000, 0x0000AD10},
    {lbl_1_rodata_45BC, 0x4004F750, 0x00000000, 0x000330FC},
    {lbl_1_rodata_45D4, 0x40026116, 0x00000000, 0x000176E8},
    {lbl_1_rodata_45EC, 0x400512CA, 0x00000000, 0x000314FC},
    {lbl_1_rodata_4604, 0x40030326, 0x00000000, 0x0001F2F4},
    {lbl_1_rodata_461C, 0x40003DFA, 0x00000000, 0x0000259C},
    {lbl_1_rodata_4634, 0x4002AE18, 0x00000000, 0x0001B4AC},
    {lbl_1_rodata_D1C, 0x40033688, 0x00000000, 0x0001FBB8},
    {lbl_1_rodata_464C, 0x4002D4E4, 0x00000000, 0x0001BC0C},
    {lbl_1_rodata_4664, 0x40041982, 0x00000000, 0x00029C54},
    {lbl_1_rodata_467C, 0x40019D7C, 0x00000000, 0x0000EFDC},
    {lbl_1_rodata_4694, 0x4000C01A, 0x00000000, 0x0000626C},
    {lbl_1_rodata_46AC, 0x4002D21A, 0x00000000, 0x00019420},
    {lbl_1_rodata_46C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_46DC, 0x4000A1B0, 0x00000000, 0x00005930},
    {lbl_1_rodata_46F4, 0x40015A48, 0x00000000, 0x0000CFC0},
    {lbl_1_rodata_470C, 0x4001545A, 0x00000000, 0x0000DCEC},
    {lbl_1_rodata_4724, 0x40024B20, 0x00000000, 0x00017880},
    {lbl_1_rodata_E20, 0x40021A44, 0x00000000, 0x00015E08},
    {lbl_1_rodata_E38, 0x40013E80, 0x00000000, 0x0000C09C},
    {lbl_1_rodata_473C, 0x4005B674, 0x00000000, 0x0003B850},
    {lbl_1_rodata_4754, 0x4002A888, 0x00000000, 0x0001AD54},
    {lbl_1_rodata_476C, 0x40066E30, 0x00000000, 0x0003FDB0},
    {lbl_1_rodata_4784, 0x40034D20, 0x00000000, 0x000229F8},
    {lbl_1_rodata_479C, 0x40004FA6, 0x00000000, 0x0000325C},
    {lbl_1_rodata_47B4, 0x4002A838, 0x00000000, 0x0001AF58},
    {lbl_1_rodata_EC8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_47CC, 0x400326BC, 0x00000000, 0x0001ED5C},
    {lbl_1_rodata_47E4, 0x40049FB6, 0x00000000, 0x0002F7F4},
    {lbl_1_rodata_47FC, 0x4001DBE2, 0x00000000, 0x00011EB0},
    {lbl_1_rodata_4814, 0x4000D434, 0x00000000, 0x00007404},
    {lbl_1_rodata_482C, 0x40037CB2, 0x00000000, 0x00020D5C},
    {lbl_1_rodata_4844, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_485C, 0x4000D3E4, 0x00000000, 0x00007AC8},
    {lbl_1_rodata_4874, 0x400241E0, 0x00000000, 0x00017754},
    {lbl_1_rodata_488C, 0x400074FA, 0x00000000, 0x00003B58},
    {lbl_1_rodata_48A4, 0x400296F0, 0x00000000, 0x0001B180},
    {lbl_1_rodata_FCC, 0x4001DA50, 0x00000000, 0x00014788},
    {lbl_1_rodata_FE4, 0x40012940, 0x00000000, 0x0000C298},
    {lbl_1_rodata_48BC, 0x4006A3E0, 0x00000000, 0x000433F4},
    {lbl_1_rodata_48D4, 0x40027CE6, 0x00000000, 0x00019288},
    {lbl_1_rodata_48EC, 0x4004CB76, 0x00000000, 0x0002E608},
    {lbl_1_rodata_4904, 0x4002CE6E, 0x00000000, 0x0001CD24},
    {lbl_1_rodata_491C, 0x400036F6, 0x00000000, 0x000021D4},
    {lbl_1_rodata_4934, 0x4003C714, 0x00000000, 0x00026594},
    {lbl_1_rodata_1074, 0x40041E74, 0x00000000, 0x00028DE4},
    {lbl_1_rodata_494C, 0x400419F0, 0x00000000, 0x00027E8C},
    {lbl_1_rodata_4964, 0x4005062C, 0x00000000, 0x00032064},
    {lbl_1_rodata_497C, 0x4001A68E, 0x00000000, 0x00010100},
    {lbl_1_rodata_4994, 0x4000BD0C, 0x00000000, 0x00006490},
    {lbl_1_rodata_49AC, 0x4002BA3A, 0x00000000, 0x00018890},
    {lbl_1_rodata_49C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_49DC, 0x4000C5B2, 0x00000000, 0x00006B28},
    {lbl_1_rodata_49F4, 0x40020164, 0x00000000, 0x000136F8},
    {lbl_1_rodata_4A0C, 0x4001CBB4, 0x00000000, 0x00012298},
    {lbl_1_rodata_4A24, 0x400226E4, 0x00000000, 0x00015C94},
    {lbl_1_rodata_1178, 0x40022118, 0x00000000, 0x000187C0},
    {lbl_1_rodata_1190, 0x400123C0, 0x00000000, 0x0000BFF0},
    {lbl_1_rodata_4A3C, 0x40050AD6, 0x00000000, 0x00033BC0},
    {lbl_1_rodata_4A54, 0x4002B29A, 0x00000000, 0x0001B754},
    {lbl_1_rodata_4A6C, 0x4004A654, 0x00000000, 0x0002D3CC},
    {lbl_1_rodata_4A84, 0x4002BEC8, 0x00000000, 0x0001C92C},
    {lbl_1_rodata_4A9C, 0x40003118, 0x00000000, 0x00001D60},
    {lbl_1_rodata_4AB4, 0x400247BA, 0x00000000, 0x0001667C},
    {lbl_1_rodata_1220, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_4ACC, 0x4003179A, 0x00000000, 0x0001E794},
    {lbl_1_rodata_4AE4, 0x4003E9CA, 0x00000000, 0x000277FC},
    {lbl_1_rodata_4AFC, 0x4001C9AC, 0x00000000, 0x0001160C},
    {lbl_1_rodata_4B14, 0x4000C6AE, 0x00000000, 0x00006854},
    {lbl_1_rodata_4B2C, 0x4002C2A0, 0x00000000, 0x00018E60},
    {lbl_1_rodata_4B44, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_4B5C, 0x4000AEE6, 0x00000000, 0x00006214},
    {lbl_1_rodata_4B74, 0x40018F00, 0x00000000, 0x0000F6DC},
    {lbl_1_rodata_4B8C, 0x4000BBFC, 0x00000000, 0x00005C28},
    {lbl_1_rodata_4BA4, 0x40022828, 0x00000000, 0x000160CC},
    {lbl_1_rodata_1324, 0x40018A20, 0x00000000, 0x00012304},
    {lbl_1_rodata_133C, 0x4000F780, 0x00000000, 0x0000AB70},
    {lbl_1_rodata_4BBC, 0x4005A288, 0x00000000, 0x00039AEC},
    {lbl_1_rodata_4BD4, 0x400243C0, 0x00000000, 0x00015F24},
    {lbl_1_rodata_4BEC, 0x400646EE, 0x00000000, 0x0003CCEC},
    {lbl_1_rodata_4C04, 0x400367C6, 0x00000000, 0x00023434},
    {lbl_1_rodata_4C1C, 0x40004876, 0x00000000, 0x000029F8},
    {lbl_1_rodata_4C34, 0x40034CBA, 0x00000000, 0x00021AD0},
    {lbl_1_rodata_13CC, 0x40047D12, 0x00000000, 0x0002EC54},
    {lbl_1_rodata_4C4C, 0x400365E6, 0x00000000, 0x000212F8},
    {lbl_1_rodata_4C64, 0x4004AC40, 0x00000000, 0x0002F514},
    {lbl_1_rodata_4C7C, 0x400194C0, 0x00000000, 0x0000EB48},
    {lbl_1_rodata_4C94, 0x4000B016, 0x00000000, 0x00005714},
    {lbl_1_rodata_4CAC, 0x40034024, 0x00000000, 0x0001DD38},
    {lbl_1_rodata_4CC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_4CDC, 0x4000BDA2, 0x00000000, 0x00006620},
    {lbl_1_rodata_4CF4, 0x4001AD8C, 0x00000000, 0x0000FC34},
    {lbl_1_rodata_4D0C, 0x4001A11C, 0x00000000, 0x00010ADC},
    {lbl_1_rodata_4D24, 0x40029CE2, 0x00000000, 0x0001B300},
    {lbl_1_rodata_14D0, 0x4001C328, 0x00000000, 0x0001365C},
    {lbl_1_rodata_14E8, 0x4000EAE0, 0x00000000, 0x00008F28},
    {lbl_1_rodata_4D3C, 0x4005B686, 0x00000000, 0x0003AB30},
    {lbl_1_rodata_4D54, 0x40024D32, 0x00000000, 0x00017034},
    {lbl_1_rodata_4D6C, 0x40052E02, 0x00000000, 0x00032730},
    {lbl_1_rodata_4D84, 0x400300AE, 0x00000000, 0x0001E3C8},
    {lbl_1_rodata_4D9C, 0x40003006, 0x00000000, 0x00001AD4},
    {lbl_1_rodata_4DB4, 0x400238FE, 0x00000000, 0x00014504},
    {lbl_1_rodata_1578, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_4DCC, 0x400368F4, 0x00000000, 0x00021C08},
    {lbl_1_rodata_4DE4, 0x40048258, 0x00000000, 0x0002D55C},
    {lbl_1_rodata_4DFC, 0x4001A49A, 0x00000000, 0x00010014},
    {lbl_1_rodata_4E14, 0x4000B5B2, 0x00000000, 0x00005FE4},
    {lbl_1_rodata_4E2C, 0x4002E658, 0x00000000, 0x0001A45C},
    {lbl_1_rodata_4E44, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_4E5C, 0x4000B8F8, 0x00000000, 0x00006478},
    {lbl_1_rodata_4E74, 0x40019758, 0x00000000, 0x0000ECA0},
    {lbl_1_rodata_4E8C, 0x4000A088, 0x00000000, 0x00004AC4},
    {lbl_1_rodata_4EA4, 0x40025B00, 0x00000000, 0x00017934},
    {lbl_1_rodata_167C, 0x4001D77C, 0x00000000, 0x00014104},
    {lbl_1_rodata_1694, 0x400103C0, 0x00000000, 0x00009A1C},
    {lbl_1_rodata_4EBC, 0x4005EEA8, 0x00000000, 0x0003D418},
    {lbl_1_rodata_4ED4, 0x40025B5E, 0x00000000, 0x00017480},
    {lbl_1_rodata_4EEC, 0x40051204, 0x00000000, 0x000316C0},
    {lbl_1_rodata_4F04, 0x4002F91C, 0x00000000, 0x0001E5D4},
    {lbl_1_rodata_4F1C, 0x40003006, 0x00000000, 0x00001AD4},
    {lbl_1_rodata_4F34, 0x40020EC0, 0x00000000, 0x00013524},
    {lbl_1_rodata_1724, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_4F4C, 0x40039F6C, 0x00000000, 0x000246BC},
    {lbl_1_rodata_4F64, 0x4004CB3A, 0x00000000, 0x00030AF0},
    {lbl_1_rodata_4F7C, 0x400190BA, 0x00000000, 0x0000F270},
    {lbl_1_rodata_4F94, 0x4000AB5A, 0x00000000, 0x00005938},
    {lbl_1_rodata_4FAC, 0x4002CB32, 0x00000000, 0x00019510},
    {lbl_1_rodata_4FC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_4FDC, 0x400072FA, 0x00000000, 0x00003440},
    {lbl_1_rodata_4FF4, 0x40016576, 0x00000000, 0x0000D6B0},
    {lbl_1_rodata_500C, 0x4000B434, 0x00000000, 0x000056CC},
    {lbl_1_rodata_5024, 0x400239BA, 0x00000000, 0x000169B0},
    {lbl_1_rodata_1828, 0x40018B54, 0x00000000, 0x00012A70},
    {lbl_1_rodata_1840, 0x4000D540, 0x00000000, 0x00009CC0},
    {lbl_1_rodata_503C, 0x4004D7E4, 0x00000000, 0x00031D7C},
    {lbl_1_rodata_5054, 0x40037FC6, 0x00000000, 0x00022C80},
    {lbl_1_rodata_506C, 0x4005EBEE, 0x00000000, 0x000387F4},
    {lbl_1_rodata_5084, 0x4002CF56, 0x00000000, 0x0001D058},
    {lbl_1_rodata_509C, 0x40002F1A, 0x00000000, 0x000018FC},
    {lbl_1_rodata_50B4, 0x40028434, 0x00000000, 0x00018E74},
    {lbl_1_rodata_18D0, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_50CC, 0x4002E0C0, 0x00000000, 0x0001C780},
    {lbl_1_rodata_50E4, 0x4003E236, 0x00000000, 0x000273D0},
    {lbl_1_rodata_50FC, 0x4002CCB6, 0x00000000, 0x0001B1AC},
    {lbl_1_rodata_5114, 0x4000FE7E, 0x00000000, 0x00009080},
    {lbl_1_rodata_512C, 0x40033542, 0x00000000, 0x0001CBAC},
    {lbl_1_rodata_5144, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_515C, 0x4000AC66, 0x00000000, 0x00005A5C},
    {lbl_1_rodata_5174, 0x40016AC0, 0x00000000, 0x0000D1FC},
    {lbl_1_rodata_518C, 0x400123B4, 0x00000000, 0x0000B4DC},
    {lbl_1_rodata_51A4, 0x40024998, 0x00000000, 0x000176D0},
    {lbl_1_rodata_19D4, 0x40020F10, 0x00000000, 0x000147E0},
    {lbl_1_rodata_19EC, 0x400124A0, 0x00000000, 0x0000C3F4},
    {lbl_1_rodata_51BC, 0x400781B0, 0x00000000, 0x000503D0},
    {lbl_1_rodata_51D4, 0x40031DC0, 0x00000000, 0x00020478},
    {lbl_1_rodata_51EC, 0x4006F6A4, 0x00000000, 0x000474BC},
    {lbl_1_rodata_5204, 0x4004A76A, 0x00000000, 0x000323A0},
    {lbl_1_rodata_521C, 0x400045B8, 0x00000000, 0x00002A84},
    {lbl_1_rodata_5234, 0x40053C9C, 0x00000000, 0x00036ED4},
    {lbl_1_rodata_1A7C, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_524C, 0x40045274, 0x00000000, 0x0002CA68},
    {lbl_1_rodata_5264, 0x4005D642, 0x00000000, 0x0003E028},
    {lbl_1_rodata_527C, 0x40022E6C, 0x00000000, 0x000165FC},
    {lbl_1_rodata_5294, 0x4000D904, 0x00000000, 0x00007970},
    {lbl_1_rodata_52AC, 0x4003A402, 0x00000000, 0x00022C60},
    {lbl_1_rodata_52C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_52DC, 0x40012FA4, 0x00000000, 0x0000B900},
    {lbl_1_rodata_52F4, 0x4002EF92, 0x00000000, 0x0001E018},
    {lbl_1_rodata_530C, 0x4001F4E2, 0x00000000, 0x000141D0},
    {lbl_1_rodata_5324, 0x400343CA, 0x00000000, 0x00022780},
    {lbl_1_rodata_1B80, 0x4001F64C, 0x00000000, 0x00017088},
    {lbl_1_rodata_1B98, 0x40012BE0, 0x00000000, 0x0000CC14},
    {lbl_1_rodata_533C, 0x40068578, 0x00000000, 0x00046BB4},
    {lbl_1_rodata_5354, 0x40031280, 0x00000000, 0x0002089C},
    {lbl_1_rodata_536C, 0x40069882, 0x00000000, 0x000445B0},
    {lbl_1_rodata_5384, 0x4003D6AA, 0x00000000, 0x00029480},
    {lbl_1_rodata_539C, 0x40004B94, 0x00000000, 0x00003224},
    {lbl_1_rodata_53B4, 0x4003BBE2, 0x00000000, 0x000282E0},
    {lbl_1_rodata_1C28, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_53CC, 0x40040560, 0x00000000, 0x0002A4A0},
    {lbl_1_rodata_53E4, 0x40051990, 0x00000000, 0x000369E4},
    {lbl_1_rodata_53FC, 0x400203A2, 0x00000000, 0x00014828},
    {lbl_1_rodata_5414, 0x400101B6, 0x00000000, 0x00009564},
    {lbl_1_rodata_542C, 0x4003F2A8, 0x00000000, 0x00026994},
    {lbl_1_rodata_5444, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_545C, 0x40014482, 0x00000000, 0x0000CC6C},
    {lbl_1_rodata_5474, 0x4002A7F4, 0x00000000, 0x0001BFE4},
    {lbl_1_rodata_548C, 0x4000E6B8, 0x00000000, 0x00008B44},
    {lbl_1_rodata_54A4, 0x4002EA98, 0x00000000, 0x0001EEC8},
    {lbl_1_rodata_1D2C, 0x40020FDC, 0x00000000, 0x00017938},
    {lbl_1_rodata_1D44, 0x4000DFC0, 0x00000000, 0x0000A1FC},
    {lbl_1_rodata_54BC, 0x40049138, 0x00000000, 0x0002F164},
    {lbl_1_rodata_54D4, 0x40031382, 0x00000000, 0x0001F8DC},
    {lbl_1_rodata_54EC, 0x4005105A, 0x00000000, 0x00030DEC},
    {lbl_1_rodata_5504, 0x4002C1C6, 0x00000000, 0x0001CC24},
    {lbl_1_rodata_551C, 0x40002E32, 0x00000000, 0x00001974},
    {lbl_1_rodata_5534, 0x4001E428, 0x00000000, 0x00010C08},
    {lbl_1_rodata_1DD4, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_554C, 0x4002E522, 0x00000000, 0x0001CD78},
    {lbl_1_rodata_5564, 0x40034EF2, 0x00000000, 0x00021214},
    {lbl_1_rodata_557C, 0x40028D72, 0x00000000, 0x0001A2BC},
    {lbl_1_rodata_5594, 0x40010670, 0x00000000, 0x000094DC},
    {lbl_1_rodata_55AC, 0x4002E65C, 0x00000000, 0x0001A2F0},
    {lbl_1_rodata_55C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_55DC, 0x400094FC, 0x00000000, 0x00004898},
    {lbl_1_rodata_55F4, 0x4001327A, 0x00000000, 0x0000AE18},
    {lbl_1_rodata_560C, 0x4000C15C, 0x00000000, 0x00005F60},
    {lbl_1_rodata_5624, 0x40026034, 0x00000000, 0x00018D34},
    {lbl_1_rodata_1ED8, 0x400195B0, 0x00000000, 0x0000F888},
    {lbl_1_rodata_1EF0, 0x4000E380, 0x00000000, 0x00009378},
    {lbl_1_rodata_563C, 0x40040FD2, 0x00000000, 0x000288D0},
    {lbl_1_rodata_5654, 0x40028B14, 0x00000000, 0x00018898},
    {lbl_1_rodata_566C, 0x4004970A, 0x00000000, 0x0002BF80},
    {lbl_1_rodata_5684, 0x40027110, 0x00000000, 0x00019234},
    {lbl_1_rodata_569C, 0x40003240, 0x00000000, 0x00001D98},
    {lbl_1_rodata_56B4, 0x40021204, 0x00000000, 0x000126C4},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_56CC, 0x400287E0, 0x00000000, 0x000185F8},
    {lbl_1_rodata_56E4, 0x40034F7C, 0x00000000, 0x000208EC},
    {lbl_1_rodata_56FC, 0x4001C13E, 0x00000000, 0x000103B4},
    {lbl_1_rodata_5714, 0x4000A8D6, 0x00000000, 0x000053E4},
    {lbl_1_rodata_572C, 0x4002C7BC, 0x00000000, 0x00018900},
    {lbl_1_rodata_5744, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_575C, 0x4000A956, 0x00000000, 0x000058FC},
    {lbl_1_rodata_5774, 0x400153CE, 0x00000000, 0x0000BDEC},
    {lbl_1_rodata_578C, 0x4000C1D4, 0x00000000, 0x00006160},
    {lbl_1_rodata_57A4, 0x4001F8E2, 0x00000000, 0x00013EC8},
    {lbl_1_rodata_2084, 0x40015CE0, 0x00000000, 0x0000E0D0},
    {lbl_1_rodata_209C, 0x40010700, 0x00000000, 0x00009E1C},
    {lbl_1_rodata_57BC, 0x400263BC, 0x00000000, 0x00017774},
    {lbl_1_rodata_57D4, 0x40011560, 0x00000000, 0x00009CA8},
    {lbl_1_rodata_57EC, 0x4002BEEE, 0x00000000, 0x000182D8},
    {lbl_1_rodata_5804, 0x40018D02, 0x00000000, 0x0000FEC8},
    {lbl_1_rodata_581C, 0x40003542, 0x00000000, 0x00002188},
    {lbl_1_rodata_5834, 0x400111D2, 0x00000000, 0x00009B94},
    {lbl_1_rodata_212C, 0x400338F0, 0x00000000, 0x0001FCB0},
    {lbl_1_rodata_584C, 0x40017428, 0x00000000, 0x0000C900},
    {lbl_1_rodata_5864, 0x4002243A, 0x00000000, 0x000147AC},
    {lbl_1_rodata_587C, 0x40010B90, 0x00000000, 0x000092D8},
    {lbl_1_rodata_5894, 0x40008F30, 0x00000000, 0x0000453C},
    {lbl_1_rodata_58AC, 0x4001D1D0, 0x00000000, 0x0000EAF8},
    {lbl_1_rodata_58C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_58DC, 0x40007FCC, 0x00000000, 0x00003DD4},
    {lbl_1_rodata_58F4, 0x4000F10A, 0x00000000, 0x000088EC},
    {lbl_1_rodata_590C, 0x40006260, 0x00000000, 0x000029C8},
    {lbl_1_rodata_5924, 0x40018028, 0x00000000, 0x0000F504},
    {lbl_1_rodata_2230, 0x40019EF0, 0x00000000, 0x00010BDC},
    {lbl_1_rodata_2248, 0x400118C0, 0x00000000, 0x0000A8D8},
    {lbl_1_rodata_593C, 0x40057EF6, 0x00000000, 0x00037E90},
    {lbl_1_rodata_5954, 0x4002D4BA, 0x00000000, 0x0001B2E8},
    {lbl_1_rodata_596C, 0x4005F900, 0x00000000, 0x00039650},
    {lbl_1_rodata_5984, 0x4003328A, 0x00000000, 0x00020D0C},
    {lbl_1_rodata_599C, 0x4000445C, 0x00000000, 0x00002914},
    {lbl_1_rodata_59B4, 0x4002BB78, 0x00000000, 0x000198BC},
    {lbl_1_rodata_22D8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_59CC, 0x400367B0, 0x00000000, 0x000215C8},
    {lbl_1_rodata_59E4, 0x40046816, 0x00000000, 0x0002C1C0},
    {lbl_1_rodata_59FC, 0x40020532, 0x00000000, 0x00013118},
    {lbl_1_rodata_5A14, 0x4000D9C4, 0x00000000, 0x000071A8},
    {lbl_1_rodata_5A2C, 0x400348B2, 0x00000000, 0x0001DC44},
    {lbl_1_rodata_5A44, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_5A5C, 0x4000CEF0, 0x00000000, 0x00007364},
    {lbl_1_rodata_5A74, 0x4001BA58, 0x00000000, 0x00010264},
    {lbl_1_rodata_5A8C, 0x4000D9EA, 0x00000000, 0x00006DA0},
    {lbl_1_rodata_5AA4, 0x4002A708, 0x00000000, 0x0001B308},
    {lbl_1_rodata_23DC, 0x40016320, 0x00000000, 0x0000E1B8},
    {lbl_1_rodata_23F4, 0x40012C40, 0x00000000, 0x0000B6EC},
    {lbl_1_rodata_5ABC, 0x400458E4, 0x00000000, 0x0002A024},
    {lbl_1_rodata_5AD4, 0x40020E66, 0x00000000, 0x00012FA0},
    {lbl_1_rodata_5AEC, 0x4004D5C8, 0x00000000, 0x0002C2FC},
    {lbl_1_rodata_5B04, 0x40027776, 0x00000000, 0x000171A4},
    {lbl_1_rodata_5B1C, 0x400032EC, 0x00000000, 0x00001EDC},
    {lbl_1_rodata_5B34, 0x4001F090, 0x00000000, 0x000107BC},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_5B4C, 0x4002A278, 0x00000000, 0x000180AC},
    {lbl_1_rodata_5B64, 0x400360EE, 0x00000000, 0x0002033C},
    {lbl_1_rodata_5B7C, 0x4001768C, 0x00000000, 0x0000D18C},
    {lbl_1_rodata_5B94, 0x4000BB46, 0x00000000, 0x00005F20},
    {lbl_1_rodata_5BAC, 0x4002C576, 0x00000000, 0x00017A08},
    {lbl_1_rodata_5BC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_5BDC, 0x4000A4DC, 0x00000000, 0x00005138},
    {lbl_1_rodata_5BF4, 0x4001464C, 0x00000000, 0x0000B2AC},
    {lbl_1_rodata_5C0C, 0x4000A8BE, 0x00000000, 0x00004E84},
    {lbl_1_rodata_5C24, 0x40020A94, 0x00000000, 0x000128C4},
    {lbl_1_rodata_2588, 0x4001D724, 0x00000000, 0x00012518},
    {lbl_1_rodata_25A0, 0x40012F00, 0x00000000, 0x0000AB08},
    {lbl_1_rodata_5C3C, 0x4005D366, 0x00000000, 0x0003C424},
    {lbl_1_rodata_5C54, 0x4002DF2C, 0x00000000, 0x0001C508},
    {lbl_1_rodata_5C6C, 0x40060B9A, 0x00000000, 0x0003A5D4},
    {lbl_1_rodata_5C84, 0x400380CE, 0x00000000, 0x000246B0},
    {lbl_1_rodata_5C9C, 0x40004A8E, 0x00000000, 0x000030B4},
    {lbl_1_rodata_5CB4, 0x400298A0, 0x00000000, 0x00019DFC},
    {lbl_1_rodata_2630, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_5CCC, 0x40036B26, 0x00000000, 0x00021F44},
    {lbl_1_rodata_5CE4, 0x4004DA60, 0x00000000, 0x00031808},
    {lbl_1_rodata_5CFC, 0x40021438, 0x00000000, 0x000139F8},
    {lbl_1_rodata_5D14, 0x4000CF50, 0x00000000, 0x00006E08},
    {lbl_1_rodata_5D2C, 0x40033E76, 0x00000000, 0x0001DDE8},
    {lbl_1_rodata_5D44, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_5D5C, 0x4000C0B2, 0x00000000, 0x00006B48},
    {lbl_1_rodata_5D74, 0x4001AFF8, 0x00000000, 0x00010BD8},
    {lbl_1_rodata_5D8C, 0x4000C984, 0x00000000, 0x000066D0},
    {lbl_1_rodata_5DA4, 0x4002D3D6, 0x00000000, 0x0001D1DC},
    {lbl_1_rodata_2734, 0x40017DE0, 0x00000000, 0x00010298},
    {lbl_1_rodata_274C, 0x4000F020, 0x00000000, 0x00008B10},
    {lbl_1_rodata_5DBC, 0x4003CBF8, 0x00000000, 0x00026744},
    {lbl_1_rodata_5DD4, 0x40021AE4, 0x00000000, 0x00014CF8},
    {lbl_1_rodata_5DEC, 0x40053E92, 0x00000000, 0x000335AC},
    {lbl_1_rodata_5E04, 0x400283FA, 0x00000000, 0x000198E0},
    {lbl_1_rodata_5E1C, 0x4000487E, 0x00000000, 0x00002F20},
    {lbl_1_rodata_5E34, 0x4001D696, 0x00000000, 0x00011754},
    {lbl_1_rodata_27DC, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_5E4C, 0x4002596A, 0x00000000, 0x00016CB4},
    {lbl_1_rodata_5E64, 0x40032728, 0x00000000, 0x0001F8E4},
    {lbl_1_rodata_5E7C, 0x4001969E, 0x00000000, 0x0000F278},
    {lbl_1_rodata_5E94, 0x4000BB26, 0x00000000, 0x000063F8},
    {lbl_1_rodata_5EAC, 0x40030CB0, 0x00000000, 0x0001C030},
    {lbl_1_rodata_5EC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_5EDC, 0x4000BCBA, 0x00000000, 0x00006588},
    {lbl_1_rodata_5EF4, 0x40015AB0, 0x00000000, 0x0000CE94},
    {lbl_1_rodata_5F0C, 0x40006E06, 0x00000000, 0x00003464},
    {lbl_1_rodata_5F24, 0x40021344, 0x00000000, 0x00014A5C},
    {lbl_1_rodata_28E0, 0x4001ABB8, 0x00000000, 0x0001390C},
    {lbl_1_rodata_28F8, 0x4000D5C0, 0x00000000, 0x00008CF0},
    {lbl_1_rodata_5F3C, 0x400511C0, 0x00000000, 0x00033070},
    {lbl_1_rodata_5F54, 0x40029DF6, 0x00000000, 0x0001A77C},
    {lbl_1_rodata_5F6C, 0x40056008, 0x00000000, 0x000356FC},
    {lbl_1_rodata_5F84, 0x40031126, 0x00000000, 0x00020050},
    {lbl_1_rodata_5F9C, 0x40003046, 0x00000000, 0x00001CF4},
    {lbl_1_rodata_5FB4, 0x4001E068, 0x00000000, 0x00011720},
    {lbl_1_rodata_2988, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_5FCC, 0x4002C38C, 0x00000000, 0x0001A994},
    {lbl_1_rodata_5FE4, 0x40045058, 0x00000000, 0x0002B49C},
    {lbl_1_rodata_5FFC, 0x4001D1F8, 0x00000000, 0x00011ED0},
    {lbl_1_rodata_6014, 0x4000BB9E, 0x00000000, 0x00006454},
    {lbl_1_rodata_602C, 0x4002FF30, 0x00000000, 0x0001B748},
    {lbl_1_rodata_6044, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_605C, 0x4000A028, 0x00000000, 0x00005460},
    {lbl_1_rodata_6074, 0x40012554, 0x00000000, 0x0000AEBC},
    {lbl_1_rodata_608C, 0x4000B274, 0x00000000, 0x00005774},
    {lbl_1_rodata_60A4, 0x40026860, 0x00000000, 0x00019188},
    {lbl_1_rodata_2A8C, 0x40022D3C, 0x00000000, 0x00019184},
    {lbl_1_rodata_2AA4, 0x4000FD40, 0x00000000, 0x0000B93C},
    {lbl_1_rodata_60BC, 0x4003B996, 0x00000000, 0x00025900},
    {lbl_1_rodata_60D4, 0x400229E2, 0x00000000, 0x000147AC},
    {lbl_1_rodata_60EC, 0x4003FFC8, 0x00000000, 0x000257DC},
    {lbl_1_rodata_6104, 0x4002C386, 0x00000000, 0x0001C328},
    {lbl_1_rodata_611C, 0x40002F9A, 0x00000000, 0x00001A28},
    {lbl_1_rodata_6134, 0x400182F0, 0x00000000, 0x0000CC9C},
    {lbl_1_rodata_2B34, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_614C, 0x400213EE, 0x00000000, 0x00013540},
    {lbl_1_rodata_6164, 0x40031ECA, 0x00000000, 0x0001F04C},
    {lbl_1_rodata_617C, 0x40018A28, 0x00000000, 0x0000E00C},
    {lbl_1_rodata_6194, 0x4000BDEA, 0x00000000, 0x000061F8},
    {lbl_1_rodata_61AC, 0x40024616, 0x00000000, 0x000130CC},
    {lbl_1_rodata_61C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_61DC, 0x40007B86, 0x00000000, 0x000039A8},
    {lbl_1_rodata_61F4, 0x4000F814, 0x00000000, 0x0000831C},
    {lbl_1_rodata_620C, 0x4000A68C, 0x00000000, 0x00004D44},
    {lbl_1_rodata_6224, 0x400246A6, 0x00000000, 0x00017314},
    {lbl_1_rodata_2C38, 0x4001881C, 0x00000000, 0x00010B50},
    {lbl_1_rodata_2C50, 0x4000F500, 0x00000000, 0x00009DA8},
    {lbl_1_rodata_623C, 0x4005781C, 0x00000000, 0x00037718},
    {lbl_1_rodata_6254, 0x400275C6, 0x00000000, 0x00017994},
    {lbl_1_rodata_626C, 0x400537C0, 0x00000000, 0x0003152C},
    {lbl_1_rodata_6284, 0x4002D706, 0x00000000, 0x0001C6C4},
    {lbl_1_rodata_629C, 0x400033A0, 0x00000000, 0x00001CF4},
    {lbl_1_rodata_62B4, 0x40027F1A, 0x00000000, 0x00018568},
    {lbl_1_rodata_2CE0, 0x4004F674, 0x00000000, 0x0002E878},
    {lbl_1_rodata_62CC, 0x4003316A, 0x00000000, 0x0001EF94},
    {lbl_1_rodata_62E4, 0x40044332, 0x00000000, 0x0002A1E0},
    {lbl_1_rodata_62FC, 0x40019734, 0x00000000, 0x0000EEC4},
    {lbl_1_rodata_6314, 0x4000BA08, 0x00000000, 0x0000610C},
    {lbl_1_rodata_632C, 0x4002BD48, 0x00000000, 0x00017EE0},
    {lbl_1_rodata_6344, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_635C, 0x4000D3D6, 0x00000000, 0x00007510},
    {lbl_1_rodata_6374, 0x4002146A, 0x00000000, 0x000147E0},
    {lbl_1_rodata_638C, 0x40009344, 0x00000000, 0x00004C7C},
    {lbl_1_rodata_63A4, 0x40024B40, 0x00000000, 0x000170B8},
    {lbl_1_rodata_2DE4, 0x400176FC, 0x00000000, 0x0000FEA4},
    {lbl_1_rodata_2DFC, 0x4000F500, 0x00000000, 0x00009D94},
    {lbl_1_rodata_623C, 0x4005781C, 0x00000000, 0x00037718},
    {lbl_1_rodata_6254, 0x400275C6, 0x00000000, 0x00017994},
    {lbl_1_rodata_626C, 0x400537C0, 0x00000000, 0x0003152C},
    {lbl_1_rodata_6284, 0x4002D706, 0x00000000, 0x0001C6C4},
    {lbl_1_rodata_629C, 0x400033A0, 0x00000000, 0x00001CF4},
    {lbl_1_rodata_62B4, 0x40027F1A, 0x00000000, 0x00018568},
    {lbl_1_rodata_2CE0, 0x4004F674, 0x00000000, 0x0002E878},
    {lbl_1_rodata_62CC, 0x4003316A, 0x00000000, 0x0001EF94},
    {lbl_1_rodata_62E4, 0x40044332, 0x00000000, 0x0002A1E0},
    {lbl_1_rodata_62FC, 0x40019734, 0x00000000, 0x0000EEC4},
    {lbl_1_rodata_6314, 0x4000BA08, 0x00000000, 0x0000610C},
    {lbl_1_rodata_632C, 0x4002BD48, 0x00000000, 0x00017EE0},
    {lbl_1_rodata_6344, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_635C, 0x4000D3D6, 0x00000000, 0x00007510},
    {lbl_1_rodata_6374, 0x4002146A, 0x00000000, 0x000147E0},
    {lbl_1_rodata_638C, 0x40009344, 0x00000000, 0x00004C7C},
    {lbl_1_rodata_63A4, 0x40024B40, 0x00000000, 0x000170B8},
    {lbl_1_rodata_2E14, 0x400176FC, 0x00000000, 0x0000FEA4},
    {lbl_1_rodata_2E2C, 0x4000F500, 0x00000000, 0x00009D90},
    {lbl_1_rodata_623C, 0x4005781C, 0x00000000, 0x00037718},
    {lbl_1_rodata_6254, 0x400275C6, 0x00000000, 0x00017994},
    {lbl_1_rodata_626C, 0x400537C0, 0x00000000, 0x0003152C},
    {lbl_1_rodata_6284, 0x4002D706, 0x00000000, 0x0001C6C4},
    {lbl_1_rodata_629C, 0x400033A0, 0x00000000, 0x00001CF4},
    {lbl_1_rodata_62B4, 0x40027F1A, 0x00000000, 0x00018568},
    {lbl_1_rodata_2CE0, 0x4004F674, 0x00000000, 0x0002E878},
    {lbl_1_rodata_62CC, 0x4003316A, 0x00000000, 0x0001EF94},
    {lbl_1_rodata_62E4, 0x40044332, 0x00000000, 0x0002A1E0},
    {lbl_1_rodata_62FC, 0x40019734, 0x00000000, 0x0000EEC4},
    {lbl_1_rodata_6314, 0x4000BA08, 0x00000000, 0x0000610C},
    {lbl_1_rodata_632C, 0x4002BD48, 0x00000000, 0x00017EE0},
    {lbl_1_rodata_6344, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_635C, 0x4000D3D6, 0x00000000, 0x00007510},
    {lbl_1_rodata_6374, 0x4002146A, 0x00000000, 0x000147E0},
    {lbl_1_rodata_638C, 0x40009344, 0x00000000, 0x00004C7C},
    {lbl_1_rodata_63A4, 0x40024B40, 0x00000000, 0x000170B8},
    {lbl_1_rodata_2E44, 0x40011810, 0x00000000, 0x0000BAFC},
    {lbl_1_rodata_2E5C, 0x4000BC80, 0x00000000, 0x00007764},
    {lbl_1_rodata_63BC, 0x4004A62A, 0x00000000, 0x0002FAF0},
    {lbl_1_rodata_63D4, 0x40026690, 0x00000000, 0x0001806C},
    {lbl_1_rodata_63EC, 0x4005235C, 0x00000000, 0x00032A10},
    {lbl_1_rodata_6404, 0x4002B7DC, 0x00000000, 0x0001BC18},
    {lbl_1_rodata_641C, 0x40002620, 0x00000000, 0x00001438},
    {lbl_1_rodata_6434, 0x4001E502, 0x00000000, 0x00011E68},
    {lbl_1_rodata_2EEC, 0x4009C7A4, 0x00000000, 0x0005C22C},
    {lbl_1_rodata_644C, 0x4002E758, 0x00000000, 0x0001C634},
    {lbl_1_rodata_6464, 0x4003AD24, 0x00000000, 0x00025248},
    {lbl_1_rodata_647C, 0x40019A3C, 0x00000000, 0x0000F4A0},
    {lbl_1_rodata_6494, 0x4000A1D0, 0x00000000, 0x000051CC},
    {lbl_1_rodata_64AC, 0x4002D9DC, 0x00000000, 0x00019D60},
    {lbl_1_rodata_64C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_64DC, 0x400094DA, 0x00000000, 0x00004DC0},
    {lbl_1_rodata_64F4, 0x400141EC, 0x00000000, 0x0000C3D4},
    {lbl_1_rodata_650C, 0x4000BBA0, 0x00000000, 0x00005C40},
    {lbl_1_rodata_6524, 0x40021A5E, 0x00000000, 0x000153A4},
    {lbl_1_rodata_2FF0, 0x40011810, 0x00000000, 0x0000BB1C},
    {lbl_1_rodata_3008, 0x4000BC80, 0x00000000, 0x00007784},
    {lbl_1_rodata_63BC, 0x4004A62A, 0x00000000, 0x0002FAF0},
    {lbl_1_rodata_63D4, 0x40026690, 0x00000000, 0x0001806C},
    {lbl_1_rodata_63EC, 0x4005235C, 0x00000000, 0x00032A10},
    {lbl_1_rodata_6404, 0x4002B7DC, 0x00000000, 0x0001BC18},
    {lbl_1_rodata_641C, 0x40002620, 0x00000000, 0x00001438},
    {lbl_1_rodata_6434, 0x4001E502, 0x00000000, 0x00011E68},
    {lbl_1_rodata_2EEC, 0x4009C7A4, 0x00000000, 0x0005C22C},
    {lbl_1_rodata_644C, 0x4002E758, 0x00000000, 0x0001C634},
    {lbl_1_rodata_6464, 0x4003AD24, 0x00000000, 0x00025248},
    {lbl_1_rodata_647C, 0x40019A3C, 0x00000000, 0x0000F4A0},
    {lbl_1_rodata_6494, 0x4000A1D0, 0x00000000, 0x000051CC},
    {lbl_1_rodata_64AC, 0x4002D9DC, 0x00000000, 0x00019D60},
    {lbl_1_rodata_64C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_64DC, 0x400094DA, 0x00000000, 0x00004DC0},
    {lbl_1_rodata_64F4, 0x400141EC, 0x00000000, 0x0000C3D4},
    {lbl_1_rodata_650C, 0x4000BBA0, 0x00000000, 0x00005C40},
    {lbl_1_rodata_6524, 0x40021A5E, 0x00000000, 0x000153A4},
    {lbl_1_rodata_3020, 0x40011810, 0x00000000, 0x0000BB48},
    {lbl_1_rodata_3038, 0x4000BC80, 0x00000000, 0x000077B0},
    {lbl_1_rodata_63BC, 0x4004A62A, 0x00000000, 0x0002FAF0},
    {lbl_1_rodata_63D4, 0x40026690, 0x00000000, 0x0001806C},
    {lbl_1_rodata_63EC, 0x4005235C, 0x00000000, 0x00032A10},
    {lbl_1_rodata_6404, 0x4002B7DC, 0x00000000, 0x0001BC18},
    {lbl_1_rodata_641C, 0x40002620, 0x00000000, 0x00001438},
    {lbl_1_rodata_6434, 0x4001E502, 0x00000000, 0x00011E68},
    {lbl_1_rodata_2EEC, 0x4009C7A4, 0x00000000, 0x0005C22C},
    {lbl_1_rodata_644C, 0x4002E758, 0x00000000, 0x0001C634},
    {lbl_1_rodata_6464, 0x4003AD24, 0x00000000, 0x00025248},
    {lbl_1_rodata_647C, 0x40019A3C, 0x00000000, 0x0000F4A0},
    {lbl_1_rodata_6494, 0x4000A1D0, 0x00000000, 0x000051CC},
    {lbl_1_rodata_64AC, 0x4002D9DC, 0x00000000, 0x00019D60},
    {lbl_1_rodata_64C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_64DC, 0x400094DA, 0x00000000, 0x00004DC0},
    {lbl_1_rodata_64F4, 0x400141EC, 0x00000000, 0x0000C3D4},
    {lbl_1_rodata_650C, 0x4000BBA0, 0x00000000, 0x00005C40},
    {lbl_1_rodata_6524, 0x40021A5E, 0x00000000, 0x000153A4},
    {lbl_1_rodata_3050, 0x4001A71C, 0x00000000, 0x0001128C},
    {lbl_1_rodata_3068, 0x4000F8E0, 0x00000000, 0x000098E4},
    {lbl_1_rodata_653C, 0x4003D09E, 0x00000000, 0x00026BD8},
    {lbl_1_rodata_6554, 0x4001CB5C, 0x00000000, 0x00011928},
    {lbl_1_rodata_656C, 0x4004BA56, 0x00000000, 0x0002DB30},
    {lbl_1_rodata_6584, 0x4001D9BA, 0x00000000, 0x0001275C},
    {lbl_1_rodata_659C, 0x400034E6, 0x00000000, 0x00001EF0},
    {lbl_1_rodata_65B4, 0x4001B818, 0x00000000, 0x0000F9C8},
    {lbl_1_rodata_30F8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_65CC, 0x40024AC6, 0x00000000, 0x000161B0},
    {lbl_1_rodata_65E4, 0x40033428, 0x00000000, 0x0001FF84},
    {lbl_1_rodata_65FC, 0x40013EBC, 0x00000000, 0x0000B978},
    {lbl_1_rodata_6614, 0x4000A3F0, 0x00000000, 0x000051B4},
    {lbl_1_rodata_662C, 0x40029748, 0x00000000, 0x00017464},
    {lbl_1_rodata_6644, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_665C, 0x40008E8E, 0x00000000, 0x00004890},
    {lbl_1_rodata_6674, 0x40010250, 0x00000000, 0x00009470},
    {lbl_1_rodata_668C, 0x4000C09C, 0x00000000, 0x0000613C},
    {lbl_1_rodata_66A4, 0x40018694, 0x00000000, 0x0000F23C},
    {lbl_1_rodata_31FC, 0x4001CE58, 0x00000000, 0x000132DC},
    {lbl_1_rodata_3214, 0x4000FE80, 0x00000000, 0x0000A0FC},
    {lbl_1_rodata_66BC, 0x4003EA32, 0x00000000, 0x00026D14},
    {lbl_1_rodata_66D4, 0x4001ED2C, 0x00000000, 0x0001206C},
    {lbl_1_rodata_66EC, 0x4004EA54, 0x00000000, 0x0002EE10},
    {lbl_1_rodata_6704, 0x4002275A, 0x00000000, 0x00015F34},
    {lbl_1_rodata_671C, 0x40002CD0, 0x00000000, 0x00001A20},
    {lbl_1_rodata_6734, 0x4001B8A4, 0x00000000, 0x0000F6B0},
    {lbl_1_rodata_32A4, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_674C, 0x40028976, 0x00000000, 0x0001830C},
    {lbl_1_rodata_6764, 0x40034E38, 0x00000000, 0x00020530},
    {lbl_1_rodata_677C, 0x4001A288, 0x00000000, 0x0000F210},
    {lbl_1_rodata_6794, 0x4000C7EC, 0x00000000, 0x0000690C},
    {lbl_1_rodata_67AC, 0x4002C5BA, 0x00000000, 0x00018BD0},
    {lbl_1_rodata_67C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_67DC, 0x4000A3F8, 0x00000000, 0x000055E4},
    {lbl_1_rodata_67F4, 0x40011862, 0x00000000, 0x0000A168},
    {lbl_1_rodata_680C, 0x4000A984, 0x00000000, 0x00004FF8},
    {lbl_1_rodata_6824, 0x4001E0E0, 0x00000000, 0x00012E10},
    {lbl_1_rodata_33A8, 0x400195B0, 0x00000000, 0x0000F9DC},
    {lbl_1_rodata_33C0, 0x4000E380, 0x00000000, 0x0000961C},
    {lbl_1_rodata_563C, 0x40040FD2, 0x00000000, 0x000288D0},
    {lbl_1_rodata_5654, 0x40028B14, 0x00000000, 0x00018898},
    {lbl_1_rodata_566C, 0x4004970A, 0x00000000, 0x0002BF80},
    {lbl_1_rodata_5684, 0x40027110, 0x00000000, 0x00019234},
    {lbl_1_rodata_569C, 0x40003240, 0x00000000, 0x00001D98},
    {lbl_1_rodata_56B4, 0x40021204, 0x00000000, 0x000126C4},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_56CC, 0x400287E0, 0x00000000, 0x000185F8},
    {lbl_1_rodata_56E4, 0x40034F7C, 0x00000000, 0x000208EC},
    {lbl_1_rodata_56FC, 0x4001C13E, 0x00000000, 0x000103B4},
    {lbl_1_rodata_5714, 0x4000A8D6, 0x00000000, 0x000053E4},
    {lbl_1_rodata_572C, 0x4002C7BC, 0x00000000, 0x00018900},
    {lbl_1_rodata_5744, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_575C, 0x4000A956, 0x00000000, 0x000058FC},
    {lbl_1_rodata_5774, 0x400153CE, 0x00000000, 0x0000BDEC},
    {lbl_1_rodata_578C, 0x4000C1D4, 0x00000000, 0x00006160},
    {lbl_1_rodata_57A4, 0x4001F8E2, 0x00000000, 0x00013EC8},
    {lbl_1_rodata_33D8, 0x400195B0, 0x00000000, 0x0000F9BC},
    {lbl_1_rodata_33F0, 0x4000E380, 0x00000000, 0x00009368},
    {lbl_1_rodata_563C, 0x40040FD2, 0x00000000, 0x000288D0},
    {lbl_1_rodata_5654, 0x40028B14, 0x00000000, 0x00018898},
    {lbl_1_rodata_566C, 0x4004970A, 0x00000000, 0x0002BF80},
    {lbl_1_rodata_5684, 0x40027110, 0x00000000, 0x00019234},
    {lbl_1_rodata_569C, 0x40003240, 0x00000000, 0x00001D98},
    {lbl_1_rodata_56B4, 0x40021204, 0x00000000, 0x000126C4},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_56CC, 0x400287E0, 0x00000000, 0x000185F8},
    {lbl_1_rodata_56E4, 0x40034F7C, 0x00000000, 0x000208EC},
    {lbl_1_rodata_56FC, 0x4001C13E, 0x00000000, 0x000103B4},
    {lbl_1_rodata_5714, 0x4000A8D6, 0x00000000, 0x000053E4},
    {lbl_1_rodata_572C, 0x4002C7BC, 0x00000000, 0x00018900},
    {lbl_1_rodata_5744, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_575C, 0x4000A956, 0x00000000, 0x000058FC},
    {lbl_1_rodata_5774, 0x400153CE, 0x00000000, 0x0000BDEC},
    {lbl_1_rodata_578C, 0x4000C1D4, 0x00000000, 0x00006160},
    {lbl_1_rodata_57A4, 0x4001F8E2, 0x00000000, 0x00013EC8},
    {lbl_1_rodata_3408, 0x400195B0, 0x00000000, 0x0000F8B0},
    {lbl_1_rodata_3420, 0x4000E380, 0x00000000, 0x0000926C},
    {lbl_1_rodata_563C, 0x40040FD2, 0x00000000, 0x000288D0},
    {lbl_1_rodata_5654, 0x40028B14, 0x00000000, 0x00018898},
    {lbl_1_rodata_566C, 0x4004970A, 0x00000000, 0x0002BF80},
    {lbl_1_rodata_5684, 0x40027110, 0x00000000, 0x00019234},
    {lbl_1_rodata_569C, 0x40003240, 0x00000000, 0x00001D98},
    {lbl_1_rodata_56B4, 0x40021204, 0x00000000, 0x000126C4},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_56CC, 0x400287E0, 0x00000000, 0x000185F8},
    {lbl_1_rodata_56E4, 0x40034F7C, 0x00000000, 0x000208EC},
    {lbl_1_rodata_56FC, 0x4001C13E, 0x00000000, 0x000103B4},
    {lbl_1_rodata_5714, 0x4000A8D6, 0x00000000, 0x000053E4},
    {lbl_1_rodata_572C, 0x4002C7BC, 0x00000000, 0x00018900},
    {lbl_1_rodata_5744, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_575C, 0x4000A956, 0x00000000, 0x000058FC},
    {lbl_1_rodata_5774, 0x400153CE, 0x00000000, 0x0000BDEC},
    {lbl_1_rodata_578C, 0x4000C1D4, 0x00000000, 0x00006160},
    {lbl_1_rodata_57A4, 0x4001F8E2, 0x00000000, 0x00013EC8},
    {lbl_1_rodata_3438, 0x400195B0, 0x00000000, 0x0000F8B0},
    {lbl_1_rodata_3450, 0x4000E380, 0x00000000, 0x00009278},
    {lbl_1_rodata_563C, 0x40040FD2, 0x00000000, 0x000288D0},
    {lbl_1_rodata_5654, 0x40028B14, 0x00000000, 0x00018898},
    {lbl_1_rodata_566C, 0x4004970A, 0x00000000, 0x0002BF80},
    {lbl_1_rodata_5684, 0x40027110, 0x00000000, 0x00019234},
    {lbl_1_rodata_569C, 0x40003240, 0x00000000, 0x00001D98},
    {lbl_1_rodata_56B4, 0x40021204, 0x00000000, 0x000126C4},
    {lbl_1_rodata_1F80, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_56CC, 0x400287E0, 0x00000000, 0x000185F8},
    {lbl_1_rodata_56E4, 0x40034F7C, 0x00000000, 0x000208EC},
    {lbl_1_rodata_56FC, 0x4001C13E, 0x00000000, 0x000103B4},
    {lbl_1_rodata_5714, 0x4000A8D6, 0x00000000, 0x000053E4},
    {lbl_1_rodata_572C, 0x4002C7BC, 0x00000000, 0x00018900},
    {lbl_1_rodata_5744, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_575C, 0x4000A956, 0x00000000, 0x000058FC},
    {lbl_1_rodata_5774, 0x400153CE, 0x00000000, 0x0000BDEC},
    {lbl_1_rodata_578C, 0x4000C1D4, 0x00000000, 0x00006160},
    {lbl_1_rodata_57A4, 0x4001F8E2, 0x00000000, 0x00013EC8},
    {lbl_1_rodata_3468, 0x400150EC, 0x00000000, 0x0000DD9C},
    {lbl_1_rodata_3480, 0x4000F000, 0x00000000, 0x00009BF8},
    {lbl_1_rodata_683C, 0x40049E14, 0x00000000, 0x0002EB64},
    {lbl_1_rodata_6854, 0x40027298, 0x00000000, 0x0001892C},
    {lbl_1_rodata_686C, 0x40054A5E, 0x00000000, 0x00033308},
    {lbl_1_rodata_6884, 0x4002A87C, 0x00000000, 0x0001B6D8},
    {lbl_1_rodata_689C, 0x40002DC4, 0x00000000, 0x00001B18},
    {lbl_1_rodata_68B4, 0x40023C14, 0x00000000, 0x00015948},
    {lbl_1_rodata_3510, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_68CC, 0x4002DC16, 0x00000000, 0x0001BB68},
    {lbl_1_rodata_68E4, 0x4003BDA4, 0x00000000, 0x0002535C},
    {lbl_1_rodata_68FC, 0x4001D84C, 0x00000000, 0x00011AE4},
    {lbl_1_rodata_6914, 0x4000E09A, 0x00000000, 0x00007BB0},
    {lbl_1_rodata_692C, 0x40031D66, 0x00000000, 0x0001C7FC},
    {lbl_1_rodata_6944, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_695C, 0x4000B4A4, 0x00000000, 0x000064C4},
    {lbl_1_rodata_6974, 0x40018C14, 0x00000000, 0x0000F6E0},
    {lbl_1_rodata_698C, 0x4000B88E, 0x00000000, 0x00005B3C},
    {lbl_1_rodata_69A4, 0x40022658, 0x00000000, 0x00015F24},
    {lbl_1_rodata_3614, 0x400150EC, 0x00000000, 0x0000DD6C},
    {lbl_1_rodata_362C, 0x4000F000, 0x00000000, 0x00009BCC},
    {lbl_1_rodata_683C, 0x40049E14, 0x00000000, 0x0002EB64},
    {lbl_1_rodata_6854, 0x40027298, 0x00000000, 0x0001892C},
    {lbl_1_rodata_686C, 0x40054A5E, 0x00000000, 0x00033308},
    {lbl_1_rodata_6884, 0x4002A87C, 0x00000000, 0x0001B6D8},
    {lbl_1_rodata_689C, 0x40002DC4, 0x00000000, 0x00001B18},
    {lbl_1_rodata_68B4, 0x40023C14, 0x00000000, 0x00015948},
    {lbl_1_rodata_3510, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_68CC, 0x4002DC16, 0x00000000, 0x0001BB68},
    {lbl_1_rodata_68E4, 0x4003BDA4, 0x00000000, 0x0002535C},
    {lbl_1_rodata_68FC, 0x4001D84C, 0x00000000, 0x00011AE4},
    {lbl_1_rodata_6914, 0x4000E09A, 0x00000000, 0x00007BB0},
    {lbl_1_rodata_692C, 0x40031D66, 0x00000000, 0x0001C7FC},
    {lbl_1_rodata_6944, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_695C, 0x4000B4A4, 0x00000000, 0x000064C4},
    {lbl_1_rodata_6974, 0x40018C14, 0x00000000, 0x0000F6E0},
    {lbl_1_rodata_698C, 0x4000B88E, 0x00000000, 0x00005B3C},
    {lbl_1_rodata_69A4, 0x40022658, 0x00000000, 0x00015F24},
    {lbl_1_rodata_3644, 0x400150EC, 0x00000000, 0x0000DD50},
    {lbl_1_rodata_365C, 0x4000F000, 0x00000000, 0x00009BAC},
    {lbl_1_rodata_683C, 0x40049E14, 0x00000000, 0x0002EB64},
    {lbl_1_rodata_6854, 0x40027298, 0x00000000, 0x0001892C},
    {lbl_1_rodata_686C, 0x40054A5E, 0x00000000, 0x00033308},
    {lbl_1_rodata_6884, 0x4002A87C, 0x00000000, 0x0001B6D8},
    {lbl_1_rodata_689C, 0x40002DC4, 0x00000000, 0x00001B18},
    {lbl_1_rodata_68B4, 0x40023C14, 0x00000000, 0x00015948},
    {lbl_1_rodata_3510, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_68CC, 0x4002DC16, 0x00000000, 0x0001BB68},
    {lbl_1_rodata_68E4, 0x4003BDA4, 0x00000000, 0x0002535C},
    {lbl_1_rodata_68FC, 0x4001D84C, 0x00000000, 0x00011AE4},
    {lbl_1_rodata_6914, 0x4000E09A, 0x00000000, 0x00007BB0},
    {lbl_1_rodata_692C, 0x40031D66, 0x00000000, 0x0001C7FC},
    {lbl_1_rodata_6944, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_695C, 0x4000B4A4, 0x00000000, 0x000064C4},
    {lbl_1_rodata_6974, 0x40018C14, 0x00000000, 0x0000F6E0},
    {lbl_1_rodata_698C, 0x4000B88E, 0x00000000, 0x00005B3C},
    {lbl_1_rodata_69A4, 0x40022658, 0x00000000, 0x00015F24},
    {lbl_1_rodata_3674, 0x400150EC, 0x00000000, 0x0000DE80},
    {lbl_1_rodata_368C, 0x4000F000, 0x00000000, 0x00009CDC},
    {lbl_1_rodata_683C, 0x40049E14, 0x00000000, 0x0002EB64},
    {lbl_1_rodata_6854, 0x40027298, 0x00000000, 0x0001892C},
    {lbl_1_rodata_686C, 0x40054A5E, 0x00000000, 0x00033308},
    {lbl_1_rodata_6884, 0x4002A87C, 0x00000000, 0x0001B6D8},
    {lbl_1_rodata_689C, 0x40002DC4, 0x00000000, 0x00001B18},
    {lbl_1_rodata_68B4, 0x40023C14, 0x00000000, 0x00015948},
    {lbl_1_rodata_3510, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_68CC, 0x4002DC16, 0x00000000, 0x0001BB68},
    {lbl_1_rodata_68E4, 0x4003BDA4, 0x00000000, 0x0002535C},
    {lbl_1_rodata_68FC, 0x4001D84C, 0x00000000, 0x00011AE4},
    {lbl_1_rodata_6914, 0x4000E09A, 0x00000000, 0x00007BB0},
    {lbl_1_rodata_692C, 0x40031D66, 0x00000000, 0x0001C7FC},
    {lbl_1_rodata_6944, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_695C, 0x4000B4A4, 0x00000000, 0x000064C4},
    {lbl_1_rodata_6974, 0x40018C14, 0x00000000, 0x0000F6E0},
    {lbl_1_rodata_698C, 0x4000B88E, 0x00000000, 0x00005B3C},
    {lbl_1_rodata_69A4, 0x40022658, 0x00000000, 0x00015F24},
    {lbl_1_rodata_36A4, 0x40017300, 0x00000000, 0x0000F260},
    {lbl_1_rodata_36BC, 0x40011D40, 0x00000000, 0x0000AED0},
    {lbl_1_rodata_69BC, 0x4002D4D6, 0x00000000, 0x0001C5A4},
    {lbl_1_rodata_69D4, 0x40015DEE, 0x00000000, 0x0000CFE0},
    {lbl_1_rodata_69EC, 0x4002DB4C, 0x00000000, 0x00018E78},
    {lbl_1_rodata_6A04, 0x40019FE2, 0x00000000, 0x00010C58},
    {lbl_1_rodata_6A1C, 0x40003542, 0x00000000, 0x00002188},
    {lbl_1_rodata_6A34, 0x400108C2, 0x00000000, 0x00009730},
    {lbl_1_rodata_374C, 0x4009C9B8, 0x00000000, 0x0005C2D0},
    {lbl_1_rodata_6A4C, 0x4001E53A, 0x00000000, 0x000116C8},
    {lbl_1_rodata_6A64, 0x4002241E, 0x00000000, 0x000147A4},
    {lbl_1_rodata_6A7C, 0x40010B90, 0x00000000, 0x000092D8},
    {lbl_1_rodata_6A94, 0x40008F30, 0x00000000, 0x0000453C},
    {lbl_1_rodata_6AAC, 0x4001D1D0, 0x00000000, 0x0000EAF8},
    {lbl_1_rodata_6AC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_6ADC, 0x40007FCC, 0x00000000, 0x00003DD4},
    {lbl_1_rodata_6AF4, 0x4000F10A, 0x00000000, 0x000088EC},
    {lbl_1_rodata_6B0C, 0x40004D48, 0x00000000, 0x00001A78},
    {lbl_1_rodata_6B24, 0x400188F6, 0x00000000, 0x0000FBD8},
    {lbl_1_rodata_3850, 0x400196C0, 0x00000000, 0x000126C0},
    {lbl_1_rodata_3868, 0x40010B60, 0x00000000, 0x0000B3F4},
    {lbl_1_rodata_6B3C, 0x4005DC16, 0x00000000, 0x00038DAC},
    {lbl_1_rodata_6B54, 0x40034C00, 0x00000000, 0x0001E9A4},
    {lbl_1_rodata_6B6C, 0x4005E28A, 0x00000000, 0x00034A04},
    {lbl_1_rodata_6B84, 0x4003DFD2, 0x00000000, 0x00025B94},
    {lbl_1_rodata_6B9C, 0x40002920, 0x00000000, 0x000015AC},
    {lbl_1_rodata_6BB4, 0x4002B206, 0x00000000, 0x00018DDC},
    {lbl_1_rodata_38F8, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_6BCC, 0x4003AFA0, 0x00000000, 0x00022830},
    {lbl_1_rodata_6BE4, 0x4004973E, 0x00000000, 0x0002BE60},
    {lbl_1_rodata_6BFC, 0x40026E14, 0x00000000, 0x00016560},
    {lbl_1_rodata_6C14, 0x4000CAC8, 0x00000000, 0x000066B4},
    {lbl_1_rodata_6C2C, 0x4003594A, 0x00000000, 0x0001C83C},
    {lbl_1_rodata_6C44, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_6C5C, 0x4000DD92, 0x00000000, 0x00007374},
    {lbl_1_rodata_6C74, 0x4001D630, 0x00000000, 0x000111C0},
    {lbl_1_rodata_6C8C, 0x4000C4E0, 0x00000000, 0x00005BBC},
    {lbl_1_rodata_6CA4, 0x40030736, 0x00000000, 0x0001CAEC},
    {lbl_1_rodata_39FC, 0x4001F27C, 0x00000000, 0x000154D0},
    {lbl_1_rodata_3A14, 0x40012B00, 0x00000000, 0x0000C0A4},
    {lbl_1_rodata_6CBC, 0x4005DE26, 0x00000000, 0x0003CDD8},
    {lbl_1_rodata_6CD4, 0x4002C266, 0x00000000, 0x0001B364},
    {lbl_1_rodata_6CEC, 0x40063F5E, 0x00000000, 0x0003CA20},
    {lbl_1_rodata_6D04, 0x4003797E, 0x00000000, 0x0002449C},
    {lbl_1_rodata_6D1C, 0x40004BAC, 0x00000000, 0x00002FE0},
    {lbl_1_rodata_6D34, 0x4002A402, 0x00000000, 0x00019B20},
    {lbl_1_rodata_3AA4, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_6D4C, 0x4003A81A, 0x00000000, 0x00024E1C},
    {lbl_1_rodata_6D64, 0x4004C49A, 0x00000000, 0x00030B2C},
    {lbl_1_rodata_6D7C, 0x4001FD10, 0x00000000, 0x00012AC0},
    {lbl_1_rodata_6D94, 0x4000ECCE, 0x00000000, 0x000080A8},
    {lbl_1_rodata_6DAC, 0x400358B2, 0x00000000, 0x0001E9D4},
    {lbl_1_rodata_6DC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_6DDC, 0x4000D5B0, 0x00000000, 0x00007A18},
    {lbl_1_rodata_6DF4, 0x4002085C, 0x00000000, 0x000143AC},
    {lbl_1_rodata_6E0C, 0x400093AE, 0x00000000, 0x0000474C},
    {lbl_1_rodata_6E24, 0x4002CE76, 0x00000000, 0x0001D144},
    {lbl_1_rodata_3BA8, 0x400118C8, 0x00000000, 0x0000D7B8},
    {lbl_1_rodata_3BC0, 0x40007C20, 0x00000000, 0x000052E8},
    {lbl_1_rodata_6E3C, 0x40041B10, 0x00000000, 0x00028878},
    {lbl_1_rodata_6E54, 0x4001D6F4, 0x00000000, 0x00011378},
    {lbl_1_rodata_6E6C, 0x40047664, 0x00000000, 0x0002A50C},
    {lbl_1_rodata_6E84, 0x40021F52, 0x00000000, 0x000156BC},
    {lbl_1_rodata_6E9C, 0x400030E2, 0x00000000, 0x00001C34},
    {lbl_1_rodata_6EB4, 0x4001F04E, 0x00000000, 0x00010888},
    {lbl_1_rodata_3C50, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_6ECC, 0x400296AC, 0x00000000, 0x00018924},
    {lbl_1_rodata_6EE4, 0x400347F4, 0x00000000, 0x0001FD6C},
    {lbl_1_rodata_6EFC, 0x40016ED4, 0x00000000, 0x0000D008},
    {lbl_1_rodata_6F14, 0x4000AA58, 0x00000000, 0x00005630},
    {lbl_1_rodata_6F2C, 0x4002F530, 0x00000000, 0x0001A5B8},
    {lbl_1_rodata_6F44, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_6F5C, 0x4000AA9C, 0x00000000, 0x00005AE0},
    {lbl_1_rodata_6F74, 0x40014292, 0x00000000, 0x0000AD54},
    {lbl_1_rodata_6F8C, 0x4000B870, 0x00000000, 0x00005714},
    {lbl_1_rodata_6FA4, 0x4001AE56, 0x00000000, 0x00010988},
    {lbl_1_rodata_3D54, 0x40018028, 0x00000000, 0x00012FD0},
    {lbl_1_rodata_3D6C, 0x4000A1E0, 0x00000000, 0x00006CCC},
    {lbl_1_rodata_6FBC, 0x4004F4A8, 0x00000000, 0x0002FAF4},
    {lbl_1_rodata_6FD4, 0x4002BCF0, 0x00000000, 0x000192D4},
    {lbl_1_rodata_6FEC, 0x40059A24, 0x00000000, 0x0003356C},
    {lbl_1_rodata_7004, 0x4002CCBE, 0x00000000, 0x0001AE14},
    {lbl_1_rodata_701C, 0x40004272, 0x00000000, 0x00002470},
    {lbl_1_rodata_7034, 0x4002BD44, 0x00000000, 0x00017730},
    {lbl_1_rodata_3DFC, 0x4009C7A8, 0x00000000, 0x0005C1DC},
    {lbl_1_rodata_704C, 0x4002FBC0, 0x00000000, 0x0001B5F0},
    {lbl_1_rodata_7064, 0x40040DCE, 0x00000000, 0x000269B0},
    {lbl_1_rodata_707C, 0x40020A8A, 0x00000000, 0x000123B4},
    {lbl_1_rodata_7094, 0x4000D5C8, 0x00000000, 0x00007070},
    {lbl_1_rodata_70AC, 0x4003A152, 0x00000000, 0x00020228},
    {lbl_1_rodata_70C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_70DC, 0x4000E134, 0x00000000, 0x00007100},
    {lbl_1_rodata_70F4, 0x4001EFB4, 0x00000000, 0x00010D88},
    {lbl_1_rodata_710C, 0x4000D24C, 0x00000000, 0x00006478},
    {lbl_1_rodata_7124, 0x4002656A, 0x00000000, 0x00017164},
    {lbl_1_rodata_3F00, 0x40020FDC, 0x00000000, 0x00017934},
    {lbl_1_rodata_3F18, 0x4000DFC0, 0x00000000, 0x0000A1F4},
    {lbl_1_rodata_54BC, 0x40049138, 0x00000000, 0x0002F164},
    {lbl_1_rodata_54D4, 0x40031382, 0x00000000, 0x0001F8DC},
    {lbl_1_rodata_54EC, 0x4005105A, 0x00000000, 0x00030DEC},
    {lbl_1_rodata_5504, 0x4002C1C6, 0x00000000, 0x0001CC24},
    {lbl_1_rodata_551C, 0x40002E32, 0x00000000, 0x00001974},
    {lbl_1_rodata_5534, 0x4001E428, 0x00000000, 0x00010C08},
    {lbl_1_rodata_1DD4, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_554C, 0x4002E522, 0x00000000, 0x0001CD78},
    {lbl_1_rodata_5564, 0x40034EF2, 0x00000000, 0x00021214},
    {lbl_1_rodata_557C, 0x40028D72, 0x00000000, 0x0001A2BC},
    {lbl_1_rodata_5594, 0x40010670, 0x00000000, 0x000094DC},
    {lbl_1_rodata_55AC, 0x4002E65C, 0x00000000, 0x0001A2F0},
    {lbl_1_rodata_55C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_55DC, 0x400094FC, 0x00000000, 0x00004898},
    {lbl_1_rodata_55F4, 0x4001327A, 0x00000000, 0x0000AE18},
    {lbl_1_rodata_560C, 0x4000C15C, 0x00000000, 0x00005F60},
    {lbl_1_rodata_5624, 0x40026034, 0x00000000, 0x00018D34},
    {lbl_1_rodata_3F30, 0x40022D3C, 0x00000000, 0x000191A4},
    {lbl_1_rodata_3F48, 0x4000FD40, 0x00000000, 0x0000B958},
    {lbl_1_rodata_60BC, 0x4003B996, 0x00000000, 0x00025900},
    {lbl_1_rodata_60D4, 0x400229E2, 0x00000000, 0x000147AC},
    {lbl_1_rodata_60EC, 0x4003FFC8, 0x00000000, 0x000257DC},
    {lbl_1_rodata_6104, 0x4002C386, 0x00000000, 0x0001C328},
    {lbl_1_rodata_611C, 0x40002F9A, 0x00000000, 0x00001A28},
    {lbl_1_rodata_6134, 0x400182F0, 0x00000000, 0x0000CC9C},
    {lbl_1_rodata_2B34, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_614C, 0x400213EE, 0x00000000, 0x00013540},
    {lbl_1_rodata_6164, 0x40031ECA, 0x00000000, 0x0001F04C},
    {lbl_1_rodata_617C, 0x40018A28, 0x00000000, 0x0000E00C},
    {lbl_1_rodata_6194, 0x4000BDEA, 0x00000000, 0x000061F8},
    {lbl_1_rodata_61AC, 0x40024616, 0x00000000, 0x000130CC},
    {lbl_1_rodata_61C4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_61DC, 0x40007B86, 0x00000000, 0x000039A8},
    {lbl_1_rodata_61F4, 0x4000F814, 0x00000000, 0x0000831C},
    {lbl_1_rodata_620C, 0x4000A68C, 0x00000000, 0x00004D44},
    {lbl_1_rodata_6224, 0x400246A6, 0x00000000, 0x00017314},
    {lbl_1_rodata_3F60, 0x40016320, 0x00000000, 0x0000E1BC},
    {lbl_1_rodata_3F78, 0x40012C40, 0x00000000, 0x0000B6F0},
    {lbl_1_rodata_5ABC, 0x400458E4, 0x00000000, 0x0002A024},
    {lbl_1_rodata_5AD4, 0x40020E66, 0x00000000, 0x00012FA0},
    {lbl_1_rodata_5AEC, 0x4004D5C8, 0x00000000, 0x0002C2FC},
    {lbl_1_rodata_5B04, 0x40027776, 0x00000000, 0x000171A4},
    {lbl_1_rodata_5B1C, 0x400032EC, 0x00000000, 0x00001EDC},
    {lbl_1_rodata_5B34, 0x4001F090, 0x00000000, 0x000107BC},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_5B4C, 0x4002A278, 0x00000000, 0x000180AC},
    {lbl_1_rodata_5B64, 0x400360EE, 0x00000000, 0x0002033C},
    {lbl_1_rodata_5B7C, 0x4001768C, 0x00000000, 0x0000D18C},
    {lbl_1_rodata_5B94, 0x4000BB46, 0x00000000, 0x00005F20},
    {lbl_1_rodata_5BAC, 0x4002C576, 0x00000000, 0x00017A08},
    {lbl_1_rodata_5BC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_5BDC, 0x4000A4DC, 0x00000000, 0x00005138},
    {lbl_1_rodata_5BF4, 0x4001464C, 0x00000000, 0x0000B2AC},
    {lbl_1_rodata_5C0C, 0x4000A8BE, 0x00000000, 0x00004E84},
    {lbl_1_rodata_5C24, 0x40020A94, 0x00000000, 0x000128C4},
    {lbl_1_rodata_3F90, 0x40016320, 0x00000000, 0x0000E198},
    {lbl_1_rodata_3FA8, 0x40012C40, 0x00000000, 0x0000B6CC},
    {lbl_1_rodata_5ABC, 0x400458E4, 0x00000000, 0x0002A024},
    {lbl_1_rodata_5AD4, 0x40020E66, 0x00000000, 0x00012FA0},
    {lbl_1_rodata_5AEC, 0x4004D5C8, 0x00000000, 0x0002C2FC},
    {lbl_1_rodata_5B04, 0x40027776, 0x00000000, 0x000171A4},
    {lbl_1_rodata_5B1C, 0x400032EC, 0x00000000, 0x00001EDC},
    {lbl_1_rodata_5B34, 0x4001F090, 0x00000000, 0x000107BC},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_5B4C, 0x4002A278, 0x00000000, 0x000180AC},
    {lbl_1_rodata_5B64, 0x400360EE, 0x00000000, 0x0002033C},
    {lbl_1_rodata_5B7C, 0x4001768C, 0x00000000, 0x0000D18C},
    {lbl_1_rodata_5B94, 0x4000BB46, 0x00000000, 0x00005F20},
    {lbl_1_rodata_5BAC, 0x4002C576, 0x00000000, 0x00017A08},
    {lbl_1_rodata_5BC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_5BDC, 0x4000A4DC, 0x00000000, 0x00005138},
    {lbl_1_rodata_5BF4, 0x4001464C, 0x00000000, 0x0000B2AC},
    {lbl_1_rodata_5C0C, 0x4000A8BE, 0x00000000, 0x00004E84},
    {lbl_1_rodata_5C24, 0x40020A94, 0x00000000, 0x000128C4},
    {lbl_1_rodata_3FC0, 0x40016320, 0x00000000, 0x0000E1C4},
    {lbl_1_rodata_3FD8, 0x40012C40, 0x00000000, 0x0000B6F8},
    {lbl_1_rodata_5ABC, 0x400458E4, 0x00000000, 0x0002A024},
    {lbl_1_rodata_5AD4, 0x40020E66, 0x00000000, 0x00012FA0},
    {lbl_1_rodata_5AEC, 0x4004D5C8, 0x00000000, 0x0002C2FC},
    {lbl_1_rodata_5B04, 0x40027776, 0x00000000, 0x000171A4},
    {lbl_1_rodata_5B1C, 0x400032EC, 0x00000000, 0x00001EDC},
    {lbl_1_rodata_5B34, 0x4001F090, 0x00000000, 0x000107BC},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_5B4C, 0x4002A278, 0x00000000, 0x000180AC},
    {lbl_1_rodata_5B64, 0x400360EE, 0x00000000, 0x0002033C},
    {lbl_1_rodata_5B7C, 0x4001768C, 0x00000000, 0x0000D18C},
    {lbl_1_rodata_5B94, 0x4000BB46, 0x00000000, 0x00005F20},
    {lbl_1_rodata_5BAC, 0x4002C576, 0x00000000, 0x00017A08},
    {lbl_1_rodata_5BC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_5BDC, 0x4000A4DC, 0x00000000, 0x00005138},
    {lbl_1_rodata_5BF4, 0x4001464C, 0x00000000, 0x0000B2AC},
    {lbl_1_rodata_5C0C, 0x4000A8BE, 0x00000000, 0x00004E84},
    {lbl_1_rodata_5C24, 0x40020A94, 0x00000000, 0x000128C4},
    {lbl_1_rodata_3FF0, 0x40016320, 0x00000000, 0x0000E0FC},
    {lbl_1_rodata_4008, 0x40012C40, 0x00000000, 0x0000B630},
    {lbl_1_rodata_5ABC, 0x400458E4, 0x00000000, 0x0002A024},
    {lbl_1_rodata_5AD4, 0x40020E66, 0x00000000, 0x00012FA0},
    {lbl_1_rodata_5AEC, 0x4004D5C8, 0x00000000, 0x0002C2FC},
    {lbl_1_rodata_5B04, 0x40027776, 0x00000000, 0x000171A4},
    {lbl_1_rodata_5B1C, 0x400032EC, 0x00000000, 0x00001EDC},
    {lbl_1_rodata_5B34, 0x4001F090, 0x00000000, 0x000107BC},
    {lbl_1_rodata_2484, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_5B4C, 0x4002A278, 0x00000000, 0x000180AC},
    {lbl_1_rodata_5B64, 0x400360EE, 0x00000000, 0x0002033C},
    {lbl_1_rodata_5B7C, 0x4001768C, 0x00000000, 0x0000D18C},
    {lbl_1_rodata_5B94, 0x4000BB46, 0x00000000, 0x00005F20},
    {lbl_1_rodata_5BAC, 0x4002C576, 0x00000000, 0x00017A08},
    {lbl_1_rodata_5BC4, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_5BDC, 0x4000A4DC, 0x00000000, 0x00005138},
    {lbl_1_rodata_5BF4, 0x4001464C, 0x00000000, 0x0000B2AC},
    {lbl_1_rodata_5C0C, 0x4000A8BE, 0x00000000, 0x00004E84},
    {lbl_1_rodata_5C24, 0x40020A94, 0x00000000, 0x000128C4},
    {lbl_1_rodata_4020, 0x40012910, 0x00000000, 0x0000CF04},
    {lbl_1_rodata_4038, 0x4000D4C0, 0x00000000, 0x000089BC},
    {lbl_1_rodata_713C, 0x4004692A, 0x00000000, 0x0002BDA0},
    {lbl_1_rodata_7154, 0x40022760, 0x00000000, 0x00014394},
    {lbl_1_rodata_716C, 0x40058C62, 0x00000000, 0x00035348},
    {lbl_1_rodata_7184, 0x4002A978, 0x00000000, 0x0001AF6C},
    {lbl_1_rodata_719C, 0x40002E50, 0x00000000, 0x00001A40},
    {lbl_1_rodata_71B4, 0x400219D2, 0x00000000, 0x00012A88},
    {lbl_1_rodata_40C8, 0x4004E820, 0x00000000, 0x0002E358},
    {lbl_1_rodata_71CC, 0x4002CEBA, 0x00000000, 0x0001AC10},
    {lbl_1_rodata_71E4, 0x4003BFE6, 0x00000000, 0x00024E48},
    {lbl_1_rodata_71FC, 0x4001A25C, 0x00000000, 0x0000EC58},
    {lbl_1_rodata_7214, 0x4000BEC4, 0x00000000, 0x0000616C},
    {lbl_1_rodata_722C, 0x40033CDA, 0x00000000, 0x0001D2AC},
    {lbl_1_rodata_7244, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_725C, 0x4000B02E, 0x00000000, 0x00005BDC},
    {lbl_1_rodata_7274, 0x400168E2, 0x00000000, 0x0000CD08},
    {lbl_1_rodata_728C, 0x4000C4EC, 0x00000000, 0x00005E34},
    {lbl_1_rodata_72A4, 0x4002346C, 0x00000000, 0x00016348},
    {lbl_1_rodata_41CC, 0x40012910, 0x00000000, 0x0000CEDC},
    {lbl_1_rodata_41E4, 0x4000D4C0, 0x00000000, 0x00008994},
    {lbl_1_rodata_713C, 0x4004692A, 0x00000000, 0x0002BDA0},
    {lbl_1_rodata_7154, 0x40022760, 0x00000000, 0x00014394},
    {lbl_1_rodata_716C, 0x40058C62, 0x00000000, 0x00035348},
    {lbl_1_rodata_7184, 0x4002A978, 0x00000000, 0x0001AF6C},
    {lbl_1_rodata_719C, 0x40002E50, 0x00000000, 0x00001A40},
    {lbl_1_rodata_71B4, 0x400219D2, 0x00000000, 0x00012A88},
    {lbl_1_rodata_40C8, 0x4004E820, 0x00000000, 0x0002E358},
    {lbl_1_rodata_71CC, 0x4002CEBA, 0x00000000, 0x0001AC10},
    {lbl_1_rodata_71E4, 0x4003BFE6, 0x00000000, 0x00024E48},
    {lbl_1_rodata_71FC, 0x4001A25C, 0x00000000, 0x0000EC58},
    {lbl_1_rodata_7214, 0x4000BEC4, 0x00000000, 0x0000616C},
    {lbl_1_rodata_722C, 0x40033CDA, 0x00000000, 0x0001D2AC},
    {lbl_1_rodata_7244, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_725C, 0x4000B02E, 0x00000000, 0x00005BDC},
    {lbl_1_rodata_7274, 0x400168E2, 0x00000000, 0x0000CD08},
    {lbl_1_rodata_728C, 0x4000C4EC, 0x00000000, 0x00005E34},
    {lbl_1_rodata_72A4, 0x4002346C, 0x00000000, 0x00016348},
    {lbl_1_rodata_41FC, 0x40013AD4, 0x00000000, 0x0000DDC8},
    {lbl_1_rodata_4214, 0x4000D7E0, 0x00000000, 0x00008C38},
    {lbl_1_rodata_713C, 0x4004692A, 0x00000000, 0x0002BDA0},
    {lbl_1_rodata_7154, 0x40022760, 0x00000000, 0x00014394},
    {lbl_1_rodata_716C, 0x40058C62, 0x00000000, 0x00035348},
    {lbl_1_rodata_7184, 0x4002A978, 0x00000000, 0x0001AF6C},
    {lbl_1_rodata_719C, 0x40002E50, 0x00000000, 0x00001A40},
    {lbl_1_rodata_71B4, 0x400219D2, 0x00000000, 0x00012A88},
    {lbl_1_rodata_40C8, 0x4004E820, 0x00000000, 0x0002E358},
    {lbl_1_rodata_71CC, 0x4002CEBA, 0x00000000, 0x0001AC10},
    {lbl_1_rodata_71E4, 0x4003BFE6, 0x00000000, 0x00024E48},
    {lbl_1_rodata_71FC, 0x4001A25C, 0x00000000, 0x0000EC58},
    {lbl_1_rodata_7214, 0x4000BEC4, 0x00000000, 0x0000616C},
    {lbl_1_rodata_722C, 0x40033CDA, 0x00000000, 0x0001D2AC},
    {lbl_1_rodata_7244, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_725C, 0x4000B02E, 0x00000000, 0x00005BDC},
    {lbl_1_rodata_7274, 0x400168E2, 0x00000000, 0x0000CD08},
    {lbl_1_rodata_728C, 0x4000C4EC, 0x00000000, 0x00005E34},
    {lbl_1_rodata_72A4, 0x4002346C, 0x00000000, 0x00016348},
    {lbl_1_rodata_422C, 0x40012910, 0x00000000, 0x0000CEB0},
    {lbl_1_rodata_4244, 0x4000D4C0, 0x00000000, 0x00008968},
    {lbl_1_rodata_713C, 0x4004692A, 0x00000000, 0x0002BDA0},
    {lbl_1_rodata_7154, 0x40022760, 0x00000000, 0x00014394},
    {lbl_1_rodata_716C, 0x40058C62, 0x00000000, 0x00035348},
    {lbl_1_rodata_7184, 0x4002A978, 0x00000000, 0x0001AF6C},
    {lbl_1_rodata_719C, 0x40002E50, 0x00000000, 0x00001A40},
    {lbl_1_rodata_71B4, 0x400219D2, 0x00000000, 0x00012A88},
    {lbl_1_rodata_40C8, 0x4004E820, 0x00000000, 0x0002E358},
    {lbl_1_rodata_71CC, 0x4002CEBA, 0x00000000, 0x0001AC10},
    {lbl_1_rodata_71E4, 0x4003BFE6, 0x00000000, 0x00024E48},
    {lbl_1_rodata_71FC, 0x4001A25C, 0x00000000, 0x0000EC58},
    {lbl_1_rodata_7214, 0x4000BEC4, 0x00000000, 0x0000616C},
    {lbl_1_rodata_722C, 0x40033CDA, 0x00000000, 0x0001D2AC},
    {lbl_1_rodata_7244, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_725C, 0x4000B02E, 0x00000000, 0x00005BDC},
    {lbl_1_rodata_7274, 0x400168E2, 0x00000000, 0x0000CD08},
    {lbl_1_rodata_728C, 0x4000C4EC, 0x00000000, 0x00005E34},
    {lbl_1_rodata_72A4, 0x4002346C, 0x00000000, 0x00016348},
    {lbl_1_rodata_425C, 0x4001AE1C, 0x00000000, 0x0001157C},
    {lbl_1_rodata_4274, 0x4000FFE0, 0x00000000, 0x00009BD8},
    {lbl_1_rodata_653C, 0x4003D09E, 0x00000000, 0x00026BD8},
    {lbl_1_rodata_6554, 0x4001CB5C, 0x00000000, 0x00011928},
    {lbl_1_rodata_656C, 0x4004BA56, 0x00000000, 0x0002DB30},
    {lbl_1_rodata_6584, 0x4001D9BA, 0x00000000, 0x0001275C},
    {lbl_1_rodata_659C, 0x400034E6, 0x00000000, 0x00001EF0},
    {lbl_1_rodata_65B4, 0x4001B818, 0x00000000, 0x0000F9C8},
    {lbl_1_rodata_30F8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_65CC, 0x40024AC6, 0x00000000, 0x000161B0},
    {lbl_1_rodata_65E4, 0x40033428, 0x00000000, 0x0001FF84},
    {lbl_1_rodata_65FC, 0x40013EBC, 0x00000000, 0x0000B978},
    {lbl_1_rodata_6614, 0x4000A3F0, 0x00000000, 0x000051B4},
    {lbl_1_rodata_662C, 0x40029748, 0x00000000, 0x00017464},
    {lbl_1_rodata_6644, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_665C, 0x40008E8E, 0x00000000, 0x00004890},
    {lbl_1_rodata_6674, 0x40010250, 0x00000000, 0x00009470},
    {lbl_1_rodata_668C, 0x4000C09C, 0x00000000, 0x0000613C},
    {lbl_1_rodata_66A4, 0x40018694, 0x00000000, 0x0000F23C},
    {lbl_1_rodata_428C, 0x4001A71C, 0x00000000, 0x000112D0},
    {lbl_1_rodata_42A4, 0x4000F8E0, 0x00000000, 0x00009924},
    {lbl_1_rodata_653C, 0x4003D09E, 0x00000000, 0x00026BD8},
    {lbl_1_rodata_6554, 0x4001CB5C, 0x00000000, 0x00011928},
    {lbl_1_rodata_656C, 0x4004BA56, 0x00000000, 0x0002DB30},
    {lbl_1_rodata_6584, 0x4001D9BA, 0x00000000, 0x0001275C},
    {lbl_1_rodata_659C, 0x400034E6, 0x00000000, 0x00001EF0},
    {lbl_1_rodata_65B4, 0x4001B818, 0x00000000, 0x0000F9C8},
    {lbl_1_rodata_30F8, 0x400336E0, 0x00000000, 0x0001FB54},
    {lbl_1_rodata_65CC, 0x40024AC6, 0x00000000, 0x000161B0},
    {lbl_1_rodata_65E4, 0x40033428, 0x00000000, 0x0001FF84},
    {lbl_1_rodata_65FC, 0x40013EBC, 0x00000000, 0x0000B978},
    {lbl_1_rodata_6614, 0x4000A3F0, 0x00000000, 0x000051B4},
    {lbl_1_rodata_662C, 0x40029748, 0x00000000, 0x00017464},
    {lbl_1_rodata_6644, 0x40003D7E, 0x00000000, 0x00000AE8},
    {lbl_1_rodata_665C, 0x40008E8E, 0x00000000, 0x00004890},
    {lbl_1_rodata_6674, 0x40010250, 0x00000000, 0x00009470},
    {lbl_1_rodata_668C, 0x4000C09C, 0x00000000, 0x0000613C},
    {lbl_1_rodata_66A4, 0x40018694, 0x00000000, 0x0000F23C},
};
static ChAramAsset lbl_1_data_A3D8[2] = {
    {0x0000040B, 0x40093FF8, 0x0E581000, 0x0005F484},
    {0x0000040B, 0x40095BB8, 0x0E5E0800, 0x0006053C},
};
static ChAramAsset lbl_1_data_A3F8[30] = {
    {0x0000040B, 0x400004D8, 0x0E66C800, 0x00000340},
    {0x0000040B, 0x40000314, 0x0E66D000, 0x00000204},
    {0x0000040B, 0x40000280, 0x0E66D800, 0x000001C4},
    {0x0000040B, 0x4000026C, 0x0E66E000, 0x000001A0},
    {0x0000040B, 0x40000464, 0x0E66E800, 0x000002F0},
    {0x0000040B, 0x40000544, 0x0E66F000, 0x00000364},
    {0x0000040B, 0x400002E4, 0x0E66F800, 0x000001D4},
    {0x0000040B, 0x40000418, 0x0E670000, 0x000002C8},
    {0x0000040B, 0x40000444, 0x0E670800, 0x000002CC},
    {0x0000040B, 0x400003D8, 0x0E671000, 0x00000278},
    {0x0000040B, 0x40000630, 0x0E671800, 0x0000040C},
    {0x0000040B, 0x400001CC, 0x0E672000, 0x00000130},
    {0x0000040B, 0x40000448, 0x0E672800, 0x000002AC},
    {0x0000040B, 0x40000390, 0x0E673000, 0x00000258},
    {0x0000040B, 0x40000394, 0x0E673800, 0x00000248},
    {0x0000040B, 0x400004F8, 0x0E674000, 0x00000304},
    {0x0000040B, 0x400003D8, 0x0E674800, 0x00000220},
    {0x0000040B, 0x4000033C, 0x0E675000, 0x00000238},
    {0x0000040B, 0x40000444, 0x0E675800, 0x000002AC},
    {0x0000040B, 0x400001B0, 0x0E676000, 0x00000110},
    {0x0000040B, 0x400002C0, 0x0E676800, 0x000001D4},
    {0x0000040B, 0x40000168, 0x0E677000, 0x000000E4},
    {0x0000040B, 0x400000D8, 0x0E677800, 0x00000058},
    {0x0000040B, 0x40000284, 0x0E678000, 0x00000178},
    {0x0000040B, 0x400000C8, 0x0E678800, 0x00000050},
    {0x0000040B, 0x4000019C, 0x0E679000, 0x00000100},
    {0x0000040B, 0x40000278, 0x0E679800, 0x0000019C},
    {0x0000040B, 0x4000021C, 0x0E67A000, 0x00000164},
    {0x0000040B, 0x400000C8, 0x0E67A800, 0x0000004C},
    {0x0000040B, 0x40000145, 0x0E67B000, 0x000000A4},
};
static ChAramAsset lbl_1_data_A5D8[54] = {
    {0x0000040B, 0x40014D14, 0x18941800, 0x0000D8F8},
    {0x0000040B, 0x40015488, 0x1894F800, 0x0000D818},
    {0x0000040B, 0x40018270, 0x1895D800, 0x0000F8DC},
    {0x0000040B, 0x4001623C, 0x1896D800, 0x0000E490},
    {0x0000040B, 0x40011E6C, 0x1897C000, 0x0000A778},
    {0x0000040B, 0x40011FD8, 0x18986800, 0x0000A850},
    {0x0000040B, 0x4001350C, 0x18991800, 0x0000C468},
    {0x0000040B, 0x40013EEC, 0x1899E000, 0x0000BEAC},
    {0x0000040B, 0x40013F68, 0x189AA000, 0x0000BE84},
    {0x0000040B, 0x40017428, 0x189B6000, 0x0000E704},
    {0x0000040B, 0x40013954, 0x189C4800, 0x0000C884},
    {0x0000040B, 0x400131A8, 0x189D1800, 0x0000C35C},
    {0x0000040B, 0x400109FC, 0x189DE000, 0x0000AA9C},
    {0x0000040B, 0x40013C48, 0x189E9000, 0x0000BA28},
    {0x0000040B, 0x4000836C, 0x189F5000, 0x00006454},
    {0x0000040B, 0x40013C0C, 0x189FB800, 0x0000BEE4},
    {0x0000040B, 0x40007038, 0x18A07800, 0x00004CAC},
    {0x0000040B, 0x400149F0, 0x18A0C800, 0x0000D820},
    {0x0000040B, 0x40008430, 0x18A1A800, 0x00005FE0},
    {0x0000040B, 0x40013938, 0x18A20800, 0x0000B038},
    {0x0000040B, 0x4001098C, 0x18A2C000, 0x0000AA3C},
    {0x0000040B, 0x40010C64, 0x18A37000, 0x0000A444},
    {0x0000040B, 0x40010C64, 0x18A37000, 0x0000A444},
    {0x0000040B, 0x40010C64, 0x18A37000, 0x0000A444},
    {0x0000040B, 0x4000EDB8, 0x18A41800, 0x000090C0},
    {0x0000040B, 0x4000EDB8, 0x18A41800, 0x000090C0},
    {0x0000040B, 0x4000EDB8, 0x18A41800, 0x000090C0},
    {0x0000040B, 0x400143A8, 0x18A4B000, 0x0000C2A4},
    {0x0000040B, 0x400152A0, 0x18A57800, 0x0000DE78},
    {0x0000040B, 0x40013C48, 0x189E9000, 0x0000BA28},
    {0x0000040B, 0x40013C48, 0x189E9000, 0x0000BA28},
    {0x0000040B, 0x40013C48, 0x189E9000, 0x0000BA28},
    {0x0000040B, 0x40013C48, 0x189E9000, 0x0000BA28},
    {0x0000040B, 0x400144D8, 0x18A65800, 0x0000CCBC},
    {0x0000040B, 0x400144D8, 0x18A65800, 0x0000CCBC},
    {0x0000040B, 0x400144D8, 0x18A65800, 0x0000CCBC},
    {0x0000040B, 0x400144D8, 0x18A65800, 0x0000CCBC},
    {0x0000040B, 0x4000B7DC, 0x18A72800, 0x00006E3C},
    {0x0000040B, 0x40001918, 0x18A79800, 0x00000CF4},
    {0x0000040B, 0x400148FC, 0x18A7A800, 0x0000D9D8},
    {0x0000040B, 0x400049BC, 0x18A88800, 0x00003804},
    {0x0000040B, 0x4000495C, 0x18A8C800, 0x000037C8},
    {0x0000040B, 0x400109FC, 0x189DE000, 0x0000AA9C},
    {0x0000040B, 0x4001098C, 0x18A2C000, 0x0000AA3C},
    {0x0000040B, 0x40007038, 0x18A07800, 0x00004CAC},
    {0x0000040B, 0x40007038, 0x18A07800, 0x00004CAC},
    {0x0000040B, 0x40007038, 0x18A07800, 0x00004CAC},
    {0x0000040B, 0x40007038, 0x18A07800, 0x00004CAC},
    {0x0000040B, 0x40011210, 0x18A90000, 0x0000ADD4},
    {0x0000040B, 0x40011210, 0x18A90000, 0x0000ADD4},
    {0x0000040B, 0x40011210, 0x18A90000, 0x0000ADD4},
    {0x0000040B, 0x40011210, 0x18A90000, 0x0000ADD4},
    {0x0000040B, 0x40010908, 0x18A9B000, 0x0000A7D4},
    {0x0000040B, 0x4000EDA8, 0x18AA5800, 0x00009B8C},
};
static u8 lbl_1_data_A938[8] = {
    0x4B, 0x2D, 0x00, 0x3F, 0x3D, 0x69, 0x00, 0x00,
};
ChAramAsset lbl_1_data_A940 = {0x00000000, 0x00000200, 0x18AAF800, 0x00015450};
static ChAramAsset lbl_1_data_A950 = {0x0000040B, 0x400204C0, 0x191C1800, 0x00013FCC};
u8 lbl_1_data_A960[16] = { // byte table; nothing in the code reads it
    0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
const char* lbl_1_data_A970[2] = {
    lbl_1_rodata_72BC, lbl_1_rodata_72C4,
};
static s16 lbl_1_data_A978[54] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53,
};
static ChDrawMtxNode lbl_1_data_A9E4[2] = {{0, fn_1_11714}, {0, fn_1_11714}};
static ChDrawMtxNode lbl_1_data_AA54[2] = {{2, fn_1_1125C}, {2, fn_1_1125C}};
static ChDrawMtxNode lbl_1_data_AAC4[2] = {{2, fn_1_10CEC}, {2, fn_1_10CEC}};
static ChDrawMtxNode lbl_1_data_AB34[2] = {{2, (void (*)(struct ChDrawMtxNode*))fn_1_C5AC}, {2, (void (*)(struct ChDrawMtxNode*))fn_1_C5AC}};
static f32 lbl_1_data_ABA4 = 0.5f;
u8 lbl_1_data_ABA8 = 1;
const char* lbl_1_data_ABAC[2] = {
    lbl_1_rodata_72CC, lbl_1_rodata_72D8,
};
static void (*lbl_1_data_ABB4[18])(void) = {
    fn_1_15170, fn_1_14FB8, fn_1_165E0, fn_1_15CE0,
    fn_1_15760, fn_1_1540C, fn_1_151F8, fn_1_E098,
    fn_1_EA20, fn_1_106C4, fn_1_10458, fn_1_10044,
    fn_1_FB98, fn_1_F6E4, fn_1_F37C, fn_1_F2F8,
    fn_1_F0D0, fn_1_F040,
};
char lbl_1_data_ABFC[2][0x40] = {
    "CAMERA", "MODEL",
};
static ChDrawNode8 lbl_1_data_AC7C[2] = {{2, fn_1_17954}, {2, fn_1_17954}};
f32 lbl_1_data_AC8C = -2.0f;
s8 lbl_1_data_AC90 = -1;
u8 lbl_1_data_AC91 = 10;
const char* lbl_1_data_AC94[2] = {
    lbl_1_rodata_72E4, lbl_1_rodata_72E8,
};
static ChDrawMtxNode lbl_1_data_AC9C[2] = {{2, fn_1_12F18}, {2, fn_1_12F18}};
f32 lbl_1_data_AD0C[3] = {
    0.0f, 0.0f, 0.0f,
};
Vec lbl_1_data_AD18 = {0.0f, 1.0f, 0.0f};
Vec lbl_1_data_AD24 = {0.0f, 1.0f, 0.0f};
Vec lbl_1_data_AD30[8] = { // cube corners
    {-2.5f, -1.0f, 9.5f}, {-2.5f, -1.0f, 10.5f}, {-1.5f, -1.0f, 10.5f}, {-1.5f, -1.0f, 9.5f},
    {-2.5f, 0.0f, 9.5f}, {-2.5f, 0.0f, 10.5f}, {-1.5f, 0.0f, 10.5f}, {-1.5f, 0.0f, 9.5f},
};
u8 lbl_1_data_AD90[6][4] = { // faces (corner indices)
    {0, 3, 2, 1}, {4, 5, 6, 7}, {0, 4, 7, 3}, {3, 7, 6, 2}, {2, 6, 5, 1}, {1, 5, 4, 0},
};
u32 lbl_1_data_ADA8[6] = { // face colours
    0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFF00FF, 0xFF00FFFF, 0x00FFFFFF,
};
f32 lbl_1_data_ADC0[1] = {
    -1.0f,
};
u8 lbl_1_data_ADC4[28] = { // zeros; only passed to fn_80026130, an empty stub, so the layout is unknown
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static ChAramAsset lbl_1_data_ADE0 = {0x0000040B, 0x40046100, 0x0E641000, 0x00024B48};
static ChallengeEmitterParams lbl_1_data_ADF0 = {-16777088, 1024, 1.0f, 60, 0.08f, {0.0f, 0.0f, 10.0f}, 512, 3064, {0.0f, -1.0f, 0.0f}};
// Packed vertex lists (lbl_1_data_EF70; nothing in the code reads them). The first entry's
// tag is 0x8000 | the number of entries that follow; the others carry a small group index.
typedef struct ChPackedVtx {
    /* 0x0 */ u16 tag;
    /* 0x2 */ u16 x;
    /* 0x4 */ u16 y;
    /* 0x6 */ u16 z;
} ChPackedVtx;
ChPackedVtx lbl_1_data_AE20[147] = {
    {0x8092, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4000, 0x4000, 0x0D62}, {0x0000, 0x6D45, 0x4000, 0x295D}, {0x0000, 0x4DFD, 0x14F1, 0x295D},
    {0x0000, 0x1B60, 0x2564, 0x295D}, {0x0000, 0x1B60, 0x5A9B, 0x295D}, {0x0000, 0x4DFD, 0x6B0E, 0x295D}, {0x0000, 0x649F, 0x2564, 0x56A2},
    {0x0000, 0x3202, 0x14F1, 0x56A2}, {0x0000, 0x12BA, 0x4000, 0x56A2}, {0x0000, 0x3202, 0x6B0E, 0x56A2}, {0x0000, 0x649F, 0x5A9B, 0x56A2},
    {0x0000, 0x4000, 0x4000, 0x729D}, {0x0000, 0x5A9B, 0x4000, 0x14F1}, {0x0000, 0x4839, 0x26B1, 0x14F1}, {0x0000, 0x2A78, 0x305C, 0x14F1},
    {0x0000, 0x2A78, 0x4FA3, 0x14F1}, {0x0000, 0x4839, 0x594E, 0x14F1}, {0x0000, 0x62D5, 0x26B1, 0x2564}, {0x0000, 0x32B2, 0x170D, 0x2564},
    {0x0000, 0x14F1, 0x4000, 0x2564}, {0x0000, 0x32B2, 0x68F2, 0x2564}, {0x0000, 0x62D5, 0x594E, 0x2564}, {0x0000, 0x7023, 0x305C, 0x4000},
    {0x0000, 0x4000, 0x0D62, 0x4000}, {0x0000, 0x0FDC, 0x305C, 0x4000}, {0x0000, 0x223F, 0x68F2, 0x4000}, {0x0000, 0x5DC0, 0x68F2, 0x4000},
    {0x0000, 0x7023, 0x4FA3, 0x4000}, {0x0000, 0x5DC0, 0x170D, 0x4000}, {0x0000, 0x223F, 0x170D, 0x4000}, {0x0000, 0x0FDC, 0x4FA3, 0x4000},
    {0x0000, 0x4000, 0x729D, 0x4000}, {0x0000, 0x4D4D, 0x170D, 0x5A9B}, {0x0000, 0x1D2A, 0x26B1, 0x5A9B}, {0x0000, 0x1D2A, 0x594E, 0x5A9B},
    {0x0000, 0x4D4D, 0x68F2, 0x5A9B}, {0x0000, 0x6B0E, 0x4000, 0x5A9B}, {0x0000, 0x5587, 0x305C, 0x6B0E}, {0x0000, 0x37C6, 0x26B1, 0x6B0E},
    {0x0000, 0x2564, 0x4000, 0x6B0E}, {0x0000, 0x37C6, 0x594E, 0x6B0E}, {0x0000, 0x5587, 0x4FA3, 0x6B0E}, {0x0001, 0x4000, 0x4000, 0x0000},
    {0x0001, 0x793E, 0x4000, 0x2360}, {0x0001, 0x51B0, 0x098E, 0x2360}, {0x0001, 0x11B0, 0x1E5A, 0x2360}, {0x0001, 0x11B0, 0x61A5, 0x2360},
    {0x0001, 0x51B0, 0x7671, 0x2360}, {0x0001, 0x6E4F, 0x1E5A, 0x5C9F}, {0x0001, 0x2E4F, 0x098E, 0x5C9F}, {0x0001, 0x06C1, 0x4000, 0x5C9F},
    {0x0001, 0x2E4F, 0x7671, 0x5C9F}, {0x0001, 0x6E4F, 0x61A5, 0x5C9F}, {0x0001, 0x4000, 0x4000, 0x8000}, {0x0001, 0x5716, 0x4000, 0x044F},
    {0x0001, 0x6B10, 0x4000, 0x10A7}, {0x0001, 0x4722, 0x2A0B, 0x044F}, {0x0001, 0x4D4E, 0x170B, 0x10A7}, {0x0001, 0x2D52, 0x326E, 0x044F},
    {0x0001, 0x1D28, 0x26AF, 0x10A7}, {0x0001, 0x2D52, 0x4D91, 0x044F}, {0x0001, 0x1D28, 0x5950, 0x10A7}, {0x0001, 0x4722, 0x55F4, 0x044F},
    {0x0001, 0x4D4E, 0x68F4, 0x10A7}, {0x0001, 0x7232, 0x2A0B, 0x1EEC}, {0x0001, 0x6464, 0x170B, 0x1EEC}, {0x0001, 0x3AA1, 0x0979, 0x1EEC},
    {0x0001, 0x244B, 0x10BB, 0x1EEC}, {0x0001, 0x0A7B, 0x3441, 0x1EEC}, {0x0001, 0x0A7B, 0x4BBE, 0x1EEC}, {0x0001, 0x244B, 0x6F44, 0x1EEC},
    {0x0001, 0x3AA1, 0x7686, 0x1EEC}, {0x0001, 0x6464, 0x68F4, 0x1EEC}, {0x0001, 0x7232, 0x55F4, 0x1EEC}, {0x0001, 0x7DBD, 0x326E, 0x3602},
    {0x0001, 0x79ED, 0x26AF, 0x49FD}, {0x0001, 0x462C, 0x0116, 0x3602}, {0x0001, 0x39D3, 0x0116, 0x49FD}, {0x0001, 0x0612, 0x26AF, 0x3602},
    {0x0001, 0x0242, 0x326E, 0x49FD}, {0x0001, 0x1606, 0x6F44, 0x3602}, {0x0001, 0x2003, 0x7686, 0x49FD}, {0x0001, 0x5FFC, 0x7686, 0x3602},
    {0x0001, 0x69F9, 0x6F44, 0x49FD}, {0x0001, 0x7DBD, 0x4D91, 0x3602}, {0x0001, 0x79ED, 0x5950, 0x49FD}, {0x0001, 0x5FFC, 0x0979, 0x3602},
    {0x0001, 0x69F9, 0x10BB, 0x49FD}, {0x0001, 0x1606, 0x10BB, 0x3602}, {0x0001, 0x2003, 0x0979, 0x49FD}, {0x0001, 0x0612, 0x5950, 0x3602},
    {0x0001, 0x0242, 0x4D91, 0x49FD}, {0x0001, 0x462C, 0x7EE9, 0x3602}, {0x0001, 0x39D3, 0x7EE9, 0x49FD}, {0x0001, 0x5BB4, 0x10BB, 0x6113},
    {0x0001, 0x455E, 0x0979, 0x6113}, {0x0001, 0x1B9B, 0x170B, 0x6113}, {0x0001, 0x0DCD, 0x2A0B, 0x6113}, {0x0001, 0x0DCD, 0x55F4, 0x6113},
    {0x0001, 0x1B9B, 0x68F4, 0x6113}, {0x0001, 0x455E, 0x7686, 0x6113}, {0x0001, 0x5BB4, 0x6F44, 0x6113}, {0x0001, 0x7584, 0x4BBE, 0x6113},
    {0x0001, 0x7584, 0x3441, 0x6113}, {0x0001, 0x52AD, 0x326E, 0x7BB0}, {0x0001, 0x62D7, 0x26AF, 0x6F58}, {0x0001, 0x38DD, 0x2A0B, 0x7BB0},
    {0x0001, 0x32B1, 0x170B, 0x6F58}, {0x0001, 0x28E9, 0x4000, 0x7BB0}, {0x0001, 0x14EF, 0x4000, 0x6F58}, {0x0001, 0x38DD, 0x55F4, 0x7BB0},
    {0x0001, 0x32B1, 0x68F4, 0x6F58}, {0x0001, 0x52AD, 0x4D91, 0x7BB0}, {0x0001, 0x62D7, 0x5950, 0x6F58}, {0x0001, 0x5EB0, 0x29B4, 0x0C73},
    {0x0001, 0x3447, 0x1BEC, 0x0C73}, {0x0001, 0x1A11, 0x4000, 0x0C73}, {0x0001, 0x3447, 0x6413, 0x0C73}, {0x0001, 0x5EB0, 0x564B, 0x0C73},
    {0x0001, 0x7F11, 0x4000, 0x4AE0}, {0x0001, 0x537D, 0x0404, 0x4AE0}, {0x0001, 0x0CF9, 0x1AED, 0x4AE0}, {0x0001, 0x0CF9, 0x6512, 0x4AE0},
    {0x0001, 0x537D, 0x7BFB, 0x4AE0}, {0x0001, 0x7306, 0x1AED, 0x351F}, {0x0001, 0x2C82, 0x0404, 0x351F}, {0x0001, 0x00EE, 0x4000, 0x351F},
    {0x0001, 0x2C82, 0x7BFB, 0x351F}, {0x0001, 0x7306, 0x6512, 0x351F}, {0x0001, 0x4BB8, 0x1BEC, 0x738C}, {0x0001, 0x214F, 0x29B4, 0x738C},
    {0x0001, 0x214F, 0x564B, 0x738C}, {0x0001, 0x4BB8, 0x6413, 0x738C}, {0x0001, 0x65EE, 0x4000, 0x738C}, {0x0002, 0x4000, 0x4000, 0x186A},
    {0x0002, 0x6367, 0x4000, 0x2E4C}, {0x0002, 0x4AF0, 0x1E53, 0x2E4C}, {0x0002, 0x235B, 0x2B30, 0x2E4C}, {0x0002, 0x235B, 0x54CF, 0x2E4C},
    {0x0002, 0x4AF0, 0x61AC, 0x2E4C}, {0x0002, 0x5CA4, 0x2B30, 0x51B3}, {0x0002, 0x350F, 0x1E53, 0x51B3}, {0x0002, 0x1C98, 0x4000, 0x51B3},
    {0x0002, 0x350F, 0x61AC, 0x51B3}, {0x0002, 0x5CA4, 0x54CF, 0x51B3}, {0x0002, 0x4000, 0x4000, 0x6795},
};
ChPackedVtx lbl_1_data_B2B8[81] = {
    {0x8050, 0x8000, 0x8000, 0x8000}, {0x0000, 0x5DAB, 0x5319, 0x3E5A}, {0x0000, 0x8000, 0x386E, 0x3E5A}, {0x0000, 0x5772, 0x28ED, 0x3E5A},
    {0x0000, 0x48CC, 0x0000, 0x3E5A}, {0x0000, 0x2D7F, 0x21DA, 0x3E5A}, {0x0000, 0x0223, 0x2335, 0x3E5A}, {0x0000, 0x19CA, 0x47A8, 0x3E5A},
    {0x0000, 0x0DAC, 0x7165, 0x3E5A}, {0x0000, 0x3791, 0x6618, 0x3E5A}, {0x0000, 0x5B76, 0x7E83, 0x3E5A}, {0x0000, 0x17D1, 0x2287, 0x3E5A},
    {0x0000, 0x0DF6, 0x356D, 0x3E5A}, {0x0000, 0x5021, 0x1475, 0x3E5A}, {0x0000, 0x3B26, 0x10EB, 0x3E5A}, {0x0000, 0x6ED5, 0x45C2, 0x3E5A},
    {0x0000, 0x6BBA, 0x30AE, 0x3E5A}, {0x0000, 0x4982, 0x724E, 0x3E5A}, {0x0000, 0x5C92, 0x68CD, 0x3E5A}, {0x0000, 0x13BA, 0x5C86, 0x3E5A},
    {0x0000, 0x229E, 0x6BBD, 0x3E5A}, {0x0000, 0x22AA, 0x222F, 0x3E5A}, {0x0000, 0x0CFC, 0x22DD, 0x3E5A}, {0x0000, 0x13E1, 0x3E8A, 0x3E5A},
    {0x0000, 0x080C, 0x2C52, 0x3E5A}, {0x0000, 0x53C9, 0x1EB1, 0x3E5A}, {0x0000, 0x4C75, 0x0A3C, 0x3E5A}, {0x0000, 0x3451, 0x1964, 0x3E5A},
    {0x0000, 0x41F7, 0x0875, 0x3E5A}, {0x0000, 0x6640, 0x4C6F, 0x3E5A}, {0x0000, 0x776A, 0x3F18, 0x3E5A}, {0x0000, 0x6198, 0x2CCC, 0x3E5A},
    {0x0000, 0x75DD, 0x348C, 0x3E5A}, {0x0000, 0x4089, 0x6C31, 0x3E5A}, {0x0000, 0x527A, 0x7867, 0x3E5A}, {0x0000, 0x5D1D, 0x5DF4, 0x3E5A},
    {0x0000, 0x5C04, 0x73A8, 0x3E5A}, {0x0000, 0x10B3, 0x66F6, 0x3E5A}, {0x0000, 0x16C4, 0x5217, 0x3E5A}, {0x0000, 0x2D16, 0x68E9, 0x3E5A},
    {0x0000, 0x1826, 0x6E91, 0x3E5A}, {0x0001, 0x50ED, 0x4C34, 0x3E5A}, {0x0001, 0x65A1, 0x3C1F, 0x3E5A}, {0x0001, 0x4D2D, 0x32C3, 0x3E5A},
    {0x0001, 0x4457, 0x1A14, 0x3E5A}, {0x0001, 0x33DF, 0x2E81, 0x3E5A}, {0x0001, 0x19B7, 0x2F51, 0x3E5A}, {0x0001, 0x27FC, 0x454E, 0x3E5A},
    {0x0001, 0x20AD, 0x5E7A, 0x3E5A}, {0x0001, 0x39F0, 0x57A8, 0x3E5A}, {0x0001, 0x4F98, 0x6665, 0x3E5A}, {0x0001, 0x26CC, 0x2EE8, 0x3E5A},
    {0x0001, 0x20DB, 0x3A4E, 0x3E5A}, {0x0001, 0x48C1, 0x266C, 0x3E5A}, {0x0001, 0x3C1A, 0x244B, 0x3E5A}, {0x0001, 0x5B48, 0x4429, 0x3E5A},
    {0x0001, 0x5966, 0x3771, 0x3E5A}, {0x0001, 0x44C3, 0x5F05, 0x3E5A}, {0x0001, 0x5043, 0x594C, 0x3E5A}, {0x0001, 0x2453, 0x51E4, 0x3E5A},
    {0x0001, 0x2D4F, 0x5B12, 0x3E5A}, {0x0001, 0x2D54, 0x2EB4, 0x3E5A}, {0x0001, 0x2042, 0x2F1D, 0x3E5A}, {0x0001, 0x246A, 0x3FCE, 0x3E5A},
    {0x0001, 0x1D49, 0x34D1, 0x3E5A}, {0x0001, 0x4AF8, 0x2C99, 0x3E5A}, {0x0001, 0x468C, 0x2042, 0x3E5A}, {0x0001, 0x37FC, 0x2965, 0x3E5A},
    {0x0001, 0x4037, 0x1F2E, 0x3E5A}, {0x0001, 0x561B, 0x4830, 0x3E5A}, {0x0001, 0x6073, 0x4023, 0x3E5A}, {0x0001, 0x534A, 0x351A, 0x3E5A},
    {0x0001, 0x5F85, 0x39C8, 0x3E5A}, {0x0001, 0x3F59, 0x5B57, 0x3E5A}, {0x0001, 0x4A2F, 0x62B6, 0x3E5A}, {0x0001, 0x5098, 0x52C1, 0x3E5A},
    {0x0001, 0x4FED, 0x5FD7, 0x3E5A}, {0x0001, 0x227F, 0x5830, 0x3E5A}, {0x0001, 0x2628, 0x4B97, 0x3E5A}, {0x0001, 0x33A1, 0x595D, 0x3E5A},
    {0x0001, 0x26FD, 0x5CC8, 0x3E5A},
};
ChPackedVtx lbl_1_data_B540[81] = {
    {0x8050, 0x8000, 0x8000, 0x8000}, {0x0000, 0x6120, 0x3828, 0x3C7E}, {0x0000, 0x69EF, 0x0F41, 0x3C7E}, {0x0000, 0x4273, 0x1CE8, 0x3C7E},
    {0x0000, 0x1E50, 0x07CA, 0x3C7E}, {0x0000, 0x1F20, 0x31A5, 0x3C7E}, {0x0000, 0x0000, 0x4D7A, 0x3C7E}, {0x0000, 0x27FC, 0x59B8, 0x3C7E},
    {0x0000, 0x38E2, 0x7FFF, 0x3C7E}, {0x0000, 0x50C6, 0x5DBE, 0x3C7E}, {0x0000, 0x7A5A, 0x598A, 0x3C7E}, {0x0000, 0x0F90, 0x3F91, 0x3C7E},
    {0x0000, 0x13FE, 0x539A, 0x3C7E}, {0x0000, 0x3060, 0x1259, 0x3C7E}, {0x0000, 0x1EB8, 0x1CB9, 0x3C7E}, {0x0000, 0x6589, 0x23B4, 0x3C7E},
    {0x0000, 0x562F, 0x1613, 0x3C7E}, {0x0000, 0x6591, 0x5BA4, 0x3C7E}, {0x0000, 0x6DBF, 0x48DA, 0x3C7E}, {0x0000, 0x306E, 0x6CDC, 0x3C7E},
    {0x0000, 0x44D4, 0x6EDD, 0x3C7E}, {0x0000, 0x1758, 0x389B, 0x3C7E}, {0x0000, 0x07C8, 0x4684, 0x3C7E}, {0x0000, 0x1DFC, 0x56A8, 0x3C7E},
    {0x0000, 0x09FD, 0x508A, 0x3C7E}, {0x0000, 0x3968, 0x17A2, 0x3C7E}, {0x0000, 0x2758, 0x0D13, 0x3C7E}, {0x0000, 0x1EEC, 0x272F, 0x3C7E},
    {0x0000, 0x1E84, 0x1240, 0x3C7E}, {0x0000, 0x6353, 0x2DEE, 0x3C7E}, {0x0000, 0x67BC, 0x197A, 0x3C7E}, {0x0000, 0x4C50, 0x197D, 0x3C7E},
    {0x0000, 0x600F, 0x12AB, 0x3C7E}, {0x0000, 0x5B2C, 0x5CB0, 0x3C7E}, {0x0000, 0x6FF7, 0x5A98, 0x3C7E}, {0x0000, 0x6770, 0x4081, 0x3C7E},
    {0x0000, 0x740E, 0x5131, 0x3C7E}, {0x0000, 0x34A8, 0x766F, 0x3C7E}, {0x0000, 0x2C36, 0x634B, 0x3C7E}, {0x0000, 0x4ACC, 0x664E, 0x3C7E},
    {0x0000, 0x3EDA, 0x7770, 0x3C7E}, {0x0001, 0x5377, 0x3AF4, 0x3C7E}, {0x0001, 0x58C7, 0x2249, 0x3C7E}, {0x0001, 0x40F4, 0x2A87, 0x3C7E},
    {0x0001, 0x2B2B, 0x1DCB, 0x3C7E}, {0x0001, 0x2BA8, 0x3709, 0x3C7E}, {0x0001, 0x18DF, 0x47D1, 0x3C7E}, {0x0001, 0x30FF, 0x4F34, 0x3C7E},
    {0x0001, 0x3B30, 0x664B, 0x3C7E}, {0x0001, 0x499A, 0x51A1, 0x3C7E}, {0x0001, 0x62AD, 0x4F19, 0x3C7E}, {0x0001, 0x2244, 0x3F6D, 0x3C7E},
    {0x0001, 0x24EF, 0x4B83, 0x3C7E}, {0x0001, 0x360E, 0x2427, 0x3C7E}, {0x0001, 0x2B69, 0x2A69, 0x3C7E}, {0x0001, 0x561F, 0x2EA0, 0x3C7E},
    {0x0001, 0x4CDE, 0x2668, 0x3C7E}, {0x0001, 0x5625, 0x505B, 0x3C7E}, {0x0001, 0x5B13, 0x4508, 0x3C7E}, {0x0001, 0x3619, 0x5ABE, 0x3C7E},
    {0x0001, 0x4265, 0x5BF6, 0x3C7E}, {0x0001, 0x26F6, 0x3B3B, 0x3C7E}, {0x0001, 0x1D91, 0x439F, 0x3C7E}, {0x0001, 0x2AF7, 0x4D5B, 0x3C7E},
    {0x0001, 0x1EE7, 0x49AA, 0x3C7E}, {0x0001, 0x3B82, 0x2756, 0x3C7E}, {0x0001, 0x309C, 0x20F9, 0x3C7E}, {0x0001, 0x2B88, 0x30B8, 0x3C7E},
    {0x0001, 0x2B49, 0x241A, 0x3C7E}, {0x0001, 0x54C9, 0x34C9, 0x3C7E}, {0x0001, 0x5772, 0x2874, 0x3C7E}, {0x0001, 0x46E9, 0x2877, 0x3C7E},
    {0x0001, 0x52D3, 0x2458, 0x3C7E}, {0x0001, 0x4FDE, 0x50FF, 0x3C7E}, {0x0001, 0x5C69, 0x4FBA, 0x3C7E}, {0x0001, 0x5743, 0x3FFE, 0x3C7E},
    {0x0001, 0x5EE0, 0x4A0F, 0x3C7E}, {0x0001, 0x38A3, 0x6085, 0x3C7E}, {0x0001, 0x338C, 0x54FB, 0x3C7E}, {0x0001, 0x45FE, 0x56CB, 0x3C7E},
    {0x0001, 0x3EC9, 0x6120, 0x3C7E},
};
ChPackedVtx lbl_1_data_B7C8[81] = {
    {0x8050, 0x8000, 0x8000, 0x8000}, {0x0000, 0x5C78, 0x29EB, 0x3AC7}, {0x0000, 0x56B2, 0x0000, 0x3AC7}, {0x0000, 0x35E3, 0x1AA4, 0x3AC7},
    {0x0000, 0x0C40, 0x1313, 0x3AC7}, {0x0000, 0x1B81, 0x3A90, 0x3AC7}, {0x0000, 0x078B, 0x5FC6, 0x3AC7}, {0x0000, 0x31C6, 0x5D95, 0x3AC7},
    {0x0000, 0x4F13, 0x7C1D, 0x3AC7}, {0x0000, 0x59EF, 0x534B, 0x3AC7}, {0x0000, 0x8000, 0x40EC, 0x3AC7}, {0x0000, 0x1185, 0x4D2C, 0x3AC7},
    {0x0000, 0x1CA9, 0x5EAF, 0x3AC7}, {0x0000, 0x2110, 0x16DA, 0x3AC7}, {0x0000, 0x13DF, 0x26D1, 0x3AC7}, {0x0000, 0x5994, 0x14F6, 0x3AC7},
    {0x0000, 0x4649, 0x0D52, 0x3AC7}, {0x0000, 0x6CF7, 0x4A1C, 0x3AC7}, {0x0000, 0x6E3B, 0x356D, 0x3AC7}, {0x0000, 0x406D, 0x6CD9, 0x3AC7},
    {0x0000, 0x5481, 0x67B5, 0x3AC7}, {0x0000, 0x1682, 0x43DE, 0x3AC7}, {0x0000, 0x0C88, 0x567B, 0x3AC7}, {0x0000, 0x2738, 0x5E22, 0x3AC7},
    {0x0000, 0x121A, 0x5F39, 0x3AC7}, {0x0000, 0x2B7B, 0x18BE, 0x3AC7}, {0x0000, 0x16A8, 0x14F6, 0x3AC7}, {0x0000, 0x17AF, 0x30B2, 0x3AC7},
    {0x0000, 0x1010, 0x1CF1, 0x3AC7}, {0x0000, 0x5B06, 0x1F72, 0x3AC7}, {0x0000, 0x5824, 0x0A7B, 0x3AC7}, {0x0000, 0x3E18, 0x13FB, 0x3AC7},
    {0x0000, 0x4E7E, 0x06A9, 0x3AC7}, {0x0000, 0x6372, 0x4EB2, 0x3AC7}, {0x0000, 0x767A, 0x4582, 0x3AC7}, {0x0000, 0x655B, 0x2FAC, 0x3AC7},
    {0x0000, 0x771D, 0x3B2B, 0x3AC7}, {0x0000, 0x47C1, 0x747B, 0x3AC7}, {0x0000, 0x391B, 0x6537, 0x3AC7}, {0x0000, 0x5737, 0x5D7F, 0x3AC7},
    {0x0000, 0x51C9, 0x71E9, 0x3AC7}, {0x0001, 0x5075, 0x3150, 0x3AC7}, {0x0001, 0x4CF8, 0x1807, 0x3AC7}, {0x0001, 0x392E, 0x2818, 0x3AC7},
    {0x0001, 0x2012, 0x2387, 0x3AC7}, {0x0001, 0x2945, 0x3B5A, 0x3AC7}, {0x0001, 0x1D3B, 0x51CB, 0x3AC7}, {0x0001, 0x36B5, 0x5077, 0x3AC7},
    {0x0001, 0x485F, 0x62E2, 0x3AC7}, {0x0001, 0x4EEC, 0x4A45, 0x3AC7}, {0x0001, 0x65E2, 0x3F2F, 0x3AC7}, {0x0001, 0x233F, 0x4691, 0x3AC7},
    {0x0001, 0x29F8, 0x5123, 0x3AC7}, {0x0001, 0x2CA0, 0x25D0, 0x3AC7}, {0x0001, 0x24AB, 0x2F6F, 0x3AC7}, {0x0001, 0x4EB8, 0x24AB, 0x3AC7},
    {0x0001, 0x4315, 0x200F, 0x3AC7}, {0x0001, 0x5A66, 0x44B9, 0x3AC7}, {0x0001, 0x5B2A, 0x383E, 0x3AC7}, {0x0001, 0x3F8A, 0x59AD, 0x3AC7},
    {0x0001, 0x4BA7, 0x5694, 0x3AC7}, {0x0001, 0x2642, 0x40F7, 0x3AC7}, {0x0001, 0x203C, 0x4C2E, 0x3AC7}, {0x0001, 0x3057, 0x50CD, 0x3AC7},
    {0x0001, 0x239A, 0x5176, 0x3AC7}, {0x0001, 0x32E9, 0x26F3, 0x3AC7}, {0x0001, 0x2658, 0x24AB, 0x3AC7}, {0x0001, 0x26F8, 0x3564, 0x3AC7},
    {0x0001, 0x225F, 0x297C, 0x3AC7}, {0x0001, 0x4F95, 0x2AFC, 0x3AC7}, {0x0001, 0x4DD8, 0x1E58, 0x3AC7}, {0x0001, 0x3E20, 0x2413, 0x3AC7},
    {0x0001, 0x4806, 0x1C0B, 0x3AC7}, {0x0001, 0x54AA, 0x477F, 0x3AC7}, {0x0001, 0x6024, 0x41F5, 0x3AC7}, {0x0001, 0x55CF, 0x34C7, 0x3AC7},
    {0x0001, 0x6088, 0x3BB8, 0x3AC7}, {0x0001, 0x43F4, 0x5E49, 0x3AC7}, {0x0001, 0x3B20, 0x5513, 0x3AC7}, {0x0001, 0x4D48, 0x506C, 0x3AC7},
    {0x0001, 0x4A03, 0x5CBB, 0x3AC7},
};
ChPackedVtx lbl_1_data_BA50[67] = {
    {0x8042, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4154, 0x3EAB, 0x0104}, {0x0000, 0x78D3, 0x5C74, 0x4000}, {0x0000, 0x5F1D, 0x072C, 0x4000},
    {0x0000, 0x09D5, 0x20E2, 0x4000}, {0x0000, 0x238B, 0x762A, 0x4000}, {0x0000, 0x4154, 0x3EAB, 0x7EFB}, {0x0000, 0x5691, 0x4A11, 0x05CF},
    {0x0000, 0x6892, 0x53BB, 0x1376}, {0x0000, 0x7499, 0x5A30, 0x27E5}, {0x0000, 0x4CBA, 0x296E, 0x05CF}, {0x0000, 0x5664, 0x176D, 0x1376},
    {0x0000, 0x5CD9, 0x0B66, 0x27E5}, {0x0000, 0x2C17, 0x3345, 0x05CF}, {0x0000, 0x1A16, 0x299B, 0x1376}, {0x0000, 0x0E0E, 0x2326, 0x27E5},
    {0x0000, 0x35EE, 0x53E8, 0x05CF}, {0x0000, 0x2C44, 0x65E9, 0x1376}, {0x0000, 0x25CF, 0x71F1, 0x27E5}, {0x0000, 0x5691, 0x4A11, 0x7A30},
    {0x0000, 0x6892, 0x53BB, 0x6C89}, {0x0000, 0x7499, 0x5A30, 0x581A}, {0x0000, 0x4CBA, 0x296E, 0x7A30}, {0x0000, 0x5664, 0x176D, 0x6C89},
    {0x0000, 0x5CD9, 0x0B66, 0x581A}, {0x0000, 0x2C17, 0x3345, 0x7A30}, {0x0000, 0x1A16, 0x299B, 0x6C89}, {0x0000, 0x0E0E, 0x2326, 0x581A},
    {0x0000, 0x35EE, 0x53E8, 0x7A30}, {0x0000, 0x2C44, 0x65E9, 0x6C89}, {0x0000, 0x25CF, 0x71F1, 0x581A}, {0x0000, 0x8000, 0x44F3, 0x4000},
    {0x0000, 0x7DA2, 0x2C7D, 0x4000}, {0x0000, 0x7216, 0x16CC, 0x4000}, {0x0000, 0x479C, 0x0000, 0x4000}, {0x0000, 0x2F26, 0x025D, 0x4000},
    {0x0000, 0x1974, 0x0DE9, 0x4000}, {0x0000, 0x02A8, 0x3863, 0x4000}, {0x0000, 0x0506, 0x50D9, 0x4000}, {0x0000, 0x1092, 0x668B, 0x4000},
    {0x0000, 0x3B0C, 0x7D57, 0x4000}, {0x0000, 0x5382, 0x7AF9, 0x4000}, {0x0000, 0x6933, 0x6F6D, 0x4000}, {0x0000, 0x6425, 0x342C, 0x0C92},
    {0x0000, 0x782D, 0x3D99, 0x210E}, {0x0000, 0x6FA1, 0x213F, 0x210E}, {0x0000, 0x36D5, 0x1BDA, 0x0C92}, {0x0000, 0x4042, 0x07D2, 0x210E},
    {0x0000, 0x23E8, 0x105E, 0x210E}, {0x0000, 0x1E83, 0x492A, 0x0C92}, {0x0000, 0x0A7B, 0x3FBD, 0x210E}, {0x0000, 0x1307, 0x5C17, 0x210E},
    {0x0000, 0x4BD3, 0x617C, 0x0C92}, {0x0000, 0x4266, 0x7584, 0x210E}, {0x0000, 0x5EC0, 0x6CF8, 0x210E}, {0x0000, 0x6425, 0x342C, 0x736D},
    {0x0000, 0x6FA1, 0x213F, 0x5EF1}, {0x0000, 0x782D, 0x3D99, 0x5EF1}, {0x0000, 0x36D5, 0x1BDA, 0x736D}, {0x0000, 0x23E8, 0x105E, 0x5EF1},
    {0x0000, 0x4042, 0x07D2, 0x5EF1}, {0x0000, 0x1E83, 0x492A, 0x736D}, {0x0000, 0x1307, 0x5C17, 0x5EF1}, {0x0000, 0x0A7B, 0x3FBD, 0x5EF1},
    {0x0000, 0x4BD3, 0x617C, 0x736D}, {0x0000, 0x5EC0, 0x6CF8, 0x5EF1}, {0x0000, 0x4266, 0x7584, 0x5EF1},
};
ChPackedVtx lbl_1_data_BC68[43] = {
    {0x802A, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4066, 0x3F99, 0x00B9}, {0x0000, 0x6033, 0x0C25, 0x53F9}, {0x0000, 0x0CF3, 0x2BF1, 0x2085},
    {0x0000, 0x73DA, 0x2BF1, 0x2085}, {0x0000, 0x209A, 0x0C25, 0x53F9}, {0x0000, 0x209A, 0x730C, 0x53F9}, {0x0000, 0x73DA, 0x5340, 0x2085},
    {0x0000, 0x0CF3, 0x5340, 0x2085}, {0x0000, 0x6033, 0x730C, 0x53F9}, {0x0000, 0x2CBF, 0x5F65, 0x73C5}, {0x0000, 0x8000, 0x3F99, 0x4052},
    {0x0000, 0x2CBF, 0x1FCC, 0x73C5}, {0x0000, 0x4066, 0x0000, 0x4052}, {0x0000, 0x0CF3, 0x5340, 0x601E}, {0x0000, 0x2CBF, 0x1FCC, 0x0CDE},
    {0x0000, 0x2CBF, 0x5F65, 0x0CDE}, {0x0000, 0x6033, 0x0C25, 0x2CAB}, {0x0000, 0x6033, 0x730C, 0x2CAB}, {0x0000, 0x73DA, 0x5340, 0x601E},
    {0x0000, 0x209A, 0x730C, 0x2CAB}, {0x0000, 0x4066, 0x3F99, 0x7FEB}, {0x0000, 0x0CF3, 0x2BF1, 0x601E}, {0x0000, 0x73DA, 0x2BF1, 0x601E},
    {0x0000, 0x209A, 0x0C25, 0x2CAB}, {0x0000, 0x540E, 0x1FCC, 0x0CDE}, {0x0000, 0x00CD, 0x3F99, 0x4052}, {0x0000, 0x540E, 0x5F65, 0x0CDE},
    {0x0000, 0x4066, 0x7F32, 0x4052}, {0x0000, 0x540E, 0x5F65, 0x73C5}, {0x0000, 0x540E, 0x1FCC, 0x73C5}, {0x0000, 0x4066, 0x2327, 0x2EBE},
    {0x0000, 0x4066, 0x5C0A, 0x2EBE}, {0x0000, 0x51FA, 0x3F99, 0x5CC3}, {0x0000, 0x23F5, 0x2E05, 0x4052}, {0x0000, 0x51FA, 0x3F99, 0x23E1},
    {0x0000, 0x4066, 0x5C0A, 0x51E6}, {0x0000, 0x4066, 0x2327, 0x51E6}, {0x0000, 0x2ED2, 0x3F99, 0x23E1}, {0x0000, 0x5CD8, 0x512D, 0x4052},
    {0x0000, 0x2ED2, 0x3F99, 0x5CC3}, {0x0000, 0x5CD8, 0x2E05, 0x4052}, {0x0000, 0x23F5, 0x512D, 0x4052},
};
ChPackedVtx lbl_1_data_BDC0[43] = {
    {0x802A, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4316, 0x3D0E, 0x0354}, {0x0000, 0x5BC9, 0x6E74, 0x2576}, {0x0000, 0x79B3, 0x34D5, 0x2576},
    {0x0000, 0x4C24, 0x0693, 0x2576}, {0x0000, 0x1212, 0x239C, 0x2576}, {0x0000, 0x1BBD, 0x63D0, 0x2576}, {0x0000, 0x741A, 0x5681, 0x5CB1},
    {0x0000, 0x6A6F, 0x164D, 0x5CB1}, {0x0000, 0x2A63, 0x0BA9, 0x5CB1}, {0x0000, 0x0C79, 0x4548, 0x5CB1}, {0x0000, 0x3A08, 0x738A, 0x5CB1},
    {0x0000, 0x4316, 0x3D0E, 0x7ED3}, {0x0000, 0x519B, 0x5A18, 0x0C8D}, {0x0000, 0x6330, 0x3839, 0x0C8D}, {0x0000, 0x4868, 0x1D09, 0x0C8D},
    {0x0000, 0x2646, 0x2E1A, 0x0C8D}, {0x0000, 0x2BF5, 0x53D6, 0x0C8D}, {0x0000, 0x71B4, 0x5542, 0x209D}, {0x0000, 0x6882, 0x1833, 0x209D},
    {0x0000, 0x2B99, 0x0E14, 0x209D}, {0x0000, 0x0F26, 0x44E1, 0x209D}, {0x0000, 0x3A7A, 0x70DF, 0x209D}, {0x0000, 0x6E6A, 0x690C, 0x4114},
    {0x0000, 0x7A50, 0x2171, 0x4114}, {0x0000, 0x39E4, 0x0000, 0x4114}, {0x0000, 0x062D, 0x32EF, 0x4114}, {0x0000, 0x26A3, 0x73DC, 0x4114},
    {0x0000, 0x4C48, 0x7A1D, 0x4114}, {0x0000, 0x8000, 0x472E, 0x4114}, {0x0000, 0x5F89, 0x0641, 0x4114}, {0x0000, 0x17C2, 0x1111, 0x4114},
    {0x0000, 0x0BDC, 0x58AC, 0x4114}, {0x0000, 0x7707, 0x353C, 0x618A}, {0x0000, 0x4BB2, 0x093E, 0x618A}, {0x0000, 0x1478, 0x24DB, 0x618A},
    {0x0000, 0x1DAA, 0x61EA, 0x618A}, {0x0000, 0x5A94, 0x6C09, 0x618A}, {0x0000, 0x5FE6, 0x4C03, 0x759A}, {0x0000, 0x5A37, 0x2647, 0x759A},
    {0x0000, 0x3492, 0x2005, 0x759A}, {0x0000, 0x22FC, 0x41E4, 0x759A}, {0x0000, 0x3DC4, 0x5D14, 0x759A},
};
ChPackedVtx lbl_1_data_BF18[93] = {
    {0x805C, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4205, 0x3DD3, 0x0108}, {0x0000, 0x7A46, 0x3DD3, 0x23CC}, {0x0000, 0x5367, 0x0853, 0x23CC},
    {0x0000, 0x1483, 0x1CC2, 0x23CC}, {0x0000, 0x1483, 0x5EE3, 0x23CC}, {0x0000, 0x5367, 0x7352, 0x23CC}, {0x0000, 0x6F88, 0x1CC2, 0x5C0C},
    {0x0000, 0x30A3, 0x0853, 0x5C0C}, {0x0000, 0x09C5, 0x3DD3, 0x5C0C}, {0x0000, 0x30A3, 0x7352, 0x5C0C}, {0x0000, 0x6F88, 0x5EE3, 0x5C0C},
    {0x0000, 0x4205, 0x3DD3, 0x7ED0}, {0x0000, 0x58B5, 0x3DD3, 0x0544}, {0x0000, 0x6C57, 0x3DD3, 0x1166}, {0x0000, 0x4908, 0x283F, 0x0544},
    {0x0000, 0x4F19, 0x1593, 0x1166}, {0x0000, 0x2FAB, 0x307D, 0x0544}, {0x0000, 0x1FC9, 0x24F3, 0x1166}, {0x0000, 0x2FAB, 0x4B28, 0x0544},
    {0x0000, 0x1FC9, 0x56B2, 0x1166}, {0x0000, 0x4908, 0x5366, 0x0544}, {0x0000, 0x4F19, 0x6612, 0x1166}, {0x0000, 0x735A, 0x283F, 0x1F6B},
    {0x0000, 0x65C9, 0x1593, 0x1F6B}, {0x0000, 0x3CBE, 0x083D, 0x1F6B}, {0x0000, 0x26CB, 0x0F5F, 0x1F6B}, {0x0000, 0x0D6E, 0x3249, 0x1F6B},
    {0x0000, 0x0D6E, 0x495D, 0x1F6B}, {0x0000, 0x26CB, 0x6C46, 0x1F6B}, {0x0000, 0x3CBE, 0x7368, 0x1F6B}, {0x0000, 0x65C9, 0x6612, 0x1F6B},
    {0x0000, 0x735A, 0x5366, 0x1F6B}, {0x0000, 0x7EB2, 0x307D, 0x361B}, {0x0000, 0x7AF2, 0x24F3, 0x49BD}, {0x0000, 0x4816, 0x0000, 0x361B},
    {0x0000, 0x3BF4, 0x0000, 0x49BD}, {0x0000, 0x0919, 0x24F3, 0x361B}, {0x0000, 0x0559, 0x307D, 0x49BD}, {0x0000, 0x18C6, 0x6C46, 0x361B},
    {0x0000, 0x2297, 0x7368, 0x49BD}, {0x0000, 0x6174, 0x7368, 0x361B}, {0x0000, 0x6B45, 0x6C46, 0x49BD}, {0x0000, 0x7EB2, 0x4B28, 0x361B},
    {0x0000, 0x7AF2, 0x56B2, 0x49BD}, {0x0000, 0x6174, 0x083D, 0x361B}, {0x0000, 0x6B45, 0x0F5F, 0x49BD}, {0x0000, 0x18C6, 0x0F5F, 0x361B},
    {0x0000, 0x2297, 0x083D, 0x49BD}, {0x0000, 0x0919, 0x56B2, 0x361B}, {0x0000, 0x0559, 0x4B28, 0x49BD}, {0x0000, 0x4816, 0x7BA6, 0x361B},
    {0x0000, 0x3BF4, 0x7BA6, 0x49BD}, {0x0000, 0x5D3F, 0x0F5F, 0x606D}, {0x0000, 0x474C, 0x083D, 0x606D}, {0x0000, 0x1E42, 0x1593, 0x606D},
    {0x0000, 0x10B1, 0x283F, 0x606D}, {0x0000, 0x10B1, 0x5366, 0x606D}, {0x0000, 0x1E42, 0x6612, 0x606D}, {0x0000, 0x474C, 0x7368, 0x606D},
    {0x0000, 0x5D3F, 0x6C46, 0x606D}, {0x0000, 0x769D, 0x495D, 0x606D}, {0x0000, 0x769D, 0x3248, 0x606D}, {0x0000, 0x5460, 0x307D, 0x7A94},
    {0x0000, 0x6442, 0x24F3, 0x6E72}, {0x0000, 0x3B03, 0x283F, 0x7A94}, {0x0000, 0x34F1, 0x1593, 0x6E72}, {0x0000, 0x2B55, 0x3DD3, 0x7A94},
    {0x0000, 0x17B4, 0x3DD3, 0x6E72}, {0x0000, 0x3B03, 0x5366, 0x7A94}, {0x0000, 0x34F1, 0x6612, 0x6E72}, {0x0000, 0x5460, 0x4B28, 0x7A94},
    {0x0000, 0x6442, 0x56B2, 0x6E72}, {0x0000, 0x602D, 0x27E9, 0x0D44}, {0x0000, 0x3680, 0x1A5F, 0x0D44}, {0x0000, 0x1CBF, 0x3DD3, 0x0D44},
    {0x0000, 0x3680, 0x6146, 0x0D44}, {0x0000, 0x602D, 0x53BC, 0x0D44}, {0x0000, 0x8000, 0x3DD3, 0x4A9C}, {0x0000, 0x552C, 0x02E1, 0x4A9C},
    {0x0000, 0x0FE1, 0x1965, 0x4A9C}, {0x0000, 0x0FE1, 0x6240, 0x4A9C}, {0x0000, 0x552C, 0x78C4, 0x4A9C}, {0x0000, 0x7429, 0x1965, 0x353C},
    {0x0000, 0x2EDE, 0x02E1, 0x353C}, {0x0000, 0x040B, 0x3DD3, 0x353C}, {0x0000, 0x2EDE, 0x78C4, 0x353C}, {0x0000, 0x7429, 0x6240, 0x353C},
    {0x0000, 0x4D8A, 0x1A5F, 0x7294}, {0x0000, 0x23DD, 0x27E9, 0x7294}, {0x0000, 0x23DD, 0x53BC, 0x7294}, {0x0000, 0x4D8A, 0x6146, 0x7294},
    {0x0000, 0x674C, 0x3DD3, 0x7294},
};
ChPackedVtx lbl_1_data_C200[135] = {
    {0x8086, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4000, 0x4000, 0x144B}, {0x0000, 0x6717, 0x4000, 0x2C74}, {0x0000, 0x4C14, 0x1AD2, 0x2C74},
    {0x0000, 0x2060, 0x2906, 0x2C74}, {0x0000, 0x2060, 0x56F9, 0x2C74}, {0x0000, 0x4C14, 0x652D, 0x2C74}, {0x0000, 0x5F9F, 0x2906, 0x538B},
    {0x0000, 0x33EB, 0x1AD2, 0x538B}, {0x0000, 0x18E8, 0x4000, 0x538B}, {0x0000, 0x33EB, 0x652D, 0x538B}, {0x0000, 0x5F9F, 0x56F9, 0x538B},
    {0x0000, 0x4000, 0x4000, 0x6BB4}, {0x0000, 0x56F9, 0x4000, 0x1AD2}, {0x0000, 0x4719, 0x2A25, 0x1AD2}, {0x0000, 0x2D69, 0x327E, 0x1AD2},
    {0x0000, 0x2D69, 0x4D81, 0x1AD2}, {0x0000, 0x4719, 0x55DA, 0x1AD2}, {0x0000, 0x5E13, 0x2A25, 0x2906}, {0x0000, 0x3483, 0x1CA4, 0x2906},
    {0x0000, 0x1AD2, 0x4000, 0x2906}, {0x0000, 0x3483, 0x635B, 0x2906}, {0x0000, 0x5E13, 0x55DA, 0x2906}, {0x0000, 0x6990, 0x327E, 0x4000},
    {0x0000, 0x4000, 0x144B, 0x4000}, {0x0000, 0x166F, 0x327E, 0x4000}, {0x0000, 0x264F, 0x635B, 0x4000}, {0x0000, 0x59B0, 0x635B, 0x4000},
    {0x0000, 0x6990, 0x4D81, 0x4000}, {0x0000, 0x59B0, 0x1CA4, 0x4000}, {0x0000, 0x264F, 0x1CA4, 0x4000}, {0x0000, 0x166F, 0x4D81, 0x4000},
    {0x0000, 0x4000, 0x6BB4, 0x4000}, {0x0000, 0x4B7C, 0x1CA4, 0x56F9}, {0x0000, 0x21EC, 0x2A25, 0x56F9}, {0x0000, 0x21EC, 0x55DA, 0x56F9},
    {0x0000, 0x4B7C, 0x635B, 0x56F9}, {0x0000, 0x652D, 0x4000, 0x56F9}, {0x0000, 0x5296, 0x327E, 0x652D}, {0x0000, 0x38E6, 0x2A25, 0x652D},
    {0x0000, 0x2906, 0x4000, 0x652D}, {0x0000, 0x38E6, 0x55DA, 0x652D}, {0x0000, 0x5296, 0x4D81, 0x652D}, {0x0001, 0x4000, 0x4000, 0x0000},
    {0x0001, 0x793E, 0x4000, 0x2360}, {0x0001, 0x51B0, 0x098E, 0x2360}, {0x0001, 0x11B0, 0x1E5A, 0x2360}, {0x0001, 0x11B0, 0x61A5, 0x2360},
    {0x0001, 0x51B0, 0x7671, 0x2360}, {0x0001, 0x6E4F, 0x1E5A, 0x5C9F}, {0x0001, 0x2E4F, 0x098E, 0x5C9F}, {0x0001, 0x06C1, 0x4000, 0x5C9F},
    {0x0001, 0x2E4F, 0x7671, 0x5C9F}, {0x0001, 0x6E4F, 0x61A5, 0x5C9F}, {0x0001, 0x4000, 0x4000, 0x8000}, {0x0001, 0x5716, 0x4000, 0x044F},
    {0x0001, 0x6B10, 0x4000, 0x10A7}, {0x0001, 0x4722, 0x2A0B, 0x044F}, {0x0001, 0x4D4E, 0x170B, 0x10A7}, {0x0001, 0x2D52, 0x326E, 0x044F},
    {0x0001, 0x1D28, 0x26AF, 0x10A7}, {0x0001, 0x2D52, 0x4D91, 0x044F}, {0x0001, 0x1D28, 0x5950, 0x10A7}, {0x0001, 0x4722, 0x55F4, 0x044F},
    {0x0001, 0x4D4E, 0x68F4, 0x10A7}, {0x0001, 0x7232, 0x2A0B, 0x1EEC}, {0x0001, 0x6464, 0x170B, 0x1EEC}, {0x0001, 0x3AA1, 0x0979, 0x1EEC},
    {0x0001, 0x244B, 0x10BB, 0x1EEC}, {0x0001, 0x0A7B, 0x3441, 0x1EEC}, {0x0001, 0x0A7B, 0x4BBE, 0x1EEC}, {0x0001, 0x244B, 0x6F44, 0x1EEC},
    {0x0001, 0x3AA1, 0x7686, 0x1EEC}, {0x0001, 0x6464, 0x68F4, 0x1EEC}, {0x0001, 0x7232, 0x55F4, 0x1EEC}, {0x0001, 0x7DBD, 0x326E, 0x3602},
    {0x0001, 0x79ED, 0x26AF, 0x49FD}, {0x0001, 0x462C, 0x0116, 0x3602}, {0x0001, 0x39D3, 0x0116, 0x49FD}, {0x0001, 0x0612, 0x26AF, 0x3602},
    {0x0001, 0x0242, 0x326E, 0x49FD}, {0x0001, 0x1606, 0x6F44, 0x3602}, {0x0001, 0x2003, 0x7686, 0x49FD}, {0x0001, 0x5FFC, 0x7686, 0x3602},
    {0x0001, 0x69F9, 0x6F44, 0x49FD}, {0x0001, 0x7DBD, 0x4D91, 0x3602}, {0x0001, 0x79ED, 0x5950, 0x49FD}, {0x0001, 0x5FFC, 0x0979, 0x3602},
    {0x0001, 0x69F9, 0x10BB, 0x49FD}, {0x0001, 0x1606, 0x10BB, 0x3602}, {0x0001, 0x2003, 0x0979, 0x49FD}, {0x0001, 0x0612, 0x5950, 0x3602},
    {0x0001, 0x0242, 0x4D91, 0x49FD}, {0x0001, 0x462C, 0x7EE9, 0x3602}, {0x0001, 0x39D3, 0x7EE9, 0x49FD}, {0x0001, 0x5BB4, 0x10BB, 0x6113},
    {0x0001, 0x455E, 0x0979, 0x6113}, {0x0001, 0x1B9B, 0x170B, 0x6113}, {0x0001, 0x0DCD, 0x2A0B, 0x6113}, {0x0001, 0x0DCD, 0x55F4, 0x6113},
    {0x0001, 0x1B9B, 0x68F4, 0x6113}, {0x0001, 0x455E, 0x7686, 0x6113}, {0x0001, 0x5BB4, 0x6F44, 0x6113}, {0x0001, 0x7584, 0x4BBE, 0x6113},
    {0x0001, 0x7584, 0x3441, 0x6113}, {0x0001, 0x52AD, 0x326E, 0x7BB0}, {0x0001, 0x62D7, 0x26AF, 0x6F58}, {0x0001, 0x38DD, 0x2A0B, 0x7BB0},
    {0x0001, 0x32B1, 0x170B, 0x6F58}, {0x0001, 0x28E9, 0x4000, 0x7BB0}, {0x0001, 0x14EF, 0x4000, 0x6F58}, {0x0001, 0x38DD, 0x55F4, 0x7BB0},
    {0x0001, 0x32B1, 0x68F4, 0x6F58}, {0x0001, 0x52AD, 0x4D91, 0x7BB0}, {0x0001, 0x62D7, 0x5950, 0x6F58}, {0x0001, 0x5EB0, 0x29B4, 0x0C73},
    {0x0001, 0x3447, 0x1BEC, 0x0C73}, {0x0001, 0x1A11, 0x4000, 0x0C73}, {0x0001, 0x3447, 0x6413, 0x0C73}, {0x0001, 0x5EB0, 0x564B, 0x0C73},
    {0x0001, 0x7F11, 0x4000, 0x4AE0}, {0x0001, 0x537D, 0x0404, 0x4AE0}, {0x0001, 0x0CF9, 0x1AED, 0x4AE0}, {0x0001, 0x0CF9, 0x6512, 0x4AE0},
    {0x0001, 0x537D, 0x7BFB, 0x4AE0}, {0x0001, 0x7306, 0x1AED, 0x351F}, {0x0001, 0x2C82, 0x0404, 0x351F}, {0x0001, 0x00EE, 0x4000, 0x351F},
    {0x0001, 0x2C82, 0x7BFB, 0x351F}, {0x0001, 0x7306, 0x6512, 0x351F}, {0x0001, 0x4BB8, 0x1BEC, 0x738C}, {0x0001, 0x214F, 0x29B4, 0x738C},
    {0x0001, 0x214F, 0x564B, 0x738C}, {0x0001, 0x4BB8, 0x6413, 0x738C}, {0x0001, 0x65EE, 0x4000, 0x738C},
};
ChPackedVtx lbl_1_data_C638[135] = {
    {0x8086, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4000, 0x4000, 0x144B}, {0x0000, 0x6717, 0x4000, 0x2C74}, {0x0000, 0x4C14, 0x1AD2, 0x2C74},
    {0x0000, 0x2060, 0x2906, 0x2C74}, {0x0000, 0x2060, 0x56F9, 0x2C74}, {0x0000, 0x4C14, 0x652D, 0x2C74}, {0x0000, 0x5F9F, 0x2906, 0x538B},
    {0x0000, 0x33EB, 0x1AD2, 0x538B}, {0x0000, 0x18E8, 0x4000, 0x538B}, {0x0000, 0x33EB, 0x652D, 0x538B}, {0x0000, 0x5F9F, 0x56F9, 0x538B},
    {0x0000, 0x4000, 0x4000, 0x6BB4}, {0x0000, 0x56F9, 0x4000, 0x1AD2}, {0x0000, 0x4719, 0x2A25, 0x1AD2}, {0x0000, 0x2D69, 0x327E, 0x1AD2},
    {0x0000, 0x2D69, 0x4D81, 0x1AD2}, {0x0000, 0x4719, 0x55DA, 0x1AD2}, {0x0000, 0x5E13, 0x2A25, 0x2906}, {0x0000, 0x3483, 0x1CA4, 0x2906},
    {0x0000, 0x1AD2, 0x4000, 0x2906}, {0x0000, 0x3483, 0x635B, 0x2906}, {0x0000, 0x5E13, 0x55DA, 0x2906}, {0x0000, 0x6990, 0x327E, 0x4000},
    {0x0000, 0x4000, 0x144B, 0x4000}, {0x0000, 0x166F, 0x327E, 0x4000}, {0x0000, 0x264F, 0x635B, 0x4000}, {0x0000, 0x59B0, 0x635B, 0x4000},
    {0x0000, 0x6990, 0x4D81, 0x4000}, {0x0000, 0x59B0, 0x1CA4, 0x4000}, {0x0000, 0x264F, 0x1CA4, 0x4000}, {0x0000, 0x166F, 0x4D81, 0x4000},
    {0x0000, 0x4000, 0x6BB4, 0x4000}, {0x0000, 0x4B7C, 0x1CA4, 0x56F9}, {0x0000, 0x21EC, 0x2A25, 0x56F9}, {0x0000, 0x21EC, 0x55DA, 0x56F9},
    {0x0000, 0x4B7C, 0x635B, 0x56F9}, {0x0000, 0x652D, 0x4000, 0x56F9}, {0x0000, 0x5296, 0x327E, 0x652D}, {0x0000, 0x38E6, 0x2A25, 0x652D},
    {0x0000, 0x2906, 0x4000, 0x652D}, {0x0000, 0x38E6, 0x55DA, 0x652D}, {0x0000, 0x5296, 0x4D81, 0x652D}, {0x0001, 0x4000, 0x4000, 0x0000},
    {0x0001, 0x793E, 0x4000, 0x2360}, {0x0001, 0x51B0, 0x098E, 0x2360}, {0x0001, 0x11B0, 0x1E5A, 0x2360}, {0x0001, 0x11B0, 0x61A5, 0x2360},
    {0x0001, 0x51B0, 0x7671, 0x2360}, {0x0001, 0x6E4F, 0x1E5A, 0x5C9F}, {0x0001, 0x2E4F, 0x098E, 0x5C9F}, {0x0001, 0x06C1, 0x4000, 0x5C9F},
    {0x0001, 0x2E4F, 0x7671, 0x5C9F}, {0x0001, 0x6E4F, 0x61A5, 0x5C9F}, {0x0001, 0x4000, 0x4000, 0x8000}, {0x0001, 0x5716, 0x4000, 0x044F},
    {0x0001, 0x6B10, 0x4000, 0x10A7}, {0x0001, 0x4722, 0x2A0B, 0x044F}, {0x0001, 0x4D4E, 0x170B, 0x10A7}, {0x0001, 0x2D52, 0x326E, 0x044F},
    {0x0001, 0x1D28, 0x26AF, 0x10A7}, {0x0001, 0x2D52, 0x4D91, 0x044F}, {0x0001, 0x1D28, 0x5950, 0x10A7}, {0x0001, 0x4722, 0x55F4, 0x044F},
    {0x0001, 0x4D4E, 0x68F4, 0x10A7}, {0x0001, 0x7232, 0x2A0B, 0x1EEC}, {0x0001, 0x6464, 0x170B, 0x1EEC}, {0x0001, 0x3AA1, 0x0979, 0x1EEC},
    {0x0001, 0x244B, 0x10BB, 0x1EEC}, {0x0001, 0x0A7B, 0x3441, 0x1EEC}, {0x0001, 0x0A7B, 0x4BBE, 0x1EEC}, {0x0001, 0x244B, 0x6F44, 0x1EEC},
    {0x0001, 0x3AA1, 0x7686, 0x1EEC}, {0x0001, 0x6464, 0x68F4, 0x1EEC}, {0x0001, 0x7232, 0x55F4, 0x1EEC}, {0x0001, 0x7DBD, 0x326E, 0x3602},
    {0x0001, 0x79ED, 0x26AF, 0x49FD}, {0x0001, 0x462C, 0x0116, 0x3602}, {0x0001, 0x39D3, 0x0116, 0x49FD}, {0x0001, 0x0612, 0x26AF, 0x3602},
    {0x0001, 0x0242, 0x326E, 0x49FD}, {0x0001, 0x1606, 0x6F44, 0x3602}, {0x0001, 0x2003, 0x7686, 0x49FD}, {0x0001, 0x5FFC, 0x7686, 0x3602},
    {0x0001, 0x69F9, 0x6F44, 0x49FD}, {0x0001, 0x7DBD, 0x4D91, 0x3602}, {0x0001, 0x79ED, 0x5950, 0x49FD}, {0x0001, 0x5FFC, 0x0979, 0x3602},
    {0x0001, 0x69F9, 0x10BB, 0x49FD}, {0x0001, 0x1606, 0x10BB, 0x3602}, {0x0001, 0x2003, 0x0979, 0x49FD}, {0x0001, 0x0612, 0x5950, 0x3602},
    {0x0001, 0x0242, 0x4D91, 0x49FD}, {0x0001, 0x462C, 0x7EE9, 0x3602}, {0x0001, 0x39D3, 0x7EE9, 0x49FD}, {0x0001, 0x5BB4, 0x10BB, 0x6113},
    {0x0001, 0x455E, 0x0979, 0x6113}, {0x0001, 0x1B9B, 0x170B, 0x6113}, {0x0001, 0x0DCD, 0x2A0B, 0x6113}, {0x0001, 0x0DCD, 0x55F4, 0x6113},
    {0x0001, 0x1B9B, 0x68F4, 0x6113}, {0x0001, 0x455E, 0x7686, 0x6113}, {0x0001, 0x5BB4, 0x6F44, 0x6113}, {0x0001, 0x7584, 0x4BBE, 0x6113},
    {0x0001, 0x7584, 0x3441, 0x6113}, {0x0001, 0x52AD, 0x326E, 0x7BB0}, {0x0001, 0x62D7, 0x26AF, 0x6F58}, {0x0001, 0x38DD, 0x2A0B, 0x7BB0},
    {0x0001, 0x32B1, 0x170B, 0x6F58}, {0x0001, 0x28E9, 0x4000, 0x7BB0}, {0x0001, 0x14EF, 0x4000, 0x6F58}, {0x0001, 0x38DD, 0x55F4, 0x7BB0},
    {0x0001, 0x32B1, 0x68F4, 0x6F58}, {0x0001, 0x52AD, 0x4D91, 0x7BB0}, {0x0001, 0x62D7, 0x5950, 0x6F58}, {0x0001, 0x5EB0, 0x29B4, 0x0C73},
    {0x0001, 0x3447, 0x1BEC, 0x0C73}, {0x0001, 0x1A11, 0x4000, 0x0C73}, {0x0001, 0x3447, 0x6413, 0x0C73}, {0x0001, 0x5EB0, 0x564B, 0x0C73},
    {0x0001, 0x7F11, 0x4000, 0x4AE0}, {0x0001, 0x537D, 0x0404, 0x4AE0}, {0x0001, 0x0CF9, 0x1AED, 0x4AE0}, {0x0001, 0x0CF9, 0x6512, 0x4AE0},
    {0x0001, 0x537D, 0x7BFB, 0x4AE0}, {0x0001, 0x7306, 0x1AED, 0x351F}, {0x0001, 0x2C82, 0x0404, 0x351F}, {0x0001, 0x00EE, 0x4000, 0x351F},
    {0x0001, 0x2C82, 0x7BFB, 0x351F}, {0x0001, 0x7306, 0x6512, 0x351F}, {0x0001, 0x4BB8, 0x1BEC, 0x738C}, {0x0001, 0x214F, 0x29B4, 0x738C},
    {0x0001, 0x214F, 0x564B, 0x738C}, {0x0001, 0x4BB8, 0x6413, 0x738C}, {0x0001, 0x65EE, 0x4000, 0x738C},
};
ChPackedVtx lbl_1_data_CA70[147] = {
    {0x8092, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4000, 0x4000, 0x0D62}, {0x0000, 0x6D45, 0x4000, 0x295D}, {0x0000, 0x4DFD, 0x14F1, 0x295D},
    {0x0000, 0x1B60, 0x2564, 0x295D}, {0x0000, 0x1B60, 0x5A9B, 0x295D}, {0x0000, 0x4DFD, 0x6B0E, 0x295D}, {0x0000, 0x649F, 0x2564, 0x56A2},
    {0x0000, 0x3202, 0x14F1, 0x56A2}, {0x0000, 0x12BA, 0x4000, 0x56A2}, {0x0000, 0x3202, 0x6B0E, 0x56A2}, {0x0000, 0x649F, 0x5A9B, 0x56A2},
    {0x0000, 0x4000, 0x4000, 0x729D}, {0x0000, 0x5A9B, 0x4000, 0x14F1}, {0x0000, 0x4839, 0x26B1, 0x14F1}, {0x0000, 0x2A78, 0x305C, 0x14F1},
    {0x0000, 0x2A78, 0x4FA3, 0x14F1}, {0x0000, 0x4839, 0x594E, 0x14F1}, {0x0000, 0x62D5, 0x26B1, 0x2564}, {0x0000, 0x32B2, 0x170D, 0x2564},
    {0x0000, 0x14F1, 0x4000, 0x2564}, {0x0000, 0x32B2, 0x68F2, 0x2564}, {0x0000, 0x62D5, 0x594E, 0x2564}, {0x0000, 0x7023, 0x305C, 0x4000},
    {0x0000, 0x4000, 0x0D62, 0x4000}, {0x0000, 0x0FDC, 0x305C, 0x4000}, {0x0000, 0x223F, 0x68F2, 0x4000}, {0x0000, 0x5DC0, 0x68F2, 0x4000},
    {0x0000, 0x7023, 0x4FA3, 0x4000}, {0x0000, 0x5DC0, 0x170D, 0x4000}, {0x0000, 0x223F, 0x170D, 0x4000}, {0x0000, 0x0FDC, 0x4FA3, 0x4000},
    {0x0000, 0x4000, 0x729D, 0x4000}, {0x0000, 0x4D4D, 0x170D, 0x5A9B}, {0x0000, 0x1D2A, 0x26B1, 0x5A9B}, {0x0000, 0x1D2A, 0x594E, 0x5A9B},
    {0x0000, 0x4D4D, 0x68F2, 0x5A9B}, {0x0000, 0x6B0E, 0x4000, 0x5A9B}, {0x0000, 0x5587, 0x305C, 0x6B0E}, {0x0000, 0x37C6, 0x26B1, 0x6B0E},
    {0x0000, 0x2564, 0x4000, 0x6B0E}, {0x0000, 0x37C6, 0x594E, 0x6B0E}, {0x0000, 0x5587, 0x4FA3, 0x6B0E}, {0x0001, 0x4000, 0x4000, 0x0000},
    {0x0001, 0x793E, 0x4000, 0x2360}, {0x0001, 0x51B0, 0x098E, 0x2360}, {0x0001, 0x11B0, 0x1E5A, 0x2360}, {0x0001, 0x11B0, 0x61A5, 0x2360},
    {0x0001, 0x51B0, 0x7671, 0x2360}, {0x0001, 0x6E4F, 0x1E5A, 0x5C9F}, {0x0001, 0x2E4F, 0x098E, 0x5C9F}, {0x0001, 0x06C1, 0x4000, 0x5C9F},
    {0x0001, 0x2E4F, 0x7671, 0x5C9F}, {0x0001, 0x6E4F, 0x61A5, 0x5C9F}, {0x0001, 0x4000, 0x4000, 0x8000}, {0x0001, 0x5716, 0x4000, 0x044F},
    {0x0001, 0x6B10, 0x4000, 0x10A7}, {0x0001, 0x4722, 0x2A0B, 0x044F}, {0x0001, 0x4D4E, 0x170B, 0x10A7}, {0x0001, 0x2D52, 0x326E, 0x044F},
    {0x0001, 0x1D28, 0x26AF, 0x10A7}, {0x0001, 0x2D52, 0x4D91, 0x044F}, {0x0001, 0x1D28, 0x5950, 0x10A7}, {0x0001, 0x4722, 0x55F4, 0x044F},
    {0x0001, 0x4D4E, 0x68F4, 0x10A7}, {0x0001, 0x7232, 0x2A0B, 0x1EEC}, {0x0001, 0x6464, 0x170B, 0x1EEC}, {0x0001, 0x3AA1, 0x0979, 0x1EEC},
    {0x0001, 0x244B, 0x10BB, 0x1EEC}, {0x0001, 0x0A7B, 0x3441, 0x1EEC}, {0x0001, 0x0A7B, 0x4BBE, 0x1EEC}, {0x0001, 0x244B, 0x6F44, 0x1EEC},
    {0x0001, 0x3AA1, 0x7686, 0x1EEC}, {0x0001, 0x6464, 0x68F4, 0x1EEC}, {0x0001, 0x7232, 0x55F4, 0x1EEC}, {0x0001, 0x7DBD, 0x326E, 0x3602},
    {0x0001, 0x79ED, 0x26AF, 0x49FD}, {0x0001, 0x462C, 0x0116, 0x3602}, {0x0001, 0x39D3, 0x0116, 0x49FD}, {0x0001, 0x0612, 0x26AF, 0x3602},
    {0x0001, 0x0242, 0x326E, 0x49FD}, {0x0001, 0x1606, 0x6F44, 0x3602}, {0x0001, 0x2003, 0x7686, 0x49FD}, {0x0001, 0x5FFC, 0x7686, 0x3602},
    {0x0001, 0x69F9, 0x6F44, 0x49FD}, {0x0001, 0x7DBD, 0x4D91, 0x3602}, {0x0001, 0x79ED, 0x5950, 0x49FD}, {0x0001, 0x5FFC, 0x0979, 0x3602},
    {0x0001, 0x69F9, 0x10BB, 0x49FD}, {0x0001, 0x1606, 0x10BB, 0x3602}, {0x0001, 0x2003, 0x0979, 0x49FD}, {0x0001, 0x0612, 0x5950, 0x3602},
    {0x0001, 0x0242, 0x4D91, 0x49FD}, {0x0001, 0x462C, 0x7EE9, 0x3602}, {0x0001, 0x39D3, 0x7EE9, 0x49FD}, {0x0001, 0x5BB4, 0x10BB, 0x6113},
    {0x0001, 0x455E, 0x0979, 0x6113}, {0x0001, 0x1B9B, 0x170B, 0x6113}, {0x0001, 0x0DCD, 0x2A0B, 0x6113}, {0x0001, 0x0DCD, 0x55F4, 0x6113},
    {0x0001, 0x1B9B, 0x68F4, 0x6113}, {0x0001, 0x455E, 0x7686, 0x6113}, {0x0001, 0x5BB4, 0x6F44, 0x6113}, {0x0001, 0x7584, 0x4BBE, 0x6113},
    {0x0001, 0x7584, 0x3441, 0x6113}, {0x0001, 0x52AD, 0x326E, 0x7BB0}, {0x0001, 0x62D7, 0x26AF, 0x6F58}, {0x0001, 0x38DD, 0x2A0B, 0x7BB0},
    {0x0001, 0x32B1, 0x170B, 0x6F58}, {0x0001, 0x28E9, 0x4000, 0x7BB0}, {0x0001, 0x14EF, 0x4000, 0x6F58}, {0x0001, 0x38DD, 0x55F4, 0x7BB0},
    {0x0001, 0x32B1, 0x68F4, 0x6F58}, {0x0001, 0x52AD, 0x4D91, 0x7BB0}, {0x0001, 0x62D7, 0x5950, 0x6F58}, {0x0001, 0x5EB0, 0x29B4, 0x0C73},
    {0x0001, 0x3447, 0x1BEC, 0x0C73}, {0x0001, 0x1A11, 0x4000, 0x0C73}, {0x0001, 0x3447, 0x6413, 0x0C73}, {0x0001, 0x5EB0, 0x564B, 0x0C73},
    {0x0001, 0x7F11, 0x4000, 0x4AE0}, {0x0001, 0x537D, 0x0404, 0x4AE0}, {0x0001, 0x0CF9, 0x1AED, 0x4AE0}, {0x0001, 0x0CF9, 0x6512, 0x4AE0},
    {0x0001, 0x537D, 0x7BFB, 0x4AE0}, {0x0001, 0x7306, 0x1AED, 0x351F}, {0x0001, 0x2C82, 0x0404, 0x351F}, {0x0001, 0x00EE, 0x4000, 0x351F},
    {0x0001, 0x2C82, 0x7BFB, 0x351F}, {0x0001, 0x7306, 0x6512, 0x351F}, {0x0001, 0x4BB8, 0x1BEC, 0x738C}, {0x0001, 0x214F, 0x29B4, 0x738C},
    {0x0001, 0x214F, 0x564B, 0x738C}, {0x0001, 0x4BB8, 0x6413, 0x738C}, {0x0001, 0x65EE, 0x4000, 0x738C}, {0x0002, 0x4000, 0x4000, 0x186A},
    {0x0002, 0x6367, 0x4000, 0x2E4C}, {0x0002, 0x4AF0, 0x1E53, 0x2E4C}, {0x0002, 0x235B, 0x2B30, 0x2E4C}, {0x0002, 0x235B, 0x54CF, 0x2E4C},
    {0x0002, 0x4AF0, 0x61AC, 0x2E4C}, {0x0002, 0x5CA4, 0x2B30, 0x51B3}, {0x0002, 0x350F, 0x1E53, 0x51B3}, {0x0002, 0x1C98, 0x4000, 0x51B3},
    {0x0002, 0x350F, 0x61AC, 0x51B3}, {0x0002, 0x5CA4, 0x54CF, 0x51B3}, {0x0002, 0x4000, 0x4000, 0x6795},
};
ChPackedVtx lbl_1_data_CF08[147] = {
    {0x8092, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4000, 0x4000, 0x0D62}, {0x0000, 0x6D45, 0x4000, 0x295D}, {0x0000, 0x4DFD, 0x14F1, 0x295D},
    {0x0000, 0x1B60, 0x2564, 0x295D}, {0x0000, 0x1B60, 0x5A9B, 0x295D}, {0x0000, 0x4DFD, 0x6B0E, 0x295D}, {0x0000, 0x649F, 0x2564, 0x56A2},
    {0x0000, 0x3202, 0x14F1, 0x56A2}, {0x0000, 0x12BA, 0x4000, 0x56A2}, {0x0000, 0x3202, 0x6B0E, 0x56A2}, {0x0000, 0x649F, 0x5A9B, 0x56A2},
    {0x0000, 0x4000, 0x4000, 0x729D}, {0x0000, 0x5A9B, 0x4000, 0x14F1}, {0x0000, 0x4839, 0x26B1, 0x14F1}, {0x0000, 0x2A78, 0x305C, 0x14F1},
    {0x0000, 0x2A78, 0x4FA3, 0x14F1}, {0x0000, 0x4839, 0x594E, 0x14F1}, {0x0000, 0x62D5, 0x26B1, 0x2564}, {0x0000, 0x32B2, 0x170D, 0x2564},
    {0x0000, 0x14F1, 0x4000, 0x2564}, {0x0000, 0x32B2, 0x68F2, 0x2564}, {0x0000, 0x62D5, 0x594E, 0x2564}, {0x0000, 0x7023, 0x305C, 0x4000},
    {0x0000, 0x4000, 0x0D62, 0x4000}, {0x0000, 0x0FDC, 0x305C, 0x4000}, {0x0000, 0x223F, 0x68F2, 0x4000}, {0x0000, 0x5DC0, 0x68F2, 0x4000},
    {0x0000, 0x7023, 0x4FA3, 0x4000}, {0x0000, 0x5DC0, 0x170D, 0x4000}, {0x0000, 0x223F, 0x170D, 0x4000}, {0x0000, 0x0FDC, 0x4FA3, 0x4000},
    {0x0000, 0x4000, 0x729D, 0x4000}, {0x0000, 0x4D4D, 0x170D, 0x5A9B}, {0x0000, 0x1D2A, 0x26B1, 0x5A9B}, {0x0000, 0x1D2A, 0x594E, 0x5A9B},
    {0x0000, 0x4D4D, 0x68F2, 0x5A9B}, {0x0000, 0x6B0E, 0x4000, 0x5A9B}, {0x0000, 0x5587, 0x305C, 0x6B0E}, {0x0000, 0x37C6, 0x26B1, 0x6B0E},
    {0x0000, 0x2564, 0x4000, 0x6B0E}, {0x0000, 0x37C6, 0x594E, 0x6B0E}, {0x0000, 0x5587, 0x4FA3, 0x6B0E}, {0x0001, 0x4000, 0x4000, 0x0000},
    {0x0001, 0x793E, 0x4000, 0x2360}, {0x0001, 0x51B0, 0x098E, 0x2360}, {0x0001, 0x11B0, 0x1E5A, 0x2360}, {0x0001, 0x11B0, 0x61A5, 0x2360},
    {0x0001, 0x51B0, 0x7671, 0x2360}, {0x0001, 0x6E4F, 0x1E5A, 0x5C9F}, {0x0001, 0x2E4F, 0x098E, 0x5C9F}, {0x0001, 0x06C1, 0x4000, 0x5C9F},
    {0x0001, 0x2E4F, 0x7671, 0x5C9F}, {0x0001, 0x6E4F, 0x61A5, 0x5C9F}, {0x0001, 0x4000, 0x4000, 0x8000}, {0x0001, 0x5716, 0x4000, 0x044F},
    {0x0001, 0x6B10, 0x4000, 0x10A7}, {0x0001, 0x4722, 0x2A0B, 0x044F}, {0x0001, 0x4D4E, 0x170B, 0x10A7}, {0x0001, 0x2D52, 0x326E, 0x044F},
    {0x0001, 0x1D28, 0x26AF, 0x10A7}, {0x0001, 0x2D52, 0x4D91, 0x044F}, {0x0001, 0x1D28, 0x5950, 0x10A7}, {0x0001, 0x4722, 0x55F4, 0x044F},
    {0x0001, 0x4D4E, 0x68F4, 0x10A7}, {0x0001, 0x7232, 0x2A0B, 0x1EEC}, {0x0001, 0x6464, 0x170B, 0x1EEC}, {0x0001, 0x3AA1, 0x0979, 0x1EEC},
    {0x0001, 0x244B, 0x10BB, 0x1EEC}, {0x0001, 0x0A7B, 0x3441, 0x1EEC}, {0x0001, 0x0A7B, 0x4BBE, 0x1EEC}, {0x0001, 0x244B, 0x6F44, 0x1EEC},
    {0x0001, 0x3AA1, 0x7686, 0x1EEC}, {0x0001, 0x6464, 0x68F4, 0x1EEC}, {0x0001, 0x7232, 0x55F4, 0x1EEC}, {0x0001, 0x7DBD, 0x326E, 0x3602},
    {0x0001, 0x79ED, 0x26AF, 0x49FD}, {0x0001, 0x462C, 0x0116, 0x3602}, {0x0001, 0x39D3, 0x0116, 0x49FD}, {0x0001, 0x0612, 0x26AF, 0x3602},
    {0x0001, 0x0242, 0x326E, 0x49FD}, {0x0001, 0x1606, 0x6F44, 0x3602}, {0x0001, 0x2003, 0x7686, 0x49FD}, {0x0001, 0x5FFC, 0x7686, 0x3602},
    {0x0001, 0x69F9, 0x6F44, 0x49FD}, {0x0001, 0x7DBD, 0x4D91, 0x3602}, {0x0001, 0x79ED, 0x5950, 0x49FD}, {0x0001, 0x5FFC, 0x0979, 0x3602},
    {0x0001, 0x69F9, 0x10BB, 0x49FD}, {0x0001, 0x1606, 0x10BB, 0x3602}, {0x0001, 0x2003, 0x0979, 0x49FD}, {0x0001, 0x0612, 0x5950, 0x3602},
    {0x0001, 0x0242, 0x4D91, 0x49FD}, {0x0001, 0x462C, 0x7EE9, 0x3602}, {0x0001, 0x39D3, 0x7EE9, 0x49FD}, {0x0001, 0x5BB4, 0x10BB, 0x6113},
    {0x0001, 0x455E, 0x0979, 0x6113}, {0x0001, 0x1B9B, 0x170B, 0x6113}, {0x0001, 0x0DCD, 0x2A0B, 0x6113}, {0x0001, 0x0DCD, 0x55F4, 0x6113},
    {0x0001, 0x1B9B, 0x68F4, 0x6113}, {0x0001, 0x455E, 0x7686, 0x6113}, {0x0001, 0x5BB4, 0x6F44, 0x6113}, {0x0001, 0x7584, 0x4BBE, 0x6113},
    {0x0001, 0x7584, 0x3441, 0x6113}, {0x0001, 0x52AD, 0x326E, 0x7BB0}, {0x0001, 0x62D7, 0x26AF, 0x6F58}, {0x0001, 0x38DD, 0x2A0B, 0x7BB0},
    {0x0001, 0x32B1, 0x170B, 0x6F58}, {0x0001, 0x28E9, 0x4000, 0x7BB0}, {0x0001, 0x14EF, 0x4000, 0x6F58}, {0x0001, 0x38DD, 0x55F4, 0x7BB0},
    {0x0001, 0x32B1, 0x68F4, 0x6F58}, {0x0001, 0x52AD, 0x4D91, 0x7BB0}, {0x0001, 0x62D7, 0x5950, 0x6F58}, {0x0001, 0x5EB0, 0x29B4, 0x0C73},
    {0x0001, 0x3447, 0x1BEC, 0x0C73}, {0x0001, 0x1A11, 0x4000, 0x0C73}, {0x0001, 0x3447, 0x6413, 0x0C73}, {0x0001, 0x5EB0, 0x564B, 0x0C73},
    {0x0001, 0x7F11, 0x4000, 0x4AE0}, {0x0001, 0x537D, 0x0404, 0x4AE0}, {0x0001, 0x0CF9, 0x1AED, 0x4AE0}, {0x0001, 0x0CF9, 0x6512, 0x4AE0},
    {0x0001, 0x537D, 0x7BFB, 0x4AE0}, {0x0001, 0x7306, 0x1AED, 0x351F}, {0x0001, 0x2C82, 0x0404, 0x351F}, {0x0001, 0x00EE, 0x4000, 0x351F},
    {0x0001, 0x2C82, 0x7BFB, 0x351F}, {0x0001, 0x7306, 0x6512, 0x351F}, {0x0001, 0x4BB8, 0x1BEC, 0x738C}, {0x0001, 0x214F, 0x29B4, 0x738C},
    {0x0001, 0x214F, 0x564B, 0x738C}, {0x0001, 0x4BB8, 0x6413, 0x738C}, {0x0001, 0x65EE, 0x4000, 0x738C}, {0x0002, 0x4000, 0x4000, 0x186A},
    {0x0002, 0x6367, 0x4000, 0x2E4C}, {0x0002, 0x4AF0, 0x1E53, 0x2E4C}, {0x0002, 0x235B, 0x2B30, 0x2E4C}, {0x0002, 0x235B, 0x54CF, 0x2E4C},
    {0x0002, 0x4AF0, 0x61AC, 0x2E4C}, {0x0002, 0x5CA4, 0x2B30, 0x51B3}, {0x0002, 0x350F, 0x1E53, 0x51B3}, {0x0002, 0x1C98, 0x4000, 0x51B3},
    {0x0002, 0x350F, 0x61AC, 0x51B3}, {0x0002, 0x5CA4, 0x54CF, 0x51B3}, {0x0002, 0x4000, 0x4000, 0x6795},
};
ChPackedVtx lbl_1_data_D3A0[147] = {
    {0x8092, 0x8000, 0x8000, 0x8000}, {0x0000, 0x4000, 0x4000, 0x0D62}, {0x0000, 0x6D45, 0x4000, 0x295D}, {0x0000, 0x4DFD, 0x14F1, 0x295D},
    {0x0000, 0x1B60, 0x2564, 0x295D}, {0x0000, 0x1B60, 0x5A9B, 0x295D}, {0x0000, 0x4DFD, 0x6B0E, 0x295D}, {0x0000, 0x649F, 0x2564, 0x56A2},
    {0x0000, 0x3202, 0x14F1, 0x56A2}, {0x0000, 0x12BA, 0x4000, 0x56A2}, {0x0000, 0x3202, 0x6B0E, 0x56A2}, {0x0000, 0x649F, 0x5A9B, 0x56A2},
    {0x0000, 0x4000, 0x4000, 0x729D}, {0x0000, 0x5A9B, 0x4000, 0x14F1}, {0x0000, 0x4839, 0x26B1, 0x14F1}, {0x0000, 0x2A78, 0x305C, 0x14F1},
    {0x0000, 0x2A78, 0x4FA3, 0x14F1}, {0x0000, 0x4839, 0x594E, 0x14F1}, {0x0000, 0x62D5, 0x26B1, 0x2564}, {0x0000, 0x32B2, 0x170D, 0x2564},
    {0x0000, 0x14F1, 0x4000, 0x2564}, {0x0000, 0x32B2, 0x68F2, 0x2564}, {0x0000, 0x62D5, 0x594E, 0x2564}, {0x0000, 0x7023, 0x305C, 0x4000},
    {0x0000, 0x4000, 0x0D62, 0x4000}, {0x0000, 0x0FDC, 0x305C, 0x4000}, {0x0000, 0x223F, 0x68F2, 0x4000}, {0x0000, 0x5DC0, 0x68F2, 0x4000},
    {0x0000, 0x7023, 0x4FA3, 0x4000}, {0x0000, 0x5DC0, 0x170D, 0x4000}, {0x0000, 0x223F, 0x170D, 0x4000}, {0x0000, 0x0FDC, 0x4FA3, 0x4000},
    {0x0000, 0x4000, 0x729D, 0x4000}, {0x0000, 0x4D4D, 0x170D, 0x5A9B}, {0x0000, 0x1D2A, 0x26B1, 0x5A9B}, {0x0000, 0x1D2A, 0x594E, 0x5A9B},
    {0x0000, 0x4D4D, 0x68F2, 0x5A9B}, {0x0000, 0x6B0E, 0x4000, 0x5A9B}, {0x0000, 0x5587, 0x305C, 0x6B0E}, {0x0000, 0x37C6, 0x26B1, 0x6B0E},
    {0x0000, 0x2564, 0x4000, 0x6B0E}, {0x0000, 0x37C6, 0x594E, 0x6B0E}, {0x0000, 0x5587, 0x4FA3, 0x6B0E}, {0x0001, 0x4000, 0x4000, 0x0000},
    {0x0001, 0x793E, 0x4000, 0x2360}, {0x0001, 0x51B0, 0x098E, 0x2360}, {0x0001, 0x11B0, 0x1E5A, 0x2360}, {0x0001, 0x11B0, 0x61A5, 0x2360},
    {0x0001, 0x51B0, 0x7671, 0x2360}, {0x0001, 0x6E4F, 0x1E5A, 0x5C9F}, {0x0001, 0x2E4F, 0x098E, 0x5C9F}, {0x0001, 0x06C1, 0x4000, 0x5C9F},
    {0x0001, 0x2E4F, 0x7671, 0x5C9F}, {0x0001, 0x6E4F, 0x61A5, 0x5C9F}, {0x0001, 0x4000, 0x4000, 0x8000}, {0x0001, 0x5716, 0x4000, 0x044F},
    {0x0001, 0x6B10, 0x4000, 0x10A7}, {0x0001, 0x4722, 0x2A0B, 0x044F}, {0x0001, 0x4D4E, 0x170B, 0x10A7}, {0x0001, 0x2D52, 0x326E, 0x044F},
    {0x0001, 0x1D28, 0x26AF, 0x10A7}, {0x0001, 0x2D52, 0x4D91, 0x044F}, {0x0001, 0x1D28, 0x5950, 0x10A7}, {0x0001, 0x4722, 0x55F4, 0x044F},
    {0x0001, 0x4D4E, 0x68F4, 0x10A7}, {0x0001, 0x7232, 0x2A0B, 0x1EEC}, {0x0001, 0x6464, 0x170B, 0x1EEC}, {0x0001, 0x3AA1, 0x0979, 0x1EEC},
    {0x0001, 0x244B, 0x10BB, 0x1EEC}, {0x0001, 0x0A7B, 0x3441, 0x1EEC}, {0x0001, 0x0A7B, 0x4BBE, 0x1EEC}, {0x0001, 0x244B, 0x6F44, 0x1EEC},
    {0x0001, 0x3AA1, 0x7686, 0x1EEC}, {0x0001, 0x6464, 0x68F4, 0x1EEC}, {0x0001, 0x7232, 0x55F4, 0x1EEC}, {0x0001, 0x7DBD, 0x326E, 0x3602},
    {0x0001, 0x79ED, 0x26AF, 0x49FD}, {0x0001, 0x462C, 0x0116, 0x3602}, {0x0001, 0x39D3, 0x0116, 0x49FD}, {0x0001, 0x0612, 0x26AF, 0x3602},
    {0x0001, 0x0242, 0x326E, 0x49FD}, {0x0001, 0x1606, 0x6F44, 0x3602}, {0x0001, 0x2003, 0x7686, 0x49FD}, {0x0001, 0x5FFC, 0x7686, 0x3602},
    {0x0001, 0x69F9, 0x6F44, 0x49FD}, {0x0001, 0x7DBD, 0x4D91, 0x3602}, {0x0001, 0x79ED, 0x5950, 0x49FD}, {0x0001, 0x5FFC, 0x0979, 0x3602},
    {0x0001, 0x69F9, 0x10BB, 0x49FD}, {0x0001, 0x1606, 0x10BB, 0x3602}, {0x0001, 0x2003, 0x0979, 0x49FD}, {0x0001, 0x0612, 0x5950, 0x3602},
    {0x0001, 0x0242, 0x4D91, 0x49FD}, {0x0001, 0x462C, 0x7EE9, 0x3602}, {0x0001, 0x39D3, 0x7EE9, 0x49FD}, {0x0001, 0x5BB4, 0x10BB, 0x6113},
    {0x0001, 0x455E, 0x0979, 0x6113}, {0x0001, 0x1B9B, 0x170B, 0x6113}, {0x0001, 0x0DCD, 0x2A0B, 0x6113}, {0x0001, 0x0DCD, 0x55F4, 0x6113},
    {0x0001, 0x1B9B, 0x68F4, 0x6113}, {0x0001, 0x455E, 0x7686, 0x6113}, {0x0001, 0x5BB4, 0x6F44, 0x6113}, {0x0001, 0x7584, 0x4BBE, 0x6113},
    {0x0001, 0x7584, 0x3441, 0x6113}, {0x0001, 0x52AD, 0x326E, 0x7BB0}, {0x0001, 0x62D7, 0x26AF, 0x6F58}, {0x0001, 0x38DD, 0x2A0B, 0x7BB0},
    {0x0001, 0x32B1, 0x170B, 0x6F58}, {0x0001, 0x28E9, 0x4000, 0x7BB0}, {0x0001, 0x14EF, 0x4000, 0x6F58}, {0x0001, 0x38DD, 0x55F4, 0x7BB0},
    {0x0001, 0x32B1, 0x68F4, 0x6F58}, {0x0001, 0x52AD, 0x4D91, 0x7BB0}, {0x0001, 0x62D7, 0x5950, 0x6F58}, {0x0001, 0x5EB0, 0x29B4, 0x0C73},
    {0x0001, 0x3447, 0x1BEC, 0x0C73}, {0x0001, 0x1A11, 0x4000, 0x0C73}, {0x0001, 0x3447, 0x6413, 0x0C73}, {0x0001, 0x5EB0, 0x564B, 0x0C73},
    {0x0001, 0x7F11, 0x4000, 0x4AE0}, {0x0001, 0x537D, 0x0404, 0x4AE0}, {0x0001, 0x0CF9, 0x1AED, 0x4AE0}, {0x0001, 0x0CF9, 0x6512, 0x4AE0},
    {0x0001, 0x537D, 0x7BFB, 0x4AE0}, {0x0001, 0x7306, 0x1AED, 0x351F}, {0x0001, 0x2C82, 0x0404, 0x351F}, {0x0001, 0x00EE, 0x4000, 0x351F},
    {0x0001, 0x2C82, 0x7BFB, 0x351F}, {0x0001, 0x7306, 0x6512, 0x351F}, {0x0001, 0x4BB8, 0x1BEC, 0x738C}, {0x0001, 0x214F, 0x29B4, 0x738C},
    {0x0001, 0x214F, 0x564B, 0x738C}, {0x0001, 0x4BB8, 0x6413, 0x738C}, {0x0001, 0x65EE, 0x4000, 0x738C}, {0x0002, 0x4000, 0x4000, 0x186A},
    {0x0002, 0x6367, 0x4000, 0x2E4C}, {0x0002, 0x4AF0, 0x1E53, 0x2E4C}, {0x0002, 0x235B, 0x2B30, 0x2E4C}, {0x0002, 0x235B, 0x54CF, 0x2E4C},
    {0x0002, 0x4AF0, 0x61AC, 0x2E4C}, {0x0002, 0x5CA4, 0x2B30, 0x51B3}, {0x0002, 0x350F, 0x1E53, 0x51B3}, {0x0002, 0x1C98, 0x4000, 0x51B3},
    {0x0002, 0x350F, 0x61AC, 0x51B3}, {0x0002, 0x5CA4, 0x54CF, 0x51B3}, {0x0002, 0x4000, 0x4000, 0x6795},
};
static ChPackedVtx lbl_1_data_D838[743] = {
    {0x82E6, 0x8000, 0x8000, 0x8000}, {0x0000, 0x3FB7, 0x3F6D, 0x26E7}, {0x0000, 0x563B, 0x3F6D, 0x34D2}, {0x0000, 0x46AC, 0x2A04, 0x34D2},
    {0x0000, 0x2D80, 0x3231, 0x34D2}, {0x0000, 0x2D80, 0x4CA9, 0x34D2}, {0x0000, 0x46AC, 0x54D7, 0x34D2}, {0x0000, 0x51EE, 0x3231, 0x4B55},
    {0x0000, 0x38C2, 0x2A04, 0x4B55}, {0x0000, 0x2933, 0x3F6D, 0x4B55}, {0x0000, 0x38C2, 0x54D7, 0x4B55}, {0x0000, 0x51EE, 0x4CA9, 0x4B55},
    {0x0000, 0x3FB7, 0x3F6D, 0x5940}, {0x0001, 0x3FB7, 0x3F6D, 0x26E7}, {0x0001, 0x563B, 0x3F6D, 0x34D2}, {0x0001, 0x46AC, 0x2A04, 0x34D2},
    {0x0001, 0x2D80, 0x3231, 0x34D2}, {0x0001, 0x2D80, 0x4CA9, 0x34D2}, {0x0001, 0x46AC, 0x54D7, 0x34D2}, {0x0001, 0x51EE, 0x3231, 0x4B55},
    {0x0001, 0x38C2, 0x2A04, 0x4B55}, {0x0001, 0x2933, 0x3F6D, 0x4B55}, {0x0001, 0x38C2, 0x54D7, 0x4B55}, {0x0001, 0x51EE, 0x4CA9, 0x4B55},
    {0x0001, 0x3FB7, 0x3F6D, 0x5940}, {0x0001, 0x48CC, 0x3F6D, 0x2899}, {0x0001, 0x50A7, 0x3F6D, 0x2D74}, {0x0001, 0x4285, 0x36CA, 0x2899},
    {0x0001, 0x44F3, 0x2F51, 0x2D74}, {0x0001, 0x385E, 0x3A17, 0x2899}, {0x0001, 0x3203, 0x3579, 0x2D74}, {0x0001, 0x385E, 0x44C4, 0x2899},
    {0x0001, 0x3203, 0x4962, 0x2D74}, {0x0001, 0x4285, 0x4810, 0x2899}, {0x0001, 0x44F3, 0x4F89, 0x2D74}, {0x0001, 0x5376, 0x36CA, 0x3311},
    {0x0001, 0x4E08, 0x2F51, 0x3311}, {0x0001, 0x3D9A, 0x29FB, 0x3311}, {0x0001, 0x34D1, 0x2CD6, 0x3311}, {0x0001, 0x2AAA, 0x3ACF, 0x3311},
    {0x0001, 0x2AAA, 0x440C, 0x3311}, {0x0001, 0x34D1, 0x5205, 0x3311}, {0x0001, 0x3D9A, 0x54E0, 0x3311}, {0x0001, 0x4E08, 0x4F89, 0x3311},
    {0x0001, 0x5376, 0x4810, 0x3311}, {0x0001, 0x5800, 0x3A17, 0x3C26}, {0x0001, 0x5680, 0x3579, 0x4401}, {0x0001, 0x4225, 0x26AE, 0x3C26},
    {0x0001, 0x3D49, 0x26AE, 0x4401}, {0x0001, 0x28EE, 0x3579, 0x3C26}, {0x0001, 0x276E, 0x3A17, 0x4401}, {0x0001, 0x2F35, 0x5205, 0x3C26},
    {0x0001, 0x3322, 0x54E0, 0x4401}, {0x0001, 0x4C4C, 0x54E0, 0x3C26}, {0x0001, 0x5039, 0x5205, 0x4401}, {0x0001, 0x5800, 0x44C4, 0x3C26},
    {0x0001, 0x5680, 0x4962, 0x4401}, {0x0001, 0x4C4C, 0x29FB, 0x3C26}, {0x0001, 0x5039, 0x2CD6, 0x4401}, {0x0001, 0x2F35, 0x2CD6, 0x3C26},
    {0x0001, 0x3322, 0x29FB, 0x4401}, {0x0001, 0x28EE, 0x4962, 0x3C26}, {0x0001, 0x276E, 0x44C4, 0x4401}, {0x0001, 0x4225, 0x582C, 0x3C26},
    {0x0001, 0x3D49, 0x582C, 0x4401}, {0x0001, 0x4A9D, 0x2CD6, 0x4D16}, {0x0001, 0x41D4, 0x29FB, 0x4D16}, {0x0001, 0x3166, 0x2F51, 0x4D16},
    {0x0001, 0x2BF8, 0x36CA, 0x4D16}, {0x0001, 0x2BF8, 0x4810, 0x4D16}, {0x0001, 0x3166, 0x4F89, 0x4D16}, {0x0001, 0x41D4, 0x54E0, 0x4D16},
    {0x0001, 0x4A9D, 0x5205, 0x4D16}, {0x0001, 0x54C4, 0x440C, 0x4D16}, {0x0001, 0x54C4, 0x3ACF, 0x4D16}, {0x0001, 0x4710, 0x3A17, 0x578E},
    {0x0001, 0x4D6B, 0x3579, 0x52B3}, {0x0001, 0x3CE9, 0x36CA, 0x578E}, {0x0001, 0x3A7B, 0x2F51, 0x52B3}, {0x0001, 0x36A2, 0x3F6D, 0x578E},
    {0x0001, 0x2EC7, 0x3F6D, 0x52B3}, {0x0001, 0x3CE9, 0x4810, 0x578E}, {0x0001, 0x3A7B, 0x4F89, 0x52B3}, {0x0001, 0x4710, 0x44C4, 0x578E},
    {0x0001, 0x4D6B, 0x4962, 0x52B3}, {0x0001, 0x4BC9, 0x36A8, 0x2BCD}, {0x0001, 0x3B1B, 0x313D, 0x2BCD}, {0x0001, 0x30CB, 0x3F6D, 0x2BCD},
    {0x0001, 0x3B1B, 0x4D9E, 0x2BCD}, {0x0001, 0x4BC9, 0x4832, 0x2BCD}, {0x0001, 0x5885, 0x3F6D, 0x445B}, {0x0001, 0x4761, 0x27D6, 0x445B},
    {0x0001, 0x2BA5, 0x30D9, 0x445B}, {0x0001, 0x2BA5, 0x4E02, 0x445B}, {0x0001, 0x4761, 0x5705, 0x445B}, {0x0001, 0x53C9, 0x30D9, 0x3BCC},
    {0x0001, 0x380D, 0x27D6, 0x3BCC}, {0x0001, 0x26E9, 0x3F6D, 0x3BCC}, {0x0001, 0x380D, 0x5705, 0x3BCC}, {0x0001, 0x53C9, 0x4E02, 0x3BCC},
    {0x0001, 0x4453, 0x313D, 0x545A}, {0x0001, 0x33A5, 0x36A8, 0x545A}, {0x0001, 0x33A5, 0x4832, 0x545A}, {0x0001, 0x4453, 0x4D9E, 0x545A},
    {0x0001, 0x4EA2, 0x3F6D, 0x545A}, {0x0002, 0x4011, 0x3F26, 0x1D8A}, {0x0002, 0x5EF5, 0x3F26, 0x30A1}, {0x0002, 0x499D, 0x21C5, 0x30A1},
    {0x0002, 0x2713, 0x2CFE, 0x30A1}, {0x0002, 0x2713, 0x514E, 0x30A1}, {0x0002, 0x499D, 0x5C87, 0x30A1}, {0x0002, 0x590F, 0x2CFE, 0x4F86},
    {0x0002, 0x3685, 0x21C5, 0x4F86}, {0x0002, 0x212D, 0x3F26, 0x4F86}, {0x0002, 0x3685, 0x5C87, 0x4F86}, {0x0002, 0x590F, 0x514E, 0x4F86},
    {0x0002, 0x4011, 0x3F26, 0x629D}, {0x0002, 0x5239, 0x3F26, 0x22B2}, {0x0002, 0x45AD, 0x2DE1, 0x22B2}, {0x0002, 0x3160, 0x347A, 0x22B2},
    {0x0002, 0x3160, 0x49D2, 0x22B2}, {0x0002, 0x45AD, 0x506B, 0x22B2}, {0x0002, 0x57D6, 0x2DE1, 0x2DEB}, {0x0002, 0x36FD, 0x2335, 0x2DEB},
    {0x0002, 0x22B0, 0x3F26, 0x2DEB}, {0x0002, 0x36FD, 0x5B17, 0x2DEB}, {0x0002, 0x57D6, 0x506B, 0x2DEB}, {0x0002, 0x60EA, 0x347A, 0x4013},
    {0x0002, 0x4011, 0x1C9C, 0x4013}, {0x0002, 0x1F38, 0x347A, 0x4013}, {0x0002, 0x2BC4, 0x5B17, 0x4013}, {0x0002, 0x545E, 0x5B17, 0x4013},
    {0x0002, 0x60EA, 0x49D2, 0x4013}, {0x0002, 0x545E, 0x2335, 0x4013}, {0x0002, 0x2BC4, 0x2335, 0x4013}, {0x0002, 0x1F38, 0x49D2, 0x4013},
    {0x0002, 0x4011, 0x61B0, 0x4013}, {0x0002, 0x4925, 0x2335, 0x523C}, {0x0002, 0x284C, 0x2DE1, 0x523C}, {0x0002, 0x284C, 0x506B, 0x523C},
    {0x0002, 0x4925, 0x5B17, 0x523C}, {0x0002, 0x5D72, 0x3F26, 0x523C}, {0x0002, 0x4EC2, 0x347A, 0x5D75}, {0x0002, 0x3A75, 0x2DE1, 0x5D75},
    {0x0002, 0x2DE9, 0x3F26, 0x5D75}, {0x0002, 0x3A75, 0x506B, 0x5D75}, {0x0002, 0x4EC2, 0x49D2, 0x5D75}, {0x0003, 0x4585, 0x4E5B, 0x1483},
    {0x0003, 0x6B7E, 0x453E, 0x31C9}, {0x0003, 0x4FDB, 0x2075, 0x2180}, {0x0003, 0x2180, 0x2FB3, 0x208B}, {0x0003, 0x207D, 0x5DE6, 0x303D},
    {0x0003, 0x4E38, 0x6B37, 0x3AE5}, {0x0003, 0x5EF1, 0x20F4, 0x4FE9}, {0x0003, 0x3136, 0x13A4, 0x4542}, {0x0003, 0x13F0, 0x399D, 0x4E5E},
    {0x0003, 0x2F93, 0x5E65, 0x5EA7}, {0x0003, 0x5DEE, 0x4F28, 0x5F9B}, {0x0003, 0x39E9, 0x3080, 0x6BA4}, {0x0003, 0x55BD, 0x4D00, 0x198A},
    {0x0003, 0x62FD, 0x49D2, 0x23C1}, {0x0003, 0x4A97, 0x3E2B, 0x12F8}, {0x0003, 0x4E33, 0x2E26, 0x1781}, {0x0003, 0x37E6, 0x4450, 0x1296},
    {0x0003, 0x2B53, 0x399D, 0x16C9}, {0x0003, 0x377D, 0x56F2, 0x18EA}, {0x0003, 0x2A90, 0x5C5F, 0x2298}, {0x0003, 0x49EE, 0x5C51, 0x1D36},
    {0x0003, 0x4CF7, 0x6663, 0x2A9C}, {0x0003, 0x6729, 0x3750, 0x28FE}, {0x0003, 0x5D83, 0x2A79, 0x234F}, {0x0003, 0x3FAC, 0x21C9, 0x1C5B},
    {0x0003, 0x2F7F, 0x271B, 0x1C06}, {0x0003, 0x1C64, 0x3FE2, 0x21F8}, {0x0003, 0x1C0A, 0x5002, 0x2772}, {0x0003, 0x2E12, 0x6803, 0x3213},
    {0x0003, 0x3E08, 0x6CA8, 0x35CB}, {0x0003, 0x5C48, 0x62B7, 0x366A}, {0x0003, 0x667F, 0x5576, 0x333C}, {0x0003, 0x6D3E, 0x3783, 0x3BB6},
    {0x0003, 0x68DD, 0x2AD9, 0x463A}, {0x0003, 0x4602, 0x1678, 0x2B2A}, {0x0003, 0x3B50, 0x11FF, 0x37A4}, {0x0003, 0x1754, 0x3140, 0x2E1E},
    {0x0003, 0x1299, 0x34B6, 0x3E1C}, {0x0003, 0x21B7, 0x62D7, 0x407F}, {0x0003, 0x26FA, 0x6304, 0x50B1}, {0x0003, 0x56D0, 0x66B6, 0x48E5},
    {0x0003, 0x5C4B, 0x5CEB, 0x55B5}, {0x0003, 0x6CD5, 0x4A25, 0x420B}, {0x0003, 0x681A, 0x4D9B, 0x5209}, {0x0003, 0x5874, 0x1BD7, 0x2F76},
    {0x0003, 0x5DB7, 0x1C03, 0x3FA8}, {0x0003, 0x2323, 0x21EF, 0x2A72}, {0x0003, 0x289E, 0x1824, 0x3742}, {0x0003, 0x1691, 0x5402, 0x39ED},
    {0x0003, 0x1230, 0x4758, 0x4471}, {0x0003, 0x441E, 0x6CDC, 0x4883}, {0x0003, 0x396C, 0x6862, 0x54FD}, {0x0003, 0x515C, 0x16D8, 0x4E14},
    {0x0003, 0x4166, 0x1232, 0x4A5C}, {0x0003, 0x2326, 0x1C24, 0x49BD}, {0x0003, 0x18EF, 0x2965, 0x4CEB}, {0x0003, 0x1845, 0x478B, 0x5729},
    {0x0003, 0x21EB, 0x5461, 0x5CD8}, {0x0003, 0x3FC2, 0x5D11, 0x63CC}, {0x0003, 0x4FEF, 0x57C0, 0x6421}, {0x0003, 0x630A, 0x3EF8, 0x5E2F},
    {0x0003, 0x6364, 0x2ED8, 0x58B5}, {0x0003, 0x47F1, 0x27E8, 0x673D}, {0x0003, 0x54DE, 0x227B, 0x5D8F}, {0x0003, 0x3580, 0x228A, 0x62F1},
    {0x0003, 0x3277, 0x1877, 0x558B}, {0x0003, 0x29B1, 0x31DA, 0x669D}, {0x0003, 0x1C71, 0x3508, 0x5C66}, {0x0003, 0x34D7, 0x40B0, 0x6D2F},
    {0x0003, 0x313B, 0x50B4, 0x68A6}, {0x0003, 0x4788, 0x3A8A, 0x6D91}, {0x0003, 0x541B, 0x453D, 0x695E}, {0x0003, 0x5ACE, 0x3BAE, 0x1A92},
    {0x0003, 0x3C80, 0x32DB, 0x1383}, {0x0003, 0x291A, 0x4C05, 0x198C}, {0x0003, 0x3B6A, 0x6465, 0x2457}, {0x0003, 0x5A22, 0x5A4C, 0x24F9},
    {0x0003, 0x6C1A, 0x3BF1, 0x4D33}, {0x0003, 0x4DA7, 0x136A, 0x3B42}, {0x0003, 0x1A94, 0x2435, 0x3A34}, {0x0003, 0x1977, 0x571C, 0x4B7F},
    {0x0003, 0x4BD9, 0x65C7, 0x573D}, {0x0003, 0x65F7, 0x27BF, 0x34A8}, {0x0003, 0x3395, 0x1913, 0x28EA}, {0x0003, 0x1354, 0x42EA, 0x32F4},
    {0x0003, 0x31C7, 0x6B70, 0x44E5}, {0x0003, 0x64DA, 0x5AA6, 0x45F2}, {0x0003, 0x4404, 0x1A76, 0x5BD0}, {0x0003, 0x254C, 0x248F, 0x5B2E},
    {0x0003, 0x24A0, 0x432C, 0x6595}, {0x0003, 0x42EE, 0x4BFF, 0x6CA4}, {0x0003, 0x5654, 0x32D5, 0x669B}, {0x0004, 0x4962, 0x52A9, 0x0C16},
    {0x0004, 0x7557, 0x46A3, 0x31BD}, {0x0004, 0x54A5, 0x1AB5, 0x1B7A}, {0x0004, 0x1CC6, 0x2DA4, 0x17AA}, {0x0004, 0x1AF1, 0x6545, 0x2B92},
    {0x0004, 0x51AD, 0x74B8, 0x3BAF}, {0x0004, 0x63E5, 0x1A2F, 0x5495}, {0x0004, 0x2D29, 0x0ABD, 0x4478}, {0x0004, 0x0980, 0x38D2, 0x4E6A},
    {0x0004, 0x2A32, 0x64C0, 0x64AD}, {0x0004, 0x6210, 0x51D1, 0x687D}, {0x0004, 0x3574, 0x2CCC, 0x7411}, {0x0004, 0x5549, 0x51D1, 0x0F8B},
    {0x0004, 0x601F, 0x5016, 0x155F}, {0x0004, 0x695B, 0x4D8F, 0x1D49}, {0x0004, 0x708C, 0x4A5B, 0x26E6}, {0x0004, 0x4D42, 0x4707, 0x0A14},
    {0x0004, 0x5075, 0x3B0A, 0x0AB5}, {0x0004, 0x52D2, 0x2F48, 0x0DF1}, {0x0004, 0x543E, 0x2453, 0x139F}, {0x0004, 0x3F8A, 0x4BAE, 0x0924},
    {0x0004, 0x35B0, 0x441D, 0x08E1}, {0x0004, 0x2C50, 0x3C55, 0x0B50}, {0x0004, 0x23DF, 0x34B8, 0x1052}, {0x0004, 0x3F17, 0x5956, 0x0E08},
    {0x0004, 0x34CF, 0x5EC4, 0x126B}, {0x0004, 0x2B0D, 0x62AD, 0x1908}, {0x0004, 0x2249, 0x64E1, 0x218E}, {0x0004, 0x4C87, 0x5D21, 0x11FD},
    {0x0004, 0x4F09, 0x662A, 0x1A23}, {0x0004, 0x50C7, 0x6D53, 0x2424}, {0x0004, 0x51AC, 0x7241, 0x2F82}, {0x0004, 0x7350, 0x3C9E, 0x2AAD},
    {0x0004, 0x6EC1, 0x32C1, 0x24A8}, {0x0004, 0x67E1, 0x2985, 0x1FFB}, {0x0004, 0x5F09, 0x215F, 0x1CDE}, {0x0004, 0x4949, 0x1B3C, 0x1677},
    {0x0004, 0x3D73, 0x1D8C, 0x137C}, {0x0004, 0x31B5, 0x2186, 0x12AF}, {0x0004, 0x26A3, 0x26FB, 0x141A}, {0x0004, 0x1878, 0x394A, 0x180D},
    {0x0004, 0x1610, 0x4540, 0x1A65}, {0x0004, 0x15AE, 0x50F1, 0x1E94}, {0x0004, 0x1755, 0x5BCA, 0x2466}, {0x0004, 0x2452, 0x6D3E, 0x2D3E},
    {0x0004, 0x2F06, 0x72FE, 0x2FD6}, {0x0004, 0x3A87, 0x763D, 0x3339}, {0x0004, 0x4645, 0x76D3, 0x373D}, {0x0004, 0x5C77, 0x6F4D, 0x38C1},
    {0x0004, 0x65D6, 0x6790, 0x362E}, {0x0004, 0x6D55, 0x5DE1, 0x3417}, {0x0004, 0x7295, 0x52B8, 0x3296}, {0x0004, 0x770F, 0x3C7D, 0x38B3},
    {0x0004, 0x760F, 0x3281, 0x4005}, {0x0004, 0x7265, 0x2929, 0x4757}, {0x0004, 0x6C3D, 0x20EC, 0x4E4F}, {0x0004, 0x4D4F, 0x12AA, 0x2177},
    {0x0004, 0x454D, 0x0CD3, 0x28F4}, {0x0004, 0x3D01, 0x0978, 0x3191}, {0x0004, 0x34D3, 0x08C3, 0x3AE4}, {0x0004, 0x142F, 0x2E60, 0x209C},
    {0x0004, 0x0DB5, 0x2FF4, 0x2B17}, {0x0004, 0x09A8, 0x324D, 0x3699}, {0x0004, 0x083B, 0x354F, 0x4291}, {0x0004, 0x1AA0, 0x6953, 0x374F},
    {0x0004, 0x1C1B, 0x6B58, 0x437A}, {0x0004, 0x1F50, 0x6B3B, 0x4F7B}, {0x0004, 0x2416, 0x6900, 0x5ABB}, {0x0004, 0x57BC, 0x720C, 0x4633},
    {0x0004, 0x5C9A, 0x6CEB, 0x5069}, {0x0004, 0x600C, 0x6595, 0x59D4}, {0x0004, 0x61E5, 0x5C66, 0x61FD}, {0x0004, 0x769B, 0x4A26, 0x3D96},
    {0x0004, 0x752E, 0x4D28, 0x498E}, {0x0004, 0x7121, 0x4F81, 0x5510}, {0x0004, 0x6AA7, 0x5115, 0x5F8B}, {0x0004, 0x5AC0, 0x1675, 0x256C},
    {0x0004, 0x5F86, 0x1439, 0x30AC}, {0x0004, 0x62BB, 0x141D, 0x3CAD}, {0x0004, 0x6436, 0x1622, 0x48D8}, {0x0004, 0x1CF1, 0x230F, 0x1E2A},
    {0x0004, 0x1ECB, 0x19E0, 0x2653}, {0x0004, 0x223C, 0x128A, 0x2FBE}, {0x0004, 0x271B, 0x0D69, 0x39F4}, {0x0004, 0x1299, 0x5E89, 0x31D8},
    {0x0004, 0x0C71, 0x564C, 0x38CF}, {0x0004, 0x08C7, 0x4CF4, 0x4022}, {0x0004, 0x07C8, 0x42F7, 0x4774}, {0x0004, 0x4A04, 0x76B2, 0x4543},
    {0x0004, 0x41D6, 0x75FD, 0x4E96}, {0x0004, 0x3989, 0x72A2, 0x5733}, {0x0004, 0x3187, 0x6CCB, 0x5EB0}, {0x0004, 0x5A84, 0x1237, 0x52E9},
    {0x0004, 0x4FD0, 0x0C77, 0x5051}, {0x0004, 0x444F, 0x0937, 0x4CEE}, {0x0004, 0x3891, 0x08A2, 0x48EA}, {0x0004, 0x225F, 0x1028, 0x4766},
    {0x0004, 0x1900, 0x17E5, 0x49F9}, {0x0004, 0x1181, 0x2194, 0x4C10}, {0x0004, 0x0C41, 0x2CBD, 0x4D91}, {0x0004, 0x0B86, 0x42D7, 0x557A},
    {0x0004, 0x1016, 0x4CB4, 0x5B7F}, {0x0004, 0x16F5, 0x55F0, 0x602C}, {0x0004, 0x1FCE, 0x5E15, 0x6349}, {0x0004, 0x358D, 0x6439, 0x69B0},
    {0x0004, 0x4163, 0x61E9, 0x6CAB}, {0x0004, 0x4D21, 0x5DEE, 0x6D78}, {0x0004, 0x5833, 0x587A, 0x6C0D}, {0x0004, 0x665F, 0x462B, 0x681A},
    {0x0004, 0x68C6, 0x3A35, 0x65C2}, {0x0004, 0x6929, 0x2E84, 0x6193}, {0x0004, 0x6782, 0x23AA, 0x5BC1}, {0x0004, 0x3FC0, 0x261E, 0x721F},
    {0x0004, 0x4A07, 0x20B1, 0x6DBC}, {0x0004, 0x53C9, 0x1CC8, 0x671F}, {0x0004, 0x5C8D, 0x1A93, 0x5E99}, {0x0004, 0x324F, 0x2253, 0x6E2A},
    {0x0004, 0x2FCE, 0x194B, 0x6604}, {0x0004, 0x2E0F, 0x1222, 0x5C03}, {0x0004, 0x2D2A, 0x0D34, 0x50A5}, {0x0004, 0x298D, 0x2DA4, 0x709C},
    {0x0004, 0x1EB8, 0x2F5F, 0x6AC8}, {0x0004, 0x157B, 0x31E6, 0x62DE}, {0x0004, 0x0E4A, 0x3519, 0x5941}, {0x0004, 0x3195, 0x386D, 0x7613},
    {0x0004, 0x2E62, 0x446A, 0x7572}, {0x0004, 0x2C04, 0x502D, 0x7236}, {0x0004, 0x2A99, 0x5B21, 0x6C88}, {0x0004, 0x3F4C, 0x33C7, 0x7703},
    {0x0004, 0x4926, 0x3B58, 0x7746}, {0x0004, 0x5286, 0x4320, 0x74D7}, {0x0004, 0x5AF7, 0x4ABD, 0x6FD5}, {0x0004, 0x591E, 0x45C2, 0x0E70},
    {0x0004, 0x63E9, 0x437D, 0x1579}, {0x0004, 0x5C3E, 0x392F, 0x1041}, {0x0004, 0x6CE3, 0x405A, 0x1F04}, {0x0004, 0x66B3, 0x364F, 0x18F9},
    {0x0004, 0x5E54, 0x2CCB, 0x151B}, {0x0004, 0x4332, 0x3F92, 0x07FC}, {0x0004, 0x4621, 0x32F2, 0x09BE}, {0x0004, 0x3907, 0x3762, 0x08D9},
    {0x0004, 0x482F, 0x268B, 0x0E96}, {0x0004, 0x3BA4, 0x2A28, 0x0C4C}, {0x0004, 0x2F4F, 0x2EF9, 0x0CE3}, {0x0004, 0x34E9, 0x5207, 0x0BF8},
    {0x0004, 0x2A9E, 0x4A01, 0x0CDE}, {0x0004, 0x2A30, 0x570C, 0x1189}, {0x0004, 0x20E2, 0x419E, 0x10E9}, {0x0004, 0x1F97, 0x4E68, 0x141F},
    {0x0004, 0x2011, 0x5A63, 0x19C6}, {0x0004, 0x4201, 0x639F, 0x14E2}, {0x0004, 0x3766, 0x68CC, 0x1A87}, {0x0004, 0x443C, 0x6C6B, 0x1E4F},
    {0x0004, 0x2D4B, 0x6C28, 0x22C8}, {0x0004, 0x394F, 0x70F7, 0x25A2}, {0x0004, 0x45AA, 0x7309, 0x29F5}, {0x0004, 0x5862, 0x5C0A, 0x1669},
    {0x0004, 0x5ACE, 0x64C5, 0x1FD9}, {0x0004, 0x632B, 0x59F6, 0x1D84}, {0x0004, 0x5C44, 0x6B60, 0x2B80}, {0x0004, 0x6542, 0x6212, 0x28A2},
    {0x0004, 0x6C25, 0x56DB, 0x2712}, {0x0004, 0x776D, 0x3FD5, 0x44F2}, {0x0004, 0x74CE, 0x42A3, 0x5173}, {0x0004, 0x753C, 0x3597, 0x4CC8},
    {0x0004, 0x6F15, 0x44C5, 0x5D75}, {0x0004, 0x70DD, 0x382D, 0x59BD}, {0x0004, 0x6FE6, 0x2C00, 0x5498}, {0x0004, 0x530B, 0x0EF3, 0x2C2C},
    {0x0004, 0x5759, 0x0D6F, 0x386E}, {0x0004, 0x4A83, 0x09D0, 0x34A7}, {0x0004, 0x59E8, 0x0E73, 0x459F}, {0x0004, 0x4E21, 0x0981, 0x4216},
    {0x0004, 0x4189, 0x0793, 0x3E72}, {0x0004, 0x14E1, 0x2405, 0x27EE}, {0x0004, 0x1771, 0x1B1F, 0x312B}, {0x0004, 0x0F14, 0x25ED, 0x3380},
    {0x0004, 0x1BF4, 0x144F, 0x3BE1}, {0x0004, 0x12C6, 0x1D9F, 0x3E09}, {0x0004, 0x0C13, 0x28D4, 0x404F}, {0x0004, 0x12D6, 0x61EC, 0x3E14},
    {0x0004, 0x0D67, 0x58C7, 0x45B2}, {0x0004, 0x1512, 0x6315, 0x4AEB}, {0x0004, 0x0AD8, 0x4E3F, 0x4DB3}, {0x0004, 0x10D4, 0x58B9, 0x532F},
    {0x0004, 0x1966, 0x61CF, 0x579C}, {0x0004, 0x4FBF, 0x731C, 0x5003}, {0x0004, 0x471B, 0x7133, 0x59A6}, {0x0004, 0x5435, 0x6CC3, 0x5A8B},
    {0x0004, 0x3E38, 0x6C33, 0x6274}, {0x0004, 0x4AFA, 0x6922, 0x644F}, {0x0004, 0x5718, 0x63C4, 0x6426}, {0x0004, 0x6C00, 0x1D89, 0x4213},
    {0x0004, 0x69C4, 0x1C60, 0x353C}, {0x0004, 0x716F, 0x26AD, 0x3A75}, {0x0004, 0x6570, 0x1DA6, 0x288B}, {0x0004, 0x6E03, 0x26BC, 0x2CF7},
    {0x0004, 0x73FF, 0x3136, 0x3274}, {0x0004, 0x2F18, 0x0C59, 0x3024}, {0x0004, 0x2AA1, 0x12B2, 0x259C}, {0x0004, 0x37BB, 0x0E41, 0x2681},
    {0x0004, 0x27BE, 0x1BB1, 0x1C01}, {0x0004, 0x33DC, 0x1653, 0x1BD8}, {0x0004, 0x409E, 0x1342, 0x1DB3}, {0x0004, 0x0769, 0x3FA0, 0x3B35},
    {0x0004, 0x099A, 0x49DE, 0x335F}, {0x0004, 0x0A08, 0x3CD2, 0x2EB4}, {0x0004, 0x0EF0, 0x5375, 0x2B8F}, {0x0004, 0x0DF9, 0x4748, 0x266A},
    {0x0004, 0x0FC1, 0x3AB0, 0x22B2}, {0x0004, 0x2BCB, 0x7081, 0x53FB}, {0x0004, 0x3453, 0x75A5, 0x4B80}, {0x0004, 0x277D, 0x7206, 0x47B8},
    {0x0004, 0x3D4D, 0x77E2, 0x41B5}, {0x0004, 0x30B5, 0x75F4, 0x3E10}, {0x0004, 0x24EE, 0x7102, 0x3A88}, {0x0004, 0x69F6, 0x5B70, 0x5839},
    {0x0004, 0x6FC2, 0x5988, 0x4CA7}, {0x0004, 0x6765, 0x6456, 0x4EFC}, {0x0004, 0x72C3, 0x56A1, 0x3FD8}, {0x0004, 0x6C10, 0x61D6, 0x421D},
    {0x0004, 0x62E2, 0x6B26, 0x4446}, {0x0004, 0x3CD5, 0x1BD6, 0x6B45}, {0x0004, 0x3A9A, 0x130A, 0x61D8}, {0x0004, 0x4770, 0x16A9, 0x65A0},
    {0x0004, 0x392C, 0x0C6C, 0x5632}, {0x0004, 0x4587, 0x0E7E, 0x5A85}, {0x0004, 0x518B, 0x134D, 0x5D5F}, {0x0004, 0x2675, 0x236B, 0x69BE},
    {0x0004, 0x1BAB, 0x257F, 0x62A3}, {0x0004, 0x2408, 0x1AB0, 0x604E}, {0x0004, 0x12B1, 0x289A, 0x5915}, {0x0004, 0x1995, 0x1D63, 0x5785},
    {0x0004, 0x2292, 0x1415, 0x54A7}, {0x0004, 0x25B9, 0x39B3, 0x71B7}, {0x0004, 0x2298, 0x4645, 0x6FE6}, {0x0004, 0x1AEE, 0x3BF8, 0x6AAE},
    {0x0004, 0x2082, 0x52AA, 0x6B0C}, {0x0004, 0x1823, 0x4926, 0x672E}, {0x0004, 0x11F3, 0x3F1B, 0x6123}, {0x0004, 0x3BA5, 0x3FE3, 0x782B},
    {0x0004, 0x45D0, 0x4812, 0x774E}, {0x0004, 0x38B6, 0x4C83, 0x7669}, {0x0004, 0x4F87, 0x507C, 0x7344}, {0x0004, 0x4332, 0x554C, 0x73DB},
    {0x0004, 0x36A7, 0x58EA, 0x7191}, {0x0004, 0x49ED, 0x2D6E, 0x742F}, {0x0004, 0x54A6, 0x2869, 0x6E9E}, {0x0004, 0x5438, 0x3574, 0x7349},
    {0x0004, 0x5EC5, 0x2512, 0x6661}, {0x0004, 0x5F3F, 0x310C, 0x6C08}, {0x0004, 0x5DF4, 0x3DD7, 0x6F3E}, {0x0005, 0x3FFD, 0x3F87, 0x0027},
    {0x0005, 0x7929, 0x3F87, 0x237D}, {0x0005, 0x51A8, 0x0927, 0x237D}, {0x0005, 0x11BC, 0x1DEC, 0x237D}, {0x0005, 0x11BC, 0x6122, 0x237D},
    {0x0005, 0x51A8, 0x75E7, 0x237D}, {0x0005, 0x6E3E, 0x1DEC, 0x5CAA}, {0x0005, 0x2E52, 0x0927, 0x5CAA}, {0x0005, 0x06D0, 0x3F87, 0x5CAA},
    {0x0005, 0x2E52, 0x75E7, 0x5CAA}, {0x0005, 0x6E3E, 0x6122, 0x5CAA}, {0x0005, 0x3FFD, 0x3F87, 0x8000}, {0x0005, 0x4E07, 0x3F87, 0x01B7},
    {0x0005, 0x5B61, 0x3F87, 0x0652}, {0x0005, 0x6765, 0x3F87, 0x0DBF}, {0x0005, 0x717D, 0x3F87, 0x17A1}, {0x0005, 0x4453, 0x322D, 0x01B7},
    {0x0005, 0x4874, 0x257A, 0x0652}, {0x0005, 0x4C2A, 0x1A0D, 0x0DBF}, {0x0005, 0x4F49, 0x1074, 0x17A1}, {0x0005, 0x34A1, 0x3747, 0x01B7},
    {0x0005, 0x29D4, 0x2F6E, 0x0652}, {0x0005, 0x201B, 0x285E, 0x0DBF}, {0x0005, 0x17F1, 0x226F, 0x17A1}, {0x0005, 0x34A1, 0x47C8, 0x01B7},
    {0x0005, 0x29D4, 0x4FA1, 0x0652}, {0x0005, 0x201B, 0x56B1, 0x0DBF}, {0x0005, 0x17F1, 0x5CA0, 0x17A1}, {0x0005, 0x4453, 0x4CE1, 0x01B7},
    {0x0005, 0x4874, 0x5995, 0x0652}, {0x0005, 0x4C2A, 0x6502, 0x0DBF}, {0x0005, 0x4F49, 0x6E9B, 0x17A1}, {0x0005, 0x75D3, 0x322D, 0x204F},
    {0x0005, 0x6FDC, 0x257A, 0x1EAD}, {0x0005, 0x678F, 0x1A0D, 0x1EAD}, {0x0005, 0x5D53, 0x1074, 0x204F}, {0x0005, 0x43ED, 0x0833, 0x204F},
    {0x0005, 0x3601, 0x09F3, 0x1EAD}, {0x0005, 0x2892, 0x0E50, 0x1EAD}, {0x0005, 0x1C48, 0x1515, 0x204F}, {0x0005, 0x0C96, 0x2AB0, 0x204F},
    {0x0005, 0x09F2, 0x3877, 0x1EAD}, {0x0005, 0x09F2, 0x4697, 0x1EAD}, {0x0005, 0x0C96, 0x545F, 0x204F}, {0x0005, 0x1C48, 0x69FA, 0x204F},
    {0x0005, 0x2892, 0x70BE, 0x1EAD}, {0x0005, 0x3601, 0x751C, 0x1EAD}, {0x0005, 0x43ED, 0x76DB, 0x204F}, {0x0005, 0x5D53, 0x6E9B, 0x204F},
    {0x0005, 0x678F, 0x6502, 0x1EAD}, {0x0005, 0x6FDC, 0x5995, 0x1EAD}, {0x0005, 0x75D3, 0x4CE1, 0x204F}, {0x0005, 0x7CD8, 0x3747, 0x2E59},
    {0x0005, 0x7D8E, 0x2F6E, 0x3A11}, {0x0005, 0x7B43, 0x285E, 0x4615}, {0x0005, 0x7613, 0x226F, 0x51CE}, {0x0005, 0x4AF2, 0x031A, 0x2E59},
    {0x0005, 0x43B3, 0x0000, 0x3A11}, {0x0005, 0x3C46, 0x0000, 0x4615}, {0x0005, 0x3508, 0x031A, 0x51CE}, {0x0005, 0x09E7, 0x226F, 0x2E59},
    {0x0005, 0x04B7, 0x285E, 0x3A11}, {0x0005, 0x026B, 0x2F6E, 0x4615}, {0x0005, 0x0321, 0x3747, 0x51CE}, {0x0005, 0x139B, 0x69FA, 0x2E59},
    {0x0005, 0x17A4, 0x70BE, 0x3A11}, {0x0005, 0x1DA6, 0x751C, 0x4615}, {0x0005, 0x2555, 0x76DB, 0x51CE}, {0x0005, 0x5AA4, 0x76DB, 0x2E59},
    {0x0005, 0x6254, 0x751C, 0x3A11}, {0x0005, 0x6856, 0x70BE, 0x4615}, {0x0005, 0x6C5F, 0x69FA, 0x51CE}, {0x0005, 0x7CD8, 0x47C8, 0x2E59},
    {0x0005, 0x7D8E, 0x4FA1, 0x3A11}, {0x0005, 0x7B43, 0x56B1, 0x4615}, {0x0005, 0x7613, 0x5CA0, 0x51CE}, {0x0005, 0x5AA4, 0x0833, 0x2E59},
    {0x0005, 0x6254, 0x09F3, 0x3A11}, {0x0005, 0x6856, 0x0E50, 0x4615}, {0x0005, 0x6C5F, 0x1515, 0x51CE}, {0x0005, 0x139B, 0x1515, 0x2E59},
    {0x0005, 0x17A4, 0x0E50, 0x3A11}, {0x0005, 0x1DA6, 0x09F3, 0x4615}, {0x0005, 0x2555, 0x0833, 0x51CE}, {0x0005, 0x09E7, 0x5CA0, 0x2E59},
    {0x0005, 0x04B7, 0x56B1, 0x3A11}, {0x0005, 0x026B, 0x4FA1, 0x4615}, {0x0005, 0x0321, 0x47C8, 0x51CE}, {0x0005, 0x4AF2, 0x7BF5, 0x2E59},
    {0x0005, 0x43B3, 0x7F0F, 0x3A11}, {0x0005, 0x3C46, 0x7F0F, 0x4615}, {0x0005, 0x3508, 0x7BF5, 0x51CE}, {0x0005, 0x63B2, 0x1515, 0x5FD8},
    {0x0005, 0x5768, 0x0E50, 0x617A}, {0x0005, 0x49F9, 0x09F3, 0x617A}, {0x0005, 0x3C0D, 0x0833, 0x5FD8}, {0x0005, 0x22A7, 0x1074, 0x5FD8},
    {0x0005, 0x186B, 0x1A0D, 0x617A}, {0x0005, 0x101D, 0x257A, 0x617A}, {0x0005, 0x0A26, 0x322D, 0x5FD8}, {0x0005, 0x0A26, 0x4CE1, 0x5FD8},
    {0x0005, 0x101D, 0x5995, 0x617A}, {0x0005, 0x186B, 0x6502, 0x617A}, {0x0005, 0x22A7, 0x6E9B, 0x5FD8}, {0x0005, 0x3C0D, 0x76DB, 0x5FD8},
    {0x0005, 0x49F9, 0x751C, 0x617A}, {0x0005, 0x5768, 0x70BE, 0x617A}, {0x0005, 0x63B2, 0x69FA, 0x5FD8}, {0x0005, 0x7364, 0x545F, 0x5FD8},
    {0x0005, 0x7608, 0x4697, 0x617A}, {0x0005, 0x7608, 0x3877, 0x617A}, {0x0005, 0x7364, 0x2AB0, 0x5FD8}, {0x0005, 0x4B58, 0x3747, 0x7E70},
    {0x0005, 0x5626, 0x2F6E, 0x79D5}, {0x0005, 0x5FDF, 0x285E, 0x7268}, {0x0005, 0x6809, 0x226F, 0x6886}, {0x0005, 0x3BA6, 0x322D, 0x7E70},
    {0x0005, 0x3786, 0x257A, 0x79D5}, {0x0005, 0x33CF, 0x1A0D, 0x7268}, {0x0005, 0x30B1, 0x1074, 0x6886}, {0x0005, 0x31F3, 0x3F87, 0x7E70},
    {0x0005, 0x2498, 0x3F87, 0x79D5}, {0x0005, 0x1894, 0x3F87, 0x7268}, {0x0005, 0x0E7D, 0x3F87, 0x6886}, {0x0005, 0x3BA6, 0x4CE1, 0x7E70},
    {0x0005, 0x3786, 0x5995, 0x79D5}, {0x0005, 0x33CF, 0x6502, 0x7268}, {0x0005, 0x30B1, 0x6E9B, 0x6886}, {0x0005, 0x4B58, 0x47C8, 0x7E70},
    {0x0005, 0x5626, 0x4FA1, 0x79D5}, {0x0005, 0x5FDF, 0x56B1, 0x7268}, {0x0005, 0x6809, 0x5CA0, 0x6886}, {0x0005, 0x5283, 0x3212, 0x0465},
    {0x0005, 0x6015, 0x31F4, 0x0A7D}, {0x0005, 0x56D1, 0x2533, 0x0A7D}, {0x0005, 0x6C28, 0x31EF, 0x13EA}, {0x0005, 0x6460, 0x2518, 0x12A7},
    {0x0005, 0x5A91, 0x19B9, 0x13EA}, {0x0005, 0x38E9, 0x29C0, 0x0465}, {0x0005, 0x3CFE, 0x1CCF, 0x0A7D}, {0x0005, 0x2E01, 0x21AE, 0x0A7D},
    {0x0005, 0x40B5, 0x1152, 0x13EA}, {0x0005, 0x3217, 0x14C1, 0x12A7}, {0x0005, 0x243F, 0x1A91, 0x13EA}, {0x0005, 0x2917, 0x3F87, 0x0465},
    {0x0005, 0x1E0B, 0x37A6, 0x0A7D}, {0x0005, 0x1E0B, 0x4769, 0x0A7D}, {0x0005, 0x1443, 0x3091, 0x13EA}, {0x0005, 0x1303, 0x3F87, 0x12A7},
    {0x0005, 0x1443, 0x4E7E, 0x13EA}, {0x0005, 0x38E9, 0x554F, 0x0465}, {0x0005, 0x2E01, 0x5D61, 0x0A7D}, {0x0005, 0x3CFE, 0x6240, 0x0A7D},
    {0x0005, 0x243F, 0x647D, 0x13EA}, {0x0005, 0x3217, 0x6A4D, 0x12A7}, {0x0005, 0x40B5, 0x6DBD, 0x13EA}, {0x0005, 0x5283, 0x4CFD, 0x0465},
    {0x0005, 0x56D1, 0x59DB, 0x0A7D}, {0x0005, 0x6015, 0x4D1B, 0x0A7D}, {0x0005, 0x5A91, 0x6556, 0x13EA}, {0x0005, 0x6460, 0x59F7, 0x12A7},
    {0x0005, 0x6C28, 0x4D20, 0x13EA}, {0x0005, 0x7F9C, 0x3F87, 0x39DE}, {0x0005, 0x7F19, 0x4769, 0x4679}, {0x0005, 0x7F19, 0x37A6, 0x4679},
    {0x0005, 0x7B0B, 0x4E7E, 0x536F}, {0x0005, 0x7CBB, 0x3F87, 0x53FD}, {0x0005, 0x7B0B, 0x3091, 0x536F}, {0x0005, 0x53A6, 0x0306, 0x39DE},
    {0x0005, 0x5AFC, 0x05F1, 0x4679}, {0x0005, 0x4BFF, 0x0112, 0x4679}, {0x0005, 0x6078, 0x0BFD, 0x536F}, {0x0005, 0x52C2, 0x05C3, 0x53FD},
    {0x0005, 0x4401, 0x02BE, 0x536F}, {0x0005, 0x0C85, 0x1A22, 0x39DE}, {0x0005, 0x1190, 0x140F, 0x4679}, {0x0005, 0x084C, 0x20CF, 0x4679},
    {0x0005, 0x1902, 0x10B6, 0x536F}, {0x0005, 0x0ED9, 0x1BD3, 0x53FD}, {0x0005, 0x076B, 0x28EC, 0x536F}, {0x0005, 0x0C85, 0x64EC, 0x39DE},
    {0x0005, 0x084C, 0x5E40, 0x4679}, {0x0005, 0x1190, 0x6B00, 0x4679}, {0x0005, 0x076B, 0x5622, 0x536F}, {0x0005, 0x0ED9, 0x633B, 0x53FD},
    {0x0005, 0x1902, 0x6E58, 0x536F}, {0x0005, 0x53A6, 0x7C09, 0x39DE}, {0x0005, 0x4BFF, 0x7DFC, 0x4679}, {0x0005, 0x5AFC, 0x791E, 0x4679},
    {0x0005, 0x4401, 0x7C51, 0x536F}, {0x0005, 0x52C2, 0x794C, 0x53FD}, {0x0005, 0x6078, 0x7311, 0x536F}, {0x0005, 0x7375, 0x1A22, 0x4649},
    {0x0005, 0x6E6A, 0x140F, 0x39AE}, {0x0005, 0x77AE, 0x20CF, 0x39AE}, {0x0005, 0x66F8, 0x10B6, 0x2CB7}, {0x0005, 0x7121, 0x1BD3, 0x2C2A},
    {0x0005, 0x788F, 0x28EC, 0x2CB7}, {0x0005, 0x2C54, 0x0306, 0x4649}, {0x0005, 0x24FD, 0x05F1, 0x39AE}, {0x0005, 0x33FB, 0x0112, 0x39AE},
    {0x0005, 0x1F82, 0x0BFD, 0x2CB7}, {0x0005, 0x2D38, 0x05C3, 0x2C2A}, {0x0005, 0x3BF8, 0x02BE, 0x2CB7}, {0x0005, 0x005E, 0x3F87, 0x4649},
    {0x0005, 0x00E0, 0x4769, 0x39AE}, {0x0005, 0x00E0, 0x37A6, 0x39AE}, {0x0005, 0x04EF, 0x4E7E, 0x2CB7}, {0x0005, 0x033F, 0x3F87, 0x2C2A},
    {0x0005, 0x04EF, 0x3091, 0x2CB7}, {0x0005, 0x2C54, 0x7C09, 0x4649}, {0x0005, 0x33FB, 0x7DFC, 0x39AE}, {0x0005, 0x24FD, 0x791E, 0x39AE},
    {0x0005, 0x3BF8, 0x7C51, 0x2CB7}, {0x0005, 0x2D38, 0x794C, 0x2C2A}, {0x0005, 0x1F82, 0x7311, 0x2CB7}, {0x0005, 0x7375, 0x64EC, 0x4649},
    {0x0005, 0x77AE, 0x5E40, 0x39AE}, {0x0005, 0x6E6A, 0x6B00, 0x39AE}, {0x0005, 0x788F, 0x5622, 0x2CB7}, {0x0005, 0x7121, 0x633B, 0x2C2A},
    {0x0005, 0x66F8, 0x6E58, 0x2CB7}, {0x0005, 0x4710, 0x29C0, 0x7BC1}, {0x0005, 0x42FB, 0x1CCF, 0x75AA}, {0x0005, 0x51F9, 0x21AE, 0x75AA},
    {0x0005, 0x3F45, 0x1152, 0x6C3D}, {0x0005, 0x4DE3, 0x14C1, 0x6D80}, {0x0005, 0x5BBB, 0x1A91, 0x6C3D}, {0x0005, 0x2D76, 0x3212, 0x7BC1},
    {0x0005, 0x1FE5, 0x31F4, 0x75AA}, {0x0005, 0x2928, 0x2533, 0x75AA}, {0x0005, 0x13D1, 0x31EF, 0x6C3D}, {0x0005, 0x1B9A, 0x2518, 0x6D80},
    {0x0005, 0x2569, 0x19B9, 0x6C3D}, {0x0005, 0x2D76, 0x4CFD, 0x7BC1}, {0x0005, 0x2928, 0x59DB, 0x75AA}, {0x0005, 0x1FE5, 0x4D1B, 0x75AA},
    {0x0005, 0x2569, 0x6556, 0x6C3D}, {0x0005, 0x1B9A, 0x59F7, 0x6D80}, {0x0005, 0x13D1, 0x4D20, 0x6C3D}, {0x0005, 0x4710, 0x554F, 0x7BC1},
    {0x0005, 0x51F9, 0x5D61, 0x75AA}, {0x0005, 0x42FB, 0x6240, 0x75AA}, {0x0005, 0x5BBB, 0x647D, 0x6C3D}, {0x0005, 0x4DE3, 0x6A4D, 0x6D80},
    {0x0005, 0x3F45, 0x6DBD, 0x6C3D}, {0x0005, 0x56E3, 0x3F87, 0x7BC1}, {0x0005, 0x61EF, 0x37A6, 0x75AA}, {0x0005, 0x61EF, 0x4769, 0x75AA},
    {0x0005, 0x6BB6, 0x3091, 0x6C3D}, {0x0005, 0x6CF6, 0x3F87, 0x6D80}, {0x0005, 0x6BB6, 0x4E7E, 0x6C3D},
};
ChPackedVtx* lbl_1_data_EF70[14] = {
    lbl_1_data_AE20, lbl_1_data_B2B8, lbl_1_data_B540, lbl_1_data_B7C8,
    lbl_1_data_BA50, lbl_1_data_BC68, lbl_1_data_BDC0, lbl_1_data_BF18,
    lbl_1_data_C200, lbl_1_data_C638, lbl_1_data_CA70, lbl_1_data_CF08,
    lbl_1_data_D3A0, lbl_1_data_D838,
};
// One value per lbl_1_data_EF70 shape, then RGBA colours; nothing in the code reads it.
typedef struct ChShapeInfo {
    /* 0x00 */ s32 value[14];
    /* 0x38 */ u32 colors[41];
} ChShapeInfo;
ChShapeInfo lbl_1_data_EFA8 = {
    {42, 21, 33, 42, 30, 33, 36, 39, 39, 39, 36, 42, 39, 54},
    {
        0x8F5C0AFF, 0xFF0000FF, 0xF1DA95FF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0xFF4040FF, 0x40FF40FF, 0x4040FFFF, 0xFFFF40FF, 0xFF40FFFF, 0x40FFFFFF, 0xFF6060FF,
        0x60FF60FF, 0x6060FFFF, 0xFFFF60FF, 0xFF60FFFF, 0x60FFFFFF, 0xF5FFFAFF, 0x60FFFFFF, 0xFFD700FF,
        0xFF60FFFF, 0xFFFF60FF, 0x98FB98FF, 0x6060FFFF, 0x7FFFD4FF, 0x60FF60FF, 0xAFEEEEFF, 0x40FFFFFF,
        0xFF6060FF,
    },
};
static ChallengeFxParams lbl_1_data_F084 = {256, 2, {0.0003f, 0.0004f, 0.005f, 0.003f}, {0x00, 0x00, 0x00, 0x00}, -20.0f}; // edited by fn_1_FB98
f32 lbl_1_data_F0A4 = 10.0f; // nothing in the code reads it
// Not defined here: the original addresses lbl_1_data_F0A8 with its own symbol even in functions that
// pool this file's other data, so it is most likely defined in another translation unit.
extern u8 lbl_1_data_F0A8[];
ChParticleParams5 lbl_1_data_F0BC = { // edited by fn_1_F6E4
    NULL, 4, 20, 80000, 30000, 78000, 60, 10, 109000, 101000,
    0, 40, 12800000, 0, 0, 0, 0xFFFFFF00, 0, 75000, 0,
};
// Not defined here: the original addresses lbl_1_data_F10C with its own symbol even in functions that
// pool this file's other data, so it is most likely defined in another translation unit.
// Fireball emitter parameters (fn_1_F37C): type-5 params plus the launch speed and acceleration.
typedef struct ChFireballParams {
    /* 0x00 */ ChParticleParams5 p;
    /* 0x50 */ s32 unk50[3];
    /* 0x5C */ s32 speed; // x100000
    /* 0x60 */ s32 accel; // x100000
    /* 0x64 */ s32 unk64;
} ChFireballParams; // size: 0x68
extern ChFireballParams lbl_1_data_F10C;
// The tail (+0x48..+0x68) of lbl_1_data_F10C, under its own symbol.
s32 lbl_1_data_F154[8] = {
    0, 0, 0, 40000, 128, 64, 50000, -1000,
};
// Not defined here: the original addresses lbl_1_data_F174 with its own symbol even in functions that
// pool this file's other data, so it is most likely defined in another translation unit.
extern ChParticleParams* lbl_1_data_F174[];
u16 lbl_1_data_F17C[6] = {
    0x0007, 0x0008, 0x0004, 0x0005, 0x0006, 0xFFFF,
};
ChParticleParams5 lbl_1_data_F188 = {
    NULL, 7, 3, 100000, 30000, 10000, 12, 8, 110000, 50000,
    0, 60, 4500000, 20000000, 0, 2000000, 0xFFFFFF00, 0, 75000, 0,
};
ChParticleParams5 lbl_1_data_F1D8 = {
    NULL, 7, 10, 18000, 20000, 60000, 12, 6, 109000, 101000,
    0, 60, 4500000, 9400000, -1000000, 4500000, 0xFFFFFF00, 0, 75000, 0,
};
ChParticleParams5 lbl_1_data_F228 = {
    NULL, 4, 1, 60000, 10000, 50000, 30, 8, 104000, 105999,
    0, 90, 12800000, 10000000, 1000000, 6000000, 0x3C3C3C00, 0, 75000, 0,
};
ChParticleParams5* lbl_1_data_F278[3] = {&lbl_1_data_F188, &lbl_1_data_F1D8, &lbl_1_data_F228};
u8 lbl_1_data_F284[16] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
};
const char* lbl_1_data_F294[3] = {
    lbl_1_rodata_7328, lbl_1_rodata_7330, lbl_1_rodata_733C,
};
ChParticleParamsC lbl_1_data_F2A0 = {
    NULL, 25, {100, 40, 60, 18000, 20000, -2000000, 2000000, 80000,
    100000, 200, -1, 0, 0, 1, 0, 0, 0, 0,
    0},
};
ChScriptRecord lbl_1_data_F2F4[6] = {
    {"TEST", {{1, 55, 0, 27, -2}, {1, 30, 0, 0, -2}, {1, 30, 0, 0, -2}, {1, 30, 0, 0, -2}, {1, 30, 0, 0, -2}}},
    {"TEST", {{1, 30, 0, 0, -2}, {1, 8, 0, 2, -2}, {1, 9, 0, 5, -2}, {1, 21, 0, 3, -2}, {1, 30, 0, 0, -2}}},
    {"TEST", {{1, 30, 0, 0, -2}, {1, 30, 0, 1, -2}, {1, 40, 0, 10, -2}, {1, 9, 0, 8, -2}, {1, 17, 0, 9, -2}, {1, 10, 0, 4, -2}, {1, 30, 0, 0, -2}}},
    {"TEST", {{1, 30, 0, 0, -2}, {1, 5, 0, 11, -2}, {1, 40, 0, 12, -2}, {1, 15, 0, 13, -2}, {1, 30, 0, 0, -2}}},
    {"TEST", {{1, 30, 0, 0, -2}, {1, 26, 0, 7, -2}, {1, 30, 0, 0, -2}}},
    {"", {0}},
};
// Animation scripts: lbl_1_data_F2F4 holds 0x50-byte records (name, then 8 steps at +0x10).
typedef struct ChScriptTable {
    /*0x0*/ s16 count;   // records before the empty one (counted by fn_1_E8D4)
    /*0x2*/ s16 current; // record being edited (fn_1_E098)
    /*0x4*/ ChScriptRecord* records;
} ChScriptTable;
static ChScriptTable lbl_1_data_F4D4 = {0, 0, lbl_1_data_F2F4};
const char* lbl_1_data_F4DC[3] = {
    lbl_1_rodata_7350, lbl_1_rodata_7354, lbl_1_rodata_7358,
};
u16 lbl_1_data_F4E8[4][2] = {{0x0014, 0x001A}, {0x003C, 0x003D}, {0x003C, 0x003D}, {0x004A, 0x004B}};
ChDrawMtxNode lbl_1_data_F4F8[2] = {{0, fn_1_C9E0}, {0, fn_1_C9E0}};
f32 lbl_1_data_F568[1] = {
    0.5f,
};
u16 lbl_1_data_F56C = 0x0014;
u16 lbl_1_data_F56E = 0x001A;
static ChallengeOverlay lbl_1_data_F570 = {1.0f, 0x00000080, 16777216.0f, 16777215.0f, 0xFFFF00C0, 0xFFFF0000};

static inline void fn_1_135C0_bone(GameActor* actor, u16 bone) {
    if (bone != 0xFFFF) {
        fn_800B2BA8(actor, bone, NULL, 0);
        actor->boneArray[bone]->stepTranslation = 1;
    }
}

// .text:0x17D90 size:0x124
void fn_1_17D90(void) {
    s32 n;
    ChScriptStep* src;
    ChallengeStep* dst;
    CharMgr* base;
    fn_800AD038(lbl_80366158[2]);
    CH_TASK->result = 0;
    CH_TASK->func = fn_1_17B5C;
    src = &lbl_1_data_F4D4.records[0].steps[6]; // src[2] is the step: the original walks base+0x40 with a 0x10 displacement
    n = 8;
    dst = &lbl_1_bss_3218[8];
    base = CHARMGR_AT(lbl_1_bss_5F73);
    while ((src--, dst--, n-- != 0)) {
        if (src[2].used != 0) {
            ANIMBank* table;
            s16 a = src[2].group;
            s16 b;
            s16 c;
            dst->group = a;
            table = base->actors[0].banks.b[a];
            b = src[2].index;
            dst->index = b;
            dst->sync = src[2].sync;
            c = src[2].frame;
            if (c == -2) {
                if (table != NULL) {
                    dst->frame = (s32)PTR32_GET(struct ANIMAnimTrack, PTR32_GET(ANIMSequences, table->animSequences)[b].trackArray)->animTime;
                } else {
                    dst->frame = 0;
                }
            } else {
                dst->frame = c;
            }
        } else {
            dst->group = -1;
            dst->sync = 0;
            dst->frame = 0;
        }
    }
    while ((s8)lbl_1_data_F4D4.records[lbl_1_data_F4D4.count].name[0] != 0) {
        lbl_1_data_F4D4.count += 1;
    }
}

// .text:0x17B5C size:0x234
// NONMATCHING ~85%: the 7-entry search is fully unrolled with fixed offsets in the original (an if-chain gets ~92%); zero-store scheduling
#if NONMATCHING
void fn_1_17B5C(void) {
    s32 i;
    ChPlayer* entry;

    lbl_1_bss_5F62 = -1;
    lbl_1_bss_5F60 = 4;
    for (i = 0; i < 0x36; i++) {
        lbl_1_bss_60A4[i] = lbl_1_data_A978[i] != -1;
    }
    for (i = 0; i < 7; i++) {
        if (lbl_1_data_2390[i] != 0) break;
    }
    lbl_1_bss_68FC.character[0] = 0;
    entry = lbl_1_bss_6940.player;
    entry->group = i;
    entry->seq = 0;
    entry->variant = 0;
    lbl_1_bss_5F5C = 0;
    CH_TASK->func = (void (*)(void))fn_1_176EC;
    fn_80052D70();
}
#endif

// .text:0x179CC size:0x190
// NONMATCHING ~95%: register-only diffs (r4/r5, f4/f5 swapped around the 1/512 constant and row pointer)
#if NONMATCHING
void fn_1_179CC(void) {
    CharActor* row;
    f32 x;
    f32 y;
    f32 z;
    switch (lbl_1_bss_5F72) {
    case 0:
        fn_1_121D4(&lbl_1_bss_67E0.cam);
        break;
    case 1:
        row = &lbl_8036E548.actors[lbl_1_bss_5F73];
        x = row->pos.x;
        y = row->pos.y;
        z = row->pos.z;
        x += (f32)lbl_803C77B8.stickX / 768.0f;
        z += (f32)lbl_803C77B8.stickY / 768.0f;
        y += (f32)lbl_803C77B8.triggerR / 768.0f;
        y -= (f32)lbl_803C77B8.triggerL / 768.0f;
        lbl_1_data_AD0C[1] -= 0.001953125f * (f32)lbl_803C77B8.substickX;
        lbl_1_data_AD0C[0] -= 0.001953125f * (f32)lbl_803C77B8.substickY;
        row->pos.x = x;
        row->pos.y = y;
        row->pos.z = z;
        row->rot.x = lbl_1_data_AD0C[0];
        row->rot.y = lbl_1_data_AD0C[1];
        row->rot.z = lbl_1_data_AD0C[2];
        break;
    }
}
#endif

// .text:0x00017954 size:0x78
void fn_1_17954(void) {
    Mtx44 projection;
    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
}

// .text:0x1770C size:0x248
// NONMATCHING ~97%: with the .data statics the pooled bases now match; only the .bss and .data pool base registers are swapped (r29/r30)
// nmverify: lbl_1_bss_3215 lbl_1_data_1F1A lbl_1_data_A9E4 lbl_1_data_AA54 lbl_1_data_AAC4 lbl_1_data_AB34 lbl_1_data_ABB4 lbl_1_data_AC7C reached through a pooled base in original
#if NONMATCHING
void fn_1_1770C(u8* object) {
    u8 active;

    lbl_1_data_ABB4[lbl_1_bss_5F71]();
    active = 0;
    if (lbl_1_bss_5F71 != 0 && (lbl_1_bss_5F68 == 0 || lbl_1_bss_5F64 != 0.0f)) {
        active = 1;
    }
    lbl_1_bss_3215 = active;
    if (lbl_1_bss_5F5C == 1) {
        fn_800B0A5C_insertQueue((void*)fn_1_107B8, 0xFF);
        lbl_1_bss_5F5C = 2;
    }
    fn_1_179CC();
    PSMTXCopy(lbl_1_bss_67E0.cam.view, lbl_1_bss_68FC.view);
    fn_1_129D0();
    PSMTXCopy(lbl_1_bss_68FC.view, lbl_1_data_AAC4[lbl_803CBBC0[0]].m);
    fn_800A7D4C(7, &lbl_1_data_AAC4[lbl_803CBBC0[0]]);
    if (lbl_1_bss_3078 != 0) {
        fn_800A7D4C(7, &lbl_1_data_AB34[lbl_803CBBC0[0]]);
    }
    PSMTXCopy(lbl_1_bss_68FC.view, lbl_1_data_AA54[lbl_803CBBC0[0]].m);
    fn_800A7D4C(7, &lbl_1_data_AA54[lbl_803CBBC0[0]]);
    if (lbl_1_data_1F1A != 0) {
        PSMTXCopy(lbl_1_bss_68FC.view, lbl_1_data_A9E4[lbl_803CBBC0[0]].m);
        fn_800A7D4C(9, &lbl_1_data_A9E4[lbl_803CBBC0[0]]);
    }
    lbl_803C5090.flags = 1;
    lbl_803C5090.scale = 1.0f;
    lbl_803C5090.unk4 = 1.0f;
    lbl_803C5090.alpha = 0xFF;
    lbl_803C5090.jitterX = 0.0f;
    lbl_803C5090.jitterY = 0.0f;
    lbl_803C5090.lines = 0x1C0;
    fn_8003A2C0();
    fn_800A7D4C(0, &lbl_1_data_AC7C[lbl_803CBBC0[0]]);
}
#endif

void fn_1_176EC(u8* object) {
    fn_1_1496C(object);
}

#if NONMATCHING
// Loader states 6..17 of fn_1_16978: start the ARAM transfer of animation bank `group` of the
// current character, or skip to `next` when the character has none.
static inline void loadAnimBank(ChMainTask* queue, s32 group, s16 next) {
    if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + group] != 0) {
        u8 character = lbl_1_bss_68FC.character[lbl_1_bss_5F73];
        lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[group] =
            (void*)ARAMTransfer(&lbl_1_data_2398[lbl_1_bss_3070.fileBase + (character * 0x13 + 2 + group)], 0, 0, 0);
        CH_TASK->result += 1;
    } else {
        lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[group] = NULL;
        queue->h.result = next;
    }
}

// The odd states: register the transferred bank once the transfer is done.
static inline void getAnimBank(s32 group) {
    ANIMGet(lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[group]);
    CH_TASK->result += 1;
}

#endif

#if !NONMATCHING
// Switch jump tables of fn_1_16978; mwcc emits them itself once the function matches.
void* jumptable_1_data_F7D4[15] = {
    (u8*)fn_1_16978 + 0xC94, (u8*)fn_1_16978 + 0xCA8, (u8*)fn_1_16978 + 0xCCC, (u8*)fn_1_16978 + 0xC94,
    (u8*)fn_1_16978 + 0xCA8, (u8*)fn_1_16978 + 0xCCC, (u8*)fn_1_16978 + 0xC94, (u8*)fn_1_16978 + 0xCA8,
    (u8*)fn_1_16978 + 0xCCC, (u8*)fn_1_16978 + 0xC94, (u8*)fn_1_16978 + 0xCA8, (u8*)fn_1_16978 + 0xCCC,
    (u8*)fn_1_16978 + 0xC94, (u8*)fn_1_16978 + 0xCA8, (u8*)fn_1_16978 + 0xCCC,
};
void* jumptable_1_data_F810[30] = {
    (u8*)fn_1_16978 + 0x54, (u8*)fn_1_16978 + 0x8C, (u8*)fn_1_16978 + 0xB4, (u8*)fn_1_16978 + 0xC8,
    (u8*)fn_1_16978 + 0xF8, (u8*)fn_1_16978 + 0x17C, (u8*)fn_1_16978 + 0x19C, (u8*)fn_1_16978 + 0x248,
    (u8*)fn_1_16978 + 0x290, (u8*)fn_1_16978 + 0x340, (u8*)fn_1_16978 + 0x388, (u8*)fn_1_16978 + 0x438,
    (u8*)fn_1_16978 + 0x480, (u8*)fn_1_16978 + 0x530, (u8*)fn_1_16978 + 0x578, (u8*)fn_1_16978 + 0x628,
    (u8*)fn_1_16978 + 0x670, (u8*)fn_1_16978 + 0x720, (u8*)fn_1_16978 + 0x768, (u8*)fn_1_16978 + 0x81C,
    (u8*)fn_1_16978 + 0x87C, (u8*)fn_1_16978 + 0x938, (u8*)fn_1_16978 + 0x958, (u8*)fn_1_16978 + 0x9D0,
    (u8*)fn_1_16978 + 0x9F0, (u8*)fn_1_16978 + 0xA2C, (u8*)fn_1_16978 + 0xA4C, (u8*)fn_1_16978 + 0xC04,
    (u8*)fn_1_16978 + 0xC34, (u8*)fn_1_16978 + 0xD44,
};
#endif

// .text:0x16978 size:0xD74
// Challenge loader state machine (queue state at +0x10): streams the player's animation banks,
// models and textures from ARAM, then hands over to fn_1_168C8.
// NONMATCHING 87%: the original reaches this unit's .data through one pooled base
// (lbl_1_data_1DC0, not split into this unit); register allocation follows from that
// nmverify: lbl_1_bss_3218 lbl_1_bss_5F73 lbl_1_data_2390 lbl_1_data_A3D8 lbl_1_data_A3F8 lbl_1_data_A5D8 lbl_1_data_A950 lbl_1_data_A978 lbl_1_data_F4D4 reached through a pooled base in original
// nmverify:  inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_1_16978(void) {
    ChMainTask* queue = lbl_803CC1B8;
    s16 step = queue->h.result;
    CharActor* row;
    s32 i;

    switch (step) {
    case 0:
        lbl_1_bss_3098 = NULL;
        ((ChTaskHeader*)fn_800B0A5C_insertQueue((void*)fn_1_10560, 11))->result = 0;
        CH_TASK->result += 1;
        break;
    case 1:
        if (lbl_1_bss_3098 != NULL) {
            fn_8004B1B8(lbl_1_bss_3098);
            CH_TASK->result += 1;
        }
        break;
    case 2:
        lbl_1_bss_5F73 = 0;
        queue->h.result = 4;
        break;
    case 3:
        if (++lbl_1_bss_5F73 == 1) {
            queue->h.result = 27;
        } else {
            queue->h.result = 4;
        }
        break;
    case 4: {
        u8 character = lbl_1_bss_68FC.character[lbl_1_bss_5F73];
        u8 variant = lbl_1_bss_6940.player[lbl_1_bss_5F73].variant;
        lbl_8036E548.actors[lbl_1_bss_5F73].files =
            (void*)ARAMTransfer(&lbl_1_data_2398[lbl_1_bss_3070.fileBase + character * 0x13 + variant], 0, 0, 0);
        CH_TASK->result += 1;
        break;
    }
    case 5:
        if (CH_ARAM_DONE()) {
            queue->h.result = 6;
        }
        break;
    case 6:
        loadAnimBank(queue, 0, 8);
        break;
    case 7:
        if (CH_ARAM_DONE()) {
            getAnimBank(0);
        }
        break;
    case 8:
        loadAnimBank(queue, 1, 10);
        break;
    case 9:
        if (CH_ARAM_DONE()) {
            getAnimBank(1);
        }
        break;
    case 10:
        loadAnimBank(queue, 2, 12);
        break;
    case 11:
        if (CH_ARAM_DONE()) {
            getAnimBank(2);
        }
        break;
    case 12:
        loadAnimBank(queue, 3, 14);
        break;
    case 13:
        if (CH_ARAM_DONE()) {
            getAnimBank(3);
        }
        break;
    case 14:
        loadAnimBank(queue, 4, 18); // skips group 5 as well
        break;
    case 15:
        if (CH_ARAM_DONE()) {
            getAnimBank(4);
        }
        break;
    case 16:
        loadAnimBank(queue, 5, 18);
        break;
    case 17:
        if (CH_ARAM_DONE()) {
            getAnimBank(5);
        }
        break;
    case 18:
        if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 6] != 0) {
            u8 character = lbl_1_bss_68FC.character[lbl_1_bss_5F73];
            lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[6] =
                (void*)ARAMTransfer(&lbl_1_data_2398[lbl_1_bss_3070.fileBase + (character * 0x13 + 8)], 0, 0, 0);
            CH_TASK->result += 1;
        } else {
            lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[6] = NULL;
            queue->h.result += 1;
        }
        break;
    case 19:
        if (CH_ARAM_DONE()) {
            if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 6] != 0) {
                ANIMGet(lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[6]);
            }
            CH_TASK->result += 1;
        }
        break;
    case 20:
        row = &lbl_8036E548.actors[lbl_1_bss_5F73];
        if (lbl_1_bss_3070.parts == 0 || row->files[4] == NULL) {
            queue->h.result = 22;
            break;
        }
        row->part = &lbl_1_bss_6940.part[lbl_1_bss_5F73];
        if (lbl_1_bss_68FC.character[lbl_1_bss_5F73] == 0) {
            lbl_8036E548.actors[lbl_1_bss_5F73].part->files = ARAMTransfer(lbl_1_data_A3F8, 0, 0, 0);
            CH_TASK->result += 1;
        } else {
            lbl_1_bss_3070.parts = 0;
            queue->h.result = 22;
        }
        break;
    case 21:
        if (CH_ARAM_DONE()) {
            queue->h.result = step + 1;
        }
        break;
    case 22: {
        s16 file = lbl_1_data_A978[lbl_1_bss_68FC.character[lbl_1_bss_5F73]];
        if (file >= 0) {
            (&lbl_1_bss_60A0)[lbl_1_bss_5F73] = (void*)ARAMTransfer(&lbl_1_data_A5D8[file], 0, 0, 0);
            CH_TASK->result += 1;
        } else {
            queue->h.result = 3;
        }
        break;
    }
    case 23:
        if (CH_ARAM_DONE()) {
            queue->h.result = 3;
        }
        break;
    case 24:
        lbl_8036E548.stadiumFiles = (void*)ARAMTransfer(lbl_1_data_A3D8, 0, 0, 0);
        CH_TASK->result += 1;
        break;
    case 25:
        if (CH_ARAM_DONE()) {
            queue->h.result = step + 1;
        }
        break;
    case 26: {
        u32* offsets;
        fn_1_D7A4(0);
        // Relocate the 80 offsets at the start of the loaded file into pointers.
        offsets = (u32*)lbl_8036E548.stadiumFiles;
        for (i = 0; i < 0x50; i++) {
            // TODO port: in-place 32-bit offset relocation of a loaded file; needs the port's relocation layer
            ((u8**)lbl_8036E548.stadiumFiles)[i] = (u8*)offsets + offsets[i];
        }
        CH_TASK->result = 27;
        break;
    }
    case 27:
        lbl_1_bss_60DC = (u8*)ARAMTransfer(&lbl_1_data_A950, 0, 0, 0);
        CH_TASK->result = 28;
        break;
    case 28:
        if (CH_ARAM_DONE()) {
            struct ActorLayout* layout;
            void* geometry;
            void* textures;

            lbl_1_bss_60E0 = ActorObjectInitTable(5);
            for (i = 0; i < 15; i++) {
                u32 offset = ((u32*)lbl_1_bss_60DC)[i];
                if (offset == 0) {
                    continue;
                }
                ((u8**)lbl_1_bss_60DC)[i] = lbl_1_bss_60DC + offset;
                // three files per actor: layout, geometry, textures
                switch (i) {
                case 0:
                case 3:
                case 6:
                case 9:
                case 12:
                    layout = ((struct ActorLayout**)lbl_1_bss_60DC)[i];
                    LoadActorLayout(layout);
                    break;
                case 1:
                case 4:
                case 7:
                case 10:
                case 13:
                    geometry = ((void**)lbl_1_bss_60DC)[i];
                    convertGeometryAndSknHeader(geometry, NULL);
                    haveActLayoutPointToGeoHeader(layout, geometry);
                    break;
                case 2:
                case 5:
                case 8:
                case 11:
                case 14:
                    textures = ((void**)lbl_1_bss_60DC)[i];
                    convertTextureHeader(textures);
                    fn_800BD190(geometry, textures);
                    fn_800BDC88(lbl_1_bss_60E0, i / 3, i / 3, layout, NULL, 0);
                    break;
                }
            }
            CH_TASK->result = 29;
        }
        break;
    case 29:
        lbl_1_bss_5F73 = 0;
        queue->h.result = 0;
        CH_TASK->func = fn_1_168C8;
        break;
    }
}
#endif

// .text:0x168C8 size:0xB0
void fn_1_168C8(void) {
    ChMainTask* queue = lbl_803CC1B8;
    if (lbl_1_bss_3084 == 0) {
        lbl_1_bss_3084 = 1;
        queue->ticks = OSGetTick();
        fn_1_135C0();
        queue->ticks = OSGetTick() - queue->ticks;
    } else {
        lbl_1_bss_3084 = 0;
        queue->h.result = 0;
        if (lbl_8036E548.actors[0].files[4] != NULL) {
            CH_TASK->func = (void (*)(void))fn_1_1770C;
        } else {
            CH_TASK->func = (void (*)(void))fn_1_1770C;
        }
    }
}

// .text:0x165E0 size:0x2E8
void fn_1_165E0(void) {
    s16 delta;
    u16 buttons;
    Light* light;

    buttons = lbl_803C77B8._04;
    delta = 0;
    light = lbl_8036E548.lights[(s8)*(u8*)&lbl_1_bss_5F70];
    if (buttons & 1) {
        delta = -1;
    } else if (buttons & 2) {
        delta = 1;
    } else if (buttons & 8) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 9;
        }
    } else if (buttons & 4) {
        if (++lbl_1_bss_307C >= 10) {
            lbl_1_bss_307C = 0;
        }
    } else if (lbl_803C77B8._02 & 0x200) {
        *(u8*)&lbl_1_bss_5F70 = 0;
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
    if (lbl_803C77B8._00 & 0x400) {
        delta *= 10;
    }
    switch (lbl_1_bss_307C) {
    case 0: {
        lbl_1_bss_5F70 += delta;
        if (lbl_1_bss_5F70 < 0) {
            *(u8*)&lbl_1_bss_5F70 = 2;
        } else if (lbl_1_bss_5F70 >= 3) {
            *(u8*)&lbl_1_bss_5F70 = 0;
        }
        break;
    }
    case 1:
        light->color.r += delta;
        if (light->color.r > 0xFF) {
            light->color.r = 0;
        }
        break;
    case 2:
        light->color.g += delta;
        if (light->color.g > 0xFF) {
            light->color.g = 0;
        }
        break;
    case 3:
        light->color.b += delta;
        if (light->color.b > 0xFF) {
            light->color.b = 0;
        }
        break;
    case 4:
        light->position.x += delta;
        break;
    case 5:
        light->position.y += delta;
        break;
    case 6:
        light->position.z += delta;
        break;
    case 7:
        light->direction.x += delta;
        break;
    case 8:
        light->direction.y += delta;
        break;
    case 9:
        light->direction.z += delta;
        break;
    }
}

// .text:0x16590 size:0x50
void* fn_1_16590(void) {
    u32 scene = lbl_1_bss_5F73;
    CharActor* base = (CharActor*)&lbl_8036E548; // stepped by actors, see CHARMGR_AT
    ANIMBank* table;
    void** bank;
    base += scene;
    // banks.b[group], stepped the way the original does: (base + group) then the field offset
    bank = (void**)base;
    bank += lbl_1_bss_6940.player[scene].group;
    table = ((CharMgr*)bank)->actors[0].banks.b[0];
    return PTR32_GET(char, PTR32_GET(ANIMSequences, table->animSequences)[lbl_1_bss_6940.player[scene].seq].sequenceName);
}

// .text:0x00016558 size:0x38
void* fn_1_16558(s32 group, s32 index) {
    CharActor* base = (CharActor*)&lbl_8036E548; // stepped by actors, see CHARMGR_AT
    ANIMBank* table;
    void** bank;
    base += lbl_1_bss_5F73;
    // banks.b[group], stepped the way the original does: (base + group) then the field offset
    bank = (void**)base;
    bank += group;
    table = ((CharMgr*)bank)->actors[0].banks.b[0];
    return PTR32_GET(char, PTR32_GET(ANIMSequences, table->animSequences)[index].sequenceName);
}

// .text:0x1644C size:0x10C
void fn_1_1644C(void) {
    CharActor* entry;
    s32 i;
    u8** p;
    entry = lbl_8036E548.active[lbl_1_bss_5F73];
    lbl_1_bss_5F69 = lbl_1_bss_5F69 ^ 1;
    if (entry != NULL) {
        ActorObject* slot = &lbl_8036E548.slots->objects[lbl_1_bss_5F73];
        if (lbl_1_bss_5F69 == 0) {
            slot->boneRemap = NULL;
        } else {
            slot->boneRemap = entry->mirror;
        }
        fn_1_ECF8(lbl_1_bss_5F73, lbl_1_bss_6940.player[lbl_1_bss_5F73].group, lbl_1_bss_5F69);
        p = (u8**)lbl_1_bss_67B8;
        for (i = 0; i < 4; i++) {
            if (p[i] != NULL) ((ShapeAnimState*)p[i])->dirtyB = 3;
        }
    }
}

// .text:0x00016400 size:0x4C
void fn_1_16400(s8 arg) {
    CharActor* base = (CharActor*)&lbl_8036E548; // stepped by actors, see CHARMGR_AT
    GameActor* row;
    u32 mod;
    base += lbl_1_bss_5F73;
    row = ((CharMgr*)base)->actors[0]._004;
    mod = row->totalBones;
    lbl_1_bss_5F6C = (lbl_1_bss_5F6C + mod + arg) % mod;
}

// .text:0x163FC size:0x4
void fn_1_163FC(void) {
}

// .text:0x1620C size:0x1F0
void fn_1_1620C(void) {
    s32 i = 0;
    do {
        CharActor* row = &lbl_8036E548.actors[i];
        row->pos.x = 0.0f;
        row->pos.y = 0.0f;
        row->pos.z = lbl_1_rodata_73F8;
        row->rot.x = 0.0f;
        row->rot.y = 0.0f;
        row->rot.z = 0.0f;
        CTRLSetTranslation(&lbl_8036E548.slots->objects[i].worldControl.base, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&lbl_8036E548.slots->objects[i].worldControl.base, 0.0f, 0.0f, 0.0f);
        i++;
    } while (i < 1);
    fn_1_1347C();
}

// .text:0x000161D0 size:0x3C
void fn_1_161D0(void) {
    lbl_1_bss_5F78 ^= 1;
    fn_800B9A9C(lbl_1_bss_5F78, lbl_1_bss_5F74);
}

#pragma fp_contract off
// .text:0x160F8 size:0xD8
void fn_1_160F8(s32 direction) {
    f32 step = lbl_1_rodata_7430;
    f32 value;
    if (lbl_803C77B8._00 & 0x400) {
        step *= lbl_1_rodata_73F8;
    }
    step *= (f32)direction;
    value = SND_LEVEL + step;
    SND_LEVEL = value;
    if (value > lbl_1_rodata_73BC) {
        SND_LEVEL = lbl_1_rodata_7394;
    }
    if (SND_LEVEL < lbl_1_rodata_7394) {
        SND_LEVEL = lbl_1_rodata_73BC;
    }
    fn_800B9A9C(lbl_1_bss_5F78, SND_LEVEL);
}

#pragma fp_contract on

// .text:0x000160D8 size:0x20
s32 fn_1_160D8(s8 a, s8 b) {
    if (a == b) return 0xFF0F;
    return 0xFFFF;
}

// .text:0x15CE0 size:0x3F8
void fn_1_15CE0(void) {
    u16 buttons = lbl_803C77B8._04;

    if (buttons & 8) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 5;
        }
    } else if (buttons & 4) {
        if (++lbl_1_bss_307C >= 6) {
            lbl_1_bss_307C = 0;
        }
    } else if (buttons & 1) {
        switch (lbl_1_bss_307C) {
        case 0:
            if (--lbl_1_bss_5F72 >= 2) {
                lbl_1_bss_5F72 = 1;
            }
            break;
        case 1:
            break;
        case 2:
            lbl_1_bss_67E0.lightOn ^= 1;
            break;
        case 3:
            lbl_1_data_1F1A ^= 1;
            break;
        case 4:
            if (lbl_1_bss_5F62 >= 0) {
                lbl_1_bss_5F62--;
            }
            break;
        case 5:
            if (lbl_1_bss_5F60 > 1) {
                lbl_1_bss_5F60--;
            }
            break;
        }
    } else if (buttons & 2) {
        switch (lbl_1_bss_307C) {
        case 0:
            if (++lbl_1_bss_5F72 >= 2) {
                lbl_1_bss_5F72 = 0;
            }
            break;
        case 1:
            break;
        case 2:
            lbl_1_bss_67E0.lightOn ^= 1;
            break;
        case 3:
            lbl_1_data_1F1A ^= 1;
            break;
        case 4:
            if (lbl_1_bss_5F62 < 1) {
                lbl_1_bss_5F62++;
            }
            break;
        case 5:
            if (lbl_1_bss_5F60 < 0x10) {
                lbl_1_bss_5F60++;
            }
            break;
        }
    } else if (buttons & 0x100) {
        switch (lbl_1_bss_307C) {
        case 1:
            fn_1_1620C();
            break;
        }
    } else if (buttons & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x15760 size:0x580
// NONMATCHING ~80%: jump-table cases written as helpers; the original inlines fn_1_CC24
#if NONMATCHING
static inline void fn_1_15760_group(s32 direction) {
    ChPlayer* entry = lbl_1_bss_6940.player; // player 0
    u8 old = entry->group;
    u8 group = old;
    do {
        if (direction < 0) {
            group = (group == 0) ? 6 : group - 1;
        } else {
            group++;
            if (group == 7) {
                group = 0;
            }
        }
    } while (lbl_1_data_2390[group] == 0);
    entry->group = group;
    if (old != group) {
        lbl_1_bss_5F5C = 1;
        entry->seq = 0;
    }
}

void fn_1_15760(void) {
    ChPlayer* entry = lbl_1_bss_6940.player;
    u16 buttons;
    u8 old;
    u16 count;
    s32 i;

    lbl_1_bss_5F73 = 0;
    if (lbl_1_bss_5F5C != 0) {
        return;
    }
    buttons = lbl_803C77B8._04;
    if (buttons & 8) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 7;
        }
    } else if (buttons & 4) {
        if (++lbl_1_bss_307C >= 8) {
            lbl_1_bss_307C = 0;
        }
    } else if (buttons & 1) {
        switch ((u32)lbl_1_bss_307C) {
        case 0:
            fn_1_15760_group(-1);
            break;
        case 1:
            count = ((ANIMBank*)lbl_8036E548.actors[0].banks.b[entry->group])->numSequences;
            old = entry->seq;
            if (old != 0) {
                entry->seq = old - 1;
            } else {
                entry->seq = count - 1;
            }
            if (old != entry->seq) {
                lbl_1_bss_5F5C = 1;
            }
            break;
        case 2:
            lbl_1_data_ABA4 -= lbl_1_rodata_7430;
            if (lbl_1_data_ABA4 < lbl_1_rodata_7394) {
                lbl_1_data_ABA4 = lbl_1_rodata_7394;
            }
            break;
        case 3:
            fn_1_1644C();
            break;
        case 4:
            lbl_1_bss_3081 ^= 1;
            break;
        case 5:
            if (lbl_1_bss_3216 == 0) {
                lbl_1_bss_3216 = 3;
            }
            lbl_1_bss_3216--;
            break;
        case 6:
            lbl_1_bss_5F68 ^= 1;
            if (lbl_1_bss_5F68 != 0) {
                ActorObjectTable* table = lbl_8036E548.slots;
                table->objects[0].time = 0.0f;
                table->objects[0].setTime = 1;
            }
            break;
        }
    } else if (buttons & 2) {
        switch ((u32)lbl_1_bss_307C) {
        case 0:
            fn_1_15760_group(1);
            break;
        case 1:
            count = ((ANIMBank*)lbl_8036E548.actors[0].banks.b[entry->group])->numSequences;
            old = entry->seq;
            entry->seq = old + 1;
            if (count == (u8)(old + 1)) {
                entry->seq = 0;
            }
            if (old != entry->seq) {
                lbl_1_bss_5F5C = 1;
            }
            break;
        case 2:
            lbl_1_data_ABA4 += lbl_1_rodata_7430;
            break;
        case 3:
            fn_1_1644C();
            break;
        case 4:
            lbl_1_bss_3081 ^= 1;
            break;
        case 5:
            if (++lbl_1_bss_3216 == 3) {
                lbl_1_bss_3216 = 0;
            }
            break;
        case 6:
            lbl_1_bss_5F68 ^= 1;
            if (lbl_1_bss_5F68 != 0) {
                ActorObjectTable* table = lbl_8036E548.slots;
                table->objects[0].time = 0.0f;
                table->objects[0].setTime = 1;
                for (i = 0; i < 5; i++) {
                    if (lbl_1_bss_67B8[i] != NULL) {
                        fn_1_26B7C(lbl_1_bss_67B8[i]);
                    }
                }
            }
            break;
        }
    } else if (buttons & 0x1000) {
        fn_1_CC24();
    } else if (buttons & 0x400) {
        if (lbl_1_bss_307C == 6 && lbl_1_bss_5F68 != 0) {
            lbl_1_bss_5F64 = lbl_1_data_ABA4;
        }
    } else if (buttons & 0x800) {
        if (lbl_1_bss_307C == 6 && lbl_1_bss_5F68 != 0) {
            lbl_1_bss_5F64 = -lbl_1_data_ABA4;
        }
    } else if (buttons & 0x100) {
        if (lbl_1_bss_307C == 6) {
            if (lbl_1_bss_5F68 != 0) {
                lbl_1_bss_5F64 = lbl_1_rodata_73BC;
            }
        } else if (lbl_1_bss_307C == 5) {
            lbl_1_bss_3214 = 1;
        }
    } else if (buttons & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
    // The original then scans player lbl_1_bss_5F73's bones for an animated one and discards the result.
}
#endif

// .text:0x1540C size:0x354
void fn_1_1540C(void) {
    u8 buffer[0x20];
    s32 top;
    s32 count;
    s32 selected;
    u16 buttons;
    u16 id;

    count = 0x14;
    selected = lbl_1_bss_5F6C;
    if (lbl_1_bss_3088 > selected) {
        lbl_1_bss_3088 = selected;
    } else if (lbl_1_bss_3088 < selected - 0x13) {
        lbl_1_bss_3088 = selected - 0x13;
    }
    top = lbl_1_bss_3088;
    fn_1_C2DC(lbl_8036E548.slots->objects[lbl_1_bss_5F73].actor->boneArray[0], buffer, 0, 0x13, 4, &selected, &top, &count);
    buttons = lbl_803C77B8._04;
    if (buttons & 8) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 5;
        }
    } else if (buttons & 4) {
        if (++lbl_1_bss_307C >= 6) {
            lbl_1_bss_307C = 0;
        }
    } else if (buttons & 1) {
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_bss_3080 ^= 1;
            break;
        case 1:
            lbl_1_data_ABA8 ^= 1;
            break;
        case 2:
            fn_1_16400(-1);
            break;
        case 3:
            break;
        case 4:
            if (lbl_1_data_AC90 >= 0) {
                lbl_1_data_AC90--;
            }
            break;
        case 5:
            ((void (*)(void))fn_1_1644C)();
            break;
        }
    } else if (buttons & 2) {
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_bss_3080 ^= 1;
            break;
        case 1:
            lbl_1_data_ABA8 ^= 1;
            break;
        case 2:
            fn_1_16400(1);
            break;
        case 3:
            break;
        case 4:
            if (lbl_1_data_AC90 < 4) {
                lbl_1_data_AC90++;
            }
            break;
        case 5:
            ((void (*)(void))fn_1_1644C)();
            break;
        }
    } else if (buttons & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
    id = lbl_8036E548.actors[0].jointIdx[0x24];
    if (id != 0xFFFF) {
        if (lbl_1_data_AC90 >= 0) {
            GameActor* actor = lbl_1_bss_60E0->objects[lbl_1_data_AC90].actor;
            s32 i;
            for (i = 0; i < actor->totalBones; i++) {
                if (actor->boneArray[i]->dispObj != NULL) {
                    fn_800B2BA8(lbl_8036E548.slots->objects[0].actor, id, actor, i);
                }
            }
        } else {
            fn_800B2BA8(lbl_8036E548.slots->objects[0].actor, id, NULL, 0);
        }
    }
}

// .text:0x151F8 size:0x214
void fn_1_151F8(void) {
    u16 buttons = lbl_803C77B8._04;
    s32 cursor;
    f32 step;
    f32 value;
    if (buttons & 8) {
        cursor = lbl_1_bss_307C - 1;
        lbl_1_bss_307C = cursor;
        if (cursor < 0) {
            lbl_1_bss_307C = 1;
        }
    } else if (buttons & 4) {
        cursor = lbl_1_bss_307C + 1;
        lbl_1_bss_307C = cursor;
        if (cursor >= 2) {
            lbl_1_bss_307C = 0;
        }
    } else if (buttons & 1) {
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_bss_5F78 ^= 1;
            fn_800B9A9C(lbl_1_bss_5F78, SND_LEVEL);
            break;
        case 1:
            step = lbl_1_rodata_7430;
            if (lbl_803C77B8._00 & 0x400) {
                step = step * lbl_1_rodata_73F8;
            }
            step = step * lbl_1_rodata_73A4[0];
            value = SND_LEVEL + step;
            SND_LEVEL = value;
            if (value > lbl_1_rodata_73BC) {
                SND_LEVEL = lbl_1_rodata_7394;
            }
            if (SND_LEVEL < lbl_1_rodata_7394) {
                SND_LEVEL = lbl_1_rodata_73BC;
            }
            fn_800B9A9C(lbl_1_bss_5F78, SND_LEVEL);
            break;
        }
    } else if (buttons & 2) {
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_bss_5F78 ^= 1;
            fn_800B9A9C(lbl_1_bss_5F78, SND_LEVEL);
            break;
        case 1:
            step = lbl_1_rodata_7430;
            if (lbl_803C77B8._00 & 0x400) {
                step = step * lbl_1_rodata_73F8;
            }
            step = step * lbl_1_rodata_73BC;
            value = SND_LEVEL + step;
            SND_LEVEL = value;
            if (value > lbl_1_rodata_73BC) {
                SND_LEVEL = lbl_1_rodata_7394;
            }
            if (SND_LEVEL < lbl_1_rodata_7394) {
                SND_LEVEL = lbl_1_rodata_73BC;
            }
            fn_800B9A9C(lbl_1_bss_5F78, SND_LEVEL);
            break;
        }
    } else if (buttons & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x00015170 size:0x88
void fn_1_15170(void) {
    u16 buttons = lbl_803C77B8._04;
    if (buttons & 0x200) {
        fn_1_148CC();
    } else if (buttons & 0x100) {
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x14FB8 size:0x1B8
void fn_1_14FB8(void) {
    u16 buttons = lbl_803C77B8._04;
    ChMainTask* q = lbl_803CC1B8;

    if (buttons & 8) {
        if (q->page != 0) {
            q->page--;
        } else {
            q->page = 8;
        }
    } else if (buttons & 4) {
        q->page++;
        if (q->page == 9) {
            q->page = 0;
        }
    } else if (lbl_803C77B8._00 & 0x100) {
        switch (q->page) {
        case 0:
            if (buttons & 0x100) lbl_1_bss_5F71 = 3;
            break;
        case 1:
            if (buttons & 0x100) lbl_1_bss_5F71 = 4;
            break;
        case 2:
            if (buttons & 0x100) lbl_1_bss_5F71 = 5;
            break;
        case 3:
            if (buttons & 0x100) lbl_1_bss_5F71 = 6;
            break;
        case 4:
            if (lbl_803C77B8._02 & 0x100) lbl_1_bss_5F71 = 2;
            break;
        case 5:
            if (lbl_803C77B8._02 & 0x100) lbl_1_bss_5F71 = 8;
            break;
        case 6:
            if (lbl_803C77B8._02 & 0x100) lbl_1_bss_5F71 = 7;
            break;
        case 7:
            if (buttons & 0x100) lbl_1_bss_5F71 = 9;
            break;
        case 8:
            if (buttons & 0x100) lbl_1_bss_5F71 = 10;
            break;
        }
    } else if (lbl_803C77B8._02 & 0x200) {
        lbl_1_bss_5F71 = 0;
        minigamesSetSomePointers();
    }
}

// .text:0x1496C size:0x64C
// Debug menu: pick the challenge character/mode, then (A) reset the scene and start fn_1_16978.
// NONMATCHING ~80%: the original inlines fn_1_1347C and fn_1_131E4
#if NONMATCHING
void fn_1_1496C(u8* object) {
    ChMainTask* queue = lbl_803CC1B8;
    u16 buttons = lbl_803C77B8._04;
    s32 i;
    CharActor* row;

    lbl_1_bss_5F73 = 0;
    if (buttons & 1) {
        for (lbl_1_bss_5F73 = 0; lbl_1_bss_5F73 < 1; lbl_1_bss_5F73++) {
            if (lbl_1_bss_68FC.character[lbl_1_bss_5F73] != 0) {
                lbl_1_bss_68FC.character[lbl_1_bss_5F73]--;
            } else {
                lbl_1_bss_68FC.character[lbl_1_bss_5F73] = 0x35;
            }
        }
    } else if (buttons & 2) {
        for (lbl_1_bss_5F73 = 0; lbl_1_bss_5F73 < 1; lbl_1_bss_5F73++) {
            if (++lbl_1_bss_68FC.character[lbl_1_bss_5F73] == 0x36) {
                lbl_1_bss_68FC.character[lbl_1_bss_5F73] = 0;
            }
        }
    } else if (lbl_803C77B8._02 & 0x400) {
        for (lbl_1_bss_5F73 = 0; lbl_1_bss_5F73 < 1; lbl_1_bss_5F73++) {
            lbl_1_bss_6940.player[lbl_1_bss_5F73].variant ^= 1;
        }
    } else if (lbl_803C77B8._02 & 0x800) {
        lbl_1_bss_3070.fileBase = 0x402 - lbl_1_bss_3070.fileBase;
    } else if (lbl_803C77B8._02 & 0x40) {
        lbl_1_bss_3070.parts = 1;
    } else if (lbl_803C77B8._02 & 0x20) {
        lbl_1_bss_3070.parts = 0;
    }
    if (lbl_803C77B8._02 & 0x100) {
        row = lbl_8036E548.actors;
        memset(row, 0, sizeof(lbl_8036E548.actors));
        for (i = 0; i < 13; i++) {
            lbl_8036E548.active[i] = row;
        }
        lbl_8036E548.active[0]->modelIndex = 0;
        lbl_8036E548.active[0]->index = 0;
        fn_1_1347C();
        fn_1_131E4();
        queue->page = 0;
        CH_TASK->result = 0;
        CH_TASK->func = fn_1_16978;
        CH_TASK->result = 0;
        lbl_1_bss_5F68 = 0;
        lbl_1_bss_5F64 = 0.0f;
    } else if (lbl_803C77B8._02 & 0x200) {
        memset(&lbl_8036E548, 0, sizeof(lbl_8036E548));
        lbl_1_bss_3070.parts = 0;
        fn_800AD038(lbl_80366158[2]);
        CH_TASK->parent->result = 1;
    }
}
#endif

// .text:0x00014928 size:0x44
void fn_1_14928(void) {
    fn_800AD038(lbl_80366158[2]);
    CH_TASK->parent->result = 1;
}

// .text:0x000148CC size:0x5C
void fn_1_148CC(void) {
    fn_800AD038(lbl_80366158[2]);
    CH_TASK->result = 0;
    CH_TASK->func = (void (*)(void))fn_1_176EC;
    lbl_1_bss_30B8 = 1;
}

// .text:0x00014888 size:0x44
void fn_1_14888(ActorObject* object) {
    if (lbl_1_bss_67E0.lightOn) {
        fn_800B9AA8(&lbl_1_bss_67E0.cam.light);
    } else {
        fn_800B9AA8(object->lights[0]);
    }
}

// .text:0x14710 size:0x174
void fn_1_14710(CharActor* object) {
    s32 i;
    s32 k;
    ChPair* p;
    ChPair* q;
    s32 mode;
    u16 x;
    u16 y;
    for (i = 0; i < 0x78; i++) {
        object->mirror[i] = i;
    }
    k = 0;
    p = lbl_1_data_1DC0;
    do {
        x = object->jointIdx[p->a];
        y = object->jointIdx[p->b];
        if (x != 0xFFFF && y != 0xFFFF) {
            object->mirror[x] = y;
            object->mirror[y] = x;
        }
        k += 4;
        p++;
    } while (lbl_1_data_1DC0[k / 4].a != 0xFFFF);
    mode = lbl_1_bss_68FC.character[lbl_1_bss_5F73];
    if (mode < 0x2C) {
        if (mode == 0x10) goto yes;
        goto no;
    }
    if (mode >= 0x30) goto no;
yes:
    q = lbl_1_data_1E18;
    goto done;
no:
    q = NULL;
done:
    if (q != NULL) {
        ChPair* r = q;
        for (; r->a != 0xFFFF; r++) {
            u16 x = object->jointIdx[r->a];
            u16 y = object->jointIdx[r->b];
            if (x != 0xFFFF && y != 0xFFFF) {
                object->mirror[x] = y;
                object->mirror[y] = x;
            }
        }
    }
}

#if !NONMATCHING
// Switch jump tables of fn_1_135C0; mwcc emits them itself once the function matches.
void* jumptable_1_data_F690[48] = {
    (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0xA90, (u8*)fn_1_135C0 + 0x112C,
    (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C,
    (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C,
    (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x10DC, (u8*)fn_1_135C0 + 0x112C,
    (u8*)fn_1_135C0 + 0x1104, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0xE14, (u8*)fn_1_135C0 + 0xAB8,
    (u8*)fn_1_135C0 + 0xAE0, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C,
    (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C,
    (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0x112C,
    (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0xA80, (u8*)fn_1_135C0 + 0xA80, (u8*)fn_1_135C0 + 0xA80,
    (u8*)fn_1_135C0 + 0xA80, (u8*)fn_1_135C0 + 0x10DC, (u8*)fn_1_135C0 + 0xB08, (u8*)fn_1_135C0 + 0x112C,
    (u8*)fn_1_135C0 + 0xE14, (u8*)fn_1_135C0 + 0xDF0, (u8*)fn_1_135C0 + 0x112C, (u8*)fn_1_135C0 + 0xAE0,
    (u8*)fn_1_135C0 + 0x1104, (u8*)fn_1_135C0 + 0x1104, (u8*)fn_1_135C0 + 0x1104, (u8*)fn_1_135C0 + 0x1104,
};
#endif

// .text:0x135C0 size:0x1150
// Challenge scene setup: builds the actor tables from the loaded files, binds animation/shape
// players, initialises the player row and starts the mode-specific controller.
// NONMATCHING ~60%: the original inlines fn_1_D13C and fn_1_D300 (three copies); pooled .bss base
// nmverify: lbl_1_bss_5F7C reached through a pooled base in original
#if NONMATCHING
void fn_1_135C0(void) {
    ActorObjectTable* main;
    ActorObjectTable* extra;
    CharActor* row = lbl_8036E548.actors;
    u32* header;
    u32* files;
    void* textures;
    struct ActorLayout* layout;
    void* geometry;
    void* skin;
    void* table;
    ChPlayer* entry;
    ActorObject* object;
    ShapeAnimPlayer* players = lbl_1_bss_60EC;
    u16 count;
    s32 i;
    s32 k;

    fn_80023B04(13);
    lbl_8036E548.slots = ActorObjectInitTable(1);
    lbl_1_bss_5F7C[1] = ActorObjectInitTable(1);
    lbl_1_bss_5F7C[0] = ActorObjectInitTable(5);
    memset(&lbl_1_bss_5F7C[3], 0, 0x118);
    lbl_8036E548.actors[0].kind = lbl_1_bss_68FC.character[0];

    for (i = 0; i < 1; i++) {
        // Relocate the player file header (5 offsets).
        header = (u32*)lbl_8036E548.actors[0].files;
        for (k = 0; k < 5; k++) {
            if (header[k] != 0) {
                header[k] += PTR_TO_U32(header); // TODO(port): in-place offset relocation of a big-endian disc header
            }
        }
        if (lbl_1_data_A978[lbl_1_bss_68FC.character[0]] >= 0) {
            files = lbl_1_bss_60A0;
            for (k = 0; k < 16; k++) {
                ((u32*)lbl_1_bss_60A0)[k] += PTR_TO_U32(lbl_1_bss_60A0); // TODO(port): same (in-place relocation)
            }
        }
        header = (u32*)lbl_8036E548.actors[0].files;
        textures = U32_TO_PTR(header[0]);
        layout = (struct ActorLayout*)U32_TO_PTR(header[1]);
        geometry = U32_TO_PTR(header[2]);
        skin = U32_TO_PTR(header[3]);
        convertTextureHeader(textures);
        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geometry, skin);
        haveActLayoutPointToGeoHeader(layout, geometry);
        fn_800BD190(geometry, textures);
        if (lbl_1_data_A978[lbl_1_bss_68FC.character[0]] >= 0) {
            files = lbl_1_bss_60A0;
            for (k = 0; k <= 7; k += 2) {
                struct ActorLayout* extraLayout = (struct ActorLayout*)U32_TO_PTR(((u32*)lbl_1_bss_60A0)[k]);
                void* extraGeometry = U32_TO_PTR(((u32*)lbl_1_bss_60A0)[k + 1]);
                LoadActorLayout(extraLayout);
                convertGeometryAndSknHeader(extraGeometry, NULL);
                haveActLayoutPointToGeoHeader(extraLayout, extraGeometry);
                fn_800BD190(extraGeometry, textures);
                fn_800BDC88(lbl_1_bss_5F7C[0], k / 2, k / 2, extraLayout, NULL, 0);
            }
            extra = lbl_1_bss_5F7C[0];
            for (k = 0; k < extra->count; k++) {
                ((ActorObjectTable*)lbl_1_bss_5F7C[0])->objects[k].animateBones = 1;
                CTRLSetTranslation(&((ActorObjectTable*)lbl_1_bss_5F7C[0])->objects[k].worldControl.base, (f32)k, 0.0f, 0.0f);
                CTRLSetRotation(&((ActorObjectTable*)lbl_1_bss_5F7C[0])->objects[k].worldControl.base, 0.0f, 0.0f, 0.0f);
            }
        }
    }

    // Make sure the selected animation group/index exist.
    for (i = 0; i < 1; i++) {
        entry = &lbl_1_bss_6940.player[lbl_1_bss_5F73];
        if (lbl_8036E548.actors[0].banks.b[entry->group] == NULL) {
            entry->group = 0;
            while (entry->group < 7 && lbl_8036E548.actors[0].banks.b[entry->group] == NULL) {
                entry->group++;
            }
        }
        entry = &lbl_1_bss_6940.player[lbl_1_bss_5F73];
        table = lbl_8036E548.actors[0].banks.b[entry->group];
        if (entry->seq >= ((ANIMBank*)table)->numSequences) {
            entry->seq = 0;
        }
    }
    main = lbl_8036E548.slots;
    fn_8002399C((struct ActorSlot*)&main->objects[0].actor, 0, 0, layout, table, skin);

    entry = &lbl_1_bss_6940.player[lbl_1_bss_5F73];
    table = lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[entry->group];
    object = &lbl_8036E548.slots->objects[lbl_1_bss_5F73];
    object->animBank = table;
    object->seqNum = entry->seq;
    object->time = 0.0f;
    object->setAnimation = 1;
    object->setTime = table != NULL;
    object->setSpeed = table != NULL;
    object->speed = 0.0f;

    // Shape (facial) animation players.
    lbl_1_bss_67B8[5] = U32_TO_PTR(((u32*)lbl_8036E548.actors[lbl_1_bss_5F73].files)[4]);
    if (lbl_1_bss_67B8[5] != NULL && lbl_1_bss_6940.player[lbl_1_bss_5F73].variant == 0) {
        fn_80025DDC(lbl_1_bss_67B8[5]);
        fn_80025C58(lbl_1_bss_67B8[5], (struct ShapeModel**)&lbl_8036E548.slots->objects[0].actor);
        if (lbl_1_data_A978[lbl_1_bss_68FC.character[0]] >= 0) {
            for (k = 0; k < 4; k++) {
                lbl_1_bss_67B8[6 + k] = U32_TO_PTR(((u32*)lbl_1_bss_60A0)[8 + k]);
                fn_80025DDC(lbl_1_bss_67B8[6 + k]);
                fn_80025C58(lbl_1_bss_67B8[6 + k], (struct ShapeModel**)&((ActorObjectTable*)lbl_1_bss_5F7C[0])->objects[k].actor);
                if (k + 1 == 4) {
                    players[k + 1].set = (ShapeAnimSet*)U32_TO_PTR(((u32*)lbl_1_bss_60A0)[15]);
                } else {
                    players[k + 1].set = (ShapeAnimSet*)U32_TO_PTR(((u32*)lbl_1_bss_60A0)[13 + k]);
                    fn_80025FFC(lbl_1_bss_67B8[6 + k], &players[k + 1]);
                    fn_80025EEC(&players[k + 1], 0, 0);
                }
                lbl_1_bss_67B8[1 + k] = &players[k + 1].state;
            }
            fn_1_D300(&lbl_8036E548.actors[lbl_1_bss_5F73]);
        }
        if (lbl_1_bss_3070.parts != 0) {
            players->set = (ShapeAnimSet*)U32_TO_PTR(((u32*)lbl_1_bss_60A0)[12]);
            fn_80025FFC(lbl_1_bss_67B8[5], players);
            fn_80025EEC(players, 0, 0);
            lbl_1_bss_67B8[0] = &players->state;
        }
    } else {
        lbl_1_bss_67B8[0] = NULL;
    }

    // Bone id -> bone index map.
    main = lbl_8036E548.slots;
    count = main->objects[0].actor->totalBones;
    memset(lbl_8036E548.actors[0].jointIdx, 0xFF, sizeof(lbl_8036E548.actors[0].jointIdx));
    for (i = 0; i < count; i++) {
        u16 id = lbl_8036E548.slots->objects[0].actor->boneArray[i]->boneID;
        if (id != 0xFFFF) {
            lbl_8036E548.actors[0].jointIdx[id] = i;
        }
    }
    fn_800BD548((struct DOListEntry*)&main->objects[0].actor, 3, lbl_8036E548.lights[0],
                lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
    lbl_8036E548.actors[0].pos.z = 0.0f;
    lbl_8036E548.actors[0].pos.y = 0.0f;
    lbl_8036E548.actors[0].pos.x = 0.0f;
    lbl_8036E548.actors[0].rot.z = 0.0f;
    lbl_8036E548.actors[0].rot.y = 0.0f;
    lbl_8036E548.actors[0].rot.x = 0.0f;
    main = lbl_8036E548.slots;
    CTRLSetTranslation(&main->objects[0].worldControl.base, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&lbl_8036E548.slots->objects[0].worldControl.base, 0.0f, 0.0f, 0.0f);
    main = lbl_8036E548.slots;
    main->objects[0].unk54 = lbl_1_rodata_73C0[0];
    main->objects[0].setSpeed = 1;
    fn_1_135C0_bone(main->objects[0].actor, row->jointIdx[3]);
    fn_1_135C0_bone(main->objects[0].actor, row->jointIdx[2]);
    fn_1_135C0_bone(main->objects[0].actor, row->jointIdx[1]);
    if (row->jointIdx[0x24] != 0xFFFF) {
        fn_800B2BA8(main->objects[0].actor, row->jointIdx[0x24], NULL, 0);
    }
    fn_1_135C0_bone(main->objects[0].actor, row->jointIdx[0x2e]);
    fn_800B2C08(lbl_8036E548.slots->objects[0].actor, 4);
    fn_8001FC4C(lbl_8036E548.active[0]);

    main = lbl_8036E548.slots;
    row->_004 = main->objects[0].actor;
    row->pos.x = 0.0f;
    row->pos.y = 0.0f;
    row->pos.z = lbl_1_rodata_73F8;
    row->_04C = lbl_1_rodata_73C0[0];
    row->mode[0] = 1;
    row->kind = lbl_1_bss_68FC.character[0];
    row->_25C = 1;
    row->_277 = 0xFF;
    main->objects[0].callback = fn_1_14888;
    if (lbl_1_bss_60A4[lbl_1_bss_68FC.character[0]] != 0) {
        fn_800B2B74(lbl_8036E548.slots->objects[0].actor, row->jointIdx[0x13]);
        fn_800B2B74(lbl_8036E548.slots->objects[0].actor, row->jointIdx[0x19]);
        fn_1_ECF8(lbl_1_bss_5F73, 0, 0);
        fn_800B2B74(lbl_8036E548.slots->objects[0].actor, row->jointIdx[0x24]);
    }

    // Mode-specific controller.
    main = lbl_8036E548.slots;
    switch ((s8)row->kind) {
    case 33:
    case 34:
    case 35:
    case 36:
        fn_80063010(row, &main->objects[0]);
        break;
    case 2:
        fn_800638B4(row, &main->objects[(s8)row->modelIndex]);
        lbl_1_bss_60E8 = NULL; // the callback returns 0
        break;
    case 19:
        fn_8004B7B4(row, &main->objects[(s8)row->modelIndex]);
        lbl_1_bss_60E8 = NULL; // the callback returns 0
        break;
    case 20:
    case 43:
        fn_800637BC(row, &main->objects[(s8)row->modelIndex]);
        lbl_1_bss_60E8 = NULL; // the callback returns 0
        break;
    case 38:
        main->objects[(s8)row->modelIndex].actor->tickFlag = 1;
        fn_1_D13C();
        fn_1_D300(&lbl_8036E548.actors[lbl_1_bss_5F73]);
        break;
    case 41:
        fn_800637D4(row, &main->objects[(s8)row->modelIndex]);
        lbl_1_bss_60E8 = NULL; // the callback returns 0
        // fallthrough
    case 18:
    case 40:
        fn_1_D13C();
        fn_1_D300(&lbl_8036E548.actors[lbl_1_bss_5F73]);
        break;
    case 14:
    case 37:
        lbl_1_bss_60E8 = fn_80052634(row, &main->objects[(s8)row->modelIndex].actor);
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        fn_80062ED4(row, &main->objects[(s8)row->modelIndex].actor);
        lbl_1_bss_60E8 = NULL; // fn_80062ED4 returns 0
        break;
    default:
        lbl_1_bss_60E8 = NULL;
        break;
    }
}
#endif

// .text:0x1347C size:0x144
void fn_1_1347C(void) {
    Mtx44 projection;
    lbl_1_bss_67E0.cam.eye.x = lbl_1_rodata_7394;
    lbl_1_bss_67E0.cam.eye.y = lbl_1_rodata_7480;
    lbl_1_bss_67E0.cam.eye.z = lbl_1_rodata_7394;
    lbl_1_bss_67E0.cam.target.x = lbl_1_rodata_7394;
    lbl_1_bss_67E0.cam.target.y = lbl_1_rodata_7394;
    lbl_1_bss_67E0.cam.target.z = lbl_1_rodata_73F8;
    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_800B806C(0, lbl_1_rodata_7484, lbl_1_rodata_7488, lbl_1_rodata_748C, lbl_1_rodata_7490,
                lbl_1_rodata_7494, lbl_1_rodata_7498, lbl_1_rodata_749C);
    lbl_1_bss_67E0.cam.mode = 0;
    lbl_1_bss_67E0.cam.dist = lbl_1_rodata_7394;
    lbl_1_bss_67E0.cam.pitch = 0;
    lbl_1_bss_67E0.cam.yaw = 0;
}

// .text:0x131E4 size:0x298
void fn_1_131E4(void) {
    ChallengeLightColor color = lbl_1_rodata_72F0;
    void** light0;
    void** light1;
    void** light2;
    void** light3;

    light0 = &lbl_8036E548.lights[0];
    LITAlloc(light0);
    light1 = &lbl_8036E548.lights[1];
    LITAlloc(light1);
    light2 = &lbl_8036E548.lights[2];
    LITAlloc(light2);
    light3 = &lbl_8036E548.lights[3];
    LITAlloc(light3);

    LITInitAttn(*light0, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*light0, lbl_1_rodata_7474, lbl_1_rodata_7478, lbl_1_rodata_7474);
    LITInitDir(*light0, lbl_1_rodata_7394, lbl_1_rodata_7394, lbl_1_rodata_7394);
    LITInitColor(*light0, LIT_COLOR(color));
    LITInitDir(*light0, lbl_1_rodata_747C, lbl_1_rodata_7394, lbl_1_rodata_747C);

    LITInitAttn(*light1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*light1, lbl_1_rodata_747C, lbl_1_rodata_7478, lbl_1_rodata_7394);
    LITInitDir(*light1, lbl_1_rodata_7394, lbl_1_rodata_7394, lbl_1_rodata_7394);
    LITInitColor(*light1, LIT_COLOR(color));

    LITInitAttn(*light2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*light2, lbl_1_rodata_7394, lbl_1_rodata_7478, lbl_1_rodata_7474);
    LITInitDir(*light2, lbl_1_rodata_7394, lbl_1_rodata_7394, lbl_1_rodata_7394);
    LITInitColor(*light2, LIT_COLOR(color));

    LITInitAttn(*light3, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*light3, lbl_1_rodata_7394, lbl_1_rodata_7478, lbl_1_rodata_747C);
    LITInitDir(*light3, lbl_1_rodata_7394, lbl_1_rodata_7394, lbl_1_rodata_7394);
    LITInitColor(*light3, LIT_COLOR(color));
}

// .text:0x12F8C size:0x258
// NONMATCHING ~85%: register allocation, pooled .bss base and the inlined fn_1_1073C differ
// nmverify: lbl_1_bss_67E0 reached through a pooled base in original
#if NONMATCHING
void fn_1_12F8C(void* tableArg, void* matrixArg) {
    ActorObjectTable* table = tableArg;
    Mtx transform;
    ActorObject* object;
    GameActor* actor;
    CharActor* row;
    GameBone* bone;
    u16 i;

    for (i = 0; i < table->count; i++) {
        object = &table->objects[i];
        if (object->actor == NULL) {
            continue;
        }
        if (object->setAnimation) {
            ACTSetAnimation(object->actor, object->animBank, 0, object->seqNum, 0.0f, object->speed);
        }
        if (object->setTime) {
            fn_800B4CA0(object->actor, object->time);
        }
        if (object->setSpeed) {
            fn_800B4C04(object->actor, object->unk54);
        }
        if (object->visFlags & 2) {
            fn_800B4AFC(object->actor, object->visFlags & 1);
        }
        Set_FUN_800b2b6c(object->actor, object->boneRemap);
        if (object->animateBones) {
            fn_800BDA24(object);
            if (lbl_1_bss_3081 != 0) {
                fn_1_1073C(&lbl_8036E548.actors[i]);
            }
            if (lbl_1_bss_308C != 0) {
                lbl_1_bss_308C = 0;
                // Debug bone dump. The original reuses the outer loop counter here.
                for (i = 0; i < object->actor->totalBones; i++) {
                    bone = object->actor->boneArray[i];
                    OSReport("#%3d %f %f %f\n", bone->boneID, bone->animCtrl.controlParams.srt.s.x,
                             bone->animCtrl.controlParams.srt.s.y, bone->animCtrl.controlParams.srt.s.z);
                }
            }
        }
        row = &lbl_8036E548.actors[i];
        PSMTXTrans(transform, row->pos.x, row->pos.y, row->pos.z);
        PSMTXConcat((f32(*)[4])matrixArg, transform, transform);
        actor = object->actor;
        actor->flags = (actor->flags & 0xFC) | fn_800B3C04(0, actor, transform);
        object = &table->objects[i];
        object->setAnimation = 0;
        object->setTime = 0;
        object->setSpeed = 0;
        object->visFlags &= 1;
    }
}
#endif

// .text:0x00012F18 size:0x74
void fn_1_12F18(struct ChDrawMtxNode* object) {
    fn_1_12820(lbl_8036E548.slots, object->m);
    if (lbl_1_data_A978[lbl_1_bss_68FC.character[0]] >= 0) {
        fn_800BD670(lbl_1_bss_5F7C[0], object->m);
    }
}

// .text:0x129D0 size:0x548
// NONMATCHING ~85%: the original inlines fn_1_D4BC, fn_1_11C98 and fn_1_D590 and uses the pooled .bss/.data bases
// nmverify: fn_80024FA4 original calls it once per shape branch; here once after picking the shape
// nmverify: lbl_1_bss_5F7C lbl_1_bss_68FC lbl_1_data_A938 lbl_1_data_A978 lbl_1_data_ABA4 lbl_1_data_AC9C reached through a pooled base in original
// nmverify:  inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_1_129D0(void) {
    CharActor* row;
    ActorObjectTable* table;
    ActorObjectTable* challengeTable;
    f32 speed;
    s32 k;

    fn_1_D4BC();
    fn_1_11C98();
    row = lbl_8036E548.actors;
    table = lbl_8036E548.slots;
    CTRLSetTranslation(&table->objects[0].worldControl.base, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&table->objects[0].worldControl.base, lbl_1_rodata_7460 * row->rot.x,
                    lbl_1_rodata_7460 * row->rot.y, lbl_1_rodata_7460 * row->rot.z);
    if (lbl_1_bss_5F68 == 0) {
        speed = lbl_1_data_ABA4;
    } else {
        speed = lbl_1_bss_5F64;
    }
    table->objects[0].unk54 = speed;
    table->objects[0].setSpeed = 1;
    if (lbl_1_bss_67B8[0] != NULL) {
        ((ShapeAnimState*)lbl_1_bss_67B8[0])->speed = speed;
    }
    if (speed != 0.0f && lbl_1_bss_3215 != 0) {
        GameActor* actor = table->objects[0].actor;
        u16 count = actor->totalBones;
        s32 i;
        f32 frame;
        ChPlayer* entry;

        for (i = 0; i < count; i++) {
            struct ANIMPipe* anim = actor->boneArray[i]->animPipe;
            if (anim != NULL && anim->currentTrack != NULL) {
                break;
            }
        }
        if (i < count) {
            frame = actor->boneArray[i]->animPipe->time;
        } else {
            frame = 0.0f;
        }
        entry = &lbl_1_bss_6940.player[lbl_1_bss_5F73];
        fn_1_D590(row, lbl_1_data_A938[entry->group] + entry->seq, frame);
    }
    lbl_1_bss_5F64 = 0.0f;
    if (lbl_1_bss_5F5C == 0) {
        challengeTable = lbl_1_bss_5F7C[0];
        for (k = 0; k < 4; k++) {
            struct ShapeModel** model;
            void* shape;
            if (lbl_1_bss_67B8[5 + k] == NULL || lbl_1_bss_67B8[k] == NULL) {
                continue;
            }
            ((ShapeAnimState*)lbl_1_bss_67B8[k])->speed = speed;
            if (fn_80024DB0(lbl_1_bss_67B8[k]) != 0 && lbl_1_bss_67B8[k] != NULL) {
                ((ShapeAnimState*)lbl_1_bss_67B8[k])->dirtyB = 3;
            }
            if (k == 0) {
                model = (struct ShapeModel**)&lbl_8036E548.slots->objects[0].actor;
            } else if (k == 3) {
                model = (struct ShapeModel**)&challengeTable->objects[3].actor;
            } else {
                model = (struct ShapeModel**)&challengeTable->objects[k - 1].actor;
            }
            if (k == 0 || lbl_1_bss_5F69 == 0) {
                shape = lbl_1_bss_67B8[5 + k];
            } else if (k == 2) {
                shape = lbl_1_bss_67B8[5 + k - 1];
            } else {
                shape = lbl_1_bss_67B8[5 + k + 1];
            }
            fn_80024FA4(model, shape, lbl_1_bss_67B8[k], -1);
        }
        if (lbl_1_bss_67B8[0] != NULL) {
            memcpy(&lbl_8036E548.actors[lbl_1_bss_5F73].part->player.state, lbl_1_bss_67B8[0], 0x20);
        }
    }
    PSMTXCopy(lbl_1_bss_68FC.view, lbl_1_data_AC9C[lbl_803CBBC0[0]].m);
    fn_800A7D4C(7, &lbl_1_data_AC9C[lbl_803CBBC0[0]]);
    if (lbl_1_data_A978[lbl_1_bss_68FC.character[0]] >= 0) {
        fn_800BD8C4(lbl_1_bss_5F7C[0], lbl_1_bss_68FC.view);
    }
    table = lbl_8036E548.slots;
    table->objects[0].animateBones = 1;
    fn_1_12F8C(lbl_8036E548.slots, lbl_1_bss_68FC.view);
    lbl_8036E548.slots->objects[0].animateBones = (lbl_1_bss_3080 == 0) & (lbl_1_bss_5F73 == 0);
    if (lbl_8036E548._3083[0] != 0) {
        u8 player = lbl_8036E548._3083[1];
        fn_80038EC4((struct CharModelObj*)(&lbl_8036E548.actors[player]),
                    (struct Model**)&lbl_8036E548.slots->objects[player].actor, 0);
    }
    fn_8003414C(&lbl_1_bss_67E0.cam);
}
#endif

// .text:0x12820 size:0x1B0
// NONMATCHING ~96%: saved-register allocation only (table/matrix/object/base rotated)
#if NONMATCHING
void fn_1_12820(void* tableArg, void* matrixArg) {
    u16 i;
    ActorObject* object;
    f32 (*matrix)[4] = matrixArg;
    CharActor* row;
    u8 lastAlpha = 0xFF;
    ActorObjectTable* table = tableArg;
    u8 alpha;
    Mtx transform;
    Mtx44 projection;
    GXColor color;

    color = lbl_1_rodata_72FC;
    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    for (i = 0; i < table->count; i++) {
        object = &table->objects[i];
        row = &lbl_8036E548.actors[i];
        if (object->actor == NULL) continue;
        object->actor->flags = 0xFF;
        if (object->animateBones == 0) continue;
        alpha = row->_277;
        if (lastAlpha != alpha) {
            lastAlpha = alpha;
            if (0xFF - alpha != 0) {
                color.a = alpha;
                if (alpha == 0) continue;
                fn_800BD2CC(1, color);
            } else {
                color.a = 0xFF;
                fn_800BD2CC(0, color);
            }
        }
        PSMTXTrans(transform, row->pos.x, row->pos.y, row->pos.z);
        PSMTXConcat(matrix, transform, transform);
        fn_800BDA94(object, transform);
    }
}
#endif

// .text:0x126CC size:0x154
// NONMATCHING ~85%: same instructions, float/int load scheduling differs (49 diff lines)
#if NONMATCHING
void fn_1_126CC(void) {
    CharActor* row = &lbl_8036E548.actors[lbl_1_bss_5F73];
    f32 x = row->pos.x;
    f32 y = row->pos.y;
    f32 z = row->pos.z;
    x += (f32)lbl_803C77B8.stickX / 768.0f;
    z += (f32)lbl_803C77B8.stickY / 768.0f;
    y += (f32)lbl_803C77B8.triggerR / 768.0f;
    y -= (f32)lbl_803C77B8.triggerL / 768.0f;
    lbl_1_data_AD0C[1] -= 0.001953125f * (f32)lbl_803C77B8.substickX;
    lbl_1_data_AD0C[0] -= 0.001953125f * (f32)lbl_803C77B8.substickY;
    row->pos.x = x;
    row->pos.y = y;
    row->pos.z = z;
    row->rot.x = lbl_1_data_AD0C[0];
    row->rot.y = lbl_1_data_AD0C[1];
    row->rot.z = lbl_1_data_AD0C[2];
}
#endif

// .text:0x121D4 size:0x4F8
void fn_1_121D4(ChViewCam* camera) {
    switch (camera->mode) {
    case 0:
        fn_1_11F08(camera);
        break;
    case 1:
        fn_1_11D00(camera);
        break;
    }
    fn_80011640(camera->view, camera->view);
    PSVECSubtract(&camera->eye, &camera->target, &camera->light.direction);
    PSVECNormalize(&camera->light.direction, &camera->light.direction);
    fn_80052968();
}

// .text:0x11F08 size:0x2CC
void fn_1_11F08(ChViewCam* camera) {
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    Vec angle;
    Vec pos;
    f32 c;
    f32 s;
    u8* view;

    pos = lbl_1_rodata_7300;
    if (!(lbl_803C77B8._00 & 0x10)) {
        camera->pitch -= lbl_803C77B8.substickY * 4;
        camera->yaw += lbl_803C77B8.substickX * 4;
        camera->strafe = (f32)lbl_803C77B8.stickX / lbl_1_rodata_7454;
        camera->dist = (f32)lbl_803C77B8.stickY * lbl_1_rodata_7448;
        camera->eye.y += (f32)lbl_803C77B8.triggerR * lbl_1_rodata_744C;
        camera->eye.y -= (f32)lbl_803C77B8.triggerL * lbl_1_rodata_744C;
    }
    angle.x = camera->pitch;
    angle.y = camera->yaw;
    angle.z = lbl_1_rodata_7394;
    PSVECScale(&angle, lbl_1_rodata_7450, &angle);
    PSMTXRotRad(rotX, 'X', angle.x);
    PSMTXRotRad(rotY, 'Y', angle.y);
    s = rotY[0][2];
    c = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &pos, &camera->target);
    camera->eye.x += camera->dist * s - camera->strafe * c;
    camera->eye.z += camera->dist * c + camera->strafe * s;
    camera->target.x += camera->eye.x;
    camera->target.y += camera->eye.y;
    camera->target.z += camera->eye.z;
    makeLookAtMatrix(camera->view, &camera->eye, &lbl_1_data_AD18, &camera->target);
    view = (u8*)fn_80052768_getCamera(0);
    memcpy(view + 0x70, &camera->eye, 0xC);
    memcpy(view + 0x7C, &camera->target, 0xC);
}

// .text:0x11D00 size:0x208
void fn_1_11D00(ChViewCam* camera) {
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    Vec angle;
    Vec pos;

    pos = lbl_1_rodata_730C;
    if (!(lbl_803C77B8._00 & 0x10)) {
        camera->pitch -= lbl_803C77B8.substickY * 4;
        camera->yaw += lbl_803C77B8.substickX * 4;
        camera->dist += (f32)lbl_803C77B8.stickY * lbl_1_rodata_7448;
        camera->target.y += (f32)lbl_803C77B8.triggerR * lbl_1_rodata_744C;
        camera->target.y -= (f32)lbl_803C77B8.triggerL * lbl_1_rodata_744C;
    }
    angle.x = camera->pitch;
    angle.y = camera->yaw;
    angle.z = lbl_1_rodata_7394;
    PSVECScale(&angle, lbl_1_rodata_7450, &angle);
    PSMTXRotRad(rotX, 'X', angle.x);
    PSMTXRotRad(rotY, 'Y', angle.y);
    PSMTXConcat(rotX, rotY, rot);
    pos.z = -camera->dist;
    PSMTXMultVec(rot, &pos, &pos);
    PSVECAdd(&pos, &camera->target, &camera->eye);
    PSMTXMultVec(rot, &lbl_1_data_AD24, &pos);
    makeLookAtMatrix(camera->view, &camera->eye, &pos, &camera->target);
}

// .text:0x00011C98 size:0x68
void fn_1_11C98(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(lbl_8036E548.lights[i], lbl_1_bss_68FC.view);
    }
}

// .text:0x11714 size:0x584
// Draws a cube textured with the current screen copy (projected UVs) plus its wireframe.
void fn_1_11714(struct ChDrawMtxNode* object) {
    Mtx44 projection2;
    f32 uv[8][2];
    Mtx44 projection;
    s32 i;
    s32 face;
    s32 corner;

    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    GXLoadPosMtxImm(object->m, 0);
    GXSetCurrentMtx(0);
    GXSetColorUpdate(1);
    C_MTXFrustum(projection2, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    fn_800245EC(projection2, lbl_1_bss_68FC.view, lbl_1_data_AD30, &uv[0][0], 8, 1);
    SetDisplayStateTexture(fn_80039AB4(), 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, 0x3C, 0, 0x7D);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, 0, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXBegin(GX_QUADS, GX_VTXFMT0, 24);
    for (i = 0; i < 24; i++) {
        corner = lbl_1_data_AD90[i / 4][i % 4];
        GXPosition3f32(lbl_1_data_AD30[corner].x, lbl_1_data_AD30[corner].y, lbl_1_data_AD30[corner].z);
        GXColor1u32(lbl_1_data_ADA8[i / 4]);
        GXTexCoord2f32(uv[corner][0], uv[corner][1]);
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    for (face = 0; face < 6; face++) {
        u8* f = lbl_1_data_AD90[face];
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 6);
        GXWGFifo.f32 = lbl_1_data_AD30[f[0]].x;
        GXWGFifo.f32 = lbl_1_data_AD30[f[0]].y;
        GXWGFifo.f32 = lbl_1_data_AD30[f[0]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = lbl_1_data_AD30[f[1]].x;
        GXWGFifo.f32 = lbl_1_data_AD30[f[1]].y;
        GXWGFifo.f32 = lbl_1_data_AD30[f[1]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = lbl_1_data_AD30[f[2]].x;
        GXWGFifo.f32 = lbl_1_data_AD30[f[2]].y;
        GXWGFifo.f32 = lbl_1_data_AD30[f[2]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = lbl_1_data_AD30[f[3]].x;
        GXWGFifo.f32 = lbl_1_data_AD30[f[3]].y;
        GXWGFifo.f32 = lbl_1_data_AD30[f[3]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = lbl_1_data_AD30[f[0]].x;
        GXWGFifo.f32 = lbl_1_data_AD30[f[0]].y;
        GXWGFifo.f32 = lbl_1_data_AD30[f[0]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = lbl_1_data_AD30[f[2]].x;
        GXWGFifo.f32 = lbl_1_data_AD30[f[2]].y;
        GXWGFifo.f32 = lbl_1_data_AD30[f[2]].z;
        GXColor1u32(0xFFFFFFFF);
    }
}

// .text:0x000116EC size:0x28
void fn_1_116EC(void* object) {
    SetDisplayStateTexture(object, 0, 0);
}

// .text:0x1125C size:0x4B8
// Draws the floor: a green line grid, or the selected floor texture tiled lbl_1_bss_5F60 times.
void fn_1_1125C(struct ChDrawMtxNode* object) {
    Mtx44 projection;
    s32 i;
    f32 t;

    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    GXLoadPosMtxImm(object->m, 0);
    GXSetCurrentMtx(0);
    GXSetColorUpdate(1);
    if (lbl_1_bss_5F62 < 0) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetNumTevStages(1);
        GXSetNumChans(1);
        GXSetNumTexGens(0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetChanCtrl(GX_COLOR0, 0, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
        for (i = -24; i < 25; i++) {
            t = i;
            GXBegin(GX_LINES, GX_VTXFMT0, 4);
            GXPosition3f32(-24.0f, 0.0f, t);
            GXColor4u8(0, 255, 0, 200);
            GXPosition3f32(24.0f, 0.0f, t);
            GXColor4u8(0, 255, 0, 200);
            GXPosition3f32(t, 0.0f, -24.0f);
            GXColor4u8(0, 255, 0, 200);
            GXPosition3f32(t, 0.0f, 24.0f);
            GXColor4u8(0, 255, 0, 200);
        }
        return;
    }
    SetDisplayStateTexture((struct TexImage*)(lbl_1_bss_60E4 + lbl_1_bss_5F62 * 0x20 + 4), 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, 0x3C, 0, 0x7D);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, 0, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-24.0f, 0.0f, -24.0f);
    GXColor1u32(0xFFFFFFFF);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(-24.0f, 0.0f, 24.0f);
    GXColor1u32(0xFFFFFFFF);
    GXTexCoord2u16(0, lbl_1_bss_5F60);
    GXPosition3f32(24.0f, 0.0f, 24.0f);
    GXColor1u32(0xFFFFFFFF);
    GXTexCoord2u16(lbl_1_bss_5F60, lbl_1_bss_5F60);
    GXPosition3f32(24.0f, 0.0f, -24.0f);
    GXColor1u32(0xFFFFFFFF);
    GXTexCoord2u16(lbl_1_bss_5F60, 0);
}

// .text:0x10E2C size:0x430
// Draws a small axis gizmo (22 line vertices) at the given model matrix.
// NONMATCHING ~99%: one stw/lis scheduling swap near the second constant group
#if NONMATCHING
void fn_1_10E2C(Mtx model, Mtx view, u32 colorX, u32 colorY, u32 colorZ) {
    GXCullMode cullMode;
    Mtx matrix;

    GXGetCullMode(&cullMode);
    PSMTXConcat(view, model, matrix);
    GXLoadPosMtxImm(matrix, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(0, 4);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetChanCtrl(0, 0, 1, 1, 0, 0, 2);
    GXSetChanCtrl(2, 0, 1, 1, 0, 0, 2);
    GXSetBlendMode(1, 4, 5, 3);
    GXSetCullMode(0);
    GXSetZMode(1, 7, 1);
    GXSetLineWidth(7, 0);
    GXBegin(0xA8, 0, 0x16);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7428;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_742C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7430;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_742C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7428;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_742C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7428;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7430;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7428;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7428;
    GXColor1u32(colorX);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorY);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7434;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorY);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7438;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorY);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7434;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorY);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_743C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorY);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7434;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorY);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorZ);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7434;
    GXColor1u32(colorZ);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7438;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorZ);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7434;
    GXColor1u32(colorZ);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_743C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXColor1u32(colorZ);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7394;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7434;
    GXColor1u32(colorZ);
    GXSetLineWidth(6, 0);
    GXSetCullMode(cullMode);
    GXSetZMode(1, 3, 1);
}
#endif

// .text:0x10CEC size:0x140
void fn_1_10CEC(struct ChDrawMtxNode* object) {
    Mtx buffer; // bone matrix
    Mtx matrix;
    CharMgr* scene;
    s32 i;
    s32 k;
    u32 a;
    u32 b;
    u32 c;
    if (lbl_1_data_ABA8 == 0) {
        CharMgr* row = CHARMGR_AT(lbl_1_bss_5F73);
        PSMTXTrans(matrix, row->actors[0].pos.x, row->actors[0].pos.y, row->actors[0].pos.z);
        PSMTXConcat(object->m, matrix, matrix);
        scene = &lbl_8036E548;
        for (i = 0; k = lbl_1_bss_5F73, i < scene->slots->objects[k].actor->totalBones; i++) {
            if ((u32)i != lbl_1_bss_5F6C) {
                a = 0x80008080;
                b = 0x80800080;
                c = 0x808080;
            } else {
                u8 f = lbl_1_bss_3090;
                lbl_1_bss_3090 = f + 1;
                if (f & 0x20) {
                    a = 0xFF8080FF;
                    b = 0x80FF80FF;
                    c = 0x8080FFFF;
                } else {
                    a = -1;
                    b = -1;
                    c = -1;
                }
            }
            fn_800B2C88(scene->slots->objects[k].actor, (u16)i, buffer);
            fn_1_10E2C(buffer, matrix, a, b, c);
        }
    }
}

// .text:0x10ACC size:0x220
void fn_1_10ACC(f32 (*matrix)[4], f32* position, void* unused, u8* color, f32 size) {
    GXCullMode cullMode;
    GXGetCullMode(&cullMode);
    GXLoadPosMtxImm(matrix, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(0, 4);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetChanCtrl(0, 0, 1, 1, 0, 0, 2);
    GXSetChanCtrl(2, 0, 1, 1, 0, 0, 2);
    GXSetBlendMode(1, 4, 5, 3);
    GXSetCullMode(0);
    GXSetZMode(1, 7, 1);
    GXSetLineWidth(10, 0);
    GXBegin(0xA8, 0, 2);
    GXPosition3f32(position[0], position[1], position[2]);
    GXColor4u8(color[0], color[1], color[2], color[3]);
    GXPosition3f32(position[0] + size, position[1] + size, position[2] + size);
    GXColor4u8(color[0], color[1], color[2], color[3]);
    GXSetLineWidth(6, 0);
    GXSetCullMode(cullMode);
    GXSetZMode(1, 3, 1);
}

// .text:0x00010AA4 size:0x28
void fn_1_10AA4(ActorObject* object, f32 value) {
    object->unk54 = value;
    object->setSpeed = 1;
    if (lbl_1_bss_67B8[0] != 0) {
        ((ShapeAnimState*)lbl_1_bss_67B8[0])->speed = value;
    }
}

// .text:0x107B8 size:0x2EC
// NONMATCHING ~75%: the original inlines fn_1_D300 (itself NONMATCHING), so this calls it
#if NONMATCHING
void fn_1_107B8(void) {
    ChPlayer* entry = &lbl_1_bss_6940.player[lbl_1_bss_5F73];
    CharActor* row = &lbl_8036E548.actors[lbl_1_bss_5F73];
    u8 group = entry->group;
    u8 index;
    void* table;
    ActorObject* object;

    row->_278 = group == 0;
    switch (group) {
    case 0:
        row->index = 9;
        break;
    case 1:
        row->index = 10;
        break;
    case 2:
        row->index = 2;
        break;
    case 3:
        row->index = 0;
        break;
    case 4:
        row->index = 1;
        break;
    default:
        row->index = 9;
        break;
    }
    index = entry->seq;
    row->anim[0] = lbl_1_data_A938[group] + index;
    table = row->banks.b[group];
    object = &lbl_8036E548.slots->objects[lbl_1_bss_5F73];
    object->animBank = table;
    object->seqNum = index;
    object->time = 0.0f;
    object->setAnimation = 1;
    object->setTime = table != NULL;
    object->setSpeed = table != NULL;
    object->speed = 0.0f;
    fn_1_ECF8(lbl_1_bss_5F73, lbl_1_bss_6940.player[lbl_1_bss_5F73].group, lbl_1_bss_5F69);
    lbl_1_bss_5F5C = 0;
    fn_1_D300(&lbl_8036E548.actors[lbl_1_bss_5F73]);
    fn_800B0A14_removeQueue(NULL); // argument unused (stale r3 in the original)
}
#endif

// .text:0x0001073C size:0x7C
void fn_1_1073C(CharActor* object) {
    Vec displacement;
    displacement.x = lbl_1_bss_67E0.cam.eye.x - object->pos.x;
    displacement.y = lbl_1_bss_67E0.cam.eye.y - object->pos.y;
    displacement.z = lbl_1_bss_67E0.cam.eye.z - object->pos.z;
    fn_80026134(0, &displacement);
    fn_80026130(0, lbl_1_data_ADC4, lbl_1_data_ADC0[0]);
}

// .text:0x000106C4 size:0x78
void fn_1_106C4(void) {
    s32 buttons = lbl_803C77B8._04;
    if (buttons & 8) return;
    if (buttons & 4) return;
    if (buttons & 1) {
        lbl_1_bss_3081 ^= 1;
        return;
    }
    if (buttons & 2) {
        lbl_1_bss_3081 ^= 1;
        return;
    }
    if (!(buttons & 0x100) && (buttons & 0x200)) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
}

void fn_1_106B4(void) {
    lbl_1_bss_3098 = 0;
}

void* fn_1_106A4(void) {
    return lbl_1_bss_3098;
}

void fn_1_10670(void) {
    ChTaskHeader* object = fn_800B0A5C_insertQueue((void*)fn_1_10560, 11);
    object->result = 0;
}

// .text:0x10560 size:0x110
void fn_1_10560(TASK_PARAM(void* object)) {
    switch (CH_TASK->result) {
    case 0:
        lbl_1_bss_3094 = (void*)ARAMTransfer(&lbl_1_data_ADE0, 0, 0, 0);
        CH_TASK->result = 1;
        break;
    case 1:
        if ((s32)lbl_803C6CF8.idle == 1) {
            u8* data = (u8*)lbl_1_bss_3094;
            lbl_1_bss_3098 = (struct TexArchive*)(data + *(u32*)data);
            convertTextureHeader(lbl_1_bss_3098);
            lbl_1_bss_60E4 = ARAMTransfer(&lbl_1_data_A940, 0, 1, 0);
            CH_TASK->result = 2;
        }
        break;
    case 2:
        if ((s32)lbl_803C6CF8.idle == 1) {
            convertTextureHeader(lbl_1_bss_60E4);
            REMOVE_QUEUE_NOARG();
        }
        break;
    }
}

// .text:0x00010458 size:0x108
void fn_1_10458(void) {
    s32 cursor;
    s32 buttons;
    if (lbl_1_bss_3098 == NULL) {
        if (lbl_1_bss_3094 == NULL) {
            ChTaskHeader* object = fn_800B0A5C_insertQueue((void*)fn_1_10560, 11);
            object->result = 0;
        }
        return;
    }
    buttons = lbl_803C77B8._04;
    if (buttons & 8) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C--;
        } else {
            lbl_1_bss_307C = 6;
        }
        return;
    }
    if (buttons & 4) {
        cursor = lbl_1_bss_307C + 1;
        lbl_1_bss_307C = cursor;
        if (cursor == 7) {
            lbl_1_bss_307C = 0;
        }
        return;
    }
    if (!(buttons & 1) && !(buttons & 2)) {
        if (buttons & 0x100) {
            lbl_1_bss_5F71 += lbl_1_bss_307C + 1;
            lbl_1_bss_307C = 0;
            return;
        }
        if (buttons & 0x200) {
            lbl_1_bss_307C = 0;
            lbl_1_bss_5F71 = 1;
        }
    }
}

// .text:0x10044 size:0x414
// NONMATCHING ~85%: the original reaches the emitter settings through the pooled .data base
// nmverify: lbl_1_data_ADE0 reached through a pooled base in original
#if NONMATCHING
void fn_1_10044(void) {
    ChallengeEmitterParams* params = &lbl_1_data_ADF0;
    u16 buttons = lbl_803C77B8._04;
    s32 step;
    Mtx rotX;
    Mtx rotY;

    if (buttons & 8) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C--;
        } else {
            lbl_1_bss_307C = 4;
        }
    } else if (buttons & 4) {
        if (++lbl_1_bss_307C == 5) {
            lbl_1_bss_307C = 0;
        }
    } else if (buttons & 1) {
        if (lbl_803C77B8._00 & 0x400) {
            step = 10;
        } else if (lbl_803C77B8._00 & 0x800) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            params->count -= step;
            if (params->count < 0) {
                params->count = 0;
            }
            break;
        case 2:
            params->speed -= 0.001f * step;
            if (params->speed < 0.001f) {
                params->speed = 0.001f;
            }
            break;
        case 3:
            params->pitch -= step;
            if (params->pitch < 1) {
                params->pitch = 1;
            }
            break;
        case 4:
            params->yaw = (params->yaw - step) & 0xFFF;
            break;
        }
    } else if (buttons & 2) {
        if (lbl_803C77B8._00 & 0x400) {
            step = 10;
        } else if (lbl_803C77B8._00 & 0x800) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            params->count += step;
            if (params->count >= 0x1400) {
                params->count = 0x1400;
            }
            break;
        case 2:
            params->speed += 0.001f * step;
            if (params->speed > 10.0f) {
                params->speed = 10.0f;
            }
            break;
        case 3:
            params->pitch += step;
            if (params->pitch > 0x200) {
                params->pitch = 0x200;
            }
            break;
        case 4:
            params->yaw = (params->yaw + step) & 0xFFF;
            break;
        }
    } else if (lbl_803C77B8._00 & 0x100) {
        if (lbl_803C77B8._02 & 0x100) {
            params->dir.x = 0.0f;
            params->dir.y = -1.0f;
            params->dir.z = 0.0f;
            PSMTXRotRad(rotX, 'x', (f32)(0.01745329238474369 * ((360.0 * params->pitch) / 4096.0)));
            PSMTXRotRad(rotY, 'y', (f32)(0.01745329238474369 * ((360.0 * params->yaw) / 4096.0)));
            PSMTXConcat(rotY, rotX, rotX);
            PSMTXMultVec(rotX, &params->dir, &params->dir);
            fn_800330CC(params->count, params->type, &params->pos, &params->dir, params->unkC, NULL, params->speed, params->unk10);
        }
    } else if (buttons & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}
#endif

#if !NONMATCHING
// Switch jump tables of fn_1_FB98; mwcc emits them itself once the function matches.
void* jumptable_1_data_F650[8] = {
    (u8*)fn_1_FB98 + 0x2BC, (u8*)fn_1_FB98 + 0x2DC, (u8*)fn_1_FB98 + 0x320, (u8*)fn_1_FB98 + 0x360,
    (u8*)fn_1_FB98 + 0x3A0, (u8*)fn_1_FB98 + 0x3E0, (u8*)fn_1_FB98 + 0x420, (u8*)fn_1_FB98 + 0x430,
};
void* jumptable_1_data_F670[8] = {
    (u8*)fn_1_FB98 + 0xCC, (u8*)fn_1_FB98 + 0xE8, (u8*)fn_1_FB98 + 0x12C, (u8*)fn_1_FB98 + 0x16C,
    (u8*)fn_1_FB98 + 0x1AC, (u8*)fn_1_FB98 + 0x1EC, (u8*)fn_1_FB98 + 0x22C, (u8*)fn_1_FB98 + 0x24C,
};
#endif

// .text:0xFB98 size:0x4AC
// NONMATCHING ~90%: the original reaches the parameters through the pooled .data base
// nmverify: lbl_1_data_D838 reached through a pooled base in original
#if NONMATCHING
void fn_1_FB98(void) {
    ChallengeFxParams* params = &lbl_1_data_F084;
    u16 buttons = lbl_803C77B8._04;
    s32 step;

    if (buttons & 8) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C -= 1;
        } else {
            lbl_1_bss_307C = 7;
        }
    } else if (buttons & 4) {
        if (++lbl_1_bss_307C == 8) {
            lbl_1_bss_307C = 0;
        }
    } else if (buttons & 1) {
        if (lbl_803C77B8._00 & 0x400) {
            step = 10;
        } else if (lbl_803C77B8._00 & 0x800) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            if (--lbl_1_bss_309C < 0) {
                lbl_1_bss_309C = 13;
            }
            break;
        case 1:
            params->scale -= 0.1 * step;
            break;
        case 2:
            params->values[0] -= 0.0001 * step;
            break;
        case 3:
            params->values[1] -= 0.0001 * step;
            break;
        case 4:
            params->values[2] -= 0.0001 * step;
            break;
        case 5:
            params->values[3] -= 0.0001 * step;
            break;
        case 6:
            params->count -= step;
            if (params->count < 1) {
                params->count = 1;
            }
            break;
        case 7:
            params->alpha -= step;
            if (params->alpha < 0) {
                params->alpha = 0;
            }
            break;
        }
    } else if (buttons & 2) {
        if (lbl_803C77B8._00 & 0x400) {
            step = 10;
        } else if (lbl_803C77B8._00 & 0x800) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            if (++lbl_1_bss_309C >= 14) {
                lbl_1_bss_309C = 0;
            }
            break;
        case 1:
            params->scale += 0.1 * step;
            break;
        case 2:
            params->values[0] += 0.0001 * step;
            break;
        case 3:
            params->values[1] += 0.0001 * step;
            break;
        case 4:
            params->values[2] += 0.0001 * step;
            break;
        case 5:
            params->values[3] += 0.0001 * step;
            break;
        case 6:
            params->count += step;
            break;
        case 7:
            params->alpha += step;
            if (params->alpha > 255) {
                params->alpha = 255;
            }
            break;
        }
    } else if (lbl_803C77B8._00 & 0x100) {
        if (lbl_803C77B8._02 & 0x100) {
            lbl_1_bss_30A0 = (lbl_1_bss_30A0 + 1) % 16;
        }
    } else if (buttons & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}
#endif

// .text:0xF798 size:0x400
void fn_1_F798(void* paramsArg, void* typesArg, s32 count) {
    s32* p = paramsArg;
    u8* types = typesArg;
    s32 s;
    s32 m;
    s32 l;
    u16 buttons;
    u8 t;
    s32 v;

    if (lbl_803C77B8._00 & 0x400) {
        s = 10;
        m = 100;
        l = 10000;
    } else if (lbl_803C77B8._00 & 0x800) {
        s = 20;
        l = 1000000;
        m = 10000;
    } else {
        s = 1;
        l = 100000;
        m = 1000;
    }
    buttons = lbl_803C77B8._04;
    if (buttons & 8) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C--;
        } else {
            lbl_1_bss_307C = count - 1;
        }
    } else if (buttons & 4) {
        if (++lbl_1_bss_307C == count) {
            lbl_1_bss_307C = 0;
        }
    } else if (buttons & 1) {
        t = types[lbl_1_bss_307C];
        switch (t) {
        case 0:
            break;
        case 1:
            p[t] = (p[t] + 41) % 42;
            break;
        case 2:
            p[2] -= s;
            if (p[2] < 1) {
                p[2] = 1;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
        case 20:
            if (p[t] - m > 0) {
                p[t] -= m;
            }
            break;
        case 6:
            p[6] -= s;
            if (p[6] < 1) {
                p[6] = 1;
                if (p[7] > p[6]) {
                    p[7] = p[6];
                }
            }
            break;
        case 7:
        case 11:
        case 21:
        case 22:
            p[t] -= s;
            if (p[types[lbl_1_bss_307C]] < 0) {
                p[types[lbl_1_bss_307C]] = 0;
            }
            break;
        case 10:
            p[t] ^= 1;
            break;
        case 12:
        case 13:
            p[t] -= l;
            if (p[types[lbl_1_bss_307C]] < 0) {
                p[types[lbl_1_bss_307C]] = 0;
            }
            break;
        case 23:
        case 24:
            p[t] -= m;
            break;
        case 14:
        case 15:
            p[t] -= l;
        case 16:
            v = ((p[16] >> 8) & 0xFF);
            v -= s;
            if (v < 0) {
                v = 0;
            }
            p[16] = v * 0x01010100;
            break;
        case 17:
        case 18:
        case 19:
            break;
        }
    } else if (buttons & 2) {
        t = types[lbl_1_bss_307C];
        switch (t) {
        case 0:
            break;
        case 1:
            p[t] = (p[t] + 1) % 42;
            break;
        case 2:
            p[2] += s;
            break;
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
        case 20:
            p[t] += m;
            break;
        case 6:
            p[6] += s;
            break;
        case 7:
            p[7] += s;
            if (p[7] > p[6]) {
                p[7] = p[6];
            }
            break;
        case 11:
        case 21:
            p[t] += s;
            if (p[types[lbl_1_bss_307C]] > 255) {
                p[types[lbl_1_bss_307C]] = 255;
            }
            break;
        case 22:
            p[t] += s;
            break;
        case 10:
            p[t] ^= 1;
            break;
        case 12:
        case 13:
            p[t] += l;
            break;
        case 23:
        case 24:
            p[t] += m;
            break;
        case 14:
        case 15:
            p[t] += l;
            break;
        case 16:
            v = ((p[16] >> 8) & 0xFF);
            v += s;
            if (v > 255) {
                v = 255;
            }
            p[16] = v * 0x01010100;
            break;
        case 17:
        case 18:
        case 19:
            break;
        }
    }
}

// .text:0xF6E4 size:0xB4
void fn_1_F6E4(void) {
    ChallengeCommand command;
    ChParticleParams5* parameters = &lbl_1_data_F0BC;
    u16 buttons;
    command = lbl_1_rodata_731C;
    fn_1_F798(parameters, lbl_1_data_F0A8, 12);
    buttons = lbl_803C77B8._04;
    if (buttons & 0x100) {
        parameters->tex = lbl_1_bss_3098;
        fn_80031CA4((Vec*)&command, (struct ParticleParams5*)parameters);
    } else if (buttons & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0xF50C size:0x1D8
void fn_1_F50C(void) {
    Vec coordinates;
    ChFireballTask* queue = lbl_803CC1B8;
    CharActor* row = &lbl_8036E548.actors[lbl_1_bss_5F73];
    if (row != NULL) {
        row->pos.x = queue->pos.x;
        row->pos.y = queue->pos.y;
        row->pos.z = queue->pos.z;
    }
    fn_80030D88(&queue->pos, &queue->vel, &lbl_1_data_F10C.p, 5);
    if (queue->spawn != 0) {
        queue->spawn = 0;
        if (queue->onFeet != 0) {
            getAnimRelatedCoordinates(0, 0x1E, &coordinates);
            coordinates.y = lbl_1_rodata_7394;
            fn_8002F258(&coordinates, queue->id, lbl_1_data_F174[0]);
            getAnimRelatedCoordinates(0, 0x22, &coordinates);
            coordinates.y = lbl_1_rodata_7394;
            fn_8002F258(&coordinates, queue->id + 1, lbl_1_data_F174[0]);
        } else {
            fn_8002F258(&queue->pos, queue->id, lbl_1_data_F174[0]);
        }
    } else if (queue->onFeet != 0) {
        getAnimRelatedCoordinates(0, 0x1E, &coordinates);
        coordinates.y = lbl_1_rodata_7394;
        fn_8002F1AC(&coordinates, queue->id);
        getAnimRelatedCoordinates(0, 0x22, &coordinates);
        coordinates.y = lbl_1_rodata_7394;
        fn_8002F1AC(&coordinates, queue->id + 1);
    } else {
        fn_8002F1AC(&queue->pos, queue->id);
    }
    PSVECAdd(&queue->vel, &queue->accel, &queue->vel);
    PSVECAdd(&queue->vel, &queue->pos, &queue->pos);
    queue->timer = queue->timer - 1;
    if (queue->timer == 0) {
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0xF37C size:0x190
void fn_1_F37C(void) {
    lbl_803C77B8_s* pad;
    ChFireballTask* object;
    fn_1_F798(&lbl_1_data_F10C, lbl_1_data_F0A8, 0x12);
    pad = &lbl_803C77B8;
    if (pad->_04 & 0x1100) {
        lbl_1_data_F10C.p.tex = lbl_1_bss_3098;
        lbl_1_data_F174[0]->tex = lbl_1_bss_3098;
        lbl_1_data_F174[0]->texIndex = 5;
        object = fn_800B0A5C_insertQueue((void*)fn_1_F50C, (u16)(CH_TASK->priority + 1));
        object->pos.y = lbl_1_rodata_7394;
        object->pos.x = lbl_1_rodata_7394;
        object->pos.z = lbl_1_rodata_73F8;
        object->vel.x = lbl_1_rodata_7394;
        object->vel.y = lbl_1_rodata_7394;
        object->vel.z = (f32)lbl_1_data_F10C.speed / lbl_1_rodata_73FC;
        object->accel.x = lbl_1_rodata_7394;
        object->accel.y = lbl_1_rodata_7394;
        object->accel.z = (f32)lbl_1_data_F10C.accel / lbl_1_rodata_73FC;
        object->timer = 0x20;
        object->spawn = 1;
        object->id = lbl_1_bss_30A4;
        lbl_1_bss_30A4 = lbl_1_bss_30A4 + 2;
        object->onFeet = (pad->_04 >> 12) & 1;
        return;
    }
    if (pad->_04 & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F2F8 size:0x84
void fn_1_F2F8(void) {
    s32 buttons = lbl_803C77B8._04;
    if (buttons & 0x100) {
        lbl_80108B90.tex = lbl_1_bss_3098;
        fn_800324EC(lbl_1_data_F17C[0], 0, -1, &lbl_80108B90);
    } else if (buttons & 0x200) {
        lbl_80108B90.tex = NULL;
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0xF1D8 size:0x120
void fn_1_F1D8(TASK_PARAM(void* unused)) {
    Control control;
    Mtx matrix;
    Vec coordinates;
    Vec direction;
    ChBurstTask* queue = lbl_803CC1B8;
    CharActor* object = lbl_8036E548.active[lbl_1_bss_5F73];
    getAnimRelatedCoordinates(0, queue->joint, &coordinates);
    control.type = 0;
    CTRLSetRotation(&control, object->rot.x, object->rot.y, object->rot.z);
    CTRLBuildMatrix(&control, matrix);
    direction.x = lbl_1_rodata_7394;
    direction.z = lbl_1_rodata_73BC;
    direction.y = lbl_1_rodata_7394;
    PSMTXMultVec(matrix, &direction, &direction);
    fn_80030D88(&coordinates, &direction, lbl_1_data_F278[0], 5);
    fn_80030D88(&coordinates, &direction, lbl_1_data_F278[1], 5);
    fn_80030D88(&coordinates, &direction, lbl_1_data_F278[2], 5);
    if (--queue->timer == 0) {
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0xF0D0 size:0x108
void fn_1_F0D0(void) {
    u16 buttons;
    fn_1_F798(lbl_1_data_F278[lbl_1_bss_30A8], lbl_1_data_F284, 16);
    buttons = lbl_803C77B8._04;
    if (buttons & 0x1000) {
        lbl_1_bss_30A8 = (lbl_1_bss_30A8 + 1) % 3;
    } else if (lbl_803C77B8._00 & 0x100) {
        if (lbl_803C77B8._02 & 0x100) {
            ChBurstTask* queue;
            struct TexArchive* tex = lbl_1_bss_3098;
            lbl_1_data_F278[2]->tex = tex;
            lbl_1_data_F278[1]->tex = tex;
            lbl_1_data_F278[0]->tex = tex;
            queue = fn_800B0A5C_insertQueue((void*)fn_1_F1D8, 0);
            queue->timer = 240;
            queue->joint = 4;
        }
    } else if (buttons & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0xF040 size:0x90
void fn_1_F040(void) {
    ChallengeCommand command;
    u16 buttons;
    command = lbl_1_rodata_7344;
    buttons = lbl_803C77B8._04;
    if (buttons & 0x100) {
        lbl_1_data_F2A0.tex = lbl_1_bss_3098;
        fn_8002955C((Vec *)&command, 0, (struct ParticleParamsC *)&lbl_1_data_F2A0); // same layout (ch_data.h)
    } else if (buttons & 0x200) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0xECF8 size:0x348
// NONMATCHING ~75%: the original inlines fn_1_D300 (itself NONMATCHING), so this calls it
#if NONMATCHING
// Mirrors the first animated bone of a challenge actor onto the player actor.
static inline void fn_1_ECF8_bind(u8 player, u16 id, s32 slot) {
    ActorObjectTable* table = lbl_1_bss_5F7C[0];
    GameActor* actor = table->objects[slot - 1].actor;
    u16 i;
    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->dispObj != NULL) {
            fn_800B2BA8(lbl_8036E548.slots->objects[player].actor, id,
                        table->objects[slot - 1].actor, i);
            break;
        }
    }
}

// nmverify: lbl_1_bss_5F7C reached through a pooled base in original
void fn_1_ECF8(u8 player, u8 group, u8 flag) {
    CharActor* row;
    u16 idA;
    u16 idB;
    s32 first;
    s32 second;

    if (lbl_1_bss_60A4[lbl_1_bss_68FC.character[player]] == 0) {
        return;
    }
    row = &lbl_8036E548.actors[player];
    idA = row->jointIdx[0x13];
    idB = row->jointIdx[0x19];
    switch (group) {
    case 0:
    case 1:
    case 5:
    case 6:
        first = 1;
        second = 2;
        break;
    default:
        if (flag != 0) {
            first = 1;
            second = 4;
        } else {
            first = 3;
            second = 2;
        }
        break;
    }
    fn_1_ECF8_bind(player, idA, first);
    fn_1_ECF8_bind(player, idB, second);
    fn_1_D300(&lbl_8036E548.actors[lbl_1_bss_5F73]);
}
#endif

// .text:0xEA20 size:0x2D8
// NONMATCHING ~90%: case 0 loop reloads the animation table differently; register allocation
#if NONMATCHING
void fn_1_EA20(void) {
    ActorObject* object;
    ChPlayer* entry;
    ANIMBank** table;
    s32 i;
    s32 j;
    u16 buttons;

    switch (lbl_1_bss_30B0) {
    case 0:
        object = &lbl_8036E548.slots->objects[lbl_1_bss_5F73];
        lbl_1_bss_5F68 = 1;
        lbl_1_bss_5F64 = 0.0f;
        object->time = 0.0f;
        object->setTime = 1;
        lbl_1_bss_30B0 = 1;
        lbl_1_bss_5F58 = 0;
        entry = &lbl_1_bss_6940.player[lbl_1_bss_5F73];
        table = (ANIMBank**)&lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[entry->group];
        j = entry->seq;
        for (i = 0; i < PTR32_GET(ANIMSequences, (*table)->animSequences)[j].totalTracks; i++) {
            f32 frame = PTR32_GET(struct ANIMAnimTrack, PTR32_GET(ANIMSequences, (*table)->animSequences)[j].trackArray)[i].animTime;
            if ((f32)lbl_1_bss_5F58 < frame) {
                lbl_1_bss_5F58 = (s32)frame;
            }
        }
        break;
    case 1:
        if (lbl_803C77B8._02 & 0x200) {
            lbl_1_bss_30B0 = 0;
            lbl_1_bss_5F71 = 1;
            break;
        }
        buttons = lbl_803C77B8._04;
        if (buttons & 1) {
            if (--lbl_1_bss_30B4 < 0) {
                lbl_1_bss_30B4 = lbl_1_bss_5F58 - 2;
            }
        } else if (buttons & 2) {
            if (++lbl_1_bss_30B4 > lbl_1_bss_5F58 - 2) {
                lbl_1_bss_30B4 = 0;
            }
        } else if (buttons & 0x100) {
            lbl_1_bss_5F68 = 0;
            fn_80039A4C();
            lbl_8036E548._3083[1] = lbl_1_bss_5F73;
            lbl_1_bss_30B0 = 2;
            lbl_8036E548.active[lbl_1_bss_5F73] = &lbl_8036E548.actors[lbl_1_bss_5F73];
        }
        break;
    default:
        if ((u32)(lbl_1_bss_30B0 - 2) == (u32)(lbl_1_bss_30B4 * 2)) {
            lbl_8036E548._3083[0] = 1;
        }
        lbl_1_bss_30B0++;
        if (lbl_803C77B8._02 & 0x200) {
            lbl_1_bss_30B0 = 0;
            lbl_8036E548._3083[0] = 0;
        } else if (lbl_803C77B8._02 & 0x100) {
            object = &lbl_8036E548.slots->objects[lbl_1_bss_5F73];
            object->time = 0.0f;
            object->setTime = 1;
            fn_80039A4C();
            lbl_8036E548._3083[1] = lbl_1_bss_5F73;
            lbl_1_bss_30B0 = 2;
            lbl_8036E548.active[lbl_1_bss_5F73] = &lbl_8036E548.actors[lbl_1_bss_5F73];
        }
        break;
    }
}
#endif

// .text:0x0000E9F8 size:0x28
void fn_1_E9F8(GameActor* object, s32 index, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        index++;
        if (index == object->totalBones) index = 0;
    }
}

// .text:0xE8D4 size:0x124
void fn_1_E8D4(void) {
    ChScriptStep* src;
    s32 n;
    ChallengeStep* dst;
    CharMgr* base;
    src = &lbl_1_data_F4D4.records[0].steps[6]; // src[2] is the step: the original walks base+0x40 with a 0x10 displacement
    n = 8;
    dst = &lbl_1_bss_3218[8];
    base = CHARMGR_AT(lbl_1_bss_5F73);
    while ((src--, dst--, n-- != 0)) {
        if (src[2].used != 0) {
            ANIMBank* table;
            s16 a = src[2].group;
            s16 b;
            s16 c;
            dst->group = a;
            table = base->actors[0].banks.b[a];
            b = src[2].index;
            dst->index = b;
            dst->sync = src[2].sync;
            c = src[2].frame;
            if (c == -2) {
                if (table != NULL) {
                    dst->frame = (s32)PTR32_GET(struct ANIMAnimTrack, PTR32_GET(ANIMSequences, table->animSequences)[b].trackArray)->animTime;
                } else {
                    dst->frame = 0;
                }
            } else {
                dst->frame = c;
            }
        } else {
            dst->group = -1;
            dst->sync = 0;
            dst->frame = 0;
        }
    }
    while ((s8)lbl_1_data_F4D4.records[lbl_1_data_F4D4.count].name[0] != 0) {
        lbl_1_data_F4D4.count += 1;
    }
}

// .text:0xE098 size:0x83C
// Debug editor for the challenge animation script (8 steps x 4 columns, plus script select / play rows).
// NONMATCHING ~85%: the original inlines fn_1_D7A4 and fn_1_D300
// nmverify: lbl_1_bss_3218 lbl_1_bss_5F73 reached through a pooled base in original
#if NONMATCHING
void fn_1_E098(void) {
    ChallengeStep* step = lbl_1_bss_3218;
    ChScriptTable* scripts = &lbl_1_data_F4D4;
    u16 buttons;
    s32 row;
    s32 col;

    for (row = 0; row < 11; row++, step++) {
        switch (row) {
        case 8:
            if (row == lbl_1_bss_30B6) {
                s16 old = scripts->current;
                buttons = lbl_803C77B8._04;
                if (buttons & 1) {
                    if (scripts->current == 0) {
                        scripts->current = scripts->count;
                    }
                    scripts->current--;
                } else if (buttons & 2) {
                    if (++scripts->current == scripts->count) {
                        scripts->current = 0;
                    }
                }
                if (old != scripts->current) {
                    fn_1_D7A4(scripts->current);
                }
            }
            break;
        case 9:
            if (row == lbl_1_bss_30B6 && (lbl_803C77B8._02 & 0x100)) {
                CH_TASK->func = fn_1_DE1C;
                ((ChScriptTask*)lbl_803CC1B8)->index = 0;
                ((ChScriptTask*)lbl_803CC1B8)->step = 8;
            }
            break;
        case 10:
            if (row == lbl_1_bss_30B6 && (lbl_803C77B8._02 & 0x100)) {
                ChScriptTask* queue = lbl_803CC1B8;
                ChallengeStep* steps = lbl_1_bss_3218;
                ChPlayer* entry;
                ActorObject* object;
                void* table;
                s32 k;

                *(void**)queue = (void*)fn_1_DE1C;
                queue->step = 0;
                entry = &lbl_1_bss_6940.player[lbl_1_bss_5F73];
                entry->group = steps[(s8)queue->step].group;
                entry->seq = steps[(s8)queue->step].index;
                object = &lbl_8036E548.slots->objects[lbl_1_bss_5F73];
                table = lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[entry->group];
                object->animBank = table;
                object->seqNum = entry->seq;
                object->time = 0.0f;
                object->setAnimation = 1;
                object->setTime = table != NULL;
                object->setSpeed = table != NULL;
                object->speed = 0.0f;
                for (k = 4; k >= 0; k--) {
                    ShapeAnimState* anims = lbl_1_bss_3258[(s8)queue->step];
                    if (anims[k].unk8 != 0) {
                        // The original indexes with the row counter instead of k.
                        lbl_1_bss_67B8[k] = &anims[row];
                        ((ShapeAnimState*)lbl_1_bss_67B8[k])->frame = 0.0f;
                    } else {
                        lbl_1_bss_67B8[k] = NULL;
                    }
                }
                fn_1_D300(&lbl_8036E548.actors[lbl_1_bss_5F73]);
            }
            break;
        default: {
            ANIMBank* table;
            ANIMSequences* anim;
            u16 highlight;
            u16 pad0;

            if (step->group >= 0) {
                table = lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[step->group];
                anim = &PTR32_GET(ANIMSequences, table->animSequences)[step->index];
            } else {
                table = NULL;
                anim = NULL;
            }
            buttons = lbl_803C77B8._04;
            pad0 = lbl_803C77B8._00;
            for (col = 0; col < 4; col++) {
                if (row != lbl_1_bss_30B6 || col != lbl_1_bss_30B7) {
                    highlight = 0xFFFF;
                } else if (pad0 & 0x100) {
                    highlight = 0xF00F;
                } else {
                    highlight = 0xFF0F;
                }
                switch (col) {
                case 0:
                    if (highlight == 0xF00F && table != NULL) {
                        if (buttons & 1) {
                            if (step->frame >= 0) {
                                step->frame--;
                            }
                        } else if (buttons & 2) {
                            if (step->frame < (s16)(s32)PTR32_GET(struct ANIMAnimTrack, anim->trackArray)->animTime) {
                                step->frame++;
                            }
                        }
                    }
                    break;
                case 1:
                    if (highlight == 0xF00F) {
                        s16 old = step->group;
                        if (buttons & 1) {
                            if (old >= 0) {
                                step->group = old - 1;
                            }
                        } else if ((buttons & 2) && old < 6) {
                            step->group = old + 1;
                        }
                        if (old != step->group) {
                            step->index = 0;
                        }
                    }
                    break;
                case 2:
                    if (highlight == 0xF00F && table != NULL) {
                        if (buttons & 1) {
                            if (step->index > 0) {
                                step->index--;
                            }
                        } else if (buttons & 2) {
                            if (step->index < table->numSequences - 1) {
                                step->index++;
                            }
                        }
                    }
                    break;
                case 3:
                    if (highlight == 0xF00F && table != NULL && (buttons & 3)) {
                        step->sync = step->sync == 0;
                    }
                    break;
                }
            }
            break;
        }
        }
    }
    if (!(lbl_803C77B8._00 & 0x100)) {
        buttons = lbl_803C77B8._04;
        if (buttons & 8) {
            if (lbl_1_bss_30B6 == 0) {
                lbl_1_bss_30B6 = 11;
            }
            lbl_1_bss_30B6--;
        } else if (buttons & 4) {
            if (++lbl_1_bss_30B6 == 11) {
                lbl_1_bss_30B6 = 0;
            }
        } else if (buttons & 1) {
            if (lbl_1_bss_30B7 == 0) {
                lbl_1_bss_30B7 = 4;
            }
            lbl_1_bss_30B7--;
        } else if (buttons & 2) {
            if (++lbl_1_bss_30B7 == 4) {
                lbl_1_bss_30B7 = 0;
            }
        } else if (buttons & 0x200) {
            lbl_1_bss_5F71 = 1;
        }
    }
}
#endif

// .text:0xDF14 size:0x184
void fn_1_DF14(void) {
    ChScriptTask* queue = lbl_803CC1B8;
    s16 state = queue->h.result;
    s32 idx = queue->index;
    ShapeAnimState** p;
    ShapeAnimState* q;
    ShapeKey* r;
    s32 n;
    switch (state) {
    case 0:
        {
            lbl_1_bss_6940.player[lbl_1_bss_5F73].group = lbl_1_bss_3218[idx].group;
            lbl_1_bss_6940.player[lbl_1_bss_5F73].seq = lbl_1_bss_3218[idx].index;
        }
        fn_800B0A5C_insertQueue((void*)fn_1_107B8, 0xFF);
        lbl_1_bss_5F5C = 2;
        CH_TASK->result += 1;
        break;
    case 1:
        if (lbl_1_bss_5F5C == 0) {
            p = (ShapeAnimState**)lbl_1_bss_67B8 + 5;
            q = lbl_1_bss_3258[idx] + 5; // walk the 5 slots backwards
            r = lbl_1_bss_3758[idx][0] + 5 * 0x40;
            n = 5;
            while ((p--, q--, r -= 0x40, n-- != 0)) {
                if (*p != NULL) {
                    memcpy(q, *p, sizeof(ShapeAnimState));
                    q->seqs[0].keys = r;
                    memcpy(r, (*p)->seqs[0].keys, (*p)->seqs[0].hdr.keyCount * sizeof(ShapeKey));
                } else {
                    memset(q, 0, sizeof(ShapeAnimState));
                }
            }
            {
                ChTaskHeader* o = CH_TASK->parent;
                o->result = 1;
                fn_800B0A14_removeQueue(o);
            }
        }
        break;
    }
}

// .text:0xDE1C size:0xF8
void fn_1_DE1C(void) {
    ChScriptTask* queue = lbl_803CC1B8;
    switch (queue->index) {
    case 0:
        if ((s8)queue->step == 0) {
            *(void**)queue = (void*)fn_1_D9B8;
        } else {
            u8 n;
            while ((s8)(n = queue->step--) != 0) {
                if (lbl_1_bss_3218[(s8)queue->step].group >= 0) {
                    ChScriptTask* object = fn_800B0A5C_insertQueue((void*)fn_1_DF14, (u16)(CH_TASK->priority + 1));
                    object->h.result = 0;
                    object->index = queue->step;
                    queue->h.result = 0;
                    queue->index = queue->index + 1;
                    break;
                }
            }
        }
        break;
    case 1:
        if (queue->h.result != 0) queue->index = 0;
        break;
    }
    ((void (*)(void))fn_1_D8A0)();
}

// .text:0xD9B8 size:0x464
// NONMATCHING ~80%: the original inlines fn_1_D300 (itself NONMATCHING), so this calls it
#if NONMATCHING
void fn_1_D9B8(void) {
    ChallengeStep* steps = lbl_1_bss_3218;
    ChScriptTask* queue = lbl_803CC1B8;
    GameActor* actor = lbl_8036E548.slots->objects[lbl_1_bss_5F73].actor;
    u16 count = actor->totalBones;
    s32 i;
    s32 frame;
    s16 target;

    for (i = 0; i < count; i++) {
        struct ANIMPipe* anim = actor->boneArray[i]->animPipe;
        if (anim != NULL && anim->currentTrack != NULL) {
            break;
        }
    }
    // The original leaves `frame` uninitialized (it holds the saved LR, a negative s32)
    // when no bone is animated, so the frame test below fails.
    frame = -1;
    if (i < count) {
        frame = actor->boneArray[i]->animPipe->time;
    }
    target = steps[(s8)queue->step].frame;
    if ((target < 0 && (lbl_803C77B8._02 & 0x100)) || (target >= 0 && frame >= target)) {
        ChPlayer* entry;
        ActorObject* object;
        void* table;
        f32 start;
        s32 k;

        do {
            queue->step++;
            if (queue->step == 8) {
                queue->step = 0;
            }
        } while (steps[(s8)queue->step].group < 0);
        entry = &lbl_1_bss_6940.player[lbl_1_bss_5F73];
        entry->group = steps[(s8)queue->step].group;
        entry->seq = steps[(s8)queue->step].index;
        object = &lbl_8036E548.slots->objects[lbl_1_bss_5F73];
        table = lbl_8036E548.actors[lbl_1_bss_5F73].banks.b[entry->group];
        object->animBank = table;
        object->seqNum = entry->seq;
        object->time = 0.0f;
        object->setAnimation = 1;
        object->setTime = table != NULL;
        object->setSpeed = table != NULL;
        object->speed = 0.0f;
        start = ((ShapeAnimState*)lbl_1_bss_67B8[0])->frame;
        for (k = 4; k >= 0; k--) {
            ShapeAnimState* anim = &lbl_1_bss_3258[(s8)queue->step][k];
            if (anim->unk8 != 0) {
                u16 key = ((ShapeAnimState*)lbl_1_bss_67B8[0])->keyIdx;
                lbl_1_bss_67B8[k] = anim;
                if (steps[(s8)queue->step].sync != 0 && (f32)((ShapeAnimState*)lbl_1_bss_67B8[k])->seqs[0].hdr.length < start) {
                    ((ShapeAnimState*)lbl_1_bss_67B8[k])->frame = start;
                    ((ShapeAnimState*)lbl_1_bss_67B8[k])->keyIdx = key;
                } else {
                    ((ShapeAnimState*)lbl_1_bss_67B8[k])->frame = 0.0f;
                    ((ShapeAnimState*)lbl_1_bss_67B8[k])->keyIdx = 0;
                }
            } else {
                lbl_1_bss_67B8[k] = NULL;
            }
        }
        fn_1_D300(&lbl_8036E548.actors[lbl_1_bss_5F73]);
    }
    if (lbl_803C77B8._04 & 0x200) {
        CH_TASK->func = (void (*)(void))fn_1_1770C;
    }
    fn_1_D8A0();
}
#endif

// .text:0xD8A0 size:0x118
void fn_1_D8A0(void) {
    Mtx44 projection;
    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_1_179CC();
    PSMTXCopy(lbl_1_bss_67E0.cam.view, lbl_1_bss_68FC.view);
    fn_800A7D4C(7, &lbl_1_data_AA54[lbl_803CBBC0[0]]);
    if (lbl_1_bss_3078 != 0) {
        fn_800A7D4C(7, &lbl_1_data_AB34[lbl_803CBBC0[0]]);
    }
    fn_800A7D4C(7, &lbl_1_data_AAC4[lbl_803CBBC0[0]]);
    fn_1_129D0();
}

// .text:0xD7A4 size:0xFC
void fn_1_D7A4(s32 index) {
    ChScriptStep* src;
    ChallengeStep* dst;
    CharMgr* base;
    s32 n;
    src = &lbl_1_data_F4D4.records[index].steps[6]; // src[2] is the step: the original walks base+0x40 with a 0x10 displacement
    dst = &lbl_1_bss_3218[8];
    base = CHARMGR_AT(lbl_1_bss_5F73);
    n = 8;
    while ((src--, dst--, n-- != 0)) {
        if (src[2].used != 0) {
            ANIMBank* table;
            s16 a = src[2].group;
            s16 b;
            s16 c;
            dst->group = a;
            table = base->actors[0].banks.b[a];
            b = src[2].index;
            dst->index = b;
            dst->sync = src[2].sync;
            c = src[2].frame;
            if (c == -2) {
                if (table != NULL) {
                    dst->frame = (s32)PTR32_GET(struct ANIMAnimTrack, PTR32_GET(ANIMSequences, table->animSequences)[b].trackArray)->animTime;
                } else {
                    dst->frame = 0;
                }
            } else {
                dst->frame = c;
            }
        } else {
            dst->group = -1;
            dst->sync = 0;
            dst->frame = 0;
        }
    }
}

// .text:0xD71C size:0x88
f32 fn_1_D71C(s32 index) {
    s32 current;
    ActorObjectTable* objects;
    s32 count;
    GameActor* model;
    objects = lbl_8036E548.slots;
    model = objects->objects[index].actor;
    count = model->totalBones;
    for (current = 0; current < count; current++) {
        struct ANIMPipe* animation = model->boneArray[current]->animPipe;
        if (animation != NULL && animation->currentTrack != NULL) {
            break;
        }
    }
    if (current < count) {
        return model->boneArray[current]->animPipe->time;
    }
    return 0.0f;
}

const char* fn_1_D6E4(void) {
    u8 index = lbl_1_bss_3216;
    switch (index) {
    case 0:
    case 1:
    case 2:
        return lbl_1_data_F4DC[index];
    default:
        return NULL;
    }
}

void fn_1_D6B4(void) {
    if (lbl_1_bss_3216 == 0) lbl_1_bss_3216 = 3;
    lbl_1_bss_3216--;
}

void fn_1_D688(void) {
    lbl_1_bss_3216++;
    if (lbl_1_bss_3216 == 3) lbl_1_bss_3216 = 0;
}

void fn_1_D67C(u8 value) {
    lbl_1_bss_3215 = value;
}

s32 fn_1_D660(void) {
    return lbl_1_bss_3215 != 0;
}

void fn_1_D650(void) {
    lbl_1_bss_3214 = 1;
}

u8 fn_1_D638(void) {
    u8 flag = lbl_1_bss_3214;
    lbl_1_bss_3214 = 0;
    return flag;
}

// .text:0xD590 size:0xA8
void fn_1_D590(void* a, s32 b, f32 value) {
    if (lbl_1_bss_3215 == 0 || lbl_1_bss_3216 == 0) return;
    if (lbl_1_bss_3216 == 2) {
        if ((s32)value == 0) {
            lbl_1_bss_3214 += (lbl_1_bss_3214 != 0);
        }
        if (lbl_1_bss_3214 == 3) lbl_1_bss_3214 = 0;
        if (lbl_1_bss_3214 == 2) goto call;
    } else {
call:
        fn_8004B208(a, b, (s8)*(u8*)&lbl_1_bss_5F62 & ~((s8)*(u8*)&lbl_1_bss_5F62 >> 31), value);
    }
}

// .text:0xD4BC size:0xD4
void fn_1_D4BC(void) {
    Vec coordinates;
    CharMgr* scene = &lbl_8036E548;
    CharActor* object = scene->actors;
    if (object != NULL) {
        object->_276 = (s32)object->_276 >> 1;
        object->_276 = (object->_276 * 8) & 0xF8;
        getAnimRelatedCoordinates(0, 0x1E, &coordinates);
        if (object->pos.y - coordinates.y < lbl_1_rodata_73C8) {
            object->_276 |= 2;
        }
        getAnimRelatedCoordinates(0, 0x22, &coordinates);
        if (object->pos.y - coordinates.y < lbl_1_rodata_73C8) {
            object->_276 |= 4;
        }
    }
    object = scene->active[0];
    object->_276 |= 1;
}

// .text:0xD300 size:0x1BC
// NONMATCHING ~96%: switch tree lacks one dead branch; r6/r7 swap
#if NONMATCHING
void fn_1_D300(CharActor* row) {
    u32 idx;
    s32 first;
    CharActor** actors;
    s32 second;

    idx = lbl_1_bss_5F73;
    switch (lbl_1_bss_6940.player[idx].group) {
    case 0:
    case 1:
        first = 1;
        second = 2;
        break;
    default:
        if (lbl_1_bss_5F69 != 0) {
            first = 1;
            second = 4;
        } else {
            first = 3;
            second = 2;
        }
        break;
    }
    actors = lbl_8036E548.active;
    actors[idx]->parts = &lbl_8036E548.partsPool[idx];
    memcpy(&actors[lbl_1_bss_5F73]->parts->part[0].player, &lbl_1_bss_60EC[first], 0x5C);
    memcpy(&actors[lbl_1_bss_5F73]->parts->part[1].player, &lbl_1_bss_60EC[second], 0x5C);
    actors[lbl_1_bss_5F73]->parts->part[0].slot = lbl_1_bss_5F73;
    actors[lbl_1_bss_5F73]->parts->part[1].slot = lbl_1_bss_5F73;
    actors[lbl_1_bss_5F73]->parts->_CD = row->_25A;
    actors[lbl_1_bss_5F73]->parts->_CE = row->_25B;
    actors[lbl_1_bss_5F73]->parts->_CF = lbl_1_bss_5F73;
    actors[lbl_1_bss_5F73]->parts->_D0 = lbl_1_bss_5F73;
    actors[lbl_1_bss_5F73]->model = lbl_8036E548.slots->objects[lbl_1_bss_5F73].actor;
}
#endif

void fn_1_D2F0(void) {
    lbl_1_bss_30B8 = 1;
}

// .text:0xD13C size:0x1B4
// NONMATCHING ~85%: scheduling/register differences around the row pointer and flag compare
#if NONMATCHING
void fn_1_D13C(void) {
    u16 bones[2];
    CharActor* row = &lbl_8036E548.actors[lbl_1_bss_5F73];
    s32 kind = 0; // uninitialized in the original (case 39 / default keep a stale register)
    s32 i;
    u16* bone;
    u16* ids;
    ChTaskHeader* queue;

    queue = fn_800B0A5C_insertQueue((void*)fn_1_CDC8, (u16)(CH_TASK->priority + 1));
    lbl_1_bss_60E8 = queue;
    queue->result = lbl_1_bss_6940.player[lbl_1_bss_5F73].group;
    switch (lbl_1_bss_68FC.character[lbl_1_bss_5F73]) {
    case 38:
        kind = 0;
        break;
    case 18:
        kind = 3;
        break;
    case 40:
        kind = 1;
        break;
    case 41:
        kind = 2;
        break;
    case 39:
        break;
    }
    row->_25A = (lbl_1_bss_6940.player[lbl_1_bss_5F73].group < 2) == (lbl_1_bss_5F69 == 0);
    ids = lbl_8036E548.actors[lbl_1_bss_5F73].jointIdx;
    bone = bones;
    bone[row->_25A] = ids[lbl_1_data_F4E8[kind][0]];
    bone[row->_25A == 0] = ids[lbl_1_data_F4E8[kind][1]];
    for (i = 0; i < 2; i++) {
        fn_800B2B74(lbl_8036E548.slots->objects[lbl_1_bss_5F73].actor, *bone);
        bone++;
    }
}
#endif

// .text:0xCDC8 size:0x374
// NONMATCHING ~85%: bone search loops use ctr in the original; register allocation
// nmverify: lbl_1_bss_5F7C reached through a pooled base in original
#if NONMATCHING
void fn_1_CDC8(void) {
    void* states[2];
    GameActor** tables[2];
    u16 bones[2];
    CharActor* row;
    u16 idB;
    s32 kind;
    s32 both;
    s32 i;
    u16 j;
    GameActor* actor;
    u8 group;

    if (lbl_1_bss_30B8 != 0) {
        lbl_1_bss_30B8 = 0;
        fn_800B0A14_removeQueue(NULL);
        return;
    }
    row = &lbl_8036E548.actors[lbl_1_bss_5F73];
    idB = row->jointIdx[0x19];
    fn_800B2BA8(lbl_8036E548.slots->objects[lbl_1_bss_5F73].actor, row->jointIdx[0x13], NULL, 0);
    fn_800B2BA8(lbl_8036E548.slots->objects[lbl_1_bss_5F73].actor, idB, NULL, 0);
    switch (lbl_1_bss_68FC.character[lbl_1_bss_5F73]) {
    case 38:
        kind = 0;
        break;
    case 18:
        kind = 3;
        break;
    case 40:
        kind = 1;
        break;
    case 41:
        kind = 2;
        break;
    default:
        kind = 0; // uninitialized in the original
        break;
    }
    group = lbl_1_bss_6940.player[lbl_1_bss_5F73].group;
    row->_25A = (lbl_1_bss_6940.player[lbl_1_bss_5F73].group < 2) == (lbl_1_bss_5F69 == 0);
    states[lbl_1_bss_5F69] = lbl_1_bss_67B8[2];
    states[lbl_1_bss_5F69 == 0] = lbl_1_bss_67B8[1];
    {
        u16* ids = lbl_8036E548.actors[lbl_1_bss_5F73].jointIdx;
        bones[0] = ids[lbl_1_data_F4E8[kind][1]];
        bones[1] = ids[lbl_1_data_F4E8[kind][0]];
    }
    tables[0] = &((ActorObjectTable*)lbl_1_bss_5F7C[0])->objects[1].actor;
    tables[1] = &((ActorObjectTable*)lbl_1_bss_5F7C[0])->objects[0].actor;
    switch (group) {
    case 0:
    case 1:
    case 5:
    case 6:
        both = 1;
        break;
    case 2:
    case 3:
    case 4:
        both = 0;
        break;
    default:
        both = 0; // uninitialized in the original
        break;
    }
    i = 0;
    do {
        if (states[i] != NULL) {
            if (fn_80024D2C(states[i]) & 0x20000000) {
                actor = *tables[i];
                for (j = 0; j < actor->totalBones; j++) {
                    if (actor->boneArray[j]->dispObj != NULL) {
                        fn_800B2BA8(lbl_8036E548.slots->objects[lbl_1_bss_5F73].actor, bones[i], actor, j);
                        break;
                    }
                }
            } else {
                fn_800B2BA8(lbl_8036E548.slots->objects[lbl_1_bss_5F73].actor, bones[i], NULL, 0);
            }
        }
        i++;
    } while ((both != 0 || lbl_1_bss_68FC.character[lbl_1_bss_5F73] == 38) && i < 2);
    if (i == 1) {
        if (lbl_1_bss_5F69 != 0) {
            tables[0] = &((ActorObjectTable*)lbl_1_bss_5F7C[0])->objects[2].actor;
        } else {
            tables[0] = &((ActorObjectTable*)lbl_1_bss_5F7C[0])->objects[2].actor;
        }
        actor = *tables[0];
        for (j = 0; j < actor->totalBones; j++) {
            if ((*tables[0])->boneArray[j]->dispObj != NULL) {
                fn_800B2BA8(lbl_8036E548.slots->objects[lbl_1_bss_5F73].actor, bones[i], actor, j);
                break;
            }
        }
    }
}
#endif

// .text:0xCCC8 size:0x100
void fn_1_CCC8(void) {
    ChBodyTask* queue = lbl_803CC1B8;
    f32* animation = queue->anim;
    if (animation != NULL && animation[0] < animation[1]) {
        if (lbl_1_bss_5F69 != 0) {
            fn_800385F0(&lbl_1_bss_30C0, lbl_1_rodata_73BC, lbl_1_rodata_73C0[0], lbl_1_rodata_73C4[0], lbl_1_rodata_73BC);
        } else {
            fn_800385F0(&lbl_1_bss_30C0, lbl_1_rodata_73A4[0], lbl_1_rodata_73C0[0], lbl_1_rodata_73C4[0], lbl_1_rodata_73BC);
        }
        lbl_1_bss_30C0.unk50 = lbl_1_data_F568[0];
        fn_80037AA0(&lbl_1_bss_30C0, 0, (void (*)(void))fn_1_CB9C, queue->id, queue->anim);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0xCC24 size:0xA4
void fn_1_CC24(void) {
    ChBodyTask* object;
    if (lbl_1_bss_30BC == 0) {
        lbl_1_bss_30BC = 1;
        object = fn_800B0A5C_insertQueue((void*)fn_1_CCC8, (u16)(CH_TASK->priority + 1));
        if (lbl_1_bss_5F69 != 0) {
            object->anim = lbl_1_bss_67B8[1];
            object->id = lbl_1_data_F56C;
        } else {
            object->anim = lbl_1_bss_67B8[2];
            object->id = lbl_1_data_F56E;
        }
    }
}

// .text:0x0000CB9C size:0x88
void fn_1_CB9C(s32 reset) {
    if (reset != 0) {
        lbl_1_bss_30BC = 0;
    } else {
        s32 index;
        ChDrawMtxNode* entry = &lbl_1_data_F4F8[lbl_803CBBC0[0]];
        PSMTXCopy(lbl_1_bss_30C0.world, entry->m);
        index = lbl_803CBBC0[0];
        fn_800A7D4C(8, &lbl_1_data_F4F8[index]);
    }
}

// .text:0xC9E0 size:0x1BC
void fn_1_C9E0(struct ChDrawMtxNode* object) {
    Mtx concat;
    Vec scaled;
    fn_1_F2C(4, 0, 0);
    PSMTXConcat(lbl_1_bss_68FC.view, object->m, concat);
    GXLoadPosMtxImm(concat, 0);
    GXSetCurrentMtx(0);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetZMode(1, 7, 1);
    GXBegin(0xA8, 0, 6);
    GXWGFifo.f32 = lbl_1_bss_30C0.p1.x;
    GXWGFifo.f32 = lbl_1_bss_30C0.p1.y;
    GXWGFifo.f32 = lbl_1_bss_30C0.p1.z;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = lbl_1_bss_30C0.p0.x;
    GXWGFifo.f32 = lbl_1_bss_30C0.p0.y;
    GXWGFifo.f32 = lbl_1_bss_30C0.p0.z;
    GXWGFifo.u32 = 0x00FF00FF;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.u32 = 0x000000FF;
    PSVECScale(&lbl_1_bss_30C0.velLocal, lbl_1_data_F570.scale, &scaled);
    GXWGFifo.f32 = scaled.x;
    GXWGFifo.f32 = scaled.y;
    GXWGFifo.f32 = scaled.z;
    GXWGFifo.u32 = 0x000000FF;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.u32 = 0xFFFFFFFF;
    PSVECScale(&lbl_1_bss_30C0.angVel, lbl_1_data_F570.scale, &scaled);
    GXWGFifo.f32 = scaled.x;
    GXWGFifo.f32 = scaled.y;
    GXWGFifo.f32 = scaled.z;
    GXWGFifo.u32 = 0xFFFFFFFF;
}

// .text:0xC5AC size:0x434
// NONMATCHING ~85%: the overlay settings are reached through the pooled .data base
// nmverify: lbl_1_data_F570 reached through a pooled base in original
#if NONMATCHING
void fn_1_C5AC(void) {
    ChallengeOverlay* overlay = &lbl_1_data_F570;
    ChallengeMtx identity = lbl_1_rodata_7364;
    Mtx44 projection;

    C_MTXOrtho(projection, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, overlay->far);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(identity.m, 0);
    GXSetCurrentMtx(0);
    fn_1_F2C(4, 0, 0);

    // depth-only pass
    GXSetColorUpdate(0);
    GXSetAlphaUpdate(0);
    GXSetZMode(1, GX_ALWAYS, 1);
    fn_1_C5AC_quad(-overlay->depth, overlay->color);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    GXSetZMode(1, GX_LEQUAL, 1);

    // additive light shaft
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(330.0f, 0.0f, -1.0f);
    GXColor1u32(overlay->colorTop);
    GXPosition3f32(310.0f, 0.0f, -1.0f);
    GXColor1u32(overlay->colorTop);
    GXPosition3f32(220.0f, 336.0f, -1.0f);
    GXColor1u32(overlay->colorBottom);
    GXPosition3f32(420.0f, 336.0f, -1.0f);
    GXColor1u32(overlay->colorBottom);

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    fn_1_C5AC_quad(-2.0f, overlay->color);

    GXSetColorUpdate(0);
    GXSetAlphaUpdate(0);
    GXSetZMode(1, GX_ALWAYS, 1);
    fn_1_C5AC_quad(-overlay->depth, overlay->color);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
}
#endif
