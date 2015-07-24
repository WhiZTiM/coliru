#include <iostream>
#include <string>


#include <boost/variant.hpp>

using namespace std;

struct Person
{
   string name() const { return "Jens"; }
};

struct Dir
{
    string name() const {return "foo"; }
};

int main()
{
   using variant = boost::variant<Person,Dir>;
   variant p = Person{};
   variant d = Dir{};
   auto mem_fn_name = [](const auto& t){ return t.name();};
   
   cout << boost::apply_visitor(mem_fn_name,p) << endl;
   cout << boost::apply_visitor(mem_fn_name,d) << endl;
}