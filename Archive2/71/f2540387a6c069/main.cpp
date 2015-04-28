#include <memory>

struct A 
{
    virtual ~A() = default;
};

struct B :public A
{
};

int main()
{
    std::unique_ptr<A>(new B);
}