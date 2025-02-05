
#include "../include/BiscuitGUI.h"
#include <chrono>
#include <thread>

namespace gui {
    BiscuitGUI::BiscuitGUI() {
        printf("[GUI] Application constructor\n");
        appParameter = biscuitEngine.BuildAppParameter();

        biscuitEngine.Initialize();     // gui 파일 읽어옴.
    }
    BiscuitGUI::~BiscuitGUI() {
        printf("[GUI] Application destructor\n");
    }
    
    void BiscuitGUI::Run() {
        gui::VulkanAPI api;
        try {
            api.SetGUIParameter(appParameter);

            api.InitWindow();
            api.InitVulkan();

            // build된 Components를 이용해서 Vertex, Index buffer를 만드는 작업을 해야 함.
            auto rootComponent = biscuitEngine.GetRootComponent();

            while(true) {
                auto startFrame = std::chrono::steady_clock::now();

                biscuitEngine.Tick();
                if(!api.Tick(biscuitEngine.GetRootComponent())) { 
                    break; 
                }                

                auto endFrame = std::chrono::steady_clock::now();
                auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - startFrame);

                if(frameDuration.count() < 1000 / frameRate) {  // 이렇게 쓰면 프레임 밀림. 보간 필요.
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / frameRate - frameDuration.count()));
                }
            }
            api.Cleanup();

        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    }
}