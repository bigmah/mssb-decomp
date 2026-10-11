#include "main/file_8003A688.h"
#include "main/file_80039AC0.h"
#include "main/file_80008E00.h"
#include "main/file_8001FE00.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "Dolphin/os.h"
#include "stl/string.h"

extern TrailSystem lbl_802D3D80;
// SoundManager (main/file_80021308.h, whose prototypes clash with UnknownHomes_Static.h).
typedef struct SoundManagerView {
    /*0x000*/ u8 _000[0x397];
    /*0x397*/ u8 outputMode;
    /*0x398*/ u8 unk398;
} SoundManagerView;
extern SoundManagerView lbl_800EF808;
extern u8 lbl_80361B20[0xF8];
extern u8 lbl_803616CC[0x454];
extern void (*lbl_803CBCA8)(void); // model callback (set by fn_8003A540)

// main/file_8000F150
void fn_8000FE54(void);
// main/file_8004207C
s32 fn_8004A34C(SaveDialog* dialog, u8 port, u8 msg, u8 mode, u8 arg4);
// main/file_800A7C08 (memory card / CRC)
void fn_800A9E34(u8 chan, u8 mode, u64 serial);
void fn_800AA930(SaveCardRequest* req, u64 serial);
void fn_800AAEE4(SaveCardRequest* req, u64 serial);
void fn_800AB474(u8 chan, u8 mode, s16 blocks, char* fileName, u64 serial);
void fn_800AC508(char* fileName, void* bannerTpl, s32 bannerSize, void* iconTpl, s32 iconSize, u32 iconSpeed,
                 u32 bannerFlags, char* comment, char* subComment, s32 blocks);
s32 fn_800ACC6C(s32 mode, s32 a, s32 b);
u16 fn_800ABB14(u8* data, s32 len);

// .text:0x8003A688 size:0x28
void fn_8003A688(s32 type, f32 speed, f32 spread) {
    lbl_802D3D80.params[type].speed = speed / 2;
    lbl_802D3D80.params[type].spread = spread / 2;
}

// .text:0x8003A6B0 size:0x198
void fn_8003A6B0(s32 type, TexImage* tex, f32 speed, f32 spread) {
    if (tex->tlut != NULL) {
        lbl_802D3D80.texMode[type] = 2;
        GXInitTexObjCI(&lbl_802D3D80.texObj[type], tex->data, tex->width, tex->height, tex->format, tex->wrapS, tex->wrapT,
                       GX_FALSE, type);
        GXInitTlutObj(&lbl_802D3D80.tlutObj[type], tex->tlut, tex->tlutFormat, tex->tlutEntries);
    } else {
        lbl_802D3D80.texMode[type] = 1;
        GXInitTexObj(&lbl_802D3D80.texObj[type], tex->data, tex->width, tex->height, tex->format, tex->wrapS, tex->wrapT,
                     GX_FALSE);
    }
    GXInitTexObjLOD(&lbl_802D3D80.texObj[type], tex->minFilter, tex->magFilter, tex->minLOD, tex->maxLOD, tex->lodBias,
                    GX_FALSE, GX_FALSE, GX_ANISO_1);
    fn_8003A688(type, speed, spread);
}

extern u8 lbl_803CB828[3];

// fn_8003A848, size:0x14
void fn_8003A848(u8 red, u8 green, u8 blue) {
    lbl_803CB828[0] = red;
    lbl_803CB828[1] = green;
    lbl_803CB828[2] = blue;
}

// .text:0x8003A85C size:0x44
void fn_8003A85C(u8 enabled) {
    lbl_802D3D80.enabled = enabled;
    lbl_802D3D80.head = 0;
    lbl_802D3D80.tail = 0;
    memset(lbl_802D3D80.texMode, 0, sizeof(lbl_802D3D80.texMode));
}

