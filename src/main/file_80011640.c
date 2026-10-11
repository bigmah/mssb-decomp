#include "main/file_80011640.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"
#include "Dolphin/GX/GXTypes.h"
#include "Dolphin/gx.h"
#include "math.h"

// Globals owned by other units (only the fields used here).
typedef struct GameSettingsView {
    /*0x00*/ u8 _00[0x6];
    /*0x06*/ u8 _06;
    /*0x07*/ u8 GameModeSelected;
    /*0x08*/ u8 _08;
    /*0x09*/ u8 StadiumID;
    /*0x0A*/ u8 _0A[0x7];
    /*0x11*/ u8 minigamesEnabled;
    /*0x12*/ u8 _12[0x54 - 0x12];
    /*0x54*/ u8 _54;
} GameSettingsView;

typedef struct AramState {
    /*0x000*/ u8 _000[0x715];
    /*0x715*/ u8 transferDone;
} AramState;

typedef struct Unk803716B8 {
    /*0x000*/ u8 _000[0x1E8];
    /*0x1E8*/ u8 _1E8;
} Unk803716B8;

// Camera returned by fn_80052734.
typedef struct CameraView {
    /*0x00*/ Mtx44 proj;
    /*0x40*/ Mtx view;
    /*0x70*/ Vec eye;
    /*0x7C*/ Vec target;
    /*0x88*/ Vec up;
} CameraView;

// Camera description handed to the shadow renderer.
typedef struct ShadowView {
    /*0x00*/ Vec eye;
    /*0x0C*/ Vec up;
    /*0x18*/ Vec target;
    /*0x24*/ u8 _24[0x1C];
    /*0x40*/ Mtx view;
    /*0x70*/ u8 _70[0xE4 - 0x70];
} ShadowView; // size: 0xE4

// ARAM file table entry.
typedef struct AramFile {
    /*0x00*/ u32 _00;
    /*0x04*/ u32 size; // top 4 bits are flags
    /*0x08*/ u8 _08[0x8];
} AramFile;

extern GameSettingsView g_d_GameSettings;
extern AramState lbl_803C6CF8;
extern Unk803716B8 lbl_803716B8;
extern AramFile* lbl_803CB790;
extern s32 lbl_803CBBF0;
extern CharLoadTask* lbl_803CC1B8;
extern CharPart lbl_80118220[13];

typedef struct RosterEntry {
    /*0x00*/ u8 _00[0x24];
    /*0x24*/ s16 charId;
    /*0x26*/ u8 _26;
    /*0x27*/ u8 _27;
    /*0x28*/ u8 _28[0xA0 - 0x28];
} RosterEntry; // size: 0xA0

extern RosterEntry inMemRoster[2][9];

extern LightPos lbl_80367318[4];
extern StadiumLights lbl_800F7478[];
extern u8 lbl_803CBC3C[4];
extern AramFile lbl_800EE910[2];

extern void fn_80023B90(LightSrc* src, LightPos* dst);
extern void fn_800BEBCC(s32 index, Vec* dir);
extern void ANIMGet(void* bank);
extern void fn_800B2C10(CharModel* model, u16 joint, Vec* out);
extern void fn_800B2C44(CharModel* model, u16 joint, Vec* out);
extern void convertTextureHeader(void* textures);
extern void LoadActorLayout(void* layout);
extern void convertGeometryAndSknHeader(void* geo, void* skn);
extern void haveActLayoutPointToGeoHeader(void* layout, void* geo);
extern void fn_800BD190(void* geo, void* tex);
extern void fn_8002399C(CharSlot* slot, s32 modelIndex, u16 index, void* layout, void* bank, void* skn);
extern void fn_800B2B74(CharModel* model, u16 joint);
extern void fn_800B2B54(CharModel* model, u16 joint, s32 arg);
extern void fn_800B2BA8(CharModel* model, u16 joint, s32 a, s32 b);
extern void fn_800B2C08(CharModel* model, u16 joint);
extern void fn_800BD548(CharSlot* slot, s32 count, ...);
extern void fn_800638B4(CharActor* actor, CharSlot* slot);
extern void fn_80063010(CharActor* actor, CharSlot* slot);
extern void fn_8004B7B4(CharActor* actor, CharSlot* slot);
extern void fn_800637BC(CharActor* actor, CharSlot* slot);
extern void fn_800637D4(CharActor* actor, CharSlot* slot);
extern void fn_8004BD6C(CharActor* actor, CharSlot* slot);
extern void fn_80052634(CharActor* actor, CharSlot* slot);
extern void fn_80062ED4(CharActor* actor, CharSlot* slot);
extern void fn_800238E0(CharSlotList* list, u8 first, u8 last, void* layout);
extern void fn_80021CA4(s32 id, s32 kind, void** files);
extern void OSPanic(const char* file, int line, const char* msg, ...);
extern u8 lbl_803CB7B4[8];
extern u8 lbl_803CB7C4[4];
extern s16 lbl_800EEAAC[];
extern CharPart* lbl_803CBC10;
extern u8 lbl_803CBC14;
extern u8 lbl_803CBC15;
extern void* _OSAllocFromHeap(s32 heap, u32 size);
extern void DOVARender(void* display, MtxPtr view, s32 n, va_list args);
extern void DOVARenderSkin(void* display, MtxPtr view, void* p, void* q, s32 n);
extern void DOSetWorldMatrix(void* display, MtxPtr mtx);
extern void fn_800BD2DC(void);
extern void fn_800BD2CC(s32 channel, GXColor color);
extern void LITAlloc(void** light);
extern void LITInitAttn(void* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
extern void LITInitPos(void* light, f32 x, f32 y, f32 z);
extern void LITInitColor(void* light, u32* color);
extern void ACTSetAnimation(void* act, void* bank, s32 a, u16 anim, f32 frame, f32 speed);
extern void fn_800B4CA0(CharModel* model, f32 v);
extern void fn_800B4C04(CharModel* model, f32 v);
extern void fn_800B4AFC(CharModel* model, s32 v);
extern void Set_FUN_800b2b6c(CharModel* model, void* p);
extern void fn_800BDA24(CharSlot* slot);
extern s32 fn_800527BC(void);
extern CameraView* fn_80052734(u16 index);
extern u8 fn_800B3C04(u16 index, CharModel* model, Mtx m);
extern s32 fn_8003A538(void);
extern void fn_8003A4C8(void);
extern u16 fn_8005268C(void);
extern void fn_800BD1E8(u32 value);
extern u8 GetDrawShadows(void);
extern void DrawShadows(u8 enable);
extern void fn_800BEC00(s32 reverse);
extern void fn_800BF058(void (*draw)(CharSlot*, s32, s32));
extern void fn_800BE09C(CharSlotList* list, ShadowView* view);
extern void fn_800BDFE0(CharSlotList* list);
extern void fn_800BDEA0(void);
extern void (*lbl_803CBBF4)(void);
extern void ACTSetBoneTrack(CharJoint* bone, void* track, s32 flag, f32 time);
extern AramFile* lbl_803CB794;
extern void* lbl_803CBC30;
extern u8 lbl_803CBC34[8];
extern s16 lbl_800EEB18[54];
extern CharSlotList* fn_80023AA4(void);
extern void fn_80023B04(s32 count);
extern AramFile* lbl_803CB7A8;
extern u8* lbl_803CBC24;
// Joint mirror pairs (0xFFFF-terminated u16 pairs).
// TODO type: these live inside lbl_800EE930's data block.
extern u16 lbl_800EE930[];
extern u16 lbl_803CB798[4];
extern u16 lbl_803CB7A0[4];
typedef struct Unk80366158 {
    /*0x00*/ u8 _00[0x28];
    /*0x28*/ u8 _28;
} Unk80366158;

extern Unk80366158 lbl_80366158;
extern f32 fn_800B4A44(CharModel* model, u16 joint);
extern f32 fn_800B4C40(CharModel* model);
extern s32 fn_8004AD54(u8 stadium, u8 kind);
extern void fn_8004B208(CharActor* actor, s16 anim, s32 a, f32 t);
extern CharSlotList* ActorObjectInitTable(s32 count);
extern void fn_800BDC88(CharSlotList* list, u16 first, u16 last, void* layout, s32 a, s32 b);
extern void fn_800B2B4C(CharModel* model, f32 v);
extern void fn_800B9948(s32 value);
extern void fn_800B993C(void);
extern CharActor* lbl_803CBC18;
extern u8 lbl_800EEA58[25];
extern void fn_8003A540(s32 arg);
extern void fn_800BF048(void (*fn)(void));
extern void* ARAMTransfer(AramFile* file, void* dst, s32 a, s32 b);
extern u32 fn_8002204C(s32 id, void* buffer);
extern void fn_8003AC90(void);
extern void fn_800ACFB0(void* object);
extern void fn_800B9AA8(void* object);
extern void fn_800B2D5C(CharModel* model);
extern void fn_800B0A14_removeQueue(void* unused);
extern void* fn_800B0A5C_insertQueue(void* draw, s32 priority);

static inline s32 getJoint(CharActor* actor, s32 k) {
    return actor != NULL ? actor->jointIdx[k] : 0xFFFF;
}

static inline void copyPartJointData(CharActor* actor, s32 which) {
    s32 joint = actor != NULL ? actor->jointIdx[lbl_803CB7B4[which]] : 0xFFFF;
    CharModel** models;
    CharModel* model;
    CharJoint* dst;
    CharModel* src;
    CharJoint** jp;
    s32 i;
    s32 n;

    if (joint != 0xFFFF) {
        models = &actor->model;
        i = 0;
        do {
            model = *models;
            if (lbl_800EEAAC[actor->kind] >= 0 && actor->parts != NULL) {
                dst = model->joints[joint];
                if (which & 1) {
                    src = lbl_8036E548.partSlots->slots[actor->parts->part[1].slot].model;
                } else {
                    src = lbl_8036E548.partSlots->slots[actor->parts->part[0].slot].model;
                }
                if (src != NULL) {
                    n = src->jointCount;
                    jp = &src->joints[n];
                    do {
                        jp--;
                        n--;
                        if ((*jp)->display != NULL) {
                            dst->display = (*jp)->display;
                            break;
                        }
                    } while (n != 0);
                }
                break;
            }
            models--;
        } while (i-- != 0);
    }
}

static inline void initModelJoints(CharActor* actor, CharSlot* slot) {
    s32 j;

    fn_800B2B74(slot->model, actor->jointIdx[19]);
    fn_800B2B74(slot->model, actor->jointIdx[25]);
    fn_800B2B74(slot->model, actor->jointIdx[36]);
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2B54(actor->model, j, 0xD);
    }
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
        slot->model->joints[(u16)j]->_136 = 1;
    }
    j = actor->jointIdx[2];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
        slot->model->joints[(u16)j]->_136 = 1;
    }
    j = actor->jointIdx[1];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
        slot->model->joints[(u16)j]->_136 = 1;
    }
    j = actor->jointIdx[36];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
    }
    j = actor->jointIdx[46];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
        slot->model->joints[(u16)j]->_136 = 1;
    }
    fn_800B2C08(slot->model, actor->jointIdx[4]);
}

// .text:0x80011640 size:0x9C
void fn_80011640(Mtx a, Mtx out) {
    Mtx scale = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.93333334f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };
    PSMTXConcat(scale, a, out);
}

// .text:0x800116DC size:0xF0
void fn_800116DC(CharActor* actor, Mtx m, u16 joint) {
    Mtx tmp;
    Mtx scale = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0714285f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };
    MtxPtr dst;

    PSMTXConcat(scale, m, tmp);
    tmp[0][3] = 0.0f;
    tmp[1][3] = 0.0f;
    tmp[2][3] = 0.0f;
    PSMTXInverse(tmp, tmp);
    dst = actor->model->joints[joint]->worldMtx;
    tmp[0][3] = dst[0][3];
    tmp[1][3] = dst[1][3];
    tmp[2][3] = dst[2][3];
    PSMTXCopy(tmp, dst);
}

// .text:0x800117CC size:0xE0
void fn_800117CC(Mtx src, Mtx m, Mtx dst) {
    Mtx tmp;
    Mtx scale = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0714285f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };

    PSMTXConcat(scale, m, tmp);
    tmp[0][3] = 0.0f;
    tmp[1][3] = 0.0f;
    tmp[2][3] = 0.0f;
    PSMTXInverse(tmp, tmp);
    tmp[0][3] = src[0][3];
    tmp[1][3] = src[1][3];
    tmp[2][3] = src[2][3];
    PSMTXCopy(tmp, dst);
}

// .text:0x800118AC size:0xC0
MtxPtr fn_800118AC(Mtx m, Mtx out) {
    Mtx scale = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0714285f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };

    PSMTXConcat(scale, m, out);
    out[0][3] = 0.0f;
    out[1][3] = 0.0f;
    out[2][3] = 0.0f;
    PSMTXInverse(out, out);
    return out;
}

// .text:0x8001196C size:0xF4
static inline void clearSlotRefs(s32 index) {
    s32 j;
    for (j = 0; j < 13; j++) {
        if (lbl_8036E548._2D6A[j] == index) {
            lbl_8036E548._2D6A[j] = -1;
        }
    }
}

static inline void detachOwnedPart(s32 index) {
    CharActor* actor;
    CharPart* part;

    actor = lbl_8036E548.active[index];
    if (actor != NULL && (part = actor->part) != NULL && actor->index == index) {
        part->_61 = -1;
        part->player.curIdx = -2;
        lbl_8036E548.active[index]->part = NULL;
    }
}

static inline void detachOwnedParts(s32 index) {
    CharActor* actor;
    CharParts* parts;

    actor = lbl_8036E548.active[index];
    if (actor != NULL && (parts = actor->parts) != NULL && actor->index == index) {
        parts->_D1 = parts->_D0;
        parts->_D0 = -1;
        parts->part[0].player.curIdx = -2;
        parts->part[1].player.curIdx = -2;
        lbl_8036E548.active[index]->parts = NULL;
    }
}

// NONMATCHING 97%: r7/r8 swapped (active[i] pointer vs parts)
#if NONMATCHING
void fn_8001196C(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        detachOwned(i);
        lbl_8036E548.active[i]->_25C = 0;
        lbl_8036E548.active[i] = NULL;
        clearSlotRefs(i);
    }
}
#endif

// .text:0x80011A60 size:0x104
// NONMATCHING 97%: register allocation only
#if NONMATCHING
void fn_80011A60(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        idx = i + 9;
        detachOwnedPart(idx);
        detachOwnedParts(idx);
        if (lbl_8036E548.active[idx] != NULL) {
            lbl_8036E548.active[idx]->_25C = 0;
            lbl_8036E548.active[idx] = NULL;
        }
        clearSlotRefs(idx);
    }
}
#endif

// .text:0x80011B64 size:0x80
void fn_80011B64(s32 index) {
    CharActor* actor;
    CharPart* part;
    CharParts* parts;

    actor = lbl_8036E548.active[index];
    if (actor != NULL) {
        part = actor->part;
        if (part != NULL) {
            part->_61 = -1;
            part->player.curIdx = -2;
            lbl_8036E548.active[index]->part = NULL;
        }
        parts = lbl_8036E548.active[index]->parts;
        if (parts != NULL) {
            parts->_D1 = parts->_D0;
            parts->_D0 = -1;
            parts->part[0].player.curIdx = -2;
            parts->part[1].player.curIdx = -2;
            lbl_8036E548.active[index]->parts = NULL;
        }
    }
}

