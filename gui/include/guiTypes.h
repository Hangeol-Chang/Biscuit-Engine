#ifndef GUI_TYPES_H
#define GUI_TYPES_H

#include <vector>
#include <optional>
#include <vulkan/vulkan.h>
#include <array>
#include <glm/glm.hpp>
#include <unordered_map>
#include <queue>

namespace gui {
    // vertex, index 등 버퍼에 사용
    struct Buffer {
        VkBuffer buffer;
        VkDeviceMemory memory;
    };
    struct Mesh {
        Buffer vertexBuffer;
        Buffer indexBuffer;
        uint32_t indexCount;
    };

    class MeshPool {
    public:
        Buffer GetMesh(uint32_t bufferId) {
            auto it = meshs.find(bufferId);
            if (it != meshs.end()) {
                return it->second.vertexBuffer;
            } else {
                throw std::runtime_error("Mesh not found");
            }
        }
        uint32_t AddMesh(const Mesh& mesh) {
            uint32_t newId = nextMeshId++;
            meshs[newId] = mesh;
            return newId;
        }
        bool RemoveMesh(VkDevice device, uint32_t bufferId){
            auto it = meshs.find(bufferId);
            if (it != meshs.end()) {
                // Free memory and destroy buffers if necessary
                DestroyBuffer(device, it->second.vertexBuffer);
                DestroyBuffer(device, it->second.indexBuffer);
                meshs.erase(it);
                return true;
            }
            return false;
            }

    private:
        std::unordered_map<uint32_t, Mesh> meshs;
        uint32_t nextMeshId = 0;

        // Helper function to destroy a buffer
        void DestroyBuffer(VkDevice device, Buffer& buffer) {
            vkDestroyBuffer(device, buffer.buffer, nullptr);
            vkFreeMemory(device, buffer.memory, nullptr);
        }
    };


    struct Vertex {
        glm::vec2 pos;
        glm::vec3 color;
        glm::vec2 texCoord; // 나중에 이거 struct 따로 분리해야 함.

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }
    };

    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };


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