// .text:0x8003A8A0 size:0x3F0
void fn_8003A8A0(Model* model, Mtx viewMtx, s32 unused) {
    Mtx mtx;
    GXVtxDescList desc[27]; // GX_MAX_VTXDESCLIST_SZ
    ModelArray* arr;
    ModelCmd* cmd;
    s32 compSize;
    s32 i;
    s32 j;
    s32 n;
    s32 attr;
    s32 shift;
    u32 type;

    PSMTXConcat(viewMtx, model->mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    arr = model->pos;
    switch ((u8)(arr->fmt >> 4)) {
    case GX_U8:
    case GX_S8:
        compSize = 1;
        break;
    case GX_U16:
    case GX_S16:
        compSize = 2;
        break;
    case GX_F32:
        compSize = 4;
        break;
    default:
        compSize = 0;
        break;
    }
    GXSetArray(GX_VA_POS, arr->data, (u8)(arr->count * compSize));
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, model->pos->fmt >> 4, model->pos->fmt & 0xF);

    if (model->texCoords != NULL) {
        for (i = 0; i < model->numTexCoords; i++) {
            arr = &model->texCoords[i];
            switch ((u8)(arr->fmt >> 4)) {
            case GX_U8:
            case GX_S8:
                compSize = 1;
                break;
            case GX_U16:
            case GX_S16:
                compSize = 2;
                break;
            case GX_F32:
                compSize = 4;
                break;
            default:
                compSize = 0;
                break;
            }
            GXSetArray(GX_VA_TEX0 + i, arr->data, (u8)(arr->count * compSize));
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + i, GX_TEX_ST, model->texCoords[i].fmt >> 4, model->texCoords[i].fmt & 0xF);
            GXSetTexCoordGen2(i, GX_MTX2x4, GX_TG_TEX0 + i, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        }
        GXSetNumTexGens(model->numTexCoords);
    } else {
        GXSetNumTexGens(0);
    }

    cmd = model->cmdList->cmds;
    for (j = 0; j < model->cmdList->count; j++) {
        switch (cmd->type) {
        case MODEL_CMD_TEXTURE: {
            u32 map = (cmd->param >> 13) & 7;
            TexArchive* textures = model->texCoords[map].textures;
            SetDisplayStateTexture((TexImage*)TEX_ARCHIVE_OBJ(textures, cmd->param & 0x1FFF), map, map);
            break;
        }
        case MODEL_CMD_VTXDESC:
            GXClearVtxDesc();
            n = 0;
            type = cmd->param & 3;
            if (type != 0) {
                desc[0].mType = type;
                n = 1;
                desc[0].mAttr = GX_VA_PNMTXIDX;
            }
            for (attr = GX_VA_POS, shift = 2; attr < GX_VA_TEX7 + 1; attr++, shift += 2) {
                type = (cmd->param >> shift) & 3;
                if (type != 0) {
                    desc[n].mAttr = attr;
                    n++;
                    desc[n - 1].mType = type;
                }
            }
            type = (cmd->param >> 26) & 3;
            if (type != 0) {
                desc[n].mAttr = attr;
                desc[n].mType = type;
                n++;
            }
            desc[n].mAttr = GX_VA_NULL;
            GXSetVtxDescv(desc);
            break;
        case MODEL_CMD_CALLBACK:
            if (lbl_803CBCA8 != NULL) {
                lbl_803CBCA8();
            }
            break;
        case 4: // unused command type
            break;
        }
        if (cmd->displayList != NULL) {
            GXCallDisplayList(cmd->displayList, cmd->displayListSize);
        }
        cmd++;
    }
}

extern u32 lbl_803CBCB8;

// Maps the slot's CARDProbeEx result to a card status and records it in the task.
static inline void SaveTask_CheckCard(SaveTask* task) {
    s32 status;
    switch (lbl_803C7838.slots[task->slot].probeResult) {
    case 0: // CARD_RESULT_READY
        status = 0x11;
        break;
    case -1: // CARD_RESULT_BUSY
        status = 0xF;
        break;
    case -3: // CARD_RESULT_NOCARD
        status = 0;
        break;
    case -2: // CARD_RESULT_WRONGDEVICE
        status = 4;
        break;
    default:
        status = -1;
        break;
    }
    switch (status) {
    case 4:
    case 0x11:
        task->cardReady = 1;
        break;
    case 0:
        task->noCard = 1;
        break;
    }
}