// .text:0x80011BE4 size:0xC4
void fn_80011BE4(s32 index) {
    s32 j;
    CharActor* actor;
    CharPart* part;
    CharParts* parts;

    actor = lbl_8036E548.active[index];
    if (actor != NULL) {
        part = actor->part;
        if (part != NULL) {
            part->_61 = -1;
            part->player.curIdx = -2;
            lbl_8036E548.active[index]->part = NULL;
        }
        parts = lbl_8036E548.active[index]->parts;
        if (parts != NULL) {
            parts->_D1 = parts->_D0;
            parts->_D0 = -1;
            parts->part[0].player.curIdx = -2;
            parts->part[1].player.curIdx = -2;
            lbl_8036E548.active[index]->parts = NULL;
        }
        lbl_8036E548.active[index]->_25C = 0;
    }
    lbl_8036E548.active[index] = NULL;
    for (j = 0; j < 13; j++) {
        if (lbl_8036E548._2D6A[j] == index) {
            lbl_8036E548._2D6A[j] = -1;
        }
    }
}

// .text:0x80011CA8 size:0xA44
static inline void copyPart(CharPart* dst, CharPart* src) {
    dst->files = src->files;
    dst->slot = src->slot;
    dst->player.set = src->player.set;
    dst->player.seqs = src->player.seqs;
    dst->player.tableList = src->player.tableList;
    dst->player.model = src->player.model;
    dst->player.curIdx = src->player.curIdx;
    memcpy(&dst->player.state, &src->player.state, sizeof(dst->player.state));
    memcpy(dst->player.tables, src->player.tables, sizeof(dst->player.tables));
}

static inline void stashPart(CharPart* tmp, CharPart* src) {
    copyPart(&tmp[src->slot % 6], src);
}

// NONMATCHING 99.7%: copy-field temps register allocation; used[] initialiser is an anonymous .sbss2 object
#if NONMATCHING
s32 fn_80011CA8(CharActor* actor, s32 a, s32 b) {
    u8 used[6] = { 0, 0, 0, 0, 0, 0 };
    CharPart tmp[6];
    s32 idx = actor->index;
    s32 first;
    s32 second;
    s32 k;
    s32 n;

    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 0].part[0]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 0].part[1]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 1].part[0]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 1].part[1]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 2].part[0]);
    stashPart(tmp, &lbl_8036E548.partsPool[idx * 3 + 2].part[1]);
    if ((u32)(a - 2) > 2) {
        if (actor->_25B != 0) {
            first = 2;
            second = 3;
        } else {
            first = 4;
            second = 5;
        }
    } else if (actor->_25A != 0) {
        first = 4;
        second = 1;
    } else {
        first = 0;
        second = 3;
    }
    copyPart(&actor->parts->part[0], &tmp[first]);
    copyPart(&actor->parts->part[1], &tmp[second]);
    used[first] = 1;
    used[second] = 1;
    n = 0;
    for (k = 0; k < 6; k++) {
        if (used[k] == 0) {
            switch (n) {
            case 0:
                copyPart(&lbl_8036E548.partsPool[idx * 3 + 1].part[0], &tmp[k]);
                break;
            case 1:
                copyPart(&lbl_8036E548.partsPool[idx * 3 + 1].part[1], &tmp[k]);
                break;
            case 2:
                copyPart(&lbl_8036E548.partsPool[idx * 3 + 2].part[0], &tmp[k]);
                break;
            case 3:
                copyPart(&lbl_8036E548.partsPool[idx * 3 + 2].part[1], &tmp[k]);
                break;
            }
            n++;
        }
    }
    copyPartJointData(lbl_8036E548.active[actor->index], 0);
    copyPartJointData(lbl_8036E548.active[actor->index], 1);
    fn_80025EEC(&actor->parts->part[0].player, a, b);
    fn_80025EEC(&actor->parts->part[1].player, a, b);
    return 1;
}
#endif

// .text:0x800126EC size:0x10C
void fn_800126EC(CharPart* part, void* tex, u8* fileIdx) {
    void* layout;
    void* geo;
    CharSlot* slot;

    slot = &lbl_8036E548.partSlots->slots[part->slot];
    layout = part->files[fileIdx[0]];
    geo = part->files[fileIdx[1]];
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, NULL);
    haveActLayoutPointToGeoHeader(layout, geo);
    fn_800BD190(geo, tex);
    fn_800238E0(lbl_8036E548.partSlots, part->slot, part->slot, layout);
    if (part->files[2] != NULL) {
        fn_80025DDC(part->files[fileIdx[2]]);
        fn_80025C58(part->files[fileIdx[2]], (ShapeModel**)&slot->model);
    }
    part->player.set = part->files[fileIdx[3]];
    fn_80025FFC(part->files[fileIdx[2]], &part->player);
}

// .text:0x800127F8 size:0x398

// NONMATCHING 99%: register allocation only (actor/tex, joint-copy temps)
#if NONMATCHING
u8 LoadModel(CharActor* actor) {
    CharParts* parts;
    CharPart* part;
    void** files;
    void* tex;

    if (actor == NULL) {
        OSPanic("model.c", 0x22E6, " Character Data None \n");
        return 0;
    }
    parts = actor->parts;
    if (parts == NULL) {
        OSPanic("model.c", 0x22EA, " Character Parts Data None \n");
        return 0;
    }
    if (lbl_803CBC14 == 0 && (s32)lbl_803C6CF8.transferDone == 1) {
        if (parts->_CD != 0) {
            part = &parts->part[1];
            lbl_803CBC10 = part;
            fn_80021CA4(actor->parts->_CF, 5, part->files);
            lbl_803CBC15 = 1;
        } else {
            lbl_803CBC10 = &parts->part[0];
            fn_80021CA4(actor->parts->_CF, 0, parts->part[0].files);
            lbl_803CBC15 = 0;
        }
        lbl_803CBC14 = 1;
    }
    if (lbl_803716B8._1E8 == 0) {
        part = lbl_803CBC10;
        tex = actor->parts->tex;
        // TODO type: the file header holds offsets that are relocated in place.
        files = part->files;
        if (files[0] != NULL) {
            files[0] = (u8*)files + (u32)files[0];
        }
        files = part->files;
        if (files[1] != NULL) {
            files[1] = (u8*)files + (u32)files[1];
        }
        files = part->files;
        if (files[2] != NULL) {
            files[2] = (u8*)files + (u32)files[2];
        }
        files = part->files;
        if (files[3] != NULL) {
            files[3] = (u8*)files + (u32)files[3];
        }
        fn_800126EC(part, tex, lbl_803CB7C4);
        copyPartJointData(lbl_8036E548.active[actor->index], lbl_803CBC15);
        lbl_803CBC14 = 0;
        lbl_803CBC10 = NULL;
        return 1;
    }
    return 0;
}
#endif

// .text:0x80012B90 size:0xAF0
void fn_80012B90(void) {
    return;
}

// .text:0x80013680 size:0xB84
void fn_80013680(void) {
    return;
}

// .text:0x80014204 size:0x3F4
void fn_80014204(void) {
    return;
}

// .text:0x800145F8 size:0x398
static inline u32 maxPartSize(u32 max, s32 idx) {
    s32 j;
    u32 size;

    for (j = 0; j < 6; j++) {
        size = lbl_803CB7A8[idx + j].size & 0x0FFFFFFF;
        if (max < size) {
            max = size;
        }
    }
    return max;
}

// NONMATCHING 84%: max-size loops unrolled/scheduled differently
#if NONMATCHING
void fn_800145F8(s32 mode) {
    u32 max = 0;
    u32 s;
    u8* buf;
    s32 t;
    s32 i;
    s32 idx;

    if (mode == 0) {
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                idx = lbl_800EEAAC[inMemRoster[t][i].charId];
                if (idx >= 0) {
                    max = maxPartSize(max, idx);
                }
            }
        }
    } else {
        for (i = 0; i < 54; i++) {
            idx = lbl_800EEAAC[i];
            if (idx >= 0) {
                max = maxPartSize(max, idx);
            }
        }
    }
    s = (max + 0x1F) & ~0x1F;
    buf = _OSAllocFromHeap(0x20, s * 26);
    lbl_803CBC24 = buf;
    for (i = 0; i < 13; i++) {
        lbl_8036E548.partsPool[i].part[0].files = (void**)(buf + s * (i * 2));
        lbl_8036E548.partsPool[i].part[1].files = (void**)(buf + s * (i * 2 + 1));
    }
    for (i = 0; i < 13; i++) {
        lbl_8036E548.partsPool[i]._CF = -1;
        lbl_8036E548.partsPool[i]._D1 = -1;
        lbl_8036E548.partsPool[i]._D0 = -1;
        lbl_8036E548.partsPool[i]._CD = 0xFF;
        lbl_8036E548.partsPool[i]._CE = 0xFF;
        lbl_8036E548.partsPool[i].tex = NULL;
        lbl_8036E548.partsPool[i]._CC = 0;
        lbl_8036E548.partsPool[i].part[0].slot = i * 2;
        lbl_8036E548.partsPool[i].part[1].slot = i * 2 + 1;
    }
}
#endif

// .text:0x80014990 size:0x88
void fn_80014990(s32 index, void* model, ShapeAnimSet* set) {
    CharActor* actor;
    CharPart* part;

    if (index >= 0 && index < 13) {
        actor = lbl_8036E548.active[index];
        if (actor != NULL) {
            goto found;
        }
    }
    return;
found:
    part = &lbl_80118220[index];
    actor->part = part;
    part->slot = actor->kind;
    part->_61 = actor->index;
    part->player.set = set;
    part->player.model = model;
    fn_80025FFC(model, &part->player);
}

