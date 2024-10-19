#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "../types/types.h"
#include <gtkmm.h>
#include <string>

namespace editor {
    class Hierarchy : public AComponent {
    public:
        Hierarchy() : AComponent("hierarchy") {}
        virtual ~Hierarchy() {}

    private:
        
    };
}

#endif // HIERARCHY_H