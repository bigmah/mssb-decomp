// REL module table. On the GameCube main.dol loads menus.rel/game.rel (and
// challenge.rel) from aaaa.dat, links them with OSLink and calls their
// _prolog/_epilog. On PC the modules are linked into the executable; each
// module's _prolog/_epilog/_unresolved are renamed per module at compile time
// (port/CMakeLists.txt) and the game's load path (fn_800097A0,
// src/main/file_80008E00.c) calls these instead.

#include <dolphin/os.h>

#include <stdio.h>
#include <string.h>

void menus_prolog(void);
void menus_epilog(void);
void game_prolog(void);
void game_epilog(void);
void challenge_prolog(void);
void challenge_epilog(void);
void challenge_unresolved(void);

typedef struct PortModule {
    const char* name;
    OSModuleID id;    // the REL's module id
    s32 dllIndex;     // index in main.dol's DLL file table (lbl_800E8AA8)
    void (*prolog)(void);
    void (*epilog)(void);
    void (*unresolved)(void);
    OSModuleHeader header; // stands in for the loaded REL image
} PortModule;

static PortModule s_modules[] = {
    {"menus", 2, 0, menus_prolog, menus_epilog, NULL},
    {"game", 3, 1, game_prolog, game_epilog, NULL},
    {"challenge", 1, 2, challenge_prolog, challenge_epilog, challenge_unresolved},
};

static PortModule* find_by_header(OSModuleHeader* header)
{
    for (size_t i = 0; i < sizeof(s_modules) / sizeof(s_modules[0]); i++)
    {
        if (&s_modules[i].header == header)
            return &s_modules[i];
    }
    return NULL;
}

OSModuleHeader* port_module_load(s32 dllIndex)
{
    for (size_t i = 0; i < sizeof(s_modules) / sizeof(s_modules[0]); i++)
    {
        PortModule* m = &s_modules[i];
        if (m->dllIndex == dllIndex)
        {
            memset(&m->header, 0, sizeof(m->header));
            m->header.info.id = m->id;
            return &m->header;
        }
    }
    fprintf(stderr, "[modules] unknown DLL index %d\n", (int)dllIndex);
    return NULL;
}

void port_module_prolog(OSModuleHeader* header)
{
    PortModule* m = find_by_header(header);
    if (m == NULL)
        return;
    fprintf(stderr, "[modules] %s: prolog\n", m->name);
    m->prolog();
}

void port_module_epilog(OSModuleHeader* header)
{
    PortModule* m = find_by_header(header);
    if (m == NULL)
        return;
    fprintf(stderr, "[modules] %s: epilog\n", m->name);
    m->epilog();
}
