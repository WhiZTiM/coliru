#include <cstddef>
#include <type_traits>
#include <iostream>
#include <cxxabi.h>
#include <functional>
 
namespace veritas
{
    namespace meta
	{
		template <typename... Ts>
		struct list {};
 
		template <typename... Args>
		struct call {};
 
		namespace placeholders
		{
			template <std::size_t N>
			struct placeholder {};
 
			using _0 = placeholder<0>;
			using _1 = placeholder<1>;
			using _2 = placeholder<2>;
			using _3 = placeholder<3>;
			using _4 = placeholder<4>;
			using _5 = placeholder<5>;
		}
 
		template <typename T>
		struct lambda;
 
		namespace details
		{
			struct recurse
			{
				template <typename tag, typename FunctionExpr, typename... ArgExprs>
				struct apply
				{
					using result = typename apply<tag, meta::call<FunctionExpr, ArgExprs...>>::result;
				};
 
				template <typename tag, typename Arg>
				struct apply<tag, Arg>
				{
					using result = Arg;
				};
 
				template <typename tag, template <typename...> class T, typename... Args>
				struct apply<tag, T<Args...>>
				{
					using result = T<typename apply<tag, Args>::result...>;
				};
			};
		}
 
		namespace details
		{
			struct eval_tag {};
 
			template <typename T>
			struct recurse::apply<eval_tag, meta::lambda<T>>
			{
				using result = meta::lambda<T>;
			};
 
			template <typename FunctionExpr, typename... ArgExprs>
			struct recurse::apply<eval_tag, meta::call<FunctionExpr, ArgExprs...>>
			{
				using function = typename apply<eval_tag, FunctionExpr>::result;
				using result = typename apply<eval_tag, typename function::template apply<
					typename apply<eval_tag, ArgExprs>::result...>::result>::result;
			};
		}
 
		template <typename T, typename... Ts>
		using eval = typename details::recurse::apply<details::eval_tag, T, Ts...>::result;
 
		struct empty
		{
			template <typename MetaClass>
			struct apply;
 
			template <template <typename...> class Container, typename... Args>
			struct apply<Container<Args...>>
			{
				using result = Container<>;
			};
		};
 
		template <typename MetaClass>
		using empty_t = meta::call<empty, MetaClass>;
 
		template <std::size_t N>
		struct get
		{
			template <typename MetaClass, std::size_t Counter = 0>
			struct apply;
 
			template <template <typename...> class Container, typename Arg, typename... Args>
			struct apply<Container<Arg, Args...>, N>
			{
				using result = Arg;
			};
 
			template <template <typename...> class Container, typename Arg, typename... Args, std::size_t K>
			struct apply<Container<Arg, Args...>, K>
			{
				using result = typename apply<Container<Args...>, K+1>::result;
			};
		};
 
		template <std::size_t N, typename MetaClass>
		using get_t = meta::call<meta::get<N>, MetaClass>;
 
		struct push_front
		{
			template <typename MetaClass, typename T>
			struct apply;
 
			template <template <typename...> class Container, typename... Args, typename T>
			struct apply<Container<Args...>, T>
			{
				using result = Container<T, Args...>;
			};
		};
 
		template <typename MetaClass, typename T>
		using push_front_t = meta::call<meta::push_front, MetaClass, T>;
 
		struct push_back
		{
			template <typename MetaClass, typename T>
			struct apply;
 
			template <template <typename...> class Container, typename... Args, typename T>
			struct apply<Container<Args...>, T>
			{
				using result = Container<Args..., T>;
			};
		};
 
		template <typename MetaClass, typename T>
		using push_back_t = meta::call<meta::push_back, MetaClass, T>;
 
		struct head
		{
			template <typename MetaClass>
			struct apply;
 
			template <template <typename...> class Container, typename Arg, typename... Args>
			struct apply<Container<Arg, Args...>>
			{
				using result = Arg;
			};
		};
 
