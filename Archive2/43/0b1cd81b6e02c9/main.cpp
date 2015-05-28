#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

struct structure1{};

struct classA
{
    std::vector< std::pair< structure1, double> > list;
    double z = 0;
    
    bool Scheduled(std::pair< structure1,double > const el, double const t )
    {
        return el.second==t;
    }
    
    void foo()
    {
        using std::placeholders::_1;
        auto Scheduled1 = std::bind(&classA::Scheduled,this,_1,z);
        bool call=std::find_if(list.begin(),list.end(),Scheduled1) != list.end();
    }
    
    void bar()
    {
        bool call = std::find_if(list.begin(),list.end(),
                                 [this](std::pair<structure1,double> const& el){return el.second==z;})!=list.end();
    }
};

int main()
{
    classA a;
    a.foo();
    a.bar();
}
