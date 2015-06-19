template <typename T>
struct has_foo_member_function
{
    typedef char yes[1];
    typedef char no[2];
    
    template <typename U, void(U::*)()>
    struct SFINAE {};
    
    template <typename U>
    static yes& test(SFINAE<U, &U::foo>*);
        
    template <typename U>
    static no& test(...);
    
    static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

struct A
{
    void foo() {}
};

struct B
{
};

#include <iostream>
int main()
{
    std::cout << has_foo_member_function<A>::value << std::endl;
    std::cout << has_foo_member_function<B>::value << std::endl;
}
