#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;


template<typename F, typename... T>
void for_each1(F fun, T&&... args)
{
    (fun (forward<T>(args)), ...);
}

template<typename F, typename... T>
void for_each2(F fun, T&&... args)
{
    (..., fun (forward<T>(args)));
}

int main()
{
     for_each1([](auto i) { cout << i << " "; }, 4, 5, 6);
     for_each2([](auto i) { cout << i << " "; }, 4, 5, 6);
}
