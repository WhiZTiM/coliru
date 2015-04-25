#include <iostream>
#include <string>
#include <vector>
#include <functional>

class A {
private:
    std::function<void(int)> _myVoidIntFunction;
public:
    A(std::function<void(int)> param): _myVoidIntFunction{param}
    {
    }
    
    void callFunc(int i)
    {
        _myVoidIntFunction(i);
    }
};
    

int main()
{
    A a{
        [](int i) {
            std::cout << "i has value:" << i << std::endl;
        }
    };
    a.callFunc(20);
    return 0;
}
