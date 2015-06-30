#include <iostream>
#include <string>
#include <functional>

typedef std::function<std::string(void)> acceptedFunc;
template<typename Func>
void asdf(Func doThing) {
    decltype(doThing()) val = doThing();
    std::cout << typeid(val).name() << " -- " << typeid(acceptedFunc).name() << std::endl;
    if(typeid(val) == typeid(acceptedFunc)) {
        std::cout << "yay" << std::endl;
    }
}


int main()
{
    asdf([&]() {
        return (std::string)"qwer";
    });
    
    
    
    
    std::cout << "done" << std::endl;
    
    return 0;
}

