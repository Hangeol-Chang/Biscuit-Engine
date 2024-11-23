#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

// engine에서 사용될 types들
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <map>
#include <memory>

namespace engine {
    class BakeBehaviour;

    ///////////////// about model /////////////////
    typedef struct IModel {
        virtual ~IModel() {};
        std::string mode;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        uint32_t meshId;    // gui가 주는 데이터.

        virtual void Print() const {
            printf("Model Mode: %s\n", mode.c_str());
            printf("Position: (%.3f, %.3f, %.3f)\n", position.x, position.y, position.z);
            printf("Rotation: (%.3f, %.3f, %.3f)\n", rotation.x, rotation.y, rotation.z);
            printf("Scale: (%.3f, %.3f, %.3f)\n", scale.x, scale.y, scale.z);
        }
    };

    typedef struct ModelData_Dynamic : public IModel {
        // json으로부터 읽는 데이터.
        std::vector<glm::vec3> vertices;
        std::vector<uint16_t> indices;
        std::vector<glm::vec2> uvs;

        void Print() const override {
            IModel::Print();
            printf("Vertices: [\n");
            int i = 0;
            for(const auto& vertex : vertices)              printf("\t%d : (%.3f, %.3f, %.3f) \n", i++, vertex.x, vertex.y, vertex.z);
            printf("]\nIndices: [\n");
            for(size_t i = 0; i < indices.size(); i += 3)   printf("\t%zu : %u %u %u \n", i, indices[i], indices[i+1], indices[i+2]);
            i = 0;
            printf("]\nUVs: [\n");
            for(const auto& uv : uvs)                       printf("\t%d : (%.3f, %.3f) \n", i++, uv.x, uv.y);
            printf("]\n");
        }
    } ModelData_Dynamic;

    typedef struct ModelData_Static : public IModel {
        std::string modelFile;
    } ModelData_Static;

    ///////////////// about texture /////////////////
    typedef struct ITexture {
        virtual ~ITexture() {};
        std::string mode;
        uint32_t textureId; // gui가 주는 데이터.

        virtual void Print() const {
            printf("Texture Mode: %s\n", mode.c_str());
        }
    };
    typedef struct TextureData_Color : public ITexture {
        glm::vec3 color;
        void Print() const override {
            ITexture::Print();
            printf("Color: (%.3f, %.3f, %.3f)\n", color.r, color.g, color.b);
        }
    } TextureData_Color;

    // image 파일 링크만 들어오는게 아니라, vulkan에서 사용할 수 있도록 메모리를 가르키고 있어야함.
    typedef struct TextureData_Image : public ITexture {
        std::string imageFile;
        void Print() const override {
            ITexture::Print();
            printf("Image File: %s\n", imageFile.c_str());
        }
    } TextureData_Image;

    ///////////////// about shader /////////////////
    typedef struct Shader {
        void Print() const {
            printf("Vertex Shader: %s\nFragment Shader: %s\n", vertexShader.c_str(), fragmentShader.c_str());
        }
        std::string vertexShader;
        std::string fragmentShader;
        // 나중에 추가할 거 생기면 추가할 것.
    };
    
    ///////////////// Component /////////////////
    class Component : public std::enable_shared_from_this<Component> {
    public:
        Component(std::string name) : name(name) {}
        Component() = default;
        virtual ~Component() = default;
        std::string GetName() { return name; }

        std::map<std::string, std::shared_ptr<Component>> parent;
        std::map<std::string, std::shared_ptr<Component>> children;

        std::string behaviourName;
        std::shared_ptr<BakeBehaviour> behaviour;

        void SetModel(std::shared_ptr<IModel> m) { this->model = m; }
        void SetTexture(std::shared_ptr<ITexture> t) { this->texture = t; }
        void SetShader(std::shared_ptr<Shader> s) { this->shader = s; }
        std::shared_ptr<IModel>     GetModel() { return model; }
        std::shared_ptr<ITexture>   GetTexture() { return texture; }
        std::shared_ptr<Shader>     GetShader() { return shader; }

        std::shared_ptr<IModel>     model;
        std::shared_ptr<ITexture>   texture;
        std::shared_ptr<Shader>     shader;

        std::string name;

        void Print(int depth = 0) const {
            std::string indent(depth * 2, ' ');
            printf("%sComponent Name: %s\n", indent.c_str(), name.c_str());
            printf("%sBehaviour Name: %s\n", indent.c_str(), behaviourName.c_str());
            printf("%sModel: -\n", indent.c_str());
            model->Print();
            printf("%sTexture: -\n", indent.c_str());
            texture->Print();
            printf("%sShader: -\n", indent.c_str());
            shader->Print();

            printf("%sChildren: -\n", indent.c_str());
            for (const auto& [childName, childPtr] : children) {
                childPtr->Print(depth + 1);
                printf("\n");
            }
        }
    private:

    };

    // application Parameter
    typedef struct ApplicationParameter {
    public:
        std::string title;
        std::pair<uint32_t, uint32_t> windowSize;
        bool fullScreen;

        bool vulkanValidation;
        bool vulkanDebug;
        bool resizeable;

        void Print() const {
            printf("== Application Parameter ==\n");
            printf("Title: %s\n", title.c_str());
            printf("Window Size: (%d, %d)\n", windowSize.first, windowSize.second);
            printf("Full Screen: %s\n", fullScreen ? "true" : "false");
            printf("Vulkan Validation: %s\n", vulkanValidation ? "true" : "false");
            printf("Vulkan Debug: %s\n", vulkanDebug ? "true" : "false");
            printf("Resizeable: %s\n", resizeable ? "true" : "false");
            printf("===========================\n");
        }
    } AppParameter;
}

#endif //ENGINE_TYPES_H