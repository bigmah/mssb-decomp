#include "game/rep_2BF8.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_00097144_text.h"
#include "game/rep_720.h"
#include "main/file_80011640.h"
#include "main/file_80069BDC.h"
#include "header_rep_data.h"

// Screen-edge limits of the off-screen player markers (lbl_3_data_D638).
typedef struct MarkerEdges {
    /*0x0*/ s16 leftFade;  // fade in from here ...
    /*0x2*/ s16 left;      // ... to here, and clamp to it
    /*0x4*/ s16 rightFade;
    /*0x6*/ s16 right;
    /*0x8*/ s16 topFade;
    /*0xA*/ s16 top;
    /*0xC*/ s16 bottomFade;
    /*0xE*/ s16 bottom;
} MarkerEdges;

extern MarkerEdges lbl_3_data_D638;
extern u16 lbl_3_data_91AC[]; // marker rotation per screen-edge direction (see fn_3_E9D30)

extern const f32 lbl_3_rodata_2C48; // 0.2f
extern const f32 lbl_3_rodata_2C4C; // 255.0f
extern const f32 lbl_3_rodata_2C50; // 1.0f

#define MARKER(task, i) (lbl_80371C30[(task)->u14.objIdx + (i)].obj)

static inline s32 fadeAlpha(s32 v, s32 from, s32 to) {
    return lbl_3_rodata_2C4C * (lbl_3_rodata_2C50 - (f32)(v - from) / (f32)(to - from));
}

// .text:0x000E9D30 size:0x610 mapped:0x80728DC4
// NONMATCHING 96%: saved-register numbering (dir/i/alpha) and a few scheduling swaps; same calls, stores and flow
#if NONMATCHING
// Minigame task: an arrow at the screen edge for each player that is off screen.
void fn_3_E9D30(void) {
    SceneTask* task = lbl_803CC1B8;
    Vec pos;
    int sx;
    int sy;
    s32 dir;
    s32 alphaX;
    s32 alphaY;
    s32 x;
    s32 y;
    s32 i;
    s32 k;
    s32 dx;
    s32 dz;

    if (lbl_3_common_bss_32724.hudOff == 0 && g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL &&
        g_Minigame._19CE == 0 && g_Minigame.turnOverStatus == 0) {
        for (i = 0; i < 3; i++) {
            if (g_Minigame.minigameControlStruct[0].fieldOrder[i] < 0) {
                continue;
            }
            dir = -1;
            alphaX = 0xFF;
            alphaY = 0xFF;
            getAnimRelatedCoordinates(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigameControlStruct[0].fieldOrder[i]], 4, &pos);
            if (fn_3_1650C(&sx, &sy, FALSE, pos.x, pos.y, pos.z) == 0) {
                // off screen: move the point toward the camera until it is on screen
                for (k = 0; k < 3; k++) {
                    dx = (s32)(g_pCamera->_284C.x - pos.x);
                    dz = (s32)(g_pCamera->_284C.z - pos.z);
                    dx = dx * lbl_3_rodata_2C48;
                    dz = dz * lbl_3_rodata_2C48;
                    pos.x += dx;
                    pos.z += dz;
                    if (fn_3_1650C(&sx, &sy, FALSE, pos.x, pos.y, pos.z) != 0) {
                        break;
                    }
                }
            }

            x = lbl_3_data_D638.left;
            if (sx <= x) {
                dir = 2;
                if (sx > lbl_3_data_D638.leftFade) {
                    alphaX = fadeAlpha(sx, lbl_3_data_D638.leftFade, x);
                }
            } else {
                x = lbl_3_data_D638.right;
                if (sx >= x) {
                    dir = 5;
                    if (sx < lbl_3_data_D638.rightFade) {
                        alphaX = fadeAlpha(sx, lbl_3_data_D638.rightFade, x);
                    }
                } else {
                    x = sx;
                }
            }
            if (alphaX > 0xFF) {
                alphaX = 0xFF;
            }

            y = lbl_3_data_D638.top;
            if (sy <= y) {
                dir += 1;
                if (sy > lbl_3_data_D638.topFade) {
                    alphaY = fadeAlpha(sy, lbl_3_data_D638.topFade, y);
                }
            } else {
                y = lbl_3_data_D638.bottom;
                if (sy >= y) {
                    dir += 2;
                    if (sy < lbl_3_data_D638.bottomFade) {
                        alphaY = fadeAlpha(sy, lbl_3_data_D638.bottomFade, y);
                    }
                } else {
                    y = sy;
                }
            }
            if (alphaY > 0xFF) {
                alphaY = 0xFF;
            }

            if (dir < 0 || alphaX <= 0 || alphaY <= 0) {
                MARKER(task, i)->flags &= ~2;
                continue;
            }
            MARKER(task, i)->flags |= 2;
            MARKER(task, i)->x = x;
            MARKER(task, i)->y = y;
            if (dir == 2 || dir == 5) {
                MARKER(task, i)->color = (MARKER(task, i)->color & ~0xFF) | alphaX;
            } else if (dir >= 2) {
                // corner: the stronger of the two
                if (alphaX > alphaY) {
                    MARKER(task, i)->color = (MARKER(task, i)->color & ~0xFF) | alphaX;
                } else {
                    MARKER(task, i)->color = (MARKER(task, i)->color & ~0xFF) | alphaY;
                }
            } else {
                MARKER(task, i)->color = (MARKER(task, i)->color & ~0xFF) | alphaY;
            }
            MARKER(task, i)->_5C = lbl_3_data_91AC[dir] << 16;
        }
        return;
    }
    lbl_3_common_bss_32724._97 = 0;
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}
#endif
