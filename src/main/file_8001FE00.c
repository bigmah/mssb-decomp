#include "main/file_8001FE00.h"
#include "main/file_80011640.h"
#include "main/file_80021308.h"
#include "main/file_800A6870.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "static/Pad.h"
#include "Dolphin/os.h"
#include "musyx/musyx.h"
#include "main/file_800B0724.h"
#include "main/file_800BDEA0.h"
#include "main/file_800263FC.h"
#include "main/file_80034F50.h"

typedef struct PaddedVec {
    Vec v;
    f32 _pad;
} PaddedVec;


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

typedef struct UnkSettings_800EFBC0 { // s32 lbl_800EFBC0[10] in file_80021308
    /*0x00*/ s32 _00[6];
    /*0x18*/ u32 _18;
    /*0x1C*/ s32 _1C[3];
} UnkSettings_800EFBC0;


extern LayoutGroup* lbl_803CC1B8;
extern f32 lbl_803CBBDC;
extern f32 lbl_803CBBE0;
extern StadiumWeight lbl_800E86BC[17];
extern DiskFileEntry lbl_800EEFD0[];
extern u8 lbl_800EF3B0[];
extern u8 lbl_800EF470[];
extern s32 lbl_800EF4B0[];
extern u16 lbl_803CB7C8[2];
extern u8 lbl_803CB7CC[8];
extern SoundOptions lbl_800EF808;
extern OptionsDefaults lbl_800E8754;
extern UnkSettings_800EFBC0 lbl_800EFBC0;

extern int rand(void);
extern void* fn_800ACF34(s32 heap, s32 size);
extern void fn_800ACF14(void* p);

// NONMATCHING 99%: original adds 0.0f + 640.0f / 256.0f at runtime (fadds); ours folds the constants
// .text:0x8001FE00 size:0x248
#if NONMATCHING
void fn_8001FE00(LayoutGroup* group) {
    QuadVtx quad[4];
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
    quad[0].pos.x = p[0].v.x;
    quad[0].pos.y = p[0].v.y;
    quad[1].pos.x = p[2].v.x;
    quad[1].pos.y = p[2].v.y;
    quad[2].pos.x = p[3].v.x;
    quad[2].pos.y = p[3].v.y;
    quad[3].pos.x = p[1].v.x;
    quad[3].pos.y = p[1].v.y;
    quad[0].pos.z = quad[1].pos.z = quad[2].pos.z = quad[3].pos.z = -lbl_803CBBE0;
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
        DiskFileEntry* file = &lbl_800EEFD0[index + 0x2D];
        lbl_8037169C.tex = fn_800ACF34(0x20, file->sizeFlags & 0x0FFFFFFF);
        ARAMTransfer(file, lbl_8037169C.tex, 1, 0);
        lbl_8037169C.loadIndex = index;
        lbl_8037169C.fadeAlpha = 0;
        lbl_8037169C.loadState++;
    } else if (lbl_8037169C.loadState == 1) {
        if ((s32)(u8)lbl_803C6CF8.idle != 1) {
            return 0;
        }
        convertTextureHeader(lbl_8037169C.tex);
        lbl_8037169C.texObj = TEX_ARCHIVE_IMG(lbl_8037169C.tex, 0);
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
    fn_80034CEC((SpaniGroup *)group); // TODO type
    REMOVE_QUEUE_NOARG();
}

