#include <type_traits>
#include <iostream>

template <typename Type>
struct RemoveQualifier_
{
    using type = Type;
};

template <typename ReturnType, typename... Arguments>
struct RemoveQualifier_<ReturnType(Arguments...)const>
{
    using type = ReturnType(Arguments...);
};

template <typename Function>
using RemoveQualifier = typename RemoveQualifier_<Function>::type;

template <class C, typename F>
RemoveQualifier<F>* ExtractFunction(F C::*);

template <typename Lambda>
auto ToFunctionPointer(Lambda&& lambda) -> decltype(ExtractFunction(&Lambda::operator()))
{
    return lambda;
}

int main()
{
    auto function1 = ToFunctionPointer([](){ std::cout << "Usual lambda without a capture list." << std::endl; });    
    auto function2 = ToFunctionPointer([](int i) mutable { std::cout << "Mutable lambda without a capture list. Parameter value: " << i << std::endl; });
    
    function1();
    function2(42);
}
