#include "runtime.ppceabi.h/global_destructor_chain.h"
#include "runtime.ppceabi.h/__init_cpp_exceptions.h"
#include "runtime.ppceabi.h/__ppc_eabi_linker.h"  /* IWYU pragma: export */
#include "runtime.ppceabi.h/Gecko_ExceptionPPC.h"

static s32 fragmentID = -2;

void __init_cpp_exceptions(void)
{
    if (fragmentID == -2)
    {
        register char* R2;
        #ifndef __INTELLISENSE__
            asm { mr R2, r2 }
        #endif
        fragmentID = __register_fragment(_eti_init_info, R2);
    }
}

void __fini_cpp_exceptions(void)
{
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

#pragma section ".ctors$10"
#pragma section ".dtors$10"
#pragma section ".dtors$15"

DECL_SECTION(".ctors$10") void* __init_cpp_exceptions_reference = __init_cpp_exceptions;
DECL_SECTION(".dtors$10") void* __destroy_global_chain_reference = __destroy_global_chain;
DECL_SECTION(".dtors$15") void* __fini_cpp_exceptions_reference = __fini_cpp_exceptions;
