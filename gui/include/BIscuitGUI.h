
// engine으로부터 파라미터를 읽어서,
// 실제로 vulkan에 그리는 명령을 내리는 클래스.

#ifndef BISCUIT_GUI_H
#define BISCUIT_GUI_H

#include <iostream>
#include "./VulkanAPI.h"

namespace gui {
    class BiscuitGUI {
    public:
        BiscuitGUI();
        ~BiscuitGUI();

        VulkanAPI graphicsAPI;

    private:

    };
}

#endif // BISCUIT_GUI_H