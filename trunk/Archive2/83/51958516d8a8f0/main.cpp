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

template<class R,class callable>
struct generic_member_visitor : boost::static_visitor<R>
{
    callable& c;
    generic_member_visitor(callable& c):c(c){}
    template<class T>
    std::string operator()(const T& t)const
    {
        return c(t);
    }
};

int main()
{
   using variant = boost::variant<Person,Dir>;
   variant p = Person{};
   variant d = Dir{};
   auto lambda = [](const auto& t){ return t.name();};
   generic_member_visitor<std::string,decltype(lambda)> gmc(lambda);
   
   cout << boost::apply_visitor(gmc,p) << endl;
   cout << boost::apply_visitor(gmc,d) << endl;
}