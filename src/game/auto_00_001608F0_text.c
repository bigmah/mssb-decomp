#include "game/auto_00_001608F0_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "main/file_80024184.h" // StarMissionIndex, StarMission

extern StarMissionIndex lbl_800E8558[54]; // per character
extern StarMission lbl_80109AE8[][10];    // star missions, per mission row

// Signed view of a mission status: -1 COMPLETED_CONDITIONALLY, -2 COMPLETED_SAVED.
#define MISSION_STATUS(t, i) (*(s8*)&(t)->inGameMissionTracker[i].starMissionStatus)

#if !NONMATCHING
// Switch jump tables of fn_3_1608F0; mwcc emits them itself once the function matches.
void* jumptable_3_data_28418[8] = {
    (u8*)fn_3_1608F0 + 0x58, (u8*)fn_3_1608F0 + 0x1B8, (u8*)fn_3_1608F0 + 0x2A0, (u8*)fn_3_1608F0 + 0x37C,
    (u8*)fn_3_1608F0 + 0x75C, (u8*)fn_3_1608F0 + 0x458, (u8*)fn_3_1608F0 + 0x534, (u8*)fn_3_1608F0 + 0x600,
};
#endif

// .text:0x001608F0 size:0x788 mapped:0x8079F984
// NONMATCHING 99.8%: g_Minigame/lbl_800E8558 base registers swapped in the prologue, and the final
// store is `li 0xFF` instead of `li -1` (the original's status field is signed there).
#if NONMATCHING
// Minigame star-mission progress event: marks the first matching open mission of the
// human player's captain as completed (STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY).
void fn_3_1608F0(s32 kind, s32 value, s32 extra) {
    BOOL found;
    StarMissionIndex* idx = &lbl_800E8558[g_Minigame.minigameControlStruct[0].charID[g_d_GameSettings._35]];
    u8 row;
    u8 trk;
    ChallengeTrackingStruct* t;
    StarMission* m;
    s32 i;

    found = FALSE;
    trk = idx->trackerIndex;
    row = idx->missionRow;

    switch (kind) {
    case 0:
        t = &starMissionCompletionTracker[trk];
        m = lbl_80109AE8[row];
        for (i = 0; i < 10; i++) {
            if (MISSION_STATUS(t, i) >= 0) {
                switch (m[i].type) {
                case 0x32:
                    if (value >= m[i].target) {
                        found = TRUE;
                        goto done;
                    }
                    break;
                }
            }
        }
        break;
    case 1:
        t = &starMissionCompletionTracker[trk];
        m = lbl_80109AE8[row];
        for (i = 0; i < 10; i++) {
            if (MISSION_STATUS(t, i) >= 0) {
                switch (m[i].type) {
                case 0x33:
                    if (extra != 0) {
                        MISSION_STATUS(t, i)++;
                        if (MISSION_STATUS(t, i) >= m[i].target) {
                            found = TRUE;
                            goto done;
                        }
                    } else {
                        MISSION_STATUS(t, i) = 0;
                    }
                    break;
                }
            }
        }
        break;
    case 2:
        t = &starMissionCompletionTracker[trk];
        m = lbl_80109AE8[row];
        for (i = 0; i < 10; i++) {
            if (MISSION_STATUS(t, i) >= 0) {
                switch (m[i].type) {
                case 0x34:
                    if (extra >= 15) {
                        MISSION_STATUS(t, i)++;
                        if (MISSION_STATUS(t, i) >= m[i].target) {
                            found = TRUE;
                            goto done;
                        }
                    }
                    break;
                }
            }
        }
        break;
    case 3:
        t = &starMissionCompletionTracker[trk];
        m = lbl_80109AE8[row];
        for (i = 0; i < 10; i++) {
            if (MISSION_STATUS(t, i) >= 0) {
                switch (m[i].type) {
                case 0x35:
                    if (value == 2) {
                        MISSION_STATUS(t, i)++;
                        if (MISSION_STATUS(t, i) >= m[i].target) {
                            found = TRUE;
                            goto done;
                        }
                    }
                    break;
                }
            }
        }
        break;
    case 5:
        t = &starMissionCompletionTracker[trk];
        m = lbl_80109AE8[row];
        for (i = 0; i < 10; i++) {
            if (MISSION_STATUS(t, i) >= 0) {
                switch (m[i].type) {
                case 0x37:
                    if (value == 4) {
                        MISSION_STATUS(t, i)++;
                        if (MISSION_STATUS(t, i) >= m[i].target) {
                            found = TRUE;
                            goto done;
                        }
                    }
                    break;
                }
            }
        }
        break;
    case 6:
        t = &starMissionCompletionTracker[trk];
        m = lbl_80109AE8[row];
        for (i = 0; i < 10; i++) {
            if (MISSION_STATUS(t, i) >= 0) {
                switch (m[i].type) {
                case 0x38:
                    MISSION_STATUS(t, i)++;
                    if (MISSION_STATUS(t, i) >= m[i].target) {
                        found = TRUE;
                        goto done;
                    }
                    break;
                }
            }
        }
        break;
    case 7:
        t = &starMissionCompletionTracker[trk];
        m = lbl_80109AE8[row];
        for (i = 0; i < 10; i++) {
            if (MISSION_STATUS(t, i) >= 0) {
                switch (m[i].type) {
                case 0x39:
                    if (value == m[i].target) {
                        found = TRUE;
                        goto done;
                    }
                    break;
                }
            }
        }
        break;
    }
done:
    if (found) {
        starMissionCompletionTracker[trk].inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
    }
}
#endif

