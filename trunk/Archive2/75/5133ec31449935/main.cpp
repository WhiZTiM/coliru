

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>





struct Fly
{
    template<typename T>
    void Move(T const& t)
    {        
       std::cout << t.Name() << " flies\n";
    }
};

struct CantFly
{
    template<typename T>
    void Move(T const& t)
    {        
       std::cout << t.Name() << " can't fly\n";
    }
};



template<typename FlyType>
struct Bird
{
    FlyType m_type;
    std::string m_name;
    
    
    Bird(std::string name)
    : m_type{ }
    , m_name(std::move(name))
    { }
    
    
    const std::string& Name() const
    {
        return m_name;
    }
    
    
    void Move()
    {
        m_type.Move(*this);
    }
};



struct Eagle : Bird<Fly>
{
    Eagle() : Bird<Fly>("Eagle") { }
};

struct Ostritch : Bird<CantFly>
{
    Ostritch() : Bird<CantFly>("Ostritch") { }
};





int main()
{
    Eagle e;
    Ostritch o;
    e.Move();
    o.Move();
}