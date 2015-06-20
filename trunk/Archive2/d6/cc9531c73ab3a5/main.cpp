#include <iostream>
#include <memory>
#include <vector>

 
struct D { // deleter
    void    operator()(int *ptr)
    {
        delete ptr;
    }
};
 
struct Foo { // object to manage
    Foo(int value) {
        unique.reset(new int(value));
    }
    Foo(const Foo& other) {
        unique = std::move(const_cast<Foo&>(other).unique);
    }
    Foo(Foo &&other) {
        std::cout << "Foo move ctor\n";
        unique = std::move(other.unique);
    }
    ~Foo() {
        std::cout << "~Foo dtor: " << std::boolalpha << bool(unique) << "\n";
        
    }
    Foo     &operator=(Foo const &other)
    {
        unique = std::move(const_cast<Foo&>(other).unique);
        return *this;
    }
    
    Foo     &operator=(Foo &&other)
    {
        unique = std::move(other.unique);
        return *this;
    }
    
    std::unique_ptr<int, D>    unique;
};
 

 
int main()
{
    std::vector<Foo>        test;
    
    for (int i = 0; i < 100; ++i)
        test.emplace_back(2);
        
    for (auto it = test.begin(); it != test.end();)
    {
        it = test.erase(it);
    }
}