#include <iostream>
#include <string>
#include <vector>

void f(int n) { std::cout <<"hi " << n << "\n"; }

template <typename Func, Func func>
struct Adapter
{
    Adapter(int n) : n_(n) { }

    void f() { func(n_); }
    int n_;
};

int main()
{
    Adapter<void(*)(int), f> adapter(43);
    adapter.f();
}
