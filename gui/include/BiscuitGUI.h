#ifndef BISCUIT_GUI_H
#define BISCUIT_GUI_H

#include <iostream>
#include "./VulkanAPI.h"
#include "BiscuitEngine.h"

namespace gui {
    class BiscuitGUI {
    public:
        BiscuitGUI();
        ~BiscuitGUI();

        VulkanAPI graphicsAPI;

        void Run();

    private:
        engine::BiscuitEngine& biscuitEngine = engine::BiscuitEngine::GetInstance();

        uint32_t frameRate = 60;
    };
}

#endif // BISCUIT_GUI_H
