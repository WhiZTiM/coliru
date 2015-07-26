#include <vector>
#include <iostream>
using std::cout;
using std::endl;


namespace foo{
    void add(){}

    struct base{};

    void addm(const base& x){}

}

namespace bar{
    template <typename T>
    struct child : public T{
        void func(){
            add();
            addm(*this);
        }
    };
}

int main(){

    bar::child<foo::base>().func();

}
