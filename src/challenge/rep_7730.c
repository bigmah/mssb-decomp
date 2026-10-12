#include "challenge/rep_7730.h"
#define REP_HEADER_FN repHeader_7730
#include "header_rep_inline.h"

#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include "main/file_800BD8C4.h"
#include "main/file_8000BA3C.h"
#include "main/file_8000F150.h"
#include "C3/control.h"
#include "stl/math.h"
#include "challenge/rep_0010.h" // ChTaskHeader, lbl_803CC1B8
#include "challenge/rep_7978.h" // ChallengeDebugCamera

// POOL BEGIN (high-to-low; memory order is the reverse)
static Mtx44 lbl_1_bss_47010;
static u8 lbl_1_bss_45890[0x17A8 - 0x28];
static ChallengeCurveTiming lbl_1_bss_45868;
static ChallengePathNode lbl_1_bss_43F68[100];
static Mtx lbl_1_bss_43F38;
static ChallengeCameraState lbl_1_bss_43EE0;
static Vec lbl_1_bss_F6E0[160][112];
static f32 lbl_1_bss_76E0[2][32 * 128];
static f32 lbl_1_bss_74E0[0x200 / 4];
static ChallengeCurvePoint lbl_1_bss_6FE0[20];
static ChallengeCurveTiming lbl_1_bss_6FB8;
static u8 lbl_1_bss_6FB4[4];
static f32 lbl_1_bss_6FA8[3];
static void* lbl_1_bss_6FA4[1];
static GXTexObj lbl_1_bss_6EA4[8];
static GXTlutObj lbl_1_bss_6E44[8];
static u32 lbl_1_bss_6E24[8];
static ChallengeDebugCamera lbl_1_bss_6D48;
static ChallengeProjectionState lbl_1_bss_6BF4;
static f32 lbl_1_bss_6BE4[4];
static ActorObjectTable* lbl_1_bss_6BE0[1];
static s32 lbl_1_bss_6BDC;
static s32 lbl_1_bss_6BD8;
// POOL END
extern void fn_1_20BD8(void);

extern void fn_1_246AC(void);




extern void fn_80037B18(void* rb, Vec* force, f32 unused);

extern void fn_1_1DA54(void);

extern const f32 lbl_1_rodata_77E4;


#include "main/aramloader.h" // ARAMLoader lbl_803C6CF8
extern const f32 lbl_1_rodata_77D8;
extern const f32 lbl_1_rodata_7804;
extern const f32 lbl_1_rodata_7858;
extern const f32 lbl_1_rodata_785C;
extern const f32 lbl_1_rodata_7860;
extern const f32 lbl_1_rodata_7864;
extern const f32 lbl_1_rodata_7868;
extern const f32 lbl_1_rodata_780C;
extern const f32 lbl_1_rodata_77DC[];
extern const f32 lbl_1_rodata_77E0[];
extern const f32 lbl_1_rodata_7814[];
extern const f32 lbl_1_rodata_7820[];
extern void* lbl_80366158[];
extern void fn_1_267F4(void);
extern const f32 lbl_1_rodata_7810;
extern const f64 lbl_1_rodata_7818[];
extern const f32 lbl_1_rodata_784C[];
extern void* fn_80038CD0(s32 count, void* pos, void* nodes, f32 a, f32 b); // RopeNode*

extern void fn_1_2004C(void);

#include "Dolphin/os.h"
extern s32 fn_80035DD4(s32);
extern void fn_80034E20(void* group, void* desc);
extern void fn_1_267BC(void);
extern ChallengeTexSlot lbl_803C4BE0[]; // SpaniTexSlot[] in main (main/file_80034F50.h)
extern char lbl_1_rodata_78F0[];
extern char lbl_1_rodata_78F8[];


extern u8 lbl_803CBBC0[];
extern void fn_800A7D4C(s32, void*);

extern void fn_80038B48(void*, void*, u8, Vec*);

extern void fn_1_1F05C(void);

extern const f64 lbl_1_rodata_7878;
extern const f64 lbl_1_rodata_7880;
extern const f64 lbl_1_rodata_7888;

extern const f32 lbl_1_rodata_77F8;
extern const f32 lbl_1_rodata_7854;
extern void fn_80038E2C(void*);


extern const f32 lbl_1_rodata_7808[];
extern const f32 lbl_1_rodata_78C4[];
extern const f32 lbl_1_rodata_78C8[];

extern s32 fn_80037BAC(void*);

typedef struct {
    u32 value;
} ChallengeLightColor;

extern ChallengeLightColor lbl_1_rodata_77B0;
extern const f32 lbl_1_rodata_7840;
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
extern void LoadActorLayout(void*);
extern void convertGeometryAndSknHeader(void* geo, void* skn);
extern void fn_800B2C08(void*, s32);
extern void fn_800BD548(ActorObject*, s32, ...);

extern const f32 lbl_1_rodata_77E4_s;


extern void* _OSAllocFromHeap(s32, s32);
extern void* memcpy(void*, const void*, u32);
extern void DCStoreRangeNoSync(void*, u32);
extern void PPCSync(void);

extern const f32 lbl_1_rodata_78AC;
extern const f32 lbl_1_rodata_78B0;
extern const f32 lbl_1_rodata_78B4;
extern const f32 lbl_1_rodata_78B8;
extern const f32 lbl_1_rodata_78BC;
extern const f32 lbl_1_rodata_78C0;
extern double cos(double);
extern int rand(void);
extern void* memset(void*, int, u32);

extern const f32 lbl_1_rodata_77E8;
extern s32 fn_80023F0C(void*, ChallengeTextureHeader*, s32, s32, s32, s32, s32, s32);
extern void DCStoreRange(void*, u32);

extern const f32 lbl_1_rodata_7844;
extern const f32 lbl_1_rodata_7848;

extern const f64 lbl_1_rodata_7828;
extern const f64 lbl_1_rodata_7830;
extern const f64 lbl_1_rodata_7838;

