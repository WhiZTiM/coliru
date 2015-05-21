#include <functional>
#include <iostream>

class callable_concept
{
public:
    virtual void operator()(int x) = 0;
};

template<typename C>
class callable_model : public callable_concept
{
public:
    callable_model(C& c) : c_(c) {}
    
    void operator()(int x) override
    {
        c_(x);
    }
private:
    C& c_;
};

int main()
{
    auto fn = [] (int x) { std::cout << "x = " << x << std::endl; };
    
    callable_model<decltype(fn)> a(fn);
    a(5); // call derived
    
    callable_concept& b = a;
    b(10); // call type-erased
    
    auto c = std::bind(a, 15);
    c(); // call bound derived
    
    //auto d = std::bind(b, 20);   // this fails
    auto d = std::bind(std::ref(b), 20);   // this works, but UB?
    d(); // call bound type-erased
}