// .text:0x80014A18 size:0x334
// NONMATCHING 89%: free-slot search ladder addressing and register allocation
#if NONMATCHING
s32 fn_80014A18(void) {
    s32 i;
    s32 k;
    s32 done;
    CharActor* actor;

    if (lbl_8036E548._2D8E == 0) {
        lbl_8036E548._2D8E = 1;
        lbl_8036E548.loadActor = -1;
        for (i = 0; i < 9; i++) {
            lbl_8036E548._2D7F[i] = -1;
        }
    }
    if (lbl_8036E548._2D8E == 1) {
        for (i = 0; i <= 8; i++) {
            for (k = 0; k < 9; k++) {
                if (lbl_8036E548.active[i]->kind == lbl_8036E548._2D7F[k]) {
                    lbl_8036E548.active[i]->banks.b[5] = lbl_8036E548.animBufs[5 + k];
                    break;
                }
            }
            if (k >= 9) {
                lbl_8036E548.loadStep = 0;
                lbl_8036E548._2D8E = 2;
                lbl_8036E548.loadActor = i;
                break;
            }
        }
        if (i > 8) {
            return 1;
        }
    }
    if (lbl_8036E548._2D8E == 2) {
        actor = &lbl_8036E548.actors[lbl_8036E548.active[lbl_8036E548.loadActor]->modelIndex];
        if (lbl_8036E548.loadStep == 0) {
            k = 0;
            if (lbl_8036E548._2D7F[0] >= 0) {
                k = 1;
                if (lbl_8036E548._2D7F[1] >= 0) {
                    k = 2;
                    if (lbl_8036E548._2D7F[2] >= 0) {
                        k = 3;
                        if (lbl_8036E548._2D7F[3] >= 0) {
                            k = 4;
                            if (lbl_8036E548._2D7F[4] >= 0) {
                                k = 5;
                                if (lbl_8036E548._2D7F[5] >= 0) {
                                    k = 6;
                                    if (lbl_8036E548._2D7F[6] >= 0) {
                                        k = 7;
                                        if (lbl_8036E548._2D7F[7] >= 0) {
                                            k = 8;
                                            if (lbl_8036E548._2D7F[8] >= 0) {
                                                k = 9;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            lbl_8036E548._2D7F[k] = actor->kind;
            if (lbl_8036E548._2D7C == 0) {
                actor->banks.b[2] = lbl_8036E548.animBufs[5 + k];
                ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 4], actor->banks.b[2], 0, 0);
            } else {
                actor->banks.b[5] = lbl_8036E548.animBufs[5 + k];
                ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 0x11], actor->banks.b[5], 0, 0);
            }
            lbl_8036E548.loadStep = 1;
            done = 0;
        } else if ((s32)lbl_803C6CF8.transferDone == 1) {
            if (lbl_8036E548._2D7C == 0) {
                ANIMGet(actor->banks.b[2]);
            } else {
                ANIMGet(actor->banks.b[5]);
            }
            done = 1;
        } else {
            done = 0;
        }
        if (done) {
            lbl_8036E548._2D8E = 1;
        }
    }
    return 0;
}
#endif

// .text:0x80014D4C size:0x104
s32 fn_80014D4C(s32 id) {
    s32 file;

    if (id < 0) {
        return 1;
    }
    if (lbl_8036E548.preload[1].id == id) {
        return 1;
    }
    if (lbl_8036E548.preload[1].state <= 1) {
        if (g_d_GameSettings.GameModeSelected == 2) {
            file = id * 0x13 + 0xA;
        } else {
            file = id * 0x13 + 2;
        }
        if ((s32)lbl_803C6CF8.transferDone != 1) {
            lbl_8036E548.preload[1].state = 1;
            return 0;
        }
        ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.preload[1].buffer, 0, 0);
        lbl_8036E548.preload[1].state = 2;
    } else if ((s32)lbl_803C6CF8.transferDone == 1) {
        lbl_8036E548.preload[1].id = id;
        lbl_8036E548.preload[1].state = 0;
        return 1;
    }
    return 0;
}

// .text:0x80014E50 size:0xF0
s32 fn_80014E50(s32 id) {
    s32 file;

    if (id < 0) {
        return 1;
    }
    if (lbl_8036E548.preload[2].state <= 1) {
        file = id * 0x13;
        if ((s32)lbl_803C6CF8.transferDone != 1) {
            lbl_8036E548.preload[2].state = 1;
            return 0;
        }
        if (fn_8002204C(id, lbl_8036E548.preload[2].buffer) == 0) {
            ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.preload[2].buffer, 0, 0);
        }
        lbl_8036E548.preload[2].state = 2;
    } else if (lbl_803716B8._1E8 == 0 && (s32)lbl_803C6CF8.transferDone == 1) {
        lbl_8036E548.preload[2].id = id;
        lbl_8036E548.preload[2].state = 0;
        return 1;
    }
    return 0;
}

// .text:0x80014F40 size:0xCC
s32 fn_80014F40(s32 id) {
    s32 file;

    if (id < 0) {
        return 1;
    }
    if (lbl_8036E548.preload[0].state <= 1) {
        file = id * 0x13 + 1;
        if ((s8)lbl_803C6CF8.transferDone != 1) {
            lbl_8036E548.preload[0].state = 1;
            return 0;
        }
        ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.preload[0].buffer, 0, 0);
        lbl_8036E548.preload[0].state = 2;
    } else if ((s32)lbl_803C6CF8.transferDone == 1) {
        lbl_8036E548.preload[0].id = id;
        lbl_8036E548.preload[0].state = 0;
        return 1;
    }
    return 0;
}

// .text:0x8001500C size:0x45C
void fn_8001500C(void) {
    return;
}

// .text:0x80015468 size:0x4E4
void fn_80015468(void) {
    return;
}

// .text:0x8001594C size:0x9F8
void fn_8001594C(void) {
    return;
}

// .text:0x80016344 size:0x3CC
void fn_80016344(void) {
    return;
}

// .text:0x80016710 size:0x450
void fn_80016710(void) {
    return;
}

// .text:0x80016B60 size:0x41C
s32 fn_80016B60(CharActor* actor) {
    s32 file;

    if (lbl_8036E548.loadStep == 0) {
        lbl_8036E548.loadStep = 1;
    }
    if (lbl_8036E548.loadStep == 1) {
        actor->banks.b[2] = lbl_8036E548.bankSets[actor->modelIndex][0];
        if (g_d_GameSettings.GameModeSelected == 7) {
            file = actor->kind * 0x13 + 0xD;
        } else {
            file = actor->kind * 0x13 + 4;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[2], 0, 0);
        lbl_8036E548.loadStep = 2;
    } else if (lbl_8036E548.loadStep == 2) {
        if ((s32)lbl_803C6CF8.transferDone == 1) {
            ANIMGet(actor->banks.b[2]);
            lbl_8036E548.loadStep = 3;
        }
    } else if (lbl_8036E548.loadStep == 3) {
        actor->banks.b[1] = lbl_8036E548.bankSets[actor->modelIndex][1];
        if (g_d_GameSettings.GameModeSelected == 2) {
            file = actor->kind * 0x13 + 0xB;
        } else if (g_d_GameSettings.GameModeSelected == 6) {
            file = actor->kind * 0x13 + 0xE;
        } else {
            file = actor->kind * 0x13 + 0xC;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[1], 0, 0);
        lbl_8036E548.loadStep = 4;
    } else if (lbl_8036E548.loadStep == 4) {
        if ((s32)lbl_803C6CF8.transferDone == 1) {
            ANIMGet(actor->banks.b[1]);
            lbl_8036E548.loadStep = 5;
        }
    } else if (lbl_8036E548.loadStep == 5) {
        actor->banks.b[3] = lbl_8036E548.bankSets[actor->modelIndex][2];
        if (g_d_GameSettings.minigamesEnabled != 0 || g_d_GameSettings.GameModeSelected == 2) {
            file = actor->kind * 0x13 + 0x12;
        } else {
            file = actor->kind * 0x13 + 5;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[3], 0, 0);
        lbl_8036E548.loadStep = 6;
    } else if (lbl_8036E548.loadStep == 6) {
        if ((s32)lbl_803C6CF8.transferDone == 1) {
            ANIMGet(actor->banks.b[3]);
            actor->banks.b[0] = lbl_8036E548.bankSets[0][3];
            lbl_8036E548.loadStep = 9;
        }
    } else if (lbl_8036E548.loadStep == 7) {
        actor->banks.b[0] = lbl_8036E548.bankSets[actor->modelIndex][3];
        if (g_d_GameSettings.GameModeSelected == 7) {
            file = actor->kind * 0x13 + 9;
        } else if (g_d_GameSettings.GameModeSelected == 2) {
            file = actor->kind * 0x13 + 0xA;
        } else {
            file = actor->kind * 0x13 + 2;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[0], 0, 0);
        lbl_8036E548.loadStep = 8;
    } else if (lbl_8036E548.loadStep == 8) {
        if ((s32)lbl_803C6CF8.transferDone == 1) {
            ANIMGet(actor->banks.b[0]);
            lbl_8036E548.loadStep = 9;
        }
    } else if (lbl_8036E548.loadStep == 9) {
        actor->banks.b[5] = lbl_8036E548.bankSets[actor->modelIndex][4];
        ARAMTransfer(&lbl_803CB790[actor->kind * 0x13 + 0x10], actor->banks.b[5], 0, 0);
        lbl_8036E548.loadStep = 10;
    } else if (lbl_8036E548.loadStep == 10) {
        if ((s32)lbl_803C6CF8.transferDone == 1) {
            ANIMGet(actor->banks.b[5]);
            lbl_8036E548.loadStep = 0;
            return 1;
        }
    }
    return 0;
}

// .text:0x80016F7C size:0x11C
s32 fn_80016F7C(void) {
    CharActor* src;
    CharActor* dst;

    if (lbl_8036E548._2D8E == 0) {
        lbl_8036E548._2D8E = 1;
        lbl_8036E548.loadStep = 0;
        lbl_8036E548.loadActor = 0;
    }
    do {
        if (fn_80016B60(&lbl_8036E548.actors[lbl_8036E548.loadActor]) == 0) {
            goto fail;
        }
        if (g_d_GameSettings.GameModeSelected == 6) {
            src = &lbl_8036E548.actors[lbl_8036E548.loadActor];
            dst = &lbl_8036E548.actors[lbl_8036E548.loadActor + 4];
            dst->banks.b[0] = src->banks.b[0];
            dst->banks.b[1] = src->banks.b[1];
            dst->banks.b[2] = src->banks.b[2];
            dst->banks.b[3] = src->banks.b[3];
            dst->banks.b[4] = src->banks.b[4];
            dst->banks.b[5] = src->banks.b[5];
            dst->banks.b[6] = src->banks.b[6];
        }
        lbl_8036E548.loadActor++;
    } while (lbl_8036E548.loadActor < 4);
    return 1;
fail:
    return 0;
}

// .text:0x80017098 size:0x2A8
// NONMATCHING 87%: roster-entry field addresses are hoisted differently
#if NONMATCHING
s32 fn_80017098(s32 team, s32 roster, s32 arg2, s32 index, s32 arg4, s32 kind) {
    CharLoadTask* task;
    RosterEntry* entry;
    CharActor* actor;
    s32 same;
    s32 slot;
    s32 i;
    s32 j;

    if (kind >= 0) {
        task = fn_800B0A5C_insertQueue(fn_800177B4, 0);
        slot = index;
        goto setup;
    }
    entry = &inMemRoster[team][roster];
    for (i = 0; i < 13; i++) {
        actor = &lbl_8036E548.actors[i];
        same = 0;
        if (actor->kind == entry->charId && actor->_25A == entry->_26 && actor->_25B == entry->_27 && actor->roster == (s8)roster) {
            same = 1;
        }
        if (actor->team == team && same && actor->_258 == arg2 && actor->_259 == arg4) {
            lbl_8036E548.state = 0;
            lbl_8036E548._2D6A[i] = index;
            lbl_8036E548._2D79 = i;
            actor->index = index;
            for (j = 0; j < 13; j++) {
                if (lbl_8036E548.active[j] == actor) {
                    lbl_8036E548.active[j] = NULL;
                    break;
                }
            }
            lbl_8036E548.active[index] = actor;
            return 1;
        }
    }
    task = fn_800B0A5C_insertQueue(fn_800177B4, 0);
    if (index >= 9) {
        slot = 9;
        if (lbl_8036E548._2D6A[9] >= 0) {
            slot = 10;
            if (lbl_8036E548._2D6A[10] >= 0) {
                slot = 11;
                if (lbl_8036E548._2D6A[11] >= 0) {
                    slot = 12;
                    if (lbl_8036E548._2D6A[12] >= 0) {
                        slot = 13;
                    }
                }
            }
        }
    } else {
        for (slot = 0; slot < 13; slot++) {
            if (lbl_8036E548._2D6A[slot] < 0) {
                break;
            }
        }
    }
setup:
    task->state = 0;
    task->actor = slot;
    task->team = team;
    task->roster = roster;
    task->_1B = arg2;
    task->index = index;
    task->_1D = arg4;
    if (kind < 0) {
        task->kind = inMemRoster[team][roster].charId;
    } else {
        task->kind = kind;
    }
    lbl_8036E548._2D6A[slot] = index;
    lbl_8036E548.state = 1;
    lbl_8036E548._2D79 = slot;
    return 0;
}
#endif

// .text:0x80017340 size:0x24C
// NONMATCHING 78%: loop induction variables (original indexes active[i + 9] per pass)
#if NONMATCHING
s32 fn_80017340(s32 actorIdx) {
    CharActor* actor = &lbl_8036E548.actors[actorIdx];
    s32 used[4];
    CharActor* other;
    s32 i;
    s32 j;
    s32 k;
    s32 file;

    if (lbl_8036E548.loadStep == 0) {
        used[0] = 0;
        used[1] = 0;
        used[2] = 0;
        used[3] = 0;
        for (i = 0; i < 4; i++) {
            j = i + 9;
            for (k = 0; k < 4; k++) {
                other = lbl_8036E548.active[j];
                if (other != NULL) {
                    if (actor->kind == lbl_8036E548.bankOwner[k]) {
                        actor->banks.b[1] = lbl_8036E548.animBufs[k + 1];
                        return 1;
                    }
                    if (other->kind == lbl_8036E548.bankOwner[k]) {
                        used[k] = 1;
                        break;
                    }
                }
            }
        }
        if (used[0] == 0) {
            lbl_8036E548.bankOwner[0] = -1;
        }
        if (used[1] == 0) {
            lbl_8036E548.bankOwner[1] = -1;
        }
        if (used[2] == 0) {
            lbl_8036E548.bankOwner[2] = -1;
        }
        if (used[3] == 0) {
            lbl_8036E548.bankOwner[3] = -1;
        }
        k = 0;
        if (lbl_8036E548.bankOwner[0] >= 0) {
            k = 1;
            if (lbl_8036E548.bankOwner[1] >= 0) {
                k = 2;
                if (lbl_8036E548.bankOwner[2] >= 0) {
                    k = 3;
                    if (lbl_8036E548.bankOwner[3] >= 0) {
                        k = 4;
                    }
                }
            }
        }
        lbl_8036E548.bankOwner[k] = actor->kind;
        actor->banks.b[1] = lbl_8036E548.animBufs[k + 1];
        if (g_d_GameSettings.GameModeSelected == 2) {
            file = actor->kind * 0x13 + 0xB;
        } else {
            file = actor->kind * 0x13 + 3;
        }
        ARAMTransfer(&lbl_803CB790[file], actor->banks.b[1], 0, 0);
        lbl_8036E548.loadStep = 1;
    } else if ((s32)lbl_803C6CF8.transferDone == 1) {
        ANIMGet(actor->banks.b[1]);
        return 1;
    }
    return 0;
}
#endif

// .text:0x8001758C size:0x228
// NONMATCHING 99%: actor->kind reload scheduled later, r9/r11 swap
#if NONMATCHING
s32 fn_8001758C(u8* state, s32 actorIdx, u8 kind, u8 team, u8 roster, s8 arg5, u8 index, u8 arg7) {
    CharActor* actor = &lbl_8036E548.actors[actorIdx];
    s32 file;

    switch (*state) {
    case 0:
        if ((s32)lbl_803C6CF8.transferDone != 1) {
            break;
        }
        actor->_25C = 1;
        actor->team = team;
        actor->roster = roster;
        actor->index = index;
        actor->kind = kind;
        actor->_258 = arg5;
        actor->_259 = arg7;
        actor->_25A = inMemRoster[team][roster]._26;
        file = actor->kind * 0x13;
        actor->_25B = inMemRoster[team][roster]._27;
        actor->_278 = (index == 9);
        if (arg7 == 0) {
            file += 1;
        }
        if (actor->_278 != 0 && arg7 == 1 && lbl_8036E548.preload[2].id == kind) {
            memcpy(actor->files, lbl_8036E548.preload[2].buffer, lbl_8036E548.preload[2].size);
            goto load;
        }
        if (index >= 10 && index <= 12 && arg7 == 0 && lbl_8036E548.preload[0].id == kind) {
            memcpy(actor->files, lbl_8036E548.preload[0].buffer, lbl_8036E548.preload[0].size);
            goto load;
        }
        if (arg7 == 0 || fn_8002204C(actor->kind, actor->files) == 0) {
            ARAMTransfer(&lbl_803CB790[file], actor->files, 0, 0);
        }
        *state = 1;
        break;
    case 1:
        if (lbl_803716B8._1E8 == 0 && (s32)lbl_803C6CF8.transferDone == 1) {
        load:
            fn_80017814(actor, actor->modelIndex, index, fn_8001FDD4);
            return 1;
        }
        break;
    }
    return 0;
}
#endif

// .text:0x800177B4 size:0x60
// NONMATCHING 96%: argument load order (0x1A loaded first in original)
#if NONMATCHING
void fn_800177B4(void) {
    CharLoadTask* task = lbl_803CC1B8;

    if (fn_8001758C(&task->state, task->actor, task->kind, task->team, task->roster, task->_1B, task->index, task->_1D) != 0) {
        lbl_8036E548.state = 2;
        fn_800B0A14_removeQueue(&lbl_8036E548);
    }
}
#endif

// .text:0x80017814 size:0x514
// NONMATCHING 95%: register allocation (joint temps, relocation base)
#if NONMATCHING
void fn_80017814(CharActor* actor, s32 modelIndex, s32 index, void (*callback)(CharSlot*)) {
    CharSlot* slot = &lbl_8036E548.slots->slots[modelIndex];
    void** files = actor->files;
    void* tex;
    void* layout;
    void* geo;
    void* skn;
    void* bank;
    s32 count;
    s32 i;
    s32 j;

    // TODO type: the file header holds offsets that are relocated in place.
    if (files[0] != NULL) {
        actor->files[0] = (u8*)files + (u32)files[0];
        if (actor->files[1] != NULL) {
            actor->files[1] = (u8*)files + (u32)files[1];
            if (actor->files[2] != NULL) {
                actor->files[2] = (u8*)files + (u32)files[2];
                if (actor->files[3] != NULL) {
                    actor->files[3] = (u8*)files + (u32)files[3];
                    if (actor->files[4] != NULL) {
                        actor->files[4] = (u8*)files + (u32)files[4];
                    }
                }
            }
        }
    }
    tex = actor->files[0];
    convertTextureHeader(tex);
    if (actor->files[1] != NULL) {
        layout = actor->files[1];
        geo = actor->files[2];
        skn = actor->files[3];
        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geo, skn);
        haveActLayoutPointToGeoHeader(layout, geo);
        fn_800BD190(geo, tex);
    } else {
        return;
    }
    if (index < 9) {
        bank = actor->banks.b[2];
    } else {
        bank = actor->banks.b[1];
    }
    fn_8002399C(slot, actor->modelIndex, (u16)modelIndex, layout, bank, skn);
    if (actor->files[4] != NULL) {
        fn_80025DDC(actor->files[4]);
        fn_80025C58(actor->files[4], (ShapeModel**)&slot->model);
    }
    count = slot->model->jointCount;
    memset(actor->jointIdx, 0xFF, sizeof(actor->jointIdx));
    for (i = 0; i < count; i++) {
        if (slot->model->joints[i]->id != 0xFFFF) {
            actor->jointIdx[slot->model->joints[i]->id] = i;
        }
    }
    fn_800B2B74(slot->model, actor->jointIdx[19]);
    fn_800B2B74(slot->model, actor->jointIdx[25]);
    fn_800B2B74(slot->model, actor->jointIdx[36]);
    actor->model = slot->model;
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2B54(actor->model, j, 0xD);
    }
    fn_800BD548(slot, 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
    CTRLSetTranslation(&slot->ctrl, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&slot->ctrl, 0.0f, 0.0f, 0.0f);
    slot->_54 = 0.5f;
    slot->_5A = 1;
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
        slot->model->joints[(u16)j]->_136 = 1;
    }
    j = actor->jointIdx[2];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
        slot->model->joints[(u16)j]->_136 = 1;
    }
    j = actor->jointIdx[1];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
        slot->model->joints[(u16)j]->_136 = 1;
    }
    j = actor->jointIdx[36];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
    }
    j = actor->jointIdx[46];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->model, j, 0, 0);
        slot->model->joints[(u16)j]->_136 = 1;
    }
    fn_800B2C08(slot->model, actor->jointIdx[4]);
    fn_8001FC4C(actor);
    slot->callback = callback;
    actor->_060 = -1;
    actor->anim[0] = -1;
    actor->anim[1] = -1;
    actor->anim[2] = -1;
    actor->_068 = -1;
    actor->_06A[0] = -1;
    actor->_06A[1] = -1;
    actor->_06A[2] = -1;
    actor->mode[0] = 0;
    actor->mode[1] = 0;
    actor->_25F[0] = 0;
    actor->_25F[1] = 0;
    actor->_25F[2] = 0;
    actor->_262[0] = 0;
    actor->_262[1] = 0;
    actor->_262[2] = 0;
    actor->_265[0] = 0;
    actor->_265[1] = 0;
    actor->_265[2] = 0;
    actor->_268 = 0;
    actor->_269[0] = 0;
    actor->_269[1] = 0;
    actor->_269[2] = 0;
    actor->_26C[0] = 0;
    actor->_26C[1] = 0;
    actor->_26C[2] = 0;
    actor->_270[0] = 0;
    actor->_270[1] = 0;
    actor->_270[2] = 0;
    actor->_273 = 0;
    actor->_277 = 0xFF;
    switch (actor->kind) {
    case 2:
        fn_800638B4(actor, slot);
        break;
    case 33:
    case 34:
    case 35:
    case 36:
        fn_80063010(actor, slot);
        break;
    case 19:
        fn_8004B7B4(actor, slot);
        break;
    case 12:
    case 21:
    case 22:
    case 23:
    case 42:
        slot->model->_99 = 1;
        break;
    case 24:
    case 25:
    case 26:
        slot->model->_99 = 1;
        break;
    case 20:
    case 43:
        fn_800637BC(actor, slot);
        break;
    case 38:
        slot->model->_99 = 1;
        fn_8004BD6C(actor, slot);
        break;
    case 41:
        fn_800637D4(actor, slot);
    case 18:
    case 40:
        fn_8004BD6C(actor, slot);
        break;
    case 14:
    case 37:
        fn_80052634(actor, slot);
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        fn_80062ED4(actor, slot);
        break;
    }
}
#endif

