#include <iostream>

template <typename T>
class A
{
private:
    T mValue;
public:
//    #if hasOperator(T, +=)
    template<typename U=T>
    auto operator +=(const U &rhs)
        -> decltype(mValue += rhs)
    {
        mValue += rhs;
        return mValue;
    }
//    #endif
};

#include <initializer_list>

struct foo{};
struct Test 
{ 
    Test() = default;
    Test(int, long, double) {}
    Test(std::initializer_list<foo>) {}
    Test& operator+=(const Test&) { return *this; }
};

int main()
{
    A<int> a;
    a += 8; //+= will forward to the += for the int

    A<Test> b; //+= is not implemented since Test does not implement +=
    b += {10, 20, 30.0};
    b += {foo{}, foo{}};
}