// Which blocks of the save image a task touches (bit 0 = shared, 1..3 = challenge saves).
static inline u32 SaveTask_BlockMask(u32 flags, s32 slot) {
    u32 mask = 0;
    if ((flags & 7) == 7) {
        mask = 0xF;
    } else if (flags & 2) {
        if (slot == 3) {
            mask |= 3;
        } else {
            mask = 1 << (slot + 1);
        }
    }
    return mask;
}

// Returns the blocks in mask whose stored size is wrong.
static inline u32 SaveImage_CheckSizes(SaveImage* img, u32 mask) {
    u32 bad = 0;
    u32 bit;
    s32 i;
    for (i = 0; i < 4; i++) {
        bit = 1 << i;
        if (mask & bit) {
            if (i == 0) {
                if (img->size != 0x5B4) {
                    bad |= bit;
                }
            } else {
                SaveChallengeBlock* blk = &img->challenge[i - 1];
                if (blk->size != 0x450C) {
                    bad |= bit;
                }
            }
        }
    }
    return bad;
}

static inline char* SaveBanner_Text(SaveBannerData* banner, s32 lang) {
    return banner->text[lang][1];
}

// Finishes the task: hands the outcome to the parent and removes it from the queue.
static inline void SaveTask_Finish(s16 outcome) {
    lbl_803CC1B8->parent->_10 = outcome;
    fn_8000FE54();
    ((void (*)(void))fn_800B0A14_removeQueue)(); // removes the running task
}

extern u8 lbl_803CBCB4;

