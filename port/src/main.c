// PC entry point (stub). Phase 2/3: bring up aurora (aurora_initialize), open
// the disc through aurora's DVD layer, set up the game heap and the REL module
// table, then call the game's original main() (renamed to game_main).

#include <stdio.h>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    fprintf(stderr, "mssb: the PC port does not run yet (see port/STATUS.md)\n");
    return 1;
}
