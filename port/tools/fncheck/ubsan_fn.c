// -fsanitize=function handler for MSSB_SANITIZE_FUNCTION builds: logs every
// (call site, callee) pair once, without UBSan's once-per-site dedup, so
// port/tools/fncheck/report.py can list the calls that would trap in wasm.
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    const char* file;
    uint32_t line;
    uint32_t col;
} SourceLocation;

typedef struct {
    uint16_t kind;
    uint16_t info;
    char name[1];
} TypeDescriptor;

typedef struct {
    SourceLocation loc;
    const TypeDescriptor* type;
} FunctionTypeMismatchData;

#define SEEN 8192
static struct { const void* data; uintptr_t fn; } s_seen[SEEN];
static pthread_mutex_t s_lock = PTHREAD_MUTEX_INITIALIZER;
static FILE* s_out;

static void report(FunctionTypeMismatchData* d, uintptr_t fn)
{
    pthread_mutex_lock(&s_lock);
    unsigned h = (unsigned)(((uintptr_t)d >> 3) ^ (fn >> 2)) % SEEN;
    for (unsigned n = 0; n < SEEN; n++, h = (h + 1) % SEEN)
    {
        if (s_seen[h].data == d && s_seen[h].fn == fn)
            goto done;
        if (s_seen[h].data == NULL)
        {
            s_seen[h].data = d;
            s_seen[h].fn = fn;
            break;
        }
    }
    if (s_out == NULL)
    {
        const char* path = getenv("MSSB_FNCHECK_LOG");
        s_out = path ? fopen(path, "a") : stderr;
        if (s_out == NULL)
            s_out = stderr;
    }
    Dl_info info;
    const char* name = (dladdr((void*)fn, &info) && info.dli_sname) ? info.dli_sname : "?";
    fprintf(s_out, "fncheck %s:%u callee %s type '%s'\n", d->loc.file, d->loc.line, name, d->type->name);
    fflush(s_out);
done:
    pthread_mutex_unlock(&s_lock);
}

void __ubsan_handle_function_type_mismatch(FunctionTypeMismatchData* d, uintptr_t fn) { report(d, fn); }
void __ubsan_handle_function_type_mismatch_abort(FunctionTypeMismatchData* d, uintptr_t fn) { report(d, fn); }
