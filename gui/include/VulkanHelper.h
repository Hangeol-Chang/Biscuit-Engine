#ifndef VULKAN_HELPER_H
#define VULKAN_HELPER_H

#include <iostream>
#include <vulkan/vulkan.h>

namespace gui {

    /*
        debugger function들은 class를 안만드는 대신
        debuging용 namespace를 만들어서 관리.
    */
   
    namespace helper {
        bool IsDeviceSuitable(VkPhysicalDevice device);
    }

    namespace debugger {
        void CheckValidExtensions();
        void CheckValidLayers();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        ) {
            std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
            return VK_FALSE;
        }
    }
}

#endif // VULKAN_HELPER_H