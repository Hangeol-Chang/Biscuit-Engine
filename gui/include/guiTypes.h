#ifndef GUI_TYPES_H
#define GUI_TYPES_H

#include <vector>
#include <optional>
#include <vulkan/vulkan.h>
#include <array>
#include <glm/glm.hpp>
#include <unordered_map>
#include <queue>
#include <memory>

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
        std::shared_ptr<Mesh> GetMesh(uint32_t bufferId) {
            auto it = meshs.find(bufferId);
            if (it != meshs.end()) {
                return std::shared_ptr<Mesh>(&it->second, [](Mesh*) {});
            } else {
                throw std::runtime_error("Mesh not found");
            }
        }
    
        uint32_t AddMesh(const Mesh& mesh) {
            uint32_t newId = nextMeshId++;
            meshs[newId] = mesh;
            return newId;
        }
    
        bool RemoveMesh(VkDevice device, uint32_t bufferId) {
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
        
        void Cleanup(VkDevice device) {
            for (auto& [id, mesh] : meshs) {
                DestroyBuffer(device, mesh.vertexBuffer);
                DestroyBuffer(device, mesh.indexBuffer);
            }
            meshs.clear();
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

    struct Texture {
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        VkImage image;
        VkDeviceMemory imageMemory;
        VkImageView imageView;
        VkSampler sampler;
    };

    class TexturePool {
    public:
        std::shared_ptr<Texture> GetTexture(uint32_t textureId) {
            auto it = textures.find(textureId);
            if (it != textures.end()) {
                return it->second;
            } else {
                throw std::runtime_error("Texture not found");
            }
        }
        uint32_t AddTexture(Texture& texture) {
            uint32_t newId = nextTextureId++;
            textures[newId] = std::make_shared<Texture>(texture);
            return newId;
        }
        bool RemoveTexture(VkDevice device, uint32_t textureId){
            auto it = textures.find(textureId);
            if (it != textures.end()) {
                // Free memory and destroy buffers if necessary
                vkDestroySampler(device, it->second->sampler, nullptr);
                vkDestroyImageView(device, it->second->imageView, nullptr);
                vkDestroyImage(device, it->second->image, nullptr);
                vkFreeMemory(device, it->second->imageMemory, nullptr);
                textures.erase(it);
                return true;
            }
            return false;
        }
        void Cleanup(VkDevice device) {
            for (auto& [id, texture] : textures) {
                vkDestroySampler(device, texture->sampler, nullptr);
                vkDestroyImageView(device, texture->imageView, nullptr);
                vkDestroyImage(device, texture->image, nullptr);
                vkFreeMemory(device, texture->imageMemory, nullptr);
            }
            textures.clear();
        }

    private:
        std::unordered_map<uint32_t, std::shared_ptr<Texture>> textures;
        uint32_t nextTextureId = 0;
    };

    // 3d Model에 대한 Pool도 추가해야함.
    // 근데 텍스쳐 안쓰고 color쓰면 어뜨캄/.?

    struct Vertex {
        glm::vec3 pos;
        glm::vec2 texCoord;

        Vertex(glm::vec3 pos, glm::vec2 texCoord) : pos(pos), texCoord(texCoord) {}

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }

        /*
        pos만 동적 업데이트 하는 법에 대해서.
        // 1. VertexBuffer 메모리를 맵핑
        void* data;
        vkMapMemory(device, vertexBufferMemory, 0, bufferSize, 0, &data);

        // 2. pos만 업데이트
        Vertex* vertexData = reinterpret_cast<Vertex*>(data);
        for (uint32_t i = 0; i < vertexCount; ++i) {
            vertexData[i].pos = newPos[i];  // newPos는 업데이트할 glm::vec3 배열
        }

        // 3. 메모리 언맵
        vkUnmapMemory(device, vertexBufferMemory);

        */
    };

    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    struct BoolBlock {
        uint32_t useTexture;    // 4바이트로 정렬해야 해서 uint16_t 쓰기 애매함.
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