// Inline copy of fn_1_20950 (below) for fn_1_21CE8 and fn_1_21408, which the original inlines it into.
// fn_1_20950 keeps its own body: a wrapper around this inline allocates its stack and registers differently.
// .data of this file (0xFB98-0x1081C), in address order: the functions address it through one pooled base.
// The five switch jump tables after it (0x1081C-0x108E0) stay in an auto unit while their functions are NONMATCHING.
typedef struct ChAramAsset { // AssetLoadInstructions without the bitfields (CW rejects initialisers for those)
    u32 compression;
    u32 sizeInfo; // top 4 bits: flags, rest: size
    u32 diskLocation;
    u32 compressedSize;
} ChAramAsset;
static ChAramAsset lbl_1_data_FB98[64] = { // per-screen files loaded by fn_80035838 (last entry empty)
    {0x0000040B, 0x4023491C, 0x19135800, 0x00082928},
    {0x0000040B, 0x4013764C, 0x1A635000, 0x0007DB48},
    {0x0000040B, 0x4003E3DC, 0x1A6B3000, 0x00021420},
    {0x0000040B, 0x4002EC10, 0x1A6D4800, 0x00013108},
    {0x0000040B, 0x400E72C0, 0x1A6E8000, 0x00060768},
    {0x0000040B, 0x40049404, 0x1A748800, 0x00020E34},
    {0x0000040B, 0x40076AE0, 0x18ED7000, 0x00036BC8},
    {0x0000040B, 0x4010FD70, 0x1A769800, 0x0005E284},
    {0x0000040B, 0x400DB738, 0x1A7C8000, 0x00049AB4},
    {0x0000040B, 0x400E9864, 0x1A812000, 0x00059DC0},
    {0x0000040B, 0x400B7718, 0x1A86C000, 0x00050288},
    {0x0000040B, 0x400D87FC, 0x1A8BC800, 0x00047BC4},
    {0x0000040B, 0x400D643C, 0x1A904800, 0x0004E3AC},
    {0x0000040B, 0x400D5C7C, 0x1A953000, 0x00048D9C},
    {0x0000040B, 0x400B767C, 0x1A99C000, 0x00047518},
    {0x0000040B, 0x400441F8, 0x1A9E3800, 0x0001AA84},
    {0x0000040B, 0x40106568, 0x1A9FE800, 0x00068C10},
    {0x0000040B, 0x4010E5A0, 0x0E97A800, 0x0009BCAC},
    {0x0000040B, 0x40016980, 0x0EA16800, 0x0000D6C4},
    {0x0000040B, 0x40016980, 0x0EA24000, 0x0000C944},
    {0x0000040B, 0x40016980, 0x0EA31000, 0x0000E700},
    {0x0000040B, 0x40016980, 0x0EA3F800, 0x0000D64C},
    {0x0000040B, 0x40016980, 0x0EA4D000, 0x0000C900},
    {0x0000040B, 0x40016980, 0x0EA5A000, 0x0000CFFC},
    {0x0000040B, 0x40016980, 0x0EA67000, 0x0000D720},
    {0x0000040B, 0x40016980, 0x0EA74800, 0x0000D6CC},
    {0x0000040B, 0x40016980, 0x0EA82000, 0x0000D21C},
    {0x0000040B, 0x40016980, 0x0EA8F800, 0x0000D0BC},
    {0x0000040B, 0x40016980, 0x0EA9D000, 0x0000B544},
    {0x0000040B, 0x40016980, 0x0EAA8800, 0x0000C4F8},
    {0x0000040B, 0x400ADFFC, 0x18AEE800, 0x0004BAB0},
    {0x0000040B, 0x4037CF5C, 0x18B3A800, 0x00208AF0},
    {0x0000040B, 0x4000A820, 0x18ED3800, 0x00003758},
    {0x0000040B, 0x4011EC24, 0x18F0E000, 0x000D8818},
    {0x0000040B, 0x400193E8, 0x191B8800, 0x000089D8},
    {0x0000040B, 0x4006C850, 0x06C96000, 0x0002C884},
    {0x0000040B, 0x4005B178, 0x06CC3000, 0x0003555C},
    {0x0000040B, 0x401EB174, 0x18D43800, 0x000FB220},
    {0x0000040B, 0x4001ED60, 0x1AA67800, 0x0000CFF0},
    {0x0000040B, 0x4000BF30, 0x1AA74800, 0x000026E0},
    {0x0000040B, 0x40003498, 0x1AA77000, 0x00000E28},
    {0x0000040B, 0x4000BDE0, 0x1AA78000, 0x000024F4},
    {0x0000040B, 0x40006088, 0x1AA7A800, 0x00001290},
    {0x0000040B, 0x400049F0, 0x1AA7C000, 0x000018F4},
    {0x0000040B, 0x40005ECC, 0x1AA7E000, 0x00001D38},
    {0x0000040B, 0x40002670, 0x1AA80000, 0x00000BE8},
    {0x00000000, 0x00028240, 0x1AA81000, 0x00028240},
    {0x00000000, 0x00028240, 0x1AAA9800, 0x00028240},
    {0x00000000, 0x00028240, 0x1AAD2000, 0x00028240},
    {0x00000000, 0x00028240, 0x1AAFA800, 0x00028240},
    {0x00000000, 0x00028240, 0x1AB23000, 0x00028240},
    {0x00000000, 0x00028240, 0x1AB4B800, 0x00028240},
    {0x00000000, 0x00028240, 0x1AB74000, 0x00028240},
    {0x00000000, 0x00028240, 0x1AB9C800, 0x00028240},
    {0x00000000, 0x00028240, 0x1ABC5000, 0x00028240},
    {0x00000000, 0x00028240, 0x1ABED800, 0x00028240},
    {0x00000000, 0x00028240, 0x1AC16000, 0x00028240},
    {0x00000000, 0x00028240, 0x1AC3E800, 0x00028240},
    {0x00000000, 0x00028240, 0x1AC67000, 0x00028240},
    {0x00000000, 0x00028240, 0x1AC8F800, 0x00028240},
    {0x00000000, 0x00028240, 0x1ACB8000, 0x00028240},
    {0x00000000, 0x00028240, 0x1ACE0800, 0x00028240},
    {0x00000000, 0x00028240, 0x1AD09000, 0x00028240},
    {0x00000000, 0x00000000, 0x00000000, 0x00000000},
};
static char sScreenNames[47][0x14] = { // names of the lbl_1_data_FB98 files (unreferenced)
    "game_td", "result", "operation", "game_toy", "game_slot", "score",
    "rule_toy", "rule_mini_01", "rule_mini_02", "rule_mini_03", "rule_mini_05", "rule_mini_04",
    "rule_mini_06", "rule_mini_07", "training", "common", "logo_all", "logo_00",
    "logo_01", "logo_02", "logo_03", "logo_04", "logo_05", "logo_06",
    "logo_07", "logo_08", "logo_09", "logo_10", "logo_11", "chara_sel",
    "select", "dictionary", "score", "end", "option", "logo_all",
    "title", "comingsoon", "bg_test", "load", "fade00", "fade01",
    "fade02", "fade03", "fade04", "fade05", "fade06",
};
static ChallengeSpriteDesc lbl_1_data_10344 = {0, 0, 0.0f, 0.0f, {0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x04, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
static u32 lbl_1_data_10384[56] = { // bone axis colours (RGBA)
    0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF,
    0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF,
    0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF,
    0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF,
    0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF,
    0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF,
    0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF,
    0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF,
};
static s32 sCam8CC = 100;
static f32 sCamWidth = 200.0f;  // cfg + 0x8D0
static f32 sCamHeight = 100.0f; // cfg + 0x8D4
static f32 sCam8D8 = 20.0f;
static s32 sCam8DC = 10;
static f32 sCam8E0 = 1.0f;
static f32 sCam8E4 = 1.0f;
static Vec sCamUp = {0.0f, -1.0f, 0.0f};
static Vec sCamPos = {0.0f, 0.0f, -5.0f};
static Vec sCamTarget = {0.0f, 0.0f, 0.0f};
static f32 lbl_1_data_104A4 = 50.0f; // bone axis length
static void (*lbl_1_data_104A8[4])(void) = {fn_1_1F2D8, fn_1_24410, fn_1_22644, fn_1_2040C};
static f32 s104B8 = 0.3f;
static f32 s104BC = 0.031496063f; // cfg + 0x924
static f32 s104C0 = 1.0f; // cfg + 0x928
static f32 s104C4 = 0.98f; // cfg + 0x92C
static f32 s104C8 = 0.05f;
static s32 s104CC = 0x400;
static Vec lbl_1_data_104D0 = {0.125f, 0.125f, 0.125f};
static u32 lbl_1_data_104DC[6] = {0xFF8080FF, 0x80FF80FF, 0x8080FFFF, 0xFFFF80FF, 0xFF80FFFF, 0x80FFFFFF};
static ChAramAsset lbl_1_data_104F4 = {0x0000040B, 0x40000528, 0x09438800, 0x00000424};
static f32 s10504 = 0.125f;
static void (*lbl_1_data_10508[2])(ChallengeTextureStages*) = {fn_1_1FD78, fn_1_1F418};
static void (*lbl_1_data_10510[2])(ChallengeTextureStages*) = {fn_1_1F900, fn_1_1F618};
static ChAramAsset lbl_1_data_10518[21] = {
    {0x0000040B, 0x40168A6C, 0x06CFD000, 0x000C69A8},
    {0x0000040B, 0x401331E0, 0x06DC4000, 0x000B67C4},
    {0x0000040B, 0x4011924C, 0x06E7A800, 0x000A5764},
    {0x0000040B, 0x400FBAE0, 0x06F20000, 0x000BE038},
    {0x0000040B, 0x400E5AC0, 0x06FDE800, 0x000B4FB8},
    {0x0000040B, 0x40131200, 0x07093800, 0x000A317C},
    {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
    {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
    {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
    {0x0000040B, 0x40141C60, 0x07207800, 0x000CE904},
    {0x0000040B, 0x4013CA40, 0x072D6800, 0x000CA560},
    {0x0000040B, 0x40141C60, 0x07207800, 0x000CE904},
    {0x0000040B, 0x4016C138, 0x073A1000, 0x000ED41C},
    {0x0000040B, 0x401157B8, 0x0748E800, 0x000CA83C},
    {0x0000040B, 0x4016C138, 0x073A1000, 0x000ED41C},
    {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
    {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
    {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
    {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
    {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
    {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
};
static s16 (*lbl_1_data_10668[1])(s16, u16, u16, u16) = {fn_1_1DE60};
static void (*lbl_1_data_1066C[1])(s16) = {(void (*)(s16))fn_1_1DE5C};
static s32 lbl_1_data_10670[1] = {4};
static ChAramAsset lbl_1_data_10674[21] = {
    {0x0000040B, 0x40168A6C, 0x06CFD000, 0x000C69A8},
    {0x0000040B, 0x401331E0, 0x06DC4000, 0x000B67C4},
    {0x0000040B, 0x4011924C, 0x06E7A800, 0x000A5764},
    {0x0000040B, 0x400FBAE0, 0x06F20000, 0x000BE038},
    {0x0000040B, 0x400E5AC0, 0x06FDE800, 0x000B4FB8},
    {0x0000040B, 0x40131200, 0x07093800, 0x000A317C},
    {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
    {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
    {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
    {0x0000040B, 0x40141C60, 0x07207800, 0x000CE904},
    {0x0000040B, 0x4013CA40, 0x072D6800, 0x000CA560},
    {0x0000040B, 0x40141C60, 0x07207800, 0x000CE904},
    {0x0000040B, 0x4016C138, 0x073A1000, 0x000ED41C},
    {0x0000040B, 0x401157B8, 0x0748E800, 0x000CA83C},
    {0x0000040B, 0x4016C138, 0x073A1000, 0x000ED41C},
    {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
    {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
    {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
    {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
    {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
    {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
};
static u8 lbl_1_data_107C4[32] = {0, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 8, 2, 3, 4, 5, 6, 7, 8, 9, 3, 4, 5, 6, 7, 8, 9, 10};
static ChallengeAnimEntry lbl_1_data_107E4[2] = {{NULL, fn_1_1D694}, {NULL, fn_1_1D694}};

static inline void updateRopeObjects(ChallengeCurvePoint* points, s32 count, MtxPtr camera) {
    ActorObject* obj;
    s32 i;
    Vec delta;
    Vec mid;
    Quaternion rot;
    Quaternion align;
    Mtx mtx;
    f32 angle;
    f32 zero;

    i = 20;
    while (i-- != 0) {
        obj = &lbl_1_bss_6BE0[0]->objects[i];
        obj->animateBones = i < count;
        if (i < count) {
            PSVECSubtract(&points[i + 1].position, &points[i].position, &delta);
            PSVECScale(&delta, lbl_1_rodata_7814[0], &mid);
            PSVECAdd(&points[i].position, &mid, &mid);
            CTRLSetTranslation(&obj->worldControl.base, mid.x, -mid.y, mid.z);
            if (PSVECMag(&delta)) {
                PSVECNormalize(&delta, &delta);
                delta.y = -delta.y;
                mid.x = lbl_1_rodata_77E4;
                mid.y = lbl_1_rodata_77D8;
                mid.z = lbl_1_rodata_77D8;
                C_QUATRotAxisRad(&rot, &mid,
                    lbl_1_rodata_7828 * (lbl_1_rodata_7830 + (i & 1)) / lbl_1_rodata_7838);
                angle = acos(PSVECDotProduct(&delta, &mid));
                PSVECCrossProduct(&mid, &delta, &mid);
                if (PSVECMag(&mid)) {
                    C_QUATRotAxisRad(&align, &mid, angle);
                    PSQUATMultiply(&align, &rot, &rot);
                }
                CTRLSetQuat(&obj->worldControl.base, rot.x, rot.y, rot.z, rot.w);
            }
            CTRLSetScale(&obj->worldControl.base, lbl_1_data_104D0.x, lbl_1_data_104D0.y, lbl_1_data_104D0.z);
            fn_800BDA24(obj);
        }
        zero = *(volatile f32*)&lbl_1_rodata_77D8;
        PSMTXTrans(mtx, zero, zero, zero);
        PSMTXConcat(camera, mtx, mtx);
        obj->actor->flags |= 3;
    }
    fn_800BD670(lbl_1_bss_6BE0[0], (MtxPtr)camera);
}

extern const f32 lbl_1_rodata_7894;
extern const f32 lbl_1_rodata_7898;

#define CHALLENGE_PAD_TRIGGER (lbl_803C77B8._04)

extern const f32 lbl_1_rodata_77FC;


extern const f32 lbl_1_rodata_78A4;
extern const f32 lbl_1_rodata_78D4;
extern const f32 lbl_1_rodata_78D8;
extern const f32 lbl_1_rodata_78DC;
extern const f32 lbl_1_rodata_78E0;

extern const f32 lbl_1_rodata_7800;

static inline void fn_1_1DE60_adjust(f32* value, u16 held, s32 decrease, f32 min, f32 max) {
    f32 v;
    f32 step;

    step = lbl_1_rodata_77F8;
    v = *value;
    if (held & 0x40) {
        step = lbl_1_rodata_77FC;
    } else if (held & 0x20) {
        step = lbl_1_rodata_7800;
    }
    if (decrease) {
        step = -step;
    }
    v += step;
    if (v < min) {
        v = min;
    }
    if (v > max) {
        v = max;
    }
    *value = v;
}

static inline void fn_1_1E290_adjust(f32* value, u16 held, s32 decrease) {
    f32 v;
    f32 step;
    step = lbl_1_rodata_77F8;
    v = *value;
    if (held & 0x40) {
        step = lbl_1_rodata_77FC;
    } else if (held & 0x20) {
        step = lbl_1_rodata_7800;
    }
    if (decrease) {
        step = -step;
    }
    v += step;
    if (v < lbl_1_rodata_7804) {
        v = lbl_1_rodata_7804;
    }
    if (v > lbl_1_rodata_7808[0]) {
        v = lbl_1_rodata_7808[0];
    }
    *value = v;
}


#if NONMATCHING
static inline f32 fn_1_1E90C_adjust(f32 value, u16 held, s32 decrease, f32 min, f32 max) {
    f32 v;
    f32 step;

    step = lbl_1_rodata_77F8;
    if (held & 0x40) {
        step = lbl_1_rodata_77FC;
    } else if (held & 0x20) {
        step = lbl_1_rodata_7800;
    }
    if (decrease) {
        step = -step;
    }
    v = value + step;
    if (v < min) {
        v = min;
    }
    if (v > max) {
        v = max;
    }
    return v;
}
#endif

extern const f32 lbl_1_rodata_78CC;
extern const f32 lbl_1_rodata_78D0;

extern const f32 lbl_1_rodata_786C;
extern const f64 lbl_1_rodata_7870;

#define CHALLENGE_PAD_STICK_Y (lbl_803C77B8.triggerR)

#include "Dolphin/mtxext.h"

extern const f32 lbl_1_rodata_7890;

extern const f32 lbl_1_rodata_789C;
extern const f32 lbl_1_rodata_78A0;
extern const f32 lbl_1_rodata_78A8;
extern void fn_1_121D4(u8* camera);

extern const f32 lbl_1_rodata_7850;

// Shared by fn_1_21CE8 / fn_1_21408: drive the rope's free end with the stick, then simulate it.
static inline void fn_1_21CE8_moveRope(ChallengeCurveDrawing* q) {
    ChallengeCurvePoint* tip;
    Vec force;
    f32 speed;

    if (q->colorMode != 0) {
        // move the free end of the rope directly
        if (lbl_803C77B8.triggerR3 >= 0x50) {
            speed = lbl_1_rodata_77FC * q->unk1C;
        } else {
            speed = lbl_1_rodata_7850 * q->unk1C;
        }
        lbl_1_bss_6FE0[q->pointCount - 1].position.x += lbl_803C77B8.stickX3 * speed;
        lbl_1_bss_6FE0[q->pointCount - 1].position.y += lbl_803C77B8.substickY3 * speed;
        lbl_1_bss_6FE0[q->pointCount - 1].position.z += lbl_803C77B8.stickY3 * speed;
        tip = &lbl_1_bss_6FE0[q->pointCount - 1];
        memcpy(&tip->prevPos, &tip->position, sizeof(Vec));
        force.x = lbl_1_rodata_77D8;
        force.y = lbl_1_rodata_77D8;
        force.z = lbl_1_rodata_77D8;
    } else {
        // or pull it with a force
        force.x = q->unk1C * (lbl_803C77B8.stickX3 * lbl_1_bss_6FE0[q->pointCount - 1].mass);
        force.y = q->unk1C * (lbl_803C77B8.substickY3 * lbl_1_bss_6FE0[q->pointCount - 1].mass);
        force.z = q->unk1C * (lbl_803C77B8.stickY3 * lbl_1_bss_6FE0[q->pointCount - 1].mass);
    }
    fn_80038B48(&lbl_1_bss_6FB8, lbl_1_bss_6FE0, q->pointCount, &force);
}

static inline void fn_1_21CE8_setupDraw(void) {
    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXLoadPosMtxImm(lbl_1_bss_43EE0.view, 0);
    GXSetCurrentMtx(0);
}

extern void fn_80035A00(void);
extern void fn_1_26928(void);
extern const ChallengeMtxBox lbl_1_rodata_7780;
extern const f32 lbl_1_rodata_78E4;
extern const f32 lbl_1_rodata_78E8;
extern const f32 lbl_1_rodata_78EC;

#define CHALLENGE_TEX_SLOTS lbl_803C4BE0
#define CHALLENGE_SPRITE_OBJ(q) (lbl_80371C30[(q)->sprite->slot].obj)

// .text:0x00026A34 size:0xC4
void fn_1_26A34(void) {
    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}

// .text:0x00026928 size:0x10C
void fn_1_26928(void) {
    ChallengeSpriteViewer* queue = (ChallengeSpriteViewer*)lbl_803CC1B8;
    u16 repeated = lbl_803C77B8._04;
    if (repeated & 2) {
        queue->screen++;
        if (queue->screen == queue->screenCount) {
            queue->screen = 0;
        }
    } else if (repeated & 1) {
        if (queue->screen == 0) {
            queue->screen = queue->screenCount;
        }
        queue->screen--;
    } else {
        u16 pressed = lbl_803C77B8._02;
        if (pressed & 0x100) {
            queue->step = 0;
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_267F4;
        } else if (pressed & 0x200) {
            ChallengeTransfer* transfer;
            fn_800AD038(lbl_80366158[2]);
            transfer = (ChallengeTransfer*)((ChTaskHeader*)lbl_803CC1B8)->parent;
            transfer->complete = 1;
            fn_800B0A14_removeQueue(transfer);
        } else if (pressed & 0x1000) {
            queue->func = fn_1_25C68;
        }
    }
    fn_800B24D4(4);
    fn_800B1188();
}

// .text:0x000267F4 size:0x134
void fn_1_267F4(void) {
    ChallengeSpriteViewer* queue = (ChallengeSpriteViewer*)lbl_803CC1B8;
    switch (queue->step) {
    case 0:
        if (fn_80035838(&lbl_1_data_FB98[queue->screen], 0) != 0) {
            queue->step = queue->step + 1;
        }
        break;
    case 1: {
        s32 index;
        ChallengeTexSlot* entry;
        queue->sprite = fn_800B0A5C_insertQueue((void*)fn_1_267BC, 1);
        queue->sprite->done = 0;
        index = fn_80035DD4(0);
        if (index == -1) {
            OSPanic(lbl_1_rodata_78F0, 0xF5, lbl_1_rodata_78F8);
        }
        entry = CHALLENGE_TEX_SLOTS;
        entry += index;
        queue->trackCount = entry->anim->table->count;
        fn_80034E20(queue->sprite, &lbl_1_data_10344);
        queue->track = 0;
        queue->cursor = 0;
        queue->frame = 0;
        queue->x = 0;
        queue->y = 0;
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_25F98;
        break;
    }
    }
}

// .text:0x000267BC size:0x38
void fn_1_267BC(void) {
    if (((ChTaskHeader*)lbl_803CC1B8)->result != 0) {
        fn_800B0A14_removeQueue((u8*)lbl_803CC1B8);
    }
}

// NONMATCHING 99%: scheduling only, in the case-3 write-back and the SetDisplayStateTexture argument setup
// .text:0x25F98 size:0x824
#if NONMATCHING
void fn_1_25F98(void) {
    ChallengeSpriteViewer* q = (ChallengeSpriteViewer*)lbl_803CC1B8;
    AnimFrame frame;
    ChallengeMtxBox mtx;
    ChallengeTexSlot* bank;
    s32 i;

    for (i = 0; i < 6; i++) {
        switch (i) {
        case 0:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 2) {
                    fn_80034CEC(q->sprite);
                    q->track++;
                    if (q->track == q->trackCount) {
                        q->track = 0;
                    }
                    q->frame = 0;
                    lbl_1_data_10344.track = q->track;
                    fn_80034E20(q->sprite, &lbl_1_data_10344);
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    fn_80034CEC(q->sprite);
                    if (q->track == 0) {
                        q->track = q->trackCount;
                    }
                    q->track--;
                    q->frame = 0;
                    lbl_1_data_10344.track = q->track;
                    fn_80034E20(q->sprite, &lbl_1_data_10344);
                } else if (lbl_803C77B8._02 & 0x100) {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 1;
                } else if (lbl_803C77B8._02 & 0x200) {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 0;
                } else if (lbl_803C77B8._02 & 0x400) {
                    CHALLENGE_SPRITE_OBJ(q)->_5C = 0;
                }
            }
            break;
        case 1:
            if (i == q->cursor) {
                if (lbl_803C77B8._02 & 0x100) {
                    q->hold = !q->hold;
                }
                if (q->hold != 0) {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 0;
                } else {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 1;
                }
                if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->hold != 0) {
                        CHALLENGE_SPRITE_OBJ(q)->_68 = 1;
                    }
                } else if ((CHALLENGE_PAD_TRIGGER & 1) && q->hold != 0) {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 4;
                }
            }
            break;
        case 2:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->frame++;
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->frame--;
                }
            }
            fn_8000CEF0(CHALLENGE_TEX_SLOTS[CHALLENGE_SPRITE_OBJ(q)->_66].anim, q->track, 0, q->frame, (u32*)&frame);
            break;
        case 3:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 2) {
                    frame.subTrack++;
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    frame.subTrack--;
                }
                // write the edited texture index back into the track's first entry
                CHALLENGE_TEX_SLOTS[CHALLENGE_SPRITE_OBJ(q)->_66].anim->table->tracks[q->track]->blocks[0]->entries[0].size
                    = frame.subTrack;
            }
            break;
        case 4:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 0x800) {
                    q->x = 0;
                } else if (CHALLENGE_PAD_TRIGGER & 0x400) {
                    q->x = 320;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->x += 8;
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->x -= 8;
                }
                lbl_1_data_10344.x = q->x;
                CHALLENGE_SPRITE_OBJ(q)->x = q->x;
            }
            break;
        case 5:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 0x800) {
                    q->y = 0;
                } else if (CHALLENGE_PAD_TRIGGER & 0x400) {
                    q->y = 224;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->y += 8;
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->y -= 8;
                }
                lbl_1_data_10344.y = q->y;
                CHALLENGE_SPRITE_OBJ(q)->y = q->y;
            }
            break;
        }
    }
    if (lbl_803C77B8._02 & 4) {
        q->cursor++;
        if (q->cursor == 6) {
            q->cursor = 0;
        }
    } else if (lbl_803C77B8._02 & 8) {
        if (q->cursor == 0) {
            q->cursor = 6;
        }
        q->cursor--;
    }
    if (lbl_803C77B8._02 & 0x1000) {
        fn_80034CEC(q->sprite);
        q->sprite->done = 1;
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_26928;
        fn_80035A00();
    }

    // draw the selected texture of the bank as a quad
    mtx = lbl_1_rodata_7780;
    if (lbl_1_bss_6BD8 != 0) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXLoadPosMtxImm(mtx.m, 0);
        GXSetCurrentMtx(0);
        bank = &CHALLENGE_TEX_SLOTS[CHALLENGE_SPRITE_OBJ(q)->_66];
        SetDisplayStateTexture((struct TexImage*)(bank->tex + lbl_1_bss_6BDC * 32 + 4), 0, 0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E4;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E8;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78EC;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E8;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 1;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7814[0];
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78EC;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E8;
        GXWGFifo.u16 = 1;
        GXWGFifo.u16 = 1;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7814[0];
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E4;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E8;
        GXWGFifo.u16 = 1;
        GXWGFifo.u16 = 0;
    }
}
#endif

// NONMATCHING 89%: orig hoists the lbl_1_data_FB98 pool base into r30 before C_MTXFrustum; the inlined fn_1_24A8C has its own f-reg swap
// .text:0x25C68 size:0x330
#if NONMATCHING
void fn_1_25C68(void) {
    ChallengePathTest* q = (ChallengePathTest*)lbl_803CC1B8;
    GXColor clear;

    *(u32*)&clear = 0;
    GXSetCopyClear(clear, 0xFFFFFF);
    C_MTXFrustum(lbl_1_bss_47010, lbl_1_rodata_78D4, lbl_1_rodata_78D8, lbl_1_rodata_78DC, lbl_1_rodata_78E0,
        (&lbl_1_rodata_77E4)[0], lbl_1_rodata_7868);
    C_MTXLookAt(lbl_1_bss_43F38, &sCamPos, &sCamUp,
        &sCamTarget);
    q->param2 = lbl_1_rodata_78A4 * sCamWidth;
    q->param3 = lbl_1_rodata_78A4 * sCamHeight;
    q->param0 = sCam8D8;
    q->param4 = 0x20;
    q->steps = sCam8DC;
    q->force = 10;
    q->count = 20;
    q->param5 = lbl_1_rodata_78A4 * sCam8E4;
    q->mass = lbl_1_rodata_78A4 * sCam8E0;
    q->param1 = lbl_1_rodata_7814[0];
    q->unk26 = 100;
    q->unk28 = 10;
    fn_1_24A8C();
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_25064;
    q->cursor = 0;
}
#endif

// NONMATCHING 86%: the original inlines fn_1_248BC (and fn_1_24A8C/fn_1_247A0) here; ours calls fn_1_248BC
// .text:0x25064 size:0xC04
// nmverify: fn_1_248BC inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_1_25064(void) {
    ChallengePathTest* q = (ChallengePathTest*)lbl_803CC1B8;
    s32 big;
    s32 small;
    s32 i;

    if (lbl_803C77B8._00 & 0x20) {
        big = 4;
        small = 1;
    } else {
        big = 64;
        small = 10;
    }
    for (i = 0; i < 11; i++) {
        switch (i) {
        case 0:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->count--;
                    fn_1_24A8C();
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->count++;
                    fn_1_24A8C();
                }
            }
            break;
        case 1:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->steps--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->steps++;
                }
                if (q->steps == 0) {
                    q->steps = 1;
                }
            }
            break;
        case 2:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param2 -= big;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param2 += big;
                }
            }
            break;
        case 3:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param3 -= big;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param3 += big;
                }
            }
            break;
        case 4:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param0 -= small;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param0 += small;
                }
            }
            break;
        case 5:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->mass -= big;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->mass += big;
                }
            }
            break;
        case 6:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->force--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->force++;
                }
            }
            break;
        case 7:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param5 -= small;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param5 += small;
                }
            }
            break;
        case 8:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->unk26 -= small;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->unk26 += small;
                }
            }
            break;
        case 9:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param4 -= big;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param4 += big;
                }
            }
            break;
        case 10:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->unk28 -= small;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->unk28 += small;
                }
            }
            break;
        }
    }
    if (CHALLENGE_PAD_TRIGGER & 8) {
        if (q->cursor == 0) {
            q->cursor = 11;
        }
        q->cursor--;
    } else if (CHALLENGE_PAD_TRIGGER & 4) {
        q->cursor++;
        if (q->cursor == 11) {
            q->cursor = 0;
        }
    } else if (lbl_803C77B8._02 & 0x100) {
        fn_1_24A8C();
    } else if (lbl_803C77B8._02 & 0x200) {
        GXColor clearColor;
        ChallengeTransfer* transfer;

        *(u32*)&clearColor = 0x11775500;
        GXSetCopyClear(clearColor, 0xFFFFFF);
        transfer = ((ChallengePathTest*)lbl_803CC1B8)->transfer;
        transfer->complete = 1;
        fn_800B0A14_removeQueue(transfer);
    }
    fn_1_247A0();
    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXLoadPosMtxImm(lbl_1_bss_43F38, 0);
    GXSetCurrentMtx(0);
    fn_1_AF4(11, 11, lbl_1_rodata_7848);
    fn_1_248BC(q->count);
}
#endif

