#include <type_traits>

void f(int t[10][20])
{
    using Param = decltype(t);
    static_assert( std::is_pointer<Param>(), "yep" );
    static_assert( std::is_array<Param>(), "nope" );
}

int main()
{
    f(nullptr);
}
