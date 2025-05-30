extern void OSReport(const char *, ...);
extern void* OSGetMEM1ArenaLo();
extern void* OSGetMEM1ArenaHi();
extern void* OSInitAlloc(void *, void *, int);
extern volatile int __OSCurrHeap;
extern void* OSAllocFromHeap(int, int);
#define OSRoundUp32B(x) (((unsigned int)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((unsigned int)(x)) & ~(32 - 1))




void __sys_alloc(int a) {
    void* arenaLo;
	void* arenaHi;
    if (__OSCurrHeap == -1) {
	    OSReport("GCN_Mem_Alloc.c : InitDefaultHeap. No Heap Available\n");
	    OSReport("Metrowerks CW runtime library initializing default heap\n");

	    arenaLo = OSGetMEM1ArenaLo();
	    arenaHi = OSGetMEM1ArenaHi();

	    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
	    OSSetMEM1ArenaLo(arenaLo);

	    arenaLo = (void*)OSRoundUp32B(arenaLo);
	    arenaHi = (void*)OSRoundDown32B(arenaHi);

	    OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));
	    OSSetMEM1ArenaLo(arenaLo = arenaHi);
    }

    OSAllocFromHeap(__OSCurrHeap, a);

}
