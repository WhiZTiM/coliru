#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <functional>

struct strucure1{};

struct classA
{
    std::vector< std::pair< strucure1, double> > list;
    double z = 0;
    
    bool Scheduled(std::pair< strucure1,double > const el, double const t )
    {
      return el.second==t;    
    }
    
    void foo()
    {
        {
            using std::placeholders::_1;
            auto Scheduled1 = std::bind(&classA::Scheduled,this,_1,z);
            bool call=std::find_if(list.begin(),list.end(),Scheduled1) != list.end();
        }
        {
            bool call = std::find_if(list.begin(),list.end(),
                                     [this](std::pair<strucure1,double> const& el){return el.second==z;})
                                     != list.end();
        }
    }
};

int main()
{
    classA a;
    a.foo();
}
