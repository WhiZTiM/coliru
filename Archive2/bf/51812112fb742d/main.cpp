#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <cctype>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits.hpp>
#include <boost/function.hpp>
#include <boost/typeof/std/utility.hpp>
#include <boost/function_types/result_type.hpp>
#include <type_traits>

template<class T>
struct is_void : boost::mpl::bool_<false>{};

template<>
struct is_void<void> : boost::mpl::bool_<true>{};

template<class T>
struct void_t { typedef void type_t ;}; 


template<class T>
struct has_const_iterator 
{   
    //catch ones which do not SFINAE on the T::const_iterator part
    /*
    template<class U, class A = typename void_t<typename U::const_iterator>::type_t >//class void_t< typename U::const_iterator>::type_t > >
    static boost::mpl::bool_<true> dummyFunc(U&&)
    {        
        std::cout << "1" << std::endl;
    }
    */
    //catch all
    /*
    static boost::mpl::bool_<false> dummyFunc(...)
    {   
        std::cout << "2" << std::endl;
    }
    */
    static boost::mpl::bool_<false> dummyFunc()
    {   
        std::cout << "3" << std::endl;
    }
    
    public:

    typedef BOOST_TYPEOF(&has_const_iterator<T>::dummyFunc) foo_type;;
    typedef boost::function_traits<foo_type> function_traits;  
    typedef typename boost::function_types::result_type<foo_type>::type type_t;
    //typedef typename std::result_of<has_const_iterator<T>::dummyFunc>::type type_tt;
    typedef typename std::result_of<A::foo>::type type_tt;
};

struct A
{
    int foo()
    {return 3;}
};

int main()
{    
  std::cout << has_const_iterator<std::vector<int> >::dummyFunc() << std::endl;    
  //std::cout << has_const_iterator<A>::value << std::endl ;
}
