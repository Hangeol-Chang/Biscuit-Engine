#ifndef VULKAN_TYPES_H
#define VULKAN_TYPES_H

#include <vector>
#include <optional>

namespace gui {
    typedef struct QueueFamilyIndices_ {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool IsComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    } QueueFamilyIndices;

    typedef struct SwapChainSupportDetails_ {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    } SwapChainSupportDetails;
}

#endif // VULKAN_TYPES_H