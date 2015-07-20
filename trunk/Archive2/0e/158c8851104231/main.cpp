#include <type_traits>

int main() {
    static_assert( ::std::is_literal_type< ::std::wstring & >::value, "Nope" );
}