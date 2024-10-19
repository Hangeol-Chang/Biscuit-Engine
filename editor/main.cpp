#include <gtkmm.h>
#include "BiscuitEditor.h"

// include 됨
#include <BakeBehaviour.h>

using namespace editor;

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.biscuit.editor");
    
    BiscuitEditor editor;
    return app->run(editor);
}