#include "interfaces.h"
#include <memory>

namespace editor {
    template<typename T>
    template<typename T2>
    int Page<T>::MakeWidget() {
        int index = widgets.size();
        widgets.push_back(std::make_shared<T2>());
        return index;
    }
    template<typename T>
    int Page<T>::MakeButton(std::string lab) {       
        int index = MakeWidget<Gtk::Button>();
        GetWidget<Gtk::Button>(index)->set_label(lab);
        return index;
    }
    template<typename T>
    int Page<T>::MakeLabel(std::string lab) {
        int index = MakeWidget<Gtk::Label>();
        GetWidget<Gtk::Label>(index)->set_text(lab);
        return index;
    }
    template<typename T>
    int Page<T>::MakeEntry(std::string lab) {
        int index = MakeWidget<Gtk::Entry>();
        GetWidget<Gtk::Entry>(index)->set_text(lab);
        return index;
    }
}