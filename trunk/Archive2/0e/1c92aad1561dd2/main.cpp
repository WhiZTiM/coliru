#include <iostream>
#include <functional>

class X
{
    int _x;
public:
    X(int x): _x {x} {}
    int &get()
    {
        std::cout << "non-const" << std::endl;
        return _x;
    }
    const int &get() const
    {
        std::cout << "const" << std::endl;
        return _x;
    }
};

int main(void)
{
    X x {10};
    auto mfn = std::mem_fn<int&()>(&X::get); // pick up the non-const version
    mfn(x);

    const X cx {100};
    // compiling error picking up the const version
    // auto cmfn = std::mem_fn(&X::get); // error
    auto cmfn = std::mem_fn<const int& () const>(&X::get); // was using return value type of int& instead of const int&
    // int& iFooMutable = cmfn(cx); // error, can't convert const int to int&
    const int& iFoo = cmfn(cx);
    std::cout << "iFoo = " << iFoo << std::endl;
}

