#include <iostream>

template <typename T>
class A
{
private:
    T mValue;
public:
    template<typename U=T>
    auto operator +=(const U &rhs)
        -> decltype(mValue += rhs)
    {
        mValue += rhs;
        return mValue;
    }
};


int main()
{
    A<int> a;
    a += 8; //+= will forward to the += for the int

    struct Test {  /*no operators defined*/ };
    A<Test> b;
//    b += Test{};
}