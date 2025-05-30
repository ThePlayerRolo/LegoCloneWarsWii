#ifndef GCN_MEM_ALLOC_H
    #define GCN_MEM_ALLOC_H

    extern void OSReport(const char *, ...);
    extern void* OSGetMEM1ArenaLo();
    extern void* OSGetMEM1ArenaHi();
    extern void* OSInitAlloc(void *, void *, int);
    extern volatile int __OSCurrHeap;
    #define OSRoundUp32B(x) (((unsigned int)(x) + 32 - 1) & ~(32 - 1))
    #define OSRoundDown32B(x) (((unsigned int)(x)) & ~(32 - 1))

#endif
