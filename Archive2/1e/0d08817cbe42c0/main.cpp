#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>


template <typename T> struct name_member { static constexpr auto value = &T::name;};

// FIELD
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

// METHOD
struct PersonM
{
    std::string name() const { return "PM";}
};

struct DirM
{
    std::string name() const {return "DM";}
};

template <template <typename T> class M, typename R>
struct method_visitor : boost::static_visitor<R>
{
    template <typename T>
    R operator()(const T & t)
    {
        return ((t).*(M<T>::value))();
    }
};

int main()
{
    {
        using variant = boost::variant<Person, Dir>;
        variant p = Person { "P"};
        variant d = Dir {"D"};
        
        field_visitor<name_member, std::string> fv;
        
        std::cout << boost::apply_visitor(fv, p) << std::endl;
        std::cout << boost::apply_visitor(fv, d) << std::endl;
    }
    
    {
        using variant = boost::variant<PersonM, DirM>;
        variant p = PersonM{};
        variant d = DirM{};
        
        method_visitor<name_member, std::string> fv;
        
        std::cout << boost::apply_visitor(fv, p) << std::endl;
        std::cout << boost::apply_visitor(fv, d) << std::endl;
    }    
}
