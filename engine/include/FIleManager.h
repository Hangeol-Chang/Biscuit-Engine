#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <json/json.h>
#include <iostream>
#include <memory>
#include "engineTypes.h"

namespace engine {

    class FileManager {
    public:
        FileManager();
        ~FileManager();

        Json::Value ReadJsonFile(const std::string& fileName);
        void WriteJsonFile(const std::string& fileName, Json::Value& root);
    private:

    };

}

#endif // FILEMANAGER_H