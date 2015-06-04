#include <iostream>
#include <type_traits>

#include <cstdlib>
#include <cassert>

template< typename visitor, typename ...visitors >
struct composite_visitor
    : std::decay_t< visitor >
    , composite_visitor< visitors... >
{

    //using std::decay_t< visitor >::operator ();
    //using composite_visitor< visitors... >::operator ();

    composite_visitor(visitor && _visitor, visitors &&... _visitors)
        : std::decay_t< visitor >(std::forward< visitor >(_visitor))
        , composite_visitor< visitors... >{std::forward< visitors >(_visitors)...}
    { ; }

};

template< typename visitor >
struct composite_visitor< visitor >
    : std::decay_t< visitor >
{

    //using std::decay_t< visitor >::operator ();

    composite_visitor(visitor && _visitor)
        : std::decay_t< visitor >(std::forward< visitor >(_visitor))
    { ; }

};

template< typename visitor, typename ...visitors >
composite_visitor< visitor, visitors... >
compose_visitors(visitor && _visitor, visitors &&... _visitors)
{
    return {std::forward< visitor >(_visitor), std::forward< visitors >(_visitors)...};
}

int
main()
{
    struct A {};
    struct B {};
#if 1
    struct { int operator () (A) { return 1; } } x;
    struct { int operator () (B) { return 2; } } y;
    auto xy = compose_visitors(x, y);
#else
    auto xy = compose_visitors([] (A) { return 1; }, [] (B) { return 2; });
#endif
    // "implicit":
    assert(xy(A{}) == 1);
    assert(xy(B{}) == 2);
    // "explicit":
    assert(xy.operator () (A{}) == 1); // error: member 'operator()' found in multiple base classes of different types
    assert(xy.operator () (B{}) == 2);
    return EXIT_SUCCESS;
}