#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

// namespace engine으로 한정하지 않음.
// engine에서 사용될 types들
#include <string>
#include <vector>

namespace engine {

    // about model
    typedef struct ModelData_Dynamic {
        std::vector<glm::Vec3> vertices;
        std::vector<uint32_t> indices;
        std::vector<glm::Vec2> uvs;
    } ModelData_Dynamic;

    typedef struct ModelData_Static {
        std::string modelFile;
    } ModelData_Static;

    template <typename T>
    class Model {
        std::string mode;
        glm::Vec3 position;
        glm::Vec3 rotation;
        glm::Vec3 scale;
        T data;
    };


    // about texture
    typedef struct TextureData_Color {
        glm::Vec4 color;
    } TextureData_Color;

    typedef struct TextureData_Image {
        std::string imageFile;
    } TextureData_Image;

    template <typename T>
    class Texture {
        std::string mode;
        T data;
    }

    // about shader
    class Shader {
        std::string vertexShader;
        std::string fragmentShader;
        // 나중에 추가할 거 생기면 추가할 것.
    }
    

    // 이 class가 그대로 렌더링에 사용될 수 있도록 하는게 베스트
    // Model mode, Texture mode
    template <typename MM, typename TM>
    class Component {
        std::string behaviour;
        std::string name;
        std::string parent;
        // std::vector<std::string> children;
        std::map<std::string, Component> children;
        
        Model<MM> model
        Texture<TM> texture;

        Shader shader;
    };
}

#endif //ENGINE_TYPES_H