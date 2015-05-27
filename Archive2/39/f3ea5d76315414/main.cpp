#include <iostream>
 template <template <int,bool,char> class>
struct Bar {};
template <int,bool,char> struct Zod {};

Bar<Zod> a;

struct GHI {
  template <int,bool,char>
  struct JKL {};
};

Bar <GHI::JKL> b;

template <template <typename... Ts> class>
struct Base {};
template<typename... Ts>
struct Floor {};
Base<Floor> c;

template <typename... Ts>
struct ABC {
  template <Ts... val>
  struct DEF {};
};
ABC<int,bool,char>::DEF<4,true,'c'> foo;
//Base<ABC<Floor< int>>::DEF<1>> bas;

void tprintf(const char* format) // base function
{
    std::cout << format;
}
 
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for ( ; *format != '\0'; format++ ) {
        if ( *format == '%' ) {
           std::cout << value;
           tprintf(format+1, Fargs...); // recursive call
           return;
        }
        std::cout << *format;
    }
}
 
int main()
{
    tprintf("% world% %\n","Hello",'!',123);
    return 0;
}