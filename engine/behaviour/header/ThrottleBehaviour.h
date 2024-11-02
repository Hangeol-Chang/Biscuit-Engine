#include "BakeBehaviour.h"

namespace engine {
    class ThrottleBehaviour : public BakeBehaviour {
    DEFINE_BAKEBEHAVIOUR(ThrottleBehaviour)
    public:
        void Awake() override;
        void Update() override;
    private:
    };
    REGISTER_BEHAVIOUR(ThrottleBehaviour)
}
