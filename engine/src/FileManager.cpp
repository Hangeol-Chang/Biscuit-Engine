#include "FileManager.h"

#include <iostream>
#include <fstream>
#include <json/json.h>

namespace engine {
    FileManager::FileManager() {
    }
    FileManager::~FileManager() {
    }

    Json::Value FileManager::ReadJsonFile(const std::string& fileName) {
        Json::Value root;
        std::ifstream file(fileName);
        file >> root;
        return root;
    }
    void FileManager::WriteJsonFile(const std::string& fileName) {
        std::ofstream file(fileName);
        // file << root;
    }

    std::shared_ptr<Component<ModelData_Dynamic, TextureData_Color>> FileManager::ReadComponent(const std::string& fileName) {
        Json::Value root = ReadJsonFile(fileName);
        printf("[DEBUG] read component\n");
        std::shared_ptr<Component<ModelData_Dynamic, TextureData_Color>> component = std::make_shared<Component<ModelData_Dynamic, TextureData_Color>>();

        // 여기서 해체하면 됨.
        // component->Deserialize(root);
        return nullptr;
    }
}