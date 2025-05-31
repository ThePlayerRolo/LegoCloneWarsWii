#ifndef _MSL_EXTRAS_H
    #define _MSL_EXTRAS_H

    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/size_def.h"

    #ifdef __cplusplus
        extern "C" {
    #endif

    int stricmp(const char*, const char*);
    int strnicmp(const char*, const char*, size_t);

    size_t strnlen(const char *str, size_t maxlen);

    int strcasecmp(const char *lhs, const char *rhs);
    int strncasecmp(const char *lhs, const char *rhs, size_t maxlen);

    #ifdef __cplusplus
        }
    #endif

#endif
