#include <iostream>
#include <type_traits>
#include <tuple>


template <typename T>
struct function_traits
    : public function_traits<decltype(&T::operator())>
{};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
{
	static const size_t nargs = sizeof...(Args);

	typedef ReturnType result_type;

	template <size_t i>
	struct arg
	{
		typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
	};
};

class ConstString
{
	const char * const begin_;
	unsigned size_;

public:
	template< unsigned N >
	constexpr ConstString(const char(&arr)[N]) : begin_(arr), size_(N - 1) {
		static_assert(N >= 1, "not a string literal");
	}

	constexpr ConstString(const char* arr, unsigned size) : begin_(arr), size_(size) {
	}

	constexpr char operator[](unsigned i) const {
		return begin_[i];
	}

	constexpr unsigned size()  const {
		return size_;
	}
};

constexpr bool EqualImpl(const ConstString str1, const ConstString str2, int n)
{
	return (str1.size() == n) ? true :
		(str1[n] != str2[n]) ? false : EqualImpl(str1, str2, n + 1);
}

constexpr bool Equal(const ConstString str1, const ConstString str2)
{
	return (str1.size() != str2.size()) ? false : EqualImpl(str1, str2, 0);
}

constexpr bool MatchImpl(const ConstString str1, const ConstString str2, unsigned pos1, unsigned pos2, unsigned count)
{
	return (count == 0) ? true :
		(str1[pos1] != str2[pos2]) ? false : MatchImpl(str1, str2, pos1 + 1, pos2 + 1, count - 1);
}

constexpr bool Match(const ConstString str1, const ConstString str2, unsigned pos)
{
	return MatchImpl(str1, str2, pos, 0, str2.size());
}

constexpr unsigned Find(const ConstString str, const char ch, unsigned pos)
{
	return (str.size() <= pos) ? -1 :
		(str[pos] == ch) ? pos : Find(str, ch, pos + 1);
}

constexpr unsigned ParseParameterImpl(ConstString str, unsigned pos, unsigned value)
{
	return (str.size() <= pos) ? value :
		Match(str, "<int>", pos) ? ParseParameterImpl(str, pos + 5, (value << 4) + 1) :
		Match(str, "<char>", pos) ? ParseParameterImpl(str, pos + 6, (value << 4) + 2) :
		ParseParameterImpl(str, pos + 1, value);
			
}

constexpr unsigned ParseParameter(ConstString str)
{
	return ParseParameterImpl(str, 0, 0);
}

template <typename Type>
constexpr bool ValidParam(unsigned param)
{
	return ((param == 1) && std::is_same<int, Type>::value) ||
		((param == 2) && std::is_same<char, Type>::value);
}

template <typename FunctionTraits, unsigned Params, size_t N>
struct ValidationImpl
{
	enum {
		Value = ValidParam<FunctionTraits::arg<N>::type>(Params & 0xf) &&
			ValidationImpl<FunctionTraits, (Params >> 4), N - 1>::Value
	};
};

template <typename FunctionTraits, unsigned Params>
struct ValidationImpl<FunctionTraits, Params, 0>
{
	enum {
		Value = ValidParam<FunctionTraits::arg<0>::type>(Params & 0xf)
	};
};

template <typename FunctionTraits, unsigned Params>
constexpr bool Validation()
{
	return ValidationImpl<FunctionTraits, Params, FunctionTraits::nargs-1>::Value;
}

template <typename FunctionTraits, unsigned Params>
class ParameterValidator
{
public:
	constexpr ParameterValidator()
		: n_(Validation<FunctionTraits, Params>() ? 0 : throw false) {}
private:
	int n_;
};

template <typename Func>
void Foo(ConstString str, Func func)
{
	
}

#define FOO(str, lambda) \
	{ \
		auto func = lambda; \
		constexpr unsigned params = ParseParameter(str); \
		constexpr ParameterValidator<function_traits<decltype(func)>, params> parameter_mismatch; \
	} \
	Foo(str, lambda);

int main()
{
	FOO("<int>", [](int value) {
		std::cout << value << std::endl;
	});

	FOO("<char>", [](char value) {
		std::cout << value << std::endl;
	});

	FOO("asdf <int> zxcv", [](int value) {
		std::cout << value << std::endl;
	});

	FOO("asdf <int> 1234 <char> xsd", [](int value, char ch) {
		std::cout << value << std::endl;
	});

	// 오류
	/*FOO("<int>", [](char value) {
		std::cout << value << std::endl;
	});*/

	/*FOO("asdf <int> 1234 <char> xsd", [](int value, int ch) {
		std::cout << value << std::endl;
	});*/

    return 0;
}

