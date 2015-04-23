#include <type_traits>

class A
{
    ~A() = delete;
};

class B
{
    ~B(){}
};

int main()
{
    static_assert (std::is_trivial<A>::value, "A is not trivial");
    static_assert (std::is_trivial<B>::value, "B is not trivial");
    return 0;
}