// .text:0x80017D28 size:0x94
void fn_80017D28(CharActor* src) {
    s32 modelIndex = src->modelIndex + 4;
    CharActor* dst = &lbl_8036E548.actors[modelIndex];

    dst->kind = src->kind;
    dst->index = src->index;
    dst->modelIndex = modelIndex;
    dst->_25C = 1;
    dst->mode[0] = 0;
    dst->parts = src->parts;
    dst->_25A = src->_25A;
    dst->_25B = src->_25B;
    dst->files = src->_0C;
    fn_80017814(dst, modelIndex, 0, fn_8001FDD4);
}

// .text:0x80017DBC size:0x268
// NONMATCHING 97%: argument load order around fn_800B2B74
#if NONMATCHING
void fn_80017DBC(CharActor* actor, s32 modelIndex) {
    CharSlot* slot = &lbl_8036E548.slots->slots[modelIndex];

    initModelJoints(actor, slot);
    switch (actor->kind) {
    case 2:
        fn_800638B4(actor, slot);
        break;
    case 33:
    case 34:
    case 35:
    case 36:
        fn_80063010(actor, slot);
        break;
    case 19:
        fn_8004B7B4(actor, slot);
        break;
    case 20:
    case 43:
        fn_800637BC(actor, slot);
        break;
    case 38:
        slot->model->_99 = 1;
        fn_8004BD6C(actor, slot);
        break;
    case 41:
        fn_800637D4(actor, slot);
    case 18:
    case 40:
        fn_8004BD6C(actor, slot);
        break;
    case 14:
    case 37:
        fn_80052634(actor, slot);
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        fn_80062ED4(actor, slot);
        break;
    }
}
#endif

// .text:0x80018024 size:0x24C
// NONMATCHING 76%: original indexes the ARAM table with lwzx instead of strength-reduced pointers
#if NONMATCHING
void fn_80018024(void) {
    u32 max0 = 0;
    u32 max1 = 0;
    u32 size;
    u32 size0;
    u32 size1;
    s32 k;
    s32 i;
    u8* p;

    for (k = 0; k < 54 * 0x13; k += 0x13) {
        size = lbl_803CB790[k].size & 0x0FFFFFFF;
        if (max0 < size) {
            max0 = size;
        }
        size = lbl_803CB790[k + 1].size & 0x0FFFFFFF;
        if (max1 < size) {
            max1 = size;
        }
    }
    size0 = (max0 + 0x1F) & ~0x1F;
    lbl_8036E548._2D64 = size0;
    size1 = (max1 + 0x1F) & ~0x1F;
    if (g_d_GameSettings.GameModeSelected == 6) {
        lbl_8036E548.fileBuf = _OSAllocFromHeap(0x20, (size0 + size1) * 4);
    } else {
        lbl_8036E548.fileBuf = _OSAllocFromHeap(0x20, size0 * 4);
    }
    p = lbl_8036E548.fileBuf;
    if (g_d_GameSettings.GameModeSelected == 6) {
        for (i = 0; i < 4; i++) {
            lbl_8036E548.actors[i].files = (void**)p;
            p += size0;
            lbl_8036E548.actors[i].part = NULL;
            lbl_8036E548.actors[i].parts = NULL;
            lbl_8036E548.actors[i]._0C = (void**)p;
            p += size1;
            lbl_8036E548.actors[i + 4].part = NULL;
            lbl_8036E548.actors[i + 4].parts = NULL;
        }
    } else {
        for (i = 0; i < 4; i++) {
            lbl_8036E548.actors[i].files = (void**)p;
            p += size0;
            lbl_8036E548.actors[i].part = NULL;
            lbl_8036E548.actors[i].parts = NULL;
        }
    }
}
#endif

// .text:0x80018270 size:0x650
// NONMATCHING 87%: max-size loops unrolled/scheduled differently
#if NONMATCHING
void fn_80018270(s32 mode) {
    u32 max1 = 0;
    u32 max0 = 0;
    u32 size;
    u32 s0;
    u32 s1;
    u32 total;
    s32 i;
    s32 t;
    s32 k;
    u8* p;

    if (mode == 2) {
        p = _OSAllocFromHeap(0x20, 0x13E80);
        lbl_8036E548.fileBuf = p;
        lbl_8036E548.actors[0].files = (void**)p;
        for (i = 1; i < 9; i++) {
            lbl_8036E548.actors[i].files = _OSAllocFromHeap(0x20, 0x12C40);
        }
        for (k = 0; k < 54; k++) {
            size = lbl_803CB790[k * 0x13].size & 0x0FFFFFFF;
            if (max0 < size) {
                max0 = size;
            }
        }
        s0 = (max0 + 0x1F) & ~0x1F;
        total = s0 * 4 + 0x13E80;
        p = _OSAllocFromHeap(0x20, total);
        lbl_8036E548.actors[10].files = (void**)(p + s0);
        lbl_8036E548.actors[11].files = (void**)(p + s0 * 2);
        lbl_8036E548.actors[12].files = (void**)(p + s0 * 3);
        lbl_8036E548._2D64 = total;
        lbl_8036E548.actors[9].files = (void**)p;
        lbl_8036E548.preload[0].buffer = p + s0 * 4;
        lbl_8036E548.preload[0].size = 0x13E80;
        lbl_8036E548.preload[0].id = -1;
        lbl_8036E548.preload[0].state = 0;
    } else {
        if (mode == 0) {
            for (t = 0; t < 2; t++) {
                for (i = 0; i < 9; i++) {
                    size = lbl_803CB790[inMemRoster[t][i].charId * 0x13].size & 0x0FFFFFFF;
                    if (max0 < size) {
                        max0 = size;
                    }
                }
            }
            for (t = 0; t < 2; t++) {
                for (i = 0; i < 9; i++) {
                    size = lbl_803CB790[inMemRoster[t][i].charId * 0x13 + 1].size & 0x0FFFFFFF;
                    if (max1 < size) {
                        max1 = size;
                    }
                }
            }
        } else {
            for (k = 0; k < 54; k++) {
                size = lbl_803CB790[k * 0x13].size & 0x0FFFFFFF;
                if (max0 < size) {
                    max0 = size;
                }
            }
            for (k = 0; k < 54; k++) {
                size = lbl_803CB790[k * 0x13 + 1].size & 0x0FFFFFFF;
                if (max1 < size) {
                    max1 = size;
                }
            }
        }
        s1 = (max1 + 0x1F) & ~0x1F;
        s0 = (max0 + 0x1F) & ~0x1F;
        total = s1 * 9 + s0 * 4 + s0 + s1;
        p = _OSAllocFromHeap(0x20, total);
        lbl_8036E548.fileBuf = p;
        lbl_8036E548._2D64 = total;
        for (i = 0; i < 9; i++) {
            lbl_8036E548.actors[i].files = (void**)p;
            p += s1;
        }
        lbl_8036E548.actors[9].files = (void**)p;
        p += s0;
        lbl_8036E548.actors[10].files = (void**)p;
        p += s0;
        lbl_8036E548.actors[11].files = (void**)p;
        p += s0;
        lbl_8036E548.actors[12].files = (void**)p;
        p += s0;
        lbl_8036E548.preload[2].buffer = p;
        lbl_8036E548.preload[2].size = s0;
        lbl_8036E548.preload[2].id = -1;
        lbl_8036E548.preload[2].state = 0;
        lbl_8036E548.preload[0].buffer = p + s0;
        lbl_8036E548.preload[0].size = s1;
        lbl_8036E548.preload[0].id = -1;
        lbl_8036E548.preload[0].state = 0;
    }
    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i].part = NULL;
        lbl_8036E548.actors[i].parts = NULL;
    }
}
#endif

// .text:0x800188C0 size:0xF8
void fn_800188C0(void) {
    CharLoadTask* task = lbl_803CC1B8;

    switch (task->state) {
    case 0:
        if (g_d_GameSettings.GameModeSelected == 6) {
            lbl_8036E548.stadiumFiles = ARAMTransfer(&lbl_800EE910[1], NULL, 0, 0);
        } else {
            lbl_8036E548.stadiumFiles = ARAMTransfer(&lbl_800EE910[0], NULL, 0, 0);
        }
        task->state++;
        break;
    case 1:
        if ((s32)lbl_803C6CF8.transferDone == 1) {
            task->state++;
        }
        break;
    case 2:
        lbl_8036E548._307B = 0;
        fn_800B0A14_removeQueue(&lbl_8036E548);
        break;
    }
}

// .text:0x800189B8 size:0x2C
void fn_800189B8(void) {
    fn_800ACFB0(lbl_8036E548._2C88);
}

// .text:0x800189E4 size:0x154
void fn_800189E4(void) {
    u32 max = 0;
    u32 size;
    s32 i;
    u8* buf;

    for (i = 0; i < 54; i++) {
        size = lbl_803CB790[i * 0x13 + 0xF].size & 0x0FFFFFFF;
        if (max < size) {
            max = size;
        }
    }
    size = (max + 0x1F) & ~0x1F;
    lbl_8036E548._2CA4 = size;
    buf = _OSAllocFromHeap(0x20, size * 4);
    lbl_8036E548._2C88 = buf;
    for (i = 0; i < 4; i++) {
        lbl_8036E548.bankSets[i][4] = buf;
        lbl_8036E548.actors[i].banks.b[5] = NULL;
        buf += size;
    }
}

// .text:0x80018B38 size:0x3C
void fn_80018B38(void) {
    fn_800ACFB0(lbl_8036E548._2C88);
    lbl_8036E548._2D68 = -1;
}

// .text:0x80018B74 size:0x278
// NONMATCHING 96%: size temporaries register allocation
#if NONMATCHING
void fn_80018B74(void) {
    u32 max0 = 0;
    u32 max1 = 0;
    u32 max2 = 0;
    u32 max3 = 0;
    u32 max4 = 0;
    u32 size;
    u32 s0;
    u32 s1;
    u32 s2;
    u32 s3;
    u32 s4;
    u32 total;
    s32 k;
    s32 m;
    u8* p;
    AramFile* f;

    f = lbl_803CB790;
    for (k = 0; k < 54; k++) {
        if (g_d_GameSettings.GameModeSelected == 7) {
            size = f[0xD].size & 0x0FFFFFFF;
            if (max0 < size) {
                max0 = size;
            }
        } else {
            size = f[4].size & 0x0FFFFFFF;
            if (max0 < size) {
                max0 = size;
            }
        }
        if (g_d_GameSettings.GameModeSelected == 6) {
            size = f[0xE].size & 0x0FFFFFFF;
            if (max1 < size) {
                max1 = size;
            }
        } else {
            size = f[0xC].size & 0x0FFFFFFF;
            if (max1 < size) {
                max1 = size;
            }
        }
        size = f[0x12].size & 0x0FFFFFFF;
        if (max2 < size) {
            max2 = size;
        }
        if (g_d_GameSettings.GameModeSelected == 7) {
            size = f[9].size & 0x0FFFFFFF;
            if (max3 < size) {
                max3 = size;
            }
        } else {
            size = f[2].size & 0x0FFFFFFF;
            if (max3 < size) {
                max3 = size;
            }
        }
        size = f[0x10].size & 0x0FFFFFFF;
        if (max4 < size) {
            max4 = size;
        }
        f += 0x13;
    }
    s2 = (max2 + 0x1F) & ~0x1F;
    s1 = (max1 + 0x1F) & ~0x1F;
    s4 = (max4 + 0x1F) & ~0x1F;
    s0 = (max0 + 0x1F) & ~0x1F;
    s3 = (max3 + 0x1F) & ~0x1F;
    lbl_8036E548.bankSize[2] = s0;
    total = s3 + (s0 + (s1 + s2 + s4)) * 4;
    lbl_8036E548.bankSize[1] = s1;
    lbl_8036E548.bankSize[3] = s2;
    lbl_8036E548.bankSize[0] = s3;
    lbl_8036E548._2CA4 = s4;
    lbl_8036E548._2D60 = total;
    p = _OSAllocFromHeap(0x20, total);
    lbl_8036E548._2C88 = p;
    for (m = 0; m < 4; m++) {
        lbl_8036E548.bankSets[m][0] = p;
        p += s0;
        lbl_8036E548.bankSets[m][1] = p;
        p += s1;
        lbl_8036E548.bankSets[m][2] = p;
        p += s2;
        if (m == 0) {
            lbl_8036E548.bankSets[m][3] = p;
            p += s3;
        } else {
            lbl_8036E548.bankSets[m][3] = lbl_8036E548.bankSets[0][3];
        }
        lbl_8036E548.bankSets[m][4] = p;
        p += s4;
        lbl_8036E548.actors[m].banks.b[0] = NULL;
        lbl_8036E548.actors[m].banks.b[3] = NULL;
        lbl_8036E548.actors[m].banks.b[4] = NULL;
        lbl_8036E548.actors[m].banks.b[1] = NULL;
        lbl_8036E548.actors[m].banks.b[2] = NULL;
        lbl_8036E548.actors[m].banks.b[5] = NULL;
    }
    lbl_8036E548._2D68 = -1;
}
#endif