// .text:0x24C4C size:0x418
void fn_1_24C4C(ChallengeRopeNode* nodes, s32 count, Vec* force, f32 springK, f32 damping, f32 restLen, f32 dtScale) {
    ChallengePathTest* q = (ChallengePathTest*)lbl_803CC1B8;
    f32 drag;
    s32 k;
    ChallengeRopeNode* node;
    ChallengeRopeNode* prev;
    Vec d;
    Vec dv;
    Vec n;
    f32 first;
    f32 speed;
    f32 len;
    f32 damp;
    f32 stretch;
    f32 friction;
    f32 mag;
    f32 coef;
    s32 i;
    s32 j;

    drag = lbl_1_rodata_7820[0] * dtScale;
    first = lbl_1_rodata_77E4;
    i = count;
    while (i-- != 0) {
        node = &nodes[i];
        if (node->fixed != 0) {
            node->force.x = node->force.y = node->force.z = lbl_1_rodata_77D8;
        } else {
            node->force.x = node->force.z = lbl_1_rodata_77D8;
            node->force.y = lbl_1_rodata_78CC * node->mass;
        }
        speed = PSVECMag(&node->vel);
        if (speed != lbl_1_rodata_77D8) {
            PSVECScale(&node->vel, drag, &d);
            PSVECNormalize(&d, &d);
            PSVECScale(&d, (q->param5 / lbl_1_rodata_78C8[0]) * (speed * speed), &d);
            PSVECAdd(&node->force, &d, &node->force);
        }
        if (first != lbl_1_rodata_77D8) {
            PSVECAdd(&node->force, force, &node->force);
            first = lbl_1_rodata_77D8;
        }
    }

    j = count;
    while (--j != 0) {
        node = &nodes[j];
        prev = &nodes[j - 1];
        PSVECSubtract(&node->pos, &prev->pos, &d);
        PSVECSubtract(&node->vel, &prev->vel, &dv);
        PSVECScale(&dv, dtScale, &dv);
        len = PSVECMag(&d);
        damp = damping * (PSVECDotProduct(&dv, &d) / len);
        PSVECNormalize(&d, &n);
        stretch = springK * (len - restLen);
        PSVECScale(&n, -(stretch + damp), &n);
        if (node->fixed == 0) {
            PSVECAdd(&node->force, &n, &node->force);
        }
        PSVECScale(&n, lbl_1_rodata_7820[0], &n);
        if (prev->fixed == 0) {
            PSVECAdd(&prev->force, &n, &prev->force);
        }
    }

    k = count;
    while (k-- != 0) {
        node = &nodes[k];
        if (node->fixed == 0 && node->pos.y <= q->unk28 / lbl_1_rodata_78D0
            && lbl_1_rodata_77D8 != PSVECMag(&node->vel)) {
            coef = q->param4 * lbl_1_rodata_78C4[0];
            friction = coef * node->force.y;
            if (friction < lbl_1_rodata_77D8) {
                friction = -friction;
            }
            memcpy(&d, &node->force, sizeof(Vec));
            d.y = lbl_1_rodata_77D8;
            mag = PSVECMag(&d);
            if (mag != lbl_1_rodata_77D8) {
                PSVECNormalize(&d, &d);
                if (friction > mag) {
                    PSVECScale(&d, -mag, &d);
                } else {
                    PSVECScale(&d, -friction, &d);
                }
                PSVECAdd(&d, &node->force, &node->force);
            }
        }
    }
}

