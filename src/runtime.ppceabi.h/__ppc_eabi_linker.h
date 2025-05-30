#ifndef __PPC_EAB_LINKER_H
    #define __PPC_EAB_LINKER_H

    #include "global.h"

    typedef struct __eti_init_info {
        void* eti_start;
        void* eti_end;
        void* code_start;
        u32 code_size;
    } __eti_init_info;

    SECTION_INIT extern __eti_init_info _eti_init_info[];

#endif
