#include <iostream>

template<typename... Ts>
struct A
{
    template<typename T>
    T do_something()
    {
        return T();
    }
};

template<typename... Ts>
struct B
{
    static void do_something()
    {
        A<Ts...> a;
        a.do_something<int>();
    }
};

int main()
{
    B<int, int, int>::do_something();   
}
