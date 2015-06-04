#include <iostream>
#include <utility>

#include <cstdlib>

template< std::size_t i >
struct alignas((1 << i)) aligned_storage
{

};

template< std::size_t ...I >
constexpr
void
test(std::index_sequence< I... >)
{
    static_assert(((sizeof(aligned_storage< I >) == (1 << I)) && ...));
}

int
main()
{
    test(std::make_index_sequence< 29 >{});
    return EXIT_SUCCESS;
}
