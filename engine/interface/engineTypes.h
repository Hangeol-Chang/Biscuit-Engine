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

        virtual void Print() const {
            printf("Model Mode: %s\n", mode.c_str());
            printf("Position: (%.3f, %.3f, %.3f)\n", position.x, position.y, position.z);
            printf("Rotation: (%.3f, %.3f, %.3f)\n", rotation.x, rotation.y, rotation.z);
            printf("Scale: (%.3f, %.3f, %.3f)\n", scale.x, scale.y, scale.z);
        }
    };

    typedef struct ModelData_Dynamic : public IModel {
        std::vector<glm::vec3> vertices;
        std::vector<uint32_t> indices;
        std::vector<glm::vec2> uvs;


        void Print() const override {
            IModel::Print();
            printf("Vertices: [");
            for (const auto& vertex : vertices) {
                printf("(%.3f, %.3f, %.3f) ", vertex.x, vertex.y, vertex.z);
            }
            printf("]\nIndices: [");
            for (const auto& index : indices) {
                printf("%u ", index);
            }
            printf("]\nUVs: [");
            for (const auto& uv : uvs) {
                printf("(%.3f, %.3f) ", uv.x, uv.y);
            }
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
    class Component {
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

        void Print(int depth = 0) const {
            std::string indent(depth * 2, ' ');
            printf("%sComponent Name: %s\n", indent.c_str(), name.c_str());
            printf("%sBehaviour Name: %s\n", indent.c_str(), behaviourName.c_str());
            printf("%sModel: -\n", indent.c_str());
            if(model->mode == "dynamic") {
                std::static_pointer_cast<ModelData_Dynamic>(model)->Print();
            } else if(model->mode == "static") {
                std::static_pointer_cast<ModelData_Dynamic>(model)->Print();
            }
            printf("%sTexture: -\n", indent.c_str());
            if(texture->mode == "color") {
                std::static_pointer_cast<TextureData_Color>(texture)->Print();
            } else if(texture->mode == "image") {
                std::static_pointer_cast<TextureData_Image>(texture)->Print();
            }
            printf("%sShader: -\n", indent.c_str());
            shader->Print();

            printf("%sChildren: -\n", indent.c_str());
            for (const auto& [childName, childPtr] : children) {
                childPtr->Print(depth + 1);
                printf("\n");
            }
        }
    private:
        std::shared_ptr<IModel>     model;
        std::shared_ptr<ITexture>   texture;
        std::shared_ptr<Shader>     shader;

        std::string name;
    };
}

#endif //ENGINE_TYPES_H