// editor, gui에서 사용할 api class
// static 하게 떠있어야함.
#ifndef BISCUIT_ENGINE_H
#define BISCUIT_ENGINE_H

#include <iostream>
#include <functional>
#include <vector>

#include "../include/FileManager.h"
#include "types.h"

namespace engine {

    // template <typename MM, typename TM>
    // class Component;    

    class BiscuitEngine {
    public:
        static BiscuitEngine& GetInstance() {
            static BiscuitEngine instance;
            return instance;
        }
        BiscuitEngine(BiscuitEngine const&) = delete;
        // void operator=(BiscuitEngine const&) = delete;

        // engine api
        void Tick();
        void AddUpdate(const std::function<void()>& cb);

        // parameter 받을 거 많음.
        template<typename T>
        void RegistComponent(T behaviour);

        // parameter 필요한거 추가할 것.
        bool Initialize();
        // json data가 업데이트 되거나, 최초 BiscuitEngine 생성될 떄 호출해서,
        // Compoenent를 만드는 함수.
        void BuildComponents();

    private :
        BiscuitEngine() = default;
        ~BiscuitEngine() = default;

        FileManager fileManager;

        std::vector<std::function<void()>> bakeUpdateFunctions;
        std::shared_ptr<Component<ModelData_Dynamic, TextureData_Color>> root;
    };
}

#endif // BISCUIT_ENGINE_H