#include <iostream>
#include <array>
using namespace std;

template<typename ...>
struct typelist {};

template<typename t1>
struct head
{
    using type = t1;  
};

template<typename ...>
struct cartesian_impl;

template<typename t1, typename t2>
struct cartesian_impl<t1,t2>
{
    using type = typelist<t1,t2>;   
};

template<typename t1,typename ... rest>
struct cartesian_impl<t1,typelist<rest...>>
{
    using type = typelist< 
                            typelist<t1,typename head<rest>::type>...
                         >;
    
};

template<typename... tl>
struct cartesian;

template<typename ... t1>
struct cartesian<typelist<t1...>>
{
    using type = typelist<
                            typename cartesian_impl<
                                                      typename head<t1>::type,
                                                      typelist<t1...>
                                                   >::type...
                         >;
    
};

template<class T>
class TD;

int main() {

    TD<typename cartesian<typelist<int,char,bool>>::type> t1;
	return 0;
}