#include "types.h"



class NuFileDevice {
public:
    u32 GetPositionOnDisc(const char*, long long&) const;
    void DirClose(int);
};
