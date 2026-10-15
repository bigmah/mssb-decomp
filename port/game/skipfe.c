// Skip the front end (PC only): with `skipfe = true` in user.ini the boot task
// (fn_800097A0) loads game.rel instead of menus.rel, after setting up an
// exhibition game the way the menus would: the character stats file, both
// teams' rosters and batting orders, the captains and the stadium.
//
// The other eight players of each team are picked the way the team menu's
// random-team option does it (fn_2_2FC0).
#include "mssbTypes.h"
#include "static/GameSettings.h"
#include "game/character_stats.h"
#include "main/charsel_state_type.h"
#include "main/aramloader.h"
#include "main/menu_globals.h" // SavedSettings
extern SavedSettings lbl_800E8754; // main/file_8004207C.h
#include "main/file_800639BC.h" // TeamSelect lbl_803C6724

extern void* ARAMTransfer(void* instr, void* dest, u8 mode, u32 aramAddr);
extern CharSelectState lbl_8034E9A0;
extern CharacterStats inMemRoster[2][9];
extern u8 lbl_80354720[2][9][4]; // batting order entries
extern u32 lbl_3_data_0[4];      // stats file record (game.rel's copy)
extern void fn_2_2FC0(u8 mode, s32 b, s32 c); // menus: build both teams

const char* port_user_ini_get(const char* key);
int port_user_ini_bool(const char* key);
s32 port_star_skills_enabled(void);
s32 port_scope_stadium(s32 stadium); // port/game/menu_scope.c

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
    s32 stadium;
    s32 t;
    s32 i;

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
    stadium = port_scope_stadium(lookup(port_user_ini_get("stadium"), sStadiumNames, 6, STADIUM_ID_MARIO_STADIUM));
    fprintf(stderr, "[skipfe] captains %d vs %d, stadium %d\n", captain[0], captain[1], stadium);

    {
        // Online play: both peers' random picks (the menus' generator, seeded
        // from the clock at boot) come from the shared seed.
        extern u32 lbl_803CB750; // main/data_800E8300.c
        const char* seed = port_user_ini_get("seed");
        if (seed != NULL) {
            lbl_803CB750 = (u32)strtoul(seed, NULL, 10);
            fprintf(stderr, "[skipfe] seed %u\n", lbl_803CB750);
        }
    }
    port_swap_char_stats(sStats, 6 * 9);
    memcpy(&lbl_8034E9A0, sStats, 0x46E0); // stats and team presets, as the menus load them
    // As the "random teams" path of the team menu (fn_2_2FC0 mode 10): CPU
    // picks the other eight players around each captain, field positions
    // and batting orders are filled in, stats copied to inMemRoster.
    lbl_8034E9A0.captain[0] = captain[0];
    lbl_8034E9A0.captain[1] = captain[1];
    fn_2_2FC0(10, 0, 1);
    // Test option: `team1 = monty,toad` puts those characters in team 1's
    // non-captain slots (the CPU's random picks never guarantee one).
    for (t = 0; t < 2; t++) {
        const char* list = port_user_ini_get(t == 0 ? "team1" : "team2");
        char name[32];
        s32 slot = 0;
        while (list != NULL && *list != '\0') {
            s32 n = 0;
            s32 id;
            while (*list == ',' || *list == ' ') {
                list++;
            }
            while (*list != '\0' && *list != ',' && *list != ' ' && n < 31) {
                name[n++] = *list++;
            }
            name[n] = '\0';
            if (n == 0) {
                break;
            }
            id = lookup(name, sCharNames, 54, -1);
            while (slot < 9 && inMemRoster[t][slot].stats.CharID == captain[t]) {
                slot++;
            }
            if (id < 0 || slot >= 9) {
                continue;
            }
            inMemRoster[t][slot] = lbl_8034E9A0.roster[id / 9][id % 9];
            slot++;
        }
    }
    for (t = 0; t < 2; t++) {
        fprintf(stderr, "[skipfe] team %d:", t);
        for (i = 0; i < 9; i++) {
            fprintf(stderr, " %d", inMemRoster[t][i].stats.CharID);
        }
        fprintf(stderr, "\n");
    }
    lbl_8034E9A0.ports[0] = 0;
    lbl_8034E9A0.ports[1] = 0xFF;
    lbl_8034E9A0.ports[2] = 0xFF;
    lbl_8034E9A0.ports[3] = 0xFF;

    g_d_GameSettings.GameModeSelected = GAME_TYPE_EXHIBITION_GAME;
    g_d_GameSettings.exhibitionMatchInd = 1;
    g_d_GameSettings.StadiumID = stadium;
    g_d_GameSettings.humanTeamNumber = 1;
    g_d_GameSettings.PlayerPorts[0] = 0;
    g_d_GameSettings.PlayerPorts[1] = 4; // CPU
    if (port_user_ini_bool("human2")) {
        // Online play (port/web/net.js): a human on each team, port 1 playing
        // team 2, as the menus set up a two-player exhibition game.
        lbl_8034E9A0.ports[1] = 1;
        g_d_GameSettings.PlayerPorts[1] = 1;
        g_d_GameSettings._10 = 1; // 0: human vs CPU, 1: two humans
        fprintf(stderr, "[skipfe] two players\n");
    }
    {
        // Game length: the options menu's innings setting (1, 3, 5, 7 or 9).
        const char* v = port_user_ini_get("innings");
        if (v != NULL && atoi(v) >= 1 && atoi(v) <= 9) {
            lbl_800E8754.innings = (u8)atoi(v);
            fprintf(stderr, "[skipfe] innings %d\n", lbl_800E8754.innings);
        }
    }
    if (!port_star_skills_enabled()) {
        lbl_800E8754._04 = 0; // Star Skills locked off (port/game/menu_scope.c)
    }
    sState = 3;
    return TRUE;
}
