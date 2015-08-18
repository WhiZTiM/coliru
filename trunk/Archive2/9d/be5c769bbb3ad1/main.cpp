#include <cstdint>
#include <iostream>
#include <sstream>
#include <limits>

struct version
{
    constexpr version(std::size_t major = 0,
					  std::size_t minor = 0,
					  std::size_t patchlevel = 0)
		: major{major}
		, minor{minor}
		, patchlevel{patchlevel}
	{

	}

	size_t major = 0;
	size_t minor = 0;
	size_t patchlevel = 0;

	std::string string() const;
};

std::ostream& operator<<(std::ostream& os, const version& v) {
	return os << v.major << "." << v.minor << "." << v.patchlevel;
}

std::string version::string() const
{
	std::ostringstream oss;
	oss << *this;
	return oss.str();
}


template<typename T, T... Elements>
struct sequence {
	constexpr sequence() {}
	static const std::size_t npos = std::numeric_limits<std::size_t>::max();
	static constexpr std::size_t length() {
		return sizeof...(Elements);
	}
};

template<typename T>
constexpr auto pop(sequence<T>)
{
	return sequence<T>{};
}

template<typename T, T Head, T... Tail>
constexpr auto pop(sequence<T, Head, Tail...>)
{
	return sequence<T, Tail...>{};
}

template<typename T, T Head, T... Tail>
constexpr T get_nth_impl(sequence<T, Head, Tail...>, std::integral_constant<std::size_t, 0> = {})
{
	return Head;
}

template<std::size_t N, typename T, T Head, T... Tail>
constexpr T get_nth_impl(sequence<T, Head, Tail...> s, std::integral_constant<std::size_t, N> idx = {})
{
	return get_nth_impl(pop(s), std::integral_constant<std::size_t, N - 1>{});
}

template<std::size_t N, typename T, T Head, T... Tail>
constexpr T get_nth(sequence<T, Head, Tail...> s, std::integral_constant<std::size_t, N> idx = {})
{
	static_assert(sizeof...(Tail) >= N, "index out of bounds");
	return get_nth_impl(s, idx);
}


template<typename T>
constexpr std::size_t find_impl(sequence<T>, T, std::size_t)
{
	return sequence<T>::npos;
}

template<typename T, T Head, T... Tail>
constexpr std::size_t find_impl(sequence<T, Head, Tail...>, T value, std::size_t index)
{
	return
		(Head == value)
		? index
		: find_impl(sequence<T, Tail...>{}, value, index + 1);
}

template<typename T, T... Elements>
constexpr std::size_t find(sequence<T, Elements...> s, T value)
{
	return find_impl(s, value, 0);
}

template<typename T, T... Reversed>
constexpr auto reverse(sequence<T>, sequence<T, Reversed...> B = {})
{
	return B;
}

template<typename T, T Head, T... Tail, T... Reversed>
constexpr auto reverse(sequence<T, Head, Tail...>, sequence<T, Reversed...> = {})
{
	return reverse(sequence<T, Tail...>{}, sequence<T, Head, Reversed...>{});
}

template<typename T>
constexpr T accumulate_digits_impl(sequence<T>, T = 0)
{
	return T{ 0 };
}

template<typename T, T Head, T... Tail>
constexpr T accumulate_digits_impl(sequence<T, Head, Tail...>, T exponent = 1)
{
	return exponent * Head + accumulate_digits_impl(sequence<T, Tail...>{}, 10 * exponent);
}

template<typename T, T... Elements>
constexpr T accumulate_digits(sequence<T, Elements...> s)
{
	return accumulate_digits_impl(reverse(s));
}

template<typename Sequence>
constexpr auto pop_n_impl(Sequence s, std::integral_constant<std::size_t, 0>)
{
	return s;
}

template<std::size_t N, typename Sequence>
constexpr auto pop_n_impl(Sequence s, std::integral_constant<std::size_t, N>)
{
	return pop_n_impl(pop(s), std::integral_constant<std::size_t, N - 1>{});
}

template<std::size_t N, typename T, T... Elements>
constexpr auto pop_n(sequence<T, Elements...> s)
{
	return pop_n_impl(s, std::integral_constant<std::size_t, N>{});
}

//list being trimmed is exhausted, return what we have
template<std::size_t Length, typename T, T... Trimmed>
constexpr auto subsequence_impl(sequence<T>, sequence<T, Trimmed...> result, std::integral_constant<std::size_t, Length>)
{
	return result;
}

//number of elements has been reached
template<typename T, T Head, T... Tail, T... Trimmed>
constexpr auto subsequence_impl(sequence<T, Head, Tail...>, sequence<T, Trimmed...> result, std::integral_constant<std::size_t, 0>)
{
	return result;
}

template<std::size_t Length, typename T, T Head, T... Tail, T... Trimmed>
constexpr auto subsequence_impl(sequence<T, Head, Tail...> A, sequence<T, Trimmed...>, std::integral_constant<std::size_t, Length>)
{
	return subsequence_impl(pop(A), sequence<T, Trimmed..., Head>{}, std::integral_constant<std::size_t, Length - 1>{});
}

template<std::size_t Start, std::size_t End, typename T, T... Elements>
constexpr auto subsequence(sequence<T, Elements...> s)
{
	return subsequence_impl(pop_n<Start>(s), sequence<T>{}, std::integral_constant<std::size_t, End - Start>{});
}

template<typename To, typename From, To... Converted>
constexpr auto cast_sequence(sequence<From>, sequence<To, Converted...> result)
{
	return result;
}

template<typename To, typename From, From Head, From... Tail, To... Converted>
constexpr auto cast_sequence(sequence<From, Head, Tail...>, sequence<To, Converted...> = {})
{
	return cast_sequence(sequence<From, Tail...>{}, sequence<To, Converted..., static_cast<To>(Head)>{});
}


template<char... chars>
constexpr auto operator"" _version()
{
	using char_seq0 = sequence<char, chars...>;
	using seq0 = sequence<char, (chars - '0')...>;
	using sep0 = std::integral_constant<std::size_t, find(char_seq0{}, '\'')>;
	using major_seq = decltype(cast_sequence<std::size_t>(subsequence<0, sep0::value>(seq0{})));
	using major = std::integral_constant<std::size_t, accumulate_digits(major_seq{})>;

	using char_seq1 = decltype(subsequence<sep0::value + 1, seq0::length()>(char_seq0{}));
	using seq1 = decltype(subsequence<sep0::value + 1, seq0::length()>(seq0{}));
	using sep1 = std::integral_constant<std::size_t, find(char_seq1{}, '\'')>;
	using minor_seq = decltype(cast_sequence<std::size_t>(subsequence<0, sep1::value>(seq1{})));
	using minor = std::integral_constant<std::size_t, accumulate_digits(minor_seq{})>;

	using seq2 = decltype(subsequence<sep1::value + 1, seq1::npos>(seq1{}));

	using patch_seq = decltype(cast_sequence<std::size_t>(subsequence<0, seq2::npos>(seq2{})));
	using patch = std::integral_constant<std::size_t, accumulate_digits(patch_seq{})>;

	return version{ major::value, minor::value, patch::value };
}

int main() {
	constexpr version ver = 1035400'546'1103244_version;

	std::cout << ver << "\n";
}
