#include "Unknown/auto_03_80023D3C_text.h"

extern u32 lbl_803CBC60;

// fn_80023EEC, size:0x20
void fn_80023EEC(VecQueue* queue, Vec* entries, s32 capacity) {
    queue->entries = entries;
    queue->capacity = capacity;
    queue->count = 0;
    queue->head = 0;
    queue->tail = 0;
    queue->step = 0;
}

// fn_80023D4C, size:0x4C
s32 fn_80023D4C(VecQueue* queue, Vec* result) {
    if (queue->count != 0) {
        queue->cursor = queue->tail;
        *result = queue->entries[queue->cursor];
        return 1;
    }
    return 0;
}

// fn_80023DFC, size:0x4C
s32 fn_80023DFC(VecQueue* queue, Vec* result) {
    if (queue->count != 0) {
        queue->cursor = queue->head;
        *result = queue->entries[queue->cursor];
        return 1;
    }
    return 0;
}

// fn_80023D3C, size:0x8
u32 fn_80023D3C(void) {
    return lbl_803CBC60;
}

// fn_80023D44, size:0x8
void fn_80023D44(u32 value) {
    lbl_803CBC60 = value;
}
