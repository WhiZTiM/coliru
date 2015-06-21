#include <type_traits>
#include <utility>

template< typename F, std::size_t ...indices >
struct enumerator;

template< typename F >
struct enumerator< F >
{

    constexpr
    enumerator(F && _f)
        : f(std::forward< F >(_f))
    { ; }

    template< std::size_t ...I >
    constexpr
    bool
    operator () () const
    {
        return f(std::index_sequence< I... >{});
    }

private :

    F f;

};

template< typename F, std::size_t first, std::size_t ...rest >
struct enumerator< F, first, rest... >
    : enumerator< F, rest... >
{

    constexpr
    enumerator(F && _f)
        : enumerator< F, rest... >(std::forward< F >(_f))
    { ; }

    template< std::size_t ...I >
    constexpr
    bool
    operator () () const
    {
        return enumerator::template operator () < I... >(std::make_index_sequence< first >{}); // ltr
    }

    template< std::size_t ...I, std::size_t ...J >
    constexpr
    bool
    operator () (std::index_sequence< J... >) const
    {
        return (enumerator< F, rest... >::template operator () < I..., J >() && ...); // rtl, `< J, I... >` - ltr
    }

};

template< std::size_t ...I, typename F >
constexpr
enumerator< F, I... >
make_enumerator(F && f)
{
    static_assert(0 < sizeof...(I));
    static_assert(((0 < I) && ...));
    return std::forward< F >(f);
}

// main.cpp

#include <iostream>

#include <cstdlib>
#include <cassert>

struct truth
{

    template< std::size_t ...I >
    constexpr
    bool
    operator () (std::index_sequence< I... >) const
    {
        return true;
    }

};

struct printer
{

    template< std::size_t ...I >
    bool
    operator () (std::index_sequence< I... >) const
    {
        for (std::size_t const & i : {I...}) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
        return true;
    }

};

int
main()
{  
    static_assert(make_enumerator< 10, 10, 10, 10 >(truth{})());
    assert((make_enumerator< 3, 3, 3 >(printer{})()));
    return EXIT_SUCCESS;
}
