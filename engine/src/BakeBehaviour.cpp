#include "../interface/BakeBehaviour.h"
#include "../common/StringHelper.h"

namespace engine {
    // static variables init
    std::map<size_t, std::shared_ptr<BakeBehaviour>> BakeBehaviour::behaviours;

    // static functions
    std::shared_ptr<BakeBehaviour> BakeBehaviour::FindBehaviour(std::string *name) {
        auto b = behaviours.find(hashStr(*name));
        if(b != behaviours.end()) { return b->second; }
        return nullptr;
    }

    // basic bake logic
    BakeBehaviour::BakeBehaviour(const std::string &name) {
        this->name = name;
    }
    
    void BakeBehaviour::Update() { useUpdate = false; }

    // regist 관련 함수들
    std::map<std::string, std::function<std::shared_ptr<BakeBehaviour>()>>& BakeBehaviour::GetRegistry() {
        static std::map<std::string, std::function<std::shared_ptr<BakeBehaviour>()>> registry;
        return registry;
    }
    void BakeBehaviour::RegistBehaviour(const std::string& name, std::function<std::shared_ptr<BakeBehaviour>()> creator) {
        GetRegistry()[name] = creator;
    }
    std::shared_ptr<BakeBehaviour> BakeBehaviour::CreateInstance(const std::string& name) {
        auto it = GetRegistry().find(name);
        printf("size of registry %d\n", GetRegistry().size());

        if (it != GetRegistry().end()) { 
            printf("find behaviour %s\n", name.c_str());
            auto instance = it->second();
            behaviours.insert({hashStr(name), instance});
            return instance; 
        }
        printf("not found behaviour %s\n", name.c_str());
        return nullptr;
    }

    void BakeBehaviour::RegistUpdates() {
        for(auto& b : behaviours) {
            try {
                b.second->Update();         // update 한 번 걸어보고, 
                if(b.second->useUpdate) {   // BakeBehaviour의 Update가 불리지 않으면 등록.
                    BiscuitEngine::GetInstance().AddUpdate( [b]() { b.second->Update(); } );
                }
            }
            catch(const std::exception& e) {
                printf("[Engine][BUG] error occured trying to regist update\n -- message -- \n");
                printf("%s\n", e.what());
            }
        }
    }


    // Update functions //  ** 검증 필요 **
    void BakeBehaviour::Translate(const glm::vec3& translation) {
        component->model->position += translation;
    }
    void BakeBehaviour::SetTransform(const glm::vec3& transform) {
        component->model->position = transform;
    }
    void BakeBehaviour::Rotate(const glm::vec3& rotation) {
        component->model->rotation += rotation;
    }
    void BakeBehaviour::SetRotation(const glm::vec3& rotation) {
        component->model->rotation = rotation;
    }
    void BakeBehaviour::Scale(const glm::vec3& scale) {
        component->model->scale *= scale;
    }
    void BakeBehaviour::SetScale(const glm::vec3& scale) {
        component->model->scale = scale;
    }


    // Model Static
    void BakeBehaviour::Update3DModel(const std::string& modelFile) {
        // 1. 파일 교체.
        auto modelStatic = std::dynamic_pointer_cast<ModelData_Static>(component->model);
        if (modelStatic) {
            modelStatic->modelFile = modelFile;
        } else {
            printf("[%s][Error] IModel is not of type ModelData_Static\n", name.c_str());
        }

        // 2. 메모리에 다시 로드. -> Vulkan 쪽에 다이나믹 로드 만들어져야 사용 가능.
        // model->LoadModel(modelFile);
    }

    // Model Dynamic
    void BakeBehaviour::UpdateVertices(const std::vector<glm::vec3>& newVertices) {
        auto dynamicModel = std::dynamic_pointer_cast<ModelData_Dynamic>(component->model);
        if (dynamicModel) {
            if (dynamicModel->vertices.size() != newVertices.size()) {
                dynamicModel->vertices.resize(newVertices.size());
            }

            std::memcpy(dynamicModel->vertices.data(), newVertices.data(), sizeof(glm::vec3) * newVertices.size());
        } else {
            printf("[%s][Error] IModel is not of type ModelData_Dynamic\n", name.c_str());
        }
    }
    void BakeBehaviour::UpdateIndices(const std::vector<uint32_t>& newIndices) {
        auto dynamicModel = std::dynamic_pointer_cast<ModelData_Dynamic>(component->model);
        if (dynamicModel) {
            if (dynamicModel->indices.size() != newIndices.size()) {
                dynamicModel->indices.resize(newIndices.size());
            }

            std::memcpy(dynamicModel->indices.data(), newIndices.data(), sizeof(uint32_t) * newIndices.size());
        } else {
            printf("[%s][Error] IModel is not of type ModelData_Dynamic\n", name.c_str());
        }
    }
    void BakeBehaviour::UpdateUVs(const std::vector<glm::vec2>& newUVs) {
        auto dynamicModel = std::dynamic_pointer_cast<ModelData_Dynamic>(component->model);
        if (dynamicModel) {
            if (dynamicModel->uvs.size() != newUVs.size()) {
                dynamicModel->uvs.resize(newUVs.size());
            }

            std::memcpy(dynamicModel->uvs.data(), newUVs.data(), sizeof(glm::vec2) * newUVs.size());
        } else {
            printf("[%s][Error] IModel is not of type ModelData_Dynamic\n", name.c_str());
        }
    }

    // Texture Color
    void BakeBehaviour::UpdateColor(const glm::vec3& color) {
        auto textureColor = std::dynamic_pointer_cast<TextureData_Color>(component->texture);
        if (textureColor) {
            textureColor->color = color;
        } else {
            printf("[%s][Error] ITexture is not of type TextureData_Color\n", name.c_str());
        }
    }
    
    // Texture Image
    void BakeBehaviour::UpdateImage(const std::string& imageFile) {
        // 1. 파일 교체.
        auto textureImage = std::dynamic_pointer_cast<TextureData_Image>(component->texture);
        if (textureImage) {
            textureImage->imageFile = imageFile;
        } else {
            printf("[%s][Error] ITexture is not of type TextureData_Image\n", name.c_str());
        }

        // 2. 메모리에 다시 로드.
        // model->LoadModel(modelFile);
    }
}