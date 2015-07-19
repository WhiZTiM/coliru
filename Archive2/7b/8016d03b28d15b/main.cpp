#include <iostream>
#include <vector>
#include <memory>

class A
{
public:
    void* operator new  ( std::size_t count, std::size_t msg, std::size_t mmsg );
    void operator delete  ( void* ptr, std::size_t msg, std::size_t mmsg );
};

void* A::operator new  ( std::size_t sz, std::size_t msg, std::size_t mmsg ){
    std::printf("global op new called, message = %lu, %lu", msg, mmsg);
    return std::malloc(sz);
}

void A::operator delete  ( void* ptr, std::size_t msg, std::size_t mmsg ){
    std::printf("global op new called, message = %lu, %lu", msg, mmsg);
}

int main(){
    A *a = new (1, 1) A;
    delete a;
}