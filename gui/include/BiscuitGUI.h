#ifndef BISCUIT_GUI_H
#define BISCUIT_GUI_H

#include <iostream>
#include "./VulkanAPI.h"
#include "BiscuitEngine.h"
#include "engineTypes.h"

namespace gui {
    class BiscuitGUI {
    public:
        BiscuitGUI();
        ~BiscuitGUI();

        VulkanAPI graphicsAPI;

        void Run();

    private:
        engine::BiscuitEngine& biscuitEngine = engine::BiscuitEngine::GetInstance();
        engine::AppParameter appParameter;

        uint32_t frameRate = 60;
    };
}

#endif // BISCUIT_GUI_H
