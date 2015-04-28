#include <iostream>
#include <string>
#include <vector>

struct JInt
{
    static std::string Signature()
	{
		return "I";
	}
};

struct JBool
{
	static std::string Signature()
	{
		return "Z";
	}
};

namespace detail
{

template<typename T>
struct java_type_to_cpp_type;

template<>
struct java_type_to_cpp_type<JInt>
{
    using type = int;
};

template<>
struct java_type_to_cpp_type<JBool>
{
    using type = bool;
};

}

template<typename T>
using java_type_to_cpp_type = typename detail::java_type_to_cpp_type<T>::type;

template <class>
struct JFunction;

template <class Ret, class... Args>
struct JFunction<Ret(Args...)>
{
	std::string Sig()
	{
		return "()" + Ret().Signature();
	}
    
    auto Execute(java_type_to_cpp_type<Args>... args) -> java_type_to_cpp_type<Ret>
    {
        // You'll have to actually execute something here...
        return java_type_to_cpp_type<Ret>{};
    }
};

int main()
{
    JFunction<JBool(JInt)> jFun;
    std::cout << jFun.Execute(4) << std::endl;
}