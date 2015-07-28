#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>

struct Person
{
    std::string name;
};

struct Dir
{
    std::string name;
};

template <template <typename T> class M, typename R>
struct field_visitor : boost::static_visitor<R>
{
    template <typename T>
    R operator()(const T & t)
    {
        return t.*(M<T>::value);
    }
};

template <typename T> struct name_member { static constexpr auto value = &T::name;};

int main()
{
    using variant = boost::variant<Person, Dir>;
    variant p = Person { "P"};
    variant d = Dir {"D"};
    
    field_visitor<name_member, std::string> fv;
    
    std::cout << boost::apply_visitor(fv, p) << std::endl;
    std::cout << boost::apply_visitor(fv, d) << std::endl;
}