// NONMATCHING 91%: f3/f6 swap for 1.0f vs int->float magic, and the tail 78C4 load is CSE'd with the head (orig reloads, addi form)
// .text:0x24A8C size:0x1C0
#if NONMATCHING
void fn_1_24A8C(void) {
    ChallengePathTest* q = (ChallengePathTest*)lbl_803CC1B8;
    s32 n;
    f32 t;

    fn_80038E2C(&lbl_1_bss_45868);
    lbl_1_bss_45868.params[0] = q->param0;
    lbl_1_bss_45868.params[1] = q->param1;
    lbl_1_bss_45868.params[2] = q->param2 * lbl_1_rodata_78C4[0];
    lbl_1_bss_45868.params[3] = q->param3 * lbl_1_rodata_78C4[0];
    lbl_1_bss_45868.params[4] = q->param4 * lbl_1_rodata_78C4[0];
    lbl_1_bss_45868.params[5] = q->param5 / lbl_1_rodata_78C8[0];
    n = q->steps;
    lbl_1_bss_45868.steps = n;
    t = (&lbl_1_rodata_77E4)[0] / (f32)n;
    lbl_1_bss_45868.step = t;
    lbl_1_bss_45868.stepSq = t * t;
    lbl_1_bss_45868.inv = (&lbl_1_rodata_77E4)[0] / ((&lbl_1_rodata_780C)[0] * t);
    if (lbl_803C77B8._00 & 0x40) {
        lbl_1_bss_45868.steps = 1;
    }
    fn_80038CD0(q->count, &lbl_1_bss_45868, lbl_1_bss_43F68, lbl_1_rodata_7808[0], q->mass * lbl_1_rodata_78C4[0]);
}
#endif

// .text:0x248BC size:0x1D0
void fn_1_248BC(s32 count) {
    u8 width;
    GXTexOffset offset;
    s32 i;
    ChallengePathNode* node;

    GXGetLineWidth(&width, &offset);
    GXSetLineWidth(0x18, offset);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, count);
    i = count;
    while (i-- != 0) {
        node = &lbl_1_bss_43F68[i];
        GXWGFifo.f32 = node->position.x;
        GXWGFifo.f32 = node->position.y;
        GXWGFifo.f32 = node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i];
    }
    GXSetLineWidth(width, offset);
    GXBegin(GX_LINES, GX_VTXFMT0, count * 4);
    i = count;
    while (i-- != 0) {
        node = &lbl_1_bss_43F68[i];
        GXWGFifo.f32 = node->position.x;
        GXWGFifo.f32 = node->position.y;
        GXWGFifo.f32 = node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i];
        GXWGFifo.f32 = lbl_1_data_104A4 * node->up.x + node->position.x;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->up.y + node->position.y;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->up.z + node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i];
        GXWGFifo.f32 = node->position.x;
        GXWGFifo.f32 = node->position.y;
        GXWGFifo.f32 = node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i] ^ 0xFFFFFF00;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->side.x + node->position.x;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->side.y + node->position.y;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->side.z + node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i] ^ 0xFFFFFF00;
    }
}

// .text:0x247A0 size:0x11C
void fn_1_247A0(void) {
    ChallengePathTest* q = (ChallengePathTest*)lbl_803CC1B8;
    u16 speed = q->force;
    Vec v;

    v.x = speed * (lbl_803C77B8.stickX * lbl_1_bss_43F68[q->count - 1].scale);
    v.y = speed * (lbl_803C77B8.substickY * lbl_1_bss_43F68[q->count - 1].scale);
    v.z = speed * (lbl_803C77B8.stickY * lbl_1_bss_43F68[q->count - 1].scale);
    fn_80038B48(&lbl_1_bss_45868, lbl_1_bss_43F68, q->count, &v);
}

// .text:0x00024778 size:0x28
void fn_1_24778(void) {
    ((ChallengeTestMenu*)lbl_803CC1B8)->cursor = 0;
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_246AC;
}

// .text:0x000246AC size:0xCC
void fn_1_246AC(void) {
    ChallengeTestMenu* queue = (ChallengeTestMenu*)lbl_803CC1B8;
    u16 repeated = lbl_803C77B8._04;
    if (repeated & 8) {
        if (queue->cursor == 0) {
            queue->cursor = 4;
        }
        queue->cursor--;
    } else if (repeated & 4) {
        queue->cursor++;
        if (queue->cursor == 4) {
            queue->cursor = 0;
        }
    } else {
        u16 pressed = lbl_803C77B8._02;
        if (pressed & 0x100) {
            queue->h.func = lbl_1_data_104A8[queue->cursor];
        } else if (pressed & 0x200) {
            ChallengeTransfer* transfer = (ChallengeTransfer*)queue->h.parent;
            transfer->complete = 1;
            fn_800B0A14_removeQueue(transfer);
        }
    }
}

// .text:0x24410 size:0x29C
void fn_1_24410(void) {
    ChallengeWaveState* q = (ChallengeWaveState*)lbl_803CC1B8;
    s32 i;
    s32 j;

    fn_1_23AD8(lbl_1_bss_47010, &lbl_1_bss_43EE0.camera, &lbl_1_bss_43EE0.target);
    lbl_1_bss_43EE0.unk30 = 0;
    lbl_1_bss_43EE0.unk38 = (&lbl_1_rodata_77D8)[0];
    lbl_1_bss_43EE0.unk32 = 0;
    q->lines = 0x40;
    q->rows = 0x40;
    q->cols = 0x40;
    q->freeze = 0;
    q->farZ = lbl_1_rodata_78AC;
    q->nearZ = lbl_1_rodata_78B0;
    q->frame = 0;
    q->impulse = lbl_1_rodata_78B4;
    q->unk20 = lbl_1_rodata_78B8;
    q->waveOn = 1;
    for (i = 0; i < 0x80; i++) {
        lbl_1_bss_74E0[i] = cos(lbl_1_rodata_78BC * (lbl_1_rodata_780C * ((f32)i * lbl_1_rodata_78C0)));
    }
    q->buffer = 0;
    memset(lbl_1_bss_76E0, 0, sizeof(lbl_1_bss_76E0));
    for (j = 0; j < 0x20; j++) {
        i = rand() % 32 * 128;
        i += rand() % 128;
        lbl_1_bss_76E0[0][i] = lbl_1_rodata_77E4;
    }
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_23B54;
}

// NONMATCHING 90%: inherits fn_1_22F4C's indexing mismatch (inlined), and the height lookup uses lfs/add instead of lfsx
// .text:0x23B54 size:0x8BC
#if NONMATCHING
void fn_1_23B54(void) {
    ChallengeWaveState* q = (ChallengeWaveState*)lbl_803CC1B8;
    s32 i;
    s32 c;
    s32 r;
    s32 row;
    s32 ix;
    s32 even;
    u8 cur;
    f32 fx;
    f32 fz;
    f32 h;
    f32 maxH;
    f32 minH;
    Vec* p;

    for (i = 0; i < 8; i++) {
        switch (i) {
        case 0:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->lines == 2) {
                        q->lines = 112;
                    }
                    q->lines--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->lines == 112) {
                        q->lines = 2;
                    }
                    q->lines++;
                }
            }
            break;
        case 1:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->cols == 2) {
                        q->cols = 160;
                    }
                    q->cols--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->cols == 160) {
                        q->cols = 2;
                    }
                    q->cols++;
                }
            }
            break;
        case 2:
            if (i == q->cursor && (CHALLENGE_PAD_TRIGGER & 3)) {
                q->freeze = !q->freeze;
            }
            break;
        case 3:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->farZ > lbl_1_rodata_77E4) {
                        q->farZ -= lbl_1_rodata_77E4;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->farZ < lbl_1_rodata_7868) {
                        q->farZ += lbl_1_rodata_77E4;
                    }
                }
            }
            break;
        case 4:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->nearZ > lbl_1_rodata_77E4) {
                        q->nearZ -= lbl_1_rodata_77E4;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->nearZ < lbl_1_rodata_7868) {
                        q->nearZ += lbl_1_rodata_77E4;
                    }
                }
            }
            break;
        case 5:
            if (i == q->cursor && (CHALLENGE_PAD_TRIGGER & 3)) {
                q->waveOn = !q->waveOn;
            }
            break;
        case 6:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->impulse > lbl_1_rodata_77D8) {
                        q->impulse -= lbl_1_rodata_786C;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->impulse < lbl_1_rodata_77E4) {
                        q->impulse += lbl_1_rodata_786C;
                    }
                }
            }
            break;
        case 7:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->unk20 > lbl_1_rodata_77D8) {
                        q->unk20 -= lbl_1_rodata_786C;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->unk20 < lbl_1_rodata_77E4) {
                        q->unk20 += lbl_1_rodata_786C;
                    }
                }
            }
            break;
        }
    }
    if (CHALLENGE_PAD_TRIGGER & 8) {
        if (q->cursor == 0) {
            q->cursor = 8;
        }
        q->cursor--;
    } else if (CHALLENGE_PAD_TRIGGER & 4) {
        q->cursor++;
        if (q->cursor == 8) {
            q->cursor = 0;
        }
    } else if (lbl_803C77B8._02 & 0x200) {
        ((ChallengeWaveState*)lbl_803CC1B8)->func = fn_1_24778;
    } else if (CHALLENGE_PAD_TRIGGER & 0x100) {
        for (i = 0; i < 16; i++) {
            row = rand() % 32;
            lbl_1_bss_76E0[0][row * 128 + rand() % 128] += q->impulse;
        }
    }

    fn_1_121D4((u8*)&lbl_1_bss_43EE0);
    if (q->freeze == 0) {
        q->rows = fn_1_23098(lbl_1_bss_47010, lbl_1_bss_43EE0.view, q->lines, q->cols, q->nearZ, q->farZ);
        if (q->waveOn != 0) {
            cur = q->buffer++;
            fn_1_22F4C(32, 128, lbl_1_bss_76E0[1 - (cur & 1)], lbl_1_bss_76E0[cur & 1], lbl_1_bss_76E0[1 - (cur & 1)]);
            minH = lbl_1_rodata_78A0;
            maxH = lbl_1_rodata_789C;
            for (c = 0; c < q->cols; c++) {
                for (r = 0; r < q->rows; r++) {
                    p = &lbl_1_bss_F6E0[c][r];
                    // wrap the ground position into [0, 2)
                    fx = p->x;
                    fz = p->y;
                    ix = fx < lbl_1_rodata_77D8 ? (s32)-fx : (s32)fx;
                    even = ix / 2 * 2;
                    if (fx < lbl_1_rodata_77D8) {
                        fx = fx + (f32)(even + 2);
                    } else {
                        fx = fx - (f32)even;
                    }
                    ix = fz < lbl_1_rodata_77D8 ? (s32)-fz : (s32)fz;
                    even = ix / 2 * 2;
                    if (fz < lbl_1_rodata_77D8) {
                        fz = fz + (f32)(even + 2);
                    } else {
                        fz = fz - (f32)even;
                    }
                    p->z = lbl_1_bss_76E0[q->buffer & 1][(s32)(lbl_1_rodata_78A4 * fx) + ((s32)(lbl_1_rodata_78A8 * fz) << 7)];
                    h = p->z;
                    if (h < minH) {
                        minH = h;
                    } else if (h > maxH) {
                        maxH = h;
                    }
                }
            }
        } else {
            minH = lbl_1_rodata_77D8;
            maxH = minH;
            for (c = 0; c < q->cols; c++) {
                for (r = 0; r < q->rows; r++) {
                    lbl_1_bss_F6E0[c][r].z = minH;
                }
            }
        }
    }
    // minH/maxH are unused by fn_1_23804 (left unset when frozen, as in the original)
    fn_1_23804(10, 10, q->rows, q->cols, maxH, minH);
    q->frame++;
}
#endif

// .text:0x00023AD8 size:0x7C
void fn_1_23AD8(Mtx44 projection, Vec* camera, Vec* target) {
    camera->x = lbl_1_rodata_77D8;
    camera->y = lbl_1_rodata_77D8;
    camera->z = lbl_1_rodata_7804;
    target->x = lbl_1_rodata_77D8;
    target->y = lbl_1_rodata_77D8;
    target->z = lbl_1_rodata_77D8;
    C_MTXFrustum(projection, lbl_1_rodata_7858, lbl_1_rodata_785C,
        lbl_1_rodata_7860, lbl_1_rodata_7864, (&lbl_1_rodata_77E4)[0], lbl_1_rodata_7868);
}

// NONMATCHING 96%: register coloring only; orig reuses the cols param register for the inner counter (r30) and keeps a copy in r31
// .text:0x23804 size:0x2D4
#if NONMATCHING
void fn_1_23804(s32 arg0, s32 arg1, s32 rows, s32 cols, f32 arg4, f32 arg5) {
    Vec* rowBase;
    Vec* p;
    s32 c;
    s32 odd;

    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXLoadPosMtxImm(lbl_1_bss_43EE0.view, 0);
    GXSetCurrentMtx(0);
    rowBase = &lbl_1_bss_F6E0[0][rows];
    while (rowBase--, --rows != 0) {
        c = cols;
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, cols * 2);
        odd = rows & 1;
        while (c-- != 0) {
            p = &rowBase[c * 112];
            GXWGFifo.f32 = p[0].x;
            GXWGFifo.f32 = p[0].z;
            GXWGFifo.f32 = p[0].y;
            GXWGFifo.u32 = odd ? 0xFFFFFFFF : 0x0000FFFF;
            GXWGFifo.f32 = p[-1].x;
            GXWGFifo.f32 = p[-1].z;
            GXWGFifo.f32 = p[-1].y;
            if (odd) {
                GXWGFifo.u32 = 0x0000FFFF;
            } else {
                GXWGFifo.u32 = 0xFFFFFFFF;
            }
        }
    }
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 8);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.u32 = 0x0000FFFF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.u32 = 0x0000FFFF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.u32 = 0x0000FFFF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.u32 = 0x0000FFFF;
}
#endif

