#include <type_traits>

struct A { A(char const*); };                // Kein POD
struct B { B(char const*); B() = default; }; // POD
struct C { C(char const*); C() = delete ; }; // POD

static_assert( not std::is_pod<A>{}, "" );
static_assert(     std::is_pod<B>{}, "" );
static_assert(     std::is_pod<C>{}, "" );

int main() {}