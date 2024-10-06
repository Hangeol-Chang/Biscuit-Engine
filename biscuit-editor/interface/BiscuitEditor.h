#include "./types/types.h"
#include <string>

namespace editor {
    class BiscuitEditor : public Page<Gtk::Grid>, public Gtk::Window {
    public:
        BiscuitEditor();
        ~BiscuitEditor() {};    

    private:
        void SetDefaultPageLayout();    // default layout으로 페이지 꾸밈.
        int MakeNewNotebook();
        template<typename T>
        int MakeNewComponent();

        shared_vector(Gtk::Notebook) notebooks;
        shared_vector(AComponent) components;
        
        Gtk::Button button;
    };
}