// .text:0x80018DEC size:0x8EC
// NONMATCHING 91%: size-table loops unrolled/scheduled differently
#if NONMATCHING
void fn_80018DEC(s32 mode) {
    u32 m0 = 0;
    u32 m1 = 0;
    u32 m5 = 0;
    u32 m6 = 0;
    u32 m7 = 0;
    u32 m8 = 0;
    u32 s0;
    u32 s1;
    u32 s5;
    u32 s6;
    u32 s7;
    u32 s8;
    u32 total;
    u32 size;
    AramFile* f;
    s32 k;
    s32 t;
    s32 i;
    u8* p;

    if (mode == 2) {
        for (k = 0; k < 54; k++) {
            f = &lbl_803CB790[k * 0x13];
            size = f[0xA].size & 0x0FFFFFFF;
            if (m0 < size) {
                m0 = size;
            }
            size = f[0xB].size & 0x0FFFFFFF;
            if (m1 < size) {
                m1 = size;
            }
            size = f[0x12].size & 0x0FFFFFFF;
            if (m6 < size) {
                m6 = size;
            }
            size = f[4].size & 0x0FFFFFFF;
            if (m8 < size) {
                m8 = size;
            }
        }
        for (i = 1; i < 9; i++) {
            f = &lbl_803CB790[inMemRoster[0][i].charId * 0x13];
            size = f[4].size & 0x0FFFFFFF;
            if (m5 < size) {
                m5 = size;
            }
            size = f[6].size & 0x0FFFFFFF;
            if (m7 < size) {
                m7 = size;
            }
        }
    } else if (mode == 0) {
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                f = &lbl_803CB790[inMemRoster[t][i].charId * 0x13];
                size = f[2].size & 0x0FFFFFFF;
            if (m0 < size) {
                m0 = size;
            }
                size = f[3].size & 0x0FFFFFFF;
            if (m1 < size) {
                m1 = size;
            }
                size = f[4].size & 0x0FFFFFFF;
            if (m5 < size) {
                m5 = size;
            }
                size = f[5].size & 0x0FFFFFFF;
            if (m6 < size) {
                m6 = size;
            }
                size = f[6].size & 0x0FFFFFFF;
            if (m7 < size) {
                m7 = size;
            }
            }
        }
    } else {
        for (k = 0; k < 54; k++) {
            f = &lbl_803CB790[k * 0x13];
            size = f[2].size & 0x0FFFFFFF;
            if (m0 < size) {
                m0 = size;
            }
            size = f[3].size & 0x0FFFFFFF;
            if (m1 < size) {
                m1 = size;
            }
            size = f[4].size & 0x0FFFFFFF;
            if (m5 < size) {
                m5 = size;
            }
            size = f[5].size & 0x0FFFFFFF;
            if (m6 < size) {
                m6 = size;
            }
            size = f[6].size & 0x0FFFFFFF;
            if (m7 < size) {
                m7 = size;
            }
        }
    }
    s0 = (m0 + 0x1F) & ~0x1F;
    s1 = (m1 + 0x1F) & ~0x1F;
    s6 = (m6 + 0x1F) & ~0x1F;
    s7 = (m7 + 0x1F) & ~0x1F;
    s5 = (m5 + 0x1F) & ~0x1F;
    lbl_8036E548.bankSize[0] = s0;
    s8 = (m8 + 0x1F) & ~0x1F;
    lbl_8036E548.bankSize[1] = s1;
    lbl_8036E548.bankSize[3] = s6;
    lbl_8036E548.bankSize[4] = s7;
    lbl_8036E548.bankSize[2] = s5;
    if (mode == 2) {
        total = s0 + (s1 * 4 + s5 * 8 + s8 + s6 + s7) + s0;
        lbl_8036E548._2C88 = _OSAllocFromHeap(0x20, total);
    } else {
        total = s0 + (s1 * 4 + s5 * 9 + s6 + s7) + s0;
        lbl_8036E548._2C88 = _OSAllocFromHeap(0x20, total);
    }
    lbl_8036E548._2D60 = total;
    i = 15;
    lbl_8036E548.animBufs[15] = lbl_8036E548._2C88;
    p = (u8*)lbl_8036E548._2C88 + s7;
    while (i > 14) {
        i--;
        lbl_8036E548.animBufs[i] = p;
        p += s6;
    }
    if (mode == 2) {
        while (i > 6) {
            i--;
            lbl_8036E548.animBufs[i] = p;
            p += s5;
        }
        i--;
        lbl_8036E548.animBufs[i] = p;
        p += s8;
    } else {
        while (i > 5) {
            i--;
            lbl_8036E548.animBufs[i] = p;
            p += s5;
        }
    }
    while (i > 1) {
        i--;
        lbl_8036E548.animBufs[i] = p;
        p += s1;
    }
    while (i > 0) {
        i--;
        lbl_8036E548.animBufs[i] = p;
        p += s0;
    }
    lbl_8036E548.preload[1].buffer = p;
    lbl_8036E548.preload[1].size = s0;
    lbl_8036E548.preload[1].id = -1;
    lbl_8036E548.preload[1].state = 0;
    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i].banks.b[0] = NULL;
        lbl_8036E548.actors[i].banks.b[3] = NULL;
        lbl_8036E548.actors[i].banks.b[4] = NULL;
        lbl_8036E548.actors[i].banks.b[1] = NULL;
        lbl_8036E548.actors[i].banks.b[2] = NULL;
        lbl_8036E548.actors[i].banks.b[5] = NULL;
    }
}
#endif

// .text:0x800196D8 size:0x388
// NONMATCHING 99%: relocation loop counter register
#if NONMATCHING
void fn_800196D8(void) {
    CharLoadTask* task = lbl_803CC1B8;
    CharLoadTask* child;
    Vec dir2;
    Vec dir;
    f32 mag;
    u8* base;
    void** raw;
    s32 i;

    switch (task->state) {
    case 0:
        child = fn_800B0A5C_insertQueue(fn_800188C0, 0);
        child->state = 0;
        child->kind = 0;
        child->_17[0] = 0xFF;
        lbl_8036E548._307B = 1;
        task->state++;
        break;
    case 1:
        if (lbl_8036E548._307B == 0) {
            task->state++;
        }
        break;
    case 2:
        dir.x = -lbl_80367318[0].x;
        dir.y = -lbl_80367318[0].y;
        dir.z = -lbl_80367318[0].z;
        mag = dolsqrtf2(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
        dir.x /= mag;
        lbl_8036E548._3087 = 1;
        dir.y /= mag;
        dir.z /= mag;
        fn_8003A540(0);
        lbl_8036E548._3086 = 1;
        DrawShadows(1);
        dir2 = dir;
        fn_800BEBCC(0, &dir2);
        fn_800BF048(fn_8001AAF0);
        fn_800BF058(fn_8001AB10);
        // TODO type: the stadium file header holds offsets, relocated in place.
        base = (u8*)lbl_8036E548.stadiumFiles;
        raw = (void**)base;
        for (i = 0; i < 80; i++) {
            ((void**)lbl_8036E548.stadiumFiles)[i] = base + (u32)raw[i];
        }
        lbl_8036E548._307C = 0;
        lbl_8036E548._307D = 0;
        lbl_8036E548._3082 = 0;
        fn_8001F8A4();
        task->state++;
        break;
    default:
        challengeMapMaybe();
        lbl_8036E548._2D7D[0] = 1;
        lbl_8036E548._307C = 1;
        fn_800B0A14_removeQueue(&lbl_8036E548);
        break;
    }
}
#endif

// .text:0x80019A60 size:0x1A0
// NONMATCHING 97%: light-table base register and colour temp stack slots
#if NONMATCHING
void fn_80019A60(void) {
    LightPos* lights = lbl_80367318;
    CharQueueTask* task;
    s32 i;
    StadiumLights* st;
    LightPos* lp;
    u32 c;
    GXColor color;

    task = fn_800B0A5C_insertQueue(fn_800196D8, 0);
    task->_14 = 0;
    task->parent->_10 = 0;
    for (i = 0; i < 4; i++) {
        fn_80023B90(&lbl_800F7478[g_d_GameSettings._54].light[i], &lbl_80367318[i]);
    }
    fn_800BD2DC();
    st = &lbl_800F7478[g_d_GameSettings._54];
    if (st->ambient.a != 0) {
        color = st->ambient;
        fn_800BD2CC(1, color);
    }
    lp = lights;
    for (i = 0; i < 4; i++) {
        LITAlloc(&lbl_8036E548.lights[i]);
        LITInitAttn(lbl_8036E548.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(lbl_8036E548.lights[i], lp->x, lp->y, lp->z);
        c = lp->color;
        LITInitColor(lbl_8036E548.lights[i], &c);
        lp++;
    }
    if (lbl_8036E548.slots6C != NULL) {
        for (i = 0; i < lbl_8036E548.slots6C->count; i++) {
            fn_800BD548(&lbl_8036E548.slots6C->slots[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        }
    }
}
#endif

// .text:0x80019C00 size:0x65C
void fn_80019C00(void) {
    return;
}

// .text:0x8001A25C size:0x1A0
// NONMATCHING 99%: light-table base register and colour temp stack slots
#if NONMATCHING
void fn_8001A25C(void) {
    LightPos* lights = lbl_80367318;
    CharQueueTask* task;
    s32 i;
    StadiumLights* st;
    LightPos* lp;
    u32 c;
    GXColor color;

    task = fn_800B0A5C_insertQueue(fn_80019C00, 0);
    task->_14 = 0;
    task->parent->_10 = 0;
    for (i = 0; i < 4; i++) {
        fn_80023B90(&lbl_800F7478[g_d_GameSettings._54].light[i], &lbl_80367318[i]);
    }
    fn_800BD2DC();
    st = &lbl_800F7478[g_d_GameSettings._54];
    if (st->ambient.a != 0) {
        color = st->ambient;
        fn_800BD2CC(1, color);
    }
    lp = lights;
    for (i = 0; i < 4; i++) {
        LITAlloc(&lbl_8036E548.lights[i]);
        LITInitAttn(lbl_8036E548.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(lbl_8036E548.lights[i], lp->x, lp->y, lp->z);
        c = lp->color;
        LITInitColor(lbl_8036E548.lights[i], &c);
        lp++;
    }
    if (lbl_8036E548.slots6C != NULL) {
        for (i = 0; i < lbl_8036E548.slots6C->count; i++) {
            fn_800BD548(&lbl_8036E548.slots6C->slots[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        }
    }
}
#endif

// .text:0x8001A3FC size:0x2B4
// NONMATCHING 62%: unrolled init loops and the 13-actor reset loop are laid out differently
#if NONMATCHING
void fn_8001A3FC(s32 arg) {
    s32 count;
    s32 i;
    s32 k;
    s32 idx;
    u32 max;
    u32 size;
    void* p;

    fn_80018270(arg);
    count = 1;
    lbl_803CBC34[0] = 0;
    lbl_803CBC34[1] = 0;
    lbl_803CBC34[2] = 0;
    lbl_803CBC34[3] = 0;
    lbl_803CBC34[4] = count;
    for (i = count; i < 13; i++) {
        lbl_80118220[i]._61 = -2;
    }
    if (count != 0) {
        max = 0;
        for (k = 0; k < 54; k++) {
            idx = lbl_800EEB18[k];
            if (idx >= 0) {
                size = lbl_803CB794[idx].size & 0x0FFFFFFF;
                if (max < size) {
                    max = size;
                }
            }
        }
        p = _OSAllocFromHeap(0x20, (max + 0x1F) & ~0x1F);
        lbl_80118220[0].files = p;
        lbl_803CBC30 = p;
        lbl_80118220[0]._61 = -1;
        lbl_80118220[0].slot = 0xFF;
    }
    fn_800145F8(arg);
    lbl_8036E548.partSlots = fn_80023AA4();
    fn_80018DEC(arg);
    fn_80023B04(0xD);
    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i].modelIndex = i;
        lbl_8036E548.active[i] = NULL;
        lbl_8036E548._2D6A[i] = -1;
        lbl_8036E548.actors[i].roster = -1;
    }
    for (i = 0; i < 9; i++) {
        lbl_8036E548._2D7F[i] = -1;
    }
    lbl_8036E548.bankOwner[0] = -1;
    lbl_8036E548.bankOwner[1] = -1;
    lbl_8036E548.bankOwner[2] = -1;
    lbl_8036E548.bankOwner[3] = -1;
}
#endif

// .text:0x8001A6B0 size:0x3F4
void challengeMapRelated(void) {
    return;
}

// .text:0x8001AAA4 size:0x4C
void fn_8001AAA4(void) {
    CharQueueTask* task = fn_800B0A5C_insertQueue(challengeMapRelated, 0);
    task->_14 = 0;
    task->parent->_10 = 0;
    lbl_8036E548._3082 = 0;
    lbl_803CBBF0 = 0;
}

// .text:0x8001AAF0 size:0x20
void fn_8001AAF0(void) {
    fn_8003AC90();
}

// .text:0x8001AB10 size:0x488
void fn_8001AB10(CharSlot* slot, s32 a, s32 b) {
    return;
}

// .text:0x8001AF98 size:0x268
void fn_8001AF98(void) {
    BOOL homeRun = g_d_GameSettings.GameModeSelected == 6;
    u32 sx;
    u32 sy;
    u32 sw;
    u32 sh;
    Vec dir;
    Vec dir2;
    f32 proj[7];
    f32 viewport[6];
    ShadowView view;
    CameraView* cam;

    if (lbl_8036E548._3087 != 0 && fn_8003A538() == 0) {
        DrawShadows(lbl_8036E548._3086);
    } else {
        DrawShadows(0);
        return;
    }
    GXGetProjectionv(proj);
    GXGetViewportv(viewport);
    GXGetScissor(&sx, &sy, &sw, &sh);
    fn_800BEC00(homeRun);
    if (homeRun) {
        cam = fn_80052734(fn_8005268C());
        PSVECSubtract(&cam->eye, &cam->target, &dir);
        dir.y = 2.0f * -dir.y;
        if (PSVECMag(&dir)) {
            PSVECNormalize(&dir, &dir);
            dir2 = dir;
            fn_800BEBCC(0, &dir2);
        }
    } else {
        fn_800BD1E8(0);
    }
    if (GetDrawShadows()) {
        view.eye = fn_80052734(0)->eye;
        view.target = fn_80052734(0)->target;
        view.up = fn_80052734(0)->up;
        PSMTXCopy(fn_80052734(0)->view, view.view);
        fn_800BE09C(lbl_8036E548.slots, &view);
        fn_800BF058(fn_8001AB10);
        fn_800BDFE0(lbl_8036E548.slots);
        if (lbl_8036E548.callback != NULL) {
            lbl_8036E548.callback();
        }
        if (homeRun) {
            fn_8003A4C8();
        } else {
            fn_800BDEA0();
        }
    }
    if (lbl_803CBBF4 != NULL) {
        lbl_803CBBF4();
        lbl_803CBBF4 = NULL;
    }
    GXSetScissor(sx, sy, sw, sh);
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXInvalidateTexAll();
}

// fn_8001B200, size:0x14
void fn_8001B200(void) {
    lbl_8036E548.callback = NULL;
}

// fn_8001B214, size:0x10
void fn_8001B214(void (*callback)(void)) {
    lbl_8036E548.callback = callback;
}

// .text:0x8001B224 size:0xAC
void fn_8001B224(void) {
    s32 i;
    CharActor* actor;

    memcpy(lbl_8036E548.actors, lbl_8036C4FC, sizeof(lbl_8036E548.actors));
    for (i = 0; i < 13; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL && (actor->mode[0] != 0 || i <= 8)) {
            fn_8001BE50(i, actor->anim[0], actor->_25F[0], actor->_262[0], actor->_06A[0] + 1, actor->_265[0], 0);
        }
    }
}

// .text:0x8001B2D0 size:0x38
void fn_8001B2D0(void) {
    memcpy(lbl_8036C4FC, lbl_8036E548.actors, sizeof(lbl_8036E548.actors));
}

// .text:0x8001B308 size:0x54
void fn_8001B308(s32 index, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    CharSlot* slot;

    if (actor != NULL) {
        slot = &lbl_8036E548.slots->slots[actor->modelIndex];
        if (enable == 0) {
            slot->mirror = NULL;
        } else {
            slot->mirror = actor->mirror;
        }
    }
}

// .text:0x8001B35C size:0x17C
static inline f32 getJointHeight(CharActor* actor, s32 k) {
    f32 y;
    s32 j;
    CharSlot* slot;
    Vec v;

    if (actor != NULL) {
        j = getJoint(actor, k);
        if (j == 0xFFFF) {
            y = 0.0f;
        } else {
            slot = &lbl_8036E548.slots->slots[actor->modelIndex];
            fn_800B2C44(slot->model, j, &v);
            y = v.y;
            y += actor->pos.y;
        }
    }
    return y;
}

s32 fn_8001B35C(s32 index, s32 kind) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 k = 1;
    s32 steps = 0;
    f32 d;
    f32 t;

    if (actor == NULL) {
        return 0;
    }
    switch (kind) {
    case 1:
        k = 2;
        break;
    case 0:
        k = 3;
        break;
    case 2:
        k = 1;
        break;
    }
    d = getJointHeight(actor, k) - actor->pos.y;
    if (d < 0.0f && d >= -30.0f) {
        steps = 1;
        t = -0.5f;
        while (TRUE) {
            if (d > t) {
                break;
            }
            t -= 0.5f;
            steps++;
        }
    } else if (d >= 0.5f && d < 30.0f) {
        t = 0.5f;
        while (TRUE) {
            if (d < t) {
                break;
            }
            t += 0.5f;
            steps--;
        }
    }
    return steps;
}

// .text:0x8001B4D8 size:0x114
static inline void getRootOffset(CharActor* actor, u16 idx, s32 k, Vec* out) {
    u16 j0 = getJoint(actor, k);
    u16 j1 = getJoint(actor, 0);
    CharSlotList* list = lbl_8036E548.slots;
    Vec v;

    fn_800B2C44(list->slots[idx].model, list->slots[idx].model->_80, &v);
    list->slots[idx]._64 = j1;
    list->slots[idx]._66 = j0;
    *out = v;
}

void fn_8001B4D8(s32 index, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 modelIndex;
    Vec d;

    if (actor != NULL) {
        modelIndex = actor->modelIndex;
        if (enable != 0 && actor->_268 == 0) {
            getRootOffset(actor, modelIndex, 0, &d);
            actor->pos.x += d.x;
            actor->pos.y += d.y;
            actor->pos.z += d.z;
            actor->_268 = 1;
        }
    }
}

// .text:0x8001B5EC size:0x13C
static inline void setRootJoints(CharActor* actor, u16 idx, s32 k) {
    u16 j0 = getJoint(actor, k);
    u16 j1 = getJoint(actor, 0);
    CharSlotList* list = lbl_8036E548.slots;
    Vec v;

    fn_800B2C44(list->slots[idx].model, list->slots[idx].model->_80, &v);
    list->slots[idx]._64 = j1;
    list->slots[idx]._66 = j0;
}

void fn_8001B5EC(s32 index, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 modelIndex;

    if (actor != NULL) {
        modelIndex = actor->modelIndex;
        if (enable == 0) {
            setRootJoints(actor, modelIndex, 4);
        } else {
            setRootJoints(actor, modelIndex, 0);
        }
    }
}

// .text:0x8001B728 size:0xE4
s32 fn_8001B728(s32 index, s32 joint, Vec* out) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 j;
    CharSlot* slot;

    if (actor == NULL) {
        return 0;
    }
    j = getJoint(actor, joint);
    if (j == 0xFFFF) {
        return 0;
    }
    slot = &lbl_8036E548.slots->slots[actor->modelIndex];
    fn_800B2C10(slot->model, j, out);
    out->x += actor->pos.x;
    out->y += actor->pos.y;
    out->z += actor->pos.z;
    return 1;
}

// .text:0x8001B80C size:0x10C
BOOL getAnimRelatedCoordinates(s32 index, s32 joint, Vec* out) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 j;
    CharSlot* slot;
    Vec pos;

    if (actor == NULL) {
        return FALSE;
    }
    j = getJoint(actor, joint);
    if (j == 0xFFFF) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
        return FALSE;
    }
    slot = &lbl_8036E548.slots->slots[actor->modelIndex];
    fn_800B2C44(slot->model, j, &pos);
    out->x = pos.x;
    out->y = pos.y;
    out->z = pos.z;
    out->x += actor->pos.x;
    out->y += actor->pos.y;
    out->z += actor->pos.z;
    return TRUE;
}

