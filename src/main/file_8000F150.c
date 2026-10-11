#include "main/file_8000F150.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"

extern u16 lbl_80366218[];
extern TexArchive* lbl_803CBBE8;
extern TexArchive lbl_800E9920;
extern GXColor lbl_803CB784;
extern u32 lbl_803CB788;
extern u32 lbl_803CB780;
extern void GXSetTexCoordScaleManually(GXTexCoordID coord, GXBool enable, u16 ss, u16 ts);

typedef struct TextDisplayList {
    /*0x0*/ u32 size;
    /*0x4*/ u32 width;  // in 9-pixel cells
    /*0x8*/ u32 height; // in 18-pixel cells
} TextDisplayList;

// This file's .data (0x800E8F60-0x800EE6A0). The original code reaches all of it
// from one base, so it is declared as one block here.
typedef struct TextStatics {
    /*0x0000*/ u8 glyphWidths[101][4];      // [glyph][fontSize]
    /*0x0194*/ u8 glyphWidthsExt[0x1FB][4]; // [glyph][fontSize]
    /*0x0980*/ u32 colors[10];
    /*0x09A8*/ u8 _09A8[0x18];              // lbl_800E9908
    /*0x09C0*/ u8 texArchive[0x3060];       // lbl_800E9920
    /*0x3A20*/ s16 positions[0x440 / 2];
    /*0x3E60*/ u16 texCoords[0x1820 / 2];
    /*0x5680*/ void* displayLists[12];
    /*0x56B0*/ TextDisplayList dlInfo[12];
} TextStatics;
extern TextStatics lbl_800E8F60;
extern u32 lbl_803CBC18;
extern ActorMgr lbl_8036E548;
extern void fn_8001BA44(s32 slot, s16 charId, u8 a, u8 b, s32 c, u8 d, u8 e);
extern void fn_800B2BA8(ActorModel* model, u16 anim, ActorModel* source, u16 sourceAnim);
extern void fn_8004B6EC(ActorMgrActor* actor, ActorModel** model);
extern void fn_8004B7F4(ActorMgrActor* actor, ActorModel** model);
extern void fn_8004BAEC(ActorMgrActor* actor, ActorModel** model);
extern void fn_8005240C(ActorMgrActor* actor, ActorModel** model);

typedef struct FogSetting {
    /*0x0*/ u8 _00[0x8];
    /*0x8*/ s32 value;
} FogSetting;
extern FogSetting lbl_800E9908[];
extern u8 lbl_803CBBC0;
extern u8 lbl_803CB760[5];
extern void fn_800A7D4C(s32, void*);

// NONMATCHING 89%: the original keeps this file's .data base (lbl_800E8F60) in r31; that needs the data defined in this TU
// .text:0x8000F150 size:0x298
#if NONMATCHING
void fn_8000F150(TextWindow* window) {
    Mtx44 proj;
    Mtx mv;
    TextDisplayList* dl;

    GXSetCopyClear(lbl_803CB784, lbl_803CB788);
    C_MTXOrtho(proj, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 2.0f);
    dl = &lbl_800E8F60.dlInfo[window->size];
    PSMTXTrans(mv, (640 - dl->width * 9) >> 1, (448 - dl->height * 18) >> 1, 0.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(mv, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 10);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, 0x400, 0x400);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    SetDisplayStateTexture(TEX_ARCHIVE_OBJ(lbl_803CBBE8, 0), 0, 0);
    GXSetArray(GX_VA_POS, lbl_800E8F60.positions, 6);
    GXSetArray(GX_VA_CLR0, &lbl_803CB780, 4);
    GXSetArray(GX_VA_TEX0, lbl_800E8F60.texCoords, 4);
    GXCallDisplayList(lbl_800E8F60.displayLists[window->size], lbl_800E8F60.dlInfo[window->size].size);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0x400, 0x400);
}
#endif

// .text:0x8000F3E8 size:0xA4
void fn_8000F3E8(s32 arg) {
    FogSetting* f = &lbl_800E9908[lbl_803CBBC0];
    switch (arg) {
    case -1:
        f->value = lbl_803CB760[4];
        break;
    case 4:
        f->value = lbl_803CB760[1];
        break;
    case 5:
        f->value = lbl_803CB760[0];
        break;
    case 6:
        f->value = lbl_803CB760[2];
        break;
    case 11:
        f->value = lbl_803CB760[3];
        break;
    }
    fn_800A7D4C(0, f);
}

// .text:0x8000F48C size:0x2C
void somethingSetTexturePointer(void) {
    lbl_803CBBE8 = &lbl_800E9920;
    convertTextureHeader(&lbl_800E9920);
}

