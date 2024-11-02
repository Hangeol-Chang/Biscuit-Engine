#include "../include/EngineDebugger.h"

namespace engine {
    void EngineDebugger::Awake() {
        printf("[DEBUG] EngineDebugger Awake\n");
        prevFrame = std::chrono::steady_clock::now();
    }
    void EngineDebugger::Update() {
        // chrono를 이용해서 현재 프레임-이전 프레임 microsecond를 출력
        auto currentFrame = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentFrame - prevFrame);
        printf("[Engine Debugger] Frame duration: %.3f\n", duration.count()/1000.0);
        prevFrame = currentFrame;
    }
}