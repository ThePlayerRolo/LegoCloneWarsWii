#ifndef NMWEXCEPTION_H
    #define NMWEXCEPTION_H

    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/cstring"  /* IWYU pragma: export */
    #include "runtime.ppceabi.h/__ppc_eabi_linker.h"
    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/size_t.h"  /* IWYU pragma: export */

    typedef void* ctor_dtor_ptr;

    #ifdef __cplusplus
        extern "C" {
    #endif

    void* __construct_new_array(void *, ctor_dtor_ptr, ctor_dtor_ptr, size_t, size_t);
    void __construct_array(void *, ctor_dtor_ptr, ctor_dtor_ptr, size_t, size_t);
    void __destroy_arr(void *, ctor_dtor_ptr, size_t, size_t);
    void __destroy_new_array(void *, ctor_dtor_ptr);
    extern void __destroy_new_array3(void*, ctor_dtor_ptr, ctor_dtor_ptr, int b); 

    extern int __register_fragment(struct __eti_init_info *, char *);
    extern void	__unregister_fragment(int);

    #ifdef __cplusplus
        };
    #endif

#endif
