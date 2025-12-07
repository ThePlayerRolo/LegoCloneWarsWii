#include "types.h"



class NuFileDevice;

struct FileDeviceDirectoryHandle {
    NuFileDevice* unk0;
    int unk4;
};

struct NuFileDeviceType {
    u32 unk0;
};

class NuFileDevice {
public:
    NuFileDevice();

    ~NuFileDevice();
    virtual u32 GetPositionOnDisc(const char*, long long&) const;
    virtual void DirClose(int);
    int AllocDirectoryHandle(const char*);
    void Interrogate();
    void AddDevice(NuFileDevice*);
    void SetDefaultDevice(NuFileDeviceType);
    void getDeviceByType(NuFileDeviceType);
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

    static NuFileDevice* sm_Devices[3];    
    static NuFileDevice* sm_DefaultDevice;
    static int sm_NumDevices; 
    static int sm_CriticalSection;
    static FileDeviceDirectoryHandle sm_DirectoryHandles[8]; 
};
