#include "types.h"


class AIManager;
class ScriptProcessor;
class AIPACKET;

class AIState {
public:
    AIState();

    ~AIState();
    //Todo: Add the rest of the functions
    virtual void ChangeState(AIState*, AIManager&, ScriptProcessor*, AIPACKET, bool);
    virtual void Execute(AIState*, AIManager&, ScriptProcessor*, AIPACKET, f32);

    int _4;
    f32 _8;
    u8 _C;
};
