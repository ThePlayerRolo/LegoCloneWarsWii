#include "macros.h"
#include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/null_def.h"
#include "types.h"
#include "numath.master/NuRand.hpp"

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

void NuRandSetSeed(nunrand_s* param_1, int param_2) {
    if (param_1 == nullptr) {
        param_1 = &global_rand;
    }
    param_1->unk0 = param_2;
}

void NuRand(nunrand_s* param_1) {
    if (param_1 == nullptr) {
        param_1 = &global_rand;
    } else {
        param_1->unk0 = 1;
    }
    u32 uVar2 = param_1->unk0 ^  0x75bd924;
}
