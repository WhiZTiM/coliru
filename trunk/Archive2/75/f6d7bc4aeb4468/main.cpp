#include <boost/variant.hpp>
class B;
class C;
class D;
using A = boost::variant<B, C, D>;

int main() {}
