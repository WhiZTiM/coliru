#include <iostream>
#include <memory>

template<typename F, typename... T>
void for_each1(F fun, T&&... args)
{
    (fun (std::forward<T>(args)), ...);
}

template<typename F, typename... T>
void for_each2(F fun, T&&... args)
{
    (..., fun (std::forward<T>(args)));
}

int main()
{
     for_each1([](auto i) { std::cout << i << " "; }, 4, 5, 6);
     std::cout << std::endl;
     for_each2([](auto i) { std::cout << i << " "; }, 4, 5, 6);
}
