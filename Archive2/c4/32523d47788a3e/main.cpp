#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>

    struct noop {
      struct anything {
        template<class T>
        operator T(){
            std::cout << "operator T\n";
            return {};
        }
        template<class T>
        operator const T&()const{
            static const T t{};
            std::cout << "operator T const&\n";
            return t;
        }
      };
      template<class...Args>
      anything operator()(Args&&...)const{return {};}
    };


int main()
{
    std::function<void(int)> f1 = noop{};
    f1(3);
    std::function<int(std::string, char, double)> f2 = noop{};
    
    std::function<std::string const&(int)> f3 = noop{};
    
    int x = noop::anything{};
    (void)x;
    int const& y = noop::anything{};
    (void)y;
    
    std::cout << "f3 creates: " << f3(2) << std::endl;
}