#include <type_traits>
class Foo
{
    void CheckFoo()
    {
        using type = typename std::remove_reference<decltype(*this)>::type;
    }
};
int main()
{}