/*
    editor 쪽에서는 변경사항을 json, xml로 저장하고,
    gui 쪽으로는 정제된 데이터를 보내주는 역할.
    
    이거 지금 ComponentParser가 하고있는데, 여기에 병합해야 함.

*/
#ifndef GUI_BUILDER_H
#define GUI_BUILDER_H

#include "types.h"

namespace engine {
    class GUIBuilder {
    public:
        GUIBuilder();
        ~GUIBuilder();

        bool BuildGUI();
        

    private:

    };
}

#endif // GUI_BUILDER_H