// NONMATCHING 83%: frustum setup scheduled differently (orig negates farZ via a double temp, frsp) and the grid row pointers are strength-reduced into different saved regs
// .text:0x23098 size:0x76C
#if NONMATCHING
s32 fn_1_23098(Mtx44 proj, Mtx camera, s32 lines, s32 cols, f32 nearZ, f32 farZ) {
    Mtx44 m;
    Mtx inv;
    Vec rays[4];
    Vec origins[4];
    Vec dir;
    Vec eye;
    f32 t[4];
    f32 dist;
    f32 nearH;
    f32 farH;
    f32 nearW;
    f32 farW;
    f32 height;
    s32 rows;
    s32 k;
    s32 i;
    s32 c;

    eye.x = lbl_1_rodata_77D8;
    eye.y = lbl_1_rodata_77D8;
    eye.z = lbl_1_rodata_77D8;
    dir.x = lbl_1_rodata_77D8;
    dir.y = lbl_1_rodata_7820[0];
    dir.z = lbl_1_rodata_77D8;
    PSMTXMultVec(camera, &eye, &eye);
    PSMTXMultVec(camera, &dir, &dir);
    PSVECSubtract(&dir, &eye, &dir);
    PSVECNormalize(&dir, &dir);
    dist = PSVECDotProduct(&dir, &eye);

    nearH = lbl_1_rodata_77DC[0] * nearZ / lbl_1_rodata_7890 * lbl_1_rodata_7814[0];
    farH = lbl_1_rodata_77DC[0] * farZ / lbl_1_rodata_7890 * lbl_1_rodata_7814[0];
    nearW = lbl_1_rodata_77E0[0] * nearZ / lbl_1_rodata_7890 * lbl_1_rodata_7814[0];
    farW = lbl_1_rodata_77E0[0] * farZ / lbl_1_rodata_7890 * lbl_1_rodata_7814[0];
    nearZ = -nearZ;
    farZ = -farZ;

    origins[0].x = nearW;
    origins[0].y = lbl_1_rodata_77D8;
    origins[0].z = nearZ;
    origins[1].x = farW;
    origins[1].y = lbl_1_rodata_77D8;
    origins[1].z = farZ;
    origins[2].x = farW;
    origins[2].y = farH;
    origins[2].z = farZ;
    origins[3].x = farW;
    origins[3].y = -farH;
    origins[3].z = farZ;
    rays[0].x = lbl_1_rodata_77D8;
    rays[0].y = nearH;
    rays[0].z = lbl_1_rodata_77D8;
    rays[1].x = lbl_1_rodata_77D8;
    rays[1].y = farH;
    rays[1].z = lbl_1_rodata_77D8;
    rays[2].x = nearW - farW;
    rays[2].y = nearH - farH;
    rays[2].z = nearZ - farZ;
    rays[3].x = nearW - farW;
    rays[3].y = -(nearH - farH);
    rays[3].z = nearZ - farZ;

    // Intersect each ray with the plane dot(dir, p) == dist.
    for (i = 0; i < 4; i++) {
        t[i] = PSVECDotProduct(&dir, &rays[i]);
        if (lbl_1_rodata_77D8 == t[i]) {
            rays[i].z = lbl_1_rodata_77D8;
        } else {
            t[i] = -(-dist + PSVECDotProduct(&dir, &origins[i])) / t[i];
            PSVECScale(&rays[i], t[i], &rays[i]);
            PSVECAdd(&origins[i], &rays[i], &rays[i]);
        }
        if (t[i] < lbl_1_rodata_77D8) {
            t[i] = -t[i];
        }
    }

    if (rays[2].z <= nearZ && rays[2].z >= farZ && rays[3].z <= nearZ && rays[3].z >= farZ) {
        memcpy(&rays[0], &rays[2], sizeof(Vec));
        memcpy(&rays[1], &rays[3], sizeof(Vec));
    } else if (t[0] <= lbl_1_rodata_77E4 && t[1] <= lbl_1_rodata_77E4) {
    } else if (t[0] <= lbl_1_rodata_77E4 || t[1] <= lbl_1_rodata_77E4) {
        if (rays[2].z <= nearZ && rays[2].z >= farZ) {
            memcpy(&rays[3], &rays[2], sizeof(Vec));
        }
        if (t[0] < lbl_1_rodata_77E4) {
            memcpy(&rays[1], &rays[3], sizeof(Vec));
        } else {
            memcpy(&rays[0], &rays[3], sizeof(Vec));
        }
    } else {
        return 0;
    }

    // Corner points of the visible ground quad, in camera space -> world (x, z).
    PSMTXInverse(camera, inv);
    PSMTXMultVec(inv, &rays[1], &rays[2]);
    lbl_1_bss_F6E0[cols - 1][0].x = rays[2].x;
    lbl_1_bss_F6E0[cols - 1][0].y = rays[2].z;
    rays[2].x = -rays[1].x;
    rays[2].y = rays[1].y;
    rays[2].z = rays[1].z;
    PSMTXMultVec(inv, &rays[2], &rays[2]);
    lbl_1_bss_F6E0[0][0].x = rays[2].x;
    lbl_1_bss_F6E0[0][0].y = rays[2].z;
    PSMTXMultVec(inv, &rays[0], &rays[2]);
    lbl_1_bss_F6E0[cols - 1][1].x = rays[2].x;
    lbl_1_bss_F6E0[cols - 1][1].y = rays[2].z;
    rays[2].x = -rays[0].x;
    rays[2].y = rays[0].y;
    rays[2].z = rays[0].z;
    PSMTXMultVec(inv, &rays[2], &rays[2]);
    lbl_1_bss_F6E0[0][1].x = rays[2].x;
    lbl_1_bss_F6E0[0][1].y = rays[2].z;

    PSMTX44Identity(m);
    memcpy(m, camera, sizeof(Mtx));
    PSMTX44Concat(proj, m, m);
    C_MTX44Inverse(m, m);
    PSMTX44MultVec(proj, &rays[0], &rays[0]);
    PSMTX44MultVec(proj, &rays[1], &rays[1]);
    height = rays[0].y - rays[1].y;
    if (height < lbl_1_rodata_77D8) {
        height = -height;
    }
    rows = (f32)lines * (height + lbl_1_rodata_780C / (f32)lines) * lbl_1_rodata_7814[0];
    if (rows < 2) {
        rows = 2;
    }

    // Left/right edges: interpolate in screen space and unproject.
    k = rows - 1;
    lbl_1_bss_F6E0[0][k].x = lbl_1_bss_F6E0[0][1].x;
    lbl_1_bss_F6E0[0][k].y = lbl_1_bss_F6E0[0][1].y;
    lbl_1_bss_F6E0[cols - 1][k].x = lbl_1_bss_F6E0[cols - 1][1].x;
    lbl_1_bss_F6E0[cols - 1][k].y = lbl_1_bss_F6E0[cols - 1][1].y;
    PSVECSubtract(&rays[0], &rays[1], &rays[2]);
    for (i = k; --i != 0;) {
        PSVECScale(&rays[2], (f32)i / (f32)k, &rays[3]);
        PSVECAdd(&rays[1], &rays[3], &rays[3]);
        PSMTX44MultVec(m, &rays[3], &eye);
        lbl_1_bss_F6E0[cols - 1][i].x = eye.x;
        lbl_1_bss_F6E0[cols - 1][i].y = eye.z;
        rays[3].x = -rays[3].x;
        PSMTX44MultVec(m, &rays[3], &eye);
        lbl_1_bss_F6E0[0][i].x = eye.x;
        lbl_1_bss_F6E0[0][i].y = eye.z;
    }

    // Fill each row between its left and right edge points.
    rays[0].y = lbl_1_rodata_77D8;
    rays[1].y = lbl_1_rodata_77D8;
    for (i = 0; i < rows; i++) {
        rays[0].x = lbl_1_bss_F6E0[0][i].x;
        rays[0].z = lbl_1_bss_F6E0[0][i].y;
        rays[1].x = lbl_1_bss_F6E0[cols - 1][i].x - rays[0].x;
        rays[1].z = lbl_1_bss_F6E0[cols - 1][i].y - rays[0].z;
        for (c = cols - 1; --c != 0;) {
            PSVECScale(&rays[1], (f32)c / (f32)(cols - 1), &rays[2]);
            PSVECAdd(&rays[0], &rays[2], &rays[2]);
            lbl_1_bss_F6E0[c][i].x = rays[2].x;
            lbl_1_bss_F6E0[c][i].y = rays[2].z;
        }
    }
    return rows;
}
#endif

// NONMATCHING 69%: original keeps i*4 index (lfsx base,r31) plus a dead `i` counter; ours strength-reduces to 3 pointers
// .text:0x22F4C size:0x14C
#if NONMATCHING
void fn_1_22F4C(s32 h, s32 w, f32* out, f32* cur, f32* prev) {
    f64 c = (lbl_1_rodata_7878 * s104C0) / s104BC;
    f32 k;
    f32 m;
    s32 y;
    s32 x;
    s32 i;
    s32 row;

    c = c * c;
    k = c;
    m = lbl_1_rodata_7880 - lbl_1_rodata_7888 * c;
    for (y = 0, row = 0; y < h; y++, row += w) {
        for (x = 0, i = row; x < w; x++, i++) {
            out[i] = m * cur[i]
                + k * (cur[(x + 1) % w + row] + (cur[(x + (w - 1)) % w + row]
                + (cur[x + w * ((y + (h - 1)) % h)] + cur[x + w * ((y + 1) % h)])))
                - prev[i];
            out[i] *= s104C4;
            
        }
    }
}
#endif

// .text:0x22DF4 size:0x158
void fn_1_22DF4(ChallengeCurveDrawing* arg) {
    arg->scale = lbl_1_rodata_77F8;
    arg->unk1C = lbl_1_rodata_7854;
    arg->unk25 = 0;
    arg->steps = 10;
    arg->pointCount = 10;
    arg->drawFlat = 1;
    arg->colorMode = 0;
    arg->drawFull = 0;
    fn_80038E2C(&lbl_1_bss_6FB8);
    fn_1_21180(arg);
}

// NONMATCHING 99.8%: only the prologue's address temps get different GPRs (r5/r7/r9 vs r11/r5/r7)
// .text:0x22874 size:0x580
#if NONMATCHING
s32 fn_1_22874(ChallengeCurveDrawing* unused) {
    ChallengeCurveDrawing* q = (ChallengeCurveDrawing*)lbl_803CC1B8;
    s32 speed;
    f32 fine;
    f32 step;
    f32 tiny;
    s32 i;
    u8 prevCount;

    if (lbl_803C77B8._00 & 0x20) {
        speed = 100;
    } else if (CHALLENGE_PAD_STICK_Y >= 0x50) {
        speed = 1;
    } else {
        speed = 10;
    }
    fine = lbl_1_rodata_786C * speed;
    step = lbl_1_rodata_77F8 * speed;
    tiny = lbl_1_rodata_77FC * speed;
    for (i = 0; i < 14; i++) {
        switch (i) {
        case 0:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->steps--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->steps++;
                }
                if (q->steps == 0) {
                    q->steps++;
                }
            }
            break;
        case 1:
            prevCount = q->pointCount;
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->pointCount = prevCount - 1;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->pointCount = prevCount + 1;
                }
                if (q->pointCount < 2) {
                    q->pointCount++;
                }
            }
            break;
        case 2:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[0] -= fine;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[0] += fine;
                }
            }
            break;
        case 3:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->scale -= step;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->scale += step;
                }
            }
            break;
        case 4:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[2] -= step;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[2] += step;
                }
            }
            break;
        case 5:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[3] -= step;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[3] += step;
                }
            }
            break;
        case 6:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[4] -= step;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[4] += step;
                }
            }
            break;
        case 7:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[5] -= tiny;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[5] += tiny;
                }
            }
            break;
        case 8:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->unk1C -= speed;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->unk1C += speed;
                }
            }
            break;
        case 9:
            if (i == q->unk25 && (CHALLENGE_PAD_TRIGGER & 3)) {
                q->drawFlat = !q->drawFlat;
            }
            break;
        case 10:
            if (i == q->unk25 && (CHALLENGE_PAD_TRIGGER & 3)) {
                q->colorMode = !q->colorMode;
            }
            break;
        case 11:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_data_104D0.x -= lbl_1_rodata_7870;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_data_104D0.x += lbl_1_rodata_7870;
                }
            }
            break;
        case 12:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_data_104D0.y -= lbl_1_rodata_7870;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_data_104D0.y += lbl_1_rodata_7870;
                }
            }
            break;
        case 13:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_data_104D0.z -= lbl_1_rodata_7870;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_data_104D0.z += lbl_1_rodata_7870;
                }
            }
            break;
        }
    }
    if (CHALLENGE_PAD_TRIGGER & 8) {
        if (q->unk25 == 0) {
            q->unk25 = 14;
        }
        q->unk25--;
    } else if (CHALLENGE_PAD_TRIGGER & 4) {
        q->unk25++;
        if (q->unk25 == 14) {
            q->unk25 = 0;
        }
    }
    return prevCount != q->pointCount;
}
#endif

// .text:0x22644 size:0x230
void fn_1_22644(void) {
    ChallengeCurveDrawing* q = (ChallengeCurveDrawing*)lbl_803CC1B8;

    fn_800AD038(lbl_80366158[2]);
    q->unk25 = 0;
    fn_1_22DF4((ChallengeCurveDrawing*)lbl_803CC1B8);
    fn_1_23AD8(lbl_1_bss_47010, &lbl_1_bss_43EE0.camera, &lbl_1_bss_43EE0.target);
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_225B8;
}

// .text:0x225B8 size:0x8C
void fn_1_225B8(void) {
    ChallengeCurveDrawing* queue = (ChallengeCurveDrawing*)lbl_803CC1B8;
    switch ((s32)queue->unk25) {
    case 0:
        fn_1_20DC8();
        queue->unk25++;
        break;
    case 1:
        if (queue->result != 0) {
            queue->func = fn_1_21408;
        }
        break;
    }
}