// .text:0x8000F4B8 size:0x7C
void fn_8000F4B8(s32 a, s32 b, s32 c, s32 d) {
    lbl_80366B18.padMask = 0;
    if (a >= 0) {
        lbl_80366B18.padMask = 1 << a;
    }
    if (b >= 0) {
        lbl_80366B18.padMask |= 1 << b;
    }
    if (c >= 0) {
        lbl_80366B18.padMask |= 1 << c;
    }
    if (d >= 0) {
        lbl_80366B18.padMask |= 1 << d;
    }
}

// .text:0x8000F534 size:0x3C0
void fn_8000F534(void* object, s32 visible) {
    return;
}

// .text:0x8000F8F4 size:0x94
void fn_8000F8F4(LayoutGroup* group) {
    s32 i;
    s32 j;
    u16 start = group->start;
    for (i = 0; i < group->count; i++) {
        LayoutObj* obj = lbl_80371C30[start + (u32)i].obj;
        if (obj != NULL && (obj->flags & 4)) {
            for (j = 0; j < 30; j++) {
                if (lbl_80366B18.owners[j].object == lbl_80371C30[start + (u32)i].obj) {
                    lbl_80366B18.owners[j].object = NULL;
                    break;
                }
            }
        }
    }
}

// .text:0x8000F988 size:0x114
s32 fn_8000F988(LayoutGroup* group, s32 index, u16 arg2, s32 table, s32 msg, s32 shadow) {
    s32 i;
    LayoutObj* obj = lbl_80371C30[group->start + index].obj;
    obj->flags |= 4;
    if (shadow != 0) {
        obj->flags |= 8;
    }
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.owners[i].object == NULL) {
            lbl_80366B18.owners[i].object = obj;
            lbl_80366B18.owners[i]._06 = arg2;
            lbl_80366B18.owners[i].entry = fn_8000FF04(table, msg, 0, 0, obj->layer, -1, 0);
            if (obj->_00 != NULL) {
                lbl_80366B18.entries[lbl_80366B18.owners[i].entry].mtx = obj->mtx;
            } else {
                lbl_80366B18.entries[lbl_80366B18.owners[i].entry].mtx = NULL;
            }
            return lbl_80366B18.owners[i].entry;
        }
    }
    return -1;
}

// .text:0x8000FA9C size:0x2B8
s32 fn_8000FA9C(s32 index) {
    return 0;
}

// .text:0x8000FD54 size:0x24
void fn_8000FD54(s32 index, s16 a, s16 b, s16 c, s16 d) {
    TextEntry* e = &lbl_80366B18.entries[index];
    e->strings[0] = a;
    e->strings[1] = b;
    e->strings[2] = c;
    e->strings[3] = d;
}

// .text:0x8000FD78 size:0x24
void fn_8000FD78(s32 index, s16 a, s16 b, s16 c, s16 d) {
    TextEntry* e = &lbl_80366B18.entries[index];
    e->numbers[0] = a;
    e->numbers[1] = b;
    e->numbers[2] = c;
    e->numbers[3] = d;
}

// .text:0x8000FD9C size:0x6C
void fn_8000FD9C(s32 index, s32 speed, s32 limit) {
    if (speed == 0) {
        lbl_80366B18.entries[index].charLimit = -1;
        lbl_80366B18.entries[index].typeSpeed = 0;
        lbl_80366B18.entries[index].typeTimer = 0;
        return;
    }
    if (limit >= 0) {
        lbl_80366B18.entries[index].charLimit = limit;
    }
    lbl_80366B18.entries[index].typeSpeed = speed;
    lbl_80366B18.entries[index].typeTimer = 0;
}

// .text:0x8000FE08 size:0x4C
void fn_8000FE08(s32 index, s32 table, s32 msg) {
    TextEntry* e;
    u16* text = lbl_80366B18.tables[table]->msgs[msg];
    e = &lbl_80366B18.entries[index];
    e->text = text;
    if (e->charLimit >= 0) {
        e->charLimit = 0;
        e->finished = 0;
        e->_35 = 0;
    }
}

// .text:0x8000FE54 size:0x94
void fn_8000FE54(void) {
    s32 i;
    for (i = 0; i < 30; i++) {
        lbl_80366B18.entries[i].state = 0;
    }
}

// .text:0x8000FEE8 size:0x1C
void fn_8000FEE8(s32 index) {
    lbl_80366B18.entries[index].state = 0;
}

