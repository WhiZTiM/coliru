#include <iostream>
 
namespace meta
{
    template<unsigned int n> struct Count { char data[n]; };
    template<int n> struct ICount : public ICount<n-1> {};
	template<> struct ICount<0> {};
 
    #define MAX_COUNT 64
	#define MAKE_COUNTER( _tag_ ) \
		static ::meta::Count<1> _counter ## _tag_ (::meta::ICount<1>)
	#define GET_COUNT( _tag_ ) \
		(sizeof(_counter ## _tag_ (::meta::ICount<MAX_COUNT + 1>())) - 1)
	#define INC_COUNT( _tag_ ) \
		static ::meta::Count<GET_COUNT(_tag_) + 2> _counter ## _tag_ (::meta::ICount<GET_COUNT(_tag_) + 2>)
}
 
template<int>
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
    test<Test<5>>();
}
