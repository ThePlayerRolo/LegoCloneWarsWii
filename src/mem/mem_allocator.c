#include "Revolution/mem.h"

void* AllocatorAllocForExpHeap_(MEMAllocator* allocator, u32 size)
{
    return MEMAllocFromExpHeapEx(allocator->heap, size, allocator->heapParam1);
}

void AllocatorFreeForExpHeap_(MEMAllocator* allocator, void* block)
{
    MEMFreeToExpHeap(allocator->heap, block);
}

void* MEMAllocFromAllocator(MEMAllocator* allocator, u32 size)
{
    return allocator->funcs->allocFunc(allocator, size);
}

void MEMFreeToAllocator(MEMAllocator* allocator, void* block)
{
    allocator->funcs->freeFunc(allocator, block);
}

void MEMInitAllocatorForExpHeap(MEMAllocator* allocator, MEMiHeapHead* heap, s32 align)
{
    static const MEMAllocatorFuncs sAllocatorFunc = {AllocatorAllocForExpHeap_, AllocatorFreeForExpHeap_};
    allocator->funcs = &sAllocatorFunc;
    allocator->heap = heap;
    allocator->heapParam1 = align;
    allocator->heapParam2 = 0;
}