// .text:0x8001B918 size:0x78
void QueueCharacterAnimation(s32 index, s32 anim, s32 a, s32 b, s32 c, s32 d, s32 e) {
    CharActor* actor = lbl_8036E548.active[index];

    actor->anim[2] = anim;
    actor->_06A[2] = c;
    actor->_25F[2] = a;
    actor->_262[2] = b;
    actor->_265[2] = d;
    actor->_26C[2] = 0;
    if (e == -1) {
        actor->_269[2] = 5;
    } else {
        actor->_269[2] = e;
    }
    if ((anim >= 0x3F && anim < 0x4B) || (anim >= 0x4B && anim < 0x69)) {
        lbl_8036E548.active[index]->_26C[2] = 1;
    }
}

// .text:0x8001B990 size:0xB4
void AnimateCharacter(s32 index, s32 anim, s32 a, u8 mode, s32 b, s32 c, s32 d, s32 e) {
    CharActor* actor = lbl_8036E548.active[index];

    if (actor == NULL) {
        return;
    }
    if (mode == 1 && actor->anim[0] == anim) {
        return;
    }
    if (mode == 3) {
        mode = 1;
    }
    actor->anim[1] = anim;
    actor->_06A[1] = c;
    actor->_25F[1] = a;
    actor->mode[1] = mode;
    actor->_262[1] = b;
    actor->_265[1] = d;
    actor->_26C[1] = 0;
    if (e == -1) {
        actor->_269[1] = 5;
    } else {
        actor->_269[1] = e;
    }
    actor->anim[2] = -1;
    if ((anim >= 0x3F && anim < 0x4B) || (anim >= 0x4B && anim < 0x69)) {
        lbl_8036E548.active[index]->_26C[1] = 1;
    }
}

// .text:0x8001BA44 size:0x40C
// Splits a global animation id into an actor anim bank and an index in it.
static inline BOOL splitAnimId(s32 anim, s32* bank, s32* idx) {
    if (anim < 0) {
        return FALSE;
    }
    if (anim < 0x2D) {
        *idx = anim;
        *bank = 2;
    } else if (anim < 0x3D) {
        *idx = anim - 0x2D;
        *bank = 1;
    } else if (anim < 0x3F) {
        *idx = anim - 0x3D;
        *bank = 4;
    } else if (anim < 0x4B) {
        *idx = anim - 0x3F;
        *bank = 3;
    } else if (anim < 0x69) {
        *idx = anim - 0x4B;
        *bank = 0;
    } else {
        *bank = 5;
        *idx = anim - 0x69;
    }
    return TRUE;
}

static inline void resetRootJoint(CharActor* actor, CharSlot* slot, s32 index) {
    if (actor->_26C[0] == 0) {
        fn_800B2B54(actor->model, getJoint(actor, 4), 0xD);
    } else {
        fn_800B2B54(actor->model, getJoint(actor, 4), 1);
        fn_800B2B54(slot->model, getJoint(lbl_8036E548.active[index], 4), 1);
        fn_800B2B4C(slot->model, 0.125f);
        slot->model->_8C = 0.0f;
    }
}

// NONMATCHING 85%: register allocation and joint-lookup scheduling
#if NONMATCHING
void fn_8001BA44(s32 index, s32 anim, u8 a, u8 b, s16 c, u8 d, u8 e) {
    CharActor* actor = lbl_8036E548.active[index];
    CharSlot* slot;
    CharAnimBank* bankData;
    s32 bank;
    s32 idx;
    f32 speed = 0.0f;

    if (actor == NULL) {
        return;
    }
    slot = &lbl_8036E548.slots->slots[actor->modelIndex];
    if (e != 0) {
        speed = 1.0f / e;
    }
    resetRootJoint(actor, slot, index);
    if (splitAnimId(anim, &bank, &idx)) {
        bankData = actor->banks.b[bank];
        if (bankData != NULL) {
            if (!(idx < bankData->count && idx >= 0)) {
                return;
            }
            slot->act = bankData;
            slot->animId = idx;
            slot->_5C = 0.0f;
            slot->_58 = 1;
            slot->_59 = bankData != NULL;
            slot->_5A = bankData != NULL;
            slot->_60 = speed;
        }
        if (actor->part != NULL) {
            fn_80025EEC(&actor->part->player, bank, idx);
        }
        if (actor->parts != NULL) {
            fn_80011CA8(actor, bank, idx);
        }
        if (a != 0) {
            slot->_5B = 3;
        } else {
            slot->_5B = 2;
        }
        slot->_5C = c * actor->_04C;
        slot->_59 = 1;
        fn_8001B5EC(index, b);
        fn_8001B308(index, d);
        actor->_268 = b;
    } else {
        slot->act = NULL;
        slot->animId = 0;
        slot->_5C = 0.0f;
        slot->_58 = 1;
        slot->_59 = 0;
        slot->_5A = 0;
        slot->_60 = 0.0f;
    }
}
#endif

// .text:0x8001BE50 size:0x3E4
// NONMATCHING 96%: register allocation and joint-lookup scheduling
#if NONMATCHING
void fn_8001BE50(s32 index, s32 anim, u8 a, u8 b, s16 c, u8 d, u8 e) {
    CharActor* actor = lbl_8036E548.active[index];
    CharSlot* slot;
    CharAnimBank* bankData;
    s32 bank;
    s32 idx;
    f32 speed = 0.0f;

    if (actor == NULL) {
        return;
    }
    slot = &lbl_8036E548.slots->slots[actor->modelIndex];
    if (e != 0) {
        speed = 1.0f / e;
    }
    resetRootJoint(actor, slot, index);
    // NOTE: bank/idx stay unset for a negative anim id, as in the original.
    splitAnimId(anim, &bank, &idx);
    bankData = actor->banks.b[bank];
    if (bankData != NULL) {
        if (!(idx < bankData->count && idx >= 0)) {
            return;
        }
        slot->act = bankData;
        slot->animId = idx;
        slot->_5C = 0.0f;
        slot->_58 = 1;
        slot->_59 = bankData != NULL;
        slot->_5A = bankData != NULL;
        slot->_60 = speed;
    }
    if (actor->part != NULL) {
        fn_80025EEC(&actor->part->player, bank, idx);
    }
    if (actor->parts != NULL && actor->parts->_CC != 0) {
        fn_80025EEC(&actor->parts->part[1].player, bank, idx);
        fn_80025EEC(&actor->parts->part[0].player, bank, idx);
    }
    if (a != 0) {
        slot->_5B = 3;
    } else {
        slot->_5B = 2;
    }
    slot->_5C = c * actor->_04C;
    slot->_59 = 1;
    fn_8001B5EC(index, b);
    fn_8001B308(index, d);
    actor->_268 = b;
}
#endif

// .text:0x8001C234 size:0x2F4
// NONMATCHING 98%: register allocation
#if NONMATCHING
void fn_8001C234(u32* doneMask) {
    s32 i;
    CharActor* actor;
    s32 j;
    s32 n;
    f32 frames;
    f32 t;

    *doneMask = 0;
    for (i = 0; i < 13; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL || actor->mode[0] == 0) {
            continue;
        }
        n = actor->_06A[0];
        if (n < 600 && lbl_80366158._28 == 0 && lbl_803CBC3C[0] == 0 && actor->_26F == 0) {
            actor->_06A[0] = n + 1;
        }
        frames = 1.0f;
        j = getJoint(lbl_8036E548.active[i], 4);
        if (j != 0xFFFF) {
            frames = fn_800B4A44(lbl_8036E548.slots->slots[actor->modelIndex].model, j);
        }
        actor->_068 = frames / actor->_04C;
        if (actor->_070 >= 0) {
            actor->_068 = actor->_070;
        }
        actor->_070 = -1;
        if (actor->mode[1] == 1 || (actor->mode[1] == 2 && actor->_068 == 0 && actor->_06A[0] > 1) || actor->anim[0] == -1) {
            *doneMask |= 1 << i;
            if (actor->anim[1] >= 0) {
                t = actor->_06A[1];
                if (g_d_GameSettings.minigamesEnabled != 0 && g_d_GameSettings._06 == 2) {
                    fn_8001BA44(i, actor->anim[1], actor->_25F[1], actor->_262[1], actor->_06A[1], actor->_265[1], actor->_269[1]);
                } else {
                    fn_8001BE50(i, actor->anim[1], actor->_25F[1], actor->_262[1], actor->_06A[1], actor->_265[1], actor->_269[1]);
                }
                actor->_060 = actor->anim[0];
                actor->anim[0] = actor->anim[1];
                actor->anim[1] = -1;
                actor->_25F[0] = actor->_25F[1];
                actor->_262[0] = actor->_262[1];
                actor->_265[0] = actor->_265[1];
                actor->_269[0] = actor->_269[1];
                actor->_26C[0] = actor->_26C[1];
                actor->_06A[0] = 0;
                if (actor->anim[2] >= 0) {
                    actor->anim[1] = actor->anim[2];
                    actor->_06A[1] = actor->_06A[2];
                    actor->_25F[1] = actor->_25F[2];
                    actor->_262[1] = actor->_262[2];
                    actor->mode[1] = 2;
                    actor->_265[1] = actor->_265[2];
                    actor->_269[1] = actor->_269[2];
                    actor->_26C[1] = actor->_26C[2];
                    actor->anim[2] = -1;
                    continue;
                }
            } else {
                t = 0.0f;
            }
            actor->mode[1] = 0;
        } else {
            t = fn_800B4C40(lbl_8036E548.slots->slots[actor->modelIndex].model);
        }
        if (lbl_803CBC3C[0] == 0) {
            fn_8004B208(actor, actor->anim[0], fn_8004AD54(g_d_GameSettings.StadiumID, actor->_275), t);
        }
    }
}
#endif

