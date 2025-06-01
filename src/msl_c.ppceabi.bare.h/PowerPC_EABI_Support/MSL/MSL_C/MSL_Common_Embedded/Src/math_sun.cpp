#include "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/math.h" /* IWYU pragma: export */

// double scalbn(double arg, int exp) {
//     int exp_2;
//     double f = frexp(arg, &exp_2);
//     exp_2 += exp;
//     return ldexp(f, exp_2);
// }

// TODO: Match with C++
asm double scalbn(void)
{
    stwu    r1, -0x20(r1)
    mflr    r0
    stw     r0, 0x24(r1)
    stw     r31, 0x1C(r1)
    mr      r31, r3
    addi    r3, r1, 0x8
    bl      frexp
    lwz     r0, 0x8(r1)
    add     r3, r0, r31
    stw     r3, 0x8(r1)
    bl      ldexp
    lwz     r0, 0x24(r1)
    lwz     r31, 0x1C(r1)
    mtlr    r0
    addi    r1, r1, 0x20
    blr
}
