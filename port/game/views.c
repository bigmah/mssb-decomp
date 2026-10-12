// Accessors for fields of global structs that some units can't reach through
// the real struct (their headers clash) and whose GameCube-offset views are
// wrong on PC.
#include "main/file_80021308.h" // SoundManager

extern SoundManager lbl_800EF808;

// SoundManager.unk39A[0]: roster slot whose sound bank is being loaded
// (game/auto_00_0005985C_text.c).
u8* port_sound_load_index(void) {
    return &lbl_800EF808.unk39A[0];
}
