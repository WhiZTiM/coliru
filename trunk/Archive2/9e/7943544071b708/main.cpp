#include <boost/smart_ptr.hpp>
#include <iostream>

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
    Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)" << std::endl; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "operator=(Noisy&&)" << std::endl; return *this; }
};

int main()
{
    {
        boost::scoped_array<Noisy> ptr(new Noisy[5]);
    }
    
    std::cout << std::endl;
    
    {
        boost::shared_array<Noisy> arr(new Noisy[5]);
    }
}
