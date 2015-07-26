#include <vector>
#include <iostream>
using std::cout;
using std::endl;


namespace foo{
    void add(){}

    struct base{};

    void addm(const base& x){}

    template <int a>
    void addt(const base& x){}

}

namespace bar{
    template <typename T>
    struct child : public T{
        void func(){
            add();
            addm(*this);
            addt<0>(*this);
        }
    };
}

int main(){

    bar::child<foo::base>().func();

}
