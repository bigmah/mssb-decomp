#include "main/file_8001FE00.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/os.h"
#include "musyx/musyx.h"

typedef struct PaddedVec {
    Vec v;
    f32 _pad;
} PaddedVec;

// ARAM file descriptor (16 bytes).
typedef struct AramFile {
    /*0x0*/ u32 _00;
    /*0x4*/ u32 size; // top 4 bits are flags
    /*0x8*/ u8 _08[0x8];
} AramFile;

typedef struct StadiumWeight {
    /*0x0*/ s8 stadium; // < 0: any stadium
    /*0x1*/ s8 weight;
    /*0x2*/ s8 weightSeen;
} StadiumWeight;

typedef struct WeightedPick {
    s16 weight;
    s16 index;
} WeightedPick;

typedef struct SoundOptions {
    /*0x000*/ u8 _000[0x396];
    /*0x396*/ u8 outputMode;
    /*0x397*/ u8 outputModeSet;
    /*0x398*/ u8 _398;
} SoundOptions;

typedef struct OptionsDefaults {
    /*0x00*/ u8 _00[0x23];
    /*0x23*/ u8 _23;
    /*0x24*/ u8 outputMode;
} OptionsDefaults;

typedef struct UnkSettings_800EFBC0 {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ u32 _18;
} UnkSettings_800EFBC0;

typedef struct AramState {
    /*0x000*/ u8 _000[0x715];
    /*0x715*/ u8 transferDone;
} AramState;

extern LayoutGroup* lbl_803CC1B8;
extern f32 lbl_803CBBDC;
extern f32 lbl_803CBBE0;
extern StadiumWeight lbl_800E86BC[17];
extern AramFile lbl_800EEFD0[];
extern u8 lbl_800EF3B0[];
extern u8 lbl_800EF470[];
extern s32 lbl_800EF4B0[];
extern u16 lbl_803CB7C8[2];
extern u8 lbl_803CB7CC[8];
extern AramState lbl_803C6CF8;
extern SoundOptions lbl_800EF808;
extern OptionsDefaults lbl_800E8754;
extern UnkSettings_800EFBC0 lbl_800EFBC0;

extern int rand(void);
extern void fn_800B2160(s32);
extern void DrawSprite_TexObj(SpriteVtx* quad, TexRecord* tex);
extern void* fn_800ACF34(s32 heap, s32 size);
extern void fn_800ACF14(void* p);
extern void fn_80034E20(void* group, void* data);
extern void fn_8003649C(void* group, s32 a, s32 b, s32 c, s32 d);

// NONMATCHING 99%: original adds 0.0f + 640.0f / 256.0f at runtime (fadds); ours folds the constants
// .text:0x8001FE00 size:0x248
#if NONMATCHING
void fn_8001FE00(LayoutGroup* group) {
    SpriteVtx quad[4];
    PaddedVec p[4];
    Mtx trans;
    Mtx m;
    f32 scale;
    f32 right;
    f32 bottom;
    s32 a;
    LayoutObj* obj;

    if (lbl_8037169C.loadState < 2) {
        return;
    }
    if (lbl_8037169C.state == 13) {
        lbl_8037169C.fadeAlpha = lbl_8037169C.alpha;
    } else {
        a = lbl_8037169C.fadeAlpha + 16;
        if (a > 255) {
            a = 255;
        }
        lbl_8037169C.fadeAlpha = a;
    }
    obj = lbl_80371C30[group->start + 4].obj;
    obj->color = lbl_8037169C.fadeAlpha | (obj->color & 0xFFFFFF00);
    fn_8000FE08(group->textIndex, 0, lbl_8037169C.loadIndex + 0x92);
    fn_800B2160(1);
    PSMTXTrans(trans, -320.0f, -224.0f, 0.0f);
    scale = lbl_803CBBE0 / lbl_803CBBDC;
    right = 640.0f;
    bottom = 256.0f;
    p[0].v.x = 0.0f;
    p[0].v.y = 0.0f;
    p[1].v.x = right;
    p[1].v.y = 0.0f;
    p[2].v.x = 0.0f;
    p[2].v.y = bottom;
    p[3].v.x = right;
    p[3].v.y = bottom;
    p[3].v.z = 0.0f;
    p[2].v.z = 0.0f;
    p[1].v.z = 0.0f;
    p[0].v.z = 0.0f;
    PSMTXScale(m, scale, scale, 1.0f);
    PSMTXConcat(m, trans, m);
    PSMTXMultVec(m, &p[0].v, &p[0].v);
    PSMTXMultVec(m, &p[1].v, &p[1].v);
    PSMTXMultVec(m, &p[2].v, &p[2].v);
    PSMTXMultVec(m, &p[3].v, &p[3].v);
    quad[0].x = p[0].v.x;
    quad[0].y = p[0].v.y;
    quad[1].x = p[2].v.x;
    quad[1].y = p[2].v.y;
    quad[2].x = p[3].v.x;
    quad[2].y = p[3].v.y;
    quad[3].x = p[1].v.x;
    quad[3].y = p[1].v.y;
    quad[0].z = quad[1].z = quad[2].z = quad[3].z = -lbl_803CBBE0;
    quad[0].color = quad[1].color = quad[2].color = quad[3].color = lbl_8037169C.fadeAlpha - 0x100;
    quad[1].s = 0;
    quad[0].s = 0;
    quad[3].s = 0x400;
    quad[2].s = 0x400;
    quad[3].t = 0;
    quad[0].t = 0;
    quad[2].t = 0x400;
    quad[1].t = 0x400;
    DrawSprite_TexObj(quad, lbl_8037169C.texObj);
}
#endif

