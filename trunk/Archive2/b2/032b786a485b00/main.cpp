#include <iostream>
#include <vector>
#include <array>
#include <functional>

class A
{
public:
    A(int n = 0) : m_n(n) { }
    virtual int f() const { return m_n; }
    virtual ~A() { }
protected:
    int m_n;
};

class B: public A
{
public:
    B(int n = 0) : A(n) { }
    virtual int f() const { return m_n + 1; }
};

template<typename T>
class MyRef
{
public:
    MyRef(T& _ref): ref(_ref){}
    T& get()
    { return ref; }
    T const& get() const
    { return ref; }  
private:
    T& ref;
};

int main()
{
    A const a(1);
    B const b(3);
    // Exemples de polymorphisme
    { // tableau statique
        std::array<A const*, 2> arr{{ &a, &b }}; //<-- poly
        for(auto element: arr)
            std::cout<<  element->f()<<" ";
        std::cout<< std::endl;
    }
    { // tableau dynamique
        std::vector<A> arr{ a, b }; //<-- pas de poly
        for(auto element: arr)
            std::cout<<  element.f()<<" ";
        std::cout<< std::endl;
    }
    { // tableau dynamique + references
        std::vector<MyRef<A const>> arr{ a, b }; //<-- poly
        for(auto element: arr)
            std::cout<<  element.get().f()<<" ";
        std::cout<< std::endl;
    }
    { // tableau dynamique+ reference (version standard)
        std::vector<std::reference_wrapper<A const>> arr{ a, b }; //<-- poly
        for(auto element: arr)
            std::cout<<  element.get().f()<<" ";
        std::cout<< std::endl;
    }
    return 0;
}
