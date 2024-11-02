#include "../interface/BakeBehaviour.h"
#include "../common/StringHelper.h"

namespace engine {
    // static variables init
    std::map<size_t, std::shared_ptr<BakeBehaviour>> BakeBehaviour::behaviours;

    // static functions
    std::shared_ptr<BakeBehaviour> BakeBehaviour::FindBehaviour(std::string *name) {
        auto b = behaviours.find(hashStr(*name));
        if(b != behaviours.end()) { return b->second; }
        return nullptr;
    }

    // basic bake logic
    BakeBehaviour::BakeBehaviour(const std::string &name) {
        this->name = name;
    }
    
    void BakeBehaviour::Update() { useUpdate = false; }

    // regist 관련 함수들
    std::map<std::string, std::function<std::shared_ptr<BakeBehaviour>()>>& BakeBehaviour::GetRegistry() {
        static std::map<std::string, std::function<std::shared_ptr<BakeBehaviour>()>> registry;
        return registry;
    }
    void BakeBehaviour::RegistBehaviour(const std::string& name, std::function<std::shared_ptr<BakeBehaviour>()> creator) {
        GetRegistry()[name] = creator;
    }
    std::shared_ptr<BakeBehaviour> BakeBehaviour::CreateInstance(const std::string& name) {
        auto it = GetRegistry().find(name);

        if (it != GetRegistry().end()) { 
            auto instance = it->second();
            behaviours.insert({hashStr(name), instance});
            return instance; 
        }
        return nullptr;
    }

    void BakeBehaviour::RegistUpdates() {
        for(auto& b : behaviours) {
            try {
                b.second->Update();         // update 한 번 걸어보고, 
                if(b.second->useUpdate) {   // BakeBehaviour의 Update가 불리지 않으면 등록.
                    BiscuitEngine::GetInstance().AddUpdate( [b]() { b.second->Update(); } );
                }
            }
            catch(const std::exception& e) {
                printf("[Engine][BUG] error occured trying to regist update\n -- message -- \n");
                printf("%s\n", e.what());
            }
        }
    }

}