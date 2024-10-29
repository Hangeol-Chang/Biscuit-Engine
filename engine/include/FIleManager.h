#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <json/json.h>
#include <iostream>
#include <memory>
#include "types.h"

namespace engine {
    // forward declaration
    struct ModelData_Dynamic;
    struct TextureData_Color;
    template <typename MM, typename TM>
    class Component;

    class FileManager {
    public:
        FileManager();
        ~FileManager();

        Json::Value ReadJsonFile(const std::string& fileName);
        void WriteJsonFile(const std::string& fileName);
    
        // read Components
        std::shared_ptr<Component<ModelData_Dynamic, TextureData_Color>> ReadComponent(const std::string& fileName);
        
    private:

    };
}

#endif // FILEMANAGER_H