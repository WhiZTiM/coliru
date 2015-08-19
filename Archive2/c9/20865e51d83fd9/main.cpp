#include <functional>
#include <iostream>
#include <list>

template<typename... Args>
struct LuaFunction
{
    std::tuple<Args...> args;

    template<unsigned int N>
	struct Dummy
	{
		template<typename Arg>
		static Arg QueryArg();
	};

	template<unsigned int N, typename ArgType>
	static void ProcessArgs()
	{
		Dummy<N>::template QueryArg<ArgType>();
	}

	template<int N, typename ArgType1, typename ArgType2, typename... Rest>
	static void ProcessArgs()
	{
		ProcessArgs<N, ArgType1>();
		ProcessArgs<N-1, ArgType2, Rest...>();
	}

	static void ProcessArgs()
	{
		ProcessArgs<sizeof...(Args), Args...>();
	}
};

template<typename... Args>
template<unsigned int N>
template<>
int LuaFunction<Args...>::Dummy<N>::QueryArg<int>()
{
	std::cout << "#" << N << ": int !" << std::endl;
	return 42;
}

template<typename... Args>
template<unsigned int N>
template<>
float LuaFunction<Args...>::Dummy<N>::QueryArg<float>()
{
	std::cout << "#" << N << ": float !" << std::endl;
	return 3.14f;
}

template<typename>
struct Test;

template<typename R, typename... Args>
struct Test<R(Args...)>
{
	static int static_func()
	{
		LuaFunction<Args...>::ProcessArgs();
		return sizeof...(Args);
	}
};

int main()
{
	std::cout << Test<int(int, float)>::static_func() << std::endl;

	std::getchar();

    return 0;
}
