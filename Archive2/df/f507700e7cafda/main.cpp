#include<iostream>
#include<type_traits>

using namespace std;

template<typename T = void>
class Foo
{
   public:
   template <typename Dummy = char>
    void
    Baz(typename std::enable_if< !std::is_same<T ,void>::value, Dummy>::type * = 0)
    {
        
    }
};

int main()
{ 
  Foo<int> x;
  x.Baz();
  
  /*
  
  Foo<void> x;
  x.Baz();
  */
  return 0;
}