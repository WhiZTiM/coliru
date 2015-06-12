#include <iostream>
#include <memory>

class A {
  public:
    A() { std::cout << "A()" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }
    A(const A&) { std::cout << "A(A&)" << std::endl; }
    A& operator=(const A&) { std::cout << "A=" << std::endl; return *this; }
};

class B {
    A a;

  public:
    A* theA() { return &a; }
};

template <typename T1, typename T2>
class MagicD {
    std::unique_ptr<T1> t1up;

  public:
    MagicD(T1* t1) : t1up(t1) {}
    MagicD(const MagicD&) {}
    ~MagicD() {}

    void operator()(T2* t2) {}

    operator T1*() {
        return t1up.release();
    }
};

int main()
{
    std::unique_ptr<B> b(new B());
    std::unique_ptr<A, MagicD<B, A>> a(b->theA(), MagicD<B, A>(b.release()));
}  
