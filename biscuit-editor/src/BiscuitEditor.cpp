#include "BiscuitEditor.h"

namespace editor {
    BiscuitEditor::BiscuitEditor() {
        // init app
        set_title("Biscuit Editor");
        set_default_size(960, 720);

        int testBt = MakeButton("Test Button");
        page.attach(*widgets[testBt], 0, 0, 1, 1);

        add(page);

        show_all_children();
    }
}