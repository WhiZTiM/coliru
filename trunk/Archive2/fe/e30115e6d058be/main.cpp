#include <iostream>

template<typename T, typename S>
struct SomeRandomClass
{
    int myInt = 0;
};

template<typename T>
struct MyTemplateClass
{
    void DoSomething(T & t) 
    {
       std::cout << "Not specialized" << std::endl;
    }
};

template<typename T, typename S>
struct MyTemplateClass< SomeRandomClass<T, S> >
{
    void DoSomething(SomeRandomClass<T,S> & t) 
    {
       std::cout << "Specialized" << std::endl;
    }
};


int main()
{
    SomeRandomClass<int, int> a;
    
    MyTemplateClass<decltype(a)> b;
    b.DoSomething(a); // prints "Specialized"
    
    double c = 3.14;
    MyTemplateClass<decltype(c)> d;
    d.DoSomething(c); // print "Not specialized"
    
    return 0;
}