// NONMATCHING 99%: the li r9,0 / li r29,0 initialisations are scheduled in the other order
// .text:0x80020048 size:0x1D0
#if NONMATCHING
s32 calledWhenStartingMatch(void) {
    WeightedPick picks[10];
    s32 i;
    s32 count;
    s32 total;
    s32 r;

    if ((u32)g_d_GameSettings._00 == 0) {
        g_d_GameSettings._00 |= 1;
        return 0;
    }
    for (i = 0; i < 10; i++) {
        picks[i].weight = 0;
        picks[i].index = -1;
    }
    total = 0;
    count = 0;
    for (i = 0; i < 17; i++) {
        if ((lbl_800E86BC[i].stadium < 0 || g_d_GameSettings.StadiumID == lbl_800E86BC[i].stadium) &&
            lbl_8037169C.lastPick != i) {
            if (g_d_GameSettings._00 & (1 << i)) {
                picks[count].weight = lbl_800E86BC[i].weightSeen;
            } else {
                picks[count].weight = lbl_800E86BC[i].weight;
            }
            total += picks[count].weight;
            picks[count].index = i;
            count++;
        }
    }
    r = rand() % total;
    for (i = 0; i < count; i++) {
        r -= picks[i].weight;
        if (r < 0) {
            g_d_GameSettings._00 |= 1 << picks[i].index;
            return picks[i].index;
        }
    }
    return 0;
}
#endif

// .text:0x80020218 size:0x34
s32 fn_80020218(void) {
    if (lbl_8037169C.state == 13 || lbl_8037169C.state == 14 || lbl_8037169C.state == 15) {
        return 1;
    }
    return 0;
}

// .text:0x8002024C size:0x2C
void fn_8002024C(void) {
    fn_800ACF14(lbl_8037169C.tex);
}

// .text:0x80020278 size:0x110
s32 fn_80020278(s32 index) {
    if (lbl_8037169C.loadState == 0) {
        AramFile* file = &lbl_800EEFD0[index + 0x2D];
        lbl_8037169C.tex = fn_800ACF34(0x20, file->size & 0x0FFFFFFF);
        ARAMTransfer(file, (s32)lbl_8037169C.tex, 1, 0); // TODO type: 2nd param is the destination
        lbl_8037169C.loadIndex = index;
        lbl_8037169C.fadeAlpha = 0;
        lbl_8037169C.loadState++;
    } else if (lbl_8037169C.loadState == 1) {
        if ((s32)lbl_803C6CF8.transferDone != 1) {
            return 0;
        }
        convertTextureHeader(lbl_8037169C.tex);
        lbl_8037169C.texObj = TEX_ARCHIVE_OBJ(lbl_8037169C.tex, 0);
        lbl_8037169C.loadState = 2;
        return 1;
    }
    return 0;
}

// .text:0x80020388 size:0x58
s32 fn_80020388(void) {
    return fn_80035838(&lbl_800EEFD0[lbl_803CB7CC[g_d_GameSettings.StadiumID] + 0x26], 13) != 0;
}

