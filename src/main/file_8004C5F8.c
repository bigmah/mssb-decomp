#include "main/file_8004C5F8.h"
#include "main/file_8000F150.h"
#include "main/file_8004B284.h"
#include "main/file_80008E00.h"
#include "Dolphin/gx.h"
#include "musyx/musyx.h"

extern LayoutGroup* lbl_803CC1B8;
extern int rand(void);
extern CharTableEntry lbl_800E8558[54];
extern u8 lbl_800EFBA4[];
extern u8 lbl_800FDE84[];
extern u8 lbl_800FE5D4[];
extern u8 lbl_800FE930[][6];
extern camera_803c639c_s lbl_803C639C[4];
extern s32 lbl_803CBD14;
extern s32 lbl_803CB880;

void fn_800521B0(void);
extern f32 fn_800335BC(s32 angle);
extern f32 fn_800335EC(s32 angle);
extern BOOL getAnimRelatedCoordinates(int charIdx, int joint, Vec* out);
extern void fn_80030D88(Vec* pos, Vec* dir, void* params, int kind);
extern SwingFx lbl_800FC890;
extern BatFxTables lbl_800FC0FC;
extern s32 lbl_803CBD0C;
extern u8 lbl_803CBBC0;
extern f32 fn_800B4C40(s32 id);
extern s16 lbl_800FEB08[5][4];
extern DialogTables lbl_800FEAAC;
extern u8 lbl_800FE93C[];
extern u8 lbl_800FE924[][6];
extern u8 lbl_800FE5C8[];
extern u8 lbl_800E854C[];
extern s32 fn_80024C04(s32 index);
extern u8 lbl_800FCA60[];
extern u8 lbl_800FDE60[];
extern u8 lbl_80361B20[];
extern u8 starMissionCompletionTracker[]; // TODO type (ChallengeTrackingStruct[])
// Sub-tables inside lbl_800FE5D4 / lbl_800FE93C (no symbols of their own).
#define lbl_800FE5D4_colOrder ((u8(*)[6])&lbl_800FE5D4[0xC])
#define lbl_800FE93C_alts ((u8(*)[5])lbl_800FE93C)
#define lbl_800FDE84_colOrder ((u8(*)[12])&lbl_800FDE84[0x34])
extern u16 lbl_803CB870[];
extern void fn_80034E20(void* group, void* desc);
extern s32 fn_80036214(void* owner, s32 idx, u32 track, u32 frame);

// .text:0x8004C5F8 size:0x404
// NONMATCHING 93%: register allocation (saved-register order)
#if NONMATCHING
void fn_8004C5F8(CharActor* actor, s32 unused, u32 kind) {
    SwingFx* tbl = &lbl_800FC890;
    Vec dir;
    Vec pos;
    s32 hasBat;
    EffectParams* fx;
    EffectParamsB* trail;

    if (lbl_80366158._28 == 1) {
        return;
    }
    dir.x = fn_800335EC((s32)(0.5f + 1024.0f * actor->angle / 3.1415927f));
    dir.z = fn_800335BC((s32)(0.5f + 1024.0f * actor->angle / 3.1415927f));
    dir.y = 0.0f;
    hasBat = actor->flags & 1;
    switch (kind) {
    case 1:
    case 3:
    case 7:
        if (hasBat) {
            trail = &tbl->trails[1];
            fx = &tbl->params[1];
            if (actor->_27A != 0) {
                fx = &tbl->params[2];
            }
            fx->stamp = lbl_803CBD0C;
            fx->rgb = (lbl_800FC0FC.colors[kind].r << 24) | ((lbl_800FC0FC.colors[kind].g & 0xFF) << 16) |
                      (lbl_800FC0FC.colors[kind].b << 8);
        } else {
            trail = &tbl->trails[0];
        }
        trail->stamp = lbl_803CBD0C;
        if (hasBat && actor->_27A != 0) {
            actor->_27A = 0;
            if (lbl_803CBBC0 != 0) {
                getAnimRelatedCoordinates(actor->_254, 0x1E, &pos);
                pos.y = 0.0f;
                fn_80030D88(&pos, &dir, fx, 5);
            } else {
                getAnimRelatedCoordinates(actor->_254, 0x22, &pos);
                pos.y = 0.0f;
                fn_80030D88(&pos, &dir, fx, 5);
            }
        }
        if ((actor->flags & 0xA) == 2) {
            getAnimRelatedCoordinates(actor->_254, 0x1E, &pos);
            pos.y = 0.0f;
            if (hasBat && actor->_27A == 0) {
                fn_80030D88(&pos, &dir, fx, 5);
            }
            fn_8002955C(&pos, &dir, trail);
        }
        if ((actor->flags & 0x14) == 4) {
            getAnimRelatedCoordinates(actor->_254, 0x22, &pos);
            pos.y = 0.0f;
            if (hasBat && actor->_27A == 0) {
                fn_80030D88(&pos, &dir, fx, 5);
            }
            fn_8002955C(&pos, &dir, trail);
        }
        break;
    case 0:
    case 2:
    case 5:
    case 6:
    case 8:
    case 10:
    case 11:
    case 12:
        if (!hasBat) {
            fx = &tbl->params[0];
        } else if (actor->_27A != 0) {
            fx = &tbl->params[2];
        } else {
            fx = &tbl->params[1];
        }
        fx->stamp = lbl_803CBD0C;
        fx->rgb = (lbl_800FC0FC.colors[kind].r << 24) | ((lbl_800FC0FC.colors[kind].g & 0xFF) << 16) |
                  (lbl_800FC0FC.colors[kind].b << 8);
        if (hasBat && actor->_27A != 0) {
            actor->_27A = 0;
            if (lbl_803CBBC0 != 0) {
                getAnimRelatedCoordinates(actor->_254, 0x1E, &pos);
                pos.y = 0.0f;
                fn_80030D88(&pos, &dir, fx, 5);
            } else {
                getAnimRelatedCoordinates(actor->_254, 0x22, &pos);
                pos.y = 0.0f;
                fn_80030D88(&pos, &dir, fx, 5);
            }
            break;
        }
        if ((actor->flags & 0xA) == 2) {
            getAnimRelatedCoordinates(actor->_254, 0x1E, &pos);
            pos.y = 0.0f;
            fn_80030D88(&pos, &dir, fx, 5);
        }
        if ((actor->flags & 0x14) == 4) {
            getAnimRelatedCoordinates(actor->_254, 0x22, &pos);
            pos.y = 0.0f;
            fn_80030D88(&pos, &dir, fx, 5);
        }
        break;
    }
}
#endif

extern s32 lbl_803CB878;

extern s32 lbl_803CB874;

// fn_8004C9FC, size:0xC
void fn_8004C9FC(void) {
    lbl_803CB874 = lbl_803CB878;
}

// fn_8004CA08, size:0xC
void fn_8004CA08(u32 value) {
    lbl_803CB878 = value;
    lbl_803CB874 = value;
}

// .text:0x8004CA14 size:0x34
void fn_8004CA14(s32 table, s32 msg) {
    fn_8000FE08(lbl_803C5F74.textIdx, table, msg);
}

// .text:0x8004CA48 size:0x24
void fn_8004CA48(s16 a, s16 b, s16 c, s16 d) {
    lbl_803C5F74.hasTextRect2 = 1;
    lbl_803C5F74.textRect2[0] = a;
    lbl_803C5F74.textRect2[1] = b;
    lbl_803C5F74.textRect2[2] = c;
    lbl_803C5F74.textRect2[3] = d;
}

