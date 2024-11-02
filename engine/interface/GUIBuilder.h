#ifndef GUI_BUILDER_H
#define GUI_BUILDER_H

#include <json/json.h>
#include "engineTypes.h"

namespace engine {
    class GUIBuilder {
    public:
        GUIBuilder();
        ~GUIBuilder();

        std::shared_ptr<Component>  LoadComponents(Json::Value& root);
        AppParameter                LoadAppParameter(Json::Value& root);

    private:
        std::shared_ptr<Component> ParseComponent(const Json::Value& compJson);
    };
}

#endif // GUI_BUILDER_H