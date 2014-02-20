#include <iostream>
#include <string>
#include <vector>

#include <type_traits>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

template <typename ReturnType, typename WrappedFunctionType, WrappedFunctionType function, typename... WrapperArgumentTypes, typename... WrappedArgumentTypes>
ReturnType FunctionWrapperInternal( WrapperArgumentTypes&&... arguments )
{
    return function( std::forward<WrapperArgumentTypes>( arguments)... );
}

template <typename T>
struct return_type_of;

template <typename ReturnType, typename... Args>
struct return_type_of<ReturnType(Args...)>
{
    typedef ReturnType type;
};


template <typename T>
struct arg_types_of;

template <typename ReturnType, typename... Args>
struct arg_types_of<ReturnType(Args...)>
{
    typedef std::tuple<Args...> type;
};

template <typename ReturnType, typename WrappedFunctionType, WrappedFunctionType function, typename WrappedFunctionReturnType, typename WrappedFunctionArgTypes, typename... WrapperArgumentTypes>
struct function_invoker;
//ReturnType FunctionWrapperInternal( WrapperArgumentTypes&&... arguments );

template <typename ReturnType, typename WrappedFunctionType, WrappedFunctionType function, typename WrappedFunctionReturnType, typename... WrappedFunctionArgTypes, typename... WrapperArgumentTypes>
struct function_invoker<ReturnType, WrappedFunctionType, function, WrappedFunctionReturnType, std::tuple<WrappedFunctionArgTypes...>, WrapperArgumentTypes... >
//ReturnType FunctionWrapperInternal<ReturnType, WrappedFunctionType, function, WrappedFunctionReturnType, std::tuple<WrappedFunctionArgTypes...> >( WrapperArgumentTypes&&... arguments )
{
    ReturnType operator ()( WrapperArgumentTypes... arguments )
    {
        return function( std::forward<WrappedFunctionArgTypes>( arguments )... );
    }
};


//template <typename ReturnType, typename WrappedFunctionType, WrappedFunctionType function, typename... WrapperArgumentTypes>
template <typename ReturnType, typename WrappedFunctionType, WrappedFunctionType function, typename... WrapperArgumentTypes, typename WrappedFunctionReturnType = typename return_type_of<typename std::remove_pointer<WrappedFunctionType>::type>::type, typename WrappedFunctionArgTypes = typename arg_types_of<typename std::remove_pointer<WrappedFunctionType>::type>::type>
ReturnType FunctionWrapper( WrapperArgumentTypes&&... arguments )
{
    return function_invoker<ReturnType, WrappedFunctionType, function, WrappedFunctionReturnType, WrappedFunctionArgTypes, WrapperArgumentTypes...>( )( std::forward<WrapperArgumentTypes>( arguments )... );
    //return FunctionWrapperInternal<ReturnType, WrappedFunctionType
    //return function( std::forward<WrapperArgumentTypes>( arguments)... );
}

int DoSomething( double foo, int bar, const char* cow )
{
    std::cout << "FOO BAR " << bar << std::endl;  
    
    return 99;
}

class RandomTest
{
public:
    operator int( ) const { return 44; }
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    FunctionWrapper<int, decltype(&DoSomething), &DoSomething, float, RandomTest, const char*>( 4.0, RandomTest( ), "adga" );
}
