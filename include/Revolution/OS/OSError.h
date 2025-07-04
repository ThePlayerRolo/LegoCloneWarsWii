#ifndef RVL_SDK_OS_ERROR_H
    #define RVL_SDK_OS_ERROR_H

    #include "types.h"
    #include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/stdio.h"

    #ifdef __cplusplus
        extern "C" {
    #endif

    #define OSError_FileLine(file_, line_, ...) \
        OSPanic(file_, line_, __VA_ARGS__)

    #define OSError_Line(line_, ...) \
        OSError_FileLine(__FILE__, line_, __VA_ARGS__)

    #define OSError(...) \
        OSError_Line(__LINE__, __VA_ARGS__)

    #define OS_ASSERT(cond, text) \
        if (! (cond) ) OSError( (text) )

    // Forward declarations
    typedef struct OSContext;

    typedef enum {
        OS_ERR_SYSTEM_RESET,
        OS_ERR_MACHINE_CHECK,
        OS_ERR_DSI,
        OS_ERR_ISI,
        OS_ERR_EXT_INTERRUPT,
        OS_ERR_ALIGNMENT,
        OS_ERR_PROGRAM,
        OS_ERR_FP_UNAVAIL,
        OS_ERR_DECREMENTER,
        OS_ERR_SYSTEM_CALL,
        OS_ERR_TRACE,
        OS_ERR_PERF_MONITOR,
        OS_ERR_IABR,
        OS_ERR_SMI,
        OS_ERR_THERMAL_INT,
        OS_ERR_PROTECTION,
        OS_ERR_FP_EXCEPTION,

        OS_ERR_MAX
    } OSErrorType;

    typedef void (*OSErrorHandler)(u8 error, struct OSContext* ctx, u32 dsisr, u32 dar, ...);

    extern OSErrorHandler __OSErrorTable[OS_ERR_MAX];
    extern u32 __OSFpscrEnableBits;

    DECL_WEAK void OSReport(const char* msg, ...);
    DECL_WEAK void OSPanic(const char* file, int line, const char* msg, ...);
    DECL_WEAK void OSVReport(const char* msg, va_list arg);

    OSErrorHandler OSSetErrorHandler(u16 error, OSErrorHandler handler);
    void __OSUnhandledException(u8 error, struct OSContext* ctx, u32 dsisr, u32 dar);

    #ifdef __cplusplus
        }
    #endif
#endif
