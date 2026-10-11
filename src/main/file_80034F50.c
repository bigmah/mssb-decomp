#include "main/file_80034F50.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"

// spani_default.c

typedef struct SpaniPad {
    /*0x00*/ u16 held;
    /*0x02*/ u16 unk2;
    /*0x04*/ u16 trig;
    /*0x06*/ u8 unk6[0x20 - 0x06];
} SpaniPad;

typedef struct SpaniDrawState {
    /*0x00*/ u8 unk0[0x84];
    /*0x84*/ s32 unk84;
    /*0x88*/ void (*drawCallback)(void);
    /*0x8C*/ u8 unk8C[0x90 - 0x8C];
} SpaniDrawState;

extern SpaniObj lbl_8039C3E0[SPANI_OBJ_COUNT];     // sprite objects
extern SpaniRef lbl_80371C30[];                    // owner-indexed sprite references
extern SpaniTexSlot lbl_803C4BE0[SPANI_TEX_SLOT_COUNT]; // loaded texture/anim banks
extern s16 lbl_8023D6C0[SPANI_OBJ_COUNT];          // texture slot -> id
extern SpaniPad lbl_803C77B8[4];
extern u8 lbl_803C6CF8[];
extern SpaniDrawState lbl_80366188;
extern Mtx lbl_800F78E0[4];
extern Mtx44 lbl_801F8640;
extern Mtx44 lbl_801F8680;
extern u8 lbl_801F86C0[];
extern u8 lbl_803C5F74[];

typedef struct SpaniStrings {
    char noSlot[0x1C];  // " SabNo = %d not to add  \n"
    char file[0x10];    // "spani_default.c"
    char noEmpty[0x14]; // "gasSpani No Empty \n"
} SpaniStrings;
extern SpaniStrings lbl_800E68A8;
extern char lbl_800E68C4[]; // "spani_default.c"
extern char lbl_800E68E8[]; // "It is a number not registered. \n"

extern s32 lbl_803CB810;
extern s32 lbl_803CB814;
extern f32 lbl_803CBBDC;
extern f32 lbl_803CBBE0;
extern u8 lbl_803CBBE4;
extern u8 lbl_803CBC90;
extern u8 lbl_803CBC91;
extern void* lbl_803CBC94;
extern s32 lbl_803CBC98;
extern SpaniObj* lbl_803CBC9C;

extern s32 ARAMTransfer(void*, int, int, int);
extern void convertTextureHeader(void* textures);
extern void fn_800B24D4(u32);
extern void fn_800ACFB0(void* object);
extern void fn_80034BCC(void);
extern void* fn_80052734(s32 index);
extern void fn_800B0D38(s32 index, s32 value);
extern s32 fn_800B216C(u8 flag, u32 mode, u8 index);
extern void fn_800B21A8(s32 mode);
extern void (*fn_8000A094(void (*cb)(void)))(void);
extern void fn_8000B9C8(SpaniAnim* anim);
extern void fn_8000CC4C(SpaniAnim* anim, SpaniTrack* track, void* src, u32 offset, u32 size);
extern u32 fn_8000CEF0(SpaniAnim* anim, u16 animId, u32 track, u32 frame, SpaniKey* out);
extern u8 fn_8000D838(u32* frame, SpaniAnim* anim, u16 animId, Mtx mtx, s32 arg4, s32 arg5, void* arg6, void* tex);
extern void fn_8000F534(SpaniObj* obj, s32 arg1);
extern void fn_80011140(void);
extern void DrawTextOnCondition(u8 layer);
extern void fn_800B27A4(s32 arg0);
extern void fn_800B27DC(Mtx44 mtx, s32 arg1);
extern void fn_800B2854(void* buf, u32 size, Mtx44 mtx, s32 arg3, s32 count, s32* modes, s32 arg6);

static inline s32 spaniFindSlot(s32 id) {
    s32 i;
    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        if (id == lbl_8023D6C0[i]) {
            return i;
        }
    }
    return -1;
}

static inline s8 spaniFindFreeSlot(void) {
    u8 i = 0;
    do {
        if (lbl_803C4BE0[i].data == NULL) {
            return i;
        }
        i++;
    } while (i < SPANI_TEX_SLOT_COUNT);
    return -1;
}

static inline void spaniClearSlot(s32 id) {
    s32 slot = spaniFindSlot(id);
    if (slot != -1) {
        lbl_8023D6C0[slot] = -1;
        lbl_803C4BE0[slot].data = NULL;
        lbl_803C4BE0[slot].tex = NULL;
        lbl_803C4BE0[slot].anim = NULL;
        PSMTXIdentity(lbl_803C4BE0[slot].mtx);
    }
}

