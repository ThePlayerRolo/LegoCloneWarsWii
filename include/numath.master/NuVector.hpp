#pragma  once
#include "types.h"

struct NUVEC {
    float x;
    float y;
    float z;
};

void NuVecNeg(NUVEC* out, NUVEC const* in);
void NuVecAdd(NUVEC* out, NUVEC const* v1, NUVEC const* v2);
void NuVecSub(NUVEC* out, NUVEC const* v1, NUVEC const* v2);
void NuVecScale(NUVEC* out, NUVEC const* in, float scale);
void NuVecAddScale(NUVEC* out, NUVEC const* v1, NUVEC const* v2, float scale);
void NuVecScaleAccum(NUVEC* v1, NUVEC const* v2, float scale);
void NuVecInvScale(NUVEC* out, NUVEC const* in, float scale);
void NuVecCross(NUVEC* out, NUVEC const* v1, NUVEC const* v2);
void NuVecCrossRel(NUVEC* out, NUVEC const* p1, NUVEC const* p2, NUVEC const* ref);
float NuVecDot(NUVEC const* v1, NUVEC const* v2);
void NuVecMax(NUVEC* out, NUVEC const* v1, NUVEC const* v2);
void NuVecMin(NUVEC* out, NUVEC const* v1, NUVEC const* v2);
