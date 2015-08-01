
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

namespace manu
    {
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
    
    	template<typename Hash>
    	const auto& get() const
    	{
    		return std::get<element_index<Hash>::value>(static_cast<const tuple_t&>(*this));
        }
        
        template<typename Hash>
        const auto& operator[](Hash)
        {
            return get<Hash>();   
        }
    
    	template<typename... Ts>
    	tuple(Ts&&... elems) : tuple_t{ std::forward<Ts>(elems)... }
    	{}
    };
    
    template<typename Hash, typename Type>
    struct entry
    {
    	using hash = Hash;
    	using type = Type;
    };
    
    template<typename... Entries>
    struct tuple_builder
    {
    	template<typename Seq>
    	struct build;
    
    	template<typename T, T... Seq>
    	struct build<std::integer_sequence<T, Seq...>>
    	{
    		using type = tuple<std::tuple<detail::pair<typename Entries::hash, std::integral_constant<T,Seq>>...>, std::tuple<typename Entries::type...>>;
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
    
    template<typename T, typename... Ts, std::size_t... Is>
    T piecewise_construct_impl(const std::tuple<Ts...>& args, std::index_sequence<Is...>)
    {
        return { std::forward<std::decay_t<Ts>>(std::get<Is>(args))... };   
    }
    
    template<typename T, typename... Ts>
    T piecewise_construct(const std::tuple<Ts...>& args)
    {
        return piecewise_construct_impl<T>(args, std::index_sequence_for<Ts...>{});   
    }
    
    template<std::size_t... Is, typename... Ts, typename T>
    auto collect_and_forward_impl(std::index_sequence<Is...>, const std::tuple<Ts...>& elems, T&& current)
    {
       return std::forward_as_tuple(std::get<Is>(elems)..., std::forward<T>(current));
    }
    
    template<typename... Ts, typename T>
    auto collect_and_forward(const std::tuple<Ts...>& elems, T&& current)
    {
       return collect_and_forward_impl(std::index_sequence_for<Ts...>{}, elems, current);
    }
    
    template<typename... Entries, typename... Ts, typename Hash, typename T, typename... Tail>
    auto make_tuple_impl(tuple_builder<Entries...>, const std::tuple<Ts...>& elems, Hash&&, T&& elem, Tail&&... tail)
    {
        return make_tuple_impl(tuple_builder<Entries..., entry<Hash,T>>{},
                               collect_and_forward(elems, elem),
                               std::forward<Tail>(tail)...);
    }
    
    template<typename... Entries, typename... Ts>
    auto make_tuple_impl(tuple_builder<Entries...>, const std::tuple<Ts...>& elems)
    {
        return piecewise_construct<build_tuple<Entries...>>(elems);
    }
    
    template<typename... Ts>
    auto make_tuple(Ts&&... elems)
    {
    	return make_tuple_impl(tuple_builder<>{}, std::make_tuple(), std::forward<Ts>(elems)...);
    }
    
    template<typename Hash, typename Tuple>
    auto tuple_get(const Tuple& t)
    {
        return t.template get<Hash>();
    }
}

#define h(x) std::integral_constant<foonathan::string_id::detail::hash_type, foonathan::string_id::detail::sid_hash(x)>{}

#define TUPLE_GET(x) manu::tuple_get<std::integral_constant<foonathan::string_id::detail::hash_type, foonathan::string_id::detail::sid_hash(x)>>

int main()
{
	auto t = manu::make_tuple(h("pi"), 3.141592654, 
                              h("e"), 2.71828182846);
    
    std::cout << TUPLE_GET("e")(t) << std::endl;
    std::cout << TUPLE_GET("pi")(t) << std::endl;
}
