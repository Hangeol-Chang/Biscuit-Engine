// editor, gui에서 사용할 api class
// static 하게 떠있어야함.
#ifndef BISCUIT_ENGINE_H
#define BISCUIT_ENGINE_H

#include <iostream>
#include <functional>
#include <vector>

namespace engine {
    class BiscuitEngine {
    public:
        static BiscuitEngine& GetInstance() {
            static BiscuitEngine instance;
            return instance;
        }
        BiscuitEngine(BiscuitEngine const&) = delete;
        void operator=(BiscuitEngine const&) = delete;

        // engine api
        void Tick();
        void AddUpdate(const std::function<void()>& cb);

        // parameter 받을 거 많음.
        template<typename T>
        void RegistComponent(T behaviour);

    private :
        BiscuitEngine();
        ~BiscuitEngine();

        std::vector<std::function<void()>> bakeUpdateFunctions;
    };
}

#endif // BISCUIT_ENGINE_H