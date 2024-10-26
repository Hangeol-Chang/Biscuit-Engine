
#include "../include/BiscuitGUI.h"
#include "BiscuitEngine.h"

namespace gui {
    BiscuitGUI::BiscuitGUI() {
        // Biscuit engine 초기화
        engine::BiscuitEngine& biscuitEngine = engine::BiscuitEngine::GetInstance();
        biscuitEngine.Initialize();


        printf("GUIApplication constructor\n");
    }

    BiscuitGUI::~BiscuitGUI() {
        printf("GUIApplication destructor\n");
    }
}