// main.dol common .bss 0x803297E0-0x80366158: uninitialised globals, compiled with -common on;
// the linker places all commons after the other .bss, one block per object in link order.
// 17 commons in one object (menu/game globals block): the first one's slot is inflated by the others' size
// (docs/common_bss.md). mwcc lists them in reverse declaration order, so they are
// declared last to first.
#include "main/menu_globals.h"
#include "main/file_800A7C08.h"
#include "game/auto_00_000759BC_text.h"
#include "main/unlock_flags.h"

u8 starMissionCompletionTracker[0x4508];
u8 lbl_80361C18[0x38];
UnlockFlags lbl_80361B20;
u8 lbl_803616CC[0x454]; // MenuCharLayout (menus/rep_0AB0.h)
u8 lbl_80354768[0xCF64]; // SaveProgress (main/file_8003A688.h)
u8 lbl_80354720[2][9][4]; // OrderEntry[2][9] (main/file_8004207C.h)
u8 inMemRoster[2][9][0xA0]; // CharacterStats[2][9] (game/UnknownHomes_Game.h)
u8 lbl_80353B98[0x48];
LineScore lbl_80353A90;
BattingRecord lbl_803537E4[2][9];
PitchingRecord lbl_803535C8[2][9];
PlayLogEntry lbl_803532A8[2][100];
RosterLogEntry lbl_80353260[2][9];
u8 lbl_8034E9A0[0x48C0]; // character select work (CharSelectState in main/file_800639BC.h views it together with the next two)
MenuState lbl_8034E978;
StreamTrack lbl_8034E478[16];
MenuWork lbl_803297E0;
