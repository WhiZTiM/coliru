#include <iostream>
#include <string>
#include <type_traits>

#include <boost/variant.hpp>

struct Person
{
    std::string name() const { return "Jens"; }
};

struct Dir
{
    std::string name() const {return "foo"; }
};

int main()
{
   using variant = boost::variant<Person,Dir>;
   variant p = Person{};
   variant d = Dir{};
   auto l = [](const auto& t){ return t.name();};
   
   std::cout << boost::apply_visitor([](const auto& t){ return t.name();},p) << "\n";
   std::cout << boost::apply_visitor(l,d) << std::endl;
}