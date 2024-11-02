#include "FileManager.h"

#include <iostream>
#include <fstream>
#include <json/json.h>
#include "engineTypes.h"

namespace engine {
    FileManager::FileManager() {}
    FileManager::~FileManager() {}

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

    std::shared_ptr<Component> FileManager::ReadComponent(const std::string& fileName) {
        Json::Value root = ReadJsonFile(fileName);
        printf("[DEBUG] read component\n");
        auto component = builder.LoadComponents(root);

        printf("---------- loaded Component info ----------\n");
        component->Print();
        printf("-------------------------------------------\n");

        // 여기서 해체하면 됨.
        // component->Deserialize(root);
        return nullptr;
    }

    AppParameter FileManager::ReadAppParameter(const std::string& fileName) {
        Json::Value root = ReadJsonFile(fileName);
        printf("[DEBUG] read app parameter\n");
        auto appParameter = builder.LoadAppParameter(root);

        appParameter.Print();
        return appParameter;
    }
}