#include "types.h"


static unsigned int fseed;
//Todo: Figure out what generates floatbase0.
static float floatBase0;






void NuRandSeed(unsigned int param1) {
    fseed = param1;
}
unsigned int NuRandGetSeed() {
    return fseed;
}

float NuRandFloatSeeded(unsigned int* param1) {
    //floatBase0 = 4;
    unsigned int uVar1 = *param1 * 0x19660d + 0x3c6ef35f;
    *param1 = uVar1;
    uVar1 &= 0x7fffff;
    uVar1|= 0x3f800000;
    return *(float*)&uVar1 - floatBase0;
}

float NuRandFloat() {
    NuRandFloatSeeded(&fseed);
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