		template <typename MetaClass>
		using head_t = meta::call<meta::head, MetaClass>;
 
		struct tail
		{
			template <typename MetaClass>
			struct apply;
 
			template <template <typename...> class Container, typename Arg, typename... Args>
			struct apply<Container<Arg, Args...>>
			{
				using result = Container<Args...>;
			};
		};
 
		template <typename MetaClass>
		using tail_t = meta::call<meta::tail, MetaClass>;
 
		struct last
		{
			template <typename MetaClass>
			struct apply;
 
			template <template <typename...> class Container, typename Arg>
			struct apply<Container<Arg>>
			{
				using result = Arg;
			};
 
			template <template <typename...> class Container, typename Arg, typename... Args>
			struct apply<Container<Arg, Args...>>
			{
				using result = typename apply<Container<Args...>>::result;
			};
		};
 
		template <typename MetaClass>
		using last_t = meta::call<meta::last, MetaClass>;
 
		struct find
		{
			template <typename MetaClass, typename T>
			struct apply;
 
			template <template <typename...> class Container, typename T>
			struct apply<Container<>, T>
			{
				using result = std::false_type;
			};
 
			template <template <typename...> class Container, typename... Args, typename T>
			struct apply<Container<T, Args...>, T>
			{
				using result = std::true_type;
			};
 
			template <template <typename...> class Container, typename Arg, typename... Args, typename T>
			struct apply<Container<Arg, Args...>, T>
			{
				using result = typename apply<Container<Args...>, T>::result;
			};
		};
 
		template <typename MetaClass, typename T>
		using find_t = meta::call<meta::find, MetaClass, T>;
 
		struct contains
		{
			template <typename MetaClass, typename Ts>
			struct apply;
 
			template <typename MetaClass, template <typename...> class Container>
			struct apply<MetaClass, Container<>>
			{
				using result = std::true_type;
			};
 
			template <typename MetaClass, template <typename...> class Container, typename Arg, typename... Args>
			struct apply<MetaClass, Container<Arg, Args...>> 
			{
				using recur = typename apply<MetaClass, Container<Args...>>::result;
 
				using result = std::integral_constant<bool,
					       meta::eval<meta::find_t<MetaClass, Arg>>::value && recur::value>;
			};
		};
 
		template <typename MetaClass, typename Ts>
		using contains_t = meta::call<meta::contains, MetaClass, Ts>;
 
		struct fmap
		{
			template <typename MetaClass, typename Function>
			struct apply;
 
			template <template <typename...> class Container, typename Function>
			struct apply<Container<>, Function>
			{
				using result = Container<>;
			};
 
			template <template <typename...> class Container, typename Function, typename Arg, typename... Args>
			struct apply<Container<Arg, Args...>, Function>
			{
				using result = meta::push_front_t<typename apply<Container<Args...>, Function>::result, 
				                                  meta::call<Function, Arg>>;
			};
		};
 
		template <typename MetaClass, typename Function>
		using fmap_t = meta::call<meta::fmap, MetaClass, Function>;
 
		struct concat
		{
			template <typename MetaClass1, typename MetaClass2>
			struct apply;
 
			template <template <typename...> class Container, typename... Args1, typename... Args2>
			struct apply<Container<Args1...>, Container<Args2...>>
			{
				using result = Container<Args1..., Args2...>;
			};
		};
 
		template <typename MetaClass1, typename MetaClass2>
		using concat_t = meta::call<meta::concat, MetaClass1, MetaClass2>;
 
		struct filter
		{
			template <typename MetaClass, typename Pred>
			struct apply;
 
			template <template <typename...> class Container, typename Pred>
			struct apply<Container<>, Pred>
			{
				using result = Container<>;
			};
 
