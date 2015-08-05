#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <climits> // CHAR_MAX

using u128 = unsigned __int128;
using u64 = std::uint64_t;

namespace detail {
    constexpr char const* find(char const* s, char c) {
		for(;;++s)
			if (*s == c)
				return s;
	}
}

constexpr u128 operator "" _u128( char const* str ) {
	int base=10;
	assert (*str != '-');
	if (*str == '+')
		++str;
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

std::ostream& operator<<(std::ostream& os, unsigned __int128 u) try {
	using namespace std;

	ostream::sentry sentry(os);
	if (!sentry)
		return os;

	auto basefield  = (os.flags() & ios::basefield);

	bool uppercase  = (os.flags() & ios::uppercase),
	     showpos    = (os.flags() & ios::showpos),
	     showbase   = (os.flags() & ios::showbase);

	int base;

	if (basefield == ios::dec)
		base = 10;
	else if (basefield == ios::hex)
		base = 16;
	else /*if (basefield == ios::oct)*/
		base = 8;

	string str(64, '\0');
	auto i = str.size()-1;

	do {
		static const char digits[] = "0123456789abcdef"
		                             "0123456789ABCDEF";
		str[i--] = digits[u%base + 16*uppercase];
		u /= base;
	} while (u != 0);

	auto last_digit_pos = i+1;

	if (showbase) {
		if (basefield == ios::hex) {
			str[i--] = (uppercase? 'X' : 'x');
			str[i--] = '0';
		}
		else if (basefield == ios::oct)
			str[i--] = '0';
	}

	if (showpos)
		str[i--] = '+';

	str.erase(0, i+1);
	last_digit_pos -= i;

	auto& facet = use_facet<numpunct<char>>(os.getloc());
	auto sep      = facet.thousands_sep();
	auto grouping = facet.grouping();

	i=0;
	for (auto pos = str.length();;++i) {
		char to_jump = grouping.empty()? -1 : grouping[min(i, grouping.size()-1)];

		if ((size_t)to_jump >= pos-last_digit_pos
		 || to_jump < 0 || to_jump == CHAR_MAX)
			break;

		pos -= to_jump;
		str.insert(pos, 1, sep);
	}

	if (str.size() < (size_t)os.width()) {
		auto adjustfield = (os.flags() & ios::adjustfield);
		std::size_t pos;
		switch (adjustfield) {
		case ios::left:
			pos = str.size();
		break;
		case ios::right:
			pos = 0;
		break;
		case ios::internal:
			if (showpos)
				pos = 1;
			else if (showbase && base==16)
				pos = 2;
			else
				pos = 0;
		break;
		default: assert(false);
		};
		str.insert(pos, os.width()-str.size(), os.fill());
	}
	os.width(0);

	return os << str;
}
catch (...) {
	auto except = os.exceptions();
	os.exceptions(except & ~std::ios::badbit);
	os.setstate(std::ios::badbit);
	if (except != os.exceptions()) // badbit was set in the exception flags
		throw;
    return os;
}

int main() {
    std::cout << std::hex << std::showpos << std::showbase << std::uppercase << std::setw(50) << std::setfill('0') << std::internal << +0x684F5687ea869;
}