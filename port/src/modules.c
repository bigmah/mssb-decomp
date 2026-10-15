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

// Each module's data and bss ranges (port/include/port/module_sections.h):
// one range each natively; on the web build one for the module's sources and
// one for its generated data (port/gen), bracketed by marker objects.
typedef struct ModuleSections {
    char* dataStart;
    char* dataEnd;
    char* bssStart;
    char* bssEnd;
    char* dataStart2;
    char* dataEnd2;
    char* bssStart2;
    char* bssEnd2;
} ModuleSections;

#if defined(__EMSCRIPTEN__)
#define MODULE_SECTION_BOUNDS(tag, module)                                               \
    extern char mssb_##module##_src_d_begin, mssb_##module##_src_d_end;                  \
    extern char mssb_##module##_src_b_begin, mssb_##module##_src_b_end;                  \
    extern char mssb_##module##_gen_d_begin, mssb_##module##_gen_d_end;                  \
    extern char mssb_##module##_gen_b_begin, mssb_##module##_gen_b_end;
#define MODULE_SECTIONS(tag, module)                                                     \
    {&mssb_##module##_src_d_begin, &mssb_##module##_src_d_end,                           \
     &mssb_##module##_src_b_begin, &mssb_##module##_src_b_end,                           \
     &mssb_##module##_gen_d_begin, &mssb_##module##_gen_d_end,                           \
     &mssb_##module##_gen_b_begin, &mssb_##module##_gen_b_end}
#elif defined(__APPLE__)
#define MODULE_SECTION_BOUNDS(tag, module)                                               \
    extern char tag##_ds __asm("section$start$__DATA$__mssb_" #tag "_d");               \
    extern char tag##_de __asm("section$end$__DATA$__mssb_" #tag "_d");                 \
    extern char tag##_bs __asm("section$start$__DATA$__mssb_" #tag "_b");               \
    extern char tag##_be __asm("section$end$__DATA$__mssb_" #tag "_b");
#define MODULE_SECTIONS(tag, module) {&tag##_ds, &tag##_de, &tag##_bs, &tag##_be}
#else
#define MODULE_SECTION_BOUNDS(tag, module)                                               \
    extern char __start_mssb_##tag##_d[] __attribute__((weak));                          \
    extern char __stop_mssb_##tag##_d[] __attribute__((weak));                           \
    extern char __start_mssb_##tag##_b[] __attribute__((weak));                          \
    extern char __stop_mssb_##tag##_b[] __attribute__((weak));
#define MODULE_SECTIONS(tag, module)                                                     \
    {__start_mssb_##tag##_d, __stop_mssb_##tag##_d, __start_mssb_##tag##_b, __stop_mssb_##tag##_b}
#endif
MODULE_SECTION_BOUNDS(chal, challenge)
MODULE_SECTION_BOUNDS(menu, menus)
MODULE_SECTION_BOUNDS(game, game)

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
    void* dataImage;  // the module's .data as linked (copied before the first prolog)
    void* dataImage2; // web: its generated data
    OSModuleHeader header; // stands in for the loaded REL image
} PortModule;

static PortModule s_modules[] = {
    {"menus", 2, 0, menus_prolog, menus_epilog, NULL, MODULE_SECTIONS(menu, menus)},
    {"game", 3, 1, game_prolog, game_epilog, NULL, MODULE_SECTIONS(game, game)},
    {"challenge", 1, 2, challenge_prolog, challenge_epilog, challenge_unresolved, MODULE_SECTIONS(chal, challenge)},
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

void port_scope_check_module(const char* name); // port/game/menu_scope.c

OSModuleHeader* port_module_load(s32 dllIndex)
{
    for (size_t i = 0; i < sizeof(s_modules) / sizeof(s_modules[0]); i++)
    {
        PortModule* m = &s_modules[i];
        if (m->dllIndex == dllIndex)
        {
            port_scope_check_module(m->name);
            memset(&m->header, 0, sizeof(m->header));
            m->header.info.id = m->id;
            return &m->header;
        }
    }
    fprintf(stderr, "[modules] unknown DLL index %d\n", (int)dllIndex);
    return NULL;
}

// Restores [dataStart, dataEnd) to the image saved at the first load and
// zeroes [bssStart, bssEnd).
static void reset_range(char* dataStart, char* dataEnd, char* bssStart, char* bssEnd, void** image)
{
    if (dataStart != NULL && dataEnd > dataStart)
    {
        size_t n = (size_t)(dataEnd - dataStart);
        if (*image == NULL)
        {
            *image = malloc(n);
            memcpy(*image, dataStart, n);
        }
        else
        {
            memcpy(dataStart, *image, n);
        }
    }
    if (bssStart != NULL && bssEnd > bssStart)
        memset(bssStart, 0, (size_t)(bssEnd - bssStart));
}

void port_module_prolog(OSModuleHeader* header)
{
    PortModule* m = find_by_header(header);
    if (m == NULL)
        return;
    {
        ModuleSections* r = &m->sections;
        fprintf(stderr, "[modules] %s: prolog (reset data %ld+%ld, bss %ld+%ld bytes)\n", m->name,
                (long)(r->dataEnd - r->dataStart), (long)(r->dataEnd2 - r->dataStart2),
                (long)(r->bssEnd - r->bssStart), (long)(r->bssEnd2 - r->bssStart2));
    }
    // As a freshly linked REL: .data as on disc, .bss zeroed.
    ModuleSections* sec = &m->sections;
    reset_range(sec->dataStart, sec->dataEnd, sec->bssStart, sec->bssEnd, &m->dataImage);
    reset_range(sec->dataStart2, sec->dataEnd2, sec->bssStart2, sec->bssEnd2, &m->dataImage2);
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
