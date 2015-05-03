#include <type_traits>

#define MAKE_IMMREF( NAME ) ImmRef< decltype( NAME ) >{ NAME }

template<typename T>
struct ImmRef {
    static_assert ( std::is_const< T >::value, "ImmRef requires a constant." );

    T & ref;
};

int nc;
int const c {};

auto good = MAKE_IMMREF( c );
auto bad = MAKE_IMMREF( nc );