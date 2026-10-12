// Debug tracing for the boot loop (MSSB_TRACE_TASKS=1): prints the scene task
// list whenever it changes, with symbol names.
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* sym_name(void* p)
{
    Dl_info info;
    if (p != NULL && dladdr(p, &info) && info.dli_sname != NULL)
        return info.dli_sname;
    return "?";
}

// funcs: the root task's function followed by the list's (count entries).
void port_trace_tasks(void** funcs, int count)
{
    static int enabled = -1;
    static void* last[64];
    static int lastCount = -1;
    if (enabled < 0)
        enabled = getenv("MSSB_TRACE_TASKS") != NULL;
    if (!enabled)
        return;
    if (count > 64)
        count = 64;
    if (count == lastCount && memcmp(last, funcs, (size_t)count * sizeof(void*)) == 0)
        return;
    memcpy(last, funcs, (size_t)count * sizeof(void*));
    lastCount = count;
    fprintf(stderr, "[tasks]");
    for (int i = 0; i < count; i++)
        fprintf(stderr, " %s", sym_name(funcs[i]));
    fprintf(stderr, "\n");
}
