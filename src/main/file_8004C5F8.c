#include "main/file_8004C5F8.h"
#include "main/file_8000F150.h"
#include "Dolphin/gx.h"
#include "musyx/musyx.h"

extern LayoutGroup* lbl_803CC1B8;
extern CharTableEntry lbl_800E8558[54];
extern u8 lbl_800EFBA4[];
extern u8 lbl_800FDE84[];
extern u8 lbl_800FE5D4[];
extern u8 lbl_800FE930[][6];
extern camera_803c639c_s lbl_803C639C[4];
extern s32 lbl_803CBD14;
extern s32 lbl_803CB880;

void fn_800521B0(void);

// .text:0x8004C5F8 size:0x404
void fn_8004C5F8(void) {
    return;
}

extern u32 lbl_803CB878;

extern u32 lbl_803CB874;

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
void fn_8004CA6C(void) {
    return;
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
void fn_8004CCC0(void) {
    return;
}

// .text:0x8004D0F0 size:0x370
void fn_8004D0F0(void) {
    return;
}

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
void fn_8004D57C(void) {
    return;
}

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
void fn_8004D990(void) {
    return;
}

// .text:0x8004DB90 size:0x75C
void fn_8004DB90(void) {
    return;
}

// .text:0x8004E2EC size:0x218
void fn_8004E2EC(void) {
    return;
}

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
void fn_8004E62C(void) {
    return;
}

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
void fn_8004EEF4(void) {
    return;
}

// .text:0x8004F10C size:0x858
void fn_8004F10C(void) {
    return;
}

// .text:0x8004F964 size:0x400
void fn_8004F964(void) {
    return;
}

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
void fn_8004FDE8(void) {
    return;
}

// .text:0x80050138 size:0x5B0
void fn_80050138(void) {
    return;
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
void fn_80050760(void) {
    return;
}

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
void fn_80050FE8(void) {
    return;
}

// .text:0x8005138C size:0x974
void fn_8005138C(void) {
    return;
}

// .text:0x80051D00 size:0x488
void fn_80051D00(void) {
    return;
}

// .text:0x80052188 size:0x28
void fn_80052188(void) {
    lbl_803C6028._8E = 0;
    lbl_803C6028._8F = 0;
    lbl_803C6028._90 = 0;
    lbl_803C6028.state7C = 0;
    lbl_803C6028.state7D = 0;
    lbl_803C6028.state7E = 0;
}

// .text:0x800521B0 size:0x25C
void fn_800521B0(void) {
    return;
}

// .text:0x8005240C size:0x228
void fn_8005240C(void) {
    return;
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
