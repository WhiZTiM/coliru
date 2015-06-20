    #include <iostream>
	#include <type_traits>

	template<typename Head, typename... Tail>
	struct Is_Admitted {
		constexpr static bool value = Is_Admitted<Head>::value && Is_Admitted<Tail...>::value;
	};

	template<>
	template<typename T>
	struct Is_Admitted<T> : public std::false_type{};

	template<> struct Is_Admitted<int> : public std::true_type{};
	template<> struct Is_Admitted<double> : public std::true_type{};

	int main()
	{
		std::cout << Is_Admitted<int, double>::value << '\n';
		std::cout << Is_Admitted<int, char>::value << '\n';
	}