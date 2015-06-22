#include <map>
#include <functional>

struct U {};
struct A : public U {};
struct B : public U {};
struct C : public U {};
struct D : public U {};

enum Type
{
    EA, EB, EC, ED
};

U* create(Type t)
{
    static const std::map<Type, std::function<U*()>> factory =
    {
        { EA, [](){ return new A(); } },
        { EB, [](){ return new B(); } },
        { EC, [](){ return new C(); } },
        { ED, [](){ return new D(); } }
    };
    auto i = factory.find(t);
    if(i != factory.end())
        return i->second();
    return nullptr;
}

int main()
{
    U* _ = create(EB);
}
