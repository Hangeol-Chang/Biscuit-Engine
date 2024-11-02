#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <json/json.h>
#include <iostream>
#include <memory>
#include "engineTypes.h"
#include "GUIBuilder.h"

namespace engine {

    class FileManager {
    public:
        FileManager();
        ~FileManager();

        Json::Value ReadJsonFile(const std::string& fileName);
        AppParameter ReadAppParameter(const std::string& fileName);

        void WriteJsonFile(const std::string& fileName);
    
        // read Components
        std::shared_ptr<Component> ReadComponent(const std::string& fileName);
    private:
        GUIBuilder builder;

    };

}

#endif // FILEMANAGER_H