// .text:0x8003AC90 size:0xF4
void fn_8003AC90(void) {
    GXColor color;
    color.a = 0xFF;
    color.b = lbl_803CBCB4;
    color.g = lbl_803CBCB4;
    color.r = lbl_803CBCB4;
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

extern GXTexObj lbl_803C50B0;
extern GXTlutObj lbl_803C50DC;
extern u16 lbl_800F7AC0[16];
extern u8 lbl_803CBCAC;

// .text:0x8003AD84 size:0xD0
void fn_8003AD84(TexArchive* arc) {
    TexImage* tex = (TexImage*)arc->recs; // TODO type: archive records are TexImage headers

    GXInitTexObjCI(&lbl_803C50B0, tex->data, tex->width, tex->height, GX_TF_C4, tex->wrapS, tex->wrapT, GX_FALSE, GX_TLUT0);
    GXInitTlutObj(&lbl_803C50DC, lbl_800F7AC0, GX_TL_IA8, 16);
    GXInitTexObjLOD(&lbl_803C50B0, tex->minFilter, tex->magFilter, tex->minLOD, tex->maxLOD, tex->lodBias, GX_FALSE, GX_FALSE,
                    GX_ANISO_1);
    lbl_803CBCAC = 1;
}

// fn_8003AE70, size:0x5C
u8 fn_8003AE70(s32 selector) {
    u8 value = 0;
    switch (selector) {
    case 0:
        value = lbl_802D4B00._95;
        break;
    case 1:
        value = lbl_802D4B00.soundMode;
        break;
    case 2:
        value = lbl_802D4B00._96;
        break;
    }
    return value;
}

// fn_8003AE54, size:0x8
u8 fn_8003AE54(void) {
    return lbl_803CBCB4;
}

// fn_8003AE5C, size:0x8
void fn_8003AE5C(u8 value) {
    lbl_803CBCB4 = value;
}

// fn_8003AE64, size:0xC
void fn_8003AE64(void) {
    lbl_803CBCB8 = 0x0;
}

// .text:0x8003AECC size:0x6E4
void fn_8003AECC(void) {
    return;
}

// .text:0x8003B5B0 size:0x5E0
// Save task: creates the save file if needed and writes lbl_802D4B00 to the card.
// NONMATCHING 99%: the original reaches the banner comment strings through a pooled .data base (addi 0x3220; addi 0x20), unsplit data
#if NONMATCHING
void fn_8003B5B0(void) {
    SaveTask* task = (SaveTask*)lbl_803CC1B8;
    OSCalendarTime date;
    SaveCardRequest req;
    SaveBannerData* banner = &lbl_800F7B00;

    SaveTask_CheckCard(task);
    switch (task->state) {
    case 0:
        task->cardReady = 0;
        task->noCard = 0;
        task->state = 1;
    case 1:
        fn_800AB474(task->slot, task->mode, lbl_803CBC48, "MarioBaseball", lbl_802D4AE0[task->slot]);
        task->state++;
        break;
    case 2:
        if (lbl_803CC1B8->_10 != 0) {
            if (task->noCard) {
                task->state = 10;
                break;
            }
            switch (lbl_803C7838.status) {
            case 5:
                fn_8004A34C(&lbl_803C50E8, task->port, 0xE, 0, 0);
                task->state++;
                break;
            case 6:
                fn_8004A34C(&lbl_803C50E8, task->port, 0xF, 0, 0);
                task->state++;
                break;
            case 16:
                task->state = 14;
                break;
            case 17:
                task->state = 5;
                break;
            case 3:
            case 13:
                task->state = 12;
                break;
            default:
                task->state = 10;
                break;
            }
        }
        break;
    case 3:
        if (task->noCard) {
            if (lbl_803C50E8.choice != 0) {
                task->state = 16;
                task->outcome = 9;
            }
        } else {
            switch (lbl_803C50E8.choice) {
            case 2:
                lbl_80366158.resetRequested = 1;
                task->state = 4;
                break;
            case 1:
            case 3:
            case 4:
                task->state = 16;
                task->outcome = 2;
                break;
            }
        }
        break;
    case 5:
        if (task->noCard) {
            task->state = 10;
            break;
        }
        fn_8004A34C(&lbl_803C50E8, task->port, 0xC, 0, 0);
        fn_800415A0(50);
        task->state++;
        break;
    case 6:
        if (fn_8004157C() == 0) {
            OSTicksToCalendarTime(OSGetTime(), &date);
            fn_800AC508("MarioBaseball", banner->bannerTpl, lbl_803CBC4C, banner->iconTpl, lbl_803CBC50, 3, 0,
                        SaveBanner_Text(banner, 1), SaveBanner_Text(banner, 0), lbl_803CBC48);
            req.fileName = NULL;
            req.buffer = &lbl_802D4B00;
            req.length = 0x10000;
            req.chan = task->slot;
            req.mode = task->mode;
            req.permissions = 4; // CARD_ATTR_NO_COPY
            req.verify = fn_80040FE0;
            req.verifyArg = SaveTask_BlockMask(task->saveFlags, task->challengeSlot);
            req.flags = 1;
            fn_800AAEE4(&req, lbl_802D4AE0[task->slot]);
            task->state++;
        }
        break;
    case 7:
        if (lbl_803CC1B8->_10 != 0) {
            switch (lbl_803C7838.status) {
            case 17:
                if (task->_1A == 0) {
                    task->state = 16;
                    task->outcome = 1;
                } else {
                    task->state = 8;
                }
                break;
            case 16:
                task->state = 14;
                break;
            case 3:
            case 13:
                task->state = 12;
                break;
            case 0:
            case 5:
            case 6:
            default:
                task->state = 10;
                break;
            }
        }
        break;
    case 8:
        fn_8004A34C(&lbl_803C50E8, task->port, 0x18, 0, 0);
        task->state++;
        break;
    case 9:
        if (lbl_803CC1B8->_10 != 0) {
            task->state = 16;
            task->outcome = 1;
        }
        break;
    case 10:
        task->state = 16;
        task->outcome = 2;
        break;
    case 11:
        break;
    case 12:
        task->state = 16;
        task->outcome = 5;
        break;
    case 13:
        break;
    case 14:
        if (task->noCard) {
            task->state = 16;
            task->outcome = 9;
            break;
        }
        fn_8004A34C(&lbl_803C50E8, task->port, 0x13, 0, 0);
        task->state++;
        break;
    case 15:
        if (task->noCard) {
            if (lbl_803CC1B8->_10 != 0) {
                task->state = 16;
                task->outcome = 9;
            }
        } else if (lbl_803CC1B8->_10 != 0) {
            task->state = 16;
            task->outcome = 8;
        }
        break;
    case 16:
        SaveTask_Finish(task->outcome);
        break;
    }
}
#endif

// .text:0x8003BB90 size:0x3C4
// Memory card check task (queued with fn_8003BF54-style fields).
void fn_8003BB90(void) {
    SaveTask* task = (SaveTask*)lbl_803CC1B8;

    SaveTask_CheckCard(task);
    switch (task->state) {
    case 0:
        fn_8004A34C(&lbl_803C50E8, task->port, 8, 0, 0);
        task->noCard = 0;
        fn_800415A0(50);
        task->state++;
        break;
    case 1:
        if (fn_8004157C() == 0) {
            if (task->noCard) {
                task->cardReady = 0;
                task->outcome = 9;
                task->state = 3;
            } else {
                fn_800A9E34(task->slot, task->mode, lbl_802D4AE0[task->slot]);
                task->state = 2;
            }
        }
        break;
    case 2:
        if (lbl_803CC1B8->_10 != 0) {
            if (lbl_803C7838.status == 0x11) {
                SaveTask_Finish(1);
            } else {
                task->state = 3;
                if (task->noCard) {
                    task->outcome = 9;
                } else {
                    switch (lbl_803C7838.status) {
                    case 13:
                        task->outcome = 5;
                        task->state = 4;
                        break;
                    case 16:
                        task->outcome = 8;
                        break;
                    case 0:
                        task->outcome = 9;
                        break;
                    default:
                        task->outcome = 2;
                        break;
                    }
                }
            }
            task->cardReady = 0;
        }
        break;
    case 3:
        fn_8004A34C(&lbl_803C50E8, task->port, 0xA, 0, 0);
        task->state = 5;
        break;
    case 4:
        fn_8004A34C(&lbl_803C50E8, task->port, 9, 0, 0);
        task->state = 5;
        break;
    case 5:
        if (task->noCard) {
            if (task->cardReady) {
                switch (lbl_803C50E8.choice) {
                case 1:
                case 2:
                    task->outcome = 7;
                    task->state = 6;
                    break;
                case 3:
                case 4:
                    task->outcome = 2;
                    task->state = 6;
                    break;
                }
            } else {
                switch (lbl_803C50E8.choice) {
                case 1:
                case 2:
                    task->outcome = 7;
                    task->state = 6;
                    break;
                case 3:
                case 4:
                    task->outcome = 2;
                    task->state = 6;
                    break;
                }
            }
        } else {
            switch (lbl_803C50E8.choice) {
            case 1:
            case 2:
                task->outcome = 7;
                task->state = 6;
                break;
            case 3:
            case 4:
                task->outcome = 2;
                task->state = 6;
                break;
            }
        }
        break;
    case 6:
        SaveTask_Finish(task->outcome);
        break;
    }
}

// .text:0x8003BF54 size:0xB8
void fn_8003BF54(u8 a, u8 b, u8 slot, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h) {
    SaveTask* task = fn_800B0A5C_insertQueue(fn_8003C00C, 0x8000);
    task->state = 0;
    task->port = a;
    task->_16 = b;
    task->slot = slot;
    task->mode = c;
    task->_19 = d;
    task->_1A = e;
    task->saveFlags = f;
    task->noCard = 0;
    task->challengeSlot = g;
    task->_21 = h;
    lbl_802D4AE0[slot] = 0;
    task->_1F = 2;
    lbl_803CC1B8->_10 = 0;
}

// .text:0x8003C00C size:0x28CC
void fn_8003C00C(void) {
    return;
}

// .text:0x8003E8D8 size:0x964
void fn_8003E8D8(void) {
    return;
}

// .text:0x8003F23C size:0x7C
void fn_8003F23C(void) {
    SaveTask* task = fn_800B0A5C_insertQueue(fn_8003F2B8, 0x8000);
    task->state = 0;
    task->port = 0;
    task->_16 = 0;
    task->slot = 0;
    task->mode = 0;
    task->_1A = 0;
    task->saveFlags = 7;
    task->noCard = 0;
    task->_21 = 0;
    lbl_803CC1B8->_10 = 0;
    lbl_802D4AE0[1] = 0;
    lbl_802D4AE0[0] = 0;
}

// .text:0x8003F2B8 size:0x1284
void fn_8003F2B8(void) {
    return;
}

// .text:0x8004053C size:0x6D8
void fn_8004053C(void) {
    return;
}

// .text:0x80040C14 size:0x3CC
// Load task: reads the save file from the card into lbl_802D4B00.
// NONMATCHING 99%: register allocation only in the inlined block-mask/size checks (r6/r7/r8/r9 rotated)
#if NONMATCHING
void fn_80040C14(void) {
    SaveTask* task = (SaveTask*)lbl_803CC1B8;
    SaveCardRequest req;
    s32 status;

    switch (lbl_803C7838.slots[task->slot].probeResult) {
    case 0:
        status = 0x11;
        break;
    case -1:
        status = 0xF;
        break;
    case -3:
        status = 0;
        break;
    case -2:
        status = 4;
        break;
    default:
        status = -1;
        break;
    }
    switch (status) {
    case 4:
    case 0:
        task->noCard = 1;
        break;
    }

    switch (task->state) {
    case 0:
        task->noCard = 0;
        req.chan = task->slot;
        req.mode = task->mode;
        req.buffer = &lbl_802D4B00;
        req.length = 0x10000;
        req.fileName = "MarioBaseball";
        req.permissions = 0;
        req.verify = fn_80041074;
        req.verifyArg = SaveTask_BlockMask(task->saveFlags, task->challengeSlot);
        req.flags = 1;
        fn_800AA930(&req, lbl_802D4AE0[task->slot]);
        task->state++;
        break;
    case 1:
        if (lbl_803CC1B8->_10 != 0) {
            if (task->noCard) {
                task->outcome = 9;
            } else {
                switch (lbl_803C7838.status) {
                case 0x11:
                    if (SaveImage_CheckSizes(&lbl_802D4B00, SaveTask_BlockMask(task->saveFlags, task->challengeSlot)) == 0) {
                        task->outcome = 1;
                    } else {
                        task->outcome = 4;
                    }
                    break;
                case 0:
                    task->outcome = 9;
                    break;
                case 0x10:
                    task->outcome = 8;
                    break;
                case 0xB:
                    task->outcome = 4;
                    break;
                case 3:
                    task->outcome = 5;
                    break;
                default:
                    task->outcome = 2;
                    break;
                }
            }
            task->state = 2;
        }
        break;
    case 2:
        SaveTask_Finish(task->outcome);
        break;
    }
}
#endif

// .text:0x80040FE0 size:0x94
u8 fn_80040FE0(void* buffer, s32 length, u32 mask) {
    SaveImage* img = buffer;
    u8* shared = img->_48;
    SaveChallengeBlock* blk;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i == 0) {
            img->crc = fn_800ABB14(shared, 0x5B0);
        } else {
            blk = &img->challenge[i - 1];
            blk->crc = fn_800ABB14(blk->data, sizeof(blk->data));
        }
    }
    return 0x11;
}

