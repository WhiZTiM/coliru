#include <vector>
#include <iostream>
#include <utility>
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

template<typename Arr, std::size_t... Is>
Msg func2( const Arr& arr, std::index_sequence<Is...> )
{
    Msg msg;
    msg.valueArray = { sizeof...(Is) / 2, ( ( Is % 2 == 0 ) ? std::get< Is / 2 >( arr ).a : std::get< Is / 2 >( arr ).b )... };
    return msg;
}

template<typename... Args>
Msg func(Args... args)
{
    return func2( std::forward_as_tuple( args... ), std::make_index_sequence< 2*sizeof...(Args) >() );
}

int main() {
    Msg msg = func(foo{1,2}, foo{3,4}, foo{5,6});
    for ( int i : msg.valueArray ) std::cout << i << " ";
    std::cout << std::endl;

    func();
}
