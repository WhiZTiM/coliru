#include <boost/variant.hpp>
class B;
class C;
class D;
using A = boost::variant<B, C, D>;

struct B { int x; };
struct C { char y; };
struct D { bool z; };

int main()
{
    A var(B{5});
}
