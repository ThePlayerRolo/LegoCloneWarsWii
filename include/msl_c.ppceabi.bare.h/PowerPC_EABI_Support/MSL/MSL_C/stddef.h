#ifndef _STDDEF_H
    #define _STDDEF_H

    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/intptr_def.h" /* IWYU pragma: export */
    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/null_def.h" /* IWYU pragma: export */
    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/size_def.h" /* IWYU pragma: export */

    #ifdef __cplusplus
        extern "C" {
    #endif

    #define offsetof(ST, M) ((size_t) & (((ST *)0)->M))

    #ifdef __cplusplus
        }
    #endif

#endif