// .text:0x80034F50 size:0x218
SpaniObj* fn_80034F50(SpaniDesc* desc) {
    s32 i;
    SpaniObj* obj;

    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        if (lbl_8039C3E0[i].flags == 0) {
            s32 slot;
            for (slot = 0; slot < SPANI_OBJ_COUNT; slot++) {
                if (desc->texId == lbl_8023D6C0[slot]) {
                    break;
                }
            }
            obj = &lbl_8039C3E0[i];
            obj->flags = 1;
            if (desc->type == 1) {
                obj->flags |= 4;
            }
            obj->unk58 = desc->unkC;
            obj->unk74 = desc->unkC;
            obj->animId = desc->animId;
            obj->layer = desc->layer;
            obj->texSlot = slot;
            obj->baseX = desc->x;
            obj->baseY = desc->y;
            obj->baseZ = 0.0f;
            obj->scale = desc->scale;
            obj->is3D = desc->is3D;
            obj->unk4 = 0;
            obj->unk8 = 0;
            obj->unk72 = desc->unk1E;
            obj->unk71 = desc->unk1D;
            if (desc->playMode == 2) {
                obj->playMode = 0;
            } else if (desc->playMode == 3) {
                obj->playMode = 1;
            } else {
                obj->playMode = desc->playMode;
                obj->flags |= 2;
            }
            obj->frame = 0;
            obj->frameStep = 0x10000;
            obj->unkA8 = 0;
            PSMTXIdentity(obj->mtx);
            return obj;
        }
    }
    return NULL;
}

// .text:0x80035168 size:0x550
void fn_80035168(void) {
    return;
}

// .text:0x800356B8 size:0x98
void fn_800356B8(void) {
    s32 i;

    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        lbl_8039C3E0[i].parent = NULL;
        lbl_8039C3E0[i].unk4 = 0;
        lbl_8039C3E0[i].unk8 = 0;
        lbl_8039C3E0[i].flags = 0;
        PSMTXIdentity(lbl_8039C3E0[i].mtx);
        lbl_80371C30[i].obj = NULL;
        lbl_80371C30[i].unk4 = 0;
    }
    fn_80011140();
    lbl_803C5F74[0] = 0;
}

// .text:0x80035750 size:0xE8
void fn_80035750(void) {
    return;
}

// .text:0x80035838 size:0x1C8
void fn_80035838(void) {
    return;
}

// .text:0x80035A00 size:0x150
void fn_80035A00(void) {
    s32 id;

    for (id = 0; id < 25; id++) {
        if ((u32)id > 1) {
            spaniClearSlot(id);
        }
    }
}

// .text:0x80035B50 size:0x154
void fn_80035B50(int id) {
    s32 slot = spaniFindSlot(id);

    if (slot != -1) {
        lbl_8023D6C0[slot] = -1;
        fn_800ACFB0(lbl_803C4BE0[slot].data);
        lbl_803C4BE0[slot].data = NULL;
        lbl_803C4BE0[slot].tex = NULL;
        lbl_803C4BE0[slot].anim = NULL;
        PSMTXIdentity(lbl_803C4BE0[slot].mtx);
    }
}

// .text:0x80035CA4 size:0x130
void fn_80035CA4(s32 id) {
    spaniClearSlot(id);
}

// .text:0x80035DD4 size:0xFC
s32 fn_80035DD4(s32 id) {
    s32 i;
    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        if (id == lbl_8023D6C0[i]) {
            return i;
        }
    }
    return -1;
}

// .text:0x80035ED0 size:0x1C
void fn_80035ED0(s32 idx) {
    lbl_8039C3E0[idx].flags = 0;
}

// .text:0x80035EEC size:0x34
void fn_80035EEC(u16 frame, s32 idx) {
    if (lbl_8039C3E0[idx].frame > (u32)(frame << 16)) {
        lbl_8039C3E0[idx].frame = frame << 16;
        lbl_8039C3E0[idx].playMode = 0;
    }
}

// .text:0x80035F20 size:0x214
void fn_80035F20(void) {
    return;
}

// .text:0x80036134 size:0xE0
void fn_80036134(SpaniOwner* owner, s32 srcIdx, u32 track, s32 dstIdx) {
    SpaniKey key;
    s16 x;
    s16 y;
    SpaniObj* obj = lbl_80371C30[owner->baseIdx + srcIdx].obj;

    fn_8000CEF0(lbl_803C4BE0[obj->texSlot].anim, obj->animId, track, obj->frame >> 16, &key);
    x = key.x;
    y = key.y;
    lbl_80371C30[owner->baseIdx + dstIdx].obj->baseX = x;
    lbl_80371C30[owner->baseIdx + dstIdx].obj->baseY = y;
}

// .text:0x80036214 size:0x5C
s32 fn_80036214(SpaniOwner* owner, s32 idx, u32 track, u32 frame) {
    SpaniKey key;
    SpaniObj* obj = lbl_80371C30[owner->baseIdx + idx].obj;

    fn_8000CEF0(lbl_803C4BE0[obj->texSlot].anim, obj->animId, track, frame, &key);
    return key.unk1C;
}

