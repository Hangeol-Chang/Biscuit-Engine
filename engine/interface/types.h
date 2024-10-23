#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

// namespace engine으로 한정하지 않음.
// engine에서 사용될 types들
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <map>
#include <memory>

#include "BakeBehaviour.h"

namespace engine {

    ///////////////// about model /////////////////
    typedef struct ModelData_Dynamic {
        std::vector<glm::vec3> vertices;
        std::vector<uint32_t> indices;
        std::vector<glm::vec2> uvs;
    } ModelData_Dynamic;

    typedef struct ModelData_Static {
        std::string modelFile;
    } ModelData_Static;

    template <typename T>   // T as ModelData_Dynamic, ModelData_Static
    class Model {
    public:
        void UpdateData(T data) { this->data = data; }
    private:
        std::string mode;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        T data;

    };

    ///////////////// about texture /////////////////
    typedef struct TextureData_Color {
        glm::vec3 color;
    } TextureData_Color;

    typedef struct TextureData_Image {
        std::string imageFile;
    } TextureData_Image;

    template <typename T>   // T as TextureData_Color, TextureData_Image
    class Texture {
    public:
        void UpdateData(T data) { this->data = data; }
    private:
        std::string mode;
        T data;
    };

    ///////////////// about shader /////////////////
    class Shader {
        std::string vertexShader;
        std::string fragmentShader;
        // 나중에 추가할 거 생기면 추가할 것.
    };
    
    ///////////////// Component /////////////////
    class ComponentBase {
    public:
        virtual ~ComponentBase() = default;

    protected:
        std::string behaviourName;
        std::string parent;
        std::string name;
        std::shared_ptr<BakeBehaviour> behaviour;
        
        std::map<std::string, std::shared_ptr<ComponentBase>> parent;
        std::map<std::string, std::shared_ptr<ComponentBase>> children;
    };

    template <typename MM, typename TM>
    class Component : public ComponentBase {
    public:
        void UpdateModel(MM model) { this->model.UpdateData(model); }
        void UpdateTexture(TM texture) { this->texture.UpdateData(texture); }

        Model<MM> GetModel() { return model; }
        Texture<TM> GetTexture() { return texture; }

    private:
        Model<MM>   model;
        Texture<TM> texture;

        Shader shader;
    };
}

#endif //ENGINE_TYPES_H