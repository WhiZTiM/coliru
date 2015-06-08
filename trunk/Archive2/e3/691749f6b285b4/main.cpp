#include <iostream>
#include <type_traits>

template<typename T> struct check_{
    
   typedef char yes;
   typedef char no[2];
   
   template<typename U>
   static auto test(U u) -> decltype(std::declval<U>()+1, yes());
   
   template<typename U>
   static no& test(...);
   
   static const bool value = sizeof(test<T>(0)) == sizeof(yes);
 };

template <typename T>
typename std::enable_if<check_<T>::value, T>::type 
f(T t)
{
    std::cout << "satisfies" << std::endl;
    return t;
} 
template <typename T>
typename std::enable_if<!check_<T>::value, T>::type 
f(T t )
{
    std::cout << "doesn't satisfy" << std::endl;
    return t;
}    

struct A{
     
};

int main()
{
    
    A a;
    f(a);
    f(1);
    
}
