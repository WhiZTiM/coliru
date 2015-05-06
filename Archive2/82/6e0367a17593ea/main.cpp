#include <iostream>

template <typename Pair>
struct use_first     
{
   typedef Pair argument_type;
   typedef typename Pair::first_type result_type;

   const result_type& operator()( const Pair& x ) const
   {
      return x.first;
   }
};

class ModuleData;
        
template<class T>
class AutoPtr
{
public:
   AutoPtr() : p(0) {}
   ~AutoPtr();

   T *p;
};

template <typename T>
AutoPtr<T>::~AutoPtr()
{
   if( p )
      p->Release();
}


template <typename T1, typename T2>
struct pair
{
   typedef T1           first_type;
   typedef T2           second_type;
   typedef pair<T1, T2> this_type;

   T1 first;
   T2 second;

   pair()
      : first(),
      second() {}

#if 1
   pair( const pair& ) = default;
#endif
};

typedef AutoPtr<ModuleData>  ModuleDataRef;

struct Test 
{
   Test();
   ~Test();
   Test( const Test & );
   Test &operator=(const Test &);

   typedef pair<const int, ModuleDataRef> ValuePair;
   use_first<ValuePair> uf;
};     

int main()
{
    std::cout << "ok" << std::endl;
    return 0;
}