// .text:0x21CE8 size:0x8D0
void fn_1_21CE8(void) {
    ChallengeCurveDrawing* q = (ChallengeCurveDrawing*)lbl_803CC1B8;

    if (fn_1_22874(q) != 0 || (lbl_803C77B8._02 & 0x100)) {
        fn_1_21180(q);
    } else if (lbl_803C77B8._02 & 0x200) {
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_21408;
    }
    fn_1_21CE8_moveRope(q);
    fn_1_21CE8_setupDraw();
    fn_1_21040();
    fn_1_21298(q);
    updateRopeObjects(lbl_1_bss_6FE0, q->pointCount - 1, lbl_1_bss_43EE0.view);
}

// NONMATCHING 99.9%: the pad base and q->colorMode swap r7/r8 in the inlined fn_1_21180
// .text:0x21408 size:0x8E0
#if NONMATCHING
void fn_1_21408(void) {
    ChallengeCurveDrawing* q = (ChallengeCurveDrawing*)lbl_803CC1B8;

    if (lbl_803C77B8._02 & 0x1000) {
        q->func = fn_1_21CE8;
    } else if (lbl_803C77B8._02 & 0x100) {
        fn_1_21180(q);
    } else if (lbl_803C77B8._02 & 0x200) {
        lbl_1_bss_6BE0[0] = NULL;
        q->func = fn_1_24778;
    }
    fn_1_121D4((u8*)&lbl_1_bss_43EE0);
    fn_1_21CE8_moveRope(q);
    fn_1_21CE8_setupDraw();
    fn_1_21040();
    fn_1_21298(q);
    if (lbl_1_bss_6BE0[0] != NULL) {
        updateRopeObjects(lbl_1_bss_6FE0, q->pointCount - 1, lbl_1_bss_43EE0.view);
    }
}
#endif

// .text:0x00021298 size:0x170
void fn_1_21298(ChallengeCurveDrawing* drawing) {
    s32 count;
    ChallengeCurvePoint* point;
    u32 color;

    if (drawing->drawFlat != 0) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, (drawing->pointCount - 1) * 2);
        count = drawing->pointCount;
        while (--count != 0) {
            point = &lbl_1_bss_6FE0[count];
            GXWGFifo.f32 = point->position.x;
            GXWGFifo.f32 = 0.0f;
            GXWGFifo.f32 = point->position.z;
            GXWGFifo.u32 = 0x80;
            GXWGFifo.f32 = point[-1].position.x;
            GXWGFifo.f32 = 0.0f;
            GXWGFifo.f32 = point[-1].position.z;
            GXWGFifo.u32 = 0x80;
        }
    }
    if (drawing->drawFull != 0) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, (drawing->pointCount - 1) * 2);
        count = drawing->pointCount;
        while (--count != 0) {
            point = &lbl_1_bss_6FE0[count];
            GXWGFifo.f32 = point->position.x;
            GXWGFifo.f32 = -point->position.y;
            GXWGFifo.f32 = point->position.z;
            color = lbl_1_data_104DC[count % 6];
            GXWGFifo.u32 = color;
            GXWGFifo.f32 = point[-1].position.x;
            GXWGFifo.f32 = -point[-1].position.y;
            GXWGFifo.f32 = point[-1].position.z;
            GXWGFifo.u32 = color;
        }
    }
}

// .text:0x21180 size:0x118
void fn_1_21180(ChallengeCurveDrawing* arg) {
    ChallengeCurveTiming* tm;
    s32 n = arg->steps;
    f32 t;
    ChallengeCurvePoint* pts;
    s32 idx;

    tm = &lbl_1_bss_6FB8;
    tm->steps = n;
    t = ((&lbl_1_rodata_77E4)[0] / (f32)n) / lbl_1_rodata_784C[0];
    tm->step = t;
    tm->stepSq = t * t;
    tm->inv = (&lbl_1_rodata_77E4)[0] / ((&lbl_1_rodata_780C)[0] * t);
    if (lbl_803C77B8._00 & 0x400) {
        tm->steps = 1;
    }
    fn_80038CD0(arg->pointCount, &lbl_1_bss_6FB8, lbl_1_bss_6FE0, lbl_1_rodata_7810, arg->scale);
    pts = lbl_1_bss_6FE0;
    idx = arg->pointCount - 1;
    lbl_1_bss_6FA8[0] = pts[idx].position.x;
    lbl_1_bss_6FA8[1] = pts[idx].position.y;
    lbl_1_bss_6FA8[2] = pts[idx].position.z;
    pts[idx].mode = arg->colorMode;
}

// .text:0x21040 size:0x140
void fn_1_21040(void) {
    u32 color;
    s32 pos;
    s32 i;

    GXBegin(GX_LINES, GX_VTXFMT0, 44);
    for (i = 0; i < 11; i++) {
        color = 0xFFFFFFFF;
        if (i == 5) {
            color = 0xFF0000FF;
        }
        pos = (i - 5) * 10;
        GXWGFifo.f32 = pos;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7844;
        GXWGFifo.u32 = color;
        GXWGFifo.f32 = pos;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7848;
        GXWGFifo.u32 = color;
        if (i == 5) {
            color = 0x00FF00FF;
        }
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7844;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = pos;
        GXWGFifo.u32 = color;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7848;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = pos;
        GXWGFifo.u32 = color;
    }
}

// .text:0x00020F8C size:0xB4
void fn_1_20F8C(void) {
    s16 phase = ((ChTaskHeader*)lbl_803CC1B8)->result;
    ChallengeTransfer* transfer = (ChallengeTransfer*)((ChTaskHeader*)lbl_803CC1B8)->parent;
    switch (phase) {
    case 0:
        if ((s32)lbl_803C6CF8.idle == 1) {
            transfer->data = (void*)ARAMTransfer(&lbl_1_data_104F4, 0, 0, 0);
            (((ChTaskHeader*)lbl_803CC1B8)->result)++;
        }
        break;
    case 1:
        if ((s32)lbl_803C6CF8.idle == 1) {
            transfer->complete = 1;
        }
        break;
    }
}

// NONMATCHING 99.8%: LITInitPos: orig `lis r3,7840; lis r4,6FA4; addi r3,r4` (float const lis first), ours swaps r3/r4
// .text:0x20E00 size:0x18C
#if NONMATCHING
void fn_1_20E00(ChallengeModelLoadTask* obj) {
    ChallengeLightColor color = lbl_1_rodata_77B0;
    u8* data;
    u16 i;
    u8* layout;
    u8* geo;

    LITAlloc(lbl_1_bss_6FA4);
    LITInitAttn(lbl_1_bss_6FA4[0], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(lbl_1_bss_6FA4[0], lbl_1_rodata_7840, lbl_1_rodata_7840, lbl_1_rodata_7840);
    LITInitDir(lbl_1_bss_6FA4[0], 0.0f, 0.0f, 0.0f);
    LITInitColor(lbl_1_bss_6FA4[0], LIT_COLOR(color));
    data = obj->data;
    layout = data + ((s32*)data)[0];
    geo = data + ((s32*)data)[1];
    lbl_1_bss_6BE0[0] = ActorObjectInitTable(20);
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, NULL);
    haveActLayoutPointToGeoHeader(layout, geo);
    for (i = 0; i < 20; i++) {
        fn_800BDC88(lbl_1_bss_6BE0[0], i, i, (struct ActorLayout *)layout, 0, 0); // TODO type
        fn_800B2C08(lbl_1_bss_6BE0[0]->objects[i].actor, 0);
        fn_800BD548(&lbl_1_bss_6BE0[0]->objects[i], 1, lbl_1_bss_6FA4[0]);
    }
}
#endif

// .text:0x00020DC8 size:0x38
void fn_1_20DC8(void) {
    ChallengeModelLoadTask* object = fn_800B0A5C_insertQueue((void*)fn_1_20BD8, 1);
    object->step = 0;
    object->h.result = 0;
}

// NONMATCHING 99.8%: same LITInitPos r3/r4 swap as fn_1_20E00 (inlined here)
// .text:0x20BD8 size:0x1F0
#if NONMATCHING
void fn_1_20BD8(void) {
    ChallengeModelLoadTask* q = (ChallengeModelLoadTask*)lbl_803CC1B8;
    ChTaskHeader* object;

    switch (q->step) {
    case 0:
        object = fn_800B0A5C_insertQueue((void*)fn_1_20F8C, 1);
        object->result = 0;
        q->step++;
        break;
    case 1:
        if (q->h.result != 0) {
            fn_1_20E00(q);
            object = q->h.parent;
            object->result = 1;
            fn_800B0A14_removeQueue(object);
        }
        break;
    }
}
#endif

// .text:0x20950 size:0x288
void fn_1_20950(ChallengeCurvePoint* points, s32 count, MtxPtr camera) {
    ActorObject* obj;
    s32 i;
    Vec delta;
    Vec mid;
    Quaternion rot;
    Quaternion align;
    Mtx mtx;
    f32 angle;
    f32 zero;

    i = 20;
    while (i-- != 0) {
        obj = &lbl_1_bss_6BE0[0]->objects[i];
        obj->animateBones = i < count;
        if (i < count) {
            PSVECSubtract(&points[i + 1].position, &points[i].position, &delta);
            PSVECScale(&delta, lbl_1_rodata_7814[0], &mid);
            PSVECAdd(&points[i].position, &mid, &mid);
            CTRLSetTranslation(&obj->worldControl.base, mid.x, -mid.y, mid.z);
            if (PSVECMag(&delta)) {
                PSVECNormalize(&delta, &delta);
                delta.y = -delta.y;
                mid.x = lbl_1_rodata_77E4;
                mid.y = lbl_1_rodata_77D8;
                mid.z = lbl_1_rodata_77D8;
                C_QUATRotAxisRad(&rot, &mid,
                    lbl_1_rodata_7828 * (lbl_1_rodata_7830 + (i & 1)) / lbl_1_rodata_7838);
                angle = acos(PSVECDotProduct(&delta, &mid));
                PSVECCrossProduct(&mid, &delta, &mid);
                if (PSVECMag(&mid)) {
                    C_QUATRotAxisRad(&align, &mid, angle);
                    PSQUATMultiply(&align, &rot, &rot);
                }
                CTRLSetQuat(&obj->worldControl.base, rot.x, rot.y, rot.z, rot.w);
            }
            CTRLSetScale(&obj->worldControl.base, lbl_1_data_104D0.x, lbl_1_data_104D0.y, lbl_1_data_104D0.z);
            fn_800BDA24(obj);
        }
        zero = *(volatile f32*)&lbl_1_rodata_77D8;
        PSMTXTrans(mtx, zero, zero, zero);
        PSMTXConcat(camera, mtx, mtx);
        obj->actor->flags |= 3;
    }
    fn_800BD670(lbl_1_bss_6BE0[0], (MtxPtr)camera);
}

// .text:0x00020890 size:0xC0
void fn_1_20890(void) {
    Mtx identity;
    C_MTXOrtho(lbl_1_bss_47010, lbl_1_rodata_77D8, lbl_1_rodata_77DC[0],
        lbl_1_rodata_77D8, lbl_1_rodata_77E0[0], lbl_1_rodata_7814[0], lbl_1_rodata_7820[0]);
    GXSetProjection(lbl_1_bss_47010, GX_ORTHOGRAPHIC);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(identity, GX_TEXMTX0, GX_MTX2x4);
    fn_80048C14(3);
    fn_80048E00(0, 32);
    fn_80048E00(1, 0);
}

// .text:0x000207D4 size:0xBC
void fn_1_207D4(void) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 8);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
}

