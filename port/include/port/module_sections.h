// REL module data on PC (force-included after prelude.h).
//
// On the GameCube each REL (menus, game, challenge) is read from disc and
// linked every time it is loaded: its .data starts out as on disc and its
// .bss is zeroed. On PC the modules are linked into the executable, so a
// module's variables would keep the values of its previous run (a second
// game started with the last game's g_GameLogic). The module sources are
// compiled with PORT_MODULE_ID set (port/CMakeLists.txt); this puts their
// data and bss into their own sections, which port/src/modules.c restores
// and clears before each prolog.
//
// Mach-O and ELF use these sections. wasm-ld has no section bounds, but it
// lays data out in input order: the web build brackets each module's sources
// (and its port/gen data) with generated marker objects instead
// (mssb_bracket_modules in port/CMakeLists.txt), and modules.c resets the
// ranges between them.
#pragma once

#if defined(PORT_MODULE_ID) && !defined(__EMSCRIPTEN__)
#if defined(__APPLE__)
#if PORT_MODULE_ID == 1
#pragma clang section bss = "__DATA,__mssb_chal_b" data = "__DATA,__mssb_chal_d"
#elif PORT_MODULE_ID == 2
#pragma clang section bss = "__DATA,__mssb_menu_b" data = "__DATA,__mssb_menu_d"
#elif PORT_MODULE_ID == 3
#pragma clang section bss = "__DATA,__mssb_game_b" data = "__DATA,__mssb_game_d"
#endif
#else
#if PORT_MODULE_ID == 1
#pragma clang section bss = "mssb_chal_b" data = "mssb_chal_d"
#elif PORT_MODULE_ID == 2
#pragma clang section bss = "mssb_menu_b" data = "mssb_menu_d"
#elif PORT_MODULE_ID == 3
#pragma clang section bss = "mssb_game_b" data = "mssb_game_d"
#endif
#endif
#endif
