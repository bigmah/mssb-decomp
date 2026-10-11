#include "main/file_80011640.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"
#include "Dolphin/GX/GXTypes.h"

// Globals owned by other units (only the fields used here).
typedef struct GameSettingsView {
    /*0x00*/ u8 _00[0x7];
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
    /*0x00*/ u8 _00[0x26];
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
extern void GXInvalidateVtxCache(void);
extern void DOVARender(void* display, s32 a, s32 b, va_list args);
extern void DOVARenderSkin(void* display, s32 a, void* p, void* q, s32 b);
extern void DOSetWorldMatrix(void* display, MtxPtr mtx);
extern void fn_800BD2DC(void);
extern void fn_800BD2CC(s32 channel, GXColor color);
extern void LITAlloc(void** light);
extern void LITInitAttn(void* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
extern void LITInitPos(void* light, f32 x, f32 y, f32 z);
extern void LITInitColor(void* light, u32* color);
extern void ACTSetAnimation(void* act, s32 a, u16 anim, f32 frame, f32 speed);
extern void fn_800B4CA0(CharModel* model, f32 v);
extern void fn_800B4C04(CharModel* model, f32 v);
extern void fn_800B4AFC(CharModel* model, s32 v);
extern void Set_FUN_800b2b6c(CharModel* model, void* p);
extern void fn_800BDA24(CharSlot* slot);
extern s32 fn_800527BC(void);
extern void* fn_80052734(u16 index);
extern u8 fn_800B3C04(u16 index, CharModel* model, Mtx m);
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
void fn_800145F8(void) {
    return;
}

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
void fn_80014A18(void) {
    return;
}

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
void fn_80017098(void) {
    return;
}

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
                        actor->banks.b[1] = lbl_8036E548.bankBuf[k];
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
        actor->banks.b[1] = lbl_8036E548.bankBuf[k];
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
void fn_80017DBC(void) {
    return;
}

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
void fn_80018270(void) {
    return;
}

// .text:0x800188C0 size:0xF8
void fn_800188C0(void) {
    CharLoadTask* task = lbl_803CC1B8;

    switch (task->state) {
    case 0:
        if (g_d_GameSettings.GameModeSelected == 6) {
            lbl_8036E548._2C84 = ARAMTransfer(&lbl_800EE910[1], NULL, 0, 0);
        } else {
            lbl_8036E548._2C84 = ARAMTransfer(&lbl_800EE910[0], NULL, 0, 0);
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
void fn_80018B74(void) {
    return;
}

// .text:0x80018DEC size:0x8EC
void fn_80018DEC(void) {
    return;
}

// .text:0x800196D8 size:0x388
void fn_800196D8(void) {
    return;
}

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
void fn_8001A3FC(void) {
    return;
}

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
void fn_8001AB10(void) {
    return;
}

// .text:0x8001AF98 size:0x268
void fn_8001AF98(void) {
    return;
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
            slot->_68 = NULL;
        } else {
            slot->_68 = actor->_072;
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
void fn_8001BA44(void) {
    return;
}

// .text:0x8001BE50 size:0x3E4
void fn_8001BE50(s32 index, s16 anim, u8 a, u8 b, s16 c, u8 d, u8 e) {
    return;
}

// .text:0x8001C234 size:0x2F4
void fn_8001C234(void) {
    return;
}

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
        ARAMTransfer(&lbl_803CB790[id * 0x13 + 6], lbl_8036E548._2CE8, 0, 0);
        lbl_803CBC3C[3] = 2;
    } else if (lbl_803CBC3C[3] == 2 && (s32)lbl_803C6CF8.transferDone == 1) {
        ANIMGet(lbl_8036E548._2CE8);
        if (lbl_8036E548.active[1]->banks.b[4] == NULL) {
            lbl_8036E548.active[1]->banks.b[4] = lbl_8036E548._2CE8;
        }
        return 1;
    }
fail:
    lbl_803CBC3C[0] = 0;
    return 0;
}

// .text:0x8001C67C size:0x2A4
int fn_8001C67C_animation(int a, int b) {
    return 0;
}

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
        ARAMTransfer(&lbl_803CB790[file], lbl_8036E548._2CE4, 0, 0);
        lbl_803CBC3C[1] = 2;
    } else if (lbl_803CBC3C[1] == 2 && (s32)lbl_803C6CF8.transferDone == 1) {
        ANIMGet(lbl_8036E548._2CE4);
        if (lbl_8036E548.active[0]->banks.b[3] == NULL) {
            lbl_8036E548.active[0]->banks.b[3] = lbl_8036E548._2CE4;
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
            ACTSetAnimation(slot->act, 0, slot->animId, 0.0f, slot->_60);
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
        Set_FUN_800b2b6c(slot->model, slot->_68);
        if (slot->_6C != 0) {
            fn_800BDA24(slot);
        }
        for (k = 0; k < fn_800527BC(); k++) {
            view = (MtxPtr)((u8*)fn_80052734(k) + 0x40); // TODO type: camera view matrix
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
void fn_8001DD58(CharModel* model, s32 pass, s32 a, s32 b, ...) {
    va_list args;
    CharJoint* joint;

    if (model->flags & (1 << (pass * 3))) {
        if (model->display != NULL) {
            GXInvalidateVtxCache();
            va_start(args, b);
            if (model->_7C != NULL) {
                DOVARender(model->display, a, b, args);
            } else {
                DOVARenderSkin(model->display, a, model->_64, model->_68, b);
            }
        }
        for (joint = model->firstJoint; joint != NULL; joint = joint->next) {
            if (joint->display != NULL) {
                DOSetWorldMatrix(joint->display, joint->worldMtx);
            }
            va_start(args, b);
            DOVARender(joint->display, a, b, args);
        }
    }
}
#endif

// .text:0x8001DEA4 size:0x234
void fn_8001DEA4(CharSlot* slot, s32 pass, s32 a) {
    CharModel* model = slot->model;

    if (slot->callback != NULL) {
        slot->callback(slot);
    }
    switch (slot->lightCount) {
    case 0:
        fn_8001DD58(model, pass, a, 0);
        break;
    case 1:
        fn_8001DD58(model, pass, a, 1, slot->lights[0]);
        break;
    case 2:
        fn_8001DD58(model, pass, a, 2, slot->lights[0], slot->lights[1]);
        break;
    case 3:
        fn_8001DD58(model, pass, a, 3, slot->lights[0], slot->lights[1], slot->lights[2]);
        break;
    case 4:
        fn_8001DD58(model, pass, a, 4, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3]);
        break;
    case 5:
        fn_8001DD58(model, pass, a, 5, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4]);
        break;
    case 6:
        fn_8001DD58(model, pass, a, 6, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4], slot->lights[5]);
        break;
    case 7:
        fn_8001DD58(model, pass, a, 7, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4], slot->lights[5], slot->lights[6]);
        break;
    case 8:
        fn_8001DD58(model, pass, a, 8, slot->lights[0], slot->lights[1], slot->lights[2], slot->lights[3], slot->lights[4], slot->lights[5], slot->lights[6], slot->lights[7]);
        break;
    }
}

// .text:0x8001E0D8 size:0x388
void fn_8001E0D8(void) {
    return;
}

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
void fn_8001E488(void) {
    return;
}

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
    return;
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
void fn_8001F5E8(void) {
    return;
}

// .text:0x8001F8A4 size:0x3A8
void fn_8001F8A4(void) {
    return;
}

// .text:0x8001FC4C size:0x188
void fn_8001FC4C(CharActor* actor) {
    return;
}

// .text:0x8001FDD4 size:0x2C
void fn_8001FDD4(CharSlot* slot) {
    if (slot->lights[0] != NULL) {
        fn_800B9AA8(slot->lights[0]);
    }
}