// .text:0x800203E0 size:0xEC
void fn_800203E0(u8 scene, s8 variant) {
    if (variant >= 0) {
        lbl_8037169C.variant = variant;
    }
    if (scene == 7) {
        lbl_8037169C.state = 7;
        lbl_8037169C.requestDuration = 1;
        fn_800B0A5C_insertQueue(fn_80020624, 2);
        return;
    }
    if (scene == 1 || scene == 6 || scene == 13) {
        if (lbl_8037169C.state >= 4 && lbl_8037169C.state <= 6) {
            scene = 6;
        } else if (lbl_8037169C.state >= 10 && lbl_8037169C.state <= 12) {
            scene = 10;
        } else if (lbl_8037169C.state >= 13 && lbl_8037169C.state <= 15) {
            scene = 13;
        } else {
            scene = 1;
        }
    }
    lbl_8037169C.request = scene;
    lbl_8037169C.requestDuration = 1;
}

// .text:0x800204CC size:0xD0
void changeScene(s32 scene, s32 duration) {
    if ((u8)scene == 7) {
        lbl_8037169C.requestDuration = duration;
        lbl_8037169C.state = 7;
        fn_800B0A5C_insertQueue(fn_80020624, 2);
        return;
    }
    if ((u8)scene == 1 || (u8)scene == 6 || (u8)scene == 13) {
        if (lbl_8037169C.state >= 4 && lbl_8037169C.state <= 6) {
            scene = 6;
        } else if (lbl_8037169C.state >= 10 && lbl_8037169C.state <= 12) {
            scene = 10;
        } else if (lbl_8037169C.state >= 13 && lbl_8037169C.state <= 15) {
            scene = 13;
        } else {
            scene = 1;
        }
    }
    lbl_8037169C.request = scene;
    lbl_8037169C.requestDuration = duration;
}

// .text:0x8002059C size:0x88
void fn_8002059C(void) {
    LayoutGroup* group = lbl_803CC1B8;
    if (lbl_8037169C.state == 7 && lbl_80371C30[group->start].obj->_69 == 2) {
        lbl_8037169C.done = 1;
        lbl_8037169C.state = 0;
    } else {
        lbl_8037169C.done = 0;
        return;
    }
    lbl_8037169C._16 = 0;
    fn_80034CEC(group);
    ((void (*)(void))fn_800B0A14_removeQueue)();
}

