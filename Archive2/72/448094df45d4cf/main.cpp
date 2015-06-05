#include <iostream>
template<typename ...Args>
void printer(Args&&... args) {
    (std::cout << ... << args) << '\n';
}


template<typename Func, typename T>
auto Min(Func f, T l, T r)
{
    return f(l, r);
}

template<typename Func, typename T, typename... Args>
auto Min(Func f, T l, T r, Args... args)
{
    return Min(f, f(l, r), args...);
}

template< typename... Args>
auto Mul_Fold(Args... args)
{
    return ( ... * args);
}


template<typename... Args>
bool Check(Args&& ... args)
{
    return (... && args);
}



int main()
{
    std::cout << Min([](auto l, auto r) { return l < r ? l : r;}, 1, 2, 0) << "\n";
    std::cout << Mul_Fold( 1, 2, 3) << "\n";
    
    auto test1 = true; //[] { return true; };
    auto test2 = false; //[] { return false; };
    auto test3 = [] { return true; };
    
    
    
    std::cout << std::boolalpha << Check(test1, test2) << "\n";
    std::cout << std::boolalpha << Check(test1, test3) << "\n";
}