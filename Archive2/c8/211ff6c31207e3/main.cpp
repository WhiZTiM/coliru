#include <iostream>
#include <string>
using namespace std;

struct Person
{
   string name() const { return "Jens"; }
};


struct generic_member_visitor
{
    template<class T, class callable>
    auto operator()(callable&& c, T&& t) const
    {
        return c(forward<T>(t));
    }
};

int main()
{
   Person p;
   auto lambda = [](const auto& t){ return t.name();};
   generic_member_visitor v;
   cout << v(lambda, p) << endl;
}