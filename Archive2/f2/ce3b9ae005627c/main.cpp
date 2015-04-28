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

int Unjavafy(JInt jInt)
{
    return 0;
}

bool Unjavafy(JBool jBool)
{
    return true;
}

template <class>
struct JFunction;

template <class Ret>
struct JFunction<Ret()>
{
	std::string Sig()
	{
		return "()" + Ret().Signature();
	}
    
    auto Execute() -> decltype(Unjavafy(Ret()))
    {
        Unjavafy(Ret());
    }
};

template <class Ret, class Arg1>
struct JFunction<Ret(Arg1)>
{
	std::string Sig()
	{
		return "(" + Arg1().Signature() + ")" + Ret().Signature();
	}
    
    auto Execute(decltype(Unjavafy(Arg1())) arg) -> decltype(Unjavafy(Ret()))
    {
        return Unjavafy(Ret());
    }
};

template <class Ret, class Arg1, class Arg2>
struct JFunction<Ret(Arg1, Arg2)>
{
	std::string Sig()
	{
		return "(" + Arg1().Signature() + Arg2().Signature() + ")" + Ret().Signature();
	}
    
    auto Execute(decltype(Unjavafy(Arg1())) arg1, decltype(Unjavafy(Arg2())) arg2) -> decltype(Unjavafy(Ret()))
    {
        return Unjavafy(Ret());
    }
};

int main()
{
    JFunction<JBool(JInt)> jFun;
    std::cout << jFun.Execute(4) << std::endl;
}