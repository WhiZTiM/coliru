#include <type_traits>
#include <utility>
#include <memory>
#include <iostream>

#include <cstdlib>
#include <cassert>

namespace
{

template< typename lambda >
auto
make_scope_guard(lambda && _lambda)
{
    using L = std::decay_t< lambda >;
    auto D = [] (L * p) { if (!!p) { std::forward< lambda >(*p)(); } delete p; };
    return std::unique_ptr< L, decltype(D) >{::new L(std::forward< lambda >(_lambda)), std::move(D)};
}

}

int
main()
{
    std::cout << 1 << std::endl;
    {
        std::cout << 2 << std::endl;
        [[gnu::unused]] auto && guard_ = make_scope_guard([&] { std::cout << 4 << std::endl; });
        std::cout << 3 << std::endl;
    }
    std::cout << 5 << std::endl;
    return EXIT_SUCCESS;
}
