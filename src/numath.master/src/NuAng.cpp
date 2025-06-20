#include "types.h"





int NuAngWrap(int param1) {
    for (; 0x8000 < param1; param1 -= 0x10000) {
    }
    for (;  param1 <= -32768; param1 += 0x10000) {
    }
    return param1;
}


void NuAngAdd(int param1, int param2) {
    NuAngWrap(param1 + param2);
}

void NuAngSub(int param1, int param2) {
    NuAngWrap(param1 - param2);
}
