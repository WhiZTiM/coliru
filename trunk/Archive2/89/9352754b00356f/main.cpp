#include <iostream>
#include <string>
#include <vector>

struct MyObj
{
    void f(int n) { std::cout <<"hi " << n << "\n"; }
};

template <typename Class, typename PFunc>
struct Adapter
{
    Adapter(Class& object, PFunc pFunc, int n) : object_(object), pFunc_(pFunc), n_(n) { }

    void f() { (object_.*pFunc_)(n_); }
    
    Class& object_;
    PFunc pFunc_;
    int n_;
};

int main()
{
    MyObj myObj;
    
    Adapter<MyObj, void(MyObj::*)(int)> adapter(myObj, &MyObj::f, 43);
    adapter.f();
}
