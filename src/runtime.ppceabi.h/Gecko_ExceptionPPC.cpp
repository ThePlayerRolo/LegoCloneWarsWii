#include "global.h"
#include "runtime.ppceabi.h/Gecko_ExceptionPPC.h"

static ProcessInfo fragmentinfo[MAXFRAGMENTS+1];

#pragma schedule once
u32 __register_fragment(struct __eti_init_info* info, char* TOC)
{
    ProcessInfo* f = fragmentinfo;
    for (u32 i = 0; i < MAXFRAGMENTS+1; i++, f++) {
        if (f->active == 0) {
            f->exception_info = info;
            f->TOC = TOC;
            f->active = 1;
            return i;
        }
    }
    return -1;
}
#pragma schedule twice

void __unregister_fragment(u32 fragmentID)
{
    ProcessInfo* f;
    if (fragmentID >= 0 && fragmentID <= MAXFRAGMENTS) {
        f = &fragmentinfo[fragmentID];
        f->exception_info = 0;
        f->TOC = 0;
        f->active = 0;
    }
}
