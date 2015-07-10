#include <iostream>

class Base {
public:
    template <typename T>
    static T func () {
        std::cout << (T)3.145 << std::endl;
        return 3.145;
    }
};

class Derived : public Base {
public:
    using derivedFuncType = decltype(&Base::func<int>);
    static constexpr derivedFuncType derivedFunc = &Base::func<int>;
};

int main() {
    Base::func<double>(); // Prints 3.145
    Derived::derivedFunc(); // Prints 3
    return 0;
}
