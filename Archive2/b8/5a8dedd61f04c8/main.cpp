#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <type_traits>

class Object {
    public:
    
    template<typename T>
    void call(T whatever, int x) {
        std::cout << "called call";
    }
};

//Some condition
bool getResult(int x)
{
    if(x == 42)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
T transformValue(T v) {
 return T();   
}

template<typename T>
void doSomething(T& value, int x)
{

    Object obj;
    if(getResult(x))
    {   //Continue as normal if the result is true.
        obj.call<T>(value, x);
    }

    else
    {        
        obj.call(transformValue(value), x);
    }
}



int main()
{
    int val = 42;
    doSomething(val, 43);
}
