#include "types.h"


static unsigned int fseed;

float NuRandFloat();




void NuRandSeed(unsigned int param1) {
    fseed = param1;
}
unsigned int NuRandGetSeed() {
    return fseed;
}

unsigned int NuRandIntSeeded(unsigned int* param1) {
    unsigned int uVar1 = *param1 * 0x19660d + 0x3c6ef35f;
    *param1 = uVar1;
    return *param1;
}

unsigned int NuRandInt() {
    return NuRandIntSeeded(&fseed);    
}



unsigned int NuRandIntInRange(unsigned int param_1, unsigned int param_2) {
    return param_1 + (unsigned int)((param_2 - param_1)*NuRandFloat());
}
