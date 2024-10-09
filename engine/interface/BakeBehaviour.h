#ifndef BAKE_BEHAVIOUR_H
#define BAKE_BEHAVIOUR_H

#include <string>
#include <map>

#include "BiscuitEngine.h"

// 유니티의 MonoBehaviour와 비슷한 역할을 하는 클래스
class BakeBehaviour {
public:
    BakeBehaviour() {
        // BiscuitEigne의 Add 등으로 스크립트를 등록해줘야함.
        // 업데이트를 사용할 떄와, 사용하지 않을 때의 등록을 나눌 것.
    }

    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update() {};

protected:
    // static하게 띄워서 
    static BakeBehaviour *FindBehaviour(std::string *name);
    static std::map<size_t, BakeBehaviour*> behaviours; // hashcode, BakeBehaviour

private:


};

#endif // BAKE_BEHAVIOUR_H 