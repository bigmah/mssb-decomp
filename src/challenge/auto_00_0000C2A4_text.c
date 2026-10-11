#include "challenge/auto_00_0000C2A4_text.h"
#include "challenge/rep_0010.h"
#include "static/UnknownHomes_Static.h"

// .text:0x0000C2A4 size:0x38
void fn_1_C2A4(void) {
    ChTaskHeader* parent = ((ChTaskHeader*)lbl_803CC1B8)->parent;

    parent->result = 1;
    fn_800B0A14_removeQueue(parent);
}

// .text:0x0000C2DC size:0x2CC
// Builds the tree-drawing prefix ("| ", "+") for the bones of a skeleton, one row at a time:
// rows are skipped while *skip > 0 and the walk stops when *remaining reaches 0.
// `width` is unused; `ret` is passed through and returned.
s32 fn_1_C2DC(ChBoneNode* bone, char* buf, s32 col, s32 width, s32 ret, s32* line, s32* skip,
              s32* remaining) {
    if (*skip == 0) {
        buf[col] = '+';
        buf[col + 1] = '\0';
        (*remaining)--;
        if (*remaining == 0) {
            return ret;
        }
    } else {
        (*skip)--;
    }
    (*line)--;
    if (bone->child != NULL) {
        if (bone->next != NULL) {
            buf[col] = '|';
        } else {
            buf[col] = ' ';
        }
        ret = fn_1_C2DC(bone->child, buf, col + 1, width, ret, line, skip, remaining);
        if (*remaining == 0) {
            return ret;
        }
    }
    if (bone->next != NULL) {
        ret = fn_1_C2DC(bone->next, buf, col, width, ret, line, skip, remaining);
        if (*remaining == 0) {
            return ret;
        }
    }
    return ret;
}

// .text:0x0000C5A8 size:0x4
void fn_1_C5A8(void) {
    return;
}
