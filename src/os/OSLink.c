/*Originally from RB3: https://github.com/DarkRTA/rb3/blob/master/src/sdk/RVL_SDK/src/os/OSLink.c*/
#include <revolution/OS.h>


void __OSModuleInit(void) {
    OS_FIRST_REL = OS_LAST_REL = NULL;
    OS_REL_NAME_TABLE = NULL;
}