// .text:0x00020640 size:0x194
void fn_1_20640(ChallengeTextureStages* stages, u32* indices) {
    u32* image;
    GXTexCoordID stage;
    u32 textureIndex;
    u32 paletteIndex;

    GXSetNumTevStages(stages->stageCount);
    GXSetNumTexGens(stages->stageCount);
    image = indices;
    for (stage = 0; stage < (s32)stages->stageCount; image++, stage++) {
        GXSetTexCoordGen2(stage, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        if (stage != 0) {
            GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        } else {
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
        textureIndex = *image;
        paletteIndex = textureIndex & 0x7FFFFFFF;
        GXLoadTexObj(&lbl_1_bss_6EA4[textureIndex], stage);
        if (textureIndex & 0x80000000) {
            GXLoadTlut(&lbl_1_bss_6E44[paletteIndex], stage);
        }
    }
}

// .text:0x0002051C size:0x124
s32 fn_1_2051C(ChallengeTextureHeader* texture, GXTexObj* object, GXTlutObj* palette, GXTlut name) {
    u8 mipmapped = texture->minLod != texture->maxLod;
    if (texture->palette != NULL) {
        GXInitTexObjCI(object, texture->image, texture->width, texture->height,
            texture->format, texture->wrapS, texture->wrapT, mipmapped, name);
        GXInitTlutObj(palette, texture->palette, texture->paletteFormat, texture->paletteEntries);
    } else {
        GXInitTexObj(object, texture->image, texture->width, texture->height,
            texture->format, texture->wrapS, texture->wrapT, mipmapped);
    }
    GXInitTexObjLOD(object, texture->minFilter, texture->magFilter,
        texture->minLod, texture->maxLod, texture->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
    return !!texture->palette;
}

// .text:0x0002040C size:0x110
void fn_1_2040C(void) {
    Mtx identity;
    ChallengeTextureStages* queue = (ChallengeTextureStages*)lbl_803CC1B8;
    queue->value = 0;
    queue->unk23 = 0;
    queue->unk24 = 0;
    queue->toggle = 0;
    queue->cursor = 0;
    queue->stageCount = 1;
    C_MTXOrtho(lbl_1_bss_47010, lbl_1_rodata_77D8, lbl_1_rodata_77DC[0],
        lbl_1_rodata_77D8, lbl_1_rodata_77E0[0], lbl_1_rodata_7814[0], lbl_1_rodata_7820[0]);
    GXSetProjection(lbl_1_bss_47010, GX_ORTHOGRAPHIC);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(identity, GX_TEXMTX0, GX_MTX2x4);
    fn_80048C14(3);
    fn_80048E00(0, 32);
    fn_80048E00(1, 0);
    fn_800AD038(lbl_80366158[2]);
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_2004C;
}

// .text:0x000202A4 size:0x168
void fn_1_202A4(void) {
    ChallengeTextureStages* queue = (ChallengeTextureStages*)lbl_803CC1B8;
    fn_80048C1C();
    lbl_1_data_10508[queue->toggle](queue);
    if (lbl_803C77B8._02 & 0x200) {
        GXColor clearColor;
        ChallengeTransfer* transfer;
        *(u32*)&clearColor = 0x11775500;
        GXSetCopyClear(clearColor, 0xFFFFFF);
        transfer = (ChallengeTransfer*)((ChTaskHeader*)lbl_803CC1B8)->parent;
        transfer->complete = 1;
        fn_800B0A14_removeQueue(transfer);
    }
    fn_80048D4C();
    fn_1_207D4();
    lbl_1_data_10510[queue->toggle](queue);
    fn_80048C28();
}

// NONMATCHING 99.5%: saved regs q=r25/i=r26 in orig, ours q=r26/i=r25 (decl/assign order variants did not help)
// .text:0x2004C size:0x258
#if NONMATCHING
void fn_1_2004C(void) {
    ChallengeTextureStages* q = (ChallengeTextureStages*)lbl_803CC1B8;
    s32 ids[9] = { 5, 6, 7, 8, 9, 13, 0x60, 0x61, 0x55 };
    u8* data;
    u32 i;

    switch (q->cursor) {
    case 0:
        q->file = (void*)ARAMTransfer(lbl_1_data_10518, 0, 0, 0);
        q->cursor++;
        break;
    case 1:
        if ((s32)lbl_803C6CF8.idle == 1) {
            data = q->file;
            q->tex = data + *(s32*)(data + 0x14); // file-relative offset in the header
            convertTextureHeader(q->tex);
            for (i = 0; i < 8; i++) {
                lbl_1_bss_6E24[i] = i;
                if (fn_1_2051C((ChallengeTextureHeader*)(q->tex + ids[i] * 32 + 4),
                        &lbl_1_bss_6EA4[i], &lbl_1_bss_6E44[i], i)) {
                    lbl_1_bss_6E24[i] |= 0x80000000;
                }
            }
            q->cursor = 0;
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_202A4;
        }
        break;
    }
}
#endif

// .text:0x1FD78 size:0x2D4
void fn_1_1FD78(ChallengeTextureStages* menu) {
    u32 step;
    s32 i;
    s32 v;
    u8 cur;

    step = 1;
    if (lbl_803C77B8._00 & 0x20) {
        step = 100;
    }
    for (i = 0; i < 6; i++) {
        cur = menu->cursor;
        switch (i) {
        case 0:
            if (i == cur) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (menu->toggle == 0) {
                        menu->toggle = 2;
                    }
                    menu->toggle--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    menu->toggle++;
                    if (menu->toggle == 2) {
                        menu->toggle = 0;
                    }
                }
            }
            break;
        case 1:
            v = fn_80048EA8(0);
            if (i == menu->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    v--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    v++;
                }
                fn_80048E00(0, v);
            }
            break;
        case 2:
            v = fn_80048EA8(1);
            if (i == menu->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    v--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    v++;
                }
                fn_80048E00(1, v);
            }
            break;
        case 3:
            if (i == cur) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (menu->value <= step) {
                        menu->value = 0;
                    } else {
                        menu->value -= step;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    menu->value += step;
                    if (menu->value > 0x1000) {
                        menu->value = 0x1000;
                    }
                }
            }
            break;
        case 4:
            if (i == cur) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    menu->unk23--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    menu->unk23++;
                }
            }
            break;
        case 5:
            if (i == cur) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (menu->stageCount > 1) {
                        menu->stageCount--;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (menu->stageCount < 4) {
                        menu->stageCount++;
                    }
                }
            }
            break;
        }
    }
    if (CHALLENGE_PAD_TRIGGER & 8) {
        if (menu->cursor == 0) {
            menu->cursor = 6;
        }
        menu->cursor--;
    } else if (CHALLENGE_PAD_TRIGGER & 4) {
        menu->cursor++;
        if (menu->cursor == 6) {
            menu->cursor = 0;
        }
    }
}

// NONMATCHING 73%: orig unrolls the index fill loop x8 (with a load/store-back of lbl_1_bss_6E24[k]) and uses two fewer saved regs; ours keeps it rolled
// .text:0x1F900 size:0x478
#if NONMATCHING
void fn_1_1F900(ChallengeTextureStages* stages) {
    s32 i;
    s32 j;
    s32 cell;
    s32 x;
    s32 y;
    u32 index[4];

    for (i = 0; i < stages->value; i++) {
        cell = i % 480 % 48;
        x = cell % 8;
        y = cell / 8;
        for (j = 0; j < stages->stageCount; j++) {
            index[j] = lbl_1_bss_6E24[(x + y) % 8];
        }
        fn_1_20640(stages, index);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXWGFifo.f32 = x * stages->unk23;
        GXWGFifo.f32 = y * stages->unk23;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0;
        GXWGFifo.f32 = x * stages->unk23;
        GXWGFifo.f32 = stages->unk23 + y * stages->unk23;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.f32 = stages->unk23 + x * stages->unk23;
        GXWGFifo.f32 = stages->unk23 + y * stages->unk23;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.f32 = stages->unk23 + x * stages->unk23;
        GXWGFifo.f32 = y * stages->unk23;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.u16 = 0;
    }
}
#endif

// NONMATCHING 97%: inlined fn_1_20640 keeps the texture index in a register (orig reloads *image for the tlut test) and the FIFO base gets a different saved reg
// .text:0x1F618 size:0x2E8
#if NONMATCHING
void fn_1_1F618(ChallengeTextureStages* stages) {
    s32 i;
    u32 index[1];
    f32 z;

    i = stages->value;
    while (i-- != 0) {
        index[0] = i % 4;
        fn_1_20640(stages, index);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        z = lbl_1_rodata_7814[0] - lbl_1_rodata_77FC * i;
        GXWGFifo.f32 = z;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E0[0];
        GXWGFifo.f32 = z;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77DC[0];
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E0[0];
        GXWGFifo.f32 = z;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77DC[0];
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = z;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.u16 = 0;
    }
}
#endif

// .text:0x1F418 size:0x200
void fn_1_1F418(ChallengeTextureStages* menu) {
    s32 i;
    s32 v;
    u8 cur;

    for (i = 0; i < 4; i++) {
        cur = menu->cursor;
        switch (i) {
        case 0:
            if (i == cur) {
                if (lbl_803C77B8._04 & 1) {
                    if (menu->toggle == 0) {
                        menu->toggle = 2;
                    }
                    menu->toggle--;
                } else if (lbl_803C77B8._04 & 2) {
                    menu->toggle++;
                    if (menu->toggle == 2) {
                        menu->toggle = 0;
                    }
                }
            }
            break;
        case 1:
            v = (s32)fn_80048EA8(0);
            if (i == menu->cursor) {
                if (lbl_803C77B8._04 & 1) {
                    v--;
                } else if (lbl_803C77B8._04 & 2) {
                    v++;
                }
                fn_80048E00(0, v);
            }
            break;
        case 2:
            v = (s32)fn_80048EA8(1);
            if (i == menu->cursor) {
                if (lbl_803C77B8._04 & 1) {
                    v--;
                } else if (lbl_803C77B8._04 & 2) {
                    v++;
                }
                fn_80048E00(1, v);
            }
            break;
        case 3:
            if (i == cur) {
                if (lbl_803C77B8._04 & 1) {
                    if (menu->value != 0) {
                        menu->value--;
                    }
                } else if (lbl_803C77B8._04 & 2) {
                    menu->value++;
                }
            }
            break;
        }
    }
    if (lbl_803C77B8._04 & 8) {
        if (menu->cursor == 0) {
            menu->cursor = 4;
        }
        menu->cursor--;
    } else if (lbl_803C77B8._04 & 4) {
        menu->cursor++;
        if (menu->cursor == 4) {
            menu->cursor = 0;
        }
    }
}

#define BODY_TEST ((ChallengeBodyTest*)lbl_803CC1B8)

// .text:0x1F2D8 size:0x140
void fn_1_1F2D8(void) {
    fn_1_273D8(&lbl_1_bss_6D48);
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1F05C;
    BODY_TEST->flags = 0;
    BODY_TEST->shape = 0;
    BODY_TEST->length = (&lbl_1_rodata_780C)[0];
    BODY_TEST->frac = (&lbl_1_rodata_7810)[0];
    BODY_TEST->radius = (&lbl_1_rodata_7810)[0];
    BODY_TEST->mass = (&lbl_1_rodata_77E4)[0];
    BODY_TEST->height = (&lbl_1_rodata_77E4)[0];
    fn_1_1F23C(&lbl_1_bss_6BF4);
    ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
    lbl_1_bss_6BE4[0] = 0.0f;
    lbl_1_bss_6BE4[1] = 0.0f;
    lbl_1_bss_6BE4[2] = 0.0f;
    lbl_1_bss_6BE4[3] = 0.0f;
}

// .text:0x0001F23C size:0x9C
void fn_1_1F23C(ChallengeProjectionState* state) {
    fn_800385F0((struct RigidBody *)&lbl_1_bss_6BF4, // TODO type
        BODY_TEST->length, BODY_TEST->frac,
        BODY_TEST->radius, BODY_TEST->mass);
    state->depth = -BODY_TEST->height;
    state->pos.y += lbl_1_rodata_780C;
    BODY_TEST->flags &= ~2U;
    BODY_TEST->flags |= 2;
}

// .text:0x1F05C size:0x1E0
void fn_1_1F05C(void) {
    ChallengeBodyTest* q;

    if (BODY_TEST->flags & 1) {
        ((ChTaskHeader*)lbl_803CC1B8)->result = fn_1_1E90C(((ChTaskHeader*)lbl_803CC1B8)->result, lbl_803C77B8._00,
            lbl_803C77B8._02, lbl_803C77B8._04);
    } else {
        fn_1_26D28(&lbl_1_bss_6D48, lbl_803C77B8._00, lbl_803C77B8._02, lbl_803C77B8._04,
            (ChallengeDebugPad*)&lbl_803C77B8.stickX);
    }
    if (lbl_803C77B8._02 & 0x200) {
        q = BODY_TEST;
        if (q->flags & 1) {
            q->h.func = fn_1_24778;
        } else {
            q->flags ^= 1;
        }
    } else if (lbl_803C77B8._02 & 0x1000) {
        BODY_TEST->flags ^= 1;
    }
    fn_1_27330(&lbl_1_bss_6D48);
    q = BODY_TEST;
    switch (q->shape) {
    case 0:
        if (q->flags & 4) {
            q->flags ^= 4;
            fn_1_1DD94();
        }
        fn_80037BAC(&lbl_1_bss_6BF4);
        break;
    }
    q = BODY_TEST;
    if (q->flags & 1) {
        fn_1_1E8C0(q->h.result);
    }
    fn_1_1EFF4();
}

// .text:0x1EFF4 size:0x68
void fn_1_1EFF4(void) {
    fn_1_272DC(&lbl_1_bss_6D48, 0);
    fn_1_AF4(20, 20, (&lbl_1_rodata_77E4)[0]);
    if (BODY_TEST->flags & 2) {
        fn_1_1E5D0(&lbl_1_bss_6BF4);
    }
}

// NONMATCHING 98%: f0/f1 swapped in the inlined step/clamp helper (orig negates into a fresh reg), r0/r4 in the modulo paths
// .text:0x1E90C size:0x6E8
#if NONMATCHING
s16 fn_1_1E90C(s16 sel, u16 held, u16 pressed, u16 repeat) {
    f32 length = BODY_TEST->length;
    f32 frac = BODY_TEST->frac;
    f32 radius = BODY_TEST->radius;
    f32 mass = BODY_TEST->mass;
    f32 height = BODY_TEST->height;
    s16 sub;

    sub = lbl_1_data_10668[BODY_TEST->shape]((s16)(sel - 8), held, pressed, repeat) + 8;
    if (sel != sub) {
        s32 n = lbl_1_data_10670[BODY_TEST->shape] + 8;
        sel = (sub + n) % n;
    } else if (pressed & 0x100) {
        switch (sel) {
        case 0:
            break;
        case 1:
            fn_1_1F23C(&lbl_1_bss_6BF4);
            break;
        case 2:
            BODY_TEST->flags ^= 4;
            break;
        case 3:
            break;
        }
    } else if (repeat & 1) {
        switch (sel) {
        case 0:
            BODY_TEST->shape = (BODY_TEST->shape + 7) % 8;
            break;
        case 3:
            length = fn_1_1E90C_adjust(length, held, 1, lbl_1_rodata_77E4, lbl_1_rodata_7808[0]);
            break;
        case 4:
            frac = fn_1_1E90C_adjust(frac, held, 1, lbl_1_rodata_77D8, lbl_1_rodata_77E4);
            break;
        case 5:
            radius = fn_1_1E90C_adjust(radius, held, 1, lbl_1_rodata_77E4, lbl_1_rodata_7808[0]);
            break;
        case 7:
            height = fn_1_1E90C_adjust(height, held, 1, lbl_1_rodata_77D8, lbl_1_rodata_7808[0]);
            break;
        }
    } else if (repeat & 2) {
        switch (sel) {
        case 0:
            BODY_TEST->shape = (BODY_TEST->shape + 1) % 8;
            break;
        case 3:
            length = fn_1_1E90C_adjust(length, held, 0, lbl_1_rodata_77E4, lbl_1_rodata_7808[0]);
            break;
        case 4:
            frac = fn_1_1E90C_adjust(frac, held, 0, lbl_1_rodata_77D8, lbl_1_rodata_77E4);
            break;
        case 5:
            radius = fn_1_1E90C_adjust(radius, held, 0, lbl_1_rodata_77E4, lbl_1_rodata_7808[0]);
            break;
        case 6:
            mass = fn_1_1E90C_adjust(mass, held, 0, lbl_1_rodata_77D8, lbl_1_rodata_7808[0]);
            break;
        case 7:
            height = fn_1_1E90C_adjust(height, held, 0, lbl_1_rodata_77D8, lbl_1_rodata_7808[0]);
            break;
        }
    } else if (repeat & 8) {
        if (sel < 8) {
            s32 n = lbl_1_data_10670[BODY_TEST->shape];
            sel = (n + sel + 7) % (n + 8);
        }
    } else if (repeat & 4) {
        if (sel < 8) {
            sel = (sel + 1) % (lbl_1_data_10670[BODY_TEST->shape] + 8);
        }
    }
    BODY_TEST->length = length;
    BODY_TEST->frac = frac;
    BODY_TEST->radius = radius;
    BODY_TEST->mass = mass;
    BODY_TEST->height = height;
    return sel;
}
#endif

