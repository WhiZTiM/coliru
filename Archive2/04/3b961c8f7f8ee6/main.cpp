#include <iostream>
#include <vector>

#define CREATE_WITH_GETTER_AND_SETTER(memberType, memberName) \
    public:                                                   \
        CREATE_SETTER(_##memberName)                          \

#define CREATE_SETTER(memberName)      \
template<typename T>                   \
void set##memberName(T&& aux)          \
{                                      \
    memberName = std::forward<T>(aux); \
}\
template<typename T>    \
void set##memberName(std::initializer_list<T>&& aux)\
{\
        memberName = std::forward<std::initializer_list<T>>(aux); \
}

#define CREATE_GETTER_CONST(name, memberName)                           \
auto name() const -> decltype(memberName) const& \
{                                                           \
    return memberName;                                      \
}

#define CREATE_GETTER(name, memberName)                           \
auto name() -> decltype(memberName) & \
{                                                           \
    return memberName;                                      \
}

#define CREATE_GETTER_TEST(type, name, memberName)                           \
type get##name() const \
{                                                           \
    return memberName;                                      \
}





class Class
{
public:
    std::vector<int> foo;
    int test;
    CREATE_SETTER(foo)
    CREATE_SETTER(test)
};


int main()
{
    Class c;
    int i = 7;
    c.setfoo({i,i}); //does not work!!!!!!
    c.settest(i);
}