// NONMATCHING 99%: two address computations (table/msg slwi) scheduled in the other order
// .text:0x8000FF04 size:0x1A0
#if NONMATCHING
s32 fn_8000FF04(s32 table, s32 msg, s16 x, s16 y, u8 layer, u32 color, u8 fontSize) {
    s32 i;
    TextEntry* e;
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.entries[i].state == 0) {
            break;
        }
    }
    if (i >= 30) {
        return 0;
    }
    e = &lbl_80366B18.entries[i];
    e->text = lbl_80366B18.tables[table]->msgs[msg];
    e->x = x;
    e->y = y;
    e->layer = layer;
    e->state = 2;
    e->fontSize = fontSize;
    e->color = color;
    e->numbers[0] = 0;
    e->numbers[1] = 0;
    e->numbers[2] = 0;
    e->numbers[3] = 0;
    e->charSpacing = 0;
    e->lineSpacing = 2;
    e->hAlign = 0;
    e->vAlign = 0;
    e->mtx = NULL;
    e->charLimit = -1;
    e->typeSpeed = 0;
    e->typeTimer = 0;
    e->finished = 0;
    e->_33 = 0;
    e->_35 = 0;
    e->_36 = 0;
    return i;
}
#endif

// .text:0x800100A4 size:0x3F4
void fn_800100A4(s32 x, s32 y, u16 s, u16 t, u16 w, u32 color, s32 kind, MtxPtr mtx) {
    return;
}

// .text:0x80010498 size:0xA94
#if NONMATCHING
void DrawText(s32 index) {
    return;
}
#endif

// .text:0x80010F2C size:0x74
void DrawTextOnCondition(s32 layer) {
    s32 i;
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.entries[i].state == 2 && layer == lbl_80366B18.entries[i].layer) {
            DrawText(i);
        }
    }
}

// NONMATCHING 96%: extra `mr` when setting up dst before the copy loop
// .text:0x80010FA0 size:0x60
#if NONMATCHING
void fn_80010FA0(void) {
    MsgTable* t = lbl_80366B18.tables[0];
    u16* dst = lbl_80366218;
    u16* src;
    lbl_80366B18.msgs = t->msgs;
    lbl_80366B18._7EC = t->msgs[1];
    lbl_80366B18._7F0 = t->msgs[2];
    lbl_80366B18._7F8 = t->msgs[6];
    lbl_80366B18._7F4 = t->msgs[5];
    src = lbl_80366B18.msgs[7];
    for (;;) {
        u16 c = *src;
        if (c == 0x4001) {
            return;
        }
        *dst = c;
        src++;
        dst++;
    }
}
#endif

// NONMATCHING 96%: saved regs r30/r31 swapped (loop counter vs. lbl_80366B18 base)
// .text:0x80011000 size:0x140
#if NONMATCHING
void fn_80011000(void) {
    s32 i;
    lbl_80366B18.fontTex[0] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[0]);
    lbl_80366B18.fontTex[1] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[1]);
    lbl_80366B18.fontTex[2] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[2]);
    lbl_80366B18.fontTex[3] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[3]);
    for (i = 0; i < 4; i++) {
        convertTextureHeader(lbl_80366B18.fontTex[i]);
        lbl_80366B18.fontTexObj[i] = TEX_ARCHIVE_OBJ(lbl_80366B18.fontTex[i], 0);
    }
    convertTextureHeader(lbl_80366B18.iconArchive);
    for (i = 0; i < 9; i++) {
        lbl_80366B18.iconTexObj[i] = TEX_ARCHIVE_OBJ(lbl_80366B18.iconArchive, i);
    }
    lbl_80366B18.scaleX = 1;
    lbl_80366B18.scaleY = 1;
}
#endif

// .text:0x80011140 size:0x74
void fn_80011140(void) {
    s32 i;
    for (i = 0; i < 30; i++) {
        lbl_80366B18.entries[i].state = 0;
        lbl_80366B18.owners[i].object = NULL;
    }
    lbl_80366B18.padMask = 0;
}

// .text:0x800111B4 size:0x24
void fn_800111B4(MsgTable* table) {
    s32 n = table->count;
    u16** p = table->msgs;
    do {
        *p = (u16*)((u32)*p + (u32)table); // file offset -> pointer (32-bit data)
        p++;
    } while (--n);
}

// .text:0x800111D8 size:0x24
ActorModel** fn_800111D8(ActorMgrActor* actor) {
    return &lbl_8036E548.models[actor->modelIndex].model;
}

