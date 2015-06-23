#include <iostream>
  
template <class T> void f2(T);
namespace A {
    struct X {
        class Y {
            friend void f2<>(int); // ::f2<>(int) is a friend
            static const int i = -1;
        };
    };
}

template <class T> void f2(T) { std::cout << A::X::Y::i << '\n'; }

int main()
{
    f2(0);
}