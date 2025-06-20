#include "gameframework.master/ClassManager.hpp"

u32 ClassManager::m_nextManagerID = 0xfffffffff;




u32 ClassManager::GetNextManagerID() {
    return ++m_nextManagerID;
}
