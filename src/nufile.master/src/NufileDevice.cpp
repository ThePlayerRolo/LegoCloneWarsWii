#include "nufile.master/NufileDevice.hpp"


int NuFileDevice::sm_CriticalSection = -1;

//Todo: Move These
int NuThreadCreateCriticalSection(char*);
void NuThreadCriticalSectionBegin(int, int);
int NuMemAllocStringFn(int, const char*, const char*, unsigned long long);
void NuThreadCriticalSectionEnd(int);


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

int NuFileDevice::AllocDirectoryHandle(const char* param1) {

    if (this->sm_CriticalSection == -1) {
        this->sm_CriticalSection = NuThreadCreateCriticalSection("NuFile");
    }
    NuThreadCriticalSectionBegin(this->sm_CriticalSection, 1);

    int iVar3 = 0;
    int iVar2 = 1;
    
    for (int i = 1; i < 8; i++) {
        if (!this->sm_DirectoryHandles[i].unk0) {
            this->sm_DirectoryHandles[i].unk0 = this;
            this->sm_DirectoryHandles[i].unk4 = NuMemAllocStringFn(0, param1, "NuFile", 0x8DD1255AB16399D8);
            iVar3 = iVar2;
            break;
        }
        
        iVar2++;
    }

    NuThreadCriticalSectionEnd(this->sm_CriticalSection);

    return iVar3;
}

void NuFileDevice::AddDevice(NuFileDevice* fileDevice) {
    this->_4 = sm_NumDevices;
    fileDevice->sm_Devices[sm_NumDevices++] = this;
}

void NuFileDevice::SetDefaultDevice(NuFileDeviceType deviceType) {
    if (!sm_NumDevices) return;
    int iVar2 = 0;
    NuFileDevice* iVar3;
    for (iVar3 = sm_Devices[iVar2]; iVar3 == 0 || this != iVar3; iVar2 += 4) {
        sm_NumDevices--;
        if (sm_NumDevices < 1) return;
    }
}

void NuFileDevice::getDeviceByType(NuFileDeviceType deviceType) {
    
}
