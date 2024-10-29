#include <iostream>
#include "./include/BiscuitGUI.h"

using namespace gui;

int main() {
    printf("[GUI] start gui process\n");

    gui::BiscuitGUI app;
    try {
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}