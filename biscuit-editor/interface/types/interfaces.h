#include <gtk/gtk.h>
#include <memory>
#include <vector>
#include <string>

#define shared_vector(x) std::vector<std::shared_ptr<x>>

namespace editor {

    template<typename T>
    class Page {
    public:
        std::shared_ptr<T> GetPage() {
            return page;
        }
    protected:
        std::shared_ptr<T> page;
        shared_vector(GtkWidget) widgets;

        template<typename T2>
        int MakeWidget();

        int MakeButton(std::string lab);
        int MakeLabel(std::string lab);
        int MakeEntry(std::string lab);
    };
}