#include "types.h"



class NuFileDevice {
public:
    NuFileDevice();

    ~NuFileDevice();
    virtual u32 GetPositionOnDisc(const char*, long long&) const;
    virtual void DirClose(int);
    void Interrogate();

    u32 _4;
    u32 _8;
    u32 _C;
    u32 _10;
    const char* _14;
    u32 _18;
    u32 _1C;
    u8 _20;
    u32 _22;
    u8 _2A;
    u32 _2C;
    u8 _30;
};
