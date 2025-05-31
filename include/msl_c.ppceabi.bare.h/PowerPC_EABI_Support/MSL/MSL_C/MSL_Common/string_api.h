#ifndef _MSL_STRING_API_H
    #define _MSL_STRING_API_H

    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/size_def.h"

    #ifdef __cplusplus
        extern "C" {
    #endif

    void* __memrchr(const void* src, int val, size_t n);

    #ifdef __cplusplus
        }
    #endif

#endif
