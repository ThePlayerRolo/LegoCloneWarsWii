#include "runtime.ppceabi.h/global_destructor_chain.h"

DtorLink* __global_destructor_chain;

void* __register_global_object(void* object, DtorFunction dtor, DtorLink* link) {
    link->next = __global_destructor_chain;
    link->dtor = dtor;
    link->object = object;
    __global_destructor_chain = link;
    return object;
}

void __destroy_global_chain(void) {
    DtorLink* link;

    while (link = __global_destructor_chain) {
        __global_destructor_chain = link->next;
        link->dtor(link->object, -1);
    }
}
