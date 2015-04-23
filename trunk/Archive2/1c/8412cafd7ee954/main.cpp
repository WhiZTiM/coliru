#include <iostream>


#define CREATE_WITH_GETTER_AND_SETTER(memberType, memberName) \
    private:                                                  \
        memberType _##memberName;                             \
    public:                                                   \
        CREATE_SETTER(_##memberName)                          \
        CREATE_GETTER(_##memberName)

#define CREATE_SETTER(memberName)      \
template<typename T>                   \
void set##memberName(T&& aux)          \
{                                      \
    memberName = std::forward<T>(aux); \
}

#define CREATE_GETTER(memberName)                           \
auto get##memberName() const -> decltype(memberName) const& \
{                                                           \
    return memberName;                                      \
}


struct Foo
{
    int x;
    int y;
};


class Class
{
    CREATE_WITH_GETTER_AND_SETTER(int, x)
    CREATE_WITH_GETTER_AND_SETTER(Foo, foo)
};


int main()
{
    Class c;
    c.set_x(10);
    const int& x = c.get_x();
    std::cout << x << std::endl;
    
    Foo f = {5,6};
    c.set_foo(f);
    //c.set_foo({5,5}); //does not work!!!!!!
    
    const Foo& f2 = c.get_foo();
    std::cout << f2.x << " " << f2.y << std::endl;
}
