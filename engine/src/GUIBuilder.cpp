#include "../interface/GUIBuilder.h"
#include "BakeBehaviour.h"

namespace engine {    
    GUIBuilder::GUIBuilder() {}
    GUIBuilder::~GUIBuilder() {}

    std::shared_ptr<Component> GUIBuilder::LoadComponents(Json::Value& root) {
        auto rootComponent = std::make_shared<Component>("root");
        rootComponent->behaviourName = "-";

        std::shared_ptr<ModelData_Static> rootModel = std::make_shared<ModelData_Static>();
        rootModel->modelFile = "-"; // Root 모델 파일 설정
        rootComponent->SetModel(rootModel);

        std::shared_ptr<TextureData_Color> rootTexture = std::make_shared<TextureData_Color>();
        rootTexture->color = glm::vec3(1.0f, 1.0f, 1.0f); // 흰색 루트 텍스처
        rootComponent->SetTexture(rootTexture);

        rootComponent->SetModel(rootModel);
        rootComponent->SetTexture(rootTexture);

        std::shared_ptr<Shader> rootShader = std::make_shared<Shader>();
        rootShader->vertexShader = "-";
        rootShader->fragmentShader = "-";
        rootComponent->SetShader(rootShader);

        // 각 컴포넌트를 루트 컴포넌트의 자식으로 추가
        for (const auto& componentData : root["components"]) {
            printf("Component name: %s\n", componentData["name"].asCString());
            auto component = ParseComponent(componentData);
            rootComponent->children[component->GetName()] = component;
        }

        return rootComponent;
    }
    AppParameter GUIBuilder::LoadAppParameter(Json::Value& root) {
        AppParameter appParameter = AppParameter();

        appParameter.title = root["application"]["title"].asString();
        appParameter.windowSize = std::make_pair(
            root["application"]["width"].asUInt(),
            root["application"]["height"].asUInt()
        );
        appParameter.fullScreen = root["application"]["fullScreen"].asBool();
        appParameter.vulkanValidation = root["vulkan"]["validation"].asBool();
        appParameter.vulkanDebug = root["vulkan"]["debug"].asBool();
        
        appParameter.resizeable = root["application"]["resizeable"].asBool();

        return appParameter;
    }

    std::shared_ptr<Component> GUIBuilder::ParseComponent(const Json::Value& componentData) {
        // 컴포넌트 이름과 행동 설정
        auto component = std::make_shared<Component>(componentData["name"].asString());
        component->behaviourName = componentData["behaviour"].asString();
        component->behaviour = BakeBehaviour::CreateInstance(component->behaviourName);
        if(component->behaviour != nullptr) {
            component->behaviour->SetComponent(component);
        }
        printf("Component name: %s, Behaviour: %s\n", component->GetName().c_str(), component->behaviourName.c_str());

        // 모델 설정
        std::shared_ptr<IModel> model = nullptr;
        std::string modelMode = componentData["model"]["mode"].asString();
        // 동적 모델의 경우 데이터 읽기
        if (modelMode == "dynamic") {
            model = std::make_shared<ModelData_Dynamic>();
            std::shared_ptr<ModelData_Dynamic> dynamicModel = std::static_pointer_cast<ModelData_Dynamic>(model);
            
            const auto& data = componentData["model"]["data"];
            for (const auto& vertex : data["vertices"]) {
                dynamicModel->vertices.emplace_back(
                    vertex[0].asFloat(),
                    vertex[1].asFloat(),
                    vertex[2].asFloat()
                );
            }

            for (const auto& index : data["indices"]) {
                dynamicModel->indices.push_back(index.asUInt());
            }
            for (const auto& uv : data["uvs"]) {
                dynamicModel->uvs.emplace_back(
                    uv[0].asFloat(),
                    uv[1].asFloat()
                );
            }
        } 
        // 정적 모델의 경우 파일 이름 설정
        else if (modelMode == "static") {
            model = std::make_shared<ModelData_Static>();
            std::shared_ptr<ModelData_Static> staticModel = std::static_pointer_cast<ModelData_Static>(model);
            staticModel->modelFile = componentData["model"]["data"]["modelFile"].asString();
        }

        model->mode = modelMode;
        model->position = glm::vec3(
            componentData["model"]["position"][0].asFloat(),
            componentData["model"]["position"][1].asFloat(),
            componentData["model"]["position"][2].asFloat()
        );
        model->rotation = glm::vec3(
            componentData["model"]["rotation"][0].asFloat(),
            componentData["model"]["rotation"][1].asFloat(),
            componentData["model"]["rotation"][2].asFloat()
        );
        model->scale = glm::vec3(
            componentData["model"]["scale"][0].asFloat(),
            componentData["model"]["scale"][1].asFloat(),
            componentData["model"]["scale"][2].asFloat()
        );
        component->SetModel(model);

        // 텍스처 설정
        std::shared_ptr<ITexture> texture = nullptr;
        std::string texMode = componentData["texture"]["mode"].asString();
        if (texMode == "color") {
            texture = std::make_shared<TextureData_Color>();
            std::shared_ptr<TextureData_Color> colorTexture = std::static_pointer_cast<TextureData_Color>(texture);
            const auto& colorData = componentData["texture"]["data"]["color"];
            colorTexture->color = glm::vec3(
                colorData[0].asFloat(),
                colorData[1].asFloat(),
                colorData[2].asFloat()
            );
            texture = colorTexture;

        } else if (texMode == "image") {
            texture = std::make_shared<TextureData_Image>();
            std::shared_ptr<TextureData_Image> imageTexture = std::static_pointer_cast<TextureData_Image>(texture);
            imageTexture->imageFile = componentData["texture"]["data"]["path"].asString();
        }
        texture->mode = texMode;
        component->SetTexture(texture);

        std::shared_ptr<Shader> shader = std::make_shared<Shader>();
        shader->vertexShader   = componentData["shader"]["vertex"].asString();
        shader->fragmentShader = componentData["shader"]["fragment"].asString();
        component->SetShader(shader);

        // 자식 컴포넌트 파싱
        for (const auto& child : componentData["childrenComponents"]) {
            auto childComponent = ParseComponent(child);
            component->children[childComponent->GetName()] = childComponent; // 자식 추가
        }

        return component;
    }
}