// .text:0x1E8C0 size:0x4C
void fn_1_1E8C0(s32 index) {
    lbl_1_data_1066C[BODY_TEST->shape]((s16)(index - 8));
}

// .text:0x1E5D0 size:0x2F0
void fn_1_1E5D0(ChallengeProjectionState* body) {
    Vec b;
    Vec a;
    Vec* pb;

    fn_1_F2C(4, 0, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    PSMTXMultVec(body->world, &body->p1, &a);
    PSMTXMultVec(body->world, &body->p0, pb = &b);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXWGFifo.f32 = a.x;
    GXWGFifo.f32 = a.y;
    GXWGFifo.f32 = a.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.f32 = b.x;
    GXWGFifo.f32 = b.y;
    GXWGFifo.f32 = b.z;
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u8 = 0xFF;
    GXBegin(GX_LINES, GX_VTXFMT0, 4);
    PSVECScale(&body->pos, lbl_1_rodata_77E4, &a);
    PSVECAdd(&a, (Vec*)&body->quat, pb); // TODO type: reads quat.xyz as a vector
    GXWGFifo.f32 = a.x;
    GXWGFifo.f32 = a.y;
    GXWGFifo.f32 = a.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.f32 = b.x;
    GXWGFifo.f32 = b.y;
    GXWGFifo.f32 = b.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0xFF;
    PSVECScale(&body->angVel, lbl_1_rodata_77E4, pb);
    PSVECAdd(&a, pb, pb);
    GXWGFifo.f32 = a.x;
    GXWGFifo.f32 = a.y;
    GXWGFifo.f32 = a.z;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.f32 = b.x;
    GXWGFifo.f32 = b.y;
    GXWGFifo.f32 = b.z;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    if (BODY_TEST->shape == 0) {
        PSVECSubtract(&body->p0, &body->p1, &a);
        PSVECScale(&a, lbl_1_bss_6BE4[0], &a);
        PSVECAdd(&body->p1, &a, &a);
        PSMTXMultVec(body->world, &a, &a);
        b.x = lbl_1_bss_6BE4[1];
        b.y = lbl_1_bss_6BE4[2];
        b.z = lbl_1_bss_6BE4[3];
        PSVECAdd(&a, pb, pb);
        GXBegin(GX_LINES, GX_VTXFMT0, 2);
        GXWGFifo.f32 = a.x;
        GXWGFifo.f32 = a.y;
        GXWGFifo.f32 = a.z;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.f32 = b.x;
        GXWGFifo.f32 = b.y;
        GXWGFifo.f32 = b.z;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
    }
}

// .text:0x1E290 size:0x340
s16 fn_1_1E290(s16 sel, u16 held, u16 pressed, u16 repeat) {
    if (sel < 0 || sel >= 3) {
        return sel;
    }
    if (repeat & 1) {
        switch (sel) {
        case 0:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.x, held, 1);
            break;
        case 1:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.y, held, 1);
            break;
        case 2:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.z, held, 1);
            break;
        }
    } else if (repeat & 2) {
        switch (sel) {
        case 0:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.x, held, 0);
            break;
        case 1:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.y, held, 0);
            break;
        case 2:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.z, held, 0);
            break;
        }
    } else if (repeat & 8) {
        sel--;
    } else if (repeat & 4) {
        sel++;
    }
    return sel;
}

// .text:0x1E28C size:0x4
void fn_1_1E28C(void) {
}

// .text:0x1DE60 size:0x42C
s16 fn_1_1DE60(s16 sel, u16 held, u16 pressed, u16 repeat) {
    if (sel < 0 || sel >= 4) {
        return sel;
    }
    if (repeat & 1) {
        switch (sel) {
        case 0:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[0], held, 1, lbl_1_rodata_77D8, lbl_1_rodata_77E4);
            break;
        case 1:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[1], held, 1, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        case 2:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[2], held, 1, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        case 3:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[3], held, 1, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        }
    } else if (repeat & 2) {
        switch (sel) {
        case 0:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[0], held, 0, lbl_1_rodata_77D8, lbl_1_rodata_77E4);
            break;
        case 1:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[1], held, 0, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        case 2:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[2], held, 0, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        case 3:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[3], held, 0, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        }
    } else if (repeat & 8) {
        sel--;
    } else if (repeat & 4) {
        sel++;
    }
    return sel;
}

// .text:0x1DE5C size:0x4
void fn_1_1DE5C(void) {
}

f32 fn_1_1DE50(void) {
    return lbl_1_bss_6BE4[0];
}

f32 fn_1_1DE40(void) {
    return lbl_1_bss_6BE4[1];
}

f32 fn_1_1DE30(void) {
    return lbl_1_bss_6BE4[2];
}

f32 fn_1_1DE20(void) {
    return lbl_1_bss_6BE4[3];
}

void fn_1_1DE14(f32 value) {
    lbl_1_bss_6BE4[0] = value;
}

void fn_1_1DE04(f32 value) {
    lbl_1_bss_6BE4[1] = value;
}

void fn_1_1DDF4(f32 value) {
    lbl_1_bss_6BE4[2] = value;
}

void fn_1_1DDE4(f32 value) {
    lbl_1_bss_6BE4[3] = value;
}

// .text:0x1DD94 size:0x50
void fn_1_1DD94(void) {
    Vec axis;
    axis.x = lbl_1_bss_6BE4[1];
    axis.y = lbl_1_bss_6BE4[2];
    axis.z = lbl_1_bss_6BE4[3];
    fn_80037B18(&lbl_1_bss_6BF4, &axis, lbl_1_bss_6BE4[0]);
}

// .text:0x0001DD48 size:0x4C
f32 fn_1_1DD48(u16 buttons, s32 reverse, f32 value, f32 positive, f32 delta, f32 negative, f32 minimum, f32 maximum) {
    if (buttons & 0x40) delta = positive;
    else if (buttons & 0x20) delta = negative;
    if (reverse) delta = -delta;
    value += delta;
    if (value < minimum) value = minimum;
    if (value > maximum) value = maximum;
    return value;
}

// .text:0x1DCE4 size:0x64
void fn_1_1DCE4(void) {
    ChallengeAnimTest* queue = (ChallengeAnimTest*)lbl_803CC1B8;
    queue->file = ARAMTransfer(lbl_1_data_10674, 0, 0, 0);
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1DA54;
}

// .text:0x1DA54 size:0x290
void fn_1_1DA54(void) {
    ChallengeAnimTest* q = (ChallengeAnimTest*)lbl_803CC1B8;
    ChallengeTextureHeader* tex;
    ChTaskHeader* object;
    s32 size;

    if ((s32)lbl_803C6CF8.idle != 1) {
        return;
    }
    q->tex = q->file + *(s32*)(q->file + 0x14); // file-relative offset in the header
    convertTextureHeader(q->tex);
    q->firstImage = 2;
    q->frameCount = 3;
    q->frame = 0;
    q->delay = 3;
    q->timer = 3;
    q->width = 0;
    q->height = 0;
    q->header = _OSAllocFromHeap(0x20, 0x20);
    memcpy(q->header, q->tex + 0x44, 0x20);
    tex = q->header;
    if (tex->palette != NULL) {
        switch (tex->paletteFormat) {
        case 0:
        case 1:
        case 2:
            size = tex->paletteEntries * 2;
            q->header->palette = _OSAllocFromHeap(0x20, size);
            memcpy(q->header->palette, *(void**)(q->tex + 0x48), size);
            break;
        }
        DCStoreRangeNoSync(q->header->palette, size);
        tex = q->header;
        switch (tex->format) {
        case 8:
            size = (tex->width + 7) / 8 * 8 * ((tex->height + 7) / 8 * 8);
            break;
        case 9:
            size = (tex->width + 7) / 8 * 8 * ((tex->height + 3) / 4 * 4);
            break;
        default:
            fn_800AD038(lbl_80366158[2]);
            object = ((ChTaskHeader*)lbl_803CC1B8)->parent;
            object->result = 1;
            fn_800B0A14_removeQueue(object);
            return;
        }
    } else {
        switch (tex->format) {
        case 14:
            size = (tex->width + 7) / 8 * 8 * ((tex->height + 7) / 8 * 8);
            break;
        default:
            fn_800AD038(lbl_80366158[2]);
            object = ((ChTaskHeader*)lbl_803CC1B8)->parent;
            object->result = 1;
            fn_800B0A14_removeQueue(object);
            return;
        }
    }
    q->header->image = _OSAllocFromHeap(0x20, size);
    memcpy(q->header->image, *(void**)(q->tex + 0x44), size);
    DCStoreRangeNoSync(q->header->image, size);
    PPCSync();
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1D944;
}

// .text:0x1D944 size:0x110
void fn_1_1D944(void) {
    ChallengeAnimTest* q = (ChallengeAnimTest*)lbl_803CC1B8;
    ChallengeAnimEntry* e;
    ChTaskHeader* obj;
    u8* d;
    u16 a, b;

    if (lbl_803C77B8._02 & 0x200) {
        fn_800AD038(lbl_80366158[2]);
        obj = ((ChTaskHeader*)lbl_803CC1B8)->parent;
        obj->result = 1;
        fn_800B0A14_removeQueue(obj);
        return;
    }
    if (--q->timer == 0) {
        q->timer = q->delay;
        q->frame = (q->frame + 1) % q->frameCount;
    }
    lbl_1_data_107E4[lbl_803CBBC0[0]].data = q->tex + (q->firstImage + q->frame) * 32 + 4;
    e = &lbl_1_data_107E4[lbl_803CBBC0[0]];
    e->width = q->width;
    e->height = q->height;
    e->active = 1;
    e->table = lbl_1_data_107C4;
    e->tex = q->header;
    fn_800A7D4C(0, e);
}

// NONMATCHING 91%: orig divides height/64, width/32 with srawi/addze (signed); ours srwi (CW knows u16 >= 0); loop regs rotate
// .text:0x1D694 size:0x2B0
#if NONMATCHING
void fn_1_1D694(ChallengeAnimEntry* obj) {
    ChallengeTextureHeader* tex;
    u8* src;
    void* dst;
    s32 rows;
    s32 cols;
    s32 y;
    s32 x;
    s32 v;

    if (obj->active != 0) {
        tex = obj->tex;
        src = obj->table;
        dst = obj->data;
        memset(tex->image, 0, tex->width * tex->height);
        rows = tex->height / 64;
        cols = tex->width / 32;
        for (y = 0; y < rows; y++) {
            for (x = 0; x < cols; x++) {
                if (x & lbl_803CBBC0[0]) {
                    v = src[y * cols + x];
                    fn_80023F0C(dst, tex, v % cols * 32, v / cols * 64, 0x20, 0x40, x * 32, y * 64);
                }
            }
        }
        DCStoreRange(tex->image, tex->width * tex->height);
    }
    {
        Mtx proj;
        Mtx view;

        C_MTXOrtho(*(Mtx44*)proj, lbl_1_rodata_77D8, lbl_1_rodata_77DC[0], lbl_1_rodata_77D8, lbl_1_rodata_77E0[0], lbl_1_rodata_77D8, (&lbl_1_rodata_77E4)[0]);
        PSMTXIdentity(view);
        GXSetProjection(*(Mtx44*)proj, GX_ORTHOGRAPHIC);
        GXLoadPosMtxImm(view, 0);
        GXSetCurrentMtx(0);
    }
    gOz_GXSetTexture(0, 0, 0);
    SetDisplayStateTexture((struct TexImage*)obj->tex, 0, 0); // ChallengeTextureHeader has the TexImage layout
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
    GXWGFifo.u32 = 0xFFFFFFFF;
    GXWGFifo.u16 = 0;
    GXWGFifo.u16 = 0;
    {
        f32 y = obj->tex->height;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = y;
    }
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
    GXWGFifo.u32 = 0xFFFFFFFF;
    GXWGFifo.u16 = 0;
    GXWGFifo.u16 = 1;
    {
        f32 x = obj->tex->width;
        f32 y = obj->tex->height;
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
    }
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
    GXWGFifo.u32 = 0xFFFFFFFF;
    GXWGFifo.u16 = 1;
    GXWGFifo.u16 = 1;
    GXWGFifo.f32 = obj->tex->width;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
    GXWGFifo.u32 = 0xFFFFFFFF;
    GXWGFifo.u16 = 1;
    GXWGFifo.u16 = 0;
}
#endif
