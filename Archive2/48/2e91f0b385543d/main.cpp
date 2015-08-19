#include <cstdio>
#include <functional>

class X
{
public:
    explicit X()
       : _del{[&](auto arg) { func(arg); }}
    {
        _del(13);
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