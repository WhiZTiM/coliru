#include <memory>

struct A {};
struct B {
    B(A *) {};
};

int main()
{
    A *a = 0;
    std::shared_ptr<B> b1 = std::make_shared<B>(a);
    std::shared_ptr<B> b2 = std::make_shared<B, A *&>(a);
}