#include <memory>

struct B1 {};
struct B2 {};
struct D : B2 {
    D(B1 *) {};
};

int main()
{
    B1 *b1 = 0;
    std::shared_ptr<D> d1 = std::make_shared<D>(b1);
    std::shared_ptr<D> d2 = std::make_shared<D, B1 *>(b1);
}