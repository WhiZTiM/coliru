#include <iostream>
#include <memory>
#include <vector>

class Foo
{
public:
    std::string name;
    Foo(std::string name)
    {
        this->name = name;
        std::cout << "Construction " << this << std::endl;
    }
    Foo(Foo & copy)
    {
       this->name = copy.name;
        std::cout << "Copy Construction " << this << std::endl;
    }
    Foo(Foo && move)
    {
        //this->name = name;
        std::cout << "Move Construction " << this << std::endl;
    }
    ~Foo()
    {
        std::cout << "Destruction " << this << std::endl;
    }
    void bar()
    {
        std::cout << "My name is-->" << name << std::endl;
    }
};

void hi(Foo & f)
{
    std::cout << "copy ";
    f.bar();
}
void hi(Foo && f)
{
    std::cout << "move ";
    f.bar();
    f.name *= " modified hehe";
}

int main()
{
    Foo f ("maxi");
    hi(std::move(f));
    f.bar();
    
}
