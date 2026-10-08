#include "Unknown/auto_03_80052734_text.h"

extern u32 lbl_803CB880;

extern u8 lbl_803C639C[];

// fn_80052734, size:0x34
void* fn_80052734(s32 index) {
    u8* camera;
    if (index < 0) {
        index = 0;
    } else if (index >= 2) {
        index = 1;
    }
    camera = lbl_803C639C + index * 0xA8;
    return camera + 0x150;
}

// fn_80052768_getCamera, size:0x30
camera_803c639c_s* fn_80052768_getCamera(int index) {
    if (index < 0) {
        index = 0;
    } else if (index >= 2) {
        index = 1;
    }
    return (camera_803c639c_s*)(lbl_803C639C + index * 0xA8);
}

// fn_800527BC, size:0x8
u32 fn_800527BC(void) {
    return lbl_803CB880;
}

// fn_80052798, size:0x24
void fn_80052798(s32 count) {
    if (count < 1) {
        count = 1;
    } else if (count > 2) {
        count = 2;
    }
    lbl_803CB880 = count;
}
