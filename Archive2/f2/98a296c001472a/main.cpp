#include <iostream>
#include <vector>
#include <memory>

class A
{
public:
    A() { throw 1; }
    
    void* operator new  ( std::size_t count, std::size_t msg, std::size_t mmsg );
    void operator delete  ( void* ptr, std::size_t msg, std::size_t mmsg );
};

void* A::operator new  ( std::size_t sz, std::size_t msg, std::size_t mmsg ){
    std::printf("global op new called, message = %lu, %lu\n", msg, mmsg);
    return std::malloc(sz);
}

void A::operator delete  ( void* ptr, std::size_t msg, std::size_t mmsg ){
    std::printf("global op delete called, message = %lu, %lu\n", msg, mmsg);
}

int main(){
    try
    {
    A *a = new (1, 1) A;
    } catch(...) {}
}