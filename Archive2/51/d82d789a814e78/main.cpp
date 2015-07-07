#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>

    struct noop {
      struct anything {
        template<class T>
        operator T()const{ return {}; }
        template<class T>
        operator const T&()const{ static const T t{}; return t; }
      };
      template<class...Args>
      anything operator()(Args&&...)const{return {};}
    };

class foo {} ;

int main()
{
    std::function<void(int)> f1 = noop{};
    f1(3);
    std::function<int(std::string, char, double)> f2 = noop{};
    
    std::function<foo const&(int)> f3 = noop{};
}