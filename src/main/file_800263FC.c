#include "main/file_800263FC.h"

// Particle / emitter system.

int __abs(int);

extern f32 lbl_8017ED68[]; // cosine table, 0x800 steps per turn
extern Mtx lbl_8017FF78;   // camera (view) matrix
extern Mtx lbl_8017FFE0;
extern Particle* lbl_803CBC74; // free particle list
extern u8 lbl_803CBC78;        // nonzero: clear all emitters on next draw
extern s32 lbl_803CBC7C;
extern Emitter* lbl_803CBC80;  // free emitter list (linked through next)
extern EmitterHead lbl_803CBC84; // active list head
#define EMITTER_HEAD ((Emitter*)&lbl_803CBC84)

static inline Emitter* FindEmitter(Emitter* e, u8 type) {
    if (e == NULL) {
        e = EMITTER_HEAD;
    }
    while ((e = e->next) != NULL) {
        if (e->type == type) {
            break;
        }
    }
    return e;
}

static inline void FreeParticles(Particle* list) {
    Particle* last = list;
    while (last != NULL && last->next != NULL) {
        last = last->next;
    }
    if (last != NULL) {
        last->next = lbl_803CBC74;
        lbl_803CBC74 = list;
    }
}

static inline Emitter* AllocParticles(Emitter* e, s32 n, s32 strict) {
    s32 count;
    Particle* p;
    Particle* last;
    count = 0;
    last = NULL;
    p = lbl_803CBC74;
    if (e != NULL) {
        while (p != NULL && n != 0) {
            last = p;
            p = p->next;
            count++;
            n--;
        }
        if (strict && n != 0) {
            return NULL;
        }
        e->count = count;
        if (count != 0) {
            e->particles = lbl_803CBC74;
            lbl_803CBC74 = p;
            if (last != NULL) {
                last->next = NULL;
            }
        } else {
            e->particles = NULL;
        }
    }
    return e;
}

static inline void FreeEmitter(Emitter* e) {
    if (e->update != NULL) {
        if (e->prev != NULL) {
            e->prev->next = e->next;
        }
        if (e->next != NULL) {
            e->next->prev = e->prev;
        }
        e->update = NULL;
        FreeParticles(e->particles);
        e->prev = NULL;
        e->next = lbl_803CBC80;
        lbl_803CBC80 = e;
    }
}

static inline Emitter* NewEmitter(EmitterUpdateFn update, u8 priority, s32 unk14, s32 n, s32 strict, u8 type) {
    Emitter* e = AllocParticles(lbl_803CBC80, n, strict);
    Emitter* at;
    if (e == NULL) {
        return NULL;
    }
    lbl_803CBC80 = lbl_803CBC80->next;
    e->update = update;
    e->priority = priority;
    e->type = type;
    e->active = 1;
    e->unk14 = unk14;
    e->next = NULL;
    e->prev = NULL;
    at = EMITTER_HEAD;
    while (at->next != NULL && at->next->priority < e->priority) {
        at = at->next;
    }
    e->next = at->next;
    if (e->next != NULL) {
        e->next->prev = e;
    }
    e->prev = at;
    at->next = e;
    return e;
}

// .text:0x800263FC size:0x59C
void fn_800263FC(void) {
    return;
}

// .text:0x80026998 size:0x4C0
void fn_80026998(void) {
    return;
}

// .text:0x80026E58 size:0x4A8
void fn_80026E58(void) {
    return;
}

// .text:0x80027300 size:0x374
void fn_80027300(void) {
    return;
}

// .text:0x80027674 size:0x2A4
void fn_80027674(void) {
    return;
}

// .text:0x80027918 size:0x50
void fn_80027918(void) {
    return;
}

// .text:0x80027968 size:0xBC4
void fn_80027968(void) {
    return;
}

// .text:0x8002852C size:0xFC
void fn_8002852C(void) {
    return;
}

// .text:0x80028628 size:0x920
void fn_80028628(void) {
    return;
}

// .text:0x80028F48 size:0x614
void fn_80028F48(void) {
    return;
}

// .text:0x8002955C size:0x294
void fn_8002955C(void) {
    return;
}

// .text:0x800297F0 size:0x4D8
void fn_800297F0(void) {
    return;
}

// .text:0x80029CC8 size:0x504
void fn_80029CC8(void) {
    return;
}

// .text:0x8002A1CC size:0x690
void fn_8002A1CC(void) {
    return;
}

// .text:0x8002A85C size:0x40C
void fn_8002A85C(void) {
    return;
}

// .text:0x8002AC68 size:0x3AC
void fn_8002AC68(void) {
    return;
}

// .text:0x8002B014 size:0x3EC
void fn_8002B014(void) {
    return;
}

// .text:0x8002B400 size:0x3F8
void fn_8002B400(void) {
    return;
}

// .text:0x8002B7F8 size:0x48C
void fn_8002B7F8(void) {
    return;
}

// .text:0x8002BC84 size:0x64C
void fn_8002BC84(void) {
    return;
}

// .text:0x8002C2D0 size:0x29C
void fn_8002C2D0(void) {
    return;
}

// .text:0x8002C56C size:0x864
void fn_8002C56C(void) {
    return;
}

// .text:0x8002CDD0 size:0x7C
void fn_8002CDD0(void) {
    return;
}

// .text:0x8002CE4C size:0x9E0
void fn_8002CE4C(void) {
    return;
}

