#include <iostream>

class Scan
{ };

class Dust
{
    Dust() = default;
    
    void Scan();
    
    void Foo() { Scan scan; };
};

void Dust::Scan()
{
    
}

int main(void)
{

}