#include <vector>
#include <iostream>
#include <type_traits>
#include <tuple>

struct foo
{
    foo(int a, int b)
        : a(a), b(b) {}
    int a;
    int b;
};

struct Msg
{
    std::vector<int> valueArray;    
};

template<typename Arg, std::size_t... Is>
Msg func2( Arg* arr, std::index_sequence<Is...> )
{
    Msg msg;
    msg.valueArray = { sizeof...(Is) / 2, ( ( Is % 2 == 0 ) ? arr[ Is / 2 ]->a : arr[ Is / 2 ]->b )... };
    return msg;
}

template<typename... Args>
Msg func(Args... args)
{
    std::common_type_t<Args...>* arr[] = { &args... };
    return func2( arr, std::make_index_sequence< 2*sizeof...(Args) >() );
}

int main() {
    Msg msg = func(foo{1,2}, foo{3,4}, foo{5,6});
    for ( int i : msg.valueArray ) std::cout << i << " ";
    std::cout << std::endl;
}
