// Web builds: no native backtraces (the browser console shows the wasm stack).
#pragma once
static inline int backtrace(void** frames, int size) { (void)frames; (void)size; return 0; }
static inline void backtrace_symbols_fd(void* const* frames, int size, int fd) { (void)frames; (void)size; (void)fd; }
