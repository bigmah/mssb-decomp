#include "main/file_80022DAC.h"

// .text:0x80022DAC size:0x2CC
void f_InitBone(void) {
    return;
}

// .text:0x80023078 size:0x268
void fn_80023078(void) {
    return;
}

// .text:0x800232E0 size:0x32C
void f_InitActorWithLayout(void) {
    return;
}

// .text:0x8002360C size:0x2D4
void BuildBoneSkinOrientationMatrix(void) {
    return;
}

// .text:0x800238E0 size:0xBC
void fn_800238E0(void) {
    return;
}

// .text:0x8002399C size:0x108
void fn_8002399C(void) {
    return;
}

// .text:0x80023AA4 size:0x60
void fn_80023AA4(void) {
    return;
}

// .text:0x80023B04 size:0x8C
void fn_80023B04(void) {
    return;
}

// .text:0x80023B90 size:0x164
void fn_80023B90(void) {
    return;
}

// .text:0x80023CF4 size:0x48
void fn_80023CF4(void) {
    return;
}

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

// fn_80023E48, size:0xA4
void fn_80023E48(VecQueue* queue, Vec* value) {
    queue->head = (queue->head + queue->step) % queue->capacity;
    if (queue->tail == queue->head) {
        queue->tail = (queue->tail + queue->step) % queue->capacity;
    }
    queue->step = 1;
    queue->entries[queue->head] = *value;
    queue->count += queue->count < queue->capacity;
}

static inline s32 VecQueueLastIndex(s32 capacity) {
    return capacity - 1;
}

// fn_80023D98, size:0x64
s32 fn_80023D98(VecQueue* queue, Vec* result) {
    s32 cursor = queue->cursor;
    if (cursor == queue->tail) {
        return 0;
    }
    queue->cursor = (cursor + VecQueueLastIndex(queue->capacity)) % queue->capacity;
    *result = queue->entries[queue->cursor];
    return 1;
}

// .text:0x80023F0C size:0x278
void fn_80023F0C(void) {
    return;
}
