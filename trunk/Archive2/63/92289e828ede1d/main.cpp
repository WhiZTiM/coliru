
#include <tuple>
#include <cstdint>
#include <iostream>

namespace foonathan {
    namespace string_id {
		namespace detail
		{
			using hash_type = std::uint64_t;

			constexpr hash_type fnv_basis = 14695981039346656037ull;
			constexpr hash_type fnv_prime = 109951162821ull;

			// FNV-1a 64 bit hash
			constexpr hash_type sid_hash(const char *str, hash_type hash = fnv_basis) noexcept
			{
				return *str ? sid_hash(str + 1, (hash ^ *str) * fnv_prime) : hash;
			}
		}
	}
} // foonathan::string_id::detail

namespace detail
{
	template <typename x>
	struct no_decay { using type = x; };

	template <typename key, typename value>
	struct pair { };

	template <typename ...xs>
	struct inherit : xs... { };

	template <typename key, typename value>
	static no_decay<value> lookup(pair<key, value>*);

	template <typename key, typename ...pairs>
	using at_key = typename decltype(lookup<key>((inherit<pairs...>*)nullptr))::type;
}

template<const char* str>
using hash = std::integral_constant<foonathan::string_id::detail::hash_type, foonathan::string_id::detail::sid_hash(str)>;

template<typename Indices, typename Types>
struct tuple;

template<typename... Indices, typename... Types>
struct tuple<std::tuple<Indices...>, std::tuple<Types...>> : public std::tuple<Types...>
{
	using tuple_t = std::tuple<Types...>;

	template<typename key>
	using element_index = detail::at_key<key, Indices...>;

	template<const char* name>
	const auto& get() const
	{
		return std::get<element_index<hash<name>>::value>(static_cast<const tuple_t&>(*this));
	}

	template<typename... Ts>
	tuple(Ts&&... elems) : tuple_t{ std::forward<Ts>(elems)... }
	{}
};

template<const char* Name, typename T>
struct entry
{
	static constexpr const char* name = Name;
	using type = T;
};

template<typename... Entries>
struct tuple_builder
{
	template<typename Seq>
	struct build;

	template<typename T, T... Seq>
	struct build<std::integer_sequence<T, Seq...>>
	{
		using type = tuple<std::tuple<detail::pair<hash<Entries::name>, std::integral_constant<T,Seq>>...>, std::tuple<typename Entries::type...>>;
	};

	using type = typename build<std::index_sequence_for<Entries...>>::type;
};

template<typename... Entries>
using build_tuple = typename tuple_builder<Entries...>::type;

template<const char* Str>
struct str
{
	static constexpr const char* value = Str;
};

template<const char*... Names, typename... Ts>
build_tuple<entry<Names, std::decay_t<Ts>>...> make_tuple(Ts&&... elems)
{
	return { std::forward<Ts>(elems)... };
}

constexpr char pi[] = "pi";
constexpr char e[] = "e";

int main()
{
	auto t = make_tuple<pi, e>(3.141592654, 2.71828182846);
    
    std::cout << t.get<pi>() << std::endl;
    std::cout << t.get<e>() << std::endl;
}