// .text:0x80041074 size:0xDC
u8 fn_80041074(void* buffer, s32 length, u32 mask) {
    SaveImage* img = buffer;
    u8* shared = img->_48;
    u32 bit;
    SaveChallengeBlock* blk;
    s32 i;
    u16 sum;

    lbl_803C50E8.badMask = 0;
    for (i = 0; i < 4; i++) {
        bit = 1 << i;
        if (mask & bit) {
            if (i == 0) {
                sum = fn_800ABB14(shared, 0x5B0);
                if (sum != img->crc) {
                    lbl_803C50E8.badMask = bit;
                    break;
                }
            } else {
                blk = &img->challenge[i - 1];
                sum = fn_800ABB14(blk->data, sizeof(blk->data));
                if (sum != blk->crc) {
                    lbl_803C50E8.badMask |= bit;
                }
            }
        }
    }
    if (lbl_803C50E8.badMask != 0) {
        return 0xB;
    }
    return 0x11;
}

// .text:0x80041150 size:0x1F8
void fn_80041150(u8 mask, u8 slot) {
    SaveImage* img = &lbl_802D4B00;
    SaveChallengeBlock* blk = img->challenge;
    u8* p8E = img->_8E;
    u8* p48 = img->_48;
    u8* p7E = img->_7E;
    u8* dst;
    s32 i;

    if (mask & 5) {
        fn_8002128C(img->soundMode);
        lbl_800EF808.unk398 = img->_95;
        lbl_80366158._1F = img->_96;
        memcpy(lbl_80361B20, img->_97, sizeof(img->_97));
        memcpy(lbl_803616CC, img->_190, sizeof(img->_190));
        g_d_GameSettings._12 = img->_5E4;
        memcpy(g_d_GameSettings._14, img->_5E5, sizeof(img->_5E5));
        memcpy(g_d_GameSettings._1A, img->_5EB, sizeof(img->_5EB));
        g_d_GameSettings._00 = img->_5F4;
        memcpy(lbl_80354768._CF18, p48, sizeof(lbl_80354768._CF18));
        memcpy(lbl_80354768._CF4E, p7E, sizeof(lbl_80354768._CF4E));
    }
    if (mask & 2) {
        if (slot != 3) {
            dst = lbl_80354768.challenge[slot];
            memcpy(dst, blk[slot].data, sizeof(blk->data));
            memcpy(&starMissionCompletionTracker, dst, sizeof(blk->data));
            return;
        }
        for (i = 0; i < 3; i++) {
            memcpy(lbl_80354768.challenge[i], blk[i].data, sizeof(blk->data));
        }
        memcpy(lbl_80354768._CF5E, p8E, sizeof(lbl_80354768._CF5E));
        memcpy(lbl_80354768._CF18, p48, sizeof(lbl_80354768._CF18));
        memcpy(lbl_80354768._CF4E, p7E, sizeof(lbl_80354768._CF4E));
    }
}

