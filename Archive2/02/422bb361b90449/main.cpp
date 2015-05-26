template<class, class> struct X{};

template<class> struct Y{};

template<class... Ts>
struct Y<X<Ts...>>{};

int main()
{
    Y<X<int, int>> y;
}
