#ifndef RUNTIME_MEM_H
    #define RUNTIME_MEM_H

    #include "types.h"
    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/size_def.h"  /* IWYU pragma: export */
    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/restrict_def.h"

    #ifdef __cplusplus
        extern "C" {
    #endif

    DECL_SECTION(".init") void* memcpy(void* RESTRICT dest, const void* RESTRICT src, size_t count);
    DECL_SECTION(".init") void __fill_mem(void* dest, s32 val, size_t count);
    DECL_SECTION(".init") void* memset(void* dest, s32 ch, size_t count);

    #ifdef __cplusplus
        }
    #endif

#endif
