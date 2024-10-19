#ifndef BAKE_BEHAVIOUR_H
#define BAKE_BEHAVIOUR_H

#include <string>
#include <map>

#include "BiscuitEngine.h"

namespace engine {
    // 유니티의 MonoBehaviour와 비슷한 역할을 하는 클래스
    class BakeBehaviour {
    protected:
        BakeBehaviour() {};
        ~BakeBehaviour() {}
    public:
        BakeBehaviour(std::string &name);

        virtual void Awake() {};
        virtual void Start() {};
        virtual void Update();

    protected:
        // static하게 띄워서 
        static BakeBehaviour *FindBehaviour(std::string *name);
        static std::map<size_t, BakeBehaviour*> behaviours; // hashcode, BakeBehaviour

    private:
        bool useUpdate = true;
    };
}

#endif // BAKE_BEHAVIOUR_H 