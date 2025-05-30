#ifndef RUNTIME_GLOBAL_DESTRUCTOR_CHAIN_H
    #define RUNTIME_GLOBAL_DESTRUCTOR_CHAIN_H
    #include "types.h"
    #ifdef __cplusplus
        extern "C" {
    #endif

    typedef void (*DtorFunction)(void* obj, s16 method);

    typedef struct DtorLink {
        struct DtorLink* next;
        DtorFunction dtor;
        void* object;
    } DtorLink;

    void* __register_global_object(void *object, DtorFunction destructor, DtorLink *regmem);
    void __destroy_global_chain(void);

    #ifdef __cplusplus
        }
    #endif
#endif