// .text:0x80020624 size:0xD8
void fn_80020624(void) {
    LayoutGroup* group = lbl_803CC1B8;
    if (lbl_8037169C._16 != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    fn_80034E20(group, lbl_800EF470);
    if (lbl_8037169C.state == 7) {
        lbl_80371C30[group->start].obj->_68 = 1;
        lbl_80371C30[group->start].obj->_5C = 0;
    }
    lbl_80371C30[group->start].obj->flags |= 2;
    lbl_8037169C._16 = 1;
    lbl_803CC1B8->callback = fn_8002059C;
}

// .text:0x800206FC size:0x968
void fn_800206FC(void) {
    LayoutGroup* group = lbl_803CC1B8;
    u8 prev = lbl_8037169C.state;
    u8 req;
    s32 k;
    LayoutObj* obj;

    lbl_8037169C._13 = 0;
    if (prev == 0) {
        req = lbl_8037169C.request;
        if (req == 3) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 2;
            } else {
                lbl_8037169C.duration = lbl_8037169C.requestDuration;
                lbl_8037169C.state = 3;
                group->timer = 0;
            }
        } else if (req == 4) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 5;
            } else {
                lbl_8037169C.duration = lbl_8037169C.requestDuration;
                lbl_8037169C.state = 4;
                group->timer = 0;
                lbl_80371C30[group->start + 1].obj->_64 = lbl_803CB7C8[rand() % 2];
                lbl_80371C30[group->start + 1].obj->_5C = 0;
            }
        } else if (req == 7) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 8;
            } else {
                lbl_8037169C.state = 7;
                lbl_8037169C.duration = lbl_8037169C.requestDuration;
                group->timer = 0;
                fn_800B0A5C_insertQueue(fn_80020624, 2);
            }
        } else if (req == 9) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 8;
            } else {
                lbl_8037169C.state = 9;
                fn_800B0A5C_insertQueue(fn_80020624, 2);
            }
        } else if (req == 10) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 11;
            } else {
                lbl_8037169C.duration = lbl_8037169C.requestDuration;
                lbl_8037169C.state = 10;
                group->timer = 0;
            }
        } else if (req == 12) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 11;
            } else {
                lbl_8037169C.state = 12;
                lbl_80371C30[group->start + 2].obj->_5C = 0;
            }
        } else if (req == 13) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 14;
            } else {
                lbl_8037169C.duration = lbl_8037169C.requestDuration;
                lbl_8037169C.state = 13;
                group->timer = 0;
            }
        } else if (req == 15) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 14;
            } else {
                lbl_8037169C.duration = lbl_8037169C.requestDuration;
                lbl_8037169C.state = 15;
            }
            group->textIndex = fn_8000F988(group, 4, 0, 0, 0x92, 0);
            lbl_80371C30[group->start + 4].obj->flags |= 2;
            lbl_80371C30[group->start + 4].obj->color &= ~0xFF;
            lbl_80366B18.entries[group->textIndex].hAlign = 1;
            lbl_80366B18.entries[group->textIndex].vAlign = 1;
        }
    }

    switch (lbl_8037169C.state) {
    case 3: // fade in
        group->timer++;
        if (lbl_8037169C.duration <= group->timer) {
            lbl_8037169C.state = 2;
            lbl_8037169C.alpha = 255;
        } else {
            lbl_8037169C.alpha = group->timer * 255 / lbl_8037169C.duration;
        }
        break;
    case 2: // fully covered
        lbl_8037169C.alpha = 255;
        if (lbl_8037169C.request == 1) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 0;
            } else {
                lbl_8037169C.duration = lbl_8037169C.requestDuration;
                lbl_8037169C.state = 1;
                group->timer = 0;
            }
        }
        lbl_8037169C._13 = 1;
        break;
    case 1: // fade out
        group->timer++;
        if (lbl_8037169C.duration <= group->timer) {
            lbl_8037169C.done = 1;
            lbl_8037169C.state = 0;
        } else {
            lbl_8037169C.alpha = 255 - group->timer * 255 / lbl_8037169C.duration;
        }
        break;
    case 4:
        group->timer++;
        if (lbl_8037169C.duration <= group->timer) {
            lbl_8037169C.state = 5;
        } else {
            lbl_8037169C.alpha = group->timer * 255 / lbl_8037169C.duration;
        }
        break;
    case 5:
        lbl_8037169C.alpha = 255;
        if (lbl_8037169C.request == 6) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 0;
            } else {
                lbl_8037169C.duration = lbl_8037169C.requestDuration;
                lbl_8037169C.state = 6;
                group->timer = 0;
            }
        }
        lbl_8037169C._13 = 1;
        break;
    case 6:
        group->timer++;
        if (lbl_8037169C.duration <= group->timer) {
            lbl_8037169C.done = 1;
            lbl_8037169C.state = 0;
        } else {
            lbl_8037169C.alpha = 255 - group->timer * 255 / lbl_8037169C.duration;
        }
        break;
    case 12:
        lbl_80371C30[group->start + 2].obj->_68 = 1;
        lbl_8037169C.state = 11;
        break;
    case 11:
        lbl_8037169C.alpha = 255;
        if (lbl_8037169C.request == 10) {
            lbl_8037169C.state = 10;
            lbl_8037169C.duration = 6;
            group->timer = 0;
        }
        if ((lbl_80371C30[group->start + 2].obj->_5C >> 16) >= 10) {
            lbl_8037169C._13 = 1;
        }
        break;
    case 10:
        group->timer++;
        if (lbl_8037169C.duration <= group->timer) {
            lbl_8037169C.done = 1;
            lbl_8037169C.state = 0;
        } else {
            lbl_8037169C.alpha = 255 - group->timer * 255 / lbl_8037169C.duration;
        }
        break;
    case 15:
        group->timer++;
        if (lbl_8037169C.duration <= group->timer) {
            lbl_8037169C.state = 14;
        } else {
            lbl_8037169C.alpha = group->timer * 255 / lbl_8037169C.duration;
        }
        break;
    case 14:
        lbl_8037169C.alpha = 255;
        if (lbl_8037169C.request == 13) {
            if (lbl_8037169C.requestDuration == 0) {
                lbl_8037169C.state = 0;
            } else {
                lbl_8037169C.duration = lbl_8037169C.requestDuration;
                lbl_8037169C.state = 13;
                group->timer = 0;
            }
        }
        lbl_8037169C._13 = 1;
        break;
    case 13:
        group->timer++;
        if (lbl_8037169C.duration <= group->timer) {
            lbl_8037169C.done = 1;
            lbl_8037169C.state = 0;
            lbl_8037169C.loadState = 0;
            fn_8000FEE8(group->textIndex);
            fn_8000F8F4(group);
        } else {
            lbl_8037169C.alpha = 255 - group->timer * 255 / lbl_8037169C.duration;
        }
        break;
    }

    if (lbl_8037169C.state >= 1 && lbl_8037169C.state <= 3) {
        lbl_8037169C.done = 0;
        lbl_80371C30[group->start].obj->flags |= 2;
        lbl_80371C30[group->start].obj->color = (lbl_80371C30[group->start].obj->color & ~0xFF) | lbl_8037169C.alpha;
    } else {
        lbl_80371C30[group->start].obj->flags &= ~2;
    }
    if (lbl_8037169C.state >= 4 && lbl_8037169C.state <= 6) {
        lbl_8037169C.done = 0;
        lbl_80371C30[group->start + 1].obj->flags |= 2;
        lbl_80371C30[group->start + 1].obj->color = (lbl_80371C30[group->start + 1].obj->color & ~0xFF) | lbl_8037169C.alpha;
    } else {
        lbl_80371C30[group->start + 1].obj->flags &= ~2;
    }
    if (lbl_8037169C.state >= 10 && lbl_8037169C.state <= 12) {
        lbl_8037169C.done = 0;
        lbl_80371C30[group->start + 2].obj->flags |= 2;
        for (k = 2; k <= 13; k++) {
            fn_8003649C(group, 2, k, 0x13, lbl_800EF4B0[lbl_8037169C.variant]);
        }
    } else {
        lbl_80371C30[group->start + 2].obj->flags &= ~2;
    }
    if (lbl_8037169C.state >= 13 && lbl_8037169C.state <= 15) {
        lbl_8037169C.done = 0;
        lbl_80371C30[group->start + 3].obj->flags |= 2;
        lbl_80371C30[group->start + 3].obj->color = (lbl_80371C30[group->start + 3].obj->color & ~0xFF) | lbl_8037169C.alpha;
        fn_8001FE00(group);
    } else {
        lbl_80371C30[group->start + 3].obj->flags &= ~2;
        lbl_80371C30[group->start + 4].obj->flags &= ~2;
    }

    if (lbl_8037169C.request == 1) {
        if (lbl_8037169C.state == 3 || prev == 3) {
            return;
        }
    } else if (lbl_8037169C.request == 3) {
        if (lbl_8037169C.state == 1 || prev == 1) {
            return;
        }
    }
    lbl_8037169C.request = 0;
}

