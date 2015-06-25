#include <iostream>
#include <utility>
#include <tuple>
 
struct interface 
{
    virtual void foo() = 0;
};
 
struct concrete : interface
{
    std::string _id;
    concrete(std::string id) : _id(id) {}
	void foo() override { std::cout << _id; }
};
 
struct dec1 : interface
{
	interface& _source;
	dec1(interface& source) : _source(source) {}
 
	void foo() override
	{ 
    	std::cout << "(";
		_source.foo();
    	std::cout << ")dec1";         
	}
};

struct dec2 : interface
{
    interface& _source;
	dec2(interface& source) : _source(source) {}
 
	void foo() override
	{ 
    	std::cout << "(";
		_source.foo();
    	std::cout << ")dec2";         
	}
};
 
 struct dec3 : interface
{
    interface& _source;
	dec3(interface& source) : _source(source) {}
 
	void foo() override
	{ 
    	std::cout << "(";
		_source.foo();
    	std::cout << ")dec3";         
	}
};
 
template <typename...>
struct last;
 
template <typename T>
struct last<T> { using type = T; };
 
template <typename T, typename... Ts>
struct last<T, Ts...> { using type = typename last<Ts...>::type; };
 
template <typename... Ts>
using last_t = typename last<Ts...>::type;
 
template <typename, typename...>
struct but_last;

template <typename... Prev, typename Last>
struct but_last<std::tuple<Prev...>, Last>
{
    using type = std::tuple<Prev...>;
};

template <typename... Prev, typename Next, typename... Rest>
struct but_last<std::tuple<Prev...>, Next, Rest...>
{
    using type = typename but_last<std::tuple<Prev..., Next>, Rest...>::type;
};

template <typename... Ts>
using but_last_t = typename but_last<std::tuple<>, Ts...>::type;

template <typename Seq, int I>
struct append;
 
template <int I, int... Is>
struct append<std::integer_sequence<int, Is...>, I>
{
	using type = std::integer_sequence<int, Is..., I>;
};
 
template <typename Seq, int I>
using append_t = typename append<Seq, I>::type;
 
template <int Start, int End, typename Seq>
struct create_sequence_helper;
 
template <int N, typename Seq>
struct create_sequence_helper<N, N, Seq>
{
	using type = Seq;
};
 
template <int Start, int End, typename Seq>
struct create_sequence_helper
{
	using type = typename create_sequence_helper<Start+1, End, append_t<Seq, Start>>::type;  
};
 
template <int Start, int End>
struct create_sequence
{
	using type = typename create_sequence_helper<Start, End, std::integer_sequence<int>>::type;
};
 
template <int Start, int End>
using create_sequence_t = typename create_sequence<Start, End>::type;
 
template <typename Source, typename Decorators, typename Ints = create_sequence_t<0, std::tuple_size<Decorators>::value-1>>
struct decorator_wrapper_helper;
 
template <typename Source, typename... Decorators, int... Ints>
struct decorator_wrapper_helper<Source, std::tuple<Decorators...>, std::integer_sequence<int, Ints...>>
{
    Source _source;
	std::tuple<Decorators...> _tuple;
    
    template <typename... Args>
	decorator_wrapper_helper(Args&&... args) : _source(std::forward<Args>(args)...), _tuple(_source, std::get<Ints>(_tuple)...) {}
};
 
template <typename Source, typename... Decorators>
using first_base_type = decorator_wrapper_helper<Source, but_last_t<std::remove_reference_t<Decorators>...>>;

template <typename... Decorators>
using second_base_type = last_t<std::remove_reference_t<Decorators>...>;
 
 
template <typename Source, typename... Decorators>
struct decorator_wrapper : first_base_type<Source, Decorators...>
                         , public second_base_type<Decorators...>
{
    template <typename... Args>
	decorator_wrapper(Args&&... args)
		: first_base_type<Source, Decorators...>(std::forward<Args>(args)...)
		, second_base_type<Decorators...>(std::get<sizeof...(Decorators)-2>(first_base_type<Source, Decorators...>::_tuple))
	{
	}
};
 
int main() 
{
	concrete t("t1");
	auto w = decorator_wrapper<concrete&, dec3, dec1, dec2, dec3>(t);
    w.foo();
    std::cout << '\n';
    auto x = decorator_wrapper<concrete, dec1, dec2>("t2");
    x.foo();
	return 0;
}