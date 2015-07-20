#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

int main() {
    static_assert( ::std::is_literal_type< ::std::wstring & >::value, "Nope" );
}