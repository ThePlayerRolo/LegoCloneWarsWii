/* Originally from https://github.com/doldecomp/ogws/blob/master/src/revolution/OS/OSIpc.c*/
#include <revolution/OS.h>

static void* IpcBufferLo = (void*)-1;
static void* IpcBufferHi = NULL;

void* __OSGetIPCBufferHi(void) {
    return IpcBufferHi;
}

void* __OSGetIPCBufferLo(void) {
    return IpcBufferLo;
}

void __OSInitIPCBuffer(void) {
    IpcBufferLo = *(void**)OSPhysicalToCached(OS_PHYS_IPC_BUFFER_START);
    IpcBufferHi = *(void**)OSPhysicalToCached(OS_PHYS_IPC_BUFFER_END);
}
