#include <type_traits>

template<typename T,
         typename = typename std::enable_if< std::is_enum<T>::value, T >::type>
bool func( T &t, int x )
{
    return false;
}

enum class Bar { a,b,c };

int main()
{
    Bar bar{Bar::a};
    func(bar, 1);
}