// .text:0x00161078 size:0x510 mapped:0x807A010C
// NONMATCHING 90%: the original re-reads m->flags in each step of the unrolled mode-mask loop
// and allocates the prologue pointers differently.
#if NONMATCHING
// End of a minigame: re-checks the captain's conditionally completed missions, completes the
// end-of-game ones (types 0x2F/0x30/0x31/0x36), then turns every tracker's completed missions
// into STAR_MISSION_TRACKING_COMPLETED_SAVED and resets the rest.
void fn_3_161078(void) {
    GameInitVariables* gs = &g_d_GameSettings;
    s32 human = gs->_35; // the human player's minigame slot
    u8* place = &g_Minigame.minigameControlStruct[0]._1C[human];
    s16* points = &g_Minigame.miniGameCurrentPoints[human];
    u8 mode = g_Minigame.GameMode_MiniGame;
    u8* p1CB1 = &g_Minigame._1CB1[human];
    StarMissionIndex* idx = &lbl_800E8558[g_Minigame.minigameControlStruct[0].charID[human]];
    u8 difficulty = gs->challengeDifficulty;
    ChallengeTrackingStruct* t = &starMissionCompletionTracker[idx->trackerIndex];
    StarMission* m = lbl_80109AE8[idx->missionRow];
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 10; i++, m++) {
        s8 status = MISSION_STATUS(t, i);
        s16 flags;

        if (status == -2) {
            continue;
        }
        if (status == -1) {
            flags = m->flags;
            if (flags & 2) {
                if (difficulty < 1) {
                    MISSION_STATUS(t, i) = 0;
                }
            } else if (flags & 4) {
                if (difficulty < 2) {
                    MISSION_STATUS(t, i) = 0;
                }
            } else if (flags & 8) {
                if (difficulty < 3) {
                    MISSION_STATUS(t, i) = 0;
                }
            }
            if ((m->flags & 1) && *place != 1) {
                MISSION_STATUS(t, i) = 0;
            }
            continue;
        }

        flags = m->flags;
        if (flags & 2) {
            if (difficulty < 1) {
                continue;
            }
        } else if (flags & 4) {
            if (difficulty < 2) {
                continue;
            }
        } else if (flags & 8) {
            if (difficulty < 3) {
                continue;
            }
        }
        if ((flags & 1) && *place != 1) {
            continue;
        }

        {
            BOOL limited = FALSE;
            BOOL modeOk = FALSE;

            for (k = 0; k < 7; k++) {
                if (m->flags & (0x10 << k)) {
                    limited = TRUE;
                    if (mode == k) {
                        modeOk = TRUE;
                    }
                }
            }
            if (limited && !modeOk) {
                continue;
            }
        }

        switch (m->type) {
        case 0x2F:
            if (*place <= m->target) {
                MISSION_STATUS(t, i) = -1;
            }
            break;
        case 0x30: {
            s32 target = m->target;

            if (mode == 1 || mode == 3) {
                target *= 100;
            } else if (mode == 0 || mode == 2) {
                target *= 10;
            }
            if (*points >= target) {
                MISSION_STATUS(t, i) = -1;
            }
            break;
        }
        case 0x31: {
            s32 rivals = 0;
            s32 beaten = 0;

            for (j = 0; j < 4; j++) {
                if (g_Minigame.minigameControlStruct[0].characterIndex[j] >= 0 && j != human &&
                    m->target == lbl_800E8558[g_Minigame.minigameControlStruct[0].charID[j]].missionRow) {
                    rivals++;
                    if (*place < g_Minigame.minigameControlStruct[0]._1C[j]) {
                        beaten++;
                    }
                }
            }
            if (rivals != 0 && beaten == rivals && *place == 1) {
                MISSION_STATUS(t, i) = -1;
            }
            break;
        }
        case 0x36:
            if (mode == 5 && *p1CB1 <= m->target) {
                MISSION_STATUS(t, i) = -1;
            }
            break;
        }
    }

    for (j = 0; j < 54; j++) {
        t = &starMissionCompletionTracker[j];
        for (i = 0; i < 10; i++) {
            if (MISSION_STATUS(t, i) <= -1) {
                MISSION_STATUS(t, i) = -2;
            } else {
                MISSION_STATUS(t, i) = 0;
            }
        }
    }
}
#endif
