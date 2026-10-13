#include "game/rep_60.h"
#define REP_HEADER_FN repHeader_60
#include "header_rep_inline.h"
#include "static/UnknownHomes_Static.h"

#include "main/scene_task.h"
#include "main/file_80011640.h" // CharMgr
#include "main/aramloader.h"
#include "main/file_80021308.h" // AramLoader, DiskFileEntry
#include "game/rep_1D58.h"      // StadiumObjMgr
#include "game/rep_3CE0.h"      // FadeState
#include "game/auto_00_00106DFC_text.h" // RandSeedView

extern SceneTask* lbl_803CC1B8;
extern DiskFileEntry lbl_800EFBE8[];
extern StadiumObjMgr lbl_3_common_bss_350E4;
extern RandSeedView lbl_3_data_228;
extern AramLoader lbl_803716B8;
extern void OSReport(const char*, ...);
extern void fn_800229CC(void);
extern s32 fn_3_BF878(void);
extern void fn_3_BD7D8(void);
extern s32 fn_3_106E50(void);
extern void fn_3_106DFC(void);
extern void fn_8001CBD4(void);
struct StadiumArchive;
extern void fn_3_5EC0(struct StadiumArchive* arc); // game/rep_1C0.h

// .text:0x0000065C size:0x278 mapped:0x8063F6F0
void manageLoadingState(void) {
    SceneTask* p = lbl_803CC1B8;
    AramLoader* r;
#ifdef TARGET_PC
    { static int last = -1; if (p->_10 != last) { last = p->_10; fprintf(stderr, "LOCALDBG load state %d\n", last); } }
#endif
    switch (p->_10) {
    case 0:
        r = &lbl_803716B8;
        if (r->stadiumAram != 0) {
            if (lbl_803C6CF8.idle == 1) {
                void* t = ARAMTransfer(&lbl_800EFBE8[g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3], 0, 3,
                                     r->stadiumAram);
                p->u14.data = t;
                lbl_8036E548._0004[0] = t;
                OSReport("Sta %d-%d aram:%x -> mem:%x\n", g_d_GameSettings.StadiumID, g_d_GameSettings.miniGameStadiumIndicator,
                         r->stadiumAram, p->u14.data);
                goto set1;
            }
        } else {
            void* t = ARAMTransfer(&lbl_800EFBE8[g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3], 0, 0, 0);
            p->u14.data = t;
            lbl_8036E548._0004[0] = t;
        set1:
            p->_10 = 1;
        }
        break;
    case 1:
        if (lbl_803C6CF8.idle == 1) {
            fn_3_5EC0(p->u14.data);
            p->_10 = 2;
            fn_800229CC();
        }
        break;
    case 2:
        switch (fn_3_B9BB4(g_d_GameSettings.StadiumID)) {
        case 1:
            p->_10 = 3;
            break;
        case -1:
            p->_10 = 4;
            break;
        }
        break;
    case 3:
        if (lbl_3_common_bss_350E4.loading == 0) {
            p->_10 = 4;
        }
        break;
    case 4:
        if (fn_3_BF878() != 0) {
            p->_10 = 5;
        }
        break;
    case 5:
        if (lbl_3_common_bss_35154._3B0 == 0) {
            p->_10 = 6;
        }
        break;
    case 6:
        fn_3_BD7D8();
        p->_10 = 7;
        break;
    case 7:
        if (fn_3_106E50() != 0) {
            p->_10 = 8;
        }
        break;
    case 8:
        if (lbl_803C6CF8.idle == 1) {
            fn_3_106DFC();
            p->_10 = 9;
        }
        break;
    default:
        p->parent->_10 = 1;
        lbl_3_data_228._10 = 1;
        fn_800B0A14_removeQueue(&lbl_3_data_228);
        break;
    }
}

// .text:0x000004F4 size:0x168
void manageStadiumLoading(void) {
    SceneTask* p = lbl_803CC1B8;
    switch (p->_10) {
    case 0:
        fn_8001CBD4();
        lbl_8036E548._0004[0] =
            ARAMTransfer(&lbl_800EFBE8[g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3], 0, 0, 0);
        p->_10 += 1;
        break;
    case 1:
        if (lbl_803C6CF8.idle == 1) {
            fn_3_5EC0(lbl_8036E548._0004[0]);
            p->_10 += 1;
        }
        break;
    case 2: {
        switch (fn_3_B9BB4(g_d_GameSettings.StadiumID)) {
        case 1:
            p->_10 = 3;
            break;
        case -1:
            p->_10 = 4;
            break;
        }
        break;
    }
    case 3:
        if (lbl_3_common_bss_350E4.loading == 0) {
            p->_10 += 1;
        }
        break;
    default:
        p->parent->_10 = 1;
        lbl_3_data_228._10 = 1;
        fn_800B0A14_removeQueue(&lbl_3_data_228);
        break;
    }
}

