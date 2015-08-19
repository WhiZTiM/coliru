#include <functional>
#include <iostream>
#include <list>

template<typename Arg>
static Arg QueryArg(unsigned int N);

template<>
int QueryArg<int>(unsigned int N)
{
    std::cout << "#" <<N << ": int !" << std::endl;
	return 42;
}

template<>
float QueryArg<float>(unsigned int N)
{
	std::cout << "#" << N << ": float !" << std::endl;
	return 3.14f;
}

template<typename... Args>
struct LuaFunction
{
    std::tuple<Args...> args;

	template<unsigned int N, typename ArgType>
	void ProcessArgs()
	{
		std::get<N>(args) = QueryArg<ArgType>(N);
	}

	template<int N, typename ArgType1, typename ArgType2, typename... Rest>
	void ProcessArgs()
	{
		ProcessArgs<N, ArgType1>();
		ProcessArgs<N+1, ArgType2, Rest...>();
	}

	void ProcessArgs()
	{
		ProcessArgs<0, Args...>();
	}
};

template<typename>
struct Test;

template<typename R, typename... Args>
struct Test<R(Args...)>
{
	static int static_func()
	{
		LuaFunction<Args...> func;
        func.ProcessArgs();
		return sizeof...(Args);
	}
};

int main()
{
	std::cout << Test<int(int, float)>::static_func() << std::endl;

	std::getchar();

    return 0;
}
