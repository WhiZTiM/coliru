#include <boost/concept_check.hpp>

template<typename Arg>
struct foo {
    using type = typename foo<Arg*>::type;
};

template<typename Arg>
struct Concept {
    BOOST_CONCEPT_USAGE(Concept)
    {
        typename foo<Arg>::type {};
    }
};

template<typename Arg>
int bar()
{
    return typename foo<Arg>::type {};
}

BOOST_CONCEPT_ASSERT((Concept<int>));

int main()
{
    return bar<int>();
}

template int bar<int>();

template<typename T>
struct foo<T*> { using type = int; };