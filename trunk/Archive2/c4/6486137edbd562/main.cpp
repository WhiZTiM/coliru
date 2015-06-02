#include <iostream>
#include <memory>

class Singleton
{
public:
    ~Singleton()  { std::cout << "destruction!\n"; }

    static Singleton& getInstance() 
    {
        static Singleton instance;
        return instance;
    }

    void foo() { std::cout << "foo!\n"; }

private:
    Singleton() { std::cout << "construction!\n"; }
};

int main()
{
    Singleton::getInstance().foo();
}