// .text:0x8001C528 size:0x60
void fn_8001C528(void) {
    s32 i;

    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i]._060 = -1;
        lbl_8036E548.actors[i].anim[0] = -1;
        lbl_8036E548.actors[i].anim[1] = -1;
        lbl_8036E548.actors[i].anim[2] = -1;
        lbl_8036E548.actors[i]._068 = 0;
        lbl_8036E548.actors[i]._06A[0] = 0;
        lbl_8036E548.actors[i].mode[1] = 1;
        lbl_8036E548.actors[i]._25F[0] = 0;
        lbl_8036E548.actors[i]._262[0] = 0;
        lbl_8036E548.actors[i]._268 = 0;
        lbl_8036E548.actors[i]._269[0] = 0;
        lbl_8036E548.actors[i]._269[1] = 0;
        lbl_8036E548.actors[i]._269[2] = 0;
        lbl_8036E548.actors[i]._26F = 0;
    }
}

// .text:0x8001C588 size:0xF4
s32 fn_8001C588(s32 id) {
    if (lbl_803CBC3C[3] == 0) {
        if ((s32)lbl_803C6CF8.transferDone != 1) {
            goto fail;
        }
        lbl_803CBC3C[3] = 1;
    }
    if (lbl_803CBC3C[3] == 1) {
        ARAMTransfer(&lbl_803CB790[id * 0x13 + 6], lbl_8036E548.animBufs[15], 0, 0);
        lbl_803CBC3C[3] = 2;
    } else if (lbl_803CBC3C[3] == 2 && (s32)lbl_803C6CF8.transferDone == 1) {
        ANIMGet(lbl_8036E548.animBufs[15]);
        if (lbl_8036E548.active[1]->banks.b[4] == NULL) {
            lbl_8036E548.active[1]->banks.b[4] = lbl_8036E548.animBufs[15];
        }
        return 1;
    }
fail:
    lbl_803CBC3C[0] = 0;
    return 0;
}

// .text:0x8001C67C size:0x2A4
// NONMATCHING 99%: joint offset/list registers swapped, mfcr scheduling
#if NONMATCHING
int fn_8001C67C_animation(int id, int index) {
    CharSlotList* list;
    CharModel* model;
    CharActor* actor;
    s32 i;
    s32 file;

    if (lbl_803CBC3C[2] == 0) {
        if ((s32)lbl_803C6CF8.transferDone != 1) {
            return 0;
        }
        list = lbl_8036E548.slots64;
        model = list->slots[4].model;
        if (model->joints[0]->track != NULL && model->joints[0]->track->_0C != NULL) {
            for (i = 0; i < model->jointCount; i++) {
                ACTSetBoneTrack(model->joints[i], NULL, model->_8C < 1.0f, 0.0f);
            }
            list->slots[4]._58 = 0;
            list->slots[4]._59 = 0;
            list->slots[4]._5A = 0;
            list->slots[4]._60 = 0.0f;
        }
        lbl_803CBC3C[2] = 1;
    }
    if (lbl_803CBC3C[2] == 1) {
        if (g_d_GameSettings.minigamesEnabled != 0) {
            if (g_d_GameSettings.GameModeSelected == 7) {
                file = id * 0x13 + 9;
            } else {
                file = id * 0x13 + 2;
            }
            ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.bankSets[0][3], 0, 0);
        } else {
            if (id == lbl_8036E548.preload[1].id) {
                memcpy(lbl_8036E548.animBufs[0], lbl_8036E548.preload[1].buffer, lbl_8036E548.preload[1].size);
                goto loaded;
            }
            if (g_d_GameSettings.GameModeSelected == 2) {
                file = id * 0x13 + 0xA;
            } else {
                file = id * 0x13 + 2;
            }
            ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.animBufs[0], 0, 0);
        }
        lbl_803CBC3C[2] = 2;
    } else if (lbl_803CBC3C[2] == 2 && (s32)lbl_803C6CF8.transferDone == 1) {
        if (g_d_GameSettings.minigamesEnabled != 0) {
            ANIMGet(lbl_8036E548.bankSets[0][3]);
            actor = lbl_8036E548.active[index];
            if (actor->banks.b[0] == NULL) {
                actor->banks.b[0] = lbl_8036E548.bankSets[0][3];
            }
        } else {
        loaded:
            ANIMGet(lbl_8036E548.animBufs[0]);
            actor = lbl_8036E548.active[index];
            if (actor->banks.b[0] == NULL) {
                actor->banks.b[0] = lbl_8036E548.animBufs[0];
            }
        }
        lbl_8036E548._2D68 = id;
        return 1;
    }
    lbl_803CBC3C[0] = 0;
    return 0;
}
#endif

// .text:0x8001C920 size:0x120
s32 fn_8001C920(s32 id) {
    s32 file;

    if (lbl_803CBC3C[1] == 0) {
        if ((s32)lbl_803C6CF8.transferDone != 1) {
            goto fail;
        }
        lbl_803CBC3C[1] = 1;
    }
    if (lbl_803CBC3C[1] == 1) {
        if (g_d_GameSettings.minigamesEnabled != 0 || g_d_GameSettings.GameModeSelected == 2) {
            file = id * 0x13 + 0x12;
        } else {
            file = id * 0x13 + 5;
        }
        ARAMTransfer(&lbl_803CB790[file], lbl_8036E548.animBufs[14], 0, 0);
        lbl_803CBC3C[1] = 2;
    } else if (lbl_803CBC3C[1] == 2 && (s32)lbl_803C6CF8.transferDone == 1) {
        ANIMGet(lbl_8036E548.animBufs[14]);
        if (lbl_8036E548.active[0]->banks.b[3] == NULL) {
            lbl_8036E548.active[0]->banks.b[3] = lbl_8036E548.animBufs[14];
        }
        return 1;
    }
fail:
    lbl_803CBC3C[0] = 0;
    return 0;
}

// .text:0x8001CA40 size:0xD0
static inline void loadLights(LightSrc* src, s32 count) {
    s32 i;
    Vec dir;
    Vec dir2;

    for (i = 0; i < count; i++) {
        fn_80023B90(&src[i], &lbl_80367318[i]);
    }
    dir.x = lbl_80367318[0].x;
    dir.y = lbl_80367318[0].y;
    dir.z = lbl_80367318[0].z;
    PSVECNormalize(&dir, &dir);
    dir2 = dir;
    fn_800BEBCC(0, &dir2);
}

void fn_8001CA40(u8 stadium) {
    g_d_GameSettings._54 = stadium;
    loadLights(lbl_800F7478[stadium].light, 4);
}

// .text:0x8001CB10 size:0xC4
void fn_8001CB10(LightSrc* src, s32 count) {
    s32 i;
    LightPos* dst;
    Vec dir2;
    Vec dir;

    for (i = 0; i < count; i++) {
        fn_80023B90(&src[i], &lbl_80367318[i]);
    }
    dir.x = lbl_80367318[0].x;
    dir.y = lbl_80367318[0].y;
    dir.z = lbl_80367318[0].z;
    PSVECNormalize(&dir, &dir);
    dir2 = dir;
    fn_800BEBCC(0, &dir2);
}

// .text:0x8001CBD4 size:0xF4
void fn_8001CBD4(void) {
    s32 stadium;

    if (g_d_GameSettings.GameModeSelected == 7) {
        stadium = g_d_GameSettings.StadiumID + 7;
    } else {
        stadium = g_d_GameSettings.StadiumID;
    }
    fn_8001CA40(stadium);
}

// .text:0x8001CCC8 size:0x1AC
// NONMATCHING 98%: scheduling of the stadium light setup
#if NONMATCHING
void fn_8001CCC8(void) {
    LightPos* lights = lbl_80367318;
    s32 i;
    StadiumLights* st;
    LightPos* lp;
    u32 c;
    GXColor color;

    lbl_8036E548._3085 = 4;
    fn_8001CBD4();
    fn_800BD2DC();
    st = &lbl_800F7478[g_d_GameSettings._54];
    if (st->ambient.a != 0) {
        color = st->ambient;
        fn_800BD2CC(1, color);
    }
    lp = lights;
    for (i = 0; i < 4; i++) {
        LITAlloc(&lbl_8036E548.lights[i]);
        LITInitAttn(lbl_8036E548.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(lbl_8036E548.lights[i], lp->x, lp->y, lp->z);
        c = lp->color;
        LITInitColor(lbl_8036E548.lights[i], &c);
        lp++;
    }
}
#endif

// .text:0x8001CE74 size:0x200
// NONMATCHING 96%: light-table base register and scheduling
#if NONMATCHING
void fn_8001CE74(void) {
    LightPos* lp = lbl_80367318;
    s32 i;
    StadiumLights* st;
    GXColor color;
    u32 c;

    lbl_8036E548._3085 = 4;
    fn_8001CBD4();
    fn_800BD2DC();
    st = &lbl_800F7478[g_d_GameSettings._54];
    if (st->ambient.a != 0) {
        color = st->ambient;
        fn_800BD2CC(1, color);
    }
    for (i = 0; i < 4; i++) {
        LITAlloc(&lbl_8036E548.lights[i]);
        LITInitAttn(lbl_8036E548.lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(lbl_8036E548.lights[i], lp->x, lp->y, lp->z);
        c = lp->color;
        LITInitColor(lbl_8036E548.lights[i], &c);
        lp++;
    }
    if (lbl_8036E548.slots6C != NULL) {
        for (i = 0; i < lbl_8036E548.slots6C->count; i++) {
            fn_800BD548(&lbl_8036E548.slots6C->slots[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        }
    }
}
#endif

// .text:0x8001D074 size:0x5C
void fn_8001D074(s32 index, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    CharModel* model;

    if (actor != NULL) {
        model = lbl_8036E548.slots->slots[actor->modelIndex].model;
        if (enable != 0) {
            model->flags |= 4;
        } else {
            model->flags &= 0xFB;
        }
    }
}

// .text:0x8001D0D0 size:0x40
void fn_8001D0D0(s32 index, f32 scale) {
    CTRLSetScale(&lbl_8036E548.slots68->slots[index].ctrl, scale, scale, scale);
}

// .text:0x8001D110 size:0x38
void fn_8001D110(s32 index, f32 x, f32 y, f32 z) {
    CTRLSetScale(&lbl_8036E548.slots68->slots[index].ctrl, x, y, z);
}

// .text:0x8001D148 size:0x38
void fn_8001D148(s32 index, f32 x, f32 y, f32 z) {
    CTRLSetScale(&lbl_8036E548.slots64->slots[index].ctrl, x, y, z);
}

// .text:0x8001D180 size:0x154
// NONMATCHING 98%: register allocation only
#if NONMATCHING
void fn_8001D180(s32 index, s32 which, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    s32 joint = actor != NULL ? actor->jointIdx[lbl_803CB7B4[which]] : 0xFFFF;
    CharModel** models;
    CharModel* model;
    CharJoint* dst;
    CharModel* src;
    CharJoint** jp;
    s32 i;
    s32 n;

    if (joint == 0xFFFF) {
        return;
    }
    models = &actor->model;
    i = 0;
    do {
        model = *models;
        if (enable == 0) {
            if (model != NULL && model->joints[joint] != NULL) {
                model->joints[joint]->display = NULL;
            }
        } else if (lbl_800EEAAC[actor->kind] >= 0 && actor->parts != NULL) {
            dst = model->joints[joint];
            if (which & 1) {
                src = lbl_8036E548.partSlots->slots[actor->parts->part[1].slot].model;
            } else {
                src = lbl_8036E548.partSlots->slots[actor->parts->part[0].slot].model;
            }
            if (src == NULL) {
                return;
            }
            n = src->jointCount;
            jp = &src->joints[n];
            do {
                jp--;
                n--;
                if ((*jp)->display != NULL) {
                    dst->display = (*jp)->display;
                    return;
                }
            } while (n != 0);
            return;
        }
        models--;
    } while (i-- != 0);
}
#endif

// .text:0x8001D2D4 size:0x8A0
void fn_8001D2D4(void) {
    return;
}

// .text:0x8001DB74 size:0x1E4
// NONMATCHING 95%: register allocation of the slot/camera loops
#if NONMATCHING
void fn_8001DB74(CharSlotList* list) {
    u16 i;
    u16 k;
    CharActor* actor;
    CharSlot* slot;
    CharModel* model;
    MtxPtr view;
    u8 mask;
    s32 shift;
    Mtx m;

    for (i = 0; i < list->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL || actor->mode[0] == 0) {
            continue;
        }
        slot = &lbl_8036E548.slots->slots[actor->modelIndex];
        if (slot->model == NULL) {
            continue;
        }
        if (slot->_58 != 0) {
            ACTSetAnimation(slot->model, slot->act, 0, slot->animId, 0.0f, slot->_60);
        }
        if (slot->_59 != 0) {
            fn_800B4CA0(slot->model, slot->_5C);
        }
        if (slot->_5A != 0) {
            fn_800B4C04(slot->model, slot->_54);
        }
        if (slot->_5B & 2) {
            fn_800B4AFC(slot->model, slot->_5B & 1);
        }
        Set_FUN_800b2b6c(slot->model, slot->mirror);
        if (slot->_6C != 0) {
            fn_800BDA24(slot);
        }
        for (k = 0; k < fn_800527BC(); k++) {
            view = fn_80052734(k)->view;
            shift = k * 3;
            mask = ~(3 << shift);
            if (lbl_8036E548._307A == 5) {
                slot->model->flags = 1;
            } else {
                PSMTXTrans(m, actor->pos.x, actor->pos.y, actor->pos.z);
                PSMTXConcat(view, m, m);
                model = slot->model;
                model->flags = (model->flags & mask) | (fn_800B3C04(k, model, m) << shift);
            }
        }
        slot->_58 = 0;
        slot->_59 = 0;
        slot->_5A = 0;
        slot->_5B &= 1;
    }
}
#endif

// .text:0x8001DD58 size:0x14C
// NONMATCHING 98%: register allocation only
#if NONMATCHING
void fn_8001DD58(CharModel* model, s32 pass, MtxPtr view, s32 n, ...) {
    va_list args;
    CharJoint* joint;

    if (model->flags & (1 << (pass * 3))) {
        if (model->display != NULL) {
            GXInvalidateVtxCache();
            va_start(args, n);
            if (model->_7C != NULL) {
                DOVARender(model->display, view, n, args);
            } else {
                DOVARenderSkin(model->display, view, model->_64, model->_68, n);
            }
        }
        for (joint = model->firstJoint; joint != NULL; joint = joint->next) {
            if (joint->display != NULL) {
                DOSetWorldMatrix(joint->display, joint->worldMtx);
            }
            va_start(args, n);
            DOVARender(joint->display, view, n, args);
        }
    }
}
#endif

// .text:0x8001DEA4 size:0x234
void fn_8001DEA4(CharSlot* slot, s32 pass, MtxPtr view) {
    CharModel* model = slot->model;

    if (slot->callback != NULL) {
        slot->callback(slot);
    }
    switch (slot->lightCount) {
    case 0:
        fn_8001DD58(model, pass, view, 0);
        break;
    case 1:
        fn_8001DD58(model, pass, view, 1, slot->lights[0]);
        break;
    case 2:
        fn_8001DD58(model, pass, view, 2, slot->lights[0], slot->lights[1]);
        break;
    case 3:
        fn_8001DD58(model, pass, view, 3, slot->lights[0], slot->lights[1], slot->lights[2]);
        break;
    case 4:
        fn_8001DD58(model, pass, view, 4, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3]);
        break;
    case 5:
        fn_8001DD58(model, pass, view, 5, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4]);
        break;
    case 6:
        fn_8001DD58(model, pass, view, 6, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4], slot->lights[5]);
        break;
    case 7:
        fn_8001DD58(model, pass, view, 7, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4], slot->lights[5], slot->lights[6]);
        break;
    case 8:
        fn_8001DD58(model, pass, view, 8, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4], slot->lights[5], slot->lights[6], slot->lights[7]);
        break;
    }
}

