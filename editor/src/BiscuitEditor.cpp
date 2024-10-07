#include "BiscuitEditor.h"
#include "components/Hierarchy.h"


namespace editor {
    BiscuitEditor::BiscuitEditor() {
        // init app
        set_title("Biscuit Editor");
        set_default_size(720, 960);
        add(page);

        // make layout
        SetDefaultPageLayout();

        show_all_children();
    }

    void BiscuitEditor::SetDefaultPageLayout() {
        printf("[EDITOR] make default layout\n");

        // notebook
        int hirerchyNotebookIndex = MakeNewNotebook();
        notebooks[hirerchyNotebookIndex]->set_scrollable();
        page.attach(*notebooks[hirerchyNotebookIndex], 0, 0, 1, 1);

        int hierarchyIndex = MakeNewComponent<Hierarchy>();
        components[hierarchyIndex]->RegistParent(notebooks[hirerchyNotebookIndex].get());
    }


    /*-- common functions --*/
    int BiscuitEditor::MakeNewNotebook() {
        int index = notebooks.size();
        notebooks.push_back(std::make_shared<Gtk::Notebook>());
        return index;
    }
    template<typename T>
    int BiscuitEditor::MakeNewComponent() {
        // 추후 빈 index를 찾는 로직으로 변경.
        int index = components.size();
        components.push_back(std::make_shared<T>());
        return index;
    }
}