#ifndef EDITOR_TYPES_H
#define EDITOR_TYPES_H

#include "interfaces.h"

namespace editor {

    class AComponent : public Page<Gtk::FlowBox> {
    public:
        AComponent() : name("none") {}
        AComponent(std::string name) : name(name) {}
        virtual ~AComponent() {}

        // notebook에 이 객체를 등록할 때 사용.
        void RegistParent(Gtk::Notebook *parent) {
            parent->append_page(this->page, name);
        }
    
    protected:
        std::string name = "this_text_is_bug";

    private:

    };

    class NoteBook : public Page<Gtk::Notebook> {
    public:
        NoteBook() {
            page.set_scrollable();
        }
        virtual ~NoteBook() {}
        
        void AddPage(Gtk::Widget *widget, std::string label) {
            page.append_page(*widget, label);
        }

    private:
        
    };
}

#endif // EDITOR_TYPES_H