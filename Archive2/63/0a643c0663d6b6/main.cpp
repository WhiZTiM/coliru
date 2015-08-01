// u128-UDL by Columbo

#include <cassert>

using u128 = unsigned __int128;

namespace detail {
    constexpr char const* find(char const* s, char c) {
		for(;;++s)
			if (*s == c)
				return s;
	}
}

constexpr u128 operator "" _u128( char const* str ) {
    assert (*str != '-');
	if (*str == '+')
		++str;

	int base=10;
	if (*str == '0') {
		++str;
		if (*str == 0)
				return 0;
		if (*str == 'X' || *str == 'x') {
			base = 16;
			++str;
		}
		else
			base = 8;
	}

	char const digits[] = "0123456789ABCDEF";
	u128 res = 0;
	for (; char c = *str; ++str) {
		const u128 max = -1;
		assert(max/base >= res);
		res *= base;
		auto digit = detail::find(digits, c >= 'a' && c <= 'z'? c - ('a'-'A') : c) - digits;
		assert(max-digit >= res);
		res += digit;
	}

	return res;
}

#include <iostream>
int main() {
    std::cout << (int)(123456789123456789123789_u128 * 654684 % 456); 
}