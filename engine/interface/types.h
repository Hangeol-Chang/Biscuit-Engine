// engine에서 사용될 types들
#include <string>

namespace engine {
    struct Vec2 {
        float x;
        float y;
    };
    struct Vec3 {
        float x;
        float y;
        float z;
    };

    typedef struct TextureInfo_ {
        std::string name;
        std::string path;
    } TextureInfo;

    // 하나의 GUI 요소
    struct Crump {

    }
}