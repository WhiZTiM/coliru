#include <iostream>
#include <string>
#include <type_traits>

#include <boost/variant.hpp>
 
template <template <typename T> class M, typename R>
struct member_visitor : boost::static_visitor<R>
{
    template <typename T>
    using member_type = decltype(M<T>::value);
    
    template <typename T>
    typename std::enable_if<std::is_member_object_pointer<member_type<T>>::value, R>::type
    operator()(const T & t)
    {
        return ((t).*(M<T>::value));
    }
    
    template <typename T>
    typename std::enable_if<std::is_member_function_pointer<member_type<T>>::value, R>::type
    operator()(const T & t)
    {
        return ((t).*(M<T>::value))();
    }    
};

struct Person
{
    std::string name;
};

struct Dir
{
    std::string name;
};

struct PersonM
{
    std::string name() const { return "PM";}
};

struct DirM
{
    std::string name() const {return "DM";}
};

template <typename T> struct name_member { static constexpr auto value = &T::name;};

int main()
{
    member_visitor<name_member, std::string> fv;
    
    using variant = boost::variant<Person, Dir, PersonM, DirM>;
    variant p = Person { "P"};
    variant d = Dir {"D"};    
    variant pm = PersonM{};
    variant dm = DirM{};
        
    std::cout << boost::apply_visitor(fv, p) << std::endl;
    std::cout << boost::apply_visitor(fv, d) << std::endl;
    std::cout << boost::apply_visitor(fv, pm) << std::endl;
    std::cout << boost::apply_visitor(fv, dm) << std::endl;        
}
