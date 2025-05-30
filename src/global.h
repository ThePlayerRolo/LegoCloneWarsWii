#ifndef GLOABL_H
    #define GLOBAL_H

    #include "types.h"

    #ifndef __INTELLISENSE__
        #define ALIGN_DECL(ALIGNMENT) __attribute__((aligned(ALIGNMENT)))
        #define SECTION_DATA __declspec(section ".data")
        #define SECTION_INIT __declspec(section ".init")
    #else
        #define STATIC_ASSERT(...)
        #define ALIGN_DECL(...)
        #define SECTION_DATA
        #define SECTION_INIT
    #endif

    #define VERSION_NTSC 0
    #define VERSION_PAL 1

    #if VERSION == VERSION_NTSC
        #define VERSION_SELECT(NTSC, PAL)(NTSC)
    #elif VERSION == VERSION_PAL
        #define VERSION_SELECT(NTSC, PAL)(PAL)
    #endif

#endif
