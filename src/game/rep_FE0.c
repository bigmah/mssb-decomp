#include "game/rep_FE0.h"
#define REP_HEADER_FN repHeader_FE0
#include "header_rep_inline.h"
#include "game/rep_1838.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0009CD90_text.h" // InMemFielderType g_Fielders[9]
#include "game/auto_00_000249E8_text.h" // SceneWork
#include "main/file_80011640.h"         // CharMgr lbl_8036E548

extern FielderAnimState g_UnkAnimation_31EAC[];
extern u8 lbl_3_data_69C0[];
extern SceneWork* lbl_3_common_bss_1323C;

// .text:0x0006B144 size:0x384 mapped:0x806AA1D8
void fn_3_6B144(void) {
    CharActor* p;
    CharActor* q;
    int j;
    int i;
    InMemFielderType* fielders;
    FielderAnimState* anims;
    u8* flags;
    u8 st;

    st = g_GameLogic.gameStatus;
    if (st != 0 && st != 1 && st != 2 && st != 8 && st != 3 && st != 0x16 && st != 0x1A &&
        (g_d_GameSettings.GameModeSelected != 6 || st != 0xB)) {
        for (j = 0; j < 9; j++) {
            q = lbl_8036E548.active[j];
            if (q != NULL) {
                q->mode[0] = 0;
            }
        }
        return;
    }
    for (i = 0; i < 9; i++) {
        f32 f;
        f32 z;
        p = lbl_8036E548.active[i];
        fielders = &g_Fielders[i];
        anims = &g_UnkAnimation_31EAC[i];
        flags = &lbl_3_data_69C0[i];
        if (p != NULL) {
            p->mode[0] = 0;
            p->_275 = fielders->_1E6;
            if (g_GameLogic.gameStatus == 3) {
                continue;
            }
            if (g_d_GameSettings.GameModeSelected == 2 &&
                (g_GameLogic.secondaryGameMode == 0xE || g_Practice.practiceLevel == 4 ||
                 ((g_GameLogic.secondaryGameMode == 0xB || g_GameLogic.secondaryGameMode == 0xC) && i > 0))) {
                continue;
            }
            p->mode[0] = 1;
            if (anims->_42 == 0) {
                p->pos.x = fielders->pos.x;
                p->pos.y = -fielders->pos.y - fielders->height;
                p->pos.z = fielders->pos.z;
            }
            f = fn_3_6AF9C(i);
            if (fielders->_20A != 0) {
                f = anims->rotY;
            }
            p->rot.y = f;
            z = 0.0f;
            p->rot.x = z;
            p->rot.z = z;
            anims->rotY = f;
            if (fielders->_263 != 0) {
                p->mode[0] = 2;
            }
            if (g_Stats.replayInd != 0) {
                p->mode[0] = lbl_3_common_bss_1323C->animSet[i];
            } else {
                if (i == 1) {
                    u8 s = g_GameLogic.gameStatus;
                    if (s == 1 || !s || s == 7 || s == 0x16 || g_GameLogic.sceneID == 1) {
                        p->mode[0] = 2;
                    }
                    if (g_GameLogic.sceneID == 3) {
                        p->mode[0] = 1;
                    }
                } else if (*flags != 0) {
                    u8 s = g_GameLogic.gameStatus;
                    if (s == 1 || !s || s == 7 || s == 0x16 || g_GameLogic.sceneID == 1) {
                        p->mode[0] = 2;
                    }
                    if (g_GameLogic.sceneID == 3) {
                        p->mode[0] = 1;
                    }
                }
            }
            {
                u8 t = fielders->_205;
                if (t == 1 || (u8)(t - 2) <= 3 || t == 6) {
                    p->mode[0] = 3;
                }
            }
        }
    }
}

// .text:0x0006AF9C size:0x1A8 mapped:0x806AA030
f32 fn_3_6AF9C(int idx) {
    InMemFielderType* fielder = &g_Fielders[idx];
    FielderAnimState* anim = &g_UnkAnimation_31EAC[idx];
    f32 base = fn_3_9FEA8(-fielder->facing - 1.5707964f);
    int a;
    int b;
    int diff;
    if (fielder->_1FC != 0) {
        return base;
    }
    a = radToShortAngle(base);
    b = radToShortAngle(anim->rotY);
    diff = fn_3_9FCA4(b, a);
    if (diff > 0x800) {
        diff -= 0x1000;
    } else if (diff <= -0x800) {
        diff += 0x1000;
    }
    if (diff > 0x600) {
        if (fielder->handedness == 0) {
            b -= 0x280;
        } else {
            b += 0x280;
        }
    } else if (diff < -0x600) {
        if (fielder->handedness == 0) {
            b -= 0x280;
        } else {
            b += 0x280;
        }
    } else if (diff > 0x200) {
        b -= 0x180;
    } else if (diff < -0x200) {
        b += 0x180;
    } else if (diff > 0x180) {
        b -= 0x100;
    } else if (diff < -0x180) {
        b += 0x100;
    } else if (diff > 0xC0) {
        b -= 0x80;
    } else if (diff < -0xC0) {
        b += 0x80;
    } else if (diff > 0x60) {
        b -= 0x40;
    } else if (diff < -0x60) {
        b += 0x40;
    } else {
        return base;
    }
    return shortAngleToRad(b);
}
