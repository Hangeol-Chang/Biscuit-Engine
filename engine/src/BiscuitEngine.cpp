#include "../interface/BiscuitEngine.h"
#include "../interface/BakeBehaviour.h"

namespace engine {
    BiscuitEngine::BiscuitEngine() {
        
    }
    BiscuitEngine::~BiscuitEngine() {
        
    }

    void BiscuitEngine::Tick() {
        for (auto& cb : bakeUpdateFunctions) { cb(); }
    }
    
    void BiscuitEngine::AddUpdate(const std::function<void()>& cb)  {
        bakeUpdateFunctions.push_back(cb);
    }
}