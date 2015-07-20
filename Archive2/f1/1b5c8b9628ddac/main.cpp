#include <type_traits>
#include <string>

int main() {
    static_assert( ::std::is_literal_type< ::std::wstring & >::value, "Nope" );
}