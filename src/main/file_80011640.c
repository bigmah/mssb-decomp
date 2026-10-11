#include "main/file_80011640.h"
#include "Dolphin/mtx.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

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
    /*0x00*/ u8 _00[0x10];
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
void fn_80011CA8(void) {
    return;
}

// .text:0x800126EC size:0x10C
void fn_800126EC(void) {
    return;
}

// .text:0x800127F8 size:0x398
void LoadModel(void) {
    return;
}

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
void fn_80017340(void) {
    return;
}

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
void fn_800177B4(void) {
    return;
}

// .text:0x80017814 size:0x514
void fn_80017814(CharActor* actor, s32 modelIndex, s32 index, void (*callback)(CharLoadObj*)) {
    return;
}

// .text:0x80017D28 size:0x94
void fn_80017D28(void) {
    return;
}

// .text:0x80017DBC size:0x268
void fn_80017DBC(void) {
    return;
}

// .text:0x80018024 size:0x24C
void fn_80018024(void) {
    return;
}

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
    return;
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
void fn_80019A60(void) {
    return;
}

// .text:0x80019C00 size:0x65C
void fn_80019C00(void) {
    return;
}

// .text:0x8001A25C size:0x1A0
void fn_8001A25C(void) {
    return;
}

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
void fn_8001B35C(void) {
    return;
}

// .text:0x8001B4D8 size:0x114
// NONMATCHING 93%: saved-register numbering of actor/list/joints/offset
#if NONMATCHING
void fn_8001B4D8(s32 index, s32 enable) {
    CharActor* actor = lbl_8036E548.active[index];
    u16 j0;
    u16 j1;
    u16 idx;
    CharSlotList* list;
    Vec d;
    Vec v;

    if (actor != NULL) {
        idx = actor->modelIndex;
        if (enable != 0 && actor->_268 == 0) {
            j0 = getJoint(actor, 0);
            j1 = getJoint(actor, 0);
            list = lbl_8036E548.slots;
            fn_800B2C44(list->slots[idx].model, list->slots[idx].model->_80, &v);
            list->slots[idx]._64 = j1;
            list->slots[idx]._66 = j0;
            d = v;
            actor->pos.x += d.x;
            actor->pos.y += d.y;
            actor->pos.z += d.z;
            actor->_268 = 1;
        }
    }
}
#endif

// .text:0x8001B5EC size:0x13C
void fn_8001B5EC(void) {
    return;
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
void fn_8001CCC8(void) {
    return;
}

// .text:0x8001CE74 size:0x200
void fn_8001CE74(void) {
    return;
}

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
void fn_8001D180(void) {
    return;
}

// .text:0x8001D2D4 size:0x8A0
void fn_8001D2D4(void) {
    return;
}

// .text:0x8001DB74 size:0x1E4
void fn_8001DB74(void) {
    return;
}

// .text:0x8001DD58 size:0x14C
void fn_8001DD58(void) {
    return;
}

// .text:0x8001DEA4 size:0x234
void fn_8001DEA4(void) {
    return;
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
void fn_8001FC4C(void) {
    return;
}

// .text:0x8001FDD4 size:0x2C
void fn_8001FDD4(CharLoadObj* obj) {
    if (obj->_70 != NULL) {
        fn_800B9AA8(obj->_70);
    }
}
