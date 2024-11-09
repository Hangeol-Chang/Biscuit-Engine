#include "../include/VulkanHelper.h"

#include <vector>
#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <set>

#include <vulkan/vulkan.h>

namespace gui {
    namespace helper {
        bool IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface, const std::vector<const char*>& deviceExtensions) {
            QueueFamilyIndices indices = FindQueueFamilies(device, surface);
            bool extensionsSupported = CheckDeviceExtensionSupport(device, deviceExtensions);
            bool swapChainAdequate = false;
            if (extensionsSupported) {
                SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device, surface);
                swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
            }
            VkPhysicalDeviceFeatures supportedFeatures;
            vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

            return indices.IsComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
        }
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
            QueueFamilyIndices indices;
            
            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

            std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());


            int i = 0;
            for (const auto& queueFamily : queueFamilies) {

                if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)  {
                    indices.graphicsFamily = i;
                }
                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
                if(presentSupport) { 
                    indices.presentFamily = i; 
                }
                
                if(indices.IsComplete()) { break; }
                i++;
            }

            return indices;
        }
        int RateDeviceSuitability(VkPhysicalDevice device) {
            VkPhysicalDeviceProperties deviceProperties;
            VkPhysicalDeviceFeatures deviceFeatures;
            vkGetPhysicalDeviceProperties(device, &deviceProperties);
            vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

            int score = 0;
            if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                score += 1000;
            }
            score += deviceProperties.limits.maxImageDimension2D;
            if(!deviceFeatures.geometryShader) { return 0; }
            return score;
        }
        bool CheckDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*>& deviceExtensions) {
            uint32_t extensionCount;
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
            std::vector<VkExtensionProperties> availableExtensions(extensionCount);
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

            std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
            for(const auto& extension : availableExtensions) {
                requiredExtensions.erase(extension.extensionName);
            }
            return requiredExtensions.empty();
        }
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) {

            SwapChainSupportDetails details;
            
            vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
            uint32_t formatCount;
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

            if(formatCount != 0) {
                details.formats.resize(formatCount);
                vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
            }

            uint32_t presentModeCount;
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

            if (presentModeCount != 0) {
                details.presentModes.resize(presentModeCount);
                vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
            }
            return details;
        }

        std::vector<char> ReadFile(const std::string& filename) {
            std::ifstream file(filename, std::ios::ate | std::ios::binary);
            if (!file.is_open()) {
                throw std::runtime_error("failed to open file!");
            }
            size_t fileSize = (size_t) file.tellg();
            std::vector<char> buffer(fileSize);

            file.seekg(0);
            file.read(buffer.data(), fileSize);
            file.close();

            return buffer;
        }
        VkShaderModule CreateShaderModule(const std::vector<char>& code, VkDevice device) {
            VkShaderModuleCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo.codeSize = code.size();
            createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
            VkShaderModule shaderModule;
            if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
                throw std::runtime_error("failed to create shader module!");
            }
            return shaderModule;
        }

        uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice) {
            VkPhysicalDeviceMemoryProperties memProperties;
            vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

            for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
                if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                    return i;
                }
            }

            throw std::runtime_error("failed to find suitable memory type!");
        }        
        void printBufferData(VkDevice device, Buffer buffer) {

            // 먼저, 메모리를 맵핑하여 CPU에서 읽을 수 있도록 합니다.
            void* data;
            VkResult result = vkMapMemory(device, buffer.memory, 0, VK_WHOLE_SIZE, 0, &data);
            if (result != VK_SUCCESS) {
                std::cerr << "Failed to map buffer memory!" << std::endl;
                return;
            }
            VkMemoryRequirements memoryRequirements;
            vkGetBufferMemoryRequirements(device, buffer.buffer, &memoryRequirements);
            
            // 버퍼의 데이터를 읽어서 출력합니다.
            // 예를 들어, 버퍼에 float 데이터가 있다고 가정:
            float* bufferData = static_cast<float*>(data);
            printf("Buffer size : %d || Buffer Data ▽ %d", memoryRequirements.size);

            for (size_t i = 0; i < memoryRequirements.size / sizeof(float); ++i) {
                if(i % 3 == 0) printf("\n%d : ", i);
                printf("%.3f ", bufferData[i]);
            }

            std::cout << std::endl;

            // 메모리 맵핑을 해제합니다.
            vkUnmapMemory(device, buffer.memory);
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