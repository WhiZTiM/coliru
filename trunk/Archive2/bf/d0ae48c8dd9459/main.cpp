#include <iostream>
 
namespace meta
{
    template<unsigned int n> struct Count { char data[n]; };
    template<int n> struct ICount : public ICount<n-1> {};
	template<> struct ICount<0> {};
 
	#define _MAX_COUNT 64
	#define GET_COUNT( _tag_ ) (sizeof(_counter ## _tag_ (::meta::ICount<_MAX_COUNT + 1>())) - 1)
    #define _DEFINE_COUNTER( _tag_ , _n_ ) static ::meta::Count< _n_ > _counter ## _tag_ (::meta::ICount< _n_ >)
    #define MAKE_COUNTER( _tag_ ) _DEFINE_COUNTER(_tag_, 1)
	#define INC_COUNT( _tag_ )    _DEFINE_COUNTER(_tag_, GET_COUNT(_tag_)+2)
}
 
 
struct Test
{
    MAKE_COUNTER( uu );
 
	static const unsigned int a = GET_COUNT( uu );
	INC_COUNT( uu );
	static const unsigned int b = GET_COUNT( uu );
	INC_COUNT( uu );
	static const unsigned int c = GET_COUNT( uu );
    INC_COUNT( uu );
    static const unsigned int d = GET_COUNT( uu );
 
};
 
template<typename T>
void test()
{
    std::cout << T::a << " " << T::b << " " << T::c << " " << T::d << "\n";
}
 
int main()
{
    test<Test>();
}