// .text:0x80020624 size:0xD8
void fn_80020624(void) {
    LayoutGroup* group = lbl_803CC1B8;
    if (lbl_8037169C._16 != 0) {
        REMOVE_QUEUE_NOARG();
        return;
    }
    fn_80034E20((SpaniGroup *)group, (SpaniDesc *)lbl_800EF470); // TODO type
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
            fn_8003649C((SpaniOwner *)group, 2, k, 0x13, lbl_800EF4B0[lbl_8037169C.variant]); // TODO type
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
    fn_80034E20((SpaniGroup *)group, (SpaniDesc *)lbl_800EF3B0); // TODO type
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
s32 fn_80021188(BOOL (*callback)(void)) {
    sndMasterVolume(0x7F, 1, 1, 1);
    return 0;
}

// .text:0x800211BC size:0x34
s32 fn_800211BC(BOOL (*callback)(void)) {
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

// ---- Data (initialisers generated from the original DOL) ----

// .data 0x800EEFD0..0x800EF508
DiskFileEntry lbl_800EEFD0[62] = {
    {1035, {0x4013764C}, {0x1A635000}, 0x7DB48},
    {1035, {0x4003E3DC}, {0x1A6B3000}, 0x21420},
    {1035, {0x4002EC10}, {0x1A6D4800}, 0x13108},
    {1035, {0x400E72C0}, {0x1A6E8000}, 0x60768},
    {1035, {0x40049404}, {0x1A748800}, 0x20E34},
    {1035, {0x40076AE0}, {0x18ED7000}, 0x36BC8},
    {1035, {0x4010FD70}, {0x1A769800}, 0x5E284},
    {1035, {0x400DB738}, {0x1A7C8000}, 0x49AB4},
    {1035, {0x400E9864}, {0x1A812000}, 0x59DC0},
    {1035, {0x400B7718}, {0x1A86C000}, 0x50288},
    {1035, {0x400D87FC}, {0x1A8BC800}, 0x47BC4},
    {1035, {0x400D643C}, {0x1A904800}, 0x4E3AC},
    {1035, {0x400D5C7C}, {0x1A953000}, 0x48D9C},
    {1035, {0x400B767C}, {0x1A99C000}, 0x47518},
    {1035, {0x400441F8}, {0x1A9E3800}, 0x1AA84},
    {1035, {0x40106568}, {0x1A9FE800}, 0x68C10},
    {1035, {0x4010E5A0}, {0xE97A800}, 0x9BCAC},
    {1035, {0x40016980}, {0xEA16800}, 54980},
    {1035, {0x40016980}, {0xEA24000}, 51524},
    {1035, {0x40016980}, {0xEA31000}, 59136},
    {1035, {0x40016980}, {0xEA3F800}, 54860},
    {1035, {0x40016980}, {0xEA4D000}, 51456},
    {1035, {0x40016980}, {0xEA5A000}, 53244},
    {1035, {0x40016980}, {0xEA67000}, 55072},
    {1035, {0x40016980}, {0xEA74800}, 54988},
    {1035, {0x40016980}, {0xEA82000}, 53788},
    {1035, {0x40016980}, {0xEA8F800}, 53436},
    {1035, {0x40016980}, {0xEA9D000}, 46404},
    {1035, {0x40016980}, {0xEAA8800}, 50424},
    {1035, {0x400ADFFC}, {0x18AEE800}, 0x4BAB0},
    {1035, {0x4037CF5C}, {0x18B3A800}, 0x208AF0},
    {1035, {0x4000A820}, {0x18ED3800}, 14168},
    {1035, {0x4011EC24}, {0x18F0E000}, 0xD8818},
    {1035, {0x400193E8}, {0x191B8800}, 35288},
    {1035, {0x4006C850}, {0x6C96000}, 0x2C884},
    {1035, {0x4005B178}, {0x6CC3000}, 0x3555C},
    {1035, {0x401EB174}, {0x18D43800}, 0xFB220},
    {1035, {0x4001ED60}, {0x1AA67800}, 53232},
    {1035, {0x4000BF30}, {0x1AA74800}, 9952},
    {1035, {0x40003498}, {0x1AA77000}, 3624},
    {1035, {0x4000BDE0}, {0x1AA78000}, 9460},
    {1035, {0x40006088}, {0x1AA7A800}, 4752},
    {1035, {0x400049F0}, {0x1AA7C000}, 6388},
    {1035, {0x40005ECC}, {0x1AA7E000}, 7480},
    {1035, {0x40002670}, {0x1AA80000}, 3048},
    {0, {0x28240}, {0x1AA81000}, 0x28240},
    {0, {0x28240}, {0x1AAA9800}, 0x28240},
    {0, {0x28240}, {0x1AAD2000}, 0x28240},
    {0, {0x28240}, {0x1AAFA800}, 0x28240},
    {0, {0x28240}, {0x1AB23000}, 0x28240},
    {0, {0x28240}, {0x1AB4B800}, 0x28240},
    {0, {0x28240}, {0x1AB74000}, 0x28240},
    {0, {0x28240}, {0x1AB9C800}, 0x28240},
    {0, {0x28240}, {0x1ABC5000}, 0x28240},
    {0, {0x28240}, {0x1ABED800}, 0x28240},
    {0, {0x28240}, {0x1AC16000}, 0x28240},
    {0, {0x28240}, {0x1AC3E800}, 0x28240},
    {0, {0x28240}, {0x1AC67000}, 0x28240},
    {0, {0x28240}, {0x1AC8F800}, 0x28240},
    {0, {0x28240}, {0x1ACB8000}, 0x28240},
    {0, {0x28240}, {0x1ACE0800}, 0x28240},
    {0, {0x28240}, {0x1AD09000}, 0x28240},
};
u8 lbl_800EF3B0[192] = {
    0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 1, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 1, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    1, 1, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 1, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u8 lbl_800EF470[64] = {
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255,
    0, 1, 0, 255, 13, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
s32 lbl_800EF4B0[6] = {0, 1, 2, 3, 4, 5};

// .sdata 0x803CB7C8..0x803CB7D8
u16 lbl_803CB7C8[2] = {21, 9};
u8 lbl_803CB7CC[8] = {0, 1, 2, 3, 4, 5, 6, 0}; // NOTE: type size 0x8 != symbol size 0xC

