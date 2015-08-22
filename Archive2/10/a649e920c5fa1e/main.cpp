#include<iostream>
#include<string>
#include<functional>


int foo1(int k)
{
    return k * 2;
}

auto foo2(double k, int z, float y) -> decltype((k + z + y) + 10)
{
    return (k + z + y) + 10;
}

std::string foo3(std::string&& _str)
{
    return _str.append(" yo");
}

int foo4(std::function<int(int)> Fn, int&& val)
{
    return Fn(std::forward<int>(val));
}

template <typename Fn>
int foo5(Fn fn, int x)
{
    return fn(x);
}

template <typename T, typename... args>
T(*LogAndCall(T(*ptr)(args...)))(args...)
{
    std::cout << "Logging function call to: " << ptr << " with " << sizeof...(args) << " argument(s)" << std::endl;
    return ptr;
}

int main()
{
    //call foo1
    auto r1 = LogAndCall(foo1)(20);
    std::cout << "Ret value: " << r1 << std::endl << std::endl;

    //call foo2
    auto r2 = LogAndCall(foo2)(12.63, 233, 12.35f);
    std::cout << "Ret value: " << r2 << std::endl << std::endl;

    //call foo3
    auto r3 = LogAndCall(foo3)("hihi");
    std::cout << "Ret value: " << r3 << std::endl << std::endl;

    //call foo4
    auto r4 = LogAndCall(foo4)([](int&& x){
        return x*10;
    },100);
    std::cout << "Ret value: " << r4 << std::endl << std::endl;

    //call foo5
    auto r5 = LogAndCall(foo5<int(int)>)([](int x){ //cannot determine which instance of function template "foo5" is intended
        return x*2;
    }, 5);
    std::cout << "Ret value: " << r5 << std::endl << std::endl;

    std::cin.get();
}
