#include <iostream>
#include "./include/VulkanAPI.h"

using namespace gui;

int main() {
    printf("gui main\n");

    VulkanAPI app;
    try {
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}