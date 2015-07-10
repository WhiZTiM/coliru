#include <iostream>
#include <type_traits>
#include <tuple>
#include <vector>
#include <functional>
 
template <typename Tuple, typename Component>
struct has_component_helper;
 
template <typename Component>
struct has_component_helper<std::tuple<>, Component>
{
    static const constexpr bool value = false;
};
 
template <typename Component, typename... Rest>
struct has_component_helper<std::tuple<Component, Rest...>, Component>
{
	static const constexpr bool value = true; 
};
 
template <typename Component, typename Arg, typename... Rest>
struct has_component_helper<std::tuple<Arg, Rest...>, Component>
{
	static const constexpr bool value = has_component_helper<std::tuple<Rest...>, Component>::value;
};
 
template <typename Tuple, typename Component>
struct has_component : std::integral_constant<bool, has_component_helper<Tuple, Component>::value> {};
 
template <typename, typename>
struct has_components_helper;
 
template <typename Tuple>
struct has_components_helper<Tuple, std::tuple<>>
{
	static constexpr bool value = true;
};
 
template <typename Tuple, typename Component, typename... Rest>
struct has_components_helper<Tuple, std::tuple<Component, Rest...>>
{
	static constexpr bool value = has_component<Tuple, Component>::value &&
		has_components_helper<Tuple, std::tuple<Rest...>>::value;
};
 
template <typename Tuple, typename Components>
struct has_components : std::integral_constant<bool, has_components_helper<Tuple, Components>::value> {};
 
template <typename, typename>
struct concat;
 
template <typename... Comps1, typename... Comps2>
struct concat<std::tuple<Comps1...>, std::tuple<Comps2...>>
{
	using type = std::tuple<Comps1..., Comps2...>;
};
 
template <typename T1, typename T2>
using concat_t = typename concat<T1, T2>::type;
 
template <typename T1, typename T2>
struct filter;
 
template <typename... Components>
struct filter<std::tuple<>, std::tuple<Components...>>
{
	using type = std::tuple<>;
};
 
template <typename LFirst, typename... LRest, typename... Components>
struct filter<std::tuple<std::vector<LFirst>, std::vector<LRest>...>, std::tuple<Components...>>
{
	using type = concat_t<std::conditional_t<has_components<LFirst, std::tuple<Components...>>::value,
	                          std::tuple<std::vector<LFirst>>,
	                          std::tuple<>>,
	                      typename filter<std::tuple<std::vector<LRest>...>, std::tuple<Components...>>::type>;
};
 
template <typename T1, typename T2>
using filter_t = typename filter<T1, T2>::type;
 
template <typename... Components>
struct for_each_h;
 
template <>
struct for_each_h<>
{
	template <typename Tuple, typename Fun>
	static void call(Tuple&, Fun) {}
};
 
template <typename Component, typename... Rest>
struct for_each_h<Component, Rest...>
{
	template <typename Tuple, typename Fun>
	static void call(Tuple& tuple, Fun fun)
	{
		for (auto& elem : std::get<Component>(tuple))
		{
			fun(elem);
		}
		for_each_h<Rest...>::template call(tuple, fun);
	}
};
 
template <typename... Components, typename Fun>
void for_each(std::tuple<Components...>& tuple, Fun fun)
{
	for_each_h<Components...>::template call(tuple, fun);
}
 
template <typename Tuple>
struct relevant_helper;
 
template <typename... Components>
struct relevant_helper<std::tuple<Components...>>
{
	template <typename Tuple>
	static auto call(Tuple& tuple)
	{
		return std::make_tuple(std::ref(std::get<Components>(tuple))...);
	}
};
 
template <typename... Objects>
struct engine
{
	std::tuple<std::vector<Objects>...> _vecs;
 
	template <typename Object, typename... Args>
	void add_entity(Args&&... args)
	{
		std::get<std::vector<Object>>(_vecs).emplace_back(std::forward<Args>(args)...);
	}
 
	template <typename... Components>
	auto get_relevant()
	{
		return relevant_helper<filter_t<decltype(_vecs), std::tuple<Components...>>>::template call(_vecs);
	}
};
 
int main()
{
	using class1 = std::tuple<int, char, bool>;
	using class2 = std::tuple<int, char, float>;
	using class3 = std::tuple<int, bool, float>;
	engine<class1, class2, class3> engine;
	auto t = engine.get_relevant<int, char>();
	engine.add_entity<class1>(0, 'a', true);
	engine.add_entity<class2>(1, 'a', 0.f);
	engine.add_entity<class3>(2, true, 0.f);
	for_each(t, [](auto t){ std::cout << std::get<int>(t) << " " << std::get<char>(t) << std::endl; });
	return 0;
}