// .text:0x8001E0D8 size:0x388
// NONMATCHING 99%: slot/loop-counter registers swapped
#if NONMATCHING
void fn_8001E0D8(CharSlotList* list, s32 pass, Mtx view) {
    u8 last = 0xFF;
    GXColor amb = lbl_800F7478[g_d_GameSettings._54].ambient;
    GXColor c;
    u16 i;
    CharActor* actor;
    CharSlot* slot;
    Mtx m;

    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < list->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL || actor->mode[0] == 2) {
            continue;
        }
        slot = &lbl_8036E548.slots->slots[actor->modelIndex];
        if (slot->model == NULL || slot->_6C == 0) {
            continue;
        }
        if (last != actor->_277) {
            last = actor->_277;
            if (0xFF - last != 0) {
                amb.a = last;
                if (last == 0) {
                    continue;
                }
                c = amb;
                fn_800BD2CC(1, c);
            } else {
                fn_800BD2CC(1, lbl_800F7478[g_d_GameSettings._54].ambient);
            }
        }
        PSMTXTrans(m, actor->pos.x, actor->pos.y, actor->pos.z);
        PSMTXConcat(view, m, m);
        fn_800B9948(actor->_05C);
        lbl_803CBC18 = actor;
        fn_8001DEA4(slot, pass, m);
    }
    fn_800B993C();
}
#endif

extern void* lbl_803CB7AC[2];

extern u8 lbl_803CBBC0;

// fn_8001E460, size:0x14
void fn_8001E460(void* value) {
    lbl_803CB7AC[lbl_803CBBC0] = value;
}

// fn_8001E474, size:0x14
void fn_8001E474(void) {
    lbl_803CB7AC[0] = 0;
    lbl_803CB7AC[1] = 0;
}

// .text:0x8001E488 size:0x2FC
// NONMATCHING 99%: slot/loop-counter registers swapped
#if NONMATCHING
void fn_8001E488(void) {
    s32 i;
    CharActor* actor;
    CharSlot* slot;
    f32 x;
    f32 y;
    Mtx44 proj;

    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < lbl_8036E548.slots->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL) {
            slot = &lbl_8036E548.slots->slots[i];
            if (slot->model != NULL && slot->_6C != 0) {
                x = actor->pos.x / 1280.0f;
                y = actor->pos.y / 1280.0f;
                C_MTXFrustum(proj, -0.175f + y, 0.175f + y, 0.25f + x, -0.25f + x, 1.0f, 512.0f);
                GXSetProjection(proj, GX_PERSPECTIVE);
                fn_8001DEA4(slot, 0, fn_80052734(0)->view);
            }
        }
    }
}
#endif

// .text:0x8001E784 size:0x9E8
void fn_8001E784(void) {
    return;
}

// .text:0x8001F16C size:0xBC
// NONMATCHING 96%: loop counter and active[] walker swap r28/r30
#if NONMATCHING
void fn_8001F16C(void) {
    CharSlotList* list;
    s32 i;
    CharActor* actor;
    CharSlot* slot;
    u8 st = lbl_8036E548._307A;

    if (st != 0 && st != 3) {
        list = lbl_8036E548.slots;
        for (i = 0; i < list->count; i++) {
            actor = lbl_8036E548.active[i];
            if (actor != NULL) {
                slot = &lbl_8036E548.slots->slots[actor->modelIndex];
                if (slot->model != NULL && slot->_6C != 0) {
                    fn_800B2D5C(slot->model);
                }
            }
        }
    }
}
#endif

// .text:0x8001F228 size:0x298
void fn_8001F228(void) {
    s32 i;
    s32 j;

    lbl_8036E548._307A = 0;
    lbl_8036E548._0004[0] = 0;
    lbl_8036E548._0004[1] = 0;
    for (i = 0; i < 21; i++) {
        lbl_8036E548._000C[i] = 0;
    }
    lbl_8036E548.slots = NULL;
    lbl_8036E548.slots64 = NULL;
    lbl_8036E548.slots68 = NULL;
    lbl_8036E548.slots6C = NULL;
    lbl_8036E548._0070 = 0;
    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i]._25C = 0;
        lbl_8036E548.active[i] = NULL;
    }
    lbl_8036E548.stadiumFiles = NULL;
    lbl_8036E548._2C88 = NULL;
    lbl_8036E548.fileBuf = NULL;
    // NOTE: the original clears 16 entries per bankSets row, running past the
    // end of bankSets into preload[] and _2D60/_2D64.
    for (i = 0; i < 16; i++) {
        lbl_8036E548.animBufs[i] = NULL;
        for (j = 0; j < 4; j++) {
            lbl_8036E548.bankSets[j][i] = NULL;
        }
    }
    for (i = 0; i < 13; i++) {
        lbl_8036E548._2D6A[i] = -1;
    }
    lbl_8036E548.trail = NULL;
    lbl_8036E548.trail2 = NULL;
    lbl_8036E548._2D98 = 0;
    lbl_8036E548.trailFile = NULL;
    lbl_8036E548._307C = 0;
    lbl_8036E548._3085 = 0;
    lbl_8036E548.callback = NULL;
    lbl_8036E548._3087 = 0;
    lbl_8036E548._3086 = 0;
    DrawShadows(0);
}

// .text:0x8001F4C0 size:0x128
void challengeMapMaybe(void) {
    s32 i;
    CharActor* actor;

    for (i = 0; i < 13; i++) {
        actor = &lbl_8036E548.actors[i];
        actor->_25C = 0;
        actor->mode[0] = 0;
        actor->_04C = 0.5f;
        actor->_060 = 0;
        actor->anim[0] = 0;
        actor->anim[1] = 0;
        actor->_06A[0] = 0;
        actor->mode[1] = 1;
        actor->_268 = 0;
        actor->_273 = 0;
        actor->_274 = 0;
        actor->_278 = 0;
        actor->_05C = 0;
        actor->pos.x = 0.0f;
        actor->pos.y = 0.0f;
        actor->pos.z = 0.0f;
        actor->_040.x = 0.0f;
        actor->_040.y = 0.0f;
        actor->_040.z = 0.0f;
        actor->_070 = -1;
    }
    for (i = 0; i < 13; i++) {
        if (lbl_8036E548.active[i] != NULL) {
            lbl_8036E548.active[i]->_25C = 1;
        }
    }
    for (i = 0; i < 25; i++) {
        lbl_8036E548.trail[i]._26 = 0;
        lbl_8036E548.trail[i]._04[0] = 0.0f;
        lbl_8036E548.trail[i]._04[1] = 0.0f;
        lbl_8036E548.trail[i]._04[2] = 0.0f;
        lbl_8036E548.trail[i]._04[3] = 0.0f;
        lbl_8036E548.trail[i]._04[4] = 0.0f;
        lbl_8036E548.trail[i]._04[5] = 0.0f;
    }
    lbl_8036E548._3078 = 0;
}

// .text:0x8001F5E8 size:0x2BC
// NONMATCHING 70%: original reloads the relocated trail pointers and indexes the trail array; ours keeps them in registers
#if NONMATCHING
void fn_8001F5E8(void) {
    u32* file;
    void* layout;
    void* geo;
    void* tex;
    s32 count = 30;
    s32 i;

    lbl_8036E548._3078 = count;
    // TODO type: file header of offsets, relocated here.
    file = lbl_8036E548.trailFile;
    lbl_8036E548.trailLayout = (u8*)file + file[0];
    lbl_8036E548.trailGeo = (u8*)file + file[1];
    lbl_8036E548.trailTex = (u8*)file + file[2];
    layout = lbl_8036E548.trailLayout;
    geo = lbl_8036E548.trailGeo;
    tex = lbl_8036E548.trailTex;
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, NULL);
    haveActLayoutPointToGeoHeader(layout, geo);
    convertTextureHeader(tex);
    fn_800BD190(geo, tex);
    lbl_8036E548.slots68 = ActorObjectInitTable(count);
    for (i = 0; i < count; i++) {
        fn_800BDC88(lbl_8036E548.slots68, i, i, lbl_8036E548.trailLayout, 0, 0);
        fn_800BD548(&lbl_8036E548.slots68->slots[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        CTRLSetTranslation(&lbl_8036E548.slots68->slots[i].ctrl, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&lbl_8036E548.slots68->slots[i].ctrl, 0.0f, 0.0f, 0.0f);
    }
    lbl_8036E548.trail2 = _OSAllocFromHeap(0x20, count * sizeof(CharTrail));
    for (i = 0; i < count; i++) {
        lbl_8036E548.trail2[i]._04[0] = 0.0f;
        lbl_8036E548.trail2[i]._04[1] = 0.0f;
        lbl_8036E548.trail2[i]._04[2] = 0.0f;
        lbl_8036E548.trail2[i]._04[3] = 0.0f;
        lbl_8036E548.trail2[i]._04[4] = 0.0f;
        lbl_8036E548.trail2[i]._04[5] = 0.0f;
        lbl_8036E548.trail2[i]._26 = 0;
        lbl_8036E548.trail2[i]._00 = 0;
    }
}
#endif

// .text:0x8001F8A4 size:0x3A8
// NONMATCHING 89%: register allocation; light-kind range checks scheduled differently
#if NONMATCHING
void fn_8001F8A4(void) {
    s32 i;
    void* layout;
    void* geo;
    void* tex;
    u8* kind;
    CharSlot* slot;

    for (i = 0; i < 24; i++) {
        layout = lbl_8036E548.stadiumFiles->obj[i].layout;
        geo = lbl_8036E548.stadiumFiles->obj[i].geo;
        tex = lbl_8036E548.stadiumFiles->obj[i].tex;
        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geo, NULL);
        haveActLayoutPointToGeoHeader(layout, geo);
        if (i == 11) {
            tex = lbl_8036E548.stadiumFiles->obj[10].tex;
        } else {
            convertTextureHeader(tex);
        }
        fn_800BD190(geo, tex);
    }
    ANIMGet(lbl_8036E548.stadiumFiles->bank);
    fn_80025DDC(lbl_8036E548.stadiumFiles->anim[0].shape);
    lbl_8036E548.stadiumAnim[0].set = lbl_8036E548.stadiumFiles->anim[0].set;
    fn_80025FFC(lbl_8036E548.stadiumFiles->anim[0].shape, &lbl_8036E548.stadiumAnim[0]);
    fn_80025EEC(&lbl_8036E548.stadiumAnim[0], 0, 0);
    fn_80025DDC(lbl_8036E548.stadiumFiles->anim[1].shape);
    lbl_8036E548.stadiumAnim[1].set = lbl_8036E548.stadiumFiles->anim[1].set;
    fn_80025FFC(lbl_8036E548.stadiumFiles->anim[1].shape, &lbl_8036E548.stadiumAnim[1]);
    fn_80025EEC(&lbl_8036E548.stadiumAnim[1], 0, 0);
    lbl_8036E548.slots64 = ActorObjectInitTable(25);
    kind = lbl_800EEA58;
    for (i = 0; i < 25; i++) {
        layout = lbl_8036E548.stadiumFiles->obj[*kind].layout;
        if (*kind < 0x10) {
            fn_800BDC88(lbl_8036E548.slots64, i, i, layout, 0, 0);
        } else {
            fn_800BDC88(lbl_8036E548.slots64, i, i, lbl_8036E548.stadiumFiles->bank, 0, 0);
            slot = &lbl_8036E548.slots64->slots[i];
            slot->animId = 0;
            slot->_5C = 0.0f;
            slot->_58 = 1;
            slot->_59 = slot->act != NULL;
            slot->_5A = slot->act != NULL;
            slot->_60 = 0.0f;
            ACTSetAnimation(slot->model, slot->act, 0, slot->animId, 0.0f, slot->_60);
            fn_800B4AFC(slot->model, 0);
        }
        if (*kind == 0 || *kind == 4 || (*kind >= 7 && *kind <= 10) || (*kind >= 12 && *kind <= 18) || *kind == 19) {
            fn_800BD548(&lbl_8036E548.slots64->slots[i], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
        } else {
            fn_800BD548(&lbl_8036E548.slots64->slots[i], 0, 0, 0, 0);
        }
        CTRLSetTranslation(&lbl_8036E548.slots64->slots[i].ctrl, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&lbl_8036E548.slots64->slots[i].ctrl, 0.0f, 0.0f, 0.0f);
        if (i == 5) {
            fn_80025C58(lbl_8036E548.stadiumAnim[0].model, (ShapeModel**)&lbl_8036E548.slots64->slots[i].model);
        } else if (i == 6) {
            fn_80025C58(lbl_8036E548.stadiumAnim[1].model, (ShapeModel**)&lbl_8036E548.slots64->slots[i].model);
        }
        kind++;
    }
    lbl_8036E548.trail = _OSAllocFromHeap(0x20, 25 * sizeof(CharTrail));
    for (i = 0; i < 25; i++) {
        lbl_8036E548.trail[i]._04[0] = 0.0f;
        lbl_8036E548.trail[i]._04[1] = 0.0f;
        lbl_8036E548.trail[i]._04[2] = 0.0f;
        lbl_8036E548.trail[i]._04[3] = 0.0f;
        lbl_8036E548.trail[i]._04[4] = 0.0f;
        lbl_8036E548.trail[i]._04[5] = 0.0f;
        lbl_8036E548.trail[i]._26 = 0;
        lbl_8036E548.trail[i]._00 = 0;
    }
}
#endif

// .text:0x8001FC4C size:0x188
static inline void mirrorJointPairs(CharActor* actor, u16* pairs) {
    u16 a;
    u16 b;

    for (; pairs[0] != 0xFFFF; pairs += 2) {
        a = actor->jointIdx[pairs[0]];
        b = actor->jointIdx[pairs[1]];
        if (a != 0xFFFF && b != 0xFFFF) {
            actor->mirror[a] = b;
            actor->mirror[b] = a;
        }
    }
}

// NONMATCHING 84%: mirror tables are addressed from lbl_800EE930 instead of the original's lbl_800EE800 anchor (this unit's .data is not split)
#if NONMATCHING
void fn_8001FC4C(CharActor* actor) {
    s32 i;
    u16* pairs;

    for (i = 0; i < 0x78; i++) {
        actor->mirror[i] = i;
    }
    pairs = &lbl_800EE930[0x18];
    i = 0;
    do {
        u16 a = actor->jointIdx[pairs[0]];
        u16 b = actor->jointIdx[pairs[1]];
        if (a != 0xFFFF && b != 0xFFFF) {
            actor->mirror[a] = b;
            actor->mirror[b] = a;
        }
        i += 2;
        pairs += 2;
    } while (lbl_800EE930[0x18 + i] != 0xFFFF);
    switch (actor->kind) {
    case 20:
    case 43:
        pairs = lbl_803CB798;
        break;
    case 41:
        pairs = &lbl_800EE930[0x34];
        break;
    case 17:
        pairs = lbl_803CB7A0;
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        pairs = &lbl_800EE930[0x40];
        break;
    default:
        pairs = NULL;
        break;
    }
    if (pairs == NULL) {
        return;
    }
    mirrorJointPairs(actor, pairs);
}
#endif

// .text:0x8001FDD4 size:0x2C
void fn_8001FDD4(CharSlot* slot) {
    if (slot->lights[0] != NULL) {
        fn_800B9AA8(slot->lights[0]);
    }
}
