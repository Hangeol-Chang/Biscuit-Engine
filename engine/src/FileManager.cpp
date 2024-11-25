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
    void FileManager::WriteJsonFile(const std::string& fileName, Json::Value& root) {
        std::ofstream file(fileName);
        // file << root;
    }
}