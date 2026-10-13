// REL module table. On the GameCube main.dol loads menus.rel/game.rel (and
// challenge.rel) from aaaa.dat, links them with OSLink and calls their
// _prolog/_epilog. On PC the modules are linked into the executable; each
// module's _prolog/_epilog/_unresolved are renamed per module at compile time
// (port/CMakeLists.txt) and the game's load path (fn_800097A0,
// src/main/file_80008E00.c) calls these instead.

#include <dolphin/os.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Each module's data and bss sections (port/include/port/module_sections.h).
typedef struct ModuleSections {
    char* dataStart;
    char* dataEnd;
    char* bssStart;
    char* bssEnd;
} ModuleSections;

#if defined(__EMSCRIPTEN__)
#define MODULE_SECTIONS(tag) {NULL, NULL, NULL, NULL}
#elif defined(__APPLE__)
#define MODULE_SECTION_BOUNDS(tag)                                                       \
    extern char tag##_ds __asm("section$start$__DATA$__mssb_" #tag "_d");               \
    extern char tag##_de __asm("section$end$__DATA$__mssb_" #tag "_d");                 \
    extern char tag##_bs __asm("section$start$__DATA$__mssb_" #tag "_b");               \
    extern char tag##_be __asm("section$end$__DATA$__mssb_" #tag "_b");
#define MODULE_SECTIONS(tag) {&tag##_ds, &tag##_de, &tag##_bs, &tag##_be}
#else
#define MODULE_SECTION_BOUNDS(tag)                                                       \
    extern char __start_mssb_##tag##_d[] __attribute__((weak));                          \
    extern char __stop_mssb_##tag##_d[] __attribute__((weak));                           \
    extern char __start_mssb_##tag##_b[] __attribute__((weak));                          \
    extern char __stop_mssb_##tag##_b[] __attribute__((weak));
#define MODULE_SECTIONS(tag)                                                             \
    {__start_mssb_##tag##_d, __stop_mssb_##tag##_d, __start_mssb_##tag##_b, __stop_mssb_##tag##_b}
#endif
#ifdef MODULE_SECTION_BOUNDS
MODULE_SECTION_BOUNDS(chal)
MODULE_SECTION_BOUNDS(menu)
MODULE_SECTION_BOUNDS(game)
#endif

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
    ModuleSections sections;
    void* dataImage; // the module's .data as linked (copied before the first prolog)
    OSModuleHeader header; // stands in for the loaded REL image
} PortModule;

static PortModule s_modules[] = {
    {"menus", 2, 0, menus_prolog, menus_epilog, NULL, MODULE_SECTIONS(menu)},
    {"game", 3, 1, game_prolog, game_epilog, NULL, MODULE_SECTIONS(game)},
    {"challenge", 1, 2, challenge_prolog, challenge_epilog, challenge_unresolved, MODULE_SECTIONS(chal)},
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
    // As a freshly linked REL: .data as on disc, .bss zeroed.
    ModuleSections* sec = &m->sections;
    if (sec->dataStart != NULL && sec->dataEnd > sec->dataStart)
    {
        size_t n = (size_t)(sec->dataEnd - sec->dataStart);
        if (m->dataImage == NULL)
        {
            m->dataImage = malloc(n);
            memcpy(m->dataImage, sec->dataStart, n);
        }
        else
        {
            memcpy(sec->dataStart, m->dataImage, n);
        }
    }
    if (sec->bssStart != NULL && sec->bssEnd > sec->bssStart)
        memset(sec->bssStart, 0, (size_t)(sec->bssEnd - sec->bssStart));
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
