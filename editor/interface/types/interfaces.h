#ifndef EDITOR_INTERFACES_H
#define EDITOR_INTERFACES_H

#include <gtkmm.h>
#include <memory>
#include <vector>
#include <string>

/*
    shared_vector를 사용하면서 생기는 고질적인 문제애 대해.
    -> 리소스 반환을 트래킹하지 않기 때문에,
    -> 그냥 한번 생성된 자리가 삭제되도 메모리에 빵구난 채로 냅둠.
    -> 저 메모리를 다시 쓰도록 트래킹 하거나, 다른 방법을 생각해봐야 하.
*/
#define shared_vector(x) std::vector<std::shared_ptr<x>>

namespace editor {

    // 클래스 정의부
    template<typename T>
    class Page;
    template<typename T1, typename T2>
    class PackedPage;

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

    template<typename T1, typename T2>
    class PackedPage {
    public:
        PackedPage() { outerPage.add(innerPage); }
        virtual ~PackedPage() {}

    protected:
        T1 outerPage;
        T2 innerPage;
    };



    // static data module
    /*
        - 뭐에 쓰는 모듈?
            - hirearchy 같은거 여러개 띄워둘 때, 각각의 창에서 데이터를 동기화하기 위함.
            - static하게 데이터를 띄워두고, 각각의 창에서 데이터를 수정하면, 다른 창에서도 동기화되도록 함.
        - 근데 그러면 이거 engine에 들어가는게 맞는거 아님?
    */
    struct DataModule {
        // 일단 미사용.
    };
}

#include "interfaces_impl.h"
#endif // EDITOR_INTERFACES_H