			template <template <typename...> class Container, typename Arg, typename... Args, typename Pred>
			struct apply<Container<Arg, Args...>, Pred>
			{
				using result = meta::concat_t<std::conditional_t<meta::eval<Pred, Arg>::value,
				                                                           Container<Arg>,
				                                                           Container<>>,
				                                         typename apply<Container<Args...>, Pred>::result>;
			};
		};
 
		template <typename MetaClass, typename Pred>
		using filter_t = meta::call<meta::filter, MetaClass, Pred>; 
 
		struct reverse
		{
			template <typename MetaClass, typename Accumulator = meta::empty_t<MetaClass>>
			struct apply;
 
			template <template <typename...> class Container, typename Accumulator>
			struct apply<Container<>, Accumulator>
			{
				using result = Accumulator;
			};
 
			template <template <typename...> class Container, typename Arg, typename... Args, typename Accumulator>
			struct apply<Container<Arg, Args...>, Accumulator>
			{
				using result = typename apply<Container<Args...>, meta::push_front_t<Accumulator, Arg>>::result;
			};
		};
 
		template <typename MetaClass>
		using reverse_t = meta::call<meta::reverse, MetaClass>;
 
		namespace details	
		{
			template <typename... Ts>
			struct replace_placeholders_tag {};
 
			template <typename... Ts, std::size_t N>
			struct recurse::apply<replace_placeholders_tag<Ts...>, meta::placeholders::placeholder<N>>
			{
				using result = meta::get_t<N, meta::list<Ts...>>;
			};
 
		    template <typename T, typename... Ts>
		    using replace_placeholders_t = typename details::recurse::apply<details::replace_placeholders_tag<Ts...>, T>::result;
		}
        
		template <typename T>
		struct lambda
		{
			template <typename... Ts>
			struct apply
			{
				using replaced = details::replace_placeholders_t<T, Ts...>;
				using result = meta::eval<replaced>;	
			};
		};
 
		template <typename T, typename... Args>
		using lambda_t = meta::call<lambda<T>, Args...>;
	}
}
 
template <typename T>
const char * type_name()
{
	return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
}
 
using namespace veritas;
using namespace veritas::meta::placeholders;
 
struct are_same
{
	template <typename T1, typename T2>
	struct apply
	{
		using result = std::integral_constant<bool, std::is_same<T1, T2>::value>;
	};
};
 
template <typename T1, typename T2>
using are_same_t = meta::call<are_same, T1, T2>;
 
struct wrap
{
	template <typename T> struct wrapper {};
 
	template <typename T>
	struct apply
	{
		using result = wrapper<T>;
	};
};
 
template <typename T>
using wrap_t = meta::call<wrap, T>;
 
int main()
{
	using t1 = meta::list<int, char, bool, float>;
	using t2 = meta::push_front_t<t1, double>;
	using t3 = meta::push_back_t<t1, double>;
	using t4 = meta::find_t<t1, char>;
	using t5 = meta::find_t<t1, double>;
	using t6 = meta::contains_t<t1, meta::list<int, char>>;
	using t7 = meta::contains_t<t1, meta::list<int, double>>;
	using t8 = meta::fmap_t<t1, wrap>;
	using t9 = meta::reverse_t<t1>;
	using t10 = meta::fmap_t<t1, meta::lambda<are_same_t<_0, bool>>>;
 
	std::cout << type_name<meta::eval<t1>>() << '\n';
	std::cout << type_name<meta::eval<t2>>() << '\n';
	std::cout << type_name<meta::eval<t3>>() << '\n';
	std::cout << type_name<meta::eval<t4>>() << '\n';
	std::cout << type_name<meta::eval<t5>>() << '\n';
	std::cout << type_name<meta::eval<t6>>() << '\n';
	std::cout << type_name<meta::eval<t7>>() << '\n';
	std::cout << type_name<meta::eval<t8>>() << '\n';
	std::cout << type_name<meta::eval<t9>>() << '\n';
	std::cout << type_name<meta::eval<t10>>() << '\n';
}