// Skip the front end (PC only): with `skipfe = true` in user.ini the boot task
// (fn_800097A0) loads game.rel instead of menus.rel, after setting up an
// exhibition game the way the menus would: the character stats file, both
// teams' rosters and batting orders, the captains and the stadium.
//
// The teams are the stats file's rows of nine characters (row = id / 9, the
// same rows game.rel's debug team picker uses, rep_0.c maybeProcessTeamData);
// each captain picks the row it is in. Batting orders come from the stats
// file's presets for those rows.
#include "mssbTypes.h"
#include "static/GameSettings.h"
#include "game/character_stats.h"
#include "main/charsel_state_type.h"
#include "main/aramloader.h"
#include "main/file_800639BC.h" // TeamSelect lbl_803C6724

extern void* ARAMTransfer(void* instr, void* dest, u8 mode, u32 aramAddr);
extern CharSelectState lbl_8034E9A0;
extern CharacterStats inMemRoster[2][9];
extern u8 lbl_80354720[2][9][4]; // batting order entries
extern u32 lbl_3_data_0[4];      // stats file record (game.rel's copy)

const char* port_user_ini_get(const char* key);
int port_user_ini_bool(const char* key);

static const char* const sCharNames[] = {
    "mario", "luigi", "dk", "diddy", "peach", "daisy", "yoshi", "babymario", "babyluigi",
    "bowser", "wario", "waluigi", "koopa", "toad", "boo", "toadette", "shyguy", "birdo",
    "monty", "bowserjr", "paratroopa", "piantablue", "piantared", "piantayellow", "nokiblue", "nokired",
    "nokigreen", "hammerbro", "toadsworth", "toadblue", "toadyellow", "toadgreen", "toadpurple",
    "magikoopablue", "magikoopared", "magikoopagreen", "magikoopayellow", "kingboo", "petey", "dixie",
    "goomba", "paragoomba", "koopared", "paratroopagreen", "shyguyblue", "shyguyyellow", "shyguygreen",
    "shyguyblack", "drybonesgray", "drybonesgreen", "drybonesred", "drybonesblue", "firebro", "boomerangbro",
};

static const char* const sStadiumNames[] = {"mario", "bowser", "wario", "yoshi", "peach", "dk"};

static s32 lookup(const char* value, const char* const* names, s32 count, s32 fallback) {
    s32 i;
    if (value == NULL) {
        return fallback;
    }
    if (value[0] >= '0' && value[0] <= '9') {
        return atoi(value);
    }
    for (i = 0; i < count; i++) {
        if (strcasecmp(value, names[i]) == 0) {
            return i;
        }
    }
    fprintf(stderr, "[skipfe] unknown name '%s'\n", value);
    return fallback;
}

static s32 sState = -1; // -1: not decided yet
static u8* sStats;

// TRUE while skipfe still has to set the game up (checked by fn_800097A0).
BOOL port_skipfe_pending(void) {
    if (sState < 0) {
        sState = port_user_ini_bool("skipfe") ? 0 : 3;
    }
    return sState < 3;
}

// Runs one step; returns TRUE once the game can be loaded.
BOOL port_skipfe_step(void) {
    s32 captain[2];
    s32 row[2];
    s32 stadium;
    s32 t;
    s32 i;
    s32 j;

    switch (sState) {
    case 0:
        sStats = ARAMTransfer(lbl_3_data_0, NULL, 1, 0);
        sState = 1;
        return FALSE;
    case 1:
        if ((s32)(u8)lbl_803C6CF8.idle != 1) {
            return FALSE;
        }
        break;
    default:
        return TRUE;
    }

    captain[0] = lookup(port_user_ini_get("captain1"), sCharNames, 54, CHAR_ID_MARIO);
    captain[1] = lookup(port_user_ini_get("captain2"), sCharNames, 54, CHAR_ID_BOWSER);
    stadium = lookup(port_user_ini_get("stadium"), sStadiumNames, 6, STADIUM_ID_MARIO_STADIUM);
    fprintf(stderr, "[skipfe] captains %d vs %d, stadium %d\n", captain[0], captain[1], stadium);

    port_swap_char_stats(sStats, 6 * 9);
    memcpy(&lbl_8034E9A0, sStats, 0x46E0); // stats and team presets, as the menus load them
    for (t = 0; t < 2; t++) {
        const u8* preset;
        row[t] = captain[t] / 9;
        memcpy(inMemRoster[t], sStats + row[t] * 9 * sizeof(CharacterStats), 9 * sizeof(CharacterStats));
        // Batting order from the preset of that row (see maybeProcessTeamData).
        preset = sStats + 0x4380 + row[t] * 0x48;
        for (i = 0; i < 9; i++) {
            u8* e = lbl_80354720[t][i];
            e[0] = i;
            e[1] = 10;
            e[2] = 10;
            e[3] = 0;
            for (j = 0; j < 9; j++) {
                if (preset[j] == i) {
                    break;
                }
            }
            if (j < 9) {
                e[1] = j;
                e[2] = preset[j + 9];
                e[3] = 1;
            }
            lbl_803C6724.picks[t][i] = row[t] * 9 + i;
            lbl_803C6724.pos[t][i] = e[2];
        }
        lbl_8034E9A0.captain[t] = captain[t];
        lbl_8034E9A0.captainSlot[t] = captain[t] % 9;
        lbl_8034E9A0.captainVariant[t] = 0;
        lbl_8034E9A0.teamRating[t] = 3;
    }
    lbl_8034E9A0.ports[0] = 0;
    lbl_8034E9A0.ports[1] = 0xFF;
    lbl_8034E9A0.ports[2] = 0xFF;
    lbl_8034E9A0.ports[3] = 0xFF;

    g_d_GameSettings.GameModeSelected = GAME_TYPE_EXHIBITION_GAME;
    g_d_GameSettings.exhibitionMatchInd = 1;
    g_d_GameSettings.StadiumID = stadium;
    g_d_GameSettings.maybeHomeAway = row[0];
    g_d_GameSettings.maybeHomeAway2 = row[1];
    g_d_GameSettings.humanTeamNumber = 1;
    g_d_GameSettings.PlayerPorts[0] = 0;
    g_d_GameSettings.PlayerPorts[1] = 4; // CPU
    sState = 3;
    return TRUE;
}
