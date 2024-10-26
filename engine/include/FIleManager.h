// input, output 처리하는 클래스.

#include <json/json.h>

namespace engine {
    class FileManager {
    public:
        FileManager();
        ~FileManager();

        Json::Value ReadJsonFile(const std::string& fileName);
        void WriteJsonFile(const std::string& fileName);
    
    private:
        Json::Value root;
    };
}