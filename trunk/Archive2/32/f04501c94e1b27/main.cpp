#include <iostream>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <typeinfo>

template<uintmax_t Value>
struct A{
    enum {value = Value};
	using type = std::conditional_t<
		(Value <= std::numeric_limits<uint8_t>::max()), uint8_t,
			std::conditional_t<
				(Value <= std::numeric_limits<uint16_t>::max()), uint16_t,
					std::conditional_t<
						(Value <= std::numeric_limits<uint32_t>::max()), uint32_t,
							std::conditional_t<
								(Value <= std::numeric_limits<uint64_t>::max()), uint64_t, uintmax_t
							>
					>
			>
	>;
};

template<uintmax_t Value>
using A_t = typename A<Value>::type;

int main() {
	A_t<std::numeric_limits<uint8_t>::max()> a;
	A_t<std::numeric_limits<uint16_t>::max()> b;
	A_t<std::numeric_limits<uint32_t>::max()> c;
	A_t<std::numeric_limits<uint64_t>::max()> d;
	
	std::cout << typeid(a).name() << ' ' << typeid(b).name() << ' ' << typeid(c).name() << ' ' << typeid(d).name();
	
	return 0;
}
