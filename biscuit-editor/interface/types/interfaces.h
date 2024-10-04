#ifndef EDITOR_INTERFACES_H
#define EDITOR_INTERFACES_H

#include <gtkmm.h>
#include <memory>
#include <vector>
#include <string>

#define shared_vector(x) std::vector<std::shared_ptr<x>>

namespace editor {

    template<typename T>
    class Page {
    public:
        T GetPage() { return page; }
    protected:
        template <typename P>
        std::shared_ptr<P> GetWidget(int index) { 
            return std::dynamic_pointer_cast<P>(widgets[index]);
        }
        T page;
        shared_vector(Gtk::Widget) widgets;

        template<typename T2>
        int MakeWidget();

        int MakeButton(std::string lab);
        int MakeLabel(std::string lab);
        int MakeEntry(std::string lab);
    };
}

#include "interfaces_impl.h"
#endif // EDITOR_INTERFACES_H