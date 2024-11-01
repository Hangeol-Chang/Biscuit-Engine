#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <json/json.h>
#include <iostream>
#include <memory>
#include "engineTypes.h"

namespace engine {
    
    // 일단 파일매니저 안에 만들지만, 스케일이 커지면 분리해야 할 수도 있음.
    class ComponentParser {
    public:
        ComponentParser();
        ~ComponentParser();
        std::shared_ptr<Component> LoadComponents(Json::Value& root);

    private:
        std::shared_ptr<Component> ParseComponent(const Json::Value& compJson);
    };

    class FileManager {
    public:
        FileManager();
        ~FileManager();

        Json::Value ReadJsonFile(const std::string& fileName);
        void WriteJsonFile(const std::string& fileName);
    
        // read Components
        std::shared_ptr<Component> ReadComponent(const std::string& fileName);
    private:
        ComponentParser parser;

    };

}

#endif // FILEMANAGER_H