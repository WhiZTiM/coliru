#include <iostream>

namespace flop {

    using Float = float (&)();
	
	#define FLOP(name, op)					\
		template <Float f1, Float f2>		\
		struct name {						\
			static constexpr auto value() {	\
				return f1() op f2();		\
			}								\
		};
		
	FLOP(add, + )
	FLOP(sub, - )
	FLOP(mul, * )
	FLOP(div, / )
	FLOP(lt,  < )
	FLOP(gt,  > )
	FLOP(lte, <=)
	FLOP(gte, >=)
	FLOP(eq,  ==)
	FLOP(neq, ==)
	
	#undef FLOP
}

#define CONSTANT(name, value)	\
constexpr float name() {		\
	return value;				\
}

CONSTANT(fourAndAHalf, 4.5f)
CONSTANT(five, 5.0f)
CONSTANT(nine, 9.0f)

template <bool>
struct BoolTxt {
	static constexpr char const *value = "true";
};

template <>
struct BoolTxt<false> {
	static constexpr char const *value = "false";
};

template <class> struct check;

int main() {
	using namespace flop;
	std::cout << BoolTxt<
		gt<
			mul<fourAndAHalf, five>::value, // OMG HAXX
			nine
		>::value()
	>::value << '\n';
}
