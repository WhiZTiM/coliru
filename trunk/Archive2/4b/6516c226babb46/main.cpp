#include <type_traits>
#include <cstddef>
#include <utility>
#include <string>

#define SFINAE
template<size_t N>
struct foo {
    template<std::size_t K
    #ifdef SFINAE
        ,class=std::enable_if_t<(K<N)>
    #endif
    >
    decltype(auto) operator=(foo<K> const& in){
        static_assert( (K<N) );
        return in;
    }
};


using L = foo<10>;
using R = foo<11>;
static_assert(!std::is_same< L, R >{});
static_assert(!std::is_assignable< L &, R >{});
static_assert(std::is_assignable< R &, L >{});
static_assert(!std::is_assignable< L &, std::string >{});

int main()
{
}