#include <cstdio>
#include <functional>
#include <string>
#include <type_traits>

class X
{
    
};

class Y
{
    
};

namespace std
{
 string to_string(const Y&)  {
     return "Y";
 }
}

template <typename T, class Enable = void>
struct TF
{
  static void print(const T&) {
    printf("Without std::to_string\n");
  }  
};
 
template <typename T>
struct TF<T, typename std::enable_if<
sizeof(std::to_string(std::declval<T>())) != 0
>::type>
{
  static void print(const T& t) {
    printf("With std::to_string: %s\n", std::to_string(t).c_str());
  }  
};

int main() 
{
    TF<int>::print(42);    
    TF<X>::print(X{});
    TF<Y>::print(Y{});
}