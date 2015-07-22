#include <iostream>

struct S {
    int foo;
};

struct S2 {
    S2(char);
    
    char foo;  
};

template<typename Ret>
Ret declval();

template<typename T>
auto getSizeOfFoo() {
    return sizeof(declval<T>().foo);   
}

int main() {
    std::cout << "Size of S::foo = " << getSizeOfFoo<S>() << '\n';
    std::cout << "Size of S2::foo = " << getSizeOfFoo<S2>() << '\n';
}