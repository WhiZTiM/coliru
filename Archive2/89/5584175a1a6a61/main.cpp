#include <functional>
#include <string>
#include <map>
#include <iostream>

namespace ae {
    struct Game {
        void stop() {std::cout << "success\n";}
    };
    template<class ...Args>
    struct holder {
        std::map<std::string, std::function<void(Args...)>> funcMap;
        
        template <typename T>
        void connect(T* targObj, void (T::*func)(Args...), std::string funcName) {
            std::function<void(Args...)> newFunc = std::bind(func, targObj); //expected primary expression before ',' token
            funcMap[std::move(funcName)] = std::move(newFunc);
        }
        void invoke(std::string funcName, Args... Vals)
        {funcMap[funcName](Vals...);}
    };
}

int main() {
    ae::Game g;
    ae::holder<> h;
    ae::Game target;
    h.connect(&g, &ae::Game::stop, "close");
    h.invoke("close");
}