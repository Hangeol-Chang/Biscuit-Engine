#include "BakeBehaviour.h"

namespace engine {
    class TBT3dArrowBehaviour : public BakeBehaviour {
    DEFINE_BAKEBEHAVIOUR(TBT3dArrowBehaviour) 
    public:
        void Awake() override;
        void Update() override;
    private:
    };
    REGISTER_BEHAVIOUR(TBT3dArrowBehaviour)
}
