
#include "../include/BiscuitGUI.h"
#include <chrono>
#include <thread>

namespace gui {
    BiscuitGUI::BiscuitGUI() {
        printf("[GUI] Application constructor\n");
        biscuitEngine.Initialize();
    }
    BiscuitGUI::~BiscuitGUI() {
        printf("[GUI] Application destructor\n");
    }
    
    void BiscuitGUI::Run() {
        // Biscuit engine tick

        gui::VulkanAPI api;
        try {
            api.InitWindow();
            api.InitVulkan();

            while(true) {
                auto startFrame = std::chrono::steady_clock::now();

                if(!api.Tick()) { break; };

                auto endFrame = std::chrono::steady_clock::now();
                auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - startFrame);

                if(frameDuration.count() < 1000 / frameRate) {
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