// .text:0x80041348 size:0x1F4
// Sanity-checks the loaded challenge save; returns 0 if it is corrupt.
// NONMATCHING 96%: duplicate-id loop keeps &teams[i] as a separate base register in the original (r6 = r7 + 0x40B8)
#if NONMATCHING
s32 fn_80041348(void) {
    s32 ok = 1;
    s32 i;
    s32 j;

    if (gChallengeState._1606 != 0 && gChallengeState._441B == 0) {
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                if (gChallengeState.teams[i].id == gChallengeState.teams[j].id && i != j) {
                    ok = 0;
                }
            }
        }
        if (gChallengeState._4415 >= 4) {
            ok = 0;
        }
        if (gChallengeState._43BC >= 0 && gChallengeState._43BC <= 1000) {
            return ok;
        }
        return 0;
    }
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (gChallengeState.teams[i].id == gChallengeState.teams[j].id && i != j) {
                ok = 0;
            }
        }
    }
    if (gChallengeState._4415 >= 4) {
        ok = 0;
    }
    if (gChallengeState._43BC < 0 || gChallengeState._43BC > 1000) {
        ok = 0;
    }
    if (gChallengeState._441C >= 6) {
        return 0;
    }
    return ok;
}
#endif

// .text:0x8004153C size:0x40
void fn_8004153C(void) {
    lbl_803CBC50 = 0x2380;
    lbl_803CBC4C = 0xE60;
    lbl_803CBC48 = fn_800ACC6C(1, 0x2380, 0x10000);
}

extern u16 lbl_803CBCC0;

// fn_8004157C, size:0x24
u16 fn_8004157C(void) {
    if (lbl_803CBCC0 != 0) {
        lbl_803CBCC0--;
        return 1;
    }
    return 0;
}

// fn_800415A0, size:0x8
void fn_800415A0(u16 value) {
    lbl_803CBCC0 = value;
}

// .text:0x800415A8 size:0xAD4
void fn_800415A8(void) {
    return;
}
