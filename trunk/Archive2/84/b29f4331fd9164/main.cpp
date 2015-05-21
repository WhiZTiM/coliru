#include <iostream>
#include <vector>

template<class T>
class Container {
    template<class T1> friend class Accessor;
    //friend typename T::MyAccessor;
    std::vector<T> _data;
};

template<class T>
class Accessor {
public:
    void doSomething(Container<T> *c) {
        std::cout << c->_data.size() << std::endl;
    }
};

template<class T, template<typename> class CustomAccessor = Accessor>
struct MyBase {
    typedef Container<T> MyContainer;
    typedef CustomAccessor<T> MyAccessor;
};

template<class T, template<typename> class First = Accessor, template<typename> class Second = Accessor>
class Composite {
public:
    typedef First<T> MyFirst;
    typedef Second<T> MySecond;

    void doSomething(Container<T> *c) {
        MyFirst a;
        a.doSomething(c);

        MySecond b;
        b.doSomething(c);
    }
};

template<class T>
class DoubleAccessor : public Composite<T> {
    
};

int main() {
    Container<MyBase<int>> c;
    Composite<MyBase<int>> comp;
    comp.doSomething(&c);
}