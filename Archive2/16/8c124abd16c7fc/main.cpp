 #include <iostream>
    
    struct A { int x; constexpr A(int i) noexcept : x{i} {} };
    struct B { const A& a; constexpr B(const A& a) noexcept : a{a} {} };
    
    constexpr int foo() { 
        constexpr A a{55};
        constexpr B b{a};
        return b.a.x;
    }
    
    int main() {
        constexpr auto b = foo();
        std::cout << b << std::endl;
    }