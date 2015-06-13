#include <iostream>
#include <string>

template<typename Type, Type... Args>
struct sum;

template<typename Type>
struct sum<Type> { static const Type value = Type(0); };

template<typename Type, Type Head, Type... Tail>
struct sum<Type, Head, Tail...> { static const Type value = Head + sum<Type, Tail...>::value; };

template <typename... Type>
struct sizeof_types {
    static const unsigned int size = sum<unsigned int, sizeof(Type)...>::value;
};

int main()
{
  // Instead of sizeof(double) + sizeof(int) + sizeof(float) + sizeof(char)
  std::cout << sizeof_types<double,int,float,char>::size;
}
