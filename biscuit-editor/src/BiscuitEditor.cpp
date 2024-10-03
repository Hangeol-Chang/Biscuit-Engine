#include "BiscuitEditor.h"

namespace editor {

    BiscuitEditor::BiscuitEditor() {
        int testBt = MakeButton("Test Button");
        gtk_grid_attach(page.get(), widgets[testBt].get(), 0, 0, 1, 1);
    }
}