// .text:0x80021064 size:0x124
void fn_80021064(void) {
    LayoutGroup* group = lbl_803CC1B8;
    fn_80034E20(group, lbl_800EF3B0);
    lbl_80371C30[group->start].obj->flags &= ~2;
    lbl_80371C30[group->start + 1].obj->flags &= ~2;
    lbl_80371C30[group->start + 2].obj->flags &= ~2;
    lbl_80371C30[group->start + 3].obj->flags &= ~2;
    lbl_80371C30[group->start + 4].obj->flags &= ~2;
    lbl_8037169C.alpha = 0;
    lbl_8037169C.state = 0;
    lbl_8037169C.request = 0;
    lbl_8037169C._13 = 0;
    lbl_8037169C.done = 0;
    lbl_8037169C._16 = 0;
    lbl_8037169C._17 = 0;
    lbl_8037169C.tex = NULL;
    lbl_8037169C.loadState = 0;
    lbl_8037169C.fadeAlpha = 0;
    lbl_8037169C.lastPick = 0xFF;
    group->textIndex = 0;
    group->_1E = 0;
    group->timer = 0;
    group->_1A = 0;
    lbl_803CC1B8->callback = fn_800206FC;
}

// .text:0x80021188 size:0x34
s32 fn_80021188(void) {
    sndMasterVolume(0x7F, 1, 1, 1);
    return 0;
}

// .text:0x800211BC size:0x34
s32 fn_800211BC(void) {
    sndMasterVolume(0, 1, 1, 1);
    return 0;
}

// fn_800211F0, size:0x14
u8 fn_800211F0(void) {
    return lbl_800EFBC0._18 & 0xFF;
}

// fn_80021204, size:0x24
void fn_80021204(void) {
    u8 first = lbl_800EF808._398;
    u8 second = lbl_800EF808.outputMode;
    lbl_800E8754._23 = first;
    lbl_800E8754.outputMode = second;
}

// .text:0x80021228 size:0x64
void fn_80021228(u8 mode) {
    u8 set = mode ? mode : 1;
    lbl_800EF808.outputModeSet = set;
    lbl_800EF808.outputMode = mode;
    sndOutputMode(mode);
    OSSetSoundMode(lbl_800EF808.outputMode != 0);
}

// .text:0x8002128C size:0x7C
void fn_8002128C(u8 mode) {
    u8 set = mode ? mode : 1;
    lbl_800EF808.outputModeSet = set;
    if (OSGetSoundMode() == 0) {
        mode = 0;
    } else if (mode != 2) {
        mode = 1;
    }
    lbl_800EF808.outputMode = mode;
    sndOutputMode(mode);
}
