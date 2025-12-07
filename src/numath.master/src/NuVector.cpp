#include "numath.master/NuVector.hpp"
#include "Revolution/MTX.h"

asm void NuVecAdd(register NUVEC* out, register NUVEC const* v1, register NUVEC const* v2) {
        // clang-format off
        nofralloc
        stwu r1, -0x10(r1)
        psq_l f1, NUVEC.x(v1), 0, 0
        psq_l f3, NUVEC.x(v2), 0, 0
        psq_l f2, NUVEC.z(v1), 1, 0
        psq_l f4, NUVEC.z(v2), 1, 0
        ps_add f1, f1, f3
        ps_add f2, f2, f4


        psq_st f1, NUVEC.x(out), 0,0 
        psq_st f2, NUVEC.z(out), 1,0
        addi r1,r1, 0x10
        blr
}

asm void NuVecSub(register NUVEC* out, register NUVEC const* v1, register NUVEC const* v2) {
        // clang-format off
        nofralloc
        stwu r1, -0x10(r1)
        psq_l f1, NUVEC.x(v1), 0, 0
        psq_l f3, NUVEC.x(v2), 0, 0
        psq_l f2, NUVEC.z(v1), 1, 0
        psq_l f4, NUVEC.z(v2), 1, 0
        ps_sub f1, f1, f3
        ps_sub f2, f2, f4


        psq_st f1, NUVEC.x(out), 0,0 
        psq_st f2, NUVEC.z(out), 1,0
        addi r1,r1, 0x10
        blr
}

void NuVecScale(NUVEC* out, NUVEC const* in, float scale) {
    out->x = in->x * scale;
    out->y = in->y * scale;
    out->z = in->z * scale;
}

void NuVecAddScale(NUVEC* out, NUVEC const* v1, NUVEC const* v2, float scale) {
    out->x = v1->x + v2->x * scale;
    out->y = v1->y + v2->y * scale;
    out->z = v1->z + v2->z * scale;
}
