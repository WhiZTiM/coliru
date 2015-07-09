#include <iostream>

using namespace std;

template <typename Derived>
struct CRTP
{
    CRTP(const char*) {}
};

struct B
{
  B(int) {}
};

struct A : B
{
  using B::B;
};

template <template <typename> class Base>
struct X : Base<int>
{
  using Base<int>::Base;
};

struct Y : CRTP<Y>
{
  using CRTP<Y>::CRTP;
};

int main() {
    B b(3);
    A a(2);
    X<CRTP> x("abc");
    Y y("def");
    
    cout << "OK" << "\n";

	return 0;
}