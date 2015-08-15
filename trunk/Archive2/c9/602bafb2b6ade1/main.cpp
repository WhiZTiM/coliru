#include <memory>
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
        std::shared_ptr<Noisy> arr1(new Noisy[5], std::default_delete<Noisy[]>{});
    }
    
    std::cout << std::endl;
    
    {
        std::shared_ptr<Noisy> arr2(new Noisy[5], [](Noisy* ptr) { delete[] ptr; } );
    }
}
