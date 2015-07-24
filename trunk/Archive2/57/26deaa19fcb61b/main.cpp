#include <iostream>
#include <string>
using namespace std;

struct Person
{
   string name() const { return "Jens"; }
};

struct generic_member_visitor
{
    template<class callable, class T>
    std::string operator()(callable& c,const T& t)
    {
        return c(t);
    }
};

int main()
{
   Person p;
   auto lambda = [](const auto& t){ return t.name();};
   generic_member_visitor gmc;
   
   cout << gmc(lambda,p) << endl;
}