#include "nufile.master/NufileDevice.hpp"





NuFileDevice::NuFileDevice() {
    _8 = 1;
    _C = 0;
    _10 = 0;
    _14 = "dat:";
    _18 = 0x400;
    _1C = 0;
    _20 = 0;
    _2C = 0;
    _30 = 0;
    _4 = -1;
}

NuFileDevice::~NuFileDevice() {
    
}

u32 NuFileDevice::GetPositionOnDisc(const char*, long long&) const {
    return 0;
}

void NuFileDevice::DirClose(int) {
    
}


void NuFileDevice::Interrogate() {
    _10 = 1;
}
