#include <vector>
#include <string>

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <glm./glm.hpp>

#include "VulkanHelper.h"

namespace gui {
    typedef struct VulkanParameter_t {
        std::string applicationName;
        std::string engineName;
        uint32_t applicationVersion;
        uint32_t engineVersion;
        uint32_t apiVersion;
        uint32_t windowWidth;
        uint32_t windowHeight;
        bool resizable;

    } VulkanParameter;

    class VulkanAPI {
    public:
        void Run();

        VulkanAPI();
        ~VulkanAPI() {};

        // Parameter file 읽는 함수.
        // engine에서 강제로 호출할 수도 있으며,
        // 호출된 후에는 연관된 것들을 Update해주는 로직이 필요함. 
        void ReadParameters(); 

    private:
        // initialize logic
        void InitWindow();
        void InitVulkan();
        void CreateInstance();
        void PickPhysicalDevice();
        void CreateLogicalDevice();
        void CreateSurface();
        void CreateSwapChain();

        void MainLoop();
        void CleanUp();

        GLFWwindow* window;
        VkInstance instance;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;


        // common vulkan functions
        


        // 분리될 debug 관련 함수들.
        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        std::vector<const char*> GetRequiredExtensions();
        // validation layer settings;
        void SetupDebugMessenger();
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        void     DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
        bool CheckValidationLayerSupport();
        std::vector<const char*> validationLayers = { 
            "not-avaliable"
        };
        VkDebugUtilsMessengerEXT debugMessenger;
        #ifdef GUI_DEBUG
            const bool enableValidationLayers = true;
        #else
            const bool enableValidationLayers = false;
        #endif
    };
}