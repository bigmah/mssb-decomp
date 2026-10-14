// Online play (port/web/src/net_web.cpp): a hash of the game state both peers
// must agree on, compared every 60 frames. Any difference means the two games
// have gone different ways (a desync), and the page stops the game.
#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

extern GameScores g_Scores;          // game/auto_00_0009CD90_text.h
extern InMemFielderType g_Fielders[9];
extern u32 lbl_803CB750;             // the menus' random generator (seeded by skipfe)

typedef struct {
    u32 h;
} StateHasher;

static void add(StateHasher* s, const void* p, u32 n) {
    const u8* b = (const u8*)p;
    u32 i;
    for (i = 0; i < n; i++) {
        s->h = (s->h ^ b[i]) * 16777619u;
    }
}

unsigned int port_game_state_hash(unsigned int frame) {
    StateHasher s = {2166136261u};
    add(&s, &frame, sizeof(frame));
    add(&s, &lbl_803CB750, sizeof(lbl_803CB750));
    add(&s, &g_GameLogic, sizeof(g_GameLogic));
    add(&s, &g_Scores, sizeof(g_Scores));
    add(&s, &g_Strikes, sizeof(g_Strikes));
    // The ball (with the gameplay random seeds) and every player on the field.
    add(&s, &g_Ball, sizeof(g_Ball));
    add(&s, &g_Pitcher, sizeof(g_Pitcher));
    add(&s, &g_Batter, sizeof(g_Batter));
    add(&s, g_Runners, sizeof(g_Runners));
    add(&s, g_Fielders, sizeof(g_Fielders));
    return s.h;
}
