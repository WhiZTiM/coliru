#include <boost/utility/string_ref.hpp>
#include <iostream>

using boost::string_ref;

int main() {
    char some_arr[] = "hello world";

    string_ref no_copy(some_arr);

    std::cout << no_copy;
}
