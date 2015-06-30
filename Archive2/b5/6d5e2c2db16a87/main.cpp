#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>

struct Foo
{
    Foo(int value) : bar(value) { }
    int bar;  
};

int
main()
{
    boost::optional<Foo> foo;
    foo = boost::in_place(5);
}