// NONMATCHING 99%: original keeps &actors[i] (addi 0xc04) in r5 and copies it to r31; ours folds the offset
// .text:0x800111FC size:0x15C
#if NONMATCHING
ActorMgrActor* fn_800111FC(ActorMgrActor* actor, s32 second) {
    s32 slot;
    ActorMgrActor* next;
    if (g_d_GameSettings.GameModeSelected != 6) {
        return actor;
    }
    slot = actor->modelIndex % 4;
    lbl_8036E548.actors[slot + 4]._25D = 0;
    lbl_8036E548.actors[slot]._25D = 0;
    next = &lbl_8036E548.actors[slot + ((second != 0) << 2)];
    lbl_8036E548.active[slot] = next;
    if (next->modelIndex != actor->modelIndex) {
        fn_8001BA44(slot, actor->_062, actor->_25F, actor->_262, 0, actor->_265, actor->_269);
        next->_064 = actor->_064;
        next->_06C = actor->_06C;
        next->_25E = actor->_25E;
        next->_260 = actor->_260;
        next->_263 = actor->_263;
        next->_266 = actor->_266;
        next->_26A = actor->_26A;
        next->_26D = actor->_26D;
        next->_066 = actor->_066;
        next->_06E = actor->_06E;
        next->_261 = actor->_261;
        next->_264 = actor->_264;
        next->_267 = actor->_267;
        next->_26B = actor->_26B;
        next->_26E = actor->_26E;
    }
    return next;
}
#endif

// .text:0x80011358 size:0x110
void fn_80011358(s32 index, s32 kind) {
    ActorMgrActor* actor;
    ActorModelSlot* models;
    ActorModelSlot* models2;
    ActorModel* model;
    ActorModel** target;
    u16 anim;
    s32 i;
    if (index < 0 || index >= 13) {
        return;
    }
    actor = lbl_8036E548.active[index];
    if (actor == NULL || (models = lbl_8036E548.models) == NULL || (models2 = lbl_8036E548.models2) == NULL) {
        return;
    }
    anim = actor->anim;
    if (anim == 0xFFFF) {
        return;
    }
    if (kind < 0 || kind >= 5) {
        kind = 4;
    }
    target = &models[actor->modelIndex].model;
    if (kind == 4) {
        fn_800B2BA8(*target, anim, NULL, 0);
        return;
    }
    model = models2[kind + 21].model;
    for (i = 0; i < model->animCount; i++) {
        if (model->anims[i]->_14 != NULL) {
            fn_800B2BA8(*target, anim, model, i);
            return;
        }
    }
}

// .text:0x80011468 size:0x108
void fn_80011468(void) {
    s32 i;
    for (i = 0; i < 13; i++) {
        ActorMgrActor* actor = lbl_8036E548.active[i];
        if (actor != NULL) {
            ActorModel** model = &lbl_8036E548.models[actor->modelIndex].model;
            switch (actor->kind) {
            case 19:
                fn_8004B6EC(actor, model);
                break;
            case 40:
            case 41:
                fn_8004B7F4(actor, model);
                break;
            case 38:
                (*model)->_99 = 1;
            case 18:
                fn_8004BAEC(actor, model);
                break;
            case 14:
            case 37:
                fn_8005240C(actor, model);
                break;
            case 6:
            case 10:
            case 12:
            case 24:
            case 25:
            case 26:
            case 42:
                (*model)->_99 = 1;
                break;
            case 20:
            case 43:
                if (actor->_062 == 0x40) {
                    (*model)->_99 = 0;
                } else {
                    (*model)->_99 = 1;
                }
                break;
            }
        }
    }
}

// fn_80011578, size:0x50
void fn_80011578(void) {
    s8 i = 0;
    s32 n;
    for (n = 13; n != 0; n--) {
        if (i >= 0 && i < 13) {
            ActorMgrActor* actor = lbl_8036E548.active[(u32)i];
            if (actor != NULL) {
                actor->_05C = 0;
            }
        }
        i++;
    }
}

// fn_800115C8, size:0x3C
void fn_800115C8(s8 index) {
    if (index >= 0 && index < 13) {
        ActorMgrActor* actor = lbl_8036E548.active[index];
        if (actor != NULL) {
            actor->_05C = 0;
        }
    }
}

// fn_80011570, size:0x8
u32 fn_80011570(void) {
    return lbl_803CBC18;
}

// fn_80011604, size:0x3C
void fn_80011604(s8 index, u32 value) {
    ActorMgrActor* actor;
    if (index < 0 || index >= 13) {
        return;
    }
    actor = lbl_8036E548.active[index];
    if (actor != NULL) {
        actor->_05C = value;
    }
}
