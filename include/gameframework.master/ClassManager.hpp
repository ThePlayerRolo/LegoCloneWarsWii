#include "types.h"

class LevelContainer;

class ClassManager {
public:
    ClassManager(int);

    u32 GetNextManagerID();
    void SetInContainer(LevelContainer&);

    static u32 m_nextManagerID;
};
