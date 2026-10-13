// Unlock everything (PC only, on unless `unlockall = false` in user.ini): every
// character and every character's star, the way the menus' debug page does it
// (fn_2_1406C / fn_2_13D70). Applied at boot and after each save load, so a
// memory card save can't lock them again.
//
//   g_d_GameSettings._1A[6]   characters unlocked, one per challenge team
//                             (checked by fn_80024C04)
//   lbl_80361B20.unlocked[]  star unlocked, per character id
#include "mssbTypes.h"
#include "static/GameSettings.h"
#include "main/unlock_flags.h"

extern UnlockFlags lbl_80361B20;

const char* port_user_ini_get(const char* key);
int port_user_ini_bool(const char* key);

void port_unlock_all(void) {
    s32 i;

    if (port_user_ini_get("unlockall") != NULL && !port_user_ini_bool("unlockall")) {
        return;
    }
    for (i = 0; i < 6; i++) {
        g_d_GameSettings._1A[i] = 1;
    }
    for (i = 0; i < 0x36; i++) {
        lbl_80361B20.unlocked[i] = 1;
    }
}
