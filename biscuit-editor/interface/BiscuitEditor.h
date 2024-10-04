#include "interfaces.h"
#include "types.h"
#include <string>

namespace editor {
    class BiscuitEditor : public Page<Gtk::Grid>, public Gtk::Window {
    public:
        BiscuitEditor();
        ~BiscuitEditor() {};    

    private:

    Gtk::Button button;
    };
}