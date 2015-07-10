#include <vector>
#include <functional>
#include <iostream>

template <typename Ret, typename... Args>
class MyDelegate{
    using FunType = std::function<Ret(Args...)>;
    std::vector<FunType> vec;

    public:
    void operator+=( const FunType& newElement)
    {
        vec.push_back(newElement);
    }


    Ret operator()(const Args&... args)
    {
        for (auto i = vec.begin(); i != vec.end(); ++i)
            (*i)(args...);
    }
};
int main()
{
    MyDelegate<void, int> delegate1;
    delegate1 += [](const int a)->void{std::cout << a << std::endl; };
    delegate1(1);
}
