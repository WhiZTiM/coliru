#include <type_traits>


struct A {private: int i;}; // SL
struct B : A {};            // SL
struct C : B {int j;};      // Kein SL; Verstreute Member
struct D : B, A {};         // Kein SL: Zwei Basisklassen vom Typ A

static_assert(     std::is_standard_layout<A>{}, "" );
static_assert(     std::is_standard_layout<B>{}, "" );
static_assert( not std::is_standard_layout<C>{}, "" );
static_assert( not std::is_standard_layout<D>{}, "" );

int main() {}