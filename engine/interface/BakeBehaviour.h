#ifndef BAKE_BEHAVIOUR_H
#define BAKE_BEHAVIOUR_H

#include <string>
#include <map>

#include "BiscuitEngine.h"

namespace engine {
    // 유니티의 MonoBehaviour와 비슷한 역할을 하는 클래스
    class BakeBehaviour {
    public:
        BakeBehaviour() {};
        ~BakeBehaviour() {}
        BakeBehaviour(std::string &name);

        virtual void Awake() {};
        virtual void Start() {};
        virtual void Update();

        // transform function
        // transform function은 호출된 후에 child객체들에 대해서도 호출해줘야 함
        // BakdBehaviour 딴에서  구현해놓고 끝낼 것.
        // BakeBehaviour의 규모가 커짐에 따라, 내부적으로 Transform Struct를 새로 만들어서 그 안으로 옮길수도.
        void Translate();   // parameter 받을거 생각해볼 것.
        void Rotation();    // parameter 받을거 생각해볼 것.
        void Scale();       // parameter 받을거 생각해볼 것.

    protected:
        // static하게 띄워서 
        static BakeBehaviour *FindBehaviour(std::string *name);
        static std::map<size_t, BakeBehaviour *> behaviours; // hashcode, BakeBehaviour

        std::vector<BakeBehaviour*> children;   // 
        BakeBehaviour *parent = nullptr;        // 최상의 오브젝트일경우 root 오브젝트를 받아야 함 (카메라 제외)

    private:
        bool useUpdate = true;
    };
}

#endif // BAKE_BEHAVIOUR_H 