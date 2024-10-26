#include "../interface/BakeBehaviour.h"
#include "../common/StringHelper.h"

namespace engine {
    // static variables init
    std::map<size_t, BakeBehaviour *> BakeBehaviour::behaviours;

    // static functions
    BakeBehaviour *BakeBehaviour::FindBehaviour(std::string *name) {
        auto b = behaviours.find(hashStr(*name));
        if(b != behaviours.end()) { return b->second; }
        return nullptr;
    }

    // basic bake logic
    BakeBehaviour::BakeBehaviour(std::string &name) {
        behaviours.insert(
            std::make_pair(hashStr(name), this)
        );
        // update 등록.
    }
    
    void BakeBehaviour::Update() {
        useUpdate = false;
    }
}