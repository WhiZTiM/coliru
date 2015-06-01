#include <type_traits>

struct A { A(char const*); };
struct B { B(char const*); B() = default; };

static_assert( not std::is_pod<A>{}, "" );
static_assert(     std::is_pod<B>{}, "" );

int main() {}