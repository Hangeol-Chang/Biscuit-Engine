#include "../include/VulkanHelper.h"

#include <vector>
#include <iostream>
#include <string>

#include <vulkan/vulkan.h>

namespace gui {
    namespace helper {
        bool IsDeviceSuitable(VkPhysicalDevice device) {
            return true;
        }
    }

    namespace debugger {
        void CheckValidExtensions() {
            uint32_t extensionCount = 0;
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
            std::vector<VkExtensionProperties> extensions(extensionCount);
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

            printf("available extensions:\n");
            for (const auto& extension : extensions)
                printf("\t %s\n", extension.extensionName);
            printf("-------------------------\n");
        }

        void CheckValidLayers() {
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
            
            printf("available layers:\n");
            for (const auto& layerProperties : availableLayers)
                printf("\t %s\n", layerProperties.layerName);
            printf("-------------------------\n");
        }
    }
}