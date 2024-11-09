#include <vector>
#include <string>

#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#else
#define VK_USE_PLATFORM_XCB_KHR
#define GLFW_EXPOSE_NATIVE_X11
#endif

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>

#include "VulkanHelper.h"
#include "guiTypes.h"
#include "engineTypes.h"


const int MAX_FRAMES_IN_FLIGHT = 2;

namespace gui {

    class VulkanAPI {
    public:
        VulkanAPI();
        ~VulkanAPI() {};

        // Setting apis
        void SetGUIParameter(engine::AppParameter parameter);

        // 외부에서 호출할 key 함수들.
        void InitWindow();
        void InitVulkan();
        bool Tick();
        void Cleanup();

        // 외부에서 호출할 setting 함수들.
        // glm::vec3 pos, glm::vec2 uv를 인수로 받아야함.
        uint32_t CreateMesh(std::vector<glm::vec3> vertices, std::vector<uint16_t> indices, std::vector<glm::vec2> uvs);
        
    private:

        // 내부 호출 setting 함수들.
        template <typename T>
        Buffer CreateBuffer(std::vector<T> data);

        // initialize logic
        void CreateInstance();
        void CreateSurface();
        void PickPhysicalDevice();
        void CreateLogicalDevice();
        void CreateSwapChain();
        void CreateImageViews();
        void CreateRenderPass();
        void CreateDescriptorSetLayout();
        void CreateGraphicsPipeline();
        void CreateFramebuffers();
        void CreateCommandPool();

        void CreateTextureImage();
        void CreateTextureImageView();
        void CreateTextureSampler();

        void CreateVertexBuffer();
        void CreateIndexBuffer();
        void CreateUniformBuffers();
        void CreateDescriptorPool();
        void CreateDescriptorSets();
        void CreateCommandBuffer();
        void CreateSyncObjects();
        static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

        void RecreateSwapChain();

        // running logic
        void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void DrawFrame();
        void UpdateUniformBuffer(uint32_t currentImage);

        void MainLoop();
        void CleanupSwapChain();

        // common functions
        void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        VkCommandBuffer BeginSingleTimeCommands();
        void EndSingleTimeCommands(VkCommandBuffer commandBuffer);

        void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        VkImageView CreateImageView(VkImage image, VkFormat format);

        GLFWwindow* window;
        VkInstance instance;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkSurfaceKHR surface;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        VkRenderPass renderPass;
        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        std::vector<void*> uniformBuffersMapped;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;

        // imgeAvailableSemaphore는 ObjectPool화 할 것.
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        uint32_t currentFrame = 0;
        bool framebufferResized = false;

        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        MeshPool meshPool;
        uint32_t testMesh;

        const std::vector<Vertex> vertices = {
            {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, -0.5f, 0.0f},  {0.0f, 0.0f}},
            {{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f}},
            {{-0.5f, 0.5f, 0.0f},  {1.0f, 1.0f}}
        };
        const std::vector<uint16_t> indices = {
            0, 1, 2, 2, 3, 0
        };


        // custom variables
        engine::AppParameter appParameter;

        /*-- setting apis --*/
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

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
