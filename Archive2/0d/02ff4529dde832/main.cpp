#include <boost/array.hpp>

#include <type_traits>


static_assert(std::is_trivially_constructible<boost::array<int, 10>>::value, ""); // minimum requirement for zero-initilization (I think)

static_assert(std::is_pod<boost::array<int, 10>>::value, ""); // heaviest requirement of all

// pretty sure it's zero initialized


int main() {}