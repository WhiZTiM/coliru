#include <tuple>
#include <iostream>


template<typename S, typename T, std::size_t... I>
  void
  print_tuple_like(S& s, const T& t, std::index_sequence<I...>)
  {
    void* unused[] = { &(s << std::get<I>(t))... };      
    (void)unused;
  }

template<typename S, typename T, typename C = decltype(T::children)>
    S& operator<<(S& s, const T& t)
{
    print_tuple_like(s, t.children, std::make_index_sequence<std::tuple_size<C>::value>{});
    return s;
}

struct X
{
    std::tuple< int, int > children;
    
    X() : children{1,2} {}
};

int main()
{
    std::cout << X() << std::endl;
}
