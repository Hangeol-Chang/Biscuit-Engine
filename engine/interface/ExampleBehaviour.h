#ifdef NONE_INCLUDE

#include "../interface/BakeBehaviour.h"

namespace engine {
    class ExampleBehaviour : public BakeBehaviour {
    DEFINE_BAKEBEHAVIOUR(ExampleBehaviour)  // 클래스 처음에 DEFINE_BAKEBEHAVIOUR를 적어여야 함.
    public:
        void Awake() override;
        void Update() override;
    private:
    };
    REGISTER_BEHAVIOUR(ExampleBehaviour)
}

#endif // NONDE_INCLUDE