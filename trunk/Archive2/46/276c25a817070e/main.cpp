#include <iostream>
#include <memory>

class A {};

class B {
    A a;

  public:
    A* theA() { return &a; }
};

template <typename T1, typename T2>
class MagicD {
    T1 *t1p;

  public:
    MagicD(T1* t1) : t1p(t1) {}

    MagicD(MagicD& other) : t1p(other.t1p) { other.t1p = 0; }

    ~MagicD() {
        delete t1p;
    }
    
    void operator()(T2* t2) {}
};

int main()
{
    std::unique_ptr<B> b(new B());
    std::unique_ptr<A, MagicD<B, A>> a(b->theA(), MagicD<B, A>(b.release()));
}  
