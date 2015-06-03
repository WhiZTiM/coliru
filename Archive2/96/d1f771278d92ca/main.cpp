#include <iostream>
#include <string>

namespace Squarion
{
namespace detail
{
    /// Compile-time counter, from SPARK Particle Engine
	template<unsigned int n> struct Count { char data[n]; };
	template<int n> struct ICount : public ICount<n-1> {};
	template<> struct ICount<0> {};

	#define MAX_COUNT 64
	#define MAKE_COUNTER( _tag_ ) \
		static Squarion::detail::Count<1> _count_ ## _tag_ (Squarion::detail::ICount<1>)
	#define GET_COUNT( _tag_ ) \
		((sizeof(_count_ ## _tag_ (Squarion::detail::ICount<MAX_COUNT + 1>())) / sizeof(bool)) - 1)
	#define INC_COUNT( _tag_ ) \
		static Squarion::detail::Count<GET_COUNT(_tag_) + 2> _count_ ## _tag_ (Squarion::detail::ICount<GET_COUNT(_tag_) + 2>)
}
}

struct Test
{
	MAKE_COUNTER(cc);								// cc = 0
	static const unsigned int a = GET_COUNT(cc);	// cc = 0
	INC_COUNT(cc);									// cc = 1
	enum { b = GET_COUNT(cc) };						// cc = 1
	static const unsigned int c = GET_COUNT(cc);	// cc = 1
	INC_COUNT(cc);									// cc = 2
	enum { d = GET_COUNT(cc) };						// cc = 2
	INC_COUNT(cc);									// cc = 3
	enum { e = GET_COUNT(cc) };						// cc = 3
	INC_COUNT(cc);									// cc = 4
	INC_COUNT(cc);									// cc = 5
	static const unsigned int f = GET_COUNT(cc);	// cc = 5
	static const unsigned int g = GET_COUNT(cc);	// cc = 5
	INC_COUNT(cc);									// cc = 6
	static const unsigned int h = GET_COUNT(cc);	// cc = 6
};

#define PRINT( x, y ) std::cout << #x "::" #y " = " << x::y << "\n"
int main()
{
	PRINT(Test, a);
	PRINT(Test, b);
	PRINT(Test, c);
	PRINT(Test, d);
	PRINT(Test, e);
	PRINT(Test, f);
	PRINT(Test, g);
	PRINT(Test, h);
}
