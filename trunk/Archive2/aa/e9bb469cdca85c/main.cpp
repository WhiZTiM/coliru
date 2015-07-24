#include <iostream>
#include <string>
using namespace std;

struct Person
{
   string name() const { return "Jens"; }
};

struct Dir
{
    string name() const {return "foo"; }
};

template<class callable>
struct generic_member_visitor
{
    template<class T>
    std::string operator()(callable& c,const T& t)const
    {
        return c(t);
    }
};

int main()
{
   Person p;
   Dir d;
   auto lambda = [](const auto& t){ return t.name();};
   generic_member_visitor<decltype(lambda)> gmc;
   
   cout << gmc(lambda,p) << endl;
   cout << gmc(lambda,d) << endl;
}