#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>

    struct noop {
      struct anything {
        template<class T>
        operator T()const{ return {}; }
      };
      template<class...Args>
      anything operator()(Args&&...)const{return {};}
    };


int main()
{
    std::function<void()> f1 = noop{};
    std::function<int(std::string, char, double)> f2 = noop{};
}