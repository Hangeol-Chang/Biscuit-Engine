#ifndef VULKAN_HELPER_H
#define VULKAN_HELPER_H

#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>
#include "guiTypes.h"

namespace gui {
    /*
        debugger function들은 class를 안만드는 대신
        debuging용 namespace를 만들어서 관리.
    */
   
    // 어디까지 helper로 꺼내야 하는건지 경계가 모호해지고 있음. 잘 정리할 것.
    namespace helper {
        bool IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface, const std::vector<const char*>& deviceExtensions);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
        int RateDeviceSuitability(VkPhysicalDevice device);
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*>& deviceExtensions);
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
        std::vector<char> ReadFile(const std::string& filename);
        VkShaderModule CreateShaderModule(const std::vector<char>& code, VkDevice device);
        uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);
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

        // debug class 있어야 할수도 ?
    }
}

#endif // VULKAN_HELPER_H