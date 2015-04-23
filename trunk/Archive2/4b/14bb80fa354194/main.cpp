#include <iostream>


#define CREATE_WITH_GETTER_AND_SETTER(memberType, memberName) \
    memberType _##memberName;                                 \
    CREATE_SETTER(_##memberName)                              \
    CREATE_GETTER(_##memberName)

#define CREATE_SETTER(memberName) \
template<typename T>              \
void set##memberName(T&& aux)     \
{                                 \
    memberName = aux;             \
}

#define CREATE_GETTER(memberName)                     \
auto get##memberName() -> decltype(memberName) const& \
{                                                     \
    return memberName;                                \
}


struct Foo
{
    int x;
    int y;
};


CREATE_WITH_GETTER_AND_SETTER(int, x)
CREATE_WITH_GETTER_AND_SETTER(Foo, foo)


int main()
{
    set_x(10);
    const int& x = get_x();
    std::cout << x << std::endl;
    
    Foo f = {5,6};
    set_foo(f);
    //set_foo({5,5}); //does not work!!!!!!
    
    const Foo& f2 = get_foo();
    std::cout << f2.x << " " << f2.y << std::endl;
}
