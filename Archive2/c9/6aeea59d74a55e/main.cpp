#include <iostream>
#include <memory>

class Singleton
{
public:
    ~Singleton()  { std::cout << "destruction!\n"; }

    static Singleton* getInstance() 
    {
        static std::unique_ptr<Singleton> instance;
        if (!instance)
            instance.reset(new Singleton());
        
        return instance.get();
    }
    
    void foo() { std::cout << "foo!\n"; }

private:
    Singleton() { std::cout << "construction!\n"; }
};

int main()
{
    Singleton::getInstance()->foo();
}
