#include "../interface/BiscuitEngine.h"
#include "../interface/BakeBehaviour.h"

#include "../include/EngineDebugger.h"
#include "../behaviour/header/UserBehaviours.h"

namespace engine {
    bool BiscuitEngine::Initialize() {
        fileManager = FileManager();
        BuildComponents();
        
        return true;
    }
    void BiscuitEngine::BuildComponents() {
        printf("[ENGINE] Build Components\n");
        // 컴포넌트 빌드.
        rootComponent = fileManager.ReadComponent("data/GUI.components.json");
        // behaviours 연결.

        // module test
        auto debugger = BakeBehaviour::CreateInstance("EngineDebugger");
        auto aa = BakeBehaviour::CreateInstance("ThrottleBehaviour");

        BakeBehaviour::RegistUpdates();
    }
    AppParameter BiscuitEngine::BuildAppParameter() {
        printf("[ENGINE] Build App Parameter\n");
        return fileManager.ReadAppParameter("data/GUI.configration.json");
    }

    void BiscuitEngine::Tick() {
        for (auto& cb : bakeUpdateFunctions) { cb(); }
    }
    
    void BiscuitEngine::AddUpdate(const std::function<void()>& cb)  {
        bakeUpdateFunctions.push_back(cb);
    }
}