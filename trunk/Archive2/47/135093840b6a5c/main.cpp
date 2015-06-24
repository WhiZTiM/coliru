#include <boost/type_traits.hpp>
#include <iostream>
#include <string>
#include <functional>



template<typename Close>
class Guard {
  Close close;
public:
  template<typename Open, typename Close_>
  Guard(Open open, Close_ close) : close(close)
  {
      // open must be void (void)
      open();
  }
  ~Guard() { close(); }
};

//template<typename Open, typename Close> 
template<typename Open, typename Close>
auto makeGuard(Open open, Close close)
 {
     return Guard<Close>(open, close);
 }
 
int main() {
    
    auto g = makeGuard([]() { std::cout << "open\n"; },
                       []() { std::cout << "close\n"; } );
}

