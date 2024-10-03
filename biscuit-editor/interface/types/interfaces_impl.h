#include "interfaces.h"
#include <memory>

namespace editor {
    template<typename T>
    template<typename T2>
    int Page<T>::MakeWidget() {
        int index = widgets.size();

        std::shared_ptr<T2> widget;
        widgets.push_back(std::static_pointer_cast<GtkWidget>(widget));

        return index;
    }
    template<typename T>
    int Page<T>::MakeButton(std::string lab) {       
        int index = MakeWidget<GtkButton>();
        GtkButton *wg = GTK_BUTTON(widgets[index].get());
        gtk_button_set_label(wg, lab.c_str());

        return index;
    }
    template<typename T>
    int Page<T>::MakeLabel(std::string lab) {
        int index = MakeWidget<GtkLabel>();
        GtkLabel *wg = GTK_LABEL(widgets[index].get());
        gtk_label_set_text(wg, lab.c_str());

        return index;
    }
    template<typename T>
    int Page<T>::MakeEntry(std::string lab) {
        std::shared_ptr<GtkWidget> entry(GTK_WIDGET(gtk_entry_new()), g_object_unref);
        gtk_entry_set_text(GTK_ENTRY(entry.get()), lab.c_str());
        widgets.push_back(entry);  // 벡터에 추가
        return 0;
    }
}