// .text:0x8002D82C size:0x43C
void fn_8002D82C(void) {
    return;
}

// .text:0x8002DC68 size:0x7C
void fn_8002DC68(void) {
    return;
}

// .text:0x8002DCE4 size:0x6F8
void fn_8002DCE4(void) {
    return;
}

// .text:0x8002E3DC size:0x44C
void fn_8002E3DC(void) {
    return;
}

// .text:0x8002E828 size:0x478
void fn_8002E828(void) {
    return;
}

// .text:0x8002ECA0 size:0x50C
void fn_8002ECA0(void) {
    return;
}

// .text:0x8002F1AC size:0xAC
void fn_8002F1AC(void) {
    return;
}

// .text:0x8002F258 size:0x39C
void fn_8002F258(void) {
    return;
}

// .text:0x8002F5F4 size:0x408
void fn_8002F5F4(void) {
    return;
}

// .text:0x8002F9FC size:0x3BC
void fn_8002F9FC(void) {
    return;
}

// .text:0x8002FDB8 size:0x6B8
void fn_8002FDB8(void) {
    return;
}

// .text:0x80030470 size:0x2B0
void fn_80030470(void) {
    return;
}

// .text:0x80030720 size:0x668
void fn_80030720(void) {
    return;
}

// .text:0x80030D88 size:0x2AC
void fn_80030D88(void) {
    return;
}

// .text:0x80031034 size:0x790
void fn_80031034(void) {
    return;
}

// .text:0x800317C4 size:0x4E0
void fn_800317C4(void) {
    return;
}

// .text:0x80031CA4 size:0x290
void fn_80031CA4(void) {
    return;
}

// .text:0x80031F34 size:0x104
void fn_80031F34(void) {
    return;
}

// .text:0x80032038 size:0x2C
s32 fn_80032038(const void* a, const void* b) {
    if (((const ParticleSortEntry*)a)->z > ((const ParticleSortEntry*)b)->z) {
        return 1;
    }
    if (((const ParticleSortEntry*)a)->z < ((const ParticleSortEntry*)b)->z) {
        return -1;
    }
    return 0;
}

// .text:0x80032064 size:0x220
void fn_80032064(void) {
    return;
}

// .text:0x80032284 size:0x268
void fn_80032284(void) {
    return;
}

// .text:0x800324EC size:0x3F4
void fn_800324EC(void) {
    return;
}

// .text:0x800328E0 size:0x7EC
void fn_800328E0(void) {
    return;
}

// .text:0x800330CC size:0x1EC
void fn_800330CC(void) {
    return;
}

// .text:0x800332B8 size:0x304
void fn_800332B8(void) {
    return;
}

// .text:0x800335BC size:0x30
f32 fn_800335BC(s32 angle) {
    s32 i = __abs(angle) & 0x7FF;
    if (i >= 0x401) {
        i = 0x800 - i;
    }
    return lbl_8017ED68[i];
}

// .text:0x800335EC size:0x34
f32 fn_800335EC(s32 angle) {
    s32 i = __abs(angle + 0x600) & 0x7FF;
    if (i >= 0x401) {
        i = 0x800 - i;
    }
    return lbl_8017ED68[i];
}

// .text:0x80033620 size:0x174
void fn_80033620(void) {
    return;
}

// .text:0x80033794 size:0x38
void fn_80033794(Particle* list) {
    FreeParticles(list);
}

// .text:0x800337CC size:0x90
void fn_800337CC(void) {
    return;
}

// .text:0x8003385C size:0xCC
void pitchingMachinePitching(void) {
    return;
}

// .text:0x80033928 size:0x3C
s32 fn_80033928(u8 type) {
    Emitter* e;
    for (e = EMITTER_HEAD->next; e != NULL; e = e->next) {
        if (e->type == type) {
            return 1;
        }
    }
    return 0;
}

// .text:0x80033964 size:0x8C
void fn_80033964(void) {
    return;
}

// .text:0x800339F0 size:0x34
Emitter* fn_800339F0(Emitter* after, u8 type) {
    return FindEmitter(after, type);
}

// .text:0x80033A24 size:0x134
void fn_80033A24(void) {
    return;
}

// .text:0x80033B58 size:0x170
void fn_80033B58(void) {
    return;
}

// .text:0x80033CC8 size:0x29C
void fn_80033CC8(void) {
    return;
}

// .text:0x80033F64 size:0xD8
void fn_80033F64(void) {
    return;
}

// .text:0x8003403C size:0xB8
void fn_8003403C(void) {
    return;
}

// .text:0x800340F4 size:0x2C
void fn_800340F4(Mtx m) {
    PSMTXCopy(lbl_8017FF78, m);
}

// .text:0x80034120 size:0x2C
void fn_80034120(void) {
    return;
}

// .text:0x8003414C size:0xD4
void fn_8003414C(void) {
    return;
}

// .text:0x80034220 size:0x30C
void minigamesSetSomePointers(void) {
    return;
}

// .text:0x8003452C size:0x39C
void minigamesGXStuff(void) {
    return;
}

// .text:0x800348C8 size:0x304
void minigamesSetSomePointers2(void) {
    return;
}

// .text:0x80034BCC size:0x120
void fn_80034BCC(void) {
    return;
}

// .text:0x80034CEC size:0x134
void fn_80034CEC(void) {
    return;
}

// .text:0x80034E20 size:0x130
void fn_80034E20(void) {
    return;
}
