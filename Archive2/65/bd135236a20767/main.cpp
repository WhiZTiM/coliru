#include <cstddef>
using std::size_t;

#include <functional>
#include <utility>
#include <array>
#include <iostream>

enum class MyEnum {
    FOO,
    BAR,
    _size
};

template<MyEnum T>class MyClass {
    public:
    constexpr int doStuff();
  // ...
};
    
//I would like to have the actual implementations of the member functions in a separate source file. I know, that in that case I have to enforce the initialization of the template for each case:

#if 0
//MyClass.cpp
template<MyEnum T> constexpr int MyClass<T>::doStuff() {
  // ...
}
#else
template<> constexpr int MyClass<MyEnum::FOO>::doStuff() { return 0; }
template<> constexpr int MyClass<MyEnum::BAR>::doStuff() { return 1; }
#endif

    template <typename T, size_t N, typename Eval, size_t... Is>
    constexpr auto make_array( Eval const& eval, const std::index_sequence<Is...>)
        -> std::array<T,N>
    {
        return std::array<T,N>{{eval(Is)...}};
    }

    template < typename T, size_t N, typename Eval >
    constexpr auto MakeArray(Eval const& eval)
        -> std::array<T,N>
    {
        return make_array<T,N>(eval,std::make_index_sequence<N>{});
    }

    struct eval {
        constexpr std::function<void()> operator() ( const size_t x ) const {
            return &MyClass<MyEnum(x)>::doStuff;
        }
    };
    
int main(){
    constexpr auto v = MakeArray<std::function<void()>, static_cast<size_t>(MyEnum::_size)>(eval{});
    
    for(auto e : v) e();
}