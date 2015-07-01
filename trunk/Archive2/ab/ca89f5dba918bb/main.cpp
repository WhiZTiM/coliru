#include <boost/multi_array/multi_array_ref.hpp>
#include <iostream>

using ref = boost::multi_array_ref<char, 1>;
using boost::extents;

int main() {
    char some_arr[] = "hello world";

    ref no_copy(some_arr, extents[sizeof(some_arr)]);

    std::cout.write(no_copy.data(), no_copy.num_elements());
}
