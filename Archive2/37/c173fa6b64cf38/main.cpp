#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>

    struct noop {
      struct anything {
        template<class T>
        operator T(){ return {}; }
        template<class T>
        operator T&()const{ static T t; return t; }
      };
      template<class...Args>
      anything operator()(Args&&...)const{return {};}
    };


int main()
{
    std::function<void()> f1 = noop{};
    std::function<int(double, char, std::string)> f2 = noop{};
    // int x = noop::anything{};
    std::function<std::string const&()> f3 = noop{};
    std::string const& s = noop::anything{};
    std::cout << s << '\n';
}