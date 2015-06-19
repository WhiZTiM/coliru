#include <iostream>
#include <list>

struct Foo { char data[102]; };

int main()
{    
    std::list<Foo> fooList;
    
    for (int ii = 0; ii < 5; ++ii)
    {
        fooList.push_back(Foo());
        std::cout << "Address of back: " << (&fooList.back()) << std::endl;
    }
    
    std::cout << std::endl;
    
    for (auto iter = fooList.begin(); iter != fooList.end(); ++iter)
    {
        std::cout << "Address of item: " << &(*iter) << std::endl;
    }
    
    return 0;
}