// .text:0x80036270 size:0x80
void fn_80036270(SpaniOwner* owner, s32 idx, u32 track, u32 frame, s16* outX, s16* outY) {
    SpaniKey key;
    SpaniObj* obj = lbl_80371C30[owner->baseIdx + idx].obj;

    fn_8000CEF0(lbl_803C4BE0[obj->texSlot].anim, obj->animId, track, frame, &key);
    *outX = key.x;
    *outY = key.y;
}

// .text:0x800362F0 size:0xE8
void fn_800362F0(SpaniOwner* owner, s32 idx) {
    s32 i;

    for (i = 0; i < SPANI_TEX_OVERRIDE_COUNT; i++) {
        lbl_80371C30[owner->baseIdx + idx].obj->texOverride[i] = 0xFFFF;
    }
}

// .text:0x800363D8 size:0xC4
void fn_800363D8(SpaniOwner* owner, s32 idx, u32 slot, u16 animId, u32 frame) {
    SpaniKey key;
    u16 texIdx;

    if (slot < SPANI_TEX_OVERRIDE_COUNT) {
        SpaniObj* obj = lbl_80371C30[owner->baseIdx + idx].obj;
        if (fn_8000CEF0(lbl_803C4BE0[obj->texSlot].anim, animId, 0, frame, &key)) {
            texIdx = key.texIdx;
        } else {
            texIdx = 0;
        }
        lbl_80371C30[owner->baseIdx + idx].obj->texOverride[slot] = texIdx;
    }
}

// .text:0x8003649C size:0xD0
void fn_8003649C(void) {
    return;
}

// .text:0x8003656C size:0xE0
void fn_8003656C(void) {
    return;
}

// .text:0x8003664C size:0x1D8
void fn_8003664C(void) {
    return;
}

// .text:0x80036824 size:0x1B8
void fn_80036824(void) {
    return;
}

// .text:0x800369DC size:0x60
void fn_800369DC(f32 zoom) {
    if (0.0f != zoom) {
        f32 s = 1.0f / zoom;
        C_MTXFrustum(lbl_801F8640, -0.175f * s, 0.175f * s, 0.25f * s, -0.25f * s, 1.0f, 512.0f);
    }
}

// .text:0x80036A3C size:0x24C
void fn_80036A3C(void) {
    s32 modes[23];
    s32 i;

    C_MTXFrustum(lbl_801F8680, -0.175f, 0.175f, -0.25f, 0.25f, 1.0f, 512.0f);
    for (i = 0; i < 23; i++) {
        switch (i) {
        case 12:
            modes[i] = 9;
            break;
        case 11:
            modes[i] = 0xA;
            break;
        case 10:
        case 13:
        case 14:
            modes[i] = 0xB;
            break;
        case 0:
            modes[i] = 0xD;
            break;
        default:
            modes[i] = 0xC;
            break;
        }
    }
    fn_800B2854(lbl_801F86C0, 0x45000, lbl_801F8680, 0, 23, modes, 0);
    fn_800B27A4(10);
    for (i = 0xD; i < 23; i++) {
        fn_800B0D38(i, 2);
    }
    for (i = 0; i < SPANI_OBJ_COUNT; i++) {
        lbl_8023D6C0[i] = -1;
    }
    lbl_803CBBE4 = 0;
    lbl_803CBBE0 = 2.0f;
    lbl_803CBBDC = 1280.0f;
    memset(lbl_8039C3E0, 0, sizeof(lbl_8039C3E0));
    lbl_80366188.unk84 = 0;
    lbl_80366188.drawCallback = NULL;
}

// .text:0x80036C88 size:0x3CC
// NONMATCHING 99.9%: r3/r4 swapped in the final dst[0] update
#if NONMATCHING
s32 fn_80036C88(s32* src, s32* dst) {
    s32 i;
    s32 sum;
    s32 diff;
    s32 idx;

    memcpy(dst, src, 23 * sizeof(s32));
    sum = 0;
    for (i = 0; i < 23; i++) {
        sum += src[i];
    }
    diff = 0x22800 - sum;
    if (diff < 0) {
        s32 excess = -diff;
        s32 take;
        do {
            s32 min = 0x7FFFFFFF;
            for (i = 0; i < 23; i++) {
                if (dst[i] != 0 && min >= dst[i]) {
                    idx = i;
                    min = dst[i];
                }
            }
            take = dst[idx];
            if (excess <= take) {
                take = excess;
            }
            excess -= take;
            dst[idx] -= take;
        } while (excess > 0 && take != 0);
        if (excess != 0) {
            for (i = 0; i < 23; i++) {
                dst[i] = 0x1800;
            }
        }
        return 1;
    }
    if (diff != 0) {
        s32 add = (diff / 23 / 32) * 32;
        s32 j;
        for (j = 0; j < 23; j++) {
            dst[j] += add;
        }
        dst[0] += diff - add * 23;
    }
    return 0;
}
#endif
