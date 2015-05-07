#include <iostream>

class Scan
{ };

class Dust
{
    Dust() = default;
    
    void Scan();
    
    void Foo() { class Scan scan; };
};

void Dust::Scan()
{
    
}

int main(void)
{

}