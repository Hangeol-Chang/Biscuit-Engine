#ifndef BAKE_BEHAVIOUR_H
#define BAKE_BEHAVIOUR_H

#include <string>
#include <map>

#include "BiscuitEngine.h"

#define DEFINE_BAKEBEHAVIOUR(DerivedClass)                              \
    public:                                                             \
        DerivedClass() {printf("constructor 1\n");};                    \
        ~DerivedClass() {};                                             \
        DerivedClass(const std::string &name) : BakeBehaviour(name) {}  \
            // printf("[%s] constructor\n", name.c_str()); }            \

// Macro to register derived classes
#define REGISTER_BEHAVIOUR(DerivedClass)                                        \
    namespace {                                                                 \
        struct DerivedClass##Registration {                                     \
            DerivedClass##Registration() {                                      \
                BakeBehaviour::RegistBehaviour(#DerivedClass, {                 \
                    []() -> std::shared_ptr<BakeBehaviour> {                    \
                        return std::make_shared<DerivedClass>(#DerivedClass);   \
                    }                                                           \
                });                                                             \
            }                                                                   \
        };                                                                      \
        static DerivedClass##Registration DerivedClass##instance;               \
    }

namespace engine {
    // 유니티의 MonoBehaviour와 비슷한 역할을 하는 클래스
    class BakeBehaviour : public std::enable_shared_from_this<BakeBehaviour> {
    public:
        BakeBehaviour() {};
        virtual ~BakeBehaviour() = default;
        BakeBehaviour(const std::string &name);

        virtual void Awake() {};
        virtual void Start() {};
        virtual void Update();

        // transform function
        // transform function은 호출된 후에 child객체들에 대해서도 호출해줘야 함
        // BakdBehaviour 딴에서  구현해놓고 끝낼 것.
        // BakeBehaviour의 규모가 커짐에 따라, 내부적으로 Transform Struct를 새로 만들어서 그 안으로 옮길수도.
        void Translate();   // parameter 받을거 생각해볼 것.
        void Rotation();    // parameter 받을거 생각해볼 것.
        void Scale();       // parameter 받을거 생각해볼 것.

        void SetComponent(std::shared_ptr<Component> c) { component = c; }

        // static global functions
        // 어떤 behaviour들이 있는지 저장해두는 곳.
        static std::map<std::string, std::function<std::shared_ptr<BakeBehaviour>()>>& GetRegistry();
        static void RegistBehaviour(const std::string& name, std::function<std::shared_ptr<BakeBehaviour>()> creator);
        static std::shared_ptr<BakeBehaviour> CreateInstance(const std::string& name, const std::string& behaviourName);
        static void RegistUpdates();    // 이거 구조 좀 다시 생각해볼 것.

        std::string name;
    protected:
        static std::shared_ptr<BakeBehaviour> FindBehaviour(std::string *name, std::string *behaviourName);
        static std::map<size_t, std::shared_ptr<BakeBehaviour>> behaviours; // hashcode, BakeBehaviour
        std::shared_ptr<Component> component;

        std::vector<std::shared_ptr<BakeBehaviour>> children;   // 
        BakeBehaviour *parent = nullptr;        // 최상의 오브젝트일경우 root 오브젝트를 받아야 함 (카메라 제외)

        bool useUpdate = true;

        /*
            model을 업데이트 하는 코드들을 전부 여기에 넣어두고,
            필요한 놈이 호출하도록 함.
            이 함수들은 무조건 성능 우선으로 제작되어야 함. vertex같은거 사이즈 커지면 로드 커질 수 있음.
        */
        // Transform
        void Translate(const glm::vec3& translation);   // translation 값만큼 이동.
        void SetTransform(const glm::vec3& transform);  // transform 값으로 변경.
        void Rotate(const glm::vec3& rotation);         // rotation 값만큼 회전.
        void SetRotation(const glm::vec3& rotation);    // rotation 값으로 회전.
        void Scale(const glm::vec3& scale);             // scale 값만큼 변경.
        void SetScale(const glm::vec3& scale);          // scale 값으로 변경.

        // Model Static
        void Update3DModel(const std::string& modelFile);

        // Model Dynamic
        void UpdateVertices(const std::vector<glm::vec3>& newVertices);
        void UpdateIndices(const std::vector<uint32_t>& newIndices);
        void UpdateUVs(const std::vector<glm::vec2>& newUVs);

        // Texture Color
        void UpdateColor(const glm::vec3& color);
        
        // Texture Image
        void UpdateImage(const std::string& imageFile);
        
    private:
    };
}

#endif // BAKE_BEHAVIOUR_H 