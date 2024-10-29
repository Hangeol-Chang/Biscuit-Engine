#include "../interface/BiscuitEngine.h"
#include "../interface/BakeBehaviour.h"

namespace engine {
    bool BiscuitEngine::Initialize() {
        fileManager = FileManager();

        BuildComponents();
        return true;
    }
    void BiscuitEngine::BuildComponents() {
        // root = std::make_shared<Component<ModelData_Dynamic, TextureData_Color>>();
        root = fileManager.ReadComponent("data/GUI.components.json");
        printf("[ENGINE] Build Components\n");
    }

    void BiscuitEngine::Tick() {
        for (auto& cb : bakeUpdateFunctions) { cb(); }
    }
    
    void BiscuitEngine::AddUpdate(const std::function<void()>& cb)  {
        bakeUpdateFunctions.push_back(cb);
    }
}