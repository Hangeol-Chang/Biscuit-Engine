#ifndef ENGINE_DEBUGGER_H
#define ENGINE_DEBUGGER_H

#include "../interface/BiscuitEngine.h"
#include "../interface/BakeBehaviour.h"

/*
    BakeBehaviour의 상속 예제이면서,
    frame debug 등 개발에 필요한 사양이 들어간 클래스.
*/

namespace engine {
    class EngineDebugger : public BakeBehaviour {
    DEFINE_BAKEBEHAVIOUR(EngineDebugger)
    public:
        void Awake() override;
        void Update() override;
    private:
    };
    REGISTER_BEHAVIOUR(EngineDebugger)
}

#endif // ENGINE_DEBUGGER_H