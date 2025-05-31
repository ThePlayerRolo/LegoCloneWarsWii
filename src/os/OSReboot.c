/* Originally from RB3: https://github.com/DarkRTA/rb3/blob/master/src/sdk/RVL_SDK/src/os/OSReboot.c*/
#include <revolution/os/OSArena.h>
#include <revolution/os/OSExec.h>
#include <revolution/os/OSInterrupt.h>
#include "types.h"

void *SaveStart = NULL;
void *SaveEnd = NULL;

void __OSReboot(u32 a, u32 b) {
    OSDisableInterrupts();
    OSSetMEM1ArenaLo((void *)0x81280000);
    OSSetMEM1ArenaHi((void *)0x812F0000);
    u32 x = 0;
    __OSNextPartitionType = *(void **)0x80003194;
    __OSBootDol(b, a | 0x80000000, &x);
}

void OSGetSaveRegion(uint *s, uint *e) {
    *s = (uint)SaveStart;
    *e = (uint)SaveEnd;
}

//May be uint
void OSSetSaveRegion(void *a, void *b) {
    SaveStart = a;
    SaveEnd =  b;
}
