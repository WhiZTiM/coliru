#include <boost/optional.hpp>

struct B { };

struct D : B { };

int main()
{
    boost::optional<D> od = D{};
    
    boost::optional<B> const& ob = boost::optional<B>(od);
}