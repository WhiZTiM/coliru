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

using variant_t = boost::variant<Person, Dir>;

template <typename T> struct name_member { static constexpr auto value = &T::name;};

template <template <typename T> class M, typename R>
struct field_visitor : boost::static_visitor<R>
{
    template <typename T>
    R operator()(const T & t)
    {
        return t.*(M<T>::value);
    }
};

int main()
{
    Person p { "P"};
    Dir d {"D"};
    
    field_visitor<name_member, std::string> fv;
    
    std::cout << fv(p) << std::endl;
    std::cout << fv(d) << std::endl;
}
