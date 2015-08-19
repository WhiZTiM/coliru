#include <memory>
#include <tuple>
#include <functional>
#include <forward_list>
#include <cassert>
#include <type_traits>

class X
{
public:
    explicit X()
       : _del{[&](auto&&... arg) { func(std::forward<decltype(arg)>(arg)...); }}
    {
    }
    
private:
    void func(int arg)
    {
        std::printf("arg: %d\n", arg);
    }

private:
    std::function<void(int)> _del;
};
    

int main()
{
    X();
}
