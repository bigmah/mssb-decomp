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

// .text:0x8001FE00 size:0x248
void fn_8001FE00(LayoutGroup* group) {
    return;
}

// .text:0x80020048 size:0x1D0
s32 calledWhenStartingMatch(void) {
    return 0;
}

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
    return;
}

// .text:0x80020624 size:0xD8
void fn_80020624(void) {
    return;
}

// .text:0x800206FC size:0x968
void fn_800206FC(void) {
    return;
}

// .text:0x80021064 size:0x124
void fn_80021064(void) {
    return;
}

// .text:0x80021188 size:0x34
s32 fn_80021188(void) {
    return 0;
}

// .text:0x800211BC size:0x34
s32 fn_800211BC(void) {
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
    return;
}

// .text:0x8002128C size:0x7C
void fn_8002128C(u8 mode) {
    return;
}
