/*Sourced From Petari : https://github.com/SMGCommunity/Petari/blob/master/src/Runtime/NMWException.cpp and RB3: 
 https://github.com/DarkRTA/rb3/blob/master/src/sdk/PowerPC_EABI_Support/Runtime/NMWException.cpp */

#include "runtime.ppceabi.h/NMWException.h"
#define ARRAY_HEADER_SIZE 16

class __partial_array_destructor {
public:
    void* mArrayStart;      // 0x0
    size_t mElemSize;       // 0x4
    size_t mArraySize;      // 0x8
    ctor_dtor_ptr mDtorPtr; // 0xC
    size_t mCurElement;     // 0x10

    __partial_array_destructor(void *arr, unsigned int size, unsigned int count, ctor_dtor_ptr ptr) {
        mArrayStart = arr;
        mElemSize = size;
        mArraySize = count;
        mDtorPtr = ptr;
        mCurElement = mArraySize;
    }

    ~__partial_array_destructor() {
        if (mCurElement < mArraySize && mDtorPtr) {
            for (char* cur = (char*)mArrayStart + (mElemSize * mCurElement); mCurElement > 0; mCurElement--) {
                cur -= mElemSize;
                ((void (*)(void *, short))mDtorPtr)(cur,-1);
            }
        }
    }
};

void __construct_array(void *pBlock, ctor_dtor_ptr ctor, ctor_dtor_ptr dtor, size_t size, size_t n) {
    __partial_array_destructor pad(pBlock, size, n, dtor);

    char* p = (char*)pBlock;
    for (pad.mCurElement = 0; pad.mCurElement < n; p += size, pad.mCurElement++) {
        ((void (*)(void *, short))ctor)(p,1);
    }
}

void *__construct_new_array(void *block, ctor_dtor_ptr ctor, ctor_dtor_ptr dtor, size_t size, size_t n) {
    char *ptr = (char *)block;

    if (ptr != 0){
        *(size_t *)ptr = size;
        *(size_t *)(ptr + 4) = n;
        ptr += 0x10;

        if (ctor) {
            
            __partial_array_destructor pad(ptr, size, n, dtor);

            char* p;
            for (pad.mCurElement = 0, p = ptr; pad.mCurElement < n; pad.mCurElement++, p += size) {
                ((void (*)(void *, short))ctor)(p,1);
            }
        }
    }
    return ptr;
}

void __destroy_arr(void *pArraySource, ctor_dtor_ptr dtor, size_t size, size_t num) {
    char* cur;

    for (cur = (char*)pArraySource + (size * num); num > 0; num--) {
        cur -= size;
        ((void (*)(void *, short))dtor)(cur,-1);
    }
}

extern void __destroy_new_array3(void *block, ctor_dtor_ptr dtor, ctor_dtor_ptr headerDtor, int b) {
    if (block) {
        size_t i, objects, objectsize;
        char *p;

        objects = ((size_t *)((char *)block - ARRAY_HEADER_SIZE))[1];
        objectsize = *(size_t *)((char *)block - ARRAY_HEADER_SIZE);
        if (dtor) {
            p = (char *)block + (objects * objectsize);

            for (i = 0; i < objects; i++) {
                p -= objectsize;
                ((void (*)(void *, short))dtor)(p,-1);
            }
        }

        if (headerDtor) {
            if (b) {
                ((void (*)(void*, int))headerDtor)((char*)block - ARRAY_HEADER_SIZE, objects * objectsize + ARRAY_HEADER_SIZE);
            } else {
                ((void (*)(void*))headerDtor)((char*)block - ARRAY_HEADER_SIZE);
            }
        }
    }
}
