#include <boost/shared_ptr.hpp>

struct B {};
struct D : B {};

int main()
{
    boost::shared_ptr<B> b;
    boost::shared_ptr<D> d;
    b.swap(d);
}