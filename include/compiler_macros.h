#ifndef COMPILER_MACROS_H
    #define COMPILER_MACROS_H

    #ifndef __MWERKS__
        #define __option(x)
        #define __declspec(x)
        #define __attribute__(x)
        #define ASM_DECL asm
        #define ASM_BLOCK asm
    #else
        #define ASM_DECL
        #define ASM_BLOCK(...)
    #endif

    #define ALIGN(x) __attribute__((aligned(x)))
    #define DONT_INLINE __declspec(noinline) // use for regular functions
    #define DONT_INLINE_CLASS __attribute__((never_inline)) // use for class methods

    #define DECL_SECTION(x) __declspec(section x)
    #define DECL_WEAK __declspec(weak)

    #ifdef VERSION_SZBE69_B8
        #define RETAIL_DONT_INLINE_FUNC inline
        #define RETAIL_DONT_INLINE_CLASS inline
    #else
        #define RETAIL_DONT_INLINE_FUNC DONT_INLINE
        #define RETAIL_DONT_INLINE_CLASS DONT_INLINE_CLASS
    #endif

#endif
