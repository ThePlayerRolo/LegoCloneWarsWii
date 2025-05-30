#ifndef RUNTIME_GECKO_EXCEPTIONPPC_H
    #define RUNTIME_GECKO_EXCEPTIONPPC_H

    #include "types.h"
    #include "runtime.ppceabi.h/__ppc_eabi_linker.h"
    #define MAXFRAGMENTS 0x1F

    typedef struct ExceptionTableIndex {
        u32 functionoffset;
        u32 eti_field;
        u32 exceptionoffset;
    } ExceptionTableIndex;

    typedef struct FragmentInfo {
        ExceptionTableIndex* exception_start;
        ExceptionTableIndex* exception_end;
        char* code_start;
        char* code_end;
        char* data_start;
        char* data_end;
        char* TOC;
        s32 active;
    } FragmentInfo;

    typedef struct ProcessInfo {
        __eti_init_info* exception_info;
        char* TOC;
        u32 active;
    } ProcessInfo;

    u32 __register_fragment(struct __eti_init_info*, char*);
    void __unregister_fragment(u32);
    s32 ExPPC_FindExceptionFragment(char*, FragmentInfo*);

#endif
