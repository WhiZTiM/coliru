#include <boost/phoenix.hpp>
#include <iostream>

using namespace boost;
using namespace phoenix;
using namespace arg_names;
using namespace local_names;

class A {
  public:
    A(int a) : mA(a){};
    int GetX() const { return mA; };

  protected:
    int mA;
};

class B : public A {
  public:
    B(int a) : A(a){};
    int GetX() const { return mA + 1; }
};

int main(void)
{
    const A* a = new A(3);
    const A* b = new B(2);
    BOOST_AUTO(test, (_1->*&A::GetX)() + (static_cast_<const B*>(_2)->*&B::GetX)());

    std::cout << test(a, b) << std::endl;
    delete a;
    delete b;
    return 0;
}
