#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

int main()
{
    namespace bm = boost::multiprecision;
    using uint2048_t = bm::number<bm::cpp_int_backend<2048, 2048, bm::unsigned_magnitude, bm::unchecked, void>>;
    uint2048_t x = 123;
    std::cout << x;
}