// .text:0x8004CA6C size:0x1AC
s32 fn_8004CA6C(u16 buttons) {
    s32 timedOut;
    if (lbl_803C5F74.state == 4) {
        return lbl_803C5F74.cursor == 0 ? 3 : 4;
    } else if (lbl_803C5F74.state == 2) {
        if (buttons != 0) {
            lbl_803CB874 = lbl_803CB878;
        }
        if (lbl_803CB874 > 0) {
            lbl_803CB874--;
        }
        timedOut = lbl_803CB874 == 0;
        if (timedOut) {
            buttons |= 0x100;
        }
        if (buttons & 0x100) {
            if (!timedOut) {
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
            if (lbl_803C5F74.cursor == 0) {
                return 1;
            }
            return 2;
        }
        if (buttons & 0x200) {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            if (lbl_803C5F74.cursor == 0) {
                lbl_803C5F74.cursor = 1;
            } else {
                return 2;
            }
        } else if ((buttons & 1) && lbl_803C5F74.cursor == 1) {
            lbl_803C5F74.cursor = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if ((buttons & 2) && lbl_803C5F74.cursor == 0) {
            lbl_803C5F74.cursor = 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    }
    return 0;
}

// fn_8004CC18, size:0x14
void fn_8004CC18(void) {
    lbl_803C5F74.state = 4;
}

// fn_8004CC2C, size:0x20
void fn_8004CC2C(void) {
    if (lbl_803C5F74.state != 4) {
        lbl_803C5F74.state = 3;
    }
}

// fn_8004CC4C, size:0x74
void fn_8004CC4C(u8 first, u8 second, u8 third, s32 selection, s16 value) {
    ConfirmDialog* dlg = &lbl_803C5F74;
    if (dlg->active == 0) {
        dlg->kind = first;
        dlg->cursor = third;
        dlg->state = 0;
        dlg->_04 = second;
        dlg->_1E = 0;
        dlg->textRect[0] = 0;
        dlg->textRect2[0] = -1;
        dlg->textRect[1] = 0;
        dlg->textRect2[1] = -1;
        dlg->textRect[2] = 0;
        dlg->textRect2[2] = -1;
        dlg->textRect[3] = 0;
        dlg->textRect2[3] = -1;
        dlg->hasTextRect = 0;
        dlg->hasTextRect2 = 0;
        if (selection >= 0) {
            dlg->table = selection;
            dlg->msg = value;
            return;
        }
        dlg->table = -1;
    }
}

// .text:0x8004CCC0 size:0x430
// NONMATCHING 99%: scheduling of the lbl_803C5F74/lbl_80366B18 address loads after fn_8000F988
#if NONMATCHING
void fn_8004CCC0(void) {
    LayoutGroup* task = lbl_803CC1B8;
    LayoutObj* obj;
    s32 done;
    s32 frame;
    u16 idx;
    if (lbl_803C5F74.state == 0) {
        lbl_803C5F74.state = 1;
        if (lbl_803C5F74.table >= 0) {
            idx = fn_8000F988(task, 8, lbl_800FEAAC.layouts[lbl_803C5F74.kind].msgId, lbl_803C5F74.table, lbl_803C5F74.msg, 0);
            lbl_80366B18.entries[idx].hAlign = 1;
            lbl_803C5F74.textIdx = idx;
            lbl_80366B18.entries[idx].vAlign = 1;
            if (lbl_803C5F74.hasTextRect != 0) {
                fn_8000FD78(idx, lbl_803C5F74.textRect[0], lbl_803C5F74.textRect[1], lbl_803C5F74.textRect[2], lbl_803C5F74.textRect[3]);
            }
            if (lbl_803C5F74.hasTextRect2 != 0) {
                fn_8000FD54(lbl_803C5F74.textIdx, lbl_803C5F74.textRect2[0], lbl_803C5F74.textRect2[1], lbl_803C5F74.textRect2[2], lbl_803C5F74.textRect2[3]);
            }
        }
    } else if (lbl_803C5F74.state == 1) {
        done = 0;
        if (lbl_803C5F74.kind == 7 || lbl_803C5F74.kind == 8 || lbl_803C5F74.kind == 10) {
            if ((s32)(lbl_80371C30[task->start + 1].obj->_5C >> 16) >= 3) {
                done |= 1;
            }
        } else {
            obj = lbl_80371C30[task->start + 3].obj;
            frame = obj->_5C >> 16;
            if (lbl_803C5F74.cursor == 0) {
                if (frame >= 5) {
                    done |= 1;
                    obj->_68 = 0;
                }
            } else if (frame <= 10) {
                done |= 1;
                obj->_68 = 0;
            }
        }
        if (done == 1) {
            lbl_803C5F74.state = 2;
        }
    } else if (lbl_803C5F74.state == 2) {
        if (lbl_803C5F74.kind != 7 && lbl_803C5F74.kind != 8 && lbl_803C5F74.kind != 10) {
            obj = lbl_80371C30[task->start + 3].obj;
            frame = obj->_5C >> 16;
            if (lbl_803C5F74.cursor == 0) {
                if (frame <= 5) {
                    obj->_68 = 0;
                } else {
                    obj->_68 = 4;
                }
            } else if (frame >= 10) {
                obj->_68 = 0;
            } else {
                obj->_68 = 1;
            }
        }
    } else if (lbl_803C5F74.state == 3) {
        if (lbl_803C5F74._04 != 0) {
            lbl_80371C30[task->start].obj->_68 = 4;
        }
        lbl_80371C30[task->start + 1].obj->_68 = 4;
        if (lbl_803C5F74.kind == 7 || lbl_803C5F74.kind == 8 || lbl_803C5F74.kind == 10 || lbl_803C5F74.kind == 9) {
            done = 0;
            if ((s32)(lbl_80371C30[task->start + 1].obj->_5C >> 16) <= 0) {
                done |= 1;
            }
        } else {
            done = 0;
            obj = lbl_80371C30[task->start + 3].obj;
            frame = obj->_5C >> 16;
            if (lbl_803C5F74.cursor == 0) {
                obj->_68 = 4;
                if (frame <= 0) {
                    done |= 1;
                }
            } else {
                obj->_68 = 1;
                if (frame >= 15) {
                    done |= 1;
                }
            }
        }
        if (done == 1) {
            goto close;
        }
    } else if (lbl_803C5F74.state == 4) {
        goto close;
    }
    if (lbl_803C5F74._1D != 0) {
        lbl_80371C30[task->start + 6].obj->flags |= 2;
        lbl_80371C30[task->start + 6].obj->_68 = 1;
    } else {
        lbl_80371C30[task->start + 6].obj->flags &= ~2;
    }
    return;
close:
    if (lbl_803C5F74.table >= 0) {
        fn_8000FEE8(lbl_803C5F74.textIdx);
        fn_8000F8F4(task);
    }
    lbl_803C5F74.state = 4;
    lbl_803C5F74.active = 0;
    fn_800B0A14_removeQueue(fn_80034CEC(task));
    lbl_80366158._20 = 1;
}
#endif

// .text:0x8004D0F0 size:0x370
// NONMATCHING: the original addresses lbl_800FE93C/lbl_800FEAAC through one
// lbl_800FCA60 base (same-TU data; the .data split ends too early)
#if NONMATCHING
void fn_8004D0F0(void) {
    LayoutGroup* task = lbl_803CC1B8;
    if (lbl_803C5F74.active != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    lbl_803C5F74.active = 1;
    fn_80034E20(task, &lbl_800FE93C[0x30]);
    if (lbl_803C5F74._04 == 0) {
        lbl_80371C30[task->start].obj->flags &= ~2;
    }
    lbl_80371C30[task->start + 1].obj->_64 = lbl_800FEAAC.layouts[lbl_803C5F74.kind].anim0;
    lbl_80371C30[task->start + 2].obj->_64 = lbl_800FEAAC.layouts[lbl_803C5F74.kind].anim1;
    lbl_80371C30[task->start + 8].obj->_5C = lbl_800FEAAC.layouts[lbl_803C5F74.kind].msgId << 16;
    lbl_80371C30[task->start + 2].obj->_72 = lbl_800FEAAC.colors[lbl_803C5F74.kind][0];
    lbl_80371C30[task->start + 3].obj->_72 = lbl_800FEAAC.colors[lbl_803C5F74.kind][1];
    lbl_80371C30[task->start + 8].obj->_72 = lbl_800FEAAC.colors[lbl_803C5F74.kind][0];
    if (lbl_803C5F74._1E == 1) {
        lbl_80371C30[task->start + 3].obj->_64 = 0xE3;
    }
    if (lbl_803C5F74.cursor == 1) {
        lbl_80371C30[task->start + 3].obj->_5C = 15 << 16;
        lbl_80371C30[task->start + 3].obj->_68 = 4;
    }
    if (lbl_803C5F74.kind == 7 || lbl_803C5F74.kind == 10) {
        lbl_80371C30[task->start + 3].obj->flags &= ~2;
    }
    if (lbl_803C5F74.kind != 9) {
        lbl_80371C30[task->start + 4].obj->flags &= ~2;
        lbl_80371C30[task->start + 5].obj->flags &= ~2;
    } else {
        fn_800363D8(task, 4, 1, 0xCD, lbl_803C5F74.cursor);
        lbl_80371C30[task->start + 3].obj->flags &= ~2;
    }
    if (lbl_803C5F74.kind != 10) {
        lbl_80371C30[task->start + 6].obj->flags &= ~2;
        lbl_803C5F74._1D = 0;
    } else {
        lbl_803C5F74._1D = 1;
    }
    if (lbl_803C5F74._1D != 0) {
        sndFXStartEx(0x1C2, lbl_800EFBA4[11], 0x3F, 0);
    } else if (lbl_803C5F74.kind == 0 || (u8)(lbl_803C5F74.kind - 1) <= 4 || lbl_803C5F74.kind == 6) {
        sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
    }
    task->timer = 0;
    task->_1A = 0;
    lbl_803CC1B8->callback = fn_8004CCC0;
}
#endif

// .text:0x8004D460 size:0x90
void fn_8004D460(s32 byId, s32 entry0) {
    s32 entries[4];
    s32 p;
    s32 entry;
    entries[0] = entry0;
    for (p = 0; p < 1; p++) {
        if (lbl_803C6028.cursor[p] >= 0) {
            entry = entries[p];
            if (entry >= 0) {
                if (byId == 0) {
                    lbl_803C6028.cursor[p] = entry;
                } else {
                    s32 id = lbl_800E8558[entry].id;
                    u8* ids = lbl_800FE930[lbl_803C6028._8C];
                    s32 j;
                    for (j = 0; j < 0x24; ids++, j++) {
                        if (id == *ids) {
                            lbl_803C6028.cursor[p] = j;
                            break;
                        }
                    }
                }
            }
        }
    }
}

// .text:0x8004D4F0 size:0x8C
void fn_8004D4F0(s8 owner, s32 entry, s32 set) {
    s32 i;
    s32 id = lbl_800E8558[entry].id;
    u8* ids = lbl_800FE930[lbl_803C6028._8C];
    for (i = 0; i < 0x24; ids++, i++) {
        if (id == *ids) {
            if (set != 0) {
                lbl_803C6028.slotOwner[i] = owner;
            } else {
                lbl_803C6028.slotOwner[i] = -1;
            }
            return;
        }
    }
}

// .text:0x8004D57C size:0x3C0
// NONMATCHING 91%: our cursor wrap in the left/right loops becomes a branchless select
#if NONMATCHING
s16 fn_8004D57C(s32 unused, s32 pressed, u16 dirs) {
    s32 occ[0x24];
    s32 count;
    s32 k;
    s32 r;

    count = 5;
    if (lbl_803C6028._8C != 0) {
        count = 6;
    }
    lbl_803C6028._78[0] = 3;
    for (k = 0; k < 0x24; k++) {
        occ[k] = -1;
    }
    if (lbl_803C6028._7F[0] >= 0) {
        lbl_803C6028._7F[0]--;
        if (lbl_803C6028._7F[0] & 1) {
            r = rand() % count;
            for (k = 0; k < 12; k++) {
                if (occ[k] < 0) {
                    if (r == 0) {
                        lbl_803C6028.cursor[0] = k;
                        break;
                    }
                    r--;
                }
            }
        }
    } else if ((pressed & 0x20) && lbl_803C6028._7F[0] == -1) {
        lbl_803C6028._7F[0] = 30;
    } else if (dirs & 2) {
        do {
            if (lbl_803C6028.cursor[0] == count - 1) {
                lbl_803C6028.cursor[0] = 0;
            } else {
                lbl_803C6028.cursor[0]++;
            }
        } while (occ[lbl_803C6028.cursor[0]] >= 0);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (dirs & 1) {
        do {
            if (lbl_803C6028.cursor[0] == 0) {
                lbl_803C6028.cursor[0] = count - 1;
            } else {
                lbl_803C6028.cursor[0]--;
            }
        } while (occ[lbl_803C6028.cursor[0]] >= 0);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
    lbl_803C6028.charId[0] = lbl_800FE930[lbl_803C6028._8C][lbl_803C6028.cursor[0]];
    if (pressed & 0x40) {
        for (k = 0; k < 9; k++) {
            if (lbl_803C6028.charId[0] == lbl_800FE93C_alts[k][0]) {
                lbl_803C6028._83[k]++;
                if (lbl_803C6028._83[k] >= 5) {
                    lbl_803C6028._83[k] = 0;
                } else if (lbl_800FE93C_alts[k][lbl_803C6028._83[k]] == 0xFF) {
                    lbl_803C6028._83[k] = 0;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
    for (k = 0; k < 9; k++) {
        if (lbl_803C6028.charId[0] == lbl_800FE93C_alts[k][0]) {
            lbl_803C6028.charId[0] = lbl_800FE93C_alts[k][lbl_803C6028._83[k]];
        }
    }
    return lbl_803C6028.charId[0];
}
#endif

// .text:0x8004D93C size:0x54
s32 fn_8004D93C(s32 arg) {
    if (lbl_803C6028.state7E == 0) {
        if (arg != 0) {
            lbl_803C6028.state7E = 3;
        } else {
            lbl_803C6028.state7E = 1;
        }
    }
    if (lbl_803C6028.state7E == 2) {
        lbl_803C6028.state7E = 0;
        return 1;
    }
    return 0;
}

// .text:0x8004D990 size:0x200
// NONMATCHING 97%: the -1/-2 constants are loaded before the arg1 branch in the original
#if NONMATCHING
void fn_8004D990(s8 arg0, s32 arg1, u8 table) {
    RosterSelect* rs = &lbl_803C6028;
    s32 i;
    if (arg1 != 0) {
        for (i = 0; i < 4; i++) {
            rs->_78[i] = 0;
            rs->cursor[i] = -1;
            rs->_7F[i] = -1;
        }
    } else {
        for (i = 0; i < 4; i++) {
            rs->_78[i] = 0;
            rs->cursor[i] = -1;
            rs->_7F[i] = -2;
        }
    }
    for (i = 0; i < 9; i++) {
        rs->_83[i] = 0;
    }
    lbl_803C6028.cursor[0] = 0;
    lbl_803C6028._8D = arg0;
    lbl_803C6028._8C = table;
    for (i = 0; i < 4; i++) {
        if (rs->cursor[i] >= 0) {
            rs->charId[i] = lbl_800FE930[lbl_803C6028._8C][rs->cursor[i]];
        }
    }
    for (i = 0; i < 0x24; i++) {
        rs->slotOwner[i] = -1;
    }
}
#endif

// .text:0x8004DB90 size:0x75C
// NONMATCHING 91%: register allocation and frame size differ
#if NONMATCHING
void fn_8004DB90(void) {
    LayoutGroup* task;
    LayoutObj* title;
    LayoutObj* obj;
    u32 frame;
    s32 i;
    s32 j;
    s32 icon;
    s32 name;
    s32 bg;

    lbl_803C6028._92 = 0;
    task = lbl_803CC1B8;
    title = lbl_80371C30[task->start + 2].obj;
    frame = title->_5C >> 16;
    if (task->textIndex == 0) {
        if (frame == 30) {
            title->_68 = 0;
            task->textIndex = 1;
        }
    } else if (task->textIndex == 1) {
        lbl_803C6028._92 = 1;
        if (lbl_803C6028.state7E == 3) {
            goto finish;
        }
        if (lbl_803C6028.state7E == 1) {
            title->_68 = 4;
            lbl_80371C30[task->start + 1].obj->_68 = 4;
            task->textIndex = 2;
        }
    } else if (task->textIndex == 2) {
        if (frame <= 5) {
            goto finish;
        }
    }

    if (task->textIndex != 3) {
        for (i = 0; i < 6; i++) {
            if (lbl_803C6028._8C == 0 && i == 5) {
                break;
            }
            icon = i + 0xB;
            bg = i + 3;
            name = i + 0x11;
            if (task->textIndex == 0) {
                obj = lbl_80371C30[task->start + icon].obj;
                if ((obj->_5C >> 16) >= 5) {
                    obj->_68 = 0;
                }
            } else if (lbl_803C6028.slotOwner[i] >= 0) {
                lbl_80371C30[task->start + icon].obj->_68 = 1;
                obj = lbl_80371C30[task->start + bg].obj;
                obj->color = (obj->color & 0xFF) | (fn_80036214(task, 0, 0, lbl_803C6028._8D) & 0xFFFFFF00);
                lbl_80371C30[task->start + bg].obj->_68 = 1;
                lbl_80371C30[task->start + name].obj->flags |= 2;
                obj = lbl_80371C30[task->start + name].obj;
                if ((obj->_5C >> 16) <= 12) {
                    obj->_5C = 12 << 16;
                    lbl_80371C30[task->start + name].obj->_68 = 1;
                    for (j = 0; j < 4; j++) {
                        if (lbl_803C6028._78[lbl_803C6028._8D] != 0 && lbl_803C6028.cursor[j] == i) {
                            lbl_80371C30[task->start + j + 23].obj->_5C = 0;
                        }
                    }
                }
                fn_800363D8(task, name, 1, 0x1A, lbl_803C6028.slotOwner[i]);
            } else {
                obj = lbl_80371C30[task->start + name].obj;
                if ((obj->_5C >> 16) > 12) {
                    obj->_68 = 4;
                } else {
                    obj->flags &= ~2;
                }
                // Note: the original tests the same cursor (_8D) every pass.
                for (j = 0; j < 4; j++) {
                    if (lbl_803C6028._78[lbl_803C6028._8D] != 0 && lbl_803C6028.cursor[lbl_803C6028._8D] == i) {
                        obj = lbl_80371C30[task->start + icon].obj;
                        frame = obj->_5C >> 16;
                        if (frame < 15) {
                            obj->_68 = 1;
                        } else if (frame > 15) {
                            obj->_68 = 4;
                        } else {
                            obj->_68 = 0;
                        }
                        obj = lbl_80371C30[task->start + bg].obj;
                        if ((obj->_5C >> 16) < 10) {
                            obj->_68 = 1;
                        } else {
                            obj->_68 = 0;
                        }
                        obj = lbl_80371C30[task->start + bg].obj;
                        obj->color = 0xFFFFFF00 | (obj->color & 0xFF);
                        break;
                    }
                }
                if (j >= 4) {
                    obj = lbl_80371C30[task->start + icon].obj;
                    if ((obj->_5C >> 16) > 5) {
                        obj->_68 = 4;
                    } else {
                        obj->_68 = 0;
                    }
                    obj = lbl_80371C30[task->start + bg].obj;
                    if ((obj->_5C >> 16) != 0) {
                        obj->_68 = 4;
                    } else {
                        obj->_68 = 0;
                    }
                }
            }
        }
    }

    if (lbl_803C6028._78[lbl_803C6028._8D] != 0 && task->textIndex == 1) {
        lbl_80371C30[task->start + 10].obj->flags |= 2;
        lbl_80371C30[task->start + 9].obj->flags |= 2;
        lbl_80371C30[task->start + 23].obj->flags |= 2;
        lbl_80371C30[task->start + 10].obj->_72 = lbl_800FE924[lbl_803C6028._8C][lbl_803C6028.cursor[lbl_803C6028._8D]];
        lbl_80371C30[task->start + 9].obj->_72 = lbl_800FE924[lbl_803C6028._8C][lbl_803C6028.cursor[lbl_803C6028._8D]];
        lbl_80371C30[task->start + 23].obj->_72 = lbl_800FE924[lbl_803C6028._8C][lbl_803C6028.cursor[lbl_803C6028._8D]];
        obj = lbl_80371C30[task->start + 23].obj;
        if ((obj->_5C >> 16) < 12) {
            obj->_68 = 1;
        } else {
            obj->_68 = 0;
            lbl_80371C30[task->start + 23].obj->_5C = 12 << 16;
        }
    } else {
        lbl_80371C30[task->start + 10].obj->flags &= ~2;
        lbl_80371C30[task->start + 9].obj->flags &= ~2;
        lbl_80371C30[task->start + 23].obj->flags &= ~2;
        lbl_80371C30[task->start + 23].obj->_5C = 0;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_803C6028._78[i] != 0) {
            lbl_803C6028._78[i]--;
        }
    }
    return;

finish:
    lbl_803C6028.state7E = 2;
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}
#endif

// .text:0x8004E2EC size:0x218
// NONMATCHING: the original addresses lbl_800FE5D4/lbl_800FE924/lbl_800FE930
// through one lbl_800FCA60 base (same-TU data; the .data split ends too early)
#if NONMATCHING
void fn_8004E2EC(void) {
    u8 table = lbl_803C6028._8C;
    LayoutGroup* task = lbl_803CC1B8;
    LayoutDesc* desc = (LayoutDesc*)&lbl_800FE5D4[0x30]; // TODO type
    s32 i;
    desc->_42 = lbl_803CB870[table];
    fn_80034E20(task, desc);
    for (i = 0; i < 6; i++) {
        if (i == 5 && table == 0) {
            continue;
        }
        fn_800363D8(task, i + 0xB, 1, 0x19, lbl_800FE930[table][i]);
        lbl_80371C30[task->start + i + 0xB].obj->_72 = lbl_800FE924[table][i];
        lbl_80371C30[task->start + i + 0x11].obj->flags &= ~2;
        lbl_80371C30[task->start + i + 0x11].obj->_72 = lbl_800FE924[table][i];
        fn_800363D8(task, i + 0x11, 1, 0x1A, lbl_803C6028._8D);
        lbl_80371C30[task->start + i + 3].obj->_72 = lbl_800FE924[table][i];
    }
    lbl_80371C30[task->start + 10].obj->_5C = lbl_803C6028._8D << 16;
    fn_800363D8(task, 0x17, 1, 0x1A, lbl_803C6028._8D);
    if (table == 0) {
        lbl_80371C30[task->start + 8].obj->flags &= ~2;
        lbl_80371C30[task->start + 16].obj->flags &= ~2;
        lbl_80371C30[task->start + 22].obj->flags &= ~2;
    }
    lbl_803C6028.state7E = 0;
    lbl_803C6028._92 = 0;
    task->textIndex = 0;
    lbl_803CC1B8->callback = fn_8004DB90;
}
#endif

// .text:0x8004E504 size:0xB0
void fn_8004E504(s32 byId, s32 entry0, s32 entry1, s32 entry2, s32 entry3) {
    s32 entries[4];
    s32 p;
    s32 entry;
    entries[0] = entry0;
    entries[1] = entry1;
    entries[2] = entry2;
    entries[3] = entry3;
    for (p = 0; p < 4; p++) {
        if (lbl_803C6028.cursor[p] >= 0) {
            entry = entries[p];
            if (entry >= 0) {
                if (byId == 0) {
                    lbl_803C6028.cursor[p] = entry;
                } else {
                    s32 id = lbl_800E8558[entry].id;
                    u8* ids = lbl_800FE5D4;
                    s32 j;
                    for (j = 0; j < 0x24; ids++, j++) {
                        if (id == *ids) {
                            lbl_803C6028.cursor[p] = j;
                            break;
                        }
                    }
                }
            }
        }
    }
}

// .text:0x8004E5B4 size:0x78
void fn_8004E5B4(s8 owner, s32 entry, s32 set) {
    s32 i;
    s32 id = lbl_800E8558[entry].id;
    for (i = 0; i < 0x24; i++) {
        if (lbl_800FE5D4[i] == id) {
            if (set != 0) {
                lbl_803C6028.slotOwner[i] = owner;
            } else {
                lbl_803C6028.slotOwner[i] = -1;
            }
            return;
        }
    }
}

// .text:0x8004E62C size:0x858
// NONMATCHING: the original addresses lbl_800FE5D4/lbl_800FE93C through one
// lbl_800FCA60 base (same-TU data; the .data split ends too early)
#if NONMATCHING
s16 fn_8004E62C(s32 p, s32 unused, s32 pressed, u16 dirs) {
    s32 occ[12];
    s32 free;
    s32 k;
    s32 q;
    s32 r;
    s32 row;
    s32 col;
    u8* order;

    free = 12;
    lbl_803C6028._78[p] = 3;
    for (k = 0; k < 12; k++) {
        occ[k] = -1;
        if (lbl_803C6028.slotOwner[k] >= 0) {
            free--;
            occ[k] = 0;
        } else {
            for (q = 0; q < 4; q++) {
                if (p != q && lbl_803C6028.cursor[q] == k && lbl_803C6028._78[q] != 0) {
                    free--;
                    occ[k] = q + 1;
                    break;
                }
            }
        }
    }

    if (lbl_803C6028._7F[p] >= 0) {
        lbl_803C6028._7F[p]--;
        if (lbl_803C6028._7F[p] & 1) {
            r = rand() % free;
            for (k = 0; k < 12; k++) {
                if (occ[k] < 0) {
                    if (r == 0) {
                        lbl_803C6028.cursor[p] = k;
                        break;
                    }
                    r--;
                }
            }
        }
    } else if ((pressed & 0x20) && lbl_803C6028._7F[p] == -1) {
        lbl_803C6028._7F[p] = 30;
    } else if (dirs & 2) {
        row = (lbl_803C6028.cursor[p] / 6) * 6;
        col = lbl_803C6028.cursor[p] % 6 + 1;
        if (col >= 6) {
            col = 0;
        }
        for (k = 0; k < 5; k++) {
            if (occ[col + row] < 0) {
                break;
            }
            col++;
            if (col >= 6) {
                col = 0;
            }
        }
        lbl_803C6028.cursor[p] = col + row;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (dirs & 1) {
        row = (lbl_803C6028.cursor[p] / 6) * 6;
        col = lbl_803C6028.cursor[p] % 6 - 1;
        if (col < 0) {
            col = 5;
        }
        for (k = 0; k < 5; k++) {
            if (occ[col + row] < 0) {
                break;
            }
            col--;
            if (col < 0) {
                col = 5;
            }
        }
        lbl_803C6028.cursor[p] = col + row;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (dirs & 4) {
        row = ((lbl_803C6028.cursor[p] / 6 + 1) % 2) * 6;
        order = lbl_800FE5D4_colOrder[lbl_803C6028.cursor[p] % 6];
        for (k = 0; k < 12; k++) {
            if (occ[row + order[k]] < 0) {
                break;
            }
        }
        if (k < 12) {
            lbl_803C6028.cursor[p] = row + order[k];
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (dirs & 8) {
        row = lbl_803C6028.cursor[p] / 6 - 1;
        if (row < 0) {
            row = 1;
        }
        order = lbl_800FE5D4_colOrder[lbl_803C6028.cursor[p] % 6];
        row *= 6;
        for (k = 0; k < 12; k++) {
            if (occ[row + order[k]] < 0) {
                break;
            }
        }
        if (k < 12) {
            lbl_803C6028.cursor[p] = row + order[k];
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    }

    lbl_803C6028.charId[p] = lbl_800FE5D4[lbl_803C6028.cursor[p]];
    if (pressed & 0x40) {
        for (k = 0; k < 9; k++) {
            if (lbl_803C6028.charId[p] == lbl_800FE93C_alts[k][0]) {
                lbl_803C6028._83[k]++;
                if (lbl_803C6028._83[k] >= 5) {
                    lbl_803C6028._83[k] = 0;
                } else if (lbl_800FE93C_alts[k][lbl_803C6028._83[k]] == 0xFF) {
                    lbl_803C6028._83[k] = 0;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
    for (k = 0; k < 9; k++) {
        if (lbl_803C6028.charId[p] == lbl_800FE93C_alts[k][0]) {
            lbl_803C6028.charId[p] = lbl_800FE93C_alts[k][lbl_803C6028._83[k]];
        }
    }
    return lbl_803C6028.charId[p];
}
#endif

// .text:0x8004EE84 size:0x70
s32 fn_8004EE84(s32 arg) {
    if (lbl_803C6028.state7D == 0) {
        if (arg == 2) {
            lbl_803C6028.state7D = 4;
            lbl_803C6028._8F = 1;
        } else if (arg != 0) {
            lbl_803C6028.state7D = 3;
        } else {
            lbl_803C6028.state7D = 1;
        }
    }
    if (lbl_803C6028.state7D == 2) {
        lbl_803C6028.state7D = 0;
        return 1;
    }
    return 0;
}

// .text:0x8004EEF4 size:0x218
// NONMATCHING 93%: constants hoisted before the branch and one shared base register in the original
#if NONMATCHING
void fn_8004EEF4(s32 p0, s32 p1, s32 p2, s32 p3, s32 arg4) {
    RosterSelect* rs = &lbl_803C6028;
    s32 i;
    if (arg4 != 0) {
        for (i = 0; i < 4; i++) {
            rs->_78[i] = 0;
            rs->cursor[i] = -1;
            rs->_7F[i] = -1;
        }
    } else {
        for (i = 0; i < 4; i++) {
            rs->_78[i] = 0;
            rs->cursor[i] = -1;
            rs->_7F[i] = -2;
        }
    }
    for (i = 0; i < 9; i++) {
        lbl_803C6028._83[i] = 0;
    }
    if (p0 != 0) {
        lbl_803C6028.cursor[0] = 0;
    }
    if (p1 != 0) {
        lbl_803C6028.cursor[1] = 1;
    }
    if (p2 != 0) {
        lbl_803C6028.cursor[2] = 1;
    }
    if (p3 != 0) {
        lbl_803C6028.cursor[3] = 1;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_803C6028.cursor[i] >= 0) {
            lbl_803C6028.charId[i] = lbl_800FE5D4[lbl_803C6028.cursor[i]];
        }
    }
    for (i = 0; i < 0x24; i++) {
        lbl_803C6028.slotOwner[i] = -1;
    }
}
#endif

// .text:0x8004F10C size:0x858
// NONMATCHING 99%: register allocation in the prologue
#if NONMATCHING
void fn_8004F10C(void) {
    LayoutGroup* task;
    LayoutObj* title;
    LayoutObj* obj;
    u32 frame;
    s32 n;
    s32 n2;
    s32 i;
    s32 j;
    s32 icon;
    s32 bg;
    s32 name;
    s8 owner;

    n2 = 0;
    lbl_803C6028._92 = 0;
    task = lbl_803CC1B8;
    title = lbl_80371C30[task->start + 2].obj;
    frame = title->_5C >> 16;
    if (task->textIndex == 0) {
        n = 0;
        if (frame == 15) {
            title->_68 = 0;
            n = 1;
        }
        obj = lbl_80371C30[task->start + 1].obj;
        if ((obj->_5C >> 16) == 15) {
            n++;
            obj->_68 = 0;
        }
        if (n == 2) {
            task->textIndex = 1;
            lbl_803C6028._90 = 0;
        }
    } else if (task->textIndex == 1) {
        lbl_803C6028._92 = 1;
        if (lbl_803C6028.state7D == 3) {
            goto finish;
        }
        if (lbl_803C6028.state7D == 1) {
            title->_68 = 4;
            lbl_80371C30[task->start + 1].obj->_68 = 4;
            task->textIndex = 2;
        } else if (lbl_803C6028.state7D == 4) {
            title->_68 = 1;
            lbl_80371C30[task->start + 1].obj->_68 = 1;
            task->textIndex = 3;
        }
    } else if (task->textIndex == 2) {
        if ((s32)frame <= 5) {
            goto finish;
        }
    } else if (task->textIndex == 3) {
        lbl_803C6028.state7D = 2;
        if (lbl_803C6028._8E == 2) {
            goto finish;
        }
        if (frame >= 55) {
            title->_68 = 0;
            n2 = 1;
        }
        obj = lbl_80371C30[task->start + 1].obj;
        if ((obj->_5C >> 16) >= 50) {
            n2++;
            obj->_68 = 0;
        }
        if (n2 >= 2) {
            lbl_803C6028._8E = 2;
        }
    }

    if (task->textIndex != 3) {
        for (i = 0; i < 12; i++) {
            icon = i + 0x17;
            bg = i + 3;
            name = i + 0x23;
            if (task->textIndex == 0) {
                obj = lbl_80371C30[task->start + icon].obj;
                if ((obj->_5C >> 16) >= 5) {
                    obj->_68 = 0;
                }
            } else if (lbl_803C6028.slotOwner[i] >= 0) {
                lbl_80371C30[task->start + icon].obj->_68 = 1;
                lbl_80371C30[task->start + bg].obj->_68 = 1;
                lbl_80371C30[task->start + name].obj->flags |= 2;
                obj = lbl_80371C30[task->start + name].obj;
                if ((obj->_5C >> 16) <= 12) {
                    obj->_5C = 12 << 16;
                    lbl_80371C30[task->start + name].obj->_68 = 1;
                    for (j = 0; j < 4; j++) {
                        if (lbl_803C6028._78[j] != 0 && lbl_803C6028.cursor[j] == i) {
                            lbl_80371C30[task->start + j + 47].obj->_5C = 0;
                        }
                    }
                }
                owner = lbl_803C6028.slotOwner[i];
                if (lbl_803C6028._74[owner] != 0) {
                    fn_800363D8(task, name, 1, 0x1A, owner + 4);
                } else {
                    fn_800363D8(task, name, 1, 0x1A, owner);
                }
            } else {
                obj = lbl_80371C30[task->start + name].obj;
                if ((obj->_5C >> 16) > 12) {
                    obj->_68 = 4;
                } else {
                    obj->flags &= ~2;
                }
                for (j = 0; j < 4; j++) {
                    if (lbl_803C6028._78[j] != 0 && lbl_803C6028.cursor[j] == i) {
                        obj = lbl_80371C30[task->start + icon].obj;
                        frame = obj->_5C >> 16;
                        if (frame < 15) {
                            obj->_68 = 1;
                        } else if (frame > 15) {
                            obj->_68 = 4;
                        } else {
                            obj->_68 = 0;
                        }
                        obj = lbl_80371C30[task->start + bg].obj;
                        if ((obj->_5C >> 16) < 10) {
                            obj->_68 = 1;
                        } else {
                            obj->_68 = 0;
                        }
                        obj = lbl_80371C30[task->start + bg].obj;
                        obj->color = 0xFFFFFF00 | (obj->color & 0xFF);
                        break;
                    }
                }
                if (j >= 4) {
                    obj = lbl_80371C30[task->start + icon].obj;
                    if ((obj->_5C >> 16) > 5) {
                        obj->_68 = 4;
                    } else {
                        obj->_68 = 0;
                    }
                    obj = lbl_80371C30[task->start + bg].obj;
                    if ((obj->_5C >> 16) != 0) {
                        obj->_68 = 4;
                    } else {
                        obj->_68 = 0;
                    }
                }
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (lbl_803C6028._78[i] != 0 && task->textIndex == 1) {
            if (lbl_803C6028._74[i] != 0) {
                fn_800363D8(task, i + 0x2F, 1, 0x1A, i + 4);
            } else {
                fn_800363D8(task, i + 0x2F, 1, 0x1A, i);
            }
            lbl_80371C30[task->start + i + 19].obj->flags |= 2;
            lbl_80371C30[task->start + i + 15].obj->flags |= 2;
            lbl_80371C30[task->start + i + 47].obj->flags |= 2;
            lbl_80371C30[task->start + i + 19].obj->_72 = lbl_800FE5C8[lbl_803C6028.cursor[i]];
            lbl_80371C30[task->start + i + 15].obj->_72 = lbl_800FE5C8[lbl_803C6028.cursor[i]];
            lbl_80371C30[task->start + i + 47].obj->_72 = lbl_800FE5C8[lbl_803C6028.cursor[i]];
            obj = lbl_80371C30[task->start + i + 47].obj;
            if ((obj->_5C >> 16) < 12) {
                obj->_68 = 1;
            } else {
                obj->_68 = 0;
                lbl_80371C30[task->start + i + 47].obj->_5C = 12 << 16;
            }
        } else {
            lbl_80371C30[task->start + i + 19].obj->flags &= ~2;
            lbl_80371C30[task->start + i + 15].obj->flags &= ~2;
            lbl_80371C30[task->start + i + 47].obj->flags &= ~2;
            lbl_80371C30[task->start + i + 47].obj->_5C = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (lbl_803C6028._78[i] != 0) {
            lbl_803C6028._78[i]--;
        }
    }
    return;

finish:
    lbl_803C6028.state7D = 2;
    lbl_803C6028._8E = 0;
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}
#endif

// .text:0x8004F964 size:0x400
// NONMATCHING: the original addresses lbl_800FDE84/lbl_800FE5C8/lbl_800FE5D4
// through one lbl_800FCA60 base (same-TU data; the .data split ends too early)
#if NONMATCHING
void fn_8004F964(void) {
    LayoutGroup* task = lbl_803CC1B8;
    s32 i;
    s32 j;
    s8 owner;

    fn_80034E20(task, &lbl_800FDE84[0xC4]);
    if (lbl_803C6028._90 != 0) {
        lbl_80371C30[task->start + 2].obj->_5C = 55 << 16;
        lbl_80371C30[task->start + 2].obj->_68 = 4;
    }
    if (lbl_803C6028._90 != 0) {
        lbl_80371C30[task->start + 1].obj->_5C = 50 << 16;
        lbl_80371C30[task->start + 1].obj->_68 = 4;
    } else {
        lbl_80371C30[task->start + 1].obj->_5C = 0;
        lbl_80371C30[task->start + 1].obj->_68 = 1;
    }
    for (i = 0; i < 12; i++) {
        fn_800363D8(task, i + 0x17, 1, 0x19, lbl_800FE5D4[i]);
        lbl_80371C30[task->start + i + 0x17].obj->_72 = lbl_800FE5C8[i];
        if (lbl_803C6028._90 != 0) {
            for (j = 0; j < 12; j++) {
                if (lbl_800E854C[j] == lbl_800FE5D4[i]) {
                    lbl_80371C30[task->start + i + 0x17].obj->_5C = 5 << 16;
                    lbl_80371C30[task->start + i + 0x17].obj->_68 = 0;
                    break;
                }
            }
        }
        lbl_80371C30[task->start + i + 0x23].obj->flags &= ~2;
        lbl_80371C30[task->start + i + 0x23].obj->_72 = lbl_800FE5C8[i];
        lbl_80371C30[task->start + i + 3].obj->_72 = lbl_800FE5C8[i];
        if (lbl_803C6028.slotOwner[i] >= 0) {
            lbl_80371C30[task->start + i + 0x17].obj->_5C = 25 << 16;
            lbl_80371C30[task->start + i + 0x17].obj->_68 = 0;
            lbl_80371C30[task->start + i + 3].obj->_5C = 25 << 16;
            lbl_80371C30[task->start + i + 3].obj->_68 = 0;
            lbl_80371C30[task->start + i + 0x23].obj->flags |= 2;
            lbl_80371C30[task->start + i + 0x23].obj->_5C = 25 << 16;
            lbl_80371C30[task->start + i + 0x23].obj->_68 = 0;
            owner = lbl_803C6028.slotOwner[i];
            if (lbl_803C6028._74[owner] != 0) {
                fn_800363D8(task, i + 0x23, 1, 0x1A, owner + 4);
            } else {
                fn_800363D8(task, i + 0x23, 1, 0x1A, owner);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        lbl_80371C30[task->start + i + 0x13].obj->_5C = i << 16;
        if (lbl_803C6028._74[i] != 0) {
            fn_800363D8(task, i + 0x2F, 1, 0x1A, i + 4);
        } else {
            fn_800363D8(task, i + 0x2F, 1, 0x1A, i);
        }
    }
    lbl_803C6028.state7D = 0;
    lbl_803C6028._92 = 0;
    task->textIndex = 0;
    lbl_803C6028._8E = 1;
    lbl_803CC1B8->callback = fn_8004F10C;
}
#endif

// .text:0x8004FD64 size:0x3C
s32 fn_8004FD64(s32 player) {
    s16 slot = lbl_803C6028.cursor[player];
    if (lbl_803C6028.slotLocked[slot] != 0) {
        return -1;
    }
    return lbl_800FDE84[slot];
}

// .text:0x8004FDA0 size:0x48
void fn_8004FDA0(s32 id) {
    s32 i;
    for (i = 0; i < 0x24; i++) {
        if (lbl_800FDE84[i] == id) {
            lbl_803C6028.slotLocked[i] = 1;
            return;
        }
    }
}

// .text:0x8004FDE8 size:0x350
s32 fn_8004FDE8(s32 p, s32 q) {
    s32 occ[0x24];
    s32 cand[8];
    s32 k;
    s32 n;
    s32 cur;
    s32 pick;

    if (lbl_803C6028.cursor[p] != lbl_803C6028.cursor[q]) {
        return -2;
    }
    for (k = 0; k < 0x24; k++) {
        occ[k] = -1;
        if (lbl_803C6028.slotLocked[k] != 0) {
            occ[k] = 0;
        } else if (lbl_803C6028.slotOwner[k] >= 0) {
            occ[k] = 0;
        } else if (lbl_800FDE84[k] == 0xFF) {
            occ[k] = 5;
        } else {
            for (n = 0; n < 4; n++) {
                if (lbl_803C6028.cursor[n] == k && lbl_803C6028._78[n] != 0) {
                    occ[k] = n + 1;
                    break;
                }
            }
        }
    }
    cur = lbl_803C6028.cursor[p];
    n = 0;
    for (k = 0; k < 8; k++) {
        cand[k] = -1;
    }
    if (cur - 13 >= 0 && occ[cur - 13] < 0) {
        n = 1;
        cand[0] = cur - 13;
    }
    if (cur - 12 >= 0 && occ[cur - 12] < 0) {
        cand[n++] = cur - 12;
    }
    if (cur - 11 >= 0 && occ[cur - 11] < 0) {
        cand[n++] = cur - 11;
    }
    if (cur - 1 >= 0 && occ[cur - 1] < 0) {
        cand[n++] = cur - 1;
    }
    if (cur + 1 < 0x24 && occ[cur + 1] < 0) {
        cand[n++] = cur + 1;
    }
    if (cur + 11 < 0x24 && occ[cur + 11] < 0) {
        cand[n++] = cur + 11;
    }
    if (cur + 12 < 0x24 && occ[cur + 12] < 0) {
        cand[n++] = cur + 12;
    }
    if (cur + 13 < 0x24 && occ[cur + 13] < 0) {
        cand[n++] = cur + 13;
    }
    pick = cand[rand() % n];
    lbl_803C6028.cursor[q] = pick;
    return lbl_800FDE84[pick];
}

// .text:0x80050138 size:0x5B0
void fn_80050138(s32 byId, s32 entry0, s32 entry1, s32 entry2, s32 entry3, s32 any) {
    s32 entries[4];
    s32 occ[0x24];
    s32 p;
    s32 entry;
    s32 k;
    s32 q;
    s32 free;
    s32 r;
    entries[0] = entry0;
    entries[1] = entry1;
    entries[2] = entry2;
    entries[3] = entry3;
    for (p = 0; p < 4; p++) {
        if (lbl_803C6028.cursor[p] >= 0) {
            entry = entries[p];
            if (entry >= 0) {
                if (byId == 0) {
                    lbl_803C6028.cursor[p] = entry;
                } else {
                    s32 id = lbl_800E8558[entry].id;
                    u8* ids = lbl_800FDE84;
                    s32 j;
                    for (j = 0; j < 0x24; ids++, j++) {
                        if (id == *ids) {
                            lbl_803C6028.cursor[p] = j;
                            break;
                        }
                    }
                }
            }
        }
    }

    // -3: pick a random selectable character and lock the cursor
    if (entry0 == -3 || entry1 == -3 || entry2 == -3 || entry3 == -3) {
        for (k = 0, free = 0x24; k < 0x24; k++) {
            occ[k] = 1;
            if (lbl_803C6028.slotOwner[k] >= 0) {
                free--;
                occ[k] = 0;
            } else if (lbl_800FDE84[k] == 0xFF) {
                free--;
                occ[k] = 0;
            } else if (lbl_800E8558[lbl_800FDE84[k]]._4 == 0) {
                free--;
                occ[k] = 0;
            } else {
                for (q = 0; q < 4; q++) {
                    if (lbl_803C6028.cursor[q] == k && (lbl_803C6028._78[q] != 0 || any != 0)) {
                        free--;
                        occ[k] = 0;
                        break;
                    }
                }
            }
        }
        for (p = 0; p < 4; p++) {
            if (entries[p] == -3) {
                r = rand() % free;
                for (k = 0; k < 0x24; k++) {
                    if (occ[k] != 0) {
                        if (r == 0) {
                            lbl_803C6028.cursor[p] = k;
                            lbl_803C6028._78[p] = 3;
                            free--;
                            occ[k] = 0;
                            break;
                        }
                        r--;
                    }
                }
            }
        }
    }

    // -2: move the cursor to a random free slot
    if (entry0 <= -2 || entry1 <= -2 || entry2 <= -2 || entry3 <= -2) {
        for (k = 0, free = 0x24; k < 0x24; k++) {
            occ[k] = -1;
            if (lbl_803C6028.slotLocked[k] != 0) {
                free--;
                occ[k] = 0;
            } else if (lbl_803C6028.slotOwner[k] >= 0) {
                free--;
                occ[k] = 0;
            } else if (lbl_800FDE84[k] == 0xFF) {
                free--;
                occ[k] = 5;
            } else {
                for (q = 0; q < 4; q++) {
                    if (lbl_803C6028.cursor[q] == k && lbl_803C6028._78[q] != 0) {
                        free--;
                        occ[k] = q + 1;
                        break;
                    }
                }
            }
        }
        for (p = 0; p < 4; p++) {
            if (entries[p] == -2) {
                r = rand() % free;
                for (k = 0; k < 0x24; k++) {
                    if (occ[k] < 0) {
                        if (r == 0) {
                            lbl_803C6028.cursor[p] = k;
                            free--;
                            break;
                        }
                        r--;
                    }
                }
            }
        }
    }
}

// .text:0x800506E8 size:0x78
void fn_800506E8(s8 owner, s32 entry, s32 set) {
    s32 i;
    s32 id = lbl_800E8558[entry].id;
    for (i = 0; i < 0x24; i++) {
        if (lbl_800FDE84[i] == id) {
            if (set != 0) {
                lbl_803C6028.slotOwner[i] = owner;
            } else {
                lbl_803C6028.slotOwner[i] = -1;
            }
            return;
        }
    }
}

// .text:0x80050760 size:0x818
// NONMATCHING: the original addresses lbl_800FDE84/lbl_800FE93C through one
// lbl_800FCA60 base (same-TU data; the .data split ends too early)
#if NONMATCHING
s16 fn_80050760(s32 p, s32 unused, s32 pressed, u16 dirs, s32 mode) {
    s32 occ[0x24];
    s32 free;
    s32 k;
    s32 q;
    s32 r;
    s32 row;
    s32 col;
    s32 slot;
    u8* order;

    free = 0x24;
    lbl_803C6028._78[p] = 3;
    for (k = 0; k < 0x24; k++) {
        occ[k] = -1;
        if (lbl_803C6028.slotLocked[k] != 0 && lbl_803C6028._7F[p] >= 0) {
            free--;
            occ[k] = 0;
        } else if (lbl_803C6028.slotOwner[k] >= 0 && lbl_803C6028._7F[p] >= 0) {
            free--;
            occ[k] = 0;
        } else if (lbl_800FDE84[k] == 0xFF) {
            free--;
            occ[k] = 5;
        } else if (mode != 1) {
            for (q = 0; q < 4; q++) {
                if (p != q && lbl_803C6028.cursor[q] == k && lbl_803C6028._78[q] != 0) {
                    free--;
                    occ[k] = q + 1;
                    break;
                }
            }
        }
    }

    if (lbl_803C6028._7F[p] >= 0) {
        lbl_803C6028._7F[p]--;
        if (lbl_803C6028._7F[p] & 1) {
            r = rand() % free;
            for (k = 0; k < 0x24; k++) {
                if (occ[k] < 0) {
                    if (r == 0) {
                        lbl_803C6028.cursor[p] = k;
                        break;
                    }
                    r--;
                }
            }
        }
    } else if ((pressed & 0x20) && lbl_803C6028._7F[p] == -1) {
        lbl_803C6028._7F[p] = 30;
    } else if (dirs & 2) {
        row = (lbl_803C6028.cursor[p] / 12) * 12;
        col = lbl_803C6028.cursor[p] % 12;
        for (k = 0; k < 12; k++) {
            col++;
            if (col >= 12) {
                col = 0;
            }
            if (occ[col + row] < 0) {
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                break;
            }
        }
        lbl_803C6028.cursor[p] = col + row;
    } else if (dirs & 1) {
        row = (lbl_803C6028.cursor[p] / 12) * 12;
        col = lbl_803C6028.cursor[p] % 12;
        for (k = 0; k < 12; k++) {
            col--;
            if (col < 0) {
                col = 11;
            }
            if (occ[col + row] < 0) {
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                break;
            }
        }
        lbl_803C6028.cursor[p] = col + row;
    } else if (dirs & 4) {
        order = lbl_800FDE84_colOrder[lbl_803C6028.cursor[p] % 12];
        row = ((lbl_803C6028.cursor[p] / 12 + 1) % 3) * 12;
        for (k = 0; k < 12; k++) {
            if (occ[row + order[k]] < 0) {
                break;
            }
        }
        if (k < 12) {
            lbl_803C6028.cursor[p] = row + order[k];
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (dirs & 8) {
        row = lbl_803C6028.cursor[p] / 12 - 1;
        if (row < 0) {
            row = 2;
        }
        order = lbl_800FDE84_colOrder[lbl_803C6028.cursor[p] % 12];
        row *= 12;
        for (k = 0; k < 12; k++) {
            if (occ[row + order[k]] < 0) {
                break;
            }
        }
        if (k < 12) {
            lbl_803C6028.cursor[p] = row + order[k];
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    }

    slot = lbl_803C6028.cursor[p];
    if (lbl_803C6028.slotOwner[slot] >= 0) {
        return -1;
    }
    if (lbl_803C6028.slotLocked[slot] != 0) {
        return -1;
    }
    lbl_803C6028.charId[p] = lbl_800FDE84[slot];
    if (pressed & 0x40) {
        for (k = 0; k < 9; k++) {
            if (lbl_803C6028.charId[p] == lbl_800FE93C_alts[k][0]) {
                lbl_803C6028._83[k]++;
                if (lbl_803C6028._83[k] >= 5) {
                    lbl_803C6028._83[k] = 0;
                } else if (lbl_800FE93C_alts[k][lbl_803C6028._83[k]] == 0xFF) {
                    lbl_803C6028._83[k] = 0;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
    for (k = 0; k < 9; k++) {
        if (lbl_803C6028.charId[p] == lbl_800FE93C_alts[k][0]) {
            lbl_803C6028.charId[p] = lbl_800FE93C_alts[k][lbl_803C6028._83[k]];
        }
    }
    return lbl_803C6028.charId[p];
}
#endif

// .text:0x80050F78 size:0x70
s32 fn_80050F78(s32 arg) {
    if (lbl_803C6028.state7C == 0) {
        if (arg == 2) {
            lbl_803C6028.state7C = 4;
            lbl_803C6028._90 = 1;
        } else if (arg != 0) {
            lbl_803C6028.state7C = 3;
        } else {
            lbl_803C6028.state7C = 1;
        }
    }
    if (lbl_803C6028.state7C == 2) {
        lbl_803C6028.state7C = 0;
        return 1;
    }
    return 0;
}

// .text:0x80050FE8 size:0x3A4
// NONMATCHING 95%: same cursor-reset constant hoisting issue as fn_8004D990
#if NONMATCHING
void fn_80050FE8(s32 p0, s32 p1, s32 p2, s32 p3, s32 arg4, s32 lockMode) {
    RosterSelect* rs;
    s32 i;
    lbl_803C6028._91 = lockMode;
    for (i = 0; i < 0x24; i++) {
        lbl_803C6028.slotLocked[i] = 0;
    }
    if (lockMode != 0) {
        for (i = 0; i < 0x24; i++) {
            if (lbl_800FDE84[i] != 0xFF && fn_80024C04(lbl_800FDE84[i]) == 0) {
                lbl_803C6028.slotLocked[i] = 1;
            }
        }
    }
    rs = &lbl_803C6028;
    if (arg4 != 0) {
        for (i = 0; i < 4; i++) {
            rs->_78[i] = 0;
            rs->cursor[i] = -1;
            rs->_74[i] = 0;
            rs->_7F[i] = -1;
        }
    } else {
        for (i = 0; i < 4; i++) {
            rs->_78[i] = 0;
            rs->cursor[i] = -1;
            rs->_74[i] = 0;
            rs->_7F[i] = -2;
        }
    }
    for (i = 0; i < 9; i++) {
        rs->_83[i] = 0;
    }
    if (p0 != 0) {
        lbl_803C6028.cursor[0] = 0;
        if (p0 == 2) {
            lbl_803C6028._74[0] = 1;
        }
    }
    if (p1 != 0) {
        lbl_803C6028.cursor[1] = 1;
        if (p1 == 2) {
            lbl_803C6028._74[1] = 1;
        }
    }
    if (p2 != 0) {
        lbl_803C6028.cursor[2] = 3;
        if (p2 == 2) {
            lbl_803C6028._74[2] = 1;
        }
    }
    if (p3 != 0) {
        lbl_803C6028.cursor[3] = 4;
        if (p3 == 2) {
            lbl_803C6028._74[3] = 1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (lbl_803C6028.cursor[i] >= 0) {
            lbl_803C6028.charId[i] = lbl_800FDE84[lbl_803C6028.cursor[i]];
        }
    }
    for (i = 0; i < 0x24; i++) {
        lbl_803C6028.slotOwner[i] = -1;
    }
}
#endif

// .text:0x8005138C size:0x974
// NONMATCHING 95%: register allocation; state-3 block addressing differs
#if NONMATCHING
void fn_8005138C(void) {
    LayoutGroup* task;
    LayoutObj* title;
    LayoutObj* obj;
    u32 frame;
    s32 i;
    s32 j;
    s32 icon;
    s32 bg;
    s32 name;
    s8 owner;

    lbl_803C6028._92 = 0;
    task = lbl_803CC1B8;
    title = lbl_80371C30[task->start + 2].obj;
    frame = title->_5C >> 16;
    if (task->textIndex == 0) {
        if ((s32)frame >= 20) {
            title->_68 = 0;
            task->textIndex = 1;
        }
    } else if (task->textIndex == 1) {
        lbl_803C6028._92 = 1;
        if (lbl_803C6028.state7C == 3) {
            goto finish;
        }
        if (lbl_803C6028.state7C == 1) {
            title->_64 = 0x13;
            lbl_80371C30[task->start + 2].obj->_5C = 20 << 16;
            lbl_80371C30[task->start + 2].obj->_68 = 4;
            lbl_80371C30[task->start + 1].obj->_68 = 1;
            task->textIndex = 2;
        } else if (lbl_803C6028.state7C == 4) {
            title->_64 = 0x14;
            lbl_80371C30[task->start + 2].obj->_5C = 20 << 16;
            lbl_80371C30[task->start + 2].obj->_68 = 4;
            task->textIndex = 3;
        }
    } else if (task->textIndex == 2) {
        if ((s32)frame <= 0) {
            goto finish;
        }
    } else if (task->textIndex == 3) {
        obj = lbl_80371C30[task->start + 1].obj;
        if ((obj->_5C >> 16) >= 50) {
            obj->_68 = 0;
        }
        if ((lbl_80371C30[task->start + 2].obj->_5C >> 16) == 0) {
            lbl_803C6028.state7C = 2;
        }
        if (lbl_803C6028._8E != 0) {
            goto finish;
        }
    }

    if (task->textIndex != 3) {
        for (i = 0; i < 0x24; i++) {
            icon = i + 0x2F;
            bg = i + 3;
            name = i + 0x77;
            if (lbl_800FDE84[i] == 0xFF) {
                continue;
            }
            if (task->textIndex == 0) {
                obj = lbl_80371C30[task->start + icon].obj;
                if ((obj->_5C >> 16) >= 5) {
                    obj->_68 = 0;
                }
            } else if (lbl_803C6028.slotOwner[i] >= 0) {
                lbl_80371C30[task->start + icon].obj->_68 = 1;
                lbl_80371C30[task->start + bg].obj->_68 = 1;
                lbl_80371C30[task->start + name].obj->flags |= 2;
                obj = lbl_80371C30[task->start + name].obj;
                if ((obj->_5C >> 16) <= 12) {
                    obj->_5C = 12 << 16;
                    lbl_80371C30[task->start + name].obj->_68 = 1;
                    for (j = 0; j < 4; j++) {
                        if (lbl_803C6028._78[j] != 0 && lbl_803C6028.cursor[j] == i) {
                            lbl_80371C30[task->start + j + 0x9B].obj->_5C = 0;
                        }
                    }
                }
                owner = lbl_803C6028.slotOwner[i];
                if (lbl_803C6028._74[owner] != 0) {
                    fn_800363D8(task, name, 1, 0x1A, owner + 4);
                } else {
                    fn_800363D8(task, name, 1, 0x1A, owner);
                }
            } else {
                obj = lbl_80371C30[task->start + name].obj;
                if ((obj->_5C >> 16) > 12) {
                    obj->_68 = 4;
                } else {
                    obj->flags &= ~2;
                }
                for (j = 0; j < 4; j++) {
                    if (lbl_803C6028._78[j] != 0 && lbl_803C6028.cursor[j] == i) {
                        obj = lbl_80371C30[task->start + icon].obj;
                        frame = obj->_5C >> 16;
                        if (frame < 15) {
                            obj->_68 = 1;
                        } else if (frame > 15) {
                            obj->_68 = 4;
                        } else {
                            obj->_68 = 0;
                        }
                        obj = lbl_80371C30[task->start + bg].obj;
                        if ((obj->_5C >> 16) < 10) {
                            obj->_68 = 1;
                        } else {
                            obj->_68 = 0;
                        }
                        obj = lbl_80371C30[task->start + bg].obj;
                        obj->color = 0xFFFFFF00 | (obj->color & 0xFF);
                        break;
                    }
                }
                if (j >= 4) {
                    obj = lbl_80371C30[task->start + icon].obj;
                    if ((obj->_5C >> 16) > 5) {
                        obj->_68 = 4;
                    } else {
                        obj->_68 = 0;
                    }
                    obj = lbl_80371C30[task->start + bg].obj;
                    if ((obj->_5C >> 16) != 0) {
                        obj->_68 = 4;
                    } else {
                        obj->_68 = 0;
                    }
                }
            }
        }
    } else {
        for (i = 0; i < 0x24; i++) {
            obj = lbl_80371C30[task->start + i + 0x2F].obj;
            if ((obj->_5C >> 16) <= 5) {
                obj->_68 = 0;
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (lbl_803C6028._78[i] != 0 && task->textIndex <= 1) {
            if (lbl_803C6028._74[i] != 0) {
                fn_800363D8(task, i + 0x9B, 1, 0x1A, i + 4);
            } else {
                fn_800363D8(task, i + 0x9B, 1, 0x1A, i);
            }
            lbl_80371C30[task->start + i + 0x2B].obj->flags |= 2;
            lbl_80371C30[task->start + i + 0x27].obj->flags |= 2;
            lbl_80371C30[task->start + i + 0x9B].obj->flags |= 2;
            lbl_80371C30[task->start + i + 0x2B].obj->_72 = lbl_800FDE60[lbl_803C6028.cursor[i]];
            lbl_80371C30[task->start + i + 0x27].obj->_72 = lbl_800FDE60[lbl_803C6028.cursor[i]];
            lbl_80371C30[task->start + i + 0x9B].obj->_72 = lbl_800FDE60[lbl_803C6028.cursor[i]];
            obj = lbl_80371C30[task->start + i + 0x9B].obj;
            if ((obj->_5C >> 16) < 12) {
                obj->_68 = 1;
            } else {
                obj->_68 = 0;
                lbl_80371C30[task->start + i + 0x9B].obj->_5C = 12 << 16;
            }
        } else {
            lbl_80371C30[task->start + i + 0x2B].obj->flags &= ~2;
            lbl_80371C30[task->start + i + 0x27].obj->flags &= ~2;
            lbl_80371C30[task->start + i + 0x9B].obj->flags &= ~2;
            lbl_80371C30[task->start + i + 0x9B].obj->_5C = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (lbl_803C6028._78[i] != 0) {
            lbl_803C6028._78[i]--;
        }
    }
    return;

finish:
    lbl_803C6028._8F = 0;
    lbl_803C6028.state7C = 2;
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}
#endif

// .text:0x80051D00 size:0x488
// NONMATCHING: the original addresses lbl_800FCA60/lbl_800FDE60/lbl_800FDE84
// through one lbl_800FCA60 base (same-TU data; the .data split ends too early)
#if NONMATCHING
void fn_80051D00(void) {
    LayoutGroup* task = lbl_803CC1B8;
    s32 i;
    s32 j;
    s32 id;
    s8 owner;

    if (lbl_803C6028._8E == 1) {
        return;
    }
    fn_80034E20(task, lbl_800FCA60);
    if (lbl_803C6028._8F == 1) {
        lbl_80371C30[task->start + 2].obj->_64 = 0x14;
    }
    lbl_80371C30[task->start + 1].obj->_5C = 50 << 16;
    for (i = 0; i < 0x24; i++) {
        if (lbl_800FDE84[i] == 0xFF) {
            lbl_80371C30[task->start + i + 0x2F].obj->flags &= ~2;
            lbl_80371C30[task->start + i + 3].obj->flags &= ~2;
        } else {
            id = lbl_800FDE84[i];
            if (lbl_803C6028.slotLocked[i] != 0) {
                id = 0x36;
            }
            fn_800363D8(task, i + 0x2F, 1, 0x19, id);
            lbl_80371C30[task->start + i + 0x2F].obj->_72 = lbl_800FDE60[i];
            if (lbl_803C6028._8F == 1) {
                for (j = 0; j < 12; j++) {
                    if (lbl_800E854C[j] == id) {
                        lbl_80371C30[task->start + i + 0x2F].obj->_5C = 5 << 16;
                        lbl_80371C30[task->start + i + 0x2F].obj->_68 = 0;
                        break;
                    }
                }
            }
            if (id < 0x36) {
                if (g_d_GameSettings.exhibitionMatchInd == 0) {
                    if (starMissionCompletionTracker[0x43D6 + id] != 0) { // TODO type
                        lbl_80371C30[task->start + i + 0x53].obj->flags |= 2;
                    }
                } else if (lbl_80361B20[id] != 0) {
                    lbl_80371C30[task->start + i + 0x53].obj->flags |= 2;
                }
            }
        }
        lbl_80371C30[task->start + i + 0x77].obj->flags &= ~2;
        lbl_80371C30[task->start + i + 0x77].obj->_72 = lbl_800FDE60[i];
        if (lbl_803C6028.slotOwner[i] >= 0) {
            lbl_80371C30[task->start + i + 0x2F].obj->_5C = 25 << 16;
            lbl_80371C30[task->start + i + 0x2F].obj->_68 = 0;
            lbl_80371C30[task->start + i + 3].obj->_5C = 25 << 16;
            lbl_80371C30[task->start + i + 3].obj->_68 = 0;
            lbl_80371C30[task->start + i + 0x77].obj->flags |= 2;
            lbl_80371C30[task->start + i + 0x77].obj->_5C = 25 << 16;
            lbl_80371C30[task->start + i + 0x77].obj->_68 = 0;
            owner = lbl_803C6028.slotOwner[i];
            if (lbl_803C6028._74[owner] != 0) {
                fn_800363D8(task, i + 0x77, 1, 0x1A, owner + 4);
            } else {
                fn_800363D8(task, i + 0x77, 1, 0x1A, owner);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        lbl_80371C30[task->start + i + 0x2B].obj->_5C = i << 16;
        if (lbl_803C6028._74[i] != 0) {
            fn_800363D8(task, i + 0x9B, 1, 0x1A, i + 4);
        } else {
            fn_800363D8(task, i + 0x9B, 1, 0x1A, i);
        }
    }
    lbl_803C6028.state7C = 0;
    lbl_803C6028._92 = 0;
    task->textIndex = 0;
    lbl_803CC1B8->callback = fn_8005138C;
}
#endif

// .text:0x80052188 size:0x28
void fn_80052188(void) {
    lbl_803C6028._8E = 0;
    lbl_803C6028._8F = 0;
    lbl_803C6028._90 = 0;
    lbl_803C6028.state7C = 0;
    lbl_803C6028.state7D = 0;
    lbl_803C6028.state7E = 0;
}

static inline u8 calcMeterAlpha(s32 row, f32 frame) {
    s16* tbl = lbl_800FEB08[row];
    s32 k;
    if (tbl != NULL) {
        for (k = 0; k < 4; k++) {
            if (frame < tbl[k]) {
                switch (k) {
                case 2:
                    return 0;
                case 3:
                    return 255.0f * (frame - lbl_800FEB08[row][k - 1]) / (tbl[k] - lbl_800FEB08[row][k - 1]);
                case 0:
                    return 0xFF;
                case 1:
                    return 255.0f * (tbl[k] - frame) / (tbl[k] - lbl_800FEB08[row][k - 1]);
                }
            }
        }
    }
    return 0xFF;
}

// .text:0x800521B0 size:0x25C
void fn_800521B0(void) {
    MeterTask* task = (MeterTask*)lbl_803CC1B8;
    CharActor* actor = task->actor;
    AnimCtl* anim = task->anim;
    f32 frame;
    s32 row;
    if (actor->_25C == 0 || (s8)actor->kind != (s8)task->kind) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (anim->hasFrame != 0) {
        frame = anim->frame;
    } else {
        frame = fn_800B4C40(anim->id);
    }
    switch (actor->anim) {
    case 0x67:
        if ((s32)actor->kind == 0xE) {
            row = 0;
        } else {
            row = 1;
        }
        break;
    case 0x47:
        row = 2;
        break;
    case 0x48:
        row = 3;
        break;
    case 0x60:
        row = 4;
        break;
    default:
        actor->meterAlpha = 0xFF;
        return;
    }
    actor->meterAlpha = calcMeterAlpha(row, frame);
}

// .text:0x8005240C size:0x228
void fn_8005240C(CharActor* actor, AnimCtl* anim) {
    f32 frame;
    u16 row;
    if (anim->hasFrame != 0) {
        frame = anim->frame;
    } else {
        frame = fn_800B4C40(anim->id);
    }
    switch (actor->anim) {
    case 0x67:
        if ((s32)actor->kind == 0xE) {
            row = 0;
        } else {
            row = 1;
        }
        break;
    case 0x47:
        row = 2;
        break;
    case 0x48:
        row = 3;
        break;
    case 0x60:
        row = 4;
        break;
    default:
        actor->meterAlpha = 0xFF;
        return;
    }
    actor->meterAlpha = calcMeterAlpha(row, frame);
}

// .text:0x80052634 size:0x58
void fn_80052634(CharActor* actor, AnimCtl* anim) {
    MeterTask* task = fn_800B0A5C_insertQueue(fn_800521B0, 4);
    task->actor = actor;
    task->anim = anim;
    task->kind = actor->kind;
}

// fn_8005268C, size:0x8
s32 fn_8005268C(void) {
    return lbl_803CBD14;
}

// .text:0x80052694 size:0xA0
void fn_80052694(s32 index) {
    if (index < 0) {
        index = 0;
    } else if (index >= 2) {
        index = 1;
    }
    lbl_803CBD14 = index;
    GXSetProjection((&lbl_803C639C[index] + 2)->proj, GX_PERSPECTIVE);
    if (lbl_803CB880 == 1) {
        GXSetScissor(0, 0, 0x280, 0x1C0);
    } else if (lbl_803CB880 == 2) {
        GXSetScissor(index * 0x140, 0, 0x140, 0x1C0);
    }
}

// fn_80052734, size:0x34
void* fn_80052734(s32 index) {
    if (index < 0) {
        index = 0;
    } else if (index >= 2) {
        index = 1;
    }
    return &lbl_803C639C[index] + 2;
}

// fn_80052768_getCamera, size:0x30
camera_803c639c_s* fn_80052768_getCamera(int index) {
    if (index < 0) {
        index = 0;
    } else if (index >= 2) {
        index = 1;
    }
    return &lbl_803C639C[index];
}

// fn_800527BC, size:0x8
s32 fn_800527BC(void) {
    return lbl_803CB880;
}

// fn_80052798, size:0x24
void fn_80052798(s32 count) {
    if (count < 1) {
        count = 1;
    } else if (count > 2) {
        count = 2;
    }
    lbl_803CB880 = count;
}
