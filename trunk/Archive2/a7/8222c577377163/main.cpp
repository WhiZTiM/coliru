#include "boost/typeof/typeof.hpp"
#include "boost/units/detail/utility.hpp"
#include <iostream>
#include <string>

struct One{};
struct Two{};

template<typename T>
struct Type
{
   static std::string name(void)
   {
      return boost::units::detail::demangle(typeid(T).name());
   }
};

template<typename T1,
         typename T2>
struct A
{
   typedef A<T1, T2> Self;

   A()
   {
      std::cout << Type<Self>::name() << std::endl;
   }
};

template<typename T1,
         typename T2,
         typename T3>
struct B : public A<One, B<T1, T2, T3> >, // The B<T1, T2, T3> here is redundant
           public A<Two, B<T1, T2, T3> >
{
   typedef B<T1, T2, T3> Self;

   B()
   {
      std::cout << Type<Self>::name() << std::endl;
   }
};

int main(int argc, char* argv[])
{
   B<int